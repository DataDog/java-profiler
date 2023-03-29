package com.datadoghq.profiler.jfr;

import com.datadoghq.profiler.Platform;

import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Timeout;

import org.junitpioneer.jupiter.RetryingTest;

public class ObjectSampleDumpSmokeTest extends JfrDumpTest {
    @Override
    protected String getProfilerCommand() {
        return "memory=16536:a";
    }

    @RetryingTest(3)
    @Timeout(value = 60)
    public void test() throws Exception {
        Assumptions.assumeFalse(Platform.isJ9());
        runTest("datadog.ObjectSample", "method3");
    }
}
