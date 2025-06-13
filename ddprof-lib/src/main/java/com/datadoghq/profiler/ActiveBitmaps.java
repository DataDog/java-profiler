package com.datadoghq.profiler;

import sun.misc.Unsafe;
import java.lang.reflect.Field;


class ActiveBitmaps {
  private static final Unsafe UNSAFE;
  static {
        Unsafe unsafe = null;
        try {
          Field f = Unsafe.class.getDeclaredField("theUnsafe");
          f.setAccessible(true);
          unsafe = (Unsafe) f.get(null);
        } catch (Exception ignore) { }
        UNSAFE = unsafe;
  }

  private static long activeCountAddr = 0;

  private static final ThreadLocal<Long> Address = new ThreadLocal<Long>() {
    @Override protected Long initialValue() {
        return -1L;
    }
  };

  public static void initialize() {
    activeCountAddr = getActiveCountAddr0(); 
  }

  // Set bitmap to native code
  static native long bitmapAddressFor0(int tid);

  static long getBitmask(int tid) {
    int tmp = (tid >> 8) & 0xff ;
    int bits = 0;
    for (int index = 0; index < 7 ; index++) {
      if ((tmp & 0x01) == 0x01) {
        bits |= 0x01;
      }
      tmp >>= 1;
      bits <<= 1; 
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
     long newVal; 
     if (active) {
       newVal = value | bitmask;  
     } else {
       newVal = value & ~bitmask;
     }
     while (!UNSAFE.compareAndSwapLong(null, addr, value, newVal)) {
       value = UNSAFE.getLong(addr);
       newVal = active ? (value | bitmask) : (value & ~bitmask);
     }
     int delta = active ? 1 : -1;
     assert activeCountAddr != 0;
     UNSAFE.getAndAddInt(null, activeCountAddr, delta);
//     if (isActive(tid) != active) {
//       throw new RuntimeException("SetActive failed");
//     }

     assert isActive(tid) == active;
  }

  // For verification 
  static native boolean isActive(int tid);

  static native long getActiveCountAddr0();
}

