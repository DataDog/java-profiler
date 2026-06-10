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

import java.lang.ref.WeakReference;
import java.time.Duration;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Alternates fill and drop phases to drive wave-pattern weak-reference
 * allocation and GC. A concurrent reader thread walks the weak-ref list
 * during the fill phase.
 *
 * <p>Fill: allocates 10 k {@code byte[]} objects with strong + weak refs.
 * Drop: releases strong refs (objects become weakly reachable), calls
 * {@link System#gc()}, counts survivors.
 *
 * <p>Targets: jweak ref leak during liveness table overflow; concurrent
 * read of a weakref cleared mid-wave; liveness table clearAll() race.
 */
public final class WeakRefWaveAntagonist implements Antagonist {

    private static final int WAVE_SIZE = 10_000;
    private static final int[] OBJECT_SIZES = {64, 256, 1_024, 4_096};

    private volatile boolean running;
    private Thread waveDriver;
    private Thread reader;

    // Written by waveDriver, read by reader. Volatile for visibility.
    private volatile List<WeakReference<byte[]>> currentWave = new ArrayList<WeakReference<byte[]>>();
    private final AtomicLong sink = new AtomicLong();

    @Override
    public String name() {
        return "weakref-wave";
    }

    @Override
    public void start() {
        running = true;
        reader = new Thread(new Runnable() {
            @Override public void run() { readerLoop(); }
        }, "chaos-weakref-reader");
        reader.setDaemon(true);
        reader.start();
        waveDriver = new Thread(new Runnable() {
            @Override public void run() { waveLoop(); }
        }, "chaos-weakref-wave");
        waveDriver.setDaemon(true);
        waveDriver.start();
    }

    @Override
    public void stopGracefully(Duration timeout) {
        running = false;
        long slice = timeout.toMillis() / 2;
        try {
            waveDriver.join(slice);
            reader.join(slice);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private void waveLoop() {
        while (running) {
            // Fill: allocate objects, hold both strong and weak refs
            List<byte[]> strongRefs = new ArrayList<byte[]>(WAVE_SIZE);
            List<WeakReference<byte[]>> weakRefs = new ArrayList<WeakReference<byte[]>>(WAVE_SIZE);
            for (int i = 0; i < WAVE_SIZE && running; i++) {
                int size = OBJECT_SIZES[i % OBJECT_SIZES.length];
                byte[] obj = new byte[size];
                obj[0] = (byte) i;
                strongRefs.add(obj);
                weakRefs.add(new WeakReference<byte[]>(obj));
            }
            // Publish filled list to reader
            currentWave = weakRefs;

            // Drop: release strong refs — objects now only weakly reachable
            strongRefs.clear();
            System.gc();

            // Count survivors (concurrent with reader on same list)
            long alive = 0;
            for (WeakReference<byte[]> ref : weakRefs) {
                if (ref.get() != null) alive++;
            }
            sink.addAndGet(alive);

            // Replace shared reference; weakRefs goes out of scope
            currentWave = new ArrayList<WeakReference<byte[]>>();
        }
    }

    private void readerLoop() {
        while (running) {
            List<WeakReference<byte[]>> wave = currentWave; // snapshot
            long alive = 0;
            for (WeakReference<byte[]> ref : wave) {
                if (ref.get() != null) alive++;
            }
            sink.addAndGet(alive);
            Thread.yield();
        }
    }
}
