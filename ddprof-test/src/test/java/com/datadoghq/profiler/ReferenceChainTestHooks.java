/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

/**
 * Test bridge for the package-private reference-chain/liveness test seams on {@link JavaProfiler},
 * so tests outside {@code com.datadoghq.profiler} can call them without the seams becoming public
 * API of the shipped jar. The native seams exist only in -DDEBUG builds (debug/asan/tsan); release
 * builds get no-op stubs.
 */
public final class ReferenceChainTestHooks {
    private ReferenceChainTestHooks() {}

    /** The calling thread's profiler tid. Call it on the allocating (leaking) thread. */
    public static int getTid() {
        return JavaProfiler.getTid();
    }

    public static boolean setGcGenerationsEnabled0(boolean enabled) {
        return JavaProfiler.setGcGenerationsEnabled0(enabled);
    }

    public static void seedKlassPopulationSample0(int klassId, int count, long epoch) {
        JavaProfiler.seedKlassPopulationSample0(klassId, count, epoch);
    }

    public static void seedTidTrendSample0(int klassId, int tid, int count, long epoch) {
        JavaProfiler.seedTidTrendSample0(klassId, tid, count, epoch);
    }

    public static void setKlassPopulationRepresentativeForTest0(int klassId, Object representative) {
        JavaProfiler.setKlassPopulationRepresentativeForTest0(klassId, representative);
    }

    public static void resetKlassPopulationForTest0() {
        JavaProfiler.resetKlassPopulationForTest0();
    }

    public static int[] selectLeakCandidateKlassIds0() {
        return JavaProfiler.selectLeakCandidateKlassIds0();
    }

    public static long tagAsReferenceChainRoot0(Object target) {
        return JavaProfiler.tagAsReferenceChainRoot0(target);
    }

    public static boolean runReferenceChainPass0() {
        return JavaProfiler.runReferenceChainPass0();
    }

    public static void pollReferenceChainTargets0() {
        JavaProfiler.pollReferenceChainTargets0();
    }

    public static int drainReferenceChainEventCountForLeaf0(Object leaf) {
        return JavaProfiler.drainReferenceChainEventCountForLeaf0(leaf);
    }

    public static void resetReferenceChainSearchForTest0() {
        JavaProfiler.resetReferenceChainSearchForTest0();
    }

    public static long getReferenceChainPendingPositionForTest0(Object target) {
        return JavaProfiler.getReferenceChainPendingPositionForTest0(target);
    }

    public static long getReferenceChainPendingSizeForTest0() {
        return JavaProfiler.getReferenceChainPendingSizeForTest0();
    }

    public static int getReferenceChainFrontierStateForTest0(Object target) {
        return JavaProfiler.getReferenceChainFrontierStateForTest0(target);
    }

    public static long getReferenceChainResolvedTargetTagForTest0(Object target) {
        return JavaProfiler.getReferenceChainResolvedTargetTagForTest0(target);
    }

    public static void heapFloorRecordForTest0(long usedBytes, long timestampNs) {
        JavaProfiler.heapFloorRecordForTest0(usedBytes, timestampNs);
    }

    public static void setMaxHeapBytesForTest0(long maxHeapBytes) {
        JavaProfiler.setMaxHeapBytesForTest0(maxHeapBytes);
    }

    public static void setHeapFloorRecordingForTest0(boolean enabled) {
        JavaProfiler.setHeapFloorRecordingForTest0(enabled);
    }

    /**
     * Clears the heap-floor ring seeded via {@link #heapFloorRecordForTest0(long, long)} so
     * the next test in the same JVM starts from an empty ring. Call before the
     * {@link #setHeapFloorRecordingForTest0(boolean)} restore, while recording is still
     * disabled, so a real GC cannot interleave a sample with the reset.
     */
    public static void heapFloorResetForTest0() {
        JavaProfiler.heapFloorResetForTest0();
    }

    /**
     * Not a read-only query: under the native engine lock the gate may account a completed
     * search's pain and restart/reset terminal search state.
     */
    public static boolean shouldRunPassForTest0() {
        return JavaProfiler.shouldRunPassForTest0();
    }

    public static int referenceChainPassesRunForTest0() {
        return JavaProfiler.referenceChainPassesRunForTest0();
    }
}
