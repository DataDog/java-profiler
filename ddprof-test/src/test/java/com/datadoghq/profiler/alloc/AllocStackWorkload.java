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
 * Allocation workload for the allocation-stack tests: allocates {@link Blob} arrays at a known
 * recursion depth, so a correct sample stack has the {@code allocate} frame on top of {@code DEPTH
 * + 1} {@code recurse} frames. The loop runs long enough for the methods to be sampled both
 * interpreted and JIT-compiled, including frames C2 inlined.
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
   * Whether a sample's stack was dropped by the call-trace storage: it then carries a single
   * synthetic frame instead of the walked stack, however the stack was captured.
   */
  static boolean isDroppedSample(JfrEvent event) {
    JfrStackTrace stackTrace = event.getStackTrace();
    if (stackTrace == null || stackTrace.isEmpty()) {
      return false;
    }
    String top = stackTrace.frames().get(0).methodName();
    return top != null && top.startsWith("<dropped");
  }

  /**
   * Whether a sample's stack has {@code DEPTH + 1} consecutive {@code recurse} frames on top,
   * optionally below one {@code allocate} frame, i.e. the walk neither lost nor invented a frame.
   * {@code allocate} is optional because a JIT may inline it so that the JVM's own stack at the
   * allocation site no longer contains it (Graal does); JVMTI GetStackTrace reports the same, so
   * the VM walker matching GetStackTrace is checked separately, by allocstack=verify.
   */
  static boolean hasExpectedStack(JfrEvent event) {
    JfrStackTrace stackTrace = event.getStackTrace();
    if (stackTrace == null || stackTrace.isEmpty()) {
      return false;
    }
    List<JfrFrame> frames = stackTrace.frames();
    int first = "allocate".equals(frames.get(0).methodName()) ? 1 : 0;
    if (frames.size() < first + DEPTH + 2) {
      return false;
    }
    for (int i = first; i <= first + DEPTH; i++) {
      if (!"recurse".equals(frames.get(i).methodName())) {
        return false;
      }
    }
    // The recursion ends at run(): no further recurse frame below the DEPTH + 1 expected.
    return !"recurse".equals(frames.get(first + DEPTH + 1).methodName());
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
