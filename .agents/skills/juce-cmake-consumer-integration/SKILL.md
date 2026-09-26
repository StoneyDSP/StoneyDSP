---
name: juce-cmake-consumer-integration
description: Integrate StoneyDSP into a JUCE CMake product without turning the library into a JUCE dependency or duplicating its implementation. Use when creating or reviewing a JUCE plugin, standalone app, consumer smoke test, or optional JUCE-module adapter.
---

# JUCE CMake Consumer Integration

Treat StoneyDSP as an installed CMake/vcpkg dependency inside the JUCE product.
The canonical path is `find_package(StoneyDSP CONFIG REQUIRED)` plus a private
link to the required exported component target.

## Default integration

Use ordinary CMake package consumption alongside JUCE:

```cmake
find_package(JUCE CONFIG REQUIRED)
find_package(StoneyDSP CONFIG REQUIRED COMPONENTS Core DSP)

target_link_libraries(MyPlugin
    PRIVATE
        StoneyDSP::DSP
        juce::juce_audio_processors)
```

Do not add StoneyDSP source directories to the product's include path or compile
its private sources in the product. The package target owns its compile
definitions, linkage mode, generated version definitions, visibility contract,
and component dependencies.

## JUCE modules are not package targets

`juce_add_module()` expects a source-module directory with a basename-matched
root header, JUCE metadata, and recursively discoverable implementation beneath
that directory. StoneyDSP intentionally has separate `include/stoneydsp` and
`src/stoneydsp` trees and must not be rearranged to fit that model.

If a real product needs module compatibility, create a separate thin adapter:

- it may expose JUCE module metadata and forwarding headers;
- it links StoneyDSP package targets rather than aggregating StoneyDSP sources;
- it must not introduce a JUCE dependency into StoneyDSP;
- it must not result in two compiled copies of StoneyDSP or duplicate symbols.

Do not create the adapter speculatively. First prove ordinary package consumption
in the target product. Refer to issue #203 and `doc/consumer-integration.md`.

## Product boundary

The JUCE product owns `AudioProcessor`, parameter/automation semantics, state,
bus layouts, editor lifecycle, plugin formats, and frontend assets. StoneyDSP
owns portable DSP only. Keep browser/WebBrowser lifecycle and UI rendering out
of the audio engine.

## Validation

Prove at least:

1. CMake configure resolves both JUCE and StoneyDSP from their intended sources.
2. The product compiles and links without StoneyDSP source-tree paths.
3. The executable/plugin loads StoneyDSP through the selected static/shared
   package mode.
4. One real host or standalone run exercises processing and parameter state.

When touching exports or linkage, also load `public-api-consumer-validation`.
