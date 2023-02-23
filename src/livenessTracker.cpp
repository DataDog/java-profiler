/*
* Copyright 2021, 2022 Datadog, Inc
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

#include <jni.h>
#include <string.h>
#include "context.h"
#include "incbin.h"
#include "livenessTracker.h"
#include "os.h"
#include "profiler.h"
#include "log.h"
#include "thread.h"
#include "tsc.h"
#include "vmStructs.h"

LivenessTracker* const LivenessTracker::_instance = new LivenessTracker();

void LivenessTracker::cleanup_table() {
    JNIEnv *env = VM::jni();

    u64 start = OS::nanotime(), end;

    _table_lock.lock();

    u32 sz, newsz = 0;
    for (u32 i = 0; i < (sz = _table_size); i++) {
        jobject ref = env->NewLocalRef(_table[i].ref);
        if (ref != NULL) {
            // it survived one more GarbageCollectionFinish event
            _table[i].age += 1;

            _table[newsz++] = _table[i];
        } else {
            env->DeleteWeakGlobalRef(_table[i].ref);
            delete[] _table[i].frames;
        }

        env->DeleteLocalRef(ref);
    }

    _table_size = newsz;

    _table_lock.unlock();

    end = OS::nanotime();
    Log::debug("Liveness tracker cleanup took %.2fms (%.2fus/element)",
                1.0f * (end - start) / 1000 / 1000, 1.0f * (end - start) / 1000 / sz);
}

void LivenessTracker::flush() {
    flush_table();
}

void LivenessTracker::flush_table() {
    JNIEnv *env = VM::jni();
    u64 start = OS::nanotime(), end;

    _table_lock.lockShared();

    u32 sz;
    for (int i = 0; i < (sz = _table_size); i++) {
        jobject ref = env->NewLocalRef(_table[i].ref);
        if (ref != NULL) {
            ObjectLivenessEvent event;
            event._start_time = _table[i].time;
            event._age = _table[i].age;
            event._alloc = _table[i].alloc;
            event._ctx = _table[i].ctx;

            jstring name_str = (jstring)env->CallObjectMethod(env->GetObjectClass(ref), _Class_getName);
            const char *name = env->GetStringUTFChars(name_str, NULL);
            event._id = name != NULL ? Profiler::instance()->classMap()->lookup(name) : 0;
            env->ReleaseStringUTFChars(name_str, name);

            Profiler::instance()->recordExternalSample(1, _table[i].tid, _table[i].frames, _table[i].frames_size, /*truncated=*/false, BCI_LIVENESS, &event);
        }

        env->DeleteLocalRef(ref);
    }

    _table_lock.unlockShared();

    end = OS::nanotime();
    Log::debug("Liveness tracker flush took %.2fms (%.2fus/element)",
                1.0f * (end - start) / 1000 / 1000, 1.0f * (end - start) / 1000 / sz);
}

void* LivenessTracker::cleanup_thread(void *arg) {
    LivenessTracker::instance()->runCleanup();
    return NULL;
}

void LivenessTracker::runCleanup() {
    VM::attachThread("java-profiler Liveness tracker cleanup");

    while (true) {
        pthread_mutex_lock(&_cleanup_mutex);
        while (_cleanup_round == 0) {
            if (!_cleanup_run) {
                goto exit;
            }
            pthread_cond_wait(&_cleanup_cond, &_cleanup_mutex);
        }
        _cleanup_round -= 1;
        pthread_mutex_unlock(&_cleanup_mutex);

        jint nentries = 0;

        cleanup_table();
    }

exit:
    VM::detachThread();
}

static jlong getMaxHeap(JNIEnv* env) {
    static jclass _rt;
    static jmethodID _get_rt;
    static jmethodID _max_memory;

    if (!(_rt = env->FindClass("java/lang/Runtime"))) {
        env->ExceptionDescribe();
        return -1;
    }

    if (!(_get_rt = env->GetStaticMethodID(_rt, "getRuntime", "()Ljava/lang/Runtime;"))) {
        env->ExceptionDescribe();
        return -1;
    }

    if (!(_max_memory = env->GetMethodID(_rt, "maxMemory", "()J"))) {
        env->ExceptionDescribe();
        return -1;
    }

    jobject rt = (jobject)env->CallStaticObjectMethod(_rt, _get_rt);
    return (jlong)env->CallLongMethod(rt, _max_memory);
}

Error LivenessTracker::initialize_table(int sampling_interval) {
    _table_max_cap = 0;
    jlong max_heap = getMaxHeap(VM::jni());
    if (max_heap == -1) {
        return Error("Unable to retrieve the max heap value");
    }

    int required_table_capacity = sampling_interval > 0 ? max_heap / sampling_interval : max_heap;
    
    if (required_table_capacity > MAX_TRACKING_TABLE_SIZE) {
        Log::warn("Tracking liveness for allocation samples with interval %d can not cover full heap.", sampling_interval);
    }
    _table_max_cap = __min(MAX_TRACKING_TABLE_SIZE, required_table_capacity);

    _table_cap = std::max(2048, _table_max_cap / 8); // the table will grow at most 3 times before fully covering heap
    return Error::OK;
}

Error LivenessTracker::start(Arguments& args) {
    Error err = initialize(args);
    if (err) { return err; }
    fprintf(stdout, "===> initializing live heap tracker\n");
    // Enable Java Object Sample events
    jvmtiEnv* jvmti = VM::jvmti();
    jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_GARBAGE_COLLECTION_FINISH, NULL);

    return Error::OK;
}

