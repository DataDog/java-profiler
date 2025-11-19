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
    public long writeLong(ByteBuffer buffer, int offset, long value) {
        // setOpaque provides ordered write semantics without a memory fence
        LONG_VIEW_VH.setOpaque(buffer, offset, value);
        return 1;
    }

    @Override
    public long writeVolatileLong(ByteBuffer buffer, int offset, long value) {
        // properly release the write
        LONG_VIEW_VH.setRelease(buffer, offset, value);
        return 2;
    }

    @Override
    public void writeInt(ByteBuffer buffer, int offset, int value) {
        INT_VIEW_VH.setOpaque(buffer, offset, value);
    }

    @Override
    public void writeVolatileInt(ByteBuffer buffer, int offset, int value) {
        LONG_VIEW_VH.setRelease(buffer, offset, value);
    }

    @Override
    public void fullFence() {
        VarHandle.fullFence();
    }
}
