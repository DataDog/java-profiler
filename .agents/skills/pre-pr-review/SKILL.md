---
name: pre-pr-review
description: Run the mandatory agentic code review over a branch and record its review marker. Use before opening a PR, marking one ready, or pushing fixes to an open PR.
---

# Pre-PR review

Run `review-marker.py` as of `origin/main`, never the checkout's copy: the branch may
be untrusted, and the hooks check markers with `origin/main`'s version. Below, `RM` is:
```bash
git show refs/remotes/origin/main:utils/review-marker.py | python3 -I - <args>
```
Only when that `git show` fails (the gate is not on `origin/main` yet) use
`python3 utils/review-marker.py <args>`.

0. **Hook.** Run `RM install-hook` (idempotent) and relay any error or note it
   prints. Never set `core.hooksPath`: a repo-local value replaces the global hooks,
   including Datadog's secret scanner.

1. **Base.** Use the PR's base as a remote ref: `origin/main`, or `origin/<branch>`
   when the work is stacked. Commit the change set first — the marker certifies
   commits, so uncommitted work is not covered.

2. **Review.** Review exactly the range the marker will certify,
   `MB=$(git merge-base refs/remotes/<base> HEAD)` to `HEAD`, named explicitly — without
   a range, reviewers default to unpushed or last-commit changes; the full ref keeps a
   tag named like the base from changing the range. Pick the reviewer from the first row
   that matches the range, top to bottom:

   | The range changes | Reviewer |
   | --- | --- |
   | Gates and trust boundaries, including fixes to them: hooks, `review-marker.py`, the `utils/*-policy.py` files, CI checks, this skill, the AGENTS.md review rules | Sphinx (`/sphinx review range $MB..$(git rev-parse HEAD) --report-json <path>`), standard effort; at most one `--effort=deep` run per PR, on the final candidate |
   | Other production code | Sphinx, standard effort |
   | Only fixes to a range already reviewed | `/code-review` medium, on the fix range only |
   | Only docs, skills or tests | `/code-review` medium; not low, which skips test files |

   Without Sphinx, use `/code-review` with the range as its target, at high effort for
   the first row and medium otherwise. Report only — run no
   reviewer fix flow; steps 3 and 4 do the triage and fixes. If no reviewer is
   available, say so and get explicit user sign-off; do not write a marker then.
   Tell the reviewer to skip `.knowledgebase/`: its content is cairn's, and step 4
   checks only its frontmatter. The marker still covers it.

   **Cost.** Plan for about $20–30 of agentic review per PR; before a run that is likely
   to exceed it, ask the user. A long orchestrating session re-reads its own context on
   every turn, so run this skill for large reviews from a fresh session where the harness
   allows; that session writes the marker.

3. **Self-checks.** In addition to the reviewer, check the diff for unused variables,
   unused or duplicated macros, dead code (methods, JNI entry points, fields, no-op
   functions, empty files left without callers; test-only helpers stay only if marked
   as such) and misspelled identifiers or comments. Then check every comment, javadoc
   and doc paragraph the change adds or modifies against the AGENTS.md
   **Comment budget** and **Comments** rules:
   - each comment ≤3 lines, each line a distinct non-obvious constraint; a longer
     comment needs a reason a reviewer would accept;
   - current behavior only — no history, and no references to plans, specs,
     review reports or findings, requirement IDs, tickets or line numbers.
   Code written by a review tool's fix flow gets the same checks: it must not
   cite the tool's own working artifacts.

4. **Findings.** Fix Critical/High findings, or get the user's explicit waiver.
   Commit the fixes and re-review what they touched. Also fix every violation of
   `python3 utils/check-copyright.py --base <base>` and `python3 utils/check-claude-md.py`:
   CI and `.githooks/pre-push` run the same checks, so a marker over them cannot merge.
   Likewise for `python3 utils/check-knowledgebase.py`, which CI runs: fix a bad
   memory with cairn, never by hand.
   - A gate or trust-boundary bypass is never downgraded below High in triage.
   - When a re-review finds new cases of a defect class it already reported, fix the
     class (a stricter rule, a closed grammar), not the next case.
   - Stop re-review rounds when they find only Medium or Low findings in the fixes
     themselves. Fix those that are cheap to fix; list the rest in the report (step 6).

5. **Marker.** On the final commits, write the marker — also when the user ran
   the review manually and reports it back:
   `RM write --tool <reviewer> --session <id> --base <base>`, where `--session` names
   the session that ran the review.
   Any later change to the branch's diff makes it stale. Then `.githooks/pre-push`
   refuses pushes to an open PR, and in Claude Code and Pi the `require-fresh-review`
   hook blocks `gh pr create`/`gh pr ready`, until this skill runs again. A rebase keeps
   the marker fresh unless the base changed lines next to the branch's hunks.

6. **Report.** State the reviewer, the outcome, and any waived or unfixed findings in
   the PR description or the reply to the review.

7. **Repeated failures.** Tell the user, in the session, each mistake you made twice
   during this change and each point the user had to explain twice. Give each a
   proposed home: `AGENTS.md`, a `doc/` page, a skill, a hook or a CI check. Do not
   edit those files for it in this change; the user decides whether it becomes a ticket.
