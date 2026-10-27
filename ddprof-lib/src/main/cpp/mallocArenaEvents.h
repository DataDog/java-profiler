/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _MALLOCARENAEVENTS_H
#define _MALLOCARENAEVENTS_H

#include "arch.h"
#include "buffers.h"
#include "mallocArenaRule.h"

// Payload of datadog.MallocArenaStats, one event per JFR chunk. A value that
// is not available is -1.
struct MallocArenaStatsRecord {
  int arenaCount;
  long long nonMainArenaBytes;
  long long freeHeldBytes;      // -1 without mallinfo2
  long long largestArenaBytes;
  int cpuQuotaMilli;            // <= 0 means no quota
  long long memoryLimit;
  long long maxHeap;            // -1 when unknown
  const char* walkStatus;       // arenaWalkStatusName() of the walk
};

// Payload of datadog.MallocArenaWarning. The derived values (headroom, its
// source, the compared measure, the recommended arena limit) come from
// evaluation. A value that is not available is -1.
struct MallocArenaWarningRecord {
  int arenaCount;
  int arenaLimit;
  const char* arenaLimitSource;
  int onlineCpus;
  int cpuQuotaMilli;            // <= 0 means no quota
  long long memoryLimit;
  const char* memoryLimitSource;
  long long maxHeap;            // -1 when unknown
  long long freeHeldBytes;      // -1 without mallinfo2
  long long nonMainArenaBytes;
  int thresholdPercent;
  int threadPrivateArenas;      // -1 without attached_threads
  long long largestArenaBytes;
  long long largestArenaMaxBytes;
  const char* glibcVersion;
  const char* layout;
  const char* walkStatus;
  MallocArenaEvaluation evaluation;
};

// Serializers of the arena events. Each writer emits the complete event,
// including its size prefix, and does not flush: the caller calls
// flushIfNeeded(). String fields are written inline (no constant pool),
// truncated to MAX_STRING_BYTES; a null string is written as "".
namespace MallocArenaEvents {

static const u32 MAX_STRING_BYTES = 32;

void writeStats(Buffer* buf, u64 ticks, const MallocArenaStatsRecord& record);

// state is MallocArenaWarningState::name() of the transition being reported.
void writeWarning(Buffer* buf, u64 ticks, const char* state,
                  const MallocArenaWarningRecord& record);

}  // namespace MallocArenaEvents

#endif  // _MALLOCARENAEVENTS_H
