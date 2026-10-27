/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstring>

#include "mallocArenaRule.h"

static const long long GiB = 1024LL * 1024 * 1024;
static const long long INT64_MAX_HEAP = 0x7fffffffffffffffLL;

// Baseline: 2 CPU quota (limit 16 arenas), 40 arenas, 4 GiB limit, 1 GiB heap
// (headroom 3 GiB), 25% threshold, 1 GiB free held (> 768 MiB).
static MallocArenaRuleInput base() {
  MallocArenaRuleInput in;
  in.walkOk = true;
  in.arenaCount = 40;
  in.nonMainArenaBytes = 2ULL * GiB;
  in.hasFreeHeld = true;
  in.freeHeldBytes = 1ULL * GiB;
  in.cpuQuotaMilli = 2000;
  in.memoryLimit = 4 * GiB;
  in.maxHeap = 1 * GiB;
  in.thresholdPercent = 25;
  return in;
}

TEST(MallocArenaRule, RaisesWhenBothConditionsHold) {
  MallocArenaEvaluation ev = evaluateMallocArenaRule(base());
  EXPECT_TRUE(ev.cond1);
  EXPECT_TRUE(ev.cond2);
  EXPECT_TRUE(ev.active);
  EXPECT_EQ(16, ev.recommendedArenaMax);
  EXPECT_EQ((u64)(3 * GiB), ev.nativeHeadroom);
  EXPECT_STREQ("limit-minus-heap", ev.headroomSource);
  EXPECT_FALSE(ev.heapExceedsLimit);
  EXPECT_STREQ("free-held", ev.conditionMeasure);
  EXPECT_EQ((u64)GiB, ev.measureBytes);
}

TEST(MallocArenaRule, NoQuotaNeverWarns) {
  MallocArenaRuleInput in = base();
  in.cpuQuotaMilli = -1;
  MallocArenaEvaluation ev = evaluateMallocArenaRule(in);
  EXPECT_FALSE(ev.cond1);
  EXPECT_FALSE(ev.active);
  EXPECT_EQ(0, ev.recommendedArenaMax);
  in.cpuQuotaMilli = 0;
  EXPECT_FALSE(evaluateMallocArenaRule(in).active);
}

TEST(MallocArenaRule, FractionalQuotaRoundsUp) {
  MallocArenaRuleInput in = base();
  in.cpuQuotaMilli = 1500;
  EXPECT_EQ(16, evaluateMallocArenaRule(in).recommendedArenaMax);
  in.cpuQuotaMilli = 1;
  EXPECT_EQ(8, evaluateMallocArenaRule(in).recommendedArenaMax);
  in.cpuQuotaMilli = 2001;
  EXPECT_EQ(24, evaluateMallocArenaRule(in).recommendedArenaMax);
}

TEST(MallocArenaRule, ArenaCountBoundary) {
  MallocArenaRuleInput in = base();
  in.arenaCount = 16;
  EXPECT_FALSE(evaluateMallocArenaRule(in).cond1);
  in.arenaCount = 17;
  EXPECT_TRUE(evaluateMallocArenaRule(in).cond1);
}

TEST(MallocArenaRule, ThresholdZeroDisablesWarning) {
  MallocArenaRuleInput in = base();
  in.thresholdPercent = 0;
  MallocArenaEvaluation ev = evaluateMallocArenaRule(in);
  EXPECT_TRUE(ev.cond1);
  EXPECT_FALSE(ev.cond2);
  EXPECT_FALSE(ev.active);
}

TEST(MallocArenaRule, ThresholdBoundaryIsStrict) {
  MallocArenaRuleInput in = base();
  in.freeHeldBytes = 3ULL * GiB / 4;  // exactly 25% of the 3 GiB headroom
  EXPECT_FALSE(evaluateMallocArenaRule(in).cond2);
  in.freeHeldBytes += 1;
  EXPECT_TRUE(evaluateMallocArenaRule(in).cond2);
}

