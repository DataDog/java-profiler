package com.datadoghq.profiler.jfr;

import org.junit.jupiter.api.Timeout;

import org.junitpioneer.jupiter.RetryingTest;

public class WallclockDumpSmokeTest extends JfrDumpTest {

    @Override
    protected String getProfilerCommand() {
        return "wall=5ms";
    }

    @RetryingTest(3)
    @Timeout(value = 60)
    public void test() throws Exception {
        registerCurrentThreadForWallClockProfiling();
        runTest("datadog.MethodSample");
    }
}
