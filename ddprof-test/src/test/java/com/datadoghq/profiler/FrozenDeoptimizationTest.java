/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.FutureTask;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.LockSupport;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/** Exercises inline scope recovery after a mounted compiled frame is deoptimized and frozen. */
public class FrozenDeoptimizationTest {
    private static final String WORKLOAD = Workload.class.getName();
    private static volatile boolean entered;
    private static volatile boolean released;
    private static volatile boolean samplingReady;
    private static volatile boolean collecting;
    private static volatile long sink;
    private static StackTraceElement[] logicalStack;

    /** Both VM modes must restore inline callers; the control never invalidates the nmethod. */
    @ParameterizedTest
    @ValueSource(strings = {"control:vm", "deopt:vm", "deopt:vmx"})
    void recoversDeoptimizedInlineCallers(String scenario) throws Exception {
        assumeTrue(Platform.isJavaVersionAtLeast(21) && !Platform.isJavaVersionAtLeast(28)
                && !Platform.isJ9() && !Platform.isZing());
        assumeTrue(!Platform.isMusl() || Platform.isAarch64());
        Path directory = Files.createTempDirectory("frozen-deoptimization-");
        Path recording = directory.resolve("samples.jfr");
        Path compilation = directory.resolve("compilation.xml");
        Path output = directory.resolve("child.log");
        String[] options = scenario.split(":");
        String javaHome = System.getenv("JAVA_TEST_HOME");
        if (javaHome == null) javaHome = System.getProperty("java.home");
        List<String> command = new ArrayList<>(Arrays.asList(
                Paths.get(javaHome, "bin", "java").toString(),
                "-Xms128m", "-Xmx512m", "-XX:+UseG1GC", "-XX:+UnlockDiagnosticVMOptions",
                "-XX:+DebugNonSafepoints", "-XX:-TieredCompilation", "-XX:-UseTypeProfile",
                "-Xbatch", "-XX:CompileThreshold=1000", "-XX:+LogCompilation",
                "-XX:LogFile=" + compilation,
                "-XX:CompileCommand=compileonly," + WORKLOAD + "::targetRoot",
                "-XX:CompileCommand=dontinline," + WORKLOAD + "::targetRoot",
                "-XX:CompileCommand=dontinline," + WORKLOAD + "::recurse",
                "-XX:CompileCommand=dontinline," + WORKLOAD + "::leaf",
                "-XX:CompileCommand=inline," + First.class.getName() + "::inlinedFirst",
                "-XX:CompileCommand=inline," + First.class.getName() + "::inlinedSecond",
                "-cp", System.getProperty("java.class.path"), getClass().getName(), options[0],
                LibraryLoader.resolveLibraryPath(System.getProperty("java.io.tmpdir")).toString(),
                recording.toString(), options[1]));
        Process child = new ProcessBuilder(command).redirectErrorStream(true)
                .redirectOutput(output.toFile()).start();
        boolean passed = false;
        try {
            assertTrue(child.waitFor(60, TimeUnit.SECONDS), "Child timed out: " + output);
            assertEquals(0, child.exitValue(), "Child failed: " + output);
            String compilerLog = new String(Files.readAllBytes(compilation), StandardCharsets.UTF_8);
            Matcher compiled = Pattern.compile("<nmethod [^>]*compile_id='(\\d+)'[^>]*compiler='c2'[^>]*method='"
                    + Pattern.quote(WORKLOAD) + " targetRoot ").matcher(compilerLog);
            assertTrue(compiled.find(), "The caller was never C2 compiled: " + compilation);
            Matcher task = Pattern.compile("<task compile_id='" + compiled.group(1)
                    + "'[^>]*>(.*?)</task>", Pattern.DOTALL).matcher(compilerLog);
            assertTrue(task.find(), "No compilation task for the target caller");
            assertTrue(task.group(1).split("<inline_success", -1).length >= 3,
                    "The target caller did not inline both methods");
            boolean invalidated = Pattern.compile("<make_not_entrant [^>]*compile_id='"
                    + compiled.group(1) + "'").matcher(compilerLog).find();
            assertEquals(options[0].equals("deopt"), invalidated,
                    "The compiled caller must be invalidated only in the deoptimization scenario");
            if (invalidated) assertTrue(compilerLog.contains("<dependency_failed"));
            assertCallers(recording, options[1]);
            passed = true;
        } finally {
            if (child.isAlive()) child.destroyForcibly().waitFor();
            if (passed && !Boolean.getBoolean("ddprof_test.keep_jfrs")) {
                Files.deleteIfExists(recording);
                Files.deleteIfExists(compilation);
                Files.deleteIfExists(output);
                Files.delete(directory);
            } else {
                System.out.println("Frozen deoptimization artifacts: " + directory);
            }
        }
    }

