# JSFX Workbench Relationship

The separate `jsfx-workbench` repository is a REAPER prototyping,
field-testing, and product-experiment workspace—not a StoneyDSP build
component.

## Decision

Keep the workbench separate. Do not add it as a Git submodule, vendored tree,
or hidden test fixture in this repository.

The boundary is useful because the projects have different runtimes and release
cycles:

- StoneyDSP owns portable C/C++ DSP, CMake/package exports, and reusable tests.
- The workbench owns EEL2/JSFX experiments, REAPER projects, plugin manifests,
  deployment, and runtime listening or measurement evidence.
- A future JUCE product owns host integration, UI, state, presets, packaging,
  and commercial release decisions.

The workbench is nevertheless an important companion. It can answer musical
and behavioural questions quickly before a native implementation exists, while
StoneyDSP remains the place where a proven algorithm is deliberately translated
into portable production code.

## What to bring across

The useful imports are practices and evidence, not the repository itself:

- Keep a canonical agent guide, durable project context, and ignored
  branch-specific current-work notes.
- Use explicit work-item indexes and detailed notes to preserve decision chains,
  non-goals, validation evidence, and handoff state across sessions.
- Treat static lint as one layer only. Separate syntax checks, signal benches,
  functional operating points, DSP measurements, and REAPER runtime evidence.
- Keep source under version control and REAPER's resource directory as a
  clearly marked, reversible deployment/runtime boundary.
- Generate catalogs and metadata from source, with a check mode that detects
  stale generated documentation.
- Keep shared modules small, versioned, and directly declared by consumers;
  avoid implicit recursive dependency behaviour.
- Use conservative, portable editor/agent adapters that point back to one
  canonical guide instead of duplicating policy.

These patterns are now represented in `AGENTS.md`, `.agents/project-context.md`,
`.agents/current-work.template.md`, `doc/agent-workflows.md`, and the skill
lock workflow in this repository.

## What not to import

Do not copy EEL2 syntax, REAPER deployment scripts, plugin manifests, JSFX
templates, or the workbench's provisional module lifecycle into the C++ library.
Those are runtime-specific concerns. Do not treat a passing `jsfx-lint` result
as proof that a C++ DSP block is correct, and do not make the REAPER Effects
directory a source or build input.

## Recommended tandem loop

1. Explore a sound or control idea in the workbench with a named fixture and
   recorded operating points.
2. Record the signal path, assumptions, measurements, and unresolved questions
   in the workbench's current-work note.
3. Translate only the stable algorithmic contract into a JUCE-independent
   StoneyDSP slice, with C++ tests and fixtures.
4. Compare the native result against the JSFX reference where equivalence is
   intended; document intentional differences rather than forcing bitwise
   parity with EEL2.
5. Let the eventual product repository own the JUCE wrapper and UI integration.

This gives the workbench a respected role as a rapid research and listening
instrument without allowing exploratory REAPER code to define the library's
public API.

## Reaktor Core discoveries

The workbench is not the only valid source of new work. Native Instruments
Reaktor Core is a visual, block-based DSP environment: a graph of connected
nodes and wires, not a written language in which functions are authored. A
Reaktor creation may therefore be the most useful specification for a new
StoneyDSP experiment even when it has no conventional source listing.

When a Reaktor result is promoted to the StoneyDSP bench, preserve the graph's
meaning rather than pretending it is already C++:

- capture the graph or signal-flow diagram, node roles, and important feedback
  or state edges;
- identify parameter units, ranges, smoothing, reset behaviour, sample-rate
  assumptions, and channel topology;
- separate observed behaviour from the creator's inferred intent and from new
  implementation choices made during translation;
- provide renders, measurements, presets, or listening comparisons at named
  operating points where available;
- record what must remain equivalent and what is allowed to change for a
  portable or realtime-safe implementation.

Reaktor work is an upstream discovery artefact and reference implementation,
not a runtime dependency. The same treatment applies to the user's existing
high-quality Reaktor work, including Trident 80B-inspired console circuits,
SP-1200 conversion/playback paths, Vicanek or matched-z equaliser filters, and
ZDF/filter-toolkit experiments: use them as valuable evidence and design
provenance, then reduce and validate the stable behavioural contract in
StoneyDSP.
