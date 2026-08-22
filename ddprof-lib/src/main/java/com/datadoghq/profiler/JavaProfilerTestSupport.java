/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler;

/**
 * Whitebox testing hooks for {@link JavaProfiler} internals. Kept in a separate
 * class so these do not appear on JavaProfiler's public API surface.
 */
public final class JavaProfilerTestSupport {
    private JavaProfilerTestSupport() {}

    /**
     * Test-only hook (debug builds only): forces the next wall-clock engine
     * start() call to fail. No-op in release builds. For whitebox testing.
     */
    public static void setForceWallStartFailureForTest(boolean force) {
        setForceWallStartFailureForTest0(force);
    }

    /**
     * Test-only accessor: whether the thread registry currently admits new
     * registrations. For whitebox testing.
     */
    public static boolean isThreadRegistryActiveForTest() {
        return isThreadRegistryActiveForTest0();
    }

    private static native void setForceWallStartFailureForTest0(boolean force);

    private static native boolean isThreadRegistryActiveForTest0();
}
