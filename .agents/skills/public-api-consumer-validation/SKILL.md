---
name: public-api-consumer-validation
description: Validate a portable C/C++ library as an external consumer across package targets, static/shared linkage, and representative toolchains. Use when adding or reviewing consumer smoke tests, install/export checks, ABI visibility coverage, or C compatibility validation in StoneyDSP.
---

# Public API Consumer Validation

Prove the package contract from the consumer boundary. A library build alone
does not prove that installed headers, exported targets, link mode, ABI
annotations, and C/C++ compatibility agree.

## Preserve the boundary

- Build consumers in a separate CMake project under a disposable build tree.
- Consume the installed or exported package with `find_package`; do not add
  source-tree include paths as a substitute for package consumption.
- Keep product, JUCE, host, and UI code out of this fixture.
- Treat C and C++ consumers as separate compatibility surfaces.

## Minimum fixture shape

Exercise, where the components exist:

- a C consumer linked through the Core target;
- a C++ consumer linked through the highest-level component target;
- a C++ consumer linked through the aggregate target;
- deterministic executable or CTest assertions, not compile-only targets.

Use the smallest public calls that prove the intended surface. Include at
least one representative type conversion or C helper, and one compiled DSP
operation when the DSP component is in scope.

## Linkage matrix

Run the same fixture against both static and shared installations. For each
mode verify:

- configure resolves the intended package and components;
- compilation sees the consumer-facing definitions;
- linking succeeds without source-tree objects or private target names;
- executables run with the expected static archive or shared runtime;
- the static build does not request DLL imports;
- the shared build exports only the declarations intentionally marked public.

Do not “fix” a linkage failure by removing public export annotations globally.
First identify whether the mismatch is target type, compile-definition
propagation, an uninstantiated template, an unavailable symbol, or an ABI
calling-convention issue.

## C compatibility checks

Compile the C consumer with the project’s supported C standard and each
representative compiler. When a standard header is unavailable on a target,
determine whether the library actually uses it before changing the include;
preserve the intended C API rather than adding platform-specific shims
without evidence.

Keep C headers free of accidental C++ namespace, template, allocation, or
JUCE dependencies. Use the project’s C-linkage and public-function macros when
the tested declaration is an exported function.

## Evidence to record

Record the package source (build-tree export, install tree, or vcpkg), linkage
mode, compiler/architecture, exact configure/build/test commands, and whether
runtime loading was exercised. Distinguish a local result from CI coverage.

When symbol visibility is part of the task, inspect the produced archive or
shared object with the platform’s symbol tool and pair that evidence with a
real consumer link. Symbol listing alone is not a consumer test.

## Stopping boundary

Begin with one CMake consumer fixture and the narrowest static/shared matrix.
Add platform rows or C API breadth only when the preceding result is green and
the additional row answers a concrete portability question. Do not turn a
smoke-test change into a package-manager, product, or ABI redesign.
