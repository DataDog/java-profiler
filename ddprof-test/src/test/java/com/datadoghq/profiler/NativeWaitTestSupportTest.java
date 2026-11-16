/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import static org.junit.jupiter.api.Assertions.*;

import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.concurrent.atomic.AtomicBoolean;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

/** Checks same-worker mask restoration independently of profiler admission. */
public class NativeWaitTestSupportTest {
  @BeforeEach
  void requireLinux() {
    Assumptions.assumeTrue(Platform.isLinux());
  }

  @Test
  void restoresMaskAfterNormalAndNestedCallbacks() {
    Thread worker = Thread.currentThread();
    long before = NativeWaitTestSupport.signalMask();
    long profiling = NativeWaitTestSupport.profilingSignalMask();
    assertNotEquals(0, profiling & ~before, "the worker must initially admit profiling signals");
    AtomicBoolean invoked = new AtomicBoolean();
    NativeWaitTestSupport.withProfilingSignalsBlocked(
        () -> {
          assertSame(worker, Thread.currentThread());
          assertEquals(before | profiling, NativeWaitTestSupport.signalMask());
          NativeWaitTestSupport.withProfilingSignalsBlocked(() -> invoked.set(true));
          assertEquals(before | profiling, NativeWaitTestSupport.signalMask());
        });
    assertTrue(invoked.get());
    assertEquals(before, NativeWaitTestSupport.signalMask());
  }

  @Test
  void restoresMaskAndPropagatesCallbackFailure() {
    long before = NativeWaitTestSupport.signalMask();
    AssertionError failure = new AssertionError("callback failure");
    assertSame(
        failure,
        assertThrows(
            AssertionError.class,
            () ->
                NativeWaitTestSupport.withProfilingSignalsBlocked(
                    () -> {
                      throw failure;
                    })));
    assertEquals(before, NativeWaitTestSupport.signalMask());
    assertThrows(
        NullPointerException.class, () -> NativeWaitTestSupport.withProfilingSignalsBlocked(null));
    assertEquals(before, NativeWaitTestSupport.signalMask());
  }

  @Test
  void rejectsInvalidWaitTargetsAndRestoresHandlerAfterFailedSend() throws Exception {
    String before = caughtSignals();
    assertThrows(IllegalStateException.class, () -> NativeWaitTestSupport.interruptWait(0));
    assertThrows(
        IllegalStateException.class, () -> NativeWaitTestSupport.interruptWait(Integer.MAX_VALUE));
    assertEquals(before, caughtSignals(), "failed delivery must restore SIGWINCH ownership");
  }

  private static String caughtSignals() throws Exception {
    for (String line : Files.readAllLines(Paths.get("/proc/self/status"), StandardCharsets.UTF_8)) {
      if (line.startsWith("SigCgt:")) return line;
    }
    throw new AssertionError("missing Linux caught-signal mask");
  }
}
