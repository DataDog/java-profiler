/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.NativeBuildConfig;

/**
 * DEBUG-only observations of the existing worker slot, without seeding state or allocating
 * identity. Release tests use decoded target-worker JFR evidence for readiness instead.
 */
final class WallClockBlockTrackerTestSupport {
  private WallClockBlockTrackerTestSupport() {}

  static boolean available() {
    return NativeBuildConfig.isDebugInstrumented();
  }

  static int currentTid() {
    return available() ? currentTid0() : -1;
  }

  static long pendingUnownedWeight(int tid) {
    return available() ? pendingUnownedWeight0(tid) : -1;
  }

  static long maxPendingUnownedSegmentWeight(int tid) {
    return available() ? maxPendingUnownedSegmentWeight0(tid) : -1;
  }

  private static native long maxPendingUnownedSegmentWeight0(int tid);

  static boolean hasActiveOwnedBlock(int tid) {
    return available() && hasActiveOwnedBlock0(tid);
  }

  private static native boolean hasActiveOwnedBlock0(int tid);

  private static native int currentTid0();

  private static native long pendingUnownedWeight0(int tid);
}
