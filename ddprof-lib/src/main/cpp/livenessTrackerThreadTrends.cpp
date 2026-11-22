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

  // With the incumbent table full, a newcomer ALWAYS accumulates in the challenger pool - even
  // when a sub-bar (count < TID_RETAINED_COUNT_BAR) incumbent sits in the table. Immediate
  // sub-bar eviction let two alternating single-sample threads overwrite the same slot every
  // epoch (each reset to count 1), so a genuinely-present thread could never reach the bar and
  // qualify. Challenger promotion (promoteThreadGenCandidates()) is the only path back into the
  // incumbent table, and it requires the challenger to OUTRANK the weakest incumbent - sub-bar
  // incumbents therefore survive newcomer churn while real threads keep accumulating samples.
  // A newcomer that lands on a full challenger pool recycles only a count-1 (single-sample)
  // challenger: bounded pool churn that can never displace an incumbent.
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

void LivenessTracker::promoteThreadGenCandidates(
    KlassCountScratch &scratch, KlassCountScratch::ThreadGens *displaced,
    int *displaced_count) {
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
      if (displaced != nullptr && displaced_count != nullptr &&
          *displaced_count < KlassCountScratch::MAX_THREAD_CHALLENGERS_PER_KLASS) {
        displaced[(*displaced_count)++] = weakest;
      }
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
  KlassCountScratch::ThreadGens displaced
      [KlassCountScratch::MAX_THREAD_CHALLENGERS_PER_KLASS];
  int displaced_count = 0;
  promoteThreadGenCandidates(scratch, displaced, &displaced_count);
  KlassPopulationEntry &entry = _klass_population[slot];
  auto push_trend_sample =
      [&](KlassPopulationEntry::TidTrend *trend,
          const KlassCountScratch::ThreadGens &gen) {
        trend->ring[trend->ring_head] = (u8)gen.age_count;
        trend->count_ring[trend->ring_head] =
            (u8)std::min<u32>(gen.count, UINT8_MAX);
        trend->ring_head =
            (u8)((trend->ring_head + 1) %
                 KlassPopulationEntry::TID_TREND_RING_SIZE);
        if (trend->ring_fill < KlassPopulationEntry::TID_TREND_RING_SIZE) {
          trend->ring_fill++;
        }
        if (tidPushQualifies(*trend, gen.count)) {
          if (trend->consecutive_positive < UINT8_MAX) {
            trend->consecutive_positive++;
          }
        } else {
          trend->consecutive_positive = 0;
        }
      };
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
        // A takeover must be earned against the victim's accumulated evidence, not just its
        // (possibly just-reset) hysteresis counter: a trend whose consecutive_positive was just
        // reset still carries its pre-reset retained counts, and a single-sample newcomer must
        // not take that slot unconditionally. A candidate victim is therefore unsustained
        // (consecutive_positive == 0) AND dead-enough: either its ring ends in two or more zero
        // epochs (the thread is really gone - its history no longer matters) or its newest live
        // retained count is below the newcomer's current epoch count. Among the qualifying
        // candidates the weakest (lowest consecutive_positive, then ring_fill) loses its slot.
        // No qualifying victim: the newcomer is dropped - bounded, it retries on a later epoch
        // (no new state; the scan is O(candidates x ring) with both constants bounded: 8 x 16).
        const u8 incoming_count =
            (u8)std::min<u32>(scratch.threads[ti].count, UINT8_MAX);
        int victim = -1;
        for (int i = 0; i < entry.tid_trend_count; i++) {
          KlassPopulationEntry::TidTrend &candidate = entry.tid_trends[i];
          if (candidate.synthetic) {
            continue;
          }
          if (candidate.consecutive_positive != 0) {
            continue; // still sustaining its qualification - never a victim
          }
          u8 trailing_zeros = 0;
          u8 last_live_count = 0;
          for (int k = 0; k < candidate.ring_fill; k++) {
            u8 sample = candidate.count_ring[(candidate.ring_head +
                KlassPopulationEntry::TID_TREND_RING_SIZE - 1 - k) %
                KlassPopulationEntry::TID_TREND_RING_SIZE];
            if (sample == 0) {
              trailing_zeros++;
              continue;
            }
            last_live_count = sample;
            break;
          }
          if (trailing_zeros < 2 && last_live_count >= incoming_count) {
            continue; // just reset (one skipped epoch) or present-but-unsustained, and still
                      // hotter than the newcomer: the accumulated evidence keeps the slot
          }
          if (victim < 0 ||
              (candidate.consecutive_positive <
                   entry.tid_trends[victim].consecutive_positive) ||
              (candidate.consecutive_positive ==
                   entry.tid_trends[victim].consecutive_positive &&
               candidate.ring_fill < entry.tid_trends[victim].ring_fill)) {
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
    push_trend_sample(trend, scratch.threads[ti]);
  }
  // A promotion that replaced an incumbent discarded the victim's current-epoch sample: the
  // absent-tid pass below would write the still-live thread a zero epoch and reset its
  // qualification. A displaced incumbent with a tracked (non-synthetic) trend records its live
  // sample instead; one without a trend slot has no qualification to lose.
  for (int d = 0; d < displaced_count; d++) {
    KlassPopulationEntry::TidTrend *trend = nullptr;
    for (int i = 0; i < entry.tid_trend_count; i++) {
      if (entry.tid_trends[i].tid == displaced[d].tid) {
        trend = &entry.tid_trends[i];
        break;
      }
    }
    if (trend == nullptr || trend->synthetic) {
      continue;
    }
    push_trend_sample(trend, displaced[d]);
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
    for (int d = 0; !present && d < displaced_count; d++) {
      present = displaced[d].tid == trend.tid;
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
