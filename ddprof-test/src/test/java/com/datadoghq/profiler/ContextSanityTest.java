/*
 * Copyright 2025, Datadog, Inc
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
 * via getThreadContext() correctly, ensuring proper memory visibility
 * between Java writes and native reads.
 */
public class ContextSanityTest {

  private static JavaProfiler profiler;

  @BeforeAll
  public static void setup() throws IOException {
    // Initialize profiler (loads native library)
    profiler = JavaProfiler.getInstance();
  }

  /**
   * Tests basic context write-read cycle.
   * Writes context values and verifies they can be read back correctly.
   */
  @Test
  public void testBasicContextWriteRead() {
    long expectedSpanId = 12345L;
    long expectedRootSpanId = 67890L;

    profiler.setContext(expectedSpanId, expectedRootSpanId);

    ThreadContext values = profiler.getThreadContext();

    assertEquals(expectedSpanId, values.getSpanId(),
        "SpanId should match what was written");
    assertEquals(expectedRootSpanId, values.getRootSpanId(),
        "RootSpanId should match what was written");
    assertEquals(ThreadContext.computeContextChecksum(expectedSpanId, expectedRootSpanId), values.getChecksum());
  }

  /**
   * Tests multiple sequential context updates.
   * Verifies each update is correctly visible in the buffer.
   */
  @Test
  public void testSequentialContextUpdates() {
    // Update 1
    profiler.setContext(1L, 2L);
    ThreadContext values1 = profiler.getThreadContext();
    assertEquals(1L, values1.getSpanId());
    assertEquals(2L, values1.getRootSpanId());
    assertEquals(ThreadContext.computeContextChecksum(1L, 2L), values1.getChecksum());

    // Update 2
    profiler.setContext(10L, 20L);
    ThreadContext values2 = profiler.getThreadContext();
    assertEquals(10L, values2.getSpanId());
    assertEquals(20L, values2.getRootSpanId());
    assertEquals(ThreadContext.computeContextChecksum(10L, 20L), values2.getChecksum());

    // Update 3
    profiler.setContext(100L, 200L);
    ThreadContext values3 = profiler.getThreadContext();
    assertEquals(100L, values3.getSpanId());
    assertEquals(200L, values3.getRootSpanId());
    assertEquals(ThreadContext.computeContextChecksum(100L, 200L), values3.getChecksum());
  }

  /**
   * Tests context with zero values (special case).
   * Verifies that clearing context is readable.
   */
  @Test
  public void testZeroContext() {
    profiler.setContext(0L, 0L);

    ThreadContext values = profiler.getThreadContext();

    assertEquals(0L, values.getSpanId(), "SpanId should be zero");
    assertEquals(0L, values.getRootSpanId(), "RootSpanId should be zero");
    assertEquals(ThreadContext.computeContextChecksum(0L, 0L), values.getChecksum());
  }

  /**
   * Tests context with maximum long values.
   * Verifies handling and readability of boundary values.
   */
  @Test
  public void testMaxValueContext() {
    long maxValue = Long.MAX_VALUE;
    profiler.setContext(maxValue, maxValue);

    ThreadContext values = profiler.getThreadContext();

    assertEquals(maxValue, values.getSpanId(), "SpanId should be MAX_VALUE");
    assertEquals(maxValue, values.getRootSpanId(), "RootSpanId should be MAX_VALUE");
    assertEquals(ThreadContext.computeContextChecksum(maxValue, maxValue), values.getChecksum());
  }

  /**
   * Tests context value roundtrip through many writes.
   * Verifies no corruption occurs over repeated updates and all values are readable.
   */
  @Test
  public void testRepeatedContextWrites() {
    // Perform 1000 roundtrips
    for (int i = 0; i < 1000; i++) {
      long spanId = i * 2L;
      long rootSpanId = i * 2L + 1;

      profiler.setContext(spanId, rootSpanId);

      ThreadContext values = profiler.getThreadContext();
      assertEquals(spanId, values.getSpanId(),
          "SpanId mismatch at iteration " + i);
      assertEquals(rootSpanId, values.getRootSpanId(),
          "RootSpanId mismatch at iteration " + i);
      assertEquals(ThreadContext.computeContextChecksum(spanId, rootSpanId), values.getChecksum());
    }
  }

  /**
   * Tests context writes with varied value patterns.
   * Ensures all value patterns are correctly written and readable.
   */
  @Test
  public void testVariedContextValues() {
    // Test various patterns
    long[][] testValues = {
        {0L, 1L},
        {-1L, -1L},
        {Long.MAX_VALUE, Long.MIN_VALUE},
        {0xDEADBEEFL, 0xCAFEBABEL},
        {1234567890L, 9876543210L}
    };

    for (int i = 0; i < testValues.length; i++) {
      long spanId = testValues[i][0];
      long rootSpanId = testValues[i][1];

      profiler.setContext(spanId, rootSpanId);

      ThreadContext values = profiler.getThreadContext();
      assertEquals(spanId, values.getSpanId(),
          "SpanId mismatch for test pattern " + i);
      assertEquals(rootSpanId, values.getRootSpanId(),
          "RootSpanId mismatch for test pattern " + i);
      assertEquals(ThreadContext.computeContextChecksum(spanId, rootSpanId), values.getChecksum());
    }
  }

