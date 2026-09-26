# CMake presets

`CMakePresets.json` is the canonical source for configure, build, test, and
workflow presets. Preset names generally follow:

```text
<architecture>-<platform>-<mode>[-verbose]
```

Examples include `x64-linux-release-verbose`, `arm64-linux-debug`,
`arm64-osx-release`, and Windows MinGW/MSVC configurations. Inspect the live
preset file rather than copying a historical support table: a preset may exist
for local development or future validation without being a continuously funded
CI target.

## Direct CMake use

```sh
cmake --preset x64-linux-release-verbose
cmake --build ./build --preset x64-linux-release-verbose
ctest --test-dir ./build --preset x64-linux-release-verbose
```

The checked-in presets select Ninja and configure vcpkg integration. Use the
same preset for configure, build, and test unless a specific investigation
requires otherwise.

## Make facade

The Makefile can select an appropriate host preset:

```sh
make preset
make configure
make build
make test
make workflow
```

`DEBUG=1` and `VERBOSE=1` select matching variants:

```sh
DEBUG=1 VERBOSE=1 make workflow
```

`make workflow` is the convenient CMake-backed developer/package route.
`make check` remains a separate native/legacy test path and should not be
reported as install/export/package validation without also running the relevant
CMake and external-consumer checks.

## Platform evidence

The current CI matrix provides representative validation on macOS, Linux,
Windows/MinGW, and Windows/MSVC x86/x64. Linux ARM64 has a preset/triplet
selection but is not currently run on every CI change. Use a manual workflow or
release-cut validation when the added coverage answers a concrete release
question.

Do not add every possible platform/compiler row to routine CI merely because a
preset exists. Balance validation value against available GitHub Actions
capacity, and retain manual dispatch for broader release verification.
