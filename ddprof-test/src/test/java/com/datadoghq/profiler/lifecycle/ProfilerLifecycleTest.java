/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.lifecycle;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.NativeMemTestHooks;
import com.datadoghq.profiler.Platform;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;
import org.junitpioneer.jupiter.RetryingTest;

import java.io.IOException;
import java.lang.management.ManagementFactory;
import java.lang.management.ThreadMXBean;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
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
 *   <li>Native memory a recording allocates is released on stop, and process-lifetime
 *       native memory does not grow across restarts (per NativeMem category)</li>
 * </ul>
 *
 * <p>Note: The native shutdown() is called automatically by VMDeath callback
 * when the JVM exits. It cannot be tested directly from Java without terminating
 * the test JVM.
 */
public class ProfilerLifecycleTest {

    private static final long CPU_WORK_NANOS = TimeUnit.MILLISECONDS.toNanos(200);
    private static final long CPU_WORK_MAX_WALL_NANOS = TimeUnit.SECONDS.toNanos(5);

    /**
     * NativeMem categories owned by a recording: released by stop(), so they must read 0
     * whenever the profiler is idle. {@code calltrace} covers the call-trace storage and
     * per-thread call-trace buffers, {@code liveness} the liveness tracker's tracking table,
     * {@code ctimer} the CPU timer table (CTimer::stop() frees it).
     * Not listed: {@code perf}, because PerfEvents::stop() deliberately keeps per-thread
     * events registered across recordings, and {@code dictionary}, which also counts the
     * context-value dictionary that deliberately survives stop() (threads cache its
     * encodings) - and that any earlier test in this JVM may have filled. The released
     * dictionaries are checked one by one through {@link #RECORDING_SCOPED_DICTIONARIES}.
     */
    private static final String[] RECORDING_SCOPED = {
            "calltrace", "jfr_buffers", "wallclock", "line_tables", "method_map", "liveness",
            "ctimer"};

    /**
     * Per-dictionary storage gauges (debug counters, compiled into every build) of the
     * dictionaries stop() releases: the class-name and the string-label (endpoint) maps.
     */
    private static final String[] RECORDING_SCOPED_DICTIONARIES = {
            "dictionary_classes_bytes", "dictionary_endpoints_bytes"};

    /**
     * Categories that live for the whole process but must not grow from one idle state to the
     * next. {@code native_symbols} and {@code thread_local} are not listed: they legitimately
     * grow as libraries are loaded and threads are created.
     */
    private static final String[] NO_GROWTH_WHEN_IDLE = {"thread_filter"};

    /** Slack for small, legitimate fluctuations (e.g. a trace recorded during teardown). */
    private static final long GROWTH_TOLERANCE_BYTES = 64 * 1024;

    /**
     * The profiler is a process-wide singleton and the tests below start it without a
     * stop on their failure paths. Leave it idle, so a retry or the next test does not
     * fail with "already started" and hide the original failure.
     */
    @AfterEach
    public void stopIfRunning() {
        JavaProfiler profiler = JavaProfiler.getInstance();
        if (profiler.getStatus().contains("Running          : true")) {
            AbstractProfilerTest.stopRetryingOnDrainTimeout(profiler);
        }
    }

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
        nativeMem("after init");

