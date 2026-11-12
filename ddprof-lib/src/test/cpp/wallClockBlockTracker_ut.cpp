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
#include "callTraceStorage.h"
#include "context_api.h"
#include "livenessTracker.h"
#include "nativeMem.h"
#include "profiler.h"
#include "threadFilter.h"
#include "threadLocalData.h"
#include "wallClockBlockTracker.h"
#include "wallClock.h"
#include "scopedPreservationCopyFailure.h"
#include "../../main/cpp/gtest_crash_handler.h"
#include <memory>
#include <future>
#include <condition_variable>
#include <mutex>
#include <thread>
#include "counters.h"

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

// Re-entry clears missed owned exits without losing an unowned origin's fields.
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

TEST_F(WallClockBlockTrackerTest, ZeroWeightUnownedTailTraceRemainsResolvableAcrossRotation) {
    ProfiledThread* current = ProfiledThread::initCurrentThreadSignalSafe();
    ASSERT_NE(nullptr, current);
    int slot_id = filter->registerThread(current->tid());
    ASSERT_GE(slot_id, 0);
    ASSERT_TRUE(filter->add(current->tid(), slot_id));
    ASSERT_FALSE(filter->unfilteredWallTrackingActive());
    WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    ASSERT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());

    CallTraceStorage storage;
    ASGCT_CallFrame frame{};
    frame.bci = 10;
    frame.method_id = (jmethodID)0x1234;
    ASSERT_TRUE(block_slot->shouldRecordUnownedBlockedSample());
    u64 initial_weight = block_slot->consumeUnownedBlockedWeight();
    ASSERT_EQ(1ULL, initial_weight);
    u64 initial_trace_id = storage.put(1, &frame, false, initial_weight);
    ASSERT_GT(initial_trace_id >> 32, 0ULL);
    tracker->publishUnownedTrace(slot_id, initial_trace_id, OSThreadState::CONDVAR_WAIT);
    storage.registerLivenessChecker(
        [&](CallTraceIdSet& live) { tracker->collectLiveTraceIds(live); },
        [&](const CallTraceIdSet& failed) { tracker->onUnpreservedTraceIds(failed); });

    u64 tail_trace_id = 0, tail_weight = 0;
    OSThreadState tail_state = OSThreadState::UNKNOWN;
    ASSERT_FALSE(block_slot->flushUnownedBlockedTail(tail_trace_id, tail_weight, tail_state));
    ASSERT_EQ(initial_trace_id, tail_trace_id);
    ASSERT_EQ(0ULL, tail_weight);
    ASSERT_EQ(OSThreadState::CONDVAR_WAIT, tail_state);
    ASSERT_EQ(initial_trace_id,
              block_slot->unowned_blocked_call_trace_id.load(std::memory_order_acquire));
    ASSERT_EQ(1ULL, block_slot->unowned_blocked_decision_count.load(std::memory_order_acquire));

    // A separately live trace verifies that rotation preserves real registered IDs.
    ASGCT_CallFrame control_frame{};
    control_frame.bci = 20;
    control_frame.method_id = (jmethodID)0x5678;
    u64 control_trace_id = storage.put(1, &control_frame, false, 1);
    ASSERT_GT(control_trace_id >> 32, 0ULL);
    ASSERT_NE(initial_trace_id, control_trace_id);
    storage.registerLivenessChecker([control_trace_id](CallTraceIdSet& live) {
        live.insert(control_trace_id);
    });

    CallTraceIdSet first_pool;
    storage.processTraces([&](const CallTraceSet& traces) {
        for (CallTrace* trace : traces) {
            first_pool.insert(trace->trace_id);
            if (trace->trace_id == initial_trace_id) {
                ASSERT_EQ(1, trace->num_frames);
                EXPECT_EQ(frame.bci, trace->frames[0].bci);
                EXPECT_EQ(frame.method_id, trace->frames[0].method_id);
            }
        }
    });
    ASSERT_EQ(1U, first_pool.count(initial_trace_id));
    ASSERT_EQ(1U, first_pool.count(control_trace_id));

    // The next blocked observation is suppressed; becoming runnable flushes its weight.
    ASSERT_FALSE(block_slot->shouldRecordUnownedBlockedSample());
    ASSERT_TRUE(block_slot->flushUnownedBlockedTail(tail_trace_id, tail_weight, tail_state));
    ASSERT_GT(tail_trace_id >> 32, 0ULL);
    ASSERT_EQ(1ULL, tail_weight);
    ASSERT_EQ(OSThreadState::CONDVAR_WAIT, tail_state);
    CallTraceIdSet next_references{tail_trace_id};

    // Copy IDs, not CallTrace pointers: processTraces reclaims frames after its callback.
    CallTraceIdSet next_pool;
    storage.processTraces([&](const CallTraceSet& traces) {
        for (CallTrace* trace : traces) {
            next_pool.insert(trace->trace_id);
        }
    });
    ASSERT_EQ(1U, next_pool.count(control_trace_id));
    for (u64 referenced_id : next_references) {
        EXPECT_EQ(1U, next_pool.count(referenced_id))
            << "Deferred unowned wall trace " << referenced_id
            << " has no stack in the next processed pool";
    }
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

// BlockState storage (~128 KiB) is allocated lazily on the first locked
// registerThread() of the wired filter (R-B2): nothing is allocated or
// accounted at construction, the storage is accounted to NativeMem
// (NM_WALLCLOCK) once allocated, stays at a stable address, and the
// destructor retracts it.
TEST(WallClockBlockTrackerNativeMemTest, StorageIsAllocatedLazilyAndAccounted) {
    const long long before = NativeMem::live(NM_WALLCLOCK);
    const long long storage_bytes =
        static_cast<long long>(WallClockBlockTracker::storageSize());
    RecordProperty("slot_storage_bytes", static_cast<int>(storage_bytes));
    RecordProperty("block_state_bytes", static_cast<int>(sizeof(WallClockBlockTracker::BlockState)));
    {
        WallClockBlockTracker local_tracker;
        EXPECT_EQ(before, NativeMem::live(NM_WALLCLOCK));
        EXPECT_EQ(nullptr, local_tracker.slotForId(0));
        local_tracker.resetAll();                          // null-safe
        local_tracker.resetSlot(0, OSThreadState::UNKNOWN);  // no-op
        EXPECT_EQ(before, NativeMem::live(NM_WALLCLOCK));

        // Declared after the tracker so it is destroyed first.
        ThreadFilter local_filter;
        local_filter.setBlockTracker(&local_tracker);
        local_filter.init("", true);
        EXPECT_EQ(0ULL, local_tracker.enterBlockedRun(&local_filter, 0, OSThreadState::CONDVAR_WAIT));
        EXPECT_EQ(before, NativeMem::live(NM_WALLCLOCK));

        ThreadFilter::SlotID slot_id = local_filter.registerThread(1234);
        ASSERT_GE(slot_id, 0);
        EXPECT_EQ(before + storage_bytes, NativeMem::live(NM_WALLCLOCK));
        WallClockBlockTracker::BlockState* block_slot = local_tracker.slotForId(slot_id);
        ASSERT_NE(nullptr, block_slot);
        EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());
        EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
        EXPECT_FALSE(block_slot->sampledThisRun());

        ThreadFilter::SlotID other = local_filter.registerThread(1235);
        ASSERT_GE(other, 0);
        local_filter.unregisterThread(other, 1235);
        EXPECT_TRUE(local_tracker.ensureAllocated());
        EXPECT_EQ(before + storage_bytes, NativeMem::live(NM_WALLCLOCK));
        EXPECT_EQ(block_slot, local_tracker.slotForId(slot_id));
    }
    EXPECT_EQ(before, NativeMem::live(NM_WALLCLOCK));
}

class UnownedContextSidecarTest : public WallClockBlockTrackerTest {
protected:
    void SetUp() override {
        WallClockBlockTrackerTest::SetUp();
        tracker->setUnownedContextSnapshotsNeeded(true);
    }

    static Context context(u32 first_tag) {
        Context value{};
        value.spanId = 0xfedcba9876543210ULL;
        value.rootSpanId = 0x8123456789abcdefULL;
        for (int i = 0; i < 10; ++i) value.setTag(i, first_tag + i);
        return value;
    }

    static void expectContext(const Context& expected, const Context& actual) {
        EXPECT_EQ(expected.spanId, actual.spanId);
        EXPECT_EQ(expected.rootSpanId, actual.rootSpanId);
        for (int i = 0; i < 10; ++i) EXPECT_EQ(expected.getTag(i), actual.getTag(i));
    }

    u64 realTrace(CallTraceStorage& traces) {
        ASGCT_CallFrame frame{};
        frame.bci = 41;
        frame.method_id = (jmethodID)0x7751;
        return traces.put(1, &frame, false, 1);
    }
};

class ScopedUnownedContextAllocationFailure {
    WallClockBlockTracker& tracker;
    bool previous;
public:
    explicit ScopedUnownedContextAllocationFailure(WallClockBlockTracker& value)
        : tracker(value), previous(value.exchangeUnownedContextAllocationFailureForTest(true)) {}
    ~ScopedUnownedContextAllocationFailure() {
        tracker.exchangeUnownedContextAllocationFailureForTest(previous);
    }
    ScopedUnownedContextAllocationFailure(const ScopedUnownedContextAllocationFailure&) = delete;
    ScopedUnownedContextAllocationFailure& operator=(const ScopedUnownedContextAllocationFailure&) = delete;
};

TEST_F(UnownedContextSidecarTest, ContextBoundariesRetainOriginalUnownedTailFields) {
    for (int transition = 0; transition < 3; ++transition) {
        SCOPED_TRACE(transition);
        const int tid = 7800 + transition;
        int id = filter->registerThread(tid);
        ASSERT_GE(id, 0);
        auto* block = tracker->slotForId(id);
        if (transition == 2) ASSERT_TRUE(filter->add(tid, id));
        if (transition == 0) {
            ASSERT_NE(0ULL, tracker->enterBlockedRun(filter.get(), id, OSThreadState::SLEEPING));
            block->markSampledThisRun(OSThreadState::SLEEPING);
        }
        CallTraceStorage traces;
        u64 root = realTrace(traces);
        ASSERT_GT(root >> 32, 0ULL);
        Context original = context(0xA100 + transition);
        ASSERT_TRUE(block->shouldRecordUnownedBlockedSample());
        ASSERT_TRUE(tracker->publishUnownedTrace(id, root, OSThreadState::CONDVAR_WAIT, original));
        ASSERT_FALSE(block->shouldRecordUnownedBlockedSample());
        ASSERT_FALSE(block->shouldRecordUnownedBlockedSample());
        if (transition == 2) filter->remove(id);
        else ASSERT_TRUE(filter->add(tid, id));
        EXPECT_EQ(BlockRunOwner::NONE, block->activeBlockOwner());
        EXPECT_FALSE(block->sampledThisRun());
        Context retained{};
        u64 publication = 0;
        ASSERT_TRUE(tracker->readUnownedContext(id, retained, publication));
        expectContext(original, retained);
        u64 trace = 0, weight = 0;
        OSThreadState state = OSThreadState::UNKNOWN;
        ASSERT_TRUE(block->flushUnownedBlockedTail(trace, weight, state));
        EXPECT_EQ(root, trace);
        EXPECT_EQ(2ULL, weight);
        EXPECT_EQ(OSThreadState::CONDVAR_WAIT, state);
    }
}

