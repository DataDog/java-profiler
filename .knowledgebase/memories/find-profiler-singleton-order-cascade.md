---
id: find-profiler-singleton-order-cascade
title: Suite has severe order-dependence anchored in the flaky red trio
kind: finding
tags: [tests, flakiness, order-dependence, lifecycle]
applies_to: [ddprof-test/src/test/**]
source: writing-any-code-thoroughly/find-profiler-singleton-order-cascade
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Suite has severe order-dependence anchored in the flaky red trio

When `NativeThreadTest[3]` / `DynamicNativeThread[3]` / `VtableReceiverFrameTest[5]`
fail (deterministically on macOS arm64), the process-wide `JavaProfiler`
singleton is left started — `AbstractProfilerTest.cleanup()` ran `after()`
before `stopProfiler()` with no try/finally, so a throw out of `after()`
skipped the stop. Every later test in the same JVM then fails in
`setupProfiler` with `IllegalStateException: Profiler already started`
(`JavaProfiler.execute0`). In default order the trio runs late (small blast
radius); in reshuffled order (random ordering or test-order prioritization) it
runs first and cascades: one observed run had 55 failures vs the 3-failure
baseline on the identical tree. `JVMAccessTest.testGetFlag` fails intermittently
only in reshuffled runs (expected `build/hs_err_pid%p.log`, got
`/tmp/hs_err_pid%p.log`) — same category, not separately root-caused.

## Evidence
- round-4 verification logs and the 18:33 order-mode run: 55 failures, all
  `Profiler already started` at `AbstractProfilerTest.setupProfiler:244`.
- Post-hardening identical scenario: 4 failures (the quartet itself), zero
  "already started" occurrences.

## What this rules out
- always-on random test ordering (see find-random-order-opt-in).
- Attributing the cascade to test-order's agent — learn agent is not attached
  in order mode; the mechanism is pure shared-singleton state.
