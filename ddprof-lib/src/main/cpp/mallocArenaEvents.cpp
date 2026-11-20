/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mallocArenaEvents.h"

#include <string.h>

#include "jfrMetadata.h"

namespace {

// Field order and types must match the metadata of datadog.MallocArenaWarning
// and datadog.MallocArenaStats in jfrMetadata.cpp.

void putString(Buffer* buf, const char* s) {
  if (s == NULL) {
    s = "";
  }
  buf->putUtf8(s, (u32)strnlen(s, MallocArenaEvents::MAX_STRING_BYTES));
}

// A negative value (-1 marks "not available") is written as the 64-bit
// two's complement pattern, which putVar64() encodes in 9 bytes.
void putLong(Buffer* buf, long long v) { buf->putVar64((u64)v); }

void putInt(Buffer* buf, int v) { buf->putVar32((u32)v); }

// The size prefix is a fixed 5-byte varint, so the event size can exceed 127
// bytes without moving the payload.
int beginEvent(Buffer* buf, JfrType type, u64 ticks) {
  int start = buf->skip(5);
  buf->putVar64(type);
  buf->putVar64(ticks);
  return start;
}

void endEvent(Buffer* buf, int start) {
  buf->putVar32(start, (u32)(buf->offset() - start));
}

}  // namespace

void MallocArenaEvents::writeStats(Buffer* buf, u64 ticks,
                                   const MallocArenaStatsRecord& r) {
  int start = beginEvent(buf, T_MALLOC_ARENA_STATS, ticks);
  putInt(buf, r.arenaCount);
  putLong(buf, r.nonMainArenaBytes);
  putLong(buf, r.freeHeldBytes);
  putLong(buf, r.largestArenaBytes);
  putInt(buf, r.cpuQuotaMilli);
  putLong(buf, r.memoryLimit);
  putLong(buf, r.maxHeap);
  putString(buf, r.walkStatus);
  endEvent(buf, start);
}

void MallocArenaEvents::writeWarning(Buffer* buf, u64 ticks, const char* state,
                                     const MallocArenaWarningRecord& r) {
  const MallocArenaEvaluation& e = r.evaluation;
  int start = beginEvent(buf, T_MALLOC_ARENA_WARNING, ticks);
  putString(buf, state);
  putInt(buf, r.arenaCount);
  putInt(buf, r.arenaLimit);
  putString(buf, r.arenaLimitSource);
  putInt(buf, r.onlineCpus);
  putInt(buf, r.cpuQuotaMilli);
  putLong(buf, r.memoryLimit);
  putString(buf, r.memoryLimitSource);
  putLong(buf, r.maxHeap);
  putLong(buf, (long long)e.nativeHeadroom);
  putString(buf, e.headroomSource);
  buf->put8(e.heapExceedsLimit ? 1 : 0);
  putLong(buf, r.freeHeldBytes);
  putLong(buf, r.nonMainArenaBytes);
  putString(buf, e.conditionMeasure);
  putInt(buf, r.thresholdPercent);
  putInt(buf, r.threadPrivateArenas);
  putLong(buf, r.largestArenaBytes);
  putLong(buf, r.largestArenaMaxBytes);
  putInt(buf, e.recommendedArenaMax);
  putString(buf, r.glibcVersion);
  putString(buf, r.layout);
  putString(buf, r.walkStatus);
  endEvent(buf, start);
}
