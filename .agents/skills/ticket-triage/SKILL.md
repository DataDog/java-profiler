---
name: ticket-triage
description: Triage an existing java-profiler PROF Jira ticket against the current code, then classify it, propose a reproducer and recommend a priority. Use when asked to triage, assess or re-check a ticket, or to say whether the problem a ticket reports still applies.
---

# Ticket triage

Triage the report against the repository as it is now. Treat every statement in the
report about behavior as an unverified claim.

1. **Read.** Read the full ticket, its comments and linked tickets. Then read the
   current production control flow, data flow, configuration and tests that the report
   concerns.

2. **Dedupe.** Search the PROF project for tickets on the same problem, with the terms
   from the title and the symptoms. Name each match with its status.

3. **Classify.** Decide whether the report still applies to the current code and runtime
   behavior: `confirmed`, `partially applicable`, `stale` or `uncertain`. Cite the source
   paths and symbols behind the decision. Keep observed facts, inferences and open
   questions apart. Without a reproducer run, say that the classification comes from
   reading the code only, and lower your stated confidence in step 6 to match.

4. **Reproducer.** Propose the smallest reproducer that proves or disproves the report:
   prerequisites, exact steps, expected and actual results. The `verify-profiler-change`
   skill names the builds and tests for the code concerned. Ask the user before you edit
   a file or run a build or the reproducer. If the user approves, run it in a throwaway
   worktree, record the exact commands and results, and remove the worktree afterwards,
   unless the user wants to keep it.

5. **Summary.** Name the likely affected code, its constraints, dependencies and risks,
   and the next steps. Do not implement a fix or commit without the user's separate
   approval.

6. **Priority.** Rate impact, likelihood and workaround, each with its reason from the
   evidence. State your confidence and the remaining unknowns, then recommend a Jira
   priority. Do not set the priority field; the user decides.

Post the result on the ticket only when the user asks. The comment follows the
`ticket-writing` skill. Its evidence table holds the reproducer with its commands and
results, or as `blocked` if it did not run.
