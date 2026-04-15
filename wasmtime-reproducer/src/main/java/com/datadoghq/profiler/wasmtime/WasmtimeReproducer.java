package com.datadoghq.profiler.wasmtime;

import com.datadoghq.profiler.JavaProfiler;
import io.github.kawamuray.wasmtime.Engine;
import io.github.kawamuray.wasmtime.Extern;
import io.github.kawamuray.wasmtime.Instance;
import io.github.kawamuray.wasmtime.Module;
import io.github.kawamuray.wasmtime.Store;
import java.io.IOException;
import java.io.InputStream;
import java.util.Collections;

/**
 * Standalone reproducer for the java-profiler + wasmtime crash.
 *
 * Starts java-profiler with cpu+wall profiling enabled, then repeatedly runs a
 * full Engine -> Store -> Module -> Instance cycle. The crash is probabilistic
 * and more likely during the startup phase when the profiler and wasmtime's
 * signal handlers are both initialising.
 *
 * The JVM exit code is non-zero on a crash. The nohup shell harness
 * (run-reproducer.sh) detects that and stops.
 *
 * wasmtime-java 0.19.0 API:
 *   Engine()                          — constructor
 *   Store(T data, Engine engine)      — constructor; pass null for Void data
 *   Module(Engine engine, byte[] wasm)— constructor
 *   Instance(Store, Module, Collection<Extern>) — constructor
 */
public class WasmtimeReproducer {

    private static final int MAX_ITERATIONS = Integer.MAX_VALUE;

    public static void main(String[] args) throws Exception {
        // Start profiling before wasmtime loads to maximise the interaction window.
        startProfiler();

        byte[] wasmBytes = loadWasmBytes();
        long startMs = System.currentTimeMillis();

        for (int attempt = 1; attempt <= MAX_ITERATIONS; attempt++) {
            long elapsed = System.currentTimeMillis() - startMs;
            System.out.printf("[attempt %d | %dms] creating Engine%n", attempt, elapsed);

            try (Engine engine = new Engine()) {
                try (Store<Void> store = new Store<>(null, engine)) {
                    try (Module module = new Module(engine, wasmBytes)) {
                        try (Instance instance = new Instance(store, module, Collections.<Extern>emptyList())) {
                            // Instance created — the interaction between profiler signal
                            // handlers and wasmtime's runtime should be live at this point.
                        }
                    }
                }
            }
        }

        System.out.println("Reproducer completed without crash.");
    }

    private static void startProfiler() {
        try {
            JavaProfiler profiler = JavaProfiler.getInstance();
            profiler.execute("start,event=cpu,wall,interval=1ms");
            System.out.println("[profiler] started cpu+wall profiling");
        } catch (Exception e) {
            System.err.println("[profiler] WARNING: could not start profiler: " + e.getMessage());
            // Continue — the crash may still be reproducible if the profiler loaded partially.
        }
    }

    private static byte[] loadWasmBytes() throws IOException {
        try (InputStream is = WasmtimeReproducer.class.getResourceAsStream("/empty.wasm")) {
            if (is == null) {
                throw new IOException("empty.wasm not found in classpath");
            }
            return is.readAllBytes();
        }
    }
}
