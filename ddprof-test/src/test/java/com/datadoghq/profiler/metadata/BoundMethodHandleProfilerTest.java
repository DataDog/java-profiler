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

public class BoundMethodHandleProfilerTest extends AbstractProfilerTest {
    @Override
    protected String getProfilerCommand() {
        if (Platform.isJ9()) {
            return "wall=100ms";
        }
        // wall=100us is ~10k samples/s. Under ASAN the workload runs for minutes,
        // producing a JFR too large for JMC to load into the 512MB test heap. Sampling
        // 10x coarser cuts both the recording size and the SIGVTALRM overhead.
        return isAsan() ? "wall=1ms" : "wall=100us";
    }

    @Test
    public void test() throws Throwable {
        assumeFalse(Platform.isJ9() && isAsan()); // running this test on j9 and asan is weirdly crashy
        assumeFalse(Platform.isJ9() && Platform.isJavaVersion(8)); // geting crash-failur in CI reliable; remove once that is fixed
        assumeFalse(Platform.isJ9() && Platform.isJavaVersion(17)); // JVMTI::GetClassSignature() is reliably crashing on a valid 'class' instance
        assumeFalse(Platform.isAarch64() && Platform.isMusl() && !Platform.isJavaVersionAtLeast(11)); // aarch64 + musl + jdk 8 will crash very often
        registerCurrentThreadForWallClockProfiling();
        // Reduce workload on aarch64+asan: ASAN slows each invocation enough that the test
        // takes 3+ minutes, generating a JFR that OOMs the 512MB test-runner heap. Combined
        // with the coarser wall rate in getProfilerCommand(), 500 keeps the recording small
        // while still generating enough bound-method-handle classes to sample.
        int numBoundMethodHandles = isAsan() && Platform.isAarch64() ? 500 : 10_000;
        int x = generateBoundMethodHandles(numBoundMethodHandles);
        assertTrue(x != 0);
        stopProfiler();
        verifyEvents("datadog.MethodSample");
        Map<String, Long> counters = profiler.getDebugCounters();
        assertFalse(counters.isEmpty(), "profiler debug counters must not be empty after BoundMethodHandle workload");
    }



    public static String append(String string, int suffix) {
        return string + suffix;
    }

    public static int generateBoundMethodHandles(int howMany) throws Throwable {
        int total = 0;
        MethodHandle append = MethodHandles.lookup()
                .findStatic(BoundMethodHandleProfilerTest.class,
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
