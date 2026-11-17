---
id: find-marker-branch-babysit-mismatch
title: Marker branch field vs Claude worker's -babysit local branch; Bits re-trigger codified
kind: finding
tags: [babysit-pr, bits, pre-push-hook, marker, claude-worker]
applies_to: []
source: pr-1001/bits-1702
status: active
recorded: 2026-11-17
valid_at: 2026-11-17
---

# Marker `branch` field vs Claude worker's `-babysit` local branch (Bits 17:02 P1, PR #1001)

The worker marker recorded `branch: <branch>` while the Claude Code worker checks
out `<branch>-babysit`, so `.githooks/pre-push` — keyed on the pushing checkout's
local branch via `marker_branch()` — silently skipped scope enforcement on
`HEAD:<branch>` pushes. Discovered by the 17:02 Bits review round on PR #1001,
verified by the babysit worker against `marker_branch()` in `.githooks/pre-push`.

Fixed in 4a4b5cbe5 (skill text): the marker's `branch` field names the worker's
actual local branch (Pi: `<branch>`; Claude Code: `<branch>-babysit`).

Codified alongside (cb6be7999 + b66d0e507): `bits-review/head` never triggers the
Bits bot itself. Stuck-pending on an otherwise-green head gets one plain top-level
`@datadog review` comment per head — recorded in the marker's `bits_triggered`
list so a restarted run never re-posts; on a draft PR the comment is required
(pushes do not re-trigger Bits on drafts). Applied to PR #1003 (comment 6944006716).
