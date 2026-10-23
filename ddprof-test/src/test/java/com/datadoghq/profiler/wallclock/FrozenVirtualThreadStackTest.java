/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.JfrFrame;
import com.datadoghq.profiler.JfrStackTrace;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.RemoteSymHelper;
import com.datadoghq.profiler.junit.CStack;
import java.lang.management.ManagementFactory;
import java.util.concurrent.FutureTask;
import java.util.concurrent.locks.LockSupport;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.TestInfo;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/** Checks recovered callers against the JVM's logical stack after virtual-thread remounts. */
public class FrozenVirtualThreadStackTest extends CStackAwareAbstractProfilerTest {
    private static final int RECURSION_DEPTH = 128;

    private volatile long sink;
    private StackTraceElement[] logicalStack;
    private boolean growChunks;
    private boolean nativeLeaf;
    private boolean cpuProfiling;
    private volatile boolean collecting;
    private volatile byte[] garbage;
    private int maxStackDepth = 256;

    /** Selects the VM walker with or without carrier frames. */
    public FrozenVirtualThreadStackTest(@CStack String cstack) {
        super(cstack);
    }

    /** Selects a deliberately small capture limit only for the depth-limit regression. */
    @Override
    @BeforeEach
    public void setupProfiler(TestInfo testInfo) throws Exception {
        maxStackDepth = testInfo.getTestMethod()
                .map(method -> method.getName().equals("respectsConfiguredDepth") ? 64 : 256)
                .orElse(256);
        cpuProfiling = testInfo.getTestMethod()
                .map(method -> method.getName().equals("restoresFrozenCallersForCpu"))
                .orElse(false);
        super.setupProfiler(testInfo);
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
        return (cpuProfiling ? "cpu=1ms,event=itimer" : "wall=1ms,walltpt=64")
                + ",filter=,jstackdepth=" + maxStackDepth;
    }

    /** Both VM walking modes must recover every application caller after a partial thaw. */
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx"})
    public void restoresFrozenCallers(@CStack String cstack) throws Exception {
        assumeTrue(!usesConcurrentRelocation());
        runWorkload(true, true);
        assertRecoveredCallers(cstack, false);
    }

    /** CPU samples must reconstruct the same callers as wall-clock samples. */
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx"})
    public void restoresFrozenCallersForCpu(@CStack String cstack) throws Exception {
        assumeTrue(!usesConcurrentRelocation());
        runWorkload(true, true);
        assertRecoveredCallers(cstack, false);
    }

    /** Repeated collection and remounting must not invalidate chunk or carrier oop discovery. */
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx"})
    public void restoresWhileCollecting(@CStack String cstack) throws Exception {
        assumeTrue(!usesConcurrentRelocation());
        long before = collectionCount();
        collecting = true;
        FutureTask<Void> task = new FutureTask<>(() -> {
            while (collecting) {
                for (int i = 0; i < 32; i++) garbage = new byte[8192];
                System.gc();
                LockSupport.parkNanos(20_000_000L);
            }
            return null;
        });
        Thread collector = new Thread(task, "frozen-stack-gc-control");
        collector.start();
        try {
            runWorkload(true, true);
        } finally {
            collecting = false;
            collector.join(10_000);
        }
        assertFalse(collector.isAlive(), "The GC workload did not finish");
        task.get();
        assertTrue(collectionCount() > before, "The workload must encounter garbage collection");
        assertRecoveredCallers(cstack, false);
    }

    /** A JNI call may be sampled while older callers are frozen, but raw heap reads are unsafe. */
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx"})
    public void preservesTruncationDuringNativeCalls(@CStack String cstack) throws Exception {
        nativeLeaf = true;
        runWorkload(true, true);
        int[] counts = reduceEvents("datadog.MethodSample", () -> new int[2], (count, sample) -> {
            JfrStackTrace trace = sample.getStackTrace();
            if ("NATIVE".equals(sample.getEnumName("mode")) && containsMethod(trace, "sampledLeaf")
                    && !containsMethod(trace, "outerWorkload")) {
                count[0]++;
                if (!trace.isTruncated()) count[1]++;
            }
        });
        assertTrue(counts[0] > 0, "No native-mode sample exercised the incomplete-stack fallback");
        assertEquals(0, counts[1], "Native-mode samples must acknowledge missing callers");
        assertTrue(profiler.getDebugCounters().getOrDefault("walkvm_frozen_failed", 0L) > 0,
                "Native execution must not attempt raw heap recovery");
    }

