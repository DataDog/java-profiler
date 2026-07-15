/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.atomic.AtomicBoolean;

/** Verifies that {@code wallprecheck=true} does not suppress context-scoped threads. */
public class WallclockMitigationsCombinedTest extends AbstractProfilerTest {
    private static final int OSTHREAD_STATE_SLEEPING = 7;

    @Test
    public void contextScopedThreadsRemainSampled() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(
                Platform.isJavaVersionAtLeast(11),
                "Sleeping-state precheck assertions are stable on JDK 11+");

        CountDownLatch ready = new CountDownLatch(3);
        AtomicBoolean stop = new AtomicBoolean(false);
        long suppressedBefore = profiler.getDebugCounters()
                .getOrDefault("wc_signals_suppressed_owned_block", 0L);

        Thread sleeping =
                new Thread(
                        () -> {
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
                            long spanId = 0x1111L;
                            long rootSpanId = 0x2222L;
                            profiler.setContext(rootSpanId, spanId, 0, 0);
                            ready.countDown();
                            ProfilerOwnedBlockHooks.parkEnter(profiler);
                            long parkedUntil = System.nanoTime() + 280_000_000L;
                            while (System.nanoTime() < parkedUntil) {
                                // spin while flagged parked
                            }
                            ProfilerOwnedBlockHooks.parkExit(
                                    profiler, System.identityHashCode(this), 0L);
                            profiler.clearContext();
                        },
                        "combined-parked");

        Thread runnable =
                new Thread(
                        () -> {
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

        assertTrue(sleepingSamples > 0,
                "Expected samples from context-scoped sleeping thread, got: " + sleepingSamples);
        assertTrue(parkedSamples > 0,
                "Expected samples from traced parked thread, got: " + parkedSamples);
        assertTrue(runnableSamples > 0,
                "Expected samples from runnable thread, got: " + runnableSamples);

        long suppressedAfter = profiler.getDebugCounters()
                .getOrDefault("wc_signals_suppressed_owned_block", 0L);
        assertEquals(suppressedBefore, suppressedAfter,
                "Context-scoped blocked threads must not be signal-suppression candidates");
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,wallprecheck=true";
    }

    private Map<String, Long> samplesByThreadName() {
        Map<String, Long> samplesByThread = new HashMap<>();
        IItemCollection events = verifyEvents("datadog.MethodSample", false);
        for (IItemIterable batch : events) {
            IMemberAccessor<String, IItem> threadNameAccessor =
                    JdkAttributes.EVENT_THREAD_NAME.getAccessor(batch.getType());
            if (threadNameAccessor == null) {
                continue;
            }
            for (IItem item : batch) {
                String threadName = threadNameAccessor.getMember(item);
                if (threadName != null) {
                    samplesByThread.merge(threadName, 1L, Long::sum);
                }
            }
        }
        return samplesByThread;
    }
}
