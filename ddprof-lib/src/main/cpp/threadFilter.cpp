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
    int top = _free_list_top.load(std::memory_order_acquire);
    for (int i = 0; i < top; ++i) {
        int value = _free_list[i].load(std::memory_order_relaxed);
        if (value >= 0) {
            int expected = value;
            if (_free_list[i].compare_exchange_strong(expected, -1, std::memory_order_acq_rel)) {
                return value; // Successfully claimed a free slot
            }
            // If CAS fails, someone else claimed it, continue scanning
        }
    }

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
    for (int i = 0; i < kFreeListSize; ++i) {
        _free_list[i].store(-1, std::memory_order_relaxed);
    }
    _free_list_top.store(0, std::memory_order_relaxed);
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

    constexpr int try_limit = 16;

    int top = _free_list_top.load(std::memory_order_acquire);
    int limit = top < kFreeListSize ? top : kFreeListSize;
    int tries = 0;

    for (int i = 0; i < limit && tries < try_limit; ++i) {
        int value = _free_list[i].load(std::memory_order_relaxed);
        if (value == -1) {
            int expected = -1;
            if (_free_list[i].compare_exchange_strong(expected, slot_id, std::memory_order_acq_rel)) {
                return; // Successfully claimed empty spot
            }
            ++tries; // Only count actual CAS attempts
        }
    }

    // Fallback: append if no empty slot found
    int pos = _free_list_top.fetch_add(1, std::memory_order_acq_rel);
    if (pos < kFreeListSize) {
        _free_list[pos].store(slot_id, std::memory_order_release);
    } else {
        // Free list overflow: ignore
    }
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
