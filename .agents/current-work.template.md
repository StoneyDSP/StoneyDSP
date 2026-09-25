# Current Work Notes

Use this file after a fresh agent session or context compaction to recover the
near-term project direction. `AGENTS.md` remains canonical for repository rules;
`.agents/project-context.md` remains the durable project map. This file is for
local branch state, review planning, non-goals, and resume notes.

Use `make agent-current-work` to create the ignored
`.agents/current-work/00-index.md`, or
`make agent-current-work current_work_slug=<slug>` to create one detailed note.
The index is a concise map; this template supplies the detailed note shape.

## Current Direction

- Describe the active branch or investigation.
- Note the reference projects, tickets, or merge requests that define the
  intended shape.
- Capture any decisions that are settled enough to guide local work but not
  durable enough for `AGENTS.md` or `.agents/project-context.md`.

## Near-Term Priorities

- Keep this list ordered by what should be done next.
- Prefer small reviewable chunks and call out known interdependencies.
- Include validation commands that are expected for the active work.

## Planned Branch Chunks

1. Current:
2. Next:
3. Later:

## Non-Goals

- List work that should stay out of the current branch.
- Record formatting, dependency, or refactor churn that should be isolated.

## Knowledge Notes

- Capture field-test findings that should later move into docs, skills, or
  README updates.
- Record whether each note is verified, branch-specific, or still speculative.

## Resume Checklist

1. Read `AGENTS.md`.
2. Read `.agents/project-context.md`.
3. Read `.agents/current-work/00-index.md` when it exists.
4. Read only the detailed notes matching the active work.
5. Check `git status --short --branch`.
6. Load the relevant repo-local skill completely before acting.
7. Use focused commands while iterating, then run the relevant CMake/CTest
   validation, documentation checks, and `make skills-lock-check` when those
   surfaces changed before handoff.
