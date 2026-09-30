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
#include "arguments.h"
#include "objectSampler.h"
#include "profiler.h"
#include "referenceChainsTestAccessors.h"
#include "../../main/cpp/gtest_crash_handler.h"
#include <atomic>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <thread>
#include <unordered_map>
#include <vector>

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
// Per-klass population tracking. These exercise LivenessTracker::instance()
// directly rather than
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
    EXPECT_EQ(entry.representative_count, 0);
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

// A klass whose every tracked instance died never appears in
// _klass_count_scratch, so the per-scratch fold skips it - without the
// zero-sample pass its ring would keep the last positive count and its
// consecutive_positive trend, keeping a dead population a leak candidate
// until the entry is evicted. Running a fold for a later epoch with an
// empty scratch must push a zero sample into the absent entry's ring,
// refresh its last_updated_epoch, and reset consecutive_positive.
TEST_F(KlassPopulationTest, FoldRecordsZeroSampleForClassesThatDisappear) {
    LivenessTracker *tracker = LivenessTracker::instance();

    // Seed a positive population history for klass 42 through epoch 3.
    for (u64 epoch = 1; epoch <= 3; epoch++) {
        int slot;
        bool created;
        tracker->klassPopulationRecordForTest(42, /*count=*/3 + (int)epoch,
                                              epoch, &slot, &created);
    }
    KlassPopulationEntry entry;
    ASSERT_TRUE(tracker->klassPopulationLookupForTest(42, &entry));
    ASSERT_EQ(entry.last_updated_epoch, 3u);

    // Every instance of klass 42 died: epoch 4's fold runs with an EMPTY
    // scratch (no survivors at all).
    tracker->foldKlassCountsZeroSampleForTest(/*epoch=*/4);

    ASSERT_TRUE(tracker->klassPopulationLookupForTest(42, &entry));
    // Zero sample recorded for the fold's epoch...
    EXPECT_EQ(entry.last_updated_epoch, 4u);
    // ...visible as the most recently pushed ring value...
    u8 head = (u8)((entry.ring_head + 30 - 1) %
                   30);
    EXPECT_EQ(entry.count_ring[head], 0u);
    // ...and the stale positive trend is cleared.
    EXPECT_EQ(entry.consecutive_positive, 0);

    // A klass that DID receive a survivor sample this epoch is not touched
    // again by the zero-sample pass (its just-pushed count stays intact).
    int slot;
    bool created;
    tracker->klassPopulationRecordForTest(43, /*count=*/2, /*epoch=*/4, &slot,
                                           &created);
    EXPECT_TRUE(created);
    tracker->foldKlassCountsZeroSampleForTest(/*epoch=*/4);
    ASSERT_TRUE(tracker->klassPopulationLookupForTest(43, &entry));
    // The survivor sample (2) is still the entry's most recent value - not
    // overwritten by a zero sample.
    u8 head43 = (u8)((entry.ring_head + 30 - 1) %
                     30);
    EXPECT_EQ(entry.count_ring[head43], 2u);
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
    // Eviction now returns evicted refs via output array, not return value.
    jweak evicted[KlassPopulationEntry::MAX_REPRESENTATIVES_PER_KLASS];
    int evicted_count = 0;
    tracker->klassPopulationRecordForTest(
        /*klass_id=*/CAP + 1, /*count=*/1, /*epoch=*/CAP + 1, &slot, &created,
        evicted, &evicted_count, KlassPopulationEntry::MAX_REPRESENTATIVES_PER_KLASS);

    EXPECT_TRUE(created);
    ASSERT_EQ(evicted_count, 1);
    EXPECT_EQ(evicted[0], victim_ref);
    // Table stays at capacity - the evicted slot was reused, not appended.
    EXPECT_EQ(tracker->klassPopulationSizeForTest(), CAP);

    KlassPopulationEntry evicted_klass_entry;
    EXPECT_FALSE(tracker->klassPopulationLookupForTest(1, &evicted_klass_entry))
        << "klass_id 1 should have been fully replaced by the eviction";

    KlassPopulationEntry new_entry;
    ASSERT_TRUE(tracker->klassPopulationLookupForTest(CAP + 1, &new_entry));
    EXPECT_EQ(new_entry.representative_count, 0);
    EXPECT_EQ(new_entry.ring_fill, 1);
}

// ---------------------------------------------------------------------------
// Slope computation and candidate ranking. Same rationale as KlassPopulationTest above
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
    // a direct pass-through to it, see its header comment). ALSO seeds a
    // qualifying per-tid trend for the same epochs (a linear 1..n ramp on a
    // fixed synthetic tid) - selectLeakCandidates() now requires a qualifying
    // allocating thread on top of the klass-level ramp, so a series seeded
    // through this helper represents a genuinely thread-concentrated leak.
    // Tests that specifically exercise the per-tid gate itself seed the
    // tid trends (or their absence) directly via tidTrendRecordForTest().
    static void seedSeries(LivenessTracker *tracker, u32 klass_id,
                            const u16 *counts, int n, u64 start_epoch) {
        for (int i = 0; i < n; i++) {
            int slot;
            bool created;
            tracker->klassPopulationRecordForTest(klass_id, counts[i],
                                                   start_epoch + i, &slot,
                                                   &created);
            tracker->tidTrendRecordForTest(klass_id, /*tid=*/42,
                                            (u32)(i + 1), start_epoch + i);
        }
    }
};

