/*
 * Copyright 2026, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>
#include "nativeMem.h"
#include "threadFilter.h"
#include "wallClockBlockTracker.h"
#include "counters.h"
#include "../../main/cpp/gtest_crash_handler.h"
#include <memory>
#include <set>

// Test name for crash handler
static constexpr char WALLCLOCK_BLOCK_TRACKER_TEST_NAME[] = "WallClockBlockTrackerTest";

class WallClockBlockTrackerTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<WALLCLOCK_BLOCK_TRACKER_TEST_NAME>();
        filter = std::make_unique<ThreadFilter>();
        filter->init("enabled");
        tracker = std::make_unique<WallClockBlockTracker>();
        filter->setBlockTracker(tracker.get());
    }

    void TearDown() override {
        filter.reset();
        tracker.reset();
        restoreDefaultSignalHandlers();
    }

    void markCurrentGenerationSampled(ThreadFilter::SlotID slot_id) {
        WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
        ASSERT_NE(nullptr, block_slot);
        block_slot->markBlockGenerationSampled(block_slot->blockGeneration());
        ASSERT_NE(0ULL, block_slot->sampledBlockGeneration());
    }

    std::unique_ptr<ThreadFilter> filter;
    std::unique_ptr<WallClockBlockTracker> tracker;
};

TEST_F(WallClockBlockTrackerTest, GenerationCheckedExitDoesNotClearAnotherOwner) {
    int slot_id = filter->registerThread(1234);
    ASSERT_GE(slot_id, 0);

    u64 first_token = tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0ULL, first_token);
    EXPECT_EQ(0ULL, tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::CONDVAR_WAIT));

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    EXPECT_EQ(OSThreadState::SLEEPING, block_slot->activeBlockState());

    EXPECT_FALSE(tracker->exitBlockedRun(slot_id, WallClockBlockTracker::tokenGeneration(first_token) + 1));
    EXPECT_EQ(OSThreadState::SLEEPING, block_slot->activeBlockState());

    EXPECT_TRUE(tracker->exitBlockedRun(slot_id, WallClockBlockTracker::tokenGeneration(first_token)));
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
}

TEST_F(WallClockBlockTrackerTest, NewGenerationRejectsStaleToken) {
    int slot_id = filter->registerThread(1234);
    ASSERT_GE(slot_id, 0);

    u64 stale_token = tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0ULL, stale_token);
    EXPECT_TRUE(tracker->exitBlockedRun(slot_id, WallClockBlockTracker::tokenGeneration(stale_token)));

    u64 current_token = tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::CONDVAR_WAIT);
    ASSERT_NE(0ULL, current_token);
    EXPECT_NE(WallClockBlockTracker::tokenGeneration(stale_token),
              WallClockBlockTracker::tokenGeneration(current_token));

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    EXPECT_FALSE(tracker->exitBlockedRun(slot_id, WallClockBlockTracker::tokenGeneration(stale_token)));
    EXPECT_EQ(OSThreadState::CONDVAR_WAIT, block_slot->activeBlockState());
    EXPECT_TRUE(tracker->exitBlockedRun(slot_id, WallClockBlockTracker::tokenGeneration(current_token)));
}

// The four tests below verify that ThreadFilter's registry-lifecycle reset
// points each clear the wired WallClockBlockTracker's parallel per-slot
// state, since the two classes coordinate via one non-owning pointer
// (ThreadFilter::setBlockTracker()) rather than a shared struct.
//
// A recording restart retains identities and invalidates their payload by
// epoch. The retained owner resets its payload through refreshSlotForRecording()
// when it next registers, covered by NewRecordingRefreshesBlockStateLazily.

TEST_F(WallClockBlockTrackerTest, RegisterThreadReuseResetsBlockState) {
    int slot_id = filter->registerThread(1001);
    ASSERT_GE(slot_id, 0);
    ASSERT_NE(0ULL, tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING));
    markCurrentGenerationSampled(slot_id);

    filter->unregisterThread(slot_id);
    int reused_id = filter->registerThread(1002);
    ASSERT_EQ(slot_id, reused_id);

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(reused_id);
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
    EXPECT_EQ(0ULL, block_slot->sampledBlockGeneration());
    EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());
}

TEST_F(WallClockBlockTrackerTest, RegisterThreadNewSlotStartsWithClearBlockState) {
    int slot_id = filter->registerThread(2001);
    ASSERT_GE(slot_id, 0);
    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
    EXPECT_EQ(0ULL, block_slot->sampledBlockGeneration());
    EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());
}

TEST_F(WallClockBlockTrackerTest, UnregisterThreadResetsBlockState) {
    int slot_id = filter->registerThread(4001);
    ASSERT_GE(slot_id, 0);
    ASSERT_NE(0ULL, tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING));
    markCurrentGenerationSampled(slot_id);

    filter->unregisterThread(slot_id);

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
    EXPECT_EQ(0ULL, block_slot->sampledBlockGeneration());
    EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());
}

TEST_F(WallClockBlockTrackerTest, NewRecordingRefreshesBlockStateLazily) {
    ThreadFilter registry;
    registry.init("", true);
    registry.setBlockTracker(tracker.get());

    int slot_id = registry.registerThread(5001);
    ASSERT_GE(slot_id, 0);
    ASSERT_NE(0u, tracker->enterBlockedRun(&registry, slot_id, OSThreadState::SLEEPING));
    markCurrentGenerationSampled(slot_id);

    ThreadFilter::Slot* identity = registry.slotForId(slot_id);
    ThreadEntry stale{5001, identity, slot_id, identity->lifecycleGeneration(),
                      identity->recordingEpoch()};
    ASSERT_TRUE(tracker->isOwnedBlockSuppressionCandidate(&registry, stale));

    // Epoch invalidation makes retained payload ineligible before its owner
    // refreshes. No other thread resets an owner's live block state on restart.
    registry.init("", true);
    EXPECT_FALSE(tracker->isOwnedBlockSuppressionCandidate(&registry, stale));
    EXPECT_EQ(identity, registry.lookupByTid(5001));
    EXPECT_EQ(nullptr, registry.activeSlotForId(slot_id, 5001));

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    EXPECT_EQ(OSThreadState::SLEEPING, block_slot->activeBlockState());
    EXPECT_NE(0ULL, block_slot->sampledBlockGeneration());

    ASSERT_EQ(slot_id, registry.registerThread(5001));
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
    EXPECT_EQ(0ULL, block_slot->sampledBlockGeneration());
    EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());
}

TEST_F(WallClockBlockTrackerTest, ClearActiveResetsBlockState) {
    int slot_id = filter->registerThread(6001);
    ASSERT_GE(slot_id, 0);
    filter->add(6001, slot_id);
    ASSERT_NE(0ULL, tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING));
    markCurrentGenerationSampled(slot_id);

    filter->clearActive();

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
    EXPECT_EQ(0ULL, block_slot->sampledBlockGeneration());
}

TEST_F(WallClockBlockTrackerTest, CollectUnownedBlockedTraceIdsFindsOnlyCachedSlots) {
    int with_trace_id = filter->registerThread(7001);
    int without_trace_id = filter->registerThread(7002);
    ASSERT_GE(with_trace_id, 0);
    ASSERT_GE(without_trace_id, 0);

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(with_trace_id);
    ASSERT_NE(nullptr, block_slot);
    block_slot->recordUnownedBlockedSample(0xABCDULL, OSThreadState::SLEEPING);

    std::set<u64> collected;
    tracker->collectUnownedBlockedTraceIds(
        [&](u64 call_trace_id) { collected.insert(call_trace_id); });

    EXPECT_EQ(collected.size(), 1u);
    EXPECT_TRUE(collected.count(0xABCDULL));
}

TEST_F(WallClockBlockTrackerTest, SaturatedGenerationIsCountedAndRecoversAfterSlotReuse) {
    int slot_id = filter->registerThread(3333);
    ASSERT_GE(slot_id, 0);
    filter->add(3333, slot_id);

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    block_slot->setBlockGenerationForTest(WallClockBlockTracker::kMaxBlockRunGeneration);

#ifdef COUNTERS
    long long saturated_before =
        Counters::getCounter(THREAD_REGISTRY_BLOCK_GENERATION_SATURATED);
#endif
    EXPECT_EQ(0ULL, tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING));
#ifdef COUNTERS
    EXPECT_EQ(saturated_before + 1,
              Counters::getCounter(THREAD_REGISTRY_BLOCK_GENERATION_SATURATED));
#endif

    filter->unregisterThread(slot_id);
    int reused_slot_id = filter->registerThread(3334);
    ASSERT_EQ(slot_id, reused_slot_id)
        << "test relies on the free list handing back the just-freed slot";
    filter->add(3334, reused_slot_id);

    EXPECT_EQ(0ULL, tracker->slotForId(reused_slot_id)->blockGeneration());

    u64 token = tracker->enterBlockedRun(filter.get(), reused_slot_id, OSThreadState::SLEEPING);
    EXPECT_NE(0ULL, token);
    EXPECT_TRUE(tracker->exitBlockedRun(reused_slot_id,
                                        WallClockBlockTracker::tokenGeneration(token)));
}

TEST_F(WallClockBlockTrackerTest, UnregisterWhileBlockRunActiveIsCounted) {
    int slot_id = filter->registerThread(4444);
    ASSERT_GE(slot_id, 0);
    filter->add(4444, slot_id);

    u64 token = tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0ULL, token);

#ifdef COUNTERS
    long long before =
        Counters::getCounter(THREAD_REGISTRY_UNREGISTER_ACTIVE_BLOCK_RUN);
#endif
    filter->unregisterThread(slot_id);
#ifdef COUNTERS
    EXPECT_EQ(before + 1,
              Counters::getCounter(THREAD_REGISTRY_UNREGISTER_ACTIVE_BLOCK_RUN));
#endif
}

TEST_F(WallClockBlockTrackerTest, TokenRoundTripPreservesNegativeJavaLongBitPattern) {
    ThreadFilter::SlotID slot_id = 7;
    u64 generation = 1ULL << 52;
    u64 token = WallClockBlockTracker::encodeBlockRunToken(slot_id, generation);
    int64_t java_token = static_cast<int64_t>(token);

    EXPECT_LT(java_token, 0);
    ThreadFilter::SlotID decoded_slot = -1;
    u64 decoded_generation = 0;
    EXPECT_TRUE(WallClockBlockTracker::decodeBlockRunToken(
        static_cast<u64>(java_token), decoded_slot, decoded_generation));
    EXPECT_EQ(slot_id, decoded_slot);
    EXPECT_EQ(generation, decoded_generation);
}

TEST_F(WallClockBlockTrackerTest, TokenRoundTripCoversSlotAndGenerationBoundaries) {
    ThreadFilter::SlotID decoded_slot = -1;
    u64 decoded_generation = 0;

    u64 first = WallClockBlockTracker::encodeBlockRunToken(0, 1);
    ASSERT_TRUE(WallClockBlockTracker::decodeBlockRunToken(
        first, decoded_slot, decoded_generation));
    EXPECT_EQ(0, decoded_slot);
    EXPECT_EQ(1ULL, decoded_generation);

    u64 last = WallClockBlockTracker::encodeBlockRunToken(
        ThreadFilter::kMaxThreads - 1, WallClockBlockTracker::kMaxBlockRunGeneration);
    EXPECT_EQ(UINT64_MAX, last);
    ASSERT_TRUE(WallClockBlockTracker::decodeBlockRunToken(
        last, decoded_slot, decoded_generation));
    EXPECT_EQ(ThreadFilter::kMaxThreads - 1, decoded_slot);
    EXPECT_EQ(WallClockBlockTracker::kMaxBlockRunGeneration, decoded_generation);

    EXPECT_FALSE(WallClockBlockTracker::decodeBlockRunToken(
        0, decoded_slot, decoded_generation));
    EXPECT_FALSE(WallClockBlockTracker::decodeBlockRunToken(
        static_cast<u64>(ThreadFilter::kMaxThreads - 1),
        decoded_slot, decoded_generation));
}

TEST_F(WallClockBlockTrackerTest, SaturatedGenerationRefusesEntryWithoutClaimingSlot) {
    int slot_id = filter->registerThread(8001);
    ASSERT_GE(slot_id, 0);
    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    block_slot->setBlockGenerationForTest(WallClockBlockTracker::kMaxBlockRunGeneration - 1);

    u64 token = tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0ULL, token);
    EXPECT_EQ(WallClockBlockTracker::kMaxBlockRunGeneration,
              WallClockBlockTracker::tokenGeneration(token));
    ASSERT_TRUE(tracker->exitBlockedRun(
        slot_id, WallClockBlockTracker::tokenGeneration(token)));

    EXPECT_EQ(0ULL, tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING));
    EXPECT_EQ(0ULL, tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING));
    EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
    EXPECT_EQ(WallClockBlockTracker::kMaxBlockRunGeneration, block_slot->blockGeneration());
}

TEST_F(WallClockBlockTrackerTest, SnapshotCapturesOwnedLifecycle) {
    int slot_id = filter->registerThread(8002);
    ASSERT_GE(slot_id, 0);
    ThreadFilter::Slot* identity_slot = filter->slotForId(slot_id);
    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, identity_slot);
    ASSERT_NE(nullptr, block_slot);
    u64 token = tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0ULL, token);

    BlockRunSnapshot snapshot = block_slot->snapshotBlockRun(identity_slot);
    EXPECT_EQ(OSThreadState::SLEEPING, snapshot.active_state);

    ASSERT_TRUE(tracker->snapshotAndExitBlockedRun(
        filter.get(), slot_id, WallClockBlockTracker::tokenGeneration(token), &snapshot));
    EXPECT_EQ(OSThreadState::SLEEPING, snapshot.active_state);
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->snapshotBlockRun(identity_slot).active_state);
}

TEST_F(WallClockBlockTrackerTest, OwnedBlockSuppressesOnlyAfterSuccessfulWallSample) {
    filter->init(nullptr, true);
    int slot_id = filter->registerThread(1234);
    ASSERT_GE(slot_id, 0);
    ThreadFilter::Slot* slot = filter->slotForId(slot_id);
    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, slot);
    u64 token = tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0ULL, token);

    ThreadEntry entry{1234, slot, slot_id, slot->lifecycleGeneration(),
                      slot->recordingEpoch()};
    u64 generation = 0;
    EXPECT_TRUE(tracker->activeOwnedBlockGeneration(filter.get(), entry, generation));
    EXPECT_EQ(WallClockBlockTracker::tokenGeneration(token), generation);
    EXPECT_FALSE(tracker->isOwnedBlockSuppressionCandidate(filter.get(), entry));

    block_slot->markBlockGenerationSampled(generation);
    EXPECT_TRUE(tracker->isOwnedBlockSuppressionCandidate(filter.get(), entry));
    EXPECT_FALSE(tracker->isOwnedBlockSuppressionCandidate(
        filter.get(),
        {1235, slot, slot_id, slot->lifecycleGeneration(), slot->recordingEpoch()}));
    EXPECT_FALSE(tracker->isOwnedBlockSuppressionCandidate(
        filter.get(),
        {1234, slot, slot_id, slot->lifecycleGeneration() + 1, slot->recordingEpoch()}));

    ASSERT_TRUE(tracker->exitBlockedRun(
        slot_id, WallClockBlockTracker::tokenGeneration(token)));
    EXPECT_FALSE(tracker->isOwnedBlockSuppressionCandidate(filter.get(), entry));
}

TEST_F(WallClockBlockTrackerTest, ExitingOwnedBlockReenablesUnownedBlockedFallback) {
    filter->init(nullptr, true);
    int slot_id = filter->registerThread(1234);
    ASSERT_GE(slot_id, 0);
    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    ASSERT_TRUE(block_slot->unownedBlockedFallbackEnabled());

    u64 token = tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0ULL, token);
    EXPECT_FALSE(block_slot->unownedBlockedFallbackEnabled());

    ASSERT_TRUE(tracker->exitBlockedRun(
        slot_id, WallClockBlockTracker::tokenGeneration(token)));
    EXPECT_TRUE(block_slot->unownedBlockedFallbackEnabled());
}

TEST_F(WallClockBlockTrackerTest, StaleSampleCompletionCannotSuppressNewBlockGeneration) {
    filter->init(nullptr, true);
    int slot_id = filter->registerThread(1234);
    ASSERT_GE(slot_id, 0);
    ThreadFilter::Slot* slot = filter->slotForId(slot_id);
    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, slot);

    u64 first_token = tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0ULL, first_token);
    u64 first_generation = WallClockBlockTracker::tokenGeneration(first_token);
    ASSERT_TRUE(tracker->exitBlockedRun(slot_id, first_generation));

    u64 second_token =
        tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::CONDVAR_WAIT);
    ASSERT_NE(0ULL, second_token);
    u64 second_generation = WallClockBlockTracker::tokenGeneration(second_token);
    ASSERT_GT(second_generation, first_generation);

    ThreadEntry entry{1234, slot, slot_id, slot->lifecycleGeneration(),
                      slot->recordingEpoch()};
    block_slot->markBlockGenerationSampled(first_generation);
    EXPECT_FALSE(tracker->isOwnedBlockSuppressionCandidate(filter.get(), entry));

    block_slot->markBlockGenerationSampled(second_generation);
    EXPECT_TRUE(tracker->isOwnedBlockSuppressionCandidate(filter.get(), entry));

    // A delayed completion from the first run must not overwrite the newer mark.
    block_slot->markBlockGenerationSampled(first_generation);
    EXPECT_EQ(second_generation, block_slot->sampledBlockGeneration());
    EXPECT_TRUE(tracker->isOwnedBlockSuppressionCandidate(filter.get(), entry));
}

TEST_F(WallClockBlockTrackerTest, ContextScopeNeverSuppressesOwnedBlock) {
    filter->init("0", false);
    int slot_id = filter->registerThread(1234);
    ASSERT_GE(slot_id, 0);
    filter->add(1234, slot_id);
    ThreadFilter::Slot* slot = filter->slotForId(slot_id);
    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, slot);
    ASSERT_NE(0ULL, tracker->enterBlockedRun(
        filter.get(), slot_id, OSThreadState::CONDVAR_WAIT));

    ThreadEntry entry{1234, slot, slot_id, slot->lifecycleGeneration(),
                      slot->recordingEpoch()};
    block_slot->markBlockGenerationSampled(block_slot->blockGeneration());
    EXPECT_FALSE(tracker->isOwnedBlockSuppressionCandidate(filter.get(), entry));
}

TEST_F(WallClockBlockTrackerTest, ContextEpochDisablesOwnedBlockSuppression) {
    filter->init(nullptr, true);
    int slot_id = filter->registerThread(1234);
    ASSERT_GE(slot_id, 0);
    ThreadFilter::Slot* slot = filter->slotForId(slot_id);
    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, slot);
    ASSERT_NE(0ULL, tracker->enterBlockedRun(
        filter.get(), slot_id, OSThreadState::CONDVAR_WAIT));
    ThreadEntry entry{1234, slot, slot_id, slot->lifecycleGeneration(),
                      slot->recordingEpoch()};
    block_slot->markBlockGenerationSampled(block_slot->blockGeneration());
    ASSERT_TRUE(tracker->isOwnedBlockSuppressionCandidate(filter.get(), entry));

    filter->add(1234, slot_id);
    EXPECT_FALSE(tracker->isOwnedBlockSuppressionCandidate(filter.get(), entry));
    filter->remove(slot_id);
    EXPECT_FALSE(tracker->isOwnedBlockSuppressionCandidate(filter.get(), entry));
}

// If a block/park run's matching exit is missed (e.g. an exception path with
// no finally/blockExit0), the slot stays "owned" forever and the owned-block
// suppression keeps skipping the thread in every later context window.
// ThreadFilter::add() must clear a stuck active block run on every
// context-window entry, and the stale token must not be able to close a
// later run.
TEST_F(WallClockBlockTrackerTest, ContextEntryClearsStuckActiveBlockRun) {
    constexpr int tid = 7001;
    int slot_id = filter->registerThread(tid);
    ASSERT_GE(slot_id, 0);

    // Simulate blockEnter0 opening a run whose matching blockExit0 never
    // arrives.
    u64 token = tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0ULL, token);
    u64 generation = WallClockBlockTracker::tokenGeneration(token);

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    block_slot->markBlockGenerationSampled(generation);
    ASSERT_EQ(generation, block_slot->sampledBlockGeneration());
    ASSERT_FALSE(block_slot->unownedBlockedFallbackEnabled());

    // The thread re-enters the context window (filterThreadAdd0 -> add())
    // while the stale block run is still "owned".
    EXPECT_TRUE(filter->add(tid, slot_id));

    EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
    EXPECT_EQ(0ULL, block_slot->sampledBlockGeneration());
    EXPECT_TRUE(block_slot->unownedBlockedFallbackEnabled());
    EXPECT_EQ(generation, block_slot->blockGeneration());

    // The late exit for the cleared run is rejected, including after a new
    // run has been opened on the same slot.
    EXPECT_FALSE(tracker->exitBlockedRun(slot_id, generation));
    filter->remove(slot_id);
    u64 next_token = tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0ULL, next_token);
    EXPECT_GT(WallClockBlockTracker::tokenGeneration(next_token), generation);
    EXPECT_FALSE(tracker->exitBlockedRun(slot_id, generation));
    EXPECT_NE(BlockRunOwner::NONE, block_slot->activeBlockOwner());
    EXPECT_TRUE(tracker->exitBlockedRun(
        slot_id, WallClockBlockTracker::tokenGeneration(next_token)));
}

// Unlike a JAVA/JVMTI/NATIVE block/park run (see
// ContextEntryClearsStuckActiveBlockRun above), a TASK_BLOCK run is paired
// explicitly by beginTaskBlock0/endTaskBlock0 around caller-controlled code,
// so the owning thread calling add()/remove() mid-run is an expected
// crossing, not a stuck leak. Context entry must leave it intact so the
// eventual exit can tell a crossed run (ineligible, but found) from one that
// never started (not found at all) -- see
// JavaProfilerTaskBlockApiTest#contextWindowAdmissionAndCrossingAreEnforced.
TEST_F(WallClockBlockTrackerTest, ContextEntryPreservesActiveTaskBlockRunForCrossingDetection) {
    constexpr int tid = 7003;
    int slot_id = filter->registerThread(tid);
    ASSERT_GE(slot_id, 0);

    u64 token = tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING,
                                         BlockRunOwner::TASK_BLOCK);
    ASSERT_NE(0ULL, token);
    u64 generation = WallClockBlockTracker::tokenGeneration(token);

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);

    EXPECT_TRUE(filter->add(tid, slot_id));
    EXPECT_EQ(BlockRunOwner::TASK_BLOCK, block_slot->activeBlockOwner())
        << "context entry must not clear an in-flight TASK_BLOCK run";
    EXPECT_EQ(OSThreadState::SLEEPING, block_slot->activeBlockState());
    filter->remove(slot_id);

    BlockRunSnapshot snapshot;
    EXPECT_TRUE(tracker->snapshotAndExitBlockedRun(filter.get(), slot_id, generation,
                                                   &snapshot));
    EXPECT_FALSE(snapshot.context_eligible)
        << "a run that crossed a context-window entry/exit must be reported "
           "ineligible instead of silently discarded";
    EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());
}

// Without an owned run, context entry must not touch the unowned-blocked
// sampling weight, which is meant to survive across context-window
// entries/exits to keep its amortized sampling ratio meaningful.
TEST_F(WallClockBlockTrackerTest, ContextEntryWithoutActiveBlockRunPreservesUnownedWeight) {
    constexpr int tid = 7002;
    int slot_id = filter->registerThread(tid);
    ASSERT_GE(slot_id, 0);

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());

    EXPECT_TRUE(block_slot->shouldRecordUnownedBlockedSample());
    block_slot->recordUnownedBlockedSample(0xABCDULL, OSThreadState::CONDVAR_WAIT);
    EXPECT_FALSE(block_slot->shouldRecordUnownedBlockedSample());
    EXPECT_FALSE(block_slot->shouldRecordUnownedBlockedSample());

    EXPECT_TRUE(filter->add(tid, slot_id));

    EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
    EXPECT_TRUE(block_slot->unownedBlockedFallbackEnabled());

    u64 call_trace_id = 0, weight = 0;
    OSThreadState state = OSThreadState::UNKNOWN;
    EXPECT_TRUE(block_slot->flushUnownedBlockedTail(call_trace_id, weight, state));
    EXPECT_EQ(0xABCDULL, call_trace_id);
    EXPECT_EQ(2ULL, weight);
    EXPECT_EQ(OSThreadState::CONDVAR_WAIT, state);
}

// The ~128 KiB _slots array is an eager, unconditional allocation (unlike
// ThreadFilter's lazily-chunked storage), so every WallClockBlockTracker must
// report it to NativeMem (NM_WALLCLOCK) at construction and retract it at
// destruction.
TEST(WallClockBlockTrackerNativeMemTest, ConstructionAndDestructionAccountForSlotsArray) {
    long long before = NativeMem::live(NM_WALLCLOCK);
    {
        WallClockBlockTracker local_tracker;
        EXPECT_EQ(before + static_cast<long long>(sizeof(WallClockBlockTracker::BlockState)) *
                                ThreadFilter::kMaxThreads,
                  NativeMem::live(NM_WALLCLOCK));
    }
    EXPECT_EQ(before, NativeMem::live(NM_WALLCLOCK));
}
