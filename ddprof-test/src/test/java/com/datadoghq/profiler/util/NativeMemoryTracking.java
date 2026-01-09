/*
 * Copyright 2025, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.datadoghq.profiler.util;

import static org.junit.jupiter.api.Assertions.fail;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.concurrent.TimeUnit;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

/**
 * Utility class for Native Memory Tracking (NMT) automation in tests.
 *
 * <p>Provides methods to capture NMT snapshots via jcmd and assert memory growth is bounded.
 */
public class NativeMemoryTracking {
  /**
   * Pattern to extract total malloc from NMT output.
   * This is what customers see growing when JVMTI leaks occur.
   */
  private static final Pattern MALLOC_PATTERN =
      Pattern.compile("malloc:\\s+(\\d+)KB\\s+#(\\d+)");

  /**
   * Pattern to extract Internal memory from NMT output.
   * JVMTI allocations are tracked under the Internal category.
   */
  private static final Pattern INTERNAL_PATTERN =
      Pattern.compile("-\\s+Internal \\(reserved=(\\d+)KB, committed=(\\d+)KB\\)");

  /** Legacy pattern for JVMTI (not used in modern JVMs, kept for reference). */
  private static final Pattern JVMTI_PATTERN =
      Pattern.compile("-\\s+JVMTI \\(reserved=(\\d+)KB, committed=(\\d+)KB\\)");

  /** Snapshot of Native Memory Tracking state at a point in time. */
  public static class NMTSnapshot {
    public final long mallocKB;
    public final long mallocCount;
    public final long internalReservedKB;
    public final long internalCommittedKB;
    public final long jvmtiReservedKB;
    public final long jvmtiCommittedKB;
    public final String fullOutput;

    NMTSnapshot(
        long malloc,
        long mallocCnt,
        long internalReserved,
        long internalCommitted,
        long jvmtiReserved,
        long jvmtiCommitted,
        String output) {
      this.mallocKB = malloc;
      this.mallocCount = mallocCnt;
      this.internalReservedKB = internalReserved;
      this.internalCommittedKB = internalCommitted;
      this.jvmtiReservedKB = jvmtiReserved;
      this.jvmtiCommittedKB = jvmtiCommitted;
      this.fullOutput = output;
    }

    public long getMallocBytes() {
      return mallocKB * 1024;
    }

    public long getInternalReservedBytes() {
      return internalReservedKB * 1024;
    }

    public long getJVMTIReservedBytes() {
      return jvmtiReservedKB * 1024;
    }

    public long getJVMTICommittedBytes() {
      return jvmtiCommittedKB * 1024;
    }
  }

  /**
   * Takes a snapshot of native memory using jcmd.
   *
   * @return NMT snapshot with JVMTI memory stats
   * @throws IOException if jcmd execution fails
   * @throws InterruptedException if jcmd is interrupted
   */
  public static NMTSnapshot takeSnapshot() throws IOException, InterruptedException {
    // Get current PID (Java 8 compatible way)
    String pid = java.lang.management.ManagementFactory.getRuntimeMXBean().getName().split("@")[0];
    Process jcmd =
        new ProcessBuilder("jcmd", pid, "VM.native_memory", "summary")
            .start();

    String output;
    try (BufferedReader reader =
        new BufferedReader(new InputStreamReader(jcmd.getInputStream()))) {
      output = reader.lines().collect(Collectors.joining("\n"));
    }

    jcmd.waitFor(5, TimeUnit.SECONDS);

    // Parse malloc total (this is what customers see growing)
    long mallocKB = 0;
    long mallocCount = 0;
    Matcher mallocMatcher = MALLOC_PATTERN.matcher(output);
    if (mallocMatcher.find()) {
      mallocKB = Long.parseLong(mallocMatcher.group(1));
      mallocCount = Long.parseLong(mallocMatcher.group(2));
    }

    // Parse Internal category (where JVMTI is tracked)
    long internalReserved = 0;
    long internalCommitted = 0;
    Matcher internalMatcher = INTERNAL_PATTERN.matcher(output);
    if (internalMatcher.find()) {
      internalReserved = Long.parseLong(internalMatcher.group(1));
      internalCommitted = Long.parseLong(internalMatcher.group(2));
    }

    // Parse JVMTI line (legacy - not present in modern JVMs)
    long jvmtiReserved = 0;
    long jvmtiCommitted = 0;
    Matcher jvmtiMatcher = JVMTI_PATTERN.matcher(output);
    if (jvmtiMatcher.find()) {
      jvmtiReserved = Long.parseLong(jvmtiMatcher.group(1));
      jvmtiCommitted = Long.parseLong(jvmtiMatcher.group(2));
    }

    return new NMTSnapshot(
        mallocKB, mallocCount, internalReserved, internalCommitted, jvmtiReserved, jvmtiCommitted, output);
  }

  /**
   * Asserts that malloc memory growth between two snapshots is bounded.
   * This tracks the total malloc metric, which is what customers see growing during leaks.
   *
   * @param before snapshot taken before the operation
   * @param after snapshot taken after the operation
   * @param maxGrowthBytes maximum allowed growth in bytes
   * @param failureMessage message to display if assertion fails
   */
  public static void assertMallocMemoryBounded(
      NMTSnapshot before, NMTSnapshot after, long maxGrowthBytes, String failureMessage) {
    long growth = after.getMallocBytes() - before.getMallocBytes();

    if (growth > maxGrowthBytes) {
      String diagnostic =
          String.format(
              "malloc memory grew by %d bytes (%.2f MB), exceeds limit of %d bytes (%.2f MB)\n"
                  + "Before: %d KB (%d allocations)\n"
                  + "After: %d KB (%d allocations, +%d)\n"
                  + "Internal category before: %d KB\n"
                  + "Internal category after: %d KB (+%d KB)\n\n"
                  + "=== NMT Before ===\n%s\n\n"
                  + "=== NMT After ===\n%s",
              growth,
              growth / (1024.0 * 1024.0),
              maxGrowthBytes,
              maxGrowthBytes / (1024.0 * 1024.0),
              before.mallocKB,
              before.mallocCount,
              after.mallocKB,
              after.mallocCount,
              after.mallocCount - before.mallocCount,
              before.internalReservedKB,
              after.internalReservedKB,
              after.internalReservedKB - before.internalReservedKB,
              before.fullOutput,
              after.fullOutput);
      fail(failureMessage + "\n" + diagnostic);
    }
  }

  /**
   * Asserts that JVMTI memory growth between two snapshots is bounded.
   * Legacy method - JVMTI category doesn't exist in modern JVMs.
   *
   * @param before snapshot taken before the operation
   * @param after snapshot taken after the operation
   * @param maxGrowthBytes maximum allowed growth in bytes
   * @param failureMessage message to display if assertion fails
   */
  public static void assertJVMTIMemoryBounded(
      NMTSnapshot before, NMTSnapshot after, long maxGrowthBytes, String failureMessage) {
    // In modern JVMs, delegate to malloc tracking since JVMTI is under Internal → malloc
    assertMallocMemoryBounded(before, after, maxGrowthBytes, failureMessage);
  }

  /**
   * Checks if Native Memory Tracking is enabled for the current JVM.
   *
   * @return true if NMT is enabled, false otherwise
   */
  public static boolean isEnabled() {
    try {
      NMTSnapshot snapshot = takeSnapshot();
      return snapshot.fullOutput.contains("Native Memory Tracking");
    } catch (Exception e) {
      return false;
    }
  }
}
