---
id: find-fix-burnin-variant-analysis
title: Parallel session's fix variants vs the implemented A+B - overlap and deltas
kind: finding
tags: [fix-variants, burn-in, design-delta]
applies_to: []
source: writing-any-code-thoroughly/find-fix-burnin-variant-analysis
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Parallel session's fix variants vs the implemented A+B - overlap and deltas

## Reasoning chain
Parallel session's verdict: expected control flow, but a demonstrated startup
false-positive vulnerability - the urgency path authorizes candidate-free
whole-heap searches on transient warmup growth. Proposed fixes:

1. Minimal: projection burn-in in secondsToOOM() - require ~300s since tracker
   activation before returning a usable projection. One scalar, no allocation.
   Cost: delayed detection of genuine startup OOM races.
2. Narrower variant: suppress only candidate-free authorization during
   burn-in.

Implemented in this worktree (A+B, 2026-10-29) - relation to the above:

- My A (urgent latch never entitles a candidate-less search, at any age) is
  STRICTLY STRONGER than variant 2: candidate-free authorization is impossible
  always, not only during burn-in. When a candidate clears the probe during
  urgency, the search starts and the ramp applies - matching the parallel
  session's stated intent ("urgent exists to chase a leak").
- My B (isUrgent() refuses to latch when the ring's observation window <
  OOM_URGENT_THRESHOLD_S) is a DIFFERENT warmup guard than variant 1's
  activation-age burn-in: window-based (history span actually backing the
  slope) vs age-based (time since tracker activation). Both kill the warmup
  false positive; the window form also handles the GC-storm case where a
  30-sample ring spans only seconds at any process age, and needs no new
  activation timestamp - it reuses the ring timestamps secondsToOOM() already
  reads.

Deliberately NOT implemented: variant 1's activation burn-in. If the operator
prefers age-based burn-in (simpler mental model, one scalar) it can replace or
complement B; with A in place, burn-in only affects the RAMP (cadence/pause
boost during the first 300s), not search authorization.

## Evidence
- Implemented change set (uncommitted): livenessTracker.{h,cpp}
  (secondsToOOM out-param, effective flag), referenceChains.cpp (hasLeakSignal,
  isUrgent warmup guard), tests + docs; 1017 gtest OK / 0 failed (2026-10-29).

## Open questions
- Whether the ramp itself should also be burn-in-gated (variant 1's full
  semantics) - currently the ramp engages on raw projections during warmup;
  bounded by pain budgets, but it did produce the 2495 boosted admits.
