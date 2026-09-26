#!/usr/bin/env node
// @ts-check

import { execFile as nodeExecFile } from "node:child_process";
import { readFile } from "node:fs/promises";
import Path from "node:path";
import Url from "node:url";

/**
 * @typedef {0} EXIT_SUCCESS
 */

/**
 * @typedef {1} EXIT_FAILURE
 */

/**
 * @typedef {{ stdout: string, stderr: string, code: number }} CommandResult
 */

/**
 * @typedef {{
 * argv: string[], execPath: string, cwd: () => string, exitCode?: number
 * }} ProcessContext
 */

/**
 * @typedef {{
 * log: (...values: unknown[]) => void,
 * error: (...values: unknown[]) => void,
 * }} ConsoleContext
 */

/**
 * @typedef {(
 * file: string,
 * args: string[],
 * options?: { cwd?: string }
 * ) => Promise<CommandResult>} ExecuteFile
 */

/**
 * @typedef {{
 * process: ProcessContext,
 * console: ConsoleContext,
 * moduleUrl: string,
 * path: typeof Path,
 * url: typeof Url,
 * readFile: typeof readFile,
 * executeFile: ExecuteFile,
 * }} Context
 */

/**
 * @typedef {{ check: boolean, dryRun: boolean, tag: boolean, confirm: boolean }} Options
 */

/**
 * @typedef {{ name: string, passed: boolean, detail: string }} CheckResult
 */

/**
 * @typedef {{
 * root: string, version: string, tag: string, checks: CheckResult[]
 * }} ReleasePlan
 */

/**
 * @type {EXIT_SUCCESS}
 */
const EXIT_SUCCESS = 0;

/**
 * @type {EXIT_FAILURE}
 */
const EXIT_FAILURE = 1;

/**
 * Run the release protocol using only the processing context supplied by the
 * caller. Process state and side effects remain visible at this boundary.
 *
 * @param {Context} ctx
 * @returns {Promise<EXIT_SUCCESS | EXIT_FAILURE>}
 */
export async function main(ctx) {
  try {
    const options = parseOptions(ctx.process.argv.slice(2));
    const root = resolveProjectRoot(ctx);
    const plan = await buildReleasePlan(ctx, root);

    printChecks(ctx, plan);
    if (options.dryRun) printDryRun(ctx, plan);

    if (!plan.checks.every((check) => check.passed)) {
      ctx.console.error("Release checks failed; no release mutation was made.");
      return EXIT_FAILURE;
    }

    if (options.check) return EXIT_SUCCESS;

    if (options.dryRun) return EXIT_SUCCESS;

    if (!options.tag) {
      ctx.console.error(
        "Usage: node scripts/release.mjs --check | --dry-run | --tag [--confirm]",
      );
      return EXIT_FAILURE;
    }

    if (!options.confirm) {
      ctx.console.error(
        `Refusing to create ${plan.tag} without explicit confirmation. ` +
          "Re-run with --tag --confirm.",
      );
      return EXIT_FAILURE;
    }

    await createTag(ctx, plan);
    ctx.console.log(`Created local annotated tag ${plan.tag}.`);
    ctx.console.log(
      "The tag was not pushed and no GitHub release was created.",
    );
    return EXIT_SUCCESS;
  } catch (error) {
    ctx.console.error(error instanceof Error ? error.message : error);
    return EXIT_FAILURE;
  }
}

/**
 * @param {string[]} args
 * @returns {Options}
 */
function parseOptions(args) {
  const allowed = new Set(["--check", "--dry-run", "--tag", "--confirm"]);
  for (const arg of args) {
    if (!allowed.has(arg)) throw new Error(`Unknown release option '${arg}'.`);
  }

  const options = {
    check: args.includes("--check"),
    dryRun: args.includes("--dry-run"),
    tag: args.includes("--tag"),
    confirm: args.includes("--confirm"),
  };
  const modeCount = [options.check, options.dryRun, options.tag].filter(
    Boolean,
  ).length;

  if (modeCount !== 1) {
    throw new Error(
      "Choose exactly one release mode: --check, --dry-run, or --tag.",
    );
  }
  if (options.confirm && !options.tag) {
    throw new Error("--confirm is only valid with --tag.");
  }
  return options;
}

