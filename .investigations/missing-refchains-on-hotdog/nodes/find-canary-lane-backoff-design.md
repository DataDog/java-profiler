---
id: find-canary-lane-backoff-design
type: finding
status: implemented
depends_on: [find-canary-search-forces-max-cadence, ev-leaktag-onpod-round4]
related: [find-getobjectswithtags-quadratic-bottleneck, q-safepoint-budget-model]
tags: [fix, design, canary, cpu-burn, work-scaled, NEW-THIS-SESSION]
created: 20260901
updated: 20260901
---

# Canary-lane work-scaled backoff (user point 3, option A)

## The defect (user-observed: ~1 core on hotdog)

canary_active bypassed every cadence check and threadLoop() skips its
sleep whenever a pass will run: an un-findable candidate held the
chase open back-to-back for 32 min at ~88 passes/min (round 3) - a
full core. The doc's "measured cost is tiny (<20ms per 60s)" claim
only ever held for findable candidates. The 15x-covering/100x-emergency
pain-budget refill multipliers existed to feed exactly this unbounded
mode.

## The law (first fixed-cap, reworked work-scaled after local evidence)

Inter-pass spacing = _canary_backoff_mult x EMA(pass wall duration,
0.8/0.2, ms). Multiplier: 1 (gate OFF - natural pass rate) -> doubles
per pass with no candidate progress -> caps at CANARY_BACKOFF_MULT_MAX
(16); candidate progress (found bit or new candidate admitted) resets
to 1; search start/restart resets to 1; the OOM urgency ramp
(_oom_ramp_active, set by threadLoop) overrides the gate; the
gc-finish-epoch trigger deliberately does NOT bypass it (GC-heavy
workloads bump the epoch every wake).

Why work-scaled: a fixed cap only binds when it exceeds the pass's
own duration - the pod's passes ran 0.7-4s, so a 1s cap would have
changed nothing (work-bound loop), while the same 1s cap starved
ReferenceChainTrackingTest's deep ~200-pass chase outright (held-off
wakes outpaced the test window; pass wall there ~20-30ms). Scaled
against measured pass cost the burn bound is structural: <= ~1/16 of
a core on pass work at the cap, whatever the work is; a deep-but-cheap
chase keeps density (200 passes at mult 16 x ~25ms = ~80s - passes).

The pain-budget refill is now a flat 100x while a chase is open - a
double-throttle guard only (the backoff owns the rate); the covering
(15x)/emergency (100x) split is deleted.

## Verification

546 gtests green (CanaryLaneBacksOffWithoutProgressAndResetsOnProgress:
deterministic seeded-EMA arithmetic - doubling, cap-hold, progress
reset, urgency bypass, hold-off/re-admit). Slow suite: ToGcRoot green
at load ~6 (backoff engaged mult 2..16, ema 20-30ms, chase completed);
leak-correlation unaffected (its chase resolves early). ToGcRoot/
UnboundedCache remain load-sensitive (separate family - the executor
JVM's in-process passes hit ~4.4s under the 5s pausetarget at load
25+, so the work-scaled spacing inflates with them; observed failing
only at load 25-55).

Doc: ReferenceChains-SignalsExplained.md sections 4/8/11 rewritten
(no-GC-wake + epoch-bypass caveat + cadence dual role; work-scaled
backoff with pod evidence; corrected tiny-cost claim).

## Pod expectation (round 5+)

`held off by canary backoff mult=N ema_ms=M` TEST_LOG lines; stuck-chase
burn decays to <= ~6% of a core on pass work; a chase that makes
progress keeps its burst. If the pod's pass-wall decomposition (static
sweep lap share - still unmeasured) shows ema dominated by the sweep,
consider sweep-lap pacing separately.
