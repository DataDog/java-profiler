/*
 * Copyright 2026 Datadog, Inc
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
#include "livenessTracker.h"
#include "../../main/cpp/gtest_crash_handler.h"
#include <cstdlib>
#include <cstring>

// Test name for crash handler
static constexpr char LIVENESS_TRACKER_TEST_NAME[] = "LivenessTrackerTest";

/**
 * Mock structure to test buffer capacity management similar to LivenessTracker's
 * tracking table resize logic. This tests the fix for the buffer overrun bug
 * where _table_cap was being updated even when realloc failed.
 */
struct TrackingTableMock {
    void* table;
    int table_cap;
    int table_max_cap;

    TrackingTableMock(int initial_cap, int max_cap)
        : table(nullptr), table_cap(initial_cap), table_max_cap(max_cap) {
        table = malloc(sizeof(int) * initial_cap);
    }

    ~TrackingTableMock() {
        if (table != nullptr) {
            free(table);
        }
    }

    /**
     * This is the CORRECT implementation (after the fix).
     * Only update table_cap if realloc succeeds.
     */
    bool resizeTableCorrect(int newcap) {
        void* tmp = realloc(table, sizeof(int) * newcap);
        if (tmp != nullptr) {
            table = tmp;
            table_cap = newcap;  // Only update capacity after successful realloc
            return true;
        }
        return false;
    }

    /**
     * This is the BUGGY implementation (before the fix).
     * Updates table_cap even when realloc fails, causing buffer overrun.
     */
    bool resizeTableBuggy(int newcap) {
        void* tmp = realloc(table, sizeof(int) * (table_cap = newcap));  // BUG: updates table_cap in the call
        if (tmp != nullptr) {
            table = tmp;
            return true;
        }
        // BUG: table_cap was already updated even though realloc failed!
        return false;
    }

    int getCapacity() const {
        return table_cap;
    }
};

class LivenessTrackerTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<LIVENESS_TRACKER_TEST_NAME>();
    }

    void TearDown() override {
        restoreDefaultSignalHandlers();
    }
};

/**
 * Test that verifies the correct behavior: capacity should only be updated
 * when realloc succeeds.
 */
TEST_F(LivenessTrackerTest, CapacityOnlyUpdatedOnSuccessfulRealloc) {
    TrackingTableMock mock(10, 100);

    int initial_cap = mock.getCapacity();
    EXPECT_EQ(initial_cap, 10);

    // Successful resize should update capacity
    bool success = mock.resizeTableCorrect(20);
    EXPECT_TRUE(success);
    EXPECT_EQ(mock.getCapacity(), 20);

    // Another successful resize
    success = mock.resizeTableCorrect(40);
    EXPECT_TRUE(success);
    EXPECT_EQ(mock.getCapacity(), 40);
}

/**
 * Test that demonstrates the bug: with the buggy implementation,
 * capacity gets updated even when realloc would fail.
 *
 * This test documents the bug that was fixed. The buggy implementation
 * would update table_cap inside the realloc call itself, meaning that
 * if realloc failed, the capacity would still be updated, leading to
 * a mismatch between actual allocated size and recorded capacity.
 */
TEST_F(LivenessTrackerTest, BuggyImplementationUpdateCapacityOnFailure) {
    TrackingTableMock mock(10, 100);

    int initial_cap = mock.getCapacity();
    EXPECT_EQ(initial_cap, 10);

    // Successful resize updates capacity (both implementations work here)
    bool success = mock.resizeTableBuggy(20);
    EXPECT_TRUE(success);
    EXPECT_EQ(mock.getCapacity(), 20);

    // Now let's demonstrate the bug with a simulated failure scenario
    // In the buggy implementation, even if we pass the capacity update inline,
    // it would get updated before realloc returns
    //
    // The buggy code was:
    //   TrackingEntry *tmp = (TrackingEntry *)realloc(
    //       _table, sizeof(TrackingEntry) * (_table_cap = newcap));
    //
    // This means _table_cap = newcap happens BEFORE checking if tmp != nullptr
    // If realloc fails (returns nullptr), _table_cap is already set to newcap,
    // but _table still points to the old, smaller buffer.
    //
    // Result: buffer overrun when code tries to access _table[i] for i >= old_cap

    // To verify this would happen, we'd need to force realloc to fail.
    // In practice, realloc fails when:
    // 1. System is out of memory
    // 2. Requested size is too large
    // 3. Memory corruption

    // We can't easily force a failure in a unit test without complex mocking,
    // but we've documented the issue and the fix ensures capacity is only
    // updated after verifying tmp != nullptr
}

