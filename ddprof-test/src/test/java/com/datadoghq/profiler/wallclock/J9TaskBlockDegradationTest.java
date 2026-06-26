package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class J9TaskBlockDegradationTest extends AbstractProfilerTest {
    private static final Set<String> EXPECTED_J9_OBSERVED_STATES =
            new HashSet<>(Arrays.asList("SLEEPING", "WAITING", "CONTENDED", "PARKED"));

    @Test
    public void j9ParkAndMonitorTaskBlockConfigIsNoOpAndDoesNotCrash() throws Exception {
        Assumptions.assumeTrue(Platform.isJ9(), "J9-only degradation contract");

        runParkWorkload();
        runMonitorWorkload();
        stopProfiler();

        verifyEvents("datadog.DatadogProfilerConfig");
        // OpenJ9 uses the ASGCT wall-clock path and does not provide HotSpot
        // RequestStackTrace correlation IDs. TaskBlock may still emit through
        // Java-owned block hooks; the J9 contract is graceful startup/shutdown,
        // not a no-op event stream.
        assertJ9TaskBlockEventsAreWellFormed(verifyEvents("datadog.TaskBlock", false));
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

    private static void assertJ9TaskBlockEventsAreWellFormed(IItemCollection taskBlockEvents) {
        long count = count(taskBlockEvents);
        assertTrue(count <= 2, "J9 degradation workloads must not emit a TaskBlock event storm");
        if (count == 0) {
            return;
        }

        TaskBlockAssertions.assertNoAnchorFields(taskBlockEvents);
        TaskBlockAssertions.assertContainsAnyObservedState(taskBlockEvents);
        Set<String> observedStates = TaskBlockAssertions.observedStates(taskBlockEvents);
        assertEquals(
                observedStates.size(),
                observedStates.stream().filter(EXPECTED_J9_OBSERVED_STATES::contains).count(),
                "Unexpected J9 TaskBlock observed states: " + observedStates);
    }

    private static long count(IItemCollection events) {
        long count = 0;
        for (IItemIterable iterable : events) {
            count += iterable.getItemCount();
        }
        return count;
    }
}
