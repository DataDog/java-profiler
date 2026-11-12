/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.chaos;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.JavaProfiler;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.InvocationTargetException;
import java.net.URL;
import java.net.URLClassLoader;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.time.Duration;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.FutureTask;
import java.util.concurrent.ThreadFactory;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import javax.tools.ToolProvider;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;
import org.junit.jupiter.api.io.TempDir;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

/** Runs the real chaos workload against native recordings without tracer instrumentation. */
@Timeout(15)
class ParkBlockChurnAntagonistTest {
  private JavaProfiler profiler;
  private Path recording;
  private boolean started;

  @BeforeEach
  void setUp() throws Exception {
    Assumptions.assumeFalse(
        System.getProperty("java.vm.name", "").contains("J9"),
        "Unfiltered owned-block prechecks are unsupported by the J9 wall engine");
    profiler = JavaProfiler.getInstance();
    recording = Files.createTempFile("chaos-owned-block-", ".jfr");
  }

  @AfterEach
  void tearDown() throws Exception {
    try {
      if (started) profiler.stop();
    } finally {
      if (recording != null) {
        if (Boolean.getBoolean("ddprof_test.keep_jfrs")) {
          System.out.println("===> control recording: " + recording.toAbsolutePath());
        } else {
          Files.deleteIfExists(recording);
        }
      }
    }
  }

  /** The native hooks and timer must provide coverage without any Java agent attached. */
  @Test
  void explicitHooksExerciseUnfilteredPrechecks() throws Exception {
    ParkBlockChurnAntagonist workload = runWorkload("wall=1ms,filter=,wallprecheck=true");
    workload.verifyPrecheckCoverage();
  }

  /** The application loader cannot link profiler classes stored in the agent's private loader. */
  @Test
  void privateAgentLoaderSuppliesHooksAndCounters(@TempDir Path directory) throws Exception {
    try (URLClassLoader loader = isolatedAgentLoader(directory, true)) {
      assertThrows(
          ClassNotFoundException.class,
          () -> loader.loadClass("com.datadoghq.profiler.JavaProfiler"));
      profiler.execute("start,wall=1ms,filter=,wallprecheck=true,jfr,file=" + recording);
      started = true;
      Class<?> type = loader.loadClass(ParkBlockChurnAntagonist.class.getName());
      Object workload = type.getConstructor(int.class, int.class).newInstance(12, 20);
      type.getMethod("start").invoke(workload);
      try {
        Thread.sleep(1000);
      } finally {
        type.getMethod("stopGracefully", Duration.class).invoke(workload, Duration.ofSeconds(5));
      }
      type.getMethod("verifyPrecheckCoverage").invoke(workload);
    }
  }

  /** An uninitialized agent must fail before launching any workers. */
  @Test
  void unavailableAgentLoaderFailsStartup(@TempDir Path directory) throws Exception {
    try (URLClassLoader loader = isolatedAgentLoader(directory, false)) {
      Class<?> type = loader.loadClass(ParkBlockChurnAntagonist.class.getName());
      Object workload = type.getConstructor().newInstance();
      InvocationTargetException failure =
          assertThrows(
              InvocationTargetException.class, () -> type.getMethod("start").invoke(workload));
      assertTrue(failure.getCause() instanceof IllegalStateException, failure.toString());
      assertTrue(
          failure.getCause().getCause() instanceof ClassNotFoundException, failure.toString());
    }
  }

