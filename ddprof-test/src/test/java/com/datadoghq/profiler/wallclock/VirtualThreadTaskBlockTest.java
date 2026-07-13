/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;

import java.lang.reflect.Method;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/** Verifies that logical virtual-thread operations never mutate carrier-owned TaskBlock state. */
public class VirtualThreadTaskBlockTest extends AbstractProfilerTest {
    private static final int OSTHREAD_STATE_SLEEPING = 7;
    private static final long WAIT_ROOT_SPAN_ID = 0x1100L;
    private static final long WAIT_SPAN_ID = 0x1101L;
    private static final long CONTENTION_ROOT_SPAN_ID = 0x2200L;
    private static final long CONTENTION_SPAN_ID = 0x2201L;
    private static final long PAIRED_BLOCKER = 0x3301L;
    private static final long PARK_BLOCKER = 0x3302L;
    private static final long OWNER_BLOCKER = 0x3303L;
    private static volatile long busySink;

    @Test
    public void virtualObjectWaitDoesNotEmitCarrierTaskBlock() throws Exception {
        long suppressedBefore = debugCounter("wc_signals_suppressed_sampled_run");
        Object monitor = new Object();
        CountDownLatch waiting = new CountDownLatch(1);
        AtomicReference<Throwable> error = new AtomicReference<>();

        Thread thread =
                startVirtualThread(
                        () -> {
                            try {
                                registerCurrentThreadForWallClockProfiling();
                                profiler.setContext(WAIT_ROOT_SPAN_ID, WAIT_SPAN_ID, 0L, WAIT_SPAN_ID);
                                synchronized (monitor) {
                                    waiting.countDown();
                                    monitor.wait(50L);
                                }
                            } catch (Throwable t) {
                                error.set(t);
                            } finally {
                                profiler.clearContext();
                            }
                        });

        assertTrue(waiting.await(5, TimeUnit.SECONDS), "virtual thread did not enter wait");
        assertCompleted(thread, error);
        assertEquals(suppressedBefore, debugCounter("wc_signals_suppressed_sampled_run"));
        stopProfiler();

        assertFalse(
                taskBlockEventsContainSpan(WAIT_SPAN_ID),
                "virtual Object.wait must not be emitted as a carrier-thread TaskBlock");
    }

    @Test
    public void virtualSynchronizedContentionDoesNotEmitCarrierTaskBlock() throws Exception {
        long suppressedBefore = debugCounter("wc_signals_suppressed_sampled_run");
        Object monitor = new Object();
        CountDownLatch attempting = new CountDownLatch(1);
        AtomicReference<Throwable> error = new AtomicReference<>();

        Thread thread;
        synchronized (monitor) {
            thread =
                    startVirtualThread(
                            () -> {
                                try {
                                    registerCurrentThreadForWallClockProfiling();
                                    profiler.setContext(
                                            CONTENTION_ROOT_SPAN_ID, CONTENTION_SPAN_ID, 0L,
                                            CONTENTION_SPAN_ID);
                                    attempting.countDown();
                                    synchronized (monitor) {
                                        // The carrier-attribution bug happens before this monitor is acquired.
                                    }
                                } catch (Throwable t) {
                                    error.set(t);
                                } finally {
                                    profiler.clearContext();
                                }
                            });

            assertTrue(
                    attempting.await(5, TimeUnit.SECONDS),
                    "virtual thread did not attempt monitor acquisition");
            Thread.sleep(50L);
        }

        assertCompleted(thread, error);
        assertEquals(suppressedBefore, debugCounter("wc_signals_suppressed_sampled_run"));
        stopProfiler();

        assertFalse(
                taskBlockEventsContainSpan(CONTENTION_SPAN_ID),
                "virtual synchronized contention must not be emitted as a carrier-thread TaskBlock");
    }