        // Step 2: First start() via execute()
        Path jfr1 = Files.createTempFile(recordings, "lifecycle_session1_", ".jfr");
        try {
            nativeMem("before first start");
            profiler.execute("start,wall=1ms,cpu=10ms,jfr,file=" + jfr1.toAbsolutePath());
            System.out.println("[Lifecycle] Step 2: First start() - profiler running");
            assertRecording(nativeMem("after first start"), "after first start");

            // Generate some CPU work to produce samples
            generateCpuWork();

            // Step 3: First stop()
            profiler.stop();
            System.out.println("[Lifecycle] Step 3: First stop() - profiler stopped");
            assertIdle(nativeMem("after first stop"), "after first stop");

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
            nativeMem("before second start");
            profiler.execute("start,wall=1ms,cpu=10ms,jfr,file=" + jfr2.toAbsolutePath());
            System.out.println("[Lifecycle] Step 4: Second start() - profiler restarted");
            assertRecording(nativeMem("after second start"), "after second start");

            // Generate more CPU work
            generateCpuWork();

            // Step 5: Second stop()
            profiler.stop();
            System.out.println("[Lifecycle] Step 5: Second stop() - profiler stopped again");
            assertIdle(nativeMem("after second stop"), "after second stop");

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
        Map<String, Long> firstIdle = null;
        for (int cycle = 1; cycle <= CYCLES; cycle++) {
            Path jfr = Files.createTempFile(recordings, "lifecycle_cycle" + cycle + "_", ".jfr");
            try {
                // Start
                nativeMem("cycle " + cycle + " before start");
                profiler.execute("start,cpu=10ms,jfr,file=" + jfr.toAbsolutePath());
                nativeMem("cycle " + cycle + " after start");

                // Generate work
                generateCpuWork();

                // Stop
                profiler.stop();
                String when = "cycle " + cycle + " after stop";
                Map<String, Long> idle = nativeMem(when);
                assertIdle(idle, when);
                if (firstIdle == null) {
                    firstIdle = idle;
                } else {
                    assertNoGrowth(firstIdle, idle, when);
                }

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
        // The workers start while the profiler is idle; without the priming pool (macOS) their
        // CPU samples are dropped as samples_dropped_thread_local.
        // Only the sample-presence assertion needs it; the lifecycle churn runs regardless.
        final boolean tlsPrimed = JavaProfiler.testTlsPrimingAvailable();

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
                    nativeMem("concurrent cycle " + cycle + " before start");
                    profiler.execute("start,wall=1ms,cpu=10ms,jfr,file=" + jfr.toAbsolutePath());
                    nativeMem("concurrent cycle " + cycle + " after start");

                    // Let profiler run while workers are active
                    Thread.sleep(100);

                    profiler.stop();
                    String when = "concurrent cycle " + cycle + " after stop";
                    assertIdle(nativeMem(when), when);

                    JfrEvents events = JfrEvents.load(jfr, "datadog.ExecutionSample"::equals);
                    // Threads started while idle have no ProfiledThread without the priming pool.
                    if (tlsPrimed) {
                        assertTrue(events.hasItems(),
                                "Cycle " + cycle + " must record samples with concurrent work");
                    }
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

    /**
     * The liveness tracker frees its table on stop() and builds a fresh one on start(): each
     * recording reports the objects it saw survive, and none of it is held while idle.
     */
    @Timeout(120)
    @RetryingTest(3)
    public void testLivenessRestartCycles() throws Exception {
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11), "liveness requires Java 11+");
        Assumptions.assumeTrue(!Platform.isJ9(), "J9 has a different JVMTI implementation");
        Assumptions.assumeTrue(!Platform.isZing(), "Zing does not support liveness tracking");

        Path recordings = Files.createDirectories(Paths.get("/tmp/recordings/lifecycle"));
        JavaProfiler profiler = JavaProfiler.getInstance();

        final int CYCLES = 3;
        for (int cycle = 1; cycle <= CYCLES; cycle++) {
            Path jfr = Files.createTempFile(recordings, "liveness_cycle" + cycle + "_", ".jfr");
            try {
                String when = "liveness cycle " + cycle;
                nativeMem(when + " before start");
                profiler.execute("start,memory=256:L,jfr,file=" + jfr.toAbsolutePath());
                assertTrue(category(nativeMem(when + " after start"), "liveness") > 0,
                        "no liveness table " + when + " after start");

                // Retained across the GCs below, so the tracker sees them survive; referenced
                // again after stop() so they stay reachable until the final chunk is written.
                List<byte[]> retained = allocateRetained();
                for (int i = 0; i < 3; i++) {
                    System.gc();
                    Thread.sleep(50);
                }

                profiler.stop();
                assertIdle(nativeMem(when + " after stop"), when + " after stop");
                assertFalse(retained.isEmpty());

                JfrEvents live = JfrEvents.load(jfr, "datadog.HeapLiveObject"::equals);
                assertTrue(live.hasItems(),
                        "Cycle " + cycle + " must record HeapLiveObject events");
                System.out.println("[Lifecycle] Liveness cycle " + cycle + "/" + CYCLES +
                        " recorded " + live.count() + " live objects");
            } finally {
                Files.deleteIfExists(jfr);
            }
        }
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
            nativeMem("status test before start");
            profiler.execute("start,cpu=10ms,jfr,file=" + jfr.toAbsolutePath());
            nativeMem("status test after start");
            String statusRunning = profiler.getStatus();
            assertTrue(statusRunning.contains("Running          : true"),
                    "Status should show running=true after start");

            // Stop profiler
            profiler.stop();
            assertIdle(nativeMem("status test after stop"), "status test after stop");
            String statusStopped = profiler.getStatus();
            assertTrue(statusStopped.contains("Running          : false"),
                    "Status should show running=false after stop");

        } finally {
            Files.deleteIfExists(jfr);
        }
    }

    /**
     * A tracer keeps calling the trace-root and queue-time APIs after stop(). They must not
     * re-allocate the endpoint or class dictionaries stop() released, and recordTraceRoot
     * answers as an empty dictionary would: accepted only if the size limit admits an entry.
     */
    @Timeout(60)
    @Test
    public void testIdleTracerCallsDoNotReallocateDictionaries() throws Exception {
        JavaProfiler profiler = JavaProfiler.getInstance();
        Path recordings = Files.createDirectories(Paths.get("/tmp/recordings/lifecycle"));
        Path jfr = Files.createTempFile(recordings, "idle_calls_", ".jfr");
        try {
            profiler.execute("start,cpu=10ms,jfr,file=" + jfr.toAbsolutePath());
            assertFalse(profiler.recordTraceRoot(4, null, "recording-operation", 10),
                    "a null endpoint is rejected while recording");
            profiler.stop();
            assertIdle(nativeMem("idle calls before"), "before idle tracer calls");

            assertTrue(profiler.recordTraceRoot(1, "idle-endpoint", "idle-operation", 10),
                    "an idle profiler accepts an endpoint the size limit admits");
            assertFalse(profiler.recordTraceRoot(2, "idle-endpoint", "idle-operation", 0),
                    "an idle profiler rejects an endpoint a zero size limit excludes");
            assertFalse(profiler.recordTraceRoot(3, null, "idle-operation", 10),
                    "a null endpoint is rejected while idle, as it is while recording");
            long now = profiler.getCurrentTicks();
            profiler.recordQueueTime(now - 1000, now, Runnable.class, ProfilerLifecycleTest.class,
                    ArrayList.class, 1, Thread.currentThread());

            assertIdle(nativeMem("idle calls after"), "after idle tracer calls");
        } finally {
            Files.deleteIfExists(jfr);
        }
    }

