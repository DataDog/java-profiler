/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

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
import java.nio.file.Paths;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

/** Verifies native I/O hooks are fully restored and can be reinstalled across profiler restarts. */
public class NativeSocketTaskBlockLifecycleTest extends AbstractProfilerTest {
  private static final int BLOCK_HOLD_MILLIS = 250;
  private static final int NATIVE_BLOCK_ATTEMPTS = 5;
  private static final String READ_RELEASE_BOUNDARY = "native-first-read-release-boundary";
  private static final String STOP_BOUNDARY = "native-stop-inflight-boundary";

  @BeforeAll
  static void preloadJdkNetworking() throws Exception {
    if (Platform.isLinux()) {
      try (ServerSocket server = new ServerSocket(0);
          Socket client = new Socket("127.0.0.1", server.getLocalPort());
          Socket accepted = server.accept()) {
        // Exercise Java networking before profiler start so the native libraries
        // needed by socket reads are loaded before the initial patch pass.
      }
    }
  }

  @Test
  public void restartWithWallPrecheckDisabledStopsNativeSocketTaskBlocks() throws Exception {
    String enabledWorkerName = "taskblock-native-lifecycle-enabled";
    for (int attempt = 0; attempt < NATIVE_BLOCK_ATTEMPTS; attempt++) {
      runCompletedSocketRead(enabledWorkerName);
    }
    stopProfiler();
    assertIoWaitTaskBlockPresent(verifyEvents("datadog.TaskBlock", false), enabledWorkerName);

    Path disabledRecording =
        Files.createTempFile(
            Paths.get("/tmp/recordings"), "NativeSocketTaskBlockLifecycleTest_disabled_", ".jfr");
    boolean disabledRunning = false;
    try {
      profiler.execute(
          "start,wall=1ms,filter=,wallprecheck=false,jfr,file="
              + disabledRecording.toAbsolutePath());
      disabledRunning = true;
      String disabledWorkerName = "taskblock-native-lifecycle-disabled";
      for (int attempt = 0; attempt < NATIVE_BLOCK_ATTEMPTS; attempt++) {
        runCompletedSocketRead(disabledWorkerName);
      }
      profiler.stop();
      disabledRunning = false;

      JfrEvents disabledTaskBlocks = verifyEvents(disabledRecording, "datadog.TaskBlock", false);
      assertFalse(
          TaskBlockAssertions.containsEventThread(disabledTaskBlocks, disabledWorkerName),
          "wallprecheck=false restart must not emit a socket TaskBlock for the worker");
    } finally {
      if (disabledRunning) {
        profiler.stop();
      }
      Files.deleteIfExists(disabledRecording);
    }

    Path reenabledRecording =
        Files.createTempFile(
            Paths.get("/tmp/recordings"), "NativeSocketTaskBlockLifecycleTest_reenabled_", ".jfr");
    boolean reenabledRunning = false;
    try {
      profiler.execute(
          "start,wall=1ms,filter=,wallprecheck=true,jfr,file="
              + reenabledRecording.toAbsolutePath());
      reenabledRunning = true;
      String reenabledWorkerName = "taskblock-native-lifecycle-reenabled";
      for (int attempt = 0; attempt < NATIVE_BLOCK_ATTEMPTS; attempt++) {
        runCompletedSocketRead(reenabledWorkerName);
      }
      profiler.stop();
      reenabledRunning = false;

      assertIoWaitTaskBlockPresent(
          verifyEvents(reenabledRecording, "datadog.TaskBlock", false), reenabledWorkerName);
    } finally {
      if (reenabledRunning) {
        profiler.stop();
      }
      Files.deleteIfExists(reenabledRecording);
    }
  }