TEST_F(UnownedContextSidecarTest, RoundTripAllTenTags) {
    int id = filter->registerThread(7751);
    ASSERT_GE(id, 0);
    ASSERT_TRUE(tracker->canPublishUnownedContext(id));
    Context actual{};
    u64 sequence = 99;
    EXPECT_FALSE(tracker->readUnownedContext(id, actual, sequence));
    EXPECT_EQ(0ULL, sequence);
    CallTraceStorage traces;
    u64 root = realTrace(traces);
    ASSERT_GT(root >> 32, 0ULL);
    Context expected = context(0xf1234560U);
    ASSERT_TRUE(tracker->publishUnownedTrace(id, root, OSThreadState::SLEEPING, expected));
    ASSERT_TRUE(tracker->readUnownedContext(id, actual, sequence));
    EXPECT_EQ(2ULL, sequence);
    expectContext(expected, actual);
    tracker->resetAll();
    EXPECT_FALSE(tracker->readUnownedContext(id, actual, sequence));
    Context empty{};
    ASSERT_TRUE(tracker->publishUnownedTrace(id, root, OSThreadState::SLEEPING, empty));
    ASSERT_TRUE(tracker->readUnownedContext(id, actual, sequence));
    EXPECT_EQ(4ULL, sequence); // Reset invalidates the root, never recycles the sequence.
    expectContext(empty, actual);
    EXPECT_EQ(64U, sizeof(ThreadFilter::Slot));
    EXPECT_EQ(64U, sizeof(WallClockBlockTracker::BlockState));
}

TEST_F(UnownedContextSidecarTest, OddPublicationIsRejectedAtEveryPayloadBoundary) {
    int id = filter->registerThread(7752);
    ASSERT_GE(id, 0);
    CallTraceStorage traces;
    u64 root = realTrace(traces);
    Context first = context(100);
    ASSERT_TRUE(tracker->publishUnownedTrace(id, root, OSThreadState::SLEEPING, first));
    struct Probe {
        WallClockBlockTracker* tracker;
        int id;
        unsigned calls = 0;
        static void check(u32 words, void* raw) {
            auto* probe = static_cast<Probe*>(raw);
            EXPECT_EQ(probe->calls++, words);
            Context candidate{};
            u64 sequence = 99;
            EXPECT_FALSE(probe->tracker->readUnownedContext(probe->id, candidate, sequence));
            EXPECT_EQ(0ULL, sequence);
            EXPECT_FALSE(probe->tracker->canPublishUnownedContext(probe->id));
        }
    } probe{tracker.get(), id};
    struct ScopedHook {
        WallClockBlockTracker& tracker;
        ScopedHook(WallClockBlockTracker& value, Probe& probe) : tracker(value) {
            tracker.setUnownedContextPublicationHookForTest(Probe::check, &probe);
        }
        ~ScopedHook() { tracker.setUnownedContextPublicationHookForTest(nullptr, nullptr); }
        ScopedHook(const ScopedHook&) = delete;
        ScopedHook& operator=(const ScopedHook&) = delete;
    } hook(*tracker, probe);
    Context second = context(200);
    ASSERT_TRUE(tracker->publishUnownedTrace(id, root, OSThreadState::CONDVAR_WAIT, second));
    EXPECT_EQ(8U, probe.calls);
    Context actual{};
    u64 sequence = 0;
    ASSERT_TRUE(tracker->readUnownedContext(id, actual, sequence));
    EXPECT_EQ(4ULL, sequence);
    expectContext(second, actual);
}

TEST_F(UnownedContextSidecarTest, ChangingPublicationIsRejected) {
    int id = filter->registerThread(7757);
    ASSERT_GE(id, 0);
    CallTraceStorage traces;
    u64 root = realTrace(traces);
    Context first = context(100);
    ASSERT_TRUE(tracker->publishUnownedTrace(id, root, OSThreadState::SLEEPING, first));
    struct Change {
        WallClockBlockTracker* tracker;
        int id;
        u64 root;
        Context replacement;
        static void publish(void* arg) {
            auto* change = static_cast<Change*>(arg);
            EXPECT_TRUE(change->tracker->publishUnownedTrace(change->id, change->root,
                OSThreadState::SLEEPING, change->replacement));
        }
    } change{tracker.get(), id, root, context(200)};
    Context actual{};
    u64 sequence = 99;
    {
        struct ScopedHook {
            WallClockBlockTracker& tracker;
            ScopedHook(WallClockBlockTracker& value, Change& change) : tracker(value) {
                tracker.setUnownedContextReadHookForTest(Change::publish, &change);
            }
            ~ScopedHook() { tracker.setUnownedContextReadHookForTest(nullptr, nullptr); }
            ScopedHook(const ScopedHook&) = delete;
            ScopedHook& operator=(const ScopedHook&) = delete;
        } hook(*tracker, change);
        EXPECT_FALSE(tracker->readUnownedContext(id, actual, sequence));
        EXPECT_EQ(0ULL, sequence);
    }
    ASSERT_TRUE(tracker->readUnownedContext(id, actual, sequence));
    EXPECT_EQ(4ULL, sequence);
    expectContext(change.replacement, actual);
}

TEST_F(UnownedContextSidecarTest, NormalColdAllocationBalancesMemory) {
    long long before = NativeMem::live(NM_WALLCLOCK);
    {
        WallClockBlockTracker local;
        local.setUnownedContextSnapshotsNeeded(true);
        ThreadFilter registry;
        registry.setBlockTracker(&local);
        registry.init("0");
        EXPECT_EQ(before, NativeMem::live(NM_WALLCLOCK));
        ASSERT_GE(registry.registerThread(7753), 0);
        const long long total = WallClockBlockTracker::storageSize() +
                               WallClockBlockTracker::unownedContextChunkSizeForTest();
        EXPECT_EQ(32768U, WallClockBlockTracker::unownedContextChunkSizeForTest());
        EXPECT_EQ(before + total, NativeMem::live(NM_WALLCLOCK));
        ASSERT_GE(registry.registerThread(7754), 0);
        local.resetAll();
        EXPECT_EQ(before + total, NativeMem::live(NM_WALLCLOCK));
        RecordProperty("context_chunk_bytes", static_cast<int>(
            WallClockBlockTracker::unownedContextChunkSizeForTest()));
    }
    EXPECT_EQ(before, NativeMem::live(NM_WALLCLOCK));
}

TEST_F(UnownedContextSidecarTest, ContextChunksAccountOnceAcrossBoundaries) {
    const long long before = NativeMem::live(NM_WALLCLOCK);
    const long long storage_bytes = static_cast<long long>(WallClockBlockTracker::storageSize());
    const long long chunk_bytes = 32768;
    {
        WallClockBlockTracker local;
        local.setUnownedContextSnapshotsNeeded(true);
        ASSERT_TRUE(local.ensureAllocated());
        EXPECT_EQ(before + storage_bytes, NativeMem::live(NM_WALLCLOCK));
        for (int first = 0; first < ThreadFilter::kMaxThreads; first += ThreadFilter::kChunkSize) {
            SCOPED_TRACE(first);
            ASSERT_TRUE(local.ensureUnownedContextAllocated(first));
            const long long allocated = storage_bytes +
                (first / ThreadFilter::kChunkSize + 1) * chunk_bytes;
            EXPECT_EQ(before + allocated, NativeMem::live(NM_WALLCLOCK));
            const int last = first + ThreadFilter::kChunkSize - 1;
            ASSERT_TRUE(local.ensureUnownedContextAllocated(last));
            EXPECT_TRUE(local.canPublishUnownedContext(first));
            EXPECT_TRUE(local.canPublishUnownedContext(last));
            EXPECT_EQ(before + allocated, NativeMem::live(NM_WALLCLOCK));
        }
        const long long full = before + storage_bytes + ThreadFilter::kMaxChunks * chunk_bytes;
        EXPECT_FALSE(local.ensureUnownedContextAllocated(-1));
        EXPECT_FALSE(local.ensureUnownedContextAllocated(ThreadFilter::kMaxThreads));
        local.resetAll();
        EXPECT_EQ(full, NativeMem::live(NM_WALLCLOCK));
    }
    EXPECT_EQ(before, NativeMem::live(NM_WALLCLOCK));
}

TEST_F(UnownedContextSidecarTest, AllocatedBackingSurvivesModeToggle) {
    const long long before = NativeMem::live(NM_WALLCLOCK);
    int id = filter->registerThread(7758);
    ASSERT_GE(id, 0);
    ASSERT_LT(id, ThreadFilter::kChunkSize);
    const long long allocated = before + static_cast<long long>(
        WallClockBlockTracker::storageSize()) + 32768;
    ASSERT_EQ(allocated, NativeMem::live(NM_WALLCLOCK));
    CallTraceStorage traces;
    u64 root = realTrace(traces);
    ASSERT_GT(root >> 32, 0ULL);
    Context first = context(500);
    ASSERT_TRUE(tracker->publishUnownedTrace(id, root, OSThreadState::SLEEPING, first));
    Context actual{};
    u64 sequence = 0;
    ASSERT_TRUE(tracker->readUnownedContext(id, actual, sequence));
    const u64 saved_sequence = sequence;
    expectContext(first, actual);

    tracker->setUnownedContextSnapshotsNeeded(false);
    EXPECT_FALSE(tracker->canPublishUnownedContext(id));
    EXPECT_FALSE(tracker->publishUnownedTrace(id, root, OSThreadState::SLEEPING, context(600)));
    EXPECT_TRUE(tracker->ensureUnownedContextAllocated(ThreadFilter::kChunkSize));
    EXPECT_EQ(allocated, NativeMem::live(NM_WALLCLOCK));
    ASSERT_TRUE(tracker->readUnownedContext(id, actual, sequence));
    EXPECT_EQ(saved_sequence, sequence);
    expectContext(first, actual);

    tracker->setUnownedContextSnapshotsNeeded(true);
    EXPECT_FALSE(tracker->canPublishUnownedContext(ThreadFilter::kChunkSize));
    EXPECT_TRUE(tracker->canPublishUnownedContext(id));
    EXPECT_TRUE(tracker->ensureUnownedContextAllocated(id));
    EXPECT_EQ(allocated, NativeMem::live(NM_WALLCLOCK));
    tracker->resetAll();
    EXPECT_FALSE(tracker->readUnownedContext(id, actual, sequence));
    Context second = context(700);
    ASSERT_TRUE(tracker->publishUnownedTrace(id, root, OSThreadState::CONDVAR_WAIT, second));
    ASSERT_TRUE(tracker->readUnownedContext(id, actual, sequence));
    EXPECT_GT(sequence, saved_sequence);
    expectContext(second, actual);
    EXPECT_EQ(allocated, NativeMem::live(NM_WALLCLOCK));
}

TEST_F(UnownedContextSidecarTest, ModeOffDoesNotAllocate) {
    tracker->setUnownedContextSnapshotsNeeded(false);
    long long before = NativeMem::live(NM_WALLCLOCK);
    EXPECT_TRUE(tracker->ensureUnownedContextAllocated(0));
    EXPECT_EQ(before, NativeMem::live(NM_WALLCLOCK));
    int id = filter->registerThread(7755);
    ASSERT_GE(id, 0);
    EXPECT_FALSE(tracker->canPublishUnownedContext(id));
    EXPECT_EQ(before + static_cast<long long>(WallClockBlockTracker::storageSize()),
              NativeMem::live(NM_WALLCLOCK));
    tracker->setUnownedContextSnapshotsNeeded(true);
    // A warm lookup cannot repair backing even after the mode flag changes.
    EXPECT_FALSE(tracker->canPublishUnownedContext(id));
    tracker->setUnownedContextSnapshotsNeeded(false);
}

