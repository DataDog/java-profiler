---
id: ongc-testable-without-jvm
title: LivenessTracker::onGC() records heap-floor samples in gtest without a JVM; container-usage tests must resolve the limit first
kind: finding
tags: [gtest, liveness, cgroup, testing]
applies_to: [ddprof-lib/src/main/cpp/os_linux.cpp, ddprof-lib/src/test/cpp/livenessTracker_ut.cpp]
source: feedback-1/find-gtest-ongc-without-jvm
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---


With no JVM, `HeapUsage::get(false)` leaves `_used` at `(size_t)-1`, so `resolvePostGcHeapUsage()`
returns a positive value and `onGC()` reaches `recordHeapFloorSample`. `onGC()`'s container
branch is therefore drivable from a plain gtest once `_initialized` and `_gc_generations` are set
and `_heap_floor_recording_disabled_for_test` is false. No mock JVM or HeapUsage seam is needed.

`OS::getContainerMemoryUsage()` returns -1 until the first `OS::getContainerMemoryLimit()` call has
picked the usage file (os_linux.cpp, resolved once). A test asserting on recorded container usage
must call `getContainerMemoryLimit()` first; otherwise it passes vacuously on Linux too.
