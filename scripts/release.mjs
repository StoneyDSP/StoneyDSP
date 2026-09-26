#!/usr/bin/env node
// @ts-check

/**
 * @typedef {0} EXIT_SUCCESS
 * @typedef {1} EXIT_FAILURE
 */

/**
 * @typedef {typeof globalThis} Context
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
 *
 * @param {Context} ctx
 * @returns {Promise<EXIT_SUCCESS | EXIT_FAILURE>}
 */
export async function main(ctx) {
  const args = ctx.process.argv.slice(2);

  const dryRun = args.includes("--dry-run");
  const checkOnly = args.includes("--check");
  const tagOnly = args.includes("--tag");

  if (checkOnly) {
    ctx.console.log("");
    return EXIT_SUCCESS;
  }

  if (tagOnly) {
    ctx.console.log("");
    return EXIT_SUCCESS;
  }

  if (!dryRun) {
    try {
      ctx.console.log("");
    } catch (error) {
      ctx.console.error("");
      throw error;
    }
  } else {
    ctx.console.log("");
  }

  return EXIT_SUCCESS;
}
