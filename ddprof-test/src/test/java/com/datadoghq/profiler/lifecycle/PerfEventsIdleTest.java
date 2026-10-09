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

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.concurrent.CountDownLatch;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * perf_events must not stay active while the profiler is idle: after stop() there are no perf
 * fds left (and so no SIGPROF and no ring mmaps), threads created while idle don't get one, and
 * every start/stop cycle still records samples.
 */
public class PerfEventsIdleTest {

    private static final int CYCLES = 3;
    // A software event, so it works on VMs without a PMU.
    private static final String PROFILER_CMD = "start,event=page-faults,interval=1,jfr,file=";

    @Timeout(120)
    @Test
    public void perfEventsAreClosedAtStop() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux(), "perf_events is Linux-only");
        Assumptions.assumeTrue(!Platform.isJ9() && !Platform.isZing(), "HotSpot only");

        JavaProfiler profiler = JavaProfiler.getInstance();
        Path dir = Files.createTempDirectory("perf-idle-");
        try {
            assertEquals(0, countPerfFds(), "perf fds open before the first start");
            for (int cycle = 0; cycle < CYCLES; cycle++) {
                Path jfr = dir.resolve("cycle-" + cycle + ".jfr");
                try {
                    profiler.execute(PROFILER_CMD + jfr.toAbsolutePath());
                } catch (IllegalStateException e) {
                    Assumptions.abort("perf_events unavailable: " + e.getMessage());
                }
                assertTrue(countPerfFds() > 0, "no perf fds while recording (cycle " + cycle + ")");
                touchPages(64 << 20);
                profiler.stop();

                assertEquals(0, countPerfFds(), "perf fds left open after stop (cycle " + cycle + ")");
                assertEquals(0, countPerfFdsOnIdleThread(),
                    "a thread created while idle got a perf fd (cycle " + cycle + ")");
                assertTrue(countExecutionSamples(jfr) > 0, "no samples recorded in cycle " + cycle);
            }
        } finally {
            try (Stream<Path> files = Files.walk(dir)) {
                files.sorted((a, b) -> b.compareTo(a)).forEach(p -> {
                    try {
                        Files.deleteIfExists(p);
                    } catch (IOException ignored) {
                    }
                });
            }
        }
    }

    private static void touchPages(int bytes) {
        ByteBuffer buffer = ByteBuffer.allocateDirect(bytes);
        for (int i = 0; i < bytes; i += 4096) {
            buffer.put(i, (byte) 1);
        }
    }

    private static int countPerfFdsOnIdleThread() throws Exception {
        CountDownLatch started = new CountDownLatch(1);
        CountDownLatch done = new CountDownLatch(1);
        Thread t = new Thread(() -> {
            started.countDown();
            try {
                done.await();
            } catch (InterruptedException ignored) {
            }
        }, "perf-idle-thread");
        t.start();
        started.await();
        try {
            return countPerfFds();
        } finally {
            done.countDown();
            t.join();
        }
    }

    private static int countPerfFds() throws IOException {
        int count = 0;
        try (Stream<Path> fds = Files.list(Paths.get("/proc/self/fd"))) {
            for (Path fd : (Iterable<Path>) fds::iterator) {
                try {
                    if (Files.readSymbolicLink(fd).toString().contains("perf_event")) {
                        count++;
                    }
                } catch (IOException ignored) {
                    // The fd was closed while listing.
                }
            }
        }
        return count;
    }

    private static long countExecutionSamples(Path jfr) throws Exception {
        return JfrEvents.forEach(jfr, "datadog.ExecutionSample"::equals, e -> { });
    }
}
