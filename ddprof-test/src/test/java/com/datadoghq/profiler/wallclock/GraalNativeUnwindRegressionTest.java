/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrFrame;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.junit.CStack;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.FutureTask;
import java.util.concurrent.TimeUnit;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;

import static org.junit.jupiter.api.Assertions.assertAll;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Isolates native gaps around System.nanoTime from continuation remounts. Run the same test on
 * GraalVM and a HotSpot control, with and without preserved frame pointers, against each profiler
 * candidate. Platform threads provide a control without continuation entry or return barriers.
 */
public class GraalNativeUnwindRegressionTest extends CStackAwareAbstractProfilerTest {
    private volatile boolean running;
    private volatile long sink;

    /** Selects the VM walker with or without carrier walking. */
    public GraalNativeUnwindRegressionTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected boolean isPlatformSupported() {
        // Other JITs can inline nanoTime without exposing a Java transition frame.
        // Controls explicitly disable its intrinsic and opt in through this property.
        boolean control = Boolean.getBoolean("ddprof_test.native_unwind_control");
        return Platform.isJavaVersionAtLeast(21) && !Platform.isJ9() && !Platform.isZing()
                && (control || Platform.isGraal() && Platform.isLinux() && Platform.isAarch64())
                && !(isInCI() && Platform.isMusl() && !Platform.isAarch64());
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=2ms,wall=2ms,walltpt=64,filter=,jstackdepth=128";
    }

    /** Requires native coverage on a platform thread, independently of continuation recovery. */
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx"})
    public void retainsNativeCoverageOnPlatformThread() throws Exception {
        runNanoTimeWorkload(false);
    }

    /** Uses a never-parked virtual thread to separate native transitions from partial thaw. */
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx"})
    public void retainsNativeCoverageOnVirtualThread() throws Exception {
        runNanoTimeWorkload(true);
    }

    /** Runs one bounded worker; propagates its failures and always stops profiling. */
    private void runNanoTimeWorkload(boolean virtual) throws Exception {
        waitForProfilerReady(2_000);
        CountDownLatch started = new CountDownLatch(1);
        running = true;
        FutureTask<Void> task = new FutureTask<>(() -> {
            started.countDown();
            nanoTimeWorkload();
            return null;
        });
        Thread worker = null;
        try {
            if (virtual) {
                // Reflection preserves the Java 8 compilation target.
                worker = (Thread) Thread.class.getMethod("startVirtualThread", Runnable.class).invoke(null, task);
            } else {
                worker = new Thread(task, "nano-time-native-control");
                worker.start();
            }
            assertTrue(started.await(10, TimeUnit.SECONDS), "The native workload did not start");
            Thread.sleep(6_000);
        } finally {
            running = false;
            try {
                if (worker != null) {
                    worker.join(10_000);
                    assertFalse(worker.isAlive(), "The native workload did not stop");
                    task.get(1, TimeUnit.SECONDS);
                }
            } finally {
                stopProfiler();
            }
        }
        verifyCStackSettings();
        assertAll(
                () -> assertNativeCoverage("datadog.ExecutionSample"),
                () -> assertNativeCoverage("datadog.MethodSample"));
    }

    /** Keeps the real clock call hot without parking, recursion, or a native test shim. */
    private void nanoTimeWorkload() {
        long value = 1;
        while (running) {
            value = (value * 6364136223846793005L) ^ System.nanoTime();
            sink = value;
        }
    }

    /** Applies the existing 99% coverage requirement to samples with a decoded workload frame. */
    private void assertNativeCoverage(String eventType) {
        NativeCoverage coverage = reduceEvents(eventType, NativeCoverage::new, NativeCoverage::accept);
        String message = eventType + " " + coverage;
        System.out.println(message);
        assertAll(message,
                () -> assertTrue(coverage.samples >= 100, "Insufficient workload samples"),
                () -> assertTrue(coverage.nanoTimeSamples >= 20,
                        "No evidence of sampled System.nanoTime transitions; result is inconclusive"),
                () -> assertTrue((coverage.samples - coverage.nativeGaps) * 100L >= coverage.samples * 99L,
                        "Fewer than 99% of workload samples avoided native gaps"));
    }

    /** Streams counts and one diagnostic stack without retaining the recording's samples. */
    private static final class NativeCoverage {
        private long samples;
        private long nanoTimeSamples;
        private long nativeGaps;
        private String firstGap;

        private void accept(JfrEvent event) {
            boolean workload = false, nanoTime = false, skipped = false;
            for (JfrFrame frame : event.getStackTrace().frames()) {
                workload |= GraalNativeUnwindRegressionTest.class.getName().equals(frame.className())
                        && "nanoTimeWorkload".equals(frame.methodName());
                nanoTime |= "java.lang.System".equals(frame.className()) && "nanoTime".equals(frame.methodName());
                skipped |= "[skipped frames]".equals(frame.methodName());
            }
            if (!workload) return;
            samples++;
            if (nanoTime) nanoTimeSamples++;
            if (nanoTime && skipped) {
                nativeGaps++;
                if (firstGap == null) {
                    StringBuilder text = new StringBuilder();
                    for (JfrFrame frame : event.getStackTrace().frames()) {
                        text.append("\n  ").append(frame.className()).append('.').append(frame.methodName());
                    }
                    firstGap = text.toString();
                }
            }
        }

        @Override
        public String toString() {
            return "samples=" + samples + " nanoTimeSamples=" + nanoTimeSamples + " nativeGaps=" + nativeGaps
                    + (firstGap == null ? "" : " firstGap=" + firstGap);
        }
    }
}
