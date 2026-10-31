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
     * Test-only accessor: whether the forced wall-engine start-failure toggle is
     * currently armed. Returns {@code false} in release builds (where the setter
     * is a no-op), so callers can self-skip via {@code Assumptions.assumeTrue}.
     * For whitebox testing.
     */
    public static boolean isForceWallStartFailureArmedForTest() {
        return isForceWallStartFailureArmedForTest0();
    }

    /**
     * Test-only accessor: whether the thread registry currently admits new
     * registrations. For whitebox testing.
     */
    public static boolean isThreadRegistryActiveForTest() {
        return isThreadRegistryActiveForTest0();
    }

    /**
     * Records a blocked sample and its deferred tail through the native wall precheck path,
     * inserting a real JFR dump at the selected boundary. Debug builds only.
     *
     * @param snapshot path receiving the chunk before the deferred tail
     * @param beforePublication whether to dump between primary recording and precheck completion;
     *     otherwise dump between tail preparation and recording
     * @param resetBeforeTail whether to reset the cached state after tail preparation
     * @return whether both primary samples were recorded and the dump succeeded;
     *     always {@code false} outside debug builds
     */
    public static boolean recordUnownedWallTailAcrossDumpForTest(
            String snapshot, boolean beforePublication, boolean resetBeforeTail) {
        return recordUnownedWallTailAcrossDumpForTest0(
                Thread.currentThread(), snapshot, beforePublication, resetBeforeTail);
    }

    private static native void setForceWallStartFailureForTest0(boolean force);

    private static native boolean isForceWallStartFailureArmedForTest0();

    private static native boolean isThreadRegistryActiveForTest0();

    private static native boolean recordUnownedWallTailAcrossDumpForTest0(
            Thread thread, String snapshot, boolean beforePublication, boolean resetBeforeTail);
}
