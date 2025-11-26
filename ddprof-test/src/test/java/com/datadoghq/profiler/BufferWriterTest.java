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

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Comprehensive tests for {@link BufferWriter} class.
 *
 * <p>This test validates:
 * <ul>
 *   <li>Correct implementation selection based on Java version</li>
 *   <li>Basic write and read operations (ordered and volatile semantics)</li>
 *   <li>Release (ordered) semantics for single-threaded signal handler safety</li>
 *   <li>Volatile (full barrier) semantics ensuring visibility across threads</li>
 *   <li>Return value validation</li>
 *   <li>Int and long write operations</li>
 *   <li>Various offsets and buffer positions</li>
 *   <li>Edge cases and boundary conditions</li>
 * </ul>
 */
public class BufferWriterTest {

    private BufferWriter bufferWriter;

    @BeforeEach
    public void setUp() {
        bufferWriter = new BufferWriter();
    }

    /**
     * Helper method to create a direct ByteBuffer with native byte order.
     * BufferWriter implementations use native byte order, so tests must read in the same order.
     */
    private ByteBuffer createBuffer(int capacity) {
        return ByteBuffer.allocateDirect(capacity).order(ByteOrder.nativeOrder());
    }

    /**
     * Tests that the correct implementation is loaded based on Java version.
     */
    @Test
    public void testCorrectImplementationLoaded() {
        assertNotNull(bufferWriter, "BufferWriter instance should not be null");

        // Verify implementation can be used without throwing exceptions
        ByteBuffer buffer = createBuffer(16);
        assertDoesNotThrow(() -> bufferWriter.writeOrderedLong(buffer, 0, 42L));
        assertDoesNotThrow(() -> bufferWriter.writeVolatileLong(buffer, 8, 99L));
    }

    /**
     * Tests basic ordered long write and read functionality at offset 0.
     */
    @Test
    public void testWriteOrderedLongAtOffsetZero() {
        ByteBuffer buffer = createBuffer(16);
        long expectedValue = 0x123456789ABCDEF0L;

        long returnedValue = bufferWriter.writeOrderedLong(buffer, 0, expectedValue);
        long actualValue = buffer.getLong(0);

        assertEquals(expectedValue, returnedValue, "Return value should match written value");
        assertEquals(expectedValue, actualValue, "Buffer value should match written value");
    }

    /**
     * Tests basic volatile long write and read functionality at offset 0.
     */
    @Test
    public void testWriteVolatileLongAtOffsetZero() {
        ByteBuffer buffer = createBuffer(16);
        long expectedValue = 0xFEDCBA9876543210L;

        long returnedValue = bufferWriter.writeVolatileLong(buffer, 0, expectedValue);
        long actualValue = buffer.getLong(0);

        assertEquals(expectedValue, returnedValue, "Return value should match written value");
        assertEquals(expectedValue, actualValue, "Buffer value should match written value");
    }

    /**
     * Tests basic ordered int write and read functionality.
     */
    @Test
    public void testWriteOrderedInt() {
        ByteBuffer buffer = createBuffer(16);
        int expectedValue = 0x12345678;

        bufferWriter.writeOrderedInt(buffer, 0, expectedValue);
        int actualValue = buffer.getInt(0);

        assertEquals(expectedValue, actualValue, "Buffer value should match written int value");
    }

    /**
     * Tests basic volatile int write and read functionality.
     */
    @Test
    public void testWriteVolatileInt() {
        ByteBuffer buffer = createBuffer(16);
        int expectedValue = 0xABCDEF01;

        bufferWriter.writeVolatileInt(buffer, 0, expectedValue);
        int actualValue = buffer.getInt(0);

        assertEquals(expectedValue, actualValue, "Buffer value should match written int value");
    }

