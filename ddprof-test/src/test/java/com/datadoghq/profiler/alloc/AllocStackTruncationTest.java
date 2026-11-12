/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.alloc;

import static org.junit.jupiter.api.Assertions.*;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import java.util.concurrent.atomic.AtomicLong;
import org.junit.jupiter.api.Test;

/** Verifies allocation-stack truncation survives capture, storage, and JFR serialization. */
public class AllocStackTruncationTest extends AbstractProfilerTest {
  @Override
  protected boolean isPlatformSupported() {
    return !(Platform.isJ9() || Platform.isZing()) && Platform.isJavaVersionAtLeast(11);
  }

  @Override
  protected String getProfilerCommand() {
    String mode = testInfo.getTestMethod().get().getName().startsWith("jvmti") ? "jvmti" : "vm";
    return "memory=262144:a,jstackdepth=8,allocstack=" + mode;
  }

  @Test
  public void jvmtiDepthLimitIsStoredAsTruncated() throws Exception {
    checkTruncation();
  }

  @Test
  public void vmDepthLimitIsStoredAsTruncated() throws Exception {
    checkTruncation();
  }

  private void checkTruncation() throws Exception {
    runTests(new AllocStackWorkload(), new AllocStackWorkload());
    AtomicLong samples = new AtomicLong();
    streamEvents(
        "datadog.ObjectSample",
        event -> {
          if (AllocStackWorkload.isBlobSample(event)
              && !AllocStackWorkload.isDroppedSample(event)) {
            samples.incrementAndGet();
            assertNotNull(event.getStackTrace());
            assertEquals(8, event.getStackTrace().frames().size());
            assertTrue(event.getStackTrace().isTruncated(), "lost allocation truncation metadata");
          }
        });
    assertTrue(samples.get() > 0, "no workload samples to check");
  }
}
