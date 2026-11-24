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
   a file, run a build, run the reproducer, or create a workspace; the create
   approval also covers the workspace's cleanup, including the failure-path teardown,
   so deletion needs a separate ask only when the user might want to keep it; do not
   offer skipping the run — a triage
   ends with the reproducer run unless it is genuinely blocked, in which case say what
   blocks it and keep the evidence `blocked`. If the user declines the run, record the
   evidence `blocked` with the reason `user declined`.

   Keep the reproducer code in a separate throwaway worktree, always — even when it runs
   elsewhere. Then check whether the `workspaces` command is on PATH:
   - If it is, create a throwaway Datadog workspace with `workspaces create <name> -y`;
     make `<name>` unique and self-describing, e.g. `triage-<TICKET-KEY>-<4 random
     characters>` such as `triage-PROF-1234-x7k2`, so the machine is traceable to its
     ticket and cannot collide with another run. If `workspaces create` fails, clean up
     any partially created workspace and fall back to the local worktree run, stating
     the reason. From workspace creation onward, every exit path — failed sync, failed
     verification, failed run — deletes the workspace with `workspaces delete <name>
     --yes` before falling back or ending; a failed run is never a reason to leave the
     machine allocated. A failed sync or apply falls back to the local worktree run
     under the same architecture rule, with the failure stated. Verify with
     `ssh workspace-<name> 'uname -sm'` that its architecture actually matches the bug
     (aarch64 vs x86_64; for a libc-specific report also match the libc via
     `ldd --version`, glibc vs musl). If it does not match, do not run the reproducer
     there: delete
     the workspace with `workspaces delete <name> --yes`. Create a compatible
     replacement if available, verify its architecture again, and use it only if it
     matches. If no compatible workspace is available, run locally only if this
     machine matches the target architecture — and, for a libc-specific report, its
     libc; if neither environment matches, leave
     the reproducer blocked and state why. Delete a correctly matched workspace with
     `workspaces delete <name> --yes` after the run, unless the user asks to keep it.

     The workspace is only a runner: it auto-clones main, so sync the worktree's
     reproducer change to it first. From the worktree root, fetch a resolvable main
     ref, compute the merge base against it, then create and validate a temporary
     patch before applying it at the cloned checkout's root:

     ```sh
     patch_file=$(mktemp) || exit 1
     ws_name=<name>   # the unique workspace name chosen above
     release_ws() { rm -f "$patch_file"; workspaces delete "$ws_name" --yes; }  # any failure after creation releases the machine
     trap release_ws EXIT
     git fetch origin main   # a resolvable main ref is required for the merge base
     merge_base=$(git merge-base HEAD origin/main) || exit 1
     git add -N -- path/to/reproducer   # intent-to-add: untracked reproducer files must appear in git diff
     git diff "$merge_base" -- path/to/reproducer > "$patch_file" || exit 1
     test -s "$patch_file" || { echo "No reproducer changes to apply" >&2; exit 1; }
     ssh workspace-$ws_name "git -C <workspace-clone> apply --3way" < "$patch_file" || exit 1
     rm -f "$patch_file"
     ```

     Replace `path/to/reproducer` with the path(s) containing the reproducer changes
     and `<workspace-clone>` with the clone's path on the workspace; the patch file is
     local, so the apply runs over ssh. The non-empty check is required: if there is
     no patch, stop and investigate instead of running `git apply`. `--3way` tolerates
     a clone that already contains part of the change (its main tip moved past the
     worktree's base); when it cannot find its base blobs (a shallow or pruned clone),
     fall back to a plain `git apply`. Run this sync block and the approved reproducer
     commands in one shell invocation, so the EXIT trap stays armed until the run
     finishes — a standalone execution of the block deletes the workspace before the
     reproducer runs. A failed
     verification or
     a failed run releases the machine on exit, and the normal exit performs the
     post-run deletion — unless the user asked to keep the workspace, in which case
     disarm the teardown first (`trap - EXIT; rm -f "$patch_file"`). The intent-to-add
     entry stays in the worktree's index, on the failure paths as well as when the
     user keeps the worktree; reset it with `git reset -- path/to/reproducer` when a
     clean index matters.
   - If it is not, verify that this machine's architecture — and, for a libc-specific
     report, its libc — matches the bug, and run the reproducer in the worktree only
     when they do; otherwise leave it blocked and state why.

   Record the exact commands and results. Before the cleanup, save the reproducer code
   or a complete diff, including new files, outside both disposable environments.
   Remove the worktree and delete the workspace afterwards, unless the user wants to
   keep them. When the result is later posted on the ticket, attach the reproducer
   code or diff to the ticket.

5. **Summary.** Name the likely affected code, its constraints, dependencies and risks,
   and the next steps. Do not implement a fix or commit without the user's separate
   approval.

6. **Priority.** Rate impact, likelihood and workaround as H, M or L, each with its
   reason from the evidence, one part at a time, wizard-style:
   - impact: H is a crash, a hang or lost data; M is wrong or missing profile data; L
     is cosmetic or a small overhead;
   - likelihood: H happens in a default or common setup; M needs a specific JVM,
     platform or option; L needs a rare race or setup;
   - workaround: H means no workaround exists; M means a workaround with a real cost;
     L means an easy workaround exists.

   For each part, propose the rating with its reason and ask the user to accept it or
   challenge it with their own rating and reason. On a challenge, re-check the user's
   rating against the evidence and note any disagreement before using it; the user's
   rating stands.

   Map the settled ratings to a priority with the ILW matrix that JDK Mission Control
   uses ([ILW Prioritization](https://wiki.openjdk.org/spaces/jmc/pages/56526160/ILW+Prioritization),
   [matrix](https://hirt.se/images/openjdk/ilw.png)):

   | Priority | Impact, likelihood, workaround |
   | --- | --- |
   | P1 | HHH, HHM, HMH |
   | P2 | MHH, HHL, HLH, HMM, HML |
   | P3 | MHM, MMH, MHL, HLM, MMM |
   | P4 | HLL, MLH, MML, MLM, LHH, LHM |
   | P5 | LMH, MLL, LMM, LHL, LLH, LML, LLM, LLL |

   In Jira, P1 to P5 are Highest, High, Medium, Low and Lowest; Top is the engineer's
   choice only. The table above is the authoritative copy. Propose the mapped priority
   and let the user override it with any value. Do not set the priority field; the
   user decides. If a rating cannot be judged, say so and give the range of priorities
   that it allows. For a `stale` ticket, recommend closing it instead of a priority and
   skip this wizard. State your confidence and the remaining unknowns.

7. **Done.** End by stating explicitly that the triage is complete, restating: the
   classification, the reproducer verdict (`run` with commands and results, or
   `blocked` with the reason), the settled I/L/W ratings, the proposed priority and
   whether the user overrode it, and the next steps. For a `stale` ticket, restate the
   classification, the reproducer verdict, the close recommendation and the next steps
   instead. A triage is done only when the user has seen all of these; do not stop
   silently or leave any of them implicit.

Post the result on the ticket only when the user asks. The comment follows the
`ticket-writing` skill. Its evidence table holds the reproducer with its commands and
results, or as `blocked` if it did not run. Put that table immediately below the exact
heading `## Triage evidence` in every triage result comment; this fixed heading is the
machine-detectable marker for results produced by this workflow. Do not rename or
localize it.
