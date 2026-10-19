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

import static org.junit.jupiter.api.Assertions.assertFalse;

public class JavaProfilerApiSurfaceTest {
    @Test
    public void ownedBlockHooksAreNotPublicApiBeforeTaskBlockInstrumentation() throws Exception {
        assertNotPublic(JavaProfiler.class.getDeclaredMethod("parkEnter"));
        assertNotPublic(JavaProfiler.class.getDeclaredMethod(
                "parkExit", long.class, long.class));
        assertNotPublic(JavaProfiler.class.getDeclaredMethod("blockEnter", int.class));
        assertNotPublic(JavaProfiler.class.getDeclaredMethod("blockExit", long.class));
    }

    @Test
    public void referenceChainTestSeamsAreNotPublicApi() {
        Set<String> seams = new HashSet<>(Arrays.asList(
                "getTid", "setGcGenerationsEnabled0", "seedKlassPopulationSample0",
                "seedTidTrendSample0", "selectLeakCandidateKlassIds0", "tagAsReferenceChainRoot0",
                "runReferenceChainPass0", "pollReferenceChainTargets0",
                "drainReferenceChainEventCountForLeaf0"));
        for (Method m : JavaProfiler.class.getDeclaredMethods()) {
            if (seams.contains(m.getName()) || m.getName().endsWith("ForTest0")) {
                assertFalse(Modifier.isPublic(m.getModifiers()),
                        m.getName() + " is a test seam and must not be public API"
                                + " (tests reach it through ReferenceChainTestHooks)");
            }
        }
    }

    private static void assertNotPublic(Method method) {
        assertFalse(Modifier.isPublic(method.getModifiers()),
                method.getName() + " must remain non-public until PR2 wires TaskBlock instrumentation");
    }
}
