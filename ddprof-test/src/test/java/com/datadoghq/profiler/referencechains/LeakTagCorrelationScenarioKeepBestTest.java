/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.IMCType;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertSame;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Plain-JUnit checks (no profiler, no dump) for {@link LeakTagCorrelationScenario#keepBest} and
 * {@link LeakTagCorrelationScenario#resultLine}: a gate violation seen in any scanned dump must
 * survive into the kept result regardless of which scan's payload wins, and must outrank every
 * payload outcome - including "no payload chain found" - in the printed result line.
 */
public class LeakTagCorrelationScenarioKeepBestTest {

  /**
   * quality 0: no payload chain; 1: out-of-pool chain; 2: in-pool, no live object; 3: in-pool and
   * correlated. Violations prefixed "T:" go to transientViolations, "N:" to noiseChains.
   */
  private static LeakTagCorrelationScenario.ScanResult scan(
      int quality, long tag, String... violations) {
    LeakTagCorrelationScenario.ScanResult r = new LeakTagCorrelationScenario.ScanResult();
    if (quality >= 1) {
      r.payloadChain =
          new ReferenceChainAssertions.ChainMatch(Collections.<IMCType>emptyList(), tag, 2);
      r.payloadChainInPool = quality >= 2;
      r.liveObjectMatchesForChainTag = quality >= 3 ? 1 : 0;
    }
    for (String v : violations) {
      if (v.startsWith("T:")) {
        r.transientViolations.add(v);
      } else if (v.startsWith("N:")) {
        r.noiseChains.add(v);
      } else {
        throw new IllegalArgumentException("violation must start with T: or N: - " + v);
      }
    }
    return r;
  }

  private static LeakTagCorrelationScenario.ScanResult fold(
      List<LeakTagCorrelationScenario.ScanResult> scans) {
    LeakTagCorrelationScenario.ScanResult best = null;
    for (LeakTagCorrelationScenario.ScanResult s : scans) {
      best = LeakTagCorrelationScenario.keepBest(best, s);
    }
    return best;
  }

  @Test
  public void earlierViolationSurvivesBetterLaterScan() {
    LeakTagCorrelationScenario.ScanResult best = scan(1, 1, "T:a");
    LeakTagCorrelationScenario.ScanResult later = scan(3, 2);
    LeakTagCorrelationScenario.ScanResult kept = LeakTagCorrelationScenario.keepBest(best, later);
    assertEquals(2, kept.payloadChain.targetTag, "the better later scan's payload must win");
    assertEquals(Collections.singletonList("T:a"), kept.transientViolations,
        "the earlier dump's transient violation must not be hidden by a better later scan");
  }

  @Test
  public void laterViolationSurvivesWorseLaterScan() {
    LeakTagCorrelationScenario.ScanResult best = scan(3, 1, "N:x");
    LeakTagCorrelationScenario.ScanResult later = scan(1, 2, "T:b");
    LeakTagCorrelationScenario.ScanResult kept = LeakTagCorrelationScenario.keepBest(best, later);
    assertEquals(1, kept.payloadChain.targetTag, "the better earlier payload must be kept");
    assertEquals(Collections.singletonList("T:b"), kept.transientViolations);
    assertEquals(Collections.singletonList("N:x"), kept.noiseChains);
  }

  @Test
  public void violationsAccumulateRegardlessOfScanOrder() {
    LeakTagCorrelationScenario.ScanResult forward =
        fold(Arrays.asList(scan(1, 1, "T:a"), scan(3, 2), scan(2, 3, "N:y")));
    assertTrue(forward.transientViolations.contains("T:a"), forward.transientViolations.toString());
    assertTrue(forward.noiseChains.contains("N:y"), forward.noiseChains.toString());

    LeakTagCorrelationScenario.ScanResult reverse =
        fold(Arrays.asList(scan(2, 3, "N:y"), scan(3, 2), scan(1, 1, "T:a")));
    assertTrue(reverse.transientViolations.contains("T:a"), reverse.transientViolations.toString());
    assertTrue(reverse.noiseChains.contains("N:y"), reverse.noiseChains.toString());
  }

  @Test
  public void newerScanWinsPayloadTieButKeepsEarlierViolations() {
    LeakTagCorrelationScenario.ScanResult best = scan(2, 10, "T:a");
    LeakTagCorrelationScenario.ScanResult later = scan(2, 11);
    LeakTagCorrelationScenario.ScanResult kept = LeakTagCorrelationScenario.keepBest(best, later);
    assertEquals(11, kept.payloadChain.targetTag, "at equal quality the newer scan wins");
    assertTrue(kept.transientViolations.contains("T:a"), kept.transientViolations.toString());
  }

  @Test
  public void mergedViolationsAreDeduplicated() {
    LeakTagCorrelationScenario.ScanResult kept =
        LeakTagCorrelationScenario.keepBest(scan(1, 1, "T:a"), scan(3, 2, "T:a"));
    assertEquals(1, kept.transientViolations.size(), kept.transientViolations.toString());
  }

  @Test
  public void nullInputsReturnTheOtherSide() {
    LeakTagCorrelationScenario.ScanResult s = scan(1, 1);
    LeakTagCorrelationScenario.ScanResult b = scan(2, 2);
    assertSame(s, LeakTagCorrelationScenario.keepBest(null, s));
    assertSame(b, LeakTagCorrelationScenario.keepBest(b, null));
    assertNull(LeakTagCorrelationScenario.keepBest(null, null));
  }

  @Test
  public void resultLineRanksGateViolationsAboveEveryPayloadOutcome() {
    assertEquals(LeakTagCorrelationScenario.NOT_FOUND_MARKER,
        LeakTagCorrelationScenario.resultLine(null));
    assertTrue(LeakTagCorrelationScenario.resultLine(scan(0, 0, "T:a"))
            .startsWith(LeakTagCorrelationScenario.TRANSIENT_CHAIN_MARKER),
        "a transient violation without any payload chain must not be reported as NOT_FOUND");
    assertTrue(LeakTagCorrelationScenario.resultLine(scan(0, 0, "N:x"))
            .startsWith(LeakTagCorrelationScenario.NOISE_CHAIN_MARKER),
        "a noise chain without any payload chain must not be reported as NOT_FOUND");
    assertTrue(LeakTagCorrelationScenario.resultLine(scan(3, 5, "T:a", "N:x"))
            .startsWith(LeakTagCorrelationScenario.TRANSIENT_CHAIN_MARKER),
        "transient outranks noise, and both outrank FOUND");
    assertEquals(LeakTagCorrelationScenario.NOT_FOUND_MARKER,
        LeakTagCorrelationScenario.resultLine(scan(0, 0)));
    assertTrue(LeakTagCorrelationScenario.resultLine(scan(1, 5))
        .startsWith(LeakTagCorrelationScenario.TAG_OUT_OF_POOL_MARKER));
    assertTrue(LeakTagCorrelationScenario.resultLine(scan(2, 5))
        .startsWith(LeakTagCorrelationScenario.NO_LIVE_OBJECT_MARKER));
    assertEquals(LeakTagCorrelationScenario.FOUND_MARKER + 7,
        LeakTagCorrelationScenario.resultLine(scan(3, 7)));
  }
}
