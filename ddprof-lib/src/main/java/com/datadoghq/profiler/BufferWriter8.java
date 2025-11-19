package com.datadoghq.profiler;

import sun.nio.ch.DirectBuffer;

import java.nio.ByteBuffer;

public final class BufferWriter8 implements BufferWriter.Impl {
    @Override
    public long writeLong(ByteBuffer buffer, int offset, long value) {
        JavaProfiler.UNSAFE.putOrderedLong(null, ((DirectBuffer) buffer).address() + offset, value);
        return JavaProfiler.UNSAFE.getLong(((DirectBuffer) buffer).address() + offset);
    }

    @Override
    public long writeVolatileLong(ByteBuffer buffer, int offset, long value) {
        JavaProfiler.UNSAFE.putLongVolatile(null, ((DirectBuffer) buffer).address() + offset, value);
        return JavaProfiler.UNSAFE.getLong(((DirectBuffer) buffer).address() + offset);
    }

    @Override
    public void writeInt(ByteBuffer buffer, int offset, int value) {
        JavaProfiler.UNSAFE.putOrderedInt(null, ((DirectBuffer) buffer).address() + offset, value);
    }

    @Override
    public void writeVolatileInt(ByteBuffer buffer, int offset, int value) {
        JavaProfiler.UNSAFE.putIntVolatile(null, ((DirectBuffer) buffer).address() + offset, value);
    }

    @Override
    public void fullFence() {
        JavaProfiler.UNSAFE.fullFence();
    }
}
