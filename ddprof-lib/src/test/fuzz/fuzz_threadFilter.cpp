/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * libFuzzer target for ThreadFilter / WallClockBlockTracker: the thread
 * identity registry and its wall-clock block-run suppression sidecar (see
 * threadFilter.h / wallClockBlockTracker.h).
 *
 * Input bytes are consumed as a stream of operations against a small, fixed
 * tid domain (deliberately narrow so registration/reuse collisions are
 * frequent):
 *   op < 0x30: registerThread(tid)
 *   op < 0x50: unregisterThread(slot_id) for a tracked tid
 *   op < 0x60: add(tid, slot_id) - context-window enter
 *   op < 0x70: remove(slot_id) - context-window exit
 *   op < 0x90: enterBlockedRun(tracker, slot_id, state)
 *   op < 0xB0: exitBlockedRun(slot_id, generation) - generation-checked; an
 *              extra fuzzed byte decides whether the real generation is used
 *              or corrupted, to exercise the stale-token rejection path
 *   op < 0xD0: exitBlockedRun(slot_id) - unconditional
 *   op < 0xF0: unregisterThreadByTid(tid)
 *   op >= 0xF0: init("", true) - simulates a recording restart, which must
 *               reset both the registry and (via resetRegistrationsLocked ->
 *               WallClockBlockTracker::resetAll()) every slot's block state
 *
 * Each op byte is followed by one more byte selecting the tid (and, for
 * enterBlockedRun and the generation-checked exit, a third byte selecting
 * the OSThreadState / generation-corruption decision respectively).
 *
 * Invariants verified (violation -> __builtin_trap() -> ASan/fuzzer crash):
 *   I1. Single-owner TID mapping: registerThread() rediscovering a tid that
 *       is still live must return the exact slot it was already given, and
 *       no two live tids may ever be mapped to the same slot_id. This is the
 *       same invariant flagged in review as being at risk from
 *       ThreadFilter::add()'s unchecked lazy-index fallback.
 *   I2. activeSlotForId(slot_id, tid) is non-null if and only if the shadow
 *       model still considers tid the current owner of slot_id.
 *   I3. After init() resets the registry, every slot this run ever put into
 *       a blocked run reports UNKNOWN active-block-state and
 *       sampled-this-run == false (resetAll() must have actually run).
 *   I4. A generation-checked exitBlockedRun() called with a generation other
 *       than the block run's current one must return false and must not
 *       change that slot's active-block-state (a stale/forged token must
 *       never clear a newer or already-cleared run).
 *
 * ASan+UBSan (enabled by the fuzz build config) additionally catch any
 * out-of-bounds chunk/tid-index access or use-after-free surfaced by the
 * lazy chunk allocation paths as this drives slot reuse and registry resets.
 */

#include <stddef.h>
#include <stdint.h>
#include <unordered_map>
#include <unordered_set>

#include "threadFilter.h"
#include "wallClockBlockTracker.h"

namespace {

// Deliberately small so the same handful of tids are registered/unregistered
// repeatedly, forcing slot reuse rather than spreading across kMaxThreads.
constexpr int kTidDomain = 16;

ThreadFilter* g_filter = nullptr;
WallClockBlockTracker* g_tracker = nullptr;

// Shadow model: tid -> slot_id for tids the driver believes are currently
// registered (mirrors only calls this fuzzer itself made).
std::unordered_map<int, ThreadFilter::SlotID> g_owner;
// slot_id -> last block-run token, so exitBlockedRun(slot_id, generation) has
// a real generation to check instead of always failing on 0.
std::unordered_map<ThreadFilter::SlotID, u64> g_last_token;
// Every slot that has ever entered a blocked run this run, checked against
// resetAll() after an init() restart.
std::unordered_set<ThreadFilter::SlotID> g_ever_blocked;

void resetShadowState() {
  g_owner.clear();
  g_last_token.clear();
}

} // namespace

