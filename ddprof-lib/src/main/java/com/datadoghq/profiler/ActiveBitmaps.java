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

  private static final ThreadLocal<Long> Address = new ThreadLocal<Long>() {
    @Override protected Long initialValue() {
        return -1L;
    }
  }; 
  
  // Set bitmap to native code
  static native long bitmapAddressFor0(int tid);

  static void setActive(int tid, boolean active) {
     long addr = Address.get();
     if (addr == -1) {
       addr = bitmapAddressFor0(tid);
       Address.set(addr);
     }
     long bitmask = 1L << (tid & 0x3f);
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

     if (isActive(tid) != active) {
       throw new RuntimeException("Blooooom! " + addr);
     }
  }
 
  // Verify
  static native boolean isActive(int tid);
}

