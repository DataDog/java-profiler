/*
 * Copyright 2026 Datadog, Inc
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

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.management.ManagementFactory;
import java.util.concurrent.TimeUnit;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Utility for tracking process memory including JVMTI allocations that NMT cannot see.
 *
 * <p>RSS (Resident Set Size) includes all process memory: heap, native allocations (malloc),
 * mmap regions, and JVMTI allocations. This is the ground truth for memory leak detection.
 */
public class ProcessMemory {

  /**
   * Takes a snapshot of process RSS memory.
   *
   * @return RSS in bytes
   * @throws IOException if memory reading fails
   */
  public static long getRssBytes() throws IOException {
    String os = System.getProperty("os.name").toLowerCase();
    try {
      if (os.contains("linux")) {
        return getRssBytesLinux();
      } else if (os.contains("mac")) {
        return getRssBytesMacOS();
      } else {
        throw new UnsupportedOperationException("RSS tracking not supported on: " + os);
      }
    } catch (InterruptedException e) {
      Thread.currentThread().interrupt();
      throw new IOException("Interrupted while reading RSS", e);
    }
  }

  /**
   * Reads RSS from /proc/self/status on Linux.
   *
   * @return RSS in bytes
   */
  private static long getRssBytesLinux() throws IOException {
    // VmRSS line in /proc/self/status shows RSS in KB
    Pattern pattern = Pattern.compile("VmRSS:\\s+(\\d+)\\s+kB");
    try (BufferedReader reader = new BufferedReader(
        new java.io.FileReader("/proc/self/status"))) {
      String line;
      while ((line = reader.readLine()) != null) {
        Matcher matcher = pattern.matcher(line);
        if (matcher.find()) {
          long rssKB = Long.parseLong(matcher.group(1));
          return rssKB * 1024; // Convert to bytes
        }
      }
    }
    throw new IOException("Could not find VmRSS in /proc/self/status");
  }

  /**
   * Reads RSS from ps command on macOS.
   *
   * @return RSS in bytes
   */
  private static long getRssBytesMacOS() throws IOException, InterruptedException {
    String pid = ManagementFactory.getRuntimeMXBean().getName().split("@")[0];

    // ps -o rss= -p <pid> returns RSS in KB on macOS
    Process ps = new ProcessBuilder("ps", "-o", "rss=", "-p", pid).start();

    String output;
    try (BufferedReader reader = new BufferedReader(
        new InputStreamReader(ps.getInputStream()))) {
      output = reader.readLine();
    }

    if (!ps.waitFor(5, TimeUnit.SECONDS)) {
      ps.destroyForcibly();
      throw new IOException("ps command timed out");
    }

    if (output == null || output.trim().isEmpty()) {
      throw new IOException("Failed to read RSS from ps command");
    }

    try {
      long rssKB = Long.parseLong(output.trim());
      return rssKB * 1024; // Convert to bytes
    } catch (NumberFormatException e) {
      throw new IOException("Failed to parse RSS value: " + output, e);
    }
  }

  /**
   * Memory snapshot at a point in time.
   */
  public static class Snapshot {
    public final long rssBytes;
    public final long timestamp;

    public Snapshot(long rss) {
      this.rssBytes = rss;
      this.timestamp = System.currentTimeMillis();
    }

    public long getRssKB() {
      return rssBytes / 1024;
    }

    public long getRssMB() {
      return rssBytes / (1024 * 1024);
    }
  }

  /**
   * Takes a process memory snapshot.
   *
   * @return memory snapshot
   * @throws IOException if memory reading fails
   */
  public static Snapshot takeSnapshot() throws IOException {
    return new Snapshot(getRssBytes());
  }

  /**
   * Calculates memory growth between two snapshots.
   *
   * @param before snapshot before operation
   * @param after snapshot after operation
   * @return growth in bytes (can be negative)
   */
  public static long calculateGrowth(Snapshot before, Snapshot after) {
    return after.rssBytes - before.rssBytes;
  }

  /**
   * Formats bytes as human-readable string.
   *
   * @param bytes number of bytes
   * @return formatted string like "4.5 MB"
   */
  public static String formatBytes(long bytes) {
    if (bytes < 1024) {
      return bytes + " B";
    } else if (bytes < 1024 * 1024) {
      return String.format("%.1f KB", bytes / 1024.0);
    } else if (bytes < 1024 * 1024 * 1024) {
      return String.format("%.1f MB", bytes / (1024.0 * 1024.0));
    } else {
      return String.format("%.2f GB", bytes / (1024.0 * 1024.0 * 1024.0));
    }
  }
}
