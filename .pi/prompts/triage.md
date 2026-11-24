---
description: Start the triage loop — pull the next untriaged PROF ticket, run the ticket-triage skill to completion, then repeat until stopped or no tickets remain
argument-hint: "[PROF-<n>]"
---
Run the ticket-triage loop for the PROF project.

If the arguments name a ticket (`${1:-}`), validate it matches `PROF-<number>`; if it
does not, stop with an error instead of searching. Triage only that ticket and stop
after its completion statement. Otherwise run the loop:

1. **Find the next untriaged ticket.** Search Jira PROF (component `library-java`) for
   tickets whose status is `Committed` and whose comments do not contain the exact
   heading `## Triage evidence` defined by the `ticket-triage` skill. Skip every ticket
   with a comment containing that marker. When no such ticket remains, report that the
   loop is exhausted and stop.
2. **Triage it.** Run the `ticket-triage` skill on that ticket through completion,
   including its step-7 Done statement. The loop never overrides the skill's gates:
   ask-first on every edit/build/run, the ILW wizard, and no priority-field writes.
3. **Check in.** After the completion statement, report one line —
   `Triage complete: PROF-<n> — <classification>, P<priority>` (for a `stale`
   classification, the close recommendation instead of a priority) — and ask whether
   to post the result comment on the ticket (producing its `## Triage evidence`
   marker, which keeps the loop from re-triaging it) and whether to continue to the
   next ticket. Continue only on an explicit yes; any other reply
   (stop, a new instruction, or silence) ends the loop.
4. Repeat from step 1.

The user can stop the loop at any point by saying stop. Never triage more than one
ticket per round without asking.
