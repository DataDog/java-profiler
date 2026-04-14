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
         */
        void writeOrderedLong(ByteBuffer buffer, int offset, long value);

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
         * Executes a store-store memory fence.
         *
         * <p>Ensures that stores before the fence are visible before stores after it.
         * Cheaper than fullFence on ARM (~5ns vs ~50ns) since it only orders
         * stores, not loads. Sufficient for publication protocols where the writer
         * needs to ensure data writes are visible before a flag/pointer write.
         */
        void storeFence();
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
     */
    public void writeOrderedLong(ByteBuffer buffer, int offset, long value) {
        impl.writeOrderedLong(buffer, offset, value);
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
     * Executes a store-store memory fence.
     *
     * <p>Ensures stores before the fence are globally visible before stores after it.
     * On ARM this emits DMB ISHST (~2 ns); on x86 it is a compiler-only barrier.
     */
    public void storeFence() {
        impl.storeFence();
    }
}