TEST(MallocArenaRule, UnknownHeapUsesFullLimit) {
  MallocArenaRuleInput in = base();
  in.maxHeap = -1;
  MallocArenaEvaluation ev = evaluateMallocArenaRule(in);
  EXPECT_EQ((u64)(4 * GiB), ev.nativeHeadroom);
  EXPECT_STREQ("limit-only", ev.headroomSource);
  EXPECT_FALSE(ev.heapExceedsLimit);
  in.maxHeap = 0;
  EXPECT_STREQ("limit-only", evaluateMallocArenaRule(in).headroomSource);
}

TEST(MallocArenaRule, UnboundedHeapUsesFullLimit) {
  MallocArenaRuleInput in = base();
  in.maxHeap = INT64_MAX_HEAP;
  MallocArenaEvaluation ev = evaluateMallocArenaRule(in);
  EXPECT_EQ((u64)(4 * GiB), ev.nativeHeadroom);
  EXPECT_STREQ("limit-only", ev.headroomSource);
  EXPECT_FALSE(ev.heapExceedsLimit);
}

TEST(MallocArenaRule, HeapAtOrAboveLimitUsesFullLimitAndFlags) {
  MallocArenaRuleInput in = base();
  in.maxHeap = 4 * GiB;
  MallocArenaEvaluation ev = evaluateMallocArenaRule(in);
  EXPECT_EQ((u64)(4 * GiB), ev.nativeHeadroom);
  EXPECT_STREQ("limit-only", ev.headroomSource);
  EXPECT_TRUE(ev.heapExceedsLimit);
  in.maxHeap = 8 * GiB;
  ev = evaluateMallocArenaRule(in);
  EXPECT_TRUE(ev.heapExceedsLimit);
  EXPECT_EQ((u64)(4 * GiB), ev.nativeHeadroom);
}

TEST(MallocArenaRule, UnknownMemoryLimitNeverWarns) {
  MallocArenaRuleInput in = base();
  in.memoryLimit = -1;
  MallocArenaEvaluation ev = evaluateMallocArenaRule(in);
  EXPECT_EQ(0u, ev.nativeHeadroom);
  EXPECT_FALSE(ev.cond2);
  EXPECT_FALSE(ev.active);
}

TEST(MallocArenaRule, CommittedFallbackWithoutFreeHeld) {
  MallocArenaRuleInput in = base();
  in.hasFreeHeld = false;
  in.freeHeldBytes = 0;
  in.nonMainArenaBytes = 2ULL * GiB;
  MallocArenaEvaluation ev = evaluateMallocArenaRule(in);
  EXPECT_STREQ("committed", ev.conditionMeasure);
  EXPECT_EQ((u64)(2 * GiB), ev.measureBytes);
  EXPECT_TRUE(ev.active);
  in.nonMainArenaBytes = 512ULL * 1024 * 1024;
  EXPECT_FALSE(evaluateMallocArenaRule(in).active);
}

TEST(MallocArenaRule, FailedWalkIsNotActive) {
  MallocArenaRuleInput in = base();
  in.walkOk = false;
  MallocArenaEvaluation ev = evaluateMallocArenaRule(in);
  EXPECT_TRUE(ev.cond1);
  EXPECT_TRUE(ev.cond2);
  EXPECT_FALSE(ev.active);
}

TEST(MallocArenaRule, NoOverflowWithHugeValues) {
  MallocArenaRuleInput in = base();
  in.memoryLimit = 0x7fffffffffffffffLL;
  in.maxHeap = -1;
  in.freeHeldBytes = 0xffffffffffffffffULL;
  in.thresholdPercent = 100;
  // measure * 100 would wrap in 64 bits; the true product is larger than
  // the headroom times the threshold.
  EXPECT_TRUE(evaluateMallocArenaRule(in).cond2);
  in.freeHeldBytes = 1;
  EXPECT_FALSE(evaluateMallocArenaRule(in).cond2);
}

TEST(MallocArenaRule, HugeQuotaDoesNotOverflowArenaLimit) {
  MallocArenaRuleInput in = base();
  in.cpuQuotaMilli = 0x7fffffffffffffffL;
  MallocArenaEvaluation ev = evaluateMallocArenaRule(in);
  EXPECT_GT(ev.recommendedArenaMax, 0);
  EXPECT_FALSE(ev.cond1);
}

