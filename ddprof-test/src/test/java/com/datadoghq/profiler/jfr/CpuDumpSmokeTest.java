package com.datadoghq.profiler.jfr;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;
import org.junitpioneer.jupiter.RetryingTest;
import org.junit.jupiter.params.provider.ValueSource;

import com.datadoghq.profiler.junit.CStack;

public class CpuDumpSmokeTest extends JfrDumpTest {
    public CpuDumpSmokeTest(@CStack String cstack) {
        super(cstack);
    }
    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms";
    }

    @RetryingTest(3)
    @Timeout(value = 60)
    @ValueSource(strings = {"vm", "fp", "dwarf"})
    public void test() throws Exception {
        runTest("datadog.ExecutionSample");
    }
}
