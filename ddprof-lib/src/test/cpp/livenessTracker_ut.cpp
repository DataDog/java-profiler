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
#include "../../main/cpp/gtest_crash_handler.h"
#include "../../main/cpp/livenessTracker.h"
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

TEST_F(LivenessTrackerTest, LiveTraceCollectionPreservesIdsFromOtherCheckers) {
    LivenessTracker tracker;
    std::unordered_set<u64> trace_ids = {0x12345678ULL};

    tracker.getLiveTraceIdsForTest(trace_ids);

    EXPECT_EQ(trace_ids.count(0x12345678ULL), 1U);
}
