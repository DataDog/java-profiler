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
 * Without allocstack, a cstack other than vm/vmx keeps allocation sample stacks on JVMTI
 * GetStackTrace: the VM stack walker is only used where cstack already relies on it.
 */
public class AllocStackFollowsCstackTest extends AbstractProfilerTest {

  @Override
  protected boolean isPlatformSupported() {
    return Platform.isLinux()
        && !(Platform.isJ9() || Platform.isZing())
        && Platform.isJavaVersionAtLeast(11);
  }

  @Override
  protected String getProfilerCommand() {
    return "memory=" + (256 * 1024) + ":a,cstack=dwarf";
  }

  @Test
  public void getStackTraceWithoutVmStacks() throws Exception {
    runTests(new AllocStackWorkload());
    Map<String, Long> counters = profiler.getDebugCounters();
    assertTrue(counters.containsKey("alloc_stack_vm"), "counters unavailable: " + counters);
    assertEquals(
        0L, counters.get("alloc_stack_vm"), "the VM walker ran with cstack=dwarf: " + counters);
  }
}
