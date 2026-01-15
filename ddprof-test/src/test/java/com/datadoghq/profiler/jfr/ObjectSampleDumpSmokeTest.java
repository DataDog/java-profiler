package com.datadoghq.profiler.jfr;

import com.datadoghq.profiler.Platform;

import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Timeout;
import org.junit.jupiter.params.provider.ValueSource;
import org.junit.jupiter.api.TestTemplate;

import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;

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

    @RetryTest(5)
    @Timeout(value = 300)
    @TestTemplate
    @ValueSource(strings = {"vm", "fp", "dwarf"})
    public void test(@CStack String cstack) throws Exception {
        runTest("datadog.ObjectSample", 3, "method3");
    }
}
