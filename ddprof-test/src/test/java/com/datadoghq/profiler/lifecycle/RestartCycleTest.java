/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.lifecycle;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;

import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

import java.nio.file.Files;
import java.nio.file.Path;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Per-recording resources (call-trace storage and buffers, JFR metadata, ...) are allocated in
 * start() and freed in stop(). Every start/stop cycle must still produce a complete recording.
 */
public class RestartCycleTest {

    private static final int CYCLES = 5;
    private static final String PROFILER_CMD = "start,cpu=1ms,memory=262144:a,jfr,file=";

    private static volatile Object sink;
    private static volatile long acc;

    @Timeout(180)
    @Test
    public void everyCycleRecordsSamples() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9() && !Platform.isZing(), "HotSpot only");

        JavaProfiler profiler = JavaProfiler.getInstance();
        for (int cycle = 0; cycle < CYCLES; cycle++) {
            Path jfr = Files.createTempFile("restart-cycle-" + cycle + "-", ".jfr");
            try {
                profiler.execute(PROFILER_CMD + jfr.toAbsolutePath());
                work(300);
                profiler.stop();

                long cpu = JfrEvents.forEach(jfr, "datadog.ExecutionSample"::equals, e -> { });
                long alloc = JfrEvents.forEach(jfr, "datadog.ObjectSample"::equals, e -> { });
                assertTrue(cpu > 0, "no CPU samples in cycle " + cycle);
                assertTrue(alloc > 0, "no allocation samples in cycle " + cycle);
            } finally {
                Files.deleteIfExists(jfr);
            }
        }
    }

    private static void work(long millis) {
        long deadline = System.nanoTime() + millis * 1_000_000L;
        long a = 0;
        while (System.nanoTime() - deadline < 0) {
            for (int i = 0; i < 1000; i++) {
                a += i * 31 + (a >>> 3);
            }
            sink = new byte[64 * 1024];
        }
        acc = a;
    }
}
