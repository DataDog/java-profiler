/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.lifecycle;

import static org.junit.jupiter.api.Assertions.*;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.Platform;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

/**
 * Stop/start stress: many restart cycles of rotating profiler modes (wall and cpu, liveness,
 * nativemem) while worker threads allocate, record trace roots and churn short-lived threads. The
 * pass criterion is "no crash, no hang, no worker exception, and the profiler can still be started
 * and stopped at the end".
 *
 * <p>The run lasts {@value #DEFAULT_SECONDS} seconds. Set the environment variable {@code
 * RESTART_STRESS_SECONDS} (1 to {@value #MAX_SECONDS}) for a longer soak.
 */
public class RestartStressTest {

  private static final long DEFAULT_SECONDS = 15;
  private static final long MAX_SECONDS = 400;
  // A sanity floor, not a throughput target: slow configs complete far fewer cycles.
  private static final int MIN_CYCLES = 3;
  // Retries for the documented-retryable drain outcomes of start() and stop(), 20 ms apart.
  // Under this test's load a drain can take longer than the shared helper's 100 ms.
  private static final int RETRIES = 200;

  // cpu=... selects CTimer when timer_create works (PerfEvents, the fallback, is not
  // restartable and does not belong in a restart stress).
  private static final String[] COMMON_MODES = {
    "start,wall=1ms,cpu=10ms,jfr,file=",
    "start,cpu=10ms,jfr,file=",
    "start,memory=256:L,jfr,file=",
    "start,wall=5ms,memory=256:L,jfr,file=",
  };
  // GOT patching conflicts with the ASan/TSan interceptors; the sibling tests skip it there.
  private static final String NATIVEMEM_MODE = "start,nativemem=0,jfr,file=";

  private final AtomicBoolean running = new AtomicBoolean();
  private final Queue<Throwable> workerFailures = new ConcurrentLinkedQueue<>();
  // Set once the assumptions passed: a skipped test must not touch the profiler.
  private volatile boolean active;

  @AfterEach
  public void stopIfRunning() throws Exception {
    running.set(false);
    if (!active) {
      return;
    }
    JavaProfiler profiler = JavaProfiler.getInstance();
    if (profiler.getStatus().contains("Running          : true")) {
      stopRetrying(profiler);
    }
  }

