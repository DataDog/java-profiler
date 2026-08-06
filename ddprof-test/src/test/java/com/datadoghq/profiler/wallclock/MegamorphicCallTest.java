/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;

import java.util.concurrent.ThreadLocalRandom;

import static org.junit.jupiter.api.Assertions.assertTrue;

public class MegamorphicCallTest extends AbstractProfilerTest {
    @Override
    protected String getProfilerCommand() {
        // wall=100us over the fixed workload below is ~10k samples/s. Under ASAN each
        // invocation is much slower, so the same fixed-rate sampling over a much longer
        // wall-clock duration produces hundreds of thousands of samples, and stack-trace
        // stringification of all of them (below) OOMs the test-runner heap. Sample 10x
        // coarser under ASAN, combined with a smaller workload, to bound the sample count.
        return isAsan() ? "wall=1ms" : "wall=100us";
    }

    private static int calculation() {
        return ThreadLocalRandom.current().nextInt();
    }

    interface Calculator {
        /**
         * This call needs to be cheap enough for a loop to be dominated by the stub
         */
        int calculate();
    }

    // This is OpenJDK specific but we choose 3 of these to prevent inlining,
    // which means we will get an itable stub frame
    static class Calculator1 implements Calculator {

        @Override
        public int calculate() {
            return calculation();
        }
    }

    static class Calculator2 implements Calculator {

        @Override
        public int calculate() {
            return calculation();
        }
    }

    static class Calculator3 implements Calculator {

        @Override
        public int calculate() {
            return calculation();
        }
    }

    private int profiledWork(int iterations, Calculator... calculators) {
        int result = 0;
        for (int i = 0; i < iterations; i++) {
            for (Calculator calculator : calculators) {
                result += calculator.calculate();
            }
        }
        return result;
    }

    @RetryingTest(5)
    public void testITableStubs() {
        Assumptions.assumeFalse(Platform.isZing() || Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        // Reduce workload under ASAN: combined with the coarser wall rate above, this
        // bounds the number of samples (and thus the stack-trace strings materialized
        // below) regardless of how much ASAN slows down each invocation.
        int iterations = isAsan() ? 100_000 : 1_000_000;
        int result = profiledWork(iterations, new Calculator1(), new Calculator2(), new Calculator3());
        System.err.println(result);
        stopProfiler();

        // Streamed rather than materialized: wall=100us over this workload produces up to
        // hundreds of thousands of samples, and every check here is per-event (a running
        // "did we see X" flag) with no need to retain the stack-trace strings afterward.
        StubSearch found = reduceEvents("datadog.MethodSample", StubSearch::new, (acc, sample) -> {
            acc.total++;
            String stackTrace = sample.getStackTraceString();
            if (stackTrace.contains(".itable stub()")) {
                acc.foundItableStub = true;
                if (stackTrace.contains("MegamorphicCallTest.profiledWork")) {
                    acc.foundProfiledWork = true;
                }
            }
        });
        System.err.println(found.total);
        assertTrue(found.total > 0, "datadog.MethodSample was empty");
        assertTrue(found.foundItableStub);
        assertTrue(found.foundProfiledWork);
    }

    private static final class StubSearch {
        long total;
        boolean foundItableStub;
        boolean foundProfiledWork;
    }
}
