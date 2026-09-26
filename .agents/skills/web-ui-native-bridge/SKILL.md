---
name: web-ui-native-bridge
description: Design and validate a bounded web-like UI to JUCE-native audio bridge while preserving host automation, realtime safety, and editor-independent audio. Use when a StoneyDSP product uses JUCE WebBrowserComponent, TypeScript, Canvas/WebGL, Lightning, DOM, or a future StoneyUI contract.
---

# Web UI Native Bridge

The browser is a presentation and interaction client. The native product layer
remains authoritative for host parameters, saved state, smoothing, reset, and
realtime DSP.

## Preserve authority and thread boundaries

- UI-to-native messages express bounded parameter intent, never direct access
  to audio-thread state.
- Native-to-UI messages provide authoritative snapshots or bounded updates.
- Host automation and preset/project recall must update the UI through the
  native parameter model.
- Browser loading, rendering, editor close/reopen, and JavaScript failures must
  not interrupt audio or invalidate state.
- Do not transport arbitrary audio-rate data into the browser. Design explicit
  telemetry contracts with rate/size bounds.

## First-product scope

Prove one small panel before extracting a general UI framework:

1. a UI gesture changes a native parameter;
2. native/host change reaches the UI;
3. editor recreation and state recall are correct;
4. packaged assets load in a real host;
5. audio remains correct without the browser.

The gain utility is the intended first proof because its stepped coarse gain,
continuous fine gain, and optional bool/choice exercise several parameter shapes
without committing a large UI or DSP architecture.

## StoneyUI extraction rule

Shared contracts and design tokens may be extracted after a second product
proves reuse. Do not force Canvas/WebGL, DOM/Web Components, and
`juce::Graphics` into one concrete widget implementation. Share control/state
semantics and visual tokens first; keep renderer/lifecycle-specific code local.

Read `doc/ui-bridge.md` before setting a bridge protocol or deciding a shared
UI boundary.
