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

    static u32 threadAgeCount(void *scratch, int index) {
        return static_cast<Scratch *>(scratch)->threads[index].age_count;
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

    static u32 challengerAgeCount(void *scratch, int index) {
        return static_cast<Scratch *>(scratch)->challengers[index].age_count;
    }

    // Folds one epoch: creates/refreshes klass_id's population record, then runs the production
    // fold (recordTidTrendSamplesLocked) over the caller's scratch under the table lock.
    static void fold(LivenessTracker *tracker, void *scratch, u32 klass_id,
                     u64 epoch) {
        int slot;
        bool created;
        tracker->klassPopulationRecordForTest(klass_id, /*count=*/1, epoch,
                                              &slot, &created);
        foldSlot(tracker, scratch, slot);
    }

    // Folds into an arbitrary slot (no record creation) - the direct seam for the slot-bounds
    // guard test.
    static void foldSlot(LivenessTracker *tracker, void *scratch, int slot) {
        tracker->_table_lock.lock();
        tracker->recordTidTrendSamplesLocked(
            slot, *static_cast<Scratch *>(scratch));
        tracker->_table_lock.unlock();
    }

    static const KlassPopulationEntry::TidTrend *trendFor(
        LivenessTracker *tracker, u32 klass_id, jint tid) {
        for (int i = 0; i < tracker->_klass_population_size; i++) {
            if (tracker->_klass_population[i].klass_id != klass_id) {
                continue;
            }
            const KlassPopulationEntry &entry = tracker->_klass_population[i];
            for (int t = 0; t < entry.tid_trend_count; t++) {
                if (entry.tid_trends[t].tid == tid) {
                    return &entry.tid_trends[t];
                }
            }
            return nullptr;
        }
        return nullptr;
    }

    static int consecutivePositive(LivenessTracker *tracker, u32 klass_id,
                                   jint tid) {
        const auto *trend = trendFor(tracker, klass_id, tid);
        return trend != nullptr ? trend->consecutive_positive : -1;
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
// The per-thread age-capacity guard: a thread sampling more than MAX_AGES_PER_THREAD distinct
// ages keeps its sorted-ages window capped at the maximum while its retained count keeps
// growing. Without the guard, the write past ages[MAX - 1] lands on age_count itself (the next
// member of ThreadGens), corrupting the accumulator.
TEST(LivenessThreadTrendTest, AgeCapacityGuardCapsDistinctAgesWithoutDroppingCount) {
    LivenessTracker *tracker = LivenessTracker::instance();
    ScratchGuard scratch{LivenessThreadTrendTestAccessor::newScratch()};

    for (u32 i = 0; i < 40; i++) {
        LivenessThreadTrendTestAccessor::add(tracker, scratch, 7, i + 1);
    }
    ASSERT_EQ(1, LivenessThreadTrendTestAccessor::threadCount(scratch));
    EXPECT_EQ(7, LivenessThreadTrendTestAccessor::threadTid(scratch, 0))
        << "accumulator header must survive the age window's cap";
    EXPECT_EQ(32u, LivenessThreadTrendTestAccessor::threadAgeCount(scratch, 0))
        << "distinct-age window must cap at MAX_AGES_PER_THREAD";
    EXPECT_EQ(40u, LivenessThreadTrendTestAccessor::threadCount(scratch, 0))
        << "the retained count keeps rising past the age cap";
    // The boundary is >= (not >): with the guard loosened to >, the 41st distinct age would be
    // admitted and written past ages[MAX - 1], corrupting age_count itself.
    LivenessThreadTrendTestAccessor::add(tracker, scratch, 7, 41);
    EXPECT_EQ(32u, LivenessThreadTrendTestAccessor::threadAgeCount(scratch, 0))
        << "the guard must hold at the cap boundary (>=, not >)";
    EXPECT_EQ(7, LivenessThreadTrendTestAccessor::threadTid(scratch, 0));
    EXPECT_EQ(41u, LivenessThreadTrendTestAccessor::threadCount(scratch, 0));
}

// Promotion must require a challenger to OUTRANK the weakest incumbent (strict >): an equal
// count AND equal distinct-age span must not replace an incumbent, or churn replaces incumbents
// that are accumulating just as much evidence.
TEST(LivenessThreadTrendTest, PromotionRequiresStrictlyBetterChallenger) {
    LivenessTracker *tracker = LivenessTracker::instance();
    ScratchGuard scratch{LivenessThreadTrendTestAccessor::newScratch()};

    for (jint tid = 1; tid <= 16; tid++) {
        for (u32 i = 0; i < 5; i++) {
            LivenessThreadTrendTestAccessor::add(tracker, scratch, tid, 1);
        }
    }
    for (u32 i = 0; i < 5; i++) {
        LivenessThreadTrendTestAccessor::add(tracker, scratch, 100, 9);
    }
    ASSERT_EQ(1, LivenessThreadTrendTestAccessor::challengerCount(scratch));
    // Equal count (5) and equal age span (1): the challenger does not outrank the weakest
    // incumbent, so promotion must leave the incumbent table untouched.
    LivenessThreadTrendTestAccessor::promote(tracker, scratch);
    ASSERT_EQ(16, LivenessThreadTrendTestAccessor::threadCount(scratch));
    for (int i = 0; i < 16; i++) {
        EXPECT_NE(100, LivenessThreadTrendTestAccessor::threadTid(scratch, i))
            << "an equal challenger replaced an incumbent (>= comparison)";
    }

    // Promotion cleared the challenger pool, so the challenger re-accumulates from scratch: six
    // samples put it strictly over the weakest incumbent's count of 5, and promotion now
    // replaces the weakest slot.
    for (u32 i = 0; i < 6; i++) {
        LivenessThreadTrendTestAccessor::add(tracker, scratch, 100, 9);
    }
    LivenessThreadTrendTestAccessor::promote(tracker, scratch);
    ASSERT_EQ(16, LivenessThreadTrendTestAccessor::threadCount(scratch));
    bool promoted = false;
    for (int i = 0; i < 16; i++) {
        promoted = promoted ||
                   LivenessThreadTrendTestAccessor::threadTid(scratch, i) == 100;
    }
    EXPECT_TRUE(promoted) << "a strictly better challenger must promote";
}

// The per-tid hysteresis counter resets on the first non-qualifying epoch: a thread over the
// retained-count bar that drops back under it must lose its accumulated consecutive_positive
// (the transient burst is not a sustained trend).
TEST(LivenessThreadTrendTest, ConsecutivePositiveResetsOnNonQualifyingEpoch) {
    LivenessTracker *tracker = LivenessTracker::instance();
    const u32 klass_id = 771;
    ScratchGuard scratch{LivenessThreadTrendTestAccessor::newScratch()};

    // Two qualifying epochs: the tid's surviving count clears the retained-count bar.
    for (u32 i = 0; i < 10; i++) {
        LivenessThreadTrendTestAccessor::add(tracker, scratch, 7, 1);
    }
    LivenessThreadTrendTestAccessor::fold(tracker, scratch, klass_id, 1);
    LivenessThreadTrendTestAccessor::fold(tracker, scratch, klass_id, 2);
    EXPECT_EQ(2, LivenessThreadTrendTestAccessor::consecutivePositive(
                     tracker, klass_id, 7));

    // One non-qualifying epoch (count 1, flat history): the counter resets to 0.
    ScratchGuard fresh{LivenessThreadTrendTestAccessor::newScratch()};
    for (u32 i = 0; i < 1; i++) {
        LivenessThreadTrendTestAccessor::add(tracker, fresh, 7, 1);
    }
    LivenessThreadTrendTestAccessor::fold(tracker, fresh, klass_id, 3);
    EXPECT_EQ(0, LivenessThreadTrendTestAccessor::consecutivePositive(
                     tracker, klass_id, 7))
        << "a non-qualifying epoch must reset the hysteresis counter";
}

// Newcomer churn stays bounded: with the incumbent table full, a burst of more than
// MAX_THREAD_CHALLENGERS_PER_KLASS one-shot newcomers recycles only the challenger pool's
// count-1 slots and never displaces an incumbent (not even a sub-bar one).
TEST(LivenessThreadTrendTest, NewcomerChurnBeyondPoolNeverDisplacesIncumbents) {
    LivenessTracker *tracker = LivenessTracker::instance();
    ScratchGuard scratch{LivenessThreadTrendTestAccessor::newScratch()};

    for (jint tid = 1; tid <= 16; tid++) {
        for (u32 i = 0; i < 5; i++) {
            LivenessThreadTrendTestAccessor::add(tracker, scratch, tid, 1);
        }
    }
    ASSERT_EQ(16, LivenessThreadTrendTestAccessor::threadCount(scratch));

    // More than 4 one-shot newcomers (one sample each) churn through the pool.
    for (jint tid = 100; tid < 110; tid++) {
        LivenessThreadTrendTestAccessor::add(tracker, scratch, tid, 1);
    }
    ASSERT_EQ(16, LivenessThreadTrendTestAccessor::threadCount(scratch));
    for (jint tid = 1; tid <= 16; tid++) {
        bool present = false;
        for (int i = 0; i < 16; i++) {
            present = present ||
                      LivenessThreadTrendTestAccessor::threadTid(scratch, i) == tid;
        }
        EXPECT_TRUE(present) << "incumbent tid " << tid
                             << " displaced by newcomer churn";
    }
    EXPECT_EQ(4, LivenessThreadTrendTestAccessor::challengerCount(scratch));
}

// A full trend table must not hand a slot to a newcomer that is weaker than the weakest victim's
// accumulated evidence: a trend whose consecutive_positive was just reset by one skipped (or
// non-qualifying) epoch still owns its pre-reset retained counts, and a single-sample newcomer
// must not take that slot unconditionally (F-772fa299c1da).
TEST(LivenessThreadTrendTest, TakeoverEarnsAgainstAccumulatedEvidence) {
    LivenessTracker *tracker = LivenessTracker::instance();
    const u32 klass_id = 772;
    ScratchGuard scratch{LivenessThreadTrendTestAccessor::newScratch()};

    // Fill all 8 trend slots with qualifying threads (count 12 clears the bar): two full epochs.
    for (int epoch = 1; epoch <= 2; epoch++) {
        ScratchGuard epoch_scratch{LivenessThreadTrendTestAccessor::newScratch()};
        for (jint tid = 1; tid <= 8; tid++) {
            for (u32 i = 0; i < 12; i++) {
                LivenessThreadTrendTestAccessor::add(tracker, epoch_scratch,
                                                     tid, 1);
            }
        }
        LivenessThreadTrendTestAccessor::fold(tracker, epoch_scratch, klass_id,
                                              epoch);
    }

    // Epoch 3: tid 1 drops to a single retained instance (resets its hysteresis, newest live
    // count 1); tids 2-8 vanish entirely (one trailing zero epoch each, pre-reset count 12).
    ScratchGuard dipped{LivenessThreadTrendTestAccessor::newScratch()};
    for (u32 i = 0; i < 1; i++) {
        LivenessThreadTrendTestAccessor::add(tracker, dipped, 1, 1);
    }
    LivenessThreadTrendTestAccessor::fold(tracker, dipped, klass_id, 3);
    EXPECT_EQ(0, LivenessThreadTrendTestAccessor::consecutivePositive(
                     tracker, klass_id, 1))
        << "setup: tid 1's hysteresis must be reset by the weak epoch";

    // A single-sample newcomer (count 1) is weaker than every victim's evidence: tid 1's newest
    // live count matches it and tids 2-8 still own pre-reset counts of 12 - the newcomer is
    // dropped and every accumulated trend survives.
    ScratchGuard newcomer{LivenessThreadTrendTestAccessor::newScratch()};
    LivenessThreadTrendTestAccessor::add(tracker, newcomer, 99, 1);
    LivenessThreadTrendTestAccessor::fold(tracker, newcomer, klass_id, 4);
    EXPECT_EQ(nullptr,
              LivenessThreadTrendTestAccessor::trendFor(tracker, klass_id, 99))
        << "a weaker newcomer must not take a slot unconditionally";
    for (jint tid = 1; tid <= 8; tid++) {
        EXPECT_NE(nullptr,
                  LivenessThreadTrendTestAccessor::trendFor(tracker, klass_id,
                                                            tid))
            << "accumulated trend for tid " << tid << " must survive";
    }

    // A newcomer that OUTRANKS the weakest victim's evidence earns the slot: count 20 beats
    // tid 1's newest live count of 1.
    ScratchGuard hot{LivenessThreadTrendTestAccessor::newScratch()};
    for (u32 i = 0; i < 20; i++) {
        LivenessThreadTrendTestAccessor::add(tracker, hot, 99, 1);
    }
    LivenessThreadTrendTestAccessor::fold(tracker, hot, klass_id, 5);
    EXPECT_NE(nullptr,
              LivenessThreadTrendTestAccessor::trendFor(tracker, klass_id, 99))
        << "a newcomer hotter than the weakest victim's evidence must take a slot";
    EXPECT_EQ(nullptr,
              LivenessThreadTrendTestAccessor::trendFor(tracker, klass_id, 1))
        << "the weakest victim's trend is the one replaced";
}

// Sustaining trends are never victims: with every slot's consecutive_positive alive, a newcomer
// of any strength is dropped (bounded retry on a later epoch).
TEST(LivenessThreadTrendTest, SustainedTrendsAreNeverTakeoverVictims) {
    LivenessTracker *tracker = LivenessTracker::instance();
    const u32 klass_id = 773;
    ScratchGuard scratch{LivenessThreadTrendTestAccessor::newScratch()};

    for (int epoch = 1; epoch <= 2; epoch++) {
        ScratchGuard epoch_scratch{LivenessThreadTrendTestAccessor::newScratch()};
        for (jint tid = 1; tid <= 8; tid++) {
            for (u32 i = 0; i < 12; i++) {
                LivenessThreadTrendTestAccessor::add(tracker, epoch_scratch,
                                                     tid, 1);
            }
        }
        LivenessThreadTrendTestAccessor::fold(tracker, epoch_scratch, klass_id,
                                              epoch);
    }
    // Epoch 3 keeps every thread present at its qualifying count.
    ScratchGuard epoch_scratch{LivenessThreadTrendTestAccessor::newScratch()};
    for (jint tid = 1; tid <= 8; tid++) {
        for (u32 i = 0; i < 12; i++) {
            LivenessThreadTrendTestAccessor::add(tracker, epoch_scratch, tid, 1);
        }
    }
    LivenessThreadTrendTestAccessor::fold(tracker, epoch_scratch, klass_id, 3);

    ScratchGuard hot{LivenessThreadTrendTestAccessor::newScratch()};
    for (u32 i = 0; i < 40; i++) {
        LivenessThreadTrendTestAccessor::add(tracker, hot, 99, 1);
    }
    LivenessThreadTrendTestAccessor::fold(tracker, hot, klass_id, 4);
    EXPECT_EQ(nullptr,
              LivenessThreadTrendTestAccessor::trendFor(tracker, klass_id, 99))
        << "no sustaining trend may be evicted, whatever the newcomer's strength";
}

// A challenger promotion that replaces an incumbent must not discard the victim's live epoch
// sample: the displaced incumbent's tracked trend records its current-epoch count instead of
// the absent-tid pass writing the still-live thread a zero epoch and resetting qualification.
TEST(LivenessThreadTrendTest, PromotionKeepsDisplacedIncumbentQualification) {
    LivenessTracker *tracker = LivenessTracker::instance();
    const u32 klass_id = 774;
    // Epochs 1-2: 16 incumbents; tids 1-8 (count 9) win the 8 trend slots, all qualifying.
    for (int epoch = 1; epoch <= 2; epoch++) {
        ScratchGuard epoch_scratch{LivenessThreadTrendTestAccessor::newScratch()};
        for (jint tid = 1; tid <= 16; tid++) {
            u32 count = tid <= 8 ? 9 : 12;
            for (u32 i = 0; i < count; i++) {
                LivenessThreadTrendTestAccessor::add(tracker, epoch_scratch,
                                                     tid, 1);
            }
        }
        LivenessThreadTrendTestAccessor::fold(tracker, epoch_scratch, klass_id,
                                              epoch);
    }
    ASSERT_EQ(2, LivenessThreadTrendTestAccessor::consecutivePositive(
                     tracker, klass_id, 1))
        << "setup: tid 1's trend must be qualified before the displacement";

    // Epoch 3: the same cohort plus four stronger challengers; promotion replaces the four
    // weakest incumbents - the trend-holding tids 1-4.
    ScratchGuard epoch3{LivenessThreadTrendTestAccessor::newScratch()};
    for (jint tid = 1; tid <= 16; tid++) {
        u32 count = tid <= 8 ? 9 : 12;
        for (u32 i = 0; i < count; i++) {
            LivenessThreadTrendTestAccessor::add(tracker, epoch3, tid, 1);
        }
    }
    for (jint tid = 100; tid < 104; tid++) {
        for (u32 i = 0; i < 20; i++) {
            LivenessThreadTrendTestAccessor::add(tracker, epoch3, tid, 1);
        }
    }
    LivenessThreadTrendTestAccessor::fold(tracker, epoch3, klass_id, 3);
    for (jint tid = 1; tid <= 4; tid++) {
        EXPECT_EQ(3, LivenessThreadTrendTestAccessor::consecutivePositive(
                         tracker, klass_id, tid))
            << "displaced incumbent " << tid
            << " keeps its qualification through the live sample";
    }
    for (jint tid = 5; tid <= 8; tid++) {
        EXPECT_EQ(3, LivenessThreadTrendTestAccessor::consecutivePositive(
                         tracker, klass_id, tid));
    }
}

// The slot bounds guard on recordTidTrendSamplesLocked(): out-of-range slots must be a no-op
// (removing the guard would index the population table out of bounds).
TEST(LivenessThreadTrendTest, OutOfRangeFoldSlotIsANoOp) {
    LivenessTracker *tracker = LivenessTracker::instance();
    const u32 klass_id = 774;
    ScratchGuard scratch{LivenessThreadTrendTestAccessor::newScratch()};
    LivenessThreadTrendTestAccessor::add(tracker, scratch, 7, 1);
    // Seed one real trend through a VALID slot, then prove out-of-range slots are no-ops.
    ScratchGuard seed{LivenessThreadTrendTestAccessor::newScratch()};
    LivenessThreadTrendTestAccessor::add(tracker, seed, 7, 1);
    int slot = -1;
    {
        bool created;
        tracker->klassPopulationRecordForTest(klass_id, 1, 1, &slot, &created);
    }
    LivenessThreadTrendTestAccessor::foldSlot(tracker, seed, slot);
    ASSERT_NE(nullptr,
              LivenessThreadTrendTestAccessor::trendFor(tracker, klass_id, 7))
        << "setup: the valid fold must create the trend";
    LivenessThreadTrendTestAccessor::foldSlot(tracker, scratch, -1);
    LivenessThreadTrendTestAccessor::foldSlot(tracker, scratch, slot + 1);
    EXPECT_NE(nullptr,
              LivenessThreadTrendTestAccessor::trendFor(tracker, klass_id, 7))
        << "out-of-range folds must not create or corrupt trends";
}
