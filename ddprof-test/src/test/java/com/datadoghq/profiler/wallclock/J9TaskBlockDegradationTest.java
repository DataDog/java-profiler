package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class J9TaskBlockDegradationTest extends AbstractProfilerTest {
    @Test
    public void j9ParkAndMonitorTaskBlockConfigIsNoOpAndDoesNotCrash() throws Exception {
        Assumptions.assumeTrue(Platform.isJ9(), "J9-only degradation contract");

        runParkWorkload();
        runMonitorWorkload();
        stopProfiler();

        IItemCollection taskBlockEvents = verifyEvents("datadog.TaskBlock", false);
        assertFalse(taskBlockEvents.hasItems(),
                "J9 does not support TaskBlock emission and should degrade to no-op behavior");
    }

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isJ9();
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,filter=0,wallprecheck=true,jvmtistacks=true";
    }

    private void runParkWorkload() throws InterruptedException {
        CountDownLatch started = new CountDownLatch(1);
        AtomicReference<Throwable> error = new AtomicReference<>();
        Thread thread = new Thread(() -> {
            try {
                registerCurrentThreadForWallClockProfiling();
                started.countDown();
                Thread.sleep(80L);
            } catch (Throwable t) {
                error.set(t);
            }
        }, "taskblock-j9-park");

        thread.start();
        assertTrue(started.await(5, TimeUnit.SECONDS), "park workload did not start");
        assertCompleted(thread, error);
    }

    private void runMonitorWorkload() throws InterruptedException {
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
            }, "taskblock-j9-monitor");

            thread.start();
            assertTrue(attempting.await(5, TimeUnit.SECONDS), "monitor workload did not start");
            Thread.sleep(80L);
        }
        assertCompleted(thread, error);
    }

    private static void assertCompleted(Thread thread, AtomicReference<Throwable> error)
            throws InterruptedException {
        thread.join(5_000L);
        assertFalse(thread.isAlive(), thread.getName() + " did not complete");
        if (error.get() != null) {
            throw new AssertionError(error.get());
        }
    }
}
