---
name: pre-pr-review
description: Run the mandatory agentic code review over a branch and record its review marker. Use before opening a PR, marking one ready, or pushing fixes to an open PR.
---

# Pre-PR review

0. **Hook.** Run `python3 utils/review-marker.py install-hook` (idempotent) and
   relay any error or note it prints. Never set `core.hooksPath`: a repo-local value
   replaces the global hooks, including Datadog's secret scanner.

1. **Base.** Use the PR's base as a remote ref: `origin/main`, or `origin/<branch>`
   when the work is stacked. Commit the change set first — the marker certifies
   commits, so uncommitted work is not covered.

2. **Review.** Use the strongest reviewer the harness provides: `/sphinx review`,
   else `/code-review`, over the diff from the merge base to `HEAD`. If none is
   available, say so and get explicit user sign-off; do not write a marker then.

3. **Judgment checks.** In addition to correctness, check every comment, javadoc
   and doc paragraph the change adds or modifies against the AGENTS.md
   **Comment budget** and **Comments** rules:
   - each comment ≤3 lines, each line a distinct non-obvious constraint; a longer
     comment needs a reason a reviewer would accept;
   - current behavior only — no history, and no references to plans, specs,
     review reports or findings, requirement IDs, tickets or line numbers.
   Code written by a review tool's fix flow gets the same check: it must not
   cite the tool's own working artifacts.

4. **Findings.** Fix Critical/High findings, or get the user's explicit waiver.
   Commit the fixes and re-review what they touched.

5. **Marker.** On the final commits, write the marker — also when the user ran
   the review manually and reports it back:
   ```bash
   python3 utils/review-marker.py write --tool <reviewer> --session <id> --base <base>
   ```
   Any later change to the branch's diff makes it stale. Then `.githooks/pre-push`
   refuses pushes to an open PR, and in Claude Code the `require-fresh-review` hook
   blocks `gh pr create`/`gh pr ready`, until this skill runs again. A clean rebase
   keeps the marker fresh.

6. **Report.** State the reviewer, the outcome and any waived findings in the PR
   description or the reply to the review.
