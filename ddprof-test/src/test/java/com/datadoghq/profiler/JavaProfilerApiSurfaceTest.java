/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import org.junit.jupiter.api.Test;

import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class JavaProfilerApiSurfaceTest {
    @Test
    public void taskBlockApiIsPublicButInternalHooksRemainPackageScoped() throws Exception {
        Method parkEnter = JavaProfiler.class.getDeclaredMethod("parkEnter");
        assertNotPublic(parkEnter);
        assertEquals(boolean.class, parkEnter.getReturnType());
        assertNotPublic(JavaProfiler.class.getDeclaredMethod(
                "parkExit", long.class, long.class));
        assertNotPublic(JavaProfiler.class.getDeclaredMethod("blockEnter", int.class));
        assertNotPublic(JavaProfiler.class.getDeclaredMethod("blockExit", long.class));
        assertTrue(Modifier.isPublic(JavaProfiler.class
                .getDeclaredMethod("beginTaskBlock").getModifiers()));
        assertTrue(Modifier.isPublic(JavaProfiler.class
                .getDeclaredMethod("endTaskBlock", long.class, long.class, long.class)
                .getModifiers()));
    }

    // State-mutating hooks into the process-wide profiler singleton: reachable from tests only
    // through the test-source bridge ReferenceChainTestHooks, never from application code.
    private static final Set<String> REFERENCE_CHAIN_TEST_SEAMS = new HashSet<>(Arrays.asList(
            "getTid", "setGcGenerationsEnabled0", "seedKlassPopulationSample0",
            "seedTidTrendSample0", "setKlassPopulationRepresentativeForTest0",
            "resetKlassPopulationForTest0", "selectLeakCandidateKlassIds0",
            "tagAsReferenceChainRoot0", "runReferenceChainPass0", "pollReferenceChainTargets0",
            "drainReferenceChainEventCount0", "resetReferenceChainSearchForTest0",
            "getReferenceChainPendingPositionForTest0", "getReferenceChainPendingSizeForTest0",
            "getReferenceChainFrontierStateForTest0", "getReferenceChainResolvedTargetTagForTest0",
            "heapFloorRecordForTest0", "setMaxHeapBytesForTest0", "setHeapFloorRecordingForTest0",
            "heapFloorResetForTest0", "heapFloorRisingForTest0",
            "shouldRunPassForTest0", "referenceChainPassesRunForTest0"));

    @Test
    public void referenceChainTestSeamsAreNotPublicApi() {
        Set<String> found = new HashSet<>();
        for (Method m : JavaProfiler.class.getDeclaredMethods()) {
            if (REFERENCE_CHAIN_TEST_SEAMS.contains(m.getName())) {
                found.add(m.getName());
                assertFalse(Modifier.isPublic(m.getModifiers()),
                        m.getName() + " is a state-mutating test seam and must stay non-public; "
                                + "tests reach it via ReferenceChainTestHooks");
            }
        }
        assertEquals(REFERENCE_CHAIN_TEST_SEAMS, found,
                "every listed reference-chain test seam must still exist on JavaProfiler");
    }

    private static void assertNotPublic(Method method) {
        assertFalse(Modifier.isPublic(method.getModifiers()),
                method.getName() + " is an internal instrumentation hook");
    }
}
