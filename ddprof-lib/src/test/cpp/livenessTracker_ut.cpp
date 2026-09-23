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

static constexpr char LIVENESS_TRACKER_TEST_NAME[] = "LivenessTrackerTest";

// Recorded capacity must only advance when realloc() succeeds.
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

    // Correct pattern: update table_cap only after realloc succeeds.
    bool resizeTableCorrect(int newcap) {
        void* tmp = realloc(table, sizeof(int) * newcap);
        if (tmp != nullptr) {
            table = tmp;
            table_cap = newcap;
            return true;
        }
        return false;
    }

    // BUG: table_cap updates inside the realloc call, so it advances even on failure.
    bool resizeTableBuggy(int newcap) {
        void* tmp = realloc(table, sizeof(int) * (table_cap = newcap));
        if (tmp != nullptr) {
            table = tmp;
            return true;
        }
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

TEST_F(LivenessTrackerTest, CapacityOnlyUpdatedOnSuccessfulRealloc) {
    TrackingTableMock mock(10, 100);

    int initial_cap = mock.getCapacity();
    EXPECT_EQ(initial_cap, 10);

    bool success = mock.resizeTableCorrect(20);
    EXPECT_TRUE(success);
    EXPECT_EQ(mock.getCapacity(), 20);

    success = mock.resizeTableCorrect(40);
    EXPECT_TRUE(success);
    EXPECT_EQ(mock.getCapacity(), 40);
}

// Buggy pattern agrees with the correct one on success; realloc failure can't be forced.
TEST_F(LivenessTrackerTest, BuggyImplementationUpdateCapacityOnFailure) {
    TrackingTableMock mock(10, 100);

    int initial_cap = mock.getCapacity();
    EXPECT_EQ(initial_cap, 10);

    bool success = mock.resizeTableBuggy(20);
    EXPECT_TRUE(success);
    EXPECT_EQ(mock.getCapacity(), 20);
}

TEST_F(LivenessTrackerTest, CorrectResizePatternVerification) {
    TrackingTableMock mock(10, 100);

    int old_cap = mock.getCapacity();
    EXPECT_EQ(old_cap, 10);

    int newcap = old_cap * 2;
    bool success = mock.resizeTableCorrect(newcap);

    if (success) {
        EXPECT_EQ(mock.getCapacity(), newcap);
    } else {
        EXPECT_EQ(mock.getCapacity(), old_cap);
    }
}

TEST_F(LivenessTrackerTest, MultipleResizeOperationsMaintainCorrectCapacity) {
    TrackingTableMock mock(4, 128);

    std::vector<int> expected_capacities = {4, 8, 16, 32, 64, 128};
    size_t resize_count = 0;

    EXPECT_EQ(mock.getCapacity(), expected_capacities[resize_count]);

    for (size_t i = 1; i < expected_capacities.size(); i++) {
        int newcap = expected_capacities[i];
        bool success = mock.resizeTableCorrect(newcap);
        EXPECT_TRUE(success) << "Resize to " << newcap << " failed";
        EXPECT_EQ(mock.getCapacity(), newcap)
            << "Capacity mismatch after resize to " << newcap;
    }

    EXPECT_EQ(mock.getCapacity(), 128);
}

/**
 * Exercises the flush_table id-assignment guard: Profiler::lookupClass()
 * returns int (-1 at class-map capacity) but Event::_id is a u32, so -1
 * would wrap to 0xFFFFFFFF and corrupt liveness attribution.
 */
struct FlushTableIdGuardMock {
    bool recorded = false;
    uint32_t recorded_id = 0;

    // Only assign/record when class_id >= 0.
    void applyGuarded(int class_id) {
        if (class_id >= 0) {
            recorded = true;
            recorded_id = static_cast<uint32_t>(class_id);
        }
    }

    // Unguarded: unconditionally assigns class_id to the u32 event id.
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
    // Without the guard, -1 narrows to 0xFFFFFFFF in the u32 event id.
    FlushTableIdGuardMock mock;
    mock.applyUnguarded(-1);
    EXPECT_TRUE(mock.recorded);
    EXPECT_EQ(0xFFFFFFFFu, mock.recorded_id);
}

// Capacity is capped at max_cap during resize.
TEST_F(LivenessTrackerTest, CapacityDoesNotExceedMaxCap) {
    TrackingTableMock mock(10, 50);

    int newcap = std::min(mock.table_cap * 2, mock.table_max_cap);
    EXPECT_LE(newcap, 50);

    mock.resizeTableCorrect(newcap);
    EXPECT_EQ(mock.getCapacity(), 20);

    newcap = std::min(mock.table_cap * 2, mock.table_max_cap);
    mock.resizeTableCorrect(newcap);
    EXPECT_EQ(mock.getCapacity(), 40);

    newcap = std::min(mock.table_cap * 2, mock.table_max_cap);
    EXPECT_EQ(newcap, 50); // capped, not doubled to 80
    mock.resizeTableCorrect(newcap);
    EXPECT_EQ(mock.getCapacity(), 50);

    newcap = std::min(mock.table_cap * 2, mock.table_max_cap);
    EXPECT_EQ(newcap, 50);
}

// ---------------------------------------------------------------------------
// Per-klass population tracking, against the real singleton:
// recordKlassPopulationSampleLocked() makes no JNI call, so it is safe without
// a live JVM; fake jweak values are opaque, never dereferenced.
// ---------------------------------------------------------------------------
class KlassPopulationTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<LIVENESS_TRACKER_TEST_NAME>();
        // The population table persists across start() calls; reset it so
        // tests don't see leftovers in this process-wide singleton.
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

// A brand new klass_id creates a new entry whose ring holds one sample.
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

// A second sample for a known klass_id updates the same slot in place.
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

// Pushing over KLASS_POPULATION_RING_SIZE (30) caps ring_fill at 30, overwriting oldest.
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
    EXPECT_EQ(entry.ring_fill, RING_SIZE); // capped despite 35 pushes
    // 35 pushes overwrite indices 0..4 with values 31..35; 5..29 keep 6..30.
    EXPECT_EQ(entry.ring_head, 5);
    EXPECT_EQ(entry.count_ring[5], 6);
    EXPECT_EQ(entry.count_ring[29], 30);
    EXPECT_EQ(entry.count_ring[0], 31);
    EXPECT_EQ(entry.count_ring[4], 35);
    EXPECT_EQ(entry.last_updated_epoch, RING_SIZE + 5u);
}

