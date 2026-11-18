---
id: find-test-order-offline-incompatible
title: test-order offline instrumentation cannot see ddprof-lib; online mode required
kind: finding
tags: [build, test-order, tooling, instrumentation]
applies_to: []
source: writing-any-code-thoroughly/find-test-order-offline-incompatible
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# test-order offline instrumentation cannot see ddprof-lib; online mode required

test-order's default `offline` instrumentation instruments only the project's
own `main` source-set output (first dir of `mainSourceSet.output.classesDirs`).
For `ddprof-test` that is the trivial `unwinding.*` app classes (9 classes);
ddprof-lib's classes — the actual code under test, compiled in another project —
are never instrumented, and neither are the test classes. Result: usage bitsets
stay all-zero, `handleBinaryPayload` merges nothing, `stopAndMerge` returns 0,
and no dependency index is ever written (verified: learn runs with the index
file absent and "No deps directory ... skipping aggregation" in logs).
Fix: `testOrder { instrumentation.set("online") }` in ddprof-test — the
`-javaagent` agent instruments classes as the JVM loads them, covering
cross-project classes. Verified: online learn wrote `.test-order/
test-dependencies.lz4` (15 tests for one package batch; 90 tests for a full
suite).

## Evidence
- `strings ddprof-test/build/.test-order/class-id-map.bin` showed only
  `com.datadoghq.profiler.unwinding.*` entries (the 9 instrumented classes).
- IndexCollectorServer logs "v2 payload received but no ClassIdMapping loaded"
  then NACKs; the string-fallback carried real data only in online mode.

## What this rules out
- Using test-order as documented (offline default) in any multi-project layout
  where the code under test lives outside the test project.
