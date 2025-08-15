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

#ifndef _CALLTRACESTORAGE_H
#define _CALLTRACESTORAGE_H

#include "arch_dd.h"
#include "concurrentHashTable.h"
#include "linearAllocator.h"
#include "spinLock.h"
#include "vmEntry.h"
#include <functional>
#include <map>
#include <vector>

class LongHashTable;

struct CallTrace {
  bool truncated;
  int num_frames;
  ASGCT_CallFrame frames[1];
};

struct CallTraceSample {
  CallTrace *trace;
  u64 samples;
  u64 counter;

  CallTrace *acquireTrace() {
    return __atomic_load_n(&trace, __ATOMIC_ACQUIRE);
  }

  void setTrace(CallTrace *value) {
    return __atomic_store_n(&trace, value, __ATOMIC_RELEASE);
  }

  CallTraceSample &operator+=(const CallTraceSample &s) {
    trace = s.trace;
    samples += s.samples;
    counter += s.counter;
    return *this;
  }

  bool operator<(const CallTraceSample &other) const {
    return counter > other.counter;
  }
};

class CallTraceStorage {
private:
  static CallTrace _overflow_trace;

  LinearAllocator _allocator;
  LongHashTable *_current_table;
  u64 _overflow;

  SpinLock _lock;

  u64 calcHash(int num_frames, ASGCT_CallFrame *frames, bool truncated);
  CallTrace *storeCallTrace(int num_frames, ASGCT_CallFrame *frames,
                            bool truncated);
  CallTrace *findCallTrace(LongHashTable *table, u64 hash);

public:
  CallTraceStorage();
  ~CallTraceStorage();

  void clear();
  void collectTraces(std::map<u32, CallTrace *> &map);
  
  u32 put(int num_frames, ASGCT_CallFrame *frames, bool truncated, u64 weight);

  // Liveness tracking support
  void incrementSamples(u32 call_trace_id);
  void decrementSamples(u32 call_trace_id);

private:
  struct CallTraceLocation {
    LongHashTable* table;
    u32 slot;
    
    CallTraceLocation() : table(nullptr), slot(0) {}
    CallTraceLocation(LongHashTable* t, u32 s) : table(t), slot(s) {}
  };
  
  // Thread-safe concurrent hash table for call trace index
  ConcurrentHashTable<u32, CallTraceLocation> _call_trace_index;
};

#endif // _CALLTRACESTORAGE
