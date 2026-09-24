# StoneyDSP Project Context

This file is durable project context for agents and maintainers. It describes
the intended boundaries and current direction; it is not a substitute for live
source, current CI results, or branch-specific notes. Keep temporary work in
`.agents/current-work/`.

## Project identity

StoneyDSP is a reusable, portable C/C++ audio DSP library. It is intended to
provide core types and platform/compiler abstractions, SIMD facilities, DSP
building blocks, CMake APIs, install/export metadata, and vcpkg consumption for
downstream products.

The library is deliberately separate from eventual products: effects,
instruments, plugins, VCV Rack modules, standalone applications, and web or
native frontends normally belong in their own repositories. A product may be
developed beside or with a pinned checkout of StoneyDSP, but product UI,
licensing, presets, host integration, packaging, and commercial decisions do
not belong in this repository unless explicitly requested.

## Repository map

- `include/stoneydsp/`: public C/C++ headers and module APIs.
- `src/stoneydsp/`: implementation translation units for the aggregate,
  `core`, `simd`, and `dsp` components.
- `test/`: Catch2 tests, generally mirroring the public header hierarchy.
- `share/cmake/Modules/`: project CMake helpers and component target builders.
- `share/vcpkg/`: the StoneyDSP vcpkg port used for package publication.
- `dep/vcpkg-registry/`: local registry ports, baselines, and triplets used by
  this repository and downstream projects.
- `doc/`: Doxygen configuration and project documentation.
- `bin/`: small executable/test entry-point sources.
- `extras/`: non-code assets such as icons.
- `.agents/skills/`: repo-local agent skills and their references.
- `skills-lock.json`: generated skill inventory and content hashes.
- `scripts/generate-skills-lock.sh`: generator/check for the skill inventory.

The repository currently contains a substantial portable core/type-system
foundation and build/package infrastructure. SIMD and DSP public surfaces are
present but comparatively early: SIMD support is scaffolded around SIMDe, and
the DSP component currently contains a small widget/gain starting point rather
than the eventual converter-colour engine.

## Documentation and generated artefacts

`doc/README.md` is the documentation map. `doc/Doxyfile` is the Doxygen
configuration and its input list; `doc/agent-workflows.md` describes the
context re-discovery, skill, documentation, validation, and worktree routines.
Run `make doc` after configuring/generated headers are available. Doxygen
writes disposable HTML under `build/doc/html/`; generated HTML is not a source
of truth.

`skills-lock.json` is generated from every `.agents/skills/**/SKILL.md` by
`make skills-lock`. Use `make skills-lock-check` to detect drift. Keep
branch-local `.agents/current-work/` ignored and use `.cache/<specific>` for
other disposable agent/tool output.

## Public component and package model

CMake is the canonical definition of configure, build, test, installation,
exports, and packaging. `CMakePresets.json`, CMake target definitions, and CI
are authoritative when another workflow disagrees.

The intended stable public component targets are:

- `StoneyDSP::Core`
- `StoneyDSP::SIMD`
- `StoneyDSP::DSP`
- the aggregate StoneyDSP target/package where applicable

Component options include `STONEYDSP_BUILD_CORE`, `STONEYDSP_BUILD_SIMD`,
`STONEYDSP_BUILD_DSP`, and `STONEYDSP_BUILD_TEST`. Preserve exported target
names, component dependencies, install destinations, generated version files,
and public include paths when changing the build system. The current production
checkout's generated install targets do not yet match the intended names, so
package-contract repair and an external consumer test are required before the
next product relies on them.

The Makefile remains a useful command facade and manual-development fallback.
Some targets delegate to CMake (`configure`, `build`, `test`, `workflow`),
while other legacy targets have independent compiler/linker/install recipes.
Do not treat both paths as equivalent. Prefer direct CMake/CTest validation for
release, package, export, and downstream-consumer claims until duplicate Make
recipes are deliberately reconciled.

Useful canonical forms are:

```sh
cmake --preset x64-linux-release-verbose
cmake --build ./build --preset x64-linux-release-verbose
ctest --test-dir ./build --preset x64-linux-release-verbose
```

The repository also supports platform/architecture presets for Windows,
macOS, and Linux, including x86, x64, and arm64 where the current matrix
permits them. `DEBUG=1` and `VERBOSE=1` affect Make's preset selection.

## Downstream consumption evidence

`StoneyVCV` proves the intended dependency workflow: a separate VCV Rack
repository supplies a pinned StoneyDSP checkout to a local vcpkg port, builds
and installs it through CMake, then consumes the package with
`find_package(StoneyDSP ... CONFIG)` and targets such as `StoneyDSP::Core`,
`StoneyDSP::SIMD`, and `StoneyDSP::DSP`.