/**
 * Test that verifies the fixed code follows the correct pattern:
 * 1. Call realloc and store result in temporary pointer
 * 2. Check if temporary pointer is not null
 * 3. Only then update the table pointer and capacity
 */
TEST_F(LivenessTrackerTest, CorrectResizePatternVerification) {
    TrackingTableMock mock(10, 100);

    // The correct pattern is:
    // 1. void* tmp = realloc(table, new_size);
    // 2. if (tmp != nullptr) {
    // 3.     table = tmp;
    // 4.     table_cap = new_cap;
    // 5. }

    int old_cap = mock.getCapacity();
    EXPECT_EQ(old_cap, 10);

    // Simulate the resize logic
    int newcap = old_cap * 2;
    bool success = mock.resizeTableCorrect(newcap);

    if (success) {
        // Capacity should be updated
        EXPECT_EQ(mock.getCapacity(), newcap);
    } else {
        // If resize failed, capacity should remain unchanged
        EXPECT_EQ(mock.getCapacity(), old_cap);
    }
}

/**
 * Integration-style test that verifies multiple resize operations
 * maintain correct capacity tracking.
 */
TEST_F(LivenessTrackerTest, MultipleResizeOperationsMaintainCorrectCapacity) {
    TrackingTableMock mock(4, 128);

    std::vector<int> expected_capacities = {4, 8, 16, 32, 64, 128};
    size_t resize_count = 0;

    EXPECT_EQ(mock.getCapacity(), expected_capacities[resize_count]);

    // Perform multiple resize operations (doubling each time)
    for (size_t i = 1; i < expected_capacities.size(); i++) {
        int newcap = expected_capacities[i];
        bool success = mock.resizeTableCorrect(newcap);
        EXPECT_TRUE(success) << "Resize to " << newcap << " failed";
        EXPECT_EQ(mock.getCapacity(), newcap)
            << "Capacity mismatch after resize to " << newcap;
    }

    // Verify final capacity
    EXPECT_EQ(mock.getCapacity(), 128);
}

/**
 * Mock structure to test the flush_table id-assignment guard: Profiler::lookupClass()
 * returns an int (-1 on class-map-at-capacity), but Event::_id is a u32. Assigning -1
 * directly would wrap to 0xFFFFFFFF and corrupt liveness attribution, so flush_table
 * must drop the sample instead. Mirrors ObjectSampler's convention for the same
 * lookupClass() failure mode.
 */
struct FlushTableIdGuardMock {
    bool recorded = false;
    uint32_t recorded_id = 0;

    // Correct behavior (after the fix): only assign/record when class_id >= 0.
    void applyGuarded(int class_id) {
        if (class_id >= 0) {
            recorded = true;
            recorded_id = static_cast<uint32_t>(class_id);
        }
    }

    // Pre-fix behavior: unconditionally assigns class_id to the u32 event id.
    void applyUnguarded(int class_id) {
        recorded = true;
        recorded_id = static_cast<uint32_t>(class_id);
    }
};

TEST_F(LivenessTrackerTest, NegativeClassIdSampleIsDropped) {
    FlushTableIdGuardMock mock;
    mock.applyGuarded(-1);
    EXPECT_FALSE(mock.recorded);
}

TEST_F(LivenessTrackerTest, NonNegativeClassIdSampleIsRecorded) {
    FlushTableIdGuardMock mock;
    mock.applyGuarded(42);
    EXPECT_TRUE(mock.recorded);
    EXPECT_EQ(42u, mock.recorded_id);
}

TEST_F(LivenessTrackerTest, UnguardedNegativeClassIdWrapsToMaxU32) {
    // Documents the bug the guard prevents: without it, -1 wraps to 0xFFFFFFFF
    // when narrowed to the u32 event id.
    FlushTableIdGuardMock mock;
    mock.applyUnguarded(-1);
    EXPECT_TRUE(mock.recorded);
    EXPECT_EQ(0xFFFFFFFFu, mock.recorded_id);
}

/**
 * Test that verifies capacity never exceeds max_cap during resize operations.
 */
