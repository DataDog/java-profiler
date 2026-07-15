/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import java.lang.reflect.Method;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;

import static org.junit.jupiter.api.Assertions.assertFalse;

/** Verifies pinned virtual-thread native I/O is attributed to its physical carrier. */
public class VirtualNativeIoTaskBlockTest extends AbstractProfilerTest {
  @Test
  public void nativeBlockOnVirtualThreadRemainsPhysicalCarrierTaskBlock() throws Exception {
    AtomicLong blocker = new AtomicLong();
    AtomicReference<Throwable> error = new AtomicReference<>();
    Thread thread = startVirtualThread(() -> {
      try {
        for (int attempt = 0; attempt < 3; attempt++) {
          blocker.set(NativeIoBlockHelper.blockingPpoll(200));
        }
      } catch (Throwable t) {
        error.set(t);
      }
    });

    long logicalThreadId = thread.getId();
    thread.join(5_000L);
    assertFalse(thread.isAlive(), "virtual thread did not complete");
    if (error.get() != null) throw new AssertionError(error.get());
    stopProfiler();

    IItemCollection events = verifyEvents("datadog.TaskBlock");
    TaskBlockAssertions.assertContainsObservedState(events, "IO_WAIT");
    TaskBlockAssertions.assertContainsStackTrace(events);
    TaskBlockAssertions.assertContainsJavaType(events, "VirtualNativeIoTaskBlockTest");
    TaskBlockAssertions.assertNoCorrelationId(events);
    TaskBlockAssertions.assertBlockerEventThreadDiffers(
        events, blocker.get(), logicalThreadId);
  }

  @Override
  protected boolean isPlatformSupported() {
    return Platform.isLinux() && Platform.isJavaVersionAtLeast(21);
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,wallprecheck=true";
  }

  private static Thread startVirtualThread(Runnable task) throws Exception {
    Method startVirtualThread = Thread.class.getMethod("startVirtualThread", Runnable.class);
    return (Thread) startVirtualThread.invoke(null, task);
  }
}
