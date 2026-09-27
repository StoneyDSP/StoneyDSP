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

## Release artefact workflow

`.github/workflows/release-artifacts.yml` is the manual release-delivery path.
It coordinates selection, immutable release identity, the aggregate matrix,
and promotion. `.github/workflows/release-build-target.yml` is the reusable
per-target implementation and keeps configure, build, test, install, consumer,
package, and upload failures visible as separate Actions steps.

The permanent workflow is deliberately separate from ordinary push and
pull-request validation, so large SDK archives are produced only when a
maintainer requests them. PR #214 temporarily enables a path-scoped
`pull_request` trigger solely to prove all six new target rows before merge;
that trigger must be removed immediately after the evidence is captured.

The dispatch inputs are:

- `release_ref`: the tag, full commit, or branch to resolve and build;
- `targets`: a comma-separated subset of the fixed target IDs below;
- `promote`: an explicit opt-in to attach the resulting files to a release;
- `release_tag`: the existing `vMAJOR.MINOR.PATCH` GitHub Release used only
  when promotion is enabled.

The plan job resolves `release_ref` once. Every matrix row checks out that exact
commit, so a moving branch cannot cause mixed-source archives. Promotion also
requires `release_tag` to match the tracked `VERSION`, to resolve to that same
commit, and to already have a GitHub Release.

### Initial published targets and names

| Target ID | Runner/toolchain | Archive |
| --- | --- | --- |
| `linux-x64` | Ubuntu x64, GCC | `StoneyDSP-<version>-linux-x86_64-gcc-static.tar.gz` |
| `linux-arm64` | Ubuntu ARM64, GCC | `StoneyDSP-<version>-linux-arm64-gcc-static.tar.gz` |
| `macos-x64` | macOS Intel, Apple Clang | `StoneyDSP-<version>-macos-x86_64-clang-static.tar.gz` |
| `macos-arm64` | macOS ARM64, Apple Clang | `StoneyDSP-<version>-macos-arm64-clang-static.tar.gz` |
| `windows-msvc-x64` | Windows x64, MSVC `/MD` | `StoneyDSP-<version>-windows-x64-msvc-md-static.zip` |
| `windows-mingw-x64` | Windows x64, MinGW | `StoneyDSP-<version>-windows-x64-mingw-static.zip` |

This published matrix is intentionally smaller than the compatibility matrix.
x86, shared-library, extra compiler, and uncontracted cross-compiled targets
remain validation candidates rather than promised binary distributions. In
particular, embedded, IoT, Android, iOS, WebAssembly, and generic ARM binaries
need an explicit ABI/toolchain profile before publication.

The macOS ARM64 row explicitly targets macOS 11.0, the first ARM64-capable
macOS release, instead of inheriting the older Intel-only 10.9 preset floor.

Each Actions artefact has the same version/platform/compiler/architecture
identity as its archive and contains the archive plus its adjacent
`.sha256` file. Run artefacts are retained for 14 days. GitHub's tag pages
already provide source ZIP and tar archives; this workflow does not duplicate
them until a curated source bundle has additional defined content.

### Archive contract

Every archive expands beneath one top-level directory named after the archive
and contains:

- public headers under `include/`;
- the static libraries under the platform's installed library directory;
- CMake package configuration and exported targets;
- any package metadata produced by the canonical CMake install path;
- `LICENSE`, `VERSION`, and `StoneyDSP-build-manifest.json`.

The manifest records the version, commit, operating system, architecture,
compiler identity, linkage, CMake preset, and source-date epoch. The packaging
script sorts entries, normalizes permissions and timestamps to the selected
commit time, asks CMake's archive implementation to record that time, and
normalizes the outer gzip header that CMake otherwise timestamps at packaging
time. Run `make release-artifact-test` to check stable archive bytes, required
contents, and the release-asset conflict policy.

The matrix runs the behavioral unit suite (excluding benchmark-labelled cases)
and then configures, builds, runs, installs, and tests the external C and C++
fixture against both static and shared packages. Only the static install tree
is archived in this first published matrix; the shared pass remains a release
gate for export/import and runtime-loading coverage. A failed row does not
cancel evidence from other rows, but the promotion job depends on the
successful aggregate matrix result and therefore cannot run after any failure.
Each row sets `VCPKG_ROOT` to the pinned `dep/vcpkg` submodule and bootstraps
that checkout before configuration. Hosted-runner vcpkg installations are not
used as an implicit substitute for the repository's selected revision.

### Promotion and reruns

Only the promotion job receives `contents: write`; planning and building keep
`contents: read`. Before enabling promotion, a repository administrator must
create the `github-release` Actions environment under **Settings >
Environments** and configure its required reviewers. Do not rely on the first
workflow run to create it: GitHub creates an otherwise missing environment
without protection rules. The environment is therefore a repository setup
prerequisite and supplies the additional human gate for release publication.

Promotion downloads only the selected archives from the current workflow run,
verifies every `.sha256`, and inspects the existing release before uploading.
If an asset name is absent it is uploaded. If the name already exists with
identical bytes it is skipped. If the name exists with different bytes, the
whole promotion is rejected before any missing assets are uploaded. Unrelated
release assets are never deleted or overwritten. This makes a same-ref rerun
safe while keeping changed same-name output visible as a conflict requiring a
new version or explicit manual resolution.

### Storage and runner cost

The six default rows use standard GitHub-hosted runners. Standard runners are
free for this public repository, while larger runners would be billed and are
not used here. macOS and multi-platform builds still consume finite shared
capacity and wall-clock time. Each row validates both static and shared
linkage, so this workflow remains manual and supports a target subset for
focused rebuilds.

Actions artefact storage accrues while archives are retained and shares the
account's artifact/package allowance. The explicit 14-day retention limits
that cost; promoted GitHub Release assets remain until the release owner
removes them. vcpkg dependency caches are separate from deliverable artefacts,
are keyed per target and dependency inputs, and are non-fatal performance
optimizations. Review GitHub's current billing and repository retention
settings before substantially increasing archive size, retention, or matrix
breadth.
