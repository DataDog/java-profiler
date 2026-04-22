/*
 * Copyright 2025, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.datadoghq.profiler.stresstest.scenarios.throughput;

import com.datadoghq.profiler.JavaProfiler;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.LockSupport;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.BenchmarkMode;
import org.openjdk.jmh.annotations.Fork;
import org.openjdk.jmh.annotations.Level;
import org.openjdk.jmh.annotations.Measurement;
import org.openjdk.jmh.annotations.Mode;
import org.openjdk.jmh.annotations.OutputTimeUnit;
import org.openjdk.jmh.annotations.Param;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.TearDown;
import org.openjdk.jmh.annotations.Threads;
import org.openjdk.jmh.annotations.Warmup;
import org.openjdk.jmh.infra.Blackhole;

/**
 * Measures the impact of wall-clock signal suppression (Approach 1 + 2) on active-thread
 * throughput in the presence of a large background population of parked threads.
 *
 * <p>Setup: 200 background threads each call profiler.addThread() then park indefinitely via
 * LockSupport.park(), mimicking the idle-thread mix found in typical Java services. JMH worker
 * threads do CPU-bound work in the foreground.
 *
 * <p>Two {@code command} params are compared:
 * <ul>
 *   <li>{@code wall=1ms} — suppression on (wallprecheck=true, wallpark=true by default)</li>
 *   <li>{@code wall=1ms,wallprecheck=false,wallpark=false} — suppression off (baseline)</li>
 * </ul>
 *
 * <p>Key secondary metrics (reported by {@link com.datadoghq.profiler.stresstest.WhiteboxProfiler}):
 * <ul>
 *   <li>{@code wc_signals_skipped_sleeping} — increments when Approach 1 skips a sleeping thread</li>
 *   <li>{@code wc_signals_skipped_parked}   — increments when Approach 2 skips a parked thread</li>
 *   <li>{@code jfr_filesize_bytes}          — proxy for total samples recorded</li>
 * </ul>
 * With suppression on, skipped-signal counters should be roughly
 * {@code BACKGROUND_THREADS * measurement_seconds / wall_interval_ms} while throughput (ops/s)
 * should be noticeably higher due to fewer context-switches hitting the worker threads.
 */
@State(Scope.Benchmark)
public class SignalSuppressionBenchmark {

    private static final int BACKGROUND_THREADS = 200;

    /**
     * Compare suppression-on vs suppression-off.
     * The first param is the treatment; the second is the baseline.
     */
    @Param({"wall=1ms", "wall=1ms,wallprecheck=false,wallpark=false"})
    public String command;

    @Param({"false"})
    public String skipResults;

    private final List<Thread> backgroundThreads = new ArrayList<>(BACKGROUND_THREADS);
    private volatile boolean running;
    private CountDownLatch backgroundReady;

    @Setup(Level.Trial)
    public void setup() throws InterruptedException, IOException {
        running = true;
        backgroundReady = new CountDownLatch(BACKGROUND_THREADS);
        JavaProfiler profiler = JavaProfiler.getInstance();

        for (int i = 0; i < BACKGROUND_THREADS; i++) {
            Thread t = new Thread(() -> {
                // Register with the wall-clock thread filter so the timer loop considers this thread.
                profiler.addThread();
                backgroundReady.countDown();
                // Park until the trial ends — this is what we want the profiler to skip.
                while (running) {
                    LockSupport.park();
                }
            });
            t.setDaemon(true);
            t.setName("suppression-sleeper-" + i);
            t.start();
            backgroundThreads.add(t);
        }
        // Wait until all background threads have registered and parked.
        backgroundReady.await(10, TimeUnit.SECONDS);
    }

    @TearDown(Level.Trial)
    public void teardown() {
        running = false;
        for (Thread t : backgroundThreads) {
            t.interrupt();
        }
        backgroundThreads.clear();
    }

    private long doWork(long seed) {
        long result = seed;
        for (int i = 0; i < 100_000; i++) {
            result = (result * 1103515245L + 12345L) & 0x7fffffffL;
        }
        return result;
    }

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 1, warmups = 0)
    @Warmup(iterations = 2, time = 2)
    @Measurement(iterations = 5, time = 5)
    @Threads(8)
    @OutputTimeUnit(TimeUnit.SECONDS)
    public void activeThreadsWithSleepingBackground(Blackhole bh) {
        bh.consume(doWork(System.nanoTime()));
    }
}
