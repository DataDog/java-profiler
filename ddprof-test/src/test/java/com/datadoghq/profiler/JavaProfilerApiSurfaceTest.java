/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import org.junit.jupiter.api.Test;

import java.lang.reflect.Method;
import java.lang.reflect.Modifier;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

/** Locks the intended public boundary of TaskBlock-related profiler hooks. */
public class JavaProfilerApiSurfaceTest {
    @Test
    public void ownedBlockHooksAreNotPublicApiBeforeTaskBlockInstrumentation() throws Exception {
        assertNotPublic(JavaProfiler.class.getDeclaredMethod("parkEnter"));
        assertNotPublic(JavaProfiler.class.getDeclaredMethod(
                "parkExit", long.class, long.class));
        assertNotPublic(JavaProfiler.class.getDeclaredMethod("blockEnter", int.class));
        assertNotPublic(JavaProfiler.class.getDeclaredMethod("blockExit", long.class));
    }

    /** Verifies that the paired lifecycle remains the only public TaskBlock recording API. */
    @Test
    public void obsoleteDirectTaskBlockRecordersAreNotExposed() {
        assertTrue(Modifier.isPublic(getDeclaredMethod(
                "beginTaskBlock", int.class).getModifiers()));
        assertTrue(Modifier.isPublic(getDeclaredMethod(
                "endTaskBlock", long.class, long.class, long.class).getModifiers()));
        assertThrows(NoSuchMethodException.class, () -> JavaProfiler.class.getDeclaredMethod(
                "recordTaskBlock", long.class, long.class, long.class, long.class));
        assertThrows(NoSuchMethodException.class, () -> JavaProfiler.class.getDeclaredMethod(
                "recordTaskBlockWithContext", long.class, long.class, long.class, long.class,
                long.class, long.class));
    }

    private static void assertNotPublic(Method method) {
        assertFalse(Modifier.isPublic(method.getModifiers()),
                method.getName() + " must remain non-public until PR2 wires TaskBlock instrumentation");
    }

    private static Method getDeclaredMethod(String name, Class<?>... parameterTypes) {
        try {
            return JavaProfiler.class.getDeclaredMethod(name, parameterTypes);
        } catch (NoSuchMethodException e) {
            throw new AssertionError(e);
        }
    }
}
