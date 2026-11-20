/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.JfrFrame;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;
import java.lang.management.ManagementFactory;
import java.lang.management.ThreadMXBean;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;

public class VtableReceiverFrameTest extends CStackAwareAbstractProfilerTest {
  private static final int MIN_WORK_ROUNDS = 10;
  private static final long MIN_WORK_CPU_NANOS = 2_000_000_000L;
  private static final long MAX_WORK_WALL_NANOS = 20_000_000_000L;

  public VtableReceiverFrameTest(@CStack String cstack) {
    super(cstack);
  }

  @Override
  protected String getProfilerCommand() {
    return "cpu=1ms";
  }

  // Vtable stubs and their receiver frames are HotSpot-specific. Checked before the profiler
  // starts, so the cstack mode CStackInjector falls back to on these JVMs is never used.
  @Override
  protected boolean isPlatformSupported() {
    return !(Platform.isZing() || Platform.isJ9() || Platform.isGraal());
  }

  abstract static class Shape {
    abstract int area();
  }

  // Three implementations force megamorphic vtable dispatch (JIT won't inline).
  // ThreadLocalRandom bodies ensure each variant is non-trivial and CPU-bound.
  static class Circle extends Shape {
    @Override
    public int area() {
      return ThreadLocalRandom.current().nextInt() | 1;
    }
  }

  static class Square extends Shape {
    @Override
    public int area() {
      return ThreadLocalRandom.current().nextInt() | 2;
    }
  }

  static class Triangle extends Shape {
    @Override
    public int area() {
      return ThreadLocalRandom.current().nextInt() | 4;
    }
  }

  /**
   * Runs at least {@link #MIN_WORK_ROUNDS} rounds and {@link #MIN_WORK_CPU_NANOS} of this thread's
   * CPU time, which cpu=1ms samples. A vtable stub is a few instructions, so a fixed loop count can
   * finish on a fast JIT before a sample lands in one. Capped by {@link #MAX_WORK_WALL_NANOS}.
   */
  private int profiledWork(Shape... shapes) {
    ThreadMXBean threads = ManagementFactory.getThreadMXBean();
    boolean cpuClock = threads.isCurrentThreadCpuTimeSupported();
    long wallStart = System.nanoTime();
    long cpuStart = cpuClock ? threads.getCurrentThreadCpuTime() : wallStart;
    int result = 0;
    for (int round = 0; ; round++) {
      for (int i = 0; i < 1_000_000; i++) {
        for (Shape shape : shapes) {
          result += shape.area();
        }
      }
      long now = System.nanoTime();
      long used = (cpuClock ? threads.getCurrentThreadCpuTime() : now) - cpuStart;
      if (round + 1 >= MIN_WORK_ROUNDS
          && (used >= MIN_WORK_CPU_NANOS || now - wallStart >= MAX_WORK_WALL_NANOS)) {
        return result;
      }
    }
  }

  /**
   * Verifies the synthetic method's declaring class, not unrelated Java callers in the trace.
   * {@code dwarf} unwinds through ASGCT stub recovery, {@code vm} through {@code walkVM}.
   */
  @RetryTest(5)
  @TestTemplate
  @ValueSource(strings = {"vm", "dwarf"})
  public void testVtableReceiverFrameInCpuSamples(@CStack String cstack) throws Exception {
    waitForProfilerReady(2000);
    int result = profiledWork(new Circle(), new Square(), new Triangle());
    System.err.println(result);
    stopProfiler();
    verifyCStackSettings();

    JfrEvents events = verifyEvents("datadog.ExecutionSample");
    int stubs = 0;
    boolean foundVtableWithReceiver = false;
    for (JfrEvent sample : events) {
      assertNotNull(sample.get("stackTrace"), "CPU sample is missing its stackTrace field");
      List<JfrFrame> frames = sample.getStackTrace().frames();
      for (int i = 0; i < frames.size(); i++) {
        JfrFrame frame = frames.get(i);
        if ("vtable stub".equals(frame.methodName())) {
          stubs++;
        }
        if ("<vtable_receiver>".equals(frame.methodName())) {
          String receiver = frame.className();
          assertNotNull(receiver, "Vtable receiver frame is missing its declaring class");
          if ((Circle.class.getName().equals(receiver)
                  || Square.class.getName().equals(receiver)
                  || Triangle.class.getName().equals(receiver))
              && i + 1 < frames.size()
              && "vtable stub".equals(frames.get(i + 1).methodName())) {
            foundVtableWithReceiver = true;
          }
        }
      }
    }
    // Separates a workload that never sampled a vtable stub from a missing receiver frame.
    assertTrue(stubs > 0, "No CPU sample contained a vtable stub frame with cstack=" + cstack);
    assertTrue(
        foundVtableWithReceiver,
        "No CPU sample contained a <vtable_receiver> method declared by a workload receiver "
            + "class (Circle/Square/Triangle) immediately before its vtable stub; "
            + "signal-handler capture or dump-time resolution is broken with cstack="
            + cstack);
  }
}
