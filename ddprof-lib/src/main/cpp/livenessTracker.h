/*
 * Copyright 2021, 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _LIVENESSTRACKER_H
#define _LIVENESSTRACKER_H

#include "arch_dd.h"
#include "context.h"
#include "engine.h"
#include "event.h"
#include "spinLock.h"
#include <jvmti.h>
#include <pthread.h>
#include <set>
#include <unordered_set>

class Recording;

typedef struct TrackingEntry {
  jweak ref;
  AllocEvent alloc;
  double skipped;
  u64 call_trace_id;
  jint tid;
  jlong time;
  jlong age;
  Context ctx;
} TrackingEntry;

// Aligned to satisfy SpinLock member alignment requirement (64 bytes)
// Required because this class contains SpinLock _table_lock member
class alignas(alignof(SpinLock)) LivenessTracker {
  friend Recording;

private:
  // pre-c++17 we should mark these inline(or out of class)
  constexpr static int MAX_TRACKING_TABLE_SIZE = 262144;
  constexpr static int MIN_SAMPLING_INTERVAL = 524288; // 512kiB

  bool _initialized;
  bool _enabled;
  Error _stored_error;

  SpinLock _table_lock;
  volatile int _table_size;
  int _table_cap;
  int _table_max_cap;
  TrackingEntry *_table;

  double _subsample_ratio;

  bool _record_heap_usage;

  jclass _Class;
  jmethodID _Class_getName;

  volatile u64 _gc_epoch;
  volatile u64 _last_gc_epoch;

  size_t _used_after_last_gc;

  Error initialize(Arguments &args);
  Error initialize_table(JNIEnv *jni, int sampling_interval);

  void cleanup_table(bool force = false);

  void flush_table(std::set<int> *tracked_thread_ids);

  void onGC();
  void runCleanup();

  jlong getMaxMemory(JNIEnv *env);

public:
  static LivenessTracker *instance() {
    static LivenessTracker instance;
    return &instance;
  }
  // Delete copy constructor and assignment operator to prevent copies
  LivenessTracker(const LivenessTracker&) = delete;
  LivenessTracker& operator=(const LivenessTracker&) = delete;

  LivenessTracker()
      : _initialized(false), _enabled(false), _stored_error(Error::OK),
        _table_size(0), _table_cap(0), _table_max_cap(0), _table(NULL),
        _subsample_ratio(0.1), _record_heap_usage(false), _Class(NULL),
        _Class_getName(0), _gc_epoch(0), _last_gc_epoch(0),
        _used_after_last_gc(0) {}

  Error start(Arguments &args);
  void stop();
  void track(JNIEnv *env, AllocEvent &event, jint tid, jobject object, u64 call_trace_id);
  void flush(std::set<int> &tracked_thread_ids);

  static void JNICALL GarbageCollectionFinish(jvmtiEnv *jvmti_env);

private:
  void getLiveTraceIds(std::unordered_set<u64>& out_buffer);
};

#endif // _LIVENESSTRACKER_H
