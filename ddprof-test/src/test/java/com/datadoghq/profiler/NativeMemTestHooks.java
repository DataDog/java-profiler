/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

/** Test bridge for the package-scoped native-memory counter refresh seam. */
public final class NativeMemTestHooks {
    private NativeMemTestHooks() {}

    public static void refreshNativeMemCounters() {
        JavaProfiler.refreshNativeMemCounters0();
    }
}
