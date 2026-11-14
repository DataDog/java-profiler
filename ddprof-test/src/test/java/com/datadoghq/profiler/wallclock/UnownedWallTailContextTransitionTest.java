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
import java.nio.file.Paths;
import java.time.Instant;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.LockSupport;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

/**
 * Verifies original custom context on real deferred ASGCT wall samples across owner transitions.
 */
public class UnownedWallTailContextTransitionTest extends AbstractProfilerTest {
  private static final String WORKER = "unowned-origin-context";
  private static final String[] FIELDS = {TAG_1, TAG_2, TAG_3};
  private static volatile long spinSink;
  private final AtomicLong workerNativeTid = new AtomicLong(-1);

  @Override
  protected void withTestAssumptions() {
    Assumptions.assumeTrue(!Platform.isJ9() && Platform.isJavaVersionAtLeast(11));
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter="
        + (unfiltered() ? "" : "0")
        + ",wallprecheck=true,jvmtistacks=false,attributes=tag1;tag2;tag3";
  }

  /** Selects whether unowned observations require explicit context membership. */
  protected boolean unfiltered() {
    return false;
  }

  /** Registers the native owner, then leaves unfiltered workers outside context. */
  private void registerUnownedWorker() {
    workerNativeTid.set(WallClockBlockTrackerTestSupport.currentTid());
    profiler.addThread();
    if (unfiltered()) {
      profiler.removeThread();
    }
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
                registerUnownedWorker();
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
      awaitWorkerWeightedTailReady(workerFailure);
      int blockedSamples = 0;
      for (int i = 0; i < snapshots.length; i++) {
        snapshots[i] =
            Files.createTempFile(Paths.get("/tmp/recordings"), "unowned-context-dump-" + i, ".jfr");
        System.out.println("===> attribution recording: " + snapshots[i]);
        dump(snapshots[i]);
        JfrEvents samples = verifyEvents(snapshots[i], "datadog.MethodSample", false);
        for (JfrEvent sample : samples) {
          if (isWorker(sample)) {
            assertResolved(sample);
            // Unfiltered startup samples can precede tag initialization and the blocked origin.
            if (unfiltered() && !sample.getStackTraceString().contains("blockedOriginA")) {
              continue;
            }
            assertTags(sample, tagsA);
            assertEquals(0L, sample.getLong(SPAN_ID, -1));
            assertEquals(0L, sample.getLong(LOCAL_ROOT_SPAN_ID, -1));
            blockedSamples++;
          }
        }
      }
      assertTrue(blockedSamples > 0, "No original worker samples across retained dumps");
      // Require this worker's fresh pending tail after the last dump. Other native Java I/O
      // workers can now legitimately contribute to the global suppression counters.
      awaitWorkerWeightedTailReady(workerFailure);
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
      if (stack.contains("blockedOriginA") && "PARKED".equals(state) && weight > 1) {
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
        assertTrue(
            time < transitionStart.get(), "Deferred A must keep its original epoch timestamp");
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
    assertTrue(
        after.getOrDefault("wc_unowned_blocked_tail_recorded", 0L)
            > before.getOrDefault("wc_unowned_blocked_tail_recorded", 0L),
        "No deferred epoch segment was actually serialized");
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
                registerUnownedWorker();
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
      awaitWorkerWeightedTailReady(workerFailure);
      releaseA.countDown();
      assertTrue(readyB.await(10, TimeUnit.SECONDS), "Worker did not enter traced B");
      assertNull(workerFailure.get(), "Worker failed before traced B");
      long retainedPending =
          WallClockBlockTrackerTestSupport.pendingUnownedWeight((int) workerNativeTid.get());
      for (int i = 0; i < 100; i++) {
        Thread.sleep(1);
        retainedPending = assertPendingDoesNotGrow(retainedPending);
      }
      for (int i = 0; i < snapshots.length; i++) {
        snapshots[i] =
            Files.createTempFile(
                Paths.get("/tmp/recordings"), "unowned-span-context-dump-" + i, ".jfr");
        System.out.println("===> attribution recording: " + snapshots[i]);
        dump(snapshots[i]);
        recordings[i] = verifyEvents(snapshots[i], "datadog.MethodSample", false);
        retainedPending = assertPendingDoesNotGrow(retainedPending);
      }
      int tracedWorkerSamples = 0;
      for (int i = 0; i < snapshots.length; i++) {
        for (JfrEvent sample : recordings[i]) {
          if (isWorker(sample) && sample.getStackTraceString().contains("runnableTracedContextB")) {
            assertEquals(7102L, sample.getLong(SPAN_ID, -1));
            assertEquals(7101L, sample.getLong(LOCAL_ROOT_SPAN_ID, -1));
            assertEquals(
                1L, sample.getLong(WEIGHT, 0), "Traced B must remain an ordinary unit sample");
            tracedWorkerSamples++;
          }
        }
      }
      assertTrue(tracedWorkerSamples > 0, "No actual traced B worker samples in retained dumps");
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
        if (recording == recordings[3]
            && stack.contains("blockedOriginA")
            && "PARKED".equals(state)
            && weight > 1) {
          originalTails++;
          assertTrue(time < clearStart.get(), "Deferred A must keep its original epoch timestamp");
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
    assertTrue(
        after.getOrDefault("wc_unowned_blocked_tail_recorded", 0L)
            > before.getOrDefault("wc_unowned_blocked_tail_recorded", 0L),
        "No deferred epoch segment was actually serialized");
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
                registerUnownedWorker();
                readyA.countDown();
                blockedOriginA(releaseA);
                readyInactive.countDown();
                runnableAcrossStop(restartedSignal, running);
                if (!running.get()) {
                  return;
                }
                // Rebind the surviving owner to the new recording before sampling.
                setTags(tagsB);
                registerUnownedWorker();
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
    Path recording =
        Files.createTempFile(Paths.get("/tmp/recordings"), "unowned-context-restart-", ".jfr");
    System.out.println("===> attribution recording: " + recording);
    boolean restarted = false;
    worker.start();
    try {
      assertTrue(readyA.await(10, TimeUnit.SECONDS), "Worker did not register A");
      awaitWorkerWeightedTailReady(workerFailure);
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
  /** Old A weight may survive the span boundary: allow its drain, never new B growth. */
  private long assertPendingDoesNotGrow(long previous) {
    if (!WallClockBlockTrackerTestSupport.available()) return previous;
    long pending =
        WallClockBlockTrackerTestSupport.pendingUnownedWeight((int) workerNativeTid.get());
    assertTrue(
        pending <= previous,
        "The known-span worker grew unowned pending weight: " + previous + " -> " + pending);
    return pending;
  }

  /** Requires the target worker, not ambient native owners, to supply weighted-tail coverage. */
  private void awaitWorkerWeightedTailReady(AtomicReference<Throwable> failure) throws Exception {
    long deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(10);
    while (System.nanoTime() < deadline) {
      assertNull(failure.get(), "Worker failed before required weighted tail");
      if (WallClockBlockTrackerTestSupport.available()) {
        int tid = (int) workerNativeTid.get();
        assertTrue(tid > 0, "Worker did not publish its actual native TID");
        long pending = WallClockBlockTrackerTestSupport.pendingUnownedWeight(tid);
        long segment = WallClockBlockTrackerTestSupport.maxPendingUnownedSegmentWeight(tid);
        if (pending >= 2 && pending <= 5 && segment >= 2) {
          System.out.println(
              "Attribution worker tail ready: tid="
                  + tid
                  + ", pending="
                  + pending
                  + ", segment="
                  + segment);
          return;
        }
      } else {
        Path witness =
            Files.createTempFile(Paths.get("/tmp/recordings"), "unowned-worker-readiness-", ".jfr");
        try {
          dump(witness);
          for (JfrEvent sample : verifyEvents(witness, "datadog.MethodSample", false)) {
            if (isWorker(sample)
                && sample.getStackTraceString().contains("blockedOriginA")
                && "PARKED".equals(sample.getEnumName(THREAD_STATE))
                && sample.getLong(WEIGHT, 0) > 1) {
              return;
            }
          }
        } finally {
          if (!Boolean.getBoolean("ddprof_test.keep_jfrs")) Files.deleteIfExists(witness);
        }
      }
      Thread.sleep(1);
    }
    throw new AssertionError(
        "No target-worker weighted-tail coverage within bounded readiness wait");
  }

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

  /** Keeps the acting thread in A until its real pending tail is ready for the transition. */
  private void blockedOriginA(CountDownLatch release) throws InterruptedException {
    release.await();
    if (!WallClockBlockTrackerTestSupport.available()) return;
    int tid = WallClockBlockTrackerTestSupport.currentTid();
    assertEquals(workerNativeTid.get(), (long) tid, "Readiness must run on the actual A worker");
    long deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(5);
    while (System.nanoTime() < deadline) {
      long pending = WallClockBlockTrackerTestSupport.pendingUnownedWeight(tid);
      // The real fallback ratio is 10 (WallClockBlockTracker::BlockState). A mid-cycle
      // observation on this worker avoids the main-to-worker periodic-rollup race.
      // One actual epoch segment must coalesce: aggregate units can span different epochs.
      long segment = WallClockBlockTrackerTestSupport.maxPendingUnownedSegmentWeight(tid);
      if (pending >= 2 && pending <= 5 && segment >= 2) return;
      if (Thread.interrupted()) throw new InterruptedException("A readiness was interrupted");
      LockSupport.parkNanos(TimeUnit.MILLISECONDS.toNanos(1));
    }
    throw new AssertionError("A worker never acquired a real mid-cycle tail before transition");
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
