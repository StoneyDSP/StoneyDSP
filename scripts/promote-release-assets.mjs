#!/usr/bin/env node
// @ts-check

import { createHash } from "node:crypto";
import { lstat, readFile, readdir } from "node:fs/promises";
import Path from "node:path";
import Url from "node:url";

/**
 * @typedef {{ name: string, path: string, digest: string }} LocalAsset
 * @typedef {{ id: number, name: string, digest?: string | null, url: string }} RemoteAsset
 * @typedef {0} EXIT_SUCCESS
 * @typedef {1} EXIT_FAILURE
 * @typedef {{
 *   process: { argv: string[], env: Record<string, string | undefined>, exitCode?: number },
 *   console: {
 *     log: (...values: unknown[]) => void,
 *     error: (...values: unknown[]) => void,
 *   },
 *   fetch: typeof fetch,
 * }} Context
 */

/** @type {EXIT_SUCCESS} */
const EXIT_SUCCESS = 0;
/** @type {EXIT_FAILURE} */
const EXIT_FAILURE = 1;

/**
 * Return the assets that are missing after proving that every same-named asset
 * already on the release has identical content.
 *
 * @param {LocalAsset[]} localAssets
 * @param {RemoteAsset[]} remoteAssets
 * @param {(asset: RemoteAsset) => Promise<string>} fetchRemoteDigest
 */
export async function planAssetPromotion(
  localAssets,
  remoteAssets,
  fetchRemoteDigest,
) {
  const remoteByName = new Map(remoteAssets.map((asset) => [asset.name, asset]));
  /** @type {LocalAsset[]} */
  const upload = [];
  /** @type {string[]} */
  const skip = [];

  for (const local of localAssets) {
    const remote = remoteByName.get(local.name);
    if (!remote) {
      upload.push(local);
      continue;
    }

    const remoteDigest = remote.digest?.startsWith("sha256:")
      ? remote.digest.slice("sha256:".length)
      : await fetchRemoteDigest(remote);
    if (remoteDigest !== local.digest) {
      throw new Error(
        `Release asset '${local.name}' already exists with different content. ` +
          "No assets were uploaded.",
      );
    }
    skip.push(local.name);
  }

  return { upload, skip };
}

/** @param {string[]} argv @param {Context} ctx */
export async function promoteReleaseAssets(argv, ctx) {
  const options = parseOptions(argv);
  const token = ctx.process.env.GITHUB_TOKEN;
  if (!token) throw new Error("GITHUB_TOKEN is required.");
  if (!/^[A-Za-z0-9_.-]+\/[A-Za-z0-9_.-]+$/.test(options.repository)) {
    throw new Error(`Invalid GitHub repository '${options.repository}'.`);
  }
  if (!/^v\d+\.\d+\.\d+$/.test(options.tag)) {
    throw new Error(`Invalid release tag '${options.tag}'.`);
  }

  const localAssets = await loadLocalAssets(Path.resolve(options.assetsDir));
  if (localAssets.length === 0) {
    throw new Error(`No release assets found in ${options.assetsDir}.`);
  }

  const apiBase = `https://api.github.com/repos/${options.repository}`;
  const release = await requestJson(
    `${apiBase}/releases/tags/${encodeURIComponent(options.tag)}`,
    token,
    ctx.fetch,
  );
  if (!Number.isSafeInteger(release.id)) {
    throw new Error("GitHub returned an invalid release response.");
  }
  const remoteAssets = await listRemoteAssets(
    apiBase,
    release.id,
    token,
    ctx.fetch,
  );

  const plan = await planAssetPromotion(
    localAssets,
    remoteAssets,
    async (asset) => {
      const response = await githubFetch(
        asset.url,
        token,
        { headers: { Accept: "application/octet-stream" } },
        ctx.fetch,
      );
      return createHash("sha256")
        .update(Buffer.from(await response.arrayBuffer()))
        .digest("hex");
    },
  );

  for (const name of plan.skip) {
    ctx.console.log(`skip identical asset: ${name}`);
  }
  for (const asset of plan.upload) {
    const uploadUrl =
      `https://uploads.github.com/repos/${options.repository}/releases/` +
      `${release.id}/assets?name=${encodeURIComponent(asset.name)}`;
    await githubFetch(
      uploadUrl,
      token,
      {
        method: "POST",
        headers: { "Content-Type": "application/octet-stream" },
        body: await readFile(asset.path),
      },
      ctx.fetch,
    );
    ctx.console.log(`uploaded asset: ${asset.name}`);
  }
}

