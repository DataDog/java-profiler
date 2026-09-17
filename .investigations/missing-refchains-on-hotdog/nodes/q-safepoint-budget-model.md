---
id: q-safepoint-budget-model
type: question
status: open
depends_on: [ev-timing-split-callback-vs-jvmti]
supersedes: []
related: [find-static-field-sweep-never-completes, find-static-field-sweep-cursor-fix]
tags: [safepoint, budget, deadline, per-call, cumulative, rate-cap, design, NEW-THIS-SESSION]
created: 2026-08-26
updated: 2026-08-26
---

# Safepoint budget model: per-call 50ms cap + cumulative 500ms/sec rate cap?

## User's clarification

The user clarified the intended safepoint budget model (two distinct
concerns, currently conflated in the code):

1. **Single STW operation**: each chunk's `FollowReferences` call should
   be capped at 50ms. If it exceeds, truncate and resume from the
   resumable cursor next pass. This is what the per-chunk deadline
   already does — but only if the deadline isn't already spent by other
   sub-operations.

2. **Cumulative per real-time second**: total STW time across all
   operations (root enum + sweep + expandFrontier + rotation) should be
   ≤500ms/sec. This is a *rate* cap, not a per-call cap.

## Current code is wrong for this model

`runPassManualWalk()` sets **one** `_pass_deadline_ns` at the top
(`:2334-2337`) and shares it across all sub-operations. So root
enumeration + expandFrontier can consume the budget before the sweep
runs. This is why the sweep was truncating at 50ms even though each
chunk only needs 3-11ms — the budget was already spent by other
sub-operations.

## Proposed fix (not yet implemented)

Give each sub-operation its own 50ms deadline (per-call cap), and add a
separate cumulative rate cap (500ms/sec) via the existing
`PainBudget`/cadence mechanism. The per-call cap ensures no single
`FollowReferences` exceeds 50ms; the rate cap ensures total STW time
stays ≤500ms/sec across all passes in a rolling 1-second window.

This is the leaky-bucket follow-up discussed earlier in the session,
but now clearly motivated by the timing data: the sweep itself is
3-11ms/chunk (well under 50ms per-call), but the shared budget means
it gets truncated because other sub-operations spent the deadline first.

## Status

Open design question. User stated the model but hasn't asked for
implementation yet. The 200ms temporary override (commit `fd18425c6`)
needs to be reverted before any deployment — it was a measurement
diagnostic, not a production change.
