package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.LockSupport;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Measures the theoretical upper bound on {@code SIGVTALRM} suppression by running with
 * {@code wallprecheck=false} and classifying sample states. Lifecycle ownership
 * ({@code wallprecheck=true}) suppresses {@code SLEEPING}, {@code CONDVAR_WAIT}, and
 * suppresses {@code OBJECT_WAIT}; {@code RUNNABLE} is not skipped. Monitor
 * contention ({@code MONITOR_WAIT}) is also suppressible when monitor hooks identify the blocked
 * interval.
 */
public class PrecheckEfficiencyTest extends AbstractProfilerTest {

    private static final String EFFICIENCY_SLEEPING = "efficiency-sleeping";
    private static final String EFFICIENCY_PARKED = "efficiency-parked";
    private static final String EFFICIENCY_WAITING = "efficiency-waiting";
    private static final String EFFICIENCY_WORKING = "efficiency-working";

    @Test
    public void compareSuppressionRates() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());

        CountDownLatch ready = new CountDownLatch(4);
        AtomicBoolean stop = new AtomicBoolean(false);
        Object monitor = new Object();

        // SLEEPING / CONDVAR_WAIT — suppressible with lifecycle ownership
        Thread sleeping = new Thread(() -> {
            ready.countDown();
            try { Thread.sleep(10_000); } catch (InterruptedException ignored) {}
        }, EFFICIENCY_SLEEPING);

        // CONDVAR_WAIT — suppressible with lifecycle ownership
        Thread parked = new Thread(() -> {
            ready.countDown();
            LockSupport.parkNanos(10_000_000_000L);
        }, EFFICIENCY_PARKED);

        // OBJECT_WAIT — suppressible with lifecycle ownership.
        Thread waiting = new Thread(() -> {
            ready.countDown();
            synchronized (monitor) {
                try { monitor.wait(10_000); } catch (InterruptedException ignored) {}
            }
        }, EFFICIENCY_WAITING);

        // RUNNABLE — not skipped
        Thread working = new Thread(() -> {
            ready.countDown();
            long x = 0;
            while (!stop.get()) { x++; }
        }, EFFICIENCY_WORKING);

        sleeping.setDaemon(true);
        parked.setDaemon(true);
        waiting.setDaemon(true);
        working.setDaemon(true);

        sleeping.start();
        parked.start();
        waiting.start();
        working.start();

        ready.await();
        Thread.sleep(500);

        stop.set(true);
        sleeping.interrupt();
        LockSupport.unpark(parked);
        synchronized (monitor) { monitor.notifyAll(); }

        sleeping.join(1000);
        parked.join(1000);
        waiting.join(1000);
        working.join(1000);

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.MethodSample", false);

        long sleepSamples = 0, parkSamples = 0, objectWaitSamples = 0, runnableSamples = 0;

        for (IItemIterable batch : events) {
            IMemberAccessor<String, IItem> stackAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(batch.getType());
            IMemberAccessor<String, IItem> stateAccessor = THREAD_STATE.getAccessor(batch.getType());
            IMemberAccessor<String, IItem> threadNameAccessor =
                    JdkAttributes.EVENT_THREAD_NAME.getAccessor(batch.getType());
            if (stackAccessor == null && stateAccessor == null && threadNameAccessor == null) {
                continue;
            }
            for (IItem item : batch) {
                if (threadNameAccessor != null) {
                    String threadName = threadNameAccessor.getMember(item);
                    if (EFFICIENCY_SLEEPING.equals(threadName)) {
                        sleepSamples++;
                        continue;
                    }
                    if (EFFICIENCY_PARKED.equals(threadName)) {
                        parkSamples++;
                        continue;
                    }
                    if (EFFICIENCY_WAITING.equals(threadName)) {
                        objectWaitSamples++;
                        continue;
                    }
                    if (EFFICIENCY_WORKING.equals(threadName)) {
                        runnableSamples++;
                        continue;
                    }
                }
                String state = stateAccessor != null ? stateAccessor.getMember(item) : null;
                // CONDVAR_WAIT is written as "PARKED" in JFR metadata.
                if (state != null && !state.isEmpty()) {
                    switch (state) {
                        case "SLEEPING":
                            sleepSamples++;
                            continue;
                        case "PARKED":
                            parkSamples++;
                            continue;
                        case "WAITING":
                            objectWaitSamples++;
                            continue;
                        default:
                            break;
                    }
                }
                String stack = stackAccessor != null ? stackAccessor.getMember(item) : null;
                if (stack != null && (stack.contains("Thread.sleep") || stack.contains("sleep0"))) {
                    sleepSamples++;
                } else if (stack != null && (stack.contains("LockSupport.park") || stack.contains("Unsafe.park")
                        || stack.contains("parkNanos"))) {
                    parkSamples++;
                } else if (stack != null && (stack.contains("Object.wait") || stack.contains("wait0"))) {
                    objectWaitSamples++;
                } else {
                    runnableSamples++;
                }
            }
        }

        long total = sleepSamples + parkSamples + objectWaitSamples + runnableSamples;
        if (total == 0) {
            System.out.println("No samples collected — skipping efficiency report");
            return;
        }

        double pctSleep      = 100.0 * sleepSamples      / total;
        double pctPark       = 100.0 * parkSamples        / total;
        double pctObjectWait = 100.0 * objectWaitSamples  / total;
        double pctRunnable   = 100.0 * runnableSamples    / total;

        double oncePerRunSuppression = pctSleep + pctPark + pctObjectWait;

        System.out.printf("%nPrecheck efficiency report (wallprecheck=false baseline, %d total samples):%n", total);
        System.out.printf("  SLEEPING     (Thread.sleep):      %4d samples (%5.1f%%)%n", sleepSamples, pctSleep);
        System.out.printf("  CONDVAR_WAIT (LockSupport.park):  %4d samples (%5.1f%%)%n", parkSamples, pctPark);
        System.out.printf("  OBJECT_WAIT  (Object.wait):       %4d samples (%5.1f%%)%n", objectWaitSamples, pctObjectWait);
        System.out.printf("  RUNNABLE / other:                 %4d samples (%5.1f%%)%n", runnableSamples, pctRunnable);
        System.out.printf(
                "Once-per-run filter (SLEEPING + CONDVAR_WAIT + OBJECT_WAIT): %.1f%% of signals suppressed (upper bound)%n",
                oncePerRunSuppression);

        assertTrue(sleepSamples > 0, "Expected samples from sleeping thread");
        assertTrue(parkSamples + objectWaitSamples > 0,
                "Expected WAITING/PARKED samples from parked or object-waiting threads");
        assertTrue(oncePerRunSuppression > 0.0,
                "Expected some suppressible SLEEPING/PARKED/WAITING samples");
        assertTrue(runnableSamples > 0, "Expected RUNNABLE samples (working thread or unidentified)");
    }

    /** Thread pool mostly idle (park), plus a sleep-driven scheduler and a CPU-bound thread. */
    @Test
    public void realisticServiceWorkload() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());

        final int POOL_SIZE = 8;
        final int TASK_DURATION_MS = 20;   // each submitted task takes ~20 ms
        final int SCHEDULE_INTERVAL_MS = 50; // scheduler fires every 50 ms

        AtomicBoolean stop = new AtomicBoolean(false);
        AtomicInteger threadIndex = new AtomicInteger(0);

        ExecutorService pool = Executors.newFixedThreadPool(POOL_SIZE, r -> {
            Thread t = new Thread(r);
            t.setName("realistic-pool-" + threadIndex.incrementAndGet());
            t.setDaemon(true);
            return t;
        });

        CountDownLatch primed = new CountDownLatch(POOL_SIZE);
        for (int i = 0; i < POOL_SIZE; i++) {
            pool.submit(primed::countDown);
        }
        primed.await();
        Thread.sleep(50);

        Thread scheduler = new Thread(() -> {
            while (!stop.get()) {
                try {
                    Thread.sleep(SCHEDULE_INTERVAL_MS);
                } catch (InterruptedException e) {
                    break;
                }
                pool.submit(() -> {
                    long x = 0;
                    long deadline = System.nanoTime() + TASK_DURATION_MS * 1_000_000L;
                    while (System.nanoTime() < deadline) { x++; }
                    return x;
                });
            }
        }, "realistic-scheduler");
        scheduler.setDaemon(true);
        scheduler.start();

        Thread hotThread = new Thread(() -> {
            long x = 0;
            while (!stop.get()) { x++; }
        }, "realistic-hot");
        hotThread.setDaemon(true);
        hotThread.start();

        Thread.sleep(500);

        stop.set(true);
        scheduler.interrupt();
        pool.shutdownNow();
        pool.awaitTermination(2, TimeUnit.SECONDS);
        hotThread.join(1000);

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.MethodSample", false);

        long sleepSamples = 0, parkSamples = 0, otherSamples = 0;

        for (IItemIterable batch : events) {
            IMemberAccessor<String, IItem> stackAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(batch.getType());
            IMemberAccessor<String, IItem> threadNameAccessor =
                    JdkAttributes.EVENT_THREAD_NAME.getAccessor(batch.getType());
            if (stackAccessor == null || threadNameAccessor == null) continue;
            for (IItem item : batch) {
                String threadName = threadNameAccessor.getMember(item);
                if (threadName == null || (!threadName.startsWith("realistic-pool-")
                        && !"realistic-scheduler".equals(threadName)
                        && !"realistic-hot".equals(threadName))) {
                    continue;
                }
                String stack = stackAccessor.getMember(item);
                if (stack == null) {
                    otherSamples++;
                } else if (stack.contains("Thread.sleep") || stack.contains("sleep0")) {
                    sleepSamples++;
                } else if (stack.contains("LockSupport.park") || stack.contains("Unsafe.park")) {
                    parkSamples++;
                } else {
                    otherSamples++;
                }
            }
        }

        long total = sleepSamples + parkSamples + otherSamples;
        if (total == 0) {
            System.out.println("No samples collected — skipping realistic workload report");
            return;
        }

        double pctSleep = 100.0 * sleepSamples / total;
        double pctPark  = 100.0 * parkSamples  / total;
        double pctOther = 100.0 * otherSamples  / total;

        double oncePerRunSuppression = pctSleep + pctPark;

        System.out.printf("%nRealistic service workload report (%d pool threads, 1 scheduler, 1 hot thread, 500ms):%n", POOL_SIZE);
        System.out.printf(
                "  Scheduler sleep (Thread.sleep):           %4d samples (%5.1f%%)%n", sleepSamples, pctSleep);
        System.out.printf(
                "  Idle pool park (LockSupport.park):       %4d samples (%5.1f%%)%n", parkSamples, pctPark);
        System.out.printf(
                "  RUNNABLE / other (active work):          %4d samples (%5.1f%%)%n", otherSamples, pctOther);
        System.out.printf(
                "Once-per-run filter (SLEEPING + CONDVAR_WAIT): %.1f%% of signals suppressed (upper bound)%n",
                oncePerRunSuppression);

        assertTrue(parkSamples > otherSamples,
                String.format("Expected idle pool threads (park=%d) to dominate active threads (other=%d)", parkSamples, otherSamples));
        assertTrue(sleepSamples > 0, "Expected samples from scheduler's Thread.sleep");
    }

    @Override
    protected String getProfilerCommand() {
        // The workload deliberately has no tracing context, so keep unfiltered
        // wall-clock sampling enabled explicitly.
        return "wall=1ms,filter=";
    }
}
