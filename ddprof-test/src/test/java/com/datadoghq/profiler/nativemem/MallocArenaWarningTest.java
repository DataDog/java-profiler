/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.nativemem;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
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
import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

/**
 * Tests {@code datadog.MallocArenaStats} and {@code datadog.MallocArenaWarning}. The quota tests
 * skip without a cgroup CPU quota (run with {@code --cpus=2 --memory=2g}); the no-warning test
 * needs {@code MALLOC_ARENA_MAX} = 8 * ceil(quota), and the warning test skips at or below it.
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

  // The event time must lie inside the interval that jdk.ActiveRecording advertises.
  private void assertWithinRecording(JfrEvent event) {
    JfrEvent recording = null;
    for (JfrEvent item : verifyEvents("jdk.ActiveRecording")) {
      recording = item;
    }
    assertNotNull(recording, "no jdk.ActiveRecording event");
    long start = recording.getLong("startTime", 0);
    long end = start + recording.getLong("duration", 0);
    long at = event.getLong("startTime", 0);
    assertTrue(
        at >= start && at <= end, "event time " + at + " outside [" + start + ", " + end + "]");
  }

  private JfrEvent lastStatsEvent() {
    JfrEvent last = null;
    for (JfrEvent item : verifyEvents(STATS)) {
      last = item;
    }
    assertNotNull(last, "no stats event");
    return last;
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
    } catch (IOException | NumberFormatException e) {
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
    JfrEvent last = lastStatsEvent();
    assertWithinRecording(last);
    String status = last.getString("walkStatus");
    if (Platform.isZing()) {
      assertEquals("unsupported-jvm", status);
      return;
    }
    Assumptions.assumeFalse(
        "replaced-allocator".equals(status)
            || "hugetlb-tunable".equals(status)
            || ("no-seed".equals(status) && seedBlockedByEnvironment()),
        "arena walk disabled by the process environment: " + status);
    assertEquals("ok", status);
    assertTrue(last.getLong("arenaCount", 0) >= 2, "arenaCount: " + last);
    assertEquals(Runtime.getRuntime().maxMemory(), last.getLong("maxHeap", -1));
  }

  @Test
  public void warnsWhenArenasExceedTheQuotaLimit() throws Exception {
    int quotaCpus = requireQuotaCpus();
    int recommended = ARENAS_PER_CPU * quotaCpus;
    Integer envMax = arenaCap();
    Assumptions.assumeTrue(
        envMax == null || envMax > recommended, "the arena cap is already " + envMax);
    Assumptions.assumeFalse(Platform.isZing() || Platform.isMusl(), "arena walk is not available");

    try (MallocArenaChurn churn = new MallocArenaChurn(recommended + 32, CHURN_BLOCKS)) {
      churn.start();
      stopProfiler();
    }
    JfrEvent lastStats = lastStatsEvent();
    Assumptions.assumeTrue(
        "ok".equals(lastStats.getString("walkStatus")),
        "the arena walk is unavailable: " + lastStats);
    Assumptions.assumeTrue(
        lastStats.getLong("arenaCount", 0) > recommended,
        "the process held no more than "
            + recommended
            + " arenas; its arena cap is too low: "
            + lastStats);
    long limit = lastStats.getLong("memoryLimit", -1);
    long heap = lastStats.getLong("maxHeap", -1);
    long headroom = heap > 0 && heap < limit ? limit - heap : limit;
    long free = lastStats.getLong("freeHeldBytes", -1);
    long measure = free >= 0 ? free : lastStats.getLong("nonMainArenaBytes", 0);
    Assumptions.assumeTrue(
        limit > 0 && measure > headroom / 100,
        "the workload held under 1% of the native headroom: " + lastStats);
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
    Integer envMax = arenaCap();
    Assumptions.assumeTrue(
        envMax != null && envMax == recommended,
        "needs MALLOC_ARENA_MAX=" + recommended + " in the test JVM environment");
    Assumptions.assumeFalse(Platform.isZing() || Platform.isMusl(), "arena walk is not available");

    try (MallocArenaChurn churn = new MallocArenaChurn(recommended + 32, CHURN_BLOCKS)) {
      churn.start();
      stopProfiler();
    }
    JfrEvent lastStats = lastStatsEvent();
    Assumptions.assumeTrue(
        "ok".equals(lastStats.getString("walkStatus")),
        "the arena walk is unavailable: " + lastStats);
    assertFalse(verifyEvents(WARNING, false).hasItems(), "no warning expected");
  }

  // The arena cap glibc applies: the glibc.malloc.arena_max tunable, else MALLOC_ARENA_MAX.
  // Null when neither holds a positive number.
  private static Integer arenaCap() {
    Long cap = tunable("glibc.malloc.arena_max");
    if (cap == null || cap <= 0) {
      cap = parseGlibcNumber(System.getenv("MALLOC_ARENA_MAX"));
    }
    return cap != null && cap > 0 ? (int) Math.min(cap, Integer.MAX_VALUE) : null;
  }

  // The arena walk cannot find its seed block when every thread allocates from main_arena or
  // the 4096-byte seed is served by mmap.
  private static boolean seedBlockedByEnvironment() {
    Long mmapThreshold = tunable("glibc.malloc.mmap_threshold");
    if (mmapThreshold == null) {
      mmapThreshold = parseGlibcNumber(System.getenv("MALLOC_MMAP_THRESHOLD_"));
    }
    return arenaCap() != null
        || System.getenv("MALLOC_CHECK_") != null
        || tunable("glibc.malloc.check") != null
        || (mmapThreshold != null && mmapThreshold <= 4096);
  }

  // The last occurrence of the tunable in GLIBC_TUNABLES that parses, or null.
  private static Long tunable(String name) {
    String list = System.getenv("GLIBC_TUNABLES");
    Long found = null;
    if (list != null) {
      for (String item : list.split(":")) {
        if (item.startsWith(name + "=")) {
          Long v = parseGlibcNumber(item.substring(name.length() + 1));
          if (v != null) {
            found = v;
          }
        }
      }
    }
    return found;
  }

  // Parses like glibc's strtol(.., 0): leading blanks, optional sign, decimal, 0x hex or octal;
  // trailing characters make it invalid.
  private static Long parseGlibcNumber(String value) {
    if (value == null || value.indexOf('#') >= 0) {
      return null;
    }
    try {
      return Long.decode(value.replaceFirst("^\\s+", ""));
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
   * CPU quota in milli-CPUs: the smallest quota on this process's cgroup and its ancestors, from
   * cgroup v2 cpu.max or the cgroup v1 CFS files, or -1 when there is none.
   */
  private static long cpuQuotaMilli() {
    String self = read(Paths.get("/proc/self/cgroup"));
    if (self == null) {
      return -1;
    }
    long min = -1;
    for (String line : self.split("\n")) {
      String[] parts = line.split(":", 3);
      if (parts.length != 3) {
        continue;
      }
      boolean v2 = parts[0].equals("0") && parts[1].isEmpty();
      boolean v1 = Arrays.asList(parts[1].split(",")).contains("cpu");
      if (!v2 && !v1) {
        continue;
      }
      Path root = Paths.get(v2 ? "/sys/fs/cgroup" : "/sys/fs/cgroup/cpu");
      Path dir = root.resolve(parts[2].replaceFirst("^/", "")).normalize();
      // The detector ignores a hierarchy whose own cgroup has no quota file.
      if (!Files.exists(dir.resolve(v2 ? "cpu.max" : "cpu.cfs_quota_us"))) {
        continue;
      }
      while (dir != null && dir.startsWith(root)) {
        long milli = v2 ? quotaV2(dir) : quotaV1(dir);
        if (milli > 0 && (min < 0 || milli < min)) {
          min = milli;
        }
        dir = dir.getParent();
      }
    }
    return min;
  }

  private static long quotaV2(Path dir) {
    String v = read(dir.resolve("cpu.max"));
    if (v == null) {
      return -1;
    }
    String[] parts = v.trim().split("\\s+");
    return parts.length == 2 && !"max".equals(parts[0]) ? toMilli(parts[0], parts[1]) : -1;
  }

  private static long quotaV1(Path dir) {
    String quota = read(dir.resolve("cpu.cfs_quota_us"));
    String period = read(dir.resolve("cpu.cfs_period_us"));
    return quota != null && period != null ? toMilli(quota.trim(), period.trim()) : -1;
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
