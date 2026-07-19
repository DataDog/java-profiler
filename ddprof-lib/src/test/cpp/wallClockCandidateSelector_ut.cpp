/*
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "wallClockCandidateSelector.h"

#include <numeric>
#include <random>
#include <set>
#include <vector>

static std::vector<int> makeCandidates(size_t count) {
    std::vector<int> candidates(count);
    std::iota(candidates.begin(), candidates.end(), 0);
    return candidates;
}

TEST(WallClockCandidateSelectorTest, VisitsOnlyTargetSizeWithoutRejections) {
    std::vector<int> candidates = makeCandidates(1000);
    std::mt19937 generator(1234);
    std::set<int> selected;

    WallClockCandidateStats stats = selectWallClockCandidates(
        candidates, 10, 40, generator, [&](int tid) {
            selected.insert(tid);
            return WallClockCandidateOutcome::SIGNAL_SENT;
        });

    EXPECT_EQ(10u, stats.visited);
    EXPECT_EQ(10u, stats.slots_consumed);
    EXPECT_EQ(0u, stats.precheck_rejected);
    EXPECT_EQ(10u, selected.size());
}

TEST(WallClockCandidateSelectorTest, PrecheckRejectedCandidatesAreBackfilled) {
    std::vector<int> candidates = makeCandidates(100);
    std::mt19937 generator(42);
    std::set<int> selected;

    WallClockCandidateStats stats = selectWallClockCandidates(
        candidates, 8, 100, generator, [&](int tid) {
            if ((tid & 1) == 0) {
                return WallClockCandidateOutcome::PRECHECK_REJECTED;
            }
            selected.insert(tid);
            return WallClockCandidateOutcome::SIGNAL_SENT;
        });

    EXPECT_EQ(8u, stats.slots_consumed);
    EXPECT_EQ(stats.slots_consumed + stats.precheck_rejected, stats.visited);
    EXPECT_EQ(8u, selected.size());
    for (int tid : selected) {
        EXPECT_EQ(1, tid & 1);
    }
}

TEST(WallClockCandidateSelectorTest, AllPrecheckRejectedCandidatesRespectVisitLimit) {
    std::vector<int> candidates = makeCandidates(257);
    std::mt19937 generator(7);
    std::set<int> visited;

    WallClockCandidateStats stats = selectWallClockCandidates(
        candidates, 10, 40, generator, [&](int tid) {
            visited.insert(tid);
            return WallClockCandidateOutcome::PRECHECK_REJECTED;
        });

    EXPECT_EQ(40u, stats.visited);
    EXPECT_EQ(0u, stats.slots_consumed);
    EXPECT_EQ(40u, stats.precheck_rejected);
    EXPECT_EQ(40u, visited.size());
    EXPECT_TRUE(stats.visit_limit_reached);
}

TEST(WallClockCandidateSelectorTest, SignalFailureConsumesCapacityWithoutBackfill) {
    std::vector<int> candidates{1, 2, 3, 4, 5};
    std::mt19937 generator(17);
    int callbacks = 0;

    WallClockCandidateStats stats = selectWallClockCandidates(
        candidates, 3, 12, generator, [&](int) {
            callbacks++;
            return WallClockCandidateOutcome::SIGNAL_FAILED;
        });

    EXPECT_EQ(3, callbacks);
    EXPECT_EQ(3u, stats.visited);
    EXPECT_EQ(3u, stats.slots_consumed);
    EXPECT_EQ(0u, stats.precheck_rejected);
}

TEST(WallClockCandidateSelectorTest, EmptyBoundsDoNoWork) {
    std::vector<int> candidates{1, 2, 3};
    std::vector<int> empty;
    std::mt19937 generator(1);
    int callbacks = 0;
    auto visitor = [&](int) {
        callbacks++;
        return WallClockCandidateOutcome::SIGNAL_SENT;
    };

    WallClockCandidateStats zero_target =
        selectWallClockCandidates(candidates, 0, 3, generator, visitor);
    WallClockCandidateStats empty_input =
        selectWallClockCandidates(empty, 3, 3, generator, visitor);
    WallClockCandidateStats zero_visits =
        selectWallClockCandidates(candidates, 3, 0, generator, visitor);

    EXPECT_EQ(0, callbacks);
    EXPECT_EQ(0u, zero_target.visited);
    EXPECT_EQ(0u, empty_input.visited);
    EXPECT_EQ(0u, zero_visits.visited);
}

TEST(WallClockCandidateSelectorTest, FixedSeedProducesDeterministicTraversal) {
    std::vector<int> first = makeCandidates(50);
    std::vector<int> second = first;
    std::mt19937 first_generator(2026);
    std::mt19937 second_generator(2026);
    std::vector<int> first_result;
    std::vector<int> second_result;

    selectWallClockCandidates(first, 12, 24, first_generator, [&](int tid) {
        first_result.push_back(tid);
        return WallClockCandidateOutcome::SIGNAL_SENT;
    });
    selectWallClockCandidates(second, 12, 24, second_generator, [&](int tid) {
        second_result.push_back(tid);
        return WallClockCandidateOutcome::SIGNAL_SENT;
    });

    EXPECT_EQ(first_result, second_result);
}

TEST(WallClockCandidateSelectorTest, RandomizedPrefixRemainsFairAcrossCandidates) {
    constexpr int candidate_count = 20;
    constexpr int sample_size = 4;
    constexpr int rounds = 10000;
    std::vector<int> candidates(candidate_count);
    std::vector<int> selections(candidate_count, 0);
    std::mt19937 generator(2026);

    for (int round = 0; round < rounds; ++round) {
        std::iota(candidates.begin(), candidates.end(), 0);
        WallClockCandidateStats stats = selectWallClockCandidates(
            candidates, sample_size, sample_size, generator, [&](int candidate) {
                selections[candidate]++;
                return WallClockCandidateOutcome::SIGNAL_SENT;
            });
        ASSERT_EQ(sample_size, stats.slots_consumed);
    }

    constexpr int expected = rounds * sample_size / candidate_count;
    for (int count : selections) {
        EXPECT_NEAR(expected, count, expected / 10);
    }
}

TEST(WallClockCandidateSelectorTest, ExhaustingInputDoesNotReportVisitLimit) {
    std::vector<int> candidates{1, 2, 3};
    std::mt19937 generator(8);

    WallClockCandidateStats stats = selectWallClockCandidates(
        candidates, 5, 20, generator,
        [](int) { return WallClockCandidateOutcome::PRECHECK_REJECTED; });

    EXPECT_EQ(3u, stats.visited);
    EXPECT_EQ(3u, stats.precheck_rejected);
    EXPECT_FALSE(stats.visit_limit_reached);
}
