/*
 * Copyright 2020 Andrei Pangin
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _THREADFILTER_H
#define _THREADFILTER_H

#include "arch.h"
#include <vector>

// The size of thread ID bitmap in bytes. Must be at least 64K to allow mmap()
const u32 BITMAP_SIZE = 65536;
// How many thread IDs one bitmap can hold
const u32 BITMAP_CAPACITY = BITMAP_SIZE * 8;

// ThreadFilter query operations must be lock-free and signal-safe;
// update operations are mostly lock-free, except rare bitmap allocations
class ThreadFilter {
private:
  // Total number of bitmaps required to hold the entire range of thread IDs
  u32 _max_thread_id;
  u32 _max_bitmaps;
  u64 **_bitmap;
  bool _enabled;
  volatile int _size;

  u64 *bitmap(int thread_id) {
    if (thread_id >= _max_thread_id) {
      return NULL;
    }
    return __atomic_load_n(
        &(_bitmap[static_cast<u32>(thread_id) / BITMAP_CAPACITY]),
        __ATOMIC_ACQUIRE);
  }

  u64 &word(u64 *bitmap, int thread_id) {
    // todo: add thread safe APIs
    return bitmap[((u32)thread_id % BITMAP_CAPACITY) >> 6];
  }

public:
  ThreadFilter();
  ThreadFilter(ThreadFilter &threadFilter) = delete;
  ~ThreadFilter();

  bool enabled() { return _enabled; }

  int size() { return _size; }

  void init(const char *filter);
  void clear();

  bool accept(int thread_id);
  void add(int thread_id);
  void remove(int thread_id);

  void collect(std::vector<int> &v);
};

#endif // _THREADFILTER_H
