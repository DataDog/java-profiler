/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;
import org.junitpioneer.jupiter.RetryingTest;
import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.Label;
import org.objectweb.asm.MethodVisitor;
import org.objectweb.asm.Opcodes;

import java.io.IOException;
import java.lang.ref.WeakReference;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Tests {@code fjmethodid=lazy}: no jmethodIDs are preloaded at ClassPrepare. walkVM stores
 * raw {@code Method*} frames, and the dump thread resolves them only after
 * {@code KlassRegistry} confirms the owning class is still loaded, allocating jmethodIDs for
 * that one class on first use.
 *
 * <p>The sampled class is defined by a custom class loader. In the partial mode
 * ({@code fjmethodid=false}) such classes are still preloaded, because the dump-time
 * {@code FindClass} lookup cannot see them; lazy mode must resolve them without either.
 */
public class LazyJmethodIdTest extends AbstractProfilerTest {

    private static final String LAZY_COMMAND = "cpu=1ms,cstack=vm,fjmethodid=lazy";

    private static int classCounter = 0;

    @Override
    protected String getProfilerCommand() {
        return LAZY_COMMAND;
    }

    /**
     * Frames from a custom-loader class must resolve to their real names, and the class's
     * jmethodIDs must have been allocated at dump time rather than preloaded.
     */
    @RetryingTest(3)
    public void customLoaderFramesResolve() throws Exception {
        assumeHotspot();
        waitForProfilerReady(2000);

        String className = nextClassName("LazySpin");
        Class<?> clazz = new SpinClassLoader().define(className);
        clazz.getMethod("spin", long.class).invoke(null, 1_000_000_000L);

        stopProfiler();

        String simpleName = className.substring(className.lastIndexOf('/') + 1);
        boolean found = false;
        for (JfrEvent sample : verifyEvents("datadog.ExecutionSample")) {
            String stackTrace = sample.getStackTraceString();
            if (stackTrace != null && stackTrace.contains(simpleName) && stackTrace.contains("spin")) {
                found = true;
                break;
            }
        }
        assertTrue(found, "No CPU sample contained a resolved " + simpleName + ".spin frame");

        // Absent in builds without counters; only check when present.
        Long classesLoaded = profiler.getDebugCounters().get("method_resolve_lazy_class_loaded");
        if (classesLoaded != null) {
            assertTrue(classesLoaded > 0,
                    "Expected jmethodIDs to be allocated at dump time for at least one class");
        }
    }

    /**
     * Frames whose class was unloaded between the sample and the dump must not be
     * dereferenced: the dump completes and those frames serialize as unknown.
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
                Thread.sleep(200);
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
                    + ", method_resolve_fault_recovered=" + counters.get("method_resolve_fault_recovered"));
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
        SpinClassLoader loader = new SpinClassLoader();
        Class<?> clazz = loader.define(className);
        clazz.getMethod("spin", long.class).invoke(null, 300_000_000L);
        return new WeakReference<>(loader);
    }

    /**
     * Defines a class with {@code public static void spin(long nanos)}, which busy-waits so
     * that CPU samples land in it.
     */
    private static final class SpinClassLoader extends ClassLoader {
        Class<?> define(String internalName) {
            byte[] bytes = generate(internalName);
            return defineClass(internalName.replace('/', '.'), bytes, 0, bytes.length);
        }

        private static byte[] generate(String internalName) {
            ClassWriter cw = new ClassWriter(ClassWriter.COMPUTE_FRAMES | ClassWriter.COMPUTE_MAXS);
            cw.visit(Opcodes.V1_8, Opcodes.ACC_PUBLIC, internalName, null, "java/lang/Object", null);

            MethodVisitor mv = cw.visitMethod(Opcodes.ACC_PUBLIC | Opcodes.ACC_STATIC, "spin", "(J)V", null, null);
            mv.visitCode();
            // long deadline = System.nanoTime() + nanos;
            mv.visitMethodInsn(Opcodes.INVOKESTATIC, "java/lang/System", "nanoTime", "()J", false);
            mv.visitVarInsn(Opcodes.LLOAD, 0);
            mv.visitInsn(Opcodes.LADD);
            mv.visitVarInsn(Opcodes.LSTORE, 2);
            // while (System.nanoTime() < deadline) {}
            Label loop = new Label();
            Label done = new Label();
            mv.visitLabel(loop);
            mv.visitMethodInsn(Opcodes.INVOKESTATIC, "java/lang/System", "nanoTime", "()J", false);
            mv.visitVarInsn(Opcodes.LLOAD, 2);
            mv.visitInsn(Opcodes.LCMP);
            mv.visitJumpInsn(Opcodes.IFGE, done);
            mv.visitJumpInsn(Opcodes.GOTO, loop);
            mv.visitLabel(done);
            mv.visitInsn(Opcodes.RETURN);
            mv.visitMaxs(0, 0);
            mv.visitEnd();

            cw.visitEnd();
            return cw.toByteArray();
        }
    }
}
