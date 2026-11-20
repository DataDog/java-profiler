/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.*;

import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.LockSupport;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

/** Failure-path regressions for worker ownership, independent of Netty/JNI availability. */
public class TimedNativeWorkerTest {
  private Path directory;

  /** Retains child-process evidence, including successful forced termination, after the test. */
  @BeforeEach
  public void retainProcessLogs() throws Exception {
    directory =
        Files.createTempDirectory(
            Files.createDirectories(Paths.get("build", "netty-worker")), "worker-");
  }

  /** Success must complete all five waits and leave no owned worker alive. */
  @Test
  public void successCompletesEveryWait() throws Exception {
    AtomicInteger calls = new AtomicInteger();
    AtomicReference<Thread> worker = new AtomicReference<>();
    TimedNativeWorker.run(
        "timed-worker-success",
        5,
        () -> {
          worker.set(Thread.currentThread());
          calls.incrementAndGet();
        },
        TimeUnit.SECONDS.toNanos(5),
        TimeUnit.SECONDS.toNanos(5));
    assertEquals(5, calls.get());
    assertNotNull(worker.get());
    assertFalse(worker.get().isDaemon());
    assertFalse(worker.get().isAlive());
  }

  /** A failure reported by the normally joined worker must remain the assertion's cause. */
  @Test
  public void workerFailureIsRetained() {
    IllegalStateException failure = new IllegalStateException("worker failed");
    AssertionError result =
        assertThrows(
            AssertionError.class,
            () ->
                TimedNativeWorker.run(
                    "timed-worker-failure",
                    5,
                    () -> {
                      throw failure;
                    },
                    TimeUnit.SECONDS.toNanos(5),
                    TimeUnit.SECONDS.toNanos(5)));
    assertSame(failure, result.getCause());
  }

  /** Timeout is primary; cancellation joins the interrupted worker and retains its failure. */
  @Test
  public void timeoutCancelsAndJoinsWorker() {
    AtomicReference<Thread> worker = new AtomicReference<>();
    AssertionError result =
        assertThrows(
            AssertionError.class,
            () ->
                TimedNativeWorker.run(
                    "timed-worker-timeout",
                    5,
                    () -> {
                      worker.set(Thread.currentThread());
                      new CountDownLatch(1).await();
                    },
                    TimeUnit.SECONDS.toNanos(1),
                    TimeUnit.SECONDS.toNanos(5)));
    assertTrue(result.getMessage().contains("bounded deadline"));
    assertNotNull(worker.get());
    assertFalse(worker.get().isAlive());
    assertEquals(1, result.getSuppressed().length);
    assertTrue(result.getSuppressed()[0] instanceof InterruptedException);
  }

  /** An interrupted owner still joins its worker and restores its interrupt flag. */
  @Test
  public void interruptedJoinStillOwnsCleanup() throws Exception {
    CountDownLatch entered = new CountDownLatch(1);
    AtomicReference<Thread> worker = new AtomicReference<>();
    AtomicReference<Throwable> failure = new AtomicReference<>();
    AtomicBoolean restored = new AtomicBoolean();
    Thread owner =
        new Thread(
            () -> {
              try {
                TimedNativeWorker.run(
                    "timed-worker-interrupted",
                    5,
                    () -> {
                      worker.set(Thread.currentThread());
                      entered.countDown();
                      new CountDownLatch(1).await();
                    },
                    TimeUnit.SECONDS.toNanos(5),
                    TimeUnit.SECONDS.toNanos(5));
              } catch (Throwable error) {
                failure.set(error);
              } finally {
                restored.set(Thread.currentThread().isInterrupted());
              }
            },
            "timed-worker-owner");
    owner.start();
    try {
      assertTrue(entered.await(5, TimeUnit.SECONDS));
    } finally {
      owner.interrupt();
      owner.join(12_000);
    }
    assertFalse(owner.isAlive());
    assertTrue(failure.get() instanceof InterruptedException);
    assertTrue(restored.get());
    assertNotNull(worker.get());
    assertFalse(worker.get().isAlive());
    assertEquals(1, failure.get().getSuppressed().length);
    assertTrue(failure.get().getSuppressed()[0] instanceof InterruptedException);
  }

  /** A cooperative child exits normally; no forced termination should be needed. */
  @Test
  public void outerJvmAllowsSuccess() throws Exception {
    Path log = directory.resolve("success.log");
    assertEquals(0, NettyEpollJvm.run(childCommand("success"), log, TimeUnit.SECONDS.toNanos(10)));
    assertTrue(read(log).contains("WORKER_SUCCESS"));
  }

