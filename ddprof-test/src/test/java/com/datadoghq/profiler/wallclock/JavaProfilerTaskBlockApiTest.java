/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class JavaProfilerTaskBlockApiTest extends AbstractProfilerTest {
    private static final int OSTHREAD_STATE_SLEEPING = 7;
    private static final long BLOCKER = 0x7301L;
    private static final long UNBLOCKING_SPAN_ID = 0x7302L;

    @Test
    public void pairedApiEmitsTaskBlockWithStack() throws Exception {
        assertTrue(runEligibleBlock(BLOCKER));
        stopProfiler();

        IItemCollection events = verifyEvents("datadog.TaskBlock");
        TaskBlockAssertions.assertNoAnchorFields(events);
        TaskBlockAssertions.assertContainsStackTrace(events);
        TaskBlockAssertions.assertContains(events, 0L, 0L, BLOCKER, UNBLOCKING_SPAN_ID);
        TaskBlockAssertions.assertContainsObservedState(events, "SLEEPING");
    }

    @Test
    public void pairedApiRejectsNestedAndInvalidTokensWithoutLosingOwner() throws Exception {
        AtomicReference<Throwable> error = new AtomicReference<>();
        AtomicBoolean recorded = new AtomicBoolean();
        Thread worker = new Thread(() -> {
            try {
                registerCurrentThreadForWallClockProfiling();
                long token = profiler.beginTaskBlock(OSTHREAD_STATE_SLEEPING);
                assertTrue(token != 0, "first interval must be armed");
                assertEquals(0L, profiler.beginTaskBlock(OSTHREAD_STATE_SLEEPING));
                assertFalse(profiler.endTaskBlock(token + 1, BLOCKER, UNBLOCKING_SPAN_ID));
                Thread.sleep(200L);
                recorded.set(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
            } catch (Throwable t) {
                error.set(t);
            }
        }, "taskblock-paired-owner");

        worker.start();
        worker.join(5_000L);
        assertFalse(worker.isAlive());
        if (error.get() != null) {
            throw new AssertionError(error.get());
        }
        assertTrue(recorded.get());
    }

    @Test
    public void pairedApiRejectsTooShortIntervalAndClearsLifecycle() throws Exception {
        AtomicBoolean recorded = new AtomicBoolean(true);
        AtomicLong secondToken = new AtomicLong();
        runRegistered(() -> {
            long token = profiler.beginTaskBlock(OSTHREAD_STATE_SLEEPING);
            recorded.set(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
            secondToken.set(profiler.beginTaskBlock(OSTHREAD_STATE_SLEEPING));
            profiler.endTaskBlock(secondToken.get(), BLOCKER, UNBLOCKING_SPAN_ID);
        });

        assertFalse(recorded.get());
        assertTrue(secondToken.get() != 0, "failed emission must still clear lifecycle state");
        stopProfiler();
        assertTrue(getRecordedCounterValue("task_block_skipped_too_short") > 0);
    }

    @Test
    public void taskBlockSpanningLiveDumpKeepsStackReference() throws Exception {
        CountDownLatch armed = new CountDownLatch(1);
        CountDownLatch release = new CountDownLatch(1);
        AtomicBoolean recorded = new AtomicBoolean();
        AtomicReference<Throwable> error = new AtomicReference<>();
        long suppressedBefore = profiler.getDebugCounters()
                .getOrDefault("wc_signals_suppressed_sampled_run", 0L);
        Thread worker = new Thread(() -> {
            try {
                registerCurrentThreadForWallClockProfiling();
                long token = profiler.beginTaskBlock(OSTHREAD_STATE_SLEEPING);
                assertTrue(token != 0, "interval must be armed");
                armed.countDown();
                assertTrue(release.await(5, TimeUnit.SECONDS));
                recorded.set(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
            } catch (Throwable t) {
                error.set(t);
            }
        }, "taskblock-live-dump");

        worker.start();
        assertTrue(armed.await(5, TimeUnit.SECONDS));
        waitForCounterAbove("wc_signals_suppressed_sampled_run", suppressedBefore, 5_000L);
        Path snapshot = Files.createTempFile("taskblock-live-dump-", ".jfr");
        try {
            dump(snapshot);
        } finally {
            Files.deleteIfExists(snapshot);
        }
        release.countDown();
        worker.join(5_000L);
        assertFalse(worker.isAlive());
        if (error.get() != null) {
            throw new AssertionError(error.get());
        }
        assertTrue(recorded.get());

        stopProfiler();
        IItemCollection events = verifyEvents("datadog.TaskBlock");
        TaskBlockAssertions.assertContainsStackTrace(events);
        TaskBlockAssertions.assertContainsEventThread(events);
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,filter=0,wallprecheck=true";
    }

    private boolean runEligibleBlock(long blocker) throws Exception {
        AtomicBoolean result = new AtomicBoolean();
        runRegistered(() -> {
            long token = profiler.beginTaskBlock(OSTHREAD_STATE_SLEEPING);
            if (token == 0) {
                throw new AssertionError("interval was not armed");
            }
            Thread.sleep(200L);
            result.set(profiler.endTaskBlock(token, blocker, UNBLOCKING_SPAN_ID));
        });
        return result.get();
    }

    private void runRegistered(ThrowingRunnable action) throws Exception {
        AtomicReference<Throwable> error = new AtomicReference<>();
        Thread worker = new Thread(() -> {
            try {
                registerCurrentThreadForWallClockProfiling();
                action.run();
            } catch (Throwable t) {
                error.set(t);
            }
        }, "taskblock-paired-api");
        worker.start();
        worker.join(5_000L);
        assertFalse(worker.isAlive());
        if (error.get() != null) {
            throw new AssertionError(error.get());
        }
    }

    private void waitForCounterAbove(String name, long baseline, long timeoutMillis) throws Exception {
        long deadline = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(timeoutMillis);
        while (System.nanoTime() < deadline) {
            if (profiler.getDebugCounters().getOrDefault(name, 0L) > baseline) {
                return;
            }
            Thread.sleep(10L);
        }
        throw new AssertionError("counter did not increase above " + baseline + ": " + name);
    }

    @FunctionalInterface
    private interface ThrowingRunnable {
        void run() throws Exception;
    }
}
