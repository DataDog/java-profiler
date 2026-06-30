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
 * Regression test for the "Disabling + teardown" coverage cell.
 *
 * <p>Races profiler.stop() against concurrent thread creation and destruction.
 * The hazard window: a thread calling JVMTI ThreadEnd (or ProfiledThread::release)
 * concurrently with stop() can hit the ThreadFilter or signal handler after they
 * have been torn down.
 *
 * <p>Does NOT extend AbstractProfilerTest — needs direct control over
 * execute()/stop() timing; uses the same pattern as ShutdownTest.
 */
public class StopWithChurningThreadsTest {

    private static final int CHURN_THREADS = 64;
    private static final int CYCLES = 50;
    private static final String PROFILER_CMD = "start,wall=5ms,filter=*,jfr,file=";

    @RetryTest(2)
    @Timeout(60)
    @Test
    public void stopRacesThreadEnd() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9(), "J9 has a different JVMTI implementation");
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11), "wall-clock requires Java 11+");
        Assumptions.assumeTrue(!Platform.isZing(), "Zing forces cstack=no");

        JavaProfiler profiler = JavaProfiler.getInstance();
        Path recordings = Files.createTempDirectory("lifecycle-cell1-");
        Queue<Throwable> errors = new LinkedBlockingQueue<>();

        AtomicBoolean running = new AtomicBoolean(true);
        CountDownLatch churnRunning = new CountDownLatch(CHURN_THREADS);
        ExecutorService churn = Executors.newFixedThreadPool(CHURN_THREADS);

        for (int i = 0; i < CHURN_THREADS; i++) {
            churn.submit(() -> {
                churnRunning.countDown();
                while (running.get()) {
                    Thread t = new Thread(() -> {});
                    t.start();
                    try {
                        t.join(5);
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                        return;
                    }
                }
            });
        }
        assertTrue(churnRunning.await(10, TimeUnit.SECONDS), "Churn threads did not start");

        try {
            for (int cycle = 0; cycle < CYCLES; cycle++) {
                Path jfr = Files.createTempFile(recordings, "c1-" + cycle + "-", ".jfr");
                try {
                    profiler.execute(PROFILER_CMD + jfr.toAbsolutePath());
                    Thread.sleep(20);
                    profiler.stop();
                } catch (Throwable t) {
                    errors.offer(t);
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
