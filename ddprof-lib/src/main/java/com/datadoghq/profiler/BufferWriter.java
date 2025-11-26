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
 *   <li><b>Ordered writes (release semantics):</b> Prevents reordering with prior writes but allows
 *       subsequent operations to be reordered before this write. More efficient than volatile writes.</li>
 *   <li><b>Volatile writes (full barrier):</b> Prevents reordering with both prior and subsequent
 *       operations. Ensures writes are completed before subsequent operations begin.</li>
 * </ul>
 *
 * <p><b>Signal Handler Safety:</b> The primary use case is protecting write sequences from being
 * observed in inconsistent states by async signal handlers (e.g., SIGPROF). When a signal interrupts
 * a write sequence on the same thread, the signal handler must see either the complete write sequence
 * or recognize the write is in-progress. This requires careful memory ordering even though both writer
 * and reader execute on the same thread.
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
         * Writes a long value to the buffer at the specified offset with ordered write semantics
         * (release barrier).
         *
         * <p>Ordered write guarantees that this write will not be reordered with respect to prior writes,
         * but subsequent operations may be reordered before this write. This is more efficient than a
         * volatile write when full bidirectional ordering is not required.
         *
         * <p>Used for writing data fields in a sequence protected by a volatile sentinel value.
         * Ensures that if a signal handler interrupts after this write, prior writes are visible.
         *
         * @param buffer the direct ByteBuffer to write to
         * @param offset the offset in bytes from the buffer's base address
         * @param value the long value to write
         * @return the written value
         */
        long writeOrderedLong(ByteBuffer buffer, int offset, long value);

        /**
         * Writes a long value to the buffer at the specified offset with volatile write semantics
         * (full memory barrier).
         *
         * <p>Volatile write provides full memory barrier semantics - prevents reordering with both
         * prior and subsequent operations. This is equivalent to writing to a volatile field.
         *
         * <p>Used for writing sentinel values (e.g., checksums) that signal completion of a write
         * sequence. Ensures that if a signal handler observes this write, all prior writes in the
         * sequence are also visible.
         *
         * @param buffer the direct ByteBuffer to write to
         * @param offset the offset in bytes from the buffer's base address
         * @param value the long value to write
         * @return the written value
         */
        long writeAndReleaseLong(ByteBuffer buffer, int offset, long value);

        /**
         * Writes an int value to the buffer at the specified offset with ordered write semantics
         * (release barrier).
         *
         * <p>Ordered write guarantees that this write will not be reordered with respect to prior writes,
         * but subsequent operations may be reordered before this write.
         *
         * <p>Used for writing data fields in a sequence protected by a volatile sentinel value.
         * Ensures that if a signal handler interrupts after this write, prior writes are visible.
         *
         * @param buffer the direct ByteBuffer to write to
         * @param offset the offset in bytes from the buffer's base address
         * @param value the int value to write
         */
        void writeInt(ByteBuffer buffer, int offset, int value);

        /**
         * Writes an int value to the buffer at the specified offset with volatile write semantics
         * (full memory barrier).
         *
         * <p>Volatile write provides full memory barrier semantics - prevents reordering with both
         * prior and subsequent operations. This is equivalent to writing to a volatile field.
         *
         * <p>Used for writing sentinel values that signal completion of a write sequence. Ensures
         * that if a signal handler observes this write, all prior writes in the sequence are also
         * visible.
         *
         * @param buffer the direct ByteBuffer to write to
         * @param offset the offset in bytes from the buffer's base address
         * @param value the int value to write
         */
        void writeAndReleaseInt(ByteBuffer buffer, int offset, int value);

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
     * Writes a long value to the buffer at the specified offset with ordered write semantics
     * (release barrier).
     *
     * <p>Ordered write guarantees that this write will not be reordered with respect to prior writes,
     * but subsequent operations may be reordered before this write. This is more efficient than a
     * volatile write when full bidirectional ordering is not required.
     *
     * <p>This is commonly used for writing context fields (span IDs, root span IDs) in a write
     * sequence that is protected by a volatile sentinel value. Ensures that if a signal handler
     * interrupts after this write, all prior writes are visible.
     *
     * @param buffer the direct ByteBuffer to write to
     * @param offset the offset in bytes from the buffer's base address
     * @param value the long value to write
     * @return the written value
     */
    public long writeOrderedLong(ByteBuffer buffer, int offset, long value) {
        return impl.writeOrderedLong(buffer, offset, value);
    }

    /**
     * Writes a long value to the buffer at the specified offset with volatile write semantics
     * (full memory barrier).
     *
     * <p>Volatile write provides full memory barrier semantics - prevents reordering with both
     * prior and subsequent operations. This is equivalent to writing to a volatile field.
     *
     * <p>This is typically used for writing checksums or other sentinel values that signal
     * completion of a write sequence. Ensures that if a signal handler observes this write,
     * all prior writes in the sequence are also visible.
     *
     * @param buffer the direct ByteBuffer to write to
     * @param offset the offset in bytes from the buffer's base address
     * @param value the long value to write
     * @return the written value
     */
    public long writeVolatileLong(ByteBuffer buffer, int offset, long value) {
        return impl.writeAndReleaseLong(buffer, offset, value);
    }

    /**
     * Writes an int value to the buffer at the specified offset with ordered write semantics
     * (release barrier).
     *
     * <p>Ordered write guarantees that this write will not be reordered with respect to prior writes,
     * but subsequent operations may be reordered before this write. This is more efficient than a
     * volatile write when full bidirectional ordering is not required.
     *
     * <p>Used for writing data fields in a sequence protected by a volatile sentinel value.
     * Ensures that if a signal handler interrupts after this write, prior writes are visible.
     *
     * @param buffer the direct ByteBuffer to write to
     * @param offset the offset in bytes from the buffer's base address
     * @param value the int value to write
     */
    public void writeOrderedInt(ByteBuffer buffer, int offset, int value) {
        impl.writeInt(buffer, offset, value);
    }

    /**
     * Writes an int value to the buffer at the specified offset with volatile write semantics
     * (full memory barrier).
     *
     * <p>Volatile write provides full memory barrier semantics - prevents reordering with both
     * prior and subsequent operations. This is equivalent to writing to a volatile field.
     *
     * <p>This is typically used for writing sentinel values that signal completion of a write
     * sequence. Ensures that if a signal handler observes this write, all prior writes in the
     * sequence are also visible.
     *
     * @param buffer the direct ByteBuffer to write to
     * @param offset the offset in bytes from the buffer's base address
     * @param value the int value to write
     */
    public void writeVolatileInt(ByteBuffer buffer, int offset, int value) {
        impl.writeAndReleaseInt(buffer, offset, value);
    }
}
