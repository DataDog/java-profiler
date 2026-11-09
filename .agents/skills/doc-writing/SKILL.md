---
name: doc-writing
description: Rules for java-profiler documentation under doc/ (naming, index, accuracy, stale sections). Use before creating, editing, renaming or deleting a file under doc/.
---

# Documentation writing

- **Naming.** Files in `doc/` use PascalCase (e.g. `BuildSystemGuide.md`);
  `doc/README.md` is the only lowercase exception. New subsystem docs go in
  `doc/architecture/` or `doc/reference/`; build docs in `doc/building/`.
- **Index.** Every doc page is indexed in `doc/README.md`. CI (`qualityChecks`)
  enforces naming and indexing; design artifacts under `docs/sphinx/`, `.sphinx/` and
  similar scratch paths must never be tracked.
- **Current state only.** Documentation never carries transient or historical notes,
  and never claims what is not true of the code. Verify numbers before writing them
  down.
- **Remove finished work.** Preserved historical sections of landed design or handover
  docs ("Suggested next steps", unverified hypotheses, open items) are rewritten or
  deleted once the work they instruct is done: never point a reader at finished work.
- **Link, do not copy.** Link to deeper sources instead of copying large documents.
- The AGENTS.md **Comment budget** and **Comments** rules apply to doc paragraphs too:
  no references to plans, phases, review reports or tickets.
- When a page changes a subsystem contract, update its row in the AGENTS.md subsystem
  index in the same change.
