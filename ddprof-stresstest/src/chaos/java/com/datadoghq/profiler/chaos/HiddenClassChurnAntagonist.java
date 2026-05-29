/*
 * Copyright 2026, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */
package com.datadoghq.profiler.chaos;

import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.MethodVisitor;
import org.objectweb.asm.Opcodes;

import java.lang.invoke.MethodHandles;
import java.lang.reflect.Array;
import java.lang.reflect.Method;
import java.time.Duration;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Generates hidden classes via {@code MethodHandles.Lookup.defineHiddenClass}
 * (Java 15+) and immediately drops all references to make them GC-eligible.
 *
 * <p>Gracefully no-ops on JDKs that do not support hidden classes.
 *
 * <p>Targets: StringDictionary concurrent eviction racing hidden-class GC;
 * class-map lookup for a class being unloaded while the profiler dumps.
 */
public final class HiddenClassChurnAntagonist implements Antagonist {

    private static final Method DEFINE_HIDDEN_CLASS;
    private static final Object EMPTY_OPTIONS; // ClassOption[0] at runtime

    static {
        Method m = null;
        Object opts = null;
        try {
            Class<?> optionClass = Class.forName("java.lang.invoke.MethodHandles$Lookup$ClassOption");
            // Build ClassOption[] type without arrayType() (requires Java 12+)
            Object emptyArray = Array.newInstance(optionClass, 0);
            m = MethodHandles.Lookup.class.getMethod(
                    "defineHiddenClass", byte[].class, boolean.class, emptyArray.getClass());
            opts = emptyArray;
        } catch (Throwable t) {
            // Java < 15: defineHiddenClass not available
        }
        DEFINE_HIDDEN_CLASS = m;
        EMPTY_OPTIONS = opts;
    }

    private static final AtomicLong COUNTER = new AtomicLong();
    private volatile boolean running;
    private Thread driver;
    private final AtomicLong sink = new AtomicLong();

    @Override
    public String name() {
        return "hidden-class-churn";
    }

    @Override
    public void start() {
        running = true;
        driver = new Thread(new Runnable() {
            @Override public void run() { loop(); }
        }, "chaos-hidden-class-churn");
        driver.setDaemon(true);
        driver.start();
    }

    @Override
    public void stopGracefully(Duration timeout) {
        running = false;
        try {
            driver.join(timeout.toMillis());
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private void loop() {
        if (DEFINE_HIDDEN_CLASS == null) {
            System.out.println("[chaos] hidden-class-churn: skipping (defineHiddenClass not available on this JDK)");
            return;
        }
        MethodHandles.Lookup lookup = MethodHandles.lookup();
        while (running) {
            long uid = COUNTER.incrementAndGet();
            byte[] bytecode = generateClass(uid);
            try {
                // invoke(lookup, byte[], boolean, ClassOption[]) → MethodHandles.Lookup
                MethodHandles.Lookup hiddenLookup = (MethodHandles.Lookup)
                        DEFINE_HIDDEN_CLASS.invoke(lookup,
                                new Object[]{bytecode, Boolean.FALSE, EMPTY_OPTIONS});
                Class<?> klass = hiddenLookup.lookupClass();
                // Invoke compute() to force JIT registration in profiler tables
                Object result = klass.getMethod("compute", long.class).invoke(null, uid);
                sink.addAndGet((long) result);
                // klass and hiddenLookup go out of scope → hidden class GC-eligible
            } catch (Throwable t) {
                // transient; JVM crash is the signal we watch for
            }
        }
    }

    private static byte[] generateClass(long uid) {
        // Unique internal name per class so each one gets a distinct entry
        // in the profiler's class map / StringDictionary.
        String internalName = "com/datadoghq/profiler/chaos/Gen" + uid;
        ClassWriter cw = new ClassWriter(ClassWriter.COMPUTE_FRAMES | ClassWriter.COMPUTE_MAXS);
        cw.visit(Opcodes.V11,
                Opcodes.ACC_PUBLIC | Opcodes.ACC_FINAL,
                internalName, null, "java/lang/Object", null);
        MethodVisitor mv = cw.visitMethod(
                Opcodes.ACC_PUBLIC | Opcodes.ACC_STATIC, "compute", "(J)J", null, null);
        mv.visitCode();
        mv.visitVarInsn(Opcodes.LLOAD, 0);
        mv.visitLdcInsn(1103515245L);
        mv.visitInsn(Opcodes.LMUL);
        mv.visitLdcInsn(12345L);
        mv.visitInsn(Opcodes.LADD);
        mv.visitInsn(Opcodes.LRETURN);
        mv.visitMaxs(0, 0);
        mv.visitEnd();
        cw.visitEnd();
        return cw.toByteArray();
    }
}
