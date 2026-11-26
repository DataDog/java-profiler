/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.nativethread;

/**
 * A pthread, invisible to the JVM, that names itself with raw bytes and burns CPU until stopped.
 * Linux only: the JNI side is compiled only there.
 */
public final class NamedNativeThread implements AutoCloseable {
  static {
    System.loadLibrary("ddproftest");
  }

  private final long handle;

  /** Starts the thread; at most the first 15 bytes of {@code name} are used, as on Linux. */
  public NamedNativeThread(byte[] name) {
    handle = start0(name);
    if (handle == 0) {
      throw new IllegalStateException("could not start a native thread");
    }
  }

  @Override
  public void close() {
    stop0(handle);
  }

  private static native long start0(byte[] name);

  private static native void stop0(long handle);
}
