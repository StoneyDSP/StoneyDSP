# Native/web UI bridge direction {#ui_bridge}

## Purpose

The valuable result from the experimental `stoneydsp.com` work is not its
scene/graph architecture. It is the demonstrated possibility of binding a
web-like frontend to a JUCE-native audio engine through JUCE's
`WebBrowserComponent` and JavaScript/native bridge.

The first product should prove this boundary with a deliberately small panel,
not establish a complete design system prematurely.

## Authority boundary

```text
web UI -> bounded parameter intent -> native parameter/control layer
native state -> bounded state snapshot/update -> web UI
native engine -> realtime audio processing -> host/audio device
```

The native side owns:

- realtime DSP and all audio-thread safety;
- host automation, parameter state, smoothing, reset, and preset recall;
- authoritative parameter values and state serialization;
- lifecycle behaviour when the editor or browser does not exist.

The frontend owns:

- presentation, interaction, layout, accessibility where applicable, and
  renderer-specific animation;
- temporary interaction state that can be discarded and reconstructed from a
  native snapshot.

Audio must continue correctly if the browser fails to load, the editor closes,
or a frontend frame is late.

## First bridge spike

Before introducing a shared UI framework, prove all of the following in one
small JUCE product:

1. UI gesture updates a native parameter.
2. Host/native parameter update reaches the UI.
3. Editor close/reopen and preset/project recall reconstruct the UI correctly.
4. Audio continues independently of browser availability.
5. Frontend assets package inside the plugin.
6. The result behaves usefully in at least one real host.

Bridge messages should be explicit, versionable, bounded in size/rate, and
separated into parameter intent, authoritative state, and diagnostic/telemetry
classes. Do not stream arbitrary audio-thread state into a browser.

## Parameters and smoothing

The desired product controls include continuous and stepped values, booleans,
and choices. It is reasonable for a TypeScript UI to render a `ParameterFloat`,
`ParameterBool`, or `ParameterChoice`-like model, but it must not become the
authoritative parameter implementation.

The native host-facing layer should establish the real parameter identifiers,
ranges, normalisation, automation semantics, defaults, and smoothing policy.
Only then should a shared UI contract mirror those choices. A UI gesture does
not itself make an audio-rate modulation signal safe; the native layer decides
how a value reaches DSP.

## StoneyUI: defer concrete reuse

A future `StoneyUI` repository may provide cross-product contracts and design
tokens:

- parameter/control metadata and state-update semantics;
- bridge lifecycle and test fixtures;
- colour, typography, spacing, and motion tokens;
- renderer-specific implementations only after a second consumer proves reuse.

Canvas/WebGL/Lightning, DOM/Web Components, and native `juce::Graphics` can
share visual language and data contracts without sharing a forced universal
widget hierarchy. Their rendering and lifecycle models differ too much for a
premature one-size-fits-all component layer.

## Gain-product proof

The planned gain utility is the right first vertical slice. Its coarse binary
gain, continuous fine gain, optional bypass/choice exercise, and decibel-facing
control provide enough parameter variety to validate the package, JUCE shell,
automation, bridge, smoothing boundary, and visual-control ideas without
committing converter-colour DSP or a large UI system.
