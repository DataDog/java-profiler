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
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Sanity tests for JavaProfiler context write-read functionality.
 * Verifies that context values written via setContext() can be read back
 * from the DirectByteBuffer correctly, ensuring proper memory visibility
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
   * Knuth's multiplicative hash constant for 64-bit values.
   * Must match the constant in JavaProfiler.
   */
  private static final long KNUTH_CONSTANT = 0x9E3779B97F4A7C15L;

  /**
   * Computes the expected checksum for given span IDs.
   * Uses the same Knuth hash algorithm as JavaProfiler.
   */
  private static long computeExpectedChecksum(long spanId, long rootSpanId) {
    long hashSpanId = spanId * KNUTH_CONSTANT;
    long hashRootSpanId = rootSpanId * KNUTH_CONSTANT;
    return hashSpanId ^ hashRootSpanId;
  }

  /**
   * Helper method to read context values from the DirectByteBuffer.
   */
  private static class ContextValues {
    final long spanId;
    final long rootSpanId;
    final long checksum;

    ContextValues(ByteBuffer buffer) {
      buffer.order(ByteOrder.LITTLE_ENDIAN);
      this.spanId = buffer.getLong(0);
      this.rootSpanId = buffer.getLong(8);
      this.checksum = buffer.getLong(16);
    }

    /**
     * Validates that the checksum matches the expected Knuth hash-based value
     * and that the write is complete (even checksum bit).
     */
    void assertChecksumValid() {
      long expectedChecksum = computeExpectedChecksum(spanId, rootSpanId);
      // Mask off the low bit for comparison (bit 0 indicates write status)
      long actualChecksumValue = checksum & ~1L;
      long expectedChecksumValue = expectedChecksum & ~1L;

      assertEquals(expectedChecksumValue, actualChecksumValue,
          String.format("Checksum mismatch: span=%d, root=%d, expected=0x%X, actual=0x%X",
              spanId, rootSpanId, expectedChecksumValue, actualChecksumValue));

      assertTrue((checksum & 1) == 0,
          String.format("Checksum should be even (write complete), but got 0x%X", checksum));
    }
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

    ByteBuffer buffer = profiler.getContextBufferForTest();
    ContextValues values = new ContextValues(buffer);

    assertEquals(expectedSpanId, values.spanId,
        "SpanId should match what was written");
    assertEquals(expectedRootSpanId, values.rootSpanId,
        "RootSpanId should match what was written");
    values.assertChecksumValid();
  }

  /**
   * Tests multiple sequential context updates.
   * Verifies each update is correctly visible in the buffer.
   */
  @Test
  public void testSequentialContextUpdates() {
    ByteBuffer buffer = profiler.getContextBufferForTest();

    // Update 1
    profiler.setContext(1L, 2L);
    ContextValues values1 = new ContextValues(buffer);
    assertEquals(1L, values1.spanId);
    assertEquals(2L, values1.rootSpanId);
    values1.assertChecksumValid();

    // Update 2
    profiler.setContext(10L, 20L);
    ContextValues values2 = new ContextValues(buffer);
    assertEquals(10L, values2.spanId);
    assertEquals(20L, values2.rootSpanId);
    values2.assertChecksumValid();

    // Update 3
    profiler.setContext(100L, 200L);
    ContextValues values3 = new ContextValues(buffer);
    assertEquals(100L, values3.spanId);
    assertEquals(200L, values3.rootSpanId);
    values3.assertChecksumValid();
  }

  /**
   * Tests context with zero values (special case).
   * Verifies that clearing context is readable.
   */
  @Test
  public void testZeroContext() {
    profiler.setContext(0L, 0L);

    ByteBuffer buffer = profiler.getContextBufferForTest();
    ContextValues values = new ContextValues(buffer);

    assertEquals(0L, values.spanId, "SpanId should be zero");
    assertEquals(0L, values.rootSpanId, "RootSpanId should be zero");
    values.assertChecksumValid();
  }

  /**
   * Tests context with maximum long values.
   * Verifies handling and readability of boundary values.
   */
  @Test
  public void testMaxValueContext() {
    long maxValue = Long.MAX_VALUE;
    profiler.setContext(maxValue, maxValue);

    ByteBuffer buffer = profiler.getContextBufferForTest();
    ContextValues values = new ContextValues(buffer);

    assertEquals(maxValue, values.spanId, "SpanId should be MAX_VALUE");
    assertEquals(maxValue, values.rootSpanId, "RootSpanId should be MAX_VALUE");
    values.assertChecksumValid();
  }

  /**
   * Tests context value roundtrip through many writes.
   * Verifies no corruption occurs over repeated updates and all values are readable.
   */
  @Test
  public void testRepeatedContextWrites() {
    ByteBuffer buffer = profiler.getContextBufferForTest();

    // Perform 1000 roundtrips
    for (int i = 0; i < 1000; i++) {
      long spanId = i * 2L;
      long rootSpanId = i * 2L + 1;

      profiler.setContext(spanId, rootSpanId);

      ContextValues values = new ContextValues(buffer);
      assertEquals(spanId, values.spanId,
          "SpanId mismatch at iteration " + i);
      assertEquals(rootSpanId, values.rootSpanId,
          "RootSpanId mismatch at iteration " + i);
      values.assertChecksumValid();
    }
  }

  /**
   * Tests context writes with varied value patterns.
   * Ensures all value patterns are correctly written and readable.
   */
  @Test
  public void testVariedContextValues() {
    ByteBuffer buffer = profiler.getContextBufferForTest();

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

      ContextValues values = new ContextValues(buffer);
      assertEquals(spanId, values.spanId,
          "SpanId mismatch for test pattern " + i);
      assertEquals(rootSpanId, values.rootSpanId,
          "RootSpanId mismatch for test pattern " + i);
      values.assertChecksumValid();
    }
  }

  /**
   * Tests nested context updates (context re-sets).
   * Verifies that repeatedly setting context on the same thread overwrites
   * previous values correctly and each update is immediately visible.
   */
  @Test
  public void testNestedContextUpdates() {
    ByteBuffer buffer = profiler.getContextBufferForTest();

    // Set initial context
    profiler.setContext(100L, 100L);
    ContextValues values1 = new ContextValues(buffer);
    assertEquals(100L, values1.spanId, "Initial spanId should be 100");
    assertEquals(100L, values1.rootSpanId, "Initial rootSpanId should be 100");
    values1.assertChecksumValid();

    // Nested update 1 - overwrite with new context
    profiler.setContext(200L, 200L);
    ContextValues values2 = new ContextValues(buffer);
    assertEquals(200L, values2.spanId, "Nested spanId should be 200");
    assertEquals(200L, values2.rootSpanId, "Nested rootSpanId should be 200");
    values2.assertChecksumValid();

    // Nested update 2 - overwrite again
    profiler.setContext(300L, 300L);
    ContextValues values3 = new ContextValues(buffer);
    assertEquals(300L, values3.spanId, "Second nested spanId should be 300");
    assertEquals(300L, values3.rootSpanId, "Second nested rootSpanId should be 300");
    values3.assertChecksumValid();

    // Nested update 3 - different spanId and rootSpanId
    profiler.setContext(400L, 350L);
    ContextValues values4 = new ContextValues(buffer);
    assertEquals(400L, values4.spanId, "Third nested spanId should be 400");
    assertEquals(350L, values4.rootSpanId, "Third nested rootSpanId should be 350");
    values4.assertChecksumValid();

    // Clear context (set to zero)
    profiler.setContext(0L, 0L);
    ContextValues values5 = new ContextValues(buffer);
    assertEquals(0L, values5.spanId, "Cleared spanId should be 0");
    assertEquals(0L, values5.rootSpanId, "Cleared rootSpanId should be 0");
    values5.assertChecksumValid();
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
    ByteBuffer bufferA = profiler.getContextBufferForTest();
    ContextValues valuesA1 = new ContextValues(bufferA);
    assertEquals(threadASpanId, valuesA1.spanId, "Thread A initial spanId");
    assertEquals(threadARootSpanId, valuesA1.rootSpanId, "Thread A initial rootSpanId");
    valuesA1.assertChecksumValid();

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
        ByteBuffer bufferB = profiler.getContextBufferForTest();
        ContextValues valuesB = new ContextValues(bufferB);

        // Verify Thread B has its own context, not Thread A's
        assertEquals(threadBSpanId, valuesB.spanId, "Thread B spanId should be its own");
        assertEquals(threadBRootSpanId, valuesB.rootSpanId, "Thread B rootSpanId should be its own");
        valuesB.assertChecksumValid();

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
    ContextValues valuesA2 = new ContextValues(bufferA);
    assertEquals(threadASpanId, valuesA2.spanId, "Thread A spanId should be unchanged");
    assertEquals(threadARootSpanId, valuesA2.rootSpanId, "Thread A rootSpanId should be unchanged");
    valuesA2.assertChecksumValid();
  }
}
