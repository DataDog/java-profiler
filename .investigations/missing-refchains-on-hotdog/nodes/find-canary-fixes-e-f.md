---
id: find-canary-fixes-e-f
type: finding
status: confirmed
depends_on: [find-cpu-pain-budget-starves-canary-passes, find-threadloop-presleep-blocks-back-to-back]
supersedes: []
related: []
tags: [fix, referenceChains, pain-budget, threadLoop, canary, NEW-THIS-SESSION]
created: 2026-08-25
updated: 2026-08-25
---

# Fix E + Fix F: threadLoop() sleep dedup, canary-aware pain-budget escalation

## Reasoning chain

User was given 2-3 alternatives for each of the two findings from this
session (`find-cpu-pain-budget-starves-canary-passes`,
`find-threadloop-presleep-blocks-back-to-back`) and chose: threadLoop
alternative A (delete the leftover unconditional sleep), pain-budget
alternative B (dynamic escalation while a canary is active, mirroring the
existing urgency-driven `_budget *= 4` ramp already in `threadLoop()`).

**Fix E (threadLoop dedup).** Deleted the unconditional
`if (cadence_ns > 0) { OS::sleep(cadence_ns); }` block at the old
`referenceChains.cpp:736-738`, confirmed by `git log -L` to be a leftover
from before commit `1f86edf3f` ("move sleep after shouldRunPass") added the
correctly-guarded sleep later in the same loop iteration
(`if (!should_run && cadence_ns > 0) { OS::sleep(cadence_ns); ... }`). That
commit never removed the original, leaving every iteration paying an extra,
unconditional `cadence_ns` sleep regardless of `should_run` - including
canary-bypass-eligible iterations the surrounding comment explicitly says
should skip it. No design tradeoff; the deleted block's own `!_running`
early-exit is already duplicated by the surviving guarded sleep's, so
nothing is lost.

**Fix F (canary-aware pain-budget escalation).** `shouldRunPass()`
(RUNNING branch) now computes `canary_active` *before* the
`_cpu_pain_budget.canStartNow()` check (previously computed only later, for
the bypass branch) and calls the new `PainBudget::setRefillRate()` to
temporarily scale `_cpu_pain_budget`'s refill rate by
`CANARY_PAIN_BUDGET_REFILL_MULTIPLIER = 4.0` (same factor already trusted
for `_budget`'s own urgency ramp), capped at `1.0` (100%/wall-clock), while
`canary_active` holds. Reverts to the configured base rate
(`_pain_budget_refill_rate`) automatically the instant `canary_active` goes
false (recomputed every call - no separate revert path needed). Both call
sites (escalation and the later bypass-return branch) now share the same
`canary_active` snapshot instead of recomputing `popcount` twice.

New helper: `PainBudget::setRefillRate(double, u64 now_ns)`
(`painBudget.h`) - drains at the *old* rate up to `now_ns` first (so the
rate change only affects time elapsed after the call), then swaps
`_refill_rate`. Necessary because assigning a freshly-constructed
`PainBudget(rate)` (the pattern `start()`/`resetSearchStateForTest()` use)
would reset `_balance_ms` to 0, silently forgiving any already-accumulated
debt every time canary state flips - not the intended semantics for a
live, per-call toggle.

## Changes made

- `ddprof-lib/src/main/cpp/painBudget.h`: added `setRefillRate()`.
- `ddprof-lib/src/main/cpp/referenceChains.h`: added
  `CANARY_PAIN_BUDGET_REFILL_MULTIPLIER = 4.0` constant next to the other
  reference-chains tuning constants.
- `ddprof-lib/src/main/cpp/referenceChains.cpp`:
  - `threadLoop()`: deleted the leftover unconditional sleep block (old
    `:728-741`, comment + sleep + running-check).
  - `shouldRunPass()`: moved `canary_active` computation ahead of the
    `_cpu_pain_budget` check, added the `setRefillRate()` call, reused
    `canary_active` in the bypass-return branch instead of recomputing.

## Verification

- `./gradlew :ddprof-lib:compileDebug -Pskip-gtest` - compiles cleanly.
- `./gradlew :ddprof-lib:gtestDebug` (full suite) - BUILD SUCCESSFUL, 188
  actionable tasks, no failures reported.

## What this rules out

Nothing new ruled out - this closes the two findings above rather than
refuting an alternative hypothesis.

## Not yet done

- **Committed and pushed** as `01047a6aa` on `jb/reference-chains`, together
  with Fix D (`find-abandon-event-queue-fix`). Not yet deployed/re-verified
  on the hotdog pod.
- No dedicated regression test added for either fix (e.g. a test asserting
  `_cpu_pain_budget`'s effective rate is 4x while `canary_active` and back
  to base once resolved) - not requested.