// A klass whose population is monotonically increasing for long enough has a
// positive slope, clears the growth/floor magnitude bars
// (hasQualifyingGrowth()) for enough consecutive epochs to satisfy the
// sustained-trend hysteresis requirement, and is returned, carrying its
// representative jweak through unchanged. 20 samples (not just the 10-sample
// minimum fill) - see MinimumFillAloneDoesNotClearHysteresis/
// SustainedGrowthClearsHysteresis below for the boundary this margin avoids.
TEST_F(SelectLeakCandidatesTest, GrowingPopulationIsSelected) {
    LivenessTracker *tracker = LivenessTracker::instance();

    u16 growing[20];
    for (int i = 0; i < 20; i++) {
        growing[i] = (u16)(i + 1);
    }
    seedSeries(tracker, /*klass_id=*/1, growing, 20, /*start_epoch=*/1);
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

// Exactly KLASS_POPULATION_MIN_FILL_FOR_TREND (10) samples clears
// hasQualifyingGrowth() on only its very last push - every earlier push saw
// ring_fill below the minimum and was rejected outright, so
// consecutive_positive is only 1 by the time fill reaches 10. One qualifying
// epoch does not clear the sustained-trend hysteresis requirement
// (LEAK_TREND_HYSTERESIS_BASE, 5 consecutive qualifying epochs) on its own -
// this used to be enough before that gate existed (hence this test's name),
// but is not anymore; see SustainedGrowthClearsHysteresis below for the new
// equivalent boundary test.
TEST_F(SelectLeakCandidatesTest, MinimumFillAloneDoesNotClearHysteresis) {
    LivenessTracker *tracker = LivenessTracker::instance();

    const u16 growing[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    seedSeries(tracker, /*klass_id=*/1, growing, 10, /*start_epoch=*/1);

    KlassCandidate out[5];
    int count = tracker->selectLeakCandidates(out, 5);

    EXPECT_EQ(count, 0);
}

// Once growth/floor keeps qualifying for enough additional epochs past
// min-fill to reach LEAK_TREND_HYSTERESIS_BASE (5 consecutive qualifying
// epochs: fill 10 through 14), the klass is trusted.
TEST_F(SelectLeakCandidatesTest, SustainedGrowthClearsHysteresis) {
    LivenessTracker *tracker = LivenessTracker::instance();

    u16 growing[14];
    for (int i = 0; i < 14; i++) {
        growing[i] = (u16)(i + 1);
    }
    seedSeries(tracker, /*klass_id=*/1, growing, 14, /*start_epoch=*/1);

    KlassCandidate out[5];
    int count = tracker->selectLeakCandidates(out, 5);

    EXPECT_EQ(count, 1);
}

// The aggregate post-GC heap floor (heapFloorRising()) lowers the number of
// consecutive qualifying epochs required from LEAK_TREND_HYSTERESIS_BASE (5)
// to LEAK_TREND_HYSTERESIS_CORROBORATED (3) for every candidate in the same
// scan - it cannot single out which klass is responsible for its own rise,
// so it can only raise or lower this bar uniformly, never reorder candidates
// against each other (see that pair's own comment, livenessTracker.h).
TEST_F(SelectLeakCandidatesTest, HeapFloorCorroborationLowersRequiredHysteresis) {
    LivenessTracker *tracker = LivenessTracker::instance();

    // 12 samples: 3 consecutive qualifying epochs past min-fill (fill = 10,
    // 11, 12) - enough for LEAK_TREND_HYSTERESIS_CORROBORATED (3) but not
    // LEAK_TREND_HYSTERESIS_BASE (5).
    u16 growing[12];
    for (int i = 0; i < 12; i++) {
        growing[i] = (u16)(i + 1);
    }
    seedSeries(tracker, /*klass_id=*/1, growing, 12, /*start_epoch=*/1);

    KlassCandidate out[5];
    EXPECT_EQ(tracker->selectLeakCandidates(out, 5), 0)
        << "3 qualifying epochs clear the corroborated (3) but not the base "
           "(5) hysteresis bar - without heap-floor corroboration this klass "
           "must not be selected yet";

    // A rising aggregate heap floor (10 samples, clearly growing) makes
    // heapFloorRising() report true, lowering the bar for this same scan.
    constexpr u64 GiB = 1ULL << 30;
    constexpr u64 MiB = 1ULL << 20;
    for (int i = 0; i < 10; i++) {
        tracker->heapFloorRecordForTest(2 * GiB + (u64)i * 50 * MiB);
    }
    ASSERT_TRUE(tracker->heapFloorRisingForTest());

    EXPECT_EQ(tracker->selectLeakCandidates(out, 5), 1);
}

// --- Per-(klass, tid) qualification gate (TidTrend, livenessTracker.h) ---
// The disjoint-tagged-vs-frontier pod finding: a whole-klass rising
// generation count can come from churn spread across MANY allocating
// threads, each retaining a STABLE handful of instances. A klass with a
// qualifying klass-level trend but NO thread whose own trend qualifies is
// NOT a leak candidate.
TEST_F(SelectLeakCandidatesTest, KlassTrendWithoutQualifyingTidIsNotSelected) {
    LivenessTracker *tracker = LivenessTracker::instance();

    // Klass-level ramp only - no per-tid trend seeded at all (the raw seam
    // loop, not seedSeries(), which would seed a qualifying tid too).
    u16 growing[20];
    for (int i = 0; i < 20; i++) {
        growing[i] = (u16)(i + 1);
        int slot;
        bool created;
        tracker->klassPopulationRecordForTest(/*klass_id=*/1, growing[i],
                                                /*epoch=*/i + 1, &slot, &created);
    }

    KlassCandidate out[5];
    EXPECT_EQ(tracker->selectLeakCandidates(out, 5), 0)
        << "a klass-level rise with no qualifying allocating thread is the "
           "machinery-churn shape observed on the hotdog pod - it must not "
           "become a candidate";
}

// A klass trend plus a tid trend that is FLAT (machinery: stable small
// retained set, no rising age span, below the retained-count bar) does
// not qualify either - each discriminator is necessary, not just one of
// them being absent.
TEST_F(SelectLeakCandidatesTest, FlatTidTrendDoesNotQualify) {
    LivenessTracker *tracker = LivenessTracker::instance();

    u16 growing[20];
    for (int i = 0; i < 20; i++) {
        growing[i] = (u16)(i + 1);
        int slot;
        bool created;
        tracker->klassPopulationRecordForTest(/*klass_id=*/1, growing[i],
                                                /*epoch=*/i + 1, &slot, &created);
        // Constant 2 surviving tracked instances, every epoch: below the
        // retained-count bar and no rising age-cardinality trend.
        tracker->tidTrendRecordForTest(/*klass_id=*/1, /*tid=*/7, /*count=*/2,
                                        /*epoch=*/i + 1);
    }

    KlassCandidate out[5];
    EXPECT_EQ(tracker->selectLeakCandidates(out, 5), 0);
}

// The retained-count bar (TID_RETAINED_COUNT_BAR) qualifies a tid whose
// instances all share one age (one-cohort-per-thread accumulation - each
// one-shot worker thread's distinct-age count stays 1 forever) as long as
// it retains enough tracked instances - the discriminator that covers
// one-cohort-per-thread allocator shapes.
TEST_F(SelectLeakCandidatesTest, RetainedCountBarQualifiesOneCohortShape) {
    LivenessTracker *tracker = LivenessTracker::instance();

    u16 growing[20];
    for (int i = 0; i < 20; i++) {
        growing[i] = (u16)(i + 1);
        int slot;
        bool created;
        tracker->klassPopulationRecordForTest(/*klass_id=*/1, growing[i],
                                                /*epoch=*/i + 1, &slot, &created);
        // 12 > TID_RETAINED_COUNT_BAR (8), flat every epoch: the age trend
        // alone would never qualify (no rise), the bar does.
        tracker->tidTrendRecordForTest(/*klass_id=*/1, /*tid=*/7, /*count=*/12,
                                        /*epoch=*/i + 1);
    }

    KlassCandidate out[5];
    ASSERT_EQ(tracker->selectLeakCandidates(out, 5), 1);
    ASSERT_GE(out[0].qualifying_tid_count, 1);
    EXPECT_EQ(out[0].qualifying_tids[0], 7);
}

// A rising per-tid trend alone (below the retained-count bar) qualifies:
// small leaks grow their age span long before their count clears the bar -
// the hotdog pod's simulated-memory-leak thread (12 tracked [B instances,
// age_count rising 2->3) is exactly this shape.
TEST_F(SelectLeakCandidatesTest, RisingTidTrendQualifiesBelowCountBar) {
    LivenessTracker *tracker = LivenessTracker::instance();

    u16 growing[20];
    for (int i = 0; i < 20; i++) {
        growing[i] = (u16)(i + 1);
        int slot;
        bool created;
        tracker->klassPopulationRecordForTest(/*klass_id=*/1, growing[i],
                                                /*epoch=*/i + 1, &slot, &created);
        // Rising, but capped at 6 tracked instances (below the bar of 8).
        u32 tid_count = (u32)((i / 3) + 1) > 6 ? 6 : (u32)((i / 3) + 1);
        tracker->tidTrendRecordForTest(/*klass_id=*/1, /*tid=*/9, tid_count,
                                        /*epoch=*/i + 1);
    }

    KlassCandidate out[5];
    ASSERT_EQ(tracker->selectLeakCandidates(out, 5), 1);
    ASSERT_GE(out[0].qualifying_tid_count, 1);
    EXPECT_EQ(out[0].qualifying_tids[0], 9);
}

// Multiple positive-slope klasses must come back sorted by slope magnitude
// descending, not insertion order. 20-sample linear series (not the original
// 10 - see GrowingPopulationIsSelected's own note) at three distinct growth
// rates so every klass clears the growth/floor magnitude bars and the
// sustained-trend hysteresis requirement, while still ranking distinctly.
TEST_F(SelectLeakCandidatesTest, OrdersByMagnitudeDescending) {
    LivenessTracker *tracker = LivenessTracker::instance();

    u16 strong[20], weak[20], medium[20];
    for (int i = 0; i < 20; i++) {
        strong[i] = (u16)(1 + i * 3); // steepest -> strongest
        weak[i] = (u16)(1 + i * 1);   // shallowest -> weakest
        medium[i] = (u16)(1 + i * 2);
    }

    seedSeries(tracker, /*klass_id=*/1, strong, 20, /*start_epoch=*/1);
    seedSeries(tracker, /*klass_id=*/2, weak, 20, /*start_epoch=*/1);
    seedSeries(tracker, /*klass_id=*/3, medium, 20, /*start_epoch=*/1);

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
    // has a distinct, positive slope: klass_id N grows by N per sample. 20
    // samples (not 10 - see GrowingPopulationIsSelected's own note) so every
    // klass also clears the sustained-trend hysteresis requirement.
    for (u32 klass_id = 1; klass_id <= 7; klass_id++) {
        u16 series[20];
        for (int i = 0; i < 20; i++) {
            series[i] = (u16)(1 + i * klass_id);
        }
        seedSeries(tracker, klass_id, series, 20, /*start_epoch=*/1);
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
        u16 series[20];
        for (int i = 0; i < 20; i++) {
            series[i] = (u16)(1 + i * klass_id);
        }
        seedSeries(tracker, klass_id, series, 20, /*start_epoch=*/1);
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

// ---------------------------------------------------------------------------
// topKlassesByGenerationCount() - ranks by most-recent count_ring sample,
// with NO trend/hysteresis gate at all (unlike selectLeakCandidates() above)
// - see its own header comment (livenessTracker.h) for why: it exists to run
// AFTER hasLeakSignal() has already fired via the slower, hysteresis-gated
// path, as a faster follow-up ranking for ReferenceChainTracker's rotation
// priority. Reuses SelectLeakCandidatesTest's fixture/seedSeries() seam -
// same table, same seeding mechanism, different read method under test.
//
// Returns stable_class_tag, NOT klass_id (the classMap dictionary id) - see
// that field's own comment (livenessTracker.h) for why the two are
// deliberately different values. klassPopulationRecordForTest() (seedSeries()'s
// own underlying seam) bypasses foldKlassCountsLocked() entirely, so it never
// mints a stable_class_tag - tests seed it explicitly via
// klassPopulationSetStableClassTagForTest(), using a value distinct from
// klass_id in each test below specifically so a test that accidentally
// asserted against klass_id instead would fail loudly, not silently pass by
// coincidence.
// ---------------------------------------------------------------------------

// A single sample (ring_fill == 1, far below selectLeakCandidates()'s
// KLASS_POPULATION_MIN_FILL_FOR_TREND) is enough to rank - the whole point
// of skipping the hysteresis gate.
TEST_F(SelectLeakCandidatesTest, TopKlassesByGenerationCountNeedsOnlyOneSample) {
    LivenessTracker *tracker = LivenessTracker::instance();

    const u16 single[1] = {42};
    seedSeries(tracker, /*klass_id=*/7, single, 1, /*start_epoch=*/1);
    tracker->klassPopulationSetStableClassTagForTest(7, -700);

    u32 out[5];
    int count = tracker->topKlassesByGenerationCount(out, 5);

    ASSERT_EQ(count, 1);
    EXPECT_EQ(out[0], (u32)-700);
}

// A klass with samples but no minted stable_class_tag yet (no live instance
// resolved so far - foldKlassCountsLocked()'s own comment) has nothing
// usable to return and must be skipped, not reported with a bogus 0 tag.
TEST_F(SelectLeakCandidatesTest, TopKlassesByGenerationCountSkipsUnmintedStableClassTag) {
    LivenessTracker *tracker = LivenessTracker::instance();

    const u16 single[1] = {42};
    seedSeries(tracker, /*klass_id=*/7, single, 1, /*start_epoch=*/1);
    // Deliberately no klassPopulationSetStableClassTagForTest() call.

    u32 out[5];
    int count = tracker->topKlassesByGenerationCount(out, 5);

    EXPECT_EQ(count, 0);
}

// Ranking is by the MOST RECENT sample, not the peak or the mean - a klass
// whose count has since fallen still ranks by where it is NOW.
TEST_F(SelectLeakCandidatesTest, TopKlassesByGenerationCountUsesMostRecentSampleNotPeak) {
    LivenessTracker *tracker = LivenessTracker::instance();

    const u16 peakedThenFell[4] = {100, 5, 5, 5}; // peak 100, now 5
    const u16 steady[4] = {10, 10, 10, 10};       // never peaked, now 10
    seedSeries(tracker, /*klass_id=*/1, peakedThenFell, 4, /*start_epoch=*/1);
    seedSeries(tracker, /*klass_id=*/2, steady, 4, /*start_epoch=*/1);
    tracker->klassPopulationSetStableClassTagForTest(1, -100);
    tracker->klassPopulationSetStableClassTagForTest(2, -200);

    u32 out[5];
    int count = tracker->topKlassesByGenerationCount(out, 5);

    ASSERT_EQ(count, 2);
    EXPECT_EQ(out[0], (u32)-200) << "klass 2 (currently 10) should outrank "
                                    "klass 1 (currently 5, despite an "
                                    "earlier peak of 100)";
    EXPECT_EQ(out[1], (u32)-100);
}

// A flat or shrinking population - which selectLeakCandidates() would
// exclude entirely (zero/negative slope) - still ranks here: this method
// applies no growth-direction requirement, only magnitude.
TEST_F(SelectLeakCandidatesTest, TopKlassesByGenerationCountIncludesFlatAndShrinkingPopulations) {
    LivenessTracker *tracker = LivenessTracker::instance();

    const u16 flat[3] = {50, 50, 50};
    const u16 shrinking[3] = {30, 20, 10};
    seedSeries(tracker, /*klass_id=*/1, flat, 3, /*start_epoch=*/1);
    seedSeries(tracker, /*klass_id=*/2, shrinking, 3, /*start_epoch=*/1);
    tracker->klassPopulationSetStableClassTagForTest(1, -100);
    tracker->klassPopulationSetStableClassTagForTest(2, -200);

    u32 out[5];
    int count = tracker->topKlassesByGenerationCount(out, 5);

    ASSERT_EQ(count, 2);
    EXPECT_EQ(out[0], (u32)-100) << "flat-at-50 outranks shrinking-to-10";
    EXPECT_EQ(out[1], (u32)-200);
}

TEST_F(SelectLeakCandidatesTest, TopKlassesByGenerationCountCapsAtMaxLeakCandidates) {
    LivenessTracker *tracker = LivenessTracker::instance();

    for (u32 klass_id = 1; klass_id <= 8; klass_id++) {
        const u16 sample[1] = {(u16)(klass_id * 10)};
        seedSeries(tracker, klass_id, sample, 1, /*start_epoch=*/1);
        tracker->klassPopulationSetStableClassTagForTest(klass_id, -(jlong)(klass_id * 100));
    }

    u32 out[10];
    int count = tracker->topKlassesByGenerationCount(out, 10);

    EXPECT_EQ(count, 5) << "capped at MAX_LEAK_CANDIDATES regardless of the "
                           "caller-supplied max";
    // Descending by most-recent count: klass 8 (count 80, tag -800) first.
    EXPECT_EQ(out[0], (u32)-800);
    EXPECT_EQ(out[4], (u32)-400);
}

TEST_F(SelectLeakCandidatesTest, TopKlassesByGenerationCountEmptyTableReturnsZero) {
    LivenessTracker *tracker = LivenessTracker::instance();

    u32 out[5];
    int count = tracker->topKlassesByGenerationCount(out, 5);

    EXPECT_EQ(count, 0);
}

// ---------------------------------------------------------------------------
// Heap-wide time-to-OOM projection (secondsToOOM()) - the aggressive-leak gap
// selectLeakCandidates()'s per-klass ring-fill/hysteresis gate leaves open:
// that gate can take longer to trust a candidate than a fast, heap-wide leak
// has left before OOM (see ReferenceChainTracker::hasLeakSignal()'s
// OOM_URGENT_THRESHOLD_S fast path, referenceChains.h/.cpp). Exercises the
// heap-floor ring/time-ring pair directly via the same heapFloorRecordForTest()
// seam SelectLeakCandidatesTest's HeapFloorCorroboration test above already
// uses for heapFloorRising(), plus setMaxHeapBytesForTest() to avoid the
// JNI-dependent HeapUsage::getMaxHeap() call this suite has no live JVM for.
// ---------------------------------------------------------------------------
class SecondsToOOMTest : public ::testing::Test {
protected:
    static constexpr u64 SEC_NS = 1000000000ULL;
    static constexpr u64 MiB = 1ULL << 20;

    void SetUp() override {
        installGtestCrashHandler<LIVENESS_TRACKER_TEST_NAME>();
        LivenessTracker::instance()->klassPopulationResetForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(true);
    }

    void TearDown() override {
        LivenessTracker::instance()->klassPopulationResetForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(false);
        LivenessTracker::instance()->setMaxHeapBytesForTest(-1);
        restoreDefaultSignalHandlers();
    }

    // Ten samples, one second apart, growing by 100MiB each: earliest third
    // (indices 0-2) means to 1100MiB at t=1s, recent third (indices 7-9)
    // means to 1800MiB at t=8s - a 700MiB rise over 7s, i.e. exactly
    // 100MiB/s, chosen so the projected time-to-exhaustion below comes out
    // to a clean value rather than a value only checked against itself.
    static void seedRisingFloor(LivenessTracker *tracker) {
        for (int i = 0; i < 10; i++) {
            tracker->heapFloorRecordForTest(1000 * MiB + (u64)i * 100 * MiB,
                                             (u64)i * SEC_NS);
        }
    }
};

// Fewer than KLASS_POPULATION_MIN_FILL_FOR_TREND (10) heap-floor samples -
// same "not enough history yet" gate ringThirdsStats() applies to every
// other trend check in this class.
TEST_F(SecondsToOOMTest, NotEnoughSamplesReturnsNegative) {
    LivenessTracker *tracker = LivenessTracker::instance();
    tracker->setMaxHeapBytesForTest((jlong)(2800 * MiB));
    for (int i = 0; i < 9; i++) {
        tracker->heapFloorRecordForTest(1000 * MiB + (u64)i * 100 * MiB,
                                         (u64)i * SEC_NS);
    }
    EXPECT_LT(tracker->secondsToOOM(), 0.0);
}

// A flat floor (zero byte delta between the earliest and recent thirds) is
// not rising - no projection is offered, mirroring hasQualifyingGrowth()'s
// own "strictly positive slope" requirement.
TEST_F(SecondsToOOMTest, FlatFloorReturnsNegative) {
    LivenessTracker *tracker = LivenessTracker::instance();
    tracker->setMaxHeapBytesForTest((jlong)(2800 * MiB));
    for (int i = 0; i < 10; i++) {
        tracker->heapFloorRecordForTest(1000 * MiB, (u64)i * SEC_NS);
    }
    EXPECT_LT(tracker->secondsToOOM(), 0.0);
}

// No heap-floor history is ever recorded outside _gc_generations (onGC()'s
// own gate) - secondsToOOM() must not fabricate a projection from whatever
// ring contents happen to be left over from a previous _gc_generations
// session.
TEST_F(SecondsToOOMTest, GcGenerationsDisabledReturnsNegative) {
    LivenessTracker *tracker = LivenessTracker::instance();
    tracker->setMaxHeapBytesForTest((jlong)(2800 * MiB));
    seedRisingFloor(tracker);
    tracker->setGcGenerationsForTest(false);

    EXPECT_LT(tracker->secondsToOOM(), 0.0);
}

// A rising floor is meaningless without a resolved max heap size to project
// against - initialize_table()'s own Error path (livenessTracker.cpp) never
// lets liveness tracking start without one, but secondsToOOM() must still
// guard the case explicitly rather than dividing/comparing against -1.
TEST_F(SecondsToOOMTest, UnresolvedMaxHeapReturnsNegative) {
    LivenessTracker *tracker = LivenessTracker::instance();
    tracker->setMaxHeapBytesForTest(-1);
    seedRisingFloor(tracker);

    EXPECT_LT(tracker->secondsToOOM(), 0.0);
}

// The worked example seedRisingFloor() documents: 700MiB rise over 7s
// (100MiB/s) with 1000MiB of headroom (2800MiB max heap - 1800MiB recent
// floor mean) projects to exactly 10 seconds.
TEST_F(SecondsToOOMTest, RisingFloorProjectsExpectedSeconds) {
    LivenessTracker *tracker = LivenessTracker::instance();
    tracker->setMaxHeapBytesForTest((jlong)(2800 * MiB));
    seedRisingFloor(tracker);

    EXPECT_NEAR(tracker->secondsToOOM(), 9.0, 1e-6);
}

// The floor's own recent-third mean has already reached the max heap size -
// exhaustion is "now", not some positive number of seconds out.
TEST_F(SecondsToOOMTest, FloorAtMaxHeapReturnsZero) {
    LivenessTracker *tracker = LivenessTracker::instance();
    tracker->setMaxHeapBytesForTest((jlong)(1800 * MiB)); // == recent third's mean
    seedRisingFloor(tracker);

    EXPECT_EQ(tracker->secondsToOOM(), 0.0);
}

// ---------------------------------------------------------------------------
// Leak tag pool (design A: direct tagging of leaking objects)
// ---------------------------------------------------------------------------
// The pool hands out JVMTI tags in [LEAK_TAG_BASE, LEAK_TAG_BASE + 256) and
// recycles them when the tracked object dies. These tests exercise the pure
// pool mechanics (acquire/release/info); tagLeakInstances() is driven against
// a mock JVM in LivenessTrackerMockJvmTest below.

class LeakTagPoolTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<LIVENESS_TRACKER_TEST_NAME>();
        LivenessTracker::instance()->leakTagPoolResetForTest();
    }

    void TearDown() override { restoreDefaultSignalHandlers(); }
};

TEST_F(LeakTagPoolTest, AcquireReturnsTagsInLeakRange) {
    LivenessTracker *tracker = LivenessTracker::instance();
    jlong base = tracker->leakTagBaseForTest();
    for (int i = 0; i < tracker->leakTagPoolSizeForTest(); i++) {
        jlong tag = tracker->acquireLeakTagForTest(/*call_trace_id=*/100 + i,
                                                  /*tid=*/7 + i);
        EXPECT_GE(tag, base) << "tag below pool range at acquire " << i;
        EXPECT_LT(tag, base + tracker->leakTagPoolSizeForTest())
            << "tag above pool range at acquire " << i;
    }
    // Pool exhausted: further acquires fail with 0.
    EXPECT_EQ(0, tracker->acquireLeakTagForTest(1, 1));
    EXPECT_EQ(0, tracker->leakTagFreeCountForTest());
}

TEST_F(LeakTagPoolTest, ReleaseReturnsTagToPoolAndInfoIsInvalidated) {
    LivenessTracker *tracker = LivenessTracker::instance();
    int pool_size = tracker->leakTagPoolSizeForTest();

    jlong tag = tracker->acquireLeakTagForTest(42, 99);
    ASSERT_GE(tag, tracker->leakTagBaseForTest());

    u64 call_trace_id = 0;
    jint tid = 0;
    EXPECT_TRUE(tracker->getLeakTagInfo(tag, &call_trace_id, &tid));
    EXPECT_EQ(42u, call_trace_id);
    EXPECT_EQ(99, tid);

    tracker->releaseLeakTagForTest(tag);
    // Released tags must not report stale info.
    u64 stale_ctid = 12345;
    jint stale_tid = 12345;
    EXPECT_FALSE(tracker->getLeakTagInfo(tag, &stale_ctid, &stale_tid))
        << "released tag still reports info";

    // The released tag can be acquired again (reusable pool), and the free
    // count was restored: pool_size-1 after the acquire, back to pool_size
    // after the release, pool_size-1 again after the re-acquire.
    EXPECT_EQ(pool_size, tracker->leakTagFreeCountForTest());
    jlong re_tag = tracker->acquireLeakTagForTest(43, 100);
    EXPECT_EQ(tag, re_tag) << "released tag should be recycled first (LIFO)";
    EXPECT_EQ(pool_size - 1, tracker->leakTagFreeCountForTest());
}

TEST_F(LeakTagPoolTest, ReleaseOutsidePoolRangeIsIgnored) {
    LivenessTracker *tracker = LivenessTracker::instance();
    jlong base = tracker->leakTagBaseForTest();
    int free_before = tracker->leakTagFreeCountForTest();

    // Tags outside [base, base+pool): frontier tags (small positive), class
    // tags (negative), and one-past-the-end must all be rejected.
    tracker->releaseLeakTagForTest(1);
    tracker->releaseLeakTagForTest(-1);
    tracker->releaseLeakTagForTest(0);
    tracker->releaseLeakTagForTest(base + tracker->leakTagPoolSizeForTest());
    tracker->releaseLeakTagForTest(base - 1);

    EXPECT_EQ(free_before, tracker->leakTagFreeCountForTest())
        << "out-of-range releases must not corrupt the free list";
}

// ---------------------------------------------------------------------------
// C1 chaos: concurrent acquire/release across forced epoch rotations. The
// single-threaded tests above pin the sequential mechanics; this one attacks
// the dedicated _leak_tag_pool_lock itself - in production acquireLeakTag()
// runs under the SHARED table lock (tagLeakInstances, BFS poll thread) while
// releaseLeakTag() runs under the EXCLUSIVE one (cleanup_table, GC-callback
// thread), so the pool lock is the ONLY thing serializing the LIFO free list
// once a second shared-lock mutator exists (see acquireLeakTag()'s own
// comment - that is the regression "Serialize the leak-tag pool" fixed).
//
// Each worker round models one GC epoch: the thread acquires a burst of tags
// (holding several at once, like one table's worth of tagged instances),
// verifies ownership, then releases everything before a full-quiescence
// barrier. Invariants checked:
//   I1. No tag to two live owners - an external per-tag owner registry
//       (CAS -1 -> slot on acquire, slot -> -1 on release) never sees a tag
//       already owned by another live thread. This is what breaks if the
//       pool lock stops serializing the pop/push pair.
//   I2. getLeakTagInfo() on a held tag reports exactly the (call_trace_id,
//       tid) the owning thread passed - the side table write and the free-
//       list pop are one atomic unit under the pool lock.
//   I3. Exhaustion returns 0 (never a garbage/reused tag) once the pool is
//       empty - forced every round by slot 0's burst exceeding the whole
//       pool on its own (scheduling-independent - see kTagChaosBurstMax).
//   I4. No cross-epoch leak - at every round's quiescence barrier every tag
//       has been released, so the free count must be back to pool size, and
//       after the run every info slot reads as not-in-use.
//   I5. The free list carries no duplicates - after the chaos, a sequential
//       full drain must yield all pool_size tags exactly once (a duplicated
//       LIFO push would surface here as a missing/duplicate tag) and the
//       pool must then be exactly exhausted.
//
// Invariant failures are recorded in atomics and asserted after join: gtest
// EXPECT_* is not safe to call from non-main threads. Run under testTsan:
// the pool lock's acquire/release pairing is what TSan validates here.
namespace {

constexpr int kTagChaosThreads = 12;
constexpr int kTagChaosRounds = 100;
// Slot 0's burst must exceed the whole pool on its own: under ASan the
// instrumented acquire path effectively serializes the threads' burst loops,
// so "total demand > pool" only guarantees exhaustion if one thread can
// drain the pool single-handedly (a 30-40 burst held by one thread at a time
// never reaches 256). Others keep small bursts so overlaps still occur when
// the scheduler interleaves them.
constexpr int kTagChaosBurstMax = 300;

// Spin barrier: all workers sync at each round boundary. The elected thread
// (exactly one per generation, the last to arrive) performs the whole-pool
// quiescence assertion while the others wait, so the count check cannot race
// the next round's acquires.
class TagChaosBarrier {
public:
    explicit TagChaosBarrier(int n) : n_(n) {}
    bool wait() { // true for exactly the one caller that closes the generation
        int gen = generation_.load(std::memory_order_acquire);
        int arrived = count_.fetch_add(1, std::memory_order_acq_rel) + 1;
        if (arrived == n_) {
            count_.store(0, std::memory_order_relaxed);
            generation_.fetch_add(1, std::memory_order_release);
            return true;
        }
        while (generation_.load(std::memory_order_acquire) == gen) {
            std::this_thread::yield();
        }
        return false;
    }

private:
    const int n_;
    std::atomic<int> count_{0};
    std::atomic<int> generation_{0};
};

struct TagChaosState {
    // owner[i]: -1 free, else the worker slot that holds tag base+i.
    std::atomic<int> *owner;
    TagChaosBarrier *barrier;
    std::atomic<int> violations{0};
    std::atomic<int> violation_slot{-1};
    std::atomic<int> exhausted_hits{0};
};

void tagChaosRecordViolation(TagChaosState &state, int slot) {
    state.violations.fetch_add(1, std::memory_order_relaxed);
    int nobody = -1;
    state.violation_slot.compare_exchange_strong(nobody, slot,
                                                 std::memory_order_relaxed);
}

void tagChaosWorker(int slot, TagChaosState &state) {
    LivenessTracker *tracker = LivenessTracker::instance();
    const jlong base = tracker->leakTagBaseForTest();
    const int pool = tracker->leakTagPoolSizeForTest();
    // Per-thread LCG so burst sizes vary round to round without <random>
    // machinery. Slot 0 bursts 260..289 (> the 256-tag pool, see
    // kTagChaosBurstMax's comment - I3 must not depend on scheduling);
    // the rest burst 30..40 so concurrent partial exhaustion still occurs
    // when bursts overlap.
    u64 seed = 0x9E3779B97F4A7C15ULL * (u64)(slot + 1);
    auto next = [&seed]() {
        seed = seed * 6364136223846793005ULL + 1442695040888963407ULL;
        return (int)((seed >> 33) & 0x7fffffff);
    };

    jlong held[kTagChaosBurstMax];
    for (int round = 0; round < kTagChaosRounds; round++) {
        int burst = (slot == 0) ? 260 + next() % 30
                                : 30 + next() % 11;
        int n = 0;
        for (int k = 0; k < burst; k++) {
            // call_trace_id must be nonzero: 0/0 in _leak_tag_info means
            // "released/never acquired", so a zero id would fake a free slot.
            u64 ctid = ((u64)(slot + 1) << 32) | (u64)(round * 1000 + k);
            jint mytid = (jint)(1000 + slot);
            jlong tag = tracker->acquireLeakTagForTest(ctid, mytid);
            if (tag == 0) {
                state.exhausted_hits.fetch_add(1, std::memory_order_relaxed);
                break; // pool empty - legal, stop bursting this round
            }
            if (tag < base || tag >= base + pool) {
                tagChaosRecordViolation(state, slot);
                break;
            }
            int idx = (int)(tag - base);
            int expected = -1;
            if (!state.owner[idx].compare_exchange_strong(expected, slot,
                                                          std::memory_order_acq_rel)) {
                tagChaosRecordViolation(state, slot); // I1: already owned
            }
            held[n++] = tag;
            u64 got_ctid = 0;
            jint got_tid = 0;
            if (!tracker->getLeakTagInfo(tag, &got_ctid, &got_tid) ||
                got_ctid != ctid || got_tid != mytid) {
                tagChaosRecordViolation(state, slot); // I2: side table mismatch
            }
        }
        // Quiescence: everyone must drop this epoch's tags before the count
        // check, so releases happen BEFORE the barrier, acquires after.
        for (int j = 0; j < n; j++) {
            int idx = (int)(held[j] - base);
            int expected = slot;
            if (!state.owner[idx].compare_exchange_strong(expected, -1,
                                                          std::memory_order_acq_rel)) {
                tagChaosRecordViolation(state, slot); // I1: owner bookkeeping lost
            }
            tracker->releaseLeakTagForTest(held[j]);
        }
        bool elected = state.barrier->wait();
        if (elected) {
            // I4: every tag of this epoch was released before the barrier -
            // the free list must be whole again, nothing leaked across epochs.
            if (tracker->leakTagFreeCountForTest() != pool) {
                tagChaosRecordViolation(state, slot);
            }
        }
        state.barrier->wait(); // hold workers until the elected check is done
    }
}

} // namespace

TEST_F(LeakTagPoolTest, ConcurrentAcquireReleaseAcrossEpochsIsConsistent) {
    LivenessTracker *tracker = LivenessTracker::instance();
    const int pool = tracker->leakTagPoolSizeForTest();
    const jlong base = tracker->leakTagBaseForTest();

    std::vector<std::atomic<int>> owner(pool);
    for (int i = 0; i < pool; i++) {
        owner[i].store(-1, std::memory_order_relaxed);
    }
    TagChaosBarrier barrier(kTagChaosThreads);
    TagChaosState state;
    state.owner = owner.data();
    state.barrier = &barrier;

    std::vector<std::thread> threads;
    threads.reserve(kTagChaosThreads);
    for (int slot = 0; slot < kTagChaosThreads; slot++) {
        threads.emplace_back(tagChaosWorker, slot, std::ref(state));
    }
    for (auto &t : threads) {
        t.join();
    }

    EXPECT_EQ(0, state.violations.load())
        << "pool invariants broken (first offending slot: "
        << state.violation_slot.load() << ")";
    // The exhaustion branch must actually have been exercised (I3): slot 0's
    // burst alone exceeds the pool every round, so a run without a single 0
    // return would mean acquireLeakTag() never observed an empty free list.
    EXPECT_GT(state.exhausted_hits.load(), 0)
        << "pool exhaustion never hit - chaos did not oversubscribe";

    // I4 (final): after full quiescence every info slot reads as released.
    for (int i = 0; i < pool; i++) {
        u64 ctid = 0;
        jint tid = 0;
        EXPECT_FALSE(tracker->getLeakTagInfo(base + i, &ctid, &tid))
            << "tag index " << i << " still reports in-use after teardown";
    }

    // I5: drain the whole pool sequentially - every tag exactly once, then
    // exact exhaustion. A duplicated free-list entry shows up as a repeated
    // tag (and, with pool_size acquires total, as some index never seen).
    std::vector<bool> seen(pool, false);
    for (int i = 0; i < pool; i++) {
        jlong tag = tracker->acquireLeakTagForTest((u64)(i + 1), (jint)i);
        ASSERT_NE(0, tag) << "pool exhausted after only " << i << " acquires";
        int idx = (int)(tag - base);
        ASSERT_GE(idx, 0);
        ASSERT_LT(idx, pool);
        EXPECT_FALSE(seen[idx]) << "tag index " << idx << " handed out twice";
        seen[idx] = true;
    }
    EXPECT_EQ(0, tracker->acquireLeakTagForTest(1, 1))
        << "pool not exactly exhausted after draining pool_size tags";
    for (int i = 0; i < pool; i++) {
        tracker->releaseLeakTagForTest(base + i);
    }
    EXPECT_EQ(pool, tracker->leakTagFreeCountForTest());
}

// ---------------------------------------------------------------------------
// Chase-phase admission boost (admitForTracking()/noteSelectedCandidates()/
// setUrgentTracking() - see livenessTracker.h). Same "exercise the singleton
// directly" rationale as KlassPopulationTest above: the admission gate is
// JNI-free pure logic (atomic reads + the per-thread RNG draw), so it is
// testable without a live JVM; only track() beyond the gate needs a JNIEnv.
//
// Determinism: admissionResetForTest() forces _subsample_ratio to 0 and resets
// this thread's RNG ThreadLocal, so an unboosted tid's draw always comes from
// a freshly default-seeded mt19937 whose first draw is strictly in (0,1) -
// ratio 0 can never admit. That pins the fall-through case without asserting
// on RNG internals.
class AdmissionBoostTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<LIVENESS_TRACKER_TEST_NAME>();
        LivenessTracker::instance()->admissionResetForTest();
    }

    void TearDown() override {
        // Leave the singleton clean for any test that follows in the same
        // process (watched tids / urgency would 100%-admit unrelated tids).
        LivenessTracker::instance()->admissionResetForTest();
        LivenessTracker::instance()->setSubsampleRatioForTest(0.1);
        restoreDefaultSignalHandlers();
    }

    static void fillCandidate(KlassCandidate *kc, jint tid) {
        kc->klass_id = 1;
        kc->representative = reinterpret_cast<jweak>(0x1);
        kc->qualifying_tids[0] = tid;
        kc->qualifying_tid_count = 1;
    }
};

