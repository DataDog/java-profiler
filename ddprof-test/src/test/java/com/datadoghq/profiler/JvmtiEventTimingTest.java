/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Collections;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;

import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * Checks when the profiler's JVMTI events are enabled relative to the JVM work they must
 * observe. The persistent events (CLASS_LOAD, CLASS_PREPARE, DYNAMIC_CODE_GENERATED,
 * COMPILED_METHOD_LOAD) are enabled lazily on the first start() rather than at agent load, so
 * anything that happens before then must either be replayed or be covered by an event that
 * stays enabled from agent load. Each test runs a fresh JVM and reads the {@code [TEST::INFO]}
 * lines the debug library prints, so they only run against the debug build.
 */
public class JvmtiEventTimingTest extends AbstractProcessProfilerTest {

    private static final String BIND_INTERCEPTION_ENABLED = "[TEST::INFO] NativeMethodBind interception enabled";
    private static final String MEMORY_USAGE_BOUND = "[TEST::INFO] NativeMethodBind: getMemoryUsage0 resolved";
    private static final String CLASS_PREPARE_ENABLED = "[TEST::INFO] Persistent JVMTI events: CLASS_PREPARE enabled";
    private static final String JMETHODIDS_PRELOADED = "[TEST::INFO] Preloaded jmethodIDs for";
    private static final String CALL_STUB_REGISTERED = "[TEST::INFO] JitCodeCache: call_stub registered";

    @BeforeEach
    void requireDebugOpenJdkClassLibrary() {
        assumeTrue("debug".equals(System.getProperty("ddprof_test.config")), "needs [TEST::INFO] output");
        // getMemoryUsage0 and the HotSpot stub names checked here do not exist on J9.
        assumeTrue(!Platform.isJ9());
    }

    /**
     * A native method binds once and binding events cannot be replayed with GenerateEvents(),
     * so NATIVE_METHOD_BIND must be enabled at agent load. VMInit's
     * {@code HeapUsage::initJMXUsage()} binds {@code MemoryImpl.getMemoryUsage0} before any
     * start(); the agent here never starts the profiler at all, so the binding can only be seen
     * if the event was on from Agent_OnLoad.
     *
     * <p>The profiler only intercepts bindings when it cannot read heap usage from VMStructs
     * ({@code HeapUsage::needsNativeBindingInterception()}), so on a HotSpot where it can, no
     * binding event is ever delivered and the test is skipped.
     */
    @Test
    void agentOnLoadSeesNativeBindingsBeforeFirstStart() throws Exception {
        Path agentLib = LibraryLoader.resolveLibraryPath(System.getProperty("java.io.tmpdir"));
        AtomicBoolean intercepting = new AtomicBoolean();
        AtomicBoolean bound = new AtomicBoolean();

        LaunchResult result = launch("noop",
                Collections.singletonList("-agentpath:" + agentLib.toAbsolutePath()),
                null,
                l -> {
                    if (l.contains(BIND_INTERCEPTION_ENABLED)) {
                        intercepting.set(true);
                    } else if (l.contains(MEMORY_USAGE_BOUND)) {
                        bound.set(true);
                    }
                    return LineConsumerResult.CONTINUE;
                },
                null);

        assertTrue(result.inTime, "forked JVM did not exit in time");
        assumeTrue(intercepting.get(), "this JVM needs no native binding interception");
        assertTrue(bound.get(),
                "VMStructs::NativeMethodBind never resolved getMemoryUsage0: NATIVE_METHOD_BIND was "
                        + "not enabled when VMInit bound it, so the JMX heap-usage fallback is lost");
    }

    /**
     * The first start() preloads jmethodIDs from a GetLoadedClasses() snapshot and relies on
     * ClassPrepare for every class prepared afterwards. CLASS_PREPARE must therefore be enabled
     * before the snapshot is taken; enabled after it, a class prepared in between gets neither.
     */
    @Test
    void classPrepareIsEnabledBeforeJmethodIdPreload() throws Exception {
        Path jfr = Files.createTempFile("jvmti-timing-", ".jfr");
        AtomicInteger lineNo = new AtomicInteger();
        AtomicInteger enabledAt = new AtomicInteger(-1);
        AtomicInteger preloadedAt = new AtomicInteger(-1);
        try {
            LaunchResult result = launch("profiler", Collections.emptyList(),
                    "start,cpu=10ms,jfr,file=" + jfr.toAbsolutePath(),
                    l -> {
                        int n = lineNo.incrementAndGet();
                        if (l.contains(CLASS_PREPARE_ENABLED)) {
                            enabledAt.compareAndSet(-1, n);
                        } else if (l.contains(JMETHODIDS_PRELOADED)) {
                            preloadedAt.compareAndSet(-1, n);
                        }
                        return LineConsumerResult.CONTINUE;
                    },
                    null);

            assertTrue(result.inTime, "forked JVM did not exit in time");
            assertNotEquals(-1, enabledAt.get(), "CLASS_PREPARE was never enabled");
            // Without lazy jmethodID resolution (the default) the first start() always preloads.
            assertNotEquals(-1, preloadedAt.get(), "first start() did not preload jmethodIDs");
            assertTrue(enabledAt.get() < preloadedAt.get(),
                    "CLASS_PREPARE was enabled (line " + enabledAt.get() + ") after the jmethodID "
                            + "preload snapshot (line " + preloadedAt.get() + "): classes prepared "
                            + "in between are never preloaded");
        } finally {
            Files.deleteIfExists(jfr);
        }
    }

    /**
     * With -agentpath the dynamic-code events are enabled only on the first start(), after
     * HotSpot has generated its bootstrap stubs, so those must be replayed in every loading mode,
     * not just on attach. call_stub is generated during VM bootstrap; without the replay its
     * bounds, which the stack walker relies on, are never recorded.
     */
    @Test
    void agentPathSessionReplaysBootstrapStubs() throws Exception {
        // call_stub is HotSpot's name for this stub; not verified on Zing.
        assumeTrue(!Platform.isZing());
        Path agentLib = LibraryLoader.resolveLibraryPath(System.getProperty("java.io.tmpdir"));
        Path jfr = Files.createTempFile("jvmti-timing-", ".jfr");
        AtomicBoolean registered = new AtomicBoolean();
        try {
            LaunchResult result = launch("noop",
                    Collections.singletonList("-agentpath:" + agentLib.toAbsolutePath()
                            + "=start,cpu=10ms,jfr,file=" + jfr.toAbsolutePath()),
                    null,
                    l -> {
                        if (l.contains(CALL_STUB_REGISTERED)) {
                            registered.set(true);
                        }
                        return LineConsumerResult.CONTINUE;
                    },
                    null);

            assertTrue(result.inTime, "forked JVM did not exit in time");
            assertTrue(registered.get(),
                    "call_stub never reached JitCodeCache in an -agentpath session: bootstrap "
                            + "DynamicCodeGenerated events were not replayed on first start()");
        } finally {
            Files.deleteIfExists(jfr);
        }
    }
}