TEST_F(UnownedContextSidecarTest, AllocationFailureRetainsNativeOwner) {
    std::async(std::launch::async, [&] {
        struct ScopedOwner {
            ThreadFilter& registry;
            ProfiledThread* owner = ProfiledThread::initCurrentThreadSignalSafe();
            explicit ScopedOwner(ThreadFilter& value) : registry(value) {}
            ~ScopedOwner() {
                if (owner != nullptr) registry.unregisterThread(owner->filterSlotId(), owner->tid());
                ProfiledThread::release();
            }
            ScopedOwner(const ScopedOwner&) = delete;
            ScopedOwner& operator=(const ScopedOwner&) = delete;
        } lifetime(*filter);
        ASSERT_NE(nullptr, lifetime.owner);
        auto& owner = *lifetime.owner;
        owner.enterLogicalContextWindow();
        const u64 logical = owner.logicalContextWindowState();
        const long long before = NativeMem::live(NM_WALLCLOCK);
        const long long storage_bytes = static_cast<long long>(WallClockBlockTracker::storageSize());
        int id;
        {
            ScopedUnownedContextAllocationFailure failure(*tracker);
            id = filter->ensureOwnerSlot(owner);
            ASSERT_GE(id, 0);
            auto* slot = filter->activeSlotForId(id, owner.tid());
            ASSERT_NE(nullptr, slot);
            EXPECT_EQ(owner.tid(), slot->nativeTid());
            EXPECT_EQ(logical, owner.logicalContextWindowState());
            EXPECT_FALSE(tracker->canPublishUnownedContext(id));
            EXPECT_EQ(before + storage_bytes, NativeMem::live(NM_WALLCLOCK));
            // No allocation retry on the successful warm binding path.
            EXPECT_EQ(id, filter->ensureOwnerSlot(owner));
            EXPECT_FALSE(tracker->canPublishUnownedContext(id));
            EXPECT_EQ(before + storage_bytes, NativeMem::live(NM_WALLCLOCK));
        }
        EXPECT_FALSE(tracker->canPublishUnownedContext(id));
        EXPECT_EQ(id, filter->registerThread(owner.tid(), logical));
        EXPECT_TRUE(tracker->canPublishUnownedContext(id));
        EXPECT_EQ(logical, owner.logicalContextWindowState());
        const long long allocated = before + storage_bytes + 32768;
        EXPECT_EQ(allocated, NativeMem::live(NM_WALLCLOCK));
        {
            ScopedUnownedContextAllocationFailure failure(*tracker);
            EXPECT_EQ(id, filter->registerThread(owner.tid(), logical));
            EXPECT_TRUE(tracker->canPublishUnownedContext(id));
            EXPECT_EQ(allocated, NativeMem::live(NM_WALLCLOCK));
        }
    }).get();
}

TEST_F(UnownedContextSidecarTest, LastEvenSequenceDoesNotWrap) {
    int id = filter->registerThread(7756);
    ASSERT_GE(id, 0);
    CallTraceStorage traces;
    u64 root = realTrace(traces);
    tracker->setUnownedContextPublicationForTest(id, UINT64_MAX - 3);
    Context expected = context(300);
    ASSERT_TRUE(tracker->publishUnownedTrace(id, root, OSThreadState::SLEEPING, expected));
    Context actual{};
    u64 sequence = 0;
    ASSERT_TRUE(tracker->readUnownedContext(id, actual, sequence));
    EXPECT_EQ(UINT64_MAX - 1, sequence);
    EXPECT_FALSE(tracker->canPublishUnownedContext(id));
    EXPECT_FALSE(tracker->publishUnownedTrace(id, root, OSThreadState::SLEEPING, context(400)));
    ASSERT_TRUE(tracker->readUnownedContext(id, actual, sequence));
    EXPECT_EQ(UINT64_MAX - 1, sequence);
    expectContext(expected, actual);
    tracker->resetAll();
    EXPECT_FALSE(tracker->readUnownedContext(id, actual, sequence));
    EXPECT_FALSE(tracker->canPublishUnownedContext(id));
}

// Exercise the actual Profiler-owned storage and collector registration, not a
// fixture callback that inserts the expected ID into the preservation set.
TEST(WallClockProductionRootsTest, ZeroWeightRootSurvivesRepeatedDumpsOutsideMembership) {
    ProfiledThread::initCurrentThreadSignalSafe();
    auto profiler = std::make_unique<Profiler>();
    auto* registry = profiler->threadFilter();
    auto* tracker = profiler->blockTracker();
    registry->init("enabled");
    int slot_id = registry->registerThread(7901);
    ASSERT_GE(slot_id, 0);
    ASSERT_TRUE(registry->add(7901, slot_id));
    ASGCT_CallFrame frame{};
    frame.bci = 37;
    frame.method_id = (jmethodID)0x7901;
    const u64 id = profiler->callTraceStorageForTest()->put(1, &frame, false, 1);
    ASSERT_GT(id >> 32, 0ULL);
    auto* block = tracker->slotForId(slot_id);
    ASSERT_TRUE(block->shouldRecordUnownedBlockedSample());
    tracker->publishUnownedTrace(slot_id, id, OSThreadState::CONDVAR_WAIT);
    registry->remove(slot_id);
    for (int dump = 0; dump < 4; ++dump) {
        bool found = false;
        profiler->processCallTraces([&](const CallTraceSet& traces) {
            for (auto* trace : traces) {
                if (trace->trace_id == id) {
                    found = true;
                    ASSERT_EQ(1, trace->num_frames);
                    EXPECT_EQ(frame.method_id, trace->frames[0].method_id);
                    EXPECT_EQ(frame.bci, trace->frames[0].bci);
                }
            }
        });
        EXPECT_TRUE(found) << "dump=" << dump;
        EXPECT_EQ(0ULL, block->unowned_blocked_pending_weight.load());
        EXPECT_EQ(1ULL, block->unowned_blocked_decision_count.load());
    }
}

TEST(WallClockProductionRootsTest, CopyFailureRetainsWeightStateAndCadence) {
    ProfiledThread::initCurrentThreadSignalSafe();
    auto profiler = std::make_unique<Profiler>();
    auto* registry = profiler->threadFilter();
    auto* tracker = profiler->blockTracker();
    registry->init("enabled");
    int slot_id = registry->registerThread(7902);
    ASSERT_GE(slot_id, 0);
    ASGCT_CallFrame frame{};
    frame.method_id = (jmethodID)0x7902;
    const u64 id = profiler->callTraceStorageForTest()->put(1, &frame, false, 1);
    auto* block = tracker->slotForId(slot_id);
    ASSERT_TRUE(block->shouldRecordUnownedBlockedSample());
    tracker->publishUnownedTrace(slot_id, id, OSThreadState::SLEEPING);
    ASSERT_FALSE(block->shouldRecordUnownedBlockedSample());
    const long long failures_before = Counters::getCounter(WC_UNOWNED_BLOCKED_TRACE_PRESERVATION_FAILED);
    {
        ScopedPreservationCopyFailure failure(id);
        profiler->processCallTraces([](const CallTraceSet&) {});
    }
    EXPECT_EQ(failures_before + 1,
              Counters::getCounter(WC_UNOWNED_BLOCKED_TRACE_PRESERVATION_FAILED));
    profiler->processCallTraces([](const CallTraceSet&) {});
    EXPECT_EQ(failures_before + 1,
              Counters::getCounter(WC_UNOWNED_BLOCKED_TRACE_PRESERVATION_FAILED));
    EXPECT_EQ(CallTraceStorage::DROPPED_TRACE_ID,
              block->unowned_blocked_call_trace_id.load());
    EXPECT_EQ(1ULL, block->unowned_blocked_pending_weight.load());
    EXPECT_EQ(2ULL, block->unowned_blocked_decision_count.load());
    EXPECT_EQ(OSThreadState::SLEEPING, block->unowned_blocked_state.load());
}

TEST(WallClockProductionRootsTest, PrunedRootIsIndexedAgainOnPublication) {
    ProfiledThread::initCurrentThreadSignalSafe();
    auto profiler = std::make_unique<Profiler>();
    auto* registry = profiler->threadFilter();
    auto* tracker = profiler->blockTracker();
    registry->init("enabled");
    int slot_id = registry->registerThread(7903);
    ASSERT_GE(slot_id, 0);
    ASGCT_CallFrame frame{};
    frame.method_id = (jmethodID)0x7903;
    auto* storage = profiler->callTraceStorageForTest();
    const u64 first = storage->put(1, &frame, false, 1);
    tracker->publishUnownedTrace(slot_id, first, OSThreadState::SLEEPING);
    profiler->processCallTraces([](const CallTraceSet&) {});
    tracker->resetSlot(slot_id, OSThreadState::UNKNOWN);
    profiler->processCallTraces([](const CallTraceSet&) {});
    const u64 second = storage->put(1, &frame, false, 1);
    ASSERT_NE(first, second);
    tracker->publishUnownedTrace(slot_id, second, OSThreadState::SLEEPING);
    for (int dump = 0; dump < 3; ++dump) {
        bool found = false;
        profiler->processCallTraces([&](const CallTraceSet& traces) {
            for (auto* trace : traces) {
                if (trace->trace_id == second) found = true;
            }
        });
        EXPECT_TRUE(found) << "dump=" << dump;
    }
}

// Owns the actual singleton preparation inputs on a fresh native thread. All
// overrides are restored before releasing TLS; no engine or signal is started.
class ScopedUnownedAttributionOwner {
public:
    Profiler* profiler = Profiler::instance();
    ProfiledThread* owner;
    WallClockASGCT clock;

    ScopedUnownedAttributionOwner()
        : owner(ProfiledThread::initCurrentThreadSignalSafe()),
          previous_attributes(profiler->exchangeNumContextAttributesForTest(1)),
          previous_reader(BaseWallClock::exchangeThreadStateReaderForTest(sleeping)),
          previous_write(profiler->sampleWriteHookForTest),
          previous_write_arg(profiler->sampleWriteHookArgForTest),
          previous_sampling_epoch(WallClockCounters::samplingEpochStart()) {
        WallClockCounters::beginSamplingEpoch(TSC::ticks());
        profiler->blockTracker()->setUnownedContextSnapshotsNeeded(true);
        profiler->threadFilter()->init("0");
        if (owner != nullptr) {
            ContextApi::initializeContextTLS(owner);
            profiler->threadFilter()->onContextWindowEnter(*owner);
        }
        profiler->sampleWriteHookForTest = acceptWrite;
        profiler->sampleWriteHookArgForTest = nullptr;
    }

    ~ScopedUnownedAttributionOwner() {
        WallClockCounters::beginSamplingEpoch(previous_sampling_epoch);
        BaseWallClock::setUnownedContextProbeHookForTest(nullptr, nullptr);
        profiler->sampleWriteHookForTest = previous_write;
        profiler->sampleWriteHookArgForTest = previous_write_arg;
        BaseWallClock::exchangeThreadStateReaderForTest(previous_reader);
        profiler->exchangeNumContextAttributesForTest(previous_attributes);
        if (owner != nullptr) {
            profiler->threadFilter()->unregisterThread(owner->filterSlotId(), owner->tid());
        }
        profiler->threadFilter()->deactivateRecording();
        profiler->blockTracker()->setUnownedContextSnapshotsNeeded(false);
        ProfiledThread::release();
    }

