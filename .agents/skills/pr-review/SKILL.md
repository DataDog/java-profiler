---
name: pr-review
description: Review another engineer's java-profiler PR, given by number or URL, and report the findings in the session. Use when asked to review a PR; for your own change, use `pre-pr-review`.
---

# PR review

This skill reviews a PR that another engineer owns. It writes no review marker, does
not run `install-hook`, and does not fix findings. It never changes the engineer's
checkout: do not use `gh pr checkout`. If a reviewer needs a checkout, use a throwaway
worktree, and remove it after the review.

1. **Target.** Read the PR's base branch, head commit, files, title and description,
   for example with `gh pr view <n> --json baseRefName,headRefOid,files,title,body`.
   Fetch the commits without a checkout: `git fetch origin <base>` and
   `git fetch origin pull/<n>/head`. The range is
   `MB=$(git merge-base refs/remotes/origin/<base> <head>)` to `<head>`. Name the head
   commit in each report and post, so that the review applies to that commit only.

2. **Reviewer.** Take the reviewer from the first row of the `pre-pr-review` step 3
   table that matches the PR's files. Also apply the fallbacks and the **Cost** rule
   below that table.
   - **Updated PR.** Use the row for fixes to a range already reviewed, on the range
     `<reviewed head>..<head>`, only if the engineer names the reviewed head, or an
     earlier review posted by this skill names it. Review the whole PR if the base
     changed under it, if no reviewed head is known, or if the reviewed head is not an
     ancestor of the head (`git merge-base --is-ancestor`).
   - **No review tool.** If the harness has no review tool, say so and name the row
     that the table picks. Offer a review by a fresh session of the same harness, and
     label its result as a model review without a review tool. Tell the engineer that
     they can run the reviewer of that row in Claude Code.

3. **Fresh context.** Run the reviewer as the `pre-pr-review` **Fresh context**
   paragraph says. Give it only the range, the PR title and description as the stated
   intent, and the instruction to skip `.knowledgebase/`. Never give it your own view
   of the PR. Run no reviewer fix flow.

4. **Triage.** Check each finding against the code at the head commit. Drop the
   findings that do not hold. Keep the severity rules of `pre-pr-review` step 4: a gate
   or trust-boundary bypass stays High.

5. **Report.** Report in the session:
   - the head commit;
   - the row, and why it matched;
   - the reviewer;
   - the findings by severity;
   - the critical areas that the PR touches, from the list in `doc/WorkTracking.md`,
     so that the engineer knows which human reviews the PR needs.

6. **Post.** Post on the PR only when the engineer agrees. The agreement can be part
   of the original request, for example "review PR 1234, post your findings". Post by
   the reviewer's posting route (`/code-review --comment` or Sphinx publication), or as
   one PR comment that follows the `pr-writing` skill. Name the head commit in the post.
   Only comment: never submit Approve or Request changes, for example with
   `gh pr review --approve` or `--request-changes`. An approval counts toward the merge,
   so it must come from a human.
