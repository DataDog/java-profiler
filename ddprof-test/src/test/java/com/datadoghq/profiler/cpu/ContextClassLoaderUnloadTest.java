/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.JfrFrame;
import com.datadoghq.profiler.JfrStackTrace;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.api.Timeout;
import org.junit.jupiter.params.provider.ValueSource;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.lang.ref.WeakReference;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Runs 20 CPU-bound threads, each with its own context class loader that defines a private
 * copy of {@link LoaderLocalWorker}. Once every thread has exited, all 20 loaders (and so
 * their classes) must be unloaded. Whether the recording is written before the unload or
 * after it, every worker thread's stack traces must name its {@code LoaderLocalWorker}
 * frames and contain no {@code unknown} method.
 *
 * <p>The loaders are not the system class loader, so their classes take the jmethodID path
 * in every cstack mode.
 */
public class ContextClassLoaderUnloadTest extends CStackAwareAbstractProfilerTest {

    private static final String WORKER_CLASS = "com.datadoghq.profiler.cpu.LoaderLocalWorker";
    private static final String WORKER_SIMPLE_NAME = "LoaderLocalWorker";
    // Name the profiler gives a frame it could not resolve (flightRecorder.cpp).
    private static final String UNKNOWN_METHOD = "unknown";
    private static final String THREAD_PREFIX = "ccl-worker-";
    private static final int THREADS = 20;
    private static final long WORK_NANOS = TimeUnit.MILLISECONDS.toNanos(500);
    private static final long UNLOAD_TIMEOUT_MS = 15_000;

    public ContextClassLoaderUnloadTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms";
    }

    /**
     * Snapshot taken after the threads exit but while their loaders are still strongly held.
     * The loaders must then unload.
     */
    @RetryTest(3)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx", "fp", "dwarf"})
    @Timeout(60)
    public void namesWorkerFramesBeforeLoadersUnload(@CStack String cstack) throws Exception {
        Assumptions.assumeFalse(Platform.isJ9() || Platform.isZing());
        waitForProfilerReady(2000);

        List<ClassLoader> loaders = runWorkers(readClassBytes(WORKER_CLASS));

        Path snapshot = Files.createTempFile("ccl-unload-" + cstack + "-", ".jfr");
        try {
            dump(snapshot);
            WorkerStacks stacks = WorkerStacks.collect(JfrEvents.load(snapshot, "datadog.ExecutionSample"));
            System.out.println("[" + cstack + "] before unload: " + stacks);
            stacks.assertResolved();
        } finally {
            Files.deleteIfExists(snapshot);
        }

        awaitUnload(weakRefs(loaders));
    }

    /**
     * No dump until the loaders have unloaded, so every worker frame is resolved after its
     * class is gone.
     */
    @RetryTest(3)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx", "fp", "dwarf"})
    @Timeout(60)
    public void namesWorkerFramesAfterLoadersUnload(@CStack String cstack) throws Exception {
        Assumptions.assumeFalse(Platform.isJ9() || Platform.isZing());
        waitForProfilerReady(2000);

        List<ClassLoader> loaders = runWorkers(readClassBytes(WORKER_CLASS));
        awaitUnload(weakRefs(loaders));

        stopProfiler();

        WorkerStacks stacks = WorkerStacks.collect(verifyEvents("datadog.ExecutionSample"));
        System.out.println("[" + cstack + "] after unload: " + stacks);
        stacks.assertResolved();
        assertGCResolveCounters(cstack);
    }

    /**
     * The GCs awaitUnload() forced must have resolved the pending samples'
     * methods from GarbageCollectionStart. With -PenableSamplerPerf, every pass
     * must also have been timed. Skipped on builds without counters.
     */
    private void assertGCResolveCounters(String cstack) {
        Map<String, Long> counters = profiler.getDebugCounters();
        Assumptions.assumeTrue(counters.containsKey("gc_resolve_passes"), "Profiler built without counters");
        long passes = counters.get("gc_resolve_passes");
        long skipped = counters.getOrDefault("gc_resolve_skipped", 0L);
        long methods = counters.getOrDefault("gc_resolved_methods", 0L);
        System.out.println("[" + cstack + "] GC resolve: " + passes + " passes, " + skipped + " skipped, "
                + methods + " methods resolved");
        assertTrue(passes > 0, "No pending-method resolution ran at GC start");
        assertTrue(methods > 0, "No method was resolved at GC start");

        if (counters.containsKey("sampler_count.gc_resolve")) {
            long timed = counters.get("sampler_count.gc_resolve");
            long timeNs = counters.getOrDefault("sampler_ticks.gc_resolve", 0L);
            System.out.println("[" + cstack + "] GC resolve time: " + timeNs + " ns over " + timed + " GCs");
            assertEquals(passes + skipped, timed, "Every GC-start resolution attempt should be timed");
            assertTrue(timeNs > 0, "GC resolve time was not recorded");
        }
    }

    /** Swaps the caller's strong references for weak ones; clears {@code loaders}. */
    private static List<WeakReference<ClassLoader>> weakRefs(List<ClassLoader> loaders) {
        List<WeakReference<ClassLoader>> refs = new ArrayList<>();
        for (ClassLoader loader : loaders) {
            refs.add(new WeakReference<>(loader));
        }
        loaders.clear();
        return refs;
    }

    /** Per-sample frame checks over the worker threads' samples in one recording. */
    private static final class WorkerStacks {
        final Map<String, Integer> samplesPerThread = new TreeMap<>();
        final Map<String, Integer> threadsWithWorkerFrames = new TreeMap<>();
        final List<String> unknownStacks = new ArrayList<>();
        final List<String> unnamedStacks = new ArrayList<>();
        int samples;

        static WorkerStacks collect(JfrEvents events) {
            WorkerStacks result = new WorkerStacks();
            for (JfrEvent sample : events) {
                String thread = sample.getThreadName("eventThread");
                if (thread == null || !thread.startsWith(THREAD_PREFIX)) {
                    continue;
                }
                JfrStackTrace stackTrace = sample.getStackTrace();
                assertTrue(stackTrace != null && !stackTrace.isEmpty(),
                        "Worker sample on " + thread + " has no stack trace");
                result.samples++;
                result.samplesPerThread.merge(thread, 1, Integer::sum);
                boolean workerFrame = false;
                boolean unknownFrame = false;
                for (JfrFrame frame : stackTrace.frames()) {
                    String method = frame.methodName();
                    String className = frame.className();
                    if (UNKNOWN_METHOD.equals(method)) {
                        unknownFrame = true;
                    } else if (className != null && className.endsWith(WORKER_SIMPLE_NAME)) {
                        workerFrame = true;
                    }
                }
                if (unknownFrame && result.unknownStacks.size() < 3) {
                    result.unknownStacks.add(thread + ":\n" + sample.getStackTraceString());
                }
                if (workerFrame) {
                    result.threadsWithWorkerFrames.merge(thread, 1, Integer::sum);
                } else if (result.unnamedStacks.size() < 3) {
                    result.unnamedStacks.add(thread + ":\n" + sample.getStackTraceString());
                }
            }
            return result;
        }

        void assertResolved() {
            assertEquals(THREADS, samplesPerThread.size(),
                    "Expected CPU samples on all " + THREADS + " worker threads, got " + samplesPerThread.keySet());
            assertTrue(unknownStacks.isEmpty(),
                    "Worker stack traces contain " + UNKNOWN_METHOD + " frames, e.g.\n"
                            + String.join("\n---\n", unknownStacks));
            assertEquals(THREADS, threadsWithWorkerFrames.size(),
                    "Expected named " + WORKER_SIMPLE_NAME + " frames on all " + THREADS
                            + " worker threads, got " + threadsWithWorkerFrames.keySet()
                            + "; worker samples without them, e.g.\n" + String.join("\n---\n", unnamedStacks));
        }

        @Override
        public String toString() {
            return samples + " worker samples, named worker frames per thread " + threadsWithWorkerFrames
                    + ", stacks with " + UNKNOWN_METHOD + " frames " + (unknownStacks.isEmpty() ? 0 : ">0");
        }
    }

    /**
     * Starts the workers together, waits for them to exit, and returns their context class
     * loaders. Once the caller drops the returned list, nothing keeps a loader reachable.
     */
    private List<ClassLoader> runWorkers(byte[] workerBytes) throws Exception {
        List<ClassLoader> loaders = new ArrayList<>();
        Thread[] threads = new Thread[THREADS];
        CountDownLatch start = new CountDownLatch(1);
        AtomicReference<Throwable> failure = new AtomicReference<>();

        for (int i = 0; i < THREADS; i++) {
            ClassLoader loader = new ChildFirstLoader(WORKER_CLASS, workerBytes, getClass().getClassLoader());
            loaders.add(loader);
            threads[i] = new Thread(() -> {
                try {
                    start.await();
                    // Load through the thread's own context loader, the way a container
                    // or plugin framework would.
                    ClassLoader ccl = Thread.currentThread().getContextClassLoader();
                    Class<?> workerClass = Class.forName(WORKER_CLASS, true, ccl);
                    if (workerClass.getClassLoader() != ccl) {
                        throw new AssertionError(WORKER_CLASS + " was not defined by the context loader");
                    }
                    Runnable worker = (Runnable) workerClass.getConstructor(long.class).newInstance(WORK_NANOS);
                    worker.run();
                } catch (Throwable t) {
                    failure.compareAndSet(null, t);
                }
            }, THREAD_PREFIX + i);
            threads[i].setContextClassLoader(loader);
        }

        for (Thread thread : threads) {
            thread.start();
        }
        start.countDown();
        for (Thread thread : threads) {
            thread.join();
        }
        assertNull(failure.get(), () -> "Worker thread failed: " + failure.get());
        // An exited Thread still holds its context class loader; drop the threads too.
        for (int i = 0; i < THREADS; i++) {
            threads[i] = null;
        }
        return loaders;
    }

    private static void awaitUnload(List<WeakReference<ClassLoader>> loaders) throws InterruptedException {
        long deadline = System.currentTimeMillis() + UNLOAD_TIMEOUT_MS;
        int alive = countAlive(loaders);
        while (alive > 0 && System.currentTimeMillis() < deadline) {
            System.gc();
            Thread.sleep(50);
            alive = countAlive(loaders);
        }
        assertEquals(0, alive, alive + " of " + THREADS
                + " context class loaders were still reachable " + UNLOAD_TIMEOUT_MS + "ms after their threads exited");
    }

    private static int countAlive(List<WeakReference<ClassLoader>> loaders) {
        int alive = 0;
        for (WeakReference<ClassLoader> ref : loaders) {
            if (ref.get() != null) {
                alive++;
            }
        }
        return alive;
    }

    private static byte[] readClassBytes(String className) throws IOException {
        String resource = className.replace('.', '/') + ".class";
        try (InputStream in = ContextClassLoaderUnloadTest.class.getClassLoader().getResourceAsStream(resource)) {
            assertNotNull(in, "Cannot find " + resource + " on the test classpath");
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            byte[] buf = new byte[8192];
            for (int n; (n = in.read(buf)) != -1; ) {
                out.write(buf, 0, n);
            }
            return out.toByteArray();
        }
    }

    /** Defines its own copy of one class from bytes; delegates everything else to the parent. */
    private static final class ChildFirstLoader extends ClassLoader {
        private final String ownedClass;
        private final byte[] ownedBytes;

        ChildFirstLoader(String ownedClass, byte[] ownedBytes, ClassLoader parent) {
            super(parent);
            this.ownedClass = ownedClass;
            this.ownedBytes = ownedBytes;
        }

        @Override
        protected Class<?> loadClass(String name, boolean resolve) throws ClassNotFoundException {
            if (!ownedClass.equals(name)) {
                return super.loadClass(name, resolve);
            }
            synchronized (getClassLoadingLock(name)) {
                Class<?> c = findLoadedClass(name);
                if (c == null) {
                    c = defineClass(name, ownedBytes, 0, ownedBytes.length);
                }
                if (resolve) {
                    resolveClass(c);
                }
                return c;
            }
        }
    }
}