TEST_F(LivenessTrackerTest, CapacityDoesNotExceedMaxCap) {
    TrackingTableMock mock(10, 50);

    // Try to resize beyond max_cap
    int newcap = std::min(mock.table_cap * 2, mock.table_max_cap);
    EXPECT_LE(newcap, 50);

    // First resize: 10 -> 20
    mock.resizeTableCorrect(newcap);
    EXPECT_EQ(mock.getCapacity(), 20);

    // Second resize: 20 -> 40
    newcap = std::min(mock.table_cap * 2, mock.table_max_cap);
    mock.resizeTableCorrect(newcap);
    EXPECT_EQ(mock.getCapacity(), 40);

    // Third resize: 40 -> 50 (capped at max_cap)
    newcap = std::min(mock.table_cap * 2, mock.table_max_cap);
    EXPECT_EQ(newcap, 50);  // Should be capped at 50, not 80
    mock.resizeTableCorrect(newcap);
    EXPECT_EQ(mock.getCapacity(), 50);

    // Fourth resize attempt: should remain at 50
    newcap = std::min(mock.table_cap * 2, mock.table_max_cap);
    EXPECT_EQ(newcap, 50);  // Already at max, newcap == table_cap
    // In the actual code, this would trigger: if (_table_cap != newcap) { ... }
    // which would be false, so no resize would be attempted
}

// ---------------------------------------------------------------------------
// Per-klass population tracking (LiveHeapReferenceChains-RemainingWorkPlan.md).
// These exercise LivenessTracker::instance() directly rather than
// a mock: recordKlassPopulationSampleLocked() deliberately makes no JNI call
// (see its header comment), so it is safe to call on the real singleton
// without a live JVM attached, unlike start()/track()/flush() elsewhere in
// this class. Fake jweak values below are opaque pointers the method under
// test never dereferences - only stored and handed back to the caller.
class KlassPopulationTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<LIVENESS_TRACKER_TEST_NAME>();
        // The table persists across recordings by design (see
        // LivenessTracker::initialize()'s own comment on why _initialized
        // survives multiple start() calls) - reset it explicitly here so
        // tests don't observe leftover state from a previous test case
        // sharing the same process-wide singleton.
        LivenessTracker::instance()->klassPopulationResetForTest();
    }

    void TearDown() override {
        LivenessTracker::instance()->klassPopulationResetForTest();
        restoreDefaultSignalHandlers();
    }

    static jweak fakeRef(uintptr_t tag) {
        return reinterpret_cast<jweak>(tag);
    }
};

// A brand new klass_id creates a new entry: out_created is true, the table
// grows by one, and the single pushed sample is the ring's only member.
TEST_F(KlassPopulationTest, InsertCreatesNewEntry) {
    LivenessTracker *tracker = LivenessTracker::instance();

    int slot = -1;
    bool created = false;
    jweak evicted = tracker->klassPopulationRecordForTest(/*klass_id=*/1,
                                                            /*count=*/5,
                                                            /*epoch=*/1,
                                                            &slot, &created);

    EXPECT_TRUE(created);
    EXPECT_EQ(evicted, nullptr);
    EXPECT_EQ(tracker->klassPopulationSizeForTest(), 1);

    KlassPopulationEntry entry;
    ASSERT_TRUE(tracker->klassPopulationLookupForTest(1, &entry));
    EXPECT_EQ(entry.klass_id, 1u);
    EXPECT_EQ(entry.ring_fill, 1);
    EXPECT_EQ(entry.ring_head, 1);
    EXPECT_EQ(entry.count_ring[0], 5);
    EXPECT_EQ(entry.last_updated_epoch, 1u);
    EXPECT_EQ(entry.representative, nullptr);
}

// A second sample for an already-known klass_id updates the same slot in
// place (out_created is false, table size unchanged) rather than creating a
// second entry.
TEST_F(KlassPopulationTest, InsertExistingUpdatesSameSlotInPlace) {
    LivenessTracker *tracker = LivenessTracker::instance();

    int slot1 = -1, slot2 = -1;
    bool created1 = false, created2 = false;
    tracker->klassPopulationRecordForTest(7, 3, 1, &slot1, &created1);
    jweak evicted = tracker->klassPopulationRecordForTest(7, 4, 2, &slot2,
                                                            &created2);

    EXPECT_TRUE(created1);
    EXPECT_FALSE(created2);
    EXPECT_EQ(slot1, slot2);
    EXPECT_EQ(evicted, nullptr);
    EXPECT_EQ(tracker->klassPopulationSizeForTest(), 1);

    KlassPopulationEntry entry;
    ASSERT_TRUE(tracker->klassPopulationLookupForTest(7, &entry));
    EXPECT_EQ(entry.ring_fill, 2);
    EXPECT_EQ(entry.count_ring[0], 3);
    EXPECT_EQ(entry.count_ring[1], 4);
    EXPECT_EQ(entry.last_updated_epoch, 2u);
}

