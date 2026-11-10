/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.alloc;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import java.util.Map;
import org.junit.jupiter.api.Test;

/**
 * cstack=vmx makes CPU and wall-clock stacks mixed (Java, native and VM frames), but allocation
 * sample stacks stay Java-only, exactly the frames JVMTI GetStackTrace reports, as they were before
 * the VM stack walker captured them.
 */
public class AllocStackVmxTest extends AbstractProfilerTest {

  @Override
  protected boolean isPlatformSupported() {
    return Platform.isLinux()
        && !(Platform.isJ9() || Platform.isZing())
        && Platform.isJavaVersionAtLeast(11);
  }

  @Override
  protected String getProfilerCommand() {
    return "memory=" + (256 * 1024) + ":a,cstack=vmx,allocstack=verify";
  }

  @Test
  public void allocationStacksStayJavaOnly() throws Exception {
    runTests(new AllocStackWorkload());
    Map<String, Long> counters = profiler.getDebugCounters();
    assertTrue(counters.containsKey("alloc_stack_verified"), "counters unavailable: " + counters);
    assertTrue(counters.get("alloc_stack_verified") > 0, "no verified samples: " + counters);
    assertEquals(
        0L,
        counters.get("alloc_stack_mismatch"),
        "walks differing from GetStackTrace: " + counters);
  }
}
