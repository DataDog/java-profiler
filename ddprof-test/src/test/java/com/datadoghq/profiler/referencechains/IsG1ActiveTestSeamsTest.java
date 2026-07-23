/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.Platform;
import java.lang.management.GarbageCollectorMXBean;
import java.lang.management.ManagementFactory;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * Collector-gating seam test (reference-chains VMStructs-walk plan, Phase 0):
 * {@code VMStructs::isG1Active()} caches {@code UseG1GC}'s resolved flag value once at
 * {@code resolveOffsets()} time, ahead of any manual-walk code that will read it. This asserts
 * the cached value matches the test JVM's actual collector, derived independently via
 * {@link ManagementFactory#getGarbageCollectorMXBeans()} rather than re-reading the same JVMTI
 * flag the native side already read - so a bug that made {@code isG1Active()} always return
 * {@code true} (or always {@code false}) would be caught on whichever collector the CI leg
 * actually launches with, instead of only ever exercising one hard-coded expectation.
 */
public class IsG1ActiveTestSeamsTest extends AbstractProfilerTest {

  @Override
  protected String getProfilerCommand() {
    return "referencechains=true:hops=32:budget=500:ttl=60000:framecap=1024";
  }

  @Override
  protected boolean isPlatformSupported() {
    return !(Platform.isJavaVersion(8) || Platform.isJ9() || Platform.isZing());
  }

  private static void assumeDebugBuild() {
    assumeTrue("debug".equals(System.getProperty("ddprof_test.config")));
  }

  /**
   * G1's collector beans are named "G1 Young Generation"/"G1 Old Generation" - no other
   * collector's bean names contain "G1", so this substring check is an unambiguous,
   * collector-agnostic way to determine which branch the running JVM actually took without
   * hard-coding a specific non-G1 collector name (Serial/Parallel/Shenandoah/ZGC all differ by
   * JDK version and launch flags).
   */
  private static boolean jvmReportsG1ActiveViaManagementBeans() {
    for (GarbageCollectorMXBean bean : ManagementFactory.getGarbageCollectorMXBeans()) {
      if (bean.getName().contains("G1")) {
        return true;
      }
    }
    return false;
  }

  @Test
  public void isG1ActiveMatchesRunningCollector() {
    assumeDebugBuild();
    boolean expected = jvmReportsG1ActiveViaManagementBeans();
    assertEquals(expected, JavaProfiler.isG1ActiveForTest0());
  }
}