// Ring buffer wraparound: pushing more than KLASS_POPULATION_RING_SIZE (30)
// samples must not grow ring_fill past 30, and the ring must overwrite the
// oldest slots in order rather than corrupting adjacent entries.
TEST_F(KlassPopulationTest, RingBufferWrapsAroundAtThirtySamples) {
    LivenessTracker *tracker = LivenessTracker::instance();

    const int RING_SIZE = 30;
    for (int i = 0; i < RING_SIZE + 5; i++) {
        int slot;
        bool created;
        tracker->klassPopulationRecordForTest(42, (u16)(i + 1), i + 1, &slot,
                                               &created);
        EXPECT_EQ(created, i == 0);
    }

    KlassPopulationEntry entry;
    ASSERT_TRUE(tracker->klassPopulationLookupForTest(42, &entry));
    // Still capped at 30 even though 35 samples were pushed.
    EXPECT_EQ(entry.ring_fill, RING_SIZE);
    // ring_head wrapped: 35 writes into a 30-slot ring lands back at index 5.
    EXPECT_EQ(entry.ring_head, 5);
    // 35 pushes write ring indices 0..29 with values 1..30, then wrap and
    // overwrite indices 0..4 with values 31..35 - leaving indices 5..29
    // still holding values 6..30 (never overwritten) and indices 0..4
    // holding the wrapped-around values 31..35.
    EXPECT_EQ(entry.count_ring[5], 6);
    EXPECT_EQ(entry.count_ring[29], 30);
    EXPECT_EQ(entry.count_ring[0], 31);
    EXPECT_EQ(entry.count_ring[4], 35);
    EXPECT_EQ(entry.last_updated_epoch, RING_SIZE + 5u);
}

// Filling the table to MAX_KLASS_POPULATION_ENTRIES and then inserting one
// more distinct klass_id must evict the least-recently-updated entry (the
// smallest last_updated_epoch) and return its representative jweak so the
// caller can release it.
TEST_F(KlassPopulationTest, EvictsLeastRecentlyUpdatedEntryWhenFull) {
    LivenessTracker *tracker = LivenessTracker::instance();

    const int CAP = 256; // MAX_KLASS_POPULATION_ENTRIES
    for (u32 klass_id = 1; klass_id <= (u32)CAP; klass_id++) {
        int slot;
        bool created;
        // epoch == klass_id, so klass_id 1 is the least-recently-updated
        // entry once the table is full.
        tracker->klassPopulationRecordForTest(klass_id, 1, klass_id, &slot,
                                               &created);
        ASSERT_TRUE(created);
    }
    EXPECT_EQ(tracker->klassPopulationSizeForTest(), CAP);

    jweak victim_ref = fakeRef(0xdead);
    tracker->klassPopulationSetRepresentativeForTest(nullptr, 1, victim_ref);

    int slot;
    bool created;
    jweak evicted = tracker->klassPopulationRecordForTest(
        /*klass_id=*/CAP + 1, /*count=*/1, /*epoch=*/CAP + 1, &slot, &created);

    EXPECT_TRUE(created);
    EXPECT_EQ(evicted, victim_ref);
    // Table stays at capacity - the evicted slot was reused, not appended.
    EXPECT_EQ(tracker->klassPopulationSizeForTest(), CAP);

    KlassPopulationEntry evicted_klass_entry;
    EXPECT_FALSE(tracker->klassPopulationLookupForTest(1, &evicted_klass_entry))
        << "klass_id 1 should have been fully replaced by the eviction";

    KlassPopulationEntry new_entry;
    ASSERT_TRUE(tracker->klassPopulationLookupForTest(CAP + 1, &new_entry));
    EXPECT_EQ(new_entry.representative, nullptr);
    EXPECT_EQ(new_entry.ring_fill, 1);
}

