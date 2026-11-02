/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _MALLOCFOOTPRINTCHECKS_H
#define _MALLOCFOOTPRINTCHECKS_H

#include <gtest/gtest.h>

// Shared with the isolated probe executable so these exact assertions run with
// both a discovered header and an inconclusive (zero) header estimate.
inline void checkOverheadFractions(double small_pct, double large_pct) {
  ASSERT_GE(small_pct, 0);
  ASSERT_GE(large_pct, 0);
  // A zero header estimate still exposes usable-size rounding: a 96-byte
  // request with 104 usable bytes has 8.33% overhead. Compare size classes
  // without requiring double-digit overhead on every small allocation.
  EXPECT_LT(large_pct, 1.0)
      << "a 512 KB chunk must not be charged a double-digit percentage";
  EXPECT_GT(small_pct, large_pct * 10);
}

#endif // _MALLOCFOOTPRINTCHECKS_H
