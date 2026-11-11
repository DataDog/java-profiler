/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import java.nio.file.Files;
import java.nio.file.Path;
import java.time.Instant;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

/**
 * Verifies original custom context on real deferred ASGCT wall samples across owner transitions.
 */
public class UnownedWallTailContextTransitionTest extends AbstractProfilerTest {
  private static final String WORKER = "unowned-origin-context";
  private static final String[] FIELDS = {TAG_1, TAG_2, TAG_3};
  private static volatile long spinSink;

  @Override
  protected void withTestAssumptions() {
    Assumptions.assumeTrue(!Platform.isJ9() && Platform.isJavaVersionAtLeast(11));
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=0,wallprecheck=true,jvmtistacks=false,attributes=tag1;tag2;tag3";
  }

  /**
   * Uses actual suppression and decoded stack/state/weight evidence, not sleeps as an exact-weight
   * oracle. Native preparation tests independently control the pending-weight decisions.
   */
  @Test
  public void tagOnlyTailKeepsOriginalFieldsAcrossDumps() throws Exception {
    String prefix = Long.toHexString(System.nanoTime());
    String[] tagsA = {prefix + "-A1", prefix + "-A2", prefix + "-A3"};
    String[] tagsB = {prefix + "-B1", prefix + "-B2", prefix + "-B3"};
    CountDownLatch ready = new CountDownLatch(1);
    CountDownLatch releaseA = new CountDownLatch(1);
    CountDownLatch readyB = new CountDownLatch(1);
    AtomicBoolean running = new AtomicBoolean(true);
    AtomicLong transitionStart = new AtomicLong();
    AtomicReference<Throwable> workerFailure = new AtomicReference<>();
    Map<String, Long> before = profiler.getDebugCounters();
    Thread worker =
        new Thread(
            () -> {
              try {
                setTags(tagsA);
                registerCurrentThreadForWallClockProfiling();
                ready.countDown();
                blockedOriginA(releaseA);
                Instant now = Instant.now();
                transitionStart.set(now.getEpochSecond() * 1_000_000_000L + now.getNano());
                setTags(tagsB);
                readyB.countDown();
                runnableContextB(running);
              } catch (Throwable failure) {
                workerFailure.set(failure);
                ready.countDown();
                readyB.countDown();
              } finally {
                profiler.removeThread();
              }
            },
            WORKER);
    Path[] snapshots = new Path[3];
    worker.start();
    try {
      assertTrue(ready.await(10, TimeUnit.SECONDS), "Worker did not register");
      awaitSuppression(before, workerFailure);
      int blockedSamples = 0;
      for (int i = 0; i < snapshots.length; i++) {
        snapshots[i] = Files.createTempFile("unowned-context-dump-" + i, ".jfr");
        System.out.println("===> attribution recording: " + snapshots[i]);
        dump(snapshots[i]);
        JfrEvents samples = verifyEvents(snapshots[i], "datadog.MethodSample", false);
        for (JfrEvent sample : samples) {
          if (isWorker(sample)) {
            assertResolved(sample);
            assertTags(sample, tagsA);
            assertEquals(0L, sample.getLong(SPAN_ID, -1));
            assertEquals(0L, sample.getLong(LOCAL_ROOT_SPAN_ID, -1));
            blockedSamples++;
          }
        }
      }
      assertTrue(blockedSamples > 0, "No original worker samples across retained dumps");
      // Require fresh real suppression after the last dump, before releasing the only selected
      // worker. This is a coverage precondition, not an exact scheduler-derived tail weight.
      awaitSuppression(profiler.getDebugCounters(), workerFailure);
      releaseA.countDown();
      assertTrue(readyB.await(10, TimeUnit.SECONDS), "Worker did not enter B");
      assertNull(workerFailure.get(), "Worker failed during transition");
      Thread.sleep(300);
    } finally {
      releaseA.countDown();
      running.set(false);
      worker.join(10_000);
      for (Path snapshot : snapshots) {
        if (snapshot != null && !Boolean.getBoolean("ddprof_test.keep_jfrs")) {
          Files.deleteIfExists(snapshot);
        }
      }
    }
    assertFalse(worker.isAlive(), "Worker survived bounded cleanup");
    assertNull(workerFailure.get(), "Worker failed");
    assertTrue(transitionStart.get() > 0, "Transition marker was not published");
    System.out.println("Attribution transition start: " + transitionStart.get());
    stopProfiler();
    JfrEvents samples = verifyEvents("datadog.MethodSample", true);
    int originalTails = 0;
    Set<Long> ordinaryTimes = new HashSet<>();
    for (JfrEvent sample : samples) {
      if (!isWorker(sample)) {
        continue;
      }
      assertResolved(sample);
      String stack = sample.getStackTraceString();
      String state = sample.getEnumName(THREAD_STATE);
      long weight = sample.getLong(WEIGHT, 0);
      Long time = sample.getLong("startTime");
      assertNotNull(time, "Worker sample has no capture time");
      if (time >= transitionStart.get()
          && stack.contains("blockedOriginA")
          && "PARKED".equals(state)
          && weight > 1) {
        originalTails++;
        System.out.println(
            "Deferred A: time="
                + time
                + ", state="
                + state
                + ", weight="
                + weight
                + ", tags="
                + sample.getString(TAG_1)
                + ";"
                + sample.getString(TAG_2)
                + ";"
                + sample.getString(TAG_3));
        assertTags(sample, tagsA);
        assertEquals(0L, sample.getLong(SPAN_ID, -1));
        assertEquals(0L, sample.getLong(LOCAL_ROOT_SPAN_ID, -1));
      }
      if ("RUNNABLE".equals(state) && stack.contains("runnableContextB")) {
        assertEquals(1L, weight, "B must not acquire already suppressed A time");
        assertTags(sample, tagsB);
        assertEquals(0L, sample.getLong(SPAN_ID, -1));
        assertEquals(0L, sample.getLong(LOCAL_ROOT_SPAN_ID, -1));
        ordinaryTimes.add(time);
      }
    }
    assertTrue(
        originalTails > 0, "Coverage incomplete: no positive weighted A tail after transition");
    assertTrue(ordinaryTimes.size() >= 2, "No ordinary B samples at distinct capture times");
    Map<String, Long> after = profiler.getDebugCounters();
    assertEquals(0L, after.getOrDefault("jvmti_stacks_requested", 0L).longValue());
    assertEquals(
        before.getOrDefault("wc_unowned_blocked_trace_preservation_failed", 0L),
        after.getOrDefault("wc_unowned_blocked_trace_preservation_failed", 0L));
  }

