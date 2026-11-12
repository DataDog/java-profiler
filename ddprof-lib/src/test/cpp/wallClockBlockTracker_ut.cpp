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
#include "../../main/cpp/gtest_crash_handler.h"
#include <memory>

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
    tracker->slotForId(slot_id)->markSampledThisRun(OSThreadState::SLEEPING);

    filter->unregisterThread(slot_id);
    int reused_id = filter->registerThread(1002);
    ASSERT_EQ(slot_id, reused_id);

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(reused_id);
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
    EXPECT_FALSE(block_slot->sampledThisRun());
    EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());
}

TEST_F(WallClockBlockTrackerTest, RegisterThreadNewSlotStartsWithClearBlockState) {
    int slot_id = filter->registerThread(2001);
    ASSERT_GE(slot_id, 0);
    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
    EXPECT_FALSE(block_slot->sampledThisRun());
    EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());
}

TEST_F(WallClockBlockTrackerTest, UnregisterThreadResetsBlockState) {
    int slot_id = filter->registerThread(4001);
    ASSERT_GE(slot_id, 0);
    ASSERT_NE(0ULL, tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING));
    tracker->slotForId(slot_id)->markSampledThisRun(OSThreadState::SLEEPING);

    filter->unregisterThread(slot_id);

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
    EXPECT_FALSE(block_slot->sampledThisRun());
    EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());
}

TEST_F(WallClockBlockTrackerTest, NewRecordingRefreshesBlockStateLazily) {
    ThreadFilter registry;
    registry.init("", true);
    registry.setBlockTracker(tracker.get());

    int slot_id = registry.registerThread(5001);
    ASSERT_GE(slot_id, 0);
    ASSERT_NE(0u, tracker->enterBlockedRun(&registry, slot_id, OSThreadState::SLEEPING));
    tracker->slotForId(slot_id)->markSampledThisRun(OSThreadState::SLEEPING);

    ThreadFilter::Slot* identity = registry.slotForId(slot_id);
    ThreadEntry stale{5001, identity, slot_id, identity->lifecycleGeneration(),
                      identity->recordingEpoch()};
    ASSERT_TRUE(tracker->shouldSuppressOwnedBlock(&registry, stale));

    // Epoch invalidation makes retained payload ineligible before its owner
    // refreshes. No other thread resets an owner's live block state on restart.
    registry.init("", true);
    EXPECT_FALSE(tracker->shouldSuppressOwnedBlock(&registry, stale));
    EXPECT_EQ(identity, registry.lookupByTid(5001));
    EXPECT_EQ(nullptr, registry.activeSlotForId(slot_id, 5001));

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    EXPECT_EQ(OSThreadState::SLEEPING, block_slot->activeBlockState());
    EXPECT_TRUE(block_slot->sampledThisRun());

    ASSERT_EQ(slot_id, registry.registerThread(5001));
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
    EXPECT_FALSE(block_slot->sampledThisRun());
    EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());
}

TEST_F(WallClockBlockTrackerTest, ClearActiveResetsBlockState) {
    int slot_id = filter->registerThread(6001);
    ASSERT_GE(slot_id, 0);
    filter->add(6001, slot_id);
    ASSERT_NE(0ULL, tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING));
    tracker->slotForId(slot_id)->markSampledThisRun(OSThreadState::SLEEPING);

    filter->clearActive();

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
    EXPECT_FALSE(block_slot->sampledThisRun());
}

// Context transitions discard deferred stacks because their original attributes
// are not retained. They also clear owned runs whose exit hook was missed.
TEST_F(WallClockBlockTrackerTest, ContextEntryClearsStuckRunAndUnownedTail) {
    constexpr int tid = 7001;
    int slot_id = filter->registerThread(tid);
    ASSERT_GE(slot_id, 0);

    // Simulate blockEnter0 opening a run whose matching blockExit0 never
    // arrives.
    u64 token = tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0ULL, token);

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    block_slot->markSampledThisRun(OSThreadState::SLEEPING);
    ASSERT_TRUE(block_slot->sampledThisRun());

    // A deferred tail must not acquire the next context's attributes.
    EXPECT_TRUE(block_slot->shouldRecordUnownedBlockedSample());
    block_slot->recordUnownedBlockedSample(0xABCDULL, OSThreadState::CONDVAR_WAIT);
    EXPECT_FALSE(block_slot->shouldRecordUnownedBlockedSample());
    EXPECT_FALSE(block_slot->shouldRecordUnownedBlockedSample());

    // The thread re-enters the context window (filterThreadAdd0 -> add())
    // while the stale block run is still "owned".
    EXPECT_TRUE(filter->add(tid, slot_id));

    EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
    EXPECT_FALSE(block_slot->sampledThisRun());
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->lastSampledState());

    u64 call_trace_id = 0, weight = 0;
    OSThreadState state = OSThreadState::UNKNOWN;
    EXPECT_FALSE(block_slot->flushUnownedBlockedTail(call_trace_id, weight, state));
    EXPECT_EQ(0u, call_trace_id);
    EXPECT_EQ(0u, weight);
    EXPECT_EQ(OSThreadState::UNKNOWN, state);
}

