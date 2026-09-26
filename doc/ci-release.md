# CI and release validation {#ci_release}

## CI is evidence, not the support policy by itself

StoneyDSP uses CI to catch package, compiler, and public-API regressions across
representative environments. The matrix is intentionally selected rather than
maximal: every routine row spends finite GitHub Actions capacity.

Current routine validation includes macOS, Linux, Windows/MinGW, and
Windows/MSVC x86/x64. Windows x86 is primarily compatibility validation rather
than a primary consumer target. Linux ARM64 has a preset/triplet path but is
kept available for deliberate/manual or release-cut validation rather than
running on every ordinary change.

Manual workflow dispatch should remain able to select broader meaningful job
sets for a release candidate. Do not add confusing global toggle variables when
a clear workflow-dispatch input or explicit release procedure answers the need.

## What CI must distinguish

- configuration failure from compilation failure;
- unit-test failure from package/consumer failure;
- code regression from a transient runner, cache, or dependency-download
  incident;
- static-library behaviour from shared/DLL import/export behaviour;
- compiler-family validation from a separate end-user target claim.

MSVC is valuable precisely because it exercises declaration visibility, DLL
import/export, and C/C++ preprocessor behaviour that may not appear under
Clang/GCC. A target-specific failure should result in a narrow diagnosis and
repair, not a global weakening of the public API.

## vcpkg caching

The CI cache stores vcpkg binary archives and downloads beneath the workspace.
Cache keys must vary with the inputs that can invalidate a package build:

- operating system;
- compiler/toolchain and relevant architecture;
- `vcpkg.json`, `vcpkg-configuration.json`, and local registry inputs;
- any other dependency input deliberately added to the cache contract.

Restore/save failures are non-fatal performance events. Configure, build, test,
and consumer-validation failures remain strict. A cold cache proves that a job
can download/build/save dependencies; it does not by itself prove a later warm
cache restoration.

## Version protocol

`VERSION` is the release source of truth. `make version-check` verifies strict
`MAJOR.MINOR.PATCH` agreement across `VERSION`, the root vcpkg manifest,
`package.json`, and the StoneyDSP port manifest. Use `make version-bump` for an
intentional release change and `make version-sync` only for a reviewed migration
to the tracked version; both preserve the manifest's human-oriented formatting
and key order.

CI runs the check because vcpkg version metadata must remain coherent. A local
hook can offer early feedback but cannot be the only guard.

## Release-cut minimum

Before publishing a package or binary asset:

1. run the intended platform/compiler matrix or explicit release subset;
2. validate the external C/C++ consumer in the relevant static/shared modes;
3. inspect public symbols when ABI visibility changed;
4. verify `make version-check`;
5. record the exact package pin, commit, or tag consumed by downstream work.

Keep release assets and commercial product packaging in their consumer
repositories. This repository owns the reusable library package and its proof.
