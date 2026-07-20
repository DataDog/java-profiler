/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import org.junit.jupiter.api.Test;

import java.lang.reflect.Method;
import java.lang.reflect.Modifier;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/** Locks the supported public boundary and package-scoped producer hooks. */
public class JavaProfilerApiSurfaceTest {
    @Test
    public void taskBlockApiIsPublicButInternalHooksRemainPackageScoped() throws Exception {
        assertNotPublic(JavaProfiler.class.getDeclaredMethod("parkEnter"));
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

    @Test
    public void monitorWaitOwnershipIsExplicitPublicApi() throws Exception {
        assertTrue(Modifier.isPublic(JavaProfiler.class
                .getDeclaredMethod("getInstance", String.class, String.class, boolean.class)
                .getModifiers()));
        assertTrue(Modifier.isPublic(JavaProfiler.class
                .getDeclaredMethod("isMonitorEventsDelegated").getModifiers()));
    }

    private static void assertNotPublic(Method method) {
        assertFalse(Modifier.isPublic(method.getModifiers()),
                method.getName() + " is an internal instrumentation hook");
    }
}