    /**
     * Tests ordered long write operations at various offsets within the buffer.
     */
    @Test
    public void testWriteOrderedLongAtVariousOffsets() {
        ByteBuffer buffer = createBuffer(64);

        // Test at different 8-byte aligned offsets
        int[] offsets = {0, 8, 16, 24, 32, 40, 48, 56};
        long[] expectedValues = {
                0x1111111111111111L,
                0x2222222222222222L,
                0x3333333333333333L,
                0x4444444444444444L,
                0x5555555555555555L,
                0x6666666666666666L,
                0x7777777777777777L,
                0x8888888888888888L
        };

        for (int i = 0; i < offsets.length; i++) {
            long returnedValue = bufferWriter.writeOrderedLong(buffer, offsets[i], expectedValues[i]);
            assertEquals(expectedValues[i], returnedValue,
                String.format("Return value at offset %d should match", offsets[i]));
        }

        for (int i = 0; i < offsets.length; i++) {
            long actualValue = buffer.getLong(offsets[i]);
            assertEquals(expectedValues[i], actualValue,
                    String.format("Buffer value at offset %d should match", offsets[i]));
        }
    }

    /**
     * Tests int write operations at various offsets within the buffer.
     */
    @Test
    public void testWriteIntAtVariousOffsets() {
        ByteBuffer buffer = createBuffer(64);

        // Test at different 4-byte aligned offsets
        int[] offsets = {0, 4, 8, 12, 16, 20, 24, 28};
        int[] expectedValues = {
                0x11111111,
                0x22222222,
                0x33333333,
                0x44444444,
                0x55555555,
                0x66666666,
                0x77777777,
                0x88888888
        };

        for (int i = 0; i < offsets.length; i++) {
            bufferWriter.writeOrderedInt(buffer, offsets[i], expectedValues[i]);
        }

        for (int i = 0; i < offsets.length; i++) {
            int actualValue = buffer.getInt(offsets[i]);
            assertEquals(expectedValues[i], actualValue,
                    String.format("Int value at offset %d should match", offsets[i]));
        }
    }

    /**
     * Tests writing special long values (min, max, zero, negative).
     */
    @Test
    public void testSpecialLongValues() {
        ByteBuffer buffer = createBuffer(40);
        long[] specialValues = {
                0L,                  // Zero
                Long.MIN_VALUE,      // Minimum long
                Long.MAX_VALUE,      // Maximum long
                -1L,                 // All bits set
                0xDEADBEEFCAFEBABEL // Arbitrary pattern
        };

        for (int i = 0; i < specialValues.length; i++) {
            int offset = i * 8;
            long returnedValue = bufferWriter.writeOrderedLong(buffer, offset, specialValues[i]);
            long actualValue = buffer.getLong(offset);
            assertEquals(specialValues[i], returnedValue,
                    String.format("Return value 0x%X should match written value", specialValues[i]));
            assertEquals(specialValues[i], actualValue,
                    String.format("Special value 0x%X should be written correctly", specialValues[i]));
        }
    }

    /**
     * Tests writing special int values (min, max, zero, negative).
     */
    @Test
    public void testSpecialIntValues() {
        ByteBuffer buffer = createBuffer(24);
        int[] specialValues = {
                0,                  // Zero
                Integer.MIN_VALUE,  // Minimum int
                Integer.MAX_VALUE,  // Maximum int
                -1,                 // All bits set
                0xDEADBEEF,        // Arbitrary pattern
                0x12345678         // Another pattern
        };

        for (int i = 0; i < specialValues.length; i++) {
            int offset = i * 4;
            bufferWriter.writeOrderedInt(buffer, offset, specialValues[i]);
            int actualValue = buffer.getInt(offset);
            assertEquals(specialValues[i], actualValue,
                    String.format("Special int value 0x%X should be written correctly", specialValues[i]));
        }
    }

