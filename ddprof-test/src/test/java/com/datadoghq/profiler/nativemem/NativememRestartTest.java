/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.nativemem;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;

import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

import java.nio.file.Files;
import java.nio.file.Path;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * stop() removes the malloc hooks and the next start installs them again, so native allocation
 * profiling must keep working across start/stop cycles, and allocations made while idle must not
 * show up in the next recording.
 */
public class NativememRestartTest {

    private static final int CYCLES = 3;
    private static final long RECORDED_SIZE = 1024;
    // Distinct from RECORDED_SIZE so idle allocations are recognizable.
    private static final long IDLE_SIZE = 777_777;

    @Timeout(120)
    @Test
    public void mallocHooksAreReinstalledOnEveryStart() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux() && !Platform.isJ9() && !Platform.isZing());
        // GOT patching conflicts with ASan/TSan interceptors.
        Assumptions.assumeTrue(System.getenv("ASAN_OPTIONS") == null && System.getenv("TSAN_OPTIONS") == null);

        JavaProfiler profiler = JavaProfiler.getInstance();
        for (int cycle = 0; cycle < CYCLES; cycle++) {
            Path jfr = Files.createTempFile("nativemem-restart-" + cycle + "-", ".jfr");
            try {
                // Made while idle: must not be recorded.
                NativeAllocHelper.nativeMalloc(IDLE_SIZE, 10);
                profiler.execute("start,nativemem=0,jfr,file=" + jfr.toAbsolutePath());
                NativeAllocHelper.nativeMalloc(RECORDED_SIZE, 1000);
                profiler.stop();

                long[] recorded = {0};
                long[] idle = {0};
                JfrEvents.forEach(jfr, "datadog.NativeMemoryAllocation"::equals, e -> {
                    Long size = e.getLong("size");
                    if (size != null && size == RECORDED_SIZE) {
                        recorded[0]++;
                    } else if (size != null && size == IDLE_SIZE) {
                        idle[0]++;
                    }
                });
                assertTrue(recorded[0] > 0, "no malloc samples in cycle " + cycle);
                assertEquals(0, idle[0], "allocations made while idle were recorded in cycle " + cycle);
            } finally {
                Files.deleteIfExists(jfr);
            }
        }
    }
}
