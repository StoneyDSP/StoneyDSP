#!/usr/bin/env node
// @ts-check

import { readFile, writeFile } from 'node:fs/promises';
import Path from 'node:path';
import Url from 'node:url';

const EXIT_SUCCESS = 0;
const EXIT_FAILURE = 1;
const RELEASE_VERSION_PATTERN =
  /^(?<major>0|[1-9]\d*)\.(?<minor>0|[1-9]\d*)\.(?<patch>0|[1-9]\d*)$/;

const VERSION_TARGETS = [
  { path: 'vcpkg.json', key: 'version' },
  { path: 'package.json', key: 'version' },
  {
    path: 'share/vcpkg/ports/stoneydsp/vcpkg.json',
    key: 'version-semver',
  },
];

export async function main(ctx) {
  const args = ctx.process.argv.slice(2);
  const dryRun = args.includes('--dry-run');
  const checkOnly = args.includes('--check');
  const syncOnly = args.includes('--sync');
  const increment = args.find((arg) => !arg.startsWith('--'));
  const versionPath = Path.resolve(
    Path.dirname(Url.fileURLToPath(import.meta.url)),
    '..',
    'VERSION'
  );
  const projectRoot = Path.dirname(versionPath);

  const current = String(await readFile(versionPath, 'utf8')).trim();
  const parsed = parseVersion(current);
  const targetFiles = await readVersionTargets(projectRoot);

  if (checkOnly) {
    assertTargetsMatch(targetFiles, formatReleaseVersion(parsed));
    ctx.console.log(formatReleaseVersion(parsed));
    return EXIT_SUCCESS;
  }

  if (syncOnly) {
    await writeVersionTargets(
      projectRoot,
      targetFiles,
      formatReleaseVersion(parsed),
      false
    );
    ctx.console.log(formatReleaseVersion(parsed));
    return EXIT_SUCCESS;
  }

  if (!increment || !['patch', 'minor', 'major'].includes(increment)) {
    ctx.console.error(
      'Usage: node scripts/bump-version.mjs <patch|minor|major> [--dry-run]'
    );
    return EXIT_FAILURE;
  }

  assertTargetsMatch(targetFiles, formatReleaseVersion(parsed));
  const nextVersion = formatReleaseVersion(bumpVersion(parsed, increment));
  if (!dryRun) {
    try {
      await writeFile(versionPath, `${nextVersion}\n`);
      await writeVersionTargets(projectRoot, targetFiles, nextVersion, false);
    } catch (error) {
      await writeFile(versionPath, `${current}\n`);
      throw error;
    }
  } else {
    await writeVersionTargets(projectRoot, targetFiles, nextVersion, true);
  }
  ctx.console.log(nextVersion);
  return EXIT_SUCCESS;
}

async function readVersionTargets(projectRoot) {
  return Promise.all(
    VERSION_TARGETS.map(async (target) => ({
      ...target,
      path: Path.resolve(projectRoot, target.path),
      text: String(await readFile(Path.resolve(projectRoot, target.path), 'utf8')),
    }))
  );
}

function assertTargetsMatch(targetFiles, expectedVersion) {
  for (const target of targetFiles) {
    const actualVersion = extractTopLevelVersion(target.text, target.key, target.path);
    if (actualVersion !== expectedVersion) {
      throw new Error(
        `${target.path} (${actualVersion}) does not match VERSION (${expectedVersion}).`
      );
    }
  }
}

async function writeVersionTargets(projectRoot, targetFiles, nextVersion, dryRun) {
  const updates = targetFiles.map((target) => ({
    ...target,
    nextText: replaceTopLevelVersion(target.text, target.key, nextVersion, target.path),
  }));

  if (dryRun) return;

  const written = [];
  try {
    for (const target of updates) {
      await writeFile(target.path, target.nextText);
      written.push(target);
    }
  } catch (error) {
    for (const target of written) await writeFile(target.path, target.text);
    throw error;
  }
}

function extractTopLevelVersion(text, key, path) {
  const matches = [...text.matchAll(versionFieldPattern(key))];
  if (matches.length === 0) {
    throw new Error(`Expected a top-level ${key} field in ${path}.`);
  }
  const manifest = JSON.parse(text);
  if (typeof manifest[key] !== 'string' || manifest[key] !== matches[0][2]) {
    throw new Error(`Expected a top-level ${key} field in ${path}.`);
  }
  return matches[0][2];
}

function replaceTopLevelVersion(text, key, version, path) {
  const matches = [...text.matchAll(versionFieldPattern(key))];
  if (matches.length === 0) {
    throw new Error(`Expected a top-level ${key} field in ${path}.`);
  }
  const manifest = JSON.parse(text);
  if (typeof manifest[key] !== 'string' || manifest[key] !== matches[0][2]) {
    throw new Error(`Expected a top-level ${key} field in ${path}.`);
  }
  return text.replace(matches[0][0], `${matches[0][1]}"${version}"`);
}

function versionFieldPattern(key) {
  return new RegExp(
    `(^[\\t ]*"${key}"[\\t ]*:[\\t ]*)"((?:[^"\\\\]|\\\\.)*)"`,
    'gm'
  );
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
