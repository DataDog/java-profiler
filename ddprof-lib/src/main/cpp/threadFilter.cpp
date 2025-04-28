// todo copyright stuff
// as I rewrote all the implem

#include "threadFilter.h"
#include <mutex>
#include <thread>
#include <cstdlib>
#include <cstring>

static std::mutex slot_mutex;


ThreadFilter::ThreadFilter() : _next_index(0), _enabled(false) {
    std::lock_guard<std::mutex> lock(slot_mutex);
    _slots.resize(128); // preallocate some slots
    // Initialize all slots to -1
    for (auto& slot : _slots) {
        slot.value.store(-1, std::memory_order_relaxed);
    }
}

ThreadFilter::~ThreadFilter() {
    std::lock_guard<std::mutex> lock(slot_mutex);
    _slots.clear();
    _free_list.clear(); // todo: implement this, not needed for benchmark
}

ThreadFilter::SlotID ThreadFilter::registerThread() {
    int index = _next_index.fetch_add(1, std::memory_order_relaxed);
    if (index < static_cast<int>(_slots.size())) {
        return index;
    }
    // Lock required to safely grow the vector
    {
        std::lock_guard<std::mutex> lock(slot_mutex);
        size_t current_size = _slots.size();
        if (static_cast<size_t>(index) >= current_size) {
            _slots.resize(current_size * 2);
            // Initialize new slots
            for (size_t i = current_size; i < current_size * 2; ++i) {
                _slots[i].value.store(-1, std::memory_order_relaxed);
            }
        }
    }
    return index;
}

void ThreadFilter::clear() {
    std::lock_guard<std::mutex> lock(slot_mutex);
    for (auto& slot : _slots) {
        slot.value.store(-1, std::memory_order_relaxed);
    }
}

bool ThreadFilter::accept(int slot_id) const {
    if (!_enabled) return true;
    return slot_id >= 0 && slot_id < static_cast<int>(_slots.size()) && _slots[slot_id].value.load(std::memory_order_acquire) != -1;
}

void ThreadFilter::add(int tid, int slot_id) {
    _slots[slot_id].value.store(tid, std::memory_order_relaxed);
}

void ThreadFilter::remove(int slot_id) {
    _slots[slot_id].value.store(-1, std::memory_order_relaxed);
}

void ThreadFilter::collect(std::vector<int>& tids) const {
    tids.clear();
    std::lock_guard<std::mutex> lock(slot_mutex);
    for (const auto& slot : _slots) {
        int slot_tid = slot.value.load(std::memory_order_acquire);
        if (slot_tid != -1) {
            tids.push_back(slot_tid);
        }
    }
}

void ThreadFilter::init(const char* filter) {
    if (filter == nullptr) {
        return;
    }
    // char* end;
    // // todo understand this strange init
    // do {
    //     int id = strtol(filter, &end, 0);
    //     if (id <= 0) {
    //         break;
    //     }

    //     if (*end == '-') {
    //         int to = strtol(end + 1, &end, 0);
    //         while (id <= to) {
    //             add(id++);
    //         }
    //     } else {
    //         add(id);
    //     }
    //     filter = end + 1;
    // } while (*end);
    _enabled = true;
}

bool ThreadFilter::enabled() const {
    return _enabled;
}

// Implementation of unregisterThread - releases a slot by its ID
void ThreadFilter::unregisterThread(SlotID slot_id) {
    if (slot_id >= 0 && slot_id < static_cast<int>(_slots.size())) {
        // Reset this slot to be available again
        _slots[slot_id].value.store(-1, std::memory_order_relaxed);
    }
}
