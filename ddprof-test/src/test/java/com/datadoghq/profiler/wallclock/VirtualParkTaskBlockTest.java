/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.JfrFrame;
import com.datadoghq.profiler.JfrStackTrace;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.Callable;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.LockSupport;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

/** Verifies TaskBlocks reported by the virtual-thread park exit hook. */
public class VirtualParkTaskBlockTest extends AbstractProfilerTest {
  private static final long BLOCKER = 0x5601L;
  private static final long UNBLOCKING_SPAN_ID = 0x5602L;
  private static final long PARK_MILLIS = 50;
  private static final int DEEP_FRAMES = 24;

  @Test
  public void unmountedParkIsAttributedToTheVirtualThread() throws Exception {
    long[] interval = new long[2];
    VirtualRun run =
        onVirtualThread(
            () -> {
              interval[0] = System.currentTimeMillis();
              boolean recorded = parkAndReport(BLOCKER, PARK_MILLIS);
              interval[1] = System.currentTimeMillis();
              return recorded;
            });
    assertTrue(run.recorded, "an untraced 50 ms virtual park must be recorded");
    assertEquals(1L, profiler.getDebugCounters().getOrDefault("task_block_virtual_emitted", 0L));
    stopProfiler();

    JfrEvent event = exactlyOne(verifyEvents("datadog.TaskBlock"), BLOCKER);
    Map<String, Object> thread = eventThread(event);
    assertEquals(run.threadId, ((Number) thread.get("javaThreadId")).longValue());
    assertEquals(0L, ((Number) thread.get("osThreadId")).longValue());
    assertEquals(run.threadName, thread.get("javaName"));
    assertTrue(
        event.getLong("duration") >= TimeUnit.MILLISECONDS.toNanos(PARK_MILLIS),
        "duration must cover the measured park");
    assertEquals("PARKED", event.getString("observedBlockingState"));
    assertEquals(Long.valueOf(0L), event.getLong("spanId"));
    assertEquals(Long.valueOf(UNBLOCKING_SPAN_ID), event.getLong("unblockingSpanId"));
    String stack = event.getStackTraceString();
    assertNotNull(stack);
    assertTrue(
        stack.startsWith("com.datadoghq.profiler.JavaProfiler.virtualParkExit()"),
        "the native frame is skipped, as for platform parks: " + stack);
    assertTrue(stack.contains("VirtualParkTaskBlockTest.parkAndReport()"), stack);

    // No carrier may own TaskBlock time for the interval the virtual thread was unmounted.
    for (JfrEvent other : verifyEvents("datadog.TaskBlock")) {
      if (other.getLong("blocker", Long.MIN_VALUE) == BLOCKER) continue;
      String name = other.getThreadName("eventThread");
      if (name == null || !name.startsWith("ForkJoinPool")) continue;
      long startMillis = TimeUnit.NANOSECONDS.toMillis(other.getLong("startTime"));
      long endMillis = startMillis + TimeUnit.NANOSECONDS.toMillis(other.getLong("duration"));
      assertFalse(
          startMillis < interval[1] && endMillis > interval[0],
          "carrier TaskBlock overlaps the virtual park: " + other);
    }
  }

  @Test
  public void longNonAsciiNameIsTruncatedToItsFirst128Chars() throws Exception {
    StringBuilder name = new StringBuilder("vt-\u00e9\u4e2d");
    while (name.length() < 300) name.append('x');
    VirtualRun run =
        onVirtualThread(
            () -> {
              Thread.currentThread().setName(name.toString());
              return parkAndReport(BLOCKER, 5);
            });
    assertTrue(run.recorded);
    stopProfiler();
    JfrEvent event = exactlyOne(verifyEvents("datadog.TaskBlock"), BLOCKER);
    assertEquals(name.substring(0, 128), eventThread(event).get("javaName"));
  }

  @Test
  public void supplementaryAndNulCharsInTheNameReadBackExactly() throws Exception {
    String name = "vt-\uD83D\uDE00-\u00e9\u4e2d-a\u0000b";
    assertEquals(name, recordedVirtualThreadName(name));
  }