/**
 * @param {Context} ctx
 * @returns {string}
 */
function resolveProjectRoot(ctx) {
  return ctx.path.resolve(
    ctx.path.dirname(ctx.url.fileURLToPath(ctx.moduleUrl)),
    "..",
  );
}

/**
 * @param {Context} ctx
 * @param {string} root
 * @returns {Promise<ReleasePlan>}
 */
async function buildReleasePlan(ctx, root) {
  const versionPath = ctx.path.join(root, "VERSION");
  const version = String(await ctx.readFile(versionPath, "utf8")).trim();
  assertReleaseVersion(version);

  const tag = `v${version}`;
  const checks = [
    await checkCleanWorktree(ctx, root),
    await checkCleanSubmodules(ctx, root),
    await checkProductionBranch(ctx, root),
    await checkVersionProtocol(ctx, root),
    await checkProductionTip(ctx, root),
    await checkLocalTag(ctx, root, tag),
    await checkRemoteTag(ctx, root, tag),
  ];

  return { root, version, tag, checks };
}

/**
 * @param {string} version
 */
function assertReleaseVersion(version) {
  if (!/^\d+\.\d+\.\d+$/.test(version)) {
    throw new Error(`Unsupported VERSION value '${version}'.`);
  }
}

/**
 * @param {Context} ctx
 * @param {ReleasePlan} plan
 */
function printDryRun(ctx, plan) {
  ctx.console.log("");
  ctx.console.log("Release dry run");
  ctx.console.log(`  version: ${plan.version}`);
  ctx.console.log(`  tag:     ${plan.tag}`);
  ctx.console.log("  action:  create one local annotated tag; do not push");
}

/**
 * @param {Context} ctx
 * @param {ReleasePlan} plan
 */
async function createTag(ctx, plan) {
  await executeGit(ctx, plan.root, [
    "tag",
    "--annotate",
    plan.tag,
    "--message",
    `StoneyDSP ${plan.tag}`,
    "HEAD",
  ]);
}

/**
 * @param {Context} ctx
 * @param {ReleasePlan} plan
 */
function printChecks(ctx, plan) {
  ctx.console.log(`Release candidate ${plan.tag} (${plan.version})`);
  for (const check of plan.checks) {
    ctx.console.log(
      `${check.passed ? "PASS" : "FAIL"} ${check.name}: ${check.detail}`,
    );
  }
}

/**
 * @param {Context} ctx
 * @param {string} root
 * @returns {Promise<CheckResult>}
 */
async function checkCleanWorktree(ctx, root) {
  const result = await executeGit(
    ctx,
    root,
    ["status", "--porcelain", "--untracked-files=all"],
    true,
  );
  const detail = result.stdout.trim();
  return {
    name: "clean worktree",
    passed: result.code === 0 && detail.length === 0,
    detail:
      result.code !== 0
        ? result.stderr.trim() || "unable to inspect worktree"
        : detail || "no tracked or untracked changes",
  };
}

/**
 * @param {Context} ctx
 * @param {string} root
 * @returns {Promise<CheckResult>}
 */
async function checkCleanSubmodules(ctx, root) {
  const result = await executeGit(
    ctx,
    root,
    ["submodule", "status", "--recursive"],
    true,
  );
  const dirty = result.stdout
    .split("\n")
    .filter((line) => line && /^[+\-U]/.test(line));
  return {
    name: "clean submodules",
    passed: result.code === 0 && dirty.length === 0,
    detail:
      dirty.length === 0
        ? "all submodules match recorded commits"
        : dirty.join("; "),
  };
}

/**
 * @param {Context} ctx
 * @param {string} root
 * @returns {Promise<CheckResult>}
 */
async function checkProductionBranch(ctx, root) {
  const result = await executeGit(
    ctx,
    root,
    ["branch", "--show-current"],
    true,
  );
  const branch = result.stdout.trim();
  return {
    name: "production branch",
    passed: result.code === 0 && branch === "production",
    detail: branch || "detached HEAD",
  };
}

