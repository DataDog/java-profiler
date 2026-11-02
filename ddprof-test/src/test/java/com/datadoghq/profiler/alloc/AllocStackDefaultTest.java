/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.alloc;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Test;

import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Without allocstack, allocation sample stacks follow cstack: on Linux HotSpot the default
 * cstack is vm, so the VM stack walker captures them rather than JVMTI GetStackTrace, whose
 * per-frame vframes grow the allocating threads' resource areas by malloc'd chunks.
 */
public class AllocStackDefaultTest extends AbstractProfilerTest {

  @Override
  protected boolean isPlatformSupported() {
    return Platform.isLinux() && !(Platform.isJ9() || Platform.isZing()) && Platform.isJavaVersionAtLeast(11);
  }

  @Override
  protected String getProfilerCommand() {
    return "memory=" + (256 * 1024) + ":a";
  }

  @Test
  public void vmWalkerIsTheDefault() throws Exception {
    runTests(new AllocStackWorkload());
    Map<String, Long> counters = profiler.getDebugCounters();
    long walked = counters.getOrDefault("alloc_stack_vm", 0L);
    long fallback = counters.getOrDefault("alloc_stack_vm_fallback", 0L);
    assertTrue(walked > 0, "the VM walker did not capture allocation stacks by default: " + counters);
    // A sample with no Java frame for the walker falls back; that is the exception.
    assertTrue(fallback * 100 <= walked, "too many fallbacks to GetStackTrace: " + counters);
  }
}
