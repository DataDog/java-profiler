// Copyright 2026, Datadog, Inc.

package com.datadoghq.profiler.jfr;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertSame;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;
import org.junit.jupiter.api.Test;

/** Pins the adaptive cycle contract: bounded growth, halving on clean passes, and the cap. */
public class AdaptiveDumpCyclesTest {

  @Test
  public void cleanPassesHalveTheBatch() throws Exception {
    List<Integer> batches = new ArrayList<>();
    AdaptiveDumpCycles.run(3, batches::add, r -> {}, r -> true, r -> {});
    assertEquals(Arrays.asList(50, 25, 12), batches);
  }

  @Test
  public void underSampledDumpGrowsAndKeepsTheGrownBatch() throws Exception {
    List<Integer> batches = new ArrayList<>();
    AtomicInteger probes = new AtomicInteger();
    AdaptiveDumpCycles.run(2, batches::add, r -> {}, r -> probes.getAndIncrement() >= 2, r -> {});
    // Cycle 1 grows 50 -> 100 -> 200 before verifying; cycle 2 stays at the grown batch.
    assertEquals(Arrays.asList(50, 100, 200, 200), batches);
    assertEquals(4, probes.get());
  }

  @Test
  public void exhaustedCapSurfacesTheAssertingFailureBounded() throws Exception {
    List<Integer> batches = new ArrayList<>();
    AtomicInteger assertCalls = new AtomicInteger();
    AssertionError failure = new AssertionError("not verified");
    try {
      AdaptiveDumpCycles.run(
          2,
          batches::add,
          r -> {},
          r -> false,
          r -> {
            assertCalls.incrementAndGet();
            throw failure;
          });
      fail("the asserting verifier must stop the cycle at the cap");
    } catch (AssertionError e) {
      assertSame(failure, e);
    }
    // Bounded: exactly the growth ladder 50 -> 100 -> 200 -> 400, no fifth attempt.
    assertEquals(Arrays.asList(50, 100, 200, 400), batches);
    assertEquals(1, assertCalls.get());
  }

  @Test
  public void passingAssertorAtExhaustedCapFailsBounded() throws Exception {
    try {
      AdaptiveDumpCycles.run(1, r -> {}, r -> {}, r -> false, r -> {});
      fail("an asserting verifier that passes where the probe failed must fail the cycle");
    } catch (IllegalStateException e) {
      assertTrue(e.getMessage().contains("MAX_BATCH"));
    }
  }
}
