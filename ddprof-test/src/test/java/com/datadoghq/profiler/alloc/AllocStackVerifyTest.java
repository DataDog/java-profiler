/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.alloc;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Test;

import java.util.Map;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.atomic.AtomicLong;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * allocstack=verify: allocation samples are walked by the VM stack walker and every walk is
 * checked against JVMTI GetStackTrace on the same thread. The walker reads the stack in place
 * instead of building a vframe per frame in the allocating thread's resource area, so it must
 * produce exactly the frames GetStackTrace does: same methods and bytecode indexes, for
 * interpreted, compiled and inlined frames.
 */
public class AllocStackVerifyTest extends AbstractProfilerTest {

  @Override
  protected boolean isPlatformSupported() {
    // The VM stack walker is HotSpot-only; the allocation sampler needs JDK 11+.
    return !(Platform.isJ9() || Platform.isZing()) && Platform.isJavaVersionAtLeast(11);
  }

  @Override
  protected String getProfilerCommand() {
    return "memory=" + (256 * 1024) + ":a,allocstack=verify";
  }

  @Test
  public void vmWalkMatchesGetStackTrace() throws Exception {
    runTests(new AllocStackWorkload(), new AllocStackWorkload());
    // stopProfiler() has run; a virtual thread is sampled in a second recording.
    Map<String, Long> counters = profiler.getDebugCounters();

    AtomicLong blobs = new AtomicLong();
    AtomicLong expected = new AtomicLong();
    streamEvents("datadog.ObjectSample", event -> {
      if (AllocStackWorkload.isBlobSample(event) && !AllocStackWorkload.isDroppedSample(event)) {
        blobs.incrementAndGet();
        if (AllocStackWorkload.hasExpectedStack(event)) {
          expected.incrementAndGet();
        }
      }
    });
    assertTrue(blobs.get() > 0, "no allocation samples of the workload");
    assertEquals(blobs.get(), expected.get(), "allocation samples with a lost or extra frame");

    // Counters are compiled into every Linux build; elsewhere they may be absent.
    if (counters.containsKey("alloc_stack_verified")) {
      assertTrue(counters.get("alloc_stack_vm") > 0, "the VM walker was not used: " + counters);
      assertTrue(counters.get("alloc_stack_verified") >= 100, "too few verified samples: " + counters);
      assertEquals(0L, counters.get("alloc_stack_mismatch"), "walks differing from GetStackTrace: " + counters);
      // A walk that loses a frame falls back to GetStackTrace before it is verified, so a
      // walker regression would show up here rather than as a mismatch.
      assertTrue(counters.get("alloc_stack_vm_fallback") * 100 <= counters.get("alloc_stack_vm"),
          "too many fallbacks to GetStackTrace: " + counters);
    }
  }

  /**
   * A mounted virtual thread keeps using GetStackTrace, which stops at the continuation
   * boundary: the VM walker does not recognize that boundary on every JDK build and would
   * walk on into the carrier's frames.
   */
  @Test
  public void virtualThreadsUseGetStackTrace() throws Exception {
    boolean ran = AllocStackWorkload.runOnVirtualThread(new AllocStackWorkload());
    stopProfiler();
    if (!ran) {
      return; // no virtual threads on this JDK
    }
    Map<String, Long> counters = profiler.getDebugCounters();

    AtomicLong blobs = new AtomicLong();
    AtomicLong expected = new AtomicLong();
    streamEvents("datadog.ObjectSample", event -> {
      if (AllocStackWorkload.isBlobSample(event) && !AllocStackWorkload.isDroppedSample(event)) {
        blobs.incrementAndGet();
        if (AllocStackWorkload.hasExpectedStack(event)) {
          expected.incrementAndGet();
        }
      }
    });
    assertTrue(blobs.get() > 0, "no allocation samples of the workload");
    assertEquals(blobs.get(), expected.get(), "allocation samples with a lost or extra frame");
    if (counters.containsKey("alloc_stack_virtual_thread")) {
      assertTrue(counters.get("alloc_stack_virtual_thread") > 0, "virtual thread samples were not skipped: " + counters);
      assertEquals(0L, counters.get("alloc_stack_mismatch"), counters.toString());
    }
  }
  @Test
  public void verifyScratchSurvivesModeChangesAtTheSameStackDepth() throws Exception {
    stopProfiler();
    Path recording = Files.createTempFile("alloc-stack-restart", ".jfr");
    try {
      for (String mode : new String[] {"jvmti", "verify", "jvmti", "verify"}) {
        profiler.execute("start,memory=262144:a,allocstack=" + mode + ",jfr,file=" + recording);
        try {
          new AllocStackWorkload().run();
          new AllocStackWorkload().run();
        } finally {
          profiler.stop();
        }
        Map<String, Long> counters = profiler.getDebugCounters();
        if (counters.containsKey("alloc_stack_verified")) {
          if (mode.equals("verify")) {
            assertTrue(counters.get("alloc_stack_verified") >= 100, counters.toString());
            assertEquals(0L, counters.get("alloc_stack_mismatch"), counters.toString());
          } else {
            assertEquals(0L, counters.get("alloc_stack_verified"), counters.toString());
          }
        }
      }
    } finally {
      Files.deleteIfExists(recording);
    }
  }

}