  /** Models shared classdata visibility without putting JavaProfiler on the application path. */
  private URLClassLoader isolatedAgentLoader(Path directory, boolean initialized) throws Exception {
    Path source = directory.resolve("datadog/trace/bootstrap/Agent.java");
    Files.createDirectories(source.getParent());
    Files.write(
        source,
        ("package datadog.trace.bootstrap; public class Agent {"
                + "private static ClassLoader AGENT_CLASSLOADER; }")
            .getBytes(StandardCharsets.UTF_8));
    int result = ToolProvider.getSystemJavaCompiler().run(null, null, null, source.toString());
    org.junit.jupiter.api.Assertions.assertEquals(0, result, "Agent loader fixture compilation");
    URLClassLoader loader =
        new URLClassLoader(new URL[] {directory.toUri().toURL()}, getClass().getClassLoader()) {
          @Override
          protected Class<?> loadClass(String name, boolean resolve) throws ClassNotFoundException {
            if (name.equals("com.datadoghq.profiler.JavaProfiler")) {
              throw new ClassNotFoundException(name);
            }
            if (name.equals(ParkBlockChurnAntagonist.class.getName())
                || name.equals(Antagonist.class.getName())) {
              Class<?> type = findLoadedClass(name);
              if (type == null) {
                String resource = name.replace('.', '/') + ".class";
                try (InputStream input = getParent().getResourceAsStream(resource)) {
                  if (input == null) throw new ClassNotFoundException(name);
                  ByteArrayOutputStream output = new ByteArrayOutputStream();
                  byte[] buffer = new byte[4096];
                  for (int count; (count = input.read(buffer)) != -1; ) {
                    output.write(buffer, 0, count);
                  }
                  byte[] bytes = output.toByteArray();
                  type = defineClass(name, bytes, 0, bytes.length);
                } catch (IOException e) {
                  throw new ClassNotFoundException(name, e);
                }
              }
              if (resolve) resolveClass(type);
              return type;
            }
            return super.loadClass(name, resolve);
          }
        };
    if (initialized) {
      java.lang.reflect.Field field =
          loader.loadClass("datadog.trace.bootstrap.Agent").getDeclaredField("AGENT_CLASSLOADER");
      field.setAccessible(true);
      field.set(null, JavaProfiler.class.getClassLoader());
    }
    return loader;
  }

  /** Calling hooks alone must not make disabled suppression appear to be covered. */
  @ParameterizedTest
  @ValueSource(
      strings = {"wall=1ms,filter=,wallprecheck=false", "wall=1ms,filter=0,wallprecheck=false"})
  void disabledPrechecksCannotPassCoverage(String command) throws Exception {
    ParkBlockChurnAntagonist workload = runWorkload(command);
    IllegalStateException failure =
        assertThrows(IllegalStateException.class, workload::verifyPrecheckCoverage);
    if (command.contains("filter=0")) {
      // Context-filtered recordings arm the hooks even with prechecks off.
      // Require rejection on the missing timer activity, beyond hook invocation.
      assertTrue(
          failure.getMessage().contains("wc_precheck_registry_lookups"), failure.getMessage());
    }
  }

  /** Shutdown cannot return while an independently gated later worker is still alive. */
  @Test
  void shutdownWaitsForEveryActiveBatchWorker() throws Exception {
    GatedBatch batch = new GatedBatch();
    ParkBlockChurnAntagonist workload = new ParkBlockChurnAntagonist(2, 20, batch);
    FutureTask<Void> shutdown =
        new FutureTask<>(
            () -> {
              workload.stopGracefully(Duration.ofSeconds(8));
              return null;
            });
    Thread stopper = new Thread(shutdown, "shutdown-batch-stopper");
    workload.start();
    try {
      assertTrue(batch.started.await(2, TimeUnit.SECONDS), "Batch workers did not start");
      stopper.start();
      awaitStopPending(stopper);
      assertThrows(
          TimeoutException.class,
          () -> shutdown.get(1200, TimeUnit.MILLISECONDS),
          "Shutdown completed with both workers held");
      batch.releaseFirst.countDown();
      joinStopped(batch.workers.get(0));
      assertTrue(batch.workers.get(1).isAlive(), "Second worker was not independently held");
      assertThrows(
          TimeoutException.class,
          () -> shutdown.get(1200, TimeUnit.MILLISECONDS),
          "Shutdown completed after only the first worker terminated");
      batch.releaseSecond.countDown();
      shutdown.get(2, TimeUnit.SECONDS);
      assertTrue(batch.workers.size() == 2, "Shutdown spawned another batch");
      for (Thread worker : batch.workers) assertFalse(worker.isAlive(), worker.getName());
      assertFalse(batch.driver.isAlive(), "Shutdown left the driver alive");
      assertNoInterruptor();
    } finally {
      if (stopper.getState() == Thread.State.NEW) stopper.start();
      try {
        awaitStopPending(stopper);
      } finally {
        try {
          batch.releaseAndJoin();
        } finally {
          joinStopped(stopper);
        }
      }
      shutdown.get(2, TimeUnit.SECONDS);
    }
  }

