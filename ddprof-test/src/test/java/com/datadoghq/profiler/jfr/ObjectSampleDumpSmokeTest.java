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

    @Override
    protected void method3() {
        // Allocation profiling: Create many String objects to trigger allocation sampling
        // Simulates the original File.list() pattern without I/O dependency
        for (int i = 0; i < 500; ++i) {
            int cntr = 10;
            // Create String array and perform substring operations (allocation-heavy)
            String[] files =
                    new String[] {
                        "file_" + i + "_0.txt",
                        "file_" + i + "_1.txt",
                        "file_" + i + "_2.txt",
                        "file_" + i + "_3.txt",
                        "file_" + i + "_4.txt"
                    };
            for (String s : files) {
                if (s != null && !s.isEmpty()) {
                    value += s.substring(0, Math.min(s.length(), 16)).hashCode();
                    if (--cntr < 0) {
                        break;
                    }
                }
            }
        }
    }

    @RetryTest(5)
    @Timeout(value = 300)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx", "fp", "dwarf"})
    public void test(@CStack String cstack) throws Exception {
        runTest("datadog.ObjectSample", 3, "method3");
    }
}
