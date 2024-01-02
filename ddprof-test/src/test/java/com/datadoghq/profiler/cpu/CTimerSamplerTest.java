package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.util.Map;
import java.util.Set;
import java.util.concurrent.ExecutionException;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assumptions.assumeFalse;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

public class CTimerSamplerTest extends AbstractProfilerTest {

    private ProfiledCode profiledCode;

    @Override
    protected void before() {
        profiledCode = new ProfiledCode(profiler);
    }

    @RetryingTest(10)
    public void test() throws ExecutionException, InterruptedException {
        // timer_create is available on Linux only
        assumeTrue(Platform.isLinux());
        for (int i = 0, id = 1; i < 100; i++, id += 3) {
            profiledCode.method1(id);
        }
        stopProfiler();
        IItemCollection events = verifyEvents("datadog.ExecutionSample");

        for (IItemIterable cpuSamples : events) {
            IMemberAccessor<String, IItem> frameAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(cpuSamples.getType());
            for (IItem sample : cpuSamples) {
                String stackTrace = frameAccessor.getMember(sample);
                assertFalse(stackTrace.contains("jvmtiError"));
            }
        }
    }

    @Override
    protected void after() throws Exception {
        profiledCode.close();
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=100us,event=ctimer";
    }
}