  /** The helper reports permission to continue, not just that its workers exited. */
  @Test
  void batchResultRequiresRunningAfterDrain() throws Exception {
    GatedBatch batch = new GatedBatch();
    ParkBlockChurnAntagonist workload = new ParkBlockChurnAntagonist(2, 20, batch);
    FutureTask<Void> shutdown =
        new FutureTask<>(
            () -> {
              workload.stopGracefully(Duration.ofSeconds(5));
              return null;
            });
    Thread stopper = new Thread(shutdown, "batch-result-stopper");
    workload.start();
    try {
      assertTrue(batch.started.await(2, TimeUnit.SECONDS), "Batch workers did not start");
      assertTrue(workload.awaitBatch(Collections.emptyList()), "Running empty batch must continue");
      Thread dead = new Thread(() -> {}, "already-drained-worker");
      dead.start();
      joinStopped(dead);
      assertTrue(
          workload.awaitBatch(Collections.singletonList(dead)),
          "Ordinary drained batch must continue");
      stopper.start();
      assertThrows(TimeoutException.class, () -> shutdown.get(100, TimeUnit.MILLISECONDS));
      FutureTask<Boolean> drain = new FutureTask<>(() -> workload.awaitBatch(batch.workers));
      Thread waiter = new Thread(drain, "batch-result-waiter");
      waiter.start();
      try {
        batch.releaseFirst.countDown();
        joinStopped(batch.workers.get(0));
        batch.releaseSecond.countDown();
        shutdown.get(2, TimeUnit.SECONDS);
        assertFalse(drain.get(2, TimeUnit.SECONDS), "Clean shutdown drain must return false");
        assertFalse(
            workload.awaitBatch(Collections.emptyList()), "Stopped empty batch must not continue");
        assertFalse(
            workload.awaitBatch(Collections.singletonList(dead)),
            "Stopped dead batch must not continue");
      } finally {
        batch.releaseFirst.countDown();
        batch.releaseSecond.countDown();
        joinStopped(waiter);
      }
    } finally {
      if (stopper.getState() == Thread.State.NEW) stopper.start();
      try {
        awaitStopPending(stopper);
      } finally {
        try {
          batch.releaseAndJoin();
        } finally {
          joinStopped(stopper);
        }
      }
      shutdown.get(2, TimeUnit.SECONDS);
    }
  }

  /** Captures the helper's restored interrupt flag before its waiting thread terminates. */
  @Test
  void interruptedBatchHelperPreservesInterruptBeforeExit() throws Exception {
    GatedBatch batch = new GatedBatch();
    ParkBlockChurnAntagonist workload = new ParkBlockChurnAntagonist(2, 20, batch);
    FutureTask<Boolean> drain =
        new FutureTask<>(
            () -> {
              assertFalse(
                  workload.awaitBatch(batch.workers), "Interrupted drain must not continue");
              return Thread.currentThread().isInterrupted();
            });
    Thread waiter = new Thread(drain, "interrupted-batch-helper-waiter");
    boolean failed = false;
    workload.start();
    try {
      assertTrue(batch.started.await(2, TimeUnit.SECONDS), "Batch workers did not start");
      waiter.start();
      awaitStopPending(waiter);
      assertTrue(waiter.isAlive(), "Helper exited before its join could be interrupted");
      failed = true;
      waiter.interrupt();
      assertTrue(drain.get(2, TimeUnit.SECONDS), "Helper lost its interrupt status before exit");
      assertTrue(
          batch.workers.get(0).isAlive() && batch.workers.get(1).isAlive(),
          "The interrupted helper must leave the held workers for cleanup");
      assertTrue(batch.workers.size() == 2, "An interrupted helper spawned another batch");
    } finally {
      try {
        batch.finish(workload, failed);
      } finally {
        if (waiter.getState() != Thread.State.NEW) joinStopped(waiter);
      }
    }
  }

