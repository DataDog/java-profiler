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
 * Hang reproducer for java-profiler + wasmtime signal handler interaction.
 *
 * Two classes of workers run concurrently under cpu+wall profiling at 1 ms:
 *
 * SpinWorkerThread  — calls spin(i64)->i64 in a tight loop, keeping Cranelift
 *                     JIT'd code executing while SIGPROF fires. Exercises frame-
 *                     pointer-less stack unwinding and signal-mask conflicts.
 *
 * TrapWorkerThread  — repeatedly calls trap()->() (WASM unreachable), which
 *                     forces wasmtime's SIGSEGV/trap handler chain to fire.
 *                     Re-creates Store+Instance on every iteration because a
 *                     WASM trap leaves the store's internal state undefined.
 *                     Exercises the SIGSEGV handler chain collision with SIGPROF.
 *
 * A MonitorThread checks per-worker progress counters every 5 s. If any counter
 * is unchanged the thread has stalled — it prints a full ThreadMXBean dump and
 * exits with code 42.
 *
 * Shared across threads: Engine, Module (immutable after construction).
 * Per-thread:           Store, Instance (not thread-safe).
 */
public class WasmtimeReproducer {

    private static final int SPIN_WORKERS = Math.max(4, Runtime.getRuntime().availableProcessors());
    private static final int TRAP_WORKERS = Math.max(2, SPIN_WORKERS / 2);
    private static final long SPIN_COUNT = 10_000_000L;
    private static final long MONITOR_INTERVAL_MS = 5_000;
    private static final int HANG_EXIT_CODE = 42;

    public static void main(String[] args) throws Exception {
        startProfiler();

        byte[] wasmBytes = loadWasmBytes();
        Engine engine = new Engine();
        Module module = new Module(engine, wasmBytes);

        int total = SPIN_WORKERS + TRAP_WORKERS;
        AtomicLong[] counters = new AtomicLong[total];
        Thread[] workers = new Thread[total];

        for (int i = 0; i < SPIN_WORKERS; i++) {
            counters[i] = new AtomicLong(0);
            workers[i] = new SpinWorkerThread(i, engine, module, counters[i]);
            workers[i].setDaemon(false);
        }
        for (int i = 0; i < TRAP_WORKERS; i++) {
            int idx = SPIN_WORKERS + i;
            counters[idx] = new AtomicLong(0);
            workers[idx] = new TrapWorkerThread(i, engine, module, counters[idx]);
            workers[idx].setDaemon(false);
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

    /**
     * Runs spin(SPIN_COUNT) in a tight loop.
     * Exercises: SIGPROF arriving inside Cranelift JIT'd code (signal mask
     * conflicts, frame-pointer-less stack unwinding, sigaltstack collisions).
     */
    private static class SpinWorkerThread extends Thread {
        private final int id;
        private final Engine engine;
        private final Module module;
        private final AtomicLong counter;

        SpinWorkerThread(int id, Engine engine, Module module, AtomicLong counter) {
            super("spin-worker-" + id);
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
                System.out.printf("[spin-worker-%d] started%n", id);
                while (!Thread.currentThread().isInterrupted()) {
                    spinFn.call(store, Val.fromI64(SPIN_COUNT));
                    counter.incrementAndGet();
                }
            } catch (Exception e) {
                System.err.printf("[spin-worker-%d] ERROR: %s%n", id, e.getMessage());
            }
        }
    }

    /**
     * Repeatedly triggers a WASM unreachable trap, forcing wasmtime's
     * SIGSEGV/SIGBUS trap-handler chain to fire on every iteration.
     *
     * Re-creates Store+Instance each iteration: after a WASM trap the store's
     * internal state is undefined. The creation/destruction cycle also stresses
     * wasmtime's JIT compilation phase under concurrent SIGPROF signals.
     *
     * Exercises: SIGSEGV handler chain collision with SIGPROF.
     */
    private static class TrapWorkerThread extends Thread {
        private final int id;
        private final Engine engine;
        private final Module module;
        private final AtomicLong counter;

        TrapWorkerThread(int id, Engine engine, Module module, AtomicLong counter) {
            super("trap-worker-" + id);
            this.id = id;
            this.engine = engine;
            this.module = module;
            this.counter = counter;
        }

        @Override
        @SuppressWarnings("unchecked")
        public void run() {
            System.out.printf("[trap-worker-%d] started%n", id);
            while (!Thread.currentThread().isInterrupted()) {
                try (Store<Void> store = new Store<>(null, engine);
                     Instance instance = new Instance(store, module, Collections.<Extern>emptyList())) {
                    Func trapFn = instance.getFunc(store, "trap").orElseThrow(
                            () -> new RuntimeException("'trap' export not found"));
                    trapFn.call(store);
                } catch (RuntimeException e) {
                    // expected: wasmtime converts the WASM unreachable trap into a RuntimeException
                }
                counter.incrementAndGet();
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
                        String name = i < SPIN_WORKERS
                                ? "spin-worker-" + i
                                : "trap-worker-" + (i - SPIN_WORKERS);
                        System.out.printf(
                                "HANG DETECTED on %s after %ds (counter stuck at %d)%n",
                                name, elapsedSec, cur);
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