  /** A deliberately uncooperative Java worker tests process containment, not JNI termination. */
  @Test
  public void survivingWorkerRequiresOuterJvmTermination() throws Exception {
    Path log = directory.resolve("survivor.log");
    AssertionError timeout =
        assertThrows(
            AssertionError.class,
            () -> NettyEpollJvm.run(childCommand("survivor"), log, TimeUnit.SECONDS.toNanos(10)));
    assertTrue(timeout.getMessage().contains("outer deadline"));
    assertEquals(0, timeout.getSuppressed().length, "forced termination/reap must succeed");
    String output = read(log);
    assertTrue(output.contains("WORKER_ENTERED"), output);
    assertTrue(output.contains("WORKER_SURVIVED"), output);
    assertTrue(output.contains("PRIMARY_AND_CLEANUP_RETAINED"), output);
  }

  /** A real nonreturning JNI call must be killed and reaped by the independent JVM owner. */
  @Test
  public void survivingJniWorkerRequiresOuterJvmTermination() throws Exception {
    Path log = directory.resolve("jni-survivor.log");
    AssertionError timeout =
        assertThrows(
            AssertionError.class,
            () ->
                NettyEpollJvm.run(childCommand("jni-survivor"), log, TimeUnit.SECONDS.toNanos(10)));
    assertTrue(timeout.getMessage().contains("outer deadline"));
    assertEquals(0, timeout.getSuppressed().length, "forced JNI termination/reap must succeed");
    String output = read(log);
    assertTrue(output.contains("JNI_WORKER_ENTERED"), output);
    assertTrue(output.contains("WORKER_SURVIVED"), output);
    assertTrue(output.contains("PRIMARY_AND_CLEANUP_RETAINED"), output);
  }

  /** Uses the current test JVM and test-classes directory; no external artifact is acquired. */
  private static java.util.List<String> childCommand(String mode) throws Exception {
    String classes =
        Paths.get(
                TimedNativeWorkerTest.class
                    .getProtectionDomain()
                    .getCodeSource()
                    .getLocation()
                    .toURI())
            .toString();
    java.util.List<String> command = new java.util.ArrayList<>();
    command.add(Paths.get(System.getProperty("java.home"), "bin", "java").toString());
    command.addAll(NettyEpollJvm.heapLayoutArgs());
    command.addAll(
        Arrays.asList(
            "-Djava.library.path=" + System.getProperty("java.library.path"),
            "-cp",
            classes,
            Child.class.getName(),
            mode));
    return command;
  }

  private static String read(Path log) throws Exception {
    return new String(Files.readAllBytes(log), StandardCharsets.UTF_8);
  }

  /** Isolated Java/JNI survivor controls; no profiler, shell, or descendant process is started. */
  public static final class Child {
    private Child() {}

    private static native void waitForever();

    /** Leaves a survivor non-daemon so only the outer JVM owner can contain this control. */
    public static void main(String[] args) throws Exception {
      System.out.println(
          "WORKER_CHILD_VM "
              + java.lang.management.ManagementFactory.getRuntimeMXBean().getName()
              + " "
              + System.getProperty("java.runtime.version"));
      if ("success".equals(args[0])) {
        AtomicInteger calls = new AtomicInteger();
        TimedNativeWorker.run(
            "child-success",
            5,
            calls::incrementAndGet,
            TimeUnit.SECONDS.toNanos(2),
            TimeUnit.SECONDS.toNanos(2));
        if (calls.get() != 5) {
          throw new AssertionError("missing waits");
        }
        System.out.println("WORKER_SUCCESS");
        return;
      }
      boolean nativeSurvivor = "jni-survivor".equals(args[0]);
      if (nativeSurvivor) {
        System.loadLibrary("ddproftest");
      }
      AtomicReference<Thread> worker = new AtomicReference<>();
      try {
        TimedNativeWorker.run(
            "child-survivor",
            5,
            () -> {
              worker.set(Thread.currentThread());
              System.out.println("WORKER_ENTERED");
              if (nativeSurvivor) {
                waitForever();
              }
              while (true) {
                Thread.interrupted();
                LockSupport.parkNanos(TimeUnit.MILLISECONDS.toNanos(10));
              }
            },
            TimeUnit.SECONDS.toNanos(1),
            TimeUnit.SECONDS.toNanos(1));
        throw new AssertionError("survivor was accepted");
      } catch (AssertionError failure) {
        if (!failure.getMessage().contains("bounded deadline")
            || failure.getSuppressed().length != 1
            || !failure.getSuppressed()[0].getMessage().contains("did not terminate")
            || worker.get() == null
            || !worker.get().isAlive()) {
          throw failure;
        }
        System.out.println("PRIMARY_AND_CLEANUP_RETAINED");
        System.out.println("WORKER_SURVIVED");
      }
    }
  }
}