    /** A second park below still-frozen callers must follow the chunk's parent link. */
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx"})
    public void restoresAcrossParentChunks(@CStack String cstack) throws Exception {
        assumeTrue(!usesConcurrentRelocation());
        growChunks = true;
        runWorkload(true, true);
        assertRecoveredCallers(cstack, true);
        assertTrue(profiler.getDebugCounters().getOrDefault("walkvm_frozen_parent", 0L) > 0,
                "The workload must recover callers across multiple chunks");
    }

    /** Heap walking must obey the same capture limit and truncation contract as native walking. */
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx"})
    public void respectsConfiguredDepth(@CStack String cstack) throws Exception {
        runWorkload(true, true);
        int[] counts = reduceEvents("datadog.MethodSample", () -> new int[3], (count, sample) -> {
            JfrStackTrace trace = sample.getStackTrace();
            if (containsMethod(trace, "sampledLeaf")) {
                count[0]++;
                if (trace.frames().size() > maxStackDepth) count[1]++;
                if (!trace.isTruncated()) count[2]++;
            }
        });
        assertTrue(counts[0] > 0, "No sample captured the leaf workload");
        assertEquals(0, counts[1], "Heap walking exceeded the configured depth");
        assertEquals(0, counts[2], "Depth-limited application stacks must be truncated");
    }

    /** Concurrently relocating collectors retain the safe incomplete-stack fallback. */
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx"})
    public void preservesTruncationWhenRecoveryUnavailable(@CStack String cstack) throws Exception {
        assumeTrue(usesConcurrentRelocation());
        runWorkload(true, true);
        assertEquals(0L, profiler.getDebugCounters().getOrDefault("walkvm_frozen_recovered", 0L));
        assertTrue(profiler.getDebugCounters().getOrDefault("walkvm_frozen_failed", 0L) > 0);
        int[] counts = reduceEvents("datadog.MethodSample", () -> new int[2], (count, sample) -> {
            JfrStackTrace trace = sample.getStackTrace();
            if (containsMethod(trace, "sampledLeaf") && !containsMethod(trace, "outerWorkload")) {
                count[0]++;
                if (!trace.isTruncated()) count[1]++;
            }
        });
        assertTrue(counts[0] > 0, "No sample exercised the unavailable recovery path");
        assertEquals(0, counts[1], "Unavailable heap walking must preserve truncation");
    }