  /** Interrupting the real driver cannot silently strand its live batch and report success. */
  @Test
  void interruptedDriverRecordsFailureWithoutAbandoningBatch() throws Exception {
    GatedBatch batch = new GatedBatch();
    ParkBlockChurnAntagonist workload = new ParkBlockChurnAntagonist(2, 20, batch);
    boolean failed = false;
    workload.start();
    try {
      assertTrue(batch.started.await(2, TimeUnit.SECONDS), "Batch workers did not start");
      awaitStopPending(batch.driver);
      assertTrue(batch.driver.isAlive(), "Driver exited before the interrupted join test");
      failed = true;
      batch.driver.interrupt();
      joinStopped(batch.driver);
      IllegalStateException error =
          assertThrows(
              IllegalStateException.class, () -> workload.stopGracefully(Duration.ofSeconds(1)));
      assertTrue(error.getMessage().contains("Unreaped"), error.getMessage());
      assertTrue(
          error.getCause() instanceof InterruptedException, "Interrupted join was not recorded");
      assertTrue(
          batch.workers.get(0).isAlive() && batch.workers.get(1).isAlive(),
          "The held workers should still need cleanup");
      assertTrue(batch.workers.size() == 2, "An interrupted driver spawned another batch");
    } finally {
      batch.finish(workload, failed);
    }
  }

  /** Short deadlines exercise the actual helper, including positive submillisecond waits. */
  @ParameterizedTest
  @ValueSource(longs = {0L, 100_000L, 40_000_000L})
  void expiredBatchRecordsFailureWithoutUnboundedJoin(long timeoutNanos) throws Exception {
    GatedBatch batch = new GatedBatch();
    ParkBlockChurnAntagonist workload = new ParkBlockChurnAntagonist(2, 20, batch);
    boolean failed = false;
    workload.start();
    try {
      assertTrue(batch.started.await(2, TimeUnit.SECONDS), "Batch workers did not start");
      long start = System.nanoTime();
      failed = true;
      assertFalse(
          workload.awaitBatch(batch.workers, timeoutNanos), "Stalled batch must not continue");
      assertTrue(
          System.nanoTime() - start < TimeUnit.MILLISECONDS.toNanos(750),
          "Helper waited a full join quantum instead of its remaining deadline");
      IllegalStateException error =
          assertThrows(
              IllegalStateException.class, () -> workload.stopGracefully(Duration.ofMillis(100)));
      assertNotNull(error.getCause(), "Stop lost the batch failure");
      assertTrue(error.getCause().getMessage().contains("stalled"), error.toString());
      assertTrue(batch.workers.size() == 2, "Deadline failure spawned another batch");
    } finally {
      batch.finish(workload, failed);
    }
  }

  /** Caller budgets that round down to zero must still be bounded. */
  @ParameterizedTest
  @ValueSource(longs = {0L, 100_000L})
  void tinyStopBudgetCannotBecomeIndefiniteJoin(long timeoutNanos) throws Exception {
    GatedBatch batch = new GatedBatch();
    ParkBlockChurnAntagonist workload = new ParkBlockChurnAntagonist(2, 20, batch);
    FutureTask<IllegalStateException> shutdown =
        new FutureTask<>(
            () ->
                assertThrows(
                    IllegalStateException.class,
                    () -> workload.stopGracefully(Duration.ofNanos(timeoutNanos))));
    Thread stopper = new Thread(shutdown, "tiny-budget-stopper");
    workload.start();
    try {
      assertTrue(batch.started.await(2, TimeUnit.SECONDS), "Batch workers did not start");
      stopper.start();
      IllegalStateException error = shutdown.get(1, TimeUnit.SECONDS);
      assertTrue(error.getMessage().contains("driver did not stop"), error.getMessage());
      assertTrue(batch.driver.isAlive(), "A held batch must keep its driver alive");
    } finally {
      batch.finish(workload, false);
      if (stopper.getState() != Thread.State.NEW) joinStopped(stopper);
    }
  }