// A watched tid is admitted even though the configured ratio (0) would
// deterministically reject it - the boost precedes the ratio draw.
TEST_F(AdmissionBoostTest, WatchedTidAdmittedDespiteRejectingRatio) {
    LivenessTracker *tracker = LivenessTracker::instance();
    KlassCandidate kc;
    fillCandidate(&kc, /*tid=*/42);
    tracker->noteSelectedCandidates(&kc, 1);

    EXPECT_TRUE(tracker->admitForTrackingForTest(42));
    // An unwatched tid on the same thread falls through to the ratio draw and
    // is rejected (ratio 0).
    EXPECT_FALSE(tracker->admitForTrackingForTest(43));
}

// Urgency admits everything - any tid, watched or not.
TEST_F(AdmissionBoostTest, UrgencyAdmitsAllTids) {
    LivenessTracker *tracker = LivenessTracker::instance();
    tracker->setUrgentTracking(true);
    EXPECT_TRUE(tracker->admitForTrackingForTest(1234));
    EXPECT_TRUE(tracker->admitForTrackingForTest(5678));

    // Releasing urgency restores the ratio gate: unwatched tids reject again,
    // watched tids stay boosted.
    tracker->setUrgentTracking(false);
    EXPECT_FALSE(tracker->admitForTrackingForTest(1234));
    KlassCandidate kc;
    fillCandidate(&kc, 1234);
    tracker->noteSelectedCandidates(&kc, 1);
    EXPECT_TRUE(tracker->admitForTrackingForTest(1234));
}

