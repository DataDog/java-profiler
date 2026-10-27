/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.lifecycle;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;

import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;
import org.junitpioneer.jupiter.RetryingTest;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Map;
import java.util.TreeMap;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Tests the complete Java profiler lifecycle:
 * <pre>
 *   getInstance() [init] → start() → stop() → start() → stop() → [JVM shutdown]
 * </pre>
 *
 * <p>This test verifies:
 * <ul>
 *   <li>Profiler can be started after init (getInstance)</li>
 *   <li>Profiler can be stopped cleanly</li>
 *   <li>Profiler can be restarted after stop</li>
 *   <li>Events are recorded in each profiling session</li>
 *   <li>Multiple stop/start cycles work correctly</li>
 * </ul>
 *
 * <p>Note: The native shutdown() is called automatically by VMDeath callback
 * when the JVM exits. It cannot be tested directly from Java without terminating
 * the test JVM.
 */
public class ProfilerLifecycleTest {

    private static final int WORK_ITERATIONS = 500_000;

    @Timeout(120)
    @RetryingTest(3)
    public void testFullLifecycle() throws Exception {
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11), "wall-clock requires Java 11+");
        Assumptions.assumeTrue(!Platform.isJ9(), "J9 has a different JVMTI implementation");
        Assumptions.assumeTrue(!Platform.isZing(), "Zing forces cstack=no");

        Path recordings = Files.createDirectories(Paths.get("/tmp/recordings/lifecycle"));

        // Step 1: getInstance() - this calls init0() internally
        JavaProfiler profiler = JavaProfiler.getInstance();
        assertNotNull(profiler, "Profiler instance must not be null after init");
        System.out.println("[Lifecycle] Step 1: getInstance() - profiler initialized");

        // Step 2: First start() via execute()
        Path jfr1 = Files.createTempFile(recordings, "lifecycle_session1_", ".jfr");
        try {
            profiler.execute("start,wall=1ms,cpu=10ms,jfr,file=" + jfr1.toAbsolutePath());
            System.out.println("[Lifecycle] Step 2: First start() - profiler running");

            // Generate some CPU work to produce samples
            generateCpuWork();

            // Step 3: First stop()
            profiler.stop();
            System.out.println("[Lifecycle] Step 3: First stop() - profiler stopped");
            printNativeMemCounters(profiler, "after first stop");

            // Verify first session recorded events
            JfrEvents session1Events = JfrEvents.load(jfr1, "datadog.ExecutionSample"::equals);
            assertTrue(session1Events.hasItems(),
                    "First session must record datadog.ExecutionSample events");
            System.out.println("[Lifecycle] First session recorded " + session1Events.count() + " CPU samples");

        } finally {
            Files.deleteIfExists(jfr1);
        }

        // Step 4: Second start() via execute() - tests restart after stop
        Path jfr2 = Files.createTempFile(recordings, "lifecycle_session2_", ".jfr");
        try {
            profiler.execute("start,wall=1ms,cpu=10ms,jfr,file=" + jfr2.toAbsolutePath());
            System.out.println("[Lifecycle] Step 4: Second start() - profiler restarted");

            // Generate more CPU work
            generateCpuWork();

            // Step 5: Second stop()
            profiler.stop();
            System.out.println("[Lifecycle] Step 5: Second stop() - profiler stopped again");
            printNativeMemCounters(profiler, "after second stop");

            // Verify second session recorded events
            JfrEvents session2Events = JfrEvents.load(jfr2, "datadog.ExecutionSample"::equals);
            assertTrue(session2Events.hasItems(),
                    "Second session must record ExecutionSample events after restart");
            System.out.println("[Lifecycle] Second session recorded " + session2Events.count() + " CPU samples");

        } finally {
            Files.deleteIfExists(jfr2);
        }

        // Step 6: JVM shutdown would call Profiler::shutdown() via VMDeath callback
        // We can't test this directly without terminating the JVM, but we verify
        // the profiler is in a clean state by checking getStatus()
        String status = profiler.getStatus();
        assertTrue(status.contains("Running          : false"),
                "Profiler should not be running after stop");
        System.out.println("[Lifecycle] Step 6: Profiler in clean state, ready for JVM shutdown");
        System.out.println("[Lifecycle] Full lifecycle test completed successfully");
    }

    @Timeout(120)
    @RetryingTest(3)
    public void testMultipleRestartCycles() throws Exception {
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11), "wall-clock requires Java 11+");
        Assumptions.assumeTrue(!Platform.isJ9(), "J9 has a different JVMTI implementation");
        Assumptions.assumeTrue(!Platform.isZing(), "Zing forces cstack=no");

        Path recordings = Files.createDirectories(Paths.get("/tmp/recordings/lifecycle"));
        JavaProfiler profiler = JavaProfiler.getInstance();

        final int CYCLES = 5;
        for (int cycle = 1; cycle <= CYCLES; cycle++) {
            Path jfr = Files.createTempFile(recordings, "lifecycle_cycle" + cycle + "_", ".jfr");
            try {
                // Start
                profiler.execute("start,cpu=10ms,jfr,file=" + jfr.toAbsolutePath());

                // Generate work
                generateCpuWork();

                // Stop
                profiler.stop();
                printNativeMemCounters(profiler, "cycle " + cycle + " after stop");

                // Verify events
                JfrEvents events = JfrEvents.load(jfr, "datadog.ExecutionSample"::equals);
                assertTrue(events.hasItems(),
                        "Cycle " + cycle + " must record ExecutionSample events");
                System.out.println("[Lifecycle] Cycle " + cycle + "/" + CYCLES +
                        " recorded " + events.count() + " CPU samples");

            } finally {
                Files.deleteIfExists(jfr);
            }
        }

        System.out.println("[Lifecycle] Completed " + CYCLES + " restart cycles successfully");
    }

    @Timeout(120)
    @RetryingTest(3)
    public void testConcurrentWorkDuringLifecycle() throws Exception {
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11), "wall-clock requires Java 11+");
        Assumptions.assumeTrue(!Platform.isJ9(), "J9 has a different JVMTI implementation");
        Assumptions.assumeTrue(!Platform.isZing(), "Zing forces cstack=no");

        Path recordings = Files.createDirectories(Paths.get("/tmp/recordings/lifecycle"));
        JavaProfiler profiler = JavaProfiler.getInstance();

        // Start background threads that will be active during profiler lifecycle changes
        final int NUM_THREADS = 4;
        AtomicBoolean running = new AtomicBoolean(true);
        CountDownLatch threadsStarted = new CountDownLatch(NUM_THREADS);
        Thread[] workers = new Thread[NUM_THREADS];

        for (int i = 0; i < NUM_THREADS; i++) {
            final int threadId = i;
            workers[i] = new Thread(() -> {
                threadsStarted.countDown();
                while (running.get()) {
                    // Do some CPU work
                    double sum = 0;
                    for (int j = 0; j < 1000; j++) {
                        sum += Math.sin(j) * Math.cos(j);
                    }
                    // Prevent optimization
                    if (sum == Double.MAX_VALUE) {
                        System.out.println("Unlikely: " + sum);
                    }
                    Thread.yield();
                }
            }, "WorkerThread-" + threadId);
            workers[i].start();
        }

        try {
            assertTrue(threadsStarted.await(5, TimeUnit.SECONDS), "Worker threads should start");

            // Perform lifecycle operations while threads are running
            for (int cycle = 1; cycle <= 3; cycle++) {
                Path jfr = Files.createTempFile(recordings, "concurrent_cycle" + cycle + "_", ".jfr");
                try {
                    profiler.execute("start,wall=1ms,cpu=10ms,jfr,file=" + jfr.toAbsolutePath());

                    // Let profiler run while workers are active
                    Thread.sleep(100);

                    profiler.stop();
                    printNativeMemCounters(profiler, "concurrent cycle " + cycle + " after stop");

                    JfrEvents events = JfrEvents.load(jfr, "datadog.ExecutionSample"::equals);
                    assertTrue(events.hasItems(),
                            "Cycle " + cycle + " must record samples with concurrent work");
                    System.out.println("[Lifecycle] Concurrent cycle " + cycle +
                            " recorded " + events.count() + " samples");

                } finally {
                    Files.deleteIfExists(jfr);
                }
            }

        } finally {
            running.set(false);
            for (Thread worker : workers) {
                worker.join(5000);
            }
        }

        System.out.println("[Lifecycle] Concurrent work lifecycle test completed");
    }

    @Timeout(60)
    @Test
    public void testStatusReflectsLifecycleState() throws Exception {
        JavaProfiler profiler = JavaProfiler.getInstance();
        Path recordings = Files.createDirectories(Paths.get("/tmp/recordings/lifecycle"));
        Path jfr = Files.createTempFile(recordings, "status_test_", ".jfr");

        try {
            // Before start - should not be running
            String statusBefore = profiler.getStatus();
            // Note: status may vary depending on previous test state, so we just check it's available
            assertNotNull(statusBefore, "Status should be available before start");

            // Start profiler
            profiler.execute("start,cpu=10ms,jfr,file=" + jfr.toAbsolutePath());
            String statusRunning = profiler.getStatus();
            assertTrue(statusRunning.contains("Running          : true"),
                    "Status should show running=true after start");

            // Stop profiler
            profiler.stop();
            printNativeMemCounters(profiler, "status test after stop");
            String statusStopped = profiler.getStatus();
            assertTrue(statusStopped.contains("Running          : false"),
                    "Status should show running=false after stop");

        } finally {
            Files.deleteIfExists(jfr);
        }
    }

    /**
     * Prints the native memory counters ({@code native_mem_*}, {@code malloc_*} and the
     * per-subsystem {@code *_bytes} gauges). Only called after stop(): start() zeroes all
     * counters and the native_mem_* / malloc_* / codecache_* mirrors are refreshed only
     * when a JFR chunk is finalized, so values read before stop() are zero or stale.
     * Debug counters are only available in builds with COUNTERS enabled.
     */
    private static void printNativeMemCounters(JavaProfiler profiler, String transition) {
        Map<String, Long> memCounters = new TreeMap<>();
        for (Map.Entry<String, Long> e : profiler.getDebugCounters().entrySet()) {
            if (e.getKey().endsWith("_bytes")) {
                memCounters.put(e.getKey(), e.getValue());
            }
        }
        if (memCounters.isEmpty()) {
            System.out.println("[Lifecycle] Native memory " + transition + ": no counters available");
            return;
        }
        StringBuilder sb = new StringBuilder("[Lifecycle] Native memory " + transition + ":");
        for (Map.Entry<String, Long> e : memCounters.entrySet()) {
            sb.append("\n    ").append(e.getKey()).append(" = ").append(e.getValue());
        }
        System.out.println(sb);
    }

    /**
     * Generates CPU-intensive work to produce profiling samples.
     */
    private void generateCpuWork() {
        double sum = 0;
        for (int i = 0; i < WORK_ITERATIONS; i++) {
            sum += Math.sin(i) * Math.cos(i) * Math.tan(i % 100 + 1);
        }
        // Prevent dead code elimination
        if (sum == Double.MAX_VALUE) {
            System.out.println("Unlikely: " + sum);
        }
    }
}
