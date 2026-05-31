package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;

import java.lang.reflect.Method;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class VirtualThreadTaskBlockTest extends AbstractProfilerTest {
    private static final long WAIT_ROOT_SPAN_ID = 0x1100L;
    private static final long WAIT_SPAN_ID = 0x1101L;
    private static final long CONTENTION_ROOT_SPAN_ID = 0x2200L;
    private static final long CONTENTION_SPAN_ID = 0x2201L;

    @Test
    public void virtualObjectWaitDoesNotEmitCarrierTaskBlock() throws Exception {
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
        stopProfiler();

        assertFalse(
                taskBlockEventsContainSpan(WAIT_SPAN_ID),
                "virtual Object.wait must not be emitted as a carrier-thread TaskBlock");
    }

    @Test
    public void virtualSynchronizedContentionDoesNotEmitCarrierTaskBlock() throws Exception {
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
        stopProfiler();

        assertFalse(
                taskBlockEventsContainSpan(CONTENTION_SPAN_ID),
                "virtual synchronized contention must not be emitted as a carrier-thread TaskBlock");
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
