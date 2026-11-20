/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

/** Exposes package-scoped owned-block hooks to the wall-clock overhead benchmark. */
public final class WallClockPrecheckBenchmarkHooks {
  private WallClockPrecheckBenchmarkHooks() {}

  /** Marks the current benchmark worker as entering an owned sleeping interval. */
  public static long enterSleeping(JavaProfiler profiler) {
    return profiler.blockEnter(7);
  }

  /** Closes an interval returned by {@link #enterSleeping(JavaProfiler)}. */
  public static void exit(JavaProfiler profiler, long token) {
    profiler.blockExit(token);
  }
}
