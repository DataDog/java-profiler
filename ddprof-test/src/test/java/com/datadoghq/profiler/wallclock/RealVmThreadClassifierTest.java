/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.*;

import com.datadoghq.profiler.Platform;
import java.lang.reflect.Method;
import java.util.concurrent.atomic.AtomicReference;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.condition.EnabledIfEnvironmentVariable;

/** Qualification against the actual JNI table, without fabricating objects or table entries. */
@EnabledIfEnvironmentVariable(named = "DDPROF_EXPECTED_VM", matches = "openj9|hotspot")
public class RealVmThreadClassifierTest extends RealVmProducerTest {
  private static native int jniVersion0();

  private static native boolean isPlatformThread0(Thread thread);

  /** Distinguishes classification from paired admission's separate calling-thread validation. */
  @Test
  public void liveJniNullPlatformAndVirtualClassification() throws Exception {
    int version = jniVersion0();
    assertTrue(version > 0, "The real JNI GetVersion must succeed");
    System.out.println(
        "REAL_JNI version=0x"
            + Integer.toHexString(version)
            + " branch="
            + (version < 0x00130000 ? "pre19" : "JNI-IsVirtualThread"));
    assertFalse(isPlatformThread0(null), "Null is not a platform thread");
    assertTrue(isPlatformThread0(Thread.currentThread()));
    assertTrue(
        isPlatformThread0(new Thread(() -> {}, "classifier-other")),
        "A valid other Thread is not invalid classifier input");

    if (Platform.isJavaVersionAtLeast(21)) {
      assertTrue(version >= 0x00130000, "VT qualification must reach the JNI19+ branch");
      Method startVirtualThread = Thread.class.getMethod("startVirtualThread", Runnable.class);
      AtomicReference<Throwable> failure = new AtomicReference<>();
      Thread virtual =
          (Thread)
              startVirtualThread.invoke(
                  null,
                  (Runnable)
                      () -> {
                        try {
                          assertFalse(
                              isPlatformThread0(Thread.currentThread()),
                              "Actual virtual thread must be rejected by the live JNI classifier");
                          Thread.sleep(20L);
                          assertEquals(
                              version, jniVersion0(), "The real JNI version must survive remount");
                          assertFalse(
                              isPlatformThread0(Thread.currentThread()),
                              "A remounted virtual thread must still be rejected by the live JNI classifier");
                        } catch (Throwable error) {
                          failure.set(error);
                        }
                      });
      virtual.join(5_000L);
      assertFalse(virtual.isAlive(), "Virtual classifier worker leaked");
      if (failure.get() != null) throw new AssertionError(failure.get());
      assertTrue(
          isPlatformThread0(Thread.currentThread()),
          "Virtual-thread rejection must preserve the subsequent platform control");
      assertFalse(
          isPlatformThread0(virtual),
          "A valid other virtual Thread must not be classified as a platform thread");
    }
  }

  @Override
  protected boolean expectsOpenJ9() {
    return "openj9".equals(System.getenv("DDPROF_EXPECTED_VM"));
  }
}
