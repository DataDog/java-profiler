/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;

import static org.junit.jupiter.api.Assertions.assertSame;
import static org.junit.jupiter.api.Assertions.assertTrue;

/** Verifies TaskBlock TLS initialization for threads created before profiler startup. */
public class JavaProfilerTaskBlockPreExistingThreadTest extends AbstractProfilerTest {
  private static final long BLOCKER = 0x7401L;
  private static final long UNBLOCKING_SPAN_ID = 0x7402L;

  private ExecutorService preExistingWorker;
  private Thread preExistingThread;

  @Override
  protected void beforeProfilerStart() throws Exception {
    preExistingWorker =
        Executors.newSingleThreadExecutor(
            task -> {
              Thread worker = new Thread(task, "taskblock-pre-existing");
              worker.setDaemon(true);
              return worker;
            });
    preExistingThread = preExistingWorker.submit(Thread::currentThread).get();
  }

  /** Stops the worker that was deliberately created before profiler startup. */
  @AfterEach
  public void stopPreExistingWorker() throws InterruptedException {
    if (preExistingWorker == null) return;
    preExistingWorker.shutdownNow();
    assertTrue(
        preExistingWorker.awaitTermination(5, TimeUnit.SECONDS),
        "Pre-existing TaskBlock worker did not terminate");
  }

  /** Verifies that the first post-start TaskBlock call initializes carrier-local TLS. */
  @Test
  public void preExistingThreadCanRecordTaskBlockAfterProfilerStart() throws Exception {
    Future<Boolean> recorded =
        preExistingWorker.submit(
            () -> {
              assertSame(preExistingThread, Thread.currentThread());
              long token = profiler.beginTaskBlock();
              assertTrue(token != 0, "Pre-existing thread must initialize TaskBlock TLS");
              Thread.sleep(200L);
              return profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID);
            });

    assertTrue(recorded.get(5, TimeUnit.SECONDS));
    stopProfiler();

    IItemCollection events = verifyEvents("datadog.TaskBlock");
    TaskBlockAssertions.assertContainsStackTrace(events);
    TaskBlockAssertions.assertContains(
        events, 0L, 0L, BLOCKER, UNBLOCKING_SPAN_ID);
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }
}
