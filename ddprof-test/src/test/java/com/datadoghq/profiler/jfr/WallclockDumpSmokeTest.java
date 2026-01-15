package com.datadoghq.profiler.jfr;

import org.junit.jupiter.api.Timeout;

import org.junitpioneer.jupiter.RetryingTest;
import org.junit.jupiter.params.provider.ValueSource;

import com.datadoghq.profiler.junit.CStack;

public class WallclockDumpSmokeTest extends JfrDumpTest {
    public WallclockDumpSmokeTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=5ms";
    }

    @RetryingTest(3)
    @Timeout(value = 60)
    @ValueSource(strings = {"vm", "fp", "dwarf"})
    public void test() throws Exception {
        registerCurrentThreadForWallClockProfiling();
        runTest("datadog.MethodSample");
    }
}
