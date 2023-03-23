/*
 * Copyright 2021 Datadog, Inc
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
#include "spinLock.h"

#include <set>

typedef struct TrackingEntry {
    jweak ref;
    AllocEvent alloc;
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
    Error _stored_error;

    SpinLock _table_lock;
    volatile int _table_size;
    int _table_cap;
    int _table_max_cap;
    TrackingEntry *_table;

    jclass _Class;
    jmethodID _Class_getName;
    jclass _MemLeak;
    jmethodID _MemLeak_process;
    jclass _MemLeakEntry;
    jmethodID _MemLeakEntry_init;

    pthread_t _cleanup_thread;
    pthread_mutex_t _cleanup_mutex;
    pthread_cond_t _cleanup_cond;
    u32 _cleanup_round;
    bool _cleanup_run;

    Error initialize(Arguments& args);
    Error initialize_table(int sampling_interval);

    void cleanup_table();

    void flush_table(std::set<int> *tracked_thread_ids);

    void onGC();
    void runCleanup();

    static void* cleanup_thread(void *arg);
    static LivenessTracker* const _instance;

  public:
    static LivenessTracker* instance() {
        return _instance;
    }

    LivenessTracker() : _initialized(false), _stored_error(Error::OK), _table_size(0), _table_cap(0), _table(NULL), _table_max_cap(0), _Class(NULL), _Class_getName(0), _MemLeak(NULL), _MemLeak_process(0), _MemLeakEntry(NULL), _MemLeakEntry_init(0), _cleanup_round(0), _cleanup_run(false) {}

    Error start(Arguments& args);
    void stop();
    void track(JNIEnv* env, AllocEvent &event, jint tid, jobject object, int num_frames, jvmtiFrameInfo* frames);
    void flush(std::set<int> &tracked_thread_ids);

    static void JNICALL GarbageCollectionFinish(jvmtiEnv *jvmti_env);
};

#endif // _LIVENESSTRACKER_H
