/*
 * Copyright 2026, Datadog, Inc.
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
import com.datadoghq.profiler.WallClockPrecheckBenchmarkHooks;
import java.nio.file.Files;
import java.nio.file.Path;
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
import org.openjdk.jmh.annotations.Warmup;

/**
 * Measures steady-state wall-clock timer overhead as an owned-block thread population grows.
 *
 * <p>The implementation separately records registry lookup work in the {@code
 * wc_precheck_registry_lookups} debug counter and bounds candidate visits to four times {@code
 * walltpt} per tick. This benchmark does not report that counter; it compares {@code
 * precheck=false} and {@code precheck=true} at each population to detect timer-loop throughput
 * regressions independently of one-time startup registration.
 */
@BenchmarkMode(Mode.Throughput)
@OutputTimeUnit(TimeUnit.MILLISECONDS)
@Fork(value = 1, warmups = 0, jvmArgsAppend = "-Xss256k")
@Warmup(iterations = 3, time = 2)
@Measurement(iterations = 5, time = 3)
@State(Scope.Benchmark)
public class WallClockPrecheckOverheadBenchmark {
  @Param({"false", "true"})
  public boolean precheck;

  @Param({"100", "500", "1000"})
  public int threadCount;

  private final List<Thread> workers = new ArrayList<>();
  private volatile boolean running;
  private JavaProfiler profiler;
  private Path recording;

  /** Creates the requested thread population before starting the profiler. */
  @Setup(Level.Trial)
  public void setup() throws Exception {
    running = true;
    CountDownLatch ready = new CountDownLatch(threadCount);
    CountDownLatch profilerStarted = new CountDownLatch(1);
    CountDownLatch armed = new CountDownLatch(threadCount);
    for (int i = 0; i < threadCount; ++i) {
      Thread worker =
          new Thread(
              () -> {
                ready.countDown();
                long token = 0;
                boolean armedReported = false;
                try {
                  profilerStarted.await();
                  token = WallClockPrecheckBenchmarkHooks.enterSleeping(profiler);
                  armed.countDown();
                  armedReported = true;
                  while (running) {
                    LockSupport.parkNanos(TimeUnit.SECONDS.toNanos(1));
                  }
                } catch (InterruptedException interrupted) {
                  Thread.currentThread().interrupt();
                } finally {
                  if (!armedReported) {
                    armed.countDown();
                  }
                  WallClockPrecheckBenchmarkHooks.exit(profiler, token);
                }
              },
              "wall-precheck-benchmark-" + i);
      worker.setDaemon(true);
      worker.start();
      workers.add(worker);
    }
    if (!ready.await(30, TimeUnit.SECONDS)) {
      throw new IllegalStateException("Timed out creating benchmark workers");
    }

    profiler = JavaProfiler.getInstance();
    recording = Files.createTempFile("wall-precheck-overhead-", ".jfr");
    profiler.execute(
        "start,wall=1ms,walltpt=16,filter=,wallprecheck="
            + precheck
            + ",jfr,file="
            + recording.toAbsolutePath());
    profilerStarted.countDown();
    if (!armed.await(30, TimeUnit.SECONDS)) {
      throw new IllegalStateException("Timed out arming benchmark workers");
    }
  }

  /** Stops profiling and releases every background worker. */
  @TearDown(Level.Trial)
  public void tearDown() throws Exception {
    running = false;
    for (Thread worker : workers) {
      LockSupport.unpark(worker);
    }
    for (Thread worker : workers) {
      worker.join(TimeUnit.SECONDS.toMillis(5));
    }
    workers.clear();
    if (profiler != null) {
      profiler.stop();
    }
    if (recording != null) {
      Files.deleteIfExists(recording);
    }
  }

  /** Provides stable foreground work whose throughput captures timer-loop interference. */
  @Benchmark
  public void foregroundWork() {
    org.openjdk.jmh.infra.Blackhole.consumeCPU(1_000);
  }
}
