/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrFrame;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.SpinClasses;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;
import org.junitpioneer.jupiter.RetryingTest;

import java.io.IOException;
import java.lang.ref.WeakReference;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Tests {@code fjmethodid=lazy}: no jmethodIDs are preloaded at ClassPrepare. walkVM stores
 * raw {@code Method*} frames, and the dump thread resolves them only if the owning class is
 * among the classes the dump pins, reading names and line numbers from VM metadata without
 * allocating any jmethodIDs.
 *
 * <p>The sampled class is defined by a custom class loader. In the partial mode
 * ({@code fjmethodid=false}) such classes are still preloaded; lazy mode must resolve them
 * without preloading.
 */
public class LazyJmethodIdTest extends AbstractProfilerTest {

    private static final String LAZY_COMMAND = "cpu=1ms,cstack=vm,fjmethodid=lazy";

    private static int classCounter = 0;

    @Override
    protected String getProfilerCommand() {
        return LAZY_COMMAND;
    }

    /**
     * Frames from a custom-loader class must resolve to their real names and line numbers, read
     * from VM metadata at dump time.
     */
    @RetryingTest(3)
    public void customLoaderFramesResolve() throws Exception {
        assumeHotspot();
        waitForProfilerReady(2000);

        String className = nextClassName("LazySpin");
        Class<?> clazz = SpinClasses.define(className);
        clazz.getMethod("spin", long.class).invoke(null, 1_000_000_000L);

        stopProfiler();

        String simpleName = className.substring(className.lastIndexOf('/') + 1);
        int spinFrames = 0;
        for (JfrEvent sample : verifyEvents("datadog.ExecutionSample")) {
            if (!sample.has("stackTrace")) {
                continue;
            }
            for (JfrFrame frame : sample.getStackTrace().frames()) {
                String frameClass = frame.className();
                if (frameClass != null && frameClass.endsWith(simpleName) && "spin".equals(frame.methodName())) {
                    spinFrames++;
                    assertTrue(SpinClasses.SPIN_LINES.contains(frame.lineNumber()),
                            "spin frame has line " + frame.lineNumber() + ", expected one of " + SpinClasses.SPIN_LINES);
                }
            }
        }
        assertTrue(spinFrames > 0, "No CPU sample contained a resolved " + simpleName + ".spin frame");

        // Absent in builds without counters; only check when present.
        Long resolved = profiler.getDebugCounters().get("method_resolve_lazy_resolved");
        if (resolved != null) {
            assertTrue(resolved > 0, "Expected raw frames to be resolved from VM metadata");
        }
    }

    /**
     * Frames whose class was unloaded between the sample and the dump must not be
     * dereferenced: the dump completes and those frames serialize as unknown. Where debug
     * counters are available, the dump must also have refused raw frames, so the class was
     * sampled and the refusal path ran.
     */
    @Test
    @Timeout(60)
    public void framesOfUnloadedClassAreDroppedSafely() throws Exception {
        assumeHotspot();
        stopProfiler();

        Path dir = Paths.get(System.getProperty("java.io.tmpdir"), "recordings");
        Files.createDirectories(dir);
        Path baseFile = Files.createTempFile(dir, "lazy-jmethodid-base-", ".jfr");
        Path dumpFile = Files.createTempFile(dir, "lazy-jmethodid-dump-", ".jfr");
        String className = nextClassName("LazyUnload");
        try {
            profiler.execute("start," + LAZY_COMMAND + ",jfr,file=" + baseFile.toAbsolutePath());
            try {
                waitForProfilerReady(2000);
                WeakReference<ClassLoader> loaderRef = spinInUnloadableClass(className);

                long deadline = System.currentTimeMillis() + 8_000;
                while (loaderRef.get() != null && System.currentTimeMillis() < deadline) {
                    System.gc();
                    Thread.sleep(20);
                }
                Assumptions.assumeTrue(loaderRef.get() == null,
                        "JVM did not unload the class within the deadline");

                profiler.dump(dumpFile);
                assertTrue(Files.size(dumpFile) > 0, "Dump after class unload produced no output");
            } finally {
                profiler.stop();
            }

            String simpleName = className.substring(className.lastIndexOf('/') + 1);
            for (JfrEvent sample : verifyEvents(dumpFile, "datadog.ExecutionSample", false)) {
                String stackTrace = sample.getStackTraceString();
                assertTrue(stackTrace == null || !stackTrace.contains(simpleName),
                        "A frame of the unloaded class was resolved after unload: " + stackTrace);
            }
            Map<String, Long> counters = profiler.getDebugCounters();
            System.out.println("method_resolve_lazy_unloaded=" + counters.get("method_resolve_lazy_unloaded")
                    + ", method_resolve_lazy_not_current=" + counters.get("method_resolve_lazy_not_current")
                    + ", method_resolve_lazy_unreadable=" + counters.get("method_resolve_lazy_unreadable")
                    + ", method_resolve_fault_recovered=" + counters.get("method_resolve_fault_recovered"));
            // Absent in builds without counters; only check when present.
            if (counters.containsKey("method_resolve_lazy_unloaded")) {
                long refused = counters.getOrDefault("method_resolve_lazy_unloaded", 0L)
                        + counters.getOrDefault("method_resolve_lazy_not_current", 0L)
                        + counters.getOrDefault("method_resolve_lazy_unreadable", 0L);
                assertTrue(refused > 0, "No raw frame was refused, so the unloaded class was never sampled");
            }
        } finally {
            try { Files.deleteIfExists(baseFile); } catch (IOException ignored) {}
            try { Files.deleteIfExists(dumpFile); } catch (IOException ignored) {}
        }
    }

    /**
     * On HotSpot builds with JFR, lazy mode must locate {@code Klass::_trace_id} by probing,
     * since vmStructs does not expose it.
     */
    @Test
    public void traceIdOffsetIsCalibrated() throws Exception {
        assumeHotspot();
        waitForProfilerReady(2000);
        Long offset = profiler.getDebugCounters().get("klass_trace_id_offset");
        System.out.println("klass_trace_id_offset=" + offset + " java.version=" + System.getProperty("java.version"));
        // Absent in builds without counters.
        Assumptions.assumeTrue(offset != null, "debug counters not available");
        // JDK 8 has JFR only from 8u272 on; without it there is no field to find.
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11), "JFR may be absent on JDK 8");
        assertTrue(offset > 0, "Klass::_trace_id offset was not found: " + offset);
    }

    private static void assumeHotspot() {
        // Lazy mode is HotSpot-only (raw Method* frames come from walkVM).
        Assumptions.assumeFalse(Platform.isZing() || Platform.isJ9() || Platform.isGraal());
    }

    private static synchronized String nextClassName(String prefix) {
        return "com/datadoghq/profiler/generated/" + prefix + (classCounter++);
    }

    // Kept out of the caller's frame so no strong reference to the class or its
    // loader survives on the stack.
    private static WeakReference<ClassLoader> spinInUnloadableClass(String className) throws Exception {
        Class<?> clazz = SpinClasses.define(className);
        clazz.getMethod("spin", long.class).invoke(null, 1_000_000_000L);
        return new WeakReference<>(clazz.getClassLoader());
    }
}
