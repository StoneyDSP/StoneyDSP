---
name: dsp-discovery-promotion
description: Promote a DSP idea from JSFX, Reaktor Core, legacy personal plugins, experiments, papers, or measurements into a small portable StoneyDSP primitive. Use when auditing candidate source, recovering a proven behaviour, defining its contract, or deciding whether it belongs in the library.
---

# DSP Discovery Promotion

Discovery environments are evidence, not dependencies. Promote only the stable
behavioural contract into StoneyDSP; leave product/host/runtime machinery in
its original project.

## Establish provenance and boundary

- Record the candidate's origin and ownership.
- Treat Reaktor Core as a visual graph, not written source code.
- Treat JSFX as a rapid listening/measurement bench, not a C++ implementation
  template.
- Quarantine legacy JUCE/plugin code before importing it. Separate portable DSP
  from GUI, host parameters, allocation, build, and historical assumptions.
- Do not infer a license change from an audit. Escalate unclear provenance.

## Recover a portable contract first

State the signal path, units, ranges, precision, parameter semantics, state,
reset, sample-rate/block/channel assumptions, processing order, edge cases, and
the intended C/C++ public surface.

Distinguish:

- observed behaviour or measured fact;
- inference about the original implementation;
- deliberate new design choice for the portable library.

Use a small state-owning processor class for stateful realtime work. Prefer
member processing methods over a free function that asks callers to manage
private delay/history state. Use free functions for stateless conversions and
coefficient design.

## Promote in small families

Move only the parts that have clear reuse value: coefficient/value types,
maths helpers, conversion functions, or allocation-free blocks. Do not import a
whole product engine to save time. Use named `Constants<T>` values where they
are part of the actual mathematical contract; do not replace every literal with
an abstraction.

## Validation ladder

Start with deterministic numerical tests, then add state/reset, sample-rate,
boundary, consumer/package, and listening/host evidence as relevant. For
analogue-inspired work, load `analogue-circuit-dsp`. For public API or linkage
work, load `public-api-consumer-validation`.

Do not make bitwise equivalence to EEL2, a browser, or a visual graph a default
acceptance criterion. Name the expected equivalence and tolerance instead.

Read `doc/dsp-development.md` for the durable project guidance.
