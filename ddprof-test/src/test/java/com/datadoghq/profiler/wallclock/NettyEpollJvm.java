/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.TimeUnit;

/** Outer owner of one test JVM, with output retained even if a JNI worker never returns. */
public final class NettyEpollJvm {
  private NettyEpollJvm() {}

  /**
   * Takes a fresh log path followed by the exact parent-reviewed child JVM argv. The command must
   * launch the JVM directly, not a shell, Gradle, or a launcher that creates descendant processes.
   */
  public static void main(String[] args) throws Exception {
    if (args.length < 2) {
      throw new IllegalArgumentException("expected fresh log path and exact child JVM argv");
    }
    int exit =
        run(
            Arrays.asList(Arrays.copyOfRange(args, 1, args.length)),
            Paths.get(args[0]),
            TimeUnit.SECONDS.toNanos(30));
    if (exit != 0) {
      throw new AssertionError("isolated Netty JVM failed with exit " + exit);
    }
  }

  /**
   * Returns an exit code only after reaping the owned JVM; timeout/interruption is never success.
   */
  static int run(List<String> command, Path log, long budgetNanos) throws Exception {
    Files.createFile(log);
    Process child =
        new ProcessBuilder(command).redirectErrorStream(true).redirectOutput(log.toFile()).start();
    Throwable primary = null;
    try {
      if (!child.waitFor(budgetNanos, TimeUnit.NANOSECONDS)) {
        throw new AssertionError("isolated Netty JVM exceeded outer deadline; log=" + log);
      }
      return child.exitValue();
    } catch (Exception | Error error) {
      primary = error;
      if (error instanceof InterruptedException) {
        Thread.currentThread().interrupt();
      }
      throw error;
    } finally {
      boolean interrupted = Thread.interrupted();
      try {
        if (child.isAlive()) {
          child.destroyForcibly();
          long deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(5);
          while (child.isAlive()) {
            long remaining = deadline - System.nanoTime();
            if (remaining <= 0) {
              throw new AssertionError("owned Netty JVM survived forced termination; log=" + log);
            }
            try {
              child.waitFor(remaining, TimeUnit.NANOSECONDS);
            } catch (InterruptedException error) {
              interrupted = true;
              if (primary == null) {
                primary = error;
              } else {
                primary.addSuppressed(error);
              }
            }
          }
        }
      } catch (Exception | Error cleanupFailure) {
        if (primary == null) {
          throw cleanupFailure;
        }
        primary.addSuppressed(cleanupFailure);
      } finally {
        if (interrupted) {
          Thread.currentThread().interrupt();
        }
      }
    }
  }
}
