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

#ifndef _EVENT_H
#define _EVENT_H

#include "context.h"
#include "os.h"
#include "threadState.h"
#include <cstring>
#include <memory>
#include <stdint.h>
using namespace std;

#define MAX_STRING_LEN 8191

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
  Context _ctx;
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

  WallClockEpochEvent(u64 start_time)
      : _dirty(false), _start_time(start_time), _duration_millis(0),
        _num_samplable_threads(0), _num_successful_samples(0),
        _num_failed_samples(0), _num_exited_threads(0),
        _num_permission_denied(0) {}

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

  void endEpoch(u64 millis) { _duration_millis = millis; }

  void clean() { _dirty = false; }

  void newEpoch(u64 start_time) {
    _dirty = false;
    _start_time = start_time;
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
