# StoneyDSP

[![Windows (MSVC)](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/windows-latest-msvc.yml/badge.svg)](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/windows-latest-msvc.yml)
[![Windows (MSYS2)](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/windows-latest.yml/badge.svg)](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/windows-latest.yml)
[![macOS](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/macos-latest.yml/badge.svg)](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/macos-latest.yml)
[![Ubuntu](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/ubuntu-latest.yml/badge.svg)](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/ubuntu-latest.yml)

StoneyDSP is a portable C and C++ audio-DSP library. It is designed as a
shared foundation for separately developed effects, instruments, VCV Rack
modules, embedded applications, and other audio products.

The library is intentionally independent of JUCE, plugin formats, browser UI
frameworks, and commercial product code. Products consume installed StoneyDSP
CMake targets—normally through vcpkg—rather than importing its source tree.

> StoneyDSP is early but actively validated. Its public package, C API, C++
> APIs, and component set are still evolving; downstream consumers should pin
> a reviewed version or commit.

## What exists today

- portable core types, compiler/platform abstractions, C-compatible helpers,
  and maths conversions;
- C++ maths constants and gain/decibel/binary-amplitude conversion helpers;
- an early DSP component with clean gain, biquad coefficient design, matched
  biquad coefficient helpers, and allocation-free biquad processing;
- installable CMake package components and a local vcpkg registry/port;
- C and C++ external-consumer smoke coverage, including static and shared
  linkage paths;
- CI coverage across macOS, Linux, Windows/MinGW, and Windows/MSVC x86/x64.

See [the documentation map](doc/README.md) for the current architecture,
consumer boundary, portability contract, DSP-development practice, and product
integration direction.

## Quick start

Clone the repository and initialise its submodules:

```sh
git clone --recurse-submodules git@github.com:StoneyDSP/StoneyDSP.git
cd StoneyDSP
```

Configure, build, and test with a named CMake preset:

```sh
cmake --preset x64-linux-release-verbose
cmake --build ./build --preset x64-linux-release-verbose
ctest --test-dir ./build --preset x64-linux-release-verbose
```

On a supported host, the Makefile can select the matching CMake preset:

```sh
make workflow
```

`make workflow` is the convenient CMake-backed developer/package path.
`make check` is a separate legacy/native test path; it is useful validation,
but is not by itself proof that installation, exports, or vcpkg consumption
work.

## Consuming StoneyDSP

A product should consume exported targets rather than source directories:

```cmake
find_package(StoneyDSP CONFIG REQUIRED COMPONENTS Core DSP)

target_link_libraries(MyProduct
    PRIVATE
        StoneyDSP::DSP)
```

The intended public components are `StoneyDSP::Core`, `StoneyDSP::SIMD`, and
`StoneyDSP::DSP`, with an aggregate package target where appropriate. For
local tandem development, a product may provision a pinned StoneyDSP checkout
through a vcpkg overlay port; a release build must pin an immutable commit or
version.

For package, linkage, C API, and JUCE-consumer guidance, see
[Consumer integration](doc/consumer-integration.md).

## Development commands

| Purpose | Command |
| --- | --- |
| Inspect automatic host preset | `make preset` |
| Configure/build/test through CMake | `make configure`, `make build`, `make test` |
| Full CMake-backed local workflow | `make workflow` |
| Independent native test path | `make check` |
| Generate Doxygen HTML | `make doc` |
| Check release-version agreement | `make version-check` |
| Regenerate agent skill index | `make skills-lock` |
| Verify agent skill index | `make skills-lock-check` |

`DEBUG=1` and `VERBOSE=1` select matching Make/CMake preset variants. Consult
[CMake presets](doc/presets.md) before assuming every nominal platform and
architecture combination is continuously tested.

## Project boundaries

StoneyDSP is the portable engine and package layer. It is not the place for:

- JUCE `AudioProcessor` classes, plugin formats, host automation, or product
  state trees;
- web application code, WebGL renderers, browser assets, or product UI scenes;
- REAPER deployment files or JSFX runtime code;
- proprietary presets, product strategy, licensing policy, or release assets.

Those concerns belong in consumer repositories. Experiments in JSFX,
Reaktor Core, WebAudio, legacy plugins, and hardware-inspired DSP are valuable
inputs, but become StoneyDSP code only after their stable, portable behaviour
has been specified and tested.

## Documentation

- [Architecture and boundaries](doc/architecture.md)
- [Consumer integration](doc/consumer-integration.md)
- [Portable public API](doc/portable-api.md)
- [DSP discovery and promotion](doc/dsp-development.md)
- [Native/web UI bridge direction](doc/ui-bridge.md)
- [CI and release validation](doc/ci-release.md)
- [Project workflow](doc/project-workflow.md)
- [Agent workflows](doc/agent-workflows.md)
- [AI usage statement](doc/ai-statement.md)

## Licence

See [LICENSE](LICENSE) for the current repository licence text. The longer-term
library licensing model remains an explicit project decision; this README does
not grant a different licence or imply a licence for future commercial
products.

## AI usage

StoneyDSP predates generative AI. AI is sometimes used as a supervised aid for
typing, research, inspection, and validation; architecture, DSP judgement,
review, and release authority remain human responsibilities. See
[How AI is used in StoneyDSP](doc/ai-statement.md).
