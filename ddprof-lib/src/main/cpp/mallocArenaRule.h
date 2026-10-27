/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _MALLOCARENARULE_H
#define _MALLOCARENARULE_H

#include "arch.h"

// Per-chunk inputs of the glibc malloc arena warning rule. All values are
// plain numbers, so the rule can be evaluated without touching the arena walk
// or the process environment.
struct MallocArenaRuleInput {
  bool walkOk;           // the arena walk produced a trustworthy arenaCount
  int arenaCount;
  u64 nonMainArenaBytes; // committed system_mem of the non-main arenas
  bool hasFreeHeld;      // freeHeldBytes is valid (mallinfo2 available)
  u64 freeHeldBytes;     // mallinfo2().fordblks
  long cpuQuotaMilli;    // CPU quota in milli-CPUs; <= 0 means no quota
  long memoryLimit;      // memory limit in bytes; <= 0 means unknown
  long long maxHeap;     // Runtime.maxMemory(); <= 0 or INT64_MAX means unknown
  int thresholdPercent;  // 0 disables the warning
};

struct MallocArenaEvaluation {
  bool cond1;                   // arenaCount exceeds recommendedArenaMax
  bool cond2;                   // measureBytes exceeds thresholdPercent of nativeHeadroom
  bool active;                  // walkOk && cond1 && cond2
  int recommendedArenaMax;      // 8 * ceil(quota CPUs); 0 when there is no quota
  u64 nativeHeadroom;           // memoryLimit minus maxHeap, or memoryLimit; 0 when the limit is unknown
  const char* headroomSource;   // "limit-minus-heap" or "limit-only"
  bool heapExceedsLimit;        // maxHeap >= memoryLimit
  const char* conditionMeasure; // "free-held" or "committed"
  u64 measureBytes;             // the value compared against the headroom
};

// Pure function: no I/O, no allocation, no global state.
MallocArenaEvaluation evaluateMallocArenaRule(const MallocArenaRuleInput& in);

// Raised/worsened/cleared state machine for the arena warning. A transition
// is reported once, not on every chunk.
class MallocArenaWarningState {
public:
  enum Transition { NONE, RAISED, WORSENED, CLEARED };

  MallocArenaWarningState() : _current(NONE), _last_measure(0) {}

  // Advances the state by one chunk. valid == false (the walk failed) keeps
  // the state and returns NONE. While a warning is raised, WORSENED is
  // returned when measure is at least 125% of the measure at the last
  // RAISED or WORSENED transition (growth of 25% or more). An active state
  // implies measure > 0.
  Transition step(bool valid, bool active, u64 measure);

  bool active() const { return _current != NONE; }

  // RAISED or WORSENED for the last emitted warning; NONE when idle.
  Transition current() const { return _current; }

  // "raised", "worsened" or "cleared"; "" for NONE.
  static const char* name(Transition t);

private:
  Transition _current;
  u64 _last_measure;
};

#endif // _MALLOCARENARULE_H