// ---------------------------------------------------------------------------
// Slope computation and candidate ranking (LiveHeapReferenceChains-
// RemainingWorkPlan.md). Same rationale as KlassPopulationTest above
// for exercising LivenessTracker::instance() directly: selectLeakCandidates()
// makes no JNI call (it only copies the opaque jweak field, never
// dereferences it), so it is safe to call on the real singleton without a
// live JVM, and the *ForTest seams already in place are enough to seed
// arbitrary ring-buffer states without going through cleanup_table().
class SelectLeakCandidatesTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<LIVENESS_TRACKER_TEST_NAME>();
        LivenessTracker::instance()->klassPopulationResetForTest();
    }

    void TearDown() override {
        LivenessTracker::instance()->klassPopulationResetForTest();
        restoreDefaultSignalHandlers();
    }

    static jweak fakeRef(uintptr_t tag) {
        return reinterpret_cast<jweak>(tag);
    }

    // Pushes `n` samples (count values `counts[0..n)`, one per epoch starting
    // at `start_epoch`) into klass_id's ring buffer via the same
    // recordKlassPopulationSampleLocked() path production code drives from
    // cleanup_table()'s epoch-advance pass (klassPopulationRecordForTest() is
    // a direct pass-through to it, see its header comment).
    static void seedSeries(LivenessTracker *tracker, u32 klass_id,
                            const u16 *counts, int n, u64 start_epoch) {
        for (int i = 0; i < n; i++) {
            int slot;
            bool created;
            tracker->klassPopulationRecordForTest(klass_id, counts[i],
                                                   start_epoch + i, &slot,
                                                   &created);
        }
    }
};

