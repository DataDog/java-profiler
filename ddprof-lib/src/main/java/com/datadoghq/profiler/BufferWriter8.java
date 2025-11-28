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

import sun.misc.Unsafe;
import sun.nio.ch.DirectBuffer;

import java.lang.reflect.Field;
import java.nio.ByteBuffer;

public final class BufferWriter8 implements BufferWriter.Impl {
    private static final Unsafe UNSAFE;
    static {
        Unsafe unsafe = null;
        // a safety and testing valve to disable unsafe access
        if (Platform.isJavaVersion(8)) {
            try {
                Field f = Unsafe.class.getDeclaredField("theUnsafe");
                f.setAccessible(true);
                unsafe = (Unsafe) f.get(null);
            } catch (Exception ignore) {
                // On Java 8 will never happen
            }
        }
        UNSAFE = unsafe;
    }

    @Override
    public long writeOrderedLong(ByteBuffer buffer, int offset, long value) {
        UNSAFE.putOrderedLong(null, ((DirectBuffer) buffer).address() + offset, value);
        return UNSAFE.getLong(((DirectBuffer) buffer).address() + offset);
    }

    @Override
    public long writeAndReleaseLong(ByteBuffer buffer, int offset, long value) {
        UNSAFE.putLongVolatile(null, ((DirectBuffer) buffer).address() + offset, value);
        return UNSAFE.getLong(((DirectBuffer) buffer).address() + offset);
    }

    @Override
    public void writeInt(ByteBuffer buffer, int offset, int value) {
        UNSAFE.putOrderedInt(null, ((DirectBuffer) buffer).address() + offset, value);
    }

    @Override
    public void writeAndReleaseInt(ByteBuffer buffer, int offset, int value) {
        UNSAFE.putIntVolatile(null, ((DirectBuffer) buffer).address() + offset, value);
    }

    @Override
    public void fullFence() {
        UNSAFE.fullFence();
    }
}
