# DSP component

`StoneyDSP::DSP` contains reusable, host-independent audio-DSP primitives. It
depends on Core but must remain independent of JUCE, plugin formats, browser UI,
and product parameter/state classes.

## Current public starting point

The component currently exposes:

- `widgets::Gain<TSamples, TGain>`: an allocation-free, clean linear gain
  processor with explicit stored gain and sample/block operations;
- `filters::BiquadCoefficients<T>`: direct-form coefficient storage and design
  helpers;
- `filters::Biquad<T>`: a single-channel state-owning biquad processor with
  selectable direct-form realisation, reset, sample/block processing, and
  prepared sample-rate state;
- matched/matched-z coefficient helpers for relevant filter shapes.

`Gain` is intentionally only a scalar multiplier. It does not smooth, clip,
drive, saturate, automate, or own host parameters. Those are distinct
behaviours and should remain explicit in a future processor graph.

`Biquad` owns its coefficients and delay/history state. Create one instance per
audio channel. Parameter updates are not presented as a magic independently
atomic realtime transaction; callers must provide coherent update semantics at
the product/control boundary.

## Realtime rules

DSP processors should be small and composable. A processing call must not
allocate, lock, perform I/O, or depend on UI/browser state. The public contract
should state units, state ownership, reset behaviour, processing order,
sample-rate assumptions, and numerical boundaries.

Use stateful class methods for stateful processing. Pure maths, conversions,
and coefficient design may be free/template functions when callers do not need
to own hidden processing state.

## Design and validation

Every DSP addition needs focused numerical/state tests. Depending on the block,
cover transfer response, monotonicity, impulse/step/sine/sweep/noise behaviour,
reset and phase, sample-rate/block size, clipping/rails, NaN/Inf/denormals, and
the external consumer surface.

`doc/dsp-development.md` explains how research, JSFX, Reaktor Core, or legacy
plugin work should be promoted into this component. Use the
`analogue-circuit-dsp` skill for analogue-inspired or nonlinear blocks.
