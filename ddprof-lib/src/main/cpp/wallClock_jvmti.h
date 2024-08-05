/*
 * Copyright 2024 Datadog
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

#ifndef _WALLCLOCK_JVMTI_H
#define _WALLCLOCK_JVMTI_H

#include <atomic>
#include <climits>
#include <signal.h>
#include <pthread.h>
#include "engine.h"
#include "os.h"
#include "threadState.h"

class JvmtiWallClockSampler : public Engine {
  private:
    static std::atomic<bool> _enabled;

    long _interval;

    // Maximum number of threads sampled in one iteration. This limit serves as a throttle
    // when generating profiling signals. Otherwise applications with too many threads may
    // suffer from a big profiling overhead. Also, keeping this limit low enough helps
    // to avoid contention on a spin lock inside Profiler::recordSample().
    int _reservoir_size;

    std::atomic<bool> _running;
    pthread_t _thread;

    void timerLoop();

    static void* threadEntry(void* wall_clock) {
        ((JvmtiWallClockSampler*)wall_clock)->timerLoop();
        return NULL;
    }

  public:
    JvmtiWallClockSampler() :
        _interval(LONG_MAX),
        _reservoir_size(0),
        _running(false),
        _thread(0) {}

    const char* units() {
        return "ns";
    }

    const char* name() {
        return "WallClock - JVMTI";
    }

    long interval() const {
        return _interval;
    }

    Error start(Arguments& args);
    void stop();

    inline void enableEvents(bool enabled) {
        _enabled.store(enabled, std::memory_order_release);
    }
};

#endif // _WALLCLOCK_JVMTI_H
