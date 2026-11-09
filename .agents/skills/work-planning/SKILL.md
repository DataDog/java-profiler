---
name: work-planning
description: Conventions for the Design, acceptance criteria and Build plan of a java-profiler ticket. Use before writing or revising a design, acceptance criteria or a Build plan, on a ticket or in a PR.
---

# Work planning

The phases and their exit criteria are in `doc/WorkTracking.md`. This skill covers how
to write the two planning artifacts. Keep each in one declared source of truth: the
design in the ticket description or a draft PR, the Build plan in the ticket
description or a versioned `plan.md` linked from the ticket. The ticket description
is the default (see the `ticket-writing` skill). The engineer accepts each artifact
before the next phase starts.

## Effort

- Effort is proportional to size. An S change gets a few lines of design; an L change
  gets alternatives and trade-offs.
- Keep both artifacts as short as reasonable. They are review surface, not
  documentation.

## Design

- **Approach.** State the chosen approach and the rejected alternatives, each with the
  reason. Name the constraints that shaped it.
- **Decisions.** List every decision the engineer must make separately, with the
  options and a recommendation. Do not bury a decision in the prose.
- **Environments.** List every environment the change must work in: the CI image, a
  clean checkout versus a working copy, local tool versions, and each supported agent
  harness. An environment the design does not name is where findings come from.
- **Critical areas.** Name each critical area from `doc/WorkTracking.md` the change
  touches, and signal-handler code (the AGENTS.md Critical Invariants), with the review
  each needs.
- **Rollout and recovery.** State how the change reaches users, and how to stop or
  revert it if a production check fails.

## Acceptance criteria

- Write them before code. Each criterion is observable and is tagged with where it is
  verified:
  - `local`: a hermetic test or a local run;
  - `test-drive`: a fresh agent session or a real run on the candidate;
  - `production-check`: observed after merge or release, with the signal and the
    observation window it needs.
- Say which criteria are permanent tests, committed with the code, and which are
  one-time evidence recorded on the ticket.

## Build plan

- Map each acceptance criterion to the check that proves it, usually as a table:
  PR | scope | criteria. Say which PRs are independent and which are stacked.
- Name only what the design leaves open, and any check whose method is not obvious
  (how to run it, what to compare against).
- Do not restate the intent or the design, and do not write a step-by-step blueprint
  of the implementation: that detail belongs in the PRs.
- When reality diverges, amend the plan in its source of truth and get the change
  accepted.
