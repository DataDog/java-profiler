/*
 * Copyright 2018 Andrei Pangin
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

#include <math.h>
#include <random>
#include "debugSupport.h"
#include "wallClock_jvmti.h"
#include "profiler.h"
#include "stackFrame.h"
#include "context.h"
#include "log.h"
#include "thread.h"
#include "tsc.h"
#include "vmStructs.h"
#include "reservoir_sampler.h"
#include <jvmti.h>

std::atomic<bool> JvmtiWallClockSampler::_enabled{false};

Error JvmtiWallClockSampler::start(Arguments &args) {
    int interval = args._event != NULL ? args._interval : args._wall;
    if (interval < 0) {
        return Error("interval must be positive");
    }
    _interval = interval ? interval : DEFAULT_WALL_INTERVAL;

    _reservoir_size =
            args._wall_threads_per_tick ?
            args._wall_threads_per_tick :
            DEFAULT_WALL_THREADS_PER_TICK;

    _running = true;

    if (pthread_create(&_thread, NULL, threadEntry, this) != 0) {
        return Error("Unable to create timer thread");
    }

    return Error::OK;
}

void JvmtiWallClockSampler::stop() {
    _running.store(false);
    // the thread join ensures we wait for the thread to finish before returning (and possibly removing the object)
    pthread_kill(_thread, WAKEUP_SIGNAL);
    int res = pthread_join(_thread, NULL);
    if(res != 0) {
        Log::warn("Unable to join WallClock thread on stop %d", res);
    }
}

void JvmtiWallClockSampler::timerLoop() {
    ThreadFilter* thread_filter = Profiler::instance()->threadFilter();
    if (!_enabled.load(std::memory_order_acquire) || !thread_filter->enabled()) {
        return;
    }
    JNIEnv* jni = VM::attachThread("datadog-wallclock-sampler");
    jvmtiEnv* jvmti = VM::jvmti();
    const int max_frames = Profiler::instance()->max_stack_depth();
    jvmtiFrameInfo* frames = frames = new jvmtiFrameInfo[max_frames];
    std::vector<int> tids;
    tids.reserve(_reservoir_size);
    std::vector<jthread> javaThreads;
    javaThreads.reserve(_reservoir_size);
    ReservoirSampler<int> reservoir(_reservoir_size);
    int self = OS::threadId();
    u64 counter = 0;


    while (_running.load(std::memory_order_relaxed)) {
        int numFailures = 0;
        int threadsAlreadyExited = 0;
        std::vector<int> sample = reservoir.sample(tids);
        Profiler::instance()->getThreads(sample, javaThreads);
        for (int i = 0; i < sample.size(); i++) {
            int tid = sample[i];
            jthread javaThread = javaThreads[i];
            if (javaThread != nullptr) {
                jint depth;
                jint error = jvmti->GetStackTrace(javaThread, 0, max_frames, frames, &depth);
                if (error == 0 && depth > 0) {
                    ExecutionEvent event;
                    event._execution_mode = ExecutionMode::JAVA;
                    event._thread_state = ThreadState::UNKNOWN;
                    jint state;
                    if (jvmti->GetThreadState(javaThread, &state) == 0) {
                        event._thread_state = convertJvmtiThreadState(state);
                        event._execution_mode = getExecutionModeFromJvmtiThreadState(state);
                    }
                    Profiler::instance()->recordExternalSample(0, tid, frames, depth, false, BCI_WALL, &event);
                }
            } else {
                threadsAlreadyExited++;
            }
        }
        tids.clear();
        OS::sleep(_interval);
    }
    VM::detachThread();
}
