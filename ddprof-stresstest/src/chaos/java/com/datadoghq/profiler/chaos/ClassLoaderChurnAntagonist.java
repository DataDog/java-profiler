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

import java.lang.reflect.Method;
import java.time.Duration;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Continuously generates throwaway classes inside disposable class loaders so
 * that class unload races stack walking and {@code CodeCache}/{@code Symbols}
 * cleanup. Each iteration:
 *
 * <ol>
 *   <li>generates a unique class with a single static {@code compute(long)} method
 *   <li>defines it in a fresh {@link ClassLoader}
 *   <li>invokes the method (forces JIT exposure, registration in profiler tables)
 *   <li>drops every reference so the loader and class become unloadable
 * </ol>
 */
public final class ClassLoaderChurnAntagonist implements Antagonist {

    private static final AtomicLong COUNTER = new AtomicLong();

    private volatile boolean running;
    private Thread driver;
    private final AtomicLong sink = new AtomicLong();

    @Override
    public String name() {
        return "classloader-churn";
    }

    @Override
    public void start() {
        running = true;
        driver = new Thread(this::loop, "chaos-classloader-churn");
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
        while (running) {
            long uid = COUNTER.incrementAndGet();
            String simpleName = "Generated_" + uid;
            String binaryName = "chaos.gen." + simpleName;
            String internalName = "chaos/gen/" + simpleName;
            byte[] bytecode = generate(internalName);
            ChurnLoader loader = new ChurnLoader();
            try {
                Class<?> klass = loader.define(binaryName, bytecode);
                Method m = klass.getMethod("compute", long.class);
                Object result = m.invoke(null, uid);
                sink.addAndGet((long) result);
            } catch (Throwable t) {
                // transient; JVM crash is the signal we watch for
            }
            // loader + klass go out of scope here.
        }
    }

    private static byte[] generate(String internalName) {
        ClassWriter cw = new ClassWriter(ClassWriter.COMPUTE_FRAMES | ClassWriter.COMPUTE_MAXS);
        cw.visit(Opcodes.V1_8,
                Opcodes.ACC_PUBLIC | Opcodes.ACC_FINAL,
                internalName,
                null,
                "java/lang/Object",
                null);

        // public static long compute(long x) { return x * 1103515245L + 12345L; }
        MethodVisitor mv = cw.visitMethod(
                Opcodes.ACC_PUBLIC | Opcodes.ACC_STATIC,
                "compute",
                "(J)J",
                null,
                null);
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

    private static final class ChurnLoader extends ClassLoader {
        ChurnLoader() {
            super(ClassLoaderChurnAntagonist.class.getClassLoader());
        }

        Class<?> define(String name, byte[] bytes) {
            return defineClass(name, bytes, 0, bytes.length);
        }
    }
}
