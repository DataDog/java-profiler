// Copyright (C) Datadog 2025
// Implementation of thread filter management

#include "threadFilter.h"

#include <cstdlib>
#include <thread>

ThreadFilter::ThreadFilter()
    : _next_index(0), _enabled(false) {
    std::unique_lock<std::mutex> lock(_slot_mutex);
    _slots.emplace_back(); // Allocate first chunk
    clear();
}

ThreadFilter::~ThreadFilter() {
    std::unique_lock<std::mutex> lock(_slot_mutex);
    _slots.clear();
}

ThreadFilter::SlotID ThreadFilter::registerThread() {
    SlotID index = _next_index.fetch_add(1, std::memory_order_relaxed);
    if (index >= kMaxThreads) {
        return -1;
    }
    const int outer_idx = index >> kChunkShift;
    {
        if (outer_idx < static_cast<int>(_slots.size())) {
            return index;
        }
    }

    {
        std::unique_lock<std::mutex> write_lock(_slot_mutex);
        while (outer_idx >= static_cast<int>(_slots.size())) {
            _slots.emplace_back();
        }
    }

    return index;
}

void ThreadFilter::clear() {
    for (auto& chunk : _slots) {
        for (auto& slot : chunk) {
            slot.value.store(-1, std::memory_order_relaxed);
        }
    }
}

bool ThreadFilter::accept(SlotID slot_id) const {
    if (!_enabled) {
        return true;
    }
    if (slot_id < 0) return false;
    int outer_idx = slot_id >> kChunkShift;
    int inner_idx = slot_id & kChunkMask;
    if (outer_idx >= static_cast<int>(_slots.size())) return false;
    return _slots[outer_idx][inner_idx].value.load(std::memory_order_acquire) != -1;
}

void ThreadFilter::add(int tid, SlotID slot_id) {
    int outer_idx = slot_id >> kChunkShift;
    int inner_idx = slot_id & kChunkMask;
    _slots[outer_idx][inner_idx].value.store(tid, std::memory_order_relaxed);
}

void ThreadFilter::remove(SlotID slot_id) {
    int outer_idx = slot_id >> kChunkShift;
    int inner_idx = slot_id & kChunkMask;
    _slots[outer_idx][inner_idx].value.store(-1, std::memory_order_relaxed);
}

void ThreadFilter::unregisterThread(SlotID slot_id) {
    if (slot_id < 0) return;
    int outer_idx = slot_id >> kChunkShift;
    int inner_idx = slot_id & kChunkMask;
    _slots[outer_idx][inner_idx].value.store(-1, std::memory_order_relaxed);
}

void ThreadFilter::collect(std::vector<int>& tids) const {
    tids.clear();
    // std::unique_lock<std::mutex> lock(_slot_mutex);
    for (const auto& chunk : _slots) {
        for (const auto& slot : chunk) {
            int slot_tid = slot.value.load(std::memory_order_acquire);
            if (slot_tid != -1) {
                tids.push_back(slot_tid);
            }
        }
    }
}

void ThreadFilter::init(const char* filter) {
    if (!filter) {
        return;
    }
    // TODO: Implement parsing of filter string if needed
    _enabled = true;
}

bool ThreadFilter::enabled() const {
    return _enabled;
}
