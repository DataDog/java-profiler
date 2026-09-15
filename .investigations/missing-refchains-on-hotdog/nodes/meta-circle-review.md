# Meta-review: are we running in circles? (weeks burned, leak still unreachable)

Date: 2026-09-15, requested by user after round-13 root cause + fix-D pick.

## Verdict

**Convergent in facts, circular in strategy.**

Not literal circles: every round found a real, distinct, verified defect
(30+ fixed bugs in the INDEX; engine 1000x faster; every mechanism now
probe-proven working). The state monotonically advances.

But rounds 9→13 — five pod rounds, several weeks — all attacked the SAME
invariant failure inside the SAME architecture:

    coverage = walk_rate x search_lifetime >= anchor_population

- Round 9: tier composition wrong (holder evicted → fix B' live feed)
- Round 10: sweep never completes (restarts) → fix A (search lifetimes)
- Round 11: collector 4/pass cursor lottery → fix budget+index+priority
- Round 12 (B+C): rate fixed 8x, order unchanged
- Round 13: measured the invariant whole: 28k population vs ~4k coverage
  (21 walks/pass x ~190 passes, admission-order selection) — the holder at
  position ~12-21k is deterministically unreachable.

Each fix tuned a parameter of the funnel (tier composition, FIFO, budget,
iteration cost, priority). None questioned the funnel itself. The round-13
measurement (rate x lifetime vs population) should have been the FIRST
analysis, before any of rounds 9-12 — it was computable from pod logs at
any point.

## Why the funnel cannot win (the structural statement)

The architecture explores a ~12M-object heap through a ~3741-edge/pass
budget. A static-held leak requires covering the static-holder population
(~28k anchors, ~6.6k distinct holder classes — MEASURED round 13: 1092
distinct classes per 5.7k-class sweep window) within a ~190-pass search
lifetime, at ~46 anchors/pass ceiling (81 edges/anchor, measured). Even the
strongest tuning (D: cohort shrink + rotation) needs multiple search
lifetimes (hours), and its collection-shaped cohort size is UNMEASURED —
the leaf filter accounts for only ~17% of admits (String/[I/[B/INST_CODE
top admit classes). D's arithmetic is not established. The pattern of
"plausibly sufficient, then a new scale surprise" has now repeated 4 times.

## The structural exit (option C, previously deprioritized)

A one-shot whole-heap pass at search start eliminates the funnel for
discovery: class → static → holder → ... → leak-tagged chunk admitted in
one bounded STW, interception fires immediately, chains complete. Our own
standards survey (find-attribution-standards-survey) found that JFR's
production LeakProfiler does exactly this shape — fresh full BFS at every
emit, first-path-wins, bounded. The design rejected it for pause-time, but:
searches are leak-gated and rare; the pod tolerates seconds of STW; and the
frontier-cap interplay is a designable problem, not a wall (e.g. one-shot
admission policy: root-attached statics + leak-tag interceptions + the
parent chain of each intercepted object only — not the full graph).

## Process failures that cost the weeks (fix these regardless)

1. **Scale invariants were never measured as a whole.** rate x lifetime vs
   population was computable from pod logs at any round; it was measured
   only in round 13, after four tuning rounds.
2. **Local tests are toy-scale.** gtests verify mechanics at dozens of
   entries; every scale defect (frontier caps, FIFO depth, index size,
   sweep order, restart cadence) could only manifest on the pod — one
   discovery per deploy cycle, deploys done only by the user, log windows
   rotating in minutes. Need a scale gtest: synthetic 30k classes /
   28k-anchor index / 250k frontier cap / restart loop, asserting the
   coverage invariant itself.
3. **Fixes were validated as "mechanically working"** (walk rate up, index
   fast, budget 16) rather than against the end-to-end success criterion
   (a leak-tagged chunk intercepted from a static-held holder). Every
   round's success gate should be the end-to-end outcome, or a measured
   invariant, never an intermediate rate.

## Decision needed

D (cohort shrink + rotation) was picked before this analysis. Given the
measured ~6.6k distinct holder classes vs 4k coverage/search and the
unmeasured collection cohort, D risks being the 5th tuning round. C exits
the failure class entirely. Recommend: design C now (with the minimal
admission policy to respect the frontier cap), keep D's cheap parts
(leaf-filter index exclusion) only if they fall out of C's design; add the
scale gtest before any next deploy.
