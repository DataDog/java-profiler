/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;

import java.nio.file.Path;
import java.util.Collections;
import java.util.concurrent.atomic.AtomicInteger;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * jmethodIDs are loaded while the profiler is still idle (when the bridge is initialized), so the
 * first start does not scan every loaded class at once. Relies on the debug build's TEST_LOG.
 */
public class MethodIdPreloadTest extends AbstractProcessProfilerTest {

    @Test
    void methodIdsArePreloadedWhileIdle() throws Exception {
        assumeTrue("debug".equals(System.getProperty("ddprof_test.config")));
        assumeTrue(Platform.isLinux() && !Platform.isJ9() && !Platform.isZing());

        AtomicInteger idleScans = new AtomicInteger();
        LaunchResult idle = launch("profiler", Collections.emptyList(), null,
            l -> {
                if (l.contains("[TEST::INFO] Preloaded jmethodIDs")) {
                    idleScans.incrementAndGet();
                }
                return LineConsumerResult.CONTINUE;
            },
            null);
        assertTrue(idle.inTime);
        assertEquals(1, idleScans.get(), "expected one class scan at getInstance(), with no start");
    }

    @Test
    void startDoesNotRescan(@TempDir Path tmp) throws Exception {
        assumeTrue("debug".equals(System.getProperty("ddprof_test.config")));
        assumeTrue(Platform.isLinux() && !Platform.isJ9() && !Platform.isZing());

        AtomicInteger scans = new AtomicInteger();
        LaunchResult started = launch("profiler", Collections.emptyList(),
            "start,cpu=10ms,jfr,file=" + tmp.resolve("preload.jfr"),
            l -> {
                if (l.contains("[TEST::INFO] Preloaded jmethodIDs")) {
                    scans.incrementAndGet();
                }
                return LineConsumerResult.CONTINUE;
            },
            null);
        assertTrue(started.inTime);
        assertEquals(1, scans.get(), "the start scanned the loaded classes again");
    }
}
