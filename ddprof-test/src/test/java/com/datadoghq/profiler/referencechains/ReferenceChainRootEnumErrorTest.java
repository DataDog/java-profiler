/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import static com.datadoghq.profiler.referencechains.ReferenceChainAssertions.assumeDebugBuild;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ReferenceChainTestHooks;
import java.nio.file.Files;
import java.nio.file.Path;
import org.junit.jupiter.api.Test;

/**
 * Drives the {@code datadog.ReferenceChainAbandoned} event's {@code root_enum_error} reason end to
 * end: with the debug-build error-injection seam active ({@link
 * ReferenceChainTestHooks#setRootEnumErrorInjection0(boolean)}), every root/stack-ref enumeration
 * attempt fails with a JVMTI error, the tracker counts the consecutive failures, and {@code
 * runPass()}'s termination ladder abandons the search with {@code ROOT_ENUM_ERROR} once {@code
 * MAX_CONSECUTIVE_ENUM_ERRORS} attempts have errored - queued as an abandonment event that {@code
 * Profiler.dump()} writes into a real JFR chunk.
 *
 * <p>Accurate serialization is the point: the ladder's other conditions (deferred TTL, held
 * no-progress counter) also hold at that mark, so this test pins that the event reports {@code
 * reason = "root_enum_error"} rather than the {@code "ttl"} a stale reason table could only
 * misattribute this failure as. The byte-level reason-string mapping is asserted separately by the
 * native {@code AbandonedEventSerializesRootEnumErrorReason} gtest; the abandon mechanics
 * themselves by {@code ConsecutiveEnumErrorsAbandonSearch}.
 *
 * <p>Only runs under the debug native build ({@code testdebug}) - the backing native method does
 * not exist in a release build (see javaApi.cpp's {@code #ifdef DEBUG} guard), same pattern as
 * {@link ReferenceChainTestSeamsTest}.
 */
public class ReferenceChainRootEnumErrorTest extends AbstractProfilerTest {

  @Override
  protected String getProfilerCommand() {
    // memory=64:l:1.0 is load-bearing (same rationale as
    // ReferenceChainTrackingTest.shouldReportAbandonedSearchOnTinyFrontierCap):
    // Profiler::start() only starts the ReferenceChainTracker when allocation
    // sampling activated. ttl=0 leaves ROOT_ENUM_ERROR as the ladder's only
    // termination bound; framecap=2000000 keeps the real heap's ambient root
    // count from hitting FRONTIER_CAP first.
    return "memory=64:l:1.0,referencechains=true:hops=32:budget=500:ttl=0:framecap=2000000";
  }

  @Override
  protected boolean isPlatformSupported() {
    // Same HotSpot-shaped JVMTI heap-walk assumption as
    // ReferenceChainTrackingTest (memleak/LivenessTrackingTest's guard).
    return !(Platform.isJavaVersion(8) || Platform.isJ9() || Platform.isZing());
  }

  // Java mirror of referenceChains.h's MAX_CONSECUTIVE_ENUM_ERRORS - no seam
  // exposes it. The abandon fires on the attempt that reaches the cap.
  private static final int MAX_CONSECUTIVE_ENUM_ERRORS = 3;

  // msSinceLastEnum seeded before every driven pass: root/stack-ref enumeration re-runs only once
  // the adaptive interval floor (>= ROOT_ENUM_MIN_INTERVAL_NS = 2s) has elapsed since the last
  // attempt, so each driven pass must see the last attempt comfortably in the past. Same seeding
  // shape the native ConsecutiveEnumErrorsAbandonSearch gtest drives.
  private static final long ENUM_LONG_AGO_MS = 100_000;

  // Driven attempts plus slack: once the search is terminal,
  // {@link ReferenceChainTestHooks#runReferenceChainPass0()} keeps returning (no-op), so the
  // extra calls are harmless and the exact cap is deliberately not hardcoded here.
  private static final int MAX_DRIVEN_PASSES = MAX_CONSECUTIVE_ENUM_ERRORS + 4;

  @Test
  public void shouldReportRootEnumErrorOnAbandonedSearch() throws Exception {
    assumeDebugBuild();

    // Shared-JVM hygiene: the tracker is a process-wide singleton whose search may have been
    // exhausted by an earlier test - establish this test's own fresh search (also zeroes the
    // consecutive-error count a prior search could have left behind).
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();

    ReferenceChainTestHooks.setRootEnumErrorInjection0(true);
    try {
      // Driven synchronously, bypassing the background thread's shouldRunPass() gate: each call
      // runs exactly one pass whose root enumeration inject-fails. No candidate seeding is
      // needed - the injection makes every attempt errored, so the ladder's completion gate
      // (no pending work) cannot fire and the error cap is the only bound when ttl=0.
      for (int i = 0; i < MAX_DRIVEN_PASSES; i++) {
        // Enumeration re-runs only past the adaptive interval floor - backdate the last
        // attempt so each driven pass runs a real (inject-failing) enumeration attempt.
        ReferenceChainTestHooks.setReferenceChainRootEnumStateForTest0(
            ENUM_LONG_AGO_MS, /* lastEnumCostMs= */ 0);
        if (i == 0) {
          assertTrue(
              ReferenceChainTestHooks.runReferenceChainPass0(),
              "Expected the first driven pass to run (reference chains enabled)");
        } else {
          ReferenceChainTestHooks.runReferenceChainPass0();
        }
      }

      // The abandonment event reached the pending queue on the cap-reaching pass; a real
      // dump() drains and writes it. A concurrent restart by the background thread would not
      // lose it - the queue survives until dump() drains it.
      Path dumpPath = Files.createTempFile("referencechains-rootenum-error-test-", ".jfr");
      Files.deleteIfExists(dumpPath);
      try {
        JfrEvents abandoned = null;
        for (int attempt = 0; attempt < 8; attempt++) {
          dump(dumpPath);
          abandoned = verifyEvents(dumpPath, "datadog.ReferenceChainAbandoned", false);
          if (abandoned.hasItems() && sawRootEnumErrorReason(abandoned)) {
            break;
          }
          Thread.sleep(1000);
        }
        assertTrue(
            abandoned != null && abandoned.hasItems(),
            "Expected at least one datadog.ReferenceChainAbandoned event after "
                + MAX_DRIVEN_PASSES
                + " inject-failing passes");
        assertTrue(
            sawRootEnumErrorReason(abandoned),
            "Expected the abandonment event's reason to be \"root_enum_error\" "
                + "(not \"ttl\" - the ladder's deferred-TTL and held no-progress conditions "
                + "also hold at the abandon mark, so serializing them would misattribute a "
                + "search whose enumeration keeps failing)");
      } finally {
        Files.deleteIfExists(dumpPath);
      }
    } finally {
      // Restore before the next test in this shared JVM: the flag is process-wide
      // singleton state, and a leftover injection would fail every later search's
      // root enumeration.
      ReferenceChainTestHooks.setRootEnumErrorInjection0(false);
    }
  }

  private static boolean sawRootEnumErrorReason(JfrEvents events) {
    for (JfrEvent item : events) {
      if ("root_enum_error".equals(item.getString("reason"))) {
        return true;
      }
    }
    return false;
  }
}
