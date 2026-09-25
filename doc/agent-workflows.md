# Agent Workflows

`AGENTS.md` is the canonical repository guide. This page explains the durable
supporting routines that help an agent recover context, choose skills, keep
documentation synchronized, and leave a reviewable worktree.

## Re-discover context

After a fresh session or context compaction:

1. Read `AGENTS.md`.
2. Read `.agents/project-context.md`.
3. Read `.agents/current-work/00-index.md` when it exists.
4. Read only the detailed notes that match the active task.
5. Check `git status --short --branch`.
6. Load the relevant `.agents/skills/*/SKILL.md` completely before acting.
7. Inspect source, tests, CMake, and current CI for the task rather than
   relying on stale notes.

`.agents/project-context.md` is durable, public-safe architecture and decision
context. `.agents/current-work/00-index.md` is the concise private coordination
map; matching slugged notes contain detailed branch-specific direction and
resume state. The entire directory is ignored. Publish only deliberately
sanitised summaries in `doc/`, issues, or release notes. Live source and
explicit user direction outrank both when they differ.

```sh
make agent-current-work
make agent-current-work current_work_slug=<slug>
make agent-current-work-list
```

## Skills

Repo-local skills are portable Markdown instructions under `.agents/skills/`.
The generated `skills-lock.json` records each skill's name, description, path,
and content hash.

```sh
make skills-lock
make skills-lock-check
```

When a skill changes, regenerate the lock and include the lock update in the
same reviewable change. Do not copy skill instructions into vendor-specific
agent files; keep `CLAUDE.md`, `GEMINI.md`, and similar files as thin pointers
to `AGENTS.md` and the skill index.

## Documentation generation

Human-maintained documentation lives in `doc/`, the public README, public
headers, CMake files, and agent context. Doxygen consumes the configured input
set and generated headers and writes disposable output to `build/doc/html/`.

```sh
make doc
```

When source headers, component behavior, presets, package exports, or test
commands change, update the nearest durable documentation in the same change.
Do not treat generated HTML as a source of truth.

## Validation rhythm

Use the narrowest focused compile/test command while iterating. Before
handoff, run the relevant CMake/CTest preset validation and documentation or
skill-lock checks when those sources changed. Report exactly what ran and
distinguish static inspection, configuration, compilation, tests, packaging,
and generated-document checks.

The canonical project build is CMake/presets. Make provides convenience and
some legacy/manual paths; do not silently treat independent Make recipes as
equivalent to CMake package validation.

## Worktree hygiene

- Inspect `git status --short --branch` before edits.
- Preserve unrelated user changes.
- Keep temporary output under ignored `build/`, `dist/`, `out/`, `.cache/`, or
  another narrowly scoped disposable directory.
- Keep current-work notes ignored and never put credentials, tokens, private
  certificates, or machine-specific absolute paths into tracked files.
- Keep library, package/build-system, documentation, and product changes
  separable where practical.
- Do not reset, rebase, force-push, or remove material without explicit
  authorization.

## Versioning

`VERSION` is the tracked release-version source consumed by CMake and the vcpkg
port. Normal configure/build operations leave it untouched. Git-derived build
identity is generated in memory only when explicitly requesting
`STONEYDSP_GENERATE_VERSIONS=ON`. Use the checked-in script instead of editing
`VERSION` or the vcpkg manifest by hand:

```sh
make version-check
make version-sync
make version-bump VERSION_INCREMENT=patch
```

The checker requires strict `MAJOR.MINOR.PATCH` semver and verifies that
`VERSION`, the root vcpkg manifest, `package.json`, and the port manifest
agree. `version-sync` is an explicit migration command for bringing those
manifests up to the tracked `VERSION`; it preserves their existing formatting
and key order. A bump updates all release sources together. CI should run
`make version-check`. A local pre-push hook may call the same check, but
correctness must not depend on untracked hooks.
