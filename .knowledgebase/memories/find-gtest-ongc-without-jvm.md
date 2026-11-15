---
id: find-gtest-ongc-without-jvm
title: LivenessTracker::onGC() records heap-floor samples in gtest without a JVM
kind: finding
tags: [gtest, liveness, test-infra]
applies_to: []
source: feedback-1/find-gtest-ongc-without-jvm
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# LivenessTracker::onGC() records heap-floor samples in gtest without a JVM

## Reasoning chain
With no JVM, HeapUsage::get(false) leaves _used at its default (size_t)-1 (vmStructs.cpp:1120ff,
_collected_heap_addr == NULL), isLastGCUsageSupported() is false, so onGC() stores it into
_used_after_last_gc and resolvePostGcHeapUsage() returns SIZE_MAX > 0 -> recordHeapFloorSample runs.
So onGC()'s container branch is directly drivable from a test once _initialized and _gc_generations are set
(needs _heap_floor_recording_disabled_for_test false in DEBUG builds).

## Evidence
- OnGCSkipsContainerUsageUntilLimitResolved passes and fill advances by 1 per onGC().

## What this rules out
- Needing a mock JVM / HeapUsage seam to test onGC() heap-floor recording.
