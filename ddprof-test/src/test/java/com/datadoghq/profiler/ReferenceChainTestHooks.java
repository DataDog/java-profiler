/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

/**
 * Test bridge for {@link JavaProfiler}'s package-private reference-chain / liveness test seams
 * (same pattern as {@link ProfilerOwnedBlockHooks}). The seams mutate the process-wide profiler
 * singleton's state, so they stay non-public in the shipped library; tests in other packages
 * reach them only through this class. All are debug-native-build only, no-ops in release builds.
 */
public final class ReferenceChainTestHooks {
    private ReferenceChainTestHooks() {}

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

    public static void setReferenceChainPassSpacingForTest0(long msSinceLastPass, long cadenceMs) {
        JavaProfiler.setReferenceChainPassSpacingForTest0(msSinceLastPass, cadenceMs);
    }

    public static void shiftReferenceChainLastGcEpochForTest0(long delta) {
        JavaProfiler.shiftReferenceChainLastGcEpochForTest0(delta);
    }

    public static void setReferenceChainRootEnumStateForTest0(long msSinceLastEnum, long lastEnumCostMs) {
        JavaProfiler.setReferenceChainRootEnumStateForTest0(msSinceLastEnum, lastEnumCostMs);
    }

    public static boolean shouldRunRootEnumForTest0(boolean manualFirstPass) {
        return JavaProfiler.shouldRunRootEnumForTest0(manualFirstPass);
    }

    public static long rootEnumIntervalFloorNsForTest0() {
        return JavaProfiler.rootEnumIntervalFloorNsForTest0();
    }

    public static long referenceChainGcFinishEpochForTest0() {
        return JavaProfiler.referenceChainGcFinishEpochForTest0();
    }

    public static void forceRunningReferenceChainSearchForTest0() {
        JavaProfiler.forceRunningReferenceChainSearchForTest0();
    }

    public static void setReferenceChainCanaryStateForTest0(int candidateCount, long foundBits) {
        JavaProfiler.setReferenceChainCanaryStateForTest0(candidateCount, foundBits);
    }

    public static void pollReferenceChainTargets0() {
        JavaProfiler.pollReferenceChainTargets0();
    }

    public static int drainReferenceChainEventCount0() {
        return JavaProfiler.drainReferenceChainEventCount0();
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
     * disabled - the native seam asserts when called while recording is enabled.
     */
    public static void heapFloorResetForTest0() {
        JavaProfiler.heapFloorResetForTest0();
    }

    /**
     * Reports whether the seeded heap-floor ring currently shows a sustained rise
     * ({@code heapFloorRising()}). {@code false} before any seeding and after
     * {@link #heapFloorResetForTest0()} emptied the ring.
     */
    public static boolean heapFloorRisingForTest0() {
        return JavaProfiler.heapFloorRisingForTest0();
    }

    /** Not a pure predicate - see {@link JavaProfiler}'s own {@code shouldRunPassForTest0()} doc. */
    public static boolean shouldRunPassForTest0() {
        return JavaProfiler.shouldRunPassForTest0();
    }

    public static int referenceChainPassesRunForTest0() {
        return JavaProfiler.referenceChainPassesRunForTest0();
    }

    /**
     * Backdates the leak-signal burn-in stamp (debug native builds only; see JavaProfiler).
     * Returns the previous stamp for {@link #setLeakSignalActivatedNsForTest0(long)}.
     */
    public static long backdateLeakSignalActivationForTest0() {
        return JavaProfiler.backdateLeakSignalActivationForTest0();
    }

    /** Restores a saved leak-signal burn-in stamp (debug native builds only; see JavaProfiler). */
    public static void setLeakSignalActivatedNsForTest0(long activatedNs) {
        JavaProfiler.setLeakSignalActivatedNsForTest0(activatedNs);
    }

    /** The current {@code secondsToOOM()} projection (debug native builds only; see JavaProfiler). */
    public static double secondsToOOMForTest0() {
        return JavaProfiler.secondsToOOMForTest0();
    }

    /** The OOM-urgency latch (debug native builds only; see JavaProfiler). */
    public static boolean urgentLatchedForTest0() {
        return JavaProfiler.urgentLatchedForTest0();
    }
}
