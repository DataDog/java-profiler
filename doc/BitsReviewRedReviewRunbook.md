<!-- Copyright 2026, Datadog, Inc. -->

# Bits Review — Red Review Runbook

How to get a pull request from a red Bits review to a mergeable state. The gate
policy, the trusted-result rules, and the publication design live in
[BitsReviewMergeGateDesign](BitsReviewMergeGateDesign.md).

## What a red review is

A red review is a Bits summary review whose metadata verdict is `FAIL` for the
current head of the pull request. The gate publishes `bits-review/head: failure`
for that head, and the pull request cannot merge while that review stays the
latest valid result.

## What does not clear FAIL

The gate reads the latest valid verdict metadata on the current head. It does
not read the review conversation. None of these actions clear a FAIL:

- Replying to a finding, with a refutation or anything else.
- Resolving the conversation under a finding.
- A human approval on the pull request.
- Dismissing the review. A dismissed latest result still blocks.
- Editing the review. An edited latest result blocks, even when edited by the
  bot that wrote it.

Only a newer valid Bits result, or an existing authorized admin bypass, unblocks
the head.

## Findings that are legitimate

Fix the findings and push. A push to the branch normally starts a fresh review of
the new head. When the fresh review ends PASS, the gate publishes success.

If no review arrives after a push, post the comment `@datadog review` on the
pull request. The automatic re-review after a push does not always run; the
comment re-triggers it.

## Findings that are all refuted

When every finding is wrong for this pull request — not applicable, or
deliberately not fixed here — the review conversation still cannot clear the
FAIL. Trigger a fresh review instead:

1. Reply to every finding with the refutation and the reason. The replies are
   the record of the decision for the human reviewers of the pull request.
2. Trigger a fresh review. Push a new commit to the branch. If a push would
   carry no change, post `@datadog review` on the pull request instead.
3. Wait for the fresh review and check the `bits-review/head` status on the PR.
4. If the fresh review ends FAIL again, either address the remaining findings,
   or merge with the existing authorized admin bypass. The bypass is the last
   resort, not part of the normal path.

A fresh review of the same head can replace a FAIL with a PASS. The gate
compares results by submission order, so the newer result wins.
