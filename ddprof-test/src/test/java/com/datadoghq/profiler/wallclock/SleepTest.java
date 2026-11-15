/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import java.util.concurrent.locks.LockSupport;
import org.junit.jupiter.api.Test;

public class SleepTest extends AbstractProfilerTest {

  @Test
  public void testSleep() {
    registerCurrentThreadForWallClockProfiling();
    long ts = System.nanoTime();
    long waitTime = 1_000_000_000L; // 1mil ns == 1s
    do {
      LockSupport.parkNanos(waitTime);
      waitTime -= (System.nanoTime() - ts);
      ts = System.nanoTime();
    } while (waitTime > 1_000);
    stopProfiler();
    assertTrue(verifyEvents("datadog.MethodSample").count() > 90);
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms";
  }
}
