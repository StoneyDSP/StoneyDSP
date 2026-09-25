---
name: analogue-circuit-dsp
description: Develop and review behavioural analogue-circuit models for audio DSP, especially JSFX/EEL2 workbench experiments. Use when translating schematics, measurements, or circuit behaviour into reusable DSP blocks; deciding model boundaries; separating ideal controls from finite analogue stages; modelling rails, feedback, bandwidth, slew, noise, summing, filters, or nonlinearities; and designing validation/null tests. Prefer topology-informed, measurable abstractions over component cosplay, and keep project-specific evidence distinct from general modelling assumptions.
---

# Analogue Circuit DSP

Build analogue-inspired DSP as a system of testable behavioural blocks rather than as a pile of unrelated saturators or a premature component-by-component clone.

## Core stance

- Treat schematics, measurements, and known hardware behaviour as evidence for topology and limits.
- Preserve the distinction between:
  - **fact**: directly supported by a schematic, measurement, datasheet, or known implementation;
  - **inference**: a reasonable reduced interpretation of that evidence;
  - **design choice**: an intentionally invented DSP abstraction.
- Never promote an inference into a fact merely because it sounds plausible.
- Prefer the leanest model that reproduces the behaviour under test.
- Do not model resistor/capacitor values individually when they only determine already-known operator ranges or static transfer curves.
- Do model electrical relationships when they affect interaction, headroom, feedback, frequency response, loading, stability, or state.

## Model in layers

Use this hierarchy unless the evidence strongly suggests otherwise:

1. **Ideal control layer**
   - faders, gain controls, pan laws, switches, routing, taps;
   - mathematically exact unless their nonideality is itself the subject of the model.
2. **Passive / frequency-selective layer**
   - filters, correction branches, attenuators, resistive sums, coupling networks.
3. **Active layer**
   - finite gain, finite bandwidth, feedback, output swing, slew, active loading.
4. **Shared-system layer**
   - buses, common summing nodes, shared feedback, branch interaction, channel count effects.
5. **Noise / tolerance layer**
   - add only when needed for the question being answered.

Do not add analogue colour just because the block is analogue in the hardware.

## Separate blocks before composing them

When possible, validate individual blocks independently before chaining them.

For each block:

- define input/output units;
- define ideal reference behaviour;
- expose or log useful internal state for laboratory builds;
- verify static response;
- verify dynamic/stateful response;
- verify level dependence;
- verify sample-rate dependence;
- only then place it into the wider signal path.

Once the block is trusted, preserve a known-good revision before adding interactions or nonlinearities.

## Use ideal / finite / residual comparisons

For topology-changing processors, prefer an internal monitor mode over host bypass:

- **Ideal**: same routing and nominal transfer, but idealized active behaviour;
- **Finite**: the actual behavioural model;
- **Residual**: `Finite - Ideal`.

Use Residual/null modes to reveal subtle bandwidth, phase, slew, rail, feedback, and nonlinear differences that ordinary A/B listening can mask.

Host bypass is not a valid ideal reference when bypass changes routing, channel summation, latency, or tap structure.

## Global voltage coordinate system

Unless a project explicitly overrides it, use this modelling convention:

- `0 dBFS reference = 24 V peak model voltage`;
- normalized sample `x = V / 24`;
- model voltage `V = 24 * x`.

This is a **coordinate/reference system, not a hard DSP limit**.

Therefore:

- signals may exceed `0 dBFS` internally in floating-point processing;
- a 30 V circuit rail simply maps above 0 dBFS;
- each circuit owns its own rails, usable swing, nominal level, and noise floor;
- changing rail voltage does not automatically change noise floor;
- changing noise floor does not automatically change headroom.

Treat approximately `24 / 2^24 = 1.43 uV` as a useful 24-bit reference-floor marker, not literal mathematical silence and not a universal analogue noise floor.

Read [references/voltage-and-levels.md](references/voltage-and-levels.md) when converting between normalized samples, volts, bits, dBFS, rails, or noise floors.

## Gain-domain convention

For binary gain controls, prefer:

`gain = 2^bits`

so:

- `+1 bit = x2 = +6.0206 dB`;
- `-1 bit = x0.5 = -6.0206 dB`.

Keep the operator-facing control law separate from the physical model. A clean gain scalar may be used before or after a finite stage to alter operating point or compensate nominal output level, provided the placement is explicit.

Do not confuse:

- **drive**: how much signal is presented to a stage;
- **closed-loop gain**: how much gain the active stage itself is asked to produce;
- **feedback factor**: an internal consequence of topology, often inverse to closed-loop gain.

## Active-stage baseline

A reusable behavioural active stage may include:

- finite open-loop gain;
- dominant-pole / gain-bandwidth behaviour;
- configurable closed-loop feedback;
- finite output swing;
- explicit or emergent slew/rate limitation;
- nonlinear transfer inside the feedback loop when justified;
- optional clean post-stage compensation for controlled A/B tests.

Do not assume a post-filter saturator is equivalent to a nonlinearity inside the feedback system.

When using an implicit nonlinear feedback equation, solve the current-sample relationship consistently. Use Newton-Raphson or another solver only when the algebra actually requires it. The derivative is solver machinery, not a separate audio effect.

Read [references/nonlinear-feedback.md](references/nonlinear-feedback.md) for solver and rail guidance.

## Filters and correction signals

Distinguish complete transfer functions from correction branches.

For a complete filter output `H(x)`, define its correction contribution as:

`delta = H(x) - x`

Then a parallel correction topology can be assembled as:

`y = x + delta1 + delta2 + ...`

At unity settings, every correction branch should produce practical silence.

Do not sum multiple complete full-band filter outputs plus dry unless that multiplication of the dry path is intentionally part of the topology.

Remember that:

- serial filters combine by transfer-function multiplication;
- parallel correction branches combine by addition;
- these are equivalent for one isolated branch but diverge when several branches are active;
- apparent movement of peaks/notches in a parallel network can arise purely from complex linear superposition, without coefficient or state coupling.

## Shared systems and summing

Retain independent sources until the modelled summing point if source-count or bus interaction is part of the experiment.

Do not digitally sum sources first and then claim a post-sum nonlinearity models the electrical summing network.

For multi-input bus models:

- preserve separate source inputs;
- model resistive/current contributions where relevant;
- give left and right buses independent state unless the hardware couples them;
- separate the ideal-sum reference from finite recovery-amplifier behaviour;
- test one loud source versus many quieter sources at equal final sum.

## Nonlinearity placement

Ask **where the nonlinearity physically participates** before choosing a waveshaper.

Possible cases include:

- memoryless output rail;
- nonlinear element inside feedback;
- nonlinear integrator/state update;
- shared nonlinear summing node;
- active-stage saturation after a passive network;
- transformer or coupling behaviour with its own state.

Do not stack nonlinearities merely to make a model sound more analogue.

## Parameter smoothing policy

Treat smoothing as part of control infrastructure, not ad hoc DSP decoration.

- Smooth continuous gain-like parameters in their meaningful operator domain when practical.
- Prefer sample-rate-independent time constants.
- Use finite ramps when exact arrival matters, especially for mute endpoints.
- Do not smooth switches/enums unless changing topology requires a crossfade or state handoff.
- Shared/group controls should distribute **targets**, not shared smoothed DSP state; each processor instance owns its own state and smoother.

## Validation workflow

Before trusting a model, test it with appropriate combinations of:

- DC;
- sine waves at multiple levels and frequencies;
- impulses / impulse trains;
- steps;
- saw/pulse waves for edge/rate behaviour;
- sweeps;
- multitone / IMD tests;
- noise;
- null/residual tests;
- real programme material.

Do not rely on sound alone. Do not rely on an analyzer alone. Use both.

Read [references/validation-playbook.md](references/validation-playbook.md) for a compact laboratory checklist.

## Schematic reduction workflow

When given a circuit or PCB:

1. Identify the main audio path.
2. Identify taps, branches, and summing/common nodes.
3. Identify which reactive components create independent states.
4. Identify active stages and feedback loops.
5. Identify which controls change topology versus merely parameter values.
6. Group repeated or shared subsystems before deriving equations.
7. Reduce the circuit into functional blocks.
8. Implement the linear/ideal case first where possible.
9. Add finite active behaviour only after the nominal response is understood.
10. Add noise, tolerances, and component-specific quirks last.

If schematic and PCB are both available, use the PCB/net connectivity to resolve ambiguous schematic grouping before inventing DSP architecture.

## Keep abstractions reusable

Prefer reusable primitives such as:

- `ActiveGainStage`
- `SoftRail`
- `PassiveAttenuator`
- `CorrectionBranch`
- `StateVariableFilter`
- `ResistiveSummingNode`
- `CouplingElement`
- `IdealFader`
- `IdealPanner`

Tune those primitives toward specific hardware later rather than duplicating nearly identical code for every console stage.

## Avoid these failure modes

- Do not chase exact historical component schedules before the topology is stable.
- Do not infer capacitor corner frequency from capacitance alone; surrounding impedance matters.
- Do not invent DC blockers because analogue gear "must have one".
- Do not infer intentional hardware character from unexplained numerical noise or plugin artefacts.
- Do not confuse a broken/oscillating hardware report with normal operating behaviour.
- Do not assume component co-location on a PCB implies intended audio coupling.
- Do not optimize multiple DSP loops into one shared solve until the dependency graph actually requires it.
- Do not use brand/model names as substitutes for an explicit transfer-function or topology description.