  /** Keeps an untraced origin through a real active span, dumps, and a later clear. */
  @Test
  public void knownSpanThenClearKeepsOriginalTail() throws Exception {
    String prefix = Long.toHexString(System.nanoTime());
    String[] tagsA = {prefix + "-A1", prefix + "-A2", prefix + "-A3"};
    String[] tagsB = {prefix + "-B1", prefix + "-B2", prefix + "-B3"};
    String[] tagsC = {prefix + "-C1", prefix + "-C2", prefix + "-C3"};
    CountDownLatch readyA = new CountDownLatch(1);
    CountDownLatch releaseA = new CountDownLatch(1);
    CountDownLatch readyB = new CountDownLatch(1);
    CountDownLatch readyC = new CountDownLatch(1);
    AtomicBoolean inB = new AtomicBoolean(true);
    AtomicBoolean running = new AtomicBoolean(true);
    AtomicLong clearStart = new AtomicLong();
    AtomicReference<Throwable> workerFailure = new AtomicReference<>();
    Map<String, Long> before = profiler.getDebugCounters();
    Thread worker =
        new Thread(
            () -> {
              try {
                // Keep trace-setter setup outside the measured blocked-to-span transition.
                profiler.setTraceContext(7101, 7102, 0, 7103, -1, null, -1, null);
                profiler.clearTraceContext();
                setTags(tagsA);
                registerCurrentThreadForWallClockProfiling();
                readyA.countDown();
                blockedOriginA(releaseA);
                profiler.setTraceContext(7101, 7102, 0, 7103, -1, null, -1, null);
                setTags(tagsB);
                readyB.countDown();
                runnableTracedContextB(inB);
                Instant now = Instant.now();
                clearStart.set(now.getEpochSecond() * 1_000_000_000L + now.getNano());
                profiler.clearTraceContext();
                setTags(tagsC);
                readyC.countDown();
                runnableContextC(running);
              } catch (Throwable failure) {
                workerFailure.set(failure);
                readyA.countDown();
                readyB.countDown();
                readyC.countDown();
              } finally {
                profiler.clearTraceContext();
                profiler.removeThread();
              }
            },
            WORKER);
    Path[] snapshots = new Path[3];
    JfrEvents[] recordings = new JfrEvents[4];
    worker.start();
    try {
      assertTrue(readyA.await(10, TimeUnit.SECONDS), "Worker did not register A");
      awaitSuppression(before, workerFailure);
      releaseA.countDown();
      assertTrue(readyB.await(10, TimeUnit.SECONDS), "Worker did not enter traced B");
      assertNull(workerFailure.get(), "Worker failed before traced B");
      Map<String, Long> inSpan = profiler.getDebugCounters();
      Thread.sleep(100);
      for (int i = 0; i < snapshots.length; i++) {
        snapshots[i] = Files.createTempFile("unowned-span-context-dump-" + i, ".jfr");
        System.out.println("===> attribution recording: " + snapshots[i]);
        dump(snapshots[i]);
        recordings[i] = verifyEvents(snapshots[i], "datadog.MethodSample", false);
      }
      assertEquals(
          inSpan.getOrDefault("wc_unowned_blocked_suppressed", 0L),
          profiler.getDebugCounters().getOrDefault("wc_unowned_blocked_suppressed", 0L),
          "A known active span must not accumulate unowned weight");
      inB.set(false);
      assertTrue(readyC.await(10, TimeUnit.SECONDS), "Worker did not clear into C");
      assertNull(workerFailure.get(), "Worker failed during clear");
      Thread.sleep(300);
    } finally {
      releaseA.countDown();
      inB.set(false);
      running.set(false);
      worker.join(10_000);
      for (Path snapshot : snapshots) {
        if (snapshot != null && !Boolean.getBoolean("ddprof_test.keep_jfrs")) {
          Files.deleteIfExists(snapshot);
        }
      }
    }
    assertFalse(worker.isAlive(), "Worker survived bounded cleanup");
    assertNull(workerFailure.get(), "Worker failed");
    assertTrue(clearStart.get() > 0, "Clear marker was not published");
    System.out.println("Attribution clear start: " + clearStart.get());
    stopProfiler();
    recordings[3] = verifyEvents("datadog.MethodSample", true);
    Set<Long> tracedTimes = new HashSet<>();
    Set<Long> clearedTimes = new HashSet<>();
    int originalTails = 0;
    for (JfrEvents recording : recordings) {
      for (JfrEvent sample : recording) {
        if (!isWorker(sample)) {
          continue;
        }
        assertResolved(sample);
        String stack = sample.getStackTraceString();
        String state = sample.getEnumName(THREAD_STATE);
        long weight = sample.getLong(WEIGHT, 0);
        Long time = sample.getLong("startTime");
        assertNotNull(time, "Worker sample has no capture time");
        if ("RUNNABLE".equals(state) && stack.contains("runnableTracedContextB")) {
          assertEquals(1L, weight, "Traced B must not consume suppressed A time");
          assertTags(sample, tagsB);
          assertEquals(7102L, sample.getLong(SPAN_ID, -1));
          assertEquals(7101L, sample.getLong(LOCAL_ROOT_SPAN_ID, -1));
          tracedTimes.add(time);
        }
        if ("RUNNABLE".equals(state) && stack.contains("runnableContextC")) {
          assertEquals(1L, weight, "Cleared C must not consume suppressed A time");
          assertTags(sample, tagsC);
          assertEquals(0L, sample.getLong(SPAN_ID, -1));
          assertEquals(0L, sample.getLong(LOCAL_ROOT_SPAN_ID, -1));
          clearedTimes.add(time);
        }
        if (time >= clearStart.get()
            && stack.contains("blockedOriginA")
            && "PARKED".equals(state)
            && weight > 1) {
          originalTails++;
          assertTags(sample, tagsA);
          assertEquals(0L, sample.getLong(SPAN_ID, -1));
          assertEquals(0L, sample.getLong(LOCAL_ROOT_SPAN_ID, -1));
        }
      }
    }
    assertTrue(tracedTimes.size() >= 2, "No ordinary B samples at distinct capture times");
    assertTrue(clearedTimes.size() >= 2, "No ordinary C samples at distinct capture times");
    assertTrue(originalTails > 0, "Coverage incomplete: no retained A tail after span clear");
    Map<String, Long> after = profiler.getDebugCounters();
    assertEquals(0L, after.getOrDefault("jvmti_stacks_requested", 0L).longValue());
    assertEquals(
        before.getOrDefault("wc_unowned_blocked_trace_preservation_failed", 0L),
        after.getOrDefault("wc_unowned_blocked_trace_preservation_failed", 0L));
  }

