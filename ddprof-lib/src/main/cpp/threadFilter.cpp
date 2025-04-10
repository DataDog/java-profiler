// todo copyright stuff
// as I rewrote all the implem

#include "threadFilter.h"
#include "common.h"
#include <mutex>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <cstdio>


ThreadFilter::ThreadFilter() : _next_index(-1) {}

ThreadFilter::~ThreadFilter() {
    std::lock_guard<std::mutex> lock(_slot_mutex);
    pthread_key_delete(_thread_slot_key);
    _next_index = -1;
    _slots.clear();
}

ThreadFilter::SlotID ThreadFilter::registerThread() {
    int index;
    std::lock_guard<std::mutex> lock(_slot_mutex);

    if (!_free_slots.empty()) { // todo: check if we can speed this up
        index = _free_slots.back();
        _free_slots.pop_back();
    } else {
        index = _next_index.fetch_add(1, std::memory_order_relaxed);
        if (index >= static_cast<int>(_slots.size())) {
            _slots.resize(std::max(_slots.size() * 2, static_cast<size_t>(index + 1)));
        }
    }
    pthread_setspecific(_thread_slot_key, reinterpret_cast<void*>(static_cast<intptr_t>(index)));
    TEST_LOG("[registerThread] slot=%d\n", index);
    return index;
}

ThreadFilter::SlotID ThreadFilter::ensureThreadRegistered() const {
    void* ptr = pthread_getspecific(_thread_slot_key);
    if (ptr == nullptr) {
        return -1;  // not registered
    }
    return static_cast<SlotID>(reinterpret_cast<intptr_t>(ptr));
}

void ThreadFilter::clear() {
    std::lock_guard<std::mutex> lock(_slot_mutex);
    for (auto& slot : _slots) {
        slot.value.store(-1, std::memory_order_release);
    }
    _free_slots.clear();
}

bool ThreadFilter::accept(int tid) const {
    if (!_enabled) return true;
    SlotID id = ensureThreadRegistered();
    if (id == -1) {
        TEST_LOG("[accept] Thread not registered, tid=%d\n", tid);
        return false;
    }
    int slot_val = _slots[id].value.load(std::memory_order_acquire);
    TEST_LOG("[accept] slot=%d value=%d (expecting tid=%d)\n", id, slot_val, tid);
    return id < static_cast<int>(_slots.size()) && slot_val == tid;
}

void ThreadFilter::add(int tid) {
    SlotID id = ensureThreadRegistered();
    if (id != -1 && id < static_cast<int>(_slots.size())) {
        _slots[id].value.store(tid, std::memory_order_release);
        TEST_LOG("[add] slot=%d set to tid=%d\n", id, tid);
    }
}

void ThreadFilter::remove(int tid) {
    SlotID id = ensureThreadRegistered();
    if (id != -1 && id < static_cast<int>(_slots.size())) {
        _slots[id].value.store(-1, std::memory_order_release);
        TEST_LOG("[remove] slot=%d cleared (tid=%d)\n", id, tid);
    }
}

void ThreadFilter::collect(std::vector<int>& tids) const {
    tids.clear();
    std::lock_guard<std::mutex> lock(_slot_mutex);
    for (size_t i = 0; i < _slots.size(); ++i) {
        int tid = _slots[i].value.load(std::memory_order_acquire);
        if (tid != -1) {
            TEST_LOG("[collect] slot=%zu tid=%d\n", i, tid);
            tids.push_back(tid);
        }
    }
}

void ThreadFilter::init(const char* filter) {
    if (filter == nullptr) {
        return;
    }
    std::lock_guard<std::mutex> lock(_slot_mutex);
    _slots.resize(128); // pre-allocate some slots
    int key_create_result = pthread_key_create(&_thread_slot_key, nullptr);
    if (key_create_result != 0) {
        TEST_LOG("[init] Failed to create thread key, error=%d\n", key_create_result);
        return;
    }
    // 0 is reserved and creates an issue with set specific (confusing it for null pointer)
    _next_index.store(1, std::memory_order_acquire);
    _enabled = true;
    // todo: init string parsing was weird
}

bool ThreadFilter::enabled() const {
    return _enabled;
}

void ThreadFilter::deregisterThread() {
    SlotID id = ensureThreadRegistered();
    if (id != -1 && id < static_cast<int>(_slots.size())) {
        _slots[id].value.store(-1, std::memory_order_release);
        pthread_setspecific(_thread_slot_key, nullptr);
        std::lock_guard<std::mutex> lock(_slot_mutex);
        _free_slots.push_back(id);
        TEST_LOG("[deregisterThread] slot=%d returned to free list\n", id);
    }
}
