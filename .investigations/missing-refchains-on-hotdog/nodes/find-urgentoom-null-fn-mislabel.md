---
id: find-urgentoom-null-fn-mislabel
type: root-cause
status: confirmed
depends_on: []
related: [find-test-seam-aliasing, find-wrapper-demotion-self-parent]
tags: [root-cause, test-seams, autoTuneDefaults, GetAvailableProcessors, gtest, mislabel-lesson, NEW-THIS-SESSION]
created: 20260916
updated: 20260916
---

# Find: UrgentOOM SIGSEGV — a null-fn test-mock gap mislabeled "pre-existing" for 5 weeks (round 16)

Parent: none (test-infrastructure root cause; discovered during round-16
verification). Evidence: the stash-run logs (HEAD repro) + the fix commit
4afe870a2; the correction is also recorded in STATE.md's Corrections
section.

## The defect

`ReferenceChainTracker::autoTuneDefaults()` (added facdc70c0,
2026-08-17) calls `jvmti->GetAvailableProcessors()` from `start()`
whenever LivenessTracker reports a max heap > 0. The
`SearchRestartTest` fixture (5adb32831, 2026-08-12 — 5 days EARLIER)
wires only SetEventNotificationMode/GetLoadedClasses/FollowReferences/
IterateOverReachableObjects — GetAvailableProcessors stayed a null table
entry. `UrgentOOMProjectionBypassesCandidateGate` is the only test in
the file that sets a max-heap (that is its subject), so it null-crashed
at `tracker->start(args)` — **before its subject ever executed** — on
every full-suite run for 5 weeks. Its actual subject (OOM-urgency
bypass of the candidate gate) was correct the whole time: fixed by
wiring `mock_GetAvailableProcessors` (fixed 1, deterministic auto-tune),
the test passes and `:ddprof-lib:gtestRelease` is green with NO
exclusions for the first time since 2026-08-17.

## The mislabel, and the lesson it teaches

Round notes recorded this crash as "pre-existing gtest SIGSEGV on clean
HEAD — separate issue" and deferred it for multiple rounds. "Clean
HEAD" was this investigation branch's own tip — every commit on it is
investigation work. The only thing the repro ever proved was "not from
today's diff". Bisect (git log -S) found both introducing commits in
minutes: the test 2026-08-12, the null call 2026-08-17 — OUR regression,
exactly the crash class I had just root-caused an hour earlier in the
same file (a minimal-mock fixture + production code adding a new JVMTI
call = null function pointer; the same class struck twice in one day:
the at-risk-FIFO residue crashed `WithoutGenerationsSignalRestart\ 
StaysUnconditional` through the reset() seam gap below).

LESSONS (both recorded in STATE.md Corrections):
1. "Reproduces on HEAD" proves "not from today's diff" — nothing more.
   Bisect to the introducing commit before calling anything
   pre-existing.
2. A crashing test is never "separate debt" — it is LOST SIGNAL. This
   one carried a valid assertion (the urgency bypass) that went
   unverified for 5 weeks while the suite crashed past it.

## The sibling seam gap (fixed the same round)

The new quota test's saturated-FIFO residue crashed the NEXT fixture's
`runPass` (null GetObjectsWithTags in SearchRestartTest's minimal
mock): the `reset()` test seam predates the B' at-risk FIFO and was
never given its clears (nor the round-15 fresh queue) — prior tests
survived only because later tests' own runPasses drained the residue
with the full Bfs mock. reset() now clears FIFO + set + klass counts +
counters + fresh queue; the quota test also drains its saturation.
Same family as find-test-seam-aliasing (singleton state leaking across
tests) — but inverted: there a stale mark reordered selection, here a
missing clear let state OUTLIVE the test that created it.