  /** Restarts the same native owner without carrying the prior recording's deferred origin. */
  @Test
  public void restartClearsPriorOriginOnSurvivingOwner() throws Exception {
    String prefix = Long.toHexString(System.nanoTime());
    String[] tagsA = {prefix + "-RA1", prefix + "-RA2", prefix + "-RA3"};
    String[] tagsB = {prefix + "-RB1", prefix + "-RB2", prefix + "-RB3"};
    CountDownLatch readyA = new CountDownLatch(1);
    CountDownLatch releaseA = new CountDownLatch(1);
    CountDownLatch readyInactive = new CountDownLatch(1);
    CountDownLatch readyB = new CountDownLatch(1);
    AtomicBoolean restartedSignal = new AtomicBoolean();
    AtomicBoolean running = new AtomicBoolean(true);
    AtomicReference<Throwable> workerFailure = new AtomicReference<>();
    Map<String, Long> before = profiler.getDebugCounters();
    Thread worker =
        new Thread(
            () -> {
              try {
                setTags(tagsA);
                registerCurrentThreadForWallClockProfiling();
                readyA.countDown();
                blockedOriginA(releaseA);
                readyInactive.countDown();
                runnableAcrossStop(restartedSignal, running);
                if (!running.get()) {
                  return;
                }
                // filter=0 clears selection at recording start; select the surviving owner again.
                setTags(tagsB);
                registerCurrentThreadForWallClockProfiling();
                readyB.countDown();
                runnableRestartedContextB(running);
              } catch (Throwable failure) {
                workerFailure.set(failure);
                readyA.countDown();
                readyInactive.countDown();
                readyB.countDown();
              } finally {
                profiler.clearTraceContext();
                profiler.removeThread();
              }
            },
            WORKER);
    Path recording = Files.createTempFile("unowned-context-restart-", ".jfr");
    System.out.println("===> attribution recording: " + recording);
    boolean restarted = false;
    worker.start();
    try {
      assertTrue(readyA.await(10, TimeUnit.SECONDS), "Worker did not register A");
      awaitSuppression(before, workerFailure);
      stopProfiler();
      releaseA.countDown();
      assertTrue(readyInactive.await(10, TimeUnit.SECONDS), "Worker did not survive stop");
      assertNull(workerFailure.get(), "Worker failed before restart");
      profiler.execute("start," + getProfilerCommand() + ",jfr,file=" + recording);
      restarted = true;
      restartedSignal.set(true);
      assertTrue(readyB.await(10, TimeUnit.SECONDS), "Worker did not refresh B after restart");
      assertNull(workerFailure.get(), "Worker failed after restart");
      Thread.sleep(300);
      profiler.stop();
      restarted = false;
      Set<Long> ordinaryTimes = new HashSet<>();
      for (JfrEvent sample : verifyEvents(recording, "datadog.MethodSample", true)) {
        if (!isWorker(sample)) {
          continue;
        }
        assertResolved(sample);
        String stack = sample.getStackTraceString();
        assertFalse(
            stack.contains("blockedOriginA"), "Prior recording's origin leaked into restart");
        if (stack.contains("runnableRestartedContextB")
            && "RUNNABLE".equals(sample.getEnumName(THREAD_STATE))) {
          assertEquals(1L, sample.getLong(WEIGHT, 0), "New B consumed prior-recording weight");
          assertTags(sample, tagsB);
          assertEquals(0L, sample.getLong(SPAN_ID, -1));
          assertEquals(0L, sample.getLong(LOCAL_ROOT_SPAN_ID, -1));
          Long time = sample.getLong("startTime");
          assertNotNull(time, "Restarted B sample has no capture time");
          ordinaryTimes.add(time);
        }
      }
      assertTrue(ordinaryTimes.size() >= 2, "No restarted B samples at distinct capture times");
      Map<String, Long> after = profiler.getDebugCounters();
      assertEquals(0L, after.getOrDefault("jvmti_stacks_requested", 0L).longValue());
      assertEquals(
          before.getOrDefault("wc_unowned_blocked_trace_preservation_failed", 0L),
          after.getOrDefault("wc_unowned_blocked_trace_preservation_failed", 0L));
    } finally {
      releaseA.countDown();
      running.set(false);
      restartedSignal.set(true);
      worker.join(10_000);
      if (restarted) {
        profiler.stop();
      }
      if (!Boolean.getBoolean("ddprof_test.keep_jfrs")) {
        Files.deleteIfExists(recording);
      }
    }
    assertFalse(worker.isAlive(), "Worker survived bounded cleanup");
    assertNull(workerFailure.get(), "Worker failed");
  }

