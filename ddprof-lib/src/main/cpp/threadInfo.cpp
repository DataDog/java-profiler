/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "threadInfo.h"
#include "counters.h"
#include "mutex.h"

void ThreadInfo::set(int tid, const char *name, u64 java_thread_id) {
  MutexLocker ml(_ti_lock);
  auto it = _thread_names.find(tid);
  long long old_bytes = it != _thread_names.end() ? nameHeapBytes(it->second) : 0;
  std::string &stored = _thread_names[tid];
  stored = std::string(name);
  long long new_bytes = nameHeapBytes(stored);
  if (new_bytes != old_bytes) {
    NativeMem::record(NM_THREAD_INFO, new_bytes - old_bytes);
  }
  _thread_ids[tid] = java_thread_id;
}

std::pair<std::shared_ptr<std::string>, u64> ThreadInfo::get(int threadId) {
  MutexLocker ml(_ti_lock);
  auto it = _thread_names.find(threadId);
  if (it != _thread_names.end()) {
    return std::make_pair(std::make_shared<std::string>(it->second),
                          _thread_ids[threadId]);
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
  long long freed_bytes = 0;
  for (const auto &kv : _thread_names) {
    freed_bytes += nameHeapBytes(kv.second);
  }
  if (freed_bytes != 0) {
    NativeMem::record(NM_THREAD_INFO, -freed_bytes);
  }
  _thread_names.clear();
  _thread_ids.clear();
}

void ThreadInfo::clearAll(std::set<int> &live_thread_ids) {
  // Reset thread names and IDs
  MutexLocker ml(_ti_lock);
  if (live_thread_ids.empty()) {
    // take the fast path
    long long freed_bytes = 0;
    for (const auto &kv : _thread_names) {
      freed_bytes += nameHeapBytes(kv.second);
    }
    if (freed_bytes != 0) {
      NativeMem::record(NM_THREAD_INFO, -freed_bytes);
    }
    _thread_names.clear();
    _thread_ids.clear();
  } else {
    // we need to honor the thread referenced from the liveness tracker
    auto name_itr = _thread_names.begin();
    while (name_itr != _thread_names.end()) {
      if (live_thread_ids.find(name_itr->first) == live_thread_ids.end()) {
        long long bytes = nameHeapBytes(name_itr->second);
        if (bytes != 0) {
          NativeMem::record(NM_THREAD_INFO, -bytes);
        }
        name_itr = _thread_names.erase(name_itr);
      } else {
        ++name_itr;
      }
    }
    auto id_itr = _thread_ids.begin();
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

void ThreadInfo::updateThreadName(
    int tid, std::function<std::string(int)> resolver) {
  // Fast path: bail out if the name is already known, holding the lock only
  // for the lookup.
  {
    MutexLocker ml(_ti_lock);
    if (_thread_names.find(tid) != _thread_names.end()) {
      return;
    }
  }
  // Resolve OUTSIDE the lock: the resolver may perform blocking I/O (e.g.
  // reading /proc/self/task/<tid>/comm). Holding _ti_lock across that would
  // stall every concurrent set/get/clearAll caller for the duration of the
  // syscall, once per unknown tid.
  std::string name = resolver(tid);
  if (name.empty()) {
    return;
  }
  // emplace is a no-op if a concurrent caller inserted this tid in the
  // meantime, so the brief unlocked window is harmless.
  MutexLocker ml(_ti_lock);
  auto result = _thread_names.emplace(tid, std::move(name));
  if (result.second) {
    long long bytes = nameHeapBytes(result.first->second);
    if (bytes != 0) {
      NativeMem::record(NM_THREAD_INFO, bytes);
    }
  }
}

void ThreadInfo::reportCounters() {
  MutexLocker ml(_ti_lock);
  Counters::set(THREAD_IDS_COUNT, _thread_ids.size());
  Counters::set(THREAD_NAMES_COUNT, _thread_names.size());
}