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
 *   op < 0x90: enterBlockedRun(tracker, slot_id, state); mark admitted runs sampled
 *   op < 0xB0: exitBlockedRun(slot_id, generation) - generation-checked; an
 *              extra fuzzed byte decides whether the real generation is used
 *              or corrupted, to exercise the stale-token rejection path
 *   op < 0xD0: resetSlot(slot_id, RUNNABLE) - unconditional clear
 *   op < 0xF0: unregisterThreadByTid(tid)
 *   op >= 0xF0: init("", true) - starts a new recording epoch while retaining
 *               native owners; their block state is refreshed on registration
 *
 * Each op byte is followed by one more byte selecting the tid (and, for
 * enterBlockedRun and the generation-checked exit, a third byte selecting
 * the OSThreadState / generation-corruption decision respectively).
 *
 * Invariants verified (violation -> __builtin_trap() -> ASan/fuzzer crash):
 *   I1. Single-owner TID mapping: registerThread() rediscovering a tid that
 *       is still live must return the exact slot it was already given, and
 *       no two live tids may ever be mapped to the same slot_id. Regression
 *       guard (no known open bug): registerThread() dedupes via
 *       lookupSlotIdByTid() under _registry_lock plus indexSlot()'s duplicate
 *       refusal, and add() rejects a slot whose nativeTid() differs (add()
 *       never binds or indexes a tid).
 *   I2. lookupByTid(tid) retains every live owner's identity. activeSlotForId()
 *       is non-null exactly when its owner has registered in the current epoch.
 *   I3. Restart makes old block state ineligible for suppression; registering
 *       a retained owner clears its block state and sampled-this-run marker.
 *   I4. A generation-checked exitBlockedRun() called with a generation other
 *       than the block run's current one must return false and must not
 *       change that slot's active-block-state (a stale/forged token must
 *       never clear a newer or already-cleared run). One called with the
 *       correct generation that reports an exit must leave the slot with
 *       owner NONE, active state UNKNOWN and no sampled-this-run marker.
 *   I5. Context-window membership: add() returns true for every owned tid and
 *       leaves its block slot with owner NONE / state UNKNOWN / not sampled;
 *       after every op, inContextWindow() matches the shadow g_in_window.
 *   I6. Two-sided suppression decision: after every op, for every owned tid,
 *       shouldSuppressOwnedBlock() is true exactly when the shadow model has
 *       an armed owned run (g_armed) in a precheck-suppression state for an
 *       owner registered in the current epoch (g_fresh). This relies on
 *       enterBlockedRun() refusing admission inside a context window
 *       (outside_context_required in unfiltered mode), so g_armed and
 *       g_in_window never hold the same tid. The fuzzer only uses unfiltered
 *       mode with a non-zero recording epoch.
 *
 * ASan+UBSan (enabled by the fuzz build config) additionally catch any
 * out-of-bounds chunk/tid-index access or use-after-free surfaced by the
 * lazy chunk allocation paths as this drives slot reuse and recording restarts.
 */

#include <stddef.h>
#include <stdint.h>
#include <unordered_map>
#include <unordered_set>

