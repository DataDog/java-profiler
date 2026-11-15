/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.nativesocket;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.Platform;
import java.net.DatagramSocket;
import java.nio.channels.Selector;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;
import org.junit.jupiter.api.Test;

/** Qualifies errno across all four real installed imports and actual sampled JFR recording. */
public class NativeIoErrnoTest extends AbstractProfilerTest {
  @Override
  protected boolean isPlatformSupported() {
    return Platform.isLinux();
  }

  @Override
  protected String getProfilerCommand() {
    return "natsock=1us";
  }

  @Override
  protected void beforeProfilerStart() throws Exception {
    System.loadLibrary("ddproftest");
    // Load the real JDK networking libraries before the patcher scans imports.
    try (DatagramSocket socket = new DatagramSocket();
        Selector selector = Selector.open()) {
      assertTrue(socket.isBound());
      selector.selectNow();
    }
  }

  /**
   * Requires successful original I/O with preserved errno and sampled evidence for every branch.
   */
  @Test
  public void preservesErrnoDuringPreOriginalLoggingAndSampledRecording() throws Exception {
    assertEquals(0, exerciseImports(), "native import/errno qualification failure code");
    stopProfiler();
    Set<String> operations = new HashSet<>();
    for (JfrEvent event : verifyEvents("datadog.NativeSocketEvent")) {
      operations.add(event.getString(OPERATION));
    }
    assertTrue(
        operations.containsAll(Arrays.asList("SEND", "RECV", "WRITE", "READ")),
        "Each actual sampled hook must record, observed: " + operations);
  }

  /** Calls installed JDK import targets; returns a source-named setup or errno failure code. */
  private static native int exerciseImports();
}