  @Test
  public void surrogatePairIsNotSplitAtTheTruncationBoundary() throws Exception {
    StringBuilder name = new StringBuilder();
    while (name.length() < 127) name.append('x');
    String prefix = name.toString();
    // The pair occupies units 127 and 128, so the high half is dropped rather than split.
    assertEquals(prefix, recordedVirtualThreadName(prefix + "\uD83D\uDE00tail"));
  }

  @Test
  public void unpairedSurrogateInTheNameIsReplaced() throws Exception {
    assertEquals("a\uFFFDb", recordedVirtualThreadName("a\uD83Db"));
  }

  private String recordedVirtualThreadName(String name) throws Exception {
    VirtualRun run =
        onVirtualThread(
            () -> {
              Thread.currentThread().setName(name);
              return parkAndReport(BLOCKER, 5);
            });
    assertTrue(run.recorded);
    stopProfiler();
    JfrEvent event = exactlyOne(verifyEvents("datadog.TaskBlock"), BLOCKER);
    return (String) eventThread(event).get("javaName");
  }

  @Test
  public void migratedParkYieldsExactlyOneEvent() throws Exception {
    Assumptions.assumeTrue(
        Runtime.getRuntime().availableProcessors() >= 2, "migration needs two carriers");
    VirtualRun run = null;
    for (int attempt = 0; attempt < 50 && run == null; attempt++) {
      VirtualRun candidate = parkUnparkedFromPlatformThread();
      if (!candidate.carrierBefore.equals(candidate.carrierAfter)) run = candidate;
    }
    assertNotNull(run, "the virtual thread never remounted on another carrier");
    assertTrue(run.recorded);
    stopProfiler();

    JfrEvent event = exactlyOne(verifyEvents("datadog.TaskBlock"), BLOCKER);
    assertEquals(run.threadId, ((Number) eventThread(event).get("javaThreadId")).longValue());
    assertEquals(0L, ((Number) eventThread(event).get("osThreadId")).longValue());
  }

  @Test
  public void remountedStackKeepsCallersBelowThePark() throws Exception {
    VirtualRun run = onVirtualThread(() -> deepPark(DEEP_FRAMES));
    assertTrue(run.recorded);
    stopProfiler();

    JfrEvent event = exactlyOne(verifyEvents("datadog.TaskBlock"), BLOCKER);
    JfrStackTrace stack = event.getStackTrace();
    // Below JDK 27 the JVMTI root VirtualThread.run is not an entry frame, so the writer marks
    // the trace truncated even when every frame is present; the frames are checked instead.
    System.out.println(
        "VIRTUAL_PARK_STACK truncated=" + stack.isTruncated() + "\n" + event.getStackTraceString());
    int deep = 0;
    for (JfrFrame frame : stack.frames()) {
      if ("deepPark".equals(frame.methodName())) deep++;
    }
    assertEquals(DEEP_FRAMES + 1, deep, "every caller frame below the park must be present");
    List<JfrFrame> frames = stack.frames();
    JfrFrame bottom = frames.get(frames.size() - 1);
    assertTrue(
        "JVM Continuation".equals(bottom.methodName())
            || event.getStackTraceString().contains("VirtualThread.run"),
        "the stack must reach the virtual thread's entry: " + event.getStackTraceString());
  }

  @Test
  public void shortParkIsSkippedAsTooShort() throws Exception {
    // The counters are process-wide: other threads' short monitor blocks can also raise them.
    // The sleep keeps the reported intervals inside the recording.
    Thread.sleep(20);
    long before = counter("task_block_skipped_too_short");
    VirtualRun run =
        onVirtualThread(
            () ->
                ProfilerOwnedBlockHooks.virtualParkExit(
                    profiler, TimeUnit.MICROSECONDS.toNanos(500), BLOCKER, 0));
    assertFalse(run.recorded);
    assertTrue(counter("task_block_skipped_too_short") >= before + 1);
    assertEquals(0L, counter("task_block_virtual_emitted"));
    assertEquals(0L, counter("task_block_virtual_skipped_before_recording"));
    VirtualRun negative =
        onVirtualThread(() -> ProfilerOwnedBlockHooks.virtualParkExit(profiler, -1, BLOCKER, 0));
    assertFalse(negative.recorded);
    assertTrue(counter("task_block_skipped_too_short") >= before + 2);
    assertEquals(0L, counter("task_block_virtual_skipped_before_recording"));
    stopProfiler();
    assertFalse(
        TaskBlockAssertions.containsBlocker(verifyEvents("datadog.TaskBlock", false), BLOCKER));
  }

