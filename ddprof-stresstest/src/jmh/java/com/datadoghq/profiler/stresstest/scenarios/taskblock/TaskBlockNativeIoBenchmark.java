/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.stresstest.scenarios.taskblock;

import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.EMITTED;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.NATIVE_IO_HOOKS_PATCHED;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.NONE;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.SKIPPED_TRACE_CONTEXT;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.TOO_SHORT;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.check;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.checkBetween;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.delta;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.Recording;
import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Map;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;
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
import org.openjdk.jmh.infra.BenchmarkParams;

/**
 * Measures the native I/O TaskBlock hooks (Linux GOT hooks on the JDK's libnio/libnet {@code read},
 * {@code write}, {@code poll}, ...) on the two cases {@code NativeSocketIoBenchmark} leaves out.
 *
 * <ul>
 *   <li>{@code nonBlockingReadEmpty}: a non-blocking {@code SocketChannel.read} with no data, which
 *       fails with {@code EAGAIN}. Nothing blocks, so this is the pure per-call hook cost.
 *   <li>{@code blockingReadEmitting}: a one-byte request whose reply a responder thread sends after
 *       {@code replyDelayMicros}. The blocked {@code read} is above the 1 ms threshold and emits
 *       one event per call.
 * </ul>
 *
 * <p>Baseline: {@code config=none}, which never loads the library. {@code config=wall} loads it and
 * samples wall-clock without TaskBlock, so the hooks are not installed; {@code config=taskblock}
 * installs them. On Linux the trial teardown fails unless the hooks were patched and the blocking
 * read emitted; the hooks do not exist on other platforms.
 */
@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.NANOSECONDS)
@Fork(value = 1, warmups = 0)
@Warmup(iterations = 3, time = 2)
@Measurement(iterations = 5, time = 3)
@Threads(1)
@State(Scope.Benchmark)
public class TaskBlockNativeIoBenchmark {
  @Param({"none", "wall", "taskblock"})
  public String config;

  /** Delay before the responder replies; above the 1 ms emission threshold. */
  @Param({"1200"})
  public long replyDelayMicros;

  /** Allowance for the in-flight call and for JMH or JVM threads that block once or twice. */
  private static final long SLACK = 16;

  private final AtomicReference<Throwable> responderFailure = new AtomicReference<>();
  private JavaProfiler profiler;
  private Recording recording;
  private ServerSocketChannel server;
  private SocketChannel client;
  private SocketChannel accepted;
  private Thread responder;
  private volatile boolean running;
  private ByteBuffer one;
  private long calls;

  @Setup(Level.Trial)
  public void setup(BenchmarkParams params) throws Exception {
    profiler = NONE.equals(config) ? null : TaskBlockBenchmarkSupport.loadProfiler();
    recording = Recording.start(profiler, config);
    InetAddress loopback = InetAddress.getLoopbackAddress();
    server = ServerSocketChannel.open();
    server.bind(new InetSocketAddress(loopback, 0));
    client = SocketChannel.open(server.getLocalAddress());
    accepted = server.accept();
    one = ByteBuffer.allocateDirect(1);
    if ("nonBlockingReadEmpty".equals(TaskBlockBenchmarkSupport.benchmarkName(params))) {
      client.configureBlocking(false);
      return;
    }
    running = true;
    responder = new Thread(this::respond, "taskblock-io-responder");
    responder.setDaemon(true);
    responder.start();
  }

  /**
   * Echoes every request byte after {@code replyDelayMicros}. It carries a trace context so its own
   * blocking read is ineligible and cannot satisfy the client's emission checks.
   */
  private void respond() {
    TaskBlockBenchmarkSupport.excludeFromTaskBlock(recording.taskBlockActive() ? profiler : null);
    ByteBuffer buffer = ByteBuffer.allocateDirect(1);
    try {
      while (running) {
        buffer.clear();
        if (accepted.read(buffer) < 0) {
          return;
        }
        TaskBlockPairedApiBenchmark.parkAtLeast(TimeUnit.MICROSECONDS.toNanos(replyDelayMicros));
        buffer.flip();
        accepted.write(buffer);
      }
    } catch (IOException e) {
      if (running) {
        responderFailure.compareAndSet(null, e);
      }
    }
  }

  /** Checks that the hooks were installed and emitted as {@code config} implies. */
  @TearDown(Level.Trial)
  public void tearDown(BenchmarkParams params) throws Exception {
    running = false;
    closeQuietly(client);
    closeQuietly(accepted);
    closeQuietly(server);
    if (responder != null) {
      responder.join(TimeUnit.SECONDS.toMillis(5));
    }
    String benchmark = TaskBlockBenchmarkSupport.benchmarkName(params);
    Map<String, Long> deltas = recording.stop(benchmark);
    System.out.printf("[taskblock-bench] benchmark=%s calls=%d%n", benchmark, calls);
    check(responderFailure.get() == null, "Responder failed: " + responderFailure.get());
    check(calls > 0, benchmark + " made no calls");
    if (NONE.equals(config)) {
      return;
    }
    long emitted = delta(deltas, EMITTED);
    if (!recording.taskBlockActive()) {
      check(
          emitted == 0 && delta(deltas, TOO_SHORT) == 0,
          benchmark + " reached TaskBlock with TaskBlock off");
      return;
    }
    if (!TaskBlockBenchmarkSupport.isLinux()) {
      System.out.println("[taskblock-bench] native I/O hooks are Linux-only; checks skipped");
      return;
    }
    // Absolute, not a delta: the hooks are patched during start, before the baseline snapshot.
    check(
        delta(profiler.getDebugCounters(), NATIVE_IO_HOOKS_PATCHED) > 0,
        "Native I/O hooks were not patched");
    if ("nonBlockingReadEmpty".equals(benchmark)) {
      // Every hooked EAGAIN read is counted too short; no other thread reads here.
      checkBetween("tooShort", delta(deltas, TOO_SHORT), calls / 2, calls + SLACK);
    } else if ("blockingReadEmitting".equals(benchmark)) {
      // Only the client's blocking read emits: the responder is excluded by its trace context.
      checkBetween("emitted", emitted, calls / 2, calls + SLACK);
      check(
          delta(deltas, SKIPPED_TRACE_CONTEXT) > 0,
          "The responder's blocking reads never reached the hooks");
    }
  }

  @Benchmark
  public int nonBlockingReadEmpty() throws IOException {
    one.clear();
    int read = client.read(one);
    calls++;
    return read;
  }

  @Benchmark
  public int blockingReadEmitting() throws IOException {
    one.clear();
    one.put((byte) 1);
    one.flip();
    client.write(one);
    one.clear();
    int read = client.read(one);
    check(read == 1, "Responder closed the connection");
    calls++;
    return read;
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
