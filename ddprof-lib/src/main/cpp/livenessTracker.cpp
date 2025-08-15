/*
 * Copyright 2021, 2025 Datadog, Inc
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

#include <algorithm>
#include <random>
#include <set>
#include <thread>

#include "arch_dd.h"
#include "callTraceStorage.h"
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
#include "common.h"
#include <jni.h>
#include <string.h>

constexpr int LivenessTracker::MAX_TRACKING_TABLE_SIZE;
constexpr int LivenessTracker::MIN_SAMPLING_INTERVAL;

void LivenessTracker::cleanup_table(bool forced) {
  u64 current = loadAcquire(_last_gc_epoch);
  u64 target_gc_epoch = loadAcquire(_gc_epoch);

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

  _tracking_table.withExclusiveLock([&](TrackingEntry* table, int& table_size) {
    u32 sz = table_size;
    if (sz > 0) {
      u64 start = OS::nanotime(), end;
      u32 newsz = 0;
      std::set<jclass> kept_classes;
      for (u32 i = 0; i < sz; i++) {
        if (table[i].ref != nullptr &&
            !env->IsSameObject(table[i].ref, nullptr)) {
          // it survived one more GarbageCollectionFinish event
          u32 target = newsz++;
          if (target != i) {
            table[target] = table[i]; // will clone TrackingEntry at 'i'
            table[i].ref = nullptr;    // will nullify the original ref
            table[i].call_trace_id = 0;
          }
          table[target].age += epoch_diff;
        } else {
          // Entry is being garbage collected - decrement samples in call trace storage
          u32 call_trace_id = table[i].call_trace_id;
          if (call_trace_id != 0 && _call_trace_storage != nullptr) {
            _call_trace_storage->decrementSamples(call_trace_id);
          }
          
          jweak tmpRef = table[i].ref;
          table[i].ref = nullptr;
          env->DeleteWeakGlobalRef(tmpRef);
          table[i].call_trace_id = 0;
        }
      }

      table_size = newsz;

      end = OS::nanotime();
      Log::debug("Liveness tracker cleanup took %.2fms (%.2fus/element)",
                 1.0f * (end - start) / 1000 / 1000,
                 1.0f * (end - start) / 1000 / sz);
    }
  });
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

  u32 sz = 0;
  _tracking_table.withExclusiveLock([&](TrackingEntry* table, int& table_size) {
    sz = table_size;
    for (int i = 0; i < sz; i++) {
      jobject ref = env->NewLocalRef(table[i].ref);
      if (ref != nullptr) {
        if (tracked_thread_ids != nullptr) {
          tracked_thread_ids->insert(table[i].tid);
        }
        ObjectLivenessEvent event;
        event._start_time = table[i].time;
        event._age = table[i].age;
        event._alloc = table[i].alloc;
        event._skipped = table[i].skipped;
        event._ctx = table[i].ctx;

        jclass clz = env->GetObjectClass(ref);
        jstring name_str = (jstring)env->CallObjectMethod(clz, _Class_getName);
        env->DeleteLocalRef(clz);
        jniExceptionCheck(env);
        const char *name = env->GetStringUTFChars(name_str, nullptr);
        event._id = name != nullptr
                        ? Profiler::instance()->lookupClass(name, strlen(name))
                        : 0;
        env->ReleaseStringUTFChars(name_str, name);

        TEST_LOG("LivenessTracker::flush recording liveness event with call_trace_id=%u", table[i].call_trace_id);
        _call_trace_storage->incrementSamples(table[i].call_trace_id);
        Profiler::instance()->recordDeferredSample(table[i].tid, table[i].call_trace_id, BCI_LIVENESS, &event);
      }

      env->DeleteLocalRef(ref);
    }
  });

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

  if (!_tracking_table.initialize(_table_max_cap)) {
    Log::warn("Failed to initialize tracking table");
    _table_max_cap = 0;
    return _stored_error = Error::OK;
  }

  _record_heap_usage = args._record_heap_usage;

  _gc_epoch = 0;
  _last_gc_epoch = 0;

  return _stored_error = Error::OK;
}

void LivenessTracker::track(JNIEnv *env, AllocEvent &event, jint tid,
                            jobject object, u32 call_trace_id) {
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
  TrackingEntry entry;
  entry.tid = tid;
  entry.time = TSC::ticks();
  entry.ref = ref;
  entry.alloc = event;
  entry.skipped = skipped;
  entry.age = 0;
  entry.call_trace_id = call_trace_id;
  entry.ctx = Contexts::get(tid);

  int idx = _tracking_table.addEntry(entry);
  
  if (idx == -1) {
    // Table is full or couldn't acquire lock
    bool retried = false;
    
retry:
    if (!retried) {
      retried = true;
      
      // try cleanup before resizing - there is a good chance it will free some space
      cleanup_table(true);

      if (_tracking_table.capacity() < _table_max_cap) {
        // Try to resize the table
        int newcap = std::min(_tracking_table.capacity() * 2, _table_max_cap);
        if (_tracking_table.resize(newcap)) {
          Log::debug("Increased size of Liveness tracking table to %d entries", newcap);
          idx = _tracking_table.addEntry(entry);
          if (idx != -1) {
            goto success;
          }
        } else {
          Log::debug("Cannot add sampled object to Liveness tracking table, "
                     "resize attempt failed, the table is overflowing");
        }
      } else {
        Log::debug("Cannot add sampled object to Liveness tracking table, it's overflowing");
      }
    }
    
    // Failed to add entry, cleanup the weak reference
    env->DeleteWeakGlobalRef(ref);
    return;
  }

success:
  // Increment sample count to preserve the call trace referenced by this tracking entry
  if (call_trace_id != 0 && _call_trace_storage != nullptr) {
    _call_trace_storage->incrementSamples(call_trace_id);
    TEST_LOG("LivenessTracker::track stored call_trace_id=%u for object", call_trace_id);
  }
  
  skipped = 0; // reset the subsampling skipped bytes
}

void JNICALL LivenessTracker::GarbageCollectionFinish(jvmtiEnv *jvmti_env) {
  LivenessTracker::instance()->onGC();
}


void LivenessTracker::markLiveCallTraces() {
  if (!_enabled || _call_trace_storage == nullptr) {
    return;
  }
  
  _tracking_table.markLiveCallTraces([this](u32 call_trace_id) {
    _call_trace_storage->incrementSamples(call_trace_id);
  });
}

void LivenessTracker::setCallTraceStorage(CallTraceStorage& storage) {
  _call_trace_storage = &storage;
}

void LivenessTracker::onGC() {
  if (!_initialized) {
    return;
  }

  // just increment the epoch
  atomicInc(_gc_epoch, 1);

  if (!ddprof::HeapUsage::isLastGCUsageSupported()) {
    storeRelease(_used_after_last_gc, ddprof::HeapUsage::get(false)._used);
  }
}
