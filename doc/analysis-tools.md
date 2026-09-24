# Analysis and Instrumentation Relationship

The separate WebAudio FFT spectrum analyser, spectrogram (currently named
`spectogram`), and oscilloscope repositories are useful companion applications
for StoneyDSP development. They are not currently candidates for inclusion in
the core library.

## Boundary

Those projects combine three concerns:

1. audio acquisition and analysis through browser `AudioNode`/
   `AnalyserNode` and AudioWorklets;
2. display state such as persistence, freeze, triggering, mid/side views,
   scrolling, palettes, and device-pixel-ratio resizing;
3. browser lifecycle, Canvas rendering, Vite, and TypeScript application code.

Only the first concern might eventually yield a portable StoneyDSP component,
and even that should be earned by a concrete need. The current projects are
best treated as UI/measurement clients and reference instruments, not as a
shared-library source subtree or a product dependency.

## What is useful now

- Use the analyser family as visual validation clients for native DSP and JUCE
  products, alongside offline fixtures and numerical tests.
- Preserve explicit analysis contracts: FFT size, sample rate, decibel floor and
  ceiling, smoothing/integration, channel mode, trigger source/level, freeze,
  persistence, and display coordinate conventions.
- Keep the separation between audio/worklet processing and main-thread drawing;
  rendering failure or browser lifecycle must not affect the audio engine.
- Reuse the projects' small, chainable control APIs and explicit `destroy()`
  lifecycle when designing a future StoneyUI or bridge-facing analyser package.
- Treat the oscillator/worklet fixtures as signal sources for visual smoke tests,
  while remembering that naive saw/square/triangle oscillators intentionally
  alias and are not production-quality DSP references.

## Possible future extraction

If two products need the same analyser behaviour, consider a separate
`StoneyAnalysis` or `StoneyUI` package with three deliberately separated
layers:

- portable analysis kernels and data contracts (FFT/windowing/levels/triggering);
- transport and bridge adapters (JUCE/WebBrowser, WebAudio, offline files);
- renderer packages (Canvas/WebGL, DOM/Web Components, or native JUCE).

Do not make browser `AnalyserNode` semantics the C++ API by accident. First
specify the numerical contract and test it against known sine, impulse, sweep,
noise, and multichannel fixtures. Then decide whether a shared implementation
belongs in StoneyDSP, an analysis package, or remains application-local.

For now, keep the source repositories independent and use their outputs as
evidence: a visual trace can reveal behaviour, but it does not replace
sample-accurate tests, null/residual comparisons, or host/runtime validation.