  @Test
  public void tracedVirtualThreadIsSkipped() throws Exception {
    // The reported interval must start after the recording did to reach the context check.
    Thread.sleep(2 * PARK_MILLIS);
    long before = counter("task_block_skipped_trace_context");
    VirtualRun run =
        onVirtualThread(
            () -> {
              profiler.setTraceContext(0x5603L, 0x5604L, 0L, 0x5604L, -1, null, -1, null);
              try {
                return ProfilerOwnedBlockHooks.virtualParkExit(
                    profiler, TimeUnit.MILLISECONDS.toNanos(PARK_MILLIS), BLOCKER, 0);
              } finally {
                profiler.clearTraceContext();
              }
            });
    assertFalse(run.recorded);
    assertTrue(counter("task_block_skipped_trace_context") >= before + 1);
    assertEquals(0L, counter("task_block_virtual_skipped_before_recording"));
    long control = 0x5605L;
    assertTrue(onVirtualThread(() -> parkAndReport(control, 5)).recorded, "untraced control");
    stopProfiler();
    JfrEvents events = verifyEvents("datadog.TaskBlock");
    assertFalse(TaskBlockAssertions.containsBlocker(events, BLOCKER));
    assertTrue(TaskBlockAssertions.containsBlocker(events, control));
  }

  @Test
  public void intervalSpanningStopAndStartIsRejected() throws Exception {
    CountDownLatch restarted = new CountDownLatch(1);
    CountDownLatch parked = new CountDownLatch(1);
    AtomicReference<Throwable> failure = new AtomicReference<>();
    Path second =
        Files.createTempFile(Paths.get("/tmp/recordings"), "virtual-park-restart-", ".jfr");
    boolean secondActive = false;
    long control = 0x5606L;
    try {
      Thread virtual =
          startVirtualThread(
              () -> {
                try {
                  long start = System.nanoTime();
                  parked.countDown();
                  assertTrue(restarted.await(10, TimeUnit.SECONDS));
                  assertFalse(
                      ProfilerOwnedBlockHooks.virtualParkExit(
                          profiler, System.nanoTime() - start, BLOCKER, 0),
                      "an interval that began in the previous recording must be rejected");
                  assertTrue(parkAndReport(control, 5), "a later park must still be recorded");
                } catch (Throwable error) {
                  failure.set(error);
                }
              });
      assertTrue(parked.await(10, TimeUnit.SECONDS));
      stopProfiler();
      profiler.execute("start," + getProfilerCommand() + ",jfr,file=" + second.toAbsolutePath());
      secondActive = true;
      restarted.countDown();
      virtual.join(10_000);
      assertFalse(virtual.isAlive());
      if (failure.get() != null) throw new AssertionError(failure.get());
      assertEquals(
          1L,
          profiler
              .getDebugCounters()
              .getOrDefault("task_block_virtual_skipped_before_recording", 0L));
      profiler.stop();
      secondActive = false;
      JfrEvents events = verifyEvents(second, "datadog.TaskBlock", true);
      assertFalse(TaskBlockAssertions.containsBlocker(events, BLOCKER));
      assertTrue(TaskBlockAssertions.containsBlocker(events, control));
    } finally {
      if (secondActive) profiler.stop();
      Files.deleteIfExists(second);
    }
  }

