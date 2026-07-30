/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Documents TaskBlock expectations for native I/O issued from an arbitrary JNI DSO.
 *
 * <p>The production interposer currently patches supported JDK networking libraries only.
 */
@Disabled("Arbitrary JNI DSO interposition is not currently supported")
public class NativeDsoTaskBlockTest extends AbstractProfilerTest {
  private static final int BLOCK_HOLD_MILLIS = 250;
  private static final int NATIVE_BLOCK_ATTEMPTS = 5;

  @Test
  public void blockingAccept4EmitsIoWaitTaskBlock() {
    long expectedBlocker =
        runNativeIoBlockRepeated(() -> NativeIoBlockHelper.blockingAccept4(BLOCK_HOLD_MILLIS));
    stopProfiler();
    assertNativeIoHelperCompleted(expectedBlocker);
  }

  @Test
  public void blockingPpollEmitsIoWaitTaskBlock() {
    long expectedBlocker =
        runNativeIoBlockRepeated(() -> NativeIoBlockHelper.blockingPpoll(BLOCK_HOLD_MILLIS));
    stopProfiler();
    assertNativeIoHelperCompleted(expectedBlocker);
  }

  @Test
  public void ownedNativeIoSuppressesWallSignalsBeforeCompletion() throws Exception {
    long before =
        profiler.getDebugCounters().getOrDefault("wc_signals_suppressed_owned_block", 0L);
    AtomicLong blocker = new AtomicLong();
    AtomicReference<Throwable> error = new AtomicReference<>();
    Thread worker =
        new Thread(
            () -> {
              try {
                blocker.set(NativeIoBlockHelper.blockingPpoll(BLOCK_HOLD_MILLIS));
              } catch (Throwable t) {
                error.set(t);
              }
            },
            "taskblock-native-suppression");

    worker.start();
    waitForCounterAbove("wc_signals_suppressed_owned_block", before, 5_000L);
    assertCompleted(worker, error);

    stopProfiler();
    assertNativeIoHelperCompleted(blocker.get());
  }

  @Test
  public void blockingPselectEmitsIoWaitTaskBlock() {
    long expectedBlocker =
        runNativeIoBlockRepeated(() -> NativeIoBlockHelper.blockingPselect(BLOCK_HOLD_MILLIS));
    stopProfiler();
    assertNativeIoHelperCompleted(expectedBlocker);
  }

  @Test
  public void blockingEpollWaitEmitsIoWaitTaskBlock() {
    long expectedBlocker =
        runNativeIoBlockRepeated(() -> NativeIoBlockHelper.blockingEpollWait(BLOCK_HOLD_MILLIS));
    stopProfiler();
    assertNativeIoHelperCompleted(expectedBlocker);
  }

  @Test
  public void blockingEpollPwaitEmitsIoWaitTaskBlock() {
    long expectedBlocker =
        runNativeIoBlockRepeated(() -> NativeIoBlockHelper.blockingEpollPwait(BLOCK_HOLD_MILLIS));
    stopProfiler();
    assertNativeIoHelperCompleted(expectedBlocker);
  }

  @Override
  protected boolean isPlatformSupported() {
    return Platform.isLinux();
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,wallscope=all,wallprecheck=true";
  }

  private void assertNativeIoHelperCompleted(long expectedBlocker) {
    assertTrue(expectedBlocker != 0L, "native I/O helper must report the expected blocker");
    IItemCollection taskBlockEvents = verifyEvents("datadog.TaskBlock", false);
    if (!taskBlockEvents.hasItems()) {
      throw new AssertionError(missingTaskBlockDiagnostic());
    }
    TaskBlockAssertions.assertNoAnchorFields(taskBlockEvents);
    TaskBlockAssertions.assertContainsStackTrace(taskBlockEvents);
    TaskBlockAssertions.assertContainsJavaType(taskBlockEvents, "NativeDsoTaskBlockTest");
    TaskBlockAssertions.assertNoCorrelationId(taskBlockEvents);
    TaskBlockAssertions.assertContainsObservedState(taskBlockEvents, "IO_WAIT");
    assertTrue(
        TaskBlockAssertions.containsBlocker(taskBlockEvents, expectedBlocker),
        "Expected native blocker " + expectedBlocker);
  }

  private long runNativeIoBlockRepeated(NativeIoBlockWorkload workload) {
    AtomicLong blocker = new AtomicLong();
    AtomicReference<Throwable> error = new AtomicReference<>();
    Thread worker =
        new Thread(
            () -> {
              try {
                for (int attempt = 0; attempt < NATIVE_BLOCK_ATTEMPTS; attempt++) {
                  blocker.set(workload.run());
                }
              } catch (Throwable t) {
                error.set(t);
              }
            },
            "taskblock-native-helper");
    worker.start();
    try {
      worker.join(5_000L);
    } catch (InterruptedException interrupted) {
      Thread.currentThread().interrupt();
      throw new AssertionError("interrupted while waiting for native helper", interrupted);
    }
    assertFalse(worker.isAlive(), "native helper did not complete");
    if (error.get() != null) {
      throw new AssertionError(error.get());
    }
    return blocker.get();
  }

  private String missingTaskBlockDiagnostic() {
    return "Expected native DSO TaskBlock after "
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

  private void waitForCounterAbove(String name, long baseline, long timeoutMillis)
      throws Exception {
    long deadline = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(timeoutMillis);
    while (System.nanoTime() < deadline) {
      if (profiler.getDebugCounters().getOrDefault(name, 0L) > baseline) {
        return;
      }
      Thread.sleep(10L);
    }
    throw new AssertionError("Counter did not increase: " + name);
  }

  private static void assertCompleted(
      Thread thread, AtomicReference<Throwable> error) throws InterruptedException {
    thread.join(5_000L);
    assertFalse(thread.isAlive(), thread.getName() + " did not complete");
    if (error.get() != null) {
      throw new AssertionError(error.get());
    }
  }

  @FunctionalInterface
  private interface NativeIoBlockWorkload {
    long run();
  }
}
