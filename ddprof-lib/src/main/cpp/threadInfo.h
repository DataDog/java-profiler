/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "countingAllocator.h"
#include "mutex.h"
#include "nativeMem.h"
#include "os.h"
#include <functional>
#include <map>
#include <memory>
#include <set>
#include <string>

class ThreadInfo {
private:
  // NM_THREAD_INFO covers these global, process-wide bookkeeping maps (they
  // grow with the total number of threads observed over the process
  // lifetime), distinct from NM_THREAD_LOCAL which covers genuinely per-thread
  // state (e.g. sizeof(ProfiledThread)).
  using ThreadNamesMap =
      std::map<int, std::string, std::less<int>,
               CountingAllocator<std::pair<const int, std::string>, NM_THREAD_INFO>>;
  using ThreadIdsMap =
      std::map<int, u64, std::less<int>,
               CountingAllocator<std::pair<const int, u64>, NM_THREAD_INFO>>;

  // std::string's own heap allocation (for names exceeding the implementation's
  // small-string-optimization inline buffer) isn't tracked by ThreadNamesMap's
  // CountingAllocator, which only accounts for map-node allocations. Track it
  // separately so NM_THREAD_INFO doesn't undercount long thread names.
  // Conservative small-string-optimization threshold: libstdc++'s inline
  // buffer holds 15 bytes, libc++'s holds 22. Using the smaller value means a
  // few libc++ strings between 16-22 bytes may be counted as heap-allocated
  // when they're actually inline (a harmless overcount) -- but it never
  // undercounts, which is the failure mode being fixed here.
  static constexpr size_t kInlineNameCapacity = 15;
  static long long nameHeapBytes(const std::string &name) {
    return name.capacity() > kInlineNameCapacity ? (long long)name.capacity() : 0;
  }

  Mutex _ti_lock;
  ThreadNamesMap _thread_names;
  ThreadIdsMap _thread_ids;

public:
  // disallow copy and assign to avoid issues with the mutex
  ThreadInfo(const ThreadInfo &) = delete;
  ThreadInfo &operator=(const ThreadInfo &) = delete;

  ThreadInfo() {}

  void set(int tid, const char *name, u64 java_thread_id);
  std::pair<std::shared_ptr<std::string>, u64> get(int tid);

  void updateThreadName(int tid, std::function<std::string(int)> resolver);

  int size();

  void clearAll(std::set<int> &live_thread_ids);
  void clearAll();

  void reportCounters();

  // For testing
  int getThreadId(int threadId);
};
