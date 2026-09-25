#!/usr/bin/env node
// @ts-check

import { readFile, writeFile } from 'node:fs/promises';
import Path from 'node:path';
import Url from 'node:url';

const EXIT_SUCCESS = 0;
const EXIT_FAILURE = 1;
const RELEASE_VERSION_PATTERN =
  /^(?<major>0|[1-9]\d*)\.(?<minor>0|[1-9]\d*)\.(?<patch>0|[1-9]\d*)$/;

export async function main(ctx) {
  const args = ctx.process.argv.slice(2);
  const dryRun = args.includes('--dry-run');
  const checkOnly = args.includes('--check');
  const increment = args.find((arg) => !arg.startsWith('--'));
  const versionPath = Path.resolve(
    Path.dirname(Url.fileURLToPath(import.meta.url)),
    '..',
    'VERSION'
  );
  const portManifestPath = Path.resolve(
    Path.dirname(versionPath),
    'share/vcpkg/ports/stoneydsp/vcpkg.json'
  );

  const current = String(await readFile(versionPath, 'utf8')).trim();
  const parsed = parseVersion(current);
  const portManifest = JSON.parse(await readFile(portManifestPath, 'utf8'));
  const manifestVersion = String(portManifest['version-semver'] ?? '');
  if (manifestVersion !== formatReleaseVersion(parsed)) {
    throw new Error(
      `VERSION (${formatReleaseVersion(parsed)}) and vcpkg manifest (${manifestVersion}) differ.`
    );
  }

  if (checkOnly) {
    ctx.console.log(formatReleaseVersion(parsed));
    return EXIT_SUCCESS;
  }

  if (!increment || !['patch', 'minor', 'major'].includes(increment)) {
    ctx.console.error(
      'Usage: node scripts/bump-version.mjs <patch|minor|major> [--dry-run]'
    );
    return EXIT_FAILURE;
  }

  const nextVersion = formatReleaseVersion(bumpVersion(parsed, increment));
  if (!dryRun) await writeFile(versionPath, `${nextVersion}\n`);
  if (!dryRun) {
    portManifest['version-semver'] = nextVersion;
    await writeFile(portManifestPath, `${JSON.stringify(portManifest, null, 2)}\n`);
  }
  ctx.console.log(nextVersion);
  return EXIT_SUCCESS;
}

function parseVersion(version) {
  const releaseMatch = RELEASE_VERSION_PATTERN.exec(version);
  if (!releaseMatch?.groups) {
    throw new Error(
      `Unsupported VERSION value '${version}'. Expected MAJOR.MINOR.PATCH.`
    );
  }
  return {
    major: Number(releaseMatch.groups.major),
    minor: Number(releaseMatch.groups.minor),
    patch: Number(releaseMatch.groups.patch),
  };
}

function bumpVersion(version, increment) {
  if (increment === 'major') return { major: version.major + 1, minor: 0, patch: 0 };
  if (increment === 'minor') return { major: version.major, minor: version.minor + 1, patch: 0 };
  return { major: version.major, minor: version.minor, patch: version.patch + 1 };
}

function formatReleaseVersion(version) {
  return `${version.major}.${version.minor}.${version.patch}`;
}

const entryPoint = globalThis.process.argv[1];
if (entryPoint && import.meta.url === Url.pathToFileURL(entryPoint).href) {
  void main(globalThis)
    .then((exitCode) => { globalThis.process.exitCode = exitCode; })
    .catch((error) => { globalThis.console.error(error); globalThis.process.exitCode = EXIT_FAILURE; });
}
