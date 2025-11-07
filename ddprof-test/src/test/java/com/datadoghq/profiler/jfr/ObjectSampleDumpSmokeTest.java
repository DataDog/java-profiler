package com.datadoghq.profiler.jfr;

import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;

import java.util.concurrent.ExecutionException;

import org.junit.jupiter.api.Timeout;
import org.junit.jupiter.api.TestTemplate;
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

    @RetryTest(5)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx", "fp", "dwarf"})
    @Timeout(value = 300)
    public void test(@CStack String cstack) throws ExecutionException, InterruptedException, Exception {
        test();
    }

    private void test() throws Exception {
        runTest("datadog.ObjectSample", 3, "method3");
    }
}
