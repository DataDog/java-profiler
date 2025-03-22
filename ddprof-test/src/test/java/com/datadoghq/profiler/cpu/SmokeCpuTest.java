package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.util.concurrent.ExecutionException;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.Platform;

public class SmokeCpuTest extends CStackAwareAbstractProfilerTest {
    public SmokeCpuTest(@CStack String cstack) {
        super(cstack);
    }

    @RetryTest(10)
    @TestTemplate
    @ValueSource(strings = {"fp", "dwarf", "vm", "vmx"})
    public void testComputations(@CStack String cstack) throws Exception {
        try (ProfiledCode profiledCode = new ProfiledCode(profiler)) {
            for (int i = 0, id = 1; i < 100; i++, id += 3) {
                profiledCode.method1(id);
            }
            stopProfiler();

            verifyCStackSettings();

            IItemCollection events = verifyEvents("datadog.ExecutionSample");

            // on mac the usage of itimer to drive the sampling provides very unreliable outputs
            for (IItemIterable cpuSamples : events) {
                IMemberAccessor<String, IItem> frameAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(cpuSamples.getType());
                for (IItem sample : cpuSamples) {
                    String stackTrace = frameAccessor.getMember(sample);
                    assertFalse(stackTrace.contains("jvmtiError"));
                    if ("vmx".equals(stackTrace)) {
                        // extra checks to make sure we see the mixed stacktraces
                        assertTrue(stackTrace.contains("JavaCalls::call_virtual()"),
                                "JavaCalls::call_virtual() (above call_stub) found in stack trace");
                        assertTrue(stackTrace.contains("call_stub()"),
                                "call_stub() (sentinel value used to halt unwinding) found in stack trace");
                    }
                }
            }
        }
    }

    @RetryTest(10)
    @TestTemplate
    @ValueSource(strings = {"vm", "fp", "dwarf", "vmx"})
    public void testIOBound(@CStack String cstack) throws Exception {
        new IOBoundCode().run();

        stopProfiler();

        verifyCStackSettings();

        IItemCollection events = verifyEvents("datadog.ExecutionSample");

        // on mac the usage of itimer to drive the sampling provides very unreliable outputs
        for (IItemIterable cpuSamples : events) {
            IMemberAccessor<String, IItem> frameAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(cpuSamples.getType());
            for (IItem sample : cpuSamples) {
                String stackTrace = frameAccessor.getMember(sample);
                assertFalse(stackTrace.contains("jvmtiError"));
                if ("vmx".equals(stackTrace)) {
                    // extra checks to make sure we see the mixed stacktraces
                    assertTrue(stackTrace.contains("JavaCalls::call_virtual()"),
                            "JavaCalls::call_virtual() (above call_stub) found in stack trace");
                    assertTrue(stackTrace.contains("call_stub()"),
                            "call_stub() (sentinel value used to halt unwinding) found in stack trace");
                }
            }
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms";
    }
}
