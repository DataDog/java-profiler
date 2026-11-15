---
id: find-lifecycle-hardening
title: AbstractProfilerTest lifecycle hardened; cascade eliminated
kind: finding
tags: [tests, lifecycle, hardening]
applies_to: [ddprof-test/src/test/java/com/datadoghq/profiler/AbstractProfilerTest.java]
source: writing-any-code-thoroughly/find-lifecycle-hardening
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# AbstractProfilerTest lifecycle hardened; cascade eliminated

Two changes, each with a fail-before/pass-after regression test:
1. `cleanup()` runs `stopProfiler()` in a `finally` around `after()` — a
   throwing `after()` can no longer leak the started singleton.
2. `setupProfiler()` recovers once from `IllegalStateException` on
   `profiler.execute(command)`: `profiler.stop()` (secondary failures caught
   and attached as suppressed) then retry — one poisoned test no longer
   cascades.
`stopped` relaxed to package-private so `ProfilerTeardownIntegrityTest` can
resync it after restarting the profiler behind `stopProfiler()`'s back.
Verified: the exact cascade scenario (order mode, prioritized run) went from
55 failures to 4 (the known flaky quartet itself), zero "already started".
Regression tests: ProfilerSetupRecoveryTest (static-init poisons the
singleton; start commands REQUIRE `jfr,file=` — a bare `start,cpu=10ms` throws
"Flight Recorder output file is not specified"), ProfilerTeardownIntegrityTest,
ProfilerSetupRecoveryFailureTest (added by the review-fix round; narrows the
static-init catch to IllegalStateException so other failures fail the test).