  /** Writes through the supported JNI setter, without activating a span or an owned block. */
  private void setTags(String[] values) {
    for (int i = 0; i < values.length; i++) {
      assertTrue(
          profiler.setContextValue(i, values[i]), "Tag setter rejected configured field " + i);
    }
  }

  /** Waits for observed recording/suppression on the only explicitly selected worker. */
  private void awaitSuppression(Map<String, Long> before, AtomicReference<Throwable> failure)
      throws Exception {
    long deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(10);
    long suppressionTarget = -1;
    while (System.nanoTime() < deadline) {
      assertNull(failure.get(), "Worker failed before required suppression");
      Map<String, Long> counters = profiler.getDebugCounters();
      long suppressed = counters.getOrDefault("wc_unowned_blocked_suppressed", 0L);
      if (suppressionTarget < 0
          && counters.getOrDefault("wc_unowned_blocked_recorded", 0L)
              > before.getOrDefault("wc_unowned_blocked_recorded", 0L)) {
        // A periodic record consumes preceding suppression. Require new suppressed observations
        // after that record instead of releasing at the just-flushed boundary.
        suppressionTarget = suppressed + 2;
      }
      if (suppressionTarget >= 0 && suppressed >= suppressionTarget) {
        System.out.println(
            "Attribution suppression ready: recorded="
                + counters.getOrDefault("wc_unowned_blocked_recorded", 0L)
                + ", suppressed="
                + suppressed
                + ", target="
                + suppressionTarget);
        return;
      }
      Thread.sleep(1);
    }
    throw new AssertionError(
        "Coverage incomplete: real unowned recording/suppression not observed");
  }

