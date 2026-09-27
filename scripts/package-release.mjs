#!/usr/bin/env node
// @ts-check

import { execFile as nodeExecFile } from "node:child_process";
import { createHash } from "node:crypto";
import {
  chmod,
  copyFile,
  cp,
  lstat,
  lutimes,
  mkdir,
  mkdtemp,
  readFile,
  readdir,
  rm,
  utimes,
  writeFile,
} from "node:fs/promises";
import Os from "node:os";
import Path from "node:path";
import { promisify } from "node:util";
import Url from "node:url";

const execFile = promisify(nodeExecFile);

/**
 * @typedef {0} EXIT_SUCCESS
 * @typedef {1} EXIT_FAILURE
 * @typedef {{
 *   process: { argv: string[], exitCode?: number },
 *   console: {
 *     log: (...values: unknown[]) => void,
 *     error: (...values: unknown[]) => void,
 *   },
 * }} Context
 */

/** @type {EXIT_SUCCESS} */
const EXIT_SUCCESS = 0;
/** @type {EXIT_FAILURE} */
const EXIT_FAILURE = 1;

const FORMATS = new Map([
  ["tar.gz", { extension: ".tar.gz", flags: "czf", format: "gnutar" }],
  ["zip", { extension: ".zip", flags: "cf", format: "zip" }],
]);

/**
 * Create a normalized SDK archive from a CMake install tree.
 *
 * @param {string[]} argv
 * @returns {Promise<{ archivePath: string, checksumPath: string, digest: string }>}
 */
