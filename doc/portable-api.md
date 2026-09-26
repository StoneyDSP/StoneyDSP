# Portable public API {#portable_api}

## The compatibility promise

StoneyDSP aims to be useful to both C++ applications and consumers that need a
plain C surface. This includes plugin products, tools, embedded programs, and
foreign-language bindings. Portability is therefore an API design concern, not
only a compiler-settings concern.

The library uses its own datum types and macro layer to state language linkage,
inline/constexpr/noexcept capability, calling convention, and symbol
visibility. Preserve those conventions in public declarations instead of
introducing an ad-hoc compiler-specific spelling.

## C and C++ boundaries

| Surface | Suitable contents |
| --- | --- |
| C | scalar datum types, deterministic value conversions, explicit buffers and lengths, opaque handles when stateful C objects are added. |
| C++ | namespaces, templates, typed coefficient structures, owned processor state, member processing methods, precision aliases. |

C-facing headers must compile as C and must not accidentally require C++
constructs. C++ enhancements should be placed behind `#ifdef __cplusplus` when
they share a header with C declarations.

## Visibility: opt in, then prove it

`STONEYDSP_API` and `STONEYDSP_PUBLIC_FUNCTION` form part of the public ABI
contract. Export only the declarations intended for a consumer. This keeps a
closed-source product or shared library from accidentally exposing internal
implementation merely because a class was given a broad export annotation.

For C++ processors, prefer member-level public annotations where that is the
chosen API model. Do not annotate both a class and its members when that causes
compiler-specific duplicate/ignored visibility diagnostics. The correct repair
for a target-specific visibility issue is narrowly scoped: preserve the macro
meaning and the deliberately public members, then remove only the conflicting
annotation at the affected declaration kind.

An omitted public annotation should surface as a consumer link failure. That is
preferable to exporting every future implementation detail by default.

## Realtime state ownership

Stateful C++ DSP processing belongs to an object that owns its delay/history,
parameters, reset behaviour, and processing order. For example, a biquad
processor exposes `processSample()` and `processBlock()` as members rather than
requiring callers to coordinate unowned state through a generic free function.

Free functions remain appropriate for pure conversions, coefficient design,
and C-facing helpers. Realtime processing must not allocate, lock, perform I/O,
or depend on a UI/browser lifecycle.

## Validation requirements

For any public API change, distinguish these separate checks:

1. header compilation in its intended language mode;
2. library compilation with the correct export definitions;
3. installed/exported CMake target resolution;
4. external consumer compilation and linking;
5. executable runtime behaviour;
6. shared-library exported-symbol inspection where relevant.

Use representative GCC/Clang and MSVC checks when the change touches
visibility, calling convention, C linkage, variadic macros, or standard-library
compatibility. Do not generalise a workaround across unrelated declarations
until the failing compiler behaviour and the intended public surface are both
understood.

## ABI discipline

Treat changes to public declarations, layout, exported symbols, calling
conventions, and package target names as compatibility work. Pair them with a
version decision and consumer evidence. Endianness, alignment, integer widths,
and floating-point assumptions should be explicit when a future C API moves
structured audio/state data across a binary boundary.