  @Test
  public void stopWhileSocketReadIsBlockedCleansUpAndAllowsReinstall() throws Exception {
    String workerName = "taskblock-native-stop-inflight";
    CountDownLatch firstReadAttempted = new CountDownLatch(1);
    CountDownLatch readAttempted = new CountDownLatch(1);
    AtomicReference<Throwable> error = new AtomicReference<>();
    ServerSocket server = new ServerSocket(0);
    Socket accepted = null;
    boolean stopped = false;

    Thread reader =
        new Thread(
            () -> {
              try (Socket socket = new Socket("127.0.0.1", server.getLocalPort())) {
                InputStream input = socket.getInputStream();
                firstReadAttempted.countDown();
                assertEquals(1, input.read(), "unexpected pre-stop socket byte");
                readAttempted.countDown();
                assertEquals(-1, input.read(), "post-stop socket read must finish at EOF");
              } catch (Throwable t) {
                error.set(t);
              }
            },
            workerName);

    try {
      reader.start();
      accepted = server.accept();
      assertTrue(
          firstReadAttempted.await(5, TimeUnit.SECONDS),
          "reader did not attempt the pre-stop socket read");
      Thread.sleep(BLOCK_HOLD_MILLIS);
      recordBoundary(READ_RELEASE_BOUNDARY);
      accepted.getOutputStream().write(1);
      assertTrue(
          readAttempted.await(5, TimeUnit.SECONDS),
          "reader did not attempt the blocking socket read");
      Thread.sleep(BLOCK_HOLD_MILLIS);
      assertTrue(reader.isAlive(), "socket read returned before the profiler was stopped");

      recordBoundary(STOP_BOUNDARY);
      stopProfiler();
      stopped = true;
      assertTrue(reader.isAlive(), "socket read returned before profiler shutdown completed");
    } finally {
      if (!stopped) {
        stopProfiler();
      }
      if (accepted != null) {
        accepted.close();
      }
      server.close();
      reader.join(5_000L);
    }

    assertFalse(reader.isAlive(), "blocked socket reader did not terminate");
    if (error.get() != null) {
      throw new AssertionError(error.get());
    }
    long readReleaseBoundary = boundaryNanos(READ_RELEASE_BOUNDARY);
    long stopBoundary = boundaryNanos(STOP_BOUNDARY);
    JfrEvents workerIoWait =
        verifyEvents("datadog.TaskBlock", false)
            .filter(
                event ->
                    "IO_WAIT".equals(event.getString("observedBlockingState"))
                        && workerName.equals(event.getThreadName("eventThread")));
    JfrEvents straddlingRead =
        workerIoWait.filter(
            event ->
                completesAtOrAfter(event, readReleaseBoundary)
                    && event.getLong("startTime") < readReleaseBoundary);
    assertTrue(straddlingRead.hasItems(), "the first read must straddle its release boundary");
    for (JfrEvent event : straddlingRead) {
      long completion = completionTimeNanos(event);
      assertTrue(completesAtOrAfter(event, completion), "completion at the boundary is included");
      assertFalse(
          completesAtOrAfter(event, completion + 1), "completion before the boundary is excluded");
    }
    assertTrue(
        workerIoWait.filter(event -> completionTimeNanos(event) < stopBoundary).hasItems(),
        "the controlled pre-stop read must produce an IO_WAIT before the stop boundary");
    // Stop reports the read still open as a continued segment; its exit must add nothing.
    assertFalse(
        workerIoWait
            .filter(
                event ->
                    completesAtOrAfter(event, stopBoundary)
                        && !Boolean.TRUE.equals(event.getBoolean("continued")))
            .hasItems(),
        "a native I/O operation returning after stop must not emit a closing TaskBlock");

    Path restartedRecording =
        Files.createTempFile(
            Paths.get("/tmp/recordings"),
            "NativeSocketTaskBlockLifecycleTest_inflight_restart_",
            ".jfr");
    boolean restarted = false;
    try {
      profiler.execute(
          "start,wall=1ms,filter=,wallprecheck=true,jfr,file="
              + restartedRecording.toAbsolutePath());
      restarted = true;
      String restartedWorkerName = "taskblock-native-stop-reinstalled";
      for (int attempt = 0; attempt < NATIVE_BLOCK_ATTEMPTS; attempt++) {
        runCompletedSocketRead(restartedWorkerName);
      }
      profiler.stop();
      restarted = false;

      JfrEvents restartedTaskBlocks = verifyEvents(restartedRecording, "datadog.TaskBlock", false);
      TaskBlockAssertions.assertNoAnchorFields(restartedTaskBlocks);
      TaskBlockAssertions.assertContainsStackTrace(restartedTaskBlocks);
      TaskBlockAssertions.assertContainsJavaType(
          restartedTaskBlocks, "NativeSocketTaskBlockLifecycleTest");
      assertTrue(
          TaskBlockAssertions.containsObservedStateForEventThread(
              restartedTaskBlocks, "IO_WAIT", restartedWorkerName),
          "socket TaskBlock hooks were not reinstalled after profiler shutdown");
    } finally {
      if (restarted) {
        profiler.stop();
      }
      Files.deleteIfExists(restartedRecording);
    }
  }

