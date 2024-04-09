#include "counters.h"
#include "mutex.h"
#include "threadInfo.h"

void ThreadInfo::set(int tid, const char* name, u64 java_thread_id) {
    MutexLocker ml(_ti_lock);
    _thread_names[tid] = std::string(name);
    _thread_ids[tid] = java_thread_id;
}

std::pair<std::shared_ptr<std::string>, u64> ThreadInfo::get(int threadId) {
    MutexLocker ml(_ti_lock);
    auto it = _thread_names.find(threadId);
    if (it != _thread_names.end()) {
        return std::make_pair(std::make_shared<std::string>(it->second), _thread_ids[threadId]);
    }
    return std::make_pair(nullptr, 0);
}

int ThreadInfo::getThreadId(int threadId) {
    MutexLocker ml(_ti_lock);
    auto it = _thread_ids.find(threadId);
    if (it != _thread_ids.end()) {
        return it->second;
    }
    return -1;
}

void ThreadInfo::clearAll() {
    MutexLocker ml(_ti_lock);
    _thread_names.clear();
    _thread_ids.clear();
}

void ThreadInfo::clearAll(std::set<int> &live_thread_ids) {
    // Reset thread names and IDs
    MutexLocker ml(_ti_lock);
    if (live_thread_ids.empty()) {
        // take the fast path
        _thread_names.clear();
        _thread_ids.clear();
    } else {
        // we need to honor the thread referenced from the liveness tracker
        std::map<int, std::string>::iterator name_itr = _thread_names.begin();
        while (name_itr != _thread_names.end()) {
            if (live_thread_ids.find(name_itr->first) == live_thread_ids.end()) {
                name_itr = _thread_names.erase(name_itr);
            } else {
                ++name_itr;
            }
        }
        std::map<int, u64>::iterator id_itr = _thread_ids.begin();
        while (id_itr != _thread_ids.end()) {
            if (live_thread_ids.find(id_itr->first) == live_thread_ids.end()) {
                id_itr = _thread_ids.erase(id_itr);
            } else {
                ++id_itr;
            }
        }
    }
}

int ThreadInfo::size() {
    MutexLocker ml(_ti_lock);
    return _thread_names.size();
}

void ThreadInfo::updateThreadName(int tid, std::function<std::unique_ptr<char[]>(int)> resolver) {
    MutexLocker ml(_ti_lock);

    std::map<int, std::string>::iterator it = _thread_names.lower_bound(tid);
    if (it == _thread_names.end() || it->first != tid) {
        std::unique_ptr<char[]> namePtr = resolver(tid);
        if (namePtr.get() != nullptr) {
            _thread_names.insert(it, std::map<int, std::string>::value_type(tid, static_cast<char*>(namePtr.get())));
        }
    }
}

void ThreadInfo::reportCounters() {
    MutexLocker ml(_ti_lock);
    Counters::set(THREAD_IDS_COUNT, _thread_ids.size());
    Counters::set(THREAD_NAMES_COUNT, _thread_names.size());
}