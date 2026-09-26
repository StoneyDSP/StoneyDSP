# Repository Guidelines

## Agent Context

Start by reading this file before making repository changes. Read
`.agents/project-context.md` when it exists before making repository-wide
tooling, workflow, or agentic configuration changes. If
`.agents/current-work/00-index.md` exists locally, read it and then only the
matching detailed notes. Treat them as non-canonical working state between the
user and current agent; live repository state and explicit user direction take
precedence.

The durable project context should describe the current library architecture,
supported toolchains, package/export conventions, and active product-consumer
integration decisions without exposing commercial strategy. Keep detailed,
branch-specific notes under
`.agents/current-work/`, using `.agents/current-work.template.md` as the
starting point and `00-index.md` as the concise map. Do not commit private
current-work notes unless explicitly requested.

After context compaction or a fresh session, use the resume sequence in
`doc/agent-workflows.md`: reacquire the canonical guide and project context,
then inspect current worktree state before relying on notes.

## Agent Skill Index

Repo-local skills live under `.agents/skills/` and are indexed by the generated
root file `skills-lock.json`. Run `make skills-lock` after changing a skill and
`make skills-lock-check` when validating agent metadata.

- `.agents/skills/analogue-circuit-dsp/SKILL.md`: behavioural analogue and
  nonlinear DSP modelling, topology reduction, block validation, and audio
  fixture design. Read this skill when working on rails, filters, feedback,
  analogue boundaries, nonlinear stages, or related DSP validation.

When a task concerns a repo-local skill, read its `SKILL.md` completely before
acting and follow any directly referenced validation guidance that applies.

## Project Structure & Module Organization

This is a C/C++ audio DSP library with installable CMake components:

- `include/stoneydsp/`: public headers and module-facing APIs.
- `src/stoneydsp/`: library implementation sources.
- `test/`: Catch2 tests, organized to mirror public library areas.
- `share/cmake/Modules/`: StoneyDSP CMake target and packaging helpers.
- `share/vcpkg/` and `dep/vcpkg-registry/`: vcpkg ports, registry metadata,
  and supported triplets.
- `doc/`: Doxygen configuration and project documentation.
- `.agents/`: durable context, current-work template, skills, and agent
  workflow documentation.
- `bin/`: small executable entry-point sources.
- `extras/`: non-code assets such as icons.

Products and downstream consumers should remain separate repositories. They
consume StoneyDSP through its exported CMake targets and vcpkg package
integration. Do not add a commercial plugin or instrument implementation to
this repository unless the user explicitly changes that boundary.

## Build, Test, and Development Commands

CMake and `CMakePresets.json` are the canonical build, test, install, export,
and package definitions. CI and agent validation should use the relevant CMake
or CTest commands directly, so that the documented source of truth is the same
one used to generate installable packages and downstream consumer targets.

The Makefile is a useful human-facing convenience layer and development
fallback. Some Make targets invoke CMake, while other legacy targets contain
independent compiler/linker recipes. Do not assume those paths are equivalent;
when they disagree, treat CMake presets, CMake targets, and CI as authoritative
until the duplicate Make path has been deliberately reconciled.

The current GitHub workflows invoke `make workflow` for the CMake-backed
developer/package path and `make check` for the independent test path. Preserve
that distinction in reports and do not describe `make check` as package/export
validation without inspecting the target it ran.

- `make preset`: report the automatically selected host preset.
- `make configure`, `make build`, `make test`, and `make workflow`: use the
  corresponding CMake/CTest workflow targets through the Make wrapper.
- `make check`, `make install`, `make doc`, `make all`, and `make clean`: may
  use Make-specific recipes; inspect the target before relying on them for
  package or release validation.

Useful direct CMake/CTest forms include:

```sh
cmake --preset x64-linux-release-verbose
cmake --build ./build --preset x64-linux-release-verbose
ctest --test-dir ./build --preset x64-linux-release-verbose
```

Use `DEBUG=1` and `VERBOSE=1` deliberately; record non-default configuration
when reporting validation. For focused work, prefer the narrowest CMake target
or CTest filter that proves the change, followed by the relevant preset/workflow
before handoff. Do not claim tests passed when only configuration or static
inspection was performed.

Agent/documentation metadata checks are:

- `make skills-lock`: regenerate `skills-lock.json` from repo-local skills.
- `make skills-lock-check`: verify the generated skill index is current.
- `make doc`: generate Doxygen output under disposable `build/doc/html/`.

See `doc/README.md` and `doc/agent-workflows.md` for the documentation map,
context re-discovery sequence, generated-artifact rules, and handoff hygiene.
The separate REAPER prototype relationship is documented in
`doc/jsfx-workbench.md`; do not import its runtime/deployment machinery into
this library.
Reaktor Core patches are another accepted discovery input. Treat them as
visual graph references and behavioural evidence, not as a written language or
an implementation dependency; capture their topology and validation evidence
before translating them into portable C++.
The separate WebAudio FFT/spectrogram/oscilloscope projects are validation and
UI clients, not current StoneyDSP components. Keep analysis kernels,
audio/bridge transport, and renderers separate if a future shared extraction is
justified.
The selected next vertical slice and its current prerequisites are maintained
in the active `.agents/current-work/` handoff note. The package-contract repair
is complete; retain the external consumer fixture as a regression gate.

## CMake, vcpkg, and Consumer Integration

StoneyDSP is consumed as an exported/config-package dependency. The intended
stable public target/component names are:

- `StoneyDSP::Core`
- `StoneyDSP::SIMD`
- `StoneyDSP::DSP`
- the aggregate `StoneyDSP` target where applicable

The current production checkout's component exports have external C/C++ consumer
smoke coverage. Revalidate that fixture whenever public headers, target names,
install destinations, component dependencies, linkage mode, or port metadata
change; do not describe a changed package contract as proven from a library
build alone.

Keep library builds, install/export tests, and vcpkg package tests aligned.
Downstream consumers may use a local StoneyDSP checkout through a vcpkg port
while developing, but release configurations must be reproducible from a
pinned package/version or commit. Verify package consumption from an external
consumer when changing exported targets, headers, install destinations,
component dependencies, or port metadata. `StoneyVCV` proves this workflow
against an older StoneyDSP layout; it does not by itself validate the current
production checkout's refactored package exports.

## Coding Style & Naming Conventions

Follow the existing C/C++ style and public naming conventions. Preserve the
library's C and C++ compatibility layers, visibility/export macros, include
guards, namespace structure, and generated-version substitutions. Keep public
headers portable and avoid introducing JUCE or product-specific dependencies
into the reusable DSP/core targets.

Prefer small, composable DSP classes with explicit units, state ownership,
reset semantics, and documented processing order. Distinguish clean utility
gain, drive, rail/headroom, filter, quantisation, and feedback behaviour rather
than hiding materially different operations behind a generic saturator.

## Testing Guidelines

Add or update focused Catch2 coverage for every behavioural change. DSP tests
should cover deterministic state transitions and relevant numerical boundaries,
not only nominal output samples. Depending on the block, consider:

- static transfer and monotonicity;
- reset and phase/state behaviour;
- sample-rate and block-size dependence;
- clipping, rails, NaN/Inf, and denormal handling;
- impulse, step, sine, sweep, noise, and offline fixture behaviour;
- C and C++ consumer compilation where public compatibility is affected.

For analogue-inspired or nonlinear DSP, use the repo-local
`analogue-circuit-dsp` skill and keep facts, inferences, and intentional design
choices distinct. Validate with both measurements/fixtures and listening when
the change is intended to alter sound.

## Commit & Pull Request Guidelines

Keep commits narrow and reviewable. Separate library implementation, CMake or
package plumbing, generated artefacts, documentation, and unrelated formatting
when practical. Pull requests should state the problem, affected public or
package surface, validation commands, and any downstream-consumer impact.

The historical Git graph is retained as-is; do not rewrite it merely to make
old branches look tidy. From the current integration boundary onward, use
`feature/<slug>` branches from `production`, review through pull requests,
require CI before integration, prefer squash or fast-forward merges, and tag
releases from the stable branch. Treat stale feature branches as archive or
cherry-pick sources after reviewing their unique commits. A future rename of
`production` to `main` is an explicit repository migration, not an incidental
cleanup.

When creating a git commit, include the available Codex credit/token usage in
the commit body. If usage cannot be determined, say that it was unavailable
rather than estimating.

## Security, Generated Files, and Workspace Hygiene

Do not commit credentials, registry tokens, local package-manager secrets,
private certificates, or machine-specific absolute paths. Treat vcpkg caches,
build trees, generated package metadata, skill-lock output, and documentation
HTML as generated unless the repository explicitly tracks the relevant
artefact. Keep generated files in their established locations and ensure a
generator/check command exists when a generated source-of-truth file is added.

Use ignored `.agents/current-work/` for branch-local handoff state. Keep
temporary agent output under ignored `build/`, `dist/`, `out/`, or
`.cache/<specific-concern>/`; do not create ad hoc scratch files beside source.

Before editing, check `git status --short --branch` and preserve unrelated user
changes. Do not reset, checkout, rebase, force-push, or remove material without
explicit authorization. Do not modify downstream product repositories while
working in StoneyDSP unless the user explicitly scopes that work.