    ScopedUnownedAttributionOwner(const ScopedUnownedAttributionOwner&) = delete;
    ScopedUnownedAttributionOwner& operator=(const ScopedUnownedAttributionOwner&) = delete;

    void setTag(u32 encoding) {
        auto* record = owner->getOtelContextRecord();
        __atomic_store_n(&record->valid, 0, __ATOMIC_RELEASE);
        __atomic_store_n(owner->getOtelTagEncodingsPtr(), encoding, __ATOMIC_RELEASE);
        __atomic_store_n(&record->valid, 1, __ATOMIC_RELEASE);
    }

    void setSpan(u64 span) {
        auto* record = owner->getOtelContextRecord();
        __atomic_store_n(&record->valid, 0, __ATOMIC_RELEASE);
        for (int i = 7; i >= 0; --i) {
            __atomic_store_n(&record->span_id[i], static_cast<u8>(span), __ATOMIC_RELEASE);
            span >>= 8;
        }
        __atomic_store_n(&record->valid, 1, __ATOMIC_RELEASE);
    }

    void primeOrigin(u32 tag, u64& id, int decisions = 4) {
        ASSERT_NE(nullptr, owner);
        setTag(tag);
        ASGCT_CallFrame frame{};
        frame.bci = 39;
        frame.method_id = (jmethodID)0x7749;
        id = profiler->callTraceStorageForTest()->put(1, &frame, false, 1);
        ASSERT_NE(0ULL, id);
        ASSERT_NE(CallTraceStorage::DROPPED_TRACE_ID, id);
        bool suppressed = true;
        auto request = clock.prepareWallSampleRequestForTest(owner, suppressed);
        ASSERT_FALSE(suppressed);
        ASSERT_TRUE(request.unowned_sample);
        ExecutionEvent event;
        event._thread_state = OSThreadState::SLEEPING;
        event._execution_mode = ExecutionMode::JAVA;
        event._weight = 1;
        ASSERT_TRUE(profiler->recordWallSample(nullptr, 1, id, &event, request).ordinary_recorded);
        for (int decision = 2; decision <= decisions; ++decision) {
            clock.prepareWallSampleRequestForTest(owner, suppressed);
            ASSERT_TRUE(suppressed) << "decision=" << decision;
        }
    }

private:
    u32 previous_attributes;
    BaseWallClock::ThreadStateReaderForTest previous_reader;
    Profiler::SampleWriteHook previous_write;
    void* previous_write_arg;
    u64 previous_sampling_epoch;
    static OSThreadState sleeping() { return OSThreadState::SLEEPING; }
    static bool acceptWrite(u32, u64, Event*, const Context*, void*) { return true; }
};

TEST(UnownedWallAttributionTest, TagOnlyChangeDoesNotSuppressIntoPriorContext) {
    auto worker = std::async(std::launch::async, [] {
        ScopedUnownedAttributionOwner scoped;
        auto* owner = scoped.owner;
        ASSERT_NE(nullptr, owner);
        const int slot_id = owner->filterSlotId();
        ASSERT_GE(slot_id, 0);
        ASSERT_TRUE(scoped.profiler->threadFilter()->accept(slot_id));
        auto* block = scoped.profiler->blockTracker()->slotForId(slot_id);
        ASSERT_NE(nullptr, block);
        scoped.setTag(113);
        Context context_a = ContextApi::snapshot();
        ASSERT_EQ(0ULL, context_a.spanId);
        ASSERT_EQ(0ULL, context_a.rootSpanId);
        ASSERT_EQ(113U, context_a.getTag(0));

        ASGCT_CallFrame frame{};
        frame.bci = 39;
        frame.method_id = (jmethodID)0x7749;
        const u64 id = scoped.profiler->callTraceStorageForTest()->put(1, &frame, false, 1);
        ASSERT_NE(0ULL, id);
        ASSERT_NE(CallTraceStorage::DROPPED_TRACE_ID, id);
        bool suppressed = true;
        auto request = scoped.clock.prepareWallSampleRequestForTest(owner, suppressed);
        ASSERT_FALSE(suppressed);
        ASSERT_TRUE(request.unowned_sample);
        ExecutionEvent event;
        event._thread_state = OSThreadState::SLEEPING;
        event._execution_mode = ExecutionMode::JAVA;
        event._weight = 1;
        auto result = scoped.profiler->recordWallSample(nullptr, 1, id, &event, request);
        ASSERT_TRUE(result.ordinary_recorded);
        ASSERT_EQ(id, block->unowned_blocked_call_trace_id.load());
        ASSERT_EQ(1ULL, event._weight);
        for (int decision = 2; decision <= 4; ++decision) {
            scoped.clock.prepareWallSampleRequestForTest(owner, suppressed);
            ASSERT_TRUE(suppressed) << "decision=" << decision;
        }
        ASSERT_EQ(3ULL, block->unowned_blocked_pending_weight.load());
        ASSERT_EQ(4ULL, block->unowned_blocked_decision_count.load());

        scoped.setTag(227);
        Context context_b = ContextApi::snapshot();
        ASSERT_EQ(0ULL, context_b.spanId);
        ASSERT_EQ(0ULL, context_b.rootSpanId);
        ASSERT_EQ(227U, context_b.getTag(0));
        scoped.clock.prepareWallSampleRequestForTest(owner, suppressed);
        EXPECT_FALSE(suppressed) << "Tag B must not add weight to the retained tag A origin";
        EXPECT_EQ(3ULL, block->unowned_blocked_pending_weight.load());
        EXPECT_EQ(5ULL, block->unowned_blocked_decision_count.load());
        EXPECT_EQ(id, block->unowned_blocked_call_trace_id.load());
    });
    worker.get();
}

TEST(UnownedWallAttributionTest, KnownSpanLeavesOriginPending) {
    auto worker = std::async(std::launch::async, [] {
        ScopedUnownedAttributionOwner scoped;
        u64 id = 0;
        ASSERT_NO_FATAL_FAILURE(scoped.primeOrigin(113, id));
        auto* block = scoped.profiler->blockTracker()->slotForId(scoped.owner->filterSlotId());
        scoped.setTag(227);
        scoped.setSpan(77);
        bool suppressed = true;
        auto request = scoped.clock.prepareWallSampleRequestForTest(scoped.owner, suppressed);
        EXPECT_FALSE(suppressed);
        EXPECT_FALSE(request.unowned_sample);
        EXPECT_FALSE(request.flush_tail);
        EXPECT_FALSE(request.context_captured);
        EXPECT_EQ(3ULL, block->unowned_blocked_pending_weight.load());
        EXPECT_EQ(4ULL, block->unowned_blocked_decision_count.load());
        EXPECT_EQ(id, block->unowned_blocked_call_trace_id.load());
        scoped.setSpan(0);
        scoped.setTag(331);
        request = scoped.clock.prepareWallSampleRequestForTest(scoped.owner, suppressed);
        EXPECT_FALSE(suppressed);
        EXPECT_TRUE(request.force_unowned_ordinary);
        EXPECT_TRUE(request.flush_tail);
        EXPECT_EQ(331U, request.context.getTag(0));
        EXPECT_EQ(3ULL, block->unowned_blocked_pending_weight.load());
        EXPECT_EQ(5ULL, block->unowned_blocked_decision_count.load());
    });
    worker.get();
}

TEST(UnownedWallAttributionTest, PeriodicBoundaryKeepsNineOldUnits) {
    auto worker = std::async(std::launch::async, [] {
        ScopedUnownedAttributionOwner scoped;
        u64 id = 0;
        ASSERT_NO_FATAL_FAILURE(scoped.primeOrigin(113, id, 10));
        auto* block = scoped.profiler->blockTracker()->slotForId(scoped.owner->filterSlotId());
        scoped.setTag(227);
        bool suppressed = true;
        auto request = scoped.clock.prepareWallSampleRequestForTest(scoped.owner, suppressed);
        ASSERT_FALSE(suppressed);
        ASSERT_TRUE(request.force_unowned_ordinary);
        ASSERT_EQ(9ULL, block->unowned_blocked_pending_weight.load());
        ASSERT_EQ(11ULL, block->unowned_blocked_decision_count.load());
        struct Writes { int ordinary = 0; int tail = 0; } writes;
        scoped.profiler->sampleWriteHookArgForTest = &writes;
        scoped.profiler->sampleWriteHookForTest = +[](u32, u64, Event* event,
                                                     const Context* context, void* arg) {
            auto* writes = static_cast<Writes*>(arg);
            auto* sample = static_cast<ExecutionEvent*>(event);
            EXPECT_NE(nullptr, context);
            if (context == nullptr) return false;
            if (sample->_thread_state == OSThreadState::RUNNABLE) {
                ++writes->ordinary;
                EXPECT_EQ(1ULL, sample->_weight);
                EXPECT_EQ(227U, context->getTag(0));
            } else {
                ++writes->tail;
                EXPECT_EQ(OSThreadState::SLEEPING, sample->_thread_state);
                EXPECT_EQ(9ULL, sample->_weight);
                EXPECT_EQ(113U, context->getTag(0));
            }
            return true;
        };
        ExecutionEvent event;
        event._thread_state = OSThreadState::RUNNABLE;
        event._execution_mode = ExecutionMode::JAVA;
        event._weight = 1;
        auto result = scoped.profiler->recordWallSample(nullptr, 1, id, &event, request);
        EXPECT_TRUE(result.ordinary_recorded);
        EXPECT_TRUE(result.tail_recorded);
        EXPECT_EQ(1, writes.ordinary);
        EXPECT_EQ(1, writes.tail);
        EXPECT_EQ(0ULL, block->unowned_blocked_pending_weight.load());
        EXPECT_EQ(11ULL, block->unowned_blocked_decision_count.load());
        Context retained{};
        u64 publication = 0;
        ASSERT_TRUE(scoped.profiler->blockTracker()->readUnownedContext(
            scoped.owner->filterSlotId(), retained, publication));
        EXPECT_EQ(227U, retained.getTag(0));
    });
    worker.get();
}

TEST(UnownedWallAttributionTest, MatchingPeriodicConsumesNineOldUnitsOnce) {
    auto worker = std::async(std::launch::async, [] {
        ScopedUnownedAttributionOwner scoped;
        u64 id = 0;
        ASSERT_NO_FATAL_FAILURE(scoped.primeOrigin(113, id, 10));
        bool suppressed = true;
        auto request = scoped.clock.prepareWallSampleRequestForTest(scoped.owner, suppressed);
        ASSERT_FALSE(suppressed);
        ASSERT_FALSE(request.force_unowned_ordinary);
        struct Writes { int count = 0; } writes;
        scoped.profiler->sampleWriteHookArgForTest = &writes;
        scoped.profiler->sampleWriteHookForTest = +[](u32, u64, Event* event,
                                                     const Context* context, void* arg) {
            ++static_cast<Writes*>(arg)->count;
            EXPECT_EQ(10ULL, static_cast<ExecutionEvent*>(event)->_weight);
            EXPECT_EQ(WallClockCounters::samplingEpochStart(),
                      static_cast<ExecutionEvent*>(event)->_sample_ticks);
            EXPECT_NE(nullptr, context);
            if (context != nullptr) EXPECT_EQ(113U, context->getTag(0));
            return true;
        };
        ExecutionEvent event;
        event._thread_state = OSThreadState::SLEEPING;
        event._execution_mode = ExecutionMode::JAVA;
        event._weight = 1;
        auto result = scoped.profiler->recordWallSample(nullptr, 1, id, &event, request);
        EXPECT_TRUE(result.ordinary_recorded);
        EXPECT_FALSE(result.tail_recorded);
        EXPECT_EQ(1, writes.count);
        auto* block = scoped.profiler->blockTracker()->slotForId(scoped.owner->filterSlotId());
        EXPECT_EQ(0ULL, block->unowned_blocked_pending_weight.load());
        EXPECT_EQ(11ULL, block->unowned_blocked_decision_count.load());
    });
    worker.get();
}

