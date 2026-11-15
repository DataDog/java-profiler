/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.*;

import com.datadoghq.profiler.AbstractProcessProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Collections;
import java.util.concurrent.atomic.AtomicReference;

/** Isolates the process-wide Java monitor ownership setting from the parent test JVM. */
public final class DelegatedObjectWaitScenario extends AbstractProcessProfilerTest {
  private static final long BLOCKER = 0x7751L;
  private static final long UNBLOCKING_SPAN = 0x7752L;
  private static final String WORKER = "delegated-object-wait-worker";

  /** Runs a fresh delegated bridge and checks every field of its single completed wait. */
  public static void assertRecording(String command) throws Exception {
    new DelegatedObjectWaitScenario().verify(command);
  }

  private void verify(String command) throws Exception {
    Path recording = Files.createTempFile("delegated-object-wait-", ".jfr");
    try {
      AtomicReference<String> identity = new AtomicReference<>();
      LaunchResult result =
          launch(
              "profiler-delegated-object-wait",
              Collections.emptyList(),
              recording.toAbsolutePath() + "|" + command,
              line -> {
                if (line.startsWith("[delegated-object-wait] ")) {
                  identity.set(line.substring("[delegated-object-wait] ".length()));
                  return LineConsumerResult.STOP;
                }
                return LineConsumerResult.CONTINUE;
              },
              null);
      assertTrue(result.inTime);
      assertEquals(0, result.exitCode);
      assertNotNull(identity.get(), "The actual worker must report its Java identity");
      long workerId = Long.parseLong(identity.get());
      int count = 0;
      JfrEvents events = JfrEvents.load(recording, "datadog.TaskBlock");
      for (JfrEvent event : events) {
        count++;
        assertNotNull(event.get("eventThread"));
        assertEquals(Long.valueOf(workerId), event.getThreadJavaId("eventThread"));
        assertEquals(WORKER, event.getThreadName("eventThread"));
        assertEquals("WAITING", event.getString("observedBlockingState"));
        assertEquals(Long.valueOf(BLOCKER), event.getLong("blocker"));
        assertEquals(Long.valueOf(UNBLOCKING_SPAN), event.getLong("unblockingSpanId"));
        assertEquals(Long.valueOf(0L), event.getLong("spanId"));
        assertEquals(Long.valueOf(0L), event.getLong("localRootSpanId"));
        assertNotNull(event.getLong("startTime"));
        assertNotNull(event.getLong("duration"));
        assertTrue(
            event.getLong("duration") >= 200_000_000L, "Wait must pass the duration threshold");
        assertFalse(event.getStackTrace().isEmpty());
        assertTrue(
            event.getStackTraceString().contains("delegatedWaitWorkload"),
            "Stack must identify the real Java wait workload");
      }
      assertEquals(
          1, count, "Java hooks and native callbacks must not duplicate the delegated wait");
    } finally {
      Files.deleteIfExists(recording);
    }
  }

  /** Child entry point called before any default bridge initialization. */
  public static void record(String argument) throws Exception {
    String[] parts = argument.split("\\|", 2);
    JavaProfiler profiler = JavaProfiler.getInstance(null, null, true);
    assertTrue(profiler.isMonitorWaitEventsDelegated());
    profiler.execute("start," + parts[1] + ",jfr,file=" + parts[0]);
    AtomicReference<Throwable> failure = new AtomicReference<>();
    Thread worker =
        new Thread(
            () -> {
              try {
                delegatedWaitWorkload(profiler);
              } catch (Throwable error) {
                failure.set(error);
              }
            },
            WORKER);
    worker.start();
    worker.join(5_000L);
    assertFalse(worker.isAlive());
    if (failure.get() != null) throw new AssertionError(failure.get());
    profiler.stop();
    System.out.println("[delegated-object-wait] " + worker.getId());
  }

  private static void delegatedWaitWorkload(JavaProfiler profiler) throws InterruptedException {
    Object monitor = new Object();
    synchronized (monitor) {
      long token = ProfilerOwnedBlockHooks.blockEnter(profiler, 5);
      assertTrue(token != 0, "Java OBJECT_WAIT hook must own the interval");
      try {
        long deadline = System.nanoTime() + 250_000_000L;
        long remaining;
        while ((remaining = deadline - System.nanoTime()) > 0) {
          monitor.wait(remaining / 1_000_000L, (int) (remaining % 1_000_000L));
        }
      } finally {
        ProfilerOwnedBlockHooks.blockExit(profiler, token, BLOCKER, UNBLOCKING_SPAN);
      }
    }
  }
}