    /** Compares the captured application chain with the independently confirmed JVM chain. */
    private void assertRecoveredCallers(String cstack, boolean nested) {
        assertTrue(profiler.getDebugCounters().getOrDefault("walkvm_cont_barrier_hit", 0L) > 0,
                "The workload must encounter a continuation return barrier");

        String event = cpuProfiling ? "datadog.ExecutionSample" : "datadog.MethodSample";
        int[] counts = reduceEvents(event, () -> new int[8], (count, sample) -> {
            JfrStackTrace trace = sample.getStackTrace();
            if (containsMethod(trace, "sampledLeaf")) {
                int recursiveCallers = 0;
                int nestedCallers = 0;
                boolean leafSeen = false;
                boolean outerSeen = false;
                for (JfrFrame frame : trace.frames()) {
                    if (!getClass().getName().equals(frame.className())) continue;
                    if ("sampledLeaf".equals(frame.methodName())) {
                        if (leafSeen) count[7]++;
                        leafSeen = true;
                    }
                    if ("nestedWorkload".equals(frame.methodName())) {
                        if (!leafSeen || recursiveCallers != 0 || outerSeen) count[4]++;
                        nestedCallers++;
                    }
                    if ("recursiveWorkload".equals(frame.methodName())) {
                        if (!leafSeen || outerSeen) count[4]++;
                        recursiveCallers++;
                    }
                    if ("outerWorkload".equals(frame.methodName())) outerSeen = true;
                }
                int expectedNested = nested ? 65 : 0;
                if (recursiveCallers > RECURSION_DEPTH + 1 || nestedCallers > expectedNested) count[7]++;
                // doYield's generated native wrapper can still have mode=JAVA.
                // Require full recovery at application execution; every other
                // sample must preserve order, avoid duplicates and flag omissions.
                JfrFrame top = trace.frames().get(0);
                boolean applicationJava = "JAVA".equals(sample.getEnumName("mode"))
                        && getClass().getName().equals(top.className())
                        && "sampledLeaf".equals(top.methodName());
                if (!applicationJava) {
                    if ((!outerSeen || recursiveCallers != RECURSION_DEPTH + 1
                            || nestedCallers != expectedNested) && !trace.isTruncated()) count[6]++;
                    return;
                }
                count[0]++;
                if (!outerSeen) count[1]++;
                if (recursiveCallers != RECURSION_DEPTH + 1) count[2]++;
                if (nestedCallers != expectedNested) count[3]++;
                if ("vm".equals(cstack) && trace.isTruncated()) count[5]++;
            }
        });
        assertTrue(counts[0] > 0, "No sample captured the leaf workload");
        assertEquals(0, counts[1], "Samples omitted the JVM-confirmed outer caller; recovered="
                + profiler.getDebugCounters().getOrDefault("walkvm_frozen_recovered", 0L)
                + ", failed=" + profiler.getDebugCounters().getOrDefault("walkvm_frozen_failed", 0L));
        assertEquals(0, counts[2], "Samples omitted or duplicated recursive application callers");
        assertEquals(0, counts[3], "Samples omitted or duplicated nested application callers");
        assertEquals(0, counts[4], "Application callers were recovered in the wrong order");
        assertEquals(0, counts[5], "Recovered VM stacks must be complete");
        assertEquals(0, counts[6], "Unsafe-state samples must acknowledge missing callers");
        assertEquals(0, counts[7], "Freezing/thawing samples must not duplicate heap and carrier frames");
        assertTrue(profiler.getDebugCounters().getOrDefault("walkvm_frozen_recovered", 0L) > 0,
                "No continuation boundary recovered its frozen callers");
    }

    private boolean usesConcurrentRelocation() {
        return ManagementFactory.getGarbageCollectorMXBeans().stream()
                .anyMatch(gc -> gc.getName().contains("ZGC") || gc.getName().contains("Shenandoah"));
    }

    private long collectionCount() {
        return ManagementFactory.getGarbageCollectorMXBeans().stream()
                .mapToLong(gc -> Math.max(0, gc.getCollectionCount())).sum();
    }

    /** A return barrier must retain carrier ancestry even while older Java callers remain frozen. */
    @TestTemplate
    @ValueSource(strings = {"vmx"})
    public void keepsCarrierFramesAfterPartialThaw() throws Exception {
        runWorkload(true, true);
        assertCarrierFramesAfterPartialThaw("recursiveWorkload");
    }

    /** Stack-passed arguments extend and align the continuation entry frame during thaw. */
    @TestTemplate
    @ValueSource(strings = {"vmx"})
    public void keepsCarrierFramesAfterPartialThawWithStackArguments() throws Exception {
        runWorkload(true, true, true);
        assertCarrierFramesAfterPartialThaw("recursiveWorkloadWithArguments");
    }

    /** Checks carrier ancestry even when heap walking has restored the outer callers. */
    private void assertCarrierFramesAfterPartialThaw(String workloadMethod) {
        assertTrue(profiler.getDebugCounters().getOrDefault("walkvm_cont_barrier_hit", 0L) > 0,
                "The workload must encounter a continuation return barrier");

        int[] counts = reduceEvents("datadog.MethodSample", () -> new int[2], (count, sample) -> {
            JfrStackTrace trace = sample.getStackTrace();
            if (!containsMethod(trace, workloadMethod)) return;
            for (JfrFrame frame : trace.frames()) {
                if ("java.util.concurrent.ForkJoinWorkerThread".equals(frame.className())
                        && "run".equals(frame.methodName())) count[0]++;
                if (frame.methodName() != null && frame.methodName().startsWith("break_cont_")) count[1]++;
            }
        });
        assertEquals(0, counts[1], "Carrier recovery rejected continuation frame pointers");
        assertTrue(counts[0] > 0, "No parked workload sample retained carrier ancestry");
    }

