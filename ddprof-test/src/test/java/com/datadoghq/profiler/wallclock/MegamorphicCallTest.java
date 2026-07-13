package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

import static org.junit.jupiter.api.Assertions.assertFalse;
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
        IItemCollection events = verifyEvents("datadog.MethodSample");
        System.err.println(events.stream().count());
        List<String> itableStubStacktraces = new ArrayList<>();
        for (IItemIterable cpuSamples : events) {
            IMemberAccessor<String, IItem> frameAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(cpuSamples.getType());
            for (IItem sample : cpuSamples) {
                String stackTrace = frameAccessor.getMember(sample);
                if (stackTrace.contains(".itable stub()")) {
                    itableStubStacktraces.add(stackTrace);
                }
            }
        }
        assertFalse(itableStubStacktraces.isEmpty());
        boolean foundProfiledWork = false;
        for (String stacktrace : itableStubStacktraces) {
            foundProfiledWork = stacktrace.contains("MegamorphicCallTest.profiledWork");
            if (foundProfiledWork)
                break;
        }
        assertTrue(foundProfiledWork);
    }
}
