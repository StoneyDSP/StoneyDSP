import assert from "node:assert/strict";
import { mkdtemp, mkdir, readFile, rm, writeFile } from "node:fs/promises";
import Os from "node:os";
import Path from "node:path";
import { execFile } from "node:child_process";
import { promisify } from "node:util";
import { test } from "node:test";

import { main, packageRelease } from "./package-release.mjs";

const execute = promisify(execFile);
const projectRoot = Path.resolve(import.meta.dirname, "..");
const version = String(await readFile(Path.join(projectRoot, "VERSION"), "utf8")).trim();

test("creates byte-stable TGZ and ZIP archives with declared SDK metadata", async () => {
  const temporary = await mkdtemp(Path.join(Os.tmpdir(), "stoneydsp-package-test-"));
  try {
    const installDir = Path.join(temporary, "install");
    await mkdir(Path.join(installDir, "include", "stoneydsp"), { recursive: true });
    await mkdir(Path.join(installDir, "lib", "cmake", "stoneydsp"), { recursive: true });
    await writeFile(Path.join(installDir, "include", "stoneydsp", "test.h"), "#pragma once\n");
    await writeFile(Path.join(installDir, "lib", "libstoneydsp.a"), "archive\n");
    await writeFile(
      Path.join(installDir, "lib", "cmake", "stoneydsp", "stoneydsp-config.cmake"),
      "# fixture\n",
    );

    for (const format of ["tar.gz", "zip"]) {
      const common = [
        "--install-dir", installDir,
        "--name", `StoneyDSP-${version}-linux-x86_64-gcc-static`,
        "--format", format,
        "--version", version,
        "--commit", "0123456789abcdef0123456789abcdef01234567",
        "--system", "linux",
        "--architecture", "x86_64",
        "--compiler", "gcc",
        "--linkage", "static",
        "--preset", "x64-linux-release",
        "--source-date-epoch", "1700000000",
      ];
      const first = await packageRelease([
        "--output-dir", Path.join(temporary, `first-${format}`),
        ...common,
      ]);
      const second = await packageRelease([
        "--output-dir", Path.join(temporary, `second-${format}`),
        ...common,
      ]);

      assert.equal(first.digest, second.digest, `${format} digest`);
      assert.deepEqual(
        await readFile(first.archivePath),
        await readFile(second.archivePath),
      );
      assert.match(
        await readFile(first.checksumPath, "utf8"),
        new RegExp(`^${first.digest}  StoneyDSP-`),
      );

      const { stdout } = await execute("cmake", [
        "-E",
        "tar",
        "tf",
        first.archivePath,
      ]);
      assert.match(stdout, /\/LICENSE$/m);
      assert.match(stdout, /\/VERSION$/m);
      assert.match(stdout, /\/StoneyDSP-build-manifest\.json$/m);
      assert.match(stdout, /\/include\/stoneydsp\/test\.h$/m);
      assert.match(stdout, /\/lib\/libstoneydsp\.a$/m);

      const extracted = Path.join(temporary, `extracted-${format}`);
      await mkdir(extracted);
      await execute("cmake", ["-E", "tar", "xf", first.archivePath], {
        cwd: extracted,
      });
      assert.equal(
        await readFile(
          Path.join(
            extracted,
            `StoneyDSP-${version}-linux-x86_64-gcc-static`,
            "include",
            "stoneydsp",
            "test.h",
          ),
          "utf8",
        ),
        "#pragma once\n",
      );
    }
  } finally {
    await rm(temporary, { recursive: true, force: true });
  }
});

test("rejects an install tree without the package contract", async () => {
  const temporary = await mkdtemp(Path.join(Os.tmpdir(), "stoneydsp-package-test-"));
  try {
    await assert.rejects(
      packageRelease([
        "--install-dir", temporary,
        "--output-dir", Path.join(temporary, "output"),
        "--name", `StoneyDSP-${version}-linux-x86_64-gcc-static`,
        "--format", "tar.gz",
        "--version", version,
        "--commit", "0123456789abcdef0123456789abcdef01234567",
        "--system", "linux",
        "--architecture", "x86_64",
        "--compiler", "gcc",
        "--linkage", "static",
        "--preset", "x64-linux-release",
        "--source-date-epoch", "1700000000",
      ]),
      /contains no files/,
    );
  } finally {
    await rm(temporary, { recursive: true, force: true });
  }
});

test("CLI entry point owns argument errors through its injected context", async () => {
  const errors = [];
  const exitCode = await main({
    process: { argv: ["node", "package-release.mjs"] },
    console: {
      log: () => {},
      error: (...values) => errors.push(values.join(" ")),
    },
  });

  assert.equal(exitCode, 1);
  assert.match(errors.join("\n"), /Missing required option/);
});
