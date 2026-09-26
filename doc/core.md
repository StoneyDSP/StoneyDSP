# Core component

`StoneyDSP::Core` is the portable base layer for the rest of the library. It
contains the platform/compiler/language abstraction, datum types, C-compatible
helpers, and shared numerical utilities used by DSP code.

## Responsibilities

- fixed-width and native-size datum aliases under `stoneydsp::core::types`;
- capability and portability macros for C/C++ language modes, compiler
  features, linkage, visibility, and platform detection;
- C-facing scalar helpers intended to compile without a C++ ABI;
- C++ maths constants and stateless conversions used by processors and
  coefficient design.

Core must not acquire JUCE, plugin-host, renderer, browser, or product-state
dependencies. Its job is to give higher components a dependable portable base.

## Maths

The `stoneydsp::core::maths` namespace currently provides:

- `Constants<T>` for named fractional, transcendental, square-root, reciprocal,
  and logarithmic values;
- `Functions<T>` for small stateless numerical helpers;
- C and C++ conversion helpers for amplitude decibels, linear gain, and binary
  amplitude coordinates.

The shared amplitude convention is:

```text
gain = 10^(dB / 20)
gain = 2^bits
```

Therefore one binary-amplitude bit is approximately `6.0206 dB`. Use a named
constant when the value is a mathematical part of the algorithm—such as
`Constants<T>::twoPi` or `oneDivSqrtTwo`—rather than making every ordinary
scalar literal a library abstraction.

## C and C++ surface

C headers use StoneyDSP datum types and public-function/linkage macros. C++
headers may provide templates and namespaces behind `#ifdef __cplusplus`. Keep
those two surfaces compatible but intentional: a C consumer must never acquire
a hidden requirement for templates, namespaces, JUCE, or C++ object lifetime.

Any change to the Core public surface should be validated by an external C and
C++ consumer, not only by a library build.
