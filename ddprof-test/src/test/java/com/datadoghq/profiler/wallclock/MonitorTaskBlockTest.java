package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Test;

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

        TaskBlockAssertions.assertContains(
                verifyEvents("datadog.TaskBlock"),
                WAIT_ROOT_SPAN_ID, WAIT_SPAN_ID, identityHash(monitor), 0L);
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

        TaskBlockAssertions.assertContains(
                verifyEvents("datadog.TaskBlock"),
                CONTENTION_ROOT_SPAN_ID, CONTENTION_SPAN_ID, identityHash(monitor), 0L);
    }

    @Override
    protected boolean isPlatformSupported() {
        return !Platform.isJ9() && !Platform.isZing();
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,filter=0,wallprecheck=true";
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
