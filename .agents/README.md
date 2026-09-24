# Agent Entry Points

`AGENTS.md` at the repository root is the canonical contributor and agent
guide. Read it first, then read `.agents/project-context.md` when reacquiring
the project after a context reset or before repository-wide workflow changes.

Repo-local skills live under `.agents/skills/` and are indexed by the generated
root file `skills-lock.json`. Read the relevant `SKILL.md` completely before
working in that area. Run `make skills-lock` after changing a skill and
`make skills-lock-check` during validation.

`.agents/current-work/` is ignored, branch-specific handoff state. Read
`00-index.md` first, then only notes matching the active task. Use
`.agents/current-work.index-template.md` and `.agents/current-work.template.md`
through `make agent-current-work` when a task needs durable near-term direction,
non-goals, validation notes, or a compaction resume point. Do not treat these
notes as canonical project policy.

## Documentation entry points

- `README.md`: public project overview and quickstart.
- `doc/README.md`: documentation map and generation workflow.
- `doc/Doxyfile`: Doxygen source/configuration of generated API documentation.
- `doc/core.md`, `doc/simd.md`, `doc/dsp.md`, and `doc/test.md`: component and
  validation documentation.
- `doc/presets.md`: CMake preset and workflow documentation.
- `.agents/project-context.md`: durable architectural and product context.

Source headers, CMake files, tests, and current CI are authoritative when
generated documentation or agent notes disagree with implementation.