void LivenessTracker::stop() {
    JNIEnv* env = VM::jni();
    cleanup_table();
    flush_table();

    // do not disable GC notifications here - the tracker is supposed to survive multiple recordings
}

static int _min(int a, int b) { return a < b ? a : b; }

Error LivenessTracker::initialize(Arguments& args) {
    if (_initialized) {
        // if the tracker was previously initialized return the stored result for consistency
        // this hack also means that if the profiler is started with different arguments for liveness tracking those will be ignored
        // it is required in order to be able to track the object liveness across many recordings
        return _stored_error;
    }
    _initialized = true;

    if (VM::hotspot_version() < 11) {
        Log::warn("Liveness tracking requires Java 11+");
        // disable liveness tracking
        _table_max_cap = 0;
        return _stored_error = Error::OK;
    }

    JNIEnv* env = VM::jni();

    Error err = initialize_table(args._memory);
    if (err) {
        return _stored_error = err;
    }
    _table_size = 0;
    _table_cap = __min(2048, _table_max_cap); // with default 512k sampling interval, it's enough for 1G of heap
    _table = (TrackingEntry*)malloc(sizeof(TrackingEntry) * _table_cap);

    if (!(_Class = env->FindClass("java/lang/Class"))) {
        free(_table);
        env->ExceptionDescribe();
        return _stored_error = Error("Unable to find java/lang/Class");
    }
    if (!(_Class_getName = env->GetMethodID(_Class, "getName", "()Ljava/lang/String;"))) {
        free(_table);
        env->ExceptionDescribe();
        return _stored_error = Error("Unable to find java/lang/Class.getName");
    }

    _cleanup_round = 0;
    _cleanup_run = true;
    if (pthread_mutex_init(&_cleanup_mutex, NULL) != 0 ||
        pthread_cond_init(&_cleanup_cond, NULL) != 0 ||
        pthread_create(&_cleanup_thread, NULL, cleanup_thread, NULL) != 0) {
        _cleanup_run = false;
        free(_table);
        return _stored_error = Error("Unable to create Liveness tracker cleanup thread");
    }

    env->ExceptionClear();

    fprintf(stdout, "===> live heap tracker initialized ok\n");
    return _stored_error = Error::OK;
}

void LivenessTracker::track(JNIEnv* env, AllocEvent &event, jint tid, jobject object, int num_frames, jvmtiFrameInfo* frames) {
    if (_table_max_cap == 0) {
        // we are not to store any objects
        return;
    }

    jweak ref = env->NewWeakGlobalRef(object);
    if (ref == NULL) {
        return;
    }

    bool retried = false;

retry:
    if (!_table_lock.tryLockShared()) {
        return;
    }

    // Increment _table_size in a thread-safe manner (CAS) and store the new value in idx
    // It bails out if _table_size would overflow _table_cap
    int idx;
    do {
        idx = _table_size;
    } while (idx < _table_cap &&
                !__sync_bool_compare_and_swap(&_table_size, idx, idx + 1));

    if (idx < _table_cap) {
        _table[idx].tid = tid;
        _table[idx].time = TSC::ticks();
        _table[idx].ref = ref;
        _table[idx].alloc = event;
        _table[idx].age = 0;
        _table[idx].frames_size = num_frames;
        _table[idx].frames = new jvmtiFrameInfo[_table[idx].frames_size];
        memcpy(_table[idx].frames, frames, sizeof(jvmtiFrameInfo) * _table[idx].frames_size);
        _table[idx].ctx = Contexts::get(tid);
    }

    _table_lock.unlockShared();

    if (idx == _table_cap) {
        if (!retried && _table_cap < _table_max_cap) {
            // guarantees we don't busy loop until memory exhaustion
            retried = true;

            // Let's increase the size of the table
            // This should only ever happen when sampling interval * size of table
            // is smaller than maximum heap size. So we only support increasing
            // the size of the table, not decreasing it.
            _table_lock.lock();

            // Only increase the size of the table to 8k elements
            int newcap = __min(_table_cap * 2, _table_max_cap);
            if (_table_cap != newcap) {
                TrackingEntry* tmp = (TrackingEntry*)realloc(_table, sizeof(TrackingEntry) * (_table_cap = newcap));
                if (tmp != NULL) {
                    _table = tmp;
                    Log::debug("Increased size of Liveness tracking table to %d entries", _table_cap);
                } else {
                    Log::debug("Cannot add sampled object to Liveness tracking table, resize attempt failed, the table is overflowing");        
                }
            }

            _table_lock.unlock();

            goto retry;
        } else {
            Log::debug("Cannot add sampled object to Liveness tracking table, it's overflowing");
        }
    }

    delete[] frames;
}

void JNICALL LivenessTracker::GarbageCollectionFinish(jvmtiEnv *jvmti_env) {
    LivenessTracker::instance()->onGC();
}

void LivenessTracker::onGC() {
    if (!_initialized) {
        return;
    }

    if (pthread_mutex_lock(&_cleanup_mutex) != 0) {
        Log::debug("[LivenessTracker] Unable to lock for cleanup");
        return;
    }
    _cleanup_round += 1;
    pthread_cond_signal(&_cleanup_cond);
    pthread_mutex_unlock(&_cleanup_mutex);
}
