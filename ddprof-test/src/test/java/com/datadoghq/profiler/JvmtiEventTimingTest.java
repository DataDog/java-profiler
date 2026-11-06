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
 * Checks when the profiler's JVMTI events are enabled relative to the JVM work they must
 * observe. Each test runs a fresh JVM and reads the {@code [TEST::INFO]} lines the debug library
 * prints, so they only run against the debug build.
 */
public class JvmtiEventTimingTest extends AbstractProcessProfilerTest {

    private static final String BIND_INTERCEPTION_ENABLED = "[TEST::INFO] NativeMethodBind interception enabled";
    private static final String BIND_INTERCEPTION_DISABLED = "[TEST::INFO] NativeMethodBind interception disabled";
    private static final String MEMORY_USAGE_BOUND = "[TEST::INFO] NativeMethodBind: getMemoryUsage0 resolved";

    @BeforeEach
    void requireDebugOpenJdkClassLibrary() {
        assumeTrue("debug".equals(System.getProperty("ddprof_test.config")), "needs [TEST::INFO] output");
        // getMemoryUsage0 does not exist on J9.
        assumeTrue(!Platform.isJ9());
    }

    /**
     * A native method binds once and binding events cannot be replayed with GenerateEvents(),
     * so NATIVE_METHOD_BIND must be enabled at agent load. VMInit's
     * {@code HeapUsage::initJMXUsage()} binds {@code MemoryImpl.getMemoryUsage0} before any
     * start(); the agent here never starts the profiler at all, so the binding can only be seen
     * if the event was on from Agent_OnLoad and initJMXUsage() got as far as the JMX call.
     *
     * <p>The profiler only intercepts bindings when it cannot read heap usage from VMStructs
     * ({@code HeapUsage::needsNativeBindingInterception()}), so on a HotSpot where it can, no
     * binding event is ever delivered and the test is skipped.
     */
    @Test
    void agentOnLoadSeesNativeBindingsBeforeFirstStart() throws Exception {
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
        assumeTrue(!notIntercepting.get(), "this JVM needs no native binding interception");
        assertTrue(bound.get(),
                "VMStructs::NativeMethodBind never resolved getMemoryUsage0: either NATIVE_METHOD_BIND "
                        + "was not enabled when VMInit bound it, or initJMXUsage() returned before the "
                        + "JMX call, so the JMX heap-usage fallback is lost");
    }
}
