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

#include "threadFilter.h"
#include "counters.h"
#include "os_dd.h"
#include "reverse_bits.h"
#include <cassert>
#include <stdlib.h>
#include <string.h>

void trackPage() {
  Counters::increment(THREAD_FILTER_PAGES, 1);
  Counters::increment(THREAD_FILTER_BYTES, BITMAP_SIZE);
}

ThreadFilter::ThreadFilter() {
  _max_thread_id = ddprof::OS::getMaxThreadId(128 * 1024);
  _max_bitmaps = (_max_thread_id + BITMAP_SIZE - 1) / BITMAP_SIZE;
  u32 capacity = _max_bitmaps * sizeof(u64 *);
  _bitmap = (u64 **)OS::safeAlloc(capacity);
  memset(_bitmap, 0, capacity);
  _bitmap[0] = (u64 *)OS::safeAlloc(BITMAP_SIZE);
  trackPage();
  _enabled = false;
  _size = 0;
}

ThreadFilter::~ThreadFilter() {
  for (int i = 0; i < _max_bitmaps; i++) {
    if (_bitmap[i] != NULL) {
      OS::safeFree(_bitmap[i], BITMAP_SIZE);
    }
  }
  if (_bitmap) {
    OS::safeFree(_bitmap, _max_bitmaps * sizeof(u64 *));
  }
}

void ThreadFilter::init(const char *filter) {
  if (filter == NULL) {
    _enabled = false;
    return;
  }

  char *end;
  do {
    int id = strtol(filter, &end, 0);
    if (id <= 0) {
      break;
    }

    if (*end == '-') {
      int to = strtol(end + 1, &end, 0);
      while (id <= to) {
        add(id++);
      }
    } else {
      add(id);
    }

    filter = end + 1;
  } while (*end);

  _enabled = true;
}

void ThreadFilter::clear() {
  for (int i = 0; i < _max_bitmaps; i++) {
    if (_bitmap[i] != NULL) {
      memset(_bitmap[i], 0, BITMAP_SIZE);
    }
  }
  _size = 0;
}

// The mapping has to be reversible: f(f(x)) == x
int ThreadFilter::mapThreadId(int thread_id) {
  // We want to map the thread_id inside the same bitmap
  static_assert(BITMAP_SIZE >= (u16)0xffff, "Potential verflow");
  u16 lower16 = (u16)(thread_id & 0xffff);
  lower16 = reverse16(lower16);
  int tid = (thread_id & ~0xffff) | lower16;
  return tid;
}

// Get bitmap that contains the thread id, create one if it does not exist
u64* ThreadFilter::getBitmapFor(int thread_id) {
  int index = thread_id / BITMAP_CAPACITY;
  assert(index >= 0 && index < (int)_max_bitmaps);
  u64* b = _bitmap[index];
  if (b == NULL) {
    b = (u64 *)OS::safeAlloc(BITMAP_SIZE);
    u64 *oldb = __sync_val_compare_and_swap(
        &_bitmap[index], NULL, b);
    if (oldb != NULL) {
      OS::safeFree(b, BITMAP_SIZE);
      b = oldb;
    } else {
      trackPage();
    }
  }
  return b;
}

u64* ThreadFilter::bitmapAddressFor(int thread_id) {
  u64* b = getBitmapFor(thread_id);
  thread_id = mapThreadId(thread_id);
  assert(b == bitmap(thread_id));
  return wordAddress(b, thread_id);
}

bool ThreadFilter::accept(int thread_id) {
  thread_id = mapThreadId(thread_id);
  u64 *b = bitmap(thread_id);
  return b != NULL && (word(b, thread_id) & (1ULL << (thread_id & 0x3f)));
}

void ThreadFilter::add(int thread_id) {
  u64 *b = getBitmapFor(thread_id);
  assert (b != NULL);
  thread_id = mapThreadId(thread_id);
  assert(b == bitmap(thread_id));
  u64 bit = 1ULL << (thread_id & 0x3f);
  if (!(__atomic_fetch_or(&word(b, thread_id), bit, __ATOMIC_RELAXED) & bit)) {
    atomicInc(_size);
  }
}

void ThreadFilter::remove(int thread_id) {
  thread_id = mapThreadId(thread_id);
  u64 *b = bitmap(thread_id);
  if (b == NULL) {
    return;
  }

  u64 bit = 1ULL << (thread_id & 0x3f);
  if (__atomic_fetch_and(&word(b, thread_id), ~bit, __ATOMIC_RELAXED) & bit) {
    atomicInc(_size, -1);
  }
}

void ThreadFilter::collect(std::vector<int> &v) {
  for (int i = 0; i < _max_bitmaps; i++) {
    u64 *b = _bitmap[i];
    if (b != NULL) {
      int start_id = i * BITMAP_CAPACITY;
      for (int j = 0; j < BITMAP_SIZE / sizeof(u64); j++) {
        // Considering the functional impact, relaxed could be a reasonable
        // order here
        u64 word = __atomic_load_n(&b[j], __ATOMIC_ACQUIRE);
        while (word != 0) {
          int tid = start_id + j * 64 + __builtin_ctzl(word);
          // restore thread id
          tid = mapThreadId(tid);
          v.push_back(tid);
          word &= (word - 1);
        }
      }
    }
  }
}
