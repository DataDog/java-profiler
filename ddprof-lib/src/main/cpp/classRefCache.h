/*
 * Copyright 2023 Datadog, Inc
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

#ifndef _CLASS_REF_CACHE_H
#define _CLASS_REF_CACHE_H

#include <set>
#include <jni.h>

#include "arch.h"
#include "spinLock.h"

class ClearTask;
class Cleaner;

/**
 The JVMTI jmethodID has a crucial weakness - it is reliably valid only while the current thread is suspended (eg. executing our native code)
 or a global strong reference to the declaring class is present. Therefore, capturing stacktrace in one method and processing
 it in another can and will lead to undefined behaviours as the declaring classes of the methods referenced from the captured
 stacktrace frames can get unloaded at any time, causing SIGSEGV.
 This cache is a workaround for this - it will keep the classes around by holding to the global strong references and also
 make sure that once requested all such references will get released in order not to hinder GC.
 There are two gotchas here - first, we need to use double-buffering to avoid expensive locking on the hot path. If we would
 naively use locks to synchronize access to the cache we would block the allocation sampler for the duration of the maintenance/cleanup task.
 The second gotcha has to do with the liveness tracker - the liveness samples are surviving multiple recordings so we must make sure
 the global references pointing to the classes used from the stacktraces of those samples will not get accidentally released. For this
 purpose we are keeping around the second set called '_persistent' where the current 'protected' classes, covering the liveness samples, are being gathered.
 The '_persistent' set is modifiable and queryable only from chunk rotation/recording stop code by design and it will never be
 executed concurrently, therefore we don't need to deal with locking there.
 */
class ClassRefCache {
  friend Cleaner;

  private:
    static ClassRefCache* const _instance;

    volatile int _epoch;
    SpinLock _cache_lock[2];
    std::set<jobject> _data[2];
    std::set<jobject> _persistent;

    void doClean(ClearTask* cleanable);

  public:
    static ClassRefCache* const instance() {
      return _instance;
    }

    ClassRefCache() : _epoch(0) {}

    /**
     * Create global strong references to the given classes and keep track of them
     */
    void store(JNIEnv* jni, std::set<jclass>& classes);

    /**
     * Instruct the cache to treat the given class set as 'persistent'.
     * The previous persistent set will get replaced by the new one.
     */
    void keep(JNIEnv* jni, std::set<jclass>& kept_classes);

    /**
     * Initiate cache cleanup.
     * This will return a task instance which can be wrapped in Cleaner RAII to automatically release all relevant global strong
     * references on destruction.
     * This pattern is used in order to have 2-phased cleanup where we first switch the cache epoch such that
     * all new class references are recorded in the 'other' copy while we are still processing the current copy.
     * Once the obtained variable goes out of scope the destructor will release all contained global references
     * in the current epoch cache, except of the ones also present in the '_persistent' cache, unless 'force' is specified,
     * in which case all references will be removed.
     */
    ClearTask clear(bool force = false);

    /**
     * Unconditionally release all references from both epoch caches, regardless of the '_persistent' set.
     * Also, clear the '_persistent' set.
     */
    void destroy();
};

class ClearTask {
  friend ClassRefCache;

  private:
    const int _epoch;
    const bool _forced;
    const u64 _cache_size;
    ClearTask(int epoch, bool forced, u64 size) : _epoch(epoch), _forced(forced), _cache_size(size) {}
  public:
    inline u64 size() {
        return _cache_size;
    }
};

/**
 * RAII to wrap ClearTask
 */
class Cleaner {
  private:
    ClearTask _task;
  public:
    Cleaner(ClearTask task) : _task(task) {}
    ~Cleaner();
};

#endif // _CLASS_REF_CACHE_H