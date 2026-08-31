---
id: find-ema-batch-collapse
type: finding
status: confirmed
depends_on: [find-getobjectswithtags-quadratic-bottleneck]
supersedes: []
related: [find-getobjectswithtags-quadratic-bottleneck, find-leak-tag-pool-implementation, find-cpu-pain-budget-blocks-bfs]
tags: [root-cause, fix, referenceChains, expandFrontier, GetObjectsWithTags, ema, aimd, NEW-THIS-SESSION]
created: 20260831
updated: 20260831
---

# Per-tag EMA batch calibration collapses to batch=2 (regression of 337b4c21d)

## Observed on-pod (build 1ce2b4f03, /tmp/hotdog-15m.log analysis)

- `expandFrontier gotw batch_size=2 resolved=2 ... gotw_ms=15-25 ema=~10.5e6`
  — ema (per-tag) at 10.5 **milliseconds**/tag vs ~62k ns/tag at the previous
  build. Edges/pass collapsed from 1700-2800 to ~100; only 3 runPass in 15min.
- Each pass: ~1000+ GetObjectsWithTags calls × ~20ms = 10.4s CPU spend into
  the cpu_pain_budget (debt 10436ms observed), ~28s wall per pass.
- Result: BFS never reached the leak-tagged objects → zero useful chains.

## Mechanism (proven by the numbers)

GetObjectsWithTags call time is dominated by a batch-independent
O(tag_map) floor (~20ms at a 225k-entry frontier tag map — observed at
both batch=2 (15-25ms) and batch=400 (20-35ms)). The calibration
`ema = elapsed / batch_size` therefore INFLATES as batch shrinks:
small batch → per-tag cost up → `batch = budget/ema` down → positive
feedback. The equilibrium "call time = deadline" is degenerate once the
floor alone ≈ deadline, so the batch falls to the minimum and stays.

## Second hole found at the same time

The expand loop had NO wall-clock deadline check: heapReferenceCallback's
amortized (0xFFF) deadline check only runs inside FollowReferences, so the
gotw calls between walks were never bounded — hence the 1400-call passes.

## Fix (commit 0db70994d)

AIMD directly on batch size against a per-CALL EMA vs GOTW_CPU_BUDGET_NS:
- over budget → batch /= 2 (floor 8)
- under budget → batch += 64 (cap 512; JNI local-ref bound)
Per-call cost is batch-insensitive in the floor regime, so AIMD converges
to the largest affordable batch instead of collapsing. Plus a deadline
check at the top of every expand while-iteration (gotw is non-safepoint,
invisible to the in-callback check).

Also fixed in the same commit: the emergency multiplier used
`_passes_since_last_progress` (frontier growth — resets every pass,
emergency=0 for the entire run) instead of
`_passes_since_last_candidate_progress`.

## Test

AdaptiveBatchSizeAimdDecreaseAndIncrease (referenceChains_ut.cpp) drives
one expandFrontier call per phase via test seams (a full runPass drains a
small graph AND adds rotation-phase gotw calls, making per-call AIMD
arithmetic unverifiable). AIMD state is NOT covered by
ReferenceChainsTestAccessor::reset() — tests must zero it explicitly.
