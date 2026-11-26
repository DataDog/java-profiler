/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicReference;

/** Owns cancellation between native waits; a nonreturning JNI call still needs JVM termination. */
final class TimedNativeWorker {
  @FunctionalInterface
  interface Wait {
    void await() throws Exception;
  }

  private TimedNativeWorker() {}

  /** Runs all waits on success and preserves primary, cleanup and worker failures on failure. */
  static void run(String name, int iterations, Wait wait, long runNanos, long cleanupNanos)
      throws Exception {
    AtomicBoolean cancelled = new AtomicBoolean();
    AtomicReference<Throwable> workerFailure = new AtomicReference<>();
    Thread worker =
        new Thread(
            () -> {
              try {
                for (int i = 0; i < iterations && !cancelled.get(); i++) {
                  wait.await();
                }
              } catch (Throwable error) {
                workerFailure.set(error);
              }
            },
            name);
    worker.setDaemon(false);
    Throwable primary = null;
    try {
      worker.start();
      long deadline = System.nanoTime() + runNanos;
      while (worker.isAlive()) {
        long remaining = deadline - System.nanoTime();
        if (remaining <= 0) {
          throw new AssertionError("timed native waits exceeded their bounded deadline");
        }
        TimeUnit.NANOSECONDS.timedJoin(worker, remaining);
      }
    } catch (Exception | Error error) {
      primary = error;
      if (error instanceof InterruptedException) {
        Thread.currentThread().interrupt();
      }
    } finally {
      cancelled.set(true);
      worker.interrupt();
      try {
        joinForCleanup(worker, cleanupNanos);
      } catch (Exception | Error cleanupFailure) {
        if (primary == null) {
          primary = cleanupFailure;
        } else {
          primary.addSuppressed(cleanupFailure);
        }
      }
      Throwable error = workerFailure.get();
      if (error != null) {
        if (primary == null) {
          primary = new AssertionError("timed Netty JNI wait failed", error);
        } else {
          primary.addSuppressed(error);
        }
      }
    }
    if (primary instanceof Exception) {
      throw (Exception) primary;
    }
    if (primary != null) {
      throw (Error) primary;
    }
  }

  /** Continues a bounded monotonic join after interruption, then restores the owner's flag. */
  private static void joinForCleanup(Thread worker, long budgetNanos) throws InterruptedException {
    boolean interrupted = Thread.interrupted();
    InterruptedException joinInterruption = null;
    long deadline = System.nanoTime() + budgetNanos;
    try {
      while (worker.isAlive()) {
        long remaining = deadline - System.nanoTime();
        if (remaining <= 0) {
          break;
        }
        try {
          TimeUnit.NANOSECONDS.timedJoin(worker, remaining);
        } catch (InterruptedException error) {
          if (joinInterruption == null) {
            joinInterruption = error;
          }
        }
      }
      if (worker.isAlive()) {
        AssertionError survivor =
            new AssertionError(
                "timed native worker did not terminate; outer owner must terminate isolated test JVM");
        if (joinInterruption != null) {
          survivor.addSuppressed(joinInterruption);
        }
        throw survivor;
      }
      if (joinInterruption != null) {
        throw joinInterruption;
      }
    } finally {
      if (interrupted || joinInterruption != null) {
        Thread.currentThread().interrupt();
      }
    }
  }
}
