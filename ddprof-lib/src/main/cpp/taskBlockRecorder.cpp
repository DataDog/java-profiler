/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "taskBlockRecorder.h"

#include <atomic>

static const u64 kMinTaskBlockNanos = 1000000; // 1 ms
static std::atomic<u64> g_min_task_block_ticks{0};

static u64 computeMinTaskBlockTicks() {
  return (TSC::frequency() * kMinTaskBlockNanos) / NANOTIME_FREQ;
}

void initializeTaskBlockDurationThreshold() {
  g_min_task_block_ticks.store(computeMinTaskBlockTicks(), std::memory_order_release);
}

bool exceedsMinTaskBlockDuration(u64 start_ticks, u64 end_ticks) {
  u64 min_ticks = g_min_task_block_ticks.load(std::memory_order_acquire);
  if (min_ticks == 0) {
    min_ticks = computeMinTaskBlockTicks();
  }
  return end_ticks > start_ticks && (end_ticks - start_ticks) >= min_ticks;
}
