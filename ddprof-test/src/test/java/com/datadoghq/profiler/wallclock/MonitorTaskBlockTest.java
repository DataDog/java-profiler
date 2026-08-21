/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Map;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;
import com.datadoghq.profiler.JfrEvents;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assumptions;

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

    JfrEvents events = verifyEvents("datadog.TaskBlock");
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

    JfrEvents events = verifyEvents("datadog.TaskBlock");
    assertTaskBlockStackReference(events);
    TaskBlockAssertions.assertContains(events, 0, 0, identityHash(monitor), 0);
    TaskBlockAssertions.assertContainsObservedState(events, "CONTENDED");
  }

  @Test
  public void shortMonitorContentionIsFilteredAndDoesNotSuppressLongerOnes() throws Exception {
    Object shortMonitor = new Object();
    Object longMonitor = new Object();

    // Burst of genuinely contended, microsecond-long enters: two threads hammer the same
    // monitor with an empty critical section, so no interval can reach the 1ms threshold.
    runContentionBurst(shortMonitor);

    // One long contended enter, the positive control: it proves the producer was alive.
    CountDownLatch attempting = new CountDownLatch(1);
    AtomicReference<Throwable> failure = new AtomicReference<>();
    Thread worker;
    synchronized (longMonitor) {
      worker = new Thread(() -> {
        try {
          attempting.countDown();
          synchronized (longMonitor) {
          }
        } catch (Throwable t) {
          failure.set(t);
        }
      }, "taskblock-long-contention");
      worker.start();
      assertTrue(attempting.await(5, TimeUnit.SECONDS));
      Thread.sleep(100);
    }
    assertCompleted(worker, failure);
    stopProfiler();

    JfrEvents events = verifyEvents("datadog.TaskBlock");
    assertTrue(TaskBlockAssertions.containsBlocker(events, identityHash(longMonitor)),
        "long contention was not emitted");
    // The burst does 40,000 contended enters with an empty critical section, so almost all
    // should fall under the 1ms filter threshold. A rare enter can still legitimately exceed
    // it if the OS descheduled the lock holder mid-critical-section (safepoint, GC, container
    // CPU contention) - that is correct profiler behavior, not a filtering bug. Tolerate a
    // small number of such outliers; a real filtering regression would leak most/all of them.
    int leaked = TaskBlockAssertions.countBlockerEvents(events, identityHash(shortMonitor));
    assertTrue(leaked <= 5,
        "sub-threshold contention must be filtered, but " + leaked + " events leaked through");
    assertTaskBlockStackReference(events);
  }

  private void runContentionBurst(Object monitor) throws Exception {
    CountDownLatch start = new CountDownLatch(1);
    AtomicReference<Throwable> burstFailure = new AtomicReference<>();
    int[] counter = new int[1];
    Thread[] burst = new Thread[2];
    for (int i = 0; i < burst.length; i++) {
      burst[i] = new Thread(() -> {
        try {
          assertTrue(start.await(5, TimeUnit.SECONDS));
          for (int n = 0; n < 20_000; n++) {
            synchronized (monitor) {
              counter[0]++;
            }
          }
        } catch (Throwable t) {
          burstFailure.set(t);
        }
      }, "taskblock-short-contention-" + i);
      burst[i].start();
    }
    start.countDown();
    for (Thread thread : burst) {
      assertCompleted(thread, burstFailure);
    }
  }

  @Test
  public void contextWindowObjectWaitDoesNotEmitTaskBlock() throws Exception {
    Object monitor = new Object();
    Object controlMonitor = new Object();
    AtomicReference<Throwable> failure = new AtomicReference<>();
    Thread worker = new Thread(() -> {
      try {
        registerCurrentThreadForWallClockProfiling();
        profiler.setTraceContext(0x4400L, 0x4401L, 0L, 0x4401L, -1, null, -1, null);
        synchronized (monitor) {
          monitor.wait(100);
        }
      } catch (Throwable t) {
        failure.set(t);
      } finally {
        profiler.clearTraceContext();
        profiler.removeThread();
      }
    }, "taskblock-traced-object-wait");

    worker.start();
    assertCompleted(worker, failure);

    // Positive control: an untraced platform-thread wait in the same recording must be
    // produced, so this test also fails when the producer stops emitting anything at all.
    AtomicReference<Throwable> controlFailure = new AtomicReference<>();
    Thread control = new Thread(() -> {
      try {
        synchronized (controlMonitor) {
          controlMonitor.wait(100);
        }
      } catch (Throwable t) {
        controlFailure.set(t);
      }
    }, "taskblock-control-object-wait");
    control.start();
    assertCompleted(control, controlFailure);

    stopProfiler();

    JfrEvents events = verifyEvents("datadog.TaskBlock");
    assertTrue(TaskBlockAssertions.containsBlocker(events, identityHash(controlMonitor)),
        "control wait was not produced");
    assertFalse(TaskBlockAssertions.containsBlocker(events, identityHash(monitor)),
        "traced wait was not suppressed");
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
    // Built from getProfilerCommand() so subclasses exercise their own configuration on the
    // restarted recording too, not just on the initial one.
    try {
      profiler.execute("start," + getProfilerCommand() + ",jfr,file="
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

      JfrEvents events = verifyEvents(recording, "datadog.TaskBlock", false);
      assertTaskBlockStackReference(events);
      assertTrue(TaskBlockAssertions.containsBlocker(
          events, identityHash(contentionMonitor)));
      assertRestartedConfiguration(profiler.getDebugCounters());
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

    // Positive control: the same contention shape on a platform thread must be produced,
    // so this test fails when carrier suppression breaks *and* when production breaks.
    Object platformMonitor = new Object();
    CountDownLatch platformAttempting = new CountDownLatch(1);
    AtomicReference<Throwable> platformFailure = new AtomicReference<>();
    Thread platformContender;
    synchronized (platformMonitor) {
      platformContender = new Thread(() -> {
        try {
          platformAttempting.countDown();
          synchronized (platformMonitor) {
          }
        } catch (Throwable t) {
          platformFailure.set(t);
        }
      }, "taskblock-control-monitor-contention");
      platformContender.start();
      assertTrue(platformAttempting.await(5, TimeUnit.SECONDS));
      Thread.sleep(100);
    }
    assertCompleted(platformContender, platformFailure);

    stopProfiler();

    JfrEvents events = verifyEvents("datadog.TaskBlock");
    assertTrue(TaskBlockAssertions.containsBlocker(events, identityHash(platformMonitor)),
        "platform control was not produced");
    assertFalse(TaskBlockAssertions.containsBlocker(events, identityHash(waitMonitor)));
    assertFalse(TaskBlockAssertions.containsBlocker(events, identityHash(contentionMonitor)));
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }

  /**
   * Hook for subclasses to assert that the restarted recording ran under their own
   * configuration. No-op here so the base class stays configuration-agnostic.
   *
   * <p>The restart's {@code start,...} command resets the native debug counters, so
   * {@code counters} only accumulates over the restarted recording: subclasses can assert
   * absolute values rather than deltas against a pre-restart baseline.
   */
  protected void assertRestartedConfiguration(Map<String, Long> counters) {
  }

  protected void assertTaskBlockStackReference(JfrEvents events) {
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
