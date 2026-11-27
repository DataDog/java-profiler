/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

/** Test bridge for the package-private hooks of {@link JavaProfilerTestSupport}. */
public final class WallStartFailureTestHooks {
  private WallStartFailureTestHooks() {}

  /** Forces the next wall-clock engine start to fail; a no-op in release builds. */
  public static void setForceWallStartFailure(boolean force) {
    JavaProfilerTestSupport.setForceWallStartFailureForTest(force);
  }

  /** Whether the forced wall-start failure is armed; always {@code false} in release builds. */
  public static boolean isForceWallStartFailureArmed() {
    return JavaProfilerTestSupport.isForceWallStartFailureArmedForTest();
  }

  /** Whether the thread registry currently admits new registrations. */
  public static boolean isThreadRegistryActive() {
    return JavaProfilerTestSupport.isThreadRegistryActiveForTest();
  }
}
