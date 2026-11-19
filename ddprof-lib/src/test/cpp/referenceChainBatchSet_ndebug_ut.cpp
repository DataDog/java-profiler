/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Death-checks the marker contract with assertions compiled out for this TU:
// NDEBUG precedes every include so <cassert> defines assert() away and only
// the abort() fallback remains - the guard release builds actually run.
#define NDEBUG
#include <cassert>
#include <gtest/gtest.h>
#include <csignal>
#include <cstdint>
#include "referenceChainBatchSet.h"

TEST(ReferenceChainBatchSetNDebugDeathTest, MarkUnresolvedTagAbortsWithoutAssertions) {
  ReferenceChainBatchSet set;
  set.reset();
  ASSERT_TRUE(set.addResolved(7));
  set.markMember(7);
  EXPECT_EXIT(set.markMember(8), ::testing::KilledBySignal(SIGABRT), "");
  EXPECT_EXIT(set.markCompleted(9), ::testing::KilledBySignal(SIGABRT), "");
  // The deaths above ran in forked children; in this process the set is
  // untouched and a valid call must survive.
  EXPECT_EQ(1u, set.size());
  EXPECT_TRUE(set.isMember(7));
  EXPECT_FALSE(set.isMember(8));
  EXPECT_FALSE(set.isCompleted(9));
}

TEST(ReferenceChainBatchSetNDebugDeathTest, ResetMakesOldMarkerTagsUnresolvedWithoutAssertions) {
  ReferenceChainBatchSet set;
  set.reset();
  ASSERT_TRUE(set.addResolved(100));
  set.markMember(100);
  set.reset();
  EXPECT_EXIT(set.markMember(100), ::testing::KilledBySignal(SIGABRT), "");
  EXPECT_EXIT(set.markCompleted(100), ::testing::KilledBySignal(SIGABRT), "");
}

// Proves NDEBUG is in effect for this TU: with assertions enabled this would
// abort, so survival is what makes the death checks above a test of the
// abort() fallback rather than of the assert.
TEST(ReferenceChainBatchSetNDebugTest, AssertionsAreCompiledOut) {
  ReferenceChainBatchSet set;
  set.reset();
  assert(false);
  EXPECT_EQ(0u, set.size());
}
