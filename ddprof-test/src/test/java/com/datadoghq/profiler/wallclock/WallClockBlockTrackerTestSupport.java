/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

/**
 * Read-only observations of the existing worker slot, without seeding state or allocating identity.
 * Works in every build.
 */
final class WallClockBlockTrackerTestSupport {
  private WallClockBlockTrackerTestSupport() {}

  static int currentTid() {
    return currentTid0();
  }

  /** Aggregate pending unowned weight of tid's slot in this recording; 0 without an entry. */
  static long pendingUnownedWeight(int tid) {
    return pendingUnownedWeight0(tid);
  }

  /** Largest single-epoch pending segment of tid's slot; 0 without an entry. */
  static long maxPendingUnownedSegmentWeight(int tid) {
    return maxPendingUnownedSegmentWeight0(tid);
  }

  private static native long maxPendingUnownedSegmentWeight0(int tid);

  private static native int currentTid0();

  private static native long pendingUnownedWeight0(int tid);
}
