---
id: find-java-tests-short-circuit
title: Java integration tests relied on the removed hasLeakSignal() short-circuit (Bits P1, fixed)
kind: finding
tags: [java-tests, ddprof-test, gate-contract, pr-921]
applies_to: [ddprof-test/src/test/java/com/datadoghq/profiler/referencechains/]
source: writing-any-code-thoroughly/find-java-tests-short-circuit
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Java integration tests relied on the removed hasLeakSignal() short-circuit (Bits P1, fixed)

## Reasoning chain
Bits Code Review P1 on PR #921 (comment r4411744857) - verified against the code:

1. AggressiveLeakReferenceChainTest.shouldOpenSearchGateOnAggressiveHeapWideGrowthWithNoLeakCandidate
   asserted the PRE-FIX behavior verbatim: BFS thread runs passes from the
   urgent projection alone with zero per-klass candidates. Fix A forbids this ->
   the test would fail.
2. ReferenceChainTrackingTest.shouldReportAbandonedSearchOnTinyFrontierCap
   already seeds its qualifying candidate (SEED_EPOCHS_FOR_HYSTERESIS) - but only
   in debug builds (all ReferenceChainTestHooks seams are debug-only no-ops,
   ReferenceChainTestHooks.java header). On release builds the test passed ONLY
   via the removed short-circuit; post-fix, no candidate -> search idle -> no
   abandonment event -> fail.

## Fix (commit 11c9502c0)
- AggressiveLeak test INVERTED into the idle regression guard
  (shouldNotOpenSearchGateOnAggressiveHeapWideGrowthWithNoLeakCandidate): leak
  signal armed + heapFloorRising precondition + gate stays closed, asserted on
  the live BFS thread (5s quiet window) and via a direct shouldRunPassForTest0()
  call - race-free now that _urgent_search_spent no longer makes the gate's
  answer order-dependent.
- Abandonment test: assumeTrue(isDebugInstrumentedBuild()) - in release the
  search correctly stays idle without a candidate; abandonment coverage rides
  the debug run. Stale "hasLeakSignal() returns true without any population
  trend" profiler-command comment and the class javadoc's "_gc_generations
  gated" note corrected.

## Evidence
- testDebug -Ptests=AggressiveLeakReferenceChainTest: 3/3 pass (2026-10-29)
- testSlowDebug -Ptests=ReferenceChainTrackingTest: 4/4 pass (2026-10-29)

## Notes
- The sphinx review's round-1 HIGH flagged the ReferenceChainTrackingTest side
  but it never surfaced as a final finding; the Bits bot caught what the review
  wave dropped. Sphinx round coverage is not exhaustive on ddprof-test.
