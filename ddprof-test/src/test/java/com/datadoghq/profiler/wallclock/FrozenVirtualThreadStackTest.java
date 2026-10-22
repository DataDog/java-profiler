/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.JfrFrame;
import com.datadoghq.profiler.JfrStackTrace;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.junit.CStack;
import java.util.concurrent.FutureTask;
import java.util.concurrent.locks.LockSupport;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/** Checks stack completeness against the JVM's logical stack after virtual-thread remounts. */
public class FrozenVirtualThreadStackTest extends CStackAwareAbstractProfilerTest {
    private static final int RECURSION_DEPTH = 128;

    private volatile long sink;
    private StackTraceElement[] logicalStack;

    /** Selects the VM walker with or without carrier frames. */
    public FrozenVirtualThreadStackTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected boolean isPlatformSupported() {
        // CStackInjector falls back to the first mode when every mode is excluded.
        // Keep that fallback from re-enabling VM walking on musl x64 in CI.
        return Platform.isJavaVersionAtLeast(21) && !Platform.isJ9() && !Platform.isZing()
                && !(isInCI() && Platform.isMusl() && !Platform.isAarch64());
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,walltpt=64,filter=,jstackdepth=256";
    }

    /** Missing logical callers must be marked truncated in both VM walking modes. */
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx"})
    public void marksSkippedFrozenCallersTruncated() throws Exception {
        runWorkload(true, true);
        assertTrue(profiler.getDebugCounters().getOrDefault("walkvm_cont_barrier_hit", 0L) > 0,
                "The workload must encounter a continuation return barrier");

        int[] counts = reduceEvents("datadog.MethodSample", () -> new int[2], (count, sample) -> {
            JfrStackTrace trace = sample.getStackTrace();
            if (containsMethod(trace, "recursiveWorkload") && !containsMethod(trace, "outerWorkload")) {
                count[0]++;
                if (!trace.isTruncated()) count[1]++;
            }
        });
        assertTrue(counts[0] > 0, "The workload must leave application callers frozen");
        assertEquals(0, counts[1], "Samples omitted a JVM-confirmed caller but reported a complete stack");
    }

    /** The same parked workload on a platform thread keeps its application callers on the stack. */
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx"})
    public void keepsPlatformCallersComplete() throws Exception {
        runWorkload(false, true);
        assertCompleteCallers();
    }

    /** Ending at a fully thawed continuation is a complete logical stack in the ordinary VM mode. */
    @TestTemplate
    @ValueSource(strings = {"vm"})
    public void keepsFullyThawedContinuationComplete() throws Exception {
        runWorkload(true, false);
        assertCompleteCallers();
    }

    /** Runs the same recursion on either kind of thread and verifies that its callers really exist. */
    private void runWorkload(boolean virtual, boolean park) throws Exception {
        waitForProfilerReady(2_000);
        FutureTask<Void> task = new FutureTask<>(() -> {
            outerWorkload(park);
            return null;
        });
        Thread worker;
        if (virtual) {
            // Reflection keeps the test compatible with the Java 8 compilation target.
            worker = (Thread) Thread.class.getMethod("startVirtualThread", Runnable.class)
                    .invoke(null, task);
        } else {
            worker = new Thread(task, "platform-stack-control");
            worker.start();
        }
        worker.join(10_000);
        assertFalse(worker.isAlive(), "The stack workload did not finish");
        task.get();
        stopProfiler();

        int recursion = 0;
        boolean outer = false;
        for (StackTraceElement frame : logicalStack) {
            if (!getClass().getName().equals(frame.getClassName())) continue;
            if (frame.getMethodName().equals("recursiveWorkload")) recursion++;
            if (frame.getMethodName().equals("outerWorkload")) outer = true;
        }
        assertEquals(RECURSION_DEPTH + 1, recursion, "The JVM must preserve all recursive callers");
        assertTrue(outer, "The outer caller must be present in the JVM logical stack");
    }

    /** Checks the negative controls without letting a run with no sampled callers pass. */
    private void assertCompleteCallers() {
        int[] counts = reduceEvents("datadog.MethodSample", () -> new int[2], (count, sample) -> {
            JfrStackTrace trace = sample.getStackTrace();
            if (containsMethod(trace, "recursiveWorkload") && containsMethod(trace, "outerWorkload")) {
                count[0]++;
                if (trace.isTruncated()) count[1]++;
            }
        });
        assertTrue(counts[0] > 0, "No sample retained the outer application caller");
        assertEquals(0, counts[1], "Fully captured control stacks were marked truncated");
    }

    private boolean containsMethod(JfrStackTrace trace, String method) {
        for (JfrFrame frame : trace.frames()) {
            if (getClass().getName().equals(frame.className()) && method.equals(frame.methodName())) {
                return true;
            }
        }
        return false;
    }

    private void outerWorkload(boolean park) {
        long deadline = System.nanoTime() + 2_000_000_000L;
        while (System.nanoTime() < deadline) recursiveWorkload(RECURSION_DEPTH, park);
    }

    /** Work after the recursive call keeps callers alive; deep recursion exceeds partial-thaw sizes. */
    private void recursiveWorkload(int depth, boolean park) {
        if (depth > 0) {
            recursiveWorkload(depth - 1, park);
        } else {
            if (park) LockSupport.parkNanos(500_000L);
            if (logicalStack == null) logicalStack = Thread.currentThread().getStackTrace();
            long deadline = System.nanoTime() + 2_000_000L;
            while (System.nanoTime() < deadline) sink ^= System.nanoTime();
        }
        sink += depth;
    }
}