That consumer currently pins an older StoneyDSP layout. The present production
checkout has since refactored its target names, namespace, package files, and
build-tree exports. Do not claim the current package contract is proven until a
fresh external consumer test installs this checkout through vcpkg and compiles
against the intentionally selected public targets. Preserve the established
`StoneyDSP::Core`, `StoneyDSP::SIMD`, and `StoneyDSP::DSP` names unless an
explicit compatibility decision replaces them.

The dependency pattern remains intentional and should be reused for future
products:

```text
product repository
  → vcpkg manifest/registry or local overlay port
  → StoneyDSP CMake package
  → exported component targets
```

For active tandem development, a product may pin or submodule a local
StoneyDSP checkout and package that source through vcpkg. Release builds must
remain reproducible from a pinned package/version or immutable commit. The
package manager is the consumer boundary; a submodule or nested checkout is
only source provisioning for development.

## Coding and compatibility principles

Preserve the C and C++ compatibility layers, visibility/export macros, include
guards, generated-version substitutions, namespace conventions, and portable
header assumptions. Do not introduce JUCE or a product's host/UI dependencies
into reusable core/DSP targets.

DSP classes should be small and composable, with explicit units, state
ownership, reset semantics, processing order, and numerical boundaries. Keep
clean utility gain, drive, rail/headroom, filtering, quantisation, dither,
feedback, and modulation conceptually distinct. Realtime code must not allocate,
lock, perform I/O, or depend on UI/browser state in the audio callback.

Use the repo-local `analogue-circuit-dsp` skill when modelling analogue
boundaries, filters, rails, feedback, nonlinearities, or validation. Keep facts
from measurements/schematics separate from inferences and intentional design
choices. Validate with fixtures and measurements as well as listening when a
change is intended to alter sound.

## Product direction: converter-colour effect

The first substantial product planned around StoneyDSP is an original stereo
converter-colour insert effect. It is inspired by the general architecture of
early digital recording/sampling systems, not an exact emulation of any named
hardware. The product identity is independent virtual record and playback
conversion rates treated as a creative colour system.

The initial signal story is:

```text
IN → ADC-like stage → PCM section → DAC-like stage → OUT
```

The proposed model is:

```text
clean input trim
→ input soft rail
→ ADC anti-alias low-pass
→ record virtual clock / sample-hold
→ ADC TPDF dither and quantiser
→ PCM coarse/fine gain
→ playback virtual clock / sample-hold
→ optional second dither and quantiser
→ DAC reconstruction low-pass
→ output soft rail
→ optional DC blocker
→ compensated output / dry-wet mix / output trim
```

Important product decisions already established in the design handoff:

- stereo insert effect, not a sampler instrument;
- independent Record Rate and Playback Rate;
- machine-domain rate range approximately 128–32768 Hz (eight octaves),
  independent of host sample rate;
- manual rate values quantised to integral Hz, with continuous fractional
  post-lattice modulation;
- shared 1–32 bit-depth control for the first implementation;
- standard signed quantiser scalar `2^(B-1)` and code range `[-S, S-1]`;
- independent TPDF dither streams per channel, stage, and uniform source;
- coarse gain in binary bit steps and a musically useful fine gain control;
- simple smooth monotonic soft rails before the first and after the last
  modelled core stage;
- ADC anti-alias and DAC reconstruction filters track their respective virtual
  rates and execute at host rate;
- second quantiser retained but defeatable;
- rate modulation is the centrepiece; broad modulation of every parameter is
  not an MVP goal;
- host-independent machine semantics: changing host rate should not silently
  change the meaning of a preset.

Explicit first-product non-goals include a sampler/pad, pitch shifter,
varispeed table reader, mastering-grade SRC, full dither laboratory, extra VCF,
arbitrary modular routing, independent converter bit depths, and a VCV Rack
module before the effect exists.

## Converter implementation sequence

The recommended vertical slices are deliberately sound-engine-first:

1. Deterministic mono native core: trims, rails, filters, virtual clocks,
   holds, quantisation, PCM gain, reconstruction, and output.
2. Stereo state, independent deterministic dither, rate modulation, LFO, and
   envelope behaviour.
3. Product-side JUCE shell, parameter tree, state serialization, bus layouts,
   and a temporary editor.
4. Minimal web UI bridge and first product panel.
5. Host matrix, presets, packaging, signing, diagnostics, and beta validation.

The first engine should be usable offline without JUCE. Product integration
should prove that the same native engine remains deterministic and musically
consistent across host sample rates, block sizes, realtime/offline rendering,
and stereo layouts.

