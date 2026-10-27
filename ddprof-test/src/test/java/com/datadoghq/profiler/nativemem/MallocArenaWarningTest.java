/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.nativemem;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Tests the glibc malloc arena events {@code datadog.MallocArenaStats} and
 * {@code datadog.MallocArenaWarning}.
 *
 * <p>The profiler writes one Stats event per JFR chunk on Linux with glibc. The Warning event needs a
 * CPU quota from cgroup v2 {@code cpu.max} or the cgroup v1 CFS files, so the quota tests skip when
 * the test process has none. To run them, give the test a quota and a modest memory limit, for example
 * {@code podman run --cpus=2 --memory=2g ...} through {@code utils/run-containers-tests.sh}. Each of the
 * {@code 8 * quota + 32} churn threads allocates 4 MiB in 1 KiB blocks and keeps every 8th block, so
 * the arenas hold several hundred MiB. The profiler command sets {@code arenawarn=1}, so the memory
 * limit must be small enough for that amount to exceed 1 percent of the native headroom.
 *
 * <p>The test that expects no warning needs the arena limit set in the environment of the test JVM,
 * for example {@code MALLOC_ARENA_MAX=16} with {@code --cpus=2}. It skips when the variable does not
 * equal 8 times the quota CPUs, rounded up. The test that expects a warning skips when the variable
 * is set to a value that does not exceed that number.
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
        Assumptions.assumeFalse("replaced-allocator".equals(status) || "hugetlb-tunable".equals(status),
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
        Assumptions.assumeTrue(envMax == null || envMax > recommended,
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
        Assumptions.assumeTrue(envMax != null && envMax == recommended,
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

    /** CPU quota in milli-CPUs from cgroup v2 cpu.max or cgroup v1 CFS files, or -1 when there is none. */
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