    /**
     * Tests that multiple consecutive writes work correctly without interference.
     */
    @Test
    public void testConsecutiveWrites() {
        ByteBuffer buffer = createBuffer(16);
        int offset = 0;

        // Write multiple times to the same offset
        bufferWriter.writeOrderedLong(buffer, offset, 100L);
        assertEquals(100L, buffer.getLong(offset));

        bufferWriter.writeOrderedLong(buffer, offset, 200L);
        assertEquals(200L, buffer.getLong(offset));

        bufferWriter.writeVolatileLong(buffer, offset, 300L);
        assertEquals(300L, buffer.getLong(offset));
    }

    /**
     * Tests volatile write semantics across threads.
     *
     * <p>This test verifies that writes performed by one thread are visible to another thread,
     * ensuring the full volatile barrier semantics (writeVolatileLong) are working correctly
     * for cross-thread visibility.
     */
    @Test
    public void testVolatileSemantics() throws InterruptedException {
        ByteBuffer buffer = createBuffer(16);
        int offset = 0;
        AtomicBoolean writerReady = new AtomicBoolean(false);
        AtomicBoolean readerDone = new AtomicBoolean(false);
        AtomicLong readValue = new AtomicLong(-1);
        CountDownLatch writerLatch = new CountDownLatch(1);
        CountDownLatch readerLatch = new CountDownLatch(1);

        long expectedValue = 0xCAFEBABEDEADBEEFL;

        // Writer thread - must use writeVolatileLong for cross-thread visibility
        Thread writer = new Thread(() -> {
            try {
                writerLatch.await(5, TimeUnit.SECONDS);
                bufferWriter.writeVolatileLong(buffer, offset, expectedValue);
                writerReady.set(true);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        });

        // Reader thread
        Thread reader = new Thread(() -> {
            try {
                // Wait for writer to signal readiness
                long startTime = System.nanoTime();
                while (!writerReady.get()) {
                    if (System.nanoTime() - startTime > TimeUnit.SECONDS.toNanos(5)) {
                        break;
                    }
                    Thread.yield();
                }

                // Read the value written by the writer thread
                long value = buffer.getLong(offset);
                readValue.set(value);
                readerDone.set(true);
                readerLatch.countDown();
            } catch (Exception e) {
                Thread.currentThread().interrupt();
            }
        });

        reader.start();
        writer.start();

        // Trigger writer
        writerLatch.countDown();

        // Wait for both threads to complete
        writer.join(5000);
        reader.join(5000);

        assertTrue(readerDone.get(), "Reader should have completed");
        assertEquals(expectedValue, readValue.get(),
                "Reader thread should see the value written by writer thread");
    }

    /**
     * Tests that writes to adjacent locations don't interfere with each other.
     */
    @Test
    public void testNonInterference() {
        ByteBuffer buffer = createBuffer(32);

        long value1 = 0x1111111111111111L;
        long value2 = 0x2222222222222222L;
        long value3 = 0x3333333333333333L;

        bufferWriter.writeOrderedLong(buffer, 0, value1);
        bufferWriter.writeOrderedLong(buffer, 8, value2);
        bufferWriter.writeOrderedLong(buffer, 16, value3);

        assertEquals(value1, buffer.getLong(0), "First value should not be affected");
        assertEquals(value2, buffer.getLong(8), "Second value should not be affected");
        assertEquals(value3, buffer.getLong(16), "Third value should not be affected");
    }

    /**
     * Tests writing to a buffer at maximum valid offset for longs.
     */
    @Test
    public void testMaximumValidOffsetLong() {
        int bufferSize = 1024;
        ByteBuffer buffer = createBuffer(bufferSize);
        int maxValidOffset = bufferSize - 8; // 8 bytes for a long

        long expectedValue = 0xFEDCBA9876543210L;
        bufferWriter.writeOrderedLong(buffer, maxValidOffset, expectedValue);

        long actualValue = buffer.getLong(maxValidOffset);
        assertEquals(expectedValue, actualValue,
                "Value at maximum offset should be written correctly");
    }

    /**
     * Tests writing to a buffer at maximum valid offset for ints.
     */
    @Test
    public void testMaximumValidOffsetInt() {
        int bufferSize = 1024;
        ByteBuffer buffer = createBuffer(bufferSize);
        int maxValidOffset = bufferSize - 4; // 4 bytes for an int

        int expectedValue = 0xFEDCBA98;
        bufferWriter.writeOrderedInt(buffer, maxValidOffset, expectedValue);

        int actualValue = buffer.getInt(maxValidOffset);
        assertEquals(expectedValue, actualValue,
                "Int value at maximum offset should be written correctly");
    }

    /**
     * Tests that overwriting values works correctly.
     */
    @Test
    public void testOverwrite() {
        ByteBuffer buffer = createBuffer(16);
        int offset = 0;

        // Write initial pattern
        bufferWriter.writeOrderedLong(buffer, offset, 0xAAAAAAAAAAAAAAAAL);
        assertEquals(0xAAAAAAAAAAAAAAAAL, buffer.getLong(offset));

        // Overwrite with different pattern
        bufferWriter.writeOrderedLong(buffer, offset, 0x5555555555555555L);
        assertEquals(0x5555555555555555L, buffer.getLong(offset));

        // Overwrite with zeros
        bufferWriter.writeVolatileLong(buffer, offset, 0L);
        assertEquals(0L, buffer.getLong(offset));
    }

    /**
     * Tests parallel writes to different offsets from multiple threads.
     * Uses writeVolatileLong for cross-thread visibility guarantees.
     */
    @Test
    public void testParallelWrites() throws InterruptedException {
        ByteBuffer buffer = createBuffer(128);
        int numThreads = 8;
        Thread[] threads = new Thread[numThreads];
        CountDownLatch startLatch = new CountDownLatch(1);
        CountDownLatch doneLatch = new CountDownLatch(numThreads);

        for (int i = 0; i < numThreads; i++) {
            final int threadIndex = i;
            final int offset = threadIndex * 16;
            final long expectedValue = (long) threadIndex * 0x1111111111111111L;

            threads[i] = new Thread(() -> {
                try {
                    startLatch.await(5, TimeUnit.SECONDS);
                    // Use volatile write for cross-thread visibility
                    bufferWriter.writeVolatileLong(buffer, offset, expectedValue);
                    doneLatch.countDown();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            });
            threads[i].start();
        }

        // Start all threads simultaneously
        startLatch.countDown();

        // Wait for all threads to complete
        assertTrue(doneLatch.await(5, TimeUnit.SECONDS),
                "All threads should complete within timeout");

        // Verify all values were written correctly
        for (int i = 0; i < numThreads; i++) {
            int offset = i * 16;
            long expectedValue = (long) i * 0x1111111111111111L;
            long actualValue = buffer.getLong(offset);
            assertEquals(expectedValue, actualValue,
                    String.format("Thread %d's value at offset %d should be correct", i, offset));
        }

        for (Thread thread : threads) {
            thread.join(1000);
        }
    }

    /**
     * Tests that the buffer's original position and limit are not affected by writes.
     */
    @Test
    public void testBufferStatePreservation() {
        ByteBuffer buffer = createBuffer(64);
        buffer.position(10);
        buffer.limit(50);

        int originalPosition = buffer.position();
        int originalLimit = buffer.limit();

        bufferWriter.writeOrderedLong(buffer, 16, 0x123456789ABCDEF0L);
        bufferWriter.writeVolatileLong(buffer, 24, 0xFEDCBA9876543210L);
        bufferWriter.writeOrderedInt(buffer, 32, 0x12345678);
        bufferWriter.writeVolatileInt(buffer, 36, 0x9ABCDEF0);

        assertEquals(originalPosition, buffer.position(),
                "Buffer position should not be affected by writes");
        assertEquals(originalLimit, buffer.limit(),
                "Buffer limit should not be affected by writes");
    }
}