  /** An interrupted public stop is a persistent failure, even after all workers are reaped. */
  @Test
  void interruptedStopRecordsFailureAndPreservesInterrupt() throws Exception {
    GatedBatch batch = new GatedBatch();
    ParkBlockChurnAntagonist workload = new ParkBlockChurnAntagonist(2, 20, batch);
    FutureTask<Boolean> shutdown =
        new FutureTask<>(
            () -> {
              IllegalStateException error =
                  assertThrows(
                      IllegalStateException.class,
                      () -> workload.stopGracefully(Duration.ofSeconds(5)));
              assertTrue(error.getCause() instanceof InterruptedException, error.toString());
              return Thread.currentThread().isInterrupted();
            });
    Thread stopper = new Thread(shutdown, "interrupted-stop-waiter");
    boolean failed = false;
    workload.start();
    try {
      assertTrue(batch.started.await(2, TimeUnit.SECONDS), "Batch workers did not start");
      stopper.start();
      awaitStopPending(stopper);
      failed = true;
      stopper.interrupt();
      assertTrue(shutdown.get(2, TimeUnit.SECONDS), "Stop caller lost its interrupt flag");
    } finally {
      batch.finish(workload, failed);
      if (stopper.getState() != Thread.State.NEW) joinStopped(stopper);
    }
  }

  /** Driver and scheduler termination share the caller's budget rather than each taking it. */
  @Test
  void stopBudgetIncludesOwnedInterruptor() throws Exception {
    GatedBatch batch = new GatedBatch(true);
    ParkBlockChurnAntagonist workload = new ParkBlockChurnAntagonist(2, 20, batch);
    FutureTask<IllegalStateException> shutdown =
        new FutureTask<>(
            () ->
                assertThrows(
                    IllegalStateException.class,
                    () -> workload.stopGracefully(Duration.ofSeconds(1))));
    Thread stopper = new Thread(shutdown, "interruptor-budget-stopper");
    workload.start();
    try {
      assertTrue(batch.started.await(2, TimeUnit.SECONDS), "Batch workers did not start");
      assertTrue(batch.interruptEntered.await(2, TimeUnit.SECONDS), "Scheduler task did not start");
      stopper.start();
      awaitStopPending(stopper);
      assertThrows(TimeoutException.class, () -> shutdown.get(600, TimeUnit.MILLISECONDS));
      batch.releaseFirst.countDown();
      batch.releaseSecond.countDown();
      joinStopped(batch.driver);
      assertTrue(batch.interruptor.isAlive(), "Scheduler task was not independently held");
      IllegalStateException error = shutdown.get(700, TimeUnit.MILLISECONDS);
      assertTrue(error.getMessage().contains("interruptor did not stop"), error.getMessage());
    } finally {
      batch.releaseInterrupt.countDown();
      batch.finish(workload, false);
      if (stopper.getState() != Thread.State.NEW) joinStopped(stopper);
    }
  }

  /** Independently gates actual hook runnables and captures the actual public-start driver. */
  private static final class GatedBatch implements ThreadFactory {
    final CountDownLatch started = new CountDownLatch(2);
    final CountDownLatch releaseFirst = new CountDownLatch(1);
    final CountDownLatch releaseSecond = new CountDownLatch(1);
    final List<Thread> workers = Collections.synchronizedList(new ArrayList<>());
    final CountDownLatch interruptEntered = new CountDownLatch(1);
    final CountDownLatch releaseInterrupt = new CountDownLatch(1);
    final boolean gateInterrupt;
    volatile Thread driver;
    volatile Thread interruptor;

    GatedBatch() {
      this(false);
    }

    GatedBatch(boolean gateInterrupt) {
      this.gateInterrupt = gateInterrupt;
    }

