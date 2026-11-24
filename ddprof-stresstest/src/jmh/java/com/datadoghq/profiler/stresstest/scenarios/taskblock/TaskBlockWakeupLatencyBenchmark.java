/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.stresstest.scenarios.taskblock;

import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.EMITTED;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.check;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.checkBetween;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.delta;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.TaskBlockBenchmarkHooks;
import com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.Recording;
import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Arrays;
import java.util.Locale;
import java.util.Map;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.LockSupport;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.BenchmarkMode;
import org.openjdk.jmh.annotations.CompilerControl;
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
import org.openjdk.jmh.infra.BenchmarkParams;
import org.openjdk.jmh.infra.IterationParams;
import org.openjdk.jmh.runner.IterationType;

/**
 * Measures wake-up latency: from the helper's wake action (a {@code nanoTime} stamp just before
 * unpark, notify or write) to the worker running user code again, including its exit-path capture.
 * For {@code objectWait} that also covers the helper's monitor exit and the worker's re-acquire.
 *
 * <p>An op is the gap plus the latency, so JMH's score would mostly show the gap. The benchmark
 * keeps measurement-iteration latencies itself and prints p50/p99/p99.9/max in the trial teardown.
 *
 * <p>The teardown fails unless {@code taskblock} emitted at least half of the ops and {@code wall}
 * none, so a gap under 1 ms fails. {@code socketRead} hooks are Linux-only; elsewhere its checks
 * are skipped.
 */
@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.MICROSECONDS)
@Fork(value = 1, warmups = 0)
@Warmup(iterations = 3, time = 2)
@Measurement(iterations = 5, time = 3)
@Threads(1)
@State(Scope.Benchmark)
public class TaskBlockWakeupLatencyBenchmark {
  @Param({"none", "wall", "taskblock"})
  public String config;

  @Param({"20", "100", "300"})
  public int stackDepth;

  @Param({"park", "objectWait", "socketRead"})
  public String source;

  /** Idle time before the wake-up; above the 1 ms emission threshold. */
  @Param({"1500"})
  public long gapMicros;

  /** Latency buffer capacity; later samples are counted, not stored. */
  private static final int MAX_SAMPLES = 1 << 18;

  /** Allowance for the in-flight op and for JMH or JVM threads that block once or twice. */
  private static final long SLACK = 16;

  private final AtomicReference<Throwable> helperFailure = new AtomicReference<>();
  private final Semaphore armed = new Semaphore(0);
  private final Object monitor = new Object();
  private final long[] latencies = new long[MAX_SAMPLES];
  private JavaProfiler profiler;
  private Recording recording;
  private Thread worker;
  private Thread helper;
  private ServerSocketChannel server;
  private SocketChannel client;
  private SocketChannel accepted;
  private ByteBuffer readBuffer;
  private ByteBuffer writeBuffer;
  private volatile boolean running;
  private volatile boolean woken;
  private volatile long wakeStamp;
  private boolean measuring;
  private int stored;
  private long measured;
  private long calls;
  private long owned;

  @Setup(Level.Trial)
  public void setup() throws Exception {
    profiler = TaskBlockBenchmarkSupport.loadProfiler();
    recording = Recording.start(profiler, config);
    worker = Thread.currentThread();
    if ("socketRead".equals(source)) {
      InetAddress loopback = InetAddress.getLoopbackAddress();
      server = ServerSocketChannel.open();
      server.bind(new InetSocketAddress(loopback, 0));
      client = SocketChannel.open(server.getLocalAddress());
      accepted = server.accept();
      readBuffer = ByteBuffer.allocateDirect(1);
      writeBuffer = ByteBuffer.allocateDirect(1);
    }
    running = true;
    helper = new Thread(this::help, "taskblock-wakeup-helper");
    helper.setDaemon(true);
    helper.start();
  }

  /** Keeps only the latencies of measurement iterations. */
  @Setup(Level.Iteration)
  public void startIteration(IterationParams iteration) {
    measuring = iteration.getType() == IterationType.MEASUREMENT;
  }

  /** Idles for the gap, then wakes; its trace context keeps its own blocks from emitting. */
  private void help() {
    TaskBlockBenchmarkSupport.excludeFromTaskBlock(recording.taskBlockActive() ? profiler : null);
    try {
      while (true) {
        armed.acquire();
        if (!running) {
          return;
        }
        TaskBlockPairedApiBenchmark.parkAtLeast(TimeUnit.MICROSECONDS.toNanos(gapMicros));
        wake();
      }
    } catch (Exception e) {
      if (running) {
        helperFailure.compareAndSet(null, e);
      }
    } finally {
      if (recording.taskBlockActive()) {
        profiler.clearTraceContext();
      }
    }
  }

