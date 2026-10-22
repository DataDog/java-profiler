/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.JfrFrame;
import com.datadoghq.profiler.JfrStackTrace;
import com.datadoghq.profiler.Platform;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.concurrent.FutureTask;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.LockSupport;
import java.util.function.BiConsumer;
import java.util.stream.Stream;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/** Checks heap-chunk ownership in the Java intervals before and after a nested native entry. */
public class NestedContinuationTransitionTest {
    private static volatile long sink;
    private static Object child;
    private static Object scope;
    private static Method run;
    private static Method yield;

    /** Suspended child frames must never be spliced into a partially thawed parent's stack. */
    @ParameterizedTest
    @ValueSource(strings = {"vm", "vmx"})
    public void rejectsSuspendedChildChunks(String mode) throws Exception {
        assumeTrue(Platform.isJavaVersionAtLeast(21) && !Platform.isJ9() && !Platform.isZing());
        assumeTrue(!(Boolean.getBoolean("ddprof_test.ci") && Platform.isMusl() && !Platform.isAarch64()));
        Path directory = Files.createTempDirectory("nested-continuation-transition-");
        Path recording = directory.resolve("transition.jfr");
        Path log = directory.resolve("child.log");
        Path patch = directory.resolve("java-base-patch");
        ContinuationTransitionSupport.writePatch(patch);

        List<String> command = Arrays.asList(
                Paths.get(System.getProperty("java.home"), "bin", "java").toString(),
                "--add-opens=java.base/jdk.internal.vm=ALL-UNNAMED",
                "--add-opens=java.base/java.lang=ALL-UNNAMED",
                "-Xmx256m", "-XX:+UseG1GC", "-XX:+UnlockDiagnosticVMOptions", "-XX:+DebugNonSafepoints",
                "-XX:CompileCommand=dontinline,*NestedContinuationTransitionTest.*",
                "--patch-module=java.base=" + patch, "-cp", System.getProperty("java.class.path"),
                getClass().getName(), directory.toString(),
                recording.toString(), mode);
        boolean verified = false;
        Process process = new ProcessBuilder(command).redirectErrorStream(true).redirectOutput(log.toFile()).start();
        try {
            assertTrue(process.waitFor(60, TimeUnit.SECONDS), "Child timed out; see " + log);
            assertEquals(0, process.exitValue(), "Child failed; see " + log);
            assertTransitions(recording);
            verified = true;
            System.out.println("Nested transition " + mode + " recording: " + recording);
        } finally {
            if (process.isAlive()) {
                process.destroyForcibly();
                process.waitFor(5, TimeUnit.SECONDS);
            }
            if (verified && !Boolean.getBoolean("ddprof_test.keep_jfrs")) {
                try (Stream<Path> files = Files.walk(directory)) {
                    for (Path file : files.sorted(Comparator.reverseOrder()).toArray(Path[]::new)) Files.delete(file);
                }
            }
        }
    }

    /** Checks both engines in both intervals and distinguishes genuine parent frames from child chunks. */
    private void assertTransitions(Path recording) throws Exception {
        int[][] samples = new int[2][2];
        int[][] missingParent = new int[2][2];
        int foreign = 0;
        int falseComplete = 0;
        for (int engine = 0; engine < 2; engine++) {
            String event = engine == 0 ? "datadog.ExecutionSample" : "datadog.MethodSample";
            for (JfrEvent sample : JfrEvents.load(recording, event)) {
                JfrStackTrace trace = sample.getStackTrace();
                if (trace == null) continue;
                int phase = contains(trace, "beforeChildEntry") ? 0 : contains(trace, "afterChildExit") ? 1 : -1;
                if (phase < 0) continue;
                samples[engine][phase]++;
                if (contains(trace, "suspendedChildRoot") || contains(trace, "suspendedChildCallers")) foreign++;
                if (!contains(trace, "parentRoot")) {
                    missingParent[engine][phase]++;
                    if (!trace.isTruncated()) falseComplete++;
                }
            }
        }
        for (int[] engine : samples) {
            assertTrue(engine[0] > 0, "The child-publication interval was not sampled");
            assertTrue(engine[1] > 0, "The child-return interval was not sampled");
        }
        for (int[] engine : missingParent) {
            assertTrue(engine[0] > 0 && engine[1] > 0,
                    "The parent must retain frozen callers during both sampled transitions");
        }
        assertEquals(0, foreign, "Parent samples contain suspended child frames: " + recording);
        assertEquals(0, falseComplete, "Missing parent callers were reported complete: " + recording);
    }

