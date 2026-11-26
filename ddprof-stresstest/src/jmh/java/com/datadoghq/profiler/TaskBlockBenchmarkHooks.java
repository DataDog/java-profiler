/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

/**
 * Exposes the package-private park hooks to the TaskBlock benchmarks. dd-trace-java calls the same
 * {@link JavaProfiler#parkEnter()} and {@link JavaProfiler#parkExit(long, long)} pair around {@code
 * LockSupport.park}.
 */
public final class TaskBlockBenchmarkHooks {
  private TaskBlockBenchmarkHooks() {}

  /** Calls {@link JavaProfiler#parkEnter()}; {@code true} means the caller must call exit. */
  public static boolean parkEnter(JavaProfiler profiler) {
    return profiler.parkEnter();
  }

  /** Calls {@link JavaProfiler#parkExit(long, long)} without a blocker or unblocking span. */
  public static void parkExit(JavaProfiler profiler) {
    profiler.parkExit(0, 0);
  }
}
