/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfilerTestSupport;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.Platform;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.Instant;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.LockSupport;
import java.util.function.BiConsumer;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

/** Verifies original custom context on deferred native wall samples across owner transitions. */
public class UnownedWallTailContextTransitionTest extends AbstractProfilerTest {
  private static final String WORKER = "unowned-origin-context";
  private static final String[] FIELDS = {TAG_1, TAG_2, TAG_3};
  private static final String METHOD_SAMPLE = "datadog.MethodSample";
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

  /** Checks retained fields across dumps with a controlled same-epoch tail in debug builds. */
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
                blockedOriginA(
                    releaseA,
                    ready,
                    () -> {
                      Instant now = Instant.now();
                      transitionStart.set(now.getEpochSecond() * 1_000_000_000L + now.getNano());
                      setTags(tagsB);
                      readyB.countDown();
                    });
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
      assertNull(workerFailure.get(), "Worker failed before origin setup");
      if (!controlledTail()) awaitWorkerWeightedTailReady(workerFailure);
      int blockedSamples = 0;
      for (int i = 0; i < snapshots.length; i++) {
        snapshots[i] =
            Files.createTempFile(Paths.get("/tmp/recordings"), "unowned-context-dump-" + i, ".jfr");
        System.out.println("===> attribution recording: " + snapshots[i]);
        dump(snapshots[i]);
        blockedSamples +=
            checkSamples(
                    snapshots[i],
                    false,
                    (acc, sample) -> {
                      if (isWorker(sample)) {
                        assertResolved(sample);
                        // Unfiltered startup samples can precede tag initialization and the
                        // blocked origin.
                        if (unfiltered()
                            && !sample.getStackTraceString().contains("blockedOriginA")) {
                          return;
                        }
                        assertTags(sample, tagsA);
                        assertEquals(0L, sample.getLong(SPAN_ID, -1));
                        assertEquals(0L, sample.getLong(LOCAL_ROOT_SPAN_ID, -1));
                        acc.matched++;
                      }
                    })
                .matched;
      }
      assertTrue(blockedSamples > 0, "No original worker samples across retained dumps");
      if (!controlledTail()) awaitWorkerWeightedTailReady(workerFailure);
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
    Samples samples =
        checkSamples(
            null,
            true,
            (acc, sample) -> {
              if (isWorker(sample)) {
                checkTransitionSample(acc, sample, tagsA, tagsB, transitionStart.get());
              }
            });
    int originalTails = samples.matched;
    Set<Long> ordinaryTimes = samples.timesB;
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
                blockedOriginA(
                    releaseA,
                    readyA,
                    () -> {
                      profiler.setTraceContext(7101, 7102, 0, 7103, -1, null, -1, null);
                      setTags(tagsB);
                      readyB.countDown();
                    });
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
    Set<Long> tracedTimes = new HashSet<>();
    Set<Long> clearedTimes = new HashSet<>();
    worker.start();
    try {
      assertTrue(readyA.await(10, TimeUnit.SECONDS), "Worker did not register A");
      assertNull(workerFailure.get(), "Worker failed before origin setup");
      if (!controlledTail()) awaitWorkerWeightedTailReady(workerFailure);
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
        Samples samples =
            checkSamples(
                snapshots[i],
                false,
                (acc, sample) ->
                    checkSpanSample(acc, sample, tagsA, tagsB, tagsC, clearStart, null));
        tracedTimes.addAll(samples.timesB);
        clearedTimes.addAll(samples.timesC);
        retainedPending = assertPendingDoesNotGrow(retainedPending);
      }
      long tracedWorkerSamples = 0;
      for (Path snapshot : snapshots) {
        tracedWorkerSamples +=
            reduceEvents(
                snapshot,
                "datadog.MethodSample",
                () -> new long[1],
                (count, sample) -> {
                  if (isWorker(sample)
                      && sample.getStackTraceString().contains("runnableTracedContextB")) {
                    assertEquals(7102L, sample.getLong(SPAN_ID, -1));
                    assertEquals(7101L, sample.getLong(LOCAL_ROOT_SPAN_ID, -1));
                    assertEquals(
                        1L,
                        sample.getLong(WEIGHT, 0),
                        "Traced B must remain an ordinary unit sample");
                    count[0]++;
                  }
                })[0];
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
    Map<Long, Long> retainedEpochs = new HashMap<>();
    for (JfrEvent epoch : verifyEvents("datadog.WallClockSamplingEpoch", false)) {
      assertNotNull(epoch.getLong("startTime"), "Epoch start is required");
      assertNotNull(epoch.getLong("samplePoolSize"), "Epoch population is required");
      assertNotNull(epoch.getLong("numSuccessfulSamples"), "Epoch denominator is required");
      retainedEpochs.put(epoch.getLong("startTime"), epoch.getLong("numSuccessfulSamples"));
    }
    Samples last =
        checkSamples(
            null,
            true,
            (acc, sample) ->
                checkSpanSample(acc, sample, tagsA, tagsB, tagsC, clearStart, retainedEpochs));
    tracedTimes.addAll(last.timesB);
    clearedTimes.addAll(last.timesC);
    int originalTails = last.matched;
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
                blockedOriginAUntilStop(releaseA);
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
      Set<Long> ordinaryTimes =
          checkSamples(
                  recording,
                  true,
                  (acc, sample) -> {
                    if (isWorker(sample)) {
                      checkRestartedSample(acc, sample, tagsB);
                    }
                  })
              .timesB;

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

  /** Verifies null rejection and failure propagation through the signal-blocked driver. */
  @Test
  public void controlledTailRejectsInvalidCallbacks() {
    assertThrows(
        NullPointerException.class, () -> JavaProfilerTestSupport.withUnownedWallTailForTest(null));
    Assumptions.assumeTrue(controlledTail(), "Requires debug tail driver");
    registerUnownedWorker();
    try {
      IllegalStateException failure = new IllegalStateException("owner transition failed");
      assertEquals(
          failure,
          assertThrows(
              IllegalStateException.class,
              () ->
                  JavaProfilerTestSupport.withUnownedWallTailForTest(
                      () -> {
                        throw failure;
                      })));
    } finally {
      profiler.removeThread();
    }
  }

  /** Small per-recording result, so no recording's MethodSample events are retained. */
  private static final class Samples {
    long count;
    int matched;
    final Set<Long> timesB = new HashSet<>();
    final Set<Long> timesC = new HashSet<>();
  }

  /**
   * Streams one recording's MethodSamples into a fresh Samples; a parse retry restarts from a new
   * one. A null recording reads the profiler's own, whose path this package cannot see.
   */
  private Samples checkSamples(
      Path recording, boolean failOnEmpty, BiConsumer<Samples, JfrEvent> check) {
    BiConsumer<Samples, JfrEvent> counted =
        (acc, sample) -> {
          acc.count++;
          check.accept(acc, sample);
        };
    Samples samples =
        recording == null
            ? reduceEvents(METHOD_SAMPLE, Samples::new, counted)
            : reduceEvents(recording, METHOD_SAMPLE, Samples::new, counted);
    System.out.println(METHOD_SAMPLE + " count: " + samples.count);
    if (failOnEmpty) {
      assertTrue(samples.count > 0, METHOD_SAMPLE + " was empty for " + getProfilerCommand());
    }
    return samples;
  }

  /** Checks one worker sample of the tag-only transition and folds its coverage into acc. */
  private static void checkTransitionSample(
      Samples acc, JfrEvent sample, String[] tagsA, String[] tagsB, long transitionStart) {
    assertResolved(sample);
    String stack = sample.getStackTraceString();
    String state = sample.getEnumName(THREAD_STATE);
    long weight = sample.getLong(WEIGHT, 0);
    Long time = sample.getLong("startTime");
    assertNotNull(time, "Worker sample has no capture time");
    if (stack.contains("blockedOriginA") && "PARKED".equals(state) && weight > 1) {
      acc.matched++;
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
      assertTrue(time < transitionStart, "Deferred A must keep its original epoch timestamp");
      assertTags(sample, tagsA);
      assertEquals(0L, sample.getLong(SPAN_ID, -1));
      assertEquals(0L, sample.getLong(LOCAL_ROOT_SPAN_ID, -1));
    }
    if ("RUNNABLE".equals(state) && stack.contains("runnableContextB")) {
      assertEquals(1L, weight, "B must not acquire already suppressed A time");
      assertTags(sample, tagsB);
      assertEquals(0L, sample.getLong(SPAN_ID, -1));
      assertEquals(0L, sample.getLong(LOCAL_ROOT_SPAN_ID, -1));
      acc.timesB.add(time);
    }
  }

  /**
   * Checks one span-test sample and folds its coverage into acc. Non-null retainedEpochs marks the
   * final recording, the only one whose deferred A tail must resolve to a retained epoch.
   */
  private static void checkSpanSample(
      Samples acc,
      JfrEvent sample,
      String[] tagsA,
      String[] tagsB,
      String[] tagsC,
      AtomicLong clearStart,
      Map<Long, Long> retainedEpochs) {
    if (!isWorker(sample)) {
      return;
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
      acc.timesB.add(time);
    }
    if ("RUNNABLE".equals(state) && stack.contains("runnableContextC")) {
      assertEquals(1L, weight, "Cleared C must not consume suppressed A time");
      assertTags(sample, tagsC);
      assertEquals(0L, sample.getLong(SPAN_ID, -1));
      assertEquals(0L, sample.getLong(LOCAL_ROOT_SPAN_ID, -1));
      acc.timesC.add(time);
    }
    if (retainedEpochs != null
        && stack.contains("blockedOriginA")
        && "PARKED".equals(state)
        && weight > 1) {
      acc.matched++;
      Long successfulSamples = retainedEpochs.get(time);
      assertNotNull(
          successfulSamples, "Standalone dump lost the retained tail's originating epoch");
      assertTrue(successfulSamples > 0, "Origin scale must be usable");
      assertTrue(time < clearStart.get(), "Deferred A must keep its original epoch timestamp");
      assertTags(sample, tagsA);
      assertEquals(0L, sample.getLong(SPAN_ID, -1));
      assertEquals(0L, sample.getLong(LOCAL_ROOT_SPAN_ID, -1));
    }
  }

  /** Checks one worker sample of the restarted recording and folds its coverage into acc. */
  private static void checkRestartedSample(Samples acc, JfrEvent sample, String[] tagsB) {
    assertResolved(sample);
    String stack = sample.getStackTraceString();
    assertFalse(stack.contains("blockedOriginA"), "Prior recording's origin leaked into restart");
    if (stack.contains("runnableRestartedContextB")
        && "RUNNABLE".equals(sample.getEnumName(THREAD_STATE))) {
      assertEquals(1L, sample.getLong(WEIGHT, 0), "New B consumed prior-recording weight");
      assertTags(sample, tagsB);
      assertEquals(0L, sample.getLong(SPAN_ID, -1));
      assertEquals(0L, sample.getLong(LOCAL_ROOT_SPAN_ID, -1));
      Long time = sample.getLong("startTime");
      assertNotNull(time, "Restarted B sample has no capture time");
      acc.timesB.add(time);
    }
  }

  private boolean controlledTail() {
    return isDebugBuild() || isAsan();
  }

  /** Natural epoch splits need not leave weight > 1; debug drivers seed one retained segment. */
  private void blockedOriginA(CountDownLatch release, CountDownLatch ready, Runnable transition)
      throws InterruptedException {
    if (controlledTail()) {
      assertTrue(
          JavaProfilerTestSupport.withUnownedWallTailForTest(
              () -> {
                ready.countDown();
                try {
                  assertTrue(
                      release.await(10, TimeUnit.SECONDS), "Controller did not release origin A");
                } catch (InterruptedException failure) {
                  Thread.currentThread().interrupt();
                  throw new AssertionError("Origin A wait interrupted", failure);
                }
                transition.run();
              }),
          "Controlled origin setup failed");
    } else {
      ready.countDown();
      blockedOriginA(release);
      transition.run();
    }
  }

  /** Writes through the supported JNI setter, without activating a span or an owned block. */
  private void setTags(String[] values) {
    for (int i = 0; i < values.length; i++) {
      assertTrue(
          profiler.setContextValue(i, values[i]), "Tag setter rejected configured field " + i);
    }
  }

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

  // The controller proves readiness before stop, which flushes the pending tail.
  // Retain an identifiable origin frame without waiting for new units after stop.
  private static void blockedOriginAUntilStop(CountDownLatch release) throws InterruptedException {
    release.await();
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
