---
id: find-fix-leak-signal-gate
title: Fix implemented: leak-signal gate keys on an effective flag (generations OR liveheap); no signal -> collector idle
kind: finding
tags: [reference-chains, fix, gating, tests]
applies_to: [ddprof-lib/src/main/cpp/livenessTracker.h, ddprof-lib/src/main/cpp/livenessTracker.cpp, ddprof-lib/src/main/cpp/referenceChainEvents.cpp]
source: writing-any-code-thoroughly/find-fix-leak-signal-gate
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Fix implemented: leak-signal gate keys on an effective flag (generations OR liveheap); no signal -> collector idle

## Reasoning chain
Scope confirmed with the operator (refchain gating only; malloc/pool filed as
PROF-16366, untouched). New contract: the population-trend signal is
constructible when generations tracking OR liveheap tracking is on; with
neither, hasLeakSignal() returns FALSE and the collector never searches (no
first pass, no restart). This replaces the old "no signal -> always search"
fallback.

Changes (worktree java-profiler-investigate-reference-chains, uncommitted as of
2026-10-28):
- livenessTracker.h: new `std::atomic<bool> _leak_signal_enabled` +
  `leakSignalEnabled()` accessor; set in initialize() =
  args._gc_generations || args._record_liveness; cleared in resetSession();
  setGcGenerationsForTest() mirrors both.
- livenessTracker.cpp: the five signal-machinery gates
  (cleanup_table population accumulation + foldKlassCountsLocked,
  secondsToOOM, maybeForceCleanup, onGC heap-floor ring) switched from
  _gc_generations to the effective flag; comments updated.
- referenceChains.cpp: hasLeakSignal() no-signal branch -> return false.
- referenceChainEvents.cpp: pollWatchedTargets() uses the same effective gate
  (a liveheap-sourced search still gets candidates polled).
- Tests: new ReferenceChainsBfsTest.NoSearchWithoutLeakSignalSource;
  WithoutGenerationsSignalRestartStaysUnconditional inverted to
  WithoutLeakSignalSourceRestartStaysIdle; two recording-boundary tests arm
  the signal AND seed a growing candidate for the restart step (the gate
  requires both).
- Docs: ReferenceChainsSignalsExplained.md (Starting a search),
  LiveHeapReferenceChainsImplementation.md (Configuration),
  ReferenceChainsCollectionSummary.md (Purpose) updated.

Verification: gtestDebug_livenessTracker_ut + gtestDebug_referenceChains_ut
266 OK / 0 FAILED; full :ddprof-lib:gtestDebug 1016 OK / 0 FAILED.

## Evidence
- Test logs under build/logs/20261028-17*.
- Gate behavior observed in test output: "hasLeakSignal -> false
  (secondsToOOM=-1.0, candidates=0, urgent=0)" with signal armed but no
  seeded candidates.

## Open questions
- Two small livenessTracker_ut additions (LeakSignalRequiresGenerationsOrLiveness,
  LeakSignalArmedByEffectiveFlag) only pin the test-seam mirroring; the real
  gate coverage lives in referenceChains_ut. Acceptable; noted for honesty.
