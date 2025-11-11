package com.datadoghq.profiler.jfr;

import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;

import java.util.concurrent.ExecutionException;

import org.junit.jupiter.api.Timeout;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;

public class CpuDumpSmokeTest extends JfrDumpTest {
    public CpuDumpSmokeTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms";
    }

    @Timeout(value = 60)
    @RetryTest(3)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx", "fp", "dwarf"})
    public void test(@CStack String cstack) throws ExecutionException, InterruptedException, Exception {
        if (!isOnBlackList(cstack)) {
            test();
        }
    }

    private void test() throws Exception {
        runTest("datadog.ExecutionSample");
    }
}
