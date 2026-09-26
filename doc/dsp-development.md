# DSP discovery and promotion {#dsp_development}

## A bench before a public API

StoneyDSP can begin with a sound, a measurement, a visual graph, a legacy
plugin, a JSFX experiment, a paper, or a circuit. None of those is
automatically library code. Promotion into the reusable library begins when the
behaviour can be described independently of its original runtime.

Use this chain:

```text
discovery -> behavioural contract -> isolated implementation -> focused tests
          -> consumer/package evidence -> reusable public API
```

Keep the discovery artefact and the portable implementation separate. A JSFX
file, Reaktor graph, browser analyser, or old JUCE plugin is evidence and
provenance; it is not a hidden dependency or a mandate to preserve old layout.

## Sources of evidence

### JSFX workbench

The REAPER JSFX workbench is an independent rapid research and listening
environment. Use it to establish signal paths, operating points, measurements,
and musical behaviour. Do not import its EEL2 runtime/deployment machinery into
StoneyDSP. When equivalence matters, compare named fixtures; do not require
bitwise parity between two languages with different numerical/runtime rules.

### Reaktor Core

Reaktor Core is a visual graph environment, not a written programming language.
For a Reaktor-derived block, record the topology, node roles, state and feedback
edges, parameter units/ranges, reset/smoothing behaviour, sample-rate/channel
assumptions, and named renders or measurements. Separate observed behaviour,
inferred intent, and new C++ design choices.

### Legacy personal plugins and experiments

Legacy source can contain valuable handwritten DSP, but it may also carry JUCE,
host, build, GUI, or historical API assumptions. Import candidates into a
quarantine/audit area first. Promote only a small, self-contained family once
ownership, dependencies, numerical contract, and tests are clear.

The previous Biquads extraction established useful precedent: direct-form
filters, coefficient design, matched/matched-z coefficient work, maths
constants, and amplitude conversions can become portable modules when stripped
of host dependencies and validated from the installed consumer boundary.

## Contract before code

For every proposed primitive, state:

- input/output units and expected value ranges;
- precision policy and relevant numeric constants;
- owned state, initial state, reset, and denormal behaviour;
- sample-rate/block/channel assumptions;
- parameter update, interpolation, and smoothing rules;
- exact processing order and nonlinearity/filter placement;
- C/C++ public surface and any expected ABI boundary;
- nominal operation plus important edge cases.

Use library maths constants such as `Constants<T>::pi`, `twoPi`, and
`oneDivSqrtTwo` when a named value is part of the mathematical contract. Keep
ordinary scalar arithmetic simple where a cast is clearer than inventing a
constant abstraction.

## Validation ladder

Start small and deterministic:

1. static transfer and coefficient expectations;
2. impulse, step, sine, sweep, and noise fixtures as appropriate;
3. reset, state, phase, and sample-rate behaviour;
4. boundary cases: silence, DC, clipping/rails, NaN/Inf, denormals;
5. C/C++ compilation and external consumer/package coverage;
6. listening and host evidence when the change is intended to alter sound.

For analogue-inspired work, use the `analogue-circuit-dsp` skill. Preserve
the difference between a measured fact, an engineering inference, and an
intentional design choice.

## Public API restraint

Do not promote a product processor wholesale because its DSP is interesting.
Prefer coefficient/value types, small allocation-free processors, conversion
helpers, or isolated stateful blocks with clear reuse value. Delay a broad
audio-engine abstraction until a second consumer proves the common contract.

This is especially relevant for parameter systems and smoothing. The first
gain product should establish the actual host/UI/native-control boundary before
StoneyDSP commits to a generic `AudioParameter` hierarchy or universal smoother
API.