  private void wake() throws IOException {
    switch (source) {
      case "park":
        wakeStamp = System.nanoTime();
        woken = true;
        LockSupport.unpark(worker);
        break;
      case "objectWait":
        synchronized (monitor) {
          wakeStamp = System.nanoTime();
          woken = true;
          monitor.notify();
        }
        break;
      default:
        writeBuffer.clear();
        writeBuffer.put((byte) 1);
        writeBuffer.flip();
        wakeStamp = System.nanoTime();
        accepted.write(writeBuffer);
    }
  }

  /** Reports the latency percentiles and checks emission as {@code config} implies. */
  @TearDown(Level.Trial)
  public void tearDown(BenchmarkParams params) throws Exception {
    running = false;
    armed.release();
    // Closing first unblocks a helper stuck in a socket write.
    closeQuietly(client);
    closeQuietly(accepted);
    closeQuietly(server);
    if (helper != null) {
      helper.join(TimeUnit.SECONDS.toMillis(5));
      check(!helper.isAlive(), "Helper did not stop");
    }
    String benchmark = TaskBlockBenchmarkSupport.benchmarkName(params);
    Map<String, Long> deltas = recording.stop(benchmark);
    printLatencies(benchmark);
    check(helperFailure.get() == null, "Helper failed: " + helperFailure.get());
    check(calls > 0, benchmark + " made no calls");
    if (TaskBlockBenchmarkSupport.NONE.equals(config)) {
      return;
    }
    long emitted = delta(deltas, EMITTED);
    if (!recording.taskBlockActive()) {
      check(emitted == 0, benchmark + " emitted TaskBlock events with TaskBlock off");
      return;
    }
    if ("socketRead".equals(source) && !TaskBlockBenchmarkSupport.isLinux()) {
      System.out.println("[taskblock-bench] native I/O hooks are Linux-only; checks skipped");
      return;
    }
    if ("park".equals(source)) {
      // parkEnter0 can decline (no ProfiledThread, JVM-internal thread), so allow 10% unowned.
      check(owned * 10 >= calls * 9 && owned <= calls, "owned " + owned + " of " + calls);
    }
    checkBetween("emitted", emitted, calls / 2, calls + SLACK);
  }

  private void printLatencies(String benchmark) {
    long[] sorted = Arrays.copyOf(latencies, stored);
    Arrays.sort(sorted);
    System.out.printf(
        Locale.ROOT,
        "[taskblock-bench] latency benchmark=%s config=%s source=%s stackDepth=%d gapMicros=%d"
            + " samples=%d dropped=%d p50Us=%.1f p99Us=%.1f p999Us=%.1f maxUs=%.1f%n",
        benchmark,
        config,
        source,
        stackDepth,
        gapMicros,
        stored,
        measured - stored,
        percentile(sorted, 0.50),
        percentile(sorted, 0.99),
        percentile(sorted, 0.999),
        percentile(sorted, 1.0));
  }

  /** Nearest-rank percentile of ascending {@code sorted} nanoseconds, in microseconds. */
  private static double percentile(long[] sorted, double fraction) {
    if (sorted.length == 0) {
      return Double.NaN;
    }
    int rank = (int) Math.ceil(fraction * sorted.length);
    return sorted[Math.max(rank, 1) - 1] / 1e3;
  }

  /** One op: build the stack, block and record the latency. */
  @Benchmark
  public int wakeup() throws Exception {
    return descend(stackDepth);
  }

  /** Recurses, uninlined, so the block happens under {@code depth} physical frames. */
  @CompilerControl(CompilerControl.Mode.DONT_INLINE)
  private int descend(int depth) throws Exception {
    if (depth == 0) {
      block();
      return 0;
    }
    return descend(depth - 1) + 1;
  }

  private void block() throws Exception {
    woken = false;
    armed.release();
    switch (source) {
      case "park":
        boolean entered = TaskBlockBenchmarkHooks.parkEnter(profiler);
        while (!woken) {
          LockSupport.park();
        }
        if (entered) {
          TaskBlockBenchmarkHooks.parkExit(profiler);
          owned++;
        }
        break;
      case "objectWait":
        synchronized (monitor) {
          while (!woken) {
            monitor.wait();
          }
        }
        break;
      default:
        readBuffer.clear();
        check(client.read(readBuffer) == 1, "Helper closed the connection");
    }
    long latency = System.nanoTime() - wakeStamp;
    calls++;
    if (measuring) {
      if (stored < MAX_SAMPLES) {
        latencies[stored++] = latency;
      }
      measured++;
    }
  }

  private static void closeQuietly(AutoCloseable closeable) {
    if (closeable == null) {
      return;
    }
    try {
      closeable.close();
    } catch (Exception ignored) {
    }
  }
}
