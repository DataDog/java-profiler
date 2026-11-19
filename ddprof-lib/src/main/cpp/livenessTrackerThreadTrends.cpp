/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "livenessTracker.h"

#include <algorithm>
#include <cstdint>

void LivenessTracker::insertThreadGen(KlassCountScratch &scratch, jint tid,
                                      u32 age) {
  auto add_sample = [age](KlassCountScratch::ThreadGens &thread) {
    thread.count++;
    for (u32 i = 0; i < thread.age_count; i++) {
      if (thread.ages[i] == age) {
        return;
      }
    }
    if (thread.age_count >= KlassCountScratch::MAX_AGES_PER_THREAD) {
      return;
    }
    u32 pos = thread.age_count;
    for (u32 i = 0; i < thread.age_count; i++) {
      if (age < thread.ages[i]) {
        pos = i;
        break;
      }
    }
    for (u32 i = thread.age_count; i > pos; i--) {
      thread.ages[i] = thread.ages[i - 1];
    }
    thread.ages[pos] = age;
    thread.age_count++;
  };
  auto initialize = [tid, age](KlassCountScratch::ThreadGens &thread) {
    thread.tid = tid;
    thread.ages[0] = age;
    thread.age_count = 1;
    thread.count = 1;
  };

  for (int i = 0; i < scratch.thread_count; i++) {
    if (scratch.threads[i].tid == tid) {
      add_sample(scratch.threads[i]);
      return;
    }
  }
  for (int i = 0; i < scratch.challenger_count; i++) {
    if (scratch.challengers[i].tid == tid) {
      add_sample(scratch.challengers[i]);
      return;
    }
  }
  if (scratch.thread_count < KlassCountScratch::MAX_THREADS_PER_KLASS) {
    initialize(scratch.threads[scratch.thread_count++]);
    return;
  }

  int victim = 0;
  for (int i = 1; i < scratch.thread_count; i++) {
    const auto &candidate = scratch.threads[i];
    const auto &current = scratch.threads[victim];
    if (candidate.count < current.count ||
        (candidate.count == current.count &&
         candidate.age_count < current.age_count)) {
      victim = i;
    }
  }
  if (scratch.threads[victim].count < TID_RETAINED_COUNT_BAR) {
    initialize(scratch.threads[victim]);
    return;
  }

  // Qualified incumbents stay intact while challengers accumulate a full-epoch count.
  if (scratch.challenger_count <
      KlassCountScratch::MAX_THREAD_CHALLENGERS_PER_KLASS) {
    initialize(scratch.challengers[scratch.challenger_count++]);
    return;
  }
  int weakest = 0;
  for (int i = 1; i < scratch.challenger_count; i++) {
    const auto &candidate = scratch.challengers[i];
    const auto &current = scratch.challengers[weakest];
    if (candidate.count < current.count ||
        (candidate.count == current.count &&
         candidate.age_count < current.age_count)) {
      weakest = i;
    }
  }
  if (scratch.challengers[weakest].count == 1) {
    initialize(scratch.challengers[weakest]);
  }
}

void LivenessTracker::promoteThreadGenCandidates(KlassCountScratch &scratch) {
  for (int i = 0; i < scratch.challenger_count; i++) {
    const auto &candidate = scratch.challengers[i];
    if (scratch.thread_count < KlassCountScratch::MAX_THREADS_PER_KLASS) {
      scratch.threads[scratch.thread_count++] = candidate;
      continue;
    }
    int victim = 0;
    for (int j = 1; j < scratch.thread_count; j++) {
      const auto &current = scratch.threads[victim];
      const auto &next = scratch.threads[j];
      if (next.count < current.count ||
          (next.count == current.count && next.age_count < current.age_count)) {
        victim = j;
      }
    }
    const auto &weakest = scratch.threads[victim];
    // A complete challenger must outrank the weakest incumbent to replace it.
    if (candidate.count > weakest.count ||
        (candidate.count == weakest.count &&
         candidate.age_count > weakest.age_count)) {
      scratch.threads[victim] = candidate;
    }
  }
  scratch.challenger_count = 0;
}

void LivenessTracker::recordTidTrendSamplesLocked(
    int slot, KlassCountScratch &scratch) {
  if (slot < 0 || slot >= _klass_population_size) {
    return;
  }
  promoteThreadGenCandidates(scratch);
  KlassPopulationEntry &entry = _klass_population[slot];
  // Present tids first: find-or-create their trend and push this epoch's
  // distinct-age count. Every scratch thread has a surviving instance.
  for (int ti = 0; ti < scratch.thread_count; ti++) {
    jint tid = scratch.threads[ti].tid;
    KlassPopulationEntry::TidTrend *trend = nullptr;
    for (int i = 0; i < entry.tid_trend_count; i++) {
      if (entry.tid_trends[i].tid == tid) {
        trend = &entry.tid_trends[i];
        break;
      }
    }
    if (trend != nullptr && trend->synthetic) {
      continue;
    }
    if (trend == nullptr) {
      if (entry.tid_trend_count < KlassPopulationEntry::MAX_TID_TRENDS) {
        trend = &entry.tid_trends[entry.tid_trend_count++];
      } else {
        int victim = -1;
        for (int i = 0; i < entry.tid_trend_count; i++) {
          if (entry.tid_trends[i].synthetic) {
            continue;
          }
          if (victim < 0 ||
              (entry.tid_trends[i].consecutive_positive <
               entry.tid_trends[victim].consecutive_positive) ||
              (entry.tid_trends[i].consecutive_positive ==
                   entry.tid_trends[victim].consecutive_positive &&
               entry.tid_trends[i].ring_fill <
                   entry.tid_trends[victim].ring_fill)) {
            victim = i;
          }
        }
        if (victim < 0) {
          continue;
        }
        trend = &entry.tid_trends[victim];
      }
      trend->tid = tid;
      trend->ring_head = 0;
      trend->ring_fill = 0;
      trend->consecutive_positive = 0;
      trend->synthetic = false;
    }
    trend->ring[trend->ring_head] = (u8)scratch.threads[ti].age_count;
    trend->count_ring[trend->ring_head] =
        (u8)std::min<u32>(scratch.threads[ti].count, UINT8_MAX);
    trend->ring_head = (u8)((trend->ring_head + 1) %
                            KlassPopulationEntry::TID_TREND_RING_SIZE);
    if (trend->ring_fill < KlassPopulationEntry::TID_TREND_RING_SIZE) {
      trend->ring_fill++;
    }
    if (tidPushQualifies(*trend, scratch.threads[ti].count)) {
      if (trend->consecutive_positive < UINT8_MAX) {
        trend->consecutive_positive++;
      }
    } else {
      trend->consecutive_positive = 0;
    }
  }
  // Absent tids receive a zero epoch so stale trends cannot remain qualified.
  for (int i = 0; i < entry.tid_trend_count; i++) {
    KlassPopulationEntry::TidTrend &trend = entry.tid_trends[i];
    if (trend.synthetic) {
      continue;
    }
    bool present = false;
    for (int ti = 0; ti < scratch.thread_count; ti++) {
      if (scratch.threads[ti].tid == trend.tid) {
        present = true;
        break;
      }
    }
    if (present) {
      continue;
    }
    trend.ring[trend.ring_head] = 0;
    trend.count_ring[trend.ring_head] = 0;
    trend.ring_head = (u8)((trend.ring_head + 1) %
                            KlassPopulationEntry::TID_TREND_RING_SIZE);
    if (trend.ring_fill < KlassPopulationEntry::TID_TREND_RING_SIZE) {
      trend.ring_fill++;
    }
    trend.consecutive_positive = 0;
  }
}
