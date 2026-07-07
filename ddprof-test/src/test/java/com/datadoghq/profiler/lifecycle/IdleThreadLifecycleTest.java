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

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Regression test for the "Disabled + teardown" coverage cell.
 *
 * <p>Verifies that thread lifecycle events (ThreadStart/ThreadEnd JVMTI callbacks,
 * ProfiledThread::release) are safe when the profiler has never been started.
 * The JVMTI callbacks registered in JNI_OnLoad delegate to onThreadStart /
 * onThreadEnd unconditionally; those paths must tolerate a never-started profiler.
 *
 * <p>Does NOT call profiler.execute() — the profiler stays idle throughout.
 */
public class IdleThreadLifecycleTest {

    private static final int THREAD_COUNT = 200;

    @Timeout(30)
    @Test
    public void threadLifecycleWhileProfilerIdle() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9(), "J9 has a different JVMTI implementation");
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));

        JavaProfiler profiler = JavaProfiler.getInstance();
        // Profiler must NOT be started — verify it is idle before we begin.
        String statusBefore = profiler.getStatus();
        assertFalse(statusBefore.contains("Running          : true"),
            "Profiler must be idle at test start; status: " + statusBefore);

        ExecutorService pool = Executors.newFixedThreadPool(16);
        CountDownLatch done = new CountDownLatch(THREAD_COUNT);
        for (int i = 0; i < THREAD_COUNT; i++) {
            pool.submit(done::countDown);
        }
        assertTrue(done.await(10, TimeUnit.SECONDS),
            "Not all " + THREAD_COUNT + " thread tasks completed");
        pool.shutdown();
        pool.awaitTermination(5, TimeUnit.SECONDS);

        // Profiler must still be idle — thread lifecycle events must not trigger a start.
        String statusAfter = profiler.getStatus();
        assertFalse(statusAfter.contains("Running          : true"),
            "Profiler must remain idle after thread churn; status: " + statusAfter);
    }
}
