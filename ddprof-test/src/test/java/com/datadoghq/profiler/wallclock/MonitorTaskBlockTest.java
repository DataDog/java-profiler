package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class MonitorTaskBlockTest extends AbstractProfilerTest {
    private static final long WAIT_ROOT_SPAN_ID = 0L;
    private static final long WAIT_SPAN_ID = 0L;
    private static final long CONTENTION_ROOT_SPAN_ID = 0L;
    private static final long CONTENTION_SPAN_ID = 0L;

    @Test
    public void platformObjectWaitEmitsTaskBlock() throws Exception {
        Object monitor = new Object();
        CountDownLatch waiting = new CountDownLatch(1);
        AtomicReference<Throwable> error = new AtomicReference<>();

        Thread thread = new Thread(() -> {
            try {
                registerCurrentThreadForWallClockProfiling();
                synchronized (monitor) {
                    waiting.countDown();
                    monitor.wait(50L);
                }
            } catch (Throwable t) {
                error.set(t);
            }
        }, "taskblock-object-wait");

        thread.start();
        assertTrue(waiting.await(5, TimeUnit.SECONDS), "platform thread did not enter Object.wait");
        assertCompleted(thread, error);
        stopProfiler();

        IItemCollection taskBlockEvents = verifyEvents("datadog.TaskBlock");
        TaskBlockAssertions.assertNoAnchorFields(taskBlockEvents);
        assertTaskBlockStackReference(taskBlockEvents);
        TaskBlockAssertions.assertContains(
                taskBlockEvents, WAIT_ROOT_SPAN_ID, WAIT_SPAN_ID, identityHash(monitor), 0L);
        TaskBlockAssertions.assertContainsObservedState(taskBlockEvents, "WAITING");
    }

    @Test
    public void platformMonitorContentionEmitsTaskBlock() throws Exception {
        Object monitor = new Object();
        CountDownLatch attempting = new CountDownLatch(1);
        AtomicReference<Throwable> error = new AtomicReference<>();

        Thread thread;
        synchronized (monitor) {
            thread = new Thread(() -> {
                try {
                    registerCurrentThreadForWallClockProfiling();
                    attempting.countDown();
                    synchronized (monitor) {
                    }
                } catch (Throwable t) {
                    error.set(t);
                }
            }, "taskblock-monitor-contention");

            thread.start();
            assertTrue(
                    attempting.await(5, TimeUnit.SECONDS),
                    "platform thread did not attempt monitor acquisition");
            Thread.sleep(50L);
        }

        assertCompleted(thread, error);
        stopProfiler();

        IItemCollection taskBlockEvents = verifyEvents("datadog.TaskBlock");
        TaskBlockAssertions.assertNoAnchorFields(taskBlockEvents);
        assertTaskBlockStackReference(taskBlockEvents);
        TaskBlockAssertions.assertContains(
                taskBlockEvents, CONTENTION_ROOT_SPAN_ID, CONTENTION_SPAN_ID,
                identityHash(monitor), 0L);
        TaskBlockAssertions.assertContainsObservedState(taskBlockEvents, "CONTENDED");
    }

    @Test
    public void tracedObjectWaitDoesNotEmitTaskBlock() throws Exception {
        Object monitor = new Object();
        CountDownLatch waiting = new CountDownLatch(1);
        AtomicReference<Throwable> error = new AtomicReference<>();

        Thread thread = new Thread(() -> {
            try {
                registerCurrentThreadForWallClockProfiling();
                profiler.setContext(0x4400L, 0x4401L, 0L, 0x4401L);
                synchronized (monitor) {
                    waiting.countDown();
                    monitor.wait(50L);
                }
            } catch (Throwable t) {
                error.set(t);
            } finally {
                profiler.clearContext();
            }
        }, "taskblock-traced-object-wait");

        thread.start();
        assertTrue(waiting.await(5, TimeUnit.SECONDS), "platform thread did not enter Object.wait");
        assertCompleted(thread, error);
        stopProfiler();

        assertFalse(
                TaskBlockAssertions.containsSpan(verifyEvents("datadog.TaskBlock", false), 0x4401L),
                "Traced Object.wait must keep MethodSample wall-clock data instead of TaskBlock");
        assertTrue(getRecordedCounterValue("task_block_skipped_trace_context") > 0);
    }

    @Test
    public void tracedMonitorContentionDoesNotEmitTaskBlock() throws Exception {
        Object monitor = new Object();
        CountDownLatch attempting = new CountDownLatch(1);
        AtomicReference<Throwable> error = new AtomicReference<>();

        Thread thread;
        synchronized (monitor) {
            thread = new Thread(() -> {
                try {
                    registerCurrentThreadForWallClockProfiling();
                    profiler.setContext(0x4500L, 0x4501L, 0L, 0x4501L);
                    attempting.countDown();
                    synchronized (monitor) {
                    }
                } catch (Throwable t) {
                    error.set(t);
                } finally {
                    profiler.clearContext();
                }
            }, "taskblock-traced-monitor-contention");

            thread.start();
            assertTrue(
                    attempting.await(5, TimeUnit.SECONDS),
                    "platform thread did not attempt monitor acquisition");
            Thread.sleep(50L);
        }

        assertCompleted(thread, error);
        stopProfiler();

        assertFalse(
                TaskBlockAssertions.containsSpan(verifyEvents("datadog.TaskBlock", false), 0x4501L),
                "Traced monitor contention must keep MethodSample wall-clock data instead of TaskBlock");
        assertTrue(getRecordedCounterValue("task_block_skipped_trace_context") > 0);
    }

    @Override
    protected boolean isPlatformSupported() {
        return !Platform.isJ9() && !Platform.isZing();
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,filter=0,wallprecheck=true";
    }

    protected void assertTaskBlockStackReference(IItemCollection taskBlockEvents) {
        TaskBlockAssertions.assertContainsStackTrace(taskBlockEvents);
    }

    private static void assertCompleted(Thread thread, AtomicReference<Throwable> error)
            throws InterruptedException {
        thread.join(5_000L);
        assertFalse(thread.isAlive(), "platform thread did not complete");
        if (error.get() != null) {
            throw new AssertionError(error.get());
        }
    }

    private static long identityHash(Object object) {
        return Integer.toUnsignedLong(System.identityHashCode(object));
    }
}
