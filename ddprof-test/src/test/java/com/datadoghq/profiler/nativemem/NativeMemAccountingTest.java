/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.nativemem;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Smoke test for the always-on categorized native-memory accounting facility
 * ({@code NativeMem}).
 *
 * <p>It does not exercise any particular allocation path; it verifies that the
 * aggregate counters the facility publishes into every recording
 * ({@code native_mem_live_bytes}, {@code native_mem_avg_bytes},
 * {@code native_mem_max_bytes}) are present after a short profiling run and hold
 * their sanity invariants. The peak total is an upper bound (sum of the precise
 * per-category peaks), so it must be {@code >=} both the current live total and
 * the moving-window average total.
 */
public class NativeMemAccountingTest extends AbstractProfilerTest {

    @Override
    protected String getProfilerCommand() {
        return "wall=~1ms";
    }

    @Test
    public void shouldPublishSaneNativeMemCounters() throws Exception {
        // Keep the sampler busy briefly so the profiler's native buffers
        // (calltrace storage, dictionaries, per-thread data, ...) are populated
        // while the recording captures the counters.
        long deadline = System.nanoTime() + 100_000_000L; // ~100ms
        double sink = 0;
        while (System.nanoTime() < deadline) {
            for (int i = 0; i < 10_000; i++) {
                sink += Math.sqrt(i);
            }
        }
        // Guard against dead-code elimination of the busy loop.
        assertTrue(!Double.isNaN(sink));

        stopProfiler();

        // getRecordedCounterValue returns -1 when the named counter was never
        // emitted, so the presence checks below double as "is emitted" assertions.
        long live = getRecordedCounterValue("native_mem_live_bytes");
        long avg = getRecordedCounterValue("native_mem_avg_bytes");
        long max = getRecordedCounterValue("native_mem_max_bytes");

        // The agent always holds some native memory while running (at minimum the
        // calltrace buffers), so the peak total is present and non-zero.
        assertTrue(max > 0, "native_mem_max_bytes present and non-zero, was " + max);
        assertTrue(live >= 0, "native_mem_live_bytes present, was " + live);
        assertTrue(avg >= 0, "native_mem_avg_bytes present, was " + avg);

        // The peak is a bracketing upper bound on the total.
        assertTrue(max >= live, "max (" + max + ") >= live (" + live + ")");
        assertTrue(max >= avg, "max (" + max + ") >= avg (" + avg + ")");
    }
}
