/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

import com.datadoghq.profiler.JavaProfiler;

import java.io.File;
import java.lang.reflect.Method;
import java.net.URL;
import java.net.URLClassLoader;
import java.nio.file.Paths;

/**
 * Synthetic workload driver for the memory-usage check, run with the profiler
 * attached via {@code -agentpath}.
 *
 * <p>Every run has two phases. A completion-bounded load phase (loading the
 * classes precompiled by {@link GenSources}, or starting threads) ends with a
 * {@code MEMCHECK_LOADED} marker on stdout; a time-bounded steady-state phase
 * then runs for the requested duration. With {@code -Dmemcheck.dumpAfterMs=N}
 * the recording is rotated once, N ms into the steady state, and
 * {@code MEMCHECK_DUMP_END} is printed afterwards. A harness samples NMT and
 * RSS relative to these markers rather than to launch, since the profiler
 * slows down class loading and a launch-relative sample can catch runs at
 * different lifecycle stages.
 *
 * <p>Modes: {@code threads N}, {@code traces N}, {@code classesM N M},
 * {@code allocs N}. {@code -Dmemcheck.noProfiler=true} runs the same workload
 * without touching the profiler API, as the no-profiler control.
 *
 * <p>Pass the agent's library path via {@code -Dmemcheck.libpath=...}, matching
 * the {@code -agentpath} argument, so {@link JavaProfiler#getInstance(String, String)}
 * attaches to the running agent instead of loading a second copy.
 */
public class MemCheckMain {

    public static void main(String[] args) throws Exception {
        String mode = args[0];
        int n = Integer.parseInt(args[1]);
        long durationMs = Long.parseLong(args[2]);
        File genDir = args.length > 3 ? new File(args[3]) : null;

        JavaProfiler profiler = null;
        if (!Boolean.getBoolean("memcheck.noProfiler")) {
            String libPath = System.getProperty("memcheck.libpath");
            if (libPath == null) {
                throw new IllegalStateException("pass -Dmemcheck.libpath=<path to the already-loaded agent library>");
            }
            profiler = JavaProfiler.getInstance(libPath, System.getProperty("java.io.tmpdir"));
            profiler.addThread();
        }

        Runnable steadyState;
        switch (mode) {
            case "threads": steadyState = loadThreads(n, profiler); break;
            case "traces": steadyState = loadTraces(n, genDir); break;
            case "classesM": steadyState = loadClassesM(n, Integer.parseInt(args[4]), genDir); break;
            case "allocs": steadyState = loadAllocs(n, genDir); break;
            default: throw new IllegalArgumentException(mode);
        }

        System.out.println("MEMCHECK_LOADED " + System.currentTimeMillis());
        System.out.flush();
        startDumper(profiler);
        runFor(durationMs, steadyState);
        // The agent was attached via -agentpath; its VMDeath hook flushes the
        // final JFR chunk when the JVM exits normally below.
    }

    /**
     * Rotates the recording once, {@code memcheck.dumpAfterMs} into the steady
     * state. The constant pools are serialized (and the dictionaries and method
     * map grown) only when a chunk is finished, so without a rotation a single
     * recording would flush only at exit, where nothing can sample it anymore.
     */
    private static void startDumper(JavaProfiler profiler) {
        String dumpAfter = System.getProperty("memcheck.dumpAfterMs");
        if (profiler == null || dumpAfter == null) {
            if (dumpAfter != null) {
                // Keep the harness's timing identical in the no-profiler arm.
                markerAfter(Long.parseLong(dumpAfter), null);
            }
            return;
        }
        String dumpPath = System.getProperty("memcheck.dumpPath",
                System.getProperty("java.io.tmpdir") + "/memcheck-middump.jfr");
        markerAfter(Long.parseLong(dumpAfter), () -> profiler.dump(Paths.get(dumpPath)));
    }

