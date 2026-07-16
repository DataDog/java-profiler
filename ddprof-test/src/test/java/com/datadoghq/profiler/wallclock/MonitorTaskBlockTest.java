/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assumptions;
import org.openjdk.jmc.common.item.IItemCollection;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/** Verifies TaskBlock production from native JVMTI monitor callbacks. */
public class MonitorTaskBlockTest extends AbstractProfilerTest {
  @Test
  public void objectWaitEmitsTaskBlockOutsideContextWindow() throws Exception {
    Object monitor = new Object();
    CountDownLatch entered = new CountDownLatch(1);
    AtomicReference<Throwable> failure = new AtomicReference<>();
    Thread worker = new Thread(() -> {
      try {
        synchronized (monitor) {
          entered.countDown();
          monitor.wait(100);
        }
      } catch (Throwable t) {
        failure.set(t);
      }
    }, "taskblock-object-wait");

    worker.start();
    assertTrue(entered.await(5, TimeUnit.SECONDS));
    assertCompleted(worker, failure);
    stopProfiler();

    IItemCollection events = verifyEvents("datadog.TaskBlock");
    assertTaskBlockStackReference(events);
    TaskBlockAssertions.assertContains(events, 0, 0, identityHash(monitor), 0);
    TaskBlockAssertions.assertContainsObservedState(events, "WAITING");
  }

  @Test
  public void monitorContentionEmitsTaskBlockOutsideContextWindow() throws Exception {
    Object monitor = new Object();
    CountDownLatch attempting = new CountDownLatch(1);
    AtomicReference<Throwable> failure = new AtomicReference<>();
    Thread worker;
    synchronized (monitor) {
      worker = new Thread(() -> {
        try {
          attempting.countDown();
          synchronized (monitor) {
          }
        } catch (Throwable t) {
          failure.set(t);
        }
      }, "taskblock-monitor-contention");
      worker.start();
      assertTrue(attempting.await(5, TimeUnit.SECONDS));
      Thread.sleep(100);
    }

    assertCompleted(worker, failure);
    stopProfiler();

    IItemCollection events = verifyEvents("datadog.TaskBlock");
    assertTaskBlockStackReference(events);
    TaskBlockAssertions.assertContains(events, 0, 0, identityHash(monitor), 0);
    TaskBlockAssertions.assertContainsObservedState(events, "CONTENDED");
  }

  @Test
  public void contextWindowObjectWaitDoesNotEmitTaskBlock() throws Exception {
    Object monitor = new Object();
    AtomicReference<Throwable> failure = new AtomicReference<>();
    Thread worker = new Thread(() -> {
      try {
        registerCurrentThreadForWallClockProfiling();
        profiler.setContext(0x4400L, 0x4401L, 0L, 0x4401L);
        synchronized (monitor) {
          monitor.wait(100);
        }
      } catch (Throwable t) {
        failure.set(t);
      } finally {
        profiler.clearContext();
        profiler.removeThread();
      }
    }, "taskblock-traced-object-wait");

    worker.start();
    assertCompleted(worker, failure);
    stopProfiler();

    assertFalse(TaskBlockAssertions.containsBlocker(
        verifyEvents("datadog.TaskBlock", false), identityHash(monitor)));
  }