TEST(UnownedWallAttributionTest, TerminalSequenceFailsOpenWithoutWrapping) {
    auto worker = std::async(std::launch::async, [] {
        ScopedUnownedAttributionOwner scoped;
        u64 id = 0;
        ASSERT_NO_FATAL_FAILURE(scoped.primeOrigin(113, id));
        auto* tracker = scoped.profiler->blockTracker();
        const int slot_id = scoped.owner->filterSlotId();
        Context origin{};
        u64 previous = 0;
        ASSERT_TRUE(tracker->readUnownedContext(slot_id, origin, previous));
        // This quiescent fixture injects a terminal value into the singleton.
        // Restore only the test override, including on fatal assertion exits.
        struct PublicationOverride {
            WallClockBlockTracker* tracker;
            int slot;
            u64 previous;
            PublicationOverride(WallClockBlockTracker* tracker, int slot, u64 previous)
                : tracker(tracker), slot(slot), previous(previous) {
                tracker->setUnownedContextPublicationForTest(slot, UINT64_MAX - 1);
            }
            ~PublicationOverride() { tracker->setUnownedContextPublicationForTest(slot, previous); }
            PublicationOverride(const PublicationOverride&) = delete;
            PublicationOverride& operator=(const PublicationOverride&) = delete;
        } publication_override(tracker, slot_id, previous);
        const u64 unavailable = Counters::getCounter(WC_UNOWNED_CONTEXT_SNAPSHOT_UNAVAILABLE);
        bool suppressed = true;
        auto request = scoped.clock.prepareWallSampleRequestForTest(scoped.owner, suppressed);
        ASSERT_FALSE(suppressed);
        ASSERT_TRUE(request.force_unowned_ordinary);
        EXPECT_EQ(UINT64_MAX - 1, request.context_publication);
        EXPECT_EQ(unavailable + 1, Counters::getCounter(WC_UNOWNED_CONTEXT_SNAPSHOT_UNAVAILABLE));
        ExecutionEvent event;
        event._thread_state = OSThreadState::RUNNABLE;
        event._execution_mode = ExecutionMode::JAVA;
        event._weight = 1;
        auto result = scoped.profiler->recordWallSample(nullptr, 1, id, &event, request);
        EXPECT_TRUE(result.ordinary_recorded);
        EXPECT_TRUE(result.tail_recorded);
        EXPECT_EQ(1ULL, event._weight);
        auto* block = tracker->slotForId(slot_id);
        EXPECT_EQ(0ULL, block->unowned_blocked_call_trace_id.load());
        EXPECT_EQ(0ULL, block->unowned_blocked_pending_weight.load());
        EXPECT_EQ(5ULL, block->unowned_blocked_decision_count.load());
        EXPECT_FALSE(tracker->canPublishUnownedContext(slot_id));
    });
    worker.get();
}

TEST(UnownedWallAttributionTest, EmptySnapshotIsNotMissing) {
    auto worker = std::async(std::launch::async, [] {
        ScopedUnownedAttributionOwner scoped;
        const u64 unavailable = Counters::getCounter(WC_UNOWNED_CONTEXT_SNAPSHOT_UNAVAILABLE);
        u64 id = 0;
        ASSERT_NO_FATAL_FAILURE(scoped.primeOrigin(0, id));
        bool suppressed = false;
        scoped.clock.prepareWallSampleRequestForTest(scoped.owner, suppressed);
        EXPECT_TRUE(suppressed);
        auto* block = scoped.profiler->blockTracker()->slotForId(scoped.owner->filterSlotId());
        EXPECT_EQ(4ULL, block->unowned_blocked_pending_weight.load());
        EXPECT_EQ(unavailable, Counters::getCounter(WC_UNOWNED_CONTEXT_SNAPSHOT_UNAVAILABLE));
    });
    worker.get();
}

TEST(UnownedWallAttributionTest, ChangedPublicationCannotJustifySuppression) {
    auto worker = std::async(std::launch::async, [] {
        ScopedUnownedAttributionOwner scoped;
        u64 id = 0;
        ASSERT_NO_FATAL_FAILURE(scoped.primeOrigin(113, id));
        struct Probe { ScopedUnownedAttributionOwner* scoped; u64 id; } probe{&scoped, id};
        BaseWallClock::setUnownedContextProbeHookForTest(+[](void* arg) {
            auto* probe = static_cast<Probe*>(arg);
            Context context = ContextApi::snapshot();
            EXPECT_TRUE(probe->scoped->profiler->blockTracker()->publishUnownedTrace(
                probe->scoped->owner->filterSlotId(), probe->id, OSThreadState::SLEEPING, context));
        }, &probe);
        const u64 unavailable = Counters::getCounter(WC_UNOWNED_CONTEXT_SNAPSHOT_UNAVAILABLE);
        bool suppressed = true;
        auto request = scoped.clock.prepareWallSampleRequestForTest(scoped.owner, suppressed);
        EXPECT_FALSE(suppressed);
        EXPECT_TRUE(request.force_unowned_ordinary);
        auto* block = scoped.profiler->blockTracker()->slotForId(scoped.owner->filterSlotId());
        EXPECT_EQ(3ULL, block->unowned_blocked_pending_weight.load());
        EXPECT_EQ(5ULL, block->unowned_blocked_decision_count.load());
        EXPECT_EQ(unavailable + 1, Counters::getCounter(WC_UNOWNED_CONTEXT_SNAPSHOT_UNAVAILABLE));
    });
    worker.get();
}

TEST(UnownedWallAttributionTest, ReusedIdentityCannotJustifySuppression) {
    auto worker = std::async(std::launch::async, [] {
        ScopedUnownedAttributionOwner scoped;
        u64 id = 0;
        ASSERT_NO_FATAL_FAILURE(scoped.primeOrigin(113, id));
        auto* registry = scoped.profiler->threadFilter();
        const int slot_id = scoped.owner->filterSlotId();
        const u64 generation = registry->slotForId(slot_id)->lifecycleGeneration();
        BaseWallClock::setUnownedContextProbeHookForTest(+[](void* arg) {
            auto* scoped = static_cast<ScopedUnownedAttributionOwner*>(arg);
            auto* registry = scoped->profiler->threadFilter();
            registry->unregisterThread(scoped->owner->filterSlotId(), scoped->owner->tid());
            EXPECT_EQ(scoped->owner->filterSlotId(), registry->registerThread(
                scoped->owner->tid(), scoped->owner->logicalContextWindowState()));
        }, &scoped);
        bool suppressed = true;
        auto request = scoped.clock.prepareWallSampleRequestForTest(scoped.owner, suppressed);
        EXPECT_FALSE(suppressed);
        EXPECT_FALSE(request.unowned_sample);
        EXPECT_FALSE(request.flush_tail);
        EXPECT_NE(generation, registry->slotForId(slot_id)->lifecycleGeneration());
        auto* block = scoped.profiler->blockTracker()->slotForId(slot_id);
        EXPECT_EQ(0ULL, block->unowned_blocked_pending_weight.load());
        EXPECT_EQ(0ULL, block->unowned_blocked_decision_count.load());
    });
    worker.get();
}

TEST(UnownedWallAttributionTest, FreshOwnerRejectsPriorRecordingEncodings) {
    int previous_slot = -1;
    u64 previous_publication = 0;
    auto first = std::async(std::launch::async, [&] {
        ScopedUnownedAttributionOwner scoped;
        u64 id = 0;
        ASSERT_NO_FATAL_FAILURE(scoped.primeOrigin(113, id));
        previous_slot = scoped.owner->filterSlotId();
        Context retained{};
        ASSERT_TRUE(scoped.profiler->blockTracker()->readUnownedContext(
            previous_slot, retained, previous_publication));
        ASSERT_EQ(113U, retained.getTag(0));
    });
    first.get();
    ASSERT_GE(previous_slot, 0);
    ASSERT_GT(previous_publication, 0ULL);

    auto second = std::async(std::launch::async, [&] {
        ScopedUnownedAttributionOwner scoped;
        ASSERT_NE(nullptr, scoped.owner);
        const int slot_id = scoped.owner->filterSlotId();
        ASSERT_EQ(previous_slot, slot_id);
        auto* tracker = scoped.profiler->blockTracker();
        auto* block = tracker->slotForId(slot_id);
        ASSERT_NE(nullptr, block);
        EXPECT_EQ(0ULL, block->unowned_blocked_call_trace_id.load());
        EXPECT_EQ(0ULL, block->unowned_blocked_pending_weight.load());
        EXPECT_EQ(0ULL, block->unowned_blocked_decision_count.load());
        Context retained{};
        u64 publication = 0;
        EXPECT_FALSE(tracker->readUnownedContext(slot_id, retained, publication));
        EXPECT_EQ(0U, ContextApi::snapshot().getTag(0));

        u64 id = 0;
        ASSERT_NO_FATAL_FAILURE(scoped.primeOrigin(227, id, 1));
        ASSERT_TRUE(tracker->readUnownedContext(slot_id, retained, publication));
        EXPECT_GT(publication, previous_publication);
        EXPECT_EQ(0ULL, retained.spanId);
        EXPECT_EQ(0ULL, retained.rootSpanId);
        EXPECT_EQ(227U, retained.getTag(0));
        EXPECT_EQ(0ULL, block->unowned_blocked_pending_weight.load());
        EXPECT_EQ(1ULL, block->unowned_blocked_decision_count.load());
    });
    second.get();
}

class WallClockSampleTransactionTest : public ::testing::Test {
public:
    std::unique_ptr<Profiler> profiler;
    WallSampleRequest request;
    u64 id = 0;
    int writes = 0;
    bool ordinary_ok = true;
    bool tail_ok = true;
    u64 emitted_weight = 0;
    void (*during_write)(WallClockSampleTransactionTest*) = nullptr;

    static bool write(u32 stripe, u64 trace_id, Event* event, const Context* context, void* arg) {
        auto* self = static_cast<WallClockSampleTransactionTest*>(arg);
        auto* sample = static_cast<ExecutionEvent*>(event);
        ++self->writes;
        if (self->during_write != nullptr) self->during_write(self);
        if (sample->_thread_state == OSThreadState::SLEEPING) {
            EXPECT_EQ(self->id, trace_id);
            EXPECT_EQ(2ULL, sample->_weight);
            if (self->tail_ok) self->emitted_weight += sample->_weight;
            return self->tail_ok;
        }
        return self->ordinary_ok;
    }

