package com.datadoghq.profiler.loadlib;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.IMCFrame;
import org.openjdk.jmc.common.IMCStackTrace;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;

import java.lang.management.ClassLoadingMXBean;
import java.lang.management.ManagementFactory;

import static org.junit.jupiter.api.Assertions.assertTrue;

public class LoadLibraryTest extends AbstractProfilerTest {

    @Test
    public void testLoadLibrary() throws InterruptedException {
        for (int i = 0; i < 200; i++) {
            Thread.sleep(10);
        }
        // Late load of libmanagement.so
        ClassLoadingMXBean bean = ManagementFactory.getClassLoadingMXBean();

        long n = 0;
        while (n >= 0) {
            n += bean.getLoadedClassCount();
            n += bean.getTotalLoadedClassCount();
            n += bean.getUnloadedClassCount();
        }
        stopProfiler();
        verifyEventsPresent("datadog.ExecutionSample");
        IItemCollection executionSamples = verifyEvents("datadog.ExecutionSample");
        boolean ok = false;
        outer: for (IItemIterable sample : executionSamples) {
            IMemberAccessor<IMCStackTrace, IItem> stackTraceAccessor = STACK_TRACE.getAccessor(sample.getType());
            for (IItem item : sample) {
                IMCStackTrace stackTrace = stackTraceAccessor.getMember(item);
                for (IMCFrame frame : stackTrace.getFrames()) {
                    System.err.println("debug: " + frame.getMethod().getMethodName());
                    if (frame.getMethod().getMethodName().contains("Java_sun_management")) {
                        ok = true;
                        break outer;
                    }
                }
            }
        }
        assertTrue(ok, "couldn't find datadog.ExecutionSample with Java_sun_management frame");
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms";
    }
}
