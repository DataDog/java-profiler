package com.datadoghq.profiler.jfr;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

public class WallclockDumpSmokeTest extends JfrDumpTest {

    @Override
    protected String getProfilerCommand() {
        return "wall=5ms";
    }

    @Test
    @Timeout(value = 30)
    public void test() throws Exception {
        registerCurrentThreadForWallClockProfiling();
        runTest("datadog.MethodSample");
    }
}
