/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junitpioneer.jupiter.RetryingTest;
import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.MethodVisitor;
import org.objectweb.asm.Opcodes;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.lang.reflect.Method;
import java.util.TreeSet;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Validates TLS priming by checking that CPU-time profiling captures samples
 * from the JVM's JIT compiler threads (HotSpot's "C1 CompilerThread*",
 * OpenJ9's "JIT Compilation Thread*").
 *
 * Compiler threads are started very early during JVM bootstrap, usually
 * before the profiler agent has attached and initialized. Because of that,
 * they never go through the normal thread-registration path the profiler
 * uses for application threads, so they have no ProfiledThread attached when
 * the first profiling signal reaches them. TLS priming is what covers this
 * gap: on that first signal, ProfiledThread::acquireCurrent() claims a slot
 * from the pool and attaches it via pthread_setspecific right there in the
 * signal handler (see threadLocalData.cpp/ThreadLocalDataPool). If priming
 * were broken, these early-started threads would simply never show up as
 * eventThread on a sample. So seeing compiler-thread samples here is direct
 * evidence that TLS priming worked.
 *
 * The test forces JIT compilation by loading a dynamically-generated class
 * with many distinct trivial methods and invoking each one past HotSpot's/
 * OpenJ9's cold-to-compiled threshold, then leaves the CPU sampler running
 * long enough for the background compiler thread(s) to actually drain the
 * resulting compile queue.
 */
public class TlsPrimingTest extends AbstractProfilerTest {

    private static final String HOTSPOT_COMPILER_THREAD_PREFIX = "C1 CompilerThre";
    private static final String J9_COMPILER_THREAD_PREFIX = "JIT Compilation Thread";

    // Distinct methods, each invoked enough times to individually cross the
    // JIT's cold-to-compiled invocation threshold, so the compiler queue has
    // sustained work rather than a single instantly-finished compile.
    private static final int METHOD_COUNT = 300;
    private static final int INVOCATIONS_PER_METHOD = 1000;

    // Compilation happens asynchronously on background compiler threads, so
    // after tripping the invocation thresholds we must give them real time to
    // drain the queue while the CPU sampler is still active.
    private static final long COMPILE_DRAIN_WAIT_MS = 4000;

    @RetryingTest(3)
    public void compilerThreadSamplesArePresent() throws Exception {
        triggerJitCompilation();

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.ExecutionSample");
        String expectedPrefix = Platform.isJ9() ? J9_COMPILER_THREAD_PREFIX : HOTSPOT_COMPILER_THREAD_PREFIX;

        Set<String> observedThreadNames = new TreeSet<>();
        boolean sawCompilerThreadSample = false;
        for (IItemIterable cpuSamples : events) {
            IMemberAccessor<String, IItem> threadNameAccessor =
                    JdkAttributes.EVENT_THREAD_NAME.getAccessor(cpuSamples.getType());
            for (IItem sample : cpuSamples) {
                String threadName = threadNameAccessor.getMember(sample);
                if (threadName == null) {
                    continue;
                }
                observedThreadNames.add(threadName);
                if (threadName.startsWith(expectedPrefix)) {
                    sawCompilerThreadSample = true;
                }
            }
        }

        assertTrue(sawCompilerThreadSample,
                "expected a datadog.ExecutionSample with eventThread starting with \"" + expectedPrefix
                        + "\", but observed thread names: " + observedThreadNames);
    }

    private void triggerJitCompilation() throws Exception {
        Class<?> generated = defineWorkloadClass();
        Object instance = generated.getDeclaredConstructor().newInstance();
        Method[] methods = generated.getDeclaredMethods();

        for (int call = 0; call < INVOCATIONS_PER_METHOD; call++) {
            for (Method m : methods) {
                m.invoke(instance);
            }
        }

        Thread.sleep(COMPILE_DRAIN_WAIT_MS);
    }

    /**
     * Generates a class with {@value #METHOD_COUNT} distinct no-arg int-returning
     * methods (each a different constant expression, so the JIT can't fold them
     * into one shared compiled method) and loads it in a fresh ClassLoader.
     */
    private static Class<?> defineWorkloadClass() throws ClassNotFoundException {
        String internalName = "com/datadoghq/profiler/cpu/generated/CompilerThreadWorkload";
        ClassWriter cw = new ClassWriter(ClassWriter.COMPUTE_FRAMES | ClassWriter.COMPUTE_MAXS);
        cw.visit(Opcodes.V1_8, Opcodes.ACC_PUBLIC, internalName, null, "java/lang/Object", null);

        MethodVisitor ctor = cw.visitMethod(Opcodes.ACC_PUBLIC, "<init>", "()V", null, null);
        ctor.visitCode();
        ctor.visitVarInsn(Opcodes.ALOAD, 0);
        ctor.visitMethodInsn(Opcodes.INVOKESPECIAL, "java/lang/Object", "<init>", "()V", false);
        ctor.visitInsn(Opcodes.RETURN);
        ctor.visitMaxs(0, 0);
        ctor.visitEnd();

        for (int i = 0; i < METHOD_COUNT; i++) {
            MethodVisitor mv = cw.visitMethod(Opcodes.ACC_PUBLIC, "method" + i, "()I", null, null);
            mv.visitCode();
            mv.visitIntInsn(Opcodes.SIPUSH, i);
            mv.visitIntInsn(Opcodes.SIPUSH, i + 1);
            mv.visitInsn(Opcodes.IMUL);
            mv.visitInsn(Opcodes.IRETURN);
            mv.visitMaxs(0, 0);
            mv.visitEnd();
        }
        cw.visitEnd();

        IsolatedClassLoader loader = new IsolatedClassLoader(TlsPrimingTest.class.getClassLoader());
        return loader.defineClass(internalName.replace('/', '.'), cw.toByteArray());
    }

    private static final class IsolatedClassLoader extends ClassLoader {
        IsolatedClassLoader(ClassLoader parent) {
            super(parent);
        }

        Class<?> defineClass(String name, byte[] bytecode) {
            return defineClass(name, bytecode, 0, bytecode.length);
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms";
    }
}