typedef MallocArenaWarningState S;

TEST(MallocArenaWarningState, RaisedOnceThenSilentWhileFlat) {
  S s;
  EXPECT_FALSE(s.active());
  EXPECT_EQ(S::NONE, s.current());
  EXPECT_EQ(S::NONE, s.step(true, false, 0));
  EXPECT_EQ(S::RAISED, s.step(true, true, 1000));
  EXPECT_TRUE(s.active());
  EXPECT_EQ(S::RAISED, s.current());
  EXPECT_EQ(S::NONE, s.step(true, true, 1000));
  EXPECT_EQ(S::NONE, s.step(true, true, 1000));
  EXPECT_EQ(S::RAISED, s.current());
}

TEST(MallocArenaWarningState, WorsenedAtPlus25PercentNotAtPlus24) {
  S s;
  s.step(true, true, 1000);
  EXPECT_EQ(S::NONE, s.step(true, true, 1249));
  EXPECT_EQ(S::RAISED, s.current());
  EXPECT_EQ(S::WORSENED, s.step(true, true, 1250));
  EXPECT_EQ(S::WORSENED, s.current());
  EXPECT_TRUE(s.active());
}

TEST(MallocArenaWarningState, WorsenedIsRelativeToLastEmitted) {
  S s;
  s.step(true, true, 1000);
  EXPECT_EQ(S::WORSENED, s.step(true, true, 1250));
  // 1500 is +50% over the initial value but +20% over the last emitted one.
  EXPECT_EQ(S::NONE, s.step(true, true, 1500));
  EXPECT_EQ(S::WORSENED, s.step(true, true, 1563));
}

TEST(MallocArenaWarningState, ShrinkingMeasureDoesNotWorsenOrLowerBaseline) {
  S s;
  s.step(true, true, 1000);
  EXPECT_EQ(S::NONE, s.step(true, true, 500));
  EXPECT_EQ(S::NONE, s.step(true, true, 1249));
  EXPECT_EQ(S::WORSENED, s.step(true, true, 1250));
}

TEST(MallocArenaWarningState, ClearedThenReRaised) {
  S s;
  s.step(true, true, 1000);
  EXPECT_EQ(S::CLEARED, s.step(true, false, 10));
  EXPECT_FALSE(s.active());
  EXPECT_EQ(S::NONE, s.current());
  EXPECT_EQ(S::NONE, s.step(true, false, 10));
  EXPECT_EQ(S::RAISED, s.step(true, true, 900));
  // The baseline restarts at the re-raise value.
  EXPECT_EQ(S::NONE, s.step(true, true, 1100));
}

TEST(MallocArenaWarningState, ClearedFromWorsened) {
  S s;
  s.step(true, true, 1000);
  s.step(true, true, 2000);
  EXPECT_EQ(S::CLEARED, s.step(true, false, 0));
  EXPECT_EQ(S::NONE, s.current());
}

TEST(MallocArenaWarningState, InvalidWalkKeepsState) {
  S s;
  s.step(true, true, 1000);
  EXPECT_EQ(S::NONE, s.step(false, false, 0));
  EXPECT_EQ(S::NONE, s.step(false, true, 5000));
  EXPECT_TRUE(s.active());
  EXPECT_EQ(S::RAISED, s.current());
  // Baseline is unchanged by invalid steps.
  EXPECT_EQ(S::WORSENED, s.step(true, true, 1250));
  S idle;
  EXPECT_EQ(S::NONE, idle.step(false, true, 5000));
  EXPECT_FALSE(idle.active());
}

TEST(MallocArenaWarningState, NoOverflowOnHugeMeasure) {
  S s;
  s.step(true, true, 0xffffffffffffffffULL / 2);
  EXPECT_EQ(S::WORSENED, s.step(true, true, 0xffffffffffffffffULL));
}

TEST(MallocArenaWarningState, TransitionNames) {
  EXPECT_STREQ("raised", S::name(S::RAISED));
  EXPECT_STREQ("worsened", S::name(S::WORSENED));
  EXPECT_STREQ("cleared", S::name(S::CLEARED));
  EXPECT_STREQ("", S::name(S::NONE));
}
