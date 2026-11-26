/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.endpoints;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import org.junit.jupiter.api.Test;

/**
 * JNI hands Java strings to the profiler as modified UTF-8 (supplementary characters as 6-byte
 * surrogate pairs, U+0000 as C0 80); the endpoint and operation constant pools must carry them as
 * standard UTF-8.
 */
public class EndpointEncodingTest extends AbstractProfilerTest {
  private static final long ROOT_SPAN_ID = 42;
  private static final String ENDPOINT = "GET /items/\uD83D\uDE00-\u00e9\u4e2d-a\u0000b";
  private static final String OPERATION_NAME = "op-\uD83D\uDE00-\u0000";

  @Test
  public void endpointAndOperationRoundTrip() {
    assertTrue(profiler.recordTraceRoot(ROOT_SPAN_ID, ENDPOINT, OPERATION_NAME, 16));
    stopProfiler();

    int matched = 0;
    for (JfrEvent event : verifyEvents("datadog.Endpoint")) {
      if (event.getLong(LOCAL_ROOT_SPAN_ID, -1) == ROOT_SPAN_ID) {
        assertEquals(ENDPOINT, event.getString("endpoint"));
        assertEquals(OPERATION_NAME, event.getString(OPERATION));
        matched++;
      }
    }
    assertEquals(1, matched, "expected one datadog.Endpoint event for root span " + ROOT_SPAN_ID);
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=~1ms";
  }
}
