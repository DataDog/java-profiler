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
 * Measures how many signals each precheck strategy would suppress for a workload
 * containing threads in each blocked state. Runs with wallprecheck=false so all
 * samples are collected; the distribution reveals the theoretical suppression rate.
 *
 * Current precheck (SLEEPING only):         suppresses only Thread.sleep samples.
 * Aggressive precheck (all blocked states): would also suppress LockSupport.park and Object.wait.
 *
 * <p>Sample classification prefers Java thread name ({@code EVENT_THREAD_NAME}) for the fixed worker
 * threads when present, then JFR thread state, then stack strings — some JVMs (e.g. Graal on aarch64)
 * omit SLEEPING / {@code Thread.sleep} in state or stacks while samples still hit the worker.
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

        // Thread in SLEEPING state (Thread.sleep) — suppressed by both precheck variants
        Thread sleeping = new Thread(() -> {
            registerCurrentThreadForWallClockProfiling();
            ready.countDown();
            try { Thread.sleep(10_000); } catch (InterruptedException ignored) {}
        }, EFFICIENCY_SLEEPING);

        // Thread in CONDVAR_WAIT state (LockSupport.parkNanos) — suppressed by old precheck only
        Thread parked = new Thread(() -> {
            registerCurrentThreadForWallClockProfiling();
            ready.countDown();
            LockSupport.parkNanos(10_000_000_000L);
        }, EFFICIENCY_PARKED);

        // Thread in OBJECT_WAIT state (Object.wait) — suppressed by old precheck only
        Thread waiting = new Thread(() -> {
            registerCurrentThreadForWallClockProfiling();
            ready.countDown();
            synchronized (monitor) {
                try { monitor.wait(10_000); } catch (InterruptedException ignored) {}
            }
        }, EFFICIENCY_WAITING);

        // Thread in RUNNABLE state (CPU spin) — not suppressed by either precheck
        Thread working = new Thread(() -> {
            registerCurrentThreadForWallClockProfiling();
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
                // Native OSThreadState is written as jdk.types.ThreadState; CONDVAR_WAIT → "PARKED"
                // in JFR metadata (flightRecorder.cpp writeThreadStates). Prefer state over stacks:
                // stacks often omit LockSupport/Unsafe frames after inlining.
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

        double newPrecheckSuppression = pctSleep;
        double oldPrecheckSuppression = pctSleep + pctPark + pctObjectWait;

        System.out.printf("%nPrecheck efficiency report (wallprecheck=false baseline, %d total samples):%n", total);
        System.out.printf("  SLEEPING     (Thread.sleep):      %4d samples (%5.1f%%)%n", sleepSamples, pctSleep);
        System.out.printf("  CONDVAR_WAIT (LockSupport.park):  %4d samples (%5.1f%%)%n", parkSamples, pctPark);
        System.out.printf("  OBJECT_WAIT  (Object.wait):       %4d samples (%5.1f%%)%n", objectWaitSamples, pctObjectWait);
        System.out.printf("  RUNNABLE / other:                 %4d samples (%5.1f%%)%n", runnableSamples, pctRunnable);
        System.out.printf("Current precheck (SLEEPING only):         %.1f%% of signals suppressed%n", newPrecheckSuppression);
        System.out.printf("Aggressive precheck (all blocked states): %.1f%% of signals suppressed%n", oldPrecheckSuppression);

        // Sanity: each controlled thread type should produce at least a few samples.
        // JDK 8 can collapse park/wait into WAITING-only classification depending on runtime/JFR details.
        assertTrue(sleepSamples > 0, "Expected samples from sleeping thread");
        if (Platform.isJavaVersion(8)) {
            assertTrue(parkSamples + objectWaitSamples > 0,
                    "Expected WAITING/PARKED samples from parked or object-waiting threads on JDK 8");
        } else {
            assertTrue(parkSamples > 0, "Expected samples from parked thread");
            assertTrue(objectWaitSamples > 0, "Expected samples from object-waiting thread");
        }
        assertTrue(runnableSamples > 0, "Expected RUNNABLE samples (working thread or unidentified)");
    }

    /**
     * Simulates a typical Java service: a fixed thread pool that is mostly idle (threads parked
     * in {@code LinkedBlockingQueue.take()}), plus a scheduler thread doing periodic
     * {@code Thread.sleep} wakeups, plus a continuously-busy computation thread.
     *
     * This workload is representative of real applications where {@code LockSupport.park}
     * dominates the thread state distribution. The output shows how aggressively each
     * precheck variant would reduce signals, and what fraction of interesting blocking
     * visibility each strategy sacrifices.
     */
    @Test
    public void realisticServiceWorkload() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());

        final int POOL_SIZE = 8;
        final int TASK_DURATION_MS = 20;   // each submitted task takes ~20 ms
        final int SCHEDULE_INTERVAL_MS = 50; // scheduler fires every 50 ms

        AtomicBoolean stop = new AtomicBoolean(false);
        AtomicInteger threadIndex = new AtomicInteger(0);

        // Thread pool whose threads register themselves with the wall-clock filter.
        // When idle, pool threads sit in LinkedBlockingQueue.take() → LockSupport.park (CONDVAR_WAIT).
        ExecutorService pool = Executors.newFixedThreadPool(POOL_SIZE, r -> {
            Thread t = new Thread(() -> {
                registerCurrentThreadForWallClockProfiling();
                r.run();
            });
            t.setName("realistic-pool-" + threadIndex.incrementAndGet());
            t.setDaemon(true);
            return t;
        });

        // Pre-warm: submit N tasks so the executor creates all POOL_SIZE threads before measurement.
        CountDownLatch primed = new CountDownLatch(POOL_SIZE);
        for (int i = 0; i < POOL_SIZE; i++) {
            pool.submit(primed::countDown);
        }
        primed.await();
        Thread.sleep(50); // let all pool threads return to idle (parked) state

        // Scheduler: sleeps between submissions, simulating a periodic task trigger.
        // Thread.sleep → SLEEPING, which is what the new precheck targets.
        Thread scheduler = new Thread(() -> {
            registerCurrentThreadForWallClockProfiling();
            while (!stop.get()) {
                try {
                    Thread.sleep(SCHEDULE_INTERVAL_MS);
                } catch (InterruptedException e) {
                    break;
                }
                // Submit a short CPU task to one pool thread
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

        // Always-busy thread: simulates a background aggregation/analytics loop.
        Thread hotThread = new Thread(() -> {
            registerCurrentThreadForWallClockProfiling();
            long x = 0;
            while (!stop.get()) { x++; }
        }, "realistic-hot");
        hotThread.setDaemon(true);
        hotThread.start();

        // Measurement window
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
            if (stackAccessor == null) continue;
            for (IItem item : batch) {
                String stack = stackAccessor.getMember(item);
                if (stack == null) {
                    otherSamples++;
                } else if (stack.contains("Thread.sleep") || stack.contains("sleep0")) {
                    // SLEEPING — suppressed by new precheck
                    sleepSamples++;
                } else if (stack.contains("LockSupport.park") || stack.contains("Unsafe.park")) {
                    // CONDVAR_WAIT — suppressed by old precheck only
                    parkSamples++;
                } else {
                    // RUNNABLE or other — not suppressed by either precheck
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

        double newPrecheckSuppression = pctSleep;
        double oldPrecheckSuppression = pctSleep + pctPark;

        System.out.printf("%nRealistic service workload report (%d pool threads, 1 scheduler, 1 hot thread, 500ms):%n", POOL_SIZE);
        System.out.printf("  SLEEPING     (Thread.sleep — scheduler):  %4d samples (%5.1f%%) — new precheck suppresses these%n", sleepSamples, pctSleep);
        System.out.printf("  CONDVAR_WAIT (LockSupport.park — idle pool): %4d samples (%5.1f%%) — old precheck also suppressed these%n", parkSamples, pctPark);
        System.out.printf("  RUNNABLE / other (active threads):        %4d samples (%5.1f%%) — never suppressed%n", otherSamples, pctOther);
        System.out.printf("Current precheck (SLEEPING only):         %.1f%% of signals suppressed%n", newPrecheckSuppression);
        System.out.printf("Aggressive precheck (all blocked states): %.1f%% of signals suppressed%n", oldPrecheckSuppression);

        // The idle pool threads should dominate: most samples should be parked
        assertTrue(parkSamples > otherSamples,
                String.format("Expected idle pool threads (park=%d) to dominate active threads (other=%d)", parkSamples, otherSamples));
        // The scheduler must appear (it sleeps 50ms at a time over 500ms → ~10 cycles)
        assertTrue(sleepSamples > 0, "Expected samples from scheduler's Thread.sleep");
    }

    @Override
    protected String getProfilerCommand() {
        // Run with no suppression so all states are sampled; we infer the suppression rates
        // from the sample distribution.
        return "wall=1ms,wallprecheck=false";
    }
}
