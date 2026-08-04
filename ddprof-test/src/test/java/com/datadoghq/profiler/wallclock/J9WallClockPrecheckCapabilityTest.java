/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Map;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;

/** Verifies that unsupported J9 wall sampling does not activate unfiltered precheck tracking. */
public class J9WallClockPrecheckCapabilityTest extends AbstractProfilerTest {
  private static final int OSTHREAD_STATE_SLEEPING = 7;
  private static final int BLOCK_HOLD_MILLIS = 500;

  /** Ensures owned-block hooks stay inactive when the selected wall engine cannot consume them. */
  @Test
  public void unsupportedEngineDoesNotActivateRegistry() {
    long token = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);

    assertEquals(0L, token, "J9WallClock must not activate unfiltered precheck tracking");
  }

  /** Ensures unsupported precheck falls back to ordinary wall samples without a profiling gap. */
  @Test
  public void blockingSocketReadFallsBackToMethodSample() throws Exception {
    String workerName = "taskblock-j9-jvmti-fallback";
    Map<String, Long> before = profiler.getDebugCounters();

    runBlockingSocketRead(workerName);

    Map<String, Long> after = profiler.getDebugCounters();
    assertEquals(
        before.getOrDefault("task_block_emitted", 0L),
        after.getOrDefault("task_block_emitted", 0L),
        "J9WallClock must not emit TaskBlock events");
    assertEquals(
        before.getOrDefault("wc_signals_suppressed_owned_block", 0L),
        after.getOrDefault("wc_signals_suppressed_owned_block", 0L),
        "J9WallClock must not suppress wall signals");

    stopProfiler();
    IItemCollection taskBlocks = verifyEvents("datadog.TaskBlock", false);
    assertFalse(
        TaskBlockAssertions.containsEventThread(taskBlocks, workerName),
        "J9WallClock fallback must not emit a TaskBlock for the worker");
    IItemCollection methodSamples = verifyEvents("datadog.MethodSample", false);
    assertTrue(
        TaskBlockAssertions.containsEventThread(methodSamples, workerName),
        "J9WallClock fallback must retain wall-clock MethodSample coverage for the worker");
  }

  @Override
  protected boolean isPlatformSupported() {
    return Platform.isJ9();
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,wallsampler=jvmti,filter=,wallprecheck=true";
  }

  private static void runBlockingSocketRead(String workerName) throws Exception {
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
        assertTrue(readAttempted.await(5, TimeUnit.SECONDS), "reader did not enter socket read");
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
}