export async function packageRelease(argv) {
  const options = parseOptions(argv);
  const format = FORMATS.get(options.format);

  if (!format)
    throw new Error(`Unsupported archive format '${options.format}'.`);

  assertToken("archive name", options.name, /^[A-Za-z0-9][A-Za-z0-9._-]*$/);
  assertToken("version", options.version, /^\d+\.\d+\.\d+$/);
  assertToken("commit", options.commit, /^[0-9a-f]{40}$/);
  assertToken("system", options.system, /^[a-z0-9][a-z0-9._-]*$/);
  assertToken(
    "architecture",
    options.architecture,
    /^[A-Za-z0-9][A-Za-z0-9._-]*$/,
  );
  assertToken("compiler", options.compiler, /^[A-Za-z0-9][A-Za-z0-9._-]*$/);
  assertToken("linkage", options.linkage, /^(static|shared)$/);
  assertToken("CMake preset", options.preset, /^[A-Za-z0-9][A-Za-z0-9._-]*$/);

  const epoch = Number(options.sourceDateEpoch);
  if (!Number.isSafeInteger(epoch) || epoch <= 0) {
    throw new Error("--source-date-epoch must be a positive integer.");
  }

  const installDir = Path.resolve(options.installDir);
  const outputDir = Path.resolve(options.outputDir);
  const installStat = await lstat(installDir).catch(() => null);

  if (!installStat?.isDirectory()) {
    throw new Error(`Install tree does not exist: ${installDir}`);
  }

  const installedFiles = await listFiles(installDir);

  if (installedFiles.length === 0) {
    throw new Error(`Install tree contains no files: ${installDir}`);
  }

  if (!installedFiles.some((file) => file.startsWith("include/"))) {
    throw new Error(
      "Install tree does not contain public headers under include/.",
    );
  }

  if (!installedFiles.some((file) => /(^|\/)cmake\//.test(file))) {
    throw new Error("Install tree does not contain CMake package metadata.");
  }

  if (
    !installedFiles.some(
      (file) => /(^|\/)lib[^/]*\//.test(file) || /(^|\/)lib\//.test(file),
    )
  ) {
    throw new Error(
      "Install tree does not contain an installed library directory.",
    );
  }

  const projectRoot = Path.resolve(
    Path.dirname(Url.fileURLToPath(import.meta.url)),
    "..",
  );

  const trackedVersion = String(
    await readFile(Path.join(projectRoot, "VERSION"), "utf8"),
  ).trim();

  if (trackedVersion !== options.version) {
    throw new Error(
      `Requested version ${options.version} does not match tracked VERSION ${trackedVersion}.`,
    );
  }

  await mkdir(outputDir, { recursive: true });

  const stagingParent = await mkdtemp(
    Path.join(Os.tmpdir(), "stoneydsp-release-"),
  );

  const archiveRoot = Path.join(stagingParent, options.name);
  const archivePath = Path.join(
    outputDir,
    `${options.name}${format.extension}`,
  );
  const checksumPath = `${archivePath}.sha256`;

  try {
    await cp(installDir, archiveRoot, {
      recursive: true,
      dereference: false,
      preserveTimestamps: false,
    });
    await copyFile(
      Path.join(projectRoot, "LICENSE"),
      Path.join(archiveRoot, "LICENSE"),
    );
    await copyFile(
      Path.join(projectRoot, "VERSION"),
      Path.join(archiveRoot, "VERSION"),
    );

    const manifest = {
      name: "StoneyDSP",
      version: options.version,
      commit: options.commit,
      system: options.system,
      architecture: options.architecture,
      compiler: options.compiler,
      linkage: options.linkage,
      cmakePreset: options.preset,
      sourceDateEpoch: epoch,
    };

    await writeFile(
      Path.join(archiveRoot, "StoneyDSP-build-manifest.json"),
      `${JSON.stringify(manifest, null, 2)}\n`,
      "utf8",
    );

    const archiveFiles = await listFiles(stagingParent);
    const timestamp = new Date(epoch * 1000);
    const archiveTimestamp = timestamp
      .toISOString()
      .replace("T", " ")
      .replace(".000Z", " UTC");

    await normalizeTree(archiveRoot, timestamp);

    const fileListPath = Path.join(stagingParent, "archive-files.txt");

    await writeFile(fileListPath, `${archiveFiles.join("\n")}\n`, "utf8");

    await execFile(
      "cmake",
      [
        "-E",
        "tar",
        format.flags,
        archivePath,
        `--format=${format.format}`,
        `--mtime=${archiveTimestamp}`,
        `--files-from=${fileListPath}`,
      ],
      { cwd: stagingParent },
    );

    if (options.format === "tar.gz") {
      await normalizeGzipTimestamp(archivePath, epoch);
    }

    const digest = createHash("sha256")
      .update(await readFile(archivePath))
      .digest("hex");

    await writeFile(
      checksumPath,
      `${digest}  ${Path.basename(archivePath)}\n`,
      "utf8",
    );

    return { archivePath, checksumPath, digest };
  } finally {
    await rm(stagingParent, { recursive: true, force: true });
  }
}

/**
 * @param {string[]} argv
 */
function parseOptions(argv) {
  /**
   * @type {Record<string, string>}
   */
  const values = {};

  for (let index = 0; index < argv.length; index += 2) {
    const option = argv[index];
    const value = argv[index + 1];

    if (!option?.startsWith("--") || value === undefined) {
      throw new Error(`Invalid package option near '${option ?? ""}'.`);
    }

    const key = option.slice(2).replaceAll("-", "_");

    if (key in values) throw new Error(`Duplicate option '${option}'.`);

    values[key] = value;
  }

  const required = [
    "install_dir",
    "output_dir",
    "name",
    "format",
    "version",
    "commit",
    "system",
    "architecture",
    "compiler",
    "linkage",
    "preset",
    "source_date_epoch",
  ];

  for (const key of required) {
    if (!values[key])
      throw new Error(
        `Missing required option '--${key.replaceAll("_", "-")}'.`,
      );
  }

  return {
    installDir: values.install_dir,
    outputDir: values.output_dir,
    name: values.name,
    format: values.format,
    version: values.version,
    commit: values.commit,
    system: values.system,
    architecture: values.architecture,
    compiler: values.compiler,
    linkage: values.linkage,
    preset: values.preset,
    sourceDateEpoch: values.source_date_epoch,
  };
}

/**
 * @param {string} label
 * @param {string} value
 * @param {RegExp} pattern
 */
function assertToken(label, value, pattern) {
  if (!pattern.test(value)) throw new Error(`Invalid ${label} '${value}'.`);
}

/**
 * @param {string} root
 * @returns {Promise<string[]>}
 */
async function listFiles(root) {
  /**
   * @type {string[]}
   */
  const files = [];

  /**
   * @param {string} directory
   */
  async function visit(directory) {
    const entries = await readdir(directory, { withFileTypes: true });
    entries.sort((left, right) => left.name.localeCompare(right.name, "en"));

    for (const entry of entries) {
      const absolute = Path.join(directory, entry.name);
      if (entry.isDirectory()) {
        await visit(absolute);
      } else if (entry.isFile() || entry.isSymbolicLink()) {
        files.push(Path.relative(root, absolute).split(Path.sep).join("/"));
      } else {
        throw new Error(`Unsupported install-tree entry: ${absolute}`);
      }
    }
  }

  await visit(root);
  return files;
}

/**
 * @param {string} root
 * @param {Date} timestamp
 */
async function normalizeTree(root, timestamp) {
  const entries = await readdir(root, { withFileTypes: true });
  entries.sort((left, right) => left.name.localeCompare(right.name, "en"));

  for (const entry of entries) {
    const absolute = Path.join(root, entry.name);
    if (entry.isDirectory()) {
      await normalizeTree(absolute, timestamp);
      await chmod(absolute, 0o755);
      await utimes(absolute, timestamp, timestamp);
    } else if (entry.isFile()) {
      const stat = await lstat(absolute);
      await chmod(absolute, stat.mode & 0o111 ? 0o755 : 0o644);
      await utimes(absolute, timestamp, timestamp);
    } else if (entry.isSymbolicLink()) {
      await lutimes(absolute, timestamp, timestamp);
    } else {
      throw new Error(`Unsupported install-tree entry: ${absolute}`);
    }
  }
  await chmod(root, 0o755);
  await utimes(root, timestamp, timestamp);
}

/**
 * CMake normalizes tar member timestamps but libarchive writes the current
 * time into the outer gzip header. Replace that four-byte field with the
 * declared source-date epoch so equal inputs remain byte-identical.
 *
 * @param {string} archivePath
 * @param {number} epoch
 */
async function normalizeGzipTimestamp(archivePath, epoch) {
  if (epoch > 0xffffffff) {
    throw new Error("--source-date-epoch exceeds the gzip timestamp range.");
  }

  const archive = await readFile(archivePath);
  if (archive.length < 10 || archive[0] !== 0x1f || archive[1] !== 0x8b) {
    throw new Error(`CMake did not create a valid gzip archive: ${archivePath}`);
  }

  archive.writeUInt32LE(epoch, 4);
  await writeFile(archivePath, archive);
}

/**
 * Own the command-line process boundary while keeping archive construction
 * callable without ambient process state.
 *
 * @param {Context} ctx
 * @returns {Promise<EXIT_SUCCESS | EXIT_FAILURE>}
 */
export async function main(ctx) {
  try {
    const { archivePath, checksumPath, digest } = await packageRelease(
      ctx.process.argv.slice(2),
    );
    ctx.console.log(`archive=${archivePath}`);
    ctx.console.log(`checksum=${checksumPath}`);
    ctx.console.log(`sha256=${digest}`);
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
