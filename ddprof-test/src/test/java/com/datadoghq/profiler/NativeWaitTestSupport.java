/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import java.util.Objects;

/** Linux-only controls for syscall ownership in independently owned test JVMs. */
public final class NativeWaitTestSupport {
  static {
    System.loadLibrary("ddproftest");
  }

  private NativeWaitTestSupport() {}

  /** Restores the calling thread's full signal mask even when the callback throws. */
  public static void withProfilingSignalsBlocked(Runnable callback) {
    withProfilingSignalsBlocked0(Objects.requireNonNull(callback));
  }

  /** Returns the calling thread's Linux signal mask, with signal N at bit N-1. */
  public static native long signalMask();

  /** Returns the Linux SIGPROF/SIGVTALRM mask without hard-coding their numbers in Java. */
  public static native long profilingSignalMask();

  /** The sole controller temporarily owns SIGWINCH until its targeted delivery is observed. */
  public static native void interruptWait(int tid);

  private static native void withProfilingSignalsBlocked0(Runnable callback);
}
