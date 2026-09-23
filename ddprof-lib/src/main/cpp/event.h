/*
 * Copyright 2020 Andrei Pangin
 * Copyright 2026, Datadog, Inc.
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

#ifndef _EVENT_H
#define _EVENT_H

#include "context.h"
#include "os.h"
#include "threadState.h"
#include <cstring>
#include <memory>
#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

#define MAX_STRING_LEN 8191

// The order is important: look for event_type comparison
enum EventType {
    PERF_SAMPLE,
    EXECUTION_SAMPLE,
    WALL_CLOCK_SAMPLE,
    MALLOC_SAMPLE,
    SOCKET_SAMPLE,
    INSTRUMENTED_METHOD,
    METHOD_TRACE,
    ALLOC_SAMPLE,
    ALLOC_OUTSIDE_TLAB,
    LIVE_OBJECT,
    LOCK_SAMPLE,
    PARK_SAMPLE,
    PROFILING_WINDOW,
    USER_EVENT,
};

class Event {
public:
  u32 _id;

  Event() : _id(0) {}
};

class ExecutionEvent : public Event {
public:
  OSThreadState _thread_state;
  ExecutionMode _execution_mode;
  u64 _weight;
  u32 _call_trace_id;

  ExecutionEvent()
      : Event(), _thread_state(OSThreadState::RUNNABLE), _execution_mode(ExecutionMode::UNKNOWN),
        _weight(1), _call_trace_id(0) {}
};

class AllocEvent : public Event {
public:
  u64 _size;
  float _weight;

  AllocEvent() : _size(0), _weight(1) {}
};

class LockEvent : public Event {
public:
  u64 _start_time;
  u64 _end_time;
  uintptr_t _address;
  long long _timeout;
};

class ObjectLivenessEvent : public Event {
public:
  AllocEvent _alloc;
  u64 _skipped;
  u64 _start_time;
  u64 _age;
  // 0 = untagged; leak tag from LivenessTracker pool. Default-initialized so
  // every construction path (current and future) serializes a defined value -
  // flush_table() overwrites it from the entry's own tag (track() zeroes it
  // at insert).
  int64_t leak_tag = 0;
  Context _ctx;
};

// Reporting surface for the reference-chain engine's bounded BFS.
// `_target_tag` is the frontier tag the chain was reconstructed for;
// `_hops`
// holds the reconstructed chain in the same leaf(target)-to-root order:
// hop[i].klass_id is the referrer-klass StringDictionary id and
// hop[i].edge_label is the edge by which hop[i] is retained by its parent
// (the field name of its parent hop for FIELD/STATIC_FIELD edges, the
// edge-kind label otherwise, resolved by the collector filling this event).
// For a static-field-rooted chain the root-side end is the static field's
// holder instance followed by the declaring class (the ROOT TYPE, appended
// by the collector from the root-attached entry's declaring-class tag) -
// the chain then reads, root-first, as the root type retaining the holder
// through its static field, on down to the target. `_depth` is the target
// entry's own frontier depth (hop count from the search's root-side
// seed). `_root_kind` is the jvmtiHeapReferenceKind of whichever edge first
// admitted this chain into the frontier - labels *why* the
// chain is reachable at all (JNI global, thread stack, static field, ...),
// written out as a string (Recording::recordReferenceChain(),
// flightRecorder.cpp) rather than a synthetic node in `_hops` itself, since
// that array is a T_CLASS cpool array with no room for a non-class
// placeholder.
// Byte cap for one hop's retention-edge label in ReferenceChainHop
// (label resolution truncates to this; recordReferenceChain() reserves
// against it) - a shared constant so the collector and the writer cannot
// drift apart on the worst-case event size.
static constexpr size_t MAX_REFERENCE_CHAIN_EDGE_LABEL = 96;

// One retained hop of a reconstructed chain. edge_label is empty when label
// resolution is unavailable (partial mock environments); production events
// carry either all labels or none (canary events), so the writer treats a
// single empty label as "no labels at all".
struct ReferenceChainHop {
  u32 klass_id;
  std::string edge_label;
};

class ReferenceChainEvent : public Event {
public:
  u64 _start_time;
  u64 _target_tag;
  u32 _depth;
  u8 _root_kind;
  std::vector<ReferenceChainHop> _hops;

  ReferenceChainEvent()
      : Event(), _start_time(0), _target_tag(0), _depth(0), _root_kind(0) {}
};

// Search-level abandonment signal: reports why the reference-chain search
// stopped before every frontier entry could be resolved, using the same
// counters the search itself already maintains.
class ReferenceChainAbandonedEvent : public Event {
public:
  u64 _start_time;
  u8 _reason; // SearchAbandonReason (the engine's reason enum)
  u32 _passes_run;
  u32 _frontier_size;
  int _hop_cap;
  int _budget;
  long _ttl_ms;
  u64 _elapsed_ns;

  ReferenceChainAbandonedEvent()
      : Event(), _start_time(0), _reason(0), _passes_run(0),
        _frontier_size(0), _hop_cap(0), _budget(0), _ttl_ms(0),
        _elapsed_ns(0) {}
};

class MallocEvent : public Event {
public:
  u64 _start_time;
  uintptr_t _address;
  u64 _size;
  float _weight;

  MallocEvent() : Event(), _start_time(0), _address(0), _size(0), _weight(1.0f) {}
};

class NativeSocketEvent : public Event {
public:
  u64  _start_time;          // TSC ticks at call entry
  u64  _end_time;            // TSC ticks at call return
  u8   _operation;           // 0 = SEND, 1 = RECV, 2 = WRITE, 3 = READ
  char _remote_addr[64];     // "ip:port" null-terminated string
  u64  _bytes;               // bytes transferred (return value of send/recv/write/read)
  float _weight;             // inverse-transform sample weight

  NativeSocketEvent() : Event(), _start_time(0), _end_time(0), _operation(0),
                        _bytes(0), _weight(1.0f) { _remote_addr[0] = '\0'; }
};

class WallClockEpochEvent {
public:
  bool _dirty;
  u64 _start_time;
  u64 _duration_millis;
  u32 _num_samplable_threads;
  u32 _num_successful_samples;
  u32 _num_failed_samples;
  u32 _num_exited_threads;
  u32 _num_permission_denied;
  u64 _num_suppressed_sampled_run;

  WallClockEpochEvent(u64 start_time)
      : _dirty(false), _start_time(start_time), _duration_millis(0),
        _num_samplable_threads(0), _num_successful_samples(0),
        _num_failed_samples(0), _num_exited_threads(0),
        _num_permission_denied(0), _num_suppressed_sampled_run(0) {}

  bool hasChanged() { return _dirty; }

  void updateNumSamplableThreads(u32 num_samplable_threads) {
    if (_num_samplable_threads != num_samplable_threads) {
      _dirty = true;
      _num_samplable_threads = num_samplable_threads;
    }
  }

  void updateNumSuccessfulSamples(u32 num_successful_samples) {
    if (_num_successful_samples != num_successful_samples) {
      _dirty = true;
      _num_successful_samples = num_successful_samples;
    }
  }

  void updateNumFailedSamples(u32 num_failed_samples) {
    if (_num_failed_samples != num_failed_samples) {
      _dirty = true;
      _num_failed_samples = num_failed_samples;
    }
  }

  void updateNumExitedThreads(u32 num_exited_threads) {
    if (_num_exited_threads != num_exited_threads) {
      _dirty = true;
      _num_exited_threads = num_exited_threads;
    }
  }

  void updateNumPermissionDenied(u32 num_permission_denied) {
    if (_num_permission_denied != num_permission_denied) {
      _dirty = true;
      _num_permission_denied = num_permission_denied;
    }
  }

  void addNumSuppressedSampledRun(u64 n) {
    if (n > 0) {
      _dirty = true;
      _num_suppressed_sampled_run += n;
    }
  }

  void endEpoch(u64 millis) { _duration_millis = millis; }

  void clean() { _dirty = false; }

  void newEpoch(u64 start_time) {
    _dirty = false;
    _start_time = start_time;
    _num_suppressed_sampled_run = 0;
  }
};

class TraceRootEvent {
public:
  u64 _local_root_span_id;
  u32 _label;
  u32 _operation;

  TraceRootEvent(u64 local_root_span_id, u32 label, u32 operation)
      : _local_root_span_id(local_root_span_id), _label(label),
        _operation(operation){};
};

typedef struct QueueTimeEvent {
  u64 _start;
  u64 _end;
  u32 _task;
  u32 _scheduler;
  u32 _origin;
  u32 _queueType;
  u32 _queueLength;
} QueueTimeEvent;

#endif // _EVENT_H
