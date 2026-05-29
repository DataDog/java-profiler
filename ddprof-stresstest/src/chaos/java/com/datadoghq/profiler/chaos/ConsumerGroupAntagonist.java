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
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Maintains 16 "consumer" threads doing light spin work. Every 3 s it
 * replaces 4 threads simultaneously (all interrupted at once, all
 * replacements started before waiting for exits) to simulate a Kafka
 * consumer group rebalance burst.
 *
 * <p>Targets: ProfiledThread recycling under burst replacement;
 * signal-vs-thread-end race window widened by simultaneous stops;
 * calltrace storage put() racing thread destruction.
 */
public final class ConsumerGroupAntagonist implements Antagonist {

    private static final int GROUP_SIZE = 16;
    private static final int BURST_SIZE = 4;
    private static final long REBALANCE_INTERVAL_MS = 3_000L;

    private final Thread[] consumers = new Thread[GROUP_SIZE];
    private volatile boolean running;
    private Thread rebalancer;
    private final AtomicLong sink = new AtomicLong();

    @Override
    public String name() {
        return "consumer-group";
    }

    @Override
    public void start() {
        running = true;
        for (int i = 0; i < GROUP_SIZE; i++) {
            consumers[i] = newConsumer(i);
            consumers[i].start();
        }
        rebalancer = new Thread(new Runnable() {
            @Override public void run() { rebalanceLoop(); }
        }, "chaos-consumer-rebalancer");
        rebalancer.setDaemon(true);
        rebalancer.start();
    }

    @Override
    public void stopGracefully(Duration timeout) {
        running = false;
        rebalancer.interrupt();
        try {
            rebalancer.join(timeout.toMillis() / 2);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
        for (Thread t : consumers) {
            if (t != null) {
                t.interrupt();
                try { t.join(500L); } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        }
    }

    private Thread newConsumer(final int index) {
        Thread t = new Thread(new Runnable() {
            @Override
            public void run() {
                long r = ThreadLocalRandom.current().nextLong();
                while (running && !Thread.currentThread().isInterrupted()) {
                    for (int i = 0; i < 100; i++) {
                        r = r * 6364136223846793005L + 1442695040888963407L;
                    }
                    sink.addAndGet(r);
                    Thread.yield();
                }
            }
        }, "chaos-consumer-" + index);
        t.setDaemon(true);
        return t;
    }

    private void rebalanceLoop() {
        int offset = 0;
        while (running) {
            try {
                Thread.sleep(REBALANCE_INTERVAL_MS);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return;
            }
            if (!running) return;

            // Interrupt all victims simultaneously (burst)
            Thread[] victims = new Thread[BURST_SIZE];
            for (int i = 0; i < BURST_SIZE; i++) {
                int idx = offset + i;
                victims[i] = consumers[idx];
                consumers[idx] = null;
                if (victims[i] != null) {
                    victims[i].interrupt();
                }
            }
            // Start replacements before waiting for victims to fully exit
            for (int i = 0; i < BURST_SIZE; i++) {
                int idx = offset + i;
                consumers[idx] = newConsumer(idx);
                consumers[idx].start();
            }
            // Now wait for victims
            for (Thread victim : victims) {
                if (victim != null) {
                    try { victim.join(1_000L); } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                        return;
                    }
                }
            }
            offset = (offset + BURST_SIZE) % GROUP_SIZE;
        }
    }
}
