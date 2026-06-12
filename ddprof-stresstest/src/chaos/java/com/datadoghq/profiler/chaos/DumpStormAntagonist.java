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

import java.time.Duration;
import java.util.ArrayList;
import java.util.List;

/**
 * Spawns short-lived, frequently-renamed threads that each generate distinct
 * stack shapes, maximising churn in the profiler's thread-name table and
 * call-trace storage right as recording chunks rotate.
 *
 * <p>Targets: {@code Recording::switchChunk/writeCpool},
 * {@code updateJavaThreadNames -> ThreadInfo::set}, {@code Dictionary::clear}.
 * Pair with a short profiler recording interval so dumps fire continuously.
 */
public final class DumpStormAntagonist implements Antagonist {

    private final int concurrentThreads;
    private volatile boolean running;
    private Thread driver;

    public DumpStormAntagonist() {
        this(96);
    }

    public DumpStormAntagonist(int concurrentThreads) {
        this.concurrentThreads = concurrentThreads;
    }

    @Override
    public String name() {
        return "dump-storm";
    }

    @Override
    public void start() {
        running = true;
        driver = new Thread(this::loop, "chaos-dump-storm");
        driver.setDaemon(true);
        driver.start();
    }

    @Override
    public void stopGracefully(Duration timeout) {
        running = false;
        try {
            if (driver != null) driver.join(timeout.toMillis());
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private void loop() {
        long seq = 0;
        while (running) {
            List<Thread> batch = new ArrayList<>(concurrentThreads);
            for (int i = 0; i < concurrentThreads && running; i++) {
                final long id = seq++;
                Thread t = new Thread(() -> distinctStack(id, 0));
                t.setName("dump-storm-" + id);
                t.setDaemon(true);
                t.start();
                batch.add(t);
            }
            for (Thread t : batch) {
                try {
                    t.join(500L);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    return;
                }
            }
        }
    }

    // Recurse to a per-thread depth so each thread yields a unique stack shape,
    // forcing new call-trace + symbol entries that the dump path must serialise.
    // Depth floor is (id % 32) + 1 so id=0 (and every 32nd id) still recurse at
    // least once, avoiding identical single-frame stacks for those threads.
    private long distinctStack(long id, int depth) {
        if (depth >= (int) (id % 32) + 1) {
            long r = id;
            for (int i = 0; i < 5000; i++) r = (r * 1103515245L + 12345L) & 0x7fffffffL;
            return r;
        }
        return distinctStack(id, depth + 1) + depth;
    }
}
