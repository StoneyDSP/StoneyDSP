# Consumer integration {#consumer_integration}

## Canonical boundary

StoneyDSP is consumed as an installed/exported CMake package. A consumer must
not use source-tree include directories or compile private StoneyDSP sources as
a replacement for package consumption.

```cmake
find_package(StoneyDSP CONFIG REQUIRED COMPONENTS Core DSP)

target_link_libraries(MyConsumer
    PRIVATE
        StoneyDSP::DSP)
```

The package and its exported targets are the contract. A successful library
build alone does not prove installed headers, compile definitions, symbol
visibility, link mode, or runtime loading work for a downstream client.

## vcpkg and tandem development

For active product development, a consumer may provide a local StoneyDSP
checkout through a vcpkg overlay port or registry configuration. This is source
provisioning for a package build, not a reason to bypass the CMake package
boundary.

Release or shareable configurations must identify a pinned package version or
immutable commit. Update that pin deliberately after validating the new library
revision in the consumer.

`StoneyVCV` is useful evidence that this workflow is viable, but it pins an
older StoneyDSP arrangement. Current exported-target and install behaviour must
be validated against the current checkout.

## Consumer validation

When modifying headers, exports, component dependencies, install destinations,
or port metadata, validate from an external CMake project.

Minimum useful coverage is:

1. C consumer through the Core surface.
2. C++ consumer through the relevant component and aggregate target.
3. Static and shared installation modes where supported.
4. Configure, compile, link, and execute—not merely header inclusion.
5. Symbol inspection paired with a real consumer link when visibility matters.

The repository skill `public-api-consumer-validation` contains the detailed
procedure and stopping boundary.

## JUCE products

JUCE product code should normally use ordinary CMake package consumption
alongside JUCE targets:

```cmake
find_package(JUCE CONFIG REQUIRED)
find_package(StoneyDSP CONFIG REQUIRED COMPONENTS Core DSP)

target_link_libraries(MyPlugin
    PRIVATE
        StoneyDSP::DSP
        juce::juce_audio_processors)
```

This is distinct from JUCE's `juce_add_module()` API. That API treats a
directory as a source module: its basename determines the module name, it
expects a matching root header and module metadata, and it recursively collects
sources beneath that directory. StoneyDSP intentionally does not follow that
co-located source-module layout.

Do not reshape `include/stoneydsp/` and `src/stoneydsp/` to imitate a JUCE
module. If a real product later needs `juce_add_module()` compatibility,
provide a separate, thin `StoneyDSP-JUCE` adapter that forwards headers and
links `StoneyDSP::Core`/`StoneyDSP::DSP`. It must never compile a second copy of
StoneyDSP sources beside the package library. See issue #203.

## C API and ABI considerations

The C-facing API is meant to remain portable across C compilers and
foreign-language or embedded clients. It must stay free of templates,
namespaces, JUCE types, C++ allocation requirements, and accidental host
dependencies.

Public C declarations use the project's linkage and visibility macros. Their
behaviour must be proven on the target compiler and linkage mode rather than
assumed from a Unix build. Windows/MSVC failures are particularly useful
evidence because DLL export/import annotation and variadic test-macro behaviour
can differ from Clang/GCC environments.

See [Portable public API](portable-api.md) for declaration and visibility
rules.
