package com.datadoghq.profiler.wasmtime;

import com.datadoghq.profiler.JavaProfiler;
import io.github.kawamuray.wasmtime.Engine;
import io.github.kawamuray.wasmtime.Extern;
import io.github.kawamuray.wasmtime.Func;
import io.github.kawamuray.wasmtime.Instance;
import io.github.kawamuray.wasmtime.Module;
import io.github.kawamuray.wasmtime.Store;
import io.github.kawamuray.wasmtime.Val;
import java.io.IOException;
import java.io.InputStream;
import java.lang.management.ManagementFactory;
import java.lang.management.ThreadInfo;
import java.lang.management.ThreadMXBean;
import java.util.Collections;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Hang reproducer for java-profiler + wasmtime interaction.
 *
 * Starts java-profiler with cpu+wall profiling, then runs N worker threads each
 * executing a compute-intensive WASM export (spin.wasm countdown loop) in a tight
 * loop.  A monitor thread checks per-worker progress counters every 5 s; if any
 * counter is unchanged the thread has stalled — it prints a full thread dump and
 * exits with code 42 (hang detected).
 *
 * Shared across threads: Engine, Module (immutable after construction).
 * Per-thread:           Store, Instance (not thread-safe).
 */
public class WasmtimeReproducer {

    private static final int WORKER_THREADS = Math.max(4, Runtime.getRuntime().availableProcessors());
    private static final long SPIN_COUNT = 10_000_000L;
    private static final long MONITOR_INTERVAL_MS = 5_000;
    private static final int HANG_EXIT_CODE = 42;

    public static void main(String[] args) throws Exception {
        startProfiler();

        byte[] wasmBytes = loadWasmBytes();
        Engine engine = new Engine();
        Module module = new Module(engine, wasmBytes);

        AtomicLong[] counters = new AtomicLong[WORKER_THREADS];
        Thread[] workers = new Thread[WORKER_THREADS];
        for (int i = 0; i < WORKER_THREADS; i++) {
            counters[i] = new AtomicLong(0);
            workers[i] = new WorkerThread(i, engine, module, counters[i]);
            workers[i].setDaemon(false);
        }

        Thread monitor = new MonitorThread(counters);
        monitor.setDaemon(true);
        monitor.start();

        for (Thread w : workers) {
            w.start();
        }
        for (Thread w : workers) {
            w.join();
        }
    }

    private static class WorkerThread extends Thread {
        private final int id;
        private final Engine engine;
        private final Module module;
        private final AtomicLong counter;

        WorkerThread(int id, Engine engine, Module module, AtomicLong counter) {
            super("worker-" + id);
            this.id = id;
            this.engine = engine;
            this.module = module;
            this.counter = counter;
        }

        @Override
        @SuppressWarnings("unchecked")
        public void run() {
            try (Store<Void> store = new Store<>(null, engine);
                 Instance instance = new Instance(store, module, Collections.<Extern>emptyList())) {
                Func spinFn = instance.getFunc(store, "spin").orElseThrow(
                        () -> new RuntimeException("'spin' export not found"));
                System.out.printf("[worker-%d] started%n", id);
                while (!Thread.currentThread().isInterrupted()) {
                    spinFn.call(store, Val.fromI64(SPIN_COUNT));
                    counter.incrementAndGet();
                }
            } catch (Exception e) {
                System.err.printf("[worker-%d] ERROR: %s%n", id, e.getMessage());
            }
        }
    }

    private static class MonitorThread extends Thread {
        private final AtomicLong[] counters;

        MonitorThread(AtomicLong[] counters) {
            super("monitor");
            this.counters = counters;
        }

        @Override
        public void run() {
            long[] prev = new long[counters.length];
            for (int i = 0; i < counters.length; i++) {
                prev[i] = counters[i].get();
            }
            long startMs = System.currentTimeMillis();
            while (true) {
                try {
                    Thread.sleep(MONITOR_INTERVAL_MS);
                } catch (InterruptedException e) {
                    return;
                }
                long elapsedSec = (System.currentTimeMillis() - startMs) / 1000;
                for (int i = 0; i < counters.length; i++) {
                    long cur = counters[i].get();
                    if (cur == prev[i]) {
                        System.out.printf(
                                "HANG DETECTED on worker-%d after %ds (counter stuck at %d)%n",
                                i, elapsedSec, cur);
                        dumpThreads();
                        System.exit(HANG_EXIT_CODE);
                    }
                    prev[i] = cur;
                }
            }
        }

        private static void dumpThreads() {
            ThreadMXBean bean = ManagementFactory.getThreadMXBean();
            ThreadInfo[] infos = bean.dumpAllThreads(true, true);
            for (ThreadInfo ti : infos) {
                System.out.println(ti);
            }
        }
    }

    private static void startProfiler() {
        try {
            JavaProfiler profiler = JavaProfiler.getInstance();
            profiler.execute("start,event=cpu,wall,interval=1ms");
            System.out.println("[profiler] started cpu+wall profiling");
        } catch (Exception e) {
            System.err.println("[profiler] WARNING: could not start profiler: " + e.getMessage());
        }
    }

    private static byte[] loadWasmBytes() throws IOException {
        try (InputStream is = WasmtimeReproducer.class.getResourceAsStream("/spin.wasm")) {
            if (is == null) {
                throw new IOException("spin.wasm not found in classpath");
            }
            return is.readAllBytes();
        }
    }
}