    void SetUp() override {
        ProfiledThread::initCurrentThreadSignalSafe();
        profiler = std::make_unique<Profiler>();
        profiler->blockTracker()->setUnownedContextSnapshotsNeeded(true);
        auto* registry = profiler->threadFilter();
        registry->init("enabled");
        request.tid = 7991;
        request.slot_id = registry->registerThread(request.tid);
        ASSERT_GE(request.slot_id, 0);
        auto* identity = registry->slotForId(request.slot_id);
        request.lifecycle_generation = identity->lifecycleGeneration();
        request.registry_epoch = registry->recordingEpoch();
        request.trace_epoch = profiler->recordingEpoch();
        request.sampling_epoch_start = TSC::ticks();
        request.flush_tail = true;
        request.context_captured = true;
        ASGCT_CallFrame frame{};
        frame.method_id = (jmethodID)0x7991;
        id = profiler->callTraceStorageForTest()->put(1, &frame, false, 1);
        ASSERT_TRUE(profiler->blockTracker()->publishUnownedTrace(
            request.slot_id, id, OSThreadState::SLEEPING, request.context));
        Context retained{};
        ASSERT_TRUE(profiler->blockTracker()->readUnownedContext(
            request.slot_id, retained, request.context_publication));
        auto* block = profiler->blockTracker()->slotForId(request.slot_id);
        ASSERT_TRUE(block->shouldRecordUnownedBlockedSample());
        ASSERT_FALSE(block->shouldRecordUnownedBlockedSample(false, false));
        ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(
            request.slot_id, request.sampling_epoch_start));
        ASSERT_FALSE(block->shouldRecordUnownedBlockedSample(false, false));
        ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(
            request.slot_id, request.sampling_epoch_start));
        profiler->sampleWriteHookForTest = write;
        profiler->sampleWriteHookArgForTest = this;
    }

    WallSampleResult sample() {
        ExecutionEvent event;
        event._thread_state = OSThreadState::RUNNABLE;
        event._execution_mode = ExecutionMode::JAVA;
        event._weight = 1;
        return profiler->recordWallSample(nullptr, 1, id, &event, request);
    }

    WallClockBlockTracker::BlockState* block() {
        return profiler->blockTracker()->slotForId(request.slot_id);
    }

    void expectTailRetained() {
        auto* block = profiler->blockTracker()->slotForId(request.slot_id);
        EXPECT_EQ(id, block->unowned_blocked_call_trace_id.load());
        EXPECT_EQ(2ULL, block->unowned_blocked_pending_weight.load());
        EXPECT_EQ(3ULL, block->unowned_blocked_decision_count.load());
        EXPECT_EQ(OSThreadState::SLEEPING, block->unowned_blocked_state.load());
    }
};

class UnownedAttributionRotationTest : public WallClockSampleTransactionTest {
public:
    static constexpr u32 ORIGIN_TAGS[3] = {113, 130, 147};
    static constexpr u32 CURRENT_TAGS[3] = {227, 256, 285};
    Context origin{};
    Context current{};
    u64 current_id = 0;
    u64 expected_tail_id = 0;
    u64 expected_tail_weight = 0;
    u64 origin_publication = 0;
    int ordinary_writes = 0;
    int tail_writes = 0;

    void SetUp() override {
        ASSERT_NO_FATAL_FAILURE(WallClockSampleTransactionTest::SetUp());
        for (int i = 0; i < 3; ++i) {
            origin.setTag(i, ORIGIN_TAGS[i]);
            current.setTag(i, CURRENT_TAGS[i]);
        }
        request.context = current;
        request.unowned_sample = true;
        request.observed_state = OSThreadState::RUNNABLE;
        profiler->sampleWriteHookForTest = writeAttribution;
        profiler->sampleWriteHookArgForTest = this;
    }

    static void expectFields(const Context& context, const u32 (&tags)[3]) {
        EXPECT_EQ(0ULL, context.spanId);
        EXPECT_EQ(0ULL, context.rootSpanId);
        for (int i = 0; i < DD_TAGS_CAPACITY; ++i) {
            EXPECT_EQ(i < 3 ? tags[i] : 0U, context.getTag(i)) << "tag=" << i;
        }
    }

    void primeRoot(int observations) {
        auto* tracker = profiler->blockTracker();
        tracker->resetSlot(request.slot_id, OSThreadState::UNKNOWN);
        ASSERT_TRUE(block()->shouldRecordUnownedBlockedSample());
        ASSERT_TRUE(tracker->publishUnownedTrace(
            request.slot_id, id, OSThreadState::SLEEPING, origin));
        for (int observation = 1; observation < observations; ++observation) {
            ASSERT_FALSE(block()->shouldRecordUnownedBlockedSample(false, false));
        ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(
            request.slot_id, request.sampling_epoch_start));
        }
        Context retained{};
        ASSERT_TRUE(tracker->readUnownedContext(
            request.slot_id, retained, origin_publication));
        expectFields(retained, ORIGIN_TAGS);
        request.context_publication = origin_publication;
        expected_tail_id = id;
        expected_tail_weight = observations - 1;
    }

    WallSampleResult boundary() {
        ASGCT_CallFrame frame{};
        frame.bci = 40;
        frame.method_id = (jmethodID)0x7992;
        current_id = profiler->callTraceStorageForTest()->put(1, &frame, false, 1);
        if (current_id == 0 || current_id == CallTraceStorage::DROPPED_TRACE_ID || current_id == id) {
            ADD_FAILURE() << "Current observation needs a fresh resolvable trace";
            return {};
        }
        ExecutionEvent event;
        event._thread_state = OSThreadState::RUNNABLE;
        event._execution_mode = ExecutionMode::JAVA;
        event._weight = 1;
        return profiler->recordWallSample(nullptr, 1, current_id, &event, request);
    }

    static bool writeAttribution(u32, u64 trace_id, Event* event,
                                 const Context* context, void* arg) {
        auto* self = static_cast<UnownedAttributionRotationTest*>(arg);
        auto* sample = static_cast<ExecutionEvent*>(event);
        EXPECT_NE(nullptr, context);
        if (context == nullptr) return false;
        if (sample->_thread_state == OSThreadState::SLEEPING) {
            ++self->tail_writes;
            EXPECT_EQ(self->expected_tail_id, trace_id);
            EXPECT_EQ(self->expected_tail_weight, sample->_weight);
            expectFields(*context, ORIGIN_TAGS);
        } else {
            ++self->ordinary_writes;
            EXPECT_EQ(OSThreadState::RUNNABLE, sample->_thread_state);
            EXPECT_EQ(self->current_id, trace_id);
            EXPECT_EQ(1ULL, sample->_weight);
            expectFields(*context, CURRENT_TAGS);
        }
        return true;
    }
};

class LivenessTrackerTestAccessor {
public:
    static void collectLiveTraceIds(CallTraceIdSet& live) {
        LivenessTracker::instance()->getLiveTraceIds(live);
    }
};

TEST_F(UnownedAttributionRotationTest, ZeroWeightOriginKeepsFieldsAcrossThreeRotations) {
    ASSERT_NO_FATAL_FAILURE(primeRoot(1));
    profiler->registerLivenessChecker([](CallTraceIdSet& live) {
        LivenessTrackerTestAccessor::collectLiveTraceIds(live);
    });
    for (int dump = 0; dump < 3; ++dump) {
        bool found = false;
        profiler->processCallTraces([&](const CallTraceSet& traces) {
            for (auto* trace : traces) {
                if (trace->trace_id != id) continue;
                found = true;
                ASSERT_EQ(1, trace->num_frames);
                EXPECT_EQ((jmethodID)0x7991, trace->frames[0].method_id);
            }
        });
        ASSERT_TRUE(found) << "dump=" << dump;
        EXPECT_EQ(id, block()->unowned_blocked_call_trace_id.load());
        EXPECT_EQ(0ULL, block()->unowned_blocked_pending_weight.load());
        EXPECT_EQ(1ULL, block()->unowned_blocked_decision_count.load());
        Context retained{};
        u64 publication = 0;
        ASSERT_TRUE(profiler->blockTracker()->readUnownedContext(
            request.slot_id, retained, publication));
        EXPECT_EQ(origin_publication, publication);
        expectFields(retained, ORIGIN_TAGS);
    }
    ASSERT_FALSE(block()->shouldRecordUnownedBlockedSample(false, false));
        ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(
            request.slot_id, request.sampling_epoch_start));
    EXPECT_EQ(1ULL, block()->unowned_blocked_pending_weight.load());
    EXPECT_EQ(2ULL, block()->unowned_blocked_decision_count.load());
    expected_tail_weight = 1;
    const auto result = boundary();
    EXPECT_TRUE(result.ordinary_recorded);
    EXPECT_TRUE(result.tail_recorded);
    EXPECT_EQ(1, ordinary_writes);
    EXPECT_EQ(1, tail_writes);
    EXPECT_EQ(0ULL, block()->unowned_blocked_pending_weight.load());
}

TEST_F(UnownedAttributionRotationTest, ConfirmedDroppedRootKeepsOriginalFieldsAndWeight) {
    ASSERT_NO_FATAL_FAILURE(primeRoot(4));
    const u64 failures = Counters::getCounter(WC_UNOWNED_BLOCKED_TRACE_PRESERVATION_FAILED);
    {
        ScopedPreservationCopyFailure failure(id);
        profiler->processCallTraces([](const CallTraceSet&) {});
    }
    EXPECT_EQ(failures + 1, Counters::getCounter(WC_UNOWNED_BLOCKED_TRACE_PRESERVATION_FAILED));
    EXPECT_EQ(CallTraceStorage::DROPPED_TRACE_ID,
              block()->unowned_blocked_call_trace_id.load());
    EXPECT_EQ(3ULL, block()->unowned_blocked_pending_weight.load());
    EXPECT_EQ(4ULL, block()->unowned_blocked_decision_count.load());
    Context retained{};
    u64 publication = 0;
    ASSERT_TRUE(profiler->blockTracker()->readUnownedContext(
        request.slot_id, retained, publication));
    EXPECT_EQ(origin_publication, publication);
    UnownedAttributionRotationTest::expectFields(retained, ORIGIN_TAGS);
    profiler->processCallTraces([](const CallTraceSet&) {});
    EXPECT_EQ(failures + 1, Counters::getCounter(WC_UNOWNED_BLOCKED_TRACE_PRESERVATION_FAILED));
    expected_tail_id = CallTraceStorage::DROPPED_TRACE_ID;
    const auto result = boundary();
    EXPECT_TRUE(result.ordinary_recorded);
    EXPECT_TRUE(result.tail_recorded);
    EXPECT_EQ(1, ordinary_writes);
    EXPECT_EQ(1, tail_writes);
    EXPECT_EQ(0ULL, block()->unowned_blocked_pending_weight.load());
}

TEST_F(WallClockSampleTransactionTest, OrdinaryNoSlotCacheReuseWritesEveryWeightOneTick) {
    auto* retained = block();
    request = WallSampleRequest{};
    request.tid = 7991;
    request.trace_epoch = profiler->recordingEpoch();
    profiler->sampleWriteHookForTest =
        +[](u32, u64 trace_id, Event* event, const Context* context, void* arg) {
            auto* self = static_cast<WallClockSampleTransactionTest*>(arg);
            auto* sample = static_cast<ExecutionEvent*>(event);
            EXPECT_EQ(self->id, trace_id);
            EXPECT_EQ(nullptr, context);
            EXPECT_EQ(OSThreadState::RUNNABLE, sample->_thread_state);
            EXPECT_EQ(1ULL, sample->_weight);
            ++self->writes;
            self->emitted_weight += sample->_weight;
            return true;
        };
    for (int tick = 0; tick < 2; ++tick) {
        const auto result = sample();
        EXPECT_TRUE(result.ordinary_recorded);
        EXPECT_FALSE(result.tail_recorded);
    }
    EXPECT_EQ(2, writes);
    EXPECT_EQ(2ULL, emitted_weight);
    EXPECT_EQ(id, retained->unowned_blocked_call_trace_id.load());
    EXPECT_EQ(2ULL, retained->unowned_blocked_pending_weight.load());
    EXPECT_EQ(3ULL, retained->unowned_blocked_decision_count.load());
}

