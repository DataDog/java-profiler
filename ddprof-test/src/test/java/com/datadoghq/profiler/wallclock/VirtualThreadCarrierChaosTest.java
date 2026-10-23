/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrFrame;
import com.datadoghq.profiler.JfrStackTrace;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.chaos.VirtualThreadRemountAntagonist;
import com.datadoghq.profiler.junit.CStack;
import java.time.Duration;
import java.util.Arrays;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

/** Checks CPU and wall-clock stack correctness while a shared chaos workload repeatedly remounts. */
public class VirtualThreadCarrierChaosTest extends CStackAwareAbstractProfilerTest {
    private static final String WORKLOAD_CLASS = VirtualThreadRemountAntagonist.class.getName();
    private final boolean carrierFrames;

    /** Selects carrier walking or the ordinary VM-mode control. */
    public VirtualThreadCarrierChaosTest(@CStack String cstack) {
        super(cstack);
        carrierFrames = "vmx".equals(cstack);
    }

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isJavaVersionAtLeast(21) && !Platform.isJ9() && !Platform.isZing()
                && !(isInCI() && Platform.isMusl() && !Platform.isAarch64());
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=2ms,wall=2ms,walltpt=64,filter=,jstackdepth=512";
    }

    /** Requires exercised return barriers and checks both layouts in each sampling engine. */
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx"})
    public void retainsCarrierAncestryDuringRepeatedRemounts() throws Exception {
        String seconds = System.getenv("DDPROF_VTHREAD_STRESS_SECONDS");
        long duration = seconds == null ? 6 : Long.parseLong(seconds);
        assertTrue(duration >= 2 && duration <= 3600, "Stress duration must be 2..3600 seconds");
        waitForProfilerReady(2_000);
        VirtualThreadRemountAntagonist workload = new VirtualThreadRemountAntagonist();
        try {
            workload.start();
            Thread.sleep(duration * 1000);
        } finally {
            try {
                workload.stopGracefully(Duration.ofSeconds(10));
            } finally {
                stopProfiler();
            }
        }
        assertTrue(workload.registerCycles() >= 10, "Register-argument workers made insufficient progress");
        assertTrue(workload.stackCycles() >= 10, "Stack-argument workers made insufficient progress");
        assertTrue(profiler.getDebugCounters().getOrDefault("walkvm_cont_barrier_hit", 0L) >= 20,
                "The stress run must sample continuation return barriers");
        verifyCStackSettings();
        assertStacks("datadog.ExecutionSample");
        assertStacks("datadog.MethodSample");
    }

    /** Reduces streamed events so extending the run does not retain every sampled stack in memory. */
    private void assertStacks(String eventType) {
        StackCounts counts = reduceEvents(eventType, StackCounts::new, StackCounts::accept);
        System.out.println(eventType + " carrier=" + carrierFrames + " " + counts);
        assertEquals(0, counts.continuationErrors, "Continuation recovery errors: " + counts);
        assertEquals(0, counts.invalidAncestry, "Missing, duplicated or misplaced carrier frames: " + counts
                + (counts.firstInvalidAncestry == null ? "" : "\nFirst invalid stack: " + counts.firstInvalidAncestry));
        assertEquals(0, counts.falseComplete, "Missing outer callers reported complete: " + counts);
        for (int layout = 0; layout < 2; layout++) {
            assertTrue(counts.eligible[layout] >= 10,
                    eventType + " must capture both argument layouts: " + counts);
        }
    }

    /** Counts boundary walks separately from samples interrupted before reaching a boundary. */
    private final class StackCounts {
        private final long[] eligible = new long[2];
        private final long[] otherStops = new long[2];
        private long continuationErrors;
        private long invalidAncestry;
        private String firstInvalidAncestry;
        private long falseComplete;

        private void accept(JfrEvent event) {
            JfrStackTrace trace = event.getStackTrace();
            boolean register = false;
            boolean stack = false;
            boolean outer = false;
            boolean continuationError = false;
            int carriers = 0;
            int carrierIndex = -1;
            int lastApplicationIndex = -1;
            int roots = 0;
            int index = 0;
            for (JfrFrame frame : trace.frames()) {
                String method = frame.methodName();
                if (WORKLOAD_CLASS.equals(frame.className())) {
                    register |= "registerFrames".equals(method);
                    stack |= "stackFrames".equals(method);
                    outer |= "registerWorkload".equals(method) || "stackWorkload".equals(method);
                    lastApplicationIndex = index;
                }
                if ("java.util.concurrent.ForkJoinWorkerThread".equals(frame.className())
                        && "run".equals(method)) {
                    carriers++;
                    carrierIndex = index;
                }
                if ("JVM Continuation".equals(method)) roots++;
                if (method != null && method.startsWith("break_cont_")) continuationError = true;
                index++;
            }
            if (!register && !stack) return;
            if (continuationError) {
                continuationErrors++;
                return;
            }
            int layout = stack ? 1 : 0;
            if (carriers == 0 && roots == 0) {
                otherStops[layout]++;
                if (!trace.isTruncated()) falseComplete++;
                return;
            }
            eligible[layout]++;
            if (register && stack || (carrierFrames
                    ? carriers != 1 || roots != 0 || carrierIndex <= lastApplicationIndex
                    : carriers != 0 || roots != 1)) {
                invalidAncestry++;
                if (firstInvalidAncestry == null) {
                    firstInvalidAncestry = "register=" + register + " stack=" + stack + " carriers=" + carriers
                            + " roots=" + roots + " truncated=" + trace.isTruncated() + "\n" + event.getStackTraceString();
                }
            }
            if (!outer && !trace.isTruncated()) falseComplete++;
        }

        /** Reports coverage and failures without retaining sampled stacks. */
        @Override
        public String toString() {
            return "eligible=" + Arrays.toString(eligible) + " otherStops=" + Arrays.toString(otherStops)
                    + " continuationErrors=" + continuationErrors + " invalidAncestry=" + invalidAncestry
                    + " falseComplete=" + falseComplete;
        }
    }
}