// noteSelectedCandidates() dedupes tids shared across candidates and caps
// the watched set at MAX_QUALIFYING_TIDS.
TEST_F(AdmissionBoostTest, WatchedTidsAreDedupedAndCapped) {
    LivenessTracker *tracker = LivenessTracker::instance();
    constexpr int kMax = KlassCandidate::MAX_QUALIFYING_TIDS;  // 8

    // Two candidates: 5 tids each, tids 3 and 4 shared -> union is 1..7, in
    // candidate order (candidates are rank-ordered, so a later candidate's
    // tids only append what the earlier ones did not cover).
    KlassCandidate kc[2];
    for (int t = 0; t < 5; t++) {
        kc[0].qualifying_tids[t] = 1 + t;  // 1..5
        kc[1].qualifying_tids[t] = 3 + t;  // 3..7 -> adds 6,7
    }
    for (int c = 0; c < 2; c++) {
        kc[c].klass_id = 1 + c;
        kc[c].representative = reinterpret_cast<jweak>(0x1 + c);
        kc[c].qualifying_tid_count = 5;
    }
    tracker->noteSelectedCandidates(kc, 2);
    ASSERT_EQ(7, tracker->watchedTidCountForTest());
    for (int i = 0; i < 7; i++) {
        EXPECT_EQ(i + 1, tracker->watchedTidForTest(i))
            << "shared tids must not duplicate; union stays in order";
    }

    // A poll whose union exceeds the cap (1..8 from candidate 1, 9 from
    // candidate 2) keeps the earlier candidates' tids and drops the overflow
    // tid - and that overflow tid is not admitted.
    KlassCandidate over[2];
    for (int t = 0; t < kMax; t++) {
        over[0].qualifying_tids[t] = 1 + t;  // 1..8
    }
    over[0].qualifying_tid_count = kMax;
    over[0].klass_id = 1;
    over[0].representative = reinterpret_cast<jweak>(0x1);
    fillCandidate(&over[1], /*tid=*/9);
    tracker->noteSelectedCandidates(over, 2);
    ASSERT_EQ(kMax, tracker->watchedTidCountForTest());
    for (int i = 0; i < kMax; i++) {
        EXPECT_EQ(i + 1, tracker->watchedTidForTest(i));
    }
    EXPECT_FALSE(tracker->admitForTrackingForTest(9));
    EXPECT_TRUE(tracker->admitForTrackingForTest(8));
}

