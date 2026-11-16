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
 * Verifies that injected root-enumeration failures reach the JFR as {@code root_enum_error}. The
 * native injection seam is inactive in release builds; this test requires DEBUG.
 */
public class ReferenceChainRootEnumErrorTest extends AbstractProfilerTest {

  @Override
  protected String getProfilerCommand() {
    // Allocation sampling is required to start the reference-chain tracker.
    // Disable the elapsed-time cutoff to target the enumeration-error path.
    // Keep a large frontier cap to avoid unrelated capacity failures.
    return "memory=64:l:1.0,referencechains=true:hops=32:budget=500:ttl=0:framecap=2000000";
  }

  @Override
  protected boolean isPlatformSupported() {
    // This test uses the same debug seams as ReferenceChainTestSeamsTest.
    // Keep their platform exclusions aligned.
    return !(Platform.isJavaVersion(8) || Platform.isJ9() || Platform.isZing());
  }

  // Keep this mirror aligned with ReferenceChainTracker::MAX_CONSECUTIVE_ENUM_ERRORS.
  // Native gtests check the exact boundary; this integration test allows extra passes.
  private static final int MAX_CONSECUTIVE_ENUM_ERRORS = 3;

  // Keep this age beyond rootEnumIntervalFloorNs()'s maximum.
  // Backdated attempts let the test run without interval sleeps.
  private static final long ENUM_LONG_AGO_MS = 100_000;

  // Extra calls can reach terminal-search cleanup without enumerating again.
  // The event assertion does not depend on the exact abandonment pass.
  private static final int MAX_DRIVEN_PASSES = MAX_CONSECUTIVE_ENUM_ERRORS + 4;

  @Test
  public void shouldReportRootEnumErrorOnAbandonedSearch() throws Exception {
    assumeDebugBuild();

    // Enable injection BEFORE the reset: resetSearchStateForTest() ends with startThread(), so
    // the background thread can run one real pass in the window after the reset - a completed
    // search would make every later driven pass a no-op. The reset does not touch the flag.
    try {
      ReferenceChainTestHooks.setRootEnumErrorInjection0(true);
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
      // Drive the tracker directly instead of waiting for background scheduling.
      // Failed enumeration marks work incomplete, preventing the empty frontier
      // from completing this search before the error limit is reached.
      for (int i = 0; i < MAX_DRIVEN_PASSES; i++) {
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

      // The final driven pass enqueues the abandonment event synchronously inside
      // runPass(); one dump drains the pending-event queue and writes the chunk.
      Path dumpPath = Files.createTempFile("referencechains-rootenum-error-test-", ".jfr");
      Files.deleteIfExists(dumpPath);
      try {
        dump(dumpPath);
        JfrEvents abandoned = verifyEvents(dumpPath, "datadog.ReferenceChainAbandoned", false);
        assertTrue(
            abandoned.hasItems(),
            "Expected at least one datadog.ReferenceChainAbandoned event after "
                + MAX_DRIVEN_PASSES
                + " inject-failing passes; if the native MAX_CONSECUTIVE_ENUM_ERRORS grew "
                + "beyond "
                + MAX_CONSECUTIVE_ENUM_ERRORS
                + ", update this test's mirror");
        assertTrue(
            sawRootEnumErrorReason(abandoned), "Expected abandonment reason \"root_enum_error\"");
      } finally {
        Files.deleteIfExists(dumpPath);
      }
    } finally {
      // Injection and seeded scheduling state belong to the process-wide tracker.
      // Restore both before the next test starts.
      ReferenceChainTestHooks.setRootEnumErrorInjection0(false);
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
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
