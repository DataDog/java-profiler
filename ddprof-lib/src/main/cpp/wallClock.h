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

#ifndef _WALLCLOCK_H
#define _WALLCLOCK_H

#include <climits>
#include <jvmti.h>
#include <signal.h>
#include <pthread.h>
#include "engine.h"
#include "os.h"
#include "threadState.h"
#include "jvmti.h"
#include <unordered_map>

class WallClock : public Engine {
  private:
    static volatile bool _enabled;
    bool _collapsing;
    long _interval;
    volatile int* _thread_states;
    int _thread_state_size;

    // Maximum number of threads sampled in one iteration. This limit serves as a throttle
    // when generating profiling signals. Otherwise applications with too many threads may
    // suffer from a big profiling overhead. Also, keeping this limit low enough helps
    // to avoid contention on a spin lock inside Profiler::recordSample().
    int _reservoir_size;

    volatile bool _running;
    pthread_t _thread;

    void timerLoop();

    static void* threadEntry(void* wall_clock) {
        ((WallClock*)wall_clock)->timerLoop();
        return NULL;
    }

    static JavaThreadState getThreadState(void* ucontext);

    static void sharedSignalHandler(int signo, siginfo_t* siginfo, void* ucontext);
    void signalHandler(int signo, siginfo_t* siginfo, void* ucontext, u64 last_sample);

  public:
    WallClock() :
        _collapsing(false),
        _interval(LONG_MAX),
        _reservoir_size(0),
        _thread_state_size(0),
        _running(false),
        _thread(0),
        _thread_states(NULL) {}

    const char* units() {
        return "ns";
    }

    const char* name() {
        return "WallClock";
    }

    Error start(Arguments& args);
    void stop();

    inline void enableEvents(bool enabled) {
        _enabled = enabled;
    }

    int indexOf(int tid) {
        // by default this should be 2 x64 cache lines, and linear search avoids sorting the reservoir
        for (int i = 0; i < _reservoir_size * 2; i += 2) {
            if (_thread_states[i] == tid) {
                return i;
            }
        }
        return -1;
    }

    void prepareThreadStates(jvmtiEnv* jvmti, std::vector<int>& reservoir, std::unordered_map<int, jthread>& thread_lookup);
};

#endif // _WALLCLOCK_H
