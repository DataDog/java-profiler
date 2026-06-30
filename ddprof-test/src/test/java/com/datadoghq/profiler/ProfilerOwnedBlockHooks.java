/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

/** Test bridge for package-scoped owned blocking hooks. */
public final class ProfilerOwnedBlockHooks {
    private ProfilerOwnedBlockHooks() {}

    public static void parkEnter(JavaProfiler profiler) {
        profiler.parkEnter();
    }

    public static void parkExit(JavaProfiler profiler, long blocker, long unblockingSpanId) {
        profiler.parkExit(blocker, unblockingSpanId);
    }

    public static long blockEnter(JavaProfiler profiler, int state) {
        return profiler.blockEnter(state);
    }

    public static void blockExit(JavaProfiler profiler, long token) {
        profiler.blockExit(token);
    }
}
