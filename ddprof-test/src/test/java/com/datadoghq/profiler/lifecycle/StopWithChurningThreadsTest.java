/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.lifecycle;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.Platform;

import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.CancellationException;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
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
    private static final int CYCLES = 500;
    // wall=1ms maximises signals in-flight during teardown; filter= disables
    // thread filtering so all threads receive SIGVTALRM, increasing collision
    // probability with ThreadEnd.
    private static final String PROFILER_CMD = "start,wall=1ms,filter=,jfr,file=";

    @Timeout(120)
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
        List<Future<?>> churnFutures = new ArrayList<>(CHURN_THREADS);

        for (int i = 0; i < CHURN_THREADS; i++) {
            churnFutures.add(churn.submit(() -> {
                churnRunning.countDown();
                while (running.get()) {
                    // No join — thread dies on its own schedule, so ThreadEnd
                    // fires at an unpredictable time relative to stop().
                    new Thread(() -> {}).start();
                }
            }));
        }

        try {
            assertTrue(churnRunning.await(10, TimeUnit.SECONDS), "Churn threads did not start");
            for (int cycle = 0; cycle < CYCLES; cycle++) {
                Path jfr = Files.createTempFile(recordings, "c1-" + cycle + "-", ".jfr");
                try {
                    profiler.execute(PROFILER_CMD + jfr.toAbsolutePath());
                    // Minimal delay: hit stop() while signals are still in-flight
                    // and threads are actively dying. Varies per cycle to avoid
                    // always landing in the same phase of the signal period.
                    Thread.sleep(cycle % 3);
                    profiler.stop();
                } catch (Throwable t) {
                    if (!errors.offer(t)) {
                        fail("Failed to record test error", t);
                    }
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
            for (Future<?> f : churnFutures) {
                try {
                    f.get();
                } catch (ExecutionException e) {
                    if (!errors.offer(e.getCause())) {
                        fail("Failed to record churn worker error", e.getCause());
                    }
                } catch (CancellationException ignored) {}
            }
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
