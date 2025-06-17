package com.datadoghq.profiler;

import sun.misc.Unsafe;
import java.lang.reflect.Field;


class ActiveBitmap {
    private static final Unsafe UNSAFE = JavaProfiler.UNSAFE;

    // Address to size field of ThreadFilter in native
    private static long activeCountAddr;

    private static final ThreadLocal<Long> Address = new ThreadLocal<Long>() {
        @Override protected Long initialValue() {
            return -1L;
        }
    };

    public static void initialize() {
        activeCountAddr = getActiveCountAddr0();
    }

    // On native side, we reverse lower 16 bits of thread id when maps to bitmap bit.
    // So the active bit position of the specific thread id maps to the reverse order
    // of the second lowest byte of thread id.
    static long getBitmask(int tid) {
        int tmp = (tid >> 8) & 0xff ;
        int bits = 0;
        for (int index = 0; index <= 7; index++) {
            if ((tmp & 0x01) == 0x01) {
                bits |= 1 << (7 - index);
            }
            tmp >>>= 1;
        }
        return 1L << (bits & 0x3f);
    }

    static void setActive(int tid, boolean active) {
        long addr = Address.get();
        if (addr == -1) {
            addr = bitmapAddressFor0(tid);
            Address.set(addr);
        }
        long bitmask = getBitmask(tid);
        long value = UNSAFE.getLong(addr);
        long newVal = active ? (value | bitmask) : (value & ~bitmask);

        while (!UNSAFE.compareAndSwapLong(null, addr, value, newVal)) {
            value = UNSAFE.getLong(addr);
            newVal = active ? (value | bitmask) : (value & ~bitmask);
        }
        int delta = active ? 1 : -1;
        assert activeCountAddr != 0;
        UNSAFE.getAndAddInt(null, activeCountAddr, delta);
        if (isActive0(tid) != active) {
            throw new RuntimeException("SetActive Failed");
        }

        assert isActive0(tid) == active;
    }


    // Address of bitmap word that contains the active bit of this thread Id
    private static native long bitmapAddressFor0(int tid);

    private static native long getActiveCountAddr0();

    // For validation
    private static native boolean isActive0(int tid);
}

