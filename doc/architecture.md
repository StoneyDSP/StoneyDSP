# Architecture and boundaries {#architecture}

## Purpose

StoneyDSP is a reusable, portable C/C++ library for audio-DSP primitives and
their supporting numeric, platform, package, and validation infrastructure.
It is built to be consumed by products rather than to become a product
repository itself.

The durable boundary is:

```text
product repository
  -> product host/UI/state integration
  -> installed StoneyDSP CMake package
  -> portable core, SIMD, and DSP components
```

This separation makes it possible to develop a JUCE plugin, a VCV Rack module,
an embedded application, or another client in parallel without turning any one
host framework into a StoneyDSP dependency.

## Repository shape

| Area | Responsibility |
| --- | --- |
| `include/stoneydsp/` | Public C and C++ headers. |
| `src/stoneydsp/` | Compiled implementation units. |
| `test/` | Catch2 coverage that mirrors the public surface. |
| `share/cmake/Modules/` | Component target construction, install, and export plumbing. |
| `share/vcpkg/`, `dep/vcpkg-registry/` | vcpkg publication and development-consumption support. |
| `doc/` | Human-maintained architectural and operational documentation. |
| `.agents/skills/` | Reusable agent procedures for non-obvious project work. |

Public headers and implementation sources are intentionally separate. That is
normal CMake-library organisation and should not be collapsed merely to match
a source-module convention from another framework.

## Components

The intended CMake package components are:

- `StoneyDSP::Core`: types, language/compiler/platform abstraction, C helpers,
  and numerical foundations;
- `StoneyDSP::SIMD`: portable SIMD-facing facilities, currently scaffolded
  around SIMDe;
- `StoneyDSP::DSP`: reusable DSP primitives, filters, and processing blocks;
- an aggregate StoneyDSP target where an application wants the assembled
  library.

Components should expose a deliberate public surface. A low-level component
must not gain JUCE, plugin-host, WebBrowser, or product-UI dependencies through
a higher-level consumer.

## Public API model

StoneyDSP has both C and C++ consumers in mind.

- C-facing declarations use the library's datum types, language/linkage
  macros, and public-function visibility annotations.
- C++ may add templates, namespaces, explicit processor state, and aliases for
  useful supported precision specialisations.
- A class owns its realtime state and expresses processing through its member
  functions. Non-owning processing helpers are reserved for genuinely
  stateless operations or explicit C-facing APIs.
- Visibility is opt-in at declaration level. Do not make an entire class or
  namespace exported merely because one public member is needed.

The C API is a first-class portability direction, not an afterthought. It is
valuable to consumers that do not want or cannot use a C++ ABI, including some
embedded or foreign-language integrations. See [Portable public API](portable-api.md).

## Product and UI boundary

Products own host integration, parameters, state serialization, UI, presets,
assets, packaging, and commercial policy. StoneyDSP owns the engine-level
behaviour that can be used independently of a particular host or renderer.

The intended native/web product arrangement is:

```text
TypeScript / HTML / CSS / Canvas / WebGL
                <-> bounded bridge
JUCE shell, host automation, product state
                <-> realtime-safe control/state handoff
StoneyDSP DSP engine
```

The native side remains authoritative for audio processing, smoothing, reset,
automation, and saved state. Browser lifecycle must never determine whether
audio continues. See [Native/web UI bridge](ui-bridge.md).

## Discovery inputs are not dependencies

JSFX, Reaktor Core, WebAudio analysis tools, older personal plugins, and
hardware research are valuable ways to discover a model or prove a behaviour.
They are not source dependencies of StoneyDSP. The portable algorithmic
contract, state model, units, and validation evidence must be recovered before
code is promoted into this library. See [DSP discovery and promotion](dsp-development.md).

## Version and release contract

`VERSION` is the tracked release-version source. It must agree with the root
vcpkg manifest, `package.json`, and port manifest. Use the supplied commands:

```sh
make version-check
make version-sync
make version-bump VERSION_INCREMENT=patch
```

Do not manually desynchronise one package manifest from the others. A version
bump is a reviewable compatibility and packaging event, not incidental build
metadata.
