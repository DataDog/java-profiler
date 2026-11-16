/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.nativemem;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

/**
 * Tests {@code datadog.MallocArenaStats} (one per chunk on Linux glibc) and {@code
 * datadog.MallocArenaWarning}. The quota tests skip without a cgroup CPU quota; run them with
 * {@code --cpus=2 --memory=2g} so the churn exceeds 1% of the native headroom ({@code
 * arenawarn=1}).
 *
 * <p>The no-warning test needs {@code MALLOC_ARENA_MAX} = 8 * ceil(quota) in the JVM environment.
 * The warning test skips when the variable is set to that value or less.
 */
public class MallocArenaWarningTest extends AbstractProfilerTest {
  private static final String STATS = "datadog.MallocArenaStats";
  private static final String WARNING = "datadog.MallocArenaWarning";
  private static final int ARENAS_PER_CPU = 8;
  private static final int CHURN_BLOCKS = 4096;

  @Override
  protected String getProfilerCommand() {
    return "wall=~1ms,arenawarn=1";
  }

  @Override
  protected boolean isPlatformSupported() {
    return Platform.isLinux();
  }

  @Override
  protected void withTestAssumptions() {
    // ASan and TSan replace malloc, so the glibc arena walk is not applicable.
    Assumptions.assumeFalse(isAsan() || isTsan());
    Assumptions.assumeFalse(
        arenasConfinedByMallocCheck(), "MALLOC_CHECK_ confines glibc before 2.34 to main_arena");
  }

  // With MALLOC_CHECK_ set, glibc before 2.34 allocates only from main_arena, so no per-thread
  // arenas exist. From 2.34 on the variable has no effect without libc_malloc_debug.so.
  private static boolean arenasConfinedByMallocCheck() {
    return System.getenv("MALLOC_CHECK_") != null && !glibcAtLeast(2, 34);
  }

  private static boolean glibcAtLeast(int major, int minor) {
    try {
      Process p =
          new ProcessBuilder("getconf", "GNU_LIBC_VERSION").redirectErrorStream(true).start();
      try (BufferedReader r =
          new BufferedReader(new InputStreamReader(p.getInputStream(), StandardCharsets.UTF_8))) {
        String line = r.readLine();
        p.waitFor();
        Matcher m = Pattern.compile("glibc (\\d+)\\.(\\d+)").matcher(line == null ? "" : line);
        if (m.find()) {
          int have = Integer.parseInt(m.group(1));
          return have > major || (have == major && Integer.parseInt(m.group(2)) >= minor);
        }
      }
    } catch (IOException e) {
      // unknown version: callers treat it as older than requested
    } catch (InterruptedException e) {
      Thread.currentThread().interrupt();
    }
    return false;
  }

  @Test
  public void statsEventsDescribeTheArenas() throws Exception {
    try (MallocArenaChurn churn = new MallocArenaChurn(4, 64)) {
      churn.start();
      stopProfiler();
    }
    if (Platform.isMusl()) {
      assertFalse(verifyEvents(STATS, false).hasItems(), "no arena events on musl");
      assertFalse(verifyEvents(WARNING, false).hasItems(), "no arena events on musl");
      return;
    }
    JfrEvents stats = verifyEvents(STATS);
    JfrEvent last = null;
    for (JfrEvent item : stats) {
      last = item;
    }
    String status = last.getString("walkStatus");
    if (Platform.isZing()) {
      assertEquals("unsupported-jvm", status);
      return;
    }
    Assumptions.assumeFalse(
        "replaced-allocator".equals(status) || "hugetlb-tunable".equals(status),
        "arena walk disabled by the process environment: " + status);
    assertEquals("ok", status);
    assertTrue(last.getLong("arenaCount", 0) >= 2, "arenaCount: " + last);
    assertEquals(Runtime.getRuntime().maxMemory(), last.getLong("maxHeap", -1));
  }

  @Test
  public void warnsWhenArenasExceedTheQuotaLimit() throws Exception {
    int quotaCpus = requireQuotaCpus();
    int recommended = ARENAS_PER_CPU * quotaCpus;
    Integer envMax = arenaMaxFromEnv();
    Assumptions.assumeTrue(
        envMax == null || envMax > recommended,
        "MALLOC_ARENA_MAX already limits the arenas to " + envMax);
    Assumptions.assumeFalse(Platform.isZing() || Platform.isMusl(), "arena walk is not available");

    try (MallocArenaChurn churn = new MallocArenaChurn(recommended + 32, CHURN_BLOCKS)) {
      churn.start();
      stopProfiler();
    }
    JfrEvents warnings = verifyEvents(WARNING);
    boolean raised = false;
    for (JfrEvent item : warnings) {
      assertEquals(recommended, item.getLong("recommendedArenaMax", -1), "event: " + item);
      raised |= "raised".equals(item.getString("state"));
    }
    assertTrue(raised, "expected a raised warning, got " + warnings.count() + " events");
  }

  @Test
  public void staysQuietWhenArenaMaxMatchesTheQuota() throws Exception {
    int quotaCpus = requireQuotaCpus();
    int recommended = ARENAS_PER_CPU * quotaCpus;
    Integer envMax = arenaMaxFromEnv();
    Assumptions.assumeTrue(
        envMax != null && envMax == recommended,
        "needs MALLOC_ARENA_MAX=" + recommended + " in the test JVM environment");
    Assumptions.assumeFalse(Platform.isZing() || Platform.isMusl(), "arena walk is not available");

    try (MallocArenaChurn churn = new MallocArenaChurn(recommended + 32, CHURN_BLOCKS)) {
      churn.start();
      stopProfiler();
    }
    assertTrue(verifyEvents(STATS).hasItems());
    assertFalse(verifyEvents(WARNING, false).hasItems(), "no warning expected");
  }

  private static Integer arenaMaxFromEnv() {
    String v = System.getenv("MALLOC_ARENA_MAX");
    if (v == null) {
      return null;
    }
    try {
      return Integer.valueOf(v.trim());
    } catch (NumberFormatException e) {
      return null;
    }
  }

  private static int requireQuotaCpus() {
    long milli = cpuQuotaMilli();
    Assumptions.assumeTrue(milli > 0, "needs a cgroup CPU quota");
    return (int) ((milli + 999) / 1000);
  }

  /**
   * CPU quota in milli-CPUs from cgroup v2 cpu.max or cgroup v1 CFS files, or -1 when there is
   * none.
   */
  private static long cpuQuotaMilli() {
    String v2 = read(Paths.get("/sys/fs/cgroup/cpu.max"));
    if (v2 != null) {
      String[] parts = v2.trim().split("\\s+");
      if (parts.length == 2 && !"max".equals(parts[0])) {
        return toMilli(parts[0], parts[1]);
      }
      return -1;
    }
    String quota = read(Paths.get("/sys/fs/cgroup/cpu/cpu.cfs_quota_us"));
    String period = read(Paths.get("/sys/fs/cgroup/cpu/cpu.cfs_period_us"));
    if (quota != null && period != null) {
      return toMilli(quota.trim(), period.trim());
    }
    return -1;
  }

  private static long toMilli(String quota, String period) {
    try {
      long q = Long.parseLong(quota);
      long p = Long.parseLong(period);
      return q > 0 && p > 0 ? q * 1000 / p : -1;
    } catch (NumberFormatException e) {
      return -1;
    }
  }

  private static String read(Path path) {
    try {
      return new String(Files.readAllBytes(path), StandardCharsets.US_ASCII);
    } catch (IOException e) {
      return null;
    }
  }
}
