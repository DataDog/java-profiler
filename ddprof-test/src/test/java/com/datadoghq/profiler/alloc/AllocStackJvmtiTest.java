/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.alloc;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Test;

import java.util.Map;
import java.util.concurrent.atomic.AtomicLong;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * allocstack=jvmti keeps capturing allocation sample stacks with JVMTI GetStackTrace, the
 * escape hatch from the VM stack walker: the walker must not run, and the stacks stay complete.
 */
public class AllocStackJvmtiTest extends AbstractProfilerTest {

  @Override
  protected boolean isPlatformSupported() {
    return !(Platform.isJ9() || Platform.isZing()) && Platform.isJavaVersionAtLeast(11);
  }

  @Override
  protected String getProfilerCommand() {
    return "memory=" + (256 * 1024) + ":a,allocstack=jvmti";
  }

  @Test
  public void getStackTraceIsUsed() throws Exception {
    runTests(new AllocStackWorkload());
    Map<String, Long> counters = profiler.getDebugCounters();

    AtomicLong blobs = new AtomicLong();
    AtomicLong expected = new AtomicLong();
    streamEvents("datadog.ObjectSample", event -> {
      if (AllocStackWorkload.isBlobSample(event)) {
        blobs.incrementAndGet();
        if (AllocStackWorkload.hasExpectedStack(event)) {
          expected.incrementAndGet();
        }
      }
    });
    assertTrue(blobs.get() > 0, "no allocation samples of the workload");
    assertEquals(blobs.get(), expected.get(), "allocation samples with a lost or extra frame");

    if (counters.containsKey("alloc_stack_vm")) {
      assertEquals(0L, counters.get("alloc_stack_vm"), "the VM walker ran with allocstack=jvmti: " + counters);
      assertEquals(0L, counters.get("alloc_stack_vm_fallback"), counters.toString());
    }
  }
}