TEST_F(WallClockBlockTrackerTest, ContextEntryWithoutOwnedRunResetsUnownedTail) {
    constexpr int tid = 7002;
    int slot_id = filter->registerThread(tid);
    ASSERT_GE(slot_id, 0);

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    u64 token = tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0u, token);
    ASSERT_TRUE(tracker->exitBlockedRun(slot_id, WallClockBlockTracker::tokenGeneration(token)));
    ASSERT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());
    ASSERT_EQ(OSThreadState::RUNNABLE, block_slot->lastSampledState());
    EXPECT_TRUE(block_slot->shouldRecordUnownedBlockedSample());
    block_slot->recordUnownedBlockedSample(123, OSThreadState::SLEEPING);
    EXPECT_FALSE(block_slot->shouldRecordUnownedBlockedSample());

    EXPECT_TRUE(filter->add(tid, slot_id));

    EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
    EXPECT_FALSE(block_slot->sampledThisRun());
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->lastSampledState());
    u64 trace = 0, weight = 0;
    OSThreadState state = OSThreadState::UNKNOWN;
    EXPECT_FALSE(block_slot->flushUnownedBlockedTail(trace, weight, state));
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

TEST_F(WallClockBlockTrackerTest, ContextExitResetsUnownedTail) {
    int slot_id = filter->registerThread(7003);
    ASSERT_TRUE(filter->add(7003, slot_id));
    auto* block = tracker->slotForId(slot_id);
    ASSERT_TRUE(block->shouldRecordUnownedBlockedSample());
    block->recordUnownedBlockedSample(456, OSThreadState::SLEEPING);
    ASSERT_FALSE(block->shouldRecordUnownedBlockedSample());
    filter->remove(slot_id);
    u64 trace = 0, weight = 0;
    OSThreadState state = OSThreadState::UNKNOWN;
    EXPECT_FALSE(block->flushUnownedBlockedTail(trace, weight, state));
}

TEST_F(WallClockBlockTrackerTest, SameIdentityExitAndReentryInvalidatesFinalValidation) {
    int slot_id = filter->registerThread(8001);
    u64 token = tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0u, token);
    auto* block = tracker->slotForId(slot_id);
    block->markSampledThisRun(OSThreadState::SLEEPING);
    auto* identity = filter->slotForId(slot_id);
    ThreadEntry entry{8001, identity, slot_id, identity->lifecycleGeneration(),
                      identity->recordingEpoch()};
    ASSERT_TRUE(tracker->shouldSuppressOwnedBlock(filter.get(), entry));
    struct Reentry {
        ThreadFilter* registry;
        WallClockBlockTracker* tracker;
        int slot_id;
        u64 token;
        static void replace(void* arg) {
            auto* self = static_cast<Reentry*>(arg);
            EXPECT_TRUE(self->tracker->exitBlockedRun(
                self->slot_id, WallClockBlockTracker::tokenGeneration(self->token)));
            self->token = self->tracker->enterBlockedRun(
                self->registry, self->slot_id, OSThreadState::SLEEPING);
            self->tracker->slotForId(self->slot_id)->markSampledThisRun(OSThreadState::SLEEPING);
        }
    } reentry{filter.get(), tracker.get(), slot_id, token};
    tracker->setSuppressionSnapshotHookForTest(Reentry::replace, &reentry);
    EXPECT_FALSE(tracker->shouldSuppressOwnedBlock(filter.get(), entry));
    tracker->setSuppressionSnapshotHookForTest(nullptr, nullptr);
    EXPECT_NE(token, reentry.token);
    EXPECT_EQ(identity->lifecycleGeneration(), entry.lifecycle_generation);
    EXPECT_TRUE(tracker->shouldSuppressOwnedBlock(filter.get(), entry));
}