    private static void markerAfter(long delayMs, Runnable action) {
        Thread t = new Thread(() -> {
            try {
                Thread.sleep(delayMs);
                if (action != null) {
                    action.run();
                }
                System.out.println("MEMCHECK_DUMP_END " + System.currentTimeMillis());
            } catch (Throwable e) {
                System.out.println("MEMCHECK_DUMP_FAILED " + e);
            }
            System.out.flush();
        }, "memcheck-dumper");
        t.setDaemon(true);
        t.start();
    }

    private interface Step {
        long run(long i) throws Exception;
    }

    private static Runnable loop(int n, Step step) {
        return () -> {
            long sink = 0;
            try {
                for (int i = 0; i < n; i++) {
                    sink += step.run(i);
                }
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
            if (sink == Long.MIN_VALUE) {
                throw new AssertionError();
            }
        };
    }

    private static void runFor(long durationMs, Runnable cycle) {
        long deadline = System.currentTimeMillis() + durationMs;
        while (System.currentTimeMillis() < deadline) {
            cycle.run();
        }
    }

    /**
     * N registered threads that alternate short bursts of CPU work with sleeps.
     * The wall-clock engine only samples explicitly registered threads, so each
     * one calls {@link JavaProfiler#addThread()}.
     */
    private static Runnable loadThreads(int n, JavaProfiler profiler) {
        for (int i = 0; i < n; i++) {
            Thread t = new Thread(() -> {
                if (profiler != null) {
                    profiler.addThread();
                }
                double sink = 0;
                // Daemon threads: they spin until the JVM exits.
                while (true) {
                    for (int j = 0; j < 5000; j++) sink += Math.sqrt(j);
                    try { Thread.sleep(2); } catch (InterruptedException ignored) {}
                    if (Double.isNaN(sink)) throw new AssertionError();
                }
            }, "memcheck-thread-" + i);
            t.setDaemon(true);
            t.start();
        }
        return () -> {
            try { Thread.sleep(100); } catch (InterruptedException ignored) {}
        };
    }

    /** One class with N static methods: N distinct call-trace shapes, one class. */
    private static Runnable loadTraces(int n, File genDir) throws Exception {
        Class<?> c = Class.forName("GenTraces", true, loader(genDir));
        Method[] methods = new Method[n];
        for (int i = 0; i < n; i++) methods[i] = c.getMethod("m" + i, long.class);
        return loop(n, i -> (long) methods[(int) i].invoke(null, i));
    }

    /**
     * N classes with M methods each, all invoked every cycle, so classes and
     * methods touched move independently (N and N*M respectively).
     */
    private static Runnable loadClassesM(int n, int methodsPerClass, File genDir) throws Exception {
        URLClassLoader loader = loader(genDir);
        Method[] methods = new Method[n * methodsPerClass];
        for (int i = 0; i < n; i++) {
            Class<?> c = Class.forName("GenClassM" + i, true, loader);
            for (int m = 0; m < methodsPerClass; m++) {
                methods[i * methodsPerClass + m] = c.getMethod("m" + m, long.class);
            }
        }
        return loop(methods.length, i -> (long) methods[(int) i].invoke(null, i));
    }

    /** N distinct short-lived object shapes, allocated and discarded every cycle. */
    private static Runnable loadAllocs(int n, File genDir) throws Exception {
        URLClassLoader loader = loader(genDir);
        Method[] factories = new Method[n];
        for (int i = 0; i < n; i++) {
            factories[i] = Class.forName("GenAlloc" + i, true, loader).getMethod("alloc", long.class);
        }
        return loop(n, i -> factories[(int) i].invoke(null, i) == null ? 1 : 0);
    }

    private static URLClassLoader loader(File genDir) throws Exception {
        // The loader is reachable from the returned Method objects, so the
        // generated classes stay loaded for the whole run.
        return new URLClassLoader(new URL[]{genDir.toURI().toURL()}, MemCheckMain.class.getClassLoader());
    }
}
