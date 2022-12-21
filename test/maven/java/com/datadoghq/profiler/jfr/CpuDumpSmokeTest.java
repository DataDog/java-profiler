package com.datadoghq.profiler.jfr;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

public class CpuDumpSmokeTest extends JfrDumpTest {

    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms,cstack=no";
    }

    @Test
    @Timeout(value = 30)
    public void test() throws Exception {
        runTest("datadog.ExecutionSample");
    }
}
