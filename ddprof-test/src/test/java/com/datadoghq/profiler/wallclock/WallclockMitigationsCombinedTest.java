/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Verifies lifecycle-owned suppression ({@code wallprecheck=true}) with a mix of sleeping,
 * parked, and runnable threads.
 */
public class WallclockMitigationsCombinedTest extends AbstractProfilerTest {
    private static final int OSTHREAD_STATE_SLEEPING = 7;

    @Test
    public void precheckAndParkSuppressionWorkTogether() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(
                Platform.isJavaVersionAtLeast(11),
                "Sleeping-state precheck assertions are stable on JDK 11+");

        CountDownLatch ready = new CountDownLatch(3);
        AtomicBoolean stop = new AtomicBoolean(false);

        Thread sleeping =
                new Thread(
                        () -> {
                            registerCurrentThreadForWallClockProfiling();
                            ready.countDown();
                            long token = ProfilerOwnedBlockHooks.blockEnter(
                                    profiler, OSTHREAD_STATE_SLEEPING);
                            try {
                                Thread.sleep(280);
                            } catch (InterruptedException ignored) {
                            } finally {
                                ProfilerOwnedBlockHooks.blockExit(profiler, token);
                            }
                        },
                        "combined-sleeping");

        Thread parkedBusy =
                new Thread(
                        () -> {
                            registerCurrentThreadForWallClockProfiling();
                            long spanId = 0x1111L;
                            long rootSpanId = 0x2222L;
                            profiler.setTraceContext(rootSpanId, spanId, 0, 0, -1, null, -1, null);
                            ready.countDown();
                            ProfilerOwnedBlockHooks.parkEnter(profiler);
                            long parkedUntil = System.nanoTime() + 280_000_000L;
                            while (System.nanoTime() < parkedUntil) {
                                // spin while flagged parked
                            }
                            ProfilerOwnedBlockHooks.parkExit(
                                    profiler, System.identityHashCode(this), 0L);
                            profiler.clearTraceContext();
                        },
                        "combined-parked");

        Thread runnable =
                new Thread(
                        () -> {
                            registerCurrentThreadForWallClockProfiling();
                            ready.countDown();
                            while (!stop.get()) {
                                // keep runnable
                            }
                        },
                        "combined-runnable");

        sleeping.setDaemon(true);
        parkedBusy.setDaemon(true);
        runnable.setDaemon(true);
        sleeping.start();
        parkedBusy.start();
        runnable.start();

        ready.await();
        Thread.sleep(350);
        stop.set(true);

        sleeping.interrupt();
        sleeping.join(1000);
        parkedBusy.join(1000);
        runnable.join(1000);

        stopProfiler();

        Map<String, Long> samplesByThread = samplesByThreadName();
        long sleepingSamples = samplesByThread.getOrDefault("combined-sleeping", 0L);
        long parkedSamples = samplesByThread.getOrDefault("combined-parked", 0L);
        long runnableSamples = samplesByThread.getOrDefault("combined-runnable", 0L);

        assertTrue(sleepingSamples < 10,
                "Expected nearly no samples from owned sleeping thread, got: " + sleepingSamples);
        assertTrue(parkedSamples > 0,
                "Expected samples from traced parked thread, got: " + parkedSamples);
        assertTrue(runnableSamples > 0,
                "Expected samples from runnable thread, got: " + runnableSamples);

        // Sleeping thread's suppression counter must have incremented.
        Map<String, Long> counters = profiler.getDebugCounters();
        if (counters.containsKey("wc_signals_suppressed_owned_block")) {
            assertTrue(
                    counters.get("wc_signals_suppressed_owned_block") > 0,
                    "Expected owned-block suppression counter to increase");
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,filter=0,wallprecheck=true";
    }

    private Map<String, Long> samplesByThreadName() {
        Map<String, Long> samplesByThread = new HashMap<>();
        JfrEvents events = verifyEvents("datadog.MethodSample", false);
        for (JfrEvent item : events) {
            String threadName = item.getThreadName("eventThread");
            if (threadName != null) {
                samplesByThread.merge(threadName, 1L, Long::sum);
            }
        }
        return samplesByThread;
    }
}