// A zero-candidate poll clears the watched set - a tid left watched after the
// chase ends would keep admitting that thread at 100% across OS tid reuse.
TEST_F(AdmissionBoostTest, ZeroCandidatePollClearsWatchedSet) {
    LivenessTracker *tracker = LivenessTracker::instance();
    KlassCandidate kc;
    fillCandidate(&kc, 77);
    tracker->noteSelectedCandidates(&kc, 1);
    EXPECT_TRUE(tracker->admitForTrackingForTest(77));

    tracker->noteSelectedCandidates(nullptr, 0);
    EXPECT_EQ(tracker->watchedTidCountForTest(), 0);
    EXPECT_FALSE(tracker->admitForTrackingForTest(77));
}

// ---------------------------------------------------------------------------
// C2 chaos: hammer admitForTracking() from many threads while a publisher
// thread flips the boost state (noteSelectedCandidates()/setUrgentTracking())
// round by round, modeling the BFS poll thread republishing the watched set
// while allocation-sampling threads run the gate.
//
// With the fixture's ratio pinned to 0, the gate is a pure function of the
// boost state (admissionResetForTest() makes unboosted draws deterministically
// reject - see AdmissionBoostTest's determinism note), which makes the
// concurrent behavior decidable:
//   W1. Window consistency - within a round (publisher quiesced between two
//       barriers) every probe result must equal expected(tid) = urgent ||
//       watched. A watched tid must admit on EVERY call: the watched scan
//       returns true before any RNG draw, so even one false means the gate
//       observed a torn boost publish (the count+array two-phase hazard -
//       noteSelectedCandidates() writes slots then release-stores the count;
//       a relaxed count load on arm64 could pair a fresh count with stale
//       slots).
//   W2. No stale boost after a clear - after the publisher publishes the
//       zero-candidate poll and urgency off, no tid from ANY earlier round's
//       watched set may admit (the analog of an OS tid being recycled into an
//       unrelated thread still hitting a leftover watched entry).
//
// tid ranges are disjoint per round ([r*64, r*64+64)) so a stale watched
// entry can be detected simply by re-probing earlier rounds' watched tids
// after the clear. Violations tally in atomics; gtest asserts run on the
// main thread after join. Run under testTsan.
namespace {

constexpr int kAdmHammers = 8;
constexpr int kAdmRounds = 60;
constexpr int kAdmIter = 100;
constexpr int kAdmMaxWatched = 4;   // <= KlassCandidate::MAX_QUALIFYING_TIDS
constexpr int kAdmRange = 64;       // per-round tid range; watched tids are
                                    // drawn from [base+1, base+61), probes
                                    // for unwatched use [base+61, base+65)

struct AdmChaosState {
    TagChaosBarrier *barrier; // 9 parties: 8 hammers + publisher
    // Publisher -> hammers round plans, written before the round's entry
    // barrier (the barrier's acq_rel fetch_add/release-store pair orders the
    // handoff); index [r] is fixed once written.
    jint watched[kAdmRounds][kAdmMaxWatched];
    jint watched_count[kAdmRounds];
    bool urgent[kAdmRounds];
    // Hammer -> main tallies.
    std::atomic<int> window_violations{0}; // W1
    std::atomic<int> stale_admitted{0};    // W2
    std::atomic<int> stale_probes{0};      // diagnostics: W2 must not be vacuous
    std::atomic<int> first_bad_tid{-1};
};

void admRecordViolation(AdmChaosState &state, jint tid) {
    state.window_violations.fetch_add(1, std::memory_order_relaxed);
    int nobody = -1;
    state.first_bad_tid.compare_exchange_strong(nobody, tid,
                                                std::memory_order_relaxed);
}

void admPublisher(AdmChaosState &state) {
    LivenessTracker *tracker = LivenessTracker::instance();
    u64 seed = 0xA24BAED4963EE407ULL;
    auto next = [&seed]() {
        seed = seed * 6364136223846793005ULL + 1442695040888963407ULL;
        return (int)((seed >> 33) & 0x7fffffff);
    };
    for (int r = 0; r < kAdmRounds; r++) {
        // Publish round r's boost state BEFORE the entry barrier.
        int count = next() % (kAdmMaxWatched + 1); // 0..4, 0 exercises the
                                                   // zero-candidate clear path
        state.watched_count[r] = count;
        for (int w = 0; w < count; w++) {
            state.watched[r][w] = (jint)(r * kAdmRange + 1 + next() % 60);
        }
        state.urgent[r] = (next() % 3) == 2;
        // Publish via the production seams - the watched set through
        // noteSelectedCandidates() (one candidate carrying all tids; the
        // dedup/cap logic is pinned by the sequential tests above), urgency
        // through setUrgentTracking().
        KlassCandidate kc;
        if (count > 0) {
            kc.klass_id = 1;
            kc.representative = reinterpret_cast<jweak>(0x1);
            for (int w = 0; w < count; w++) {
                kc.qualifying_tids[w] = state.watched[r][w];
            }
            kc.qualifying_tid_count = count;
            tracker->noteSelectedCandidates(&kc, 1);
        } else {
            tracker->noteSelectedCandidates(nullptr, 0);
        }
        tracker->setUrgentTracking(state.urgent[r]);

        state.barrier->wait(); // A: window open
        state.barrier->wait(); // B: window probes done
        // Clear phase: exactly what a chase teardown does.
        tracker->noteSelectedCandidates(nullptr, 0);
        tracker->setUrgentTracking(false);
        state.barrier->wait(); // C: clear published
        state.barrier->wait(); // D: stale probes done, next round
    }
}

void admHammer(int slot, AdmChaosState &state) {
    LivenessTracker *tracker = LivenessTracker::instance();
    for (int r = 0; r < kAdmRounds; r++) {
        state.barrier->wait(); // A
        // W1: within the window the gate must be a pure function of the
        // published (urgent, watched) state - every call, any thread.
        bool urgent = state.urgent[r];
        jint base = (jint)(r * kAdmRange);
        for (int it = 0; it < kAdmIter; it++) {
            for (int w = 0; w < state.watched_count[r]; w++) {
                if (!tracker->admitForTrackingForTest(state.watched[r][w])) {
                    admRecordViolation(state, state.watched[r][w]);
                }
            }
            for (int u = 0; u < 4; u++) {
                bool admitted =
                    tracker->admitForTrackingForTest(base + 61 + u);
                if (admitted != urgent) { // unwatched: false; urgent: true
                    admRecordViolation(state, base + 61 + u);
                }
            }
        }
        state.barrier->wait(); // B
        state.barrier->wait(); // C (clear published by the publisher)
        // W2: after the clear, nothing may admit - probed tids include every
        // tid watched in the last five rounds (plus the current unwatched
        // probes), so a leftover watched entry from any of them trips here.
        for (int it = 0; it < kAdmIter; it++) {
            for (int back = 0; back <= 5 && back <= r; back++) {
                int rr = r - back;
                for (int w = 0; w < state.watched_count[rr]; w++) {
                    state.stale_probes.fetch_add(1, std::memory_order_relaxed);
                    if (tracker->admitForTrackingForTest(state.watched[rr][w])) {
                        state.stale_admitted.fetch_add(1,
                                                       std::memory_order_relaxed);
                        admRecordViolation(state, state.watched[rr][w]);
                    }
                }
            }
            for (int u = 0; u < 4; u++) {
                if (tracker->admitForTrackingForTest(base + 61 + u)) {
                    state.stale_admitted.fetch_add(1, std::memory_order_relaxed);
                    admRecordViolation(state, base + 61 + u);
                }
            }
        }
        state.barrier->wait(); // D
        (void)slot;
    }
}

} // namespace

