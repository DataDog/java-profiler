---
id: find-cpu-pain-budget-blocks-bfs
type: finding
status: diagnosed
depends_on: []
supersedes: []
related: [find-shared-deadline-starves-expand, q-safepoint-budget-model]
tags: [root-cause, referenceChains, cpu-pain-budget, shouldRunPass, silent-gate, NEW-THIS-SESSION]
created: 2026-08-28
updated: 2026-08-28
---

# cpu_pain_budget silently blocks BFS in RUNNING state

## Observation

After the leak signal fired (5 candidates, `heapFloorRising=1`), `shouldRunPass`
returned `false` on every iteration with **no log**. Only `pollWatchedTargets`
ran (unconditional). The BFS never started — zero `runPass` logs.

## Root cause

In `shouldRunPass()`, the RUNNING branch (line ~895) checks
`_cpu_pain_budget.canStartNow(now_ns)` and returns `false` with no log when
it fails. A previous search had spent ~1075ms of CPU pain into the budget.
At 12% refill rate (canary escalation: 3% × 4), the budget drained at
~12.5ms per ~100ms iteration — taking ~90 seconds to drain enough for the
next pass.

This was **completely silent** — no log, no counter, no diagnostic. The
only symptom was `pollWatchedTargets` running with zero `runPass` logs.

## Fix (diagnostic, committed fcc67179a)

Added `TEST_LOG` to the cpu_pain_budget block path, reporting balance,
refill_rate, and canary_active. Confirmed on-pod that the budget was the
block.

## Note

This is not a bug per se — the pain budget is working as designed (rate-
limiting CPU cost). But the 12% refill rate for canary searches means
~90 seconds between passes after a search that spent 1000ms of CPU. For
a 2-3 hop leak that needs ~5 passes, that's ~7.5 minutes of BFS time
after the initial debt drains. The canary multiplier (4×) may need to
be higher, or the initial debt should be reset when a canary search is
active.
