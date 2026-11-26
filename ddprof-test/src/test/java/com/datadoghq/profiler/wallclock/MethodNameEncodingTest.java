/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrFrame;
import java.util.Set;
import java.util.TreeSet;
import java.util.concurrent.atomic.AtomicBoolean;
import org.junit.jupiter.api.Test;

/**
 * JVMTI reports method names as modified UTF-8 (U+1D49C as a 6-byte surrogate pair); the JFR symbol
 * pool must carry them as standard UTF-8. The class name stays ASCII: javac cannot write a
 * non-ASCII class file name when the platform file-name encoding is not UTF-8.
 */
public class MethodNameEncodingTest extends AbstractProfilerTest {
  // Built from code points: a misread source then fails to compile or fails the frame assertion
  // below, instead of garbling this constant and the identifier alike and still matching.
  private static final String METHOD =
      "burn" + new String(Character.toChars(0x1D49C)) + new String(Character.toChars(0xE9));
  private static final String CLASS = MethodNameEncodingTest.class.getName() + "$Spinner";

  static volatile long sink;

  static final class Spinner {
    static long burn𝒜é(AtomicBoolean stop) {
      long x = 0;
      while (!stop.get()) {
        x += System.nanoTime() & 1;
      }
      return x;
    }
  }

  @Test
  public void supplementaryMethodNameRoundTrips() throws Exception {
    AtomicBoolean stop = new AtomicBoolean();
    Thread worker =
        new Thread(
            () -> {
              registerCurrentThreadForWallClockProfiling();
              sink = Spinner.burn𝒜é(stop);
            },
            "method-name-encoding");
    worker.start();
    Thread.sleep(500);
    stop.set(true);
    worker.join();
    stopProfiler();

    Set<String> seen = new TreeSet<>();
    boolean found = false;
    for (JfrEvent event : verifyEvents("datadog.MethodSample", false)) {
      for (JfrFrame frame : event.getStackTrace().frames()) {
        String method = frame.methodName();
        if (method != null && method.startsWith("burn")) {
          seen.add(frame.className() + "." + method);
          found |= METHOD.equals(method) && CLASS.equals(frame.className());
        }
      }
    }
    assertTrue(found, "expected a frame " + CLASS + "." + METHOD + ", saw " + seen);
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=0";
  }
}