    /** Requires restoration, correct ordering and truthful completeness for sampled Java bodies. */
    private static void assertCallers(Path recording, String cstack) throws Exception {
        List<String> expected = new ArrayList<>();
        expected.add("leaf");
        for (int i = 0; i < 129; i++) expected.add("recurse");
        expected.addAll(Arrays.asList("inlinedSecond", "inlinedFirst", "targetRoot"));
        int[] counts = JfrEvents.reduce(recording, "datadog.MethodSample"::equals,
                () -> new int[5], (count, event) -> {
            JfrStackTrace trace = event.getStackTrace();
            if (trace.isEmpty() || !"JAVA".equals(event.getEnumName("mode"))) return;
            JfrFrame top = trace.frames().get(0);
            if (!WORKLOAD.equals(top.className()) || !"leaf".equals(top.methodName())) return;
            count[0]++;
            List<String> callers = new ArrayList<>();
            for (JfrFrame frame : trace.frames()) {
                if (WORKLOAD.equals(frame.className()) || First.class.getName().equals(frame.className())) {
                    callers.add(frame.methodName());
                }
            }
            boolean full = expected.equals(callers);
            if (full) count[1]++;
            else if (!trace.isTruncated()) count[3]++;
            // Seeing targetRoot proves the walker reached the physical compiled frame.
            if (callers.contains("targetRoot") && !full) count[2]++;
            if (full && cstack.equals("vm") && trace.isTruncated()) count[4]++;
        });
        System.out.println("eligible=" + counts[0] + " restored=" + counts[1]
                + " missingInline=" + counts[2] + " falselyComplete=" + counts[3]);
        assertTrue(counts[0] > 0, "No Java-body samples exercised the workload");
        assertEquals(0, counts[2], "Compiled frames lost their inline callers");
        assertEquals(0, counts[3], "Incomplete stacks claimed completeness");
        assertTrue(counts[1] > 0, "No sample restored the complete inline chain");
        assertEquals(0, counts[4], "Restored VM stacks were marked truncated");
    }

    /** Child entry point: invalidate while mounted, then freeze before sampling the leaf. */
    public static void main(String[] args) throws Exception {
        for (int i = 0; i < 20_000; i++) sink = Workload.targetRoot(0, false);
        JavaProfiler profiler = JavaProfiler.getInstance(args[1], null);
        FutureTask<Long> task = new FutureTask<>(() -> Workload.targetRoot(128, true));
        Thread worker = (Thread) Thread.class.getMethod("startVirtualThread", Runnable.class)
                .invoke(null, task);
        long deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(10);
        while ((!entered || worker.getState() != Thread.State.RUNNABLE) && System.nanoTime() < deadline) {
            Thread.sleep(1);
        }
        if (!entered || worker.getState() != Thread.State.RUNNABLE) throw new AssertionError("Not mounted");
        try {
            // Disabling type profiles makes C2 depend on the unique interface implementor.
            // Resolving Second invalidates targetRoot without replacing any method bytecode.
            if (args[0].equals("deopt")) Class.forName(FrozenDeoptimizationTest.class.getName() + "$Second");
            released = true;
            deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(10);
            while (!samplingReady && System.nanoTime() < deadline) Thread.sleep(1);
            if (!samplingReady) throw new AssertionError("Worker did not remount");
            // Start only after the park: pre-park samples exercise the carrier walker instead.
            profiler.execute("start,jfr,wall=1ms,walltpt=64,filter=,jstackdepth=512,cstack="
                    + args[3] + ",file=" + args[2]);
        } finally {
            released = true;
            collecting = true;
        }
        worker.join(15_000);
        if (worker.isAlive()) throw new AssertionError("Worker did not finish");
        sink = task.get();
        profiler.stop();
        List<String> logical = new ArrayList<>();
        for (StackTraceElement frame : logicalStack) {
            if (WORKLOAD.equals(frame.getClassName()) || First.class.getName().equals(frame.getClassName())) {
                logical.add(frame.getMethodName());
            }
        }
        if (logical.size() != 133 || !logical.contains("inlinedFirst") || !logical.contains("inlinedSecond")) {
            throw new AssertionError("JVM logical callers were not preserved: " + logical);
        }
        if (profiler.getDebugCounters().getOrDefault("walkvm_frozen_recovered", 0L) <= 0) {
            throw new AssertionError("No frozen callers were recovered");
        }
    }

    /** Interface dispatch gives the compiled caller a class hierarchy dependency. */
    public interface Strategy {
        /** Invokes the recursive workload through two inline scopes. */
        long inlinedFirst(int depth, boolean active);
    }

    /** The sole loaded implementor during C2 compilation. */
    public static class First implements Strategy {
        @Override
        public long inlinedFirst(int depth, boolean active) {
            return inlinedSecond(depth, active) + 13;
        }

        private long inlinedSecond(int depth, boolean active) {
            return Workload.recurse(depth, active) + 17;
        }
    }

    /** Loaded only when the mounted caller must be invalidated. */
    public static class Second implements Strategy {
        @Override
        public long inlinedFirst(int depth, boolean active) {
            return 0;
        }
    }

    /** Only targetRoot is compiled; the deep interpreted chain keeps it frozen after remounting. */
    public static class Workload {
        private static volatile Strategy strategy = new First();

        static long targetRoot(int depth, boolean active) {
            return strategy.inlinedFirst(depth, active) + 11;
        }

        static long recurse(int depth, boolean active) {
            long result = depth > 0 ? recurse(depth - 1, active) : leaf(active);
            return result + depth;
        }

        /** A real park after invalidation freezes the still-live compiled caller. */
        static long leaf(boolean active) {
            if (!active) return 19;
            entered = true;
            while (!released) sink++;
            LockSupport.parkNanos(500_000L);
            logicalStack = Thread.currentThread().getStackTrace();
            samplingReady = true;
            while (!collecting) sink++;
            long deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(3);
            long value = 23;
            while (System.nanoTime() < deadline) {
                for (int i = 0; i < 4096; i++) value = (value ^ i) * 0x5deece66dL + 11;
                sink = value;
            }
            return value;
        }
    }
}
