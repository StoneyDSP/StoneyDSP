# Project workflow {#project_workflow}

This document describes the normal public workflow for StoneyDSP library and
consumer development. It is intentionally practical: the issue, project-board,
branch, and pull-request conventions should make the next piece of work easy
to find, review, validate, and integrate.

## Source of truth

`production` is the stable integration and release branch. The organization
GitHub Project is the public coordination board. GitHub Issues describe
actionable work, and pull requests carry the implementation and validation.

The local `.agents/project-context.md` file records durable, public-safe
architecture and boundary decisions. Detailed execution notes live in the
ignored `.agents/current-work/` directory and are private handoff state.

Public documentation, issues, and project-board entries must be deliberately
sanitised. Do not publish unreleased product strategy, commercial positioning,
pricing, customer information, or differentiating implementation details merely
because an item is being tracked locally.

## Issue and ticket lifecycle

Create an issue when work has a clear outcome that can be independently
reviewed. A useful issue contains:

- a concise problem or outcome statement;
- scope and explicit non-goals;
- acceptance criteria;
- dependencies or prerequisites;
- the intended repository and workstream;
- relevant validation evidence or reproduction steps.

Prefer several small issues over a broad historical `WIP` issue. Use labels for
cross-cutting classification such as `bug`, `feature`, `CI/CD`, `dependencies`,
`documentation`, or `tests`. Use the organization project for sequencing and
status, not as a substitute for an issue description.

Completed or obsolete historical issues should be closed, not deleted. Add a
short explanation when closing an item as superseded, and carry any still-useful
context into a new focused issue.

## Organization project board

The organization project is the portfolio across StoneyDSP and its future
consumer repositories. Keep the board intentionally small and current:

- `Blocked`: work waiting on a dependency or decision;
- `Ready`: scoped work that can be started;
- `In Progress`: actively being implemented;
- `Review`: a pull request is open and awaiting review or required checks;
- `Test`: implementation is merged or staged for focused validation;
- `Done`: acceptance criteria are satisfied.

Use repository-filtered views when the organization project contains multiple
repositories. Do not duplicate an issue merely to make a repository-specific
board: filter the shared project by its `Repository` field instead.

Product implementation belongs in its product repository. The shared board may
contain a public, high-level product-consumer issue, while detailed product
strategy remains private in that repository.

## Branch and pull-request workflow

Start every new change from the current `production` tip:

```sh
git switch production
git pull --ff-only origin production
git switch -c feature/<short-slug>
```

Use `fix/<short-slug>` for defects and `feature/<short-slug>` for new
capabilities. Keep a branch focused on one issue or one tightly coupled change.

Open one pull request targeting `production`. Link the issue, state the affected
public/package surface, record validation commands and results, and identify any
downstream consumer impact. Keep library implementation, build/package changes,
documentation, and unrelated cleanup separable where practical.

The normal integration loop is:

```text
issue → branch → focused implementation → validation → pull request
      → review and required CI → merge to production → delete branch
```

Do not rewrite shared history or force-push without explicit authorization.
Rebase a personal feature branch when it materially simplifies review, but do
not revive the former multi-branch merge-stream workflow.

## Validation expectations

Validation should match the change:

- source and DSP changes: focused unit tests plus relevant CMake/CTest paths;
- package/export changes: install/export checks and the external consumer;
- CI changes: a deliberate workflow run and inspection of each affected job;
- public API changes: C and C++ consumer compilation where applicable;
- product consumers: real plugin/standalone, host, state, automation, and UI
  bridge evidence as appropriate.

Report what actually ran. Distinguish static inspection, configuration,
compilation, tests, packaging, and runtime/listening evidence. A transient
runner or dependency-download failure should be tracked separately from a code
failure when the logs support that distinction.

## Stale branches and pull requests

Historical branches are retained as evidence until their unique work has been
audited. Once a branch is superseded:

1. close its obsolete pull requests with a short supersession comment;
2. confirm no unique accepted work remains;
3. delete the remote branch;
4. retain backups or generated deployment branches where they still serve a
   purpose.

Closing a pull request or deleting a branch does not delete its discussion or
   commit history. New work should be reintroduced through a focused issue and
   a fresh branch from `production`.

## Private handoff notes

Use `.agents/current-work/` for detailed, branch-local execution state,
compaction resume points, candid investigation notes, and implementation
checklists. These files are ignored and should not be committed by default.

When a private note produces a generally useful decision or workflow lesson,
publish an edited, public-safe version in `doc/`, the project issue, or the
release notes. Do not copy private product strategy verbatim into the public
repository.
