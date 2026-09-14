---
id: ev-leaktag-onpod-round11
type: evidence
status: confirmed
depends_on: [ev-leaktag-onpod-round10, find-anchor-live-feed-design]
related: [find-anchor-holder-eviction, find-per-tid-qualification-design, find-togcroot-orphaned-slot-stranding]
tags: [pod-verification, round-11, cycle-complete, collector-cursor, candidate-flap, oom-endgame, NEW-THIS-SESSION]
created: 20260914
updated: 20260914
---

# Pod round 11 (04539b821 = canary-limit revert + collector-first order): sweep laps COMPLETE for the first time; interception still zero; candidate itself flapped out while the heap marches to OOM

Same pod `prof-analyzer-hotdog-jb-d9d8cf-plwpx`, JVM 70341 restarted with the
new build (fresh tracker confirmed: pushed_total reset to ~0 and grew
1945→5035→7719+).

## A (canary limit 30) — WORKED

- Search lifetimes up from round 10's 3-6 min to tens of minutes; pass
  pacing observed via `canary backoff mult=16 ema_ms=171` (~2s/pass) and
  threadLoop cadence ~1s.
- **`cycle_complete=1` observed repeatedly — the static sweep completes
  laps for the first time on this pod** (rounds 3-10 never completed one:
  either pre-cursor-fix truncation or restart-driven resets). Laps now
  wrap in <2 min at high pacing (cursor alternation 0↔30k across 30s
  polls initially misread as restarts — they are LAP WRAPS).
- Consequence: the root-attached static cohort is no longer the
  round-9-sized 76 machinery statics — every swept class's statics are
  admitted (collector picks walk ~4/pass, 69 root_kind=8 anchors walked
  in an 8-min sample).

## B (collector-first order) — no-op in production

Real `GetObjectsWithTags` returns results in UNSPECIFIED order (observed
interspersed parent=0/parent!=0 walk lines) — the walk order is the GOTW
iteration order, not the request-vector order. The round-10 "collector
suffix starvation" model was mock-order-based; in production truncation
drops both cohorts uniformly (~40% of the 20-anchor batch). The requeue
protection still functions (order-independent).

## Interception still zero

Wrapper (`Collections$UnmodifiableRandomAccessList`) never appeared in
walked anchors. It is admitted root-attached STATIC (laps reach
ProfileAnalyzer) and sits in the collector's wrapping-cursor lottery:
4 picks/pass over a now-large cohort, ~40% of picks dropped by truncation
— the wrapper was not reached before the search went terminal.

## NEW: the candidate flapped out while the leak demonstrably grows

At ~20:35: `selectLeakCandidates entry[0] klass_id=4 ring_fill=30
has_trend=1 slope=-47.348387 consecutive_positive=0 required=3` →
0 candidates → search terminal (search_state=2, tags_released=1,
`hasLeakSignal -> false (secondsToOOM=4351.6, candidates=0, urgent=0)`)
— WHILE `secondsToOOM` shows +389MB/280s and the heap at ~4.7GB.
Suspicion (unproven): self-reinforcing dropout — candidate slot drops
(one epoch of negative delta) → admitForTracking's watched-tid boost
clears → the tracked sample thins → negative slope keeps the candidate
out. Tagging had been healthy at scale all along (59 x 78MB chunks,
klass_id=4 tid=70542).

## Next window

OOM endgame: secondsToOOM ~4300s at observation time and shrinking —
when it crosses the urgency threshold, the urgent search opens without a
candidate and urgency tracking tags everything: the interception
machinery gets a fresh window with laps completing. Watch for the
wrapper walk + `leak-tag intercepted` during the urgency phase.
