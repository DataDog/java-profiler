package com.datadoghq.profiler.lifecycle;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.junit.RetryTest;

import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Queue;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

/**
 * Regression test for the "Enabling + startup/teardown" coverage cell.
 *
 * <p>Races profiler.execute() against threads that are already generating JVMTI
 * ThreadStart/ThreadEnd events. The hazard window: execute() installs signal
 * handlers, initialises the thread filter, and registers JVMTI callbacks one by
 * one; a thread starting or ending during this sequence may call onThreadStart /
 * onThreadEnd on a half-initialised engine.
 *
 * <p>Does NOT extend AbstractProfilerTest — needs direct control over
 * execute()/stop() timing; uses the same pattern as ShutdownTest.
 */
public class StartWithChurningThreadsTest {

    private static final int CHURN_THREADS = 64;
    private static final int CYCLES = 500;
    private static final String PROFILER_CMD = "start,wall=1ms,jfr,file=";

    @RetryTest(2)
    @Timeout(120)
    @Test
    public void startRacesThreadStartEnd() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9(), "J9 has a different JVMTI implementation");
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11), "wall-clock requires Java 11+");
        Assumptions.assumeTrue(!Platform.isZing(), "Zing forces cstack=no");

        JavaProfiler profiler = JavaProfiler.getInstance();
        Path recordings = Files.createTempDirectory("lifecycle-cell2-");
        Queue<Throwable> errors = new LinkedBlockingQueue<>();

        AtomicBoolean running = new AtomicBoolean(true);
        // Latch: churn threads signal they are running before execute() is called,
        // ensuring JVMTI events fire during profiler initialisation.
        CountDownLatch churnRunning = new CountDownLatch(CHURN_THREADS);
        ExecutorService churn = Executors.newFixedThreadPool(CHURN_THREADS);

        for (int i = 0; i < CHURN_THREADS; i++) {
            churn.submit(() -> {
                churnRunning.countDown();
                while (running.get()) {
                    new Thread(() -> {}).start();
                }
            });
        }
        // Wait for churn to be active BEFORE calling execute()
        assertTrue(churnRunning.await(10, TimeUnit.SECONDS), "Churn threads did not start");

        try {
            for (int cycle = 0; cycle < CYCLES; cycle++) {
                Path jfr = Files.createTempFile(recordings, "c2-" + cycle + "-", ".jfr");
                try {
                    // execute() races with active thread churn
                    profiler.execute(PROFILER_CMD + jfr.toAbsolutePath());
                    Thread.sleep(cycle % 3);
                    profiler.stop();
                } catch (Throwable t) {
                    errors.add(t);
                    break;
                } finally {
                    Files.deleteIfExists(jfr);
                }
            }
        } finally {
            running.set(false);
            churn.shutdown();
            if (!churn.awaitTermination(5, TimeUnit.SECONDS)) {
                churn.shutdownNow();
            }
            try {
                profiler.stop();
            } catch (Exception ignored) {
                // already stopped
            }
            deleteDirectory(recordings);
        }

        if (!errors.isEmpty()) {
            fail(errors.poll());
        }
    }

    private static void deleteDirectory(Path dir) {
        try {
            Files.walk(dir)
                .sorted(java.util.Comparator.reverseOrder())
                .forEach(p -> { try { Files.deleteIfExists(p); } catch (IOException ignored) {} });
        } catch (IOException ignored) {}
    }
}
