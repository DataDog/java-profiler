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

// If a block/park run's matching exit is missed (e.g. an exception path with
// no finally/blockExit0), the slot stays "owned" forever and
// shouldSuppressOwnedBlock() keeps skipping the thread in every later
// context window. ThreadFilter::add() must clear a stuck active block run on
// every context-window entry, but must NOT reset the unrelated
// unowned-blocked sampling weight, which is meant to survive across
// context-window entries/exits to keep its amortized sampling ratio
// meaningful.
TEST_F(WallClockBlockTrackerTest, ContextEntryClearsStuckActiveBlockRunButPreservesUnownedWeight) {
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

    // Accumulate unowned-blocked fallback weight/state, independent of the
    // owned block run above -- this must survive the context re-entry below.
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
    EXPECT_TRUE(block_slot->flushUnownedBlockedTail(call_trace_id, weight, state));
    EXPECT_EQ(0xABCDULL, call_trace_id);
    EXPECT_EQ(2ULL, weight);
    EXPECT_EQ(OSThreadState::CONDVAR_WAIT, state);
}

TEST_F(WallClockBlockTrackerTest, ContextEntryWithoutActiveBlockRunIsANoop) {
    constexpr int tid = 7002;
    int slot_id = filter->registerThread(tid);
    ASSERT_GE(slot_id, 0);

    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());

    EXPECT_TRUE(filter->add(tid, slot_id));

    EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
    EXPECT_FALSE(block_slot->sampledThisRun());
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
