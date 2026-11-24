/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

/** Exposes package-scoped owned-block hooks to the wall-clock overhead benchmark. */
public final class WallClockPrecheckBenchmarkHooks {
  private WallClockPrecheckBenchmarkHooks() {}

  /** Native {@code OSThreadState::SLEEPING} (ddprof-lib/src/main/cpp/threadState.h). */
  public static final int OSTHREAD_STATE_SLEEPING = 7;

  /** Marks the current benchmark worker as entering an owned sleeping interval. */
  public static long enterSleeping(JavaProfiler profiler) {
    return profiler.blockEnter(OSTHREAD_STATE_SLEEPING);
  }

  /** Closes an interval returned by {@link #enterSleeping(JavaProfiler)}. */
  public static void exit(JavaProfiler profiler, long token) {
    profiler.blockExit(token, 0, 0);
  }
}