/**
 * @param {string} apiBase
 * @param {number} releaseId
 * @param {string} token
 * @param {typeof fetch} fetchImpl
 */
async function listRemoteAssets(apiBase, releaseId, token, fetchImpl) {
  /** @type {RemoteAsset[]} */
  const assets = [];
  for (let page = 1; ; page += 1) {
    const batch = await requestJson(
      `${apiBase}/releases/${releaseId}/assets?per_page=100&page=${page}`,
      token,
      fetchImpl,
    );
    if (!Array.isArray(batch)) {
      throw new Error("GitHub returned an invalid release-assets response.");
    }
    assets.push(...batch);
    if (batch.length < 100) return assets;
  }
}

/** @param {string} directory @returns {Promise<LocalAsset[]>} */
async function loadLocalAssets(directory) {
  const entries = await readdir(directory, { withFileTypes: true }).catch(() => []);
  entries.sort((left, right) => left.name.localeCompare(right.name, "en"));
  /** @type {LocalAsset[]} */
  const assets = [];
  for (const entry of entries) {
    if (!entry.isFile()) {
      throw new Error(`Unexpected non-file in release asset directory: ${entry.name}`);
    }
    if (!/\.(?:zip|tar\.gz|sha256)$/.test(entry.name)) {
      throw new Error(`Unexpected release asset file: ${entry.name}`);
    }
    const path = Path.join(directory, entry.name);
    const stat = await lstat(path);
    if (stat.size === 0) throw new Error(`Release asset is empty: ${entry.name}`);
    assets.push({
      name: entry.name,
      path,
      digest: createHash("sha256").update(await readFile(path)).digest("hex"),
    });
  }
  return assets;
}

/** @param {string[]} argv */
function parseOptions(argv) {
  /** @type {Record<string, string>} */
  const values = {};
  for (let index = 0; index < argv.length; index += 2) {
    const option = argv[index];
    const value = argv[index + 1];
    if (!option?.startsWith("--") || value === undefined) {
      throw new Error(`Invalid promotion option near '${option ?? ""}'.`);
    }
    const key = option.slice(2).replaceAll("-", "_");
    if (key in values) throw new Error(`Duplicate option '${option}'.`);
    values[key] = value;
  }
  for (const key of ["repository", "tag", "assets_dir"]) {
    if (!values[key]) throw new Error(`Missing required option '--${key.replaceAll("_", "-")}'.`);
  }
  return {
    repository: values.repository,
    tag: values.tag,
    assetsDir: values.assets_dir,
  };
}

/** @param {string} url @param {string} token @param {typeof fetch} fetchImpl */
async function requestJson(url, token, fetchImpl) {
  const response = await githubFetch(url, token, {}, fetchImpl);
  return response.json();
}

/**
 * @param {string} url
 * @param {string} token
 * @param {RequestInit} [options]
 * @param {typeof fetch} [fetchImpl]
 */
async function githubFetch(url, token, options = {}, fetchImpl = globalThis.fetch) {
  const headers = new Headers(options.headers);
  headers.set("Accept", headers.get("Accept") ?? "application/vnd.github+json");
  headers.set("Authorization", `Bearer ${token}`);
  headers.set("X-GitHub-Api-Version", "2026-03-10");
  headers.set("User-Agent", "StoneyDSP-release-artifacts");
  const response = await fetchImpl(url, { ...options, headers });
  if (!response.ok) {
    const detail = (await response.text()).slice(0, 1000);
    throw new Error(
      `GitHub request failed (${response.status} ${response.statusText}): ${detail}`,
    );
  }
  return response;
}

/**
 * Own the command-line and network process boundary while keeping promotion
 * planning independently testable.
 *
 * @param {Context} ctx
 * @returns {Promise<EXIT_SUCCESS | EXIT_FAILURE>}
 */
export async function main(ctx) {
  try {
    await promoteReleaseAssets(ctx.process.argv.slice(2), ctx);
    return EXIT_SUCCESS;
  } catch (error) {
    ctx.console.error(error instanceof Error ? error.message : error);
    return EXIT_FAILURE;
  }
}

const entryPoint = globalThis.process.argv[1];
if (entryPoint && import.meta.url === Url.pathToFileURL(entryPoint).href) {
  void main(globalThis).then((exitCode) => {
    globalThis.process.exitCode = exitCode;
  });
}
