package com.datadoghq.profiler.jfr;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;
import org.junitpioneer.jupiter.RetryingTest;

public class CpuDumpSmokeTest extends JfrDumpTest {

    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms";
    }

    @RetryingTest(3)
    @Timeout(value = 60)
    public void test() throws Exception {
        runTest("datadog.ExecutionSample");
    }
}
