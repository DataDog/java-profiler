/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "monitorEntryStacks.h"

#include "nativeMem.h"
#include "profiler.h"

#include <stdlib.h>

static_assert((MonitorEntryStacks::SLOTS & (MonitorEntryStacks::SLOTS - 1)) == 0 &&
                  MonitorEntryStacks::SLOTS == (1 << MonitorEntryStacks::SERIAL_SHIFT),
              "lease encoding packs the slot index below the claim serial");

bool MonitorEntryStacks::allocate(int max_depth) {
  if (max_depth <= 0 || _storage.load(std::memory_order_acquire) != nullptr) return false;
  // One extra frame holds captureJVMTIFrames()' truncation probe.
  size_t capacity = static_cast<size_t>(max_depth) + 1;
  CallTraceBuffer* storage =
      static_cast<CallTraceBuffer*>(calloc(SLOTS * capacity, sizeof(CallTraceBuffer)));
  if (storage == nullptr) return false;
  NativeMem::record(NM_CALLTRACE, static_cast<long long>(SLOTS * capacity * sizeof(CallTraceBuffer)));
  _max_depth = max_depth;
  _slot_capacity = capacity;
  // Release: a claimer that acquires the pointer sees the depth and capacity.
  _storage.store(storage, std::memory_order_release);
  return true;
}

void MonitorEntryStacks::release() {
  CallTraceBuffer* storage = _storage.exchange(nullptr, std::memory_order_acq_rel);
  if (storage == nullptr) return;
  // Leases of the freed storage, including ones held by exited threads, go stale.
  for (int i = 0; i < SLOTS; i++) _owner[i].store(0, std::memory_order_release);
  free(storage);
  NativeMem::record(NM_CALLTRACE, -static_cast<long long>(SLOTS * _slot_capacity * sizeof(CallTraceBuffer)));
  _slot_capacity = 0;
  _max_depth = 0;
}

u64 MonitorEntryStacks::claim(int max_depth) {
  if (_storage.load(std::memory_order_acquire) == nullptr || max_depth != _max_depth) return 0;
  // Relaxed: the serial only needs uniqueness; the owner CAS publishes the claim.
  u64 serial = _next_serial.fetch_add(1, std::memory_order_relaxed);
  for (int i = 0; i < SLOTS; i++) {
    u64 expected = 0;
    if (_owner[i].load(std::memory_order_acquire) == 0 &&
        _owner[i].compare_exchange_strong(expected, serial, std::memory_order_acq_rel,
                                          std::memory_order_acquire)) {
      _num_frames[i] = 0;
      _truncated[i] = false;
      return (serial << SERIAL_SHIFT) | static_cast<u64>(i);
    }
  }
  return 0;
}

void MonitorEntryStacks::unclaim(u64 lease) {
  u64 expected = serialOf(lease);
  _owner[slotOf(lease)].compare_exchange_strong(expected, 0, std::memory_order_acq_rel,
                                                std::memory_order_acquire);
}

bool MonitorEntryStacks::owns(u64 lease) const {
  return _storage.load(std::memory_order_acquire) != nullptr &&
         _owner[slotOf(lease)].load(std::memory_order_acquire) == serialOf(lease);
}

CallTraceBuffer* MonitorEntryStacks::buffer(u64 lease) const {
  if (!owns(lease)) return nullptr;
  return _storage.load(std::memory_order_acquire) + slotOf(lease) * _slot_capacity;
}

void MonitorEntryStacks::setCaptured(u64 lease, int num_frames, bool truncated) {
  _num_frames[slotOf(lease)] = num_frames;
  _truncated[slotOf(lease)] = truncated;
}

ASGCT_CallFrame* MonitorEntryStacks::frames(u64 lease, int& num_frames,
                                            bool& truncated) const {
  CallTraceBuffer* slot = buffer(lease);
  if (slot == nullptr || _num_frames[slotOf(lease)] <= 0) return nullptr;
  num_frames = _num_frames[slotOf(lease)];
  truncated = _truncated[slotOf(lease)];
  return slot->_asgct_frames;
}

int MonitorEntryStacks::claimedForTest() const {
  int claimed = 0;
  for (int i = 0; i < SLOTS; i++) {
    if (_owner[i].load(std::memory_order_acquire) != 0) claimed++;
  }
  return claimed;
}