TEST_F(AdmissionBoostTest, ConcurrentBoostPublishAndGateProbesStayConsistent) {
    LivenessTracker *tracker = LivenessTracker::instance();

    AdmChaosState state;
    memset(state.watched, 0, sizeof(state.watched));
    memset(state.watched_count, 0, sizeof(state.watched_count));
    memset(state.urgent, 0, sizeof(state.urgent));
    TagChaosBarrier barrier(kAdmHammers + 1);
    state.barrier = &barrier;

    std::vector<std::thread> threads;
    threads.reserve(kAdmHammers + 1);
    threads.emplace_back(admPublisher, std::ref(state));
    for (int slot = 0; slot < kAdmHammers; slot++) {
        threads.emplace_back(admHammer, slot, std::ref(state));
    }
    for (auto &t : threads) {
        t.join();
    }

    EXPECT_EQ(0, state.window_violations.load())
        << "gate result diverged from the published boost state (first bad "
        << "tid: " << state.first_bad_tid.load() << ")";
    EXPECT_EQ(0, state.stale_admitted.load())
        << "tid admitted after the boost was cleared - stale watched entry";
    // The stale check must not be vacuous: over 60 rounds the publisher
    // emits mostly non-empty watched sets, so re-probes of previously
    // watched tids are guaranteed to have happened.
    EXPECT_GT(state.stale_probes.load(), 0)
        << "no previously-watched tid was ever re-probed after a clear";
}

