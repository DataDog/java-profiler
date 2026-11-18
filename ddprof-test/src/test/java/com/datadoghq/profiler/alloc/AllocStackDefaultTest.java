/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.alloc;

import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import java.util.Map;
import org.junit.jupiter.api.Test;

/**
 * Without allocstack, allocation sample stacks follow cstack: on Linux HotSpot the default cstack
 * is vm, so the VM stack walker captures them rather than JVMTI GetStackTrace, whose per-frame
 * vframes grow the allocating threads' resource areas by malloc'd chunks.
 */
public class AllocStackDefaultTest extends AbstractProfilerTest {

  @Override
  protected boolean isPlatformSupported() {
    return Platform.isLinux()
        && !(Platform.isJ9() || Platform.isZing())
        && Platform.isJavaVersionAtLeast(11);
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
    assertTrue(
        walked >= 100, "too few VM allocation samples to evaluate fallback rate: " + counters);
    // A sample with no Java frame for the walker falls back; that is the exception.
    assertTrue(fallback <= walked / 100, "too many fallbacks to GetStackTrace: " + counters);
  }
}
