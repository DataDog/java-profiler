---
id: find-admission-boost-implementation
type: finding
status: implemented
depends_on: [find-default-live-samples-ratio-lottery, find-canary-lane-backoff-design]
related: [q-togcroot-acceptance-paths, find-per-tid-qualification-design]
tags: [fix, design, livenessTracker, admission, work-scaled, NEW-THIS-SESSION]
created: 20260901
updated: 20260901
---

# Chase-phase admission boost (user option A): raise tracking probability once a leak is detected, or under urgency

## The design (user-picked from A/B/C)

`LivenessTracker::admitForTracking(tid)` is track()'s new admission
gate. Two raises over the configured _live_samples_ratio (default 10%):

1. Watched tids - selectLeakCandidates()'s qualifying_tids (at most 8)
   published by noteSelectedCandidates() from RCT's FULL poll
   (pollWatchedTargets()); admitted at 100%. Bounded by the candidate
   threads' own allocation rate, so tracking-table volume scales with
   the leak's threads, not the process. Refreshed and CLEARED poll by
   poll (zero-candidate polls clear it - a stale watched tid would
   100%-admit an unrelated thread across OS tid reuse). NOT called from
   hasLeakSignal()'s max=1 probe (partial view could drop other active
   candidates' tids).
2. Urgency - setUrgentTracking(urgent) called every threadLoop()
   iteration next to _oom_ramp_active, so the boost tracks the ramp
   exactly. Admits everything: under the OOM ramp maximizing last-
   chapter capture outweighs table volume. Transition-only TEST_LOG.

Fail-open by construction: boosts only add admissions. Two-phase
count+array publish with RELEASE/ACQUIRE per the project's arm64
ordering rule. Boosted admissions skip the RNG draw. Cleared on
fresh start(). Rejected alternatives: global-only raise (10x table
cost for the whole process during the entire chase) and klass-scoped
via jclass (GC-move-unsafe pointer identity; IsSameObject on the
reject path is not free; per-tid already covers tagLeakInstances()'
exact tagging scope).

## The user's scope correction (accepted, important)

Detection is NOT compromised by the default 10% at any ratio: the
subsample scales the signal, it does not gate it. A leak that fills a
large part of the heap leaves a proportional tracked population and a
positive trend every epoch - detection fires as surely as at 100%.
The 10% residue on detection is LATENCY only (spotty per-epoch counts
on slow small-rate leaks delay hysteresis clearing). A cohort small
enough for the lottery to zero it out is too small for ANY machinery
to act on early (per-tid bar 8, trend hysteresis would rank it
nowhere) - the local test's artificial small cohort, not a production
shape. Division of labor: default ratio bounds steady-state cost;
detection stays asymptotically certain; the boost restores 100%
fidelity exactly for the chase phase where fidelity matters.

## Verification

- 4 gtests (AdmissionBoostTest, livenessTracker_ut.cpp): watched-tid
  admitted despite ratio 0 (RNG reset via admissionResetForTest makes
  the fall-through reject deterministic - fresh mt19937 default seed's
  first draw is strictly in (0,1)); urgency admits all + releases;
  dedupe + cap at MAX_QUALIFYING_TIDS=8 in candidate order;
  zero-candidate poll clears. 550 gtests green.
- Slow suite: boost engaged in children (noteSelectedCandidates watched
  tid lines; scenario tid published), leak-correlation + UnboundedCache
  green; ToGcRoot failed with the IDENTICAL pre-boost signature - the
  known q-togcroot-acceptance-paths family, not a regression (suite
  tests run :l:1.0 so admission was already 100%).
- Doc: ReferenceChains-SignalsExplained.md section 5 extended (the
  leak-signal also raises tracking fidelity; urgency raises admission
  to 100%).

## Code landmarks

admitForTracking()/noteSelectedCandidates()/setUrgentTracking() decls
+ _watched_tids/_watched_tid_count/_urgent_tracking fields in
livenessTracker.h (fields next to _subsample_ratio); implementations
in livenessTracker.cpp near releaseThreadLocalState; track() gate
replaces the inline RNG block; RCT call sites: threadLoop (~_oom_ramp_active
store, setUrgentTracking next to it) and pollWatchedTargets (right
after selectLeakCandidates). ForTest seams: admitForTrackingForTest,
setSubsampleRatioForTest, admissionResetForTest (cpp - clears TLS RNG),
watchedTidCountForTest, watchedTidForTest.