    /** Matches an application method without relying on hidden-frame rendering. */
    private static boolean contains(JfrStackTrace trace, String method) {
        for (JfrFrame frame : trace.frames()) {
            if (NestedContinuationTransitionTest.class.getName().equals(frame.className())
                    && method.equals(frame.methodName())) return true;
        }
        return false;
    }

    /** Runs in isolation because the patch extends intervals inside a java.base class. */
    public static void main(String[] args) throws Exception {
        Class<?> continuation = Class.forName("jdk.internal.vm.Continuation");
        Class<?> scopeType = Class.forName("jdk.internal.vm.ContinuationScope");
        scope = scopeType.getConstructor(String.class).newInstance("nested-profiler-regression");
        run = continuation.getMethod("run");
        yield = continuation.getMethod("yield", scopeType);
        child = continuation.getConstructor(scopeType, Runnable.class)
                .newInstance(scope, (Runnable) NestedContinuationTransitionTest::suspendedChildRoot);
        run.invoke(child); // Leave distinct child callers frozen before mounting the parent.

        Field parent = continuation.getDeclaredField("parent");
        parent.setAccessible(true);
        Field tail = continuation.getDeclaredField("tail");
        tail.setAccessible(true);
        Field carrierCont = Thread.class.getDeclaredField("cont");
        carrierCont.setAccessible(true);
        Method currentCarrier = Thread.class.getDeclaredMethod("currentCarrierThread");
        currentCarrier.setAccessible(true);
        int[] phases = {0, 0};
        BiConsumer<Object, Integer> hook = (value, phase) -> {
            if (value != child) return;
            try {
                if (parent.get(child) == null || tail.get(child) == null
                        || carrierCont.get(currentCarrier.invoke(null)) != child) {
                    throw new AssertionError("The real transition must publish a suspended child over its parent");
                }
                phases[phase - 1]++;
                if (phase == 1) beforeChildEntry();
                else afterChildExit();
            } catch (ReflectiveOperationException e) {
                throw new AssertionError(e);
            }
        };
        JavaProfiler profiler = JavaProfiler.getInstance(null, args[0]);
        profiler.execute("start,cpu=1ms,event=itimer,wall=1ms,walltpt=64,filter=,jstackdepth=256,cstack="
                + args[2] + ",file=" + args[1]);
        System.getProperties().put(ContinuationTransitionSupport.HOOK, hook);
        try {
            FutureTask<Void> task = new FutureTask<>(() -> {
                parentRoot();
                return null;
            });
            Thread worker = (Thread) Thread.class.getMethod("startVirtualThread", Runnable.class).invoke(null, task);
            worker.join(30_000);
            if (worker.isAlive()) throw new AssertionError("Nested continuation workload did not finish");
            task.get();
        } finally {
            System.getProperties().remove(ContinuationTransitionSupport.HOOK);
            profiler.stop();
        }
        if (phases[0] != 1 || phases[1] != 1) throw new AssertionError("Both real transition hooks must run once");
        if (profiler.getDebugCounters().getOrDefault("walkvm_cont_barrier_hit", 0L) == 0) {
            throw new AssertionError("The parent must retain frozen callers at a return barrier");
        }
    }

    private static void parentRoot() throws Exception {
        parentCallers(128);
    }

    /** Forces partial thaw before entering the already suspended nested continuation. */
    private static void parentCallers(int depth) throws Exception {
        if (depth > 0) parentCallers(depth - 1);
        else {
            LockSupport.parkNanos(1_000_000L);
            run.invoke(child);
        }
        sink += depth;
    }

    private static void suspendedChildRoot() {
        suspendedChildCallers(64);
    }

    /** Yields twice so both transition intervals have nonempty child chunks available. */
    private static void suspendedChildCallers(int depth) {
        if (depth > 0) suspendedChildCallers(depth - 1);
        else {
            try {
                yield.invoke(null, scope);
                yield.invoke(null, scope);
            } catch (ReflectiveOperationException e) {
                throw new AssertionError(e);
            }
        }
        sink += depth;
    }

    private static void beforeChildEntry() {
        spin();
    }

    private static void afterChildExit() {
        spin();
    }

    /** Keeps the real Java transition open long enough for both asynchronous engines to sample it. */
    private static void spin() {
        long deadline = System.nanoTime() + 2_000_000_000L;
        long sum = 1;
        while (System.nanoTime() < deadline) {
            for (int i = 0; i < 1000; i++) sum = sum * 1664525 + 1013904223;
            sink = sum;
        }
    }
}
