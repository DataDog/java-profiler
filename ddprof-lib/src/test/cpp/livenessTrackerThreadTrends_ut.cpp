/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "livenessTracker.h"

#include <gtest/gtest.h>

class LivenessThreadTrendTestAccessor {
public:
    using Scratch = LivenessTracker::KlassCountScratch;

    static void *newScratch() { return new Scratch{}; }
    static void deleteScratch(void *scratch) { delete static_cast<Scratch *>(scratch); }

    static void add(LivenessTracker *tracker, void *scratch, jint tid, u32 age) {
        tracker->insertThreadGen(*static_cast<Scratch *>(scratch), tid, age);
    }

    static void promote(LivenessTracker *tracker, void *scratch) {
        tracker->promoteThreadGenCandidates(*static_cast<Scratch *>(scratch));
    }

    static int threadCount(void *scratch) {
        return static_cast<Scratch *>(scratch)->thread_count;
    }

    static int challengerCount(void *scratch) {
        return static_cast<Scratch *>(scratch)->challenger_count;
    }

    static jint threadTid(void *scratch, int index) {
        return static_cast<Scratch *>(scratch)->threads[index].tid;
    }

    static u32 threadCount(void *scratch, int index) {
        return static_cast<Scratch *>(scratch)->threads[index].count;
    }

    static jint challengerTid(void *scratch, int index) {
        return static_cast<Scratch *>(scratch)->challengers[index].tid;
    }

    static u32 challengerCount(void *scratch, int index) {
        return static_cast<Scratch *>(scratch)->challengers[index].count;
    }
};

namespace {
struct ScratchGuard {
    void *scratch;
    ~ScratchGuard() {
        LivenessThreadTrendTestAccessor::deleteScratch(scratch);
    }
    operator void *() const { return scratch; }
};
} // namespace

TEST(LivenessThreadTrendTest, SingleNewcomerCannotDisplaceQualifiedIncumbent) {
    LivenessTracker *tracker = LivenessTracker::instance();
    ScratchGuard scratch{LivenessThreadTrendTestAccessor::newScratch()};

    for (jint tid = 1; tid <= 16; tid++) {
        u32 count = tid == 1 ? 8 : 12;
        for (u32 i = 0; i < count; i++) {
            LivenessThreadTrendTestAccessor::add(tracker, scratch, tid, 1);
        }
    }
    LivenessThreadTrendTestAccessor::add(tracker, scratch, 99, 1);
    ASSERT_EQ(16, LivenessThreadTrendTestAccessor::threadCount(scratch));
    ASSERT_EQ(1, LivenessThreadTrendTestAccessor::challengerCount(scratch));
    EXPECT_EQ(1, LivenessThreadTrendTestAccessor::threadTid(scratch, 0));
    EXPECT_EQ(8u, LivenessThreadTrendTestAccessor::threadCount(scratch, 0));
    EXPECT_EQ(99, LivenessThreadTrendTestAccessor::challengerTid(scratch, 0));
    EXPECT_EQ(1u, LivenessThreadTrendTestAccessor::challengerCount(scratch, 0));

    LivenessThreadTrendTestAccessor::promote(tracker, scratch);
    EXPECT_EQ(1, LivenessThreadTrendTestAccessor::threadTid(scratch, 0));
    EXPECT_EQ(8u, LivenessThreadTrendTestAccessor::threadCount(scratch, 0));
}

TEST(LivenessThreadTrendTest, ChallengerPoolKeepsFourSamplesBeforePromotion) {
    LivenessTracker *tracker = LivenessTracker::instance();
    ScratchGuard scratch{LivenessThreadTrendTestAccessor::newScratch()};

    for (jint tid = 1; tid <= 16; tid++) {
        for (u32 i = 0; i < 8; i++) {
            LivenessThreadTrendTestAccessor::add(tracker, scratch, tid, 1);
        }
    }
    for (jint tid = 100; tid < 104; tid++) {
        LivenessThreadTrendTestAccessor::add(tracker, scratch, tid, 1);
    }
    LivenessThreadTrendTestAccessor::add(tracker, scratch, 104, 1);
    ASSERT_EQ(4, LivenessThreadTrendTestAccessor::challengerCount(scratch));
    EXPECT_EQ(104, LivenessThreadTrendTestAccessor::challengerTid(scratch, 0));
    for (u32 i = 0; i < 11; i++) {
        LivenessThreadTrendTestAccessor::add(tracker, scratch, 104, 1);
    }
    LivenessThreadTrendTestAccessor::promote(tracker, scratch);
    bool found = false;
    for (int i = 0; i < LivenessThreadTrendTestAccessor::threadCount(scratch);
         i++) {
        found = found ||
                LivenessThreadTrendTestAccessor::threadTid(scratch, i) == 104;
    }
    EXPECT_TRUE(found);
}

TEST(LivenessThreadTrendTest, LargerLateCohortsPromoteFromChallengerPool) {
    LivenessTracker *tracker = LivenessTracker::instance();
    ScratchGuard scratch{LivenessThreadTrendTestAccessor::newScratch()};
    constexpr jint kFirstChallenger = 100;
    constexpr int kChallengers = 4;

    for (jint tid = 1; tid <= 16; tid++) {
        for (u32 i = 0; i < 8; i++) {
            LivenessThreadTrendTestAccessor::add(tracker, scratch, tid, 1);
        }
    }
    for (int i = 0; i < kChallengers; i++) {
        for (u32 n = 0; n < 12; n++) {
            LivenessThreadTrendTestAccessor::add(
                tracker, scratch, kFirstChallenger + i, 1);
        }
    }
    ASSERT_EQ(kChallengers,
              LivenessThreadTrendTestAccessor::challengerCount(scratch));
    LivenessThreadTrendTestAccessor::promote(tracker, scratch);

    bool found[kChallengers] = {};
    for (int i = 0; i < LivenessThreadTrendTestAccessor::threadCount(scratch);
         i++) {
        jint tid = LivenessThreadTrendTestAccessor::threadTid(scratch, i);
        if (tid >= kFirstChallenger && tid < kFirstChallenger + kChallengers) {
            found[tid - kFirstChallenger] = true;
        }
    }
    for (int candidate = 0; candidate < kChallengers; candidate++) {
        EXPECT_TRUE(found[candidate]) << (kFirstChallenger + candidate);
    }
}
