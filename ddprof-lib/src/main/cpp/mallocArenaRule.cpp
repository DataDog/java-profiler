/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mallocArenaRule.h"

// glibc caps the number of arenas at 8 x online CPUs by default.
static const int ARENAS_PER_CPU = 8;

static const long long MAX_HEAP_UNLIMITED = 0x7fffffffffffffffLL;

MallocArenaEvaluation evaluateMallocArenaRule(const MallocArenaRuleInput& in) {
  MallocArenaEvaluation ev;
  ev.cond1 = false;
  ev.cond2 = false;
  ev.active = false;
  ev.recommendedArenaMax = 0;
  ev.nativeHeadroom = 0;
  ev.headroomSource = "limit-only";
  ev.heapExceedsLimit = false;
  ev.conditionMeasure = in.hasFreeHeld ? "free-held" : "committed";
  ev.measureBytes = in.hasFreeHeld ? in.freeHeldBytes : in.nonMainArenaBytes;

  if (in.cpuQuotaMilli > 0) {
    long quotaCpus = in.cpuQuotaMilli / 1000 + (in.cpuQuotaMilli % 1000 != 0 ? 1 : 0);
    if (quotaCpus > 0x7fffffffL / ARENAS_PER_CPU) {
      quotaCpus = 0x7fffffffL / ARENAS_PER_CPU;
    }
    ev.recommendedArenaMax = (int)(quotaCpus * ARENAS_PER_CPU);
    ev.cond1 = in.arenaCount > ev.recommendedArenaMax;
  }

  if (in.memoryLimit > 0) {
    u64 limit = (u64)in.memoryLimit;
    ev.nativeHeadroom = limit;
    if (in.maxHeap > 0 && in.maxHeap != MAX_HEAP_UNLIMITED) {
      if ((u64)in.maxHeap >= limit) {
        ev.heapExceedsLimit = true;
      } else {
        ev.nativeHeadroom = limit - (u64)in.maxHeap;
        ev.headroomSource = "limit-minus-heap";
      }
    }
    if (in.thresholdPercent > 0) {
      // 128-bit products: the byte counts times 100 can exceed 64 bits.
      ev.cond2 = (unsigned __int128)ev.measureBytes * 100 >
                 (unsigned __int128)ev.nativeHeadroom * (unsigned)in.thresholdPercent;
    }
  }

  ev.active = in.walkOk && ev.cond1 && ev.cond2;
  return ev;
}

MallocArenaWarningState::Transition MallocArenaWarningState::step(bool valid, bool active, u64 measure) {
  if (!valid) {
    return NONE;
  }
  if (_current == NONE) {
    if (!active) {
      return NONE;
    }
    _current = RAISED;
    _last_measure = measure;
    return RAISED;
  }
  if (!active) {
    _current = NONE;
    _last_measure = 0;
    return CLEARED;
  }
  if ((unsigned __int128)measure * 4 >= (unsigned __int128)_last_measure * 5) {
    _current = WORSENED;
    _last_measure = measure;
    return WORSENED;
  }
  return NONE;
}

const char* MallocArenaWarningState::name(Transition t) {
  switch (t) {
    case RAISED:   return "raised";
    case WORSENED: return "worsened";
    case CLEARED:  return "cleared";
    default:       return "";
  }
}
