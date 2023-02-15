/*
 * Copyright 2022 Andrei Pangin
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

#ifndef _OBJECTSAMPLER_H
#define _OBJECTSAMPLER_H

#include <jvmti.h>
#include <time.h>
#include "arch.h"
#include "engine.h"
#include "livenessTracker.h"
#include "jfrMetadata.h"

typedef int(*get_sampling_interval)();
static int __min(int a, int b) {
    return a < b ? a : b;
}

class ObjectSampler : public Engine {
  friend Recording;

  private:
    static get_sampling_interval _get_sampling_interval;
    static int* _sampling_interval;

    static int sampling_interval() {
      return _sampling_interval != NULL ? *_sampling_interval : _get_sampling_interval();
    }

    static ObjectSampler* const _instance;

    int _interval;
    bool _record_allocations;
    bool _record_liveness;
    int _max_stack_depth;

    long _last_event_count;

    const static int CONFIG_UPDATE_CHECK_PERIDD_SECS = 1;

  protected:
    void recordAllocation(jvmtiEnv* jvmti, JNIEnv* jni, jthread thread, int event_type, jobject object, jclass object_klass, jlong size);

  public:
    static ObjectSampler* const instance() {
        return _instance;
    }

    const char* title() {
        return "Allocation profile";
    }

    const char* units() {
        return "bytes";
    }

    Error check(Arguments& args);
    Error start(Arguments& args);
    Error updateConfiguration(TypeHistogram &event_histo);
    void stop();

    static void JNICALL SampledObjectAlloc(jvmtiEnv* jvmti, JNIEnv* jni, jthread thread,
                                           jobject object, jclass object_klass, jlong size);
};

#endif // _OBJECTSAMPLER_H