TEST_F(WallClockSampleTransactionTest, StripeExhaustionKeepsTail) {
    WallSampleResult result;
    {
        auto locks = profiler->recordingLocksForTest();
        result = sample();
    }
    EXPECT_FALSE(result.ordinary_recorded);
    EXPECT_FALSE(result.tail_recorded);
    EXPECT_EQ(0, writes);
    expectTailRetained();
}

TEST_F(WallClockSampleTransactionTest, OrdinaryWriteSuccessDoesNotConsumeRejectedTail) {
    tail_ok = false;
    const auto result = sample();
    EXPECT_TRUE(result.ordinary_recorded);
    EXPECT_FALSE(result.tail_recorded);
    expectTailRetained();
    tail_ok = true;
    EXPECT_TRUE(sample().tail_recorded);
    EXPECT_FALSE(sample().tail_recorded);
    EXPECT_EQ(2ULL, emitted_weight);
}

TEST_F(WallClockSampleTransactionTest, TailSuccessAfterOrdinaryRejectionCommitsOnce) {
    ordinary_ok = false;
    const auto result = sample();
    EXPECT_FALSE(result.ordinary_recorded);
    EXPECT_TRUE(result.tail_recorded);
    EXPECT_FALSE(sample().tail_recorded);
    EXPECT_EQ(2ULL, emitted_weight);
}

TEST_F(WallClockSampleTransactionTest, RejectedWritesKeepTail) {
    ordinary_ok = false;
    tail_ok = false;
    const auto result = sample();
    EXPECT_FALSE(result.ordinary_recorded);
    EXPECT_FALSE(result.tail_recorded);
    expectTailRetained();
}

TEST_F(WallClockSampleTransactionTest, FailedBlockedWriteRestoresOnlySuppressedWeight) {
    request.flush_tail = false;
    request.unowned_sample = true;
    request.observed_state = OSThreadState::CONDVAR_WAIT;
    ordinary_ok = false;
    EXPECT_FALSE(sample().ordinary_recorded);
    expectTailRetained();
    ordinary_ok = true;
    EXPECT_TRUE(sample().ordinary_recorded);
    EXPECT_EQ(0ULL, block()->unowned_blocked_pending_weight.load());
    EXPECT_EQ(id, block()->unowned_blocked_call_trace_id.load());
    EXPECT_EQ(OSThreadState::CONDVAR_WAIT, block()->unowned_blocked_state.load());
}

class UnownedBoundaryTransactionTest : public WallClockSampleTransactionTest,
                                       public ::testing::WithParamInterface<int> {
public:
    u64 current_id = 0;
    unsigned ordinary_writes = 0;
    unsigned tail_writes = 0;
    static bool writeBoundary(u32, u64 trace_id, Event* event, const Context* context, void* arg) {
        auto* self = static_cast<UnownedBoundaryTransactionTest*>(arg);
        auto* sample = static_cast<ExecutionEvent*>(event);
        EXPECT_NE(nullptr, context);
        if (sample->_thread_state == OSThreadState::SLEEPING) {
            ++self->tail_writes;
            EXPECT_EQ(self->id, trace_id);
            EXPECT_EQ(3ULL, sample->_weight);
            if (context != nullptr) EXPECT_EQ(113U, context->getTag(0));
            return self->tail_ok;
        }
        ++self->ordinary_writes;
        EXPECT_EQ(self->current_id, trace_id);
        EXPECT_EQ(1ULL, sample->_weight);
        if (context != nullptr) EXPECT_EQ(227U, context->getTag(0));
        return self->ordinary_ok;
    }
    void SetUp() override {
        WallClockSampleTransactionTest::SetUp();
        Context original{};
        original.setTag(0, 113);
        ASSERT_TRUE(profiler->blockTracker()->publishUnownedTrace(
            request.slot_id, id, OSThreadState::SLEEPING, original));
        ASSERT_FALSE(block()->shouldRecordUnownedBlockedSample(false, false));
        ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(
            request.slot_id, request.sampling_epoch_start));
        ASSERT_EQ(3ULL, block()->unowned_blocked_pending_weight.load());
        request.unowned_sample = true;
        request.observed_state = OSThreadState::CONDVAR_WAIT;
        request.force_unowned_ordinary = true;
        request.context.setTag(0, 227);
        ASGCT_CallFrame frame{};
        frame.bci = 49;
        frame.method_id = (jmethodID)0x7993;
        current_id = profiler->callTraceStorageForTest()->put(1, &frame, false, 1);
        ASSERT_GT(current_id >> 32, 0ULL);
        ASSERT_NE(id, current_id);
        profiler->sampleWriteHookForTest = writeBoundary;
        profiler->sampleWriteHookArgForTest = this;
    }
};

TEST_P(UnownedBoundaryTransactionTest, BoundaryWriteOutcomes) {
    ordinary_ok = (GetParam() & 1) != 0;
    tail_ok = (GetParam() & 2) != 0;
    ExecutionEvent event;
    event._thread_state = OSThreadState::CONDVAR_WAIT;
    event._execution_mode = ExecutionMode::JAVA;
    event._weight = 1;
    auto result = profiler->recordWallSample(nullptr, 1, current_id, &event, request);
    EXPECT_EQ(ordinary_ok, result.ordinary_recorded);
    EXPECT_EQ(tail_ok, result.tail_recorded);
    EXPECT_EQ(1U, ordinary_writes);
    EXPECT_EQ(1U, tail_writes);
    EXPECT_EQ(tail_ok ? 0ULL : 3ULL, block()->unowned_blocked_pending_weight.load());
    EXPECT_EQ(4ULL, block()->unowned_blocked_decision_count.load());
    EXPECT_EQ(tail_ok ? (ordinary_ok ? current_id : 0ULL) : id,
              block()->unowned_blocked_call_trace_id.load());
    Context retained{};
    u64 sequence = 0;
    if (!tail_ok || ordinary_ok) {
        ASSERT_TRUE(profiler->blockTracker()->readUnownedContext(request.slot_id, retained, sequence));
        EXPECT_EQ(tail_ok ? 227U : 113U, retained.getTag(0));
    }
}

INSTANTIATE_TEST_SUITE_P(IndependentWrites, UnownedBoundaryTransactionTest, ::testing::Values(0, 1, 2, 3));

TEST_F(WallClockSampleTransactionTest, FreshRecordingClearsRootsButKeepsCollector) {
    ASSERT_EQ(0ULL, request.registry_epoch);
    ASSERT_EQ(0, profiler->resetRecordingStateForTest());
    EXPECT_EQ(0ULL, block()->unowned_blocked_call_trace_id.load());
    EXPECT_EQ(0ULL, block()->unowned_blocked_pending_weight.load());
    EXPECT_EQ(0ULL, block()->unowned_blocked_decision_count.load());
    bool old_root_found = false;
    profiler->processCallTraces([&](const CallTraceSet& traces) {
        for (auto* trace : traces) if (trace->trace_id == id) old_root_found = true;
    });
    EXPECT_FALSE(old_root_found);
    ASGCT_CallFrame frame{};
    frame.bci = 47;
    frame.method_id = (jmethodID)0x7992;
    const u64 fresh = profiler->callTraceStorageForTest()->put(1, &frame, false, 1);
    ASSERT_GT(fresh >> 32, 0ULL);
    ASSERT_NE(id, fresh);
    profiler->blockTracker()->publishUnownedTrace(request.slot_id, fresh, OSThreadState::SLEEPING);
    for (int dump = 0; dump < 3; ++dump) {
        bool found = false;
        profiler->processCallTraces([&](const CallTraceSet& traces) {
            for (auto* trace : traces) {
                if (trace->trace_id == fresh) {
                    found = true;
                    EXPECT_EQ(47, trace->frames[0].bci);
                    EXPECT_EQ(frame.method_id, trace->frames[0].method_id);
                }
            }
        });
        EXPECT_TRUE(found);
    }
}

TEST_F(WallClockSampleTransactionTest, AbsentRootKeepsWeightWithResolvableDroppedMarker) {
    const long long failures_before =
        Counters::getCounter(WC_UNOWNED_BLOCKED_TRACE_PRESERVATION_FAILED);
    {
        auto locks = profiler->recordingLocksForTest();
        // Quiescent fault injection: no source table now contains the cached ID.
        profiler->callTraceStorageForTest()->clear();
        profiler->processCallTraces([](const CallTraceSet&) {});
    }
    EXPECT_EQ(failures_before + 1,
              Counters::getCounter(WC_UNOWNED_BLOCKED_TRACE_PRESERVATION_FAILED));
    id = CallTraceStorage::DROPPED_TRACE_ID;
    expectTailRetained();
    bool marker_resolves = false;
    profiler->processCallTraces([&](const CallTraceSet& traces) {
        for (auto* trace : traces) if (trace->trace_id == id) marker_resolves = true;
    });
    EXPECT_TRUE(marker_resolves);
    EXPECT_EQ(failures_before + 1,
              Counters::getCounter(WC_UNOWNED_BLOCKED_TRACE_PRESERVATION_FAILED));
    EXPECT_TRUE(sample().tail_recorded);
    EXPECT_FALSE(sample().tail_recorded);
    EXPECT_EQ(2ULL, emitted_weight);
}

TEST_F(WallClockSampleTransactionTest, StaleIdentityCannotConsumeOrPublish) {
    profiler->threadFilter()->unregisterThread(request.slot_id, request.tid);
    ASSERT_EQ(request.slot_id, profiler->threadFilter()->registerThread(request.tid + 1));
    profiler->blockTracker()->publishUnownedTrace(request.slot_id, id, OSThreadState::SLEEPING);
    ASSERT_TRUE(block()->shouldRecordUnownedBlockedSample());
    ASSERT_FALSE(block()->shouldRecordUnownedBlockedSample(false, false));
        ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(
            request.slot_id, request.sampling_epoch_start));
    const auto result = sample();
    EXPECT_TRUE(result.ordinary_recorded);
    EXPECT_FALSE(result.tail_recorded);
    EXPECT_EQ(1ULL, block()->unowned_blocked_pending_weight.load());
    EXPECT_EQ(id, block()->unowned_blocked_call_trace_id.load());
}

TEST_F(WallClockSampleTransactionTest, ResetDuringFailedWriteDoesNotRestorePredecessorWeight) {
    request.flush_tail = false;
    request.unowned_sample = true;
    ordinary_ok = false;
    during_write = +[](WallClockSampleTransactionTest* self) {
        auto* registry = self->profiler->threadFilter();
        registry->unregisterThread(self->request.slot_id, self->request.tid);
        EXPECT_EQ(self->request.slot_id, registry->registerThread(self->request.tid + 1));
    };
    EXPECT_FALSE(sample().ordinary_recorded);
    EXPECT_EQ(0ULL, block()->unowned_blocked_pending_weight.load());
    EXPECT_EQ(0ULL, block()->unowned_blocked_call_trace_id.load());
    EXPECT_EQ(0ULL, block()->unowned_blocked_decision_count.load());
}

