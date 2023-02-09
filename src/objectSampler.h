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
#include "arch.h"
#include "engine.h"
#include "livenessTracker.h"

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

    static int _interval;
    static bool _record_allocations;
    static bool _record_liveness;
    static int _max_stack_depth;

  protected:
    static void recordAllocation(jvmtiEnv* jvmti, JNIEnv* jni, jthread thread, int event_type, jobject object, jclass object_klass, jlong size);

  public:
    const char* title() {
        return "Allocation profile";
    }

    const char* units() {
        return "bytes";
    }

    Error check(Arguments& args);
    Error start(Arguments& args);
    void stop();

    static void JNICALL SampledObjectAlloc(jvmtiEnv* jvmti, JNIEnv* jni, jthread thread,
                                           jobject object, jclass object_klass, jlong size);
};

#endif // _OBJECTSAMPLER_H
