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

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.CountDownLatch;

import static org.junit.jupiter.api.Assertions.assertEquals;

/**
 * The pthread_create hook stays installed after stop(), so threads created while the profiler is
 * idle get their ProfiledThread from the hook rather than claiming a TLS pool slot on their first
 * profiling signal. More idle-created threads than the pool has slots, all taking CPU-timer
 * signals, must therefore not exhaust the pool once profiling starts again.
 */
public class IdleThreadCreationTest {

    // Well above the TLS pool's 64 slots.
    private static final int IDLE_THREADS = 200;
    private static final String PROFILER_CMD = "start,cpu=1ms,jfr,file=";
    private static final long BURN_NANOS = 50_000_000L;

    private static volatile long sink;

    @Timeout(60)
    @Test
    public void threadsCreatedWhileIdleDontUseThePool() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux(), "TLS priming is Linux-only");
        Assumptions.assumeTrue(!Platform.isJ9() && !Platform.isZing(), "HotSpot only");

        JavaProfiler profiler = JavaProfiler.getInstance();
        Path first = Files.createTempFile("idle-threads-1-", ".jfr");
        Path second = Files.createTempFile("idle-threads-2-", ".jfr");
        CountDownLatch burn = new CountDownLatch(1);
        CountDownLatch burned = new CountDownLatch(IDLE_THREADS);
        CountDownLatch release = new CountDownLatch(1);
        List<Thread> threads = new ArrayList<>();
        try {
            // The first start installs the pthread_create hook.
            profiler.execute(PROFILER_CMD + first.toAbsolutePath());
            profiler.stop();

            CountDownLatch started = new CountDownLatch(IDLE_THREADS);
            for (int i = 0; i < IDLE_THREADS; i++) {
                Thread t = new Thread(() -> {
                    started.countDown();
                    try {
                        // Burn CPU once profiling is on again, so every one of these threads
                        // takes CPU-timer signals.
                        burn.await();
                        long deadline = System.nanoTime() + BURN_NANOS;
                        long acc = 0;
                        while (System.nanoTime() - deadline < 0) {
                            acc += acc * 31 + 7;
                        }
                        sink = acc;
                        burned.countDown();
                        release.await();
                    } catch (InterruptedException ignored) {
                    }
                }, "idle-created-" + i);
                t.setDaemon(true);
                t.start();
                threads.add(t);
            }
            started.await();

            profiler.execute(PROFILER_CMD + second.toAbsolutePath());
            burn.countDown();
            burned.await();
            Map<String, Long> counters = profiler.getDebugCounters();
            profiler.stop();

            assertEquals(0L, counters.getOrDefault("thread_local_pool_exhausted", 0L).longValue(),
                "threads created while idle claimed TLS pool slots");
        } finally {
            burn.countDown();
            release.countDown();
            for (Thread t : threads) {
                t.join();
            }
            Files.deleteIfExists(first);
            Files.deleteIfExists(second);
        }
    }
}
