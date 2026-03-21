/*
 * Copyright 2025, 2026 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.datadoghq.profiler;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import java.io.IOException;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Sanity tests for JavaProfiler context write-read functionality.
 * Verifies that context values written via setContext() can be read back
 * via getThreadContext() correctly.
 */
public class ContextSanityTest {

  private static JavaProfiler profiler;

  @BeforeAll
  public static void setup() throws IOException {
    profiler = JavaProfiler.getInstance();
  }

  @Test
  public void testBasicContextWriteRead() {
    long expectedSpanId = 12345L;
    long expectedRootSpanId = 67890L;

    // Use 4-arg form: rootSpanId maps to localRootSpanId
    profiler.setContext(expectedRootSpanId, expectedSpanId, 0, expectedSpanId);

    ThreadContext values = profiler.getThreadContext();

    assertEquals(expectedSpanId, values.getSpanId(),
        "SpanId should match what was written");
    assertEquals(expectedRootSpanId, values.getRootSpanId(),
        "RootSpanId should match what was written");
  }

  @Test
  public void testSequentialContextUpdates() {
    profiler.setContext(2L, 1L, 0, 1L);
    ThreadContext values1 = profiler.getThreadContext();
    assertEquals(1L, values1.getSpanId());
    assertEquals(2L, values1.getRootSpanId());

    profiler.setContext(20L, 10L, 0, 10L);
    ThreadContext values2 = profiler.getThreadContext();
    assertEquals(10L, values2.getSpanId());
    assertEquals(20L, values2.getRootSpanId());

    profiler.setContext(200L, 100L, 0, 100L);
    ThreadContext values3 = profiler.getThreadContext();
    assertEquals(100L, values3.getSpanId());
    assertEquals(200L, values3.getRootSpanId());
  }

  @Test
  public void testZeroContext() {
    profiler.clearContext();

    ThreadContext values = profiler.getThreadContext();

    assertEquals(0L, values.getSpanId(), "SpanId should be zero");
    assertEquals(0L, values.getRootSpanId(), "RootSpanId should be zero");
  }

  @Test
  public void testMaxValueContext() {
    long maxValue = Long.MAX_VALUE;
    profiler.setContext(maxValue, maxValue, 0, maxValue);

    ThreadContext values = profiler.getThreadContext();

    assertEquals(maxValue, values.getSpanId(), "SpanId should be MAX_VALUE");
    assertEquals(maxValue, values.getRootSpanId(), "RootSpanId should be MAX_VALUE");
  }

  @Test
  public void testRepeatedContextWrites() {
    for (int i = 1; i <= 1000; i++) {
      long spanId = i * 2L;
      long rootSpanId = i * 2L + 1;

      profiler.setContext(rootSpanId, spanId, 0, spanId);

      ThreadContext values = profiler.getThreadContext();
      assertEquals(spanId, values.getSpanId(),
          "SpanId mismatch at iteration " + i);
      assertEquals(rootSpanId, values.getRootSpanId(),
          "RootSpanId mismatch at iteration " + i);
    }
  }

  @Test
  public void testVariedContextValues() {
    // [localRootSpanId, spanId]
    long[][] testValues = {
        {1L, 0L},          // spanId=0 clears context — skip clear case
        {0xCAFEBABEL, 0xDEADBEEFL},
        {9876543210L, 1234567890L}
    };

    for (int i = 0; i < testValues.length; i++) {
      long rootSpanId = testValues[i][0];
      long spanId = testValues[i][1];

      if (spanId == 0) {
        // OTEL mode: spanId=0 means clear
        continue;
      }

      profiler.setContext(rootSpanId, spanId, 0, spanId);

      ThreadContext values = profiler.getThreadContext();
      assertEquals(spanId, values.getSpanId(),
          "SpanId mismatch for test pattern " + i);
      assertEquals(rootSpanId, values.getRootSpanId(),
          "RootSpanId mismatch for test pattern " + i);
    }
  }

  @Test
  public void testNestedContextUpdates() {
    profiler.setContext(100L, 100L, 0, 100L);
    ThreadContext values1 = profiler.getThreadContext();
    assertEquals(100L, values1.getSpanId());
    assertEquals(100L, values1.getRootSpanId());

    profiler.setContext(200L, 200L, 0, 200L);
    ThreadContext values2 = profiler.getThreadContext();
    assertEquals(200L, values2.getSpanId());
    assertEquals(200L, values2.getRootSpanId());

    profiler.setContext(300L, 300L, 0, 300L);
    ThreadContext values3 = profiler.getThreadContext();
    assertEquals(300L, values3.getSpanId());
    assertEquals(300L, values3.getRootSpanId());

    profiler.setContext(350L, 400L, 0, 400L);
    ThreadContext values4 = profiler.getThreadContext();
    assertEquals(400L, values4.getSpanId());
    assertEquals(350L, values4.getRootSpanId());

    profiler.clearContext();
    ThreadContext values5 = profiler.getThreadContext();
    assertEquals(0L, values5.getSpanId());
    assertEquals(0L, values5.getRootSpanId());
  }

  @Test
  public void testThreadIsolation() throws InterruptedException {
    long threadASpanId = 1000L;
    long threadARootSpanId = 1001L;
    profiler.setContext(threadARootSpanId, threadASpanId, 0, threadASpanId);

    ThreadContext valuesA1 = profiler.getThreadContext();
    assertEquals(threadASpanId, valuesA1.getSpanId());
    assertEquals(threadARootSpanId, valuesA1.getRootSpanId());

    final long threadBSpanId = 2000L;
    final long threadBRootSpanId = 2001L;
    final boolean[] threadBSuccess = {false};
    final AssertionError[] threadBError = {null};

    Thread threadB = new Thread(() -> {
      try {
        profiler.setContext(threadBRootSpanId, threadBSpanId, 0, threadBSpanId);

        ThreadContext valuesB = profiler.getThreadContext();
        assertEquals(threadBSpanId, valuesB.getSpanId());
        assertEquals(threadBRootSpanId, valuesB.getRootSpanId());

        threadBSuccess[0] = true;
      } catch (AssertionError e) {
        threadBError[0] = e;
      }
    }, "TestThread-B");

    threadB.start();
    threadB.join();

    if (threadBError[0] != null) {
      throw threadBError[0];
    }
    assertTrue(threadBSuccess[0]);

    ThreadContext valuesA2 = profiler.getThreadContext();
    assertEquals(threadASpanId, valuesA2.getSpanId());
    assertEquals(threadARootSpanId, valuesA2.getRootSpanId());
  }
}