Tests should cover rate mapping, phase preservation, clock tick counts,
quantiser code boundaries and tie rules, dither distribution/independence,
rail monotonicity and asymmetry, filter stability, reset behaviour, bypass,
dry/wet boundaries, and NaN/Inf/denormal safety. Retain audio fixtures for
silence, DC, impulse, sines, sweeps, noise, and representative programme
material.

## Native/web UI direction

The most valuable UI insight from the experimental `stoneydsp.com` repository
is the binding of a web-like SPA frontend to a native JUCE audio engine through
JUCE's `WebBrowserComponent` and its supported JavaScript/native bridge. The
scene/graph/application architecture in that repository is experimental and is
not the canonical StoneyDSP product architecture.

The intended product boundary is:

```text
TypeScript / HTML / CSS / Canvas / WebGL UI
            ↕ explicit bounded parameter/state bridge
JUCE plugin/native shell and host integration
            ↕ authoritative realtime-safe native state
native DSP engine, including StoneyDSP
```

The native side owns audio processing, parameter smoothing, state recall,
reset semantics, host automation, and realtime safety. The browser is a
presentation and interaction surface. UI lifecycle, browser availability, or
frontend rendering failures must not interrupt audio processing.

Before designing a large shared UI abstraction, a small JUCE/WebBrowser spike
should prove:

1. web UI → native parameter update;
2. native parameter/state → web UI update;
3. editor close/reopen and project/preset recall;
4. audio continuity independent of browser lifecycle;
5. packaged frontend assets inside the plugin;
6. useful behaviour in at least one real host.

## Possible StoneyUI repository

A separate StoneyUI repository may eventually provide product-line UI
infrastructure. Its stable first layer should be contracts and design-system
infrastructure, not a universal widget implementation:

- control identifiers, values, metadata, and state updates;
- binding/lifecycle semantics and bridge messages;
- design tokens, colour systems, typography, spacing, and motion;
- test utilities and host/bridge fixtures;
- renderer-specific packages only after a second product proves reuse.

Lightning/WebGL, DOM/Web Components, and native `juce::Graphics` may share
contracts and visual tokens without sharing concrete widget source. Web
Components assume a DOM runtime; Lightning/WebGL and native JUCE rendering
have different lifecycle and layout primitives. Avoid forcing all three into a
lowest-common-denominator component API.

Products should own product-specific scenes, layouts, engine adapters, host
bindings, presets, licensing, and packaging. A second consumer—not the size of
`stoneydsp.com`—is the evidence needed before extracting a shared UI package.

## TypeScript utility boundary

The separate `nathanjhood/utils` workspace is a general-purpose TypeScript
project. Its `@nathanjhood/int` package mirrors primitive integer names and
its shared package provides validators, but it is not currently a StoneyDSP or
audio/UI product package. It is also independently licensed as GPL-3.0-only.

Do not move that workspace into this C++ library or call it StoneyUI by
default. A future StoneyUI package may consume small, deliberately selected
TypeScript utilities, while a cross-language numeric contract would need its
own `@stoneydsp/*` package, tests, versioning, and explicit licence decision.
Until a real consumer proves that need, keep the utility workspace separate
and avoid making TypeScript's nominal integer types a C++ API requirement.

## REAPER JSFX workbench relationship

The REAPER `jsfx-workbench` remains a distinct companion repository, not a
submodule or source subtree of StoneyDSP.
It has a different runtime and release boundary: EEL2/JSFX experiments,
REAPER-native signal benches, plugin manifests, deployment, and field evidence
belong there. StoneyDSP owns the portable C/C++ translation, package exports,
and production-facing tests. The REAPER Effects directory is runtime/install
space, never a StoneyDSP source or build input.

The workbench's most valuable contribution is cultural and methodological:
canonical agent guidance, durable project context, ignored branch-local
current-work notes with an index, thin editor adapters, generated source
catalogues with check modes, and explicit separation of static lint, signal
bench, DSP measurement, and runtime evidence. These conventions are captured
in `doc/jsfx-workbench.md` and adapted to this repository's CMake/Doxygen/vcpkg
workflow.

Use the workbench for rapid listening and behavioural exploration. When an idea
is stable, record its signal path, operating points, measurements, assumptions,
and unresolved questions there, then translate the algorithmic contract into a
JUCE-independent StoneyDSP slice. Compare outputs where equivalence is intended,
but do not make EEL2 implementation details or bitwise parity prerequisites for
the C++ API.

## WebAudio analysis tools as validation clients

