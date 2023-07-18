package com.datadoghq.profiler.metadata;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;

import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodHandles;
import java.lang.invoke.MethodType;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class BoundMethodHandeMetadataSizeTest extends AbstractProfilerTest {
    @Override
    protected String getProfilerCommand() {
        return "wall=1us";
    }

    @Test
    public void test() throws Throwable {
        registerCurrentThreadForWallClockProfiling();
        int numBoundMethodHandles = 10_000;
        int x = generateBoundMethodHandles(numBoundMethodHandles);
        assertTrue(x != 0);
        stopProfiler();
        verifyEvents("datadog.MethodSample");
        Map<String, Long> counters = profiler.getDebugCounters();
        assertFalse(counters.isEmpty());
        // assert about the size of metadata here
    }



    public static String append(String string, int suffix) {
        return string + suffix;
    }

    public static int generateBoundMethodHandles(int howMany) throws Throwable {
        int total = 0;
        MethodHandle append = MethodHandles.lookup()
                .findStatic(BoundMethodHandeMetadataSizeTest.class,
                        "append",
                        MethodType.methodType(String.class, String.class, int.class));
        for (int i = 0; i < howMany; i++) {
            // binding many constants amplifies the effect of class generation below
            MethodHandle bound = append.bindTo("string" + i);
            for (int j = 0; j < 1024; j++) {
                // many invocations has the effect of generate a new class
                total += ((String) bound.invokeExact(j)).length();
            }
        }
        return total;
    }
}
