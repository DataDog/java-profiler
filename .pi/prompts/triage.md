---
description: Triage PROF tickets one at a time with the ticket-triage skill — after each completed ticket, confirm before the next, until stopped or no untriaged tickets remain
argument-hint: "[PROF-<n>]"
---
Run the ticket-triage loop for the PROF project.

This file and its twin for the other harness (`.pi/prompts/triage.md` /
`.claude/commands/triage.md`) are kept in sync: change both together.

If the arguments name a ticket (`${1:-}`), validate it matches `PROF-<number>`; if it
does not, stop with an error instead of searching. Triage only that ticket and stop
after its completion statement. Otherwise run the loop:

1. **Find the next untriaged ticket.** Search Jira PROF (component `library-java`) for
   tickets whose status is `Committed` and whose comments carry no triage result
   comment — one whose body has a level-2 heading `Triage evidence` (the marker the
   `ticket-triage` skill defines). Decide by reading the ticket's comments; use JQL
   text search only as a prefilter, never as the decision. Also skip every ticket
   triaged in this session, whether or not its result comment was posted. A ticket
   whose result comment was declined in an earlier session is re-triaged by a later
   run — that is the intended cost of the declined post; the marker is the only
   durable record. When no
   such ticket remains, report that the loop is exhausted and stop.
2. **Triage it.** Run the `ticket-triage` skill on that ticket through completion,
   including its step-7 Done statement. The loop never overrides the skill's gates:
   ask-first on every edit/build/run and workspace create/delete, the ILW wizard, and
   no priority-field writes.
3. **Check in.** After the completion statement, report one line —
   `Triage complete: PROF-<n> — <classification>, P<priority>` (for a `stale`
   classification, the close recommendation instead of a priority) — and ask whether
   to post the result comment on the ticket (producing its `Triage evidence`
   marker, which keeps later loop runs from re-triaging it) and whether to continue to
   the next ticket. Continue only on an explicit yes; any other reply
   (stop, a new instruction, or silence) ends the loop.
4. Repeat from step 1.

The user can stop the loop at any point by saying stop. Never triage more than one
ticket per round without asking.
