/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import java.util.Set;
import java.util.TreeSet;
import java.util.concurrent.atomic.AtomicBoolean;
import org.junit.jupiter.api.Test;

/**
 * JVMTI reports thread names as modified UTF-8 (supplementary characters as 6-byte surrogate pairs,
 * U+0000 as C0 80); the JFR thread table must carry them as standard UTF-8.
 */
public class ThreadNameEncodingTest extends AbstractProfilerTest {
  private static final String NAME = "worker-😀-é中-a\u0000b";

  @Test
  public void platformThreadNameRoundTrips() throws Exception {
    AtomicBoolean stop = new AtomicBoolean();
    Thread worker =
        new Thread(
            () -> {
              registerCurrentThreadForWallClockProfiling();
              long x = 0;
              while (!stop.get()) {
                x += System.nanoTime() & 1;
              }
              if (x == -1) {
                System.out.println(x);
              }
            },
            NAME);
    worker.start();
    Thread.sleep(500);
    stop.set(true);
    worker.join();
    stopProfiler();

    JfrEvents events = verifyEvents("datadog.MethodSample", false);
    Set<String> seen = new TreeSet<>();
    boolean found = false;
    for (JfrEvent event : events) {
      String name = event.getThreadName("eventThread");
      if (name != null) {
        seen.add(name);
        found |= NAME.equals(name);
      }
    }
    assertTrue(found, "expected a sample from a thread named " + NAME + ", saw " + seen);
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=0";
  }
}
