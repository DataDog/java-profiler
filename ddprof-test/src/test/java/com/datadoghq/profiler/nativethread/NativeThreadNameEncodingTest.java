/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.nativethread;

import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.Platform;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.Set;
import java.util.TreeSet;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

/**
 * A native thread name read from /proc is cut at 15 bytes, which can split a character; the JFR
 * thread table must drop the cut-off bytes instead of writing invalid UTF-8.
 */
public class NativeThreadNameEncodingTest extends AbstractProfilerTest {
  private static final String KEPT = "native-é中";

  @Test
  public void cutNativeThreadNameKeepsWholeCharacters() throws Exception {
    Assumptions.assumeTrue(Platform.isLinux(), "native thread names are read from /proc on Linux");
    byte[] kept = KEPT.getBytes(StandardCharsets.UTF_8);
    byte[] cut = Arrays.copyOf(kept, kept.length + 2);
    cut[kept.length] = (byte) 0xE4; // the first two bytes of 中 (E4 B8 AD)
    cut[kept.length + 1] = (byte) 0xB8;
    try (NamedNativeThread thread = new NamedNativeThread(cut)) {
      Thread.sleep(500);
      // Stop while the thread runs: the profiler reads native thread names from /proc at stop.
      stopProfiler();
    }

    Set<String> seen = new TreeSet<>();
    for (JfrEvent event : verifyEvents("datadog.ExecutionSample")) {
      String name = event.getThreadName("eventThread");
      if (name != null && name.startsWith("native-")) {
        seen.add(name);
      }
    }
    assertTrue(
        seen.contains(KEPT), "expected a sample from a thread named " + KEPT + ", saw " + seen);
  }

  @Override
  protected String getProfilerCommand() {
    return "cpu=1ms";
  }
}
