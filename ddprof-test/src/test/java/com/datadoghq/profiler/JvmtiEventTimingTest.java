/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.nio.file.Path;
import java.util.Collections;
import java.util.concurrent.atomic.AtomicBoolean;

import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * Checks that agent startup does not bootstrap JMX, by watching for the {@code getMemoryUsage0}
 * native binding while the agent is intercepting {@code NativeMethodBind}. It runs a fresh JVM
 * and reads the {@code [TEST::INFO]} lines the debug library prints, so it only runs against the
 * debug build.
 */
public class JvmtiEventTimingTest extends AbstractProcessProfilerTest {

    private static final String BIND_INTERCEPTION_ENABLED = "[TEST::INFO] NativeMethodBind interception enabled";
    private static final String BIND_INTERCEPTION_DISABLED = "[TEST::INFO] NativeMethodBind interception disabled";
    private static final String MEMORY_USAGE_BOUND = "[TEST::INFO] NativeMethodBind: getMemoryUsage0 resolved";

    @BeforeEach
    void requireDebugBuildOnNonJ9() {
        assumeTrue("debug".equals(System.getProperty("ddprof_test.config")), "needs [TEST::INFO] output");
        // getMemoryUsage0 does not exist on J9.
        assumeTrue(!Platform.isJ9());
    }

    /**
     * Agent load and VMInit must not bootstrap JMX: nothing reads the JMX heap usage, so the
     * {@code getMemoryUsage0} binding seen at startup would be pure startup cost.
     */
    @Test
    void agentStartupDoesNotBootstrapJmx() throws Exception {
        Path agentLib = LibraryLoader.resolveLibraryPath(System.getProperty("java.io.tmpdir"));
        AtomicBoolean intercepting = new AtomicBoolean();
        AtomicBoolean notIntercepting = new AtomicBoolean();
        AtomicBoolean bound = new AtomicBoolean();

        LaunchResult result = launch("noop",
                Collections.singletonList("-agentpath:" + agentLib.toAbsolutePath()),
                null,
                l -> {
                    if (l.contains(BIND_INTERCEPTION_ENABLED)) {
                        intercepting.set(true);
                    } else if (l.contains(BIND_INTERCEPTION_DISABLED)) {
                        notIntercepting.set(true);
                    } else if (l.contains(MEMORY_USAGE_BOUND)) {
                        bound.set(true);
                    }
                    return LineConsumerResult.CONTINUE;
                },
                null);

        assertTrue(result.inTime, "forked JVM did not exit in time");
        assertEquals(0, result.exitCode, "forked JVM exited with an error");
        // An agent that failed before deciding prints neither marker: fail rather than skip.
        assertTrue(intercepting.get() || notIntercepting.get(),
                "the agent never reported whether it intercepts native bindings");
        // Without interception no binding is ever reported, so there is nothing to check.
        assumeTrue(!notIntercepting.get(), "this JVM needs no native binding interception");
        assertFalse(bound.get(), "getMemoryUsage0 was bound at startup: the agent initialized JMX");
    }
}
