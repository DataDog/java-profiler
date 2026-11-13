/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <csignal>
#include <cstdint>
#include "referenceChainBatchSet.h"

TEST(ReferenceChainBatchSetTest, ResetClearsMembershipAndCompletion) {
  ReferenceChainBatchSet set;
  set.reset();
  ASSERT_TRUE(set.addResolved(11));
  set.markMember(11);
  set.markCompleted(11);
  ASSERT_TRUE(set.anyCompleted());
  set.reset();
  EXPECT_FALSE(set.isMember(11));
  EXPECT_FALSE(set.isResolved(11));
  EXPECT_FALSE(set.isCompleted(11));
  EXPECT_FALSE(set.anyCompleted());
  EXPECT_EQ(0u, set.size());
}

TEST(ReferenceChainBatchSetTest, AddResolvedIsIdempotent) {
  ReferenceChainBatchSet set;
  set.reset();
  ASSERT_TRUE(set.addResolved(7));
  set.markMember(7);
  set.markCompleted(7);
  EXPECT_TRUE(set.addResolved(7));
  EXPECT_EQ(1u, set.size());
  EXPECT_TRUE(set.isMember(7));
  EXPECT_TRUE(set.isCompleted(7));
}

TEST(ReferenceChainBatchSetTest, AddResolvedRejectsOnlyBeyondCapacity) {
  ReferenceChainBatchSet set;
  set.reset();
  for (size_t i = 0; i < ReferenceChainBatchSet::CAPACITY; i++) {
    ASSERT_TRUE(set.addResolved(static_cast<jlong>(i) + 1)) << "tag " << i + 1 << " rejected";
  }
  EXPECT_EQ(ReferenceChainBatchSet::CAPACITY, static_cast<size_t>(set.size()));
  EXPECT_FALSE(set.addResolved(static_cast<jlong>(ReferenceChainBatchSet::CAPACITY) + 1));
  for (size_t i = 0; i < ReferenceChainBatchSet::CAPACITY; i++) {
    jlong tag = static_cast<jlong>(i) + 1;
    EXPECT_TRUE(set.isResolved(tag));
    EXPECT_TRUE(set.addResolved(tag));
  }
  EXPECT_EQ(ReferenceChainBatchSet::CAPACITY, static_cast<size_t>(set.size()));
}

TEST(ReferenceChainBatchSetTest, MemberFlagIsIndependentOfResolved) {
  ReferenceChainBatchSet set;
  set.reset();
  set.addResolved(5);
  EXPECT_TRUE(set.isResolved(5));
  EXPECT_FALSE(set.isMember(5));
  set.markMember(5);
  EXPECT_TRUE(set.isMember(5));
  EXPECT_TRUE(set.isResolved(5));
  set.markCompleted(5);
  EXPECT_TRUE(set.isCompleted(5));
  EXPECT_FALSE(set.isMember(6));
  EXPECT_FALSE(set.isResolved(6));
  EXPECT_FALSE(set.isCompleted(6));
}

TEST(ReferenceChainBatchSetTest, CompletionIsPerTagAndAnyCompletedTracksIt) {
  ReferenceChainBatchSet set;
  set.reset();
  set.addResolved(1);
  set.addResolved(2);
  EXPECT_FALSE(set.anyCompleted());
  set.markCompleted(1);
  set.markCompleted(1);
  EXPECT_TRUE(set.anyCompleted());
  EXPECT_TRUE(set.isCompleted(1));
  EXPECT_FALSE(set.isCompleted(2));
  set.markCompleted(2);
  EXPECT_TRUE(set.isCompleted(2));
  set.reset();
  EXPECT_FALSE(set.anyCompleted());
}

// An unresolved tag is a caller-contract violation: both markers assert (debug)
// or abort (release) instead of corrupting the set. Pinned via SIGABRT, which
// both paths raise; any other exit fails the check.
TEST(ReferenceChainBatchSetDeathTest, MarkUnresolvedTagAborts) {
  ReferenceChainBatchSet set;
  set.reset();
  set.addResolved(7);
  set.markMember(7);
  EXPECT_EXIT(set.markMember(8), ::testing::KilledBySignal(SIGABRT), "");
  EXPECT_EXIT(set.markCompleted(9), ::testing::KilledBySignal(SIGABRT), "");
  // The deaths above ran in forked children; in this process the set is
  // untouched and a valid call must survive.
  EXPECT_EQ(1u, set.size());
  EXPECT_FALSE(set.isMember(8));
  EXPECT_FALSE(set.isCompleted(9));
  set.markCompleted(7);
  EXPECT_TRUE(set.isCompleted(7));
  EXPECT_TRUE(set.anyCompleted());
}

// Fills the set to CAPACITY with `tags`, then asserts every key is found and
// 10,000 absent keys are not. `absent` yields absent probe i in 0..9999.
static void fillAndProbeFullTable(const jlong *tags, jlong (*absent)(size_t)) {
  ReferenceChainBatchSet set;
  set.reset();
  for (size_t i = 0; i < ReferenceChainBatchSet::CAPACITY; i++) {
    EXPECT_TRUE(set.addResolved(tags[i])) << "tag " << tags[i] << " rejected";
  }
  EXPECT_EQ(ReferenceChainBatchSet::CAPACITY, static_cast<size_t>(set.size()));
  for (size_t i = 0; i < ReferenceChainBatchSet::CAPACITY; i++) {
    EXPECT_TRUE(set.isResolved(tags[i])) << "tag " << tags[i] << " not found";
  }
  for (size_t i = 0; i < 10000; i++) {
    jlong probe = absent(i);
    EXPECT_FALSE(set.isResolved(probe)) << "absent tag " << probe << " found";
  }
}

static jlong absentSequential(size_t i) { return static_cast<jlong>(i) + 600; }
static jlong absentSparse(size_t i) { return (static_cast<jlong>(i) << 20) + 1; }
static jlong absentNearMax(size_t i) { return INT64_MAX - 1024 - static_cast<jlong>(i); }

// Sequential, strided (1 MiB apart, starting at key 0) and near-INT64_MAX
// tag patterns stress the hash spread and the wrap-around probe path.
TEST(ReferenceChainBatchSetTest, FullTableFindsEveryKeyAndRejectsAbsentOnes) {
  jlong tags[ReferenceChainBatchSet::CAPACITY];
  for (size_t i = 0; i < ReferenceChainBatchSet::CAPACITY; i++) {
    tags[i] = static_cast<jlong>(i) + 1;
  }
  fillAndProbeFullTable(tags, absentSequential);
  for (size_t i = 0; i < ReferenceChainBatchSet::CAPACITY; i++) {
    tags[i] = static_cast<jlong>(i) << 20;
  }
  fillAndProbeFullTable(tags, absentSparse);
  for (size_t i = 0; i < ReferenceChainBatchSet::CAPACITY; i++) {
    tags[i] = INT64_MAX - static_cast<jlong>(i);
  }
  fillAndProbeFullTable(tags, absentNearMax);
}

TEST(ReferenceChainBatchSetTest, ReuseAfterResetForgetsOldKeys) {
  ReferenceChainBatchSet set;
  set.reset();
  set.addResolved(100);
  set.markMember(100);
  set.markCompleted(100);
  set.reset();
  set.addResolved(200);
  EXPECT_TRUE(set.isResolved(200));
  EXPECT_FALSE(set.isResolved(100));
  EXPECT_FALSE(set.isMember(100));
  EXPECT_FALSE(set.isCompleted(100));
  EXPECT_FALSE(set.anyCompleted());
  EXPECT_EQ(1u, set.size());
}