  @Test
  public void staleWaitStateIsRecoveredAfterProfilerRestart() throws Exception {
    Object waitMonitor = new Object();
    Object contentionMonitor = new Object();
    CountDownLatch waiting = new CountDownLatch(1);
    CountDownLatch waitCompleted = new CountDownLatch(1);
    CountDownLatch restartReady = new CountDownLatch(1);
    CountDownLatch attemptingContention = new CountDownLatch(1);
    AtomicReference<Throwable> failure = new AtomicReference<>();
    Thread worker = new Thread(() -> {
      try {
        synchronized (waitMonitor) {
          waiting.countDown();
          waitMonitor.wait();
        }
        waitCompleted.countDown();
        assertTrue(restartReady.await(5, TimeUnit.SECONDS));
        attemptingContention.countDown();
        synchronized (contentionMonitor) {
        }
      } catch (Throwable t) {
        failure.set(t);
      }
    }, "taskblock-monitor-restart");

    worker.start();
    assertTrue(waiting.await(5, TimeUnit.SECONDS));
    Thread.sleep(50);
    stopProfiler();
    synchronized (waitMonitor) {
      waitMonitor.notifyAll();
    }
    assertTrue(waitCompleted.await(5, TimeUnit.SECONDS));

    Path recording = Files.createTempFile("MonitorTaskBlockTest-restart-", ".jfr");
    boolean restarted = false;
    try {
      profiler.execute("start,wall=1ms,filter=,wallprecheck=true,jfr,file="
          + recording.toAbsolutePath());
      restarted = true;
      synchronized (contentionMonitor) {
        restartReady.countDown();
        assertTrue(attemptingContention.await(5, TimeUnit.SECONDS));
        Thread.sleep(100);
      }
      assertCompleted(worker, failure);
      profiler.stop();
      restarted = false;

      IItemCollection events = verifyEvents(recording, "datadog.TaskBlock", false);
      assertTaskBlockStackReference(events);
      assertTrue(TaskBlockAssertions.containsBlocker(
          events, identityHash(contentionMonitor)));
    } finally {
      restartReady.countDown();
      synchronized (waitMonitor) {
        waitMonitor.notifyAll();
      }
      if (restarted) profiler.stop();
      worker.join(5_000);
      Files.deleteIfExists(recording);
    }
  }

  @Test
  public void virtualMonitorCallbacksDoNotEmitCarrierTaskBlocks() throws Exception {
    Method startVirtualThread;
    try {
      startVirtualThread = Thread.class.getMethod("startVirtualThread", Runnable.class);
    } catch (NoSuchMethodException unavailableBeforeJdk21) {
      Assumptions.assumeTrue(false, "virtual threads require JDK 21");
      return;
    }

    Object waitMonitor = new Object();
    AtomicReference<Throwable> failure = new AtomicReference<>();
    Thread waiter = (Thread) startVirtualThread.invoke(null, (Runnable) () -> {
      try {
        synchronized (waitMonitor) {
          waitMonitor.wait(100);
        }
      } catch (Throwable t) {
        failure.set(t);
      }
    });
    assertCompleted(waiter, failure);

    Object contentionMonitor = new Object();
    CountDownLatch attempting = new CountDownLatch(1);
    Thread contender;
    synchronized (contentionMonitor) {
      contender = (Thread) startVirtualThread.invoke(null, (Runnable) () -> {
        try {
          attempting.countDown();
          synchronized (contentionMonitor) {
          }
        } catch (Throwable t) {
          failure.set(t);
        }
      });
      assertTrue(attempting.await(5, TimeUnit.SECONDS));
      Thread.sleep(100);
    }
    assertCompleted(contender, failure);
    stopProfiler();

    IItemCollection events = verifyEvents("datadog.TaskBlock", false);
    assertFalse(TaskBlockAssertions.containsBlocker(events, identityHash(waitMonitor)));
    assertFalse(TaskBlockAssertions.containsBlocker(events, identityHash(contentionMonitor)));
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }

  protected void assertTaskBlockStackReference(IItemCollection events) {
    TaskBlockAssertions.assertContainsStackTrace(events);
    TaskBlockAssertions.assertContainsJavaType(events, "MonitorTaskBlockTest");
    TaskBlockAssertions.assertNoCorrelationId(events);
  }

  private static void assertCompleted(Thread thread, AtomicReference<Throwable> failure)
      throws InterruptedException {
    thread.join(5_000);
    assertFalse(thread.isAlive(), "worker did not complete");
    if (failure.get() != null) throw new AssertionError(failure.get());
  }

  private static long identityHash(Object object) {
    return Integer.toUnsignedLong(System.identityHashCode(object));
  }
}