  /** Identifies the actual selected worker, not arbitrary process-wide samples. */
  private static boolean isWorker(JfrEvent sample) {
    return WORKER.equals(sample.getThreadName("eventThread"));
  }

  /**
   * Requires a real resolved stack and positive represented time on every observed worker sample.
   */
  private static void assertResolved(JfrEvent sample) {
    assertFalse(sample.getStackTrace().isEmpty(), "Unresolved worker stack after context rotation");
    assertTrue(sample.getLong(WEIGHT, 0) > 0, "Worker sample lost represented time");
  }

  /** All configured fields belong to the retained origin, not the owner at emission. */
  private static void assertTags(JfrEvent sample, String[] values) {
    for (int i = 0; i < FIELDS.length; i++) {
      assertEquals(values[i], sample.getString(FIELDS[i]), "Wrong original field " + FIELDS[i]);
    }
  }

  /** Leaves a distinct unowned blocked frame for actual signal-driven stack walking. */
  private static void blockedOriginA(CountDownLatch release) throws InterruptedException {
    release.await();
  }

  /** Remains runnable while profiling is stopped, so restart cannot create a new blocked origin. */
  private static void runnableAcrossStop(AtomicBoolean restarted, AtomicBoolean running) {
    long value = 1;
    while (running.get() && !restarted.get()) {
      value = value * 1664525 + 1013904223;
      spinSink = value;
    }
  }

  /** Supplies ordinary samples on the same surviving owner after its recording is restarted. */
  private static void runnableRestartedContextB(AtomicBoolean running) {
    long value = 1;
    while (running.get()) {
      value = value * 1664525 + 1013904223;
      spinSink = value;
    }
  }

  /** Keeps a distinct traced B frame observable while an unowned origin remains retained. */
  private static void runnableTracedContextB(AtomicBoolean inB) {
    long value = 1;
    while (inB.get()) {
      value = value * 1664525 + 1013904223;
      spinSink = value;
    }
  }

  /** Keeps cleared C samples distinguishable from both the old origin and the active span. */
  private static void runnableContextC(AtomicBoolean running) {
    long value = 1;
    while (running.get()) {
      value = value * 1664525 + 1013904223;
      spinSink = value;
    }
  }

  /** Supplies ordinary runnable B samples after the supported tag transition. */
  private static void runnableContextB(AtomicBoolean running) {
    long value = 1;
    while (running.get()) {
      value = value * 1664525 + 1013904223;
      spinSink = value;
    }
  }
}