/**
 * @param {Context} ctx
 * @param {string} root
 * @returns {Promise<CheckResult>}
 */
async function checkVersionProtocol(ctx, root) {
  const script = ctx.path.join(root, "scripts", "bump-version.mjs");
  const result = await ctx.executeFile(
    ctx.process.execPath,
    [script, "--check"],
    {
      cwd: root,
    },
  );
  return {
    name: "version protocol",
    passed: result.code === 0,
    detail: result.code === 0 ? result.stdout.trim() : result.stderr.trim(),
  };
}

/**
 * @param {Context} ctx
 * @param {string} root
 * @returns {Promise<CheckResult>}
 */
async function checkProductionTip(ctx, root) {
  const [head, remote] = await Promise.all([
    executeGit(ctx, root, ["rev-parse", "--verify", "HEAD"], true),
    executeGit(
      ctx,
      root,
      ["rev-parse", "--verify", "refs/remotes/origin/production"],
      true,
    ),
  ]);
  const headHash = head.stdout.trim();
  const remoteHash = remote.stdout.trim();
  return {
    name: "production tip",
    passed: head.code === 0 && remote.code === 0 && headHash === remoteHash,
    detail: remoteHash
      ? `${headHash} == ${remoteHash}`
      : "origin/production is unavailable",
  };
}

/**
 * @param {Context} ctx
 * @param {string} root
 * @param {string} tag
 * @returns {Promise<CheckResult>}
 */
async function checkLocalTag(ctx, root, tag) {
  const result = await executeGit(
    ctx,
    root,
    ["show-ref", "--verify", "--quiet", `refs/tags/${tag}`],
    true,
  );
  return {
    name: "local tag is absent",
    passed: result.code === 1,
    detail:
      result.code === 1
        ? `${tag} is not present`
        : result.code === 0
          ? `${tag} already exists`
          : result.stderr.trim() || "unable to inspect local tags",
  };
}

/**
 * @param {Context} ctx
 * @param {string} root
 * @param {string} tag
 * @returns {Promise<CheckResult>}
 */
async function checkRemoteTag(ctx, root, tag) {
  const result = await executeGit(
    ctx,
    root,
    ["ls-remote", "--tags", "origin", `refs/tags/${tag}`],
    true,
  );
  const present = result.code === 0 && result.stdout.trim().length > 0;
  return {
    name: "remote tag is absent",
    passed: result.code === 0 && !present,
    detail:
      result.code !== 0
        ? result.stderr.trim() || "unable to query origin tags"
        : present
          ? `${tag} already exists on origin`
          : "origin has no matching tag",
  };
}

/**
 * @param {Context} ctx
 * @param {string} root
 * @param {string[]} args
 * @param {boolean} allowFailure
 * @returns {Promise<CommandResult>}
 */
async function executeGit(ctx, root, args, allowFailure = false) {
  try {
    return await ctx.executeFile("git", ["-C", root, ...args]);
  } catch (error) {
    const result = /** @type {Partial<CommandResult> & { code?: number }} */ (
      error
    );
    if (allowFailure) {
      return {
        stdout: String(result.stdout ?? ""),
        stderr: String(result.stderr ?? ""),
        code: Number(result.code ?? 1),
      };
    }
    throw error;
  }
}

/**
 * @returns {ExecuteFile}
 */
function createExecuteFile() {
  return (file, args, options = {}) =>
    new Promise((resolve, reject) => {
      nodeExecFile(file, args, options, (error, stdout, stderr) => {
        if (error) {
          Object.assign(error, { stdout, stderr, code: error.code });
          reject(error);
          return;
        }
        resolve({ stdout, stderr, code: 0 });
      });
    });
}

const entryPoint = globalThis.process.argv[1];
if (entryPoint && import.meta.url === Url.pathToFileURL(entryPoint).href) {
  const context = {
    process: globalThis.process,
    console: globalThis.console,
    moduleUrl: import.meta.url,
    path: Path,
    url: Url,
    readFile,
    executeFile: createExecuteFile(),
  };
  void main(context).then((exitCode) => {
    globalThis.process.exitCode = exitCode;
  });
}
