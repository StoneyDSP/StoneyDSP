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
  readlink,
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
  ["zip", { extension: ".zip" }],
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

    await normalizeTree(archiveRoot, timestamp);

    if (options.format === "zip") {
      await createDeterministicZip(
        stagingParent,
        archiveFiles,
        archivePath,
        epoch,
      );
    } else {
      const archiveTimestamp = timestamp
        .toISOString()
        .replace("T", " ")
        .replace(".000Z", " UTC");
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
 * Write a ZIP with stable ordering and no host-generated extra fields. Stored
 * entries avoid zlib-version differences while retaining standard ZIP
 * compatibility for the Windows SDK deliverables.
 *
 * @param {string} root
 * @param {string[]} files
 * @param {string} archivePath
 * @param {number} epoch
 */
async function createDeterministicZip(root, files, archivePath, epoch) {
  const { date, time } = zipTimestamp(epoch);
  const localParts = [];
  const centralParts = [];
  let offset = 0;

  if (files.length > 0xffff) {
    throw new Error("ZIP archive contains too many entries for ZIP32.");
  }

  for (const relative of files) {
    const absolute = Path.join(root, ...relative.split("/"));
    const stat = await lstat(absolute);
    const symbolicLink = stat.isSymbolicLink();
    const data = symbolicLink
      ? Buffer.from(await readlink(absolute), "utf8")
      : await readFile(absolute);
    const name = Buffer.from(relative, "utf8");
    const checksum = crc32(data);
    const mode = symbolicLink
      ? 0o120777
      : stat.mode & 0o111
        ? 0o100755
        : 0o100644;

    if (name.length > 0xffff) {
      throw new Error(`ZIP entry name is too long: ${relative}`);
    }
    if (data.length > 0xffffffff || offset > 0xffffffff) {
      throw new Error("ZIP archive exceeds the supported ZIP32 size.");
    }

    const local = Buffer.alloc(30);
    local.writeUInt32LE(0x04034b50, 0);
    local.writeUInt16LE(20, 4);
    local.writeUInt16LE(0x0800, 6);
    local.writeUInt16LE(0, 8);
    local.writeUInt16LE(time, 10);
    local.writeUInt16LE(date, 12);
    local.writeUInt32LE(checksum, 14);
    local.writeUInt32LE(data.length, 18);
    local.writeUInt32LE(data.length, 22);
    local.writeUInt16LE(name.length, 26);
    local.writeUInt16LE(0, 28);

    const central = Buffer.alloc(46);
    central.writeUInt32LE(0x02014b50, 0);
    central.writeUInt16LE((3 << 8) | 20, 4);
    central.writeUInt16LE(20, 6);
    central.writeUInt16LE(0x0800, 8);
    central.writeUInt16LE(0, 10);
    central.writeUInt16LE(time, 12);
    central.writeUInt16LE(date, 14);
    central.writeUInt32LE(checksum, 16);
    central.writeUInt32LE(data.length, 20);
    central.writeUInt32LE(data.length, 24);
    central.writeUInt16LE(name.length, 28);
    central.writeUInt16LE(0, 30);
    central.writeUInt16LE(0, 32);
    central.writeUInt16LE(0, 34);
    central.writeUInt16LE(0, 36);
    central.writeUInt32LE((mode << 16) >>> 0, 38);
    central.writeUInt32LE(offset, 42);

    localParts.push(local, name, data);
    centralParts.push(central, name);
    offset += local.length + name.length + data.length;
  }

  const centralSize = centralParts.reduce((size, part) => size + part.length, 0);
  if (offset + centralSize > 0xffffffff) {
    throw new Error("ZIP archive exceeds the supported ZIP32 size.");
  }

  const end = Buffer.alloc(22);
  end.writeUInt32LE(0x06054b50, 0);
  end.writeUInt16LE(0, 4);
  end.writeUInt16LE(0, 6);
  end.writeUInt16LE(files.length, 8);
  end.writeUInt16LE(files.length, 10);
  end.writeUInt32LE(centralSize, 12);
  end.writeUInt32LE(offset, 16);
  end.writeUInt16LE(0, 20);

  await writeFile(
    archivePath,
    Buffer.concat([...localParts, ...centralParts, end]),
  );
}

/**
 * @param {number} epoch
 */
function zipTimestamp(epoch) {
  const timestamp = new Date(epoch * 1000);
  const year = timestamp.getUTCFullYear();
  if (year < 1980 || year > 2107) {
    throw new Error("--source-date-epoch is outside the ZIP timestamp range.");
  }

  return {
    date:
      ((year - 1980) << 9) |
      ((timestamp.getUTCMonth() + 1) << 5) |
      timestamp.getUTCDate(),
    time:
      (timestamp.getUTCHours() << 11) |
      (timestamp.getUTCMinutes() << 5) |
      Math.floor(timestamp.getUTCSeconds() / 2),
  };
}

/**
 * @param {Buffer} data
 */
function crc32(data) {
  let checksum = 0xffffffff;
  for (const byte of data) {
    checksum = CRC32_TABLE[(checksum ^ byte) & 0xff] ^ (checksum >>> 8);
  }
  return (checksum ^ 0xffffffff) >>> 0;
}

const CRC32_TABLE = new Uint32Array(256);
for (let index = 0; index < CRC32_TABLE.length; index += 1) {
  let value = index;
  for (let bit = 0; bit < 8; bit += 1) {
    value = value & 1 ? 0xedb88320 ^ (value >>> 1) : value >>> 1;
  }
  CRC32_TABLE[index] = value >>> 0;
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
