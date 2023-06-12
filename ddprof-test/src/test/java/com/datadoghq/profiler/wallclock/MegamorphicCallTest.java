package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.condition.DisabledIfSystemProperty;
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

@DisabledIfSystemProperty(named = "java.vm.name", matches = ".*J9.*",
        disabledReason = "Assumes HotSpot inlining heuristics")
public class MegamorphicCallTest extends AbstractProfilerTest {
    @Override
    protected String getProfilerCommand() {
        // use wall because it lets us control which threads to sample
        return "wall=100us";
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

    private int profiledWork(Calculator... calculators) {
        int result = 0;
        for (int i = 0; i < 1_000_000; i++) {
            for (Calculator calculator : calculators) {
                result += calculator.calculate();
            }
        }
        return result;
    }

    @Test
    public void testITableStubs() {
        registerCurrentThreadForWallClockProfiling();
        int result = profiledWork(new Calculator1(), new Calculator2(), new Calculator3());
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