  private void recordBoundary(String markerName) {
    // Endpoint timestamps use the call's TSC ticks; ProfilerSetting timestamps use chunk start.
    assertTrue(profiler.recordTraceRoot(0, markerName, null, Integer.MAX_VALUE));
  }

  private long boundaryNanos(String markerName) {
    JfrEvents boundaries =
        verifyEvents("datadog.Endpoint")
            .filter(event -> markerName.equals(event.getString("endpoint")));
    assertEquals(1, boundaries.count(), "expected exactly one boundary marker: " + markerName);
    Long startTime = boundaries.iterator().next().getLong("startTime");
    assertNotNull(startTime, "the boundary marker must have a timestamp");
    return startTime;
  }

  private static boolean completesAtOrAfter(JfrEvent event, long boundaryNanos) {
    return completionTimeNanos(event) >= boundaryNanos;
  }

  private static long completionTimeNanos(JfrEvent event) {
    Long startTime = event.getLong("startTime");
    Long duration = event.getLong("duration");
    assertNotNull(startTime, "TaskBlock must have a start timestamp");
    assertNotNull(duration, "TaskBlock must have a duration");
    return startTime + duration;
  }

  @Override
  protected boolean isPlatformSupported() {
    return Platform.isLinux();
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }

  private void assertIoWaitTaskBlockPresent(JfrEvents taskBlockEvents, String workerName) {
    if (!taskBlockEvents.hasItems()) {
      fail(missingTaskBlockDiagnostic());
    }
    TaskBlockAssertions.assertNoAnchorFields(taskBlockEvents);
    TaskBlockAssertions.assertContainsStackTrace(taskBlockEvents);
    TaskBlockAssertions.assertContainsJavaType(
        taskBlockEvents, "NativeSocketTaskBlockLifecycleTest");
    TaskBlockAssertions.assertNoCorrelationId(taskBlockEvents);
    TaskBlockAssertions.assertContainsObservedState(taskBlockEvents, "IO_WAIT");
    assertTrue(
        TaskBlockAssertions.containsObservedStateForEventThread(
            taskBlockEvents, "IO_WAIT", workerName),
        "Expected native IO_WAIT TaskBlock for " + workerName);
  }

  private void runCompletedSocketRead(String workerName) throws Exception {
    CountDownLatch readAttempted = new CountDownLatch(1);
    AtomicReference<Throwable> error = new AtomicReference<>();

    try (ServerSocket server = new ServerSocket(0)) {
      Thread reader =
          new Thread(
              () -> {
                try (Socket socket = new Socket("127.0.0.1", server.getLocalPort())) {
                  InputStream input = socket.getInputStream();
                  readAttempted.countDown();
                  int value = input.read();
                  if (value != 1) {
                    throw new AssertionError("unexpected socket byte: " + value);
                  }
                } catch (Throwable t) {
                  error.set(t);
                }
              },
              workerName);

      reader.start();
      try (Socket accepted = server.accept()) {
        assertTrue(
            readAttempted.await(5, TimeUnit.SECONDS),
            "reader did not attempt the blocking socket read");
        Thread.sleep(BLOCK_HOLD_MILLIS);
        OutputStream output = accepted.getOutputStream();
        output.write(1);
        output.flush();
      }
      reader.join(5_000L);
      assertFalse(reader.isAlive(), "socket reader did not complete");
      if (error.get() != null) {
        throw new AssertionError(error.get());
      }
    }
  }

  private String missingTaskBlockDiagnostic() {
    return "Expected lifecycle native TaskBlock after "
        + NATIVE_BLOCK_ATTEMPTS
        + " blocked interval(s); emitted="
        + getRecordedCounterValue("task_block_emitted")
        + ", stack_capture_failed="
        + getRecordedCounterValue("task_block_stack_capture_failed")
        + ", skipped_too_short="
        + getRecordedCounterValue("task_block_skipped_too_short")
        + ", skipped_trace_context="
        + getRecordedCounterValue("task_block_skipped_trace_context")
        + ", record_failed="
        + getRecordedCounterValue("task_block_record_failed");
  }
}
