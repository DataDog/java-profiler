package com.datadoghq.profiler.metadata;

import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;

import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodHandles;
import java.lang.invoke.MethodType;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeFalse;

public class BoundMethodHandleMetadataSizeTest extends AbstractProfilerTest {
    @Override
    protected String getProfilerCommand() {
        return "wall=100us";
    }

    @Test
    public void test() throws Throwable {
        assumeFalse(Platform.isJ9() && isAsan()); // running this test on j9 and asan is weirdly crashy
        assumeFalse(Platform.isJ9() && Platform.isJavaVersion(8)); // geting crash-failur in CI reliable; remove once that is fixed
        assumeFalse(Platform.isJ9() && Platform.isJavaVersion(17)); // JVMTI::GetClassSignature() is reliably crashing on a valid 'class' instance
        assumeFalse(Platform.isAarch64() && Platform.isMusl() && !Platform.isJavaVersionAtLeast(11)); // aarch64 + musl + jdk 8 will crash very often
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
                .findStatic(BoundMethodHandleMetadataSizeTest.class,
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
