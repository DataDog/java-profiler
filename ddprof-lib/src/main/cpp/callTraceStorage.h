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
  // Stores traces with SAME IDs as short-term, with reference counting
  LinearAllocator _longterm_allocator;
  SpinLock _longterm_lock;
  std::map<u32, CallTraceSample> _longterm_traces;
  

  u64 calcHash(int num_frames, ASGCT_CallFrame *frames, bool truncated);
  CallTrace *storeCallTrace(int num_frames, ASGCT_CallFrame *frames,
                            bool truncated, bool longterm);
  CallTrace *findCallTrace(LongHashTable *table, u64 hash);
  CallTrace *copyCallTrace(CallTrace *original_trace, LinearAllocator *target_allocator);
  bool tracesEqual(CallTrace *trace1, CallTrace *trace2);
  u32 putShortterm(int num_frames, ASGCT_CallFrame *frames, bool truncated, u64 weight);

public:
  CallTraceStorage();
  ~CallTraceStorage();

  void clear();  // Clears short-term storage, compacts long-term storage if needed
  void collectTraces(std::map<u32, CallTrace *> &map);  // Collects from both storages
  void collectAndConsolidateTraces(std::map<u32, CallTrace *> &map);  // Collects from both storages with deduplication
  void resetCollectedSamples();  // Resets samples to 0 for all collected traces
  void compact(); // Compacts long-term storage

  u32 put(int num_frames, ASGCT_CallFrame *frames, bool truncated, u64 weight);
  void promoteToLongterm(u32 call_trace_id);  // Copy trace to long-term with same ID
  void removeLongtermReference(u32 call_trace_id);  // Decrements long-term reference count
  
  // Methods for incrementing/decrementing samples count (for testing and liveness tracking)
  void incrementSamples(u32 call_trace_id);
  void decrementSamples(u32 call_trace_id);
};

#endif // _CALLTRACESTORAGE