    @Test
    public void pairedTaskBlockApiRejectsVirtualThreadWithoutArmingCarrier() throws Exception {
        long suppressedBefore = debugCounter("wc_signals_suppressed_sampled_run");
        long emittedBefore = debugCounter("task_block_emitted");
        AtomicReference<Throwable> error = new AtomicReference<>();
        AtomicLong token = new AtomicLong(-1L);
        Thread thread = startVirtualThread(() -> {
            try {
                registerCurrentThreadForWallClockProfiling();
                long armed = profiler.beginTaskBlock(OSTHREAD_STATE_SLEEPING);
                token.set(armed);
                stayMountedForSampling();
                if (armed != 0L) {
                    profiler.endTaskBlock(armed, PAIRED_BLOCKER, 0L);
                }
            } catch (Throwable t) {
                error.set(t);
            }
        });

        assertCompleted(thread, error);
        assertEquals(0L, token.get(), "virtual thread must not receive a TaskBlock token");
        assertEquals(suppressedBefore, debugCounter("wc_signals_suppressed_sampled_run"));
        assertEquals(emittedBefore, debugCounter("task_block_emitted"));
        stopProfiler();
        assertFalse(TaskBlockAssertions.containsBlocker(
                verifyEvents("datadog.TaskBlock", false), PAIRED_BLOCKER));
    }

    @Test
    public void blockHookRejectsVirtualThreadWithoutArmingCarrier() throws Exception {
        long suppressedBefore = debugCounter("wc_signals_suppressed_sampled_run");
        AtomicReference<Throwable> error = new AtomicReference<>();
        AtomicLong token = new AtomicLong(-1L);
        Thread thread = startVirtualThread(() -> {
            try {
                registerCurrentThreadForWallClockProfiling();
                long armed = ProfilerOwnedBlockHooks.blockEnter(
                        profiler, OSTHREAD_STATE_SLEEPING);
                token.set(armed);
                stayMountedForSampling();
                ProfilerOwnedBlockHooks.blockExit(profiler, armed);
            } catch (Throwable t) {
                error.set(t);
            }
        });

        assertCompleted(thread, error);
        assertEquals(0L, token.get(), "virtual thread must not arm a blocked run");
        assertEquals(suppressedBefore, debugCounter("wc_signals_suppressed_sampled_run"));
    }

    @Test
    public void parkHooksRejectVirtualThreadWithoutCarrierEventOrSuppression() throws Exception {
        long suppressedBefore = debugCounter("wc_signals_suppressed_sampled_run");
        long emittedBefore = debugCounter("task_block_emitted");
        AtomicReference<Throwable> error = new AtomicReference<>();
        Thread thread = startVirtualThread(() -> {
            try {
                registerCurrentThreadForWallClockProfiling();
                ProfilerOwnedBlockHooks.parkEnter(profiler);
                stayMountedForSampling();
                ProfilerOwnedBlockHooks.parkExit(profiler, PARK_BLOCKER, 0L);
            } catch (Throwable t) {
                error.set(t);
            }
        });

        assertCompleted(thread, error);
        assertEquals(suppressedBefore, debugCounter("wc_signals_suppressed_sampled_run"));
        assertEquals(emittedBefore, debugCounter("task_block_emitted"));
        stopProfiler();
        assertFalse(TaskBlockAssertions.containsBlocker(
                verifyEvents("datadog.TaskBlock", false), PARK_BLOCKER));
    }

