/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeFalse;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * Smoke test for the {@code datadog.UnwindFailure} JFR event, which surfaces the DEBUG-only
 * {@code UnwindStats}/{@code UnwindFailures} native counters ({@code unwindStats.h}).
 *
 * <p>Those counters are only compiled in when the native library is built with {@code -DDEBUG}
 * (the {@code debug}, {@code asan}, and {@code tsan} configurations), and even then are only
 * recorded when {@code HotspotSupport::walkVM} fails to unwind a runtime-stub frame and has no
 * {@code frameSize()} fallback available - a rare, hard-to-force condition on a healthy JVM.
 * {@code cstack=vm} is used because that is the only mode that routes Java-frame collection
 * through {@code walkVM}; {@code fp}/{@code dwarf} unwinding never touches this code path.
 *
 * <p>Since a real stub-unwind failure cannot be reliably provoked from a plain Java workload,
 * this test does not require the event to occur. It instead verifies that: the profiler runs
 * cleanly under {@code cstack=vm} on a DEBUG build (the pipeline that would emit the event does
 * not crash or corrupt the recording), and if any {@code datadog.UnwindFailure} events *are*
 * emitted, their schema is sane (kind is "stub" or "other", name is non-empty, count is
 * positive).
 */
public class UnwindFailuresTest extends AbstractProfilerTest {

    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms,cstack=vm";
    }

    @Test
    public void unwindFailureEventsHaveSaneSchemaWhenPresent() throws Exception {
        // UnwindFailures/UnwindStats are compiled out unless the native lib is built with
        // -DDEBUG (debug/asan/tsan configs); on a release build datadog.UnwindFailure can
        // never appear, so there is nothing to check.
        String config = System.getProperty("ddprof_test.config");
        assumeTrue(config != null && ("debug".equals(config) || config.endsWith("san")),
                "datadog.UnwindFailure is only recorded in DEBUG-instrumented builds (debug/asan/tsan)");

        // HotspotSupport::walkVM (and therefore UnwindFailures recording) is Hotspot-only.
        assumeFalse(Platform.isZing() || Platform.isJ9() || Platform.isGraal());

        // Exercise a variety of call shapes (virtual/interface dispatch, lambdas, recursion,
        // exceptions) for a little while to maximise the - inherently small - chance of hitting
        // an unwindable stub frame while the cpu=1ms sampler is active.
        long deadline = System.nanoTime() + 300_000_000L; // ~300ms
        long sink = 0;
        while (System.nanoTime() < deadline) {
            sink += churn(20);
        }
        assertTrue(sink != Long.MIN_VALUE); // guard against dead-code elimination

        stopProfiler();

        // The sampler must have produced a healthy recording regardless of whether any
        // unwind failures happened to occur.
        verifyEventsPresent("datadog.ExecutionSample");

        JfrEvents unwindFailures = verifyEvents("datadog.UnwindFailure", false);
        for (JfrEvent event : unwindFailures) {
            String kind = event.getString("kind");
            String name = event.getString("name");
            long count = event.getLong("count", -1);

            assertTrue("stub".equals(kind) || "other".equals(kind),
                    "unexpected UnwindFailure kind: " + kind);
            assertFalse(name == null || name.isEmpty(), "UnwindFailure name must not be empty");
            assertTrue(count > 0, "UnwindFailure count must be positive, was " + count);
        }
    }

    private interface Op {
        long apply(long x);
    }

    private static long churn(int depth) {
        Op add = x -> x + 1;
        Op mul = x -> x * 3;
        try {
            if (depth <= 0) {
                throw new RuntimeException("bottom");
            }
            return add.apply(mul.apply(churn(depth - 1)));
        } catch (RuntimeException e) {
            return depth;
        }
    }
}
