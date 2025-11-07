package com.datadoghq.profiler.jfr;

import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;

import java.util.concurrent.ExecutionException;

import org.junit.jupiter.api.Timeout;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;

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
    public void test(@CStack String cstack) throws ExecutionException, InterruptedException, Exception {
        test();
    }

    private void test() throws Exception {
        registerCurrentThreadForWallClockProfiling();
        runTest("datadog.MethodSample");
    }
}
