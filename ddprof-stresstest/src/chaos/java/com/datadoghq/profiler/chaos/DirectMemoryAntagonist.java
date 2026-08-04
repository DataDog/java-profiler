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

import java.nio.ByteBuffer;
import java.time.Duration;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Drives direct (off-heap) memory allocation at high rate via
 * {@link ByteBuffer#allocateDirect}. Two concurrent modes:
 * <ul>
 *   <li><b>Ring-buffer mode:</b> allocates buffers of {4 KB, 64 KB, 512 KB},
 *       keeps 32 live slots, evicts the oldest each cycle.
 *   <li><b>Burst mode:</b> allocates and immediately drops 1 KB buffers in a
 *       tight loop.
 * </ul>
 *
 * <p>Targets: liveness-table overflow under high off-heap churn; jweak ref
 * release racing realloc failure cleanup.
 */
public final class DirectMemoryAntagonist implements Antagonist {

    private static final int RING_SIZE = 32;
    private static final int[] RING_SIZES_BYTES = {4_096, 65_536, 524_288};
    private static final int BURST_SIZE_BYTES = 1_024;

    private volatile boolean running;
    private Thread ringDriver;
    private Thread burstDriver;
    private final AtomicLong sink = new AtomicLong();

    @Override
    public String name() {
        return "direct-memory";
    }

    @Override
    public void start() {
        running = true;
        ringDriver = new Thread(new Runnable() {
            @Override public void run() { ringLoop(); }
        }, "chaos-direct-memory-ring");
        ringDriver.setDaemon(true);
        ringDriver.start();
        burstDriver = new Thread(new Runnable() {
            @Override public void run() { burstLoop(); }
        }, "chaos-direct-memory-burst");
        burstDriver.setDaemon(true);
        burstDriver.start();
    }

    @Override
    public void stopGracefully(Duration timeout) {
        running = false;
        long slice = timeout.toMillis() / 2;
        try {
            ringDriver.join(slice);
            burstDriver.join(slice);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private void ringLoop() {
        ByteBuffer[] ring = new ByteBuffer[RING_SIZE];
        int slot = 0;
        int sizeIdx = 0;
        while (running) {
            ring[slot] = null; // evict oldest — GC + Cleaner handles dealloc
            try {
                ByteBuffer buf = ByteBuffer.allocateDirect(RING_SIZES_BYTES[sizeIdx]);
                buf.put(0, (byte) slot); // touch to prevent elision
                sink.addAndGet(buf.capacity());
                ring[slot] = buf;
            } catch (OutOfMemoryError e) {
                // Direct memory exhausted; clear ring to allow recovery
                for (int i = 0; i < RING_SIZE; i++) {
                    ring[i] = null;
                }
            }
            slot = (slot + 1) % RING_SIZE;
            sizeIdx = (sizeIdx + 1) % RING_SIZES_BYTES.length;
            MemoryGovernor.pace();
        }
        for (int i = 0; i < RING_SIZE; i++) {
            ring[i] = null;
        }
    }

    private void burstLoop() {
        long acc = 0L;
        while (running) {
            try {
                ByteBuffer buf = ByteBuffer.allocateDirect(BURST_SIZE_BYTES);
                buf.put(0, (byte) 42);
                acc += buf.limit();
            } catch (OutOfMemoryError ignored) {
                // direct memory exhausted; fall through to sleep so Cleaner can drain
            }
            // Pace allocations so the Cleaner daemon thread can drain the
            // PhantomReference queue before direct memory fills up across a
            // long run. Without this, burstLoop saturates MaxDirectMemorySize
            // even though each buf is immediately dropped.
            try {
                Thread.sleep(1L);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return;
            }
            MemoryGovernor.pace();
        }
        sink.addAndGet(acc);
    }
}
