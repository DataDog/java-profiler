package com.datadoghq.profiler;

import java.util.ArrayList;
import java.util.List;
import java.nio.ByteBuffer;
import java.nio.Buffer;
import java.lang.invoke.VarHandle;

class ActiveBitmaps {
    static final int BITMAP_SIZE = 65536; // 64K
    static final int BITMAP_CAPACITY = BITMAP_SIZE * 8;
    static final List<ByteBuffer> bitmaps = new ArrayList<>();

    public synchronized static void setActive(int tid, boolean active) {
        ByteBuffer bitmap = bitmapFor(tid);
        int index = (tid % BITMAP_CAPACITY) / 8;
        byte val = bitmap.get(index);
        byte mask = (byte)(1 << (tid & 0x07));
        if (active) {
            bitmap.put(index, (byte)(val | mask));
        } else {
            bitmap.put(index, (byte)(val & (~mask)));
        }
	// Volatile store
	VarHandle.fullFence();
    }

    static ByteBuffer bitmapFor(int tid) {
        int index = tid / BITMAP_CAPACITY;
        if (bitmaps.size() <= index) {
            for (int i = bitmaps.size(); i <= index; i++) {
                bitmaps.add(null);
            }
        }
        ByteBuffer bitmap = bitmaps.get(index);
        if (bitmap == null) {
            bitmap = allocateBitmap();
            setBitmap(index, bitmap);
            bitmaps.set(index, allocateBitmap());
        }
        return bitmap;
    }

    static ByteBuffer allocateBitmap() {
        ByteBuffer b = ByteBuffer.allocateDirect(BITMAP_SIZE);
        for (int index = 0; index < BITMAP_SIZE; index++) {
            b.put(index, (byte)0);
        }
        return b;
    }

    // Set bitmap to native code
    static native ByteBuffer newBitmapFor(int index);
}

