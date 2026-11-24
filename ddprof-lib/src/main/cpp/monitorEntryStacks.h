/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _MONITOR_ENTRY_STACKS_H
#define _MONITOR_ENTRY_STACKS_H

#include "arch.h"
#include "vmEntry.h"

#include <atomic>

union CallTraceBuffer;

// Recording-scoped stacks captured at MonitorContendedEnter and consumed at
// MonitorContendedEntered. Each claim stores a never-reused serial in an ownership
// word that outlives the storage, so a stale or repeated release frees nothing.
class MonitorEntryStacks {
 public:
  static constexpr int SLOTS = 64;
  static constexpr u64 SLOT_MASK = SLOTS - 1;
  static constexpr int SERIAL_SHIFT = 6;

  MonitorEntryStacks() = default;
  MonitorEntryStacks(const MonitorEntryStacks&) = delete;
  MonitorEntryStacks& operator=(const MonitorEntryStacks&) = delete;

  // Not reachable by claimers until it publishes; false on OOM or when already allocated.
  bool allocate(int max_depth);
  // Caller excludes claim() and frames() callers: TaskBlock activity is closed and drained.
  void release();

  // Returns a nonzero lease, or 0 when unallocated, depth-mismatched or exhausted.
  // Caller holds TaskBlock activity so release() cannot free the slot's buffer.
  u64 claim(int max_depth);
  // Idempotent; a lease released before, or from an earlier recording, matches no word.
  void unclaim(u64 lease);
  // Writable buffer of a lease this thread holds; same activity rule as claim().
  CallTraceBuffer* buffer(u64 lease) const;
  void setCaptured(u64 lease, int num_frames, bool truncated);
  // The captured frames of a current lease, or nullptr; same activity rule as claim().
  ASGCT_CallFrame* frames(u64 lease, int& num_frames, bool& truncated) const;

  bool allocated() const { return _storage.load(std::memory_order_acquire) != nullptr; }
  int claimedForTest() const;

 private:
  static int slotOf(u64 lease) { return static_cast<int>(lease & SLOT_MASK); }
  static u64 serialOf(u64 lease) { return lease >> SERIAL_SHIFT; }
  bool owns(u64 lease) const;

  std::atomic<CallTraceBuffer*> _storage{nullptr};
  // Next claim serial; starts at 1 so a lease is never 0.
  std::atomic<u64> _next_serial{1};
  // Owning claim serial per slot, 0 when free; release() clears them all.
  std::atomic<u64> _owner[SLOTS]{};
  // Written by the lease holder only, read back by the same thread at exit.
  int _num_frames[SLOTS]{};
  bool _truncated[SLOTS]{};
  int _max_depth{0};
  size_t _slot_capacity{0};
};

// Releases its lease on destruction unless detach() hands the lease over.
class MonitorEntryStackLease {
 private:
  MonitorEntryStacks* _stacks;
  u64 _lease;
  bool _expected;

 public:
  MonitorEntryStackLease(MonitorEntryStacks* stacks, u64 lease, bool expected = true)
      : _stacks(stacks), _lease(lease), _expected(expected) {}
  ~MonitorEntryStackLease() {
    if (_lease != 0) _stacks->unclaim(_lease);
  }
  MonitorEntryStackLease(const MonitorEntryStackLease&) = delete;
  MonitorEntryStackLease& operator=(const MonitorEntryStackLease&) = delete;

  u64 lease() const { return _lease; }
  u64 detach() {
    u64 lease = _lease;
    _lease = 0;
    return lease;
  }
  // True when the producer captures at entry, so a missing stack is a fallback.
  bool expected() const { return _expected; }
  ASGCT_CallFrame* frames(int& num_frames, bool& truncated) const {
    return _lease == 0 ? nullptr : _stacks->frames(_lease, num_frames, truncated);
  }
};

#endif // _MONITOR_ENTRY_STACKS_H
