/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import java.lang.management.ManagementFactory;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.TimeUnit;

/** Outer owner of one test JVM, with output retained even if a JNI worker never returns. */
public final class NettyEpollJvm {
  private NettyEpollJvm() {}

  /** Child heap when the parent JVM was started without -Xmx. */
  static final String DEFAULT_CHILD_HEAP = "-Xmx512m";

  private static final String[] HEAP_LAYOUT_FLAGS = {
    "-Xmx", "-XX:HeapBaseMinAddress=", "-XX:CompressedClassSpaceSize="
  };

  /** Heap-layout flags of this JVM for a child JVM; see {@link #heapLayoutArgs(List)}. */
  static List<String> heapLayoutArgs() {
    return heapLayoutArgs(ManagementFactory.getRuntimeMXBean().getInputArguments());
  }

  /**
   * Selects the parent's heap size and the ASan heap-placement flags, which keep the Java heap
   * below the shadow region only when the child uses them too. The last occurrence wins, as in the
   * JVM.
   */
  static List<String> heapLayoutArgs(List<String> parentArgs) {
    Map<String, String> selected = new LinkedHashMap<>();
    selected.put("-Xmx", DEFAULT_CHILD_HEAP);
    for (String arg : parentArgs) {
      for (String flag : HEAP_LAYOUT_FLAGS) {
        if (arg.startsWith(flag)) {
          selected.put(flag, arg);
        }
      }
    }
    return new ArrayList<>(selected.values());
  }

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
