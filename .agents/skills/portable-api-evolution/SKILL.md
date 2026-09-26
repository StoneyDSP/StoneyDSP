---
name: portable-api-evolution
description: Change or review StoneyDSP C/C++ public declarations, visibility macros, ABI-sensitive types, or realtime processor ownership across GCC, Clang, MinGW, and MSVC. Use when compiler/linker failures involve exports, C linkage, variadic macros, templates, or installed consumer behaviour.
---

# Portable API Evolution

Treat a public declaration as a contract across language modes, link modes, and
toolchains. A green local build does not establish a portable ABI.

## Diagnose narrowly

First identify whether the failure is caused by declaration visibility,
class/member annotation overlap, target compile definitions, C/C++ language
mode, template instantiation, calling convention, or consumer linkage. Preserve
the meaning of `STONEYDSP_API`, `STONEYDSP_PUBLIC_FUNCTION`,
`STONEYDSP_EXPORTS`, `STONEYDSP_STATIC`, and the language capability macros.

Do not solve one compiler's error by globally removing export annotations or
turning a deliberately opt-in API into a broad class-level export. Remove or
adjust only the conflicting annotation after confirming every intentionally
public member remains declared public.

## C and C++ shape

- C headers remain free of namespaces, templates, C++ allocation, and JUCE.
- C++ stateful processors own their state and expose member processing methods.
- Use StoneyDSP datum types and macro conventions at the public boundary.
- Be explicit about `float` versus `double` aliases and precision support.

## Required proof

Pair source/build validation with an external installed/exported consumer. Test
both static and shared linkage where relevant, including runtime execution.
When visibility changes, inspect symbols and pair that with an actual import
link. Use MSVC x86/x64 as first-class validation, not an afterthought.

Load `public-api-consumer-validation` for the concrete fixture matrix and read
`doc/portable-api.md` for the durable rationale.
