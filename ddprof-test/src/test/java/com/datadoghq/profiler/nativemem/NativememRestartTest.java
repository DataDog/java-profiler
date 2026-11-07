/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.nativemem;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.BeforeAll;
import org.junitpioneer.jupiter.RetryingTest;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Verifies that native memory (malloc) profiling survives a stop/restart cycle.
 *
 * <p>This test exercises the malloc hook lifecycle:
 * <ol>
 *   <li>First session: profiler starts, malloc hooks are patched, allocations are sampled</li>
 *   <li>Stop: malloc hooks are unpatched (GOT slots restored to original functions)</li>
 *   <li>Second session: profiler restarts, malloc hooks are re-patched, allocations are sampled</li>
 * </ol>
 *
 * <p>Events must be recorded in the second profiling session, confirming that the
 * stop/start lifecycle management (hook unpatch/repatch) is working correctly.
 */
public class NativememRestartTest extends AbstractProfilerTest {

    @BeforeAll
    static void preloadNativeLib() {
        // Ensure libddproftest.so is loaded before the profiler starts in @BeforeEach.
        // This matches the pattern in NativememProfilerTest.
        NativeAllocHelper.nativeMalloc(0, 0);
    }

    @Override
    protected String getProfilerCommand() {
        return "nativemem=0"; // sample every allocation
    }

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isLinux() && !Platform.isJ9() && !Platform.isZing();
    }

    @RetryingTest(3)
    public void testNativememProfilerRestart() throws Exception {
        // GOT patching conflicts with ASan/TSan interceptors
        Assumptions.assumeFalse(isAsan() || isTsan());

        // First session: framework already started the profiler in @BeforeEach.
        triggerAllocations(500);
        stopProfiler();

        // Verify first session recorded events
        JfrEvents firstSessionEvents = verifyEvents("datadog.NativeMemoryAllocation");
        assertTrue(firstSessionEvents.hasItems(),
                "NativeMemoryAllocation events must be recorded in the first profiling session");
        System.out.println("First session recorded " + firstSessionEvents.count() + " malloc events");

        // Second session: start manually with a fresh JFR file.
        Files.createDirectories(Paths.get("/tmp/recordings"));
        Path jfr2 = Files.createTempFile(Paths.get("/tmp/recordings"), "NativememRestartTest_restart", ".jfr");
        try {
            profiler.execute("start,nativemem=0,jfr,file=" + jfr2.toAbsolutePath());

            triggerAllocations(500);

            profiler.stop();

            JfrEvents secondSessionEvents = verifyEvents(jfr2, "datadog.NativeMemoryAllocation", true);
            assertTrue(secondSessionEvents.hasItems(),
                    "NativeMemoryAllocation events must be recorded in the second profiling session");
            System.out.println("Second session recorded " + secondSessionEvents.count() + " malloc events");
        } finally {
            Files.deleteIfExists(jfr2);
        }
    }

    @RetryingTest(3)
    public void testMultipleRestartCycles() throws Exception {
        // GOT patching conflicts with ASan/TSan interceptors
        Assumptions.assumeFalse(isAsan() || isTsan());

        // First session (started by framework)
        triggerAllocations(200);
        stopProfiler();

        JfrEvents firstEvents = verifyEvents("datadog.NativeMemoryAllocation");
        assertTrue(firstEvents.hasItems(), "First session must record events");
        System.out.println("Cycle 1: " + firstEvents.count() + " events");

        // Multiple restart cycles to stress the unpatch/repatch logic
        for (int cycle = 2; cycle <= 4; cycle++) {
            Path jfrPath = Files.createTempFile(
                    Paths.get("/tmp/recordings"),
                    "NativememRestartTest_cycle" + cycle + "_",
                    ".jfr");
            try {
                profiler.execute("start,nativemem=0,jfr,file=" + jfrPath.toAbsolutePath());
                triggerAllocations(200);
                profiler.stop();

                JfrEvents events = verifyEvents(jfrPath, "datadog.NativeMemoryAllocation", true);
                assertTrue(events.hasItems(),
                        "Cycle " + cycle + " must record NativeMemoryAllocation events");
                System.out.println("Cycle " + cycle + ": " + events.count() + " events");
            } finally {
                Files.deleteIfExists(jfrPath);
            }
        }
    }

    private static void triggerAllocations(int count) {
        NativeAllocHelper.nativeMalloc(1024, count);
    }
}
