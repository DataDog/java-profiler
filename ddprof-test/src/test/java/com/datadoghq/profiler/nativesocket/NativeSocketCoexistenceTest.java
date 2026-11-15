/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.nativesocket;

import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.wallclock.NativeSocketTaskBlockTest;
import org.junit.jupiter.api.Test;

/** Requires both native I/O owners to record the same real blocking socket workload. */
public class NativeSocketCoexistenceTest extends NativeSocketTaskBlockTest {
  @Override
  protected String getProfilerCommand() {
    return super.getProfilerCommand() + ",natsock=1us";
  }

  /** Retains the original TaskBlock/stack assertions and also requires an inbound byte event. */
  @Override
  @Test
  public void blockingSocketReadEmitsIoWaitTaskBlock() throws Exception {
    super.blockingSocketReadEmitsIoWaitTaskBlock();
    boolean readerSampled = false;
    for (JfrEvent event : verifyEvents("datadog.NativeSocketEvent")) {
      String operation = event.getString(OPERATION);
      if (("READ".equals(operation) || "RECV".equals(operation))
          && "taskblock-native-socket-read".equals(event.getThreadName("eventThread"))) {
        readerSampled = true;
      }
    }
    assertTrue(readerSampled, "The actual TaskBlock reader must also produce a socket byte sample");
  }
}
