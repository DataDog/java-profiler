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

import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodHandles;
import java.lang.invoke.MethodType;
import java.lang.reflect.Field;
import java.time.Duration;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Drives concurrent Java heap allocation and native ({@code malloc}/{@code free})
 * pressure to exercise the alloc engine and the GOT-patched libc allocator path.
 *
 * <p>Two driver threads:
 * <ul>
 *   <li>{@code chaos-alloc-java}: cycles short-lived {@code byte[]} of varied sizes
 *   <li>{@code chaos-alloc-native}: tight {@code allocateMemory}/{@code freeMemory}
 *       loop via reflective {@code sun.misc.Unsafe} access. No-ops gracefully if
 *       the access is blocked.
 * </ul>
 */
public final class AllocStormAntagonist implements Antagonist {

    private static final int[] SIZES = {64, 256, 1024, 4096, 16_384, 65_536};
    private static final long NATIVE_BLOCK_SIZE = 4096L;

    private static final Object UNSAFE;
    private static final MethodHandle ALLOCATE_MEMORY;
    private static final MethodHandle FREE_MEMORY;

    static {
        Object instance = null;
        MethodHandle alloc = null;
        MethodHandle free = null;
        try {
            Class<?> unsafeClass = Class.forName("sun.misc.Unsafe");
            Field f = unsafeClass.getDeclaredField("theUnsafe");
            f.setAccessible(true);
            instance = f.get(null);
            MethodHandles.Lookup lookup = MethodHandles.lookup();
            alloc = lookup.findVirtual(unsafeClass, "allocateMemory",
                    MethodType.methodType(long.class, long.class));
            free = lookup.findVirtual(unsafeClass, "freeMemory",
                    MethodType.methodType(void.class, long.class));
        } catch (Throwable t) {
            // Fall through; native loop will no-op.
        }
        UNSAFE = instance;
        ALLOCATE_MEMORY = alloc;
        FREE_MEMORY = free;
    }

    private volatile boolean running;
    private Thread javaDriver;
    private Thread nativeDriver;
    private final AtomicLong sink = new AtomicLong();

    @Override
    public String name() {
        return "alloc-storm";
    }

    @Override
    public void start() {
        running = true;
        javaDriver = new Thread(this::javaLoop, "chaos-alloc-java");
        javaDriver.setDaemon(true);
        javaDriver.start();
        nativeDriver = new Thread(this::nativeLoop, "chaos-alloc-native");
        nativeDriver.setDaemon(true);
        nativeDriver.start();
    }

    @Override
    public void stopGracefully(Duration timeout) {
        running = false;
        long millis = timeout.toMillis();
        try {
            javaDriver.join(millis);
            nativeDriver.join(millis);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private void javaLoop() {
        long acc = 0L;
        int idx = 0;
        while (running) {
            byte[] buf = new byte[SIZES[idx]];
            // Touch first/last byte so the JIT cannot elide the allocation.
            buf[0] = (byte) idx;
            acc += buf[buf.length - 1];
            idx = (idx + 1) % SIZES.length;
        }
        sink.addAndGet(acc);
    }

    private void nativeLoop() {
        if (UNSAFE == null || ALLOCATE_MEMORY == null || FREE_MEMORY == null) {
            System.out.println("[chaos] alloc-storm: native loop skipped (Unsafe not accessible)");
            return;
        }
        long acc = 0L;
        try {
            while (running) {
                long addr = (long) ALLOCATE_MEMORY.invoke(UNSAFE, NATIVE_BLOCK_SIZE);
                acc += addr;
                FREE_MEMORY.invoke(UNSAFE, addr);
            }
        } catch (Throwable t) {
            // reflective failure; JVM crash is the signal we watch for
        }
        sink.addAndGet(acc);
    }
}
