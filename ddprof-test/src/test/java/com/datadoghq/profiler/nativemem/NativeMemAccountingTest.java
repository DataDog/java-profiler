/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.nativemem;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvents;
import org.junit.jupiter.api.Test;

import java.nio.file.Files;
import java.nio.file.Path;

import static org.junit.jupiter.api.Assertions.assertEquals;
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
        busyLoop();

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

    /**
     * Integration test for the cross-chunk post-flush snapshot ({@code
     * Recording::capturePostFlushNativeMem}, {@code flightRecorder.cpp}): a
     * dump() mid-recording forces exactly one chunk switch on the continuous
     * recording, so the resulting file has exactly two chunks. This pins:
     * <ul>
     *   <li>the first-chunk-absent invariant ({@code _has_post_flush} starts
     *       {@code false}): the post-flush labels must not appear in the first
     *       chunk;</li>
     *   <li>the later-chunk-present case: they must appear, and be sane, once
     *       {@code finishChunk()} has run at least once;</li>
     *   <li>the label spelling ({@code native_mem_post_flush_live_bytes.*} /
     *       {@code native_mem_post_flush_max_bytes.*}).</li>
     * </ul>
     * With exactly one forced chunk switch, a post-flush label can appear at
     * most once in the whole recording (only in the second chunk) -- so
     * "exactly one occurrence" is equivalent to "absent in chunk 1, present in
     * chunk 2", without needing per-chunk parsing.
     */
    @Test
    public void shouldEmitPostFlushCountersOnlyAfterAChunkSwitch() throws Exception {
        String liveLabel = "native_mem_post_flush_live_bytes.jfr_buffers";
        String maxLabel = "native_mem_post_flush_max_bytes.jfr_buffers";

        // Nothing has flushed yet: the very first getRecordedCounterValue below
        // would find these labels nowhere in the recording if this busyLoop()
        // were the only chunk. Populate some native memory before forcing the
        // switch so the post-flush snapshot has a non-trivial "jfr_buffers"
        // value to capture.
        busyLoop();

        Path dumpTarget = Files.createTempFile("native-mem-post-flush", ".jfr");
        try {
            // Forces exactly one finishChunk(end_recording=true, do_cleanup=true)
            // on the continuous recording (see FlightRecorder::dump ->
            // Recording::switchChunk), which is where capturePostFlushNativeMem()
            // runs.
            dump(dumpTarget);

            // Keep the second chunk non-empty too.
            busyLoop();
            stopProfiler();

            long live = getRecordedCounterValue(liveLabel);
            long max = getRecordedCounterValue(maxLabel);
            assertTrue(live >= 0, liveLabel + " present, was " + live);
            assertTrue(max >= 0, maxLabel + " present, was " + max);
            assertTrue(max >= live, "post-flush max (" + max + ") >= post-flush live (" + live + ")");

            assertEquals(1, countCounterOccurrences(liveLabel),
                    liveLabel + " must appear exactly once: absent in the first chunk (_has_post_flush"
                            + " starts false), present from the second chunk onward");
            assertEquals(1, countCounterOccurrences(maxLabel),
                    maxLabel + " must appear exactly once: absent in the first chunk, present from the"
                            + " second chunk onward");
        } finally {
            Files.deleteIfExists(dumpTarget);
        }
    }

    /** Keeps the sampler busy briefly so native buffers are populated for the counters to report. */
    private void busyLoop() {
        long deadline = System.nanoTime() + 100_000_000L; // ~100ms
        double sink = 0;
        while (System.nanoTime() < deadline) {
            for (int i = 0; i < 10_000; i++) {
                sink += Math.sqrt(i);
            }
        }
        // Guard against dead-code elimination of the busy loop.
        assertTrue(!Double.isNaN(sink));
    }

    /** Counts how many {@code datadog.ProfilerCounter} events carry {@code counterName}. */
    private long countCounterOccurrences(String counterName) throws Exception {
        JfrEvents events = verifyEvents("datadog.ProfilerCounter", false);
        return events.filter(item -> counterName.equals(item.getString(NAME))).count();
    }
}