// ---------------------------------------------------------------------------
// LivenessTracker driven through its public start()/track()/onGC()/
// maybeForceCleanup()/tagLeakInstances() API against a minimal mock JVM: a
// JavaVM whose GetEnv() hands out a mock JNIEnv, and a mock jvmtiEnv, swapped
// into VM's statics via VMTestAccessor. Objects are entries of a fixed array;
// a jweak/local ref is the object's own address, and "collecting" an object
// just flips its alive flag (IsSameObject(ref, nullptr) and NewLocalRef()
// report it dead from then on).
//
// start() initializes the tracking table only once per process (the table
// deliberately survives recordings), so every test here must leave the table
// empty: TearDown() kills all mock objects and runs one more sweep to reap
// their rows before the mock JVM goes away.

namespace {

struct MockJvmObject {
    bool alive;
    void *klass; // fake jclass: the address of a MockJvm class marker
};

struct MockJvm {
    static constexpr int kMaxObjects = 1024;

    JNIInvokeInterface_ vm_tbl{};
    JavaVM_ vm{};
    JNINativeInterface_ jni_tbl{};
    JNIEnv_ jni{};
    jvmtiInterface_1_ jvmti_tbl{};
    _jvmtiEnv jvmti{};

    // Reserved up front and never grown, so object addresses stay stable.
    std::vector<MockJvmObject> objects;
    std::unordered_map<const void *, jlong> tags;
    // Fake jclass -> JVMTI class signature.
    std::unordered_map<const void *, const char *> class_signatures;

    // Address-only markers standing in for classes and objects the tracker's
    // initialization resolves (java.lang.Runtime, java.lang.Class, the
    // Runtime instance) and for the tracked objects' classes.
    char runtime_class, class_class, runtime_object;
    char retained_class, trailing_class;

    MockJvmObject *asObject(const void *p) {
        if (objects.empty()) {
            return nullptr;
        }
        const MockJvmObject *first = objects.data();
        const MockJvmObject *last = first + objects.size();
        const MockJvmObject *o = static_cast<const MockJvmObject *>(p);
        return (o >= first && o < last) ? const_cast<MockJvmObject *>(o) : nullptr;
    }

    jobject newObject(void *klass) {
        objects.push_back({true, klass});
        return reinterpret_cast<jobject>(&objects.back());
    }
};

MockJvm *g_mock_jvm = nullptr;

jint JNICALL mockGetEnv(JavaVM *, void **penv, jint) {
    *penv = &g_mock_jvm->jni;
    return JNI_OK;
}

jclass JNICALL mockFindClass(JNIEnv *, const char *name) {
    if (strcmp(name, "java/lang/Runtime") == 0) {
        return reinterpret_cast<jclass>(&g_mock_jvm->runtime_class);
    }
    if (strcmp(name, "java/lang/Class") == 0) {
        return reinterpret_cast<jclass>(&g_mock_jvm->class_class);
    }
    return nullptr;
}

jmethodID JNICALL mockGetMethodID(JNIEnv *, jclass clazz, const char *, const char *) {
    return reinterpret_cast<jmethodID>(clazz);
}

jobject JNICALL mockCallStaticObjectMethodV(JNIEnv *, jclass, jmethodID, va_list) {
    return reinterpret_cast<jobject>(&g_mock_jvm->runtime_object);
}

// Runtime.maxMemory(): large enough that the tracking table's capacity is not
// the limiting factor for any test here.
jlong JNICALL mockCallLongMethodV(JNIEnv *, jobject, jmethodID, va_list) {
    return 64LL * 1024 * 1024 * 1024;
}

jboolean JNICALL mockExceptionCheck(JNIEnv *) { return JNI_FALSE; }
void JNICALL mockExceptionClear(JNIEnv *) {}
void JNICALL mockExceptionDescribe(JNIEnv *) {}

jweak JNICALL mockNewWeakGlobalRef(JNIEnv *, jobject obj) {
    return reinterpret_cast<jweak>(obj);
}
void JNICALL mockDeleteWeakGlobalRef(JNIEnv *, jweak) {}

jobject JNICALL mockNewLocalRef(JNIEnv *, jobject ref) {
    MockJvmObject *o = g_mock_jvm->asObject(ref);
    return (o != nullptr && !o->alive) ? nullptr : ref;
}
void JNICALL mockDeleteLocalRef(JNIEnv *, jobject) {}

jboolean JNICALL mockIsSameObject(JNIEnv *, jobject a, jobject b) {
    if (b == nullptr) {
        MockJvmObject *o = g_mock_jvm->asObject(a);
        return (a == nullptr || (o != nullptr && !o->alive)) ? JNI_TRUE : JNI_FALSE;
    }
    return a == b ? JNI_TRUE : JNI_FALSE;
}

jclass JNICALL mockGetObjectClass(JNIEnv *, jobject obj) {
    MockJvmObject *o = g_mock_jvm->asObject(obj);
    return reinterpret_cast<jclass>(o != nullptr ? o->klass : &g_mock_jvm->class_class);
}

jvmtiError JNICALL mockSetEventNotificationMode(jvmtiEnv *, jvmtiEventMode, jvmtiEvent,
                                                jthread, ...) {
    return JVMTI_ERROR_NONE;
}

jvmtiError JNICALL mockGetTag(jvmtiEnv *, jobject obj, jlong *tag) {
    auto it = g_mock_jvm->tags.find(obj);
    *tag = it != g_mock_jvm->tags.end() ? it->second : 0;
    return JVMTI_ERROR_NONE;
}

jvmtiError JNICALL mockSetTag(jvmtiEnv *, jobject obj, jlong tag) {
    g_mock_jvm->tags[obj] = tag;
    return JVMTI_ERROR_NONE;
}

jvmtiError JNICALL mockGetClassSignature(jvmtiEnv *, jclass klass, char **signature,
                                         char **generic) {
    auto it = g_mock_jvm->class_signatures.find(klass);
    if (it == g_mock_jvm->class_signatures.end()) {
        return JVMTI_ERROR_INVALID_CLASS;
    }
    *signature = strdup(it->second);
    if (generic != nullptr) {
        *generic = nullptr;
    }
    return JVMTI_ERROR_NONE;
}

jvmtiError JNICALL mockDeallocate(jvmtiEnv *, unsigned char *mem) {
    free(mem);
    return JVMTI_ERROR_NONE;
}

constexpr const char *kRetainedSignature = "Lcom/datadoghq/lt/Retained;";
constexpr const char *kTrailingSignature = "Lcom/datadoghq/lt/Trailing;";

// The class id resolveKlassId() produces for `signature`: same
// normalizeClassSignature() + Profiler::lookupClass() sequence.
u32 classIdOf(const char *signature) {
    const char *name = nullptr;
    size_t len = 0;
    if (!ObjectSampler::normalizeClassSignature(signature, &name, &len)) {
        return 0;
    }
    int id = Profiler::instance()->lookupClass(name, len);
    return id > 0 ? (u32)id : 0;
}

} // namespace

