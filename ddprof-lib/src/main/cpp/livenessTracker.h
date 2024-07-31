/*
 * Copyright 2021, 2023 Datadog, Inc
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

#ifndef _LIVENESSTRACKER_H
#define _LIVENESSTRACKER_H

#include <jvmti.h>
#include <pthread.h>
#include "arch.h"
#include "context.h"
#include "engine.h"
#include "event.h"
#include "spinLock.h"
#include <set>

class Recording;

typedef struct TrackingEntry {
    jweak ref;
    AllocEvent alloc;
    double skipped;
    jint frames_size;
    jvmtiFrameInfo *frames;
    jint tid;
    jlong time;
    jlong age;
    Context ctx;
} TrackingEntry;

class LivenessTracker  {
  friend Recording;

  private:
    const static int MAX_TRACKING_TABLE_SIZE = 262144;
    const static int MIN_SAMPLING_INTERVAL = 524288; // 512kiB

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

    Error initialize(Arguments& args);
    Error initialize_table(JNIEnv* jni, int sampling_interval);

    void cleanup_table(bool force = false);

    void flush_table(std::set<int> *tracked_thread_ids);

    void onGC();
    void runCleanup();

    jlong getMaxMemory(JNIEnv* env);

    static LivenessTracker* const _instance;

  public:
    static LivenessTracker* instance() {
        return _instance;
    }

    LivenessTracker() : _initialized(false), _enabled(false), _stored_error(Error::OK), _table_size(0), _table_cap(0), _table(NULL), _table_max_cap(0), _subsample_ratio(0.1), _record_heap_usage(false), _Class(NULL), _Class_getName(0), _gc_epoch(0), _last_gc_epoch(0), _used_after_last_gc(0) {}

    Error start(Arguments& args);
    void stop();
    void track(JNIEnv* env, AllocEvent &event, jint tid, jobject object, int num_frames, jvmtiFrameInfo* frames);
    void flush(std::set<int> &tracked_thread_ids);

    static void JNICALL GarbageCollectionFinish(jvmtiEnv *jvmti_env);
};

#endif // _LIVENESSTRACKER_H
