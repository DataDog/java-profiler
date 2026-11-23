/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

/** Test bridge for package-scoped owned blocking hooks. */
public final class ProfilerOwnedBlockHooks {
  private ProfilerOwnedBlockHooks() {}

  public static boolean parkEnter(JavaProfiler profiler) {
    return profiler.parkEnter();
  }

  public static void parkExit(JavaProfiler profiler, long blocker, long unblockingSpanId) {
    profiler.parkExit(blocker, unblockingSpanId);
  }

  public static boolean virtualParkExit(
      JavaProfiler profiler, long elapsedNanos, long blocker, long unblockingSpanId) {
    return profiler.virtualParkExit(elapsedNanos, blocker, unblockingSpanId);
  }

  public static long blockEnter(JavaProfiler profiler, int state) {
    return profiler.blockEnter(state);
  }

  public static void blockExit(JavaProfiler profiler, long token) {
    profiler.blockExit(token, 0, 0);
  }

  public static void blockExit(
      JavaProfiler profiler, long token, long blocker, long unblockingSpanId) {
    profiler.blockExit(token, blocker, unblockingSpanId);
  }

  /** Returns the runtime capability used by the synchronous success-test classes. */
  public static boolean taskBlockSupported(JavaProfiler profiler) {
    return profiler.taskBlockSupportedForTest();
  }

  /** Returns whether the default wall engine tracks unfiltered owners, as park producers need. */
  public static boolean wallRegistryTrackingSupported(JavaProfiler profiler) {
    return profiler.wallRegistryTrackingSupportedForTest();
  }

  /** Returns the native platform-thread classification of the calling thread. */
  public static boolean platformThread(JavaProfiler profiler) {
    return profiler.platformThreadForTest();
  }

  /** Completes the calling thread's block with controlled timestamps in debug native builds. */
  public static boolean endTaskBlockAtTicks(
      long token, long startTicks, long endTicks, long blocker, long unblockingSpanId) {
    return JavaProfiler.endTaskBlockAtTicksForTest0(
        Thread.currentThread(), token, startTicks, endTicks, blocker, unblockingSpanId);
  }

  public static long beginTaskBlockForThread(JavaProfiler profiler, Thread thread) {
    return profiler.beginTaskBlockForThread(thread);
  }

  public static boolean endTaskBlockForThread(
      JavaProfiler profiler, Thread thread, long token, long blocker, long unblockingSpanId) {
    return profiler.endTaskBlockForThread(thread, token, blocker, unblockingSpanId);
  }
}