    @Override
    public Thread newThread(Runnable task) {
      driver = Thread.currentThread();
      int index = workers.size();
      if (index >= 2) throw new AssertionError("Unexpected overlapping batch");
      CountDownLatch release = index == 0 ? releaseFirst : releaseSecond;
      Thread worker =
          new Thread(
              () -> {
                started.countDown();
                awaitRelease(release);
                task.run();
              },
              "gated-block-worker-" + index) {
            @Override
            public void interrupt() {
              if (gateInterrupt
                  && Thread.currentThread()
                      .getName()
                      .equals("chaos-park-block-churn-interruptor")) {
                interruptor = Thread.currentThread();
                interruptEntered.countDown();
                awaitRelease(releaseInterrupt);
              }
              super.interrupt();
            }
          };
      workers.add(worker);
      return worker;
    }

    /** Reaps every captured thread even when a test intentionally made stop fail. */
    void finish(ParkBlockChurnAntagonist workload, boolean failed) throws Exception {
      FutureTask<Throwable> shutdown =
          new FutureTask<>(
              () -> {
                try {
                  workload.stopGracefully(Duration.ofSeconds(5));
                  return null;
                } catch (IllegalStateException e) {
                  return e;
                }
              });
      Thread stopper = new Thread(shutdown, "batch-cleanup-stopper");
      stopper.start();
      try {
        awaitStopPending(stopper);
      } finally {
        releaseInterrupt.countDown();
        try {
          releaseAndJoin();
        } finally {
          joinStopped(stopper);
        }
      }
      Throwable error = shutdown.get(2, TimeUnit.SECONDS);
      if (failed) assertNotNull(error, "Recorded failure was reported as a clean stop");
      else assertNull(error, "Unexpected cleanup failure");
      assertNoInterruptor();
    }

    void releaseAndJoin() throws InterruptedException {
      releaseFirst.countDown();
      releaseSecond.countDown();
      // Join the publisher before reading a possibly incomplete list after setup failure.
      try {
        if (driver != null) driver.join(2_000L);
      } finally {
        synchronized (workers) {
          for (Thread worker : workers) worker.join(2_000L);
        }
      }
      if (driver != null) assertFalse(driver.isAlive(), "Cleanup left the driver alive");
      for (Thread worker : workers) assertFalse(worker.isAlive(), worker.getName());
    }
  }

  /** Scheduler interrupts must not open the test's lifetime gate. */
  private static void awaitRelease(CountDownLatch release) {
    boolean interrupted = false;
    while (true) {
      try {
        release.await();
        break;
      } catch (InterruptedException e) {
        interrupted = true;
      }
    }
    if (interrupted) Thread.currentThread().interrupt();
  }

  /** A timed join or completion proves the stop/driver passed its nonblocking setup. */
  private static void awaitStopPending(Thread thread) throws InterruptedException {
    long deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(2);
    while (thread.isAlive() && thread.getState() != Thread.State.TIMED_WAITING) {
      assertTrue(
          System.nanoTime() < deadline, "Thread did not reach a timed join: " + thread.getName());
      Thread.sleep(1);
    }
  }

  private static void joinStopped(Thread thread) throws InterruptedException {
    thread.join(2_000L);
    assertFalse(thread.isAlive(), "Cleanup left a live thread: " + thread.getName());
  }

  private static void assertNoInterruptor() {
    for (Thread thread : Thread.getAllStackTraces().keySet()) {
      assertFalse(
          thread.isAlive() && thread.getName().equals("chaos-park-block-churn-interruptor"),
          "Shutdown left the owned scheduler alive");
    }
  }

  /** Creates repeated real thread lifecycles while sampling, and joins them before returning. */
  private ParkBlockChurnAntagonist runWorkload(String command) throws Exception {
    profiler.execute("start," + command + ",jfr,file=" + recording.toAbsolutePath());
    started = true;
    ParkBlockChurnAntagonist workload = new ParkBlockChurnAntagonist(12, 20);
    workload.start();
    try {
      Thread.sleep(1000);
    } finally {
      workload.stopGracefully(Duration.ofSeconds(5));
    }
    return workload;
  }
}
