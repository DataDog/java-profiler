/*
 * Copyright 2021, 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <algorithm>
#include <random>
#include <set>
#include <thread>

#include "arch_dd.h"
#include "context.h"
#include "incbin.h"
#include "jniHelper.h"
#include "livenessTracker.h"
#include "log.h"
#include "os.h"
#include "profiler.h"
#include "thread.h"
#include "tsc.h"
#include "vmStructs_dd.h"
#include <jni.h>
#include <string.h>

constexpr int LivenessTracker::MAX_TRACKING_TABLE_SIZE;
constexpr int LivenessTracker::MIN_SAMPLING_INTERVAL;

void LivenessTracker::cleanup_table(bool forced) {
  u64 current = load(_last_gc_epoch);
  u64 target_gc_epoch = load(_gc_epoch);

  if ((target_gc_epoch == _last_gc_epoch ||
       !__sync_bool_compare_and_swap(&_last_gc_epoch, current,
                                     target_gc_epoch)) &&
      !forced) {
    // if the last processed GC epoch hasn't changed, or if we failed to update
    // it, there's nothing to do
    return;
  }

  JNIEnv *env = VM::jni();

  int epoch_diff = (int)(target_gc_epoch - current);

  _table_lock.lock();
  u32 sz = _table_size;
  if (sz > 0) {
    u64 start = OS::nanotime(), end;
    u32 newsz = 0;
    std::set<jclass> kept_classes;
    for (u32 i = 0; i < sz; i++) {
      if (_table[i].ref != nullptr &&
          !env->IsSameObject(_table[i].ref, nullptr)) {
        // it survived one more GarbageCollectionFinish event
        u32 target = newsz++;
        if (target != i) {
          _table[target] = _table[i]; // will clone TrackingEntry at 'i'
          _table[i].ref = nullptr;    // will nullify the original ref
          _table[i].call_trace_id = 0;
        }
        _table[target].age += epoch_diff;
      } else {
        jweak tmpRef = _table[i].ref;
        _table[i].ref = nullptr;
        env->DeleteWeakGlobalRef(tmpRef);
        _table[i].call_trace_id = 0;
      }
    }

    _table_size = newsz;

    end = OS::nanotime();
    Log::debug("Liveness tracker cleanup took %.2fms (%.2fus/element)",
               1.0f * (end - start) / 1000 / 1000,
               1.0f * (end - start) / 1000 / sz);
  }
  _table_lock.unlock();
}

void LivenessTracker::flush(std::set<int> &tracked_thread_ids) {
  if (!_enabled) {
    // disabled
    return;
  }
  flush_table(&tracked_thread_ids);
}

void LivenessTracker::flush_table(std::set<int> *tracked_thread_ids) {
  JNIEnv *env = VM::jni();
  u64 start = OS::nanotime(), end;

  // make sure that the tracking table is cleaned up before we start flushing it
  // this is to make sure we are including as few false 'live' objects as
  // possible
  cleanup_table();

  _table_lock.lock();

  u32 sz;
  for (int i = 0; i < (sz = _table_size); i++) {
    jobject ref = env->NewLocalRef(_table[i].ref);
    if (ref != nullptr) {
      if (tracked_thread_ids != nullptr) {
        tracked_thread_ids->insert(_table[i].tid);
      }
      ObjectLivenessEvent event;
      event._start_time = _table[i].time;
      event._age = _table[i].age;
      event._alloc = _table[i].alloc;
      event._skipped = _table[i].skipped;
      event._ctx = _table[i].ctx;

      jclass clz = env->GetObjectClass(ref);
      jstring name_str = (jstring)env->CallObjectMethod(clz, _Class_getName);
      env->DeleteLocalRef(clz);
      jniExceptionCheck(env);
      const char *name = env->GetStringUTFChars(name_str, nullptr);
      event._id = name != nullptr
                      ? Profiler::instance()->lookupClass(name, strlen(name))
                      : 0;
      env->ReleaseStringUTFChars(name_str, name);

      Profiler::instance()->recordDeferredSample(_table[i].tid, _table[i].call_trace_id, BCI_LIVENESS, &event);
    }

    env->DeleteLocalRef(ref);
  }

  _table_lock.unlock();

  if (_record_heap_usage) {
    bool isLastGc = ddprof::HeapUsage::isLastGCUsageSupported();
    size_t used = isLastGc ? ddprof::HeapUsage::get()._used_at_last_gc
                           : loadAcquire(_used_after_last_gc);
    if (used == 0) {
      used = ddprof::HeapUsage::get()._used;
      isLastGc = false;
    }
    Profiler::instance()->writeHeapUsage(used, isLastGc);
  }

  end = OS::nanotime();
  if (sz) {
    Log::debug("Liveness tracker flush took %.2fms (%.2fus/element)",
               1.0f * (end - start) / 1000 / 1000,
               1.0f * (end - start) / 1000 / sz);
  }
}

Error LivenessTracker::initialize_table(JNIEnv *jni, int sampling_interval) {
  _table_max_cap = 0;
  jlong max_heap = ddprof::HeapUsage::getMaxHeap(jni);
  if (max_heap == -1) {
    return Error("Can not track liveness for allocation samples without heap "
                 "size information.");
  }

  int required_table_capacity =
      sampling_interval > 0 ? max_heap / sampling_interval : max_heap;

  if (required_table_capacity > MAX_TRACKING_TABLE_SIZE) {
    Log::warn("Tracking liveness for allocation samples with interval %d can "
              "not cover full heap.",
              sampling_interval);
  }
  _table_max_cap = std::min(MAX_TRACKING_TABLE_SIZE, required_table_capacity);

  _table_cap = std::max(
      2048,
      _table_max_cap /
          8); // the table will grow at most 3 times before fully covering heap

  return Error::OK;
}

Error LivenessTracker::start(Arguments &args) {
  Error err = initialize(args);
  if (err) {
    return err;
  }
  if (!_enabled) {
    // disabled
    return Error::OK;
  }
  
  // Self-register with the profiler for liveness checking
  Profiler::instance()->registerLivenessChecker([this](std::vector<u64>& buffer) {
    this->getLiveTraceIds(buffer);
  });
  
  // Enable Java Object Sample events
  jvmtiEnv *jvmti = VM::jvmti();
  jvmti->SetEventNotificationMode(
      JVMTI_ENABLE, JVMTI_EVENT_GARBAGE_COLLECTION_FINISH, nullptr);

  return Error::OK;
}

void LivenessTracker::stop() {
  if (!_enabled) {
    // disabled
    return;
  }
  cleanup_table();
  flush_table(nullptr);

  // do not disable GC notifications here - the tracker is supposed to survive
  // multiple recordings
}

static int _min(int a, int b) { return a < b ? a : b; }

Error LivenessTracker::initialize(Arguments &args) {
  _enabled = args._gc_generations || args._record_liveness;

  if (!_enabled) {
    return Error::OK;
  }

  if (_initialized) {
    // if the tracker was previously initialized return the stored result for
    // consistency this hack also means that if the profiler is started with
    // different arguments for liveness tracking those will be ignored it is
    // required in order to be able to track the object liveness across many
    // recordings
    return _stored_error;
  }
  _initialized = true;

  if (VM::hotspot_version() < 11) {
    Log::warn("Liveness tracking requires Java 11+");
    // disable liveness tracking
    _table_max_cap = 0;
    return _stored_error = Error::OK;
  }

  JNIEnv *env = VM::jni();

  Error err = initialize_table(env, args._memory);
  if (err) {
    Log::warn("Liveness tracking requires heap size information");
    // disable liveness tracking
    _table_max_cap = 0;
    return _stored_error = Error::OK;
  }
  if (!(_Class = env->FindClass("java/lang/Class"))) {
    jniExceptionCheck(env, true);
    err = Error("Unable to find java/lang/Class");
  } else if (!(_Class_getName = env->GetMethodID(_Class, "getName",
                                                 "()Ljava/lang/String;"))) {
    jniExceptionCheck(env, true);
    err = Error("Unable to find java/lang/Class.getName");
  }
  if (err) {
    Log::warn("Liveness tracking requires access to java.lang.Class#getName()");
    // disable liveness tracking
    _table_max_cap = 0;
    return _stored_error = Error::OK;
  }

  _subsample_ratio = args._live_samples_ratio;

  _table_size = 0;
  _table_cap =
      std::min(2048, _table_max_cap); // with default 512k sampling interval, it's
                                   // enough for 1G of heap
  _table = (TrackingEntry *)malloc(sizeof(TrackingEntry) * _table_cap);

  _record_heap_usage = args._record_heap_usage;

  _gc_epoch = 0;
  _last_gc_epoch = 0;

  return _stored_error = Error::OK;
}

void LivenessTracker::track(JNIEnv *env, AllocEvent &event, jint tid,
                            jobject object, u64 call_trace_id) {
  if (!_enabled) {
    // disabled
    return;
  }
  if (_table_max_cap == 0) {
    // we are not to store any objects
    return;
  }

  static thread_local std::mt19937 gen(std::random_device{}());
  static thread_local std::uniform_real_distribution<> dis(0, 1.0);
  static thread_local double skipped = 0;

  if (_subsample_ratio < 1.0 && dis(gen) > _subsample_ratio) {
    skipped += static_cast<double>(event._weight) * event._size;
    return;
  }

  jweak ref = env->NewWeakGlobalRef(object);
  if (ref == nullptr) {
    return;
  }
  bool retried = false;
retry:
  if (!_table_lock.tryLockShared()) {
    // we failed to add the weak reference to the table so it won't get cleaned
    // up otherwise
    env->DeleteWeakGlobalRef(ref);
    return;
  }

  // Increment _table_size in a thread-safe manner (CAS) and store the new value
  // in idx It bails out if _table_size would overflow _table_cap
  int idx;
  do {
    idx = __atomic_load_n(&_table_size, __ATOMIC_RELAXED);
  } while (idx < _table_cap &&
           !__sync_bool_compare_and_swap(&_table_size, idx, idx + 1));

  if (idx < _table_cap) {
    _table[idx].tid = tid;
    _table[idx].time = TSC::ticks();
    _table[idx].ref = ref;
    _table[idx].alloc = event;
    _table[idx].skipped = skipped;
    _table[idx].age = 0;
    _table[idx].call_trace_id = call_trace_id;
    _table[idx].ctx = Contexts::get(tid);
  }

  _table_lock.unlockShared();

  if (idx == _table_cap) {
    if (!retried) {
      // guarantees we don't busy loop until memory exhaustion
      retried = true;

      // try cleanup before resizing - there is a good chance it will free some
      // space
      cleanup_table(true);

      if (_table_cap < _table_max_cap) {

        // Let's increase the size of the table
        // This should only ever happen when sampling interval * size of table
        // is smaller than maximum heap size. So we only support increasing
        // the size of the table, not decreasing it.
        _table_lock.lock();

        // Only increase the size of the table to _table_max_cap elements
        int newcap = std::min(_table_cap * 2, _table_max_cap);
        if (_table_cap != newcap) {
          TrackingEntry *tmp = (TrackingEntry *)realloc(
              _table, sizeof(TrackingEntry) * (_table_cap = newcap));
          if (tmp != nullptr) {
            _table = tmp;
            Log::debug(
                "Increased size of Liveness tracking table to %d entries",
                _table_cap);
          } else {
            Log::debug("Cannot add sampled object to Liveness tracking table, "
                       "resize attempt failed, the table is overflowing");
          }
        }

        _table_lock.unlock();

        goto retry;
      } else {
        Log::debug("Cannot add sampled object to Liveness tracking table, it's "
                   "overflowing");
      }
    }
  }
  skipped = 0; // reset the subsampling skipped bytes
}

void JNICALL LivenessTracker::GarbageCollectionFinish(jvmtiEnv *jvmti_env) {
  LivenessTracker::instance()->onGC();
}

void LivenessTracker::onGC() {
  if (!_initialized) {
    return;
  }

  // just increment the epoch
  atomicIncRelaxed(_gc_epoch,u64(1));

  if (!ddprof::HeapUsage::isLastGCUsageSupported()) {
    store(_used_after_last_gc, ddprof::HeapUsage::get(false)._used);
  }
}

void LivenessTracker::getLiveTraceIds(std::vector<u64>& out_buffer) {
  out_buffer.clear();
  
  if (!_enabled || !_initialized) {
    return;
  }
  
  // Lock the table to iterate over tracking entries
  _table_lock.lockShared();
  
  // Reserve space to avoid reallocations during filling
  out_buffer.reserve(_table_size);
  
  // Collect call_trace_id values from all live tracking entries
  for (int i = 0; i < _table_size; i++) {
    TrackingEntry* entry = &_table[i];
    if (entry->ref != nullptr) {
      out_buffer.push_back(entry->call_trace_id);
    }
  }
  
  _table_lock.unlockShared();
}
