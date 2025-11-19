package com.datadoghq.profiler;

import java.nio.ByteBuffer;

/**
 * Version-agnostic wrapper for direct ByteBuffer memory operations with explicit memory ordering guarantees.
 *
 * <p>This class provides low-level memory access operations on direct ByteBuffers with precise control
 * over memory ordering semantics. It abstracts differences between Java 8 (using sun.misc.Unsafe) and
 * Java 9+ (using VarHandle APIs) to provide consistent behavior across JVM versions.
 *
 * <p>The class supports two types of memory ordering:
 * <ul>
 *   <li><b>Ordered writes:</b> Prevents reordering with prior writes but allows subsequent operations
 *       to be reordered before this write. More efficient than volatile writes.</li>
 *   <li><b>Volatile writes:</b> Full memory barrier - prevents reordering with both prior and subsequent
 *       operations. Ensures immediate visibility to all threads.</li>
 * </ul>
 *
 * <p>This is primarily used by the profiler for writing thread-local context data (span IDs, checksums)
 * to direct ByteBuffers that are shared between Java and native code via JNI.
 *
 * <p><b>Thread Safety:</b> This class is thread-safe. Individual write operations provide their own
 * memory ordering guarantees as documented.
 */
public final class BufferWriter {
    /**
     * Service Provider Interface for version-specific buffer write implementations.
     *
     * <p>Implementations of this interface provide the actual low-level memory access operations:
     * <ul>
     *   <li>{@code BufferWriter8} - Java 8 implementation using sun.misc.Unsafe</li>
     *   <li>{@code BufferWriter9} - Java 9+ implementation using VarHandle</li>
     * </ul>
     *
     * <p>The implementation is selected automatically based on the runtime Java version.
     */
    public interface Impl {
        /**
         * Writes a long value to the buffer at the specified offset with ordered write semantics.
         *
         * <p>Ordered write guarantees that this write will not be reordered with respect to prior writes,
         * but subsequent operations may be reordered before this write. This is more efficient than a
         * volatile write when full bidirectional ordering is not required.
         *
         * @param buffer the direct ByteBuffer to write to
         * @param offset the offset in bytes from the buffer's base address
         * @param value the long value to write
         * @return the written value
         */
        long writeLong(ByteBuffer buffer, int offset, long value);

        /**
         * Writes a long value to the buffer at the specified offset with volatile write semantics.
         *
         * <p>Volatile write provides full memory barrier semantics - prevents reordering with both
         * prior and subsequent operations, and ensures the write is immediately visible to all threads.
         * This is equivalent to writing to a volatile field.
         *
         * @param buffer the direct ByteBuffer to write to
         * @param offset the offset in bytes from the buffer's base address
         * @param value the long value to write
         * @return the written value
         */
        long writeVolatileLong(ByteBuffer buffer, int offset, long value);

        /**
         * Writes an int value to the buffer at the specified offset with ordered write semantics.
         *
         * <p>Ordered write guarantees that this write will not be reordered with respect to prior writes,
         * but subsequent operations may be reordered before this write.
         *
         * @param buffer the direct ByteBuffer to write to
         * @param offset the offset in bytes from the buffer's base address
         * @param value the int value to write
         */
        void writeInt(ByteBuffer buffer, int offset, int value);

        /**
         * Writes an int value to the buffer at the specified offset with volatile write semantics.
         *
         * <p>Volatile write provides full memory barrier semantics - prevents reordering with both
         * prior and subsequent operations, and ensures the write is immediately visible to all threads.
         *
         * @param buffer the direct ByteBuffer to write to
         * @param offset the offset in bytes from the buffer's base address
         * @param value the int value to write
         */
        void writeVolatileInt(ByteBuffer buffer, int offset, int value);

        /**
         * Executes a full memory fence (barrier).
         *
         * <p>A full fence prevents reordering of any memory operations across the fence boundary.
         * Operations before the fence will complete before any operations after the fence begin.
         * This is equivalent to calling both a load fence and a store fence.
         */
        void fullFence();
    }

    private final Impl impl;

    /**
     * Creates a new BufferWriter with the appropriate implementation for the current Java version.
     *
     * <p>The implementation is selected based on the runtime Java version:
     * <ul>
     *   <li>Java 8: Uses {@code BufferWriter8} which leverages sun.misc.Unsafe for memory operations</li>
     *   <li>Java 9+: Uses {@code BufferWriter9} which leverages VarHandle for memory operations</li>
     * </ul>
     *
     * <p>The implementation is loaded reflectively to avoid compile-time dependencies on
     * version-specific APIs.
     *
     * @throws RuntimeException if the implementation class cannot be loaded or instantiated
     */
    public BufferWriter() {
        try {
            if (Platform.isJavaVersion(8)) {
                impl = (BufferWriter.Impl) Class.forName("com.datadoghq.profiler.BufferWriter8").getConstructor().newInstance();
            } else {
                impl = (BufferWriter.Impl) Class.forName("com.datadoghq.profiler.BufferWriter9").getConstructor().newInstance();
            }
        } catch (Throwable t) {
            throw new RuntimeException(t);
        }
    }

    /**
     * Writes a long value to the buffer at the specified offset with ordered write semantics.
     *
     * <p>Ordered write guarantees that this write will not be reordered with respect to prior writes,
     * but subsequent operations may be reordered before this write. This is more efficient than a
     * volatile write when full bidirectional ordering is not required.
     *
     * <p>This is commonly used for writing context fields (span IDs) that need to be visible to
     * readers, but where a full memory barrier is not required.
     *
     * @param buffer the direct ByteBuffer to write to
     * @param offset the offset in bytes from the buffer's base address
     * @param value the long value to write
     * @return the written value
     */
    public long writeLong(ByteBuffer buffer, int offset, long value) {
        return impl.writeLong(buffer, offset, value);
    }

    /**
     * Writes a long value to the buffer at the specified offset with volatile write semantics.
     *
     * <p>Volatile write provides full memory barrier semantics - prevents reordering with both
     * prior and subsequent operations, and ensures the write is immediately visible to all threads.
     * This is equivalent to writing to a volatile field.
     *
     * <p>This is typically used for writing checksums or other sentinel values that signal
     * completion of a write sequence and must be fully visible across all threads.
     *
     * @param buffer the direct ByteBuffer to write to
     * @param offset the offset in bytes from the buffer's base address
     * @param value the long value to write
     * @return the written value
     */
    public long writeVolatileLong(ByteBuffer buffer, int offset, long value) {
        return impl.writeVolatileLong(buffer, offset, value);
    }

    /**
     * Writes an int value to the buffer at the specified offset with ordered write semantics.
     *
     * <p>Ordered write guarantees that this write will not be reordered with respect to prior writes,
     * but subsequent operations may be reordered before this write. This is more efficient than a
     * volatile write when full bidirectional ordering is not required.
     *
     * @param buffer the direct ByteBuffer to write to
     * @param offset the offset in bytes from the buffer's base address
     * @param value the int value to write
     */
    public void writeInt(ByteBuffer buffer, int offset, int value) {
        impl.writeInt(buffer, offset, value);
    }
}
