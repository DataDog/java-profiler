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

#include <cmath>
#include <jni.h>
#include <string.h>
#include "objectSampler.h"
#include "pidController.h"
#include "profiler.h"
#include "context.h"
#include "thread.h"
#include "vmStructs.h"

get_sampling_interval ObjectSampler::_get_sampling_interval;
int* ObjectSampler::_sampling_interval;


ObjectSampler* const ObjectSampler::_instance = new ObjectSampler();

void ObjectSampler::SampledObjectAlloc(jvmtiEnv* jvmti, JNIEnv* jni, jthread thread,
                                       jobject object, jclass object_klass, jlong size) {
    ObjectSampler::instance()->recordAllocation(jvmti, jni, thread, BCI_ALLOC, object, object_klass, size);
}

void ObjectSampler::recordAllocation(jvmtiEnv* jvmti, JNIEnv* jni, jthread thread, int event_type, jobject object, jclass object_klass, jlong size) {
    int tid = ProfiledThread::currentTid();

    AllocEvent event;
    int interval = sampling_interval();

    event._size = size;
    event._weight =  (size == 0 || interval == 0) ? 1 : 1 / (1 - std::exp(-size / (float)interval));

    char* class_name;
    if (jvmti->GetClassSignature(object_klass, &class_name, NULL) == 0) {
        if (class_name[0] == 'L') {
            event._id = Profiler::instance()->classMap()->lookup(class_name + 1, strlen(class_name) - 2);
        } else {
            event._id = Profiler::instance()->classMap()->lookup(class_name);
        }
        jvmti->Deallocate((unsigned char*)class_name);
    }

    jvmtiFrameInfo *frames = new jvmtiFrameInfo[_max_stack_depth];
    jint frames_size = 0;
    if (jvmti->GetStackTrace(thread, 0, _max_stack_depth,
                                frames, &frames_size) != JVMTI_ERROR_NONE || frames_size <= 0) {
        delete[] frames;
        return;
    }

    if (_record_allocations) {
        Profiler::instance()->recordExternalSample(size, tid, frames, frames_size, /*truncated=*/false, BCI_ALLOC, &event);
        
        u64 current_samples = __sync_add_and_fetch(&_alloc_event_count, 1);
        // in order to lower the number of atomic reads from the timestamp variable the check will be performed only each 1024 samples
        // the number 1024 is chosen arbitrarily to +- match the expected number of samples per sampling window (1000)
        if ((current_samples & 1023) == 0) { // effectively 'current_samples % 1024 == 0'
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

    if (_record_liveness) {
        // 'frames' will be released by the tracker
        LivenessTracker::instance()->track(jni, event, tid, object, frames_size, frames);
    } else {
        // otherwise the 'frames' need to be deleted here
        delete[] frames;
    }
}

Error ObjectSampler::check(Arguments& args) {
    if (!VM::canSampleObjects()) {
        return Error("SampledObjectAlloc is not supported on this JVM");
    }
    
    _interval = args._memory;
    _record_allocations = args._record_allocations;
    _record_liveness = args._record_liveness;

    _max_stack_depth = Profiler::instance()->max_stack_depth();

    // resolve the function/member pointers to retrieve the current JVMTI heap sampling interval
    // the reason for re-retrieving is that the interval can be modified by external JVMTI agents
    CodeCache* libjvm = VMStructs::libjvm();

    // this symbol should be available given the current JVTMI heap sampler implementation
    // Note: when/if that implementation would change in the future the alternatives should be added here
    const void* get_interval_ptr = libjvm->findSymbol("_ZN17ThreadHeapSampler21get_sampling_intervalEv");
    if (get_interval_ptr == NULL) {
        _sampling_interval = (int*) libjvm->findSymbol("_ZN17ThreadHeapSampler18_sampling_intervalE");
    }
    if (get_interval_ptr == NULL && _sampling_interval == NULL) {
        // fail if it is not possible to resolve the required symbol
        Log::warn("Allocation sampling is not supported on this JDK");
        return Error::OK;
    }
    _get_sampling_interval = (get_sampling_interval)get_interval_ptr;

    return Error::OK;
}

Error ObjectSampler::start(Arguments& args) {
    Error error = check(args);
    if (error) {
        return error;
    }
    
    if (_interval > 0) {
        if (_record_liveness) {
            // TODO all this '_record_liveness' checks should be done in LivenessTracker but that would require massive refactoring
            error = LivenessTracker::instance()->start(args);
            if (error) {
                return error;
            }
        }
        jvmtiEnv* jvmti = VM::jvmti();
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

    if (_record_liveness) {
        LivenessTracker::instance()->stop();
    }
}

Error ObjectSampler::updateConfiguration(u64 events, double time_coefficient) {
    static PidController pid_controller(
        1000, // target 60k events per minute or 1k per second
        16, // use a rather strong proportional gain in order to react quickly to bursts
        23, // emphasize the integration based gain to focus on long-term rate limiting rather than on fair distribution
        3,  // the derivational gain is rather small because the allocation rate can change abruptly (low impact of the predicted allocation rate)
        CONFIG_UPDATE_CHECK_PERIOD_SECS, 
        15
    );

    float signal = pid_controller.compute(events, time_coefficient);
    int current_interval = sampling_interval();
    int required_interval = current_interval - signal;
    if (required_interval >= _interval) { // do not dip below the manually configured sampling interval
        VM::jvmti()->SetHeapSamplingInterval(required_interval);
    }

    return Error::OK;
}