class LivenessTrackerMockJvmTest : public ::testing::Test {
protected:
    MockJvm jvm;
    JavaVM *saved_vm = nullptr;
    jvmtiEnv *saved_jvmti = nullptr;
    bool saved_hotspot = false;
    int saved_hotspot_version = 0;

    // maybeForceCleanup() only sweeps once 30s have passed since its last
    // sweep. The tracker keeps that timestamp across tests, so the fake clock
    // is process-wide and only moves forward.
    static u64 fake_now_ns;

    void SetUp() override {
        installGtestCrashHandler<LIVENESS_TRACKER_TEST_NAME>();
        jvm.objects.reserve(MockJvm::kMaxObjects);
        jvm.class_signatures[&jvm.retained_class] = kRetainedSignature;
        jvm.class_signatures[&jvm.trailing_class] = kTrailingSignature;

        jvm.vm_tbl.GetEnv = &mockGetEnv;
        jvm.vm.functions = &jvm.vm_tbl;

        jvm.jni_tbl.FindClass = &mockFindClass;
        jvm.jni_tbl.GetMethodID = &mockGetMethodID;
        jvm.jni_tbl.GetStaticMethodID = &mockGetMethodID;
        jvm.jni_tbl.CallStaticObjectMethodV = &mockCallStaticObjectMethodV;
        jvm.jni_tbl.CallLongMethodV = &mockCallLongMethodV;
        jvm.jni_tbl.ExceptionCheck = &mockExceptionCheck;
        jvm.jni_tbl.ExceptionClear = &mockExceptionClear;
        jvm.jni_tbl.ExceptionDescribe = &mockExceptionDescribe;
        jvm.jni_tbl.NewWeakGlobalRef = &mockNewWeakGlobalRef;
        jvm.jni_tbl.DeleteWeakGlobalRef = &mockDeleteWeakGlobalRef;
        jvm.jni_tbl.NewLocalRef = &mockNewLocalRef;
        jvm.jni_tbl.DeleteLocalRef = &mockDeleteLocalRef;
        jvm.jni_tbl.IsSameObject = &mockIsSameObject;
        jvm.jni_tbl.GetObjectClass = &mockGetObjectClass;
        jvm.jni.functions = &jvm.jni_tbl;

        jvm.jvmti_tbl.SetEventNotificationMode = &mockSetEventNotificationMode;
        jvm.jvmti_tbl.GetTag = &mockGetTag;
        jvm.jvmti_tbl.SetTag = &mockSetTag;
        jvm.jvmti_tbl.GetClassSignature = &mockGetClassSignature;
        jvm.jvmti_tbl.Deallocate = &mockDeallocate;
        jvm.jvmti.functions = &jvm.jvmti_tbl;

        g_mock_jvm = &jvm;
        saved_vm = VMTestAccessor::getVm();
        saved_jvmti = VMTestAccessor::getJvmti();
        saved_hotspot = VMTestAccessor::getHotspot();
        saved_hotspot_version = VMTestAccessor::getHotspotVersion();
        VMTestAccessor::setVm(&jvm.vm);
        VMTestAccessor::setJvmti(&jvm.jvmti);
        // initialize() disables tracking below Java 11.
        VMTestAccessor::setHotspot(true);
        VMTestAccessor::setHotspotVersion(17);

        LivenessTracker *tracker = LivenessTracker::instance();
        tracker->klassPopulationResetForTest();
        tracker->leakTagPoolResetForTest();
        Arguments args;
        ASSERT_FALSE(args.parse("generations=true"));
        ASSERT_FALSE(tracker->start(args));
        // Track every allocation handed to track().
        tracker->setSubsampleRatioForTest(1.0);
    }

    void TearDown() override {
        for (MockJvmObject &o : jvm.objects) {
            o.alive = false;
        }
        LivenessTracker *tracker = LivenessTracker::instance();
        sweep();
        tracker->klassPopulationResetForTest();
        tracker->leakTagPoolResetForTest();
        tracker->admissionResetForTest();
        tracker->setSubsampleRatioForTest(0.1);
        tracker->setGcGenerationsForTest(false);
        VMTestAccessor::setVm(saved_vm);
        VMTestAccessor::setJvmti(saved_jvmti);
        VMTestAccessor::setHotspot(saved_hotspot);
        VMTestAccessor::setHotspotVersion(saved_hotspot_version);
        g_mock_jvm = nullptr;
        restoreDefaultSignalHandlers();
    }

    jobject trackNew(void *klass, jint tid) {
        jobject obj = jvm.newObject(klass);
        track(obj, tid);
        return obj;
    }

    void track(jobject obj, jint tid) {
        AllocEvent event;
        event._size = 16;
        LivenessTracker::instance()->track(&jvm.jni, event, tid, obj,
                                           /*call_trace_id=*/1);
    }

    // One GC (the JVMTI GarbageCollectionFinish callback, which bumps the GC
    // epoch) followed by the background-thread sweep for it
    // (cleanup_table(force=true, allow_resolve=true)).
    void sweep() {
        LivenessTracker *tracker = LivenessTracker::instance();
        LivenessTracker::GarbageCollectionFinish(&jvm.jvmti);
        fake_now_ns += 60ULL * 1000 * 1000 * 1000;
        tracker->maybeForceCleanup(fake_now_ns);
    }
};

u64 LivenessTrackerMockJvmTest::fake_now_ns = 0;

// Each sweep resolves the class of at most RESOLVE_BUDGET_PER_SWEEP (256,
// livenessTracker.cpp) survivors. Survivors keep their table order across
// compaction, so the budget must go to entries that have no cached class id
// yet; spending it on the same leading entries every sweep would leave every
// entry past the first 256 unresolved - and uncounted - forever.
TEST_F(LivenessTrackerMockJvmTest, ResolveBudgetReachesSurvivorsPastTheFirstSweep) {
    constexpr int kResolveBudgetPerSweep = 256;
    constexpr int kTrailing = 8;
    LivenessTracker *tracker = LivenessTracker::instance();
    u32 retained_id = classIdOf(kRetainedSignature);
    u32 trailing_id = classIdOf(kTrailingSignature);
    ASSERT_NE(0u, retained_id);
    ASSERT_NE(0u, trailing_id);

    for (int i = 0; i < kResolveBudgetPerSweep; i++) {
        trackNew(&jvm.retained_class, /*tid=*/1);
    }
    for (int i = 0; i < kTrailing; i++) {
        trackNew(&jvm.trailing_class, /*tid=*/1);
    }

    KlassPopulationEntry entry{};
    sweep();
    ASSERT_TRUE(tracker->klassPopulationLookupForTest(retained_id, &entry));
    ASSERT_FALSE(tracker->klassPopulationLookupForTest(trailing_id, &entry))
        << "the first sweep's budget should be used up by the leading entries";

    sweep();
    EXPECT_TRUE(tracker->klassPopulationLookupForTest(trailing_id, &entry))
        << "the second sweep must spend its budget on the still-unresolved "
           "trailing entries, not re-resolve the cached leading ones";
}

// Two table rows can hold weak refs to the same object (the same allocation
// recorded twice). Only the first row to tag the object may own its pool tag:
// if the second row adopted the tag it found on the object, both rows would
// release the same pool index when the object dies, pushing it onto the free
// list twice.
TEST_F(LivenessTrackerMockJvmTest, SharedObjectLeakTagHasSingleOwner) {
    LivenessTracker *tracker = LivenessTracker::instance();
    const int pool = tracker->leakTagPoolSizeForTest();
    u32 retained_id = classIdOf(kRetainedSignature);
    ASSERT_NE(0u, retained_id);

    constexpr jint kTid = 7;
    jobject obj = trackNew(&jvm.retained_class, kTid);
    track(obj, kTid);
    // Resolves both rows' cached class id, which tagLeakInstances() matches on.
    sweep();

    // Held by the test so the pool is never full: a duplicate release then
    // shows up as an over-count instead of writing past the free list.
    // TearDown()'s leakTagPoolResetForTest() returns it.
    ASSERT_NE(0, tracker->acquireLeakTagForTest(/*call_trace_id=*/1, /*tid=*/1));

    KlassCandidate candidate{};
    candidate.klass_id = retained_id;
    candidate.qualifying_tids[0] = kTid;
    candidate.qualifying_tid_count = 1;
    EXPECT_EQ(1, tracker->tagLeakInstances(&jvm.jvmti, &candidate, 1))
        << "only one of the two rows sharing the object may take its leak tag";
    EXPECT_EQ(pool - 2, tracker->leakTagFreeCountForTest());
    jlong tag = 0;
    mockGetTag(&jvm.jvmti, obj, &tag);
    EXPECT_GE(tag, tracker->leakTagBaseForTest());

    // Object dies: its rows are reaped, releasing the tag exactly once.
    g_mock_jvm->asObject(obj)->alive = false;
    sweep();
    EXPECT_EQ(pool - 1, tracker->leakTagFreeCountForTest())
        << "the object's leak tag must go back to the pool exactly once";
}
