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
import com.datadoghq.profiler.Platform;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

/** A dump reports the elapsed part of an open owned interval; the exit reports the rest. */
public class TaskBlockOpenIntervalSegmentsTest extends AbstractProfilerTest {
  private static final long BLOCKER = 0x16858L;
  private static final long UNBLOCKING_SPAN_ID = 0x16859L;
  private static final long ONE_MS_NANOS = 1_000_000L;
  // NativeBlockKind::STREAM_SOCKET_READ, the high half of a native block's blocker.
  private static final long STREAM_SOCKET_READ_KIND = 8L;

  @Test
  public void sleepSpanningTwoDumpsYieldsThreeContiguousSegments() throws Exception {
    String name = "taskblock-segments-sleep";
    AtomicLong outerNanos = new AtomicLong();
    AtomicBoolean recorded = new AtomicBoolean();
    CountDownLatch began = new CountDownLatch(1);
    Thread worker =
        worker(
            name,
            () -> {
              long before = System.nanoTime();
              long token = profiler.beginTaskBlock();
              assertTrue(token != 0, "interval was not armed");
              began.countDown();
              Thread.sleep(3_000L);
              recorded.set(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
              outerNanos.set(System.nanoTime() - before);
            });
    AtomicReference<Throwable> error = start(worker);
    assertTrue(began.await(5, TimeUnit.SECONDS));
    Path first = dumpAfter(1_000L);
    Path second = dumpAfter(1_000L);
    join(worker, error);
    assertTrue(recorded.get(), "the exit must record the last segment");
    stopProfiler();

    List<JfrEvent> segments = new ArrayList<>();
    segments.addAll(eventsFor(first, name, 1));
    segments.addAll(eventsFor(second, name, 1));
    segments.addAll(eventsIn(verifyEvents("datadog.TaskBlock", false), name, 1));
    assertContiguous(segments);
    long total = 0;
    for (int i = 0; i < segments.size(); i++) {
      JfrEvent segment = segments.get(i);
      boolean last = i == segments.size() - 1;
      assertEquals(!last, segment.getBoolean("continued"), "continued on segment " + i);
      assertEquals(last ? UNBLOCKING_SPAN_ID : 0L, segment.getLong("unblockingSpanId"));
      assertEquals(last ? BLOCKER : 0L, segment.getLong("blocker"));
      assertFalse(segment.getStackTrace().frames().isEmpty(), "segment " + i + " has a stack");
      total += segment.getLong("duration");
    }
    assertTrue(total >= 3_000L * ONE_MS_NANOS - ONE_MS_NANOS, "sum " + total + " < sleep");
    assertTrue(total <= outerNanos.get() + ONE_MS_NANOS, "sum " + total + " exceeds the interval");
  }

  @Test
  public void backToBackDumpsKeepSegmentsContiguous() throws Exception {
    String name = "taskblock-segments-carry";
    CountDownLatch began = new CountDownLatch(1);
    Thread worker =
        worker(
            name,
            () -> {
              long token = profiler.beginTaskBlock();
              began.countDown();
              Thread.sleep(600L);
              assertTrue(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
            });
    AtomicReference<Throwable> error = start(worker);
    assertTrue(began.await(5, TimeUnit.SECONDS));
    Path first = dumpAfter(200L);
    // A second dump right away usually finds a segment under 1 ms and carries it.
    Path second = dumpAfter(0L);
    join(worker, error);
    stopProfiler();

    List<JfrEvent> segments = new ArrayList<>();
    segments.addAll(eventsFor(first, name, 1));
    segments.addAll(eventsFor(second, name, -1));
    segments.addAll(eventsIn(verifyEvents("datadog.TaskBlock", false), name, 1));
    assertContiguous(segments);
    for (JfrEvent segment : segments) {
      assertTrue(segment.getLong("duration") >= ONE_MS_NANOS, "no segment under 1 ms is emitted");
    }
  }

  @Test
  public void subMillisecondIntervalsEmitNothingAcrossDumps() throws Exception {
    String name = "taskblock-segments-short";
    AtomicBoolean stop = new AtomicBoolean();
    Thread worker =
        worker(
            name,
            () -> {
              while (!stop.get()) {
                long token = profiler.beginTaskBlock();
                profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID);
              }
            });
    AtomicReference<Throwable> error = start(worker);
    List<Path> dumps = new ArrayList<>();
    for (int i = 0; i < 5; i++) dumps.add(dumpAfter(20L));
    stop.set(true);
    join(worker, error);
    stopProfiler();
    List<JfrEvent> events = new ArrayList<>();
    for (Path dump : dumps) events.addAll(eventsFor(dump, name, -1));
    events.addAll(eventsIn(verifyEvents("datadog.TaskBlock", false), name, -1));
    // A pause can stretch an interval past 1 ms; only a closing segment may be shorter.
    for (int i = 0; i < events.size(); i++) {
      boolean closesContinued = i > 0 && events.get(i - 1).getBoolean("continued");
      assertTrue(
          events.get(i).getLong("duration") >= ONE_MS_NANOS || closesContinued,
          "a sub-millisecond interval was reported: " + events.get(i));
    }
  }

  @Test
  public void abandonedPairedIntervalIsNotReportedWhileThreadParksElsewhere() throws Exception {
    String name = "taskblock-segments-abandoned";
    CountDownLatch parked = new CountDownLatch(1);
    CountDownLatch release = new CountDownLatch(1);
    Thread worker =
        worker(
            name,
            () -> {
              assertTrue(profiler.beginTaskBlock() != 0);
              // No endTaskBlock: the interval is abandoned while the thread parks.
              parked.countDown();
              assertTrue(release.await(10, TimeUnit.SECONDS));
            });
    AtomicReference<Throwable> error = start(worker);
    assertTrue(parked.await(5, TimeUnit.SECONDS));
    Path dump = dumpAfter(200L);
    release.countDown();
    join(worker, error);
    stopProfiler();
    eventsFor(dump, name, 0);
  }

  @Test
  public void stopReportsOpenPartAndRestartDoesNotReReportIt() throws Exception {
    String name = "taskblock-segments-stop";
    CountDownLatch began = new CountDownLatch(1);
    AtomicBoolean endRecorded = new AtomicBoolean(true);
    Thread worker =
        worker(
            name,
            () -> {
              long token = profiler.beginTaskBlock();
              began.countDown();
              try {
                Thread.sleep(10_000L);
              } catch (InterruptedException restartedRecording) {
                // Interrupted once the next recording has started.
              }
              endRecorded.set(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
            });
    AtomicReference<Throwable> error = start(worker);
    assertTrue(began.await(5, TimeUnit.SECONDS));
    Thread.sleep(300L);
    stopProfiler();
    List<JfrEvent> atStop = eventsIn(verifyEvents("datadog.TaskBlock", false), name, 1);
    assertTrue(atStop.get(0).getBoolean("continued"), "the block was still open at stop");
    assertTrue(atStop.get(0).getLong("duration") >= 250L * ONE_MS_NANOS);

    Path next = Files.createTempFile("taskblock-segments-restart-", ".jfr");
    profiler.execute("start," + getProfilerCommand() + ",jfr,file=" + next.toAbsolutePath());
    try {
      worker.interrupt();
      join(worker, error);
      Thread.sleep(50L);
    } finally {
      profiler.stop();
    }
    assertFalse(endRecorded.get(), "the exit must not report time from the stopped recording");
    eventsFor(next, name, 0);
  }

  @Test
  public void nativeReadSpanningDumpContributesToBothChunks() throws Exception {
    Assumptions.assumeTrue(Platform.isLinux(), "native I/O hooks are Linux-only");
    System.loadLibrary("ddproftest");
    String name = "taskblock-segments-native-read";
    CountDownLatch reading = new CountDownLatch(1);
    try (ServerSocket server = new ServerSocket(0)) {
      Thread reader =
          worker(
              name,
              () -> {
                try (Socket socket = new Socket("127.0.0.1", server.getLocalPort())) {
                  InputStream input = socket.getInputStream();
                  reading.countDown();
                  assertEquals(1, input.read());
                }
              });
      AtomicReference<Throwable> error = start(reader);
      Path first;
      try (Socket accepted = server.accept()) {
        assertTrue(reading.await(5, TimeUnit.SECONDS));
        first = dumpAfter(400L);
        Thread.sleep(300L);
        OutputStream output = accepted.getOutputStream();
        output.write(1);
        output.flush();
        join(reader, error);
      }
      stopProfiler();
      List<JfrEvent> segments = new ArrayList<>();
      segments.addAll(socketReads(JfrEvents.load(first, "datadog.TaskBlock"), name));
      segments.addAll(socketReads(verifyEvents("datadog.TaskBlock", false), name));
      assertEquals("IO_WAIT", segments.get(0).getEnumName("observedBlockingState"));
      assertTrue(segments.get(0).getBoolean("continued"));
      assertFalse(segments.get(1).getBoolean("continued"));
      assertContiguous(segments);
    }
  }

  @Override
  protected boolean isPlatformSupported() {
    return TaskBlockAssertions.isSupported();
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }

  private Path dumpAfter(long millis) throws Exception {
    if (millis > 0) Thread.sleep(millis);
    Path recording = Files.createTempFile("taskblock-segments-", ".jfr");
    dump(recording);
    return recording;
  }

  /** Loads the worker's TaskBlocks; expected < 0 accepts any count. */
  private static List<JfrEvent> eventsFor(Path recording, String thread, int expected)
      throws Exception {
    return eventsIn(JfrEvents.load(recording, "datadog.TaskBlock"), thread, expected);
  }

  private static List<JfrEvent> eventsIn(JfrEvents events, String thread, int expected) {
    return eventsIn(events, thread, expected, false);
  }

  /**
   * The worker's connect can record its own TaskBlock when it takes 1 ms; only the stream read is
   * under test. Dump-time segments carry no blocker, so they are kept by their continued flag.
   */
  private static List<JfrEvent> socketReads(JfrEvents events, String thread) {
    return eventsIn(events, thread, 1, true);
  }

  private static List<JfrEvent> eventsIn(
      JfrEvents events, String thread, int expected, boolean socketReadsOnly) {
    List<JfrEvent> result = new ArrayList<>();
    StringBuilder seen = new StringBuilder();
    for (JfrEvent event : events) {
      assertNotNull(event.getBoolean("continued"), "TaskBlock must carry the continued field");
      if (!thread.equals(event.getThreadName("eventThread"))) continue;
      seen.append(" [blocker=0x")
          .append(Long.toHexString(event.getLong("blocker")))
          .append(" duration=")
          .append(event.getLong("duration"))
          .append(" continued=")
          .append(event.getBoolean("continued"))
          .append(']');
      boolean dumpSegment = event.getBoolean("continued") && event.getLong("blocker") == 0L;
      if (socketReadsOnly
          && !dumpSegment
          && (event.getLong("blocker") >>> 32) != STREAM_SOCKET_READ_KIND) {
        continue;
      }
      result.add(event);
    }
    if (expected >= 0) {
      assertEquals(expected, result.size(), "TaskBlocks of " + thread + ":" + seen);
    }
    result.sort(Comparator.comparingLong(e -> e.getLong("startTime")));
    return result;
  }

  /** Each segment starts where the previous one ended; only the last is not continued. */
  private static void assertContiguous(List<JfrEvent> segments) {
    assertFalse(segments.isEmpty());
    for (int i = 1; i < segments.size(); i++) {
      JfrEvent previous = segments.get(i - 1);
      long previousEnd = previous.getLong("startTime") + previous.getLong("duration");
      long gap = segments.get(i).getLong("startTime") - previousEnd;
      // Each chunk converts ticks to nanos from its own anchor, so boundaries drift by
      // microseconds.
      assertTrue(Math.abs(gap) <= 100_000L, "gap or overlap of " + gap + " ns before segment " + i);
      assertTrue(previous.getBoolean("continued"), "segment " + (i - 1) + " is continued");
    }
    assertFalse(segments.get(segments.size() - 1).getBoolean("continued"));
  }

  private static Thread worker(String name, ThrowingRunnable action) {
    return new Thread(
        () -> {
          try {
            action.run();
          } catch (Throwable t) {
            throw new RuntimeException(t);
          }
        },
        name);
  }

  private static AtomicReference<Throwable> start(Thread thread) {
    AtomicReference<Throwable> error = new AtomicReference<>();
    thread.setUncaughtExceptionHandler((t, e) -> error.set(e));
    thread.start();
    return error;
  }

  private static void join(Thread thread, AtomicReference<Throwable> error) throws Exception {
    thread.join(10_000L);
    assertFalse(thread.isAlive(), thread.getName() + " did not finish");
    if (error.get() != null) throw new AssertionError(error.get());
  }

  @FunctionalInterface
  private interface ThrowingRunnable {
    void run() throws Exception;
  }
}
