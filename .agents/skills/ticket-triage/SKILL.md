---
name: ticket-triage
description: Triage an existing java-profiler Jira ticket or bug report against the current code, then classify it, propose a reproducer and recommend a priority. Use when asked to triage, assess or re-check a ticket, or to say whether a reported problem still applies.
---

# Ticket triage

Triage the report against the repository as it is now. Treat every statement in the
report about behavior as an unverified claim.

1. **Dedupe.** Search the PROF project for tickets on the same problem, and name each
   match with its status.

2. **Read.** Read the full ticket, its comments and linked tickets. Then read the
   current production control flow, data flow, configuration and tests that the report
   concerns.

3. **Classify.** Decide whether the report still applies to the current code and runtime
   behavior: `confirmed`, `partially applicable`, `stale` or `uncertain`. Cite the source
   paths and symbols behind the decision. Keep observed facts, inferences and open
   questions apart.

4. **Reproducer.** Propose the smallest reproducer that proves or disproves the report:
   prerequisites, exact steps, expected and actual results. The `verify-profiler-change`
   skill names the builds and tests for the code concerned. Ask the user before you edit
   a file or run a build or the reproducer. If the user approves, record the exact
   commands and results, and remove what the run generated unless the user wants to keep
   it.

5. **Summary.** Name the likely affected code, its constraints, dependencies and risks,
   and the next steps. Do not implement a fix or commit without the user's separate
   approval.

6. **Priority.** Rate impact, likelihood and workaround, each with its reason from the
   evidence. State your confidence and the remaining unknowns, then recommend a Jira
   priority. Do not set the priority field; the user decides.

To record the result on the ticket, post it as a comment that follows the
`ticket-writing` skill, with a reproducer run in its evidence table.
