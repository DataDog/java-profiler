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

import java.lang.invoke.MethodHandles;
import java.lang.invoke.VarHandle;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public final class BufferWriter9 implements BufferWriter.Impl {
    private static final VarHandle LONG_VIEW_VH;
    private static final VarHandle INT_VIEW_VH;

    static {
        try {
            // Create a view into ByteBuffer as if it were a long array
            // The VarHandle coordinates are (ByteBuffer, int index) where index is in bytes
            LONG_VIEW_VH = MethodHandles.byteBufferViewVarHandle(
                    long[].class, ByteOrder.nativeOrder());
            INT_VIEW_VH = MethodHandles.byteBufferViewVarHandle(
                    int[].class, ByteOrder.nativeOrder());
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public long writeOrderedLong(ByteBuffer buffer, int offset, long value) {
        // setRelease provides ordered write semantics (matches Unsafe.putOrderedLong)
        LONG_VIEW_VH.setRelease(buffer, offset, value);
        return (long) LONG_VIEW_VH.get(buffer, offset);
    }

    @Override
    public long writeAndReleaseLong(ByteBuffer buffer, int offset, long value) {
        // setVolatile provides full volatile semantics (matches Unsafe.putLongVolatile)
        LONG_VIEW_VH.setVolatile(buffer, offset, value);
        return (long) LONG_VIEW_VH.get(buffer, offset);
    }

    @Override
    public void writeInt(ByteBuffer buffer, int offset, int value) {
        // setRelease provides ordered write semantics (matches Unsafe.putOrderedInt)
        INT_VIEW_VH.setRelease(buffer, offset, value);
    }

    @Override
    public void writeAndReleaseInt(ByteBuffer buffer, int offset, int value) {
        // setVolatile provides full volatile semantics (matches Unsafe.putIntVolatile)
        INT_VIEW_VH.setVolatile(buffer, offset, value);
    }

    @Override
    public void fullFence() {
        VarHandle.fullFence();
    }
}