    /**
     * Reads and prints the profiler's live native memory per NativeMem category, as of the
     * moment of the call (not a mirror refreshed at JFR chunk boundaries). Categories are
     * printed in bytes, the total in KB.
     */
    private static Map<String, Long> nativeMem(String transition) {
        Map<String, Long> live = NativeMemTestHooks.liveBytesByCategory();
        long total = 0;
        StringBuilder sb = new StringBuilder();
        for (Map.Entry<String, Long> e : live.entrySet()) {
            sb.append("\n    ").append(e.getKey()).append(" = ").append(e.getValue());
            total += e.getValue();
        }
        System.out.println("[Lifecycle] Native memory " + transition
                + String.format(" (total %.1f KB):", total / 1024.0) + sb);
        return live;
    }

    private static long category(Map<String, Long> live, String name) {
        Long value = live.get(name);
        assertNotNull(value, "no NativeMem category named " + name + " in " + live.keySet());
        return value;
    }

    /**
     * A running recording holds its JFR buffers and call-trace storage again; also shows the
     * seam reports real values. Not {@code dictionary}: it allocates on the first insert,
     * which need not have happened yet right after start().
     */
    private static void assertRecording(Map<String, Long> live, String when) {
        for (String name : new String[] {"jfr_buffers", "calltrace"}) {
            assertTrue(category(live, name) > 0, "no " + name + " memory " + when);
        }
    }

    /** Everything a recording allocates has been released once the profiler is idle. */
    private static void assertIdle(Map<String, Long> live, String when) throws IOException {
        for (String name : RECORDING_SCOPED) {
            assertEquals(0L, category(live, name), name + " still holds memory " + when);
        }
        Map<String, Long> counters = JavaProfiler.getInstance().getDebugCounters();
        for (String name : RECORDING_SCOPED_DICTIONARIES) {
            Long bytes = counters.get(name);
            assertNotNull(bytes, "no debug counter named " + name + " in " + counters.keySet());
            assertEquals(0L, (long) bytes, name + " still holds memory " + when);
        }
    }

    /** Process-lifetime structures have not grown since an earlier idle state. */
    private static void assertNoGrowth(Map<String, Long> baseline, Map<String, Long> live, String when) {
        for (String name : NO_GROWTH_WHEN_IDLE) {
            long before = category(baseline, name);
            long now = category(live, name);
            assertTrue(now <= before + GROWTH_TOLERANCE_BYTES,
                    name + " grew from " + before + " to " + now + " bytes " + when);
        }
    }

    /** Allocates ~64 MiB of 64 KiB arrays, enough for a 256 KiB sampling interval to hit. */
    private static List<byte[]> allocateRetained() {
        List<byte[]> retained = new ArrayList<>();
        for (int i = 0; i < 1024; i++) {
            retained.add(new byte[64 * 1024]);
        }
        return retained;
    }

    /**
     * Burns {@link #CPU_WORK_NANOS} of this thread's CPU time, so that a {@code cpu=10ms}
     * recording collects about 20 samples. A fixed iteration count finishes in a few ms once
     * JIT-compiled, leaving a recording with zero samples. Capped by {@link #CPU_WORK_MAX_WALL_NANOS}.
     */
    private void generateCpuWork() {
        ThreadMXBean threads = ManagementFactory.getThreadMXBean();
        boolean cpuClock = threads.isCurrentThreadCpuTimeSupported();
        long wallStart = System.nanoTime();
        long start = cpuClock ? threads.getCurrentThreadCpuTime() : wallStart;
        double sum = 0;
        int i = 0;
        while (true) {
            sum += Math.sin(i) * Math.cos(i) * Math.tan(i % 100 + 1);
            if (++i % 10_000 == 0) {
                long now = System.nanoTime();
                long used = (cpuClock ? threads.getCurrentThreadCpuTime() : now) - start;
                if (used >= CPU_WORK_NANOS || now - wallStart >= CPU_WORK_MAX_WALL_NANOS) {
                    break;
                }
            }
        }
        // Prevent dead code elimination
        if (sum == Double.MAX_VALUE) {
            System.out.println("Unlikely: " + sum);
        }
    }
}
