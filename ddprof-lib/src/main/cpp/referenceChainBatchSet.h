/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _REFERENCECHAINBATCHSET_H
#define _REFERENCECHAINBATCHSET_H

#include "arch.h"
#include <jni.h>
#include <cstddef>
#include <cstring>
#include <stdexcept>

// Fixed-capacity open-addressing set for one traversal batch's tags and
// per-tag flags: never thread_local, owned by ReferenceChainTracker and
// reset per batch. Valid batch bookkeeping never heap-allocates.

// Out-of-contract marker calls on absent tags throw std::logic_error, and
// throwing may allocate: allocation freedom covers valid bookkeeping only.

// Actors: the BFS thread writes before FollowReferences(); the callback on
// the HotSpot VM thread reads and records completion during that synchronous
// VM operation; the BFS thread reads the result after the call returns.
class ReferenceChainBatchSet {
 public:
  // One batch's tag capacity, matching the tracker's batch upper bound
  // (GOTW_MAX_BATCH, 512); an oversized batch is rejected, not overflowed.
  static constexpr size_t CAPACITY = 512;

  // Clears membership, resolution and completion; stale keys stay in _keys
  // (occupancy is _flags). Also the first-use initializer (no constructor).
  void reset() {
    memset(_flags, 0, sizeof(_flags));
    _count = 0;
    _completed_count = 0;
  }

  // Idempotent: re-adding a present tag keeps its flags and the size.
  // Returns false only when `tag` is absent and the set holds CAPACITY tags.
  bool addResolved(jlong tag) {
    const u32 start = static_cast<u32>(mix(tag) >> (64 - SLOT_SHIFT));
    u32 i = start;
    do {
      if (_flags[i] == 0) {
        if (_count == CAPACITY) return false;
        _keys[i] = tag;
        _flags[i] = RESOLVED;
        _count++;
        return true;
      }
      if (_keys[i] == tag) { _flags[i] |= RESOLVED; return true; }
      i = (i + 1) & (SLOTS - 1);
    } while (i != start);
    return false; // unreachable: _count <= CAPACITY < SLOTS leaves an empty slot
  }

  // Sets the descent-gate flag of a present tag. An absent tag breaks the
  // caller contract (addResolved first) and throws in every build.
  void markMember(jlong tag) {
    const u32 i = findSlot(tag);
    if (i == SLOTS) throw std::logic_error("markMember: unresolved tag");
    _flags[i] |= MEMBER;
  }

  // Records completion of a present tag (same contract as markMember);
  // _completed_count counts each tag once, so a repeated completion keeps
  // anyCompleted() true.
  void markCompleted(jlong tag) {
    const u32 i = findSlot(tag);
    if (i == SLOTS) throw std::logic_error("markCompleted: unresolved tag");
    if ((_flags[i] & COMPLETED) == 0) _completed_count++;
    _flags[i] |= COMPLETED;
  }

  bool isResolved(jlong tag) const { return hasFlag(tag, RESOLVED); }
  bool isMember(jlong tag) const { return hasFlag(tag, MEMBER); }
  bool isCompleted(jlong tag) const { return hasFlag(tag, COMPLETED); }
  bool anyCompleted() const { return _completed_count != 0; }
  u32 size() const { return _count; }

 private:
  static constexpr u32 SLOT_SHIFT = 10;
  static constexpr u32 SLOTS = 1u << SLOT_SHIFT;
  static_assert(SLOTS >= 2 * CAPACITY);
  static constexpr u8 RESOLVED = 1;
  static constexpr u8 MEMBER = 2;
  static constexpr u8 COMPLETED = 4;

  // Occupancy lives in _flags (0 = empty), so key 0 needs no sentinel.
  jlong _keys[SLOTS];
  u8 _flags[SLOTS];
  u32 _count;
  u32 _completed_count;

  // Multiply-shift mixing (same constant as PriorityExpandSet::mix): without
  // it, sequential or sparsely spaced tags land in a narrow run of slots.
  static u64 mix(jlong tag) { return static_cast<u64>(tag) * 0x9E3779B97F4A7C15ULL; }

  // Load factor stays <= 0.5 (_count <= CAPACITY = SLOTS / 2); a lookup stops
  // at an empty slot, a matching key, or SLOTS probes. Returns SLOTS if absent.
  u32 findSlot(jlong tag) const {
    const u32 start = static_cast<u32>(mix(tag) >> (64 - SLOT_SHIFT));
    u32 i = start;
    do {
      if (_flags[i] == 0) return SLOTS;
      if (_keys[i] == tag) return i;
      i = (i + 1) & (SLOTS - 1);
    } while (i != start);
    return SLOTS;
  }

  bool hasFlag(jlong tag, u8 flag) const {
    const u32 i = findSlot(tag);
    return i != SLOTS && (_flags[i] & flag) != 0;
  }
};

// Descriptor footprint stays within its 32 KiB permanent-member budget.
static_assert(sizeof(ReferenceChainBatchSet) <= 32 * 1024);

#endif // _REFERENCECHAINBATCHSET_H
