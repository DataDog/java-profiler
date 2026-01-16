package com.datadoghq.profiler.jfr;

import org.junit.jupiter.api.Timeout;
import org.junit.jupiter.params.provider.ValueSource;
import org.junit.jupiter.api.TestTemplate;

import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;

public class WallclockDumpSmokeTest extends JfrDumpTest {
    public WallclockDumpSmokeTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=5ms";
    }

    @RetryTest(3)
    @Timeout(value = 60)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx", "fp", "dwarf"})
    public void test(@CStack String cstack) throws Exception {
        registerCurrentThreadForWallClockProfiling();
        runTest("datadog.MethodSample");
    }
}