  @Timeout(600)
  @Test
  public void restartUnderLoad() throws Exception {
    Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11), "wall-clock requires Java 11+");
    Assumptions.assumeTrue(!Platform.isJ9(), "J9 has a different JVMTI implementation");
    Assumptions.assumeTrue(!Platform.isZing(), "Zing forces cstack=no");
    active = true;

    List<String> modes = new ArrayList<>();
    for (String mode : COMMON_MODES) {
      modes.add(mode);
    }
    boolean sanitizer =
        System.getenv("ASAN_OPTIONS") != null
            || System.getenv("TSAN_OPTIONS") != null
            || System.getenv("UBSAN_OPTIONS") != null;
    if (Platform.isLinux() && !sanitizer) {
      modes.add(NATIVEMEM_MODE);
    }

    long budgetNanos = TimeUnit.SECONDS.toNanos(budgetSeconds());
    int workers = 4;

    Path recordings = Files.createTempDirectory("restart-stress");
    JavaProfiler profiler = JavaProfiler.getInstance();

    AtomicLong ops = new AtomicLong();
    running.set(true);
    List<Thread> threads = new ArrayList<>();
    for (int i = 0; i < workers; i++) {
      final int id = i;
      Thread t = new Thread(() -> worker(profiler, id, ops), "restart-stress-" + i);
      t.setDaemon(true);
      threads.add(t);
      t.start();
    }

    long deadline = System.nanoTime() + budgetNanos;
    int cycles = 0;
    try {
      while (System.nanoTime() < deadline && workerFailures.isEmpty()) {
        String mode = modes.get(cycles % modes.size());
        Path jfr = Files.createTempFile(recordings, "stress_" + cycles + "_", ".jfr");
        startRetrying(profiler, mode + jfr.toAbsolutePath());
        try {
          Thread.sleep(20 + ThreadLocalRandom.current().nextInt(80));
          if (cycles % 7 == 0) {
            System.gc();
          }
        } finally {
          stopRetrying(profiler);
        }
        Files.deleteIfExists(jfr);
        cycles++;
        if (cycles % 25 == 0) {
          System.out.println("[RestartStress] cycles=" + cycles + " ops=" + ops.get());
        }
      }
    } finally {
      running.set(false);
      long joinDeadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(10);
      for (Thread t : threads) {
        long remainingMs = TimeUnit.NANOSECONDS.toMillis(joinDeadline - System.nanoTime());
        t.join(Math.max(1, remainingMs));
      }
      deleteQuietly(recordings);
    }

    System.out.println(
        "[RestartStress] done: cycles="
            + cycles
            + " ops="
            + ops.get()
            + " workerFailures="
            + workerFailures.size());
    for (Throwable failure : workerFailures) {
      failure.printStackTrace();
    }
    try {
      for (Thread t : threads) {
        assertFalse(t.isAlive(), "worker did not finish: " + t.getName());
      }
      assertTrue(workerFailures.isEmpty(), "worker threads failed: " + workerFailures);
      assertTrue(cycles >= MIN_CYCLES, "too few restart cycles completed: " + cycles);
      assertFalse(
          profiler.getStatus().contains("Running          : true"),
          "profiler must not be running after the last stop()");

      // Still restartable: an errored or wedged profiler would fail here.
      Path jfr = Files.createTempFile("stress_final_", ".jfr");
      try {
        startRetrying(profiler, modes.get(0) + jfr.toAbsolutePath());
        stopRetrying(profiler);
      } finally {
        Files.deleteIfExists(jfr);
      }
    } finally {
      workerFailures.clear();
    }
  }

  private static long budgetSeconds() {
    String value = System.getenv("RESTART_STRESS_SECONDS");
    if (value != null) {
      try {
        return Math.max(1, Math.min(MAX_SECONDS, Long.parseLong(value.trim())));
      } catch (NumberFormatException ignored) {
        // fall back to the default
      }
    }
    return DEFAULT_SECONDS;
  }

  /** start() reports a drain it could not complete as "retry start()"; any other error is real. */
  private static void startRetrying(JavaProfiler profiler, String command)
      throws IOException, InterruptedException {
    IllegalStateException last = null;
    for (int attempt = 0; attempt < RETRIES; attempt++) {
      try {
        profiler.execute(command);
        return;
      } catch (IllegalStateException e) {
        String msg = e.getMessage();
        if (msg == null || !msg.contains("retry start()")) {
          throw e;
        }
        last = e;
        Thread.sleep(20);
      }
    }
    throw new IllegalStateException("start() kept asking for a retry for 4 s", last);
  }

  /**
   * "retry stop()" means teardown was skipped and stop() is idempotent. "the profiler is stopped"
   * means teardown finished and only the hook drain timed out: already stopped.
   */
  private static void stopRetrying(JavaProfiler profiler) throws InterruptedException {
    IllegalStateException last = null;
    for (int attempt = 0; attempt < RETRIES; attempt++) {
      try {
        profiler.stop();
        return;
      } catch (IllegalStateException e) {
        String msg = e.getMessage();
        if (msg != null && msg.contains("the profiler is stopped")) {
          return;
        }
        if (msg == null || !msg.contains("retry stop()")) {
          throw e;
        }
        last = e;
        Thread.sleep(20);
      }
    }
    throw new IllegalStateException("stop() kept asking for a retry for 4 s", last);
  }

  private static void deleteQuietly(Path dir) {
    try (DirectoryStream<Path> files = Files.newDirectoryStream(dir)) {
      for (Path file : files) {
        Files.deleteIfExists(file);
      }
      Files.deleteIfExists(dir);
    } catch (IOException ignored) {
      // scratch files only
    }
  }

  private void worker(JavaProfiler profiler, int id, AtomicLong ops) {
    try {
      List<byte[]> retained = new ArrayList<>();
      long n = 0;
      while (running.get()) {
        ThreadLocalRandom rnd = ThreadLocalRandom.current();
        retained.add(new byte[256 + rnd.nextInt(4096)]);
        if (retained.size() > 2000) {
          retained.subList(0, 1000).clear();
        }
        if ((n & 127) == 0) {
          ByteBuffer direct = ByteBuffer.allocateDirect(512 + rnd.nextInt(3584));
          direct.put(0, (byte) 1);
        }
        if ((n & 31) == 0) {
          profiler.recordTraceRoot(n, "stress-endpoint-" + (n % 8), "op", 100);
        }
        if ((n & 255) == 0) {
          // Short-lived Java thread: registration and exit paths under restart.
          Thread churn =
              new Thread(
                  () -> {
                    long x = 0;
                    for (int i = 0; i < 20_000; i++) {
                      x += i * 31L;
                    }
                    if (x == 42) {
                      System.out.print("");
                    }
                  },
                  "restart-stress-churn-" + id);
          churn.start();
          churn.join(1000);
        }
        n++;
        ops.incrementAndGet();
        if ((n & 31) == 0) {
          Thread.sleep(1);
        }
      }
    } catch (Throwable t) {
      workerFailures.add(t);
    }
  }
}
