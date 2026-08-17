/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.MethodVisitor;
import org.objectweb.asm.Opcodes;

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
 * signal handler (see threadLocalData.cpp/ThreadLocalDataPool).
 *
 * The presence of compiler-thread samples is itself the proof that priming
 * worked on those threads. CTimer::signalHandler (the engine behind "cpu=")
 * opens with SIGNAL_HANDLER_GUARD_OR_DROP_WITH_ERRNO(saved_errno), which
 * returns before recordSample() is ever reached whenever
 * ProfiledThread::acquireCurrent() comes back null (see ctimer_linux.cpp and
 * guards.h). A compiler thread whose priming failed
 * therefore contributes no datadog.ExecutionSample at all, so counting those
 * samples is a direct, per-thread observation rather than a proxy.
 *
 * Note that these samples legitimately carry an empty frame list -- a compiler
 * thread has no Java stack to unwind -- so the stack contents cannot be used
 * as a priming signal, only the samples' existence.
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

    // Floor for the proportional drop allowance, so a run that happened to record
    // very few samples doesn't turn a couple of incidental pool-slot losses into a
    // failure. Mirrors NativeThreadPrimingTest's MAX_SYNTHETIC_NATIVE_THREAD_SAMPLES.
    private static final long MIN_DROPPED_ALLOWANCE = 10;

    @Override
    protected boolean isPlatformSupported() {
        // TLS priming is not implemented on macOS. Zing is excluded separately:
        // its compiler threads don't use either the HotSpot ("C1 CompilerThre")
        // or OpenJ9 ("JIT Compilation Thread") naming this test's assertion
        // recognizes, so it would fail here even when priming works correctly.
        //
        // This is necessary but not sufficient: even on Linux/glibc, whether priming is
        // actually active depends on where this process's ProfiledThread pthread key landed
        // (see ProfiledThread::supportPriming()), which isn't known until the native library
        // is loaded. That's checked separately below, once the profiler is up.
        return !Platform.isMac() && !Platform.isZing();
    }

    @RetryingTest(3)
    public void compilerThreadSamplesArePresent() throws Exception {
        Assumptions.assumeTrue(JavaProfiler.testTlsPrimingAvailable(),
                "TLS priming pool unavailable on this run (ProfiledThread key fell outside "
                        + "glibc's preallocated key range -- see ProfiledThread::supportPriming())");

        triggerJitCompilation();

        stopProfiler();

        JfrEvents events = verifyEvents("datadog.ExecutionSample");
        String expectedPrefix = Platform.isJ9() ? J9_COMPILER_THREAD_PREFIX : HOTSPOT_COMPILER_THREAD_PREFIX;

        Set<String> observedThreadNames = new TreeSet<>();
        long totalSamples = 0;
        long compilerThreadSamples = 0;
        for (JfrEvent sample : events) {
            String threadName = sample.getThreadName("eventThread");
            if (threadName == null) {
                continue;
            }
            totalSamples++;
            observedThreadNames.add(threadName);
            if (threadName.startsWith(expectedPrefix)) {
                compilerThreadSamples++;
            }
        }

        assertTrue(compilerThreadSamples > 0,
                "expected a datadog.ExecutionSample with eventThread starting with \"" + expectedPrefix
                        + "\", but observed thread names: " + observedThreadNames);

        // Secondary, whole-process signal only -- see the class javadoc for why the
        // assertion above is the actual proof. samples_dropped_thread_local cannot be
        // asserted to be exactly zero here:
        //  * it is absent entirely from builds without -DCOUNTERS, where
        //    getDebugCounters() hands back an empty map (javaApi.cpp/JavaProfiler);
        //  * it is shared with the mallocTracer, wallClock, nativeSocketSampler and
        //    JVMTI recording paths, and with every SIGNAL_HANDLER_GUARD_OR_DROP()/
        //    SIGNAL_HANDLER_GUARD_OR_DROP_WITH_ERRNO() signal handler (perf, ctimer,
        //    itimer) -- SIGNAL_HANDLER_GUARD_NO_SAMPLE(), used by the non-sampling
        //    wakeupHandler in vmEntry.cpp, does not touch this counter; and
        //  * it also counts threads that merely lost the race for one of the pool's
        //    64 slots (ThreadLocalDataPool::DEFAULT_CAPACITY) rather than hitting a
        //    priming bug. Capacity exhaustion does separately increment
        //    thread_local_pool_exhausted (ThreadLocalDataPool::claim()), but only for
        //    drops that went through ProfiledThread::acquireCurrent() -- e.g.
        //    NativeSocketSampler::recordEvent()'s initCurrentThreadSignalSafe() path
        //    drops via samples_dropped_thread_local without ever touching the pool --
        //    so a nonzero gap between the two counters still isn't proof of a real
        //    priming bug rather than one of those other causes.
        // A systematic priming failure drops samples on the order of the sample count,
        // so bound it proportionally instead: that still catches a real regression
        // without failing on a machine whose JVM simply runs more threads than the pool
        // has slots.
        Long droppedThreadLocal = profiler.getDebugCounters().get("samples_dropped_thread_local");
        System.out.println("compilerThreadSamples=" + compilerThreadSamples + "/" + totalSamples
                + ", samples_dropped_thread_local=" + droppedThreadLocal);
        if (droppedThreadLocal != null) {
            long maxDrops = Math.max(MIN_DROPPED_ALLOWANCE, totalSamples / 20);
            assertTrue(droppedThreadLocal <= maxDrops,
                    "TLS priming failed for an implausible number of signals: "
                            + droppedThreadLocal + " drops for " + totalSamples
                            + " recorded samples (allowed at most " + maxDrops + ")");
        }
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
    private static Class<?> defineWorkloadClass() throws ClassFormatError {
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
