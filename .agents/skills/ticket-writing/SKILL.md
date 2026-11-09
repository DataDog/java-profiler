---
name: ticket-writing
description: Conventions for java-profiler Jira tickets in the PROF project, covering how to create a ticket or sub-task, write its Intent, record decisions and evidence, and move its status. Use before creating or editing a Jira ticket or posting a ticket comment, and whenever work on a ticket starts, a PR opens or merges, or its evidence is complete.
---

# Ticket writing

The ticket is the system of record: anyone must be able to pick the work up from it
without the conversation. The phases are in `doc/WorkTracking.md`; this skill covers how
the ticket carries them. External contributors use GitHub issues with the same
structure; the Jira-only rules below (component, assignee, status) do not apply there.

The `pr-writing` skill's style rules apply to every ticket text and comment.

## Creating a ticket

- **Shape.** A parent Task carries the problem and the direction only. Each step is a
  Sub-task that carries its own Intent, Design, acceptance criteria and Build plan.
  Epics are for program-level work, not for one change.
- **Component.** `library-java` for java-profiler work; `openjdk` for upstream OpenJDK
  work.
- **Assignee.** Always set it explicitly. Without one, Jira assigns the component
  default, which is another engineer.
- **Status.** A new ticket starts in Committed. Check the status after creating it.
- **Dedupe first.** Search for an existing ticket on the same problem, and link related
  tickets instead of restating them.

## The description

- **Header line.** Phase, size (S/M/L) with one sentence on why, parent, and the
  pattern or previous step it follows.
- **Intent.** What and why, scoped to this ticket, with the owner and the observable
  outcome. Never the how.
- **Out of scope.** Name what this ticket deliberately leaves out, and where it goes.
- **Findings.** Facts from the investigation that shape the scope, each checkable
  against the code.
- **Decisions.** Each decision the engineer must make is listed separately and, once
  made, recorded with who made it and the date.
- Design, acceptance criteria and the Build plan follow the `work-planning` skill.
- Keep the description current: it holds the latest accepted state. History goes in
  comments.

## Comments

- **Sign-off.** When the engineer accepts the intent, a design or a plan, post a comment
  that names who accepted what, and the date.
- **Evidence.** Report every check in a table: criterion, state, observed result. Name
  what produced it: the candidate commit and the configuration (build type, platform,
  harness and version); for a production check, the deployed revision, environment and
  observation window. Put the interpretation in its own paragraph, after the table.
- **After the candidate changes,** re-run each check on the new candidate before you
  report it as passed. Results from an earlier commit are reported as such.
- **Links, not bare names.** Every commit, PR and branch is a link. A link to an
  unpushed commit does not resolve, so push first, or add the links after the push.
- **No line numbers.** Refer to files and symbols; line numbers go stale.

## Status follows the work

| Status | When |
| --- | --- |
| Committed | Intent recorded; no work started |
| In Progress | From the start of Design through Build and Test |
| In Review | Every planned PR is open and review is requested, after the pre-PR review gate |
| Blocked | A dependency outside the assignee's control, such as another team or an external decision, stops all work |
| Done | Every acceptance criterion has recorded evidence, including the `production-check` criteria |

- Move the status in the same session as the event that causes it, and say so in the
  comment.
- While a planned PR is still to be written, the ticket stays In Progress, even if
  earlier PRs, such as the first of a stack, are already in review.
- Waiting for the engineer's sign-off on a design or a decision is not Blocked.
- A blocked part, with other parts still moving, is recorded in a comment; the status
  does not change.
- A parent Task is In Progress while any of its sub-tasks is, and Done when all of
  them are Done.
- A merged PR with production checks still pending stays In Review. Its comment lists
  the pending checks. Merging alone is never Done.
- Before Done, post a closing comment that maps every criterion to its evidence.
