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
    int slot_id = filter->registerThread();
    ASSERT_GE(slot_id, 0);

    u64 first_token = tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0ULL, first_token);
    EXPECT_EQ(0ULL, tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::CONDVAR_WAIT));

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    EXPECT_EQ(OSThreadState::SLEEPING, block_slot->activeBlockState());

    EXPECT_FALSE(tracker->exitBlockedRun(slot_id, ThreadFilter::tokenGeneration(first_token) + 1));
    EXPECT_EQ(OSThreadState::SLEEPING, block_slot->activeBlockState());

    EXPECT_TRUE(tracker->exitBlockedRun(slot_id, ThreadFilter::tokenGeneration(first_token)));
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
}

TEST_F(WallClockBlockTrackerTest, NewGenerationRejectsStaleToken) {
    int slot_id = filter->registerThread();
    ASSERT_GE(slot_id, 0);

    u64 stale_token = tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0ULL, stale_token);
    EXPECT_TRUE(tracker->exitBlockedRun(slot_id, ThreadFilter::tokenGeneration(stale_token)));

    u64 current_token = tracker->enterBlockedRun(filter.get(), slot_id, OSThreadState::CONDVAR_WAIT);
    ASSERT_NE(0ULL, current_token);
    EXPECT_NE(ThreadFilter::tokenGeneration(stale_token),
              ThreadFilter::tokenGeneration(current_token));

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    EXPECT_FALSE(tracker->exitBlockedRun(slot_id, ThreadFilter::tokenGeneration(stale_token)));
    EXPECT_EQ(OSThreadState::CONDVAR_WAIT, block_slot->activeBlockState());
    EXPECT_TRUE(tracker->exitBlockedRun(slot_id, ThreadFilter::tokenGeneration(current_token)));
}

// The four tests below verify that ThreadFilter's registry-lifecycle reset
// points each clear the wired WallClockBlockTracker's parallel per-slot
// state, since the two classes coordinate via one non-owning pointer
// (ThreadFilter::setBlockTracker()) rather than a shared struct.
//
// refreshSlotForRecording()'s own resetSlot() call is not covered here: its
// reset branch only fires when a slot's published recording epoch differs
// from the registry's current one while the slot's tid mapping survives -
// unreachable through sequential registerThread()/init() calls, since every
// transition into unfiltered tracking mode (the only way the epoch changes)
// goes through resetRegistrationsLocked() first, which already clears the
// tid mapping. It is only reachable via a registration racing a concurrent
// init(), which the existing ConcurrentSameTidRegistrationConvergesOnOneSlot
// stress test in threadFilter_ut.cpp already exercises for the identity side
// of that race.

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

TEST_F(WallClockBlockTrackerTest, InitResetRegistrationsLockedResetsBlockState) {
    ThreadFilter registry;
    registry.init("", true);
    registry.setBlockTracker(tracker.get());

    int slot_id = registry.registerThread(5001);
    ASSERT_GE(slot_id, 0);
    ASSERT_NE(0u, tracker->enterBlockedRun(&registry, slot_id, OSThreadState::SLEEPING));
    tracker->slotForId(slot_id)->markSampledThisRun(OSThreadState::SLEEPING);

    // Re-entering unfiltered tracking mode drives resetRegistrationsLocked(),
    // which must clear every slot's block state via a single resetAll() call.
    registry.init("", true);

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
    EXPECT_FALSE(block_slot->sampledThisRun());
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