    @Test
    public void virtualThreadCannotEndPlatformOwnedTaskBlock() throws Exception {
        CountDownLatch armed = new CountDownLatch(1);
        CountDownLatch intruderFinished = new CountDownLatch(1);
        AtomicLong token = new AtomicLong();
        AtomicBoolean ownerRecorded = new AtomicBoolean();
        AtomicBoolean intruderRecorded = new AtomicBoolean(true);
        AtomicReference<Throwable> ownerError = new AtomicReference<>();
        AtomicReference<Throwable> intruderError = new AtomicReference<>();

        Thread owner = new Thread(() -> {
            try {
                registerCurrentThreadForWallClockProfiling();
                long ownerToken = profiler.beginTaskBlock(OSTHREAD_STATE_SLEEPING);
                assertTrue(ownerToken != 0L, "platform owner must arm TaskBlock");
                token.set(ownerToken);
                armed.countDown();
                assertTrue(intruderFinished.await(5, TimeUnit.SECONDS));
                Thread.sleep(200L);
                ownerRecorded.set(profiler.endTaskBlock(ownerToken, OWNER_BLOCKER, 0L));
            } catch (Throwable t) {
                ownerError.set(t);
            }
        }, "taskblock-platform-owner");
        owner.start();
        assertTrue(armed.await(5, TimeUnit.SECONDS), "platform owner did not arm TaskBlock");

        Thread intruder = startVirtualThread(() -> {
            try {
                intruderRecorded.set(profiler.endTaskBlock(token.get(), OWNER_BLOCKER, 0L));
            } catch (Throwable t) {
                intruderError.set(t);
            } finally {
                intruderFinished.countDown();
            }
        });

        assertCompleted(intruder, intruderError);
        owner.join(5_000L);
        assertFalse(owner.isAlive(), "platform owner did not complete");
        if (ownerError.get() != null) {
            throw new AssertionError(ownerError.get());
        }
        assertFalse(intruderRecorded.get(), "virtual thread must not consume a platform token");
        assertTrue(ownerRecorded.get(), "platform owner must retain and record its interval");

        stopProfiler();
        TaskBlockAssertions.assertContainsBlocker(
                verifyEvents("datadog.TaskBlock"), OWNER_BLOCKER);
    }

    @Test
    public void nativeBlockOnVirtualThreadRemainsPhysicalCarrierTaskBlock() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux(), "native blocking interception is Linux-only");
        AtomicLong blocker = new AtomicLong();
        AtomicReference<Throwable> error = new AtomicReference<>();
        Thread thread = startVirtualThread(() -> {
            try {
                registerCurrentThreadForWallClockProfiling();
                for (int attempt = 0; attempt < 3; attempt++) {
                    blocker.set(NativeIoBlockHelper.blockingPpoll(200));
                }
            } catch (Throwable t) {
                error.set(t);
            }
        });

        long logicalThreadId = thread.getId();
        assertCompleted(thread, error);
        stopProfiler();

        IItemCollection events = verifyEvents("datadog.TaskBlock");
        TaskBlockAssertions.assertContainsBlocker(events, blocker.get());
        TaskBlockAssertions.assertContainsObservedState(events, "IO_WAIT");
        TaskBlockAssertions.assertContainsStackTrace(events);
        TaskBlockAssertions.assertBlockerEventThreadDiffers(
                events, blocker.get(), logicalThreadId);
    }

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isJavaVersionAtLeast(21) && !Platform.isJ9();
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,filter=0,wallprecheck=true";
    }

    private static Thread startVirtualThread(Runnable task) throws Exception {
        Method startVirtualThread = Thread.class.getMethod("startVirtualThread", Runnable.class);
        return (Thread) startVirtualThread.invoke(null, task);
    }

    private static void assertCompleted(Thread thread, AtomicReference<Throwable> error)
            throws InterruptedException {
        thread.join(5_000L);
        assertFalse(thread.isAlive(), "virtual thread did not complete");
        if (error.get() != null) {
            throw new AssertionError(error.get());
        }
    }

    /** Keeps the virtual thread mounted so a leaked carrier blocked-run is sampled and suppressed. */
    private static void stayMountedForSampling() {
        long value = busySink;
        long deadline = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(200L);
        while (System.nanoTime() < deadline) {
            value = (value * 31L) + 1L;
        }
        busySink = value;
    }

    private long debugCounter(String name) {
        return profiler.getDebugCounters().getOrDefault(name, 0L);
    }

    private boolean taskBlockEventsContainSpan(long spanId) {
        IItemCollection events = verifyEvents("datadog.TaskBlock", false);
        for (IItemIterable iterable : events) {
            IMemberAccessor<IQuantity, IItem> spanAccessor = SPAN_ID.getAccessor(iterable.getType());
            if (spanAccessor == null) {
                continue;
            }
            for (IItem item : iterable) {
                if (spanAccessor.getMember(item).longValue() == spanId) {
                    return true;
                }
            }
        }
        return false;
    }
}
