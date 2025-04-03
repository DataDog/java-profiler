// todo copyright stuff
// as I rewrote all the implem

#include "threadFilter.h"
#include <mutex>
#include <thread>
#include <cstdlib>
#include <cstring>

static ThreadFilter* global_filter = nullptr;
thread_local ThreadFilter::SlotID tls_slot_id = -1; // todo, use the signal safe stuff 
static std::mutex slot_mutex;

ThreadFilter::ThreadFilter() : _next_index(0) {
    std::lock_guard<std::mutex> lock(slot_mutex);
    _slots.resize(128); // preallocate some slots
}

ThreadFilter::~ThreadFilter() {
    std::lock_guard<std::mutex> lock(slot_mutex);
    _slots.clear();
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
    }
  }
  return index;
}

ThreadFilter::SlotID ThreadFilter::ensureThreadRegistered() {
    if (tls_slot_id == -1) {
        tls_slot_id = registerThread();
    }
    return tls_slot_id;
}

void ThreadFilter::clear() {
    std::lock_guard<std::mutex> lock(slot_mutex);
    for (auto& slot : _slots) {
        slot.value.store(-1, std::memory_order_relaxed);
    }
}

bool ThreadFilter::accept(int tid) const {
    if (!_enabled) return true;
    SlotID id = tls_slot_id;
    return id >= 0 && id < static_cast<int>(_slots.size()) && _slots[id].value.load(std::memory_order_acquire) != -1;
}

void ThreadFilter::add(int tid) {
    SlotID id = ensureThreadRegistered();
    _slots[id].value.store(tid, std::memory_order_relaxed);
}

void ThreadFilter::remove(int /*tid*/) {
    SlotID id = ensureThreadRegistered(); // we probably are already registered 
    _slots[id].value.store(-1, std::memory_order_relaxed);
}

void ThreadFilter::collect(std::vector<int>& tids) const {
    tids.clear();
    std::lock_guard<std::mutex> lock(slot_mutex);
    for (const auto& slot : _slots) {
        int tid = slot.value.load(std::memory_order_acquire);
        if (tid != -1) {
            tids.push_back(tid);
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
