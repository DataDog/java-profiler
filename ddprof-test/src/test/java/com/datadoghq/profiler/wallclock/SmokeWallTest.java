package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.cpu.ProfiledCode;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.util.concurrent.ExecutionException;

import static org.junit.jupiter.api.Assertions.assertFalse;

public class SmokeWallTest extends CStackAwareAbstractProfilerTest {
    private ProfiledCode profiledCode;

    public SmokeWallTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected void before() {
        profiledCode = new ProfiledCode(profiler);
    }

    @RetryTest(10)
    @TestTemplate
    @ValueSource(strings = {"fp", "dwarf", "vm", "vmx"})
    public void test(@CStack String cstack) throws ExecutionException, InterruptedException {
        for (int i = 0, id = 1; i < 100; i++, id += 3) {
            profiledCode.method1(id);
        }
        stopProfiler();

        verifyCStackSettings();

        IItemCollection events = verifyEvents("datadog.MethodSample");

        // on mac the usage of itimer to drive the sampling provides very unreliable outputs
//        if (!Platform.isMac()) {
            for (IItemIterable cpuSamples : events) {
                IMemberAccessor<String, IItem> frameAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(cpuSamples.getType());
                for (IItem sample : cpuSamples) {
                    String stackTrace = frameAccessor.getMember(sample);
                    assertFalse(stackTrace.contains("jvmtiError"));
                }
            }
//        }
    }

    @Override
    protected void after() throws Exception {
        profiledCode.close();
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms";
    }
}
