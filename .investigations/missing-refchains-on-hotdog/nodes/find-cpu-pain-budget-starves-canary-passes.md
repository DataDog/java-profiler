---
id: find-cpu-pain-budget-starves-canary-passes
type: finding
status: confirmed
depends_on: [find-canary-stuck-abandon-detector]
supersedes: []
related: [find-threadloop-presleep-blocks-back-to-back, ev-hotdog-trace-zero-runpass]
tags: [root-cause, referenceChains, pain-budget, canary, starvation, shouldRunPass, silent-gate]
created: 2026-08-25
updated: 2026-08-25
---

# `_cpu_pain_budget` silently starves `runPass()`, explaining zero canary resolution

## Reasoning chain

Second direction the user asked to "proceed" on: why has zero canary
candidate ever resolved, even with Fix A/B/C all confirmed working?

`shouldRunPass()` (`referenceChains.cpp:840-937`) checks, in order: first-pass
branch, terminal-state branch, then at `:893`
`if (!_cpu_pain_budget.canStartNow(now_ns)) { return false; }` — **the only
branch in the whole function with no `TEST_LOG` call** — before it ever
reaches the canary-active bypass (`_candidate_count > 0 && popcount(found) <
candidate_count` → "run immediately", which does have its own `TEST_LOG`).
A blocked pain budget is therefore invisible in logs: you see
`pollWatchedTargets` firing every cycle (it's unconditional, `:801`) and
never see a single `runPass` line, with no diagnostic clue why.

`PainBudget` (`painBudget.h`) is a leaky bucket over *cost*, not *rate*:
`spend(pain_ms)` adds debt, `canStartNow()` drains `elapsed_ms * refill_rate`
off the balance and returns true only once balance ≤ 0. `_cpu_pain_budget` is
spent every single pass (`referenceChains.cpp:3033`,
`_cpu_pain_budget.spend(TSC::ticks_to_millis(non_safepoint_ticks))`) with the
pass's non-safepoint CPU cost (root/stack-ref enumeration dispatch, frontier
admission, rotation-candidate collection — i.e. real cost proportional to
heap/frontier size, not a fixed small constant).

Traced `_refill_rate`'s value (not done in the prior session, completed this
turn): NOT hardcoded to 0.0 in production. `referenceChains.cpp:505-511`
constructs it from `_pain_budget_refill_rate = std::max(args.
_reference_chains_pain_budget_percent, 0) / 100.0`, and
`_reference_chains_pain_budget_percent` defaults to
`DEFAULT_REFERENCE_CHAINS_PAIN_BUDGET_PERCENT = 1` (`arguments.h:104,359`) —
i.e. **1% by default**, tunable via `painbudget=<0-100>` in the reference-chains
config string (`arguments.cpp:545-548`). So the earlier "refill_rate == 0.0
forever" landmine from `painBudget.h`'s own comment does NOT apply verbatim —
this rules out a literal permanent block.

What a 1% refill rate means in practice: draining N ms of debt takes N/0.01 =
**100×N milliseconds** of wall-clock time. A pass costing just 500ms of
non-safepoint work (plausible on a large heap with a wide frontier — this is
exactly the "genuinely expensive, bounded operation" `painBudget.h`'s own
comment describes) creates a **50-second** drain requirement before the next
pass is even considered, regardless of how urgently a canary candidate is
waiting. This is consistent with, and sufficient to explain, the live
evidence below.

## Evidence

Continuous 45-second trace captured directly from the pod (`kubectl logs -f
--since=1s` to `/tmp/hotdog_trace.log`, 25,865 lines — see
`ev-hotdog-trace-zero-runpass` for the full evidence writeup):

- `grep -c "runPass done"` → **0** matches in 45s.
- `grep -c "pollWatchedTargets"` → **1472** matches in the same window
  (confirms this is unconditional and unaffected — `referenceChains.cpp:801`
  runs it every loop iteration regardless of `should_run`).
- `pollWatchedTargets` output shows `candidate_count=5`, all 5 slots
  occupied, candidates repeating unchanged across many polls — consistent
  with a search that is not advancing because `runPass()` itself is not
  running, not because candidates aren't being found/tracked.

This directly rules out "cadence sleep alone" as sufficient explanation:
`threadLoop()`'s cadence sleeps top out at roughly 1-2s per idle iteration
(see `find-threadloop-presleep-blocks-back-to-back`), which cannot account
for a full 45-second window with literally zero passes. A silent gate that
can block for tens of seconds at a time is required, and `_cpu_pain_budget`
is the only such gate in the code (confirmed: the only branch in
`shouldRunPass()` without a `TEST_LOG`).

## What this rules out

- **Literal permanent block from `_refill_rate == 0.0`** — refuted.
  `_pain_budget_refill_rate` is constructed from a nonzero default (1%,
  `DEFAULT_REFERENCE_CHAINS_PAIN_BUDGET_PERCENT`), not left at the
  `PainBudget` default-constructor's `0.0`. The budget *does* eventually
  drain — just far too slowly relative to realistic per-pass cost for the
  canary-bypass "run back-to-back" design intent to hold.
- **Cadence sleeps as the sole cause of the 45s silent window** — refuted by
  the arithmetic (max ~1-2s per idle iteration) not matching the observed
  duration.

## Not yet done

- Have not measured the actual non-safepoint cost of a single `runPass()` on
  this pod's heap directly (no `TEST_LOG` exists at the spend site either —
  same silent-gate problem, one level removed). The 100×-drain-time argument
  is derived from the documented refill-rate semantics and the config
  default, not from a directly observed `_balance_ms` value.
  `PainBudget::balanceMs()` exists for exactly this kind of introspection but
  is not currently logged anywhere.
- No fix proposed or implemented yet — this is a design-level tradeoff (how
  aggressively the canary bypass should be allowed to override the pain
  budget, or whether the budget needs a canary-aware carve-out) that should
  be proposed to the user before touching `shouldRunPass()`'s gating order or
  `PainBudget`'s semantics.
