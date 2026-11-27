/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.memleak;

import static org.junit.jupiter.api.Assertions.*;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.Platform;
import java.lang.management.ManagementFactory;
import java.lang.ref.WeakReference;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.FutureTask;
import java.util.function.BiConsumer;
import org.junit.jupiter.api.Test;

/** Verifies current-allocation liveness after a completed collection and snapshot. */
public class GCGenerationsTest extends AbstractProfilerTest {
  private static final String LIVE_EVENT = "datadog.HeapLiveObject";
  private static final int OBJECTS_PER_WORKER = 128;
  private static final int ARRAY_LENGTH = 80_000;

  @Override
  protected String getProfilerCommand() {
    return "memory=128,generations=true";
  }

  @Override
  protected boolean isPlatformSupported() {
    return !(Platform.isJavaVersion(8) || Platform.isJ9() || Platform.isZing());
  }

  @Test
  public void shouldGetLiveObjectSamples() throws Exception {
    MemLeakTarget first = new MemLeakTarget();
    MemLeakTarget second = new MemLeakTarget();
    long started = epochNanos();
    try {
      runWorkers(first, second);
      collect();
      stopProfiler();
      assertCurrentSamples(currentSamples(started, epochNanos() + 1_000_000));
      first.assertReachable(true);
      second.assertReachable(true);
    } finally {
      first.release();
      second.release();
    }
  }

  @Test
  public void shouldNotReportCollectedCurrentObjects() throws Exception {
    MemLeakTarget first = new MemLeakTarget();
    MemLeakTarget second = new MemLeakTarget();
    Path retained = Files.createTempFile("gc-generations-retained", ".jfr");
    long started = epochNanos();
    try {
      runWorkers(first, second);
      collect();
      dump(retained);
      assertCurrentSamples(currentSamples(retained, started, epochNanos() + 1_000_000));
      first.assertReachable(true);
      second.assertReachable(true);
      first.release();
      second.release();
      collect();
      first.assertReachable(false);
      second.assertReachable(false);
      stopProfiler();
      assertEquals(0, currentSamples(started, epochNanos() + 1_000_000));
    } finally {
      first.release();
      second.release();
      Files.deleteIfExists(retained);
    }
  }

  @Test
  public void shouldNotReportPreviousRecordingAdmissions() throws Exception {
    MemLeakTarget first = new MemLeakTarget();
    MemLeakTarget second = new MemLeakTarget();
    MemLeakTarget third = new MemLeakTarget();
    MemLeakTarget fourth = new MemLeakTarget();
    long started = epochNanos();
    try {
      runWorkers(first, second);
      collect();
      stopProfiler();
      long firstFinished = epochNanos() + 1_000_000;
      assertCurrentSamples(currentSamples(started, firstFinished));

      // Disjoint admission windows: the first cohort's window ends before the second's starts.
      while (epochNanos() <= firstFinished) {
        Thread.sleep(1);
      }
      setupProfiler(testInfo);
      long restarted = epochNanos();
      runWorkers(third, fourth);
      collect();
      stopProfiler();
      long previous =
          reduceEvents(
              LIVE_EVENT,
              () -> new long[1],
              (matches, event) -> {
                if (isTargetAdmittedDuring(event, started, firstFinished)) {
                  matches[0]++;
                }
              })[0];
      // Liveness state is released at stop, so the still-reachable first cohort is not reported.
      assertEquals(0, previous, "entries admitted by the previous recording are not retained");
      assertCurrentSamples(currentSamples(restarted, epochNanos() + 1_000_000));
      first.assertReachable(true);
      second.assertReachable(true);
      third.assertReachable(true);
      fourth.assertReachable(true);
    } finally {
      first.release();
      second.release();
      third.release();
      fourth.release();
    }
  }

  private long currentSamples(long started, long finished) {
    return reduceEvents(LIVE_EVENT, () -> new long[1], currentSampleCounter(started, finished))[0];
  }

