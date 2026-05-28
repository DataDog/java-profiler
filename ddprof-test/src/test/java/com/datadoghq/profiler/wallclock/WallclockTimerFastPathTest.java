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
 * Regression guard for the wall-clock timer-side fast path that <strong>elides</strong>
 * {@code pthread_kill}/{@code SIGVTALRM} delivery (and the cross-CPU IPIs it triggers) when a
 * registered thread is in a {@code SLEEPING} / {@code CONDVAR_WAIT} run and has already produced
 * its one entry {@code MethodSample}.
 *
 * <p>The handler-side once-per-run filter (covered by {@link PrecheckTest} and {@link
 * TaskBlockCoverageTest}) suppresses <em>JFR events</em> after the entry sample, but the signals
 * still fire. The fast path on the timer thread reads the same slot state and skips the syscall
 * entirely — that is the property that actually reduces wakeups/IPIs on the production target.
 *
 * <p>{@link PrecheckTest} and {@link WallclockPrecheckBaselineTest} only assert on emitted JFR
 * events, which are unaffected by whether the signal was elided at the timer or dropped in the
 * handler. So if the timer fast path regresses (e.g. someone takes the slot lookup out, or the
 * memory ordering breaks visibility of the {@code sampled_this_run} flag), those tests still pass
 * and the IPI savings are silently lost. This test fills that gap by comparing the {@code
 * wallclock_signal_own} counter (incremented once per handler invocation == once per delivered
 * signal) between a {@code wallprecheck=false} baseline run and a {@code wallprecheck=true} run.
 *
 * <p>Two complementary workloads:
 * <ul>
 *   <li>{@link #timerElidesIpiForLongParkRuns()} — one worker, long {@code LockSupport.parkNanos}
 *       runs. Maximises the elision ratio (most ticks land inside a single park run); makes the
 *       check tight and easy to diagnose when it fails.</li>
 *   <li>{@link #timerElidesIpiForRealisticServiceWorkload()} — a fixed thread pool whose threads
 *       sit parked in {@code LinkedBlockingQueue.take()} plus a {@code Thread.sleep}-driven
 *       scheduler and a CPU-bound thread. Mirrors a typical Java service profile, where
 *       {@code LockSupport.park} dominates the state distribution.</li>
 * </ul>
 *
 * <p>Both methods register the workload threads with the wall-clock thread filter and run with
 * {@code filter=0} so that only those threads receive signals — keeping the counter math
 * dominated by workload signals rather than JVM-internal threads.
 */
public class WallclockTimerFastPathTest extends AbstractProfilerTest {

    private static final String COUNTER_KEY = "wallclock_signal_own";
    private static final long SAMPLING_INTERVAL_MS = 10L;

    // Allow up to 50% of the baseline signal volume after the fast path engages. The theoretical
    // ratio is much lower (entry sample only), but CI noise (boundary jitter when the thread
    // transitions in/out of park, JVM warmup ticks before the slot is associated, etc.) means a
    // 50% guard is the right balance between catching regressions and not flaking. With the
    // fast path working we routinely see ratios well below 25%.
    private static final double MAX_ALLOWED_RATIO = 0.5;

    @Test
    public void timerElidesIpiForLongParkRuns() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        // wallprecheck reads HotSpot OSThreadState; JDK 8 misreports sleep / park states.
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));

        Map<String, Long> beforeA = profiler.getDebugCounters();
        Assumptions.assumeTrue(beforeA.containsKey(COUNTER_KEY),
                "wallclock_signal_own counter not available (build without COUNTERS)");

        // Recording A: wallprecheck=false (started by @BeforeEach via getProfilerCommand()).
        runParkWorkload("fastpath-park-A");
        stopProfiler();
        long signalsA = signalDelta(beforeA, profiler.getDebugCounters());

        // Recording B: wallprecheck=true, same workload, separate JFR file.
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
                "WallclockTimerFastPathTest_realistic_B_", ".jfr");
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

        // Sanity: the baseline must actually have produced signals — otherwise the ratio is
        // meaningless and the test is silently green for the wrong reason. The threshold is
        // intentionally permissive (a few dozen) since CI runners vary widely; the meaningful
        // assertion is the ratio check below.
        assertTrue(signalsA > 20,
                "recording A: baseline produced too few wallclock_signal_own ticks (" + signalsA
                        + "); workload may not be running long enough");

        // Core IPI-elide invariant: the wall-clock timer must skip the syscall for parked
        // threads after the entry sample. If this regresses, JP6 still suppresses the JFR
        // events (so PrecheckTest passes) but every tick still wakes the worker CPU.
        assertTrue(signalsB < signalsA * MAX_ALLOWED_RATIO,
                "timer fast path appears disengaged: recording A delivered " + signalsA
                        + " signals, recording B delivered " + signalsB
                        + " (ratio " + String.format("%.3f", ratio)
                        + "; expected < " + MAX_ALLOWED_RATIO + ")");
    }

    private void runParkWorkload(String workerName) throws Exception {
        // Re-park loop: LockSupport.parkNanos returns early when SIGVTALRM interrupts the
        // underlying pthread_cond_timedwait, which without re-parking would collapse the
        // effective parked time to near-zero (one signal per nominal park run). We loop
        // until the deadline to keep the worker continuously parked for ~PARK_NANOS each
        // run, which is what the timer fast path is supposed to exploit.
        final int PARK_RUNS = 100;
        final long PARK_NANOS = 100_000_000L; // 100 ms per run → ~10 s total parked time
        AtomicBoolean stop = new AtomicBoolean(false);

        Thread worker = new Thread(() -> {
            registerCurrentThreadForWallClockProfiling();
            // TaskBlock emission requires a non-zero spanId — keeps the workload aligned with
            // how parkEnter/parkExit are exercised in the other wall-clock tests. The counter
            // we check (wallclock_signal_own) is independent of TaskBlock emission.
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
        // Tuned for ~1s of measurement, mirroring PrecheckEfficiencyTest.realisticServiceWorkload
        // but scaled up enough to give the counter a clear signal under filter=0.
        final int POOL_SIZE = 8;
        final int TASK_DURATION_MS = 20;
        final int SCHEDULE_INTERVAL_MS = 50;
        final int MEASUREMENT_MS = 1000;

        AtomicBoolean stop = new AtomicBoolean(false);
        AtomicInteger threadIndex = new AtomicInteger(0);

        // Mostly-idle pool: threads park in LinkedBlockingQueue.take() between submissions.
        ExecutorService pool = Executors.newFixedThreadPool(POOL_SIZE, r -> {
            Thread t = new Thread(() -> {
                registerCurrentThreadForWallClockProfiling();
                r.run();
            });
            t.setName(tag + "-pool-" + threadIndex.incrementAndGet());
            t.setDaemon(true);
            return t;
        });

        // Pre-warm: ensure all POOL_SIZE threads exist and are parked before measurement.
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
        // Recording A baseline: wallprecheck explicitly disabled, filter=0 so only registered
        // threads are sampled (keeps wallclock_signal_own dominated by workload signals).
        return "wall=" + SAMPLING_INTERVAL_MS + "ms,wallprecheck=false,filter=0";
    }
}
