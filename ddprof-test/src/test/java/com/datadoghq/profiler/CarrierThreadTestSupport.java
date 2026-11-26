/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler;

/** Keeps context writes, readback and cleanup on one mounted carrier through a JNI activation. */
public final class CarrierThreadTestSupport {
  static {
    System.loadLibrary("ddproftest");
  }

  private CarrierThreadTestSupport() {}

  /** Runs the callback pinned and returns its actual carrier's Java thread id. */
  public static native long runPinned(Runnable callback);
}
