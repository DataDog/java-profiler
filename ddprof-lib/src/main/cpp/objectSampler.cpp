/*
 * Copyright 2022 Andrei Pangin
 * Copyright 2022, 2023 Datadog, Inc
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
#include <cmath>
#include <set>

#include <jni.h>
#include <string.h>
#include "objectSampler.h"
#include "pidController.h"
#include "profiler.h"
#include "context.h"
#include "thread.h"
#include "vmStructs.h"
#include <math.h>


ObjectSampler* const ObjectSampler::_instance = new ObjectSampler();

void ObjectSampler::SampledObjectAlloc(jvmtiEnv* jvmti, JNIEnv* jni, jthread thread,
                                       jobject object, jclass object_klass, jlong size) {
    ObjectSampler::instance()->recordAllocation(jvmti, jni, thread, BCI_ALLOC, object, object_klass, size);
}

void ObjectSampler::recordAllocation(jvmtiEnv* jvmti, JNIEnv* jni, jthread thread, int event_type, jobject object, jclass object_klass, jlong size) {
    if (!(_gc_generations || _record_allocations || _record_liveness)) {
        // nothing to do here, bail out
        return;
    }

    int tid = ProfiledThread::currentTid();

    AllocEvent event;

    char* class_name;
    if (jvmti->GetClassSignature(object_klass, &class_name, NULL) == 0) {
        int id = -1;
        if (class_name[0] == 'L') {
            id = Profiler::instance()->lookupClass(class_name + 1, strlen(class_name) - 2);
        } else {
            id = Profiler::instance()->lookupClass(class_name, strlen(class_name));
        }
        jvmti->Deallocate((unsigned char*)class_name);
        if (id == -1) {
            return;
        }
        event._id = id;
    }

    jint frames_size = 0;
    jvmtiFrameInfo *frames = nullptr;
    
    // we do record the details and stacktraces only for when recording allocations or liveness
    if (_record_allocations || _record_liveness) {
        event._size = size;
        event._weight =  (float)((size == 0 || _interval == 0) ? 1 : 1 / (1 - exp(-size / (double)_interval)));

        frames = new jvmtiFrameInfo[_max_stack_depth];

        if (jvmti->GetStackTrace(thread, 0, _max_stack_depth,
                                    frames, &frames_size) != JVMTI_ERROR_NONE || frames_size <= 0) {
            delete[] frames;
            return;
        }

        if (frames_size > 0) {
            std::set<jclass> classes;
            jclass method_class;
            for (int i = 0; i < frames_size; i++) {
                if (jvmti->GetMethodDeclaringClass(frames[i].method, &method_class) == 0) {
                    classes.insert(method_class);
                }
            }
        }
    }

    if (_record_allocations) {
        Profiler::instance()->recordExternalSample(size, tid, frames, frames_size, /*truncated=*/false, BCI_ALLOC, &event);
        
        u64 current_samples = __sync_add_and_fetch(&_alloc_event_count, 1);
        // in order to lower the number of atomic reads from the timestamp variable the check will be performed only each N samples
        if ((current_samples % _target_samples_per_window) == 0) { 
            static u64 check_period_ns = static_cast<u64>(CONFIG_UPDATE_CHECK_PERIOD_SECS) * 1000 * 1000 * 1000;
            u64 now = OS::nanotime();
            u64 prev = __atomic_load_n(&_last_config_update_ts, __ATOMIC_RELAXED);
            u64 time_diff = now - prev;
            // the config was last updated more than CONFIG_UPDATE_CHECK_PERIOD_SECS seconds ago
            if (time_diff > check_period_ns) {
                // this branch can be entered on multiple threads concurrently but only one will be able to make the config change
                if (__atomic_compare_exchange(&_last_config_update_ts, &prev, &now, false, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)) {
                    __sync_fetch_and_add(&_alloc_event_count, -current_samples);
                    updateConfiguration(current_samples, static_cast<double>(check_period_ns) / time_diff);
                }
            }
        }
    }

    // Either we are recording liveness or tracking GC generations (lightweight livenss samples)
    if (_gc_generations || _record_liveness) {
        LivenessTracker::instance()->track(jni, event, tid, object, frames_size, frames);
    }

    // it's safe to delete frames - the liveness tracker keeps a full copy of the frames and manages its own memory
    delete[] frames;
}

Error ObjectSampler::check(Arguments& args) {
    if (!VM::canSampleObjects()) {
        return Error("Allocation Sampling is not supported on this JVM");
    }
    
    _interval = std::max(args._memory, static_cast<long>(4 * 1024 * 1024));
    _configured_interval = args._memory;
    _record_allocations = args._record_allocations;
    _record_liveness = args._record_liveness;
    _gc_generations = args._gc_generations;

    _max_stack_depth = Profiler::instance()->max_stack_depth();

    return Error::OK;
}

Error ObjectSampler::start(Arguments& args) {
    Error error = check(args);
    if (error) {
        return error;
    }
    if (_interval > 0) {
        if (_record_liveness || _gc_generations) {
            error = LivenessTracker::instance()->start(args);
            if (error) {
                return error;
            }
        }
        
        jvmtiEnv* jvmti = VM::jvmti();
        // JVMTI Object Sampler is a 'solo' feature, meaning that it can only be used by one JVMTI environment.
        // Therefore, we can rely on the fact that if this agent gets hold of the sample it will be its exclusive owner.
        jvmti->SetHeapSamplingInterval(_interval);
        jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_SAMPLED_OBJECT_ALLOC, NULL);
        __atomic_store_n(&_last_config_update_ts, OS::nanotime(), __ATOMIC_RELEASE);
        // need to reset the running sum in order for 'updateConfiguration' to be able to generate proper diffs
        _alloc_event_count = 0;
    }

    return Error::OK;
}

void ObjectSampler::stop() {
    jvmtiEnv* jvmti = VM::jvmti();
    jvmti->SetEventNotificationMode(JVMTI_DISABLE, JVMTI_EVENT_SAMPLED_OBJECT_ALLOC, NULL);

    if (_record_liveness || _gc_generations) {
        LivenessTracker::instance()->stop();
    }
}

Error ObjectSampler::updateConfiguration(u64 events, double time_coefficient) {
    static PidController pid_controller(
        _target_samples_per_window, // target 6k events per minute or 1k per second
        31,  // use a rather strong proportional gain in order to react quickly to bursts
        511, // emphasize the integration based gain to focus on long-term rate limiting rather than on fair distribution
        3,   // the derivational gain is rather small because the allocation rate can change abruptly (low impact of the predicted allocation rate)
        CONFIG_UPDATE_CHECK_PERIOD_SECS, 
        15
    );

    float signal = pid_controller.compute(events, time_coefficient);
    int required_interval = _interval - static_cast<int>(signal);
    required_interval = required_interval >= _configured_interval ? required_interval : _configured_interval; // do not dip below the manually configured sampling interval
    if (required_interval != _interval) {
        _interval = required_interval;
        VM::jvmti()->SetHeapSamplingInterval(_interval);
    }

    return Error::OK;
}