#include "threadFilter.h"
#include "threadState.h"
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
// Owners that have registered against the current recording epoch.
std::unordered_set<int> g_fresh;
// Owners whose context window is currently entered (I5).
std::unordered_set<int> g_in_window;
// Owners with an admitted, sampled owned block run and its state (I6).
std::unordered_map<int, OSThreadState> g_armed;

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
        if (g_fresh.insert(tid).second) {
          // New slot, or a retained owner refreshed for this epoch: context
          // state and block state are reset.
          g_in_window.erase(tid);
          g_armed.erase(tid);
          auto* block = g_tracker->slotForId(slot_id);
          if (block->activeBlockState() != OSThreadState::UNKNOWN ||
              block->activeBlockOwner() != BlockRunOwner::NONE ||
              block->sampledThisRun()) {
            // Newly registered or refreshed owners start with clean payload (I3).
            __builtin_trap();
          }
        }
      }
    } else if (op < 0x50) {
      auto it = g_owner.find(tid);
      if (it != g_owner.end()) {
        g_filter->unregisterThread(it->second, tid);
        g_last_token.erase(it->second);
        g_owner.erase(it);
        g_fresh.erase(tid);
        g_in_window.erase(tid);
        g_armed.erase(tid);
      }
    } else if (op < 0x60) {
      auto it = g_owner.find(tid);
      if (it != g_owner.end()) {
        // I5: an owned tid's add() must succeed and clear any active run.
        if (!g_filter->add(tid, it->second)) __builtin_trap();
        auto* b = g_tracker->slotForId(it->second);
        if (b == nullptr || b->activeBlockOwner() != BlockRunOwner::NONE ||
            b->activeBlockState() != OSThreadState::UNKNOWN || b->sampledThisRun()) {
          __builtin_trap();
        }
        g_in_window.insert(tid);
        g_armed.erase(tid);
      }
    } else if (op < 0x70) {
      auto it = g_owner.find(tid);
      if (it != g_owner.end()) {
        g_filter->remove(it->second);
        g_in_window.erase(tid);
      }
    } else if (op < 0x90) {
      auto it = g_owner.find(tid);
      if (it != g_owner.end()) {
        OSThreadState state = static_cast<OSThreadState>(1 + (nextByte() % 9));
        u64 token = g_tracker->enterBlockedRun(g_filter, it->second, state);
        if (token != 0) {
          g_last_token[it->second] = token;
          g_tracker->slotForId(it->second)->markSampledThisRun(state);
          g_armed[tid] = state;
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
            // I4 post-state: the run is fully cleared.
            if (block_slot == nullptr ||
                block_slot->activeBlockOwner() != BlockRunOwner::NONE ||
                block_slot->activeBlockState() != OSThreadState::UNKNOWN ||
                block_slot->sampledThisRun()) {
              __builtin_trap();
            }
            g_last_token.erase(it->second);
            g_armed.erase(tid);
          }
        }
      }
    } else if (op < 0xD0) {
      auto it = g_owner.find(tid);
      if (it != g_owner.end()) {
        g_tracker->resetSlot(it->second, OSThreadState::RUNNABLE);
        g_armed.erase(tid);
      }
    } else if (op < 0xF0) {
      g_filter->unregisterThreadByTid(tid);
      auto it = g_owner.find(tid);
      if (it != g_owner.end()) g_last_token.erase(it->second);
      g_owner.erase(tid);
      g_fresh.erase(tid);
      g_in_window.erase(tid);
      g_armed.erase(tid);
    } else {
      g_filter->init("", /*track_unfiltered_wall=*/true);
      g_fresh.clear();
      g_last_token.clear();
      // init() leaves retained context state alone (g_in_window unchanged);
      // old-epoch runs can no longer suppress.
      g_armed.clear();

      for (auto& kv : g_owner) {
        auto* identity = g_filter->slotForId(kv.second);
        ThreadEntry stale{kv.first, identity, kv.second, identity->lifecycleGeneration(),
                          identity->recordingEpoch()};
        if (g_tracker->shouldSuppressOwnedBlock(g_filter, stale)) {
          // Retained payload from the previous epoch cannot suppress a sample (I3).
          __builtin_trap();
        }
      }
    }

    // I2: cheap enough to check after every op.
    for (int candidate_tid = 1; candidate_tid <= kTidDomain; ++candidate_tid) {
      auto it = g_owner.find(candidate_tid);
      auto* identity = g_filter->lookupByTid(candidate_tid);
      if (it == g_owner.end()) {
        if (identity != nullptr) __builtin_trap();
        continue;
      }
      bool active = g_filter->activeSlotForId(it->second, candidate_tid) != nullptr;
      if (identity != g_filter->slotForId(it->second) ||
          active != (g_fresh.count(candidate_tid) != 0)) {
        __builtin_trap();
      }
    }

    for (auto& kv : g_owner) {
      auto* identity = g_filter->slotForId(kv.second);
      // I5: context-window membership matches the shadow model.
      if (identity->inContextWindow() != (g_in_window.count(kv.first) != 0)) {
        __builtin_trap();
      }
      // I6: the suppression decision is two-sided.
      ThreadEntry entry{kv.first, identity, kv.second, identity->lifecycleGeneration(),
                        identity->recordingEpoch()};
      auto armed = g_armed.find(kv.first);
      bool expected = armed != g_armed.end() && g_fresh.count(kv.first) != 0 &&
                      isPrecheckSuppressionState(armed->second);
      if (g_tracker->shouldSuppressOwnedBlock(g_filter, entry) != expected) {
        __builtin_trap();
      }
    }
  }

  return 0;
}
