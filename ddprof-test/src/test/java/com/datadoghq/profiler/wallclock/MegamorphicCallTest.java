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
    private static final long ASAN_DURATION_NS = 1_000_000_000L;

    @Override
    protected String getProfilerCommand() {
        // wall=100us over the fixed workload below is ~10k samples/s. Under ASAN that rate
        // produced hundreds of thousands of samples, and stack-trace stringification of
        // all of them (below) OOMs the test-runner heap. Sample 10x coarser under ASAN,
        // over a fixed duration, to bound the sample count.
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
        // itable stub frames are HotSpot-specific; GraalVM's JIT doesn't generate the
        // same stub layout, as with the other itable/vtable stub tests in this suite.
        Assumptions.assumeFalse(Platform.isZing() || Platform.isJ9() || Platform.isGraal());
        registerCurrentThreadForWallClockProfiling();
        Calculator[] calculators = {new Calculator1(), new Calculator2(), new Calculator3()};
        int result;
        if (isAsan()) {
            // ASAN does not instrument JIT-compiled code, so a fixed iteration count
            // finishes within a few 1ms sampling periods. Run for a fixed duration
            // instead: at most ~1000 samples at wall=1ms, enough to hit the itable stub while
            // still bounding the stack-trace strings materialized below.
            result = 0;
            long start = System.nanoTime();
            while (System.nanoTime() - start < ASAN_DURATION_NS) {
                result += profiledWork(100_000, calculators);
            }
        } else {
            result = profiledWork(1_000_000, calculators);
        }
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
