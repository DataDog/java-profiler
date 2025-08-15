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
#include "linearAllocator.h"
#include "spinLock.h"
#include "vmEntry.h"
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

  // Short-term storage (regular samples, cleared on dump)
  LinearAllocator _allocator;
  LongHashTable *_current_table;
  u64 _overflow;
  SpinLock _lock;

  // Long-term storage (persists across dumps)
  LinearAllocator _longterm_allocator;
  LongHashTable *_current_longterm_table;
  u64 _longterm_overflow;
  SpinLock _longterm_lock;

  u64 calcHash(int num_frames, ASGCT_CallFrame *frames, bool truncated);
  CallTrace *storeCallTrace(int num_frames, ASGCT_CallFrame *frames,
                            bool truncated, bool longterm);
  CallTrace *findCallTrace(LongHashTable *table, u64 hash);
  CallTrace *copyCallTrace(CallTrace *original_trace, LinearAllocator *target_allocator);
  u32 putShortterm(int num_frames, ASGCT_CallFrame *frames, bool truncated, u64 weight);
  u32 putLongterm(int num_frames, ASGCT_CallFrame *frames, bool truncated);

public:
  CallTraceStorage();
  ~CallTraceStorage();

  void clear();  // Clears short-term storage, compacts long-term storage if needed
  void collectTraces(std::map<u32, CallTrace *> &map);  // Collects from both storages
  void compact(); // Compacts long-term storage

  u32 put(int num_frames, ASGCT_CallFrame *frames, bool truncated, u64 weight, bool longterm = false);
  void removeLongtermReference(u32 call_trace_id);
  
  // Methods for incrementing/decrementing samples count (for testing and liveness tracking)
  void incrementSamples(u32 call_trace_id);
  void decrementSamples(u32 call_trace_id);
};

#endif // _CALLTRACESTORAGE
