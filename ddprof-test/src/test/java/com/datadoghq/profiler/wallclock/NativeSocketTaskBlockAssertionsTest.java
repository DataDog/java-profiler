/* Copyright 2026, Datadog, Inc. */
package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertThrows;

import org.junit.jupiter.api.Test;

/** Controls the single-selector-wait count window independently of syscall retry timing. */
class NativeSocketTaskBlockAssertionsTest {
  @Test
  void zeroSelectorEventsRequireRecorderRejection() {
    NativeSocketTaskBlockTest.assertSelectorTaskBlockCount(0, 1);
    assertThrows(
        AssertionError.class, () -> NativeSocketTaskBlockTest.assertSelectorTaskBlockCount(0, 0));
  }

  @Test
  void emittedSelectorEventsRetainTheRetryUpperBound() {
    NativeSocketTaskBlockTest.assertSelectorTaskBlockCount(1, 0);
    NativeSocketTaskBlockTest.assertSelectorTaskBlockCount(2, 0);
    assertThrows(
        AssertionError.class, () -> NativeSocketTaskBlockTest.assertSelectorTaskBlockCount(3, 1));
  }
}
