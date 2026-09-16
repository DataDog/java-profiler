---
id: ev-leaktag-onpod-round10
type: evidence
status: confirmed
depends_on: [find-anchor-live-feed-design, find-already-admitted-blocks-unreachable]
related: [find-anchor-holder-eviction, find-canary-stuck-restart-wipes-frontier, find-togcroot-orphaned-slot-stranding]
tags: [pod-verification, round-10, b-prime, live-feed, fifo, sweep-lap, restarts, NEW-THIS-SESSION]
created: 20260914
updated: 20260914
---

# Pod round 10 (build 6f3c6cc2e = B' + nesting fix): B' machinery LIVE; interception zero — restarts reset the sweep lap before it reaches the leak holder's class

Pod `prof-analyzer-hotdog-jb-d9d8cf-plwpx` (fresh from redeploy), JVM
26.0.2+10, container `prof-analyzer`, deployed build verified via the
`static_anchor_fifo_*` fields (unique to 6f3c6cc2e) in rotation_candidates.

## B' mechanically verified live

- Pushes: `static_anchor_fifo_pushed_total` +250-500/min; FIFO size pins at
  ~1008-1021 (the 1024 cap — cap-drop throttling active); counter NOT reset
  on restartSearch (by design), size IS (1008→477 observed = a restart).
- Drain/walk: `static_anchor_tags=20` = 16 FIFO + 4 collector per pass;
  chain-attached anchors (`parent!=0 root_kind=0` — bytebuddy/micronaut
  machinery, e.g. MethodSortMatch$Sort enums, ConstructorComparator) ARE
  being walked — the population round 9's tier structurally excluded.
- Walk truncation: `walked=6..16 of selected=20 truncated=1` in ~60% of
  passes — the FIFO-first order starves the collector's suffix those
  passes (secondary issue; see below).
- Leak tagging healthy: klass_id=2 tid=12875 tagged=21 max_size=78643216.

## Interception STILL zero — the new blocker chain (observed, not inferred)

1. Restarts every few minutes: frontierSize non-monotonic across samples
   (17k → 370k → 24k → 237k), FIFO cleared mid-run (1008→477),
   candidateFound flapping 0/1 ↔ 0/0 (matches the known shared-JVM epoch
   noise resetting consecutive_positive — find-togcroot-orphaned-slot-
   stranding fix-2 residual).
2. Each restart resets the static sweep cursor: `cycle_complete=0` always,
   cursor at 20022→24897 of 34397 after ~7 min of one search
   (~500-2800 classes/pass, ~1 pass/min ⇒ 15-60 min/lap uninterrupted).
3. ProfileAnalyzer (app class, HIGH class index — machinery loads first)
   is never swept before the next restart ⇒ LEAK_BUFFER's
   UnmodifiableRandomAccessList wrapper is never admitted root-attached
   static ⇒ neither the collector cohort NOR the at-risk FIFO can ever
   select it (it has no frontier entry at all).
4. The 2 wrapper instances walked (tags 5999, 9519) are OTHER unmodifiable
   lists (their walks found no tagged chunks — no intercept lines).

## Suspected restart driver (candidate, not yet caught in a log window)

TEMP `CANARY_NO_PROGRESS_PASS_LIMIT` 30→3 (deployed to the pod, on the
MUST-REVERT list): unfound canary ⇒ abandon+restart after only ~3 passes
≈ 3 min at the observed ~1 pass/min — matches the observed restart
cadence. Also unfound-candidate no-progress abandons during the 0/0
flaps. The exact abandon REASON line has not been captured yet (1-min log
retention; the transition is a rare line).

## Secondary findings

- FIFO-first drain order starves the collector suffix on truncated
  passes — the LEAK wrapper (single-referrer static ⇒ collector cohort,
  never at-risk) would be in the starved suffix whenever it IS admitted.
- At-risk population ≈ 1024 (cap) — the design's "push-rate ≪ drain-rate
  needs the filter" caveat is now MEASURED: pushes 15-30x the drain rate.
