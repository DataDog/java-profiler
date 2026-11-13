/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import java.util.concurrent.locks.LockSupport;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

public class CollapsingSleepTest extends AbstractProfilerTest {

  @Test
  public void testSleep() {
    Assumptions.assumeTrue(!Platform.isJ9());
    System.out.println(
        "Debug counters before registration (snapshot): " + profiler.getDebugCounters());
    registerCurrentThreadForWallClockProfiling();
    long ts = System.nanoTime();
    long workloadStart = ts;
    long waitTime = 1_000_000_000L; // 1mil ns == 1s
    do {
      LockSupport.parkNanos(waitTime);
      waitTime -= (System.nanoTime() - ts);
      ts = System.nanoTime();
    } while (waitTime > 1_000);
    long workloadElapsed = System.nanoTime() - workloadStart;
    stopProfiler();
    JfrEvents events = verifyEvents("datadog.MethodSample");
    assertTrue(events.hasItems());
    long totalWeight = 0;
    long missingWeight = 0;
    long minWeight = Long.MAX_VALUE;
    long maxWeight = Long.MIN_VALUE;
    for (JfrEvent item : events) {
      totalWeight += item.getLong(WEIGHT, 0);
      Long weight = item.getLong(WEIGHT);
      if (weight == null) {
        missingWeight++;
      } else {
        minWeight = Math.min(minWeight, weight);
        maxWeight = Math.max(maxWeight, weight);
      }
    }
    String diagnostics =
        "workloadElapsedNs="
            + workloadElapsed
            + ", eventCount="
            + events.count()
            + ", totalWeight="
            + totalWeight
            + ", missingOrNonNumericWeight="
            + missingWeight
            + ", minWeight="
            + (missingWeight == events.count() ? "none" : minWeight)
            + ", maxWeight="
            + (missingWeight == events.count() ? "none" : maxWeight);
    System.out.println("CollapsingSleepTest diagnostics: " + diagnostics);
    System.out.println("Debug counters after stop (snapshot): " + profiler.getDebugCounters());
    assertTrue(totalWeight > 700, diagnostics);
    assertTrue(events.count() > 9);
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=~1ms";
  }
}