The separate `fft-spectrum-analyser`, `spectogram`, and `oscilloscope`
repositories are useful visual analysis and instrumentation clients. Keep them
separate from StoneyDSP: they combine
browser `AudioNode`/`AnalyserNode` or AudioWorklet acquisition, Canvas rendering,
display persistence/freeze/trigger state, and Vite/TypeScript lifecycle.

Their durable value is as validation clients for a native engine and as design
evidence for a future StoneyUI or analysis package. Preserve explicit numerical
and display contracts—FFT size, sample rate, dB floor/ceiling, smoothing,
channel/mid-side mode, trigger semantics, persistence, and coordinate mapping—
without making browser `AnalyserNode` behaviour the C++ API by accident.

Only extract portable FFT, windowing, level, or trigger kernels after a second
consumer establishes the need and known signal fixtures define the contract.
Keep analysis kernels, bridge/transport adapters, and Canvas/WebGL/DOM/native
renderers as separate layers. Visual traces complement, but do not replace,
sample-accurate tests, offline fixtures, null/residual comparisons, or host
runtime evidence. The intentional aliasing in simple oscillator/worklet
fixtures makes them useful smoke-test sources, not production oscillator
references.

## Reaktor Core as a discovery source

New StoneyDSP work may also originate in Native Instruments Reaktor Core. Treat
Reaktor Core correctly as a visual, block-based DSP graph: nodes are connected
with wires, and the artefact is not a written programming language with
user-authored functions. A Reaktor patch can be a strong reference
implementation and musical proof without being directly portable source code.

For a Reaktor-derived work item, ask for the graph/signal-flow description,
node and feedback/state roles, parameter units and ranges, reset and smoothing
semantics, sample-rate and channel assumptions, and any renders or measurements
at named operating points. Keep observed behaviour, inferred intent, and new
C++ design choices explicitly separate. Preserve only the stable behavioural
contract in StoneyDSP; Reaktor is neither a library dependency nor a hidden
runtime in this repository.

The user's prior Reaktor Core work—including Trident 80B-style console
circuits, SP-1200 sampler/playback paths, Vicanek or matched-z equalisers, and
ZDF/filter-toolkit designs—is valuable provenance for future experiments. It
should enter the bench as topology, transfer-function, state, and validation
evidence, then be reduced into small portable C++ blocks and tests. Use the
analogue-circuit-dsp skill whenever the translation involves analogue
boundaries, feedback, filters, rails, nonlinearities, or null/measurement
design.

## Workflow and change discipline

Keep library and product repositories independently reviewable and versioned.
During tandem development, a product may consume a local pinned checkout via a
vcpkg overlay port; after validation, update the product's pinned dependency to
an intentional StoneyDSP commit or package version. Do not make product code a
hidden test fixture inside the library.

Keep changes narrow and record unresolved architectural choices in an ADR or
branch-local note rather than silently freezing public parameter IDs, state
formats, or UI bridge protocols. Preserve unrelated user changes and inspect
`git status --short --branch` before edits.

## Recommended next move

First repair and externally test the current CMake/vcpkg consumer contract;
this is a bounded prerequisite because StoneyVCV proves an older package
layout, not the current refactor. Then create a separate gain-utility product
repository as the first full vertical slice. It should consume StoneyDSP via
vcpkg, build selected JUCE plugin/standalone targets across the supported
desktop matrix, and prove automation, state, embedded assets, and a minimal
Canvas/WebGL native/web binding while keeping the audio engine independent of
the browser lifecycle.

Use the active `.agents/current-work/` note as the detailed near-term scope and
acceptance gate. The FFT analyser should be the second slice: it can reuse the
proven shell and UI bridge, then add native-to-UI analysis telemetry as the one
major new risk.

## Current open decisions

These are intentionally unresolved and should not be silently decided by an
agent:

- first shipping product repository, JUCE version, formats, and host matrix;
- Butterworth order and exact cutoff coefficient;
- hidden output DC blocker and its validation criteria;
- fine-gain canonical range versus the currently successful overlapping range;
- exact second-quantiser and dither UX;
- global drive range and rail/asymmetry mapping;
- LFO transport/reset policy and envelope sidechain fallback;
- dry/wet latency/phase policy;
- float versus double processing policy for nominal 25–32-bit settings;
- StoneyUI package/repository split and the first renderer to standardize;
- licensing/trial/offline policy for low-priced products.
- the shared-library licence text, which currently combines MIT wording with a
  second set of redistribution restrictions and commercial-policy links. The
  current working recommendation is Apache-2.0 for the reusable library and
  separate proprietary product licences, subject to provenance and legal review.

Do not let these block the JUCE-independent mono DSP slice unless a decision is
required by the code being written.
