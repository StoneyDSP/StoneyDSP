# Testing and validation

StoneyDSP validation is layered. A passing unit test is valuable but does not
prove package exports, ABI visibility, a plugin host, or listening behaviour.

## Layers

| Layer | What it establishes |
| --- | --- |
| Focused Catch2 test | Deterministic API/DSP behaviour. |
| CMake configure/build/CTest | The configured target graph and selected toolchain. |
| External consumer | Installed/exported headers, targets, linkage, and runtime loading. |
| CI matrix | Representative platform/compiler regression coverage. |
| Host/listening/measurement | Product interaction, lifecycle, and intended sound. |

Use the narrowest relevant layer while iterating, then run the broader layer
needed to substantiate the handoff claim.

## DSP tests

DSP coverage should test more than nominal output values. Consider:

- static transfer and monotonicity;
- impulse, step, sine, sweep, and noise responses;
- state/reset/phase and block-boundary behaviour;
- sample-rate dependence;
- rails, clipping, NaN/Inf, and denormal handling;
- parameter edge cases and coherent update semantics;
- offline fixtures and listening/measurement evidence for intentional sound
  changes.

## Public package tests

For public-header, C API, visibility, CMake, install, or vcpkg changes, prove
an external CMake consumer. Exercise C and C++ surfaces independently, static
and shared linkage where applicable, and executable runtime behaviour. Pair
symbol inspection with a real import link when DLL/shared-object visibility is
under review.

The `public-api-consumer-validation` skill holds the detailed fixture guidance.
