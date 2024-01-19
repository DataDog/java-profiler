package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.util.concurrent.ExecutionException;

import static org.junit.jupiter.api.Assertions.assertFalse;


public class VMStructsBasedCpuTest extends AbstractProfilerTest {

    private ProfiledCode profiledCode;

    @Override
    protected void before() {
        profiledCode = new ProfiledCode(profiler);
    }

    @Test
    public void test() throws ExecutionException, InterruptedException {
        for (int i = 0, id = 1; i < 100; i++, id += 3) {
            profiledCode.method1(id);
        }
        stopProfiler();
        IItemCollection events = verifyEvents("datadog.ExecutionSample");
        for (IItemIterable it : events) {
            IMemberAccessor<String, IItem> stackTraceAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(it.getType());
            for (IItem item : it) {
                String stacktrace = stackTraceAccessor.getMember(item);
                assertFalse(stacktrace.contains("JavaCalls::call_virtual()"),
                        "JavaCalls::call_virtual() (above call_stub) found in stack trace");
                assertFalse(stacktrace.contains("call_stub()"),
                        "call_stub() (sentinel value used to halt unwinding) found in stack trace");
            }
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms" + (vmstructsUnwinderSupported() ? ",cstack=vm" : "");
    }

    private boolean vmstructsUnwinderSupported() {
        return !Platform.isJ9() && !Platform.isZing();
    }
}