extern "C" int LLVMFuzzerInitialize(int* /*argc*/, char*** /*argv*/) {
  g_filter = new ThreadFilter();
  g_tracker = new WallClockBlockTracker();
  g_filter->setBlockTracker(g_tracker);
  g_filter->init("", /*track_unfiltered_wall=*/true);
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) return 0;

  size_t pos = 0;
  auto nextByte = [&]() -> uint8_t { return pos < size ? data[pos++] : 0; };

  while (pos < size) {
    uint8_t op = nextByte();
    int tid = 1 + (nextByte() % kTidDomain);

    if (op < 0x30) {
      ThreadFilter::SlotID slot_id = g_filter->registerThread(tid);
      if (slot_id >= 0) {
        auto it = g_owner.find(tid);
        if (it != g_owner.end() && it->second != slot_id) {
          // A still-live tid must always rediscover the same slot.
          __builtin_trap();
        }
        for (auto& kv : g_owner) {
          if (kv.first != tid && kv.second == slot_id) {
            // Two live tids must never share a slot_id (I1).
            __builtin_trap();
          }
        }
        g_owner[tid] = slot_id;
      }
    } else if (op < 0x50) {
      auto it = g_owner.find(tid);
      if (it != g_owner.end()) {
        g_filter->unregisterThread(it->second, tid);
        g_owner.erase(it);
      }
    } else if (op < 0x60) {
      auto it = g_owner.find(tid);
      if (it != g_owner.end()) {
        g_filter->add(tid, it->second);
      }
    } else if (op < 0x70) {
      auto it = g_owner.find(tid);
      if (it != g_owner.end()) {
        g_filter->remove(it->second);
      }
    } else if (op < 0x90) {
      auto it = g_owner.find(tid);
      if (it != g_owner.end()) {
        OSThreadState state = static_cast<OSThreadState>(1 + (nextByte() % 9));
        u64 token = g_tracker->enterBlockedRun(g_filter, it->second, state);
        if (token != 0) {
          g_last_token[it->second] = token;
          g_ever_blocked.insert(it->second);
        }
      }
    } else if (op < 0xB0) {
      auto it = g_owner.find(tid);
      if (it != g_owner.end()) {
        auto tok_it = g_last_token.find(it->second);
        if (tok_it != g_last_token.end()) {
          uint8_t corruption_byte = nextByte();
          u32 correct_generation = WallClockBlockTracker::tokenGeneration(tok_it->second);
          bool corrupt = (corruption_byte & 0x1) != 0;
          u32 generation = corrupt
              ? correct_generation + 1 + (corruption_byte >> 1)
              : correct_generation;

          WallClockBlockTracker::BlockState* block_slot = g_tracker->slotForId(it->second);
          OSThreadState state_before =
              block_slot ? block_slot->activeBlockState() : OSThreadState::UNKNOWN;
          bool exited = g_tracker->exitBlockedRun(it->second, generation);

          if (generation != correct_generation) {
            // I4: a mismatched generation must be rejected and must not
            // touch the slot's active-block-state.
            if (exited || (block_slot && block_slot->activeBlockState() != state_before)) {
              __builtin_trap();
            }
          } else if (exited) {
            g_last_token.erase(it->second);
          }
        }
      }
    } else if (op < 0xD0) {
      auto it = g_owner.find(tid);
      if (it != g_owner.end()) {
        g_tracker->exitBlockedRun(it->second);
      }
    } else if (op < 0xF0) {
      g_filter->unregisterThreadByTid(tid);
      g_owner.erase(tid);
    } else {
      g_filter->init("", /*track_unfiltered_wall=*/true);
      resetShadowState();

      for (ThreadFilter::SlotID slot_id : g_ever_blocked) {
        WallClockBlockTracker::BlockState* block_slot = g_tracker->slotForId(slot_id);
        if (block_slot == nullptr) continue;
        if (block_slot->activeBlockState() != OSThreadState::UNKNOWN ||
            block_slot->sampledThisRun()) {
          // resetAll() must have cleared every slot on registry reset (I3).
          __builtin_trap();
        }
      }
    }

    // I2: cheap enough to check after every op.
    for (auto& kv : g_owner) {
      if (g_filter->activeSlotForId(kv.second, kv.first) == nullptr) {
        __builtin_trap();
      }
    }
  }

  return 0;
}
