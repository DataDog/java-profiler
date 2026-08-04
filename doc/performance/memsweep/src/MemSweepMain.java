import com.datadoghq.profiler.JavaProfiler;

import java.io.File;
import java.lang.reflect.Method;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CountDownLatch;

/**
 * Standalone synthetic-workload driver for the java-profiler native-memory
 * sweep, run with the agent attached via -agentpath. Modes: threads, traces,
 * classes, classesM, allocs. traces/classes/classesM/allocs load classes
 * precompiled by GenSources+javac ahead of time (outside this process) so
 * the profiled JVM never loads the compiler's own classes.
 *
 * Every sampled thread must call JavaProfiler.addThread() -- the wall-clock
 * engine here only samples explicitly registered threads, it does not
 * auto-register new threads via a JVMTI ThreadStart hook. Confirmed on both
 * macOS and Linux; very likely intentional fork behavior rather than a
 * platform-specific gap (see memory-sweep-results-linux.md).
 *
 * Pass the already-loaded agent's library path via -Dmemsweep.libpath=...
 * (must match the -agentpath argument) so JavaProfiler.getInstance() attaches
 * to the running agent instead of trying to load a second copy.
 */
public class MemSweepMain {

    public static void main(String[] args) throws Exception {
        String mode = args[0];
        int n = Integer.parseInt(args[1]);
        long durationMs = Long.parseLong(args[2]);
        File genDir = args.length > 3 ? new File(args[3]) : null;

        String libPath = System.getProperty("memsweep.libpath");
        if (libPath == null) {
            throw new IllegalStateException("pass -Dmemsweep.libpath=<path to the already-loaded agent .so/.dylib>");
        }
        String scratchDir = System.getProperty("java.io.tmpdir");
        JavaProfiler profiler = JavaProfiler.getInstance(libPath, scratchDir);
        profiler.addThread();

        switch (mode) {
            case "threads": runThreads(n, durationMs, profiler); break;
            case "traces": runTraces(n, durationMs, genDir); break;
            case "classes": runClasses(n, durationMs, genDir); break;
            case "classesM": runClassesM(n, Integer.parseInt(args[4]), durationMs, genDir); break;
            case "allocs": runAllocs(n, durationMs, genDir); break;
            default: throw new IllegalArgumentException(mode);
        }
        // Agent was attached via -agentpath; the VMDeath shutdown hook
        // flushes the final JFR chunk when the JVM exits normally below.
    }

    private static void runThreads(int n, long durationMs, JavaProfiler profiler) throws InterruptedException {
        long deadline = System.currentTimeMillis() + durationMs;
        List<Thread> threads = new ArrayList<>();
        CountDownLatch start = new CountDownLatch(1);
        for (int i = 0; i < n; i++) {
            Thread t = new Thread(() -> {
                profiler.addThread();
                try { start.await(); } catch (InterruptedException ignored) {}
                double sink = 0;
                while (System.currentTimeMillis() < deadline) {
                    for (int j = 0; j < 5000; j++) sink += Math.sqrt(j);
                    try { Thread.sleep(2); } catch (InterruptedException ignored) {}
                }
                if (Double.isNaN(sink)) throw new AssertionError();
            }, "sweep-thread-" + i);
            t.setDaemon(true);
            threads.add(t);
            t.start();
        }
        start.countDown();
        for (Thread t : threads) t.join();
    }

    // Single precompiled class, N distinct static methods -> N distinct
    // call-trace shapes, class/method-owner count stays at 1.
    private static void runTraces(int n, long durationMs, File genDir) throws Exception {
        URLClassLoader loader = new URLClassLoader(new URL[]{genDir.toURI().toURL()}, MemSweepMain.class.getClassLoader());
        Class<?> genClass = Class.forName("GenTraces", true, loader);
        Method[] methods = new Method[n];
        for (int i = 0; i < n; i++) methods[i] = genClass.getMethod("m" + i, long.class);

        long deadline = System.currentTimeMillis() + durationMs;
        long sink = 0;
        while (System.currentTimeMillis() < deadline) {
            for (int i = 0; i < n; i++) sink += (long) methods[i].invoke(null, (long) i);
        }
        if (sink == Long.MIN_VALUE) throw new AssertionError();
    }

    // N distinct precompiled classes, each with one method -> N distinct
    // classes/methods, call-trace shape count stays low (same call site).
    private static void runClasses(int n, long durationMs, File genDir) throws Exception {
        URLClassLoader loader = new URLClassLoader(new URL[]{genDir.toURI().toURL()}, MemSweepMain.class.getClassLoader());
        List<Class<?>> classes = new ArrayList<>();
        List<Method> methods = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            Class<?> c = Class.forName("GenClass" + i, true, loader);
            classes.add(c); // keep alive so it can't be unloaded mid-sweep
            methods.add(c.getMethod("compute", long.class));
        }

        long deadline = System.currentTimeMillis() + durationMs;
        long sink = 0;
        while (System.currentTimeMillis() < deadline) {
            for (int i = 0; i < n; i++) sink += (long) methods.get(i).invoke(null, (long) i);
        }
        if (sink == Long.MIN_VALUE) throw new AssertionError();
        if (classes.size() != n) throw new AssertionError();
    }

    // N classes, each with M methods, ALL of which get invoked every cycle --
    // unlike `classes` above, this can distinguish "overhead tracks distinct
    // classes touched" from "overhead tracks distinct methods touched", since
    // classes-touched and methods-touched no longer move together.
    private static void runClassesM(int n, int methodsPerClass, long durationMs, File genDir) throws Exception {
        URLClassLoader loader = new URLClassLoader(new URL[]{genDir.toURI().toURL()}, MemSweepMain.class.getClassLoader());
        List<Class<?>> classes = new ArrayList<>();
        List<Method[]> methodsByClass = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            Class<?> c = Class.forName("GenClassM" + i, true, loader);
            classes.add(c); // keep alive so it can't be unloaded mid-sweep
            Method[] ms = new Method[methodsPerClass];
            for (int m = 0; m < methodsPerClass; m++) ms[m] = c.getMethod("m" + m, long.class);
            methodsByClass.add(ms);
        }

        long deadline = System.currentTimeMillis() + durationMs;
        long sink = 0;
        while (System.currentTimeMillis() < deadline) {
            for (int i = 0; i < n; i++) {
                Method[] ms = methodsByClass.get(i);
                for (int m = 0; m < ms.length; m++) sink += (long) ms[m].invoke(null, (long) i);
            }
        }
        if (sink == Long.MIN_VALUE) throw new AssertionError();
        if (classes.size() != n) throw new AssertionError();
    }

    // N distinct short-lived object shapes, allocated and immediately discarded
    // in a cycle -- isolates allocation-sampling-driven calltrace/dictionary
    // growth (memory=<interval>:a engine) from wall-clock reflection calls.
    private static void runAllocs(int n, long durationMs, File genDir) throws Exception {
        URLClassLoader loader = new URLClassLoader(new URL[]{genDir.toURI().toURL()}, MemSweepMain.class.getClassLoader());
        List<Method> factories = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            Class<?> c = Class.forName("GenAlloc" + i, true, loader);
            factories.add(c.getMethod("alloc", long.class));
        }

        long deadline = System.currentTimeMillis() + durationMs;
        Object sink = null;
        while (System.currentTimeMillis() < deadline) {
            for (int i = 0; i < n; i++) sink = factories.get(i).invoke(null, (long) i);
        }
        if (sink == null) throw new AssertionError();
    }
}