// This hook runs on an ordinary native test thread, never in a signal handler.
// The dump thread announces its attempt before trying all production stripes.
TEST_F(WallClockSampleTransactionTest, PublishedRootPrecedesDumpSnapshot) {
    request.flush_tail = false;
    request.unowned_sample = true;
    request.observed_state = OSThreadState::CONDVAR_WAIT;
    block()->resetUnownedBlockedSampling();
    std::mutex mutex;
    std::condition_variable cv;
    bool write_entered = false;
    bool dump_attempted = false;
    bool snapshot_taken = false;
    struct Schedule {
        std::mutex* mutex;
        std::condition_variable* cv;
        bool* write_entered;
        bool* dump_attempted;
        bool* snapshot_taken;
    } schedule{&mutex, &cv, &write_entered, &dump_attempted, &snapshot_taken};
    // Reuse the actual serializer boundary, not a fixture transaction model.
    profiler->sampleWriteHookArgForTest = &schedule;
    profiler->sampleWriteHookForTest = +[](u32, u64, Event*, const Context*, void* arg) {
        auto* s = static_cast<Schedule*>(arg);
        std::unique_lock<std::mutex> lock(*s->mutex);
        *s->write_entered = true;
        s->cv->notify_all();
        s->cv->wait(lock, [&] { return *s->dump_attempted; });
        EXPECT_FALSE(*s->snapshot_taken);
        return true;
    };
    std::thread dump([&] {
        ProfiledThread::initCurrentThreadSignalSafe();
        {
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock, [&] { return write_entered; });
            dump_attempted = true;
            cv.notify_all();
        }
        auto locks = profiler->recordingLocksForTest();
        {
            std::lock_guard<std::mutex> lock(mutex);
            snapshot_taken = true;
        }
        profiler->processCallTraces([](const CallTraceSet&) {});
    });
    const auto result = sample();
    dump.join();
    EXPECT_TRUE(result.ordinary_recorded);
    EXPECT_TRUE(snapshot_taken);
    bool found = false;
    profiler->processCallTraces([&](const CallTraceSet& traces) {
        for (auto* trace : traces) if (trace->trace_id == id) found = true;
    });
    EXPECT_TRUE(found);
}

TEST_F(WallClockSampleTransactionTest, DumpExcludesDeferredConsumeAndEmission) {
    bool found = false;
    {
        auto locks = profiler->recordingLocksForTest();
        const auto excluded = sample();
        EXPECT_FALSE(excluded.tail_recorded);
        expectTailRetained();
        profiler->processCallTraces([&](const CallTraceSet& traces) {
            for (auto* trace : traces) if (trace->trace_id == id) found = true;
        });
    }
    EXPECT_TRUE(found);
    during_write = +[](WallClockSampleTransactionTest* self) { self->expectTailRetained(); };
    EXPECT_TRUE(sample().tail_recorded);
    during_write = nullptr;
    EXPECT_EQ(0ULL, block()->unowned_blocked_call_trace_id.load());
    EXPECT_FALSE(sample().tail_recorded);
    EXPECT_EQ(2ULL, emitted_weight);
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

// Derive each scale from the actual filtered population and production reservoir.
TEST(UnownedWallAttributionTest, RetainedTailKeepsEffectiveWeightAcrossPopulationChanges) {
    for (const auto& pools : {std::pair<int, int>{16, 160}, {160, 16}}) {
        auto worker = std::async(std::launch::async, [pools] {
            ScopedUnownedAttributionOwner scoped;
            auto* registry = scoped.profiler->threadFilter();
            std::vector<int> extras;
            auto populate = [&](int count) {
                for (int id : extras) registry->unregisterThread(id);
                extras.clear();
                for (int i = 1; i < count; ++i) {
                    int tid = 9000000 + i;
                    int id = registry->registerThread(tid);
                    ASSERT_GE(id, 0);
                    ASSERT_TRUE(registry->add(tid, id));
                    extras.push_back(id);
                }
            };
            auto scale = [&] {
                std::vector<ThreadEntry> entries;
                registry->collect(entries);
                ReservoirSampler<ThreadEntry> reservoir(16, 1);
                return static_cast<double>(entries.size()) / reservoir.sample(entries).size();
            };
            populate(pools.first);
            double original_scale = scale();
            const u64 original_time = TSC::ticks();
            WallClockCounters::beginSamplingEpoch(original_time);
            u64 id = 0;
            ASSERT_NO_FATAL_FAILURE(scoped.primeOrigin(113, id, 10));
            registry->onContextWindowExit(*scoped.owner);
            populate(pools.second);
            registry->onContextWindowEnter(*scoped.owner);
            scoped.setTag(227);
            const u64 boundary = TSC::ticks();
            WallClockCounters::beginSamplingEpoch(boundary);
            ASSERT_GT(boundary, original_time);
            double later_scale = scale();
            struct Writes {
                u64 boundary;
                double original_scale, later_scale, effective = 0;
                int tails = 0;
            } writes{boundary, original_scale, later_scale};
            scoped.profiler->sampleWriteHookArgForTest = &writes;
            scoped.profiler->sampleWriteHookForTest = +[](u32, u64, Event* raw,
                                                         const Context* context, void* arg) {
                auto* sample = static_cast<ExecutionEvent*>(raw);
                auto* writes = static_cast<Writes*>(arg);
                if (sample->_thread_state != OSThreadState::SLEEPING) return true;
                ++writes->tails;
                EXPECT_NE(nullptr, context);
                if (context != nullptr) EXPECT_EQ(113U, context->getTag(0));
                u64 timestamp = sample->_sample_ticks != 0 ? sample->_sample_ticks : TSC::ticks();
                EXPECT_LT(timestamp, writes->boundary) << "Tail must retain its original epoch timestamp";
                writes->effective += sample->_weight * (timestamp < writes->boundary
                    ? writes->original_scale : writes->later_scale);
                return true;
            };
            bool suppressed = false;
            auto request = scoped.clock.prepareWallSampleRequestForTest(scoped.owner, suppressed);
            request.unowned_sample = false;
            request.flush_tail = true;
            ExecutionEvent event;
            event._thread_state = OSThreadState::RUNNABLE;
            auto result = scoped.profiler->recordWallSample(nullptr, 1, id, &event, request);
            EXPECT_TRUE(result.tail_recorded);
            EXPECT_EQ(1, writes.tails);
            EXPECT_DOUBLE_EQ(9 * original_scale, writes.effective)
                << "pool " << pools.first << " -> " << pools.second;
            for (int extra : extras) registry->unregisterThread(extra);
        });
        worker.get();
    }
}

TEST(UnownedWallAttributionTest, BoundedEpochSegmentsFailOpenAndCommitOnlySuccessfulWrites) {
    auto worker = std::async(std::launch::async, [] {
        ScopedUnownedAttributionOwner scoped;
        u64 id = 0;
        ASSERT_NO_FATAL_FAILURE(scoped.primeOrigin(113, id));
        u64 epochs[WallClockBlockTracker::kMaxWeightSegments];
        epochs[0] = WallClockCounters::samplingEpochStart();
        bool suppressed = false;
        for (size_t i = 1; i < WallClockBlockTracker::kMaxWeightSegments; ++i) {
            epochs[i] = TSC::ticks();
            ASSERT_GT(epochs[i], epochs[i - 1]);
            WallClockCounters::beginSamplingEpoch(epochs[i]);
            scoped.clock.prepareWallSampleRequestForTest(scoped.owner, suppressed);
            ASSERT_TRUE(suppressed);
        }
        WallClockCounters::beginSamplingEpoch(TSC::ticks());
        auto request = scoped.clock.prepareWallSampleRequestForTest(scoped.owner, suppressed);
        ASSERT_FALSE(suppressed) << "Full provenance storage must record the current observation";
        auto* block = scoped.profiler->blockTracker()->slotForId(scoped.owner->filterSlotId());
        ASSERT_EQ(6ULL, block->unowned_blocked_pending_weight.load());
        const u64 recorded_before = Counters::getCounter(WC_UNOWNED_BLOCKED_TAIL_RECORDED);
        struct Writes { u64 rejected; bool fail = true; u64 emitted = 0; int tails = 0; } writes{epochs[1]};
        scoped.profiler->sampleWriteHookArgForTest = &writes;
        scoped.profiler->sampleWriteHookForTest = +[](u32, u64, Event* raw, const Context* context, void* arg) {
            auto* writes = static_cast<Writes*>(arg);
            auto* event = static_cast<ExecutionEvent*>(raw);
            if (event->_execution_mode != ExecutionMode::UNKNOWN) {
                EXPECT_EQ(1ULL, event->_weight);
                return true;
            }
            ++writes->tails;
            EXPECT_NE(0ULL, event->_sample_ticks);
            EXPECT_NE(nullptr, context);
            if (context != nullptr) EXPECT_EQ(113U, context->getTag(0));
            if (writes->fail && event->_sample_ticks == writes->rejected) return false;
            writes->emitted += event->_weight;
            return true;
        };
        ExecutionEvent event;
        event._thread_state = OSThreadState::SLEEPING;
        event._execution_mode = ExecutionMode::JAVA;
        auto result = scoped.profiler->recordWallSample(nullptr, 1, id, &event, request);
        EXPECT_TRUE(result.ordinary_recorded);
        EXPECT_FALSE(result.tail_recorded);
        EXPECT_EQ(4, writes.tails);
        EXPECT_EQ(5ULL, writes.emitted);
        EXPECT_EQ(recorded_before + 3, Counters::getCounter(WC_UNOWNED_BLOCKED_TAIL_RECORDED));
        EXPECT_EQ(1ULL, block->unowned_blocked_pending_weight.load());
        scoped.setTag(227);
        request = scoped.clock.prepareWallSampleRequestForTest(scoped.owner, suppressed);
        ASSERT_FALSE(suppressed);
        writes.fail = false;
        result = scoped.profiler->recordWallSample(nullptr, 1, id, &event, request);
        EXPECT_TRUE(result.tail_recorded);
        EXPECT_EQ(5, writes.tails) << "Already committed segments must not be written again";
        EXPECT_EQ(6ULL, writes.emitted);
        EXPECT_EQ(recorded_before + 4, Counters::getCounter(WC_UNOWNED_BLOCKED_TAIL_RECORDED));
        EXPECT_EQ(0ULL, block->unowned_blocked_pending_weight.load());
    });
    worker.get();
}

TEST(UnownedWallAttributionTest, MissingSamplingEpochCannotAccumulateUnscaledWeight) {
    auto worker = std::async(std::launch::async, [] {
        ScopedUnownedAttributionOwner scoped;
        u64 id = 0;
        ASSERT_NO_FATAL_FAILURE(scoped.primeOrigin(113, id, 1));
        WallClockCounters::beginSamplingEpoch(0);
        bool suppressed = true;
        auto request = scoped.clock.prepareWallSampleRequestForTest(scoped.owner, suppressed);
        EXPECT_FALSE(suppressed);
        EXPECT_TRUE(request.unowned_sample);
        auto* block = scoped.profiler->blockTracker()->slotForId(scoped.owner->filterSlotId());
        EXPECT_EQ(0ULL, block->unowned_blocked_pending_weight.load());
    });
    worker.get();
}
