/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

/**
 * Test bridge for {@link JavaProfiler}'s package-private wall-clock test seams (same pattern as
 * {@link ReferenceChainTestHooks}). The seams mutate or inspect the process-wide profiler
 * singleton's state, so they stay non-public in the shipped library; tests in other packages reach
 * them only through this class. All are debug-native-build only; in release builds the setter is a
 * no-op and the accessors return {@code false}.
 */
public final class JavaProfilerTestSupport {
  private JavaProfilerTestSupport() {}

  /** Forces the next wall-clock engine start() call to fail (debug builds only). */
  public static void setForceWallStartFailureForTest(boolean force) {
    JavaProfiler.setForceWallStartFailureForTest0(force);
  }

  /**
   * Whether the forced wall-engine start-failure toggle is currently armed. Returns {@code false}
   * in release builds (where the setter is a no-op), so callers can self-skip via {@code
   * Assumptions.assumeTrue}.
   */
  public static boolean isForceWallStartFailureArmedForTest() {
    return JavaProfiler.isForceWallStartFailureArmedForTest0();
  }

  /**
   * Whether the thread registry currently admits new registrations. Returns {@code false} in
   * release builds; gate on {@link #isForceWallStartFailureArmedForTest()}.
   */
  public static boolean isThreadRegistryActiveForTest() {
    return JavaProfiler.isThreadRegistryActiveForTest0();
  }

  /**
   * Records a blocked sample and its deferred tail through the native wall precheck path, inserting
   * a real JFR dump at the selected boundary. Debug builds only.
   *
   * @param snapshot path receiving the chunk before the deferred tail
   * @param dumpAfterPrimary whether to dump after the primary recording transaction; otherwise dump
   *     between tail preparation and recording
   * @param resetBeforeTail whether to reset the cached state after tail preparation
   * @return whether both primary samples were recorded and the dump succeeded; always {@code false}
   *     outside debug builds
   */
  public static boolean recordUnownedWallTailAcrossDumpForTest(
      String snapshot, boolean dumpAfterPrimary, boolean resetBeforeTail) {
    return JavaProfiler.recordUnownedWallTailAcrossDumpForTest0(
        Thread.currentThread(), snapshot, dumpAfterPrimary, resetBeforeTail);
  }
}