  @Override
  protected void withTestAssumptions() {
    Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(21), "virtual threads require JDK 21");
  }

  @Override
  protected boolean isPlatformSupported() {
    return TaskBlockAssertions.parkSupported();
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }

  private long counter(String name) {
    return profiler.getDebugCounters().getOrDefault(name, 0L);
  }

  private boolean parkAndReport(long blocker, long millis) {
    long start = System.nanoTime();
    long deadline = start + TimeUnit.MILLISECONDS.toNanos(millis);
    long remaining;
    while ((remaining = deadline - System.nanoTime()) > 0) {
      LockSupport.parkNanos(remaining);
    }
    return ProfilerOwnedBlockHooks.virtualParkExit(
        profiler, System.nanoTime() - start, blocker, UNBLOCKING_SPAN_ID);
  }

  private boolean deepPark(int depth) {
    return depth == 0 ? parkAndReport(BLOCKER, PARK_MILLIS) : deepPark(depth - 1);
  }

  /** Parks until a platform thread unparks it, after the other carriers were kept busy. */
  private VirtualRun parkUnparkedFromPlatformThread() throws Exception {
    VirtualRun run = new VirtualRun();
    CountDownLatch parking = new CountDownLatch(1);
    AtomicReference<Throwable> failure = new AtomicReference<>();
    Thread virtual =
        startVirtualThread(
            () -> {
              try {
                run.carrierBefore = carrierName();
                long start = System.nanoTime();
                parking.countDown();
                LockSupport.park();
                run.carrierAfter = carrierName();
                if (!run.carrierBefore.equals(run.carrierAfter)) {
                  run.recorded =
                      ProfilerOwnedBlockHooks.virtualParkExit(
                          profiler, System.nanoTime() - start, BLOCKER, 0);
                }
              } catch (Throwable error) {
                failure.set(error);
              }
            });
    run.threadId = virtual.getId();
    assertTrue(parking.await(10, TimeUnit.SECONDS));
    List<Thread> busy = new ArrayList<>();
    for (int i = 0; i < Runtime.getRuntime().availableProcessors(); i++) {
      busy.add(startVirtualThread(VirtualParkTaskBlockTest::spinBriefly));
    }
    Thread.sleep(5);
    LockSupport.unpark(virtual);
    virtual.join(10_000);
    for (Thread thread : busy) thread.join(10_000);
    assertFalse(virtual.isAlive());
    if (failure.get() != null) throw new AssertionError(failure.get());
    return run;
  }

  private static void spinBriefly() {
    long deadline = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(10);
    while (System.nanoTime() < deadline) {
      // Busy: keeps this carrier from picking up the unparked thread.
    }
  }

  /** {@code VirtualThread.toString()} names the mounted carrier after the last {@code @}. */
  private static String carrierName() {
    String description = Thread.currentThread().toString();
    return description.substring(description.lastIndexOf('@') + 1);
  }

  private VirtualRun onVirtualThread(Callable<Boolean> body) throws Exception {
    VirtualRun run = new VirtualRun();
    AtomicReference<Throwable> failure = new AtomicReference<>();
    Thread virtual =
        startVirtualThread(
            () -> {
              try {
                run.threadName = Thread.currentThread().getName();
                run.recorded = body.call();
              } catch (Throwable error) {
                failure.set(error);
              }
            });
    run.threadId = virtual.getId();
    virtual.join(10_000);
    assertFalse(virtual.isAlive());
    if (failure.get() != null) throw new AssertionError(failure.get());
    return run;
  }

  private static Thread startVirtualThread(Runnable body) throws Exception {
    Method start = Thread.class.getMethod("startVirtualThread", Runnable.class);
    return (Thread) start.invoke(null, body);
  }

  @SuppressWarnings("unchecked")
  private static Map<String, Object> eventThread(JfrEvent event) {
    Object thread = event.get("eventThread");
    assertTrue(thread instanceof Map, "eventThread must resolve to a thread-pool entry");
    return (Map<String, Object>) thread;
  }

  private static JfrEvent exactlyOne(JfrEvents events, long blocker) {
    JfrEvent match = null;
    for (JfrEvent event : events) {
      if (event.getLong("blocker", Long.MIN_VALUE) != blocker) continue;
      assertTrue(match == null, "more than one TaskBlock for blocker " + blocker);
      match = event;
    }
    assertNotNull(match, "no TaskBlock for blocker " + blocker);
    return match;
  }

  private static final class VirtualRun {
    volatile long threadId;
    volatile String threadName;
    volatile boolean recorded;
    volatile String carrierBefore;
    volatile String carrierAfter;
  }
}