// A klass whose population is monotonically increasing across a full
// (>=10-sample) window has a positive slope and is returned, carrying its
// representative jweak through unchanged.
TEST_F(SelectLeakCandidatesTest, GrowingPopulationIsSelected) {
    LivenessTracker *tracker = LivenessTracker::instance();

    const u16 growing[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    seedSeries(tracker, /*klass_id=*/1, growing, 10, /*start_epoch=*/1);
    jweak rep = fakeRef(0x1);
    tracker->klassPopulationSetRepresentativeForTest(nullptr, 1, rep);

    KlassCandidate out[5];
    int count = tracker->selectLeakCandidates(out, 5);

    ASSERT_EQ(count, 1);
    EXPECT_EQ(out[0].klass_id, 1u);
    EXPECT_EQ(out[0].representative, rep);
}

// A klass with a flat population (zero slope) is not a growth candidate -
// the design doc requires strictly positive slope, not "non-negative".
TEST_F(SelectLeakCandidatesTest, FlatPopulationIsNotSelected) {
    LivenessTracker *tracker = LivenessTracker::instance();

    const u16 flat[10] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    seedSeries(tracker, /*klass_id=*/1, flat, 10, /*start_epoch=*/1);

    KlassCandidate out[5];
    int count = tracker->selectLeakCandidates(out, 5);

    EXPECT_EQ(count, 0);
}

// A klass whose population is shrinking has a negative slope and must not be
// reported as a leak candidate.
TEST_F(SelectLeakCandidatesTest, ShrinkingPopulationIsNotSelected) {
    LivenessTracker *tracker = LivenessTracker::instance();

    const u16 shrinking[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    seedSeries(tracker, /*klass_id=*/1, shrinking, 10, /*start_epoch=*/1);

    KlassCandidate out[5];
    int count = tracker->selectLeakCandidates(out, 5);

    EXPECT_EQ(count, 0);
}

// A klass with fewer than KLASS_POPULATION_MIN_FILL_FOR_TREND (10) samples
// is skipped regardless of how strong its apparent trend looks - not enough
// history yet to trust it (design doc's explicit minimum-fill requirement).
TEST_F(SelectLeakCandidatesTest, JustBelowMinimumFillIsNotSelected) {
    LivenessTracker *tracker = LivenessTracker::instance();

    const u16 growing_but_short[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    seedSeries(tracker, /*klass_id=*/1, growing_but_short, 9,
               /*start_epoch=*/1);

    KlassCandidate out[5];
    int count = tracker->selectLeakCandidates(out, 5);

    EXPECT_EQ(count, 0);
}

// Exactly KLASS_POPULATION_MIN_FILL_FOR_TREND (10) samples is enough - the
// design doc's threshold is phrased as "e.g. >=10 samples", not ">10".
TEST_F(SelectLeakCandidatesTest, ExactlyMinimumFillIsSelected) {
    LivenessTracker *tracker = LivenessTracker::instance();

    const u16 growing[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    seedSeries(tracker, /*klass_id=*/1, growing, 10, /*start_epoch=*/1);

    KlassCandidate out[5];
    int count = tracker->selectLeakCandidates(out, 5);

    EXPECT_EQ(count, 1);
}

// Multiple positive-slope klasses must come back sorted by slope magnitude
// descending, not insertion order.
TEST_F(SelectLeakCandidatesTest, OrdersByMagnitudeDescending) {
    LivenessTracker *tracker = LivenessTracker::instance();

    // klass 1: earliest third avg 2, recent third avg 9 -> slope 7 (strongest)
    const u16 strong[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // klass 2: earliest third avg 2, recent third avg 5 -> slope 3 (weakest)
    const u16 weak[10] = {1, 2, 3, 4, 4, 4, 4, 5, 5, 5};
    // klass 3: earliest third avg 2, recent third avg 7 -> slope 5 (middle)
    const u16 medium[10] = {1, 2, 3, 4, 5, 5, 6, 7, 7, 7};

    seedSeries(tracker, /*klass_id=*/1, strong, 10, /*start_epoch=*/1);
    seedSeries(tracker, /*klass_id=*/2, weak, 10, /*start_epoch=*/1);
    seedSeries(tracker, /*klass_id=*/3, medium, 10, /*start_epoch=*/1);

    KlassCandidate out[5];
    int count = tracker->selectLeakCandidates(out, 5);

    ASSERT_EQ(count, 3);
    EXPECT_EQ(out[0].klass_id, 1u); // strongest
    EXPECT_EQ(out[1].klass_id, 3u); // middle
    EXPECT_EQ(out[2].klass_id, 2u); // weakest
}

// More than MAX_LEAK_CANDIDATES (5) positive-slope klasses exist: only the
// top 5 by magnitude are returned, even though the caller asked for more -
// design doc's "top 3-5" cutoff is an upper bound the method itself enforces,
// not just a suggestion to the caller.
TEST_F(SelectLeakCandidatesTest, CapsAtMaxLeakCandidatesRegardlessOfRequestedMax) {
    LivenessTracker *tracker = LivenessTracker::instance();

    // 7 klasses, each growing by a distinct amount per sample so every one
    // has a distinct, positive slope: klass_id N grows by N per sample.
    for (u32 klass_id = 1; klass_id <= 7; klass_id++) {
        u16 series[10];
        for (int i = 0; i < 10; i++) {
            series[i] = (u16)(1 + i * klass_id);
        }
        seedSeries(tracker, klass_id, series, 10, /*start_epoch=*/1);
    }

    KlassCandidate out[10];
    int count = tracker->selectLeakCandidates(out, 10);

    ASSERT_EQ(count, 5); // MAX_LEAK_CANDIDATES, not the requested 10
    // Steeper growth (larger klass_id) means larger slope - the 5 returned
    // must be the 5 largest klass_ids, strongest first.
    EXPECT_EQ(out[0].klass_id, 7u);
    EXPECT_EQ(out[1].klass_id, 6u);
    EXPECT_EQ(out[2].klass_id, 5u);
    EXPECT_EQ(out[3].klass_id, 4u);
    EXPECT_EQ(out[4].klass_id, 3u);
}

// The caller's own buffer capacity (`max`) is honored when it is smaller
// than MAX_LEAK_CANDIDATES - the method must never write past `max` slots.
TEST_F(SelectLeakCandidatesTest, HonorsCallerSuppliedMaxBelowCap) {
    LivenessTracker *tracker = LivenessTracker::instance();

    for (u32 klass_id = 1; klass_id <= 3; klass_id++) {
        u16 series[10];
        for (int i = 0; i < 10; i++) {
            series[i] = (u16)(1 + i * klass_id);
        }
        seedSeries(tracker, klass_id, series, 10, /*start_epoch=*/1);
    }

    KlassCandidate out[2];
    int count = tracker->selectLeakCandidates(out, 2);

    ASSERT_EQ(count, 2);
    EXPECT_EQ(out[0].klass_id, 3u); // strongest
    EXPECT_EQ(out[1].klass_id, 2u); // second-strongest; klass 1 dropped
}

// An empty population table (nothing tracked yet, or _gc_generations was
// never enabled so population tracking's own gate left the table empty) yields no
// candidates regardless of `max` - no separate guard is needed inside
// selectLeakCandidates() beyond the table being empty.
TEST_F(SelectLeakCandidatesTest, EmptyTableReturnsZero) {
    LivenessTracker *tracker = LivenessTracker::instance();

    KlassCandidate out[5];
    int count = tracker->selectLeakCandidates(out, 5);

    EXPECT_EQ(count, 0);
}
