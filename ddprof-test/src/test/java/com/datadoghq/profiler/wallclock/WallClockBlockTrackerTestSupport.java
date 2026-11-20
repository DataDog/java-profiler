/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.NativeBuildConfig;

/**
 * Read-only observations of the existing worker slot, without seeding state or allocating identity.
 * The tid and pending-weight reads work in every build; the registry and owned-block observations
 * are DEBUG-only.
 */
final class WallClockBlockTrackerTestSupport {
  private WallClockBlockTrackerTestSupport() {}

  /** Whether the DEBUG-only registry and owned-block observations are compiled in. */
  static boolean available() {
    return NativeBuildConfig.isDebugInstrumented();
  }

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

  /** Observes the target native thread's existing registry entry; false in release. */
  static boolean hasRegistryEntry(int tid) {
    return available() && hasRegistryEntry0(tid);
  }

  private static native boolean hasRegistryEntry0(int tid);

  static boolean hasActiveOwnedBlock(int tid) {
    return available() && hasActiveOwnedBlock0(tid);
  }

  private static native boolean hasActiveOwnedBlock0(int tid);

  /** Reads a blocked native owner's identity even when its recording projection is stale. */
  static NativeOwnerSnapshot nativeOwnerSnapshot(int tid) {
    long[] values = nativeOwnerSnapshot0(tid);
    if (values == null) throw new AssertionError("missing retained native identity for tid " + tid);
    return new NativeOwnerSnapshot(values);
  }

  /** The caller holds the target in a kernel wait; these fields do not form a general snapshot. */
  static final class NativeOwnerSnapshot {
    final long slotId;
    final long lifecycleGeneration;
    final long recordingEpoch;
    final long blockGeneration;
    final long currentRecordingEpoch;

    private NativeOwnerSnapshot(long[] values) {
      slotId = values[0];
      lifecycleGeneration = values[1];
      recordingEpoch = values[2];
      blockGeneration = values[3];
      currentRecordingEpoch = values[4];
    }
  }

  private static native long[] nativeOwnerSnapshot0(int tid);

  private static native int currentTid0();

  private static native long pendingUnownedWeight0(int tid);
}
