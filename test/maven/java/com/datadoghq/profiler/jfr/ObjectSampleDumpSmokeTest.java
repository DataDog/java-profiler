package com.datadoghq.profiler.jfr;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

public class ObjectSampleDumpSmokeTest extends JfrDumpTest {

    @Override
    protected String getProfilerCommand() {
        return "memory=16536:a";
    }

    @Test
    @Timeout(value = 60)
    public void test() throws Exception {
        runTest("datadog.ObjectSample", "method3");
    }
}