    /** The same parked workload on a platform thread keeps its application callers on the stack. */
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx"})
    public void keepsPlatformCallersComplete() throws Exception {
        runWorkload(false, true);
        assertCompleteCallers();
    }

    /** A never-parked virtual thread retains its callers in both VM walking modes. */
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx"})
    public void keepsNeverParkedVirtualThreadComplete() throws Exception {
        runWorkload(true, false);
        assertCompleteCallers();
    }

    /** Runs the same recursion on either kind of thread and verifies that its callers really exist. */
    private void runWorkload(boolean virtual, boolean park) throws Exception {
        runWorkload(virtual, park, false);
    }

    /** Selects recursive frames with either register-only or stack-passed arguments. */
    private void runWorkload(boolean virtual, boolean park, boolean stackArguments) throws Exception {
        waitForProfilerReady(2_000);
        FutureTask<Void> task = new FutureTask<>(() -> {
            outerWorkload(park, stackArguments);
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
        int nested = 0;
        boolean outer = false;
        for (StackTraceElement frame : logicalStack) {
            if (!getClass().getName().equals(frame.getClassName())) continue;
            if (frame.getMethodName().equals(stackArguments ? "recursiveWorkloadWithArguments" : "recursiveWorkload")) recursion++;
            if (frame.getMethodName().equals("nestedWorkload")) nested++;
            if (frame.getMethodName().equals("outerWorkload")) outer = true;
        }
        assertEquals(RECURSION_DEPTH + 1, recursion, "The JVM must preserve all recursive callers");
        assertEquals(growChunks ? 65 : 0, nested, "The JVM must preserve all nested callers");
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

    private void outerWorkload(boolean park, boolean stackArguments) {
        long deadline = System.nanoTime() + 2_000_000_000L;
        while (System.nanoTime() < deadline) {
            if (stackArguments) {
                recursiveWorkloadWithArguments(RECURSION_DEPTH, park, 1, 2, 3, 4, 5, 6, 7, 8, 9);
            } else {
                recursiveWorkload(RECURSION_DEPTH, park);
            }
        }
    }

    /** Work after the recursive call keeps callers alive; deep recursion exceeds partial-thaw sizes. */
    private void recursiveWorkload(int depth, boolean park) {
        if (depth > 0) {
            recursiveWorkload(depth - 1, park);
        } else if (growChunks) {
            if (park) LockSupport.parkNanos(500_000L);
            nestedWorkload(64, park);
        } else {
            sampledLeaf(park);
        }
        sink += depth;
    }

    /** Grows another stack segment while the earlier recursive callers remain frozen. */
    private void nestedWorkload(int depth, boolean park) {
        if (depth > 0) nestedWorkload(depth - 1, park);
        else sampledLeaf(park);
        sink += depth;
    }

    /** Identifies samples taken while all recursive callers are still live. */
    private void sampledLeaf(boolean park) {
        if (park) LockSupport.parkNanos(500_000L);
        if (logicalStack == null) logicalStack = Thread.currentThread().getStackTrace();
        long deadline = System.nanoTime() + 2_000_000L;
        long value = sink;
        while (System.nanoTime() < deadline) {
            if (nativeLeaf) {
                value ^= RemoteSymHelper.burnCpu(100_000, 2);
            } else {
                // Keep the interrupted PC in Java rather than nanoTime's native implementation.
                for (int i = 0; i < 16_384; i++) value = (value ^ i) * 0x5deece66dL + 11;
            }
            sink = value;
        }
    }

    /** Keeps stack-passed arguments live across the recursive call and the park/remount cycle. */
    private void recursiveWorkloadWithArguments(int depth, boolean park,
            long a, long b, long c, long d, long e, long f, long g, long h, long i) {
        if (depth > 0) {
            recursiveWorkloadWithArguments(depth - 1, park, a, b, c, d, e, f, g, h, i);
        } else {
            if (park) LockSupport.parkNanos(500_000L);
            if (logicalStack == null) logicalStack = Thread.currentThread().getStackTrace();
            long deadline = System.nanoTime() + 2_000_000L;
            while (System.nanoTime() < deadline) sink ^= System.nanoTime();
        }
        sink += depth + a + b + c + d + e + f + g + h + i;
    }
}
