package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Map;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.LockSupport;

import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

/**
 * Regression guard for the timer-thread fast path: when a thread is in a {@code SLEEPING} /
 * {@code CONDVAR_WAIT} run and has already produced its entry sample, the timer elides
 * {@code pthread_kill} entirely (skipping the cross-CPU IPI). Verified by comparing the
 * {@code wallclock_signal_own} counter between a {@code wallprecheck=false} baseline run and a
 * {@code wallprecheck=true} run — the counter must drop by ≥50%.
 */
public class WallclockTimerFastPathTest extends AbstractProfilerTest {

    private static final String COUNTER_KEY = "wallclock_signal_own";
    private static final long SAMPLING_INTERVAL_MS = 10L;

    // CI noise (boundary jitter, warmup) keeps us at 50%; working fast path routinely sees <25%.
    private static final double MAX_ALLOWED_RATIO = 0.5;

    @Test
    public void timerElidesIpiForLongParkRuns() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));

        Map<String, Long> beforeA = profiler.getDebugCounters();
        Assumptions.assumeTrue(beforeA.containsKey(COUNTER_KEY),
                "wallclock_signal_own counter not available (build without COUNTERS)");

        runParkWorkload("fastpath-park-A");
        stopProfiler();
        long signalsA = signalDelta(beforeA, profiler.getDebugCounters());

        Path recordingB = Files.createTempFile(Paths.get("/tmp/recordings"),
                "WallclockTimerFastPathTest_park_B_", ".jfr");
        profiler.execute("start,wall=" + SAMPLING_INTERVAL_MS + "ms,wallprecheck=true,filter=0"
                + ",attributes=tag1;tag2;tag3,jfr,file=" + recordingB.toAbsolutePath());
        Map<String, Long> beforeB = profiler.getDebugCounters();
        runParkWorkload("fastpath-park-B");
        profiler.stop();
        long signalsB = signalDelta(beforeB, profiler.getDebugCounters());

        Files.deleteIfExists(recordingB);

        assertIpiFastPathEngaged("park", signalsA, signalsB);
    }

    @Test
    public void timerElidesIpiForRealisticServiceWorkload() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));

        Map<String, Long> beforeA = profiler.getDebugCounters();
        Assumptions.assumeTrue(beforeA.containsKey(COUNTER_KEY),
                "wallclock_signal_own counter not available (build without COUNTERS)");

        runRealisticWorkload("realistic-A");
        stopProfiler();
        long signalsA = signalDelta(beforeA, profiler.getDebugCounters());

        Path recordingB = Files.createTempFile(Paths.get("/tmp/recordings"),
                "WallclockTimerFastPathTest_realistic_B_", ".jfr"); // recording B: wallprecheck=true
        profiler.execute("start,wall=" + SAMPLING_INTERVAL_MS + "ms,wallprecheck=true,filter=0"
                + ",attributes=tag1;tag2;tag3,jfr,file=" + recordingB.toAbsolutePath());
        Map<String, Long> beforeB = profiler.getDebugCounters();
        runRealisticWorkload("realistic-B");
        profiler.stop();
        long signalsB = signalDelta(beforeB, profiler.getDebugCounters());

        Files.deleteIfExists(recordingB);

        assertIpiFastPathEngaged("realistic", signalsA, signalsB);
    }

    private long signalDelta(Map<String, Long> before, Map<String, Long> after) {
        return after.getOrDefault(COUNTER_KEY, 0L) - before.getOrDefault(COUNTER_KEY, 0L);
    }

    private void assertIpiFastPathEngaged(String tag, long signalsA, long signalsB) {
        double ratio = signalsA == 0 ? Double.NaN : (double) signalsB / signalsA;
        System.out.printf(
                "%nWallclockTimerFastPathTest [%s]:%n"
                        + "  Recording A (wallprecheck=false): wallclock_signal_own delta = %d%n"
                        + "  Recording B (wallprecheck=true ): wallclock_signal_own delta = %d%n"
                        + "  ratio B/A = %.3f (max allowed %.3f)%n",
                tag, signalsA, signalsB, ratio, MAX_ALLOWED_RATIO);

        assertTrue(signalsA > 20,
                "recording A: baseline produced too few wallclock_signal_own ticks (" + signalsA
                        + "); workload may not be running long enough");

        assertTrue(signalsB < signalsA * MAX_ALLOWED_RATIO,
                "timer fast path appears disengaged: recording A delivered " + signalsA
                        + " signals, recording B delivered " + signalsB
                        + " (ratio " + String.format("%.3f", ratio)
                        + "; expected < " + MAX_ALLOWED_RATIO + ")");
    }

    private void runParkWorkload(String workerName) throws Exception {
        final int PARK_RUNS = 100;
        final long PARK_NANOS = 100_000_000L; // 100 ms per run
        AtomicBoolean stop = new AtomicBoolean(false);

        Thread worker = new Thread(() -> {
            registerCurrentThreadForWallClockProfiling();
            profiler.setContext(0x5678L, 0x1234L, 0, 0);
            try {
                for (int i = 0; i < PARK_RUNS && !stop.get(); i++) {
                    profiler.parkEnter();
                    long deadline = System.nanoTime() + PARK_NANOS;
                    long remaining;
                    while (!stop.get() && (remaining = deadline - System.nanoTime()) > 0) {
                        LockSupport.parkNanos(remaining);
                    }
                    profiler.parkExit(System.identityHashCode(this), 0L);
                }
            } finally {
                profiler.clearContext();
            }
        }, workerName);
        worker.setDaemon(true);
        worker.start();
        worker.join();
    }

    private void runRealisticWorkload(String tag) throws Exception {
        final int POOL_SIZE = 8;
        final int TASK_DURATION_MS = 20;
        final int SCHEDULE_INTERVAL_MS = 50;
        final int MEASUREMENT_MS = 1000;

        AtomicBoolean stop = new AtomicBoolean(false);
        AtomicInteger threadIndex = new AtomicInteger(0);

        ExecutorService pool = Executors.newFixedThreadPool(POOL_SIZE, r -> {
            Thread t = new Thread(() -> {
                registerCurrentThreadForWallClockProfiling();
                r.run();
            });
            t.setName(tag + "-pool-" + threadIndex.incrementAndGet());
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
            registerCurrentThreadForWallClockProfiling();
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
        }, tag + "-scheduler");
        scheduler.setDaemon(true);
        scheduler.start();

        Thread hot = new Thread(() -> {
            registerCurrentThreadForWallClockProfiling();
            long x = 0;
            while (!stop.get()) { x++; }
        }, tag + "-hot");
        hot.setDaemon(true);
        hot.start();

        Thread.sleep(MEASUREMENT_MS);

        stop.set(true);
        scheduler.interrupt();
        pool.shutdownNow();
        pool.awaitTermination(2, TimeUnit.SECONDS);
        hot.join(1000);
        scheduler.join(1000);
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=" + SAMPLING_INTERVAL_MS + "ms,wallprecheck=false,filter=0";
    }
}
