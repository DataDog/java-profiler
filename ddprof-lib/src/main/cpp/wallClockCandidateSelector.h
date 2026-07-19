/*
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef WALL_CLOCK_CANDIDATE_SELECTOR_H
#define WALL_CLOCK_CANDIDATE_SELECTOR_H

#include <algorithm>
#include <cstddef>
#include <random>
#include <utility>
#include <vector>

enum class WallClockCandidateOutcome {
    SIGNAL_SENT,
    SIGNAL_FAILED,
    PRECHECK_REJECTED,
};

struct WallClockCandidateStats {
    size_t visited = 0;
    size_t slots_consumed = 0;
    size_t precheck_rejected = 0;
    bool visit_limit_reached = false;
};

// Visits a uniformly randomized prefix without replacement. A precheck rejection
// is the only outcome that does not consume target capacity. This runs only on
// the wall-clock timer thread.
template <typename T, typename URBG, typename Visitor>
WallClockCandidateStats selectWallClockCandidates(std::vector<T>& candidates,
                                                  size_t target_size,
                                                  size_t visit_limit,
                                                  URBG& generator,
                                                  Visitor&& visitor) {
    WallClockCandidateStats stats;
    if (target_size == 0 || candidates.empty() || visit_limit == 0) {
        return stats;
    }

    size_t max_visits = std::min(candidates.size(), visit_limit);
    for (size_t i = 0; i < max_visits && stats.slots_consumed < target_size; ++i) {
        std::uniform_int_distribution<size_t> next(i, candidates.size() - 1);
        size_t selected = next(generator);
        if (selected != i) {
            std::swap(candidates[i], candidates[selected]);
        }

        stats.visited++;
        WallClockCandidateOutcome outcome = visitor(candidates[i]);
        if (outcome == WallClockCandidateOutcome::PRECHECK_REJECTED) {
            stats.precheck_rejected++;
        } else {
            stats.slots_consumed++;
        }
    }
    stats.visit_limit_reached =
        stats.slots_consumed < target_size &&
        stats.visited == max_visits && max_visits < candidates.size();
    return stats;
}

#endif // WALL_CLOCK_CANDIDATE_SELECTOR_H