  private long currentSamples(Path recording, long started, long finished) {
    return reduceEvents(
        recording, LIVE_EVENT, () -> new long[1], currentSampleCounter(started, finished))[0];
  }

  /**
   * Admission time, not flush time, distinguishes current arrays from retained historical entries.
   */
  private static BiConsumer<long[], JfrEvent> currentSampleCounter(long started, long finished) {
    return (matches, event) -> {
      if (isTargetAdmittedDuring(event, started, finished)) {
        assertNotNull(event.getLong("age"));
        assertTrue(event.getLong("age") > 0, "target survived the confirmed collection");
        assertNotNull(event.getDouble(WEIGHT));
        assertTrue(event.getDouble(WEIGHT) > 0);
        assertNotNull(event.get(STACK_TRACE));
        assertTrue(event.getStackTraceString().contains("GCGenerationsTest$MemLeakTarget.run"));
        matches[0]++;
      }
    };
  }

  private static boolean isTargetAdmittedDuring(JfrEvent event, long started, long finished) {
    assertNotNull(event.getClassName("objectClass"));
    assertNotNull(event.getLong("startTime"));
    assertNotNull(event.getLong(SIZE));
    return "[I".equals(event.getClassName("objectClass"))
        && event.getLong(SIZE) >= ARRAY_LENGTH * 4L
        && event.getLong(SIZE) <= ARRAY_LENGTH * 4L + 32
        && event.getLong("startTime") >= started
        && event.getLong("startTime") <= finished;
  }

  private static void assertCurrentSamples(long count) {
    assertTrue(count > 0, "snapshot must contain live arrays admitted by this invocation");
  }

  private static long epochNanos() {
    // JFR's header clock is microsecond based; floor the lower bound and ceil the upper bound.
    return System.currentTimeMillis() * 1_000_000;
  }

  private static void collect() {
    long before = collectionCount();
    System.gc();
    assertTrue(collectionCount() > before, "explicit collection must complete before the snapshot");
  }

  private static long collectionCount() {
    return ManagementFactory.getGarbageCollectorMXBeans().stream()
        .mapToLong(gc -> Math.max(0, gc.getCollectionCount()))
        .sum();
  }

  private static void runWorkers(MemLeakTarget first, MemLeakTarget second) throws Exception {
    FutureTask<Void> firstTask = new FutureTask<>(first, null);
    FutureTask<Void> secondTask = new FutureTask<>(second, null);
    Thread firstThread = new Thread(firstTask);
    Thread secondThread = new Thread(secondTask);
    firstThread.start();
    secondThread.start();
    firstThread.join();
    secondThread.join();
    firstTask.get();
    secondTask.get();
  }

  /** Each worker owns at most 40 MiB; the caller releases its roots after the snapshot returns. */
  private static final class MemLeakTarget implements Runnable {
    private final List<int[]> roots = new ArrayList<>(OBJECTS_PER_WORKER);
    private final List<WeakReference<int[]>> observed = new ArrayList<>(OBJECTS_PER_WORKER);

    @Override
    public void run() {
      for (int i = 0; i < OBJECTS_PER_WORKER; i++) {
        int[] value = new int[ARRAY_LENGTH];
        roots.add(value);
        observed.add(new WeakReference<>(value));
      }
    }

    private void assertReachable(boolean expected) {
      assertEquals(OBJECTS_PER_WORKER, observed.size(), "the bounded workload completed");
      assertEquals(expected ? OBJECTS_PER_WORKER : 0, roots.size());
      for (int i = 0; i < observed.size(); i++) {
        int[] value = observed.get(i).get();
        assertEquals(expected, value != null, "confirmed target reachability");
        if (expected) {
          assertSame(roots.get(i), value, "worker roots remain owned through the snapshot");
        }
      }
    }

    private void release() {
      roots.clear();
    }
  }
}
