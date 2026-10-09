/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.memleak;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;

import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * stop() frees the liveness table (deleting its weak refs and clearing leak tags) and turns the GC
 * callbacks off; the next start() initializes the tracker from scratch. Every cycle must still
 * report the objects that are live at its end.
 */
public class LivenessRestartTest {

    private static final int CYCLES = 3;

    @Timeout(180)
    @Test
    public void everyCycleReportsLiveObjects() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9() && !Platform.isZing(), "HotSpot only");
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11), "liveness tracking requires Java 11+");

        JavaProfiler profiler = JavaProfiler.getInstance();
        for (int cycle = 0; cycle < CYCLES; cycle++) {
            Path jfr = Files.createTempFile("liveness-restart-" + cycle + "-", ".jfr");
            List<byte[]> retained = new ArrayList<>();
            try {
                profiler.execute("start,memory=256:L,jfr,file=" + jfr.toAbsolutePath());
                for (int i = 0; i < 20_000; i++) {
                    retained.add(new byte[1024]);
                }
                System.gc();
                profiler.stop();

                long live = JfrEvents.forEach(jfr, "datadog.HeapLiveObject"::equals, e -> { });
                assertTrue(live > 0, "no live objects reported in cycle " + cycle);
            } finally {
                retained.clear();
                Files.deleteIfExists(jfr);
            }
        }
    }
}
