package com.datadoghq.profiler.jfr;

import com.datadoghq.profiler.Platform;

import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Timeout;

import com.datadoghq.profiler.junit.CStack;
import org.junitpioneer.jupiter.RetryingTest;
import org.junit.jupiter.params.provider.ValueSource;

public class ObjectSampleDumpSmokeTest extends JfrDumpTest {
    public ObjectSampleDumpSmokeTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected boolean isPlatformSupported() {
        return !Platform.isJavaVersion(8) && !Platform.isJ9();
    }

    @Override
    protected String getProfilerCommand() {
        return "memory=32:a";
    }

    @RetryingTest(5)
    @Timeout(value = 300)
    @ValueSource(strings = {"vm", "fp", "dwarf"})
    public void test() throws Exception {
        runTest("datadog.ObjectSample", 3, "method3");
    }
}