// Full-table insert evicts the least-recently-updated entry, handing back
// its representative jweak for the caller to release.
TEST_F(KlassPopulationTest, EvictsLeastRecentlyUpdatedEntryWhenFull) {
    LivenessTracker *tracker = LivenessTracker::instance();

    const int CAP = 256; // MAX_KLASS_POPULATION_ENTRIES
    for (u32 klass_id = 1; klass_id <= (u32)CAP; klass_id++) {
        int slot;
        bool created;
        // epoch == klass_id: klass_id 1 ends up least-recently-updated.
        tracker->klassPopulationRecordForTest(klass_id, 1, klass_id, &slot,
                                               &created);
        ASSERT_TRUE(created);
    }
    EXPECT_EQ(tracker->klassPopulationSizeForTest(), CAP);

    jweak victim_ref = fakeRef(0xdead);
    tracker->klassPopulationSetRepresentativeForTest(nullptr, 1, victim_ref);

    int slot;
    bool created;
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
// Slope computation and candidate ranking, on the real singleton:
// selectLeakCandidates() is JNI-free; *ForTest seams suffice to seed ring
// states without cleanup_table().
// ---------------------------------------------------------------------------
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

    // Pushes `n` samples (counts[0..n), one per epoch from start_epoch) into
    // klass_id's ring, plus a qualifying per-tid ramp on a fixed tid for the
    // same epochs - selectLeakCandidates() requires a qualifying allocating
    // thread on top of the klass ramp. Per-tid-gate tests seed tid trends via
    // tidTrendRecordForTest() directly.
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

// A long-enough monotonic increase clears the magnitude bars and hysteresis.
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

// Zero slope is not a growth candidate (strictly positive required).
TEST_F(SelectLeakCandidatesTest, FlatPopulationIsNotSelected) {
    LivenessTracker *tracker = LivenessTracker::instance();

    const u16 flat[10] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    seedSeries(tracker, /*klass_id=*/1, flat, 10, /*start_epoch=*/1);

    KlassCandidate out[5];
    int count = tracker->selectLeakCandidates(out, 5);

    EXPECT_EQ(count, 0);
}

// A shrinking population has negative slope and must not be reported.
TEST_F(SelectLeakCandidatesTest, ShrinkingPopulationIsNotSelected) {
    LivenessTracker *tracker = LivenessTracker::instance();

    const u16 shrinking[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    seedSeries(tracker, /*klass_id=*/1, shrinking, 10, /*start_epoch=*/1);

    KlassCandidate out[5];
    int count = tracker->selectLeakCandidates(out, 5);

    EXPECT_EQ(count, 0);
}

// Below KLASS_POPULATION_MIN_FILL_FOR_TREND (10) samples: not trusted.
TEST_F(SelectLeakCandidatesTest, JustBelowMinimumFillIsNotSelected) {
    LivenessTracker *tracker = LivenessTracker::instance();

    const u16 growing_but_short[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    seedSeries(tracker, /*klass_id=*/1, growing_but_short, 9,
               /*start_epoch=*/1);

    KlassCandidate out[5];
    int count = tracker->selectLeakCandidates(out, 5);

    EXPECT_EQ(count, 0);
}

// Min fill (10) reached on the last push only: 1 qualifying epoch < hysteresis (5).
TEST_F(SelectLeakCandidatesTest, MinimumFillAloneDoesNotClearHysteresis) {
    LivenessTracker *tracker = LivenessTracker::instance();

    const u16 growing[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    seedSeries(tracker, /*klass_id=*/1, growing, 10, /*start_epoch=*/1);

    KlassCandidate out[5];
    int count = tracker->selectLeakCandidates(out, 5);

    EXPECT_EQ(count, 0);
}

// Growth sustained for LEAK_TREND_HYSTERESIS_BASE (5) qualifying epochs is trusted.
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

// The aggregate post-GC heap floor (heapFloorRising()) lowers the required
// consecutive qualifying epochs from LEAK_TREND_HYSTERESIS_BASE (5) to
// LEAK_TREND_HYSTERESIS_CORROBORATED (3) for every klass alike.
TEST_F(SelectLeakCandidatesTest, HeapFloorCorroborationLowersRequiredHysteresis) {
    LivenessTracker *tracker = LivenessTracker::instance();

    // 12 samples = 3 qualifying epochs past min-fill: clears the 3-bar, not the 5.
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

    // A rising aggregate heap floor lowers the bar for this same scan.
    constexpr u64 GiB = 1ULL << 30;
    constexpr u64 MiB = 1ULL << 20;
    for (int i = 0; i < 10; i++) {
        tracker->heapFloorRecordForTest(2 * GiB + (u64)i * 50 * MiB);
    }
    ASSERT_TRUE(tracker->heapFloorRisingForTest());

    EXPECT_EQ(tracker->selectLeakCandidates(out, 5), 1);
}

// --- Per-(klass, tid) qualification gate (TidTrend, livenessTracker.h) ---
// A whole-klass rising count can be churn spread across many threads, each
// retaining a stable handful: with no qualifying per-tid trend, the klass is
// not a leak candidate.
TEST_F(SelectLeakCandidatesTest, KlassTrendWithoutQualifyingTidIsNotSelected) {
    LivenessTracker *tracker = LivenessTracker::instance();

    // Klass-level ramp only - no per-tid trend seeded.
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
        << "a klass-level rise with no qualifying allocating thread must not "
           "become a candidate";
}

// A flat per-tid trend (stable small retained set, no age rise) does not qualify.
TEST_F(SelectLeakCandidatesTest, FlatTidTrendDoesNotQualify) {
    LivenessTracker *tracker = LivenessTracker::instance();

    u16 growing[20];
    for (int i = 0; i < 20; i++) {
        growing[i] = (u16)(i + 1);
        int slot;
        bool created;
        tracker->klassPopulationRecordForTest(/*klass_id=*/1, growing[i],
                                                /*epoch=*/i + 1, &slot, &created);
        // Flat at 2, below the retained-count bar, with no age rise.
        tracker->tidTrendRecordForTest(/*klass_id=*/1, /*tid=*/7, /*count=*/2,
                                        /*epoch=*/i + 1);
    }

    KlassCandidate out[5];
    EXPECT_EQ(tracker->selectLeakCandidates(out, 5), 0);
}

// Flat count above TID_RETAINED_COUNT_BAR (8) qualifies with no age rise (one-cohort shape).
TEST_F(SelectLeakCandidatesTest, RetainedCountBarQualifiesOneCohortShape) {
    LivenessTracker *tracker = LivenessTracker::instance();

    u16 growing[20];
    for (int i = 0; i < 20; i++) {
        growing[i] = (u16)(i + 1);
        int slot;
        bool created;
        tracker->klassPopulationRecordForTest(/*klass_id=*/1, growing[i],
                                                /*epoch=*/i + 1, &slot, &created);
        // 12 > TID_RETAINED_COUNT_BAR (8), flat: the bar qualifies, not the age trend.
        tracker->tidTrendRecordForTest(/*klass_id=*/1, /*tid=*/7, /*count=*/12,
                                        /*epoch=*/i + 1);
    }

    KlassCandidate out[5];
    ASSERT_EQ(tracker->selectLeakCandidates(out, 5), 1);
    ASSERT_GE(out[0].qualifying_tid_count, 1);
    EXPECT_EQ(out[0].qualifying_tids[0], 7);
}

// Rising per-tid trend qualifies below the bar: small leaks grow their age span first.
TEST_F(SelectLeakCandidatesTest, RisingTidTrendQualifiesBelowCountBar) {
    LivenessTracker *tracker = LivenessTracker::instance();

    u16 growing[20];
    for (int i = 0; i < 20; i++) {
        growing[i] = (u16)(i + 1);
        int slot;
        bool created;
        tracker->klassPopulationRecordForTest(/*klass_id=*/1, growing[i],
                                                /*epoch=*/i + 1, &slot, &created);
        // Rising, but capped below the bar of 8.
        u32 tid_count = (u32)((i / 3) + 1) > 6 ? 6 : (u32)((i / 3) + 1);
        tracker->tidTrendRecordForTest(/*klass_id=*/1, /*tid=*/9, tid_count,
                                        /*epoch=*/i + 1);
    }

    KlassCandidate out[5];
    ASSERT_EQ(tracker->selectLeakCandidates(out, 5), 1);
    ASSERT_GE(out[0].qualifying_tid_count, 1);
    EXPECT_EQ(out[0].qualifying_tids[0], 9);
}

// Positive-slope klasses come back sorted by slope magnitude descending.
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

// Over MAX_LEAK_CANDIDATES (5) positive-slope klasses: only the top 5 return.
TEST_F(SelectLeakCandidatesTest, CapsAtMaxLeakCandidatesRegardlessOfRequestedMax) {
    LivenessTracker *tracker = LivenessTracker::instance();

    // klass_id N grows by N per sample - distinct positive slopes.
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
    // Steeper growth (larger klass_id) = larger slope: the 5 largest klass_ids.
    EXPECT_EQ(out[0].klass_id, 7u);
    EXPECT_EQ(out[1].klass_id, 6u);
    EXPECT_EQ(out[2].klass_id, 5u);
    EXPECT_EQ(out[3].klass_id, 4u);
    EXPECT_EQ(out[4].klass_id, 3u);
}

// The caller's buffer capacity (`max`) is honored when below MAX_LEAK_CANDIDATES.
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

// An empty population table yields no candidates regardless of `max`.
TEST_F(SelectLeakCandidatesTest, EmptyTableReturnsZero) {
    LivenessTracker *tracker = LivenessTracker::instance();

    KlassCandidate out[5];
    int count = tracker->selectLeakCandidates(out, 5);

    EXPECT_EQ(count, 0);
}

// ---------------------------------------------------------------------------
// topKlassesByGenerationCount() - ranks by most-recent count_ring sample with
// no trend/hysteresis gate, as a fast follow-up ranking once hasLeakSignal()
// has fired. Returns stable_class_tag, NOT the classMap dictionary klass_id;
// klassPopulationRecordForTest() never mints one (it bypasses
// foldKlassCountsLocked()), so tests set it explicitly with a value distinct
// from klass_id, so a mistaken klass_id assertion fails loudly.
// ---------------------------------------------------------------------------

// A single sample is enough to rank - the point of skipping the gate.
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

// Unminted stable_class_tag (no live instance resolved): skipped, not a bogus tag.
TEST_F(SelectLeakCandidatesTest, TopKlassesByGenerationCountSkipsUnmintedStableClassTag) {
    LivenessTracker *tracker = LivenessTracker::instance();

    const u16 single[1] = {42};
    seedSeries(tracker, /*klass_id=*/7, single, 1, /*start_epoch=*/1);
    // Deliberately no klassPopulationSetStableClassTagForTest() call.

    u32 out[5];
    int count = tracker->topKlassesByGenerationCount(out, 5);

    EXPECT_EQ(count, 0);
}

// Ranking is by the MOST RECENT sample, not the peak or the mean.
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

// Flat or shrinking populations still rank here: no growth-direction gate.
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
// Heap-wide time-to-OOM projection (secondsToOOM()): the fast, heap-wide gap
// the per-klass gate leaves open - it can take longer to trust a candidate
// than a fast leak has left before OOM (ReferenceChainTracker's
// OOM_URGENT_THRESHOLD_S path). Exercises the heap-floor rings via
// heapFloorRecordForTest(); setMaxHeapBytesForTest() avoids the
// JNI-dependent HeapUsage::getMaxHeap() call.
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

    // Ten samples, one second apart, rising exactly 100MiB/s.
    static void seedRisingFloor(LivenessTracker *tracker) {
        for (int i = 0; i < 10; i++) {
            tracker->heapFloorRecordForTest(1000 * MiB + (u64)i * 100 * MiB,
                                             (u64)i * SEC_NS);
        }
    }
};

// Fewer than the 10-sample minimum the ringThirdsStats() gate applies.
TEST_F(SecondsToOOMTest, NotEnoughSamplesReturnsNegative) {
    LivenessTracker *tracker = LivenessTracker::instance();
    tracker->setMaxHeapBytesForTest((jlong)(2800 * MiB));
    for (int i = 0; i < 9; i++) {
        tracker->heapFloorRecordForTest(1000 * MiB + (u64)i * 100 * MiB,
                                         (u64)i * SEC_NS);
    }
    EXPECT_LT(tracker->secondsToOOM(), 0.0);
}

// A flat floor (zero delta between earliest and recent thirds) is not rising.
TEST_F(SecondsToOOMTest, FlatFloorReturnsNegative) {
    LivenessTracker *tracker = LivenessTracker::instance();
    tracker->setMaxHeapBytesForTest((jlong)(2800 * MiB));
    for (int i = 0; i < 10; i++) {
        tracker->heapFloorRecordForTest(1000 * MiB, (u64)i * SEC_NS);
    }
    EXPECT_LT(tracker->secondsToOOM(), 0.0);
}

// Floor history only accumulates inside _gc_generations; no projecting stale rings.
TEST_F(SecondsToOOMTest, GcGenerationsDisabledReturnsNegative) {
    LivenessTracker *tracker = LivenessTracker::instance();
    tracker->setMaxHeapBytesForTest((jlong)(2800 * MiB));
    seedRisingFloor(tracker);
    tracker->setGcGenerationsForTest(false);

    EXPECT_LT(tracker->secondsToOOM(), 0.0);
}

// A rising floor is meaningless without a resolved max heap size.
TEST_F(SecondsToOOMTest, UnresolvedMaxHeapReturnsNegative) {
    LivenessTracker *tracker = LivenessTracker::instance();
    tracker->setMaxHeapBytesForTest(-1);
    seedRisingFloor(tracker);

    EXPECT_LT(tracker->secondsToOOM(), 0.0);
}

// 100MiB/s with 1000MiB of headroom projects to ~10 seconds.
TEST_F(SecondsToOOMTest, RisingFloorProjectsExpectedSeconds) {
    LivenessTracker *tracker = LivenessTracker::instance();
    tracker->setMaxHeapBytesForTest((jlong)(2800 * MiB));
    seedRisingFloor(tracker);

    EXPECT_NEAR(tracker->secondsToOOM(), 9.0, 1e-6);
}

// The recent-third mean has reached the max heap size - exhaustion is now.
TEST_F(SecondsToOOMTest, FloorAtMaxHeapReturnsZero) {
    LivenessTracker *tracker = LivenessTracker::instance();
    tracker->setMaxHeapBytesForTest((jlong)(1800 * MiB)); // == recent third's mean
    seedRisingFloor(tracker);

    EXPECT_EQ(tracker->secondsToOOM(), 0.0);
}

// ---------------------------------------------------------------------------
// Leak tag pool: hands out JVMTI tags in [LEAK_TAG_BASE, LEAK_TAG_BASE + 256)
// and recycles them on release. Exercises the pure pool mechanics;
// tagLeakInstances() itself needs a live JVM (SetTag).
// ---------------------------------------------------------------------------
class LeakTagPoolTest : public ::testing::Test {
protected:
    void SetUp() override {
        LivenessTracker::instance()->leakTagPoolResetForTest();
    }
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
    u64 stale_ctid = 12345;
    jint stale_tid = 12345;
    EXPECT_FALSE(tracker->getLeakTagInfo(tag, &stale_ctid, &stale_tid))
        << "released tag still reports info";

    // Free count restored; the released tag is recycled first (LIFO).
    EXPECT_EQ(pool_size, tracker->leakTagFreeCountForTest());
    jlong re_tag = tracker->acquireLeakTagForTest(43, 100);
    EXPECT_EQ(tag, re_tag) << "released tag should be recycled first (LIFO)";
    EXPECT_EQ(pool_size - 1, tracker->leakTagFreeCountForTest());
}

TEST_F(LeakTagPoolTest, ReleaseOutsidePoolRangeIsIgnored) {
    LivenessTracker *tracker = LivenessTracker::instance();
    jlong base = tracker->leakTagBaseForTest();
    int free_before = tracker->leakTagFreeCountForTest();

    // Out-of-range tags (frontier, class, one-past-the-end) are all rejected.
    tracker->releaseLeakTagForTest(1);
    tracker->releaseLeakTagForTest(-1);
    tracker->releaseLeakTagForTest(0);
    tracker->releaseLeakTagForTest(base + tracker->leakTagPoolSizeForTest());
    tracker->releaseLeakTagForTest(base - 1);

    EXPECT_EQ(free_before, tracker->leakTagFreeCountForTest())
        << "out-of-range releases must not corrupt the free list";
}

// ---------------------------------------------------------------------------
// Chase-phase admission boost (admitForTracking()/noteSelectedCandidates()/
// setUrgentTracking(), livenessTracker.h). The gate is JNI-free pure logic,
// so it is testable without a live JVM; only track() beyond it needs JNIEnv.
//
// Determinism: admissionResetForTest() forces the subsample ratio to 0 and
// clears this thread's RNG, so an unboosted tid's first draw from a freshly
// seeded mt19937 is strictly in (0,1) - ratio 0 can never admit.
// ---------------------------------------------------------------------------
class AdmissionBoostTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<LIVENESS_TRACKER_TEST_NAME>();
        LivenessTracker::instance()->admissionResetForTest();
    }

    void TearDown() override {
        // Leave clean: leftover watched tids / urgency would 100%-admit later tests.
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

// Watched tid admitted even though ratio (0) would reject it - boost precedes draw.
TEST_F(AdmissionBoostTest, WatchedTidAdmittedDespiteRejectingRatio) {
    LivenessTracker *tracker = LivenessTracker::instance();
    KlassCandidate kc;
    fillCandidate(&kc, /*tid=*/42);
    tracker->noteSelectedCandidates(&kc, 1);

    EXPECT_TRUE(tracker->admitForTrackingForTest(42));
    // An unwatched tid falls through to the ratio draw and is rejected.
    EXPECT_FALSE(tracker->admitForTrackingForTest(43));
}

// Urgency admits everything - any tid, watched or not.
TEST_F(AdmissionBoostTest, UrgencyAdmitsAllTids) {
    LivenessTracker *tracker = LivenessTracker::instance();
    tracker->setUrgentTracking(true);
    EXPECT_TRUE(tracker->admitForTrackingForTest(1234));
    EXPECT_TRUE(tracker->admitForTrackingForTest(5678));

    // Releasing urgency restores the ratio gate: unwatched tids reject again.
    tracker->setUrgentTracking(false);
    EXPECT_FALSE(tracker->admitForTrackingForTest(1234));
    KlassCandidate kc;
    fillCandidate(&kc, 1234);
    tracker->noteSelectedCandidates(&kc, 1);
    EXPECT_TRUE(tracker->admitForTrackingForTest(1234));
}

// noteSelectedCandidates() dedupes shared tids and caps at MAX_QUALIFYING_TIDS.
TEST_F(AdmissionBoostTest, WatchedTidsAreDedupedAndCapped) {
    LivenessTracker *tracker = LivenessTracker::instance();
    constexpr int kMax = KlassCandidate::MAX_QUALIFYING_TIDS;  // 8

    // 5 tids each, tids 3 and 4 shared: union is 1..7 in candidate order.
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

    // Union exceeding the cap (1..8 then 9): earlier tids kept, tid 9 not admitted.
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

// A zero-candidate poll clears the watched set (OS tids are reused - no stale admits).
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
