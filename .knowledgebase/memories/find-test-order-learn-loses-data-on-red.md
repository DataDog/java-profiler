---
id: find-test-order-learn-loses-data-on-red
title: Upstream test-order discards learned index when the test run fails
kind: finding
tags: [build, test-order, tooling, patch]
applies_to: [build-logic/**, doc/building/TestingGuide.md]
source: writing-any-code-thoroughly/find-test-order-learn-loses-data-on-red
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Upstream test-order discards learned index when the test run fails

Upstream v0.1.1 wires index aggregation into `testTask.doLast("aggregateDeps")`
— `doLast` never runs when the task fails, and the in-daemon
`IndexCollectorServer` is dropped without merging, so a red suite can never
complete learn mode (the local suite is deterministically red on this Mac:
NativeThreadTest[3], DynamicNativeThread[3], VtableReceiverFrameTest[5]).
Patched the mavenLocal plugin: also `testTask.finalizedBy("testOrderOfflineRestore")`
in the online learn configuration — the shared restore task drains every
project collector via `stopAndMerge`, persisting the index despite failures.
Verified: red cpu-batch run still wrote the index ("merged 14 test classes via
socket"); full-suite learn with 3 reds wrote all 90 test classes.

## Evidence
- `TestOrderPlugin.java:888` (doLast aggregateDeps) and the `close()` doc
  "Stop the server without merging (e.g., on build failure)".
- Post-patch logs at 18:23 and 18:33: index written on FAILED runs.

## What this rules out
- deadend-batched-learn-runs — batching learn over green subsets is
  unnecessary once the finalizer patch is in place.
