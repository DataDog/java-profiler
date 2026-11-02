/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.alloc;

import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrFrame;
import com.datadoghq.profiler.JfrStackTrace;

import java.lang.reflect.Method;
import java.util.List;

/**
 * Allocation workload for the allocation-stack tests: allocates {@link Blob} arrays at a
 * known recursion depth, so a correct sample stack has the {@code allocate} frame on top of
 * {@code DEPTH + 1} {@code recurse} frames. The loop runs long enough for the methods to be
 * sampled both interpreted and JIT-compiled, including frames C2 inlined.
 */
final class AllocStackWorkload implements Runnable {
  static final int DEPTH = 48;
  private static final int ITERATIONS = 200_000;

  /** The marker type: only {@link #allocate} creates arrays of it. */
  static final class Blob {}

  static volatile Object sink;

  @Override
  public void run() {
    recurse(DEPTH);
  }

  private static void recurse(int depth) {
    if (depth > 0) {
      recurse(depth - 1);
    } else {
      for (int i = 0; i < ITERATIONS; i++) {
        allocate();
      }
    }
  }

  private static void allocate() {
    sink = new Blob[64];
  }

  /** Whether an allocation sample is one of this workload's {@link Blob} arrays. */
  static boolean isBlobSample(JfrEvent event) {
    String className = event.getClassName("objectClass");
    return className != null && className.contains("AllocStackWorkload$Blob");
  }

  /**
   * Whether a sample's stack has {@code allocate} followed by {@code DEPTH + 1}
   * {@code recurse} frames, i.e. the walk neither lost nor invented a frame.
   */
  static boolean hasExpectedStack(JfrEvent event) {
    JfrStackTrace stackTrace = event.getStackTrace();
    if (stackTrace == null || stackTrace.isEmpty()) {
      return false;
    }
    List<JfrFrame> frames = stackTrace.frames();
    int top = 0;
    while (top < frames.size() && !"allocate".equals(frames.get(top).methodName())) {
      top++;
    }
    if (top == frames.size() || frames.size() < top + 1 + DEPTH + 1) {
      return false;
    }
    for (int i = top + 1; i <= top + DEPTH + 1; i++) {
      if (!"recurse".equals(frames.get(i).methodName())) {
        return false;
      }
    }
    return true;
  }

  /** Runs the workload on a virtual thread, or returns false on a JDK without them. */
  static boolean runOnVirtualThread(Runnable task) throws Exception {
    Method ofVirtual;
    try {
      ofVirtual = Thread.class.getMethod("ofVirtual");
    } catch (NoSuchMethodException e) {
      return false;
    }
    Object builder = ofVirtual.invoke(null);
    Method start = Class.forName("java.lang.Thread$Builder").getMethod("start", Runnable.class);
    Thread thread = (Thread) start.invoke(builder, task);
    thread.join();
    return true;
  }
}