  /**
   * Tests nested context updates (context re-sets).
   * Verifies that repeatedly setting context on the same thread overwrites
   * previous values correctly and each update is immediately visible.
   */
  @Test
  public void testNestedContextUpdates() {
    // Set initial context
    profiler.setContext(100L, 100L);
    ThreadContext values1 = profiler.getThreadContext();
    assertEquals(100L, values1.getSpanId(), "Initial spanId should be 100");
    assertEquals(100L, values1.getRootSpanId(), "Initial rootSpanId should be 100");
    assertEquals(ThreadContext.computeContextChecksum(100L, 100L), values1.getChecksum());

    // Nested update 1 - overwrite with new context
    profiler.setContext(200L, 200L);
    ThreadContext values2 = profiler.getThreadContext();
    assertEquals(200L, values2.getSpanId(), "Nested spanId should be 200");
    assertEquals(200L, values2.getRootSpanId(), "Nested rootSpanId should be 200");
    assertEquals(ThreadContext.computeContextChecksum(200L, 200L), values2.getChecksum());

    // Nested update 2 - overwrite again
    profiler.setContext(300L, 300L);
    ThreadContext values3 = profiler.getThreadContext();
    assertEquals(300L, values3.getSpanId(), "Second nested spanId should be 300");
    assertEquals(300L, values3.getRootSpanId(), "Second nested rootSpanId should be 300");
    assertEquals(ThreadContext.computeContextChecksum(300L, 300L), values3.getChecksum());

    // Nested update 3 - different spanId and rootSpanId
    profiler.setContext(400L, 350L);
    ThreadContext values4 = profiler.getThreadContext();
    assertEquals(400L, values4.getSpanId(), "Third nested spanId should be 400");
    assertEquals(350L, values4.getRootSpanId(), "Third nested rootSpanId should be 350");
    assertEquals(ThreadContext.computeContextChecksum(400L, 350L), values4.getChecksum());

    // Clear context (set to zero)
    profiler.setContext(0L, 0L);
    ThreadContext values5 = profiler.getThreadContext();
    assertEquals(0L, values5.getSpanId(), "Cleared spanId should be 0");
    assertEquals(0L, values5.getRootSpanId(), "Cleared rootSpanId should be 0");
    assertEquals(ThreadContext.computeContextChecksum(0L, 0L), values5.getChecksum());
  }

  /**
   * Tests thread-local storage isolation between threads.
   * Thread A spawns Thread B while A has context C1. Thread B immediately
   * sets context C2. Verifies both threads have independent context storage
   * and each thread can read its own context correctly.
   */
  @Test
  public void testThreadIsolation() throws InterruptedException {
    // Thread A (main test thread) sets context C1
    long threadASpanId = 1000L;
    long threadARootSpanId = 1000L;
    profiler.setContext(threadASpanId, threadARootSpanId);

    // Verify Thread A can read its context
    ThreadContext valuesA1 = profiler.getThreadContext();
    assertEquals(threadASpanId, valuesA1.getSpanId(), "Thread A initial spanId");
    assertEquals(threadARootSpanId, valuesA1.getRootSpanId(), "Thread A initial rootSpanId");
    assertEquals(ThreadContext.computeContextChecksum(threadASpanId, threadARootSpanId), valuesA1.getChecksum());

    // Holder for Thread B's results
    final long threadBSpanId = 2000L;
    final long threadBRootSpanId = 2000L;
    final boolean[] threadBSuccess = {false};
    final AssertionError[] threadBError = {null};

    // Thread A spawns Thread B
    Thread threadB = new Thread(() -> {
      try {
        // Thread B immediately sets its own context C2
        profiler.setContext(threadBSpanId, threadBRootSpanId);

        // Thread B reads its own context
        ThreadContext valuesB = profiler.getThreadContext();

        // Verify Thread B has its own context, not Thread A's
        assertEquals(threadBSpanId, valuesB.getSpanId(), "Thread B spanId should be its own");
        assertEquals(threadBRootSpanId, valuesB.getRootSpanId(), "Thread B rootSpanId should be its own");
        assertEquals(ThreadContext.computeContextChecksum(threadBSpanId, threadBRootSpanId), valuesB.getChecksum());

        threadBSuccess[0] = true;
      } catch (AssertionError e) {
        threadBError[0] = e;
      }
    }, "TestThread-B");

    threadB.start();
    threadB.join();

    // Verify Thread B's assertions passed
    if (threadBError[0] != null) {
      throw threadBError[0];
    }
    assertTrue(threadBSuccess[0], "Thread B should have completed successfully");

    // Verify Thread A's context is unchanged after Thread B ran
    ThreadContext valuesA2 = profiler.getThreadContext();
    assertEquals(threadASpanId, valuesA2.getSpanId(), "Thread A spanId should be unchanged");
    assertEquals(threadARootSpanId, valuesA2.getRootSpanId(), "Thread A rootSpanId should be unchanged");
    assertEquals(ThreadContext.computeContextChecksum(threadASpanId, threadARootSpanId), valuesA2.getChecksum());
  }
}
