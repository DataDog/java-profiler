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
#include "wallClock.h"
#include "profiler.h"
#include "stackFrame.h"
#include "context.h"
#include "log.h"
#include "thread.h"
#include "tsc.h"
#include "jvmti.h"
#include "vmStructs.h"

volatile bool WallClock::_enabled = false;

JavaThreadState WallClock::getThreadState(void* ucontext) {
    StackFrame frame(ucontext);
    uintptr_t pc = frame.pc();

    // Consider a thread sleeping, if it has been interrupted in the middle of syscall execution,
    // either when PC points to the syscall instruction, or if syscall has just returned with EINTR
    if (StackFrame::isSyscall((instruction_t*)pc)) {
        return JAVA_THREAD_BLOCKED;
    }

    // Make sure the previous instruction address is readable
    uintptr_t prev_pc = pc - SYSCALL_SIZE;
    if ((pc & 0xfff) >= SYSCALL_SIZE || Profiler::instance()->findLibraryByAddress((instruction_t*)prev_pc) != NULL) {
        if (StackFrame::isSyscall((instruction_t*)prev_pc) && frame.checkInterruptedSyscall()) {
            return JAVA_THREAD_BLOCKED;
        }
    }

    return JAVA_THREAD_RUNNABLE;
}

void WallClock::sharedSignalHandler(int signo, siginfo_t* siginfo, void* ucontext) {
    WallClock *engine = (WallClock*)Profiler::instance()->wallEngine();
    if (signo == SIGVTALRM) {
        engine->signalHandler(signo, siginfo, ucontext, engine->_interval);
    }
}

void WallClock::signalHandler(int signo, siginfo_t* siginfo, void* ucontext, u64 last_sample) {
    ProfiledThread* current = ProfiledThread::current();
    int tid = current != NULL ? current->tid() : OS::threadId();
    Shims::instance().setSighandlerTid(tid);
    Context& ctx = Contexts::get(tid);
    u64 skipped = 0;
    if (current != NULL) {
        if (_collapsing && !current->noteWallSample(ctx.spanId, &skipped)) {
            return;
        }
    }

    ExecutionEvent event;
    // if we're on a Java thread, we can look up the thread state, otherwise we'll figure it out from the top frame
    int index = indexOf(tid);
    int state = index >= 0 ? _thread_states[index + 1] : -1;
    event._thread_state = state >= 0 ? convertThreadState(state) : getThreadState(ucontext);
    event._weight = skipped + 1;
    Profiler::instance()->recordSample(ucontext, last_sample, tid, BCI_WALL, &event);
    Shims::instance().setSighandlerTid(-1);
}

Error WallClock::start(Arguments &args) {
    int interval = args._event != NULL ? args._interval : args._wall;
    if (interval < 0) {
        return Error("interval must be positive");
    }
    _interval = interval ? interval : DEFAULT_WALL_INTERVAL;

    _collapsing = args._wall_collapsing;

    _reservoir_size =
            args._wall_threads_per_tick ?
            args._wall_threads_per_tick :
            DEFAULT_WALL_THREADS_PER_TICK;

    _thread_state_size = (2 * _reservoir_size * sizeof(int) + 32) & ~63;
    _thread_states = (int*) aligned_alloc(64, _thread_state_size);
    for (int i = 0; i < _reservoir_size * 2; i += 2) {
        _thread_states[i] = 0x7FFFFFFF;
        _thread_states[i + 1] = -1;
    }

    OS::installSignalHandler(SIGVTALRM, sharedSignalHandler);

    _running = true;

    if (pthread_create(&_thread, NULL, threadEntry, this) != 0) {
        return Error("Unable to create timer thread");
    }

    return Error::OK;
}

void WallClock::stop() {
    _running = false;
    pthread_kill(_thread, WAKEUP_SIGNAL);
    pthread_join(_thread, NULL);
}

void WallClock::prepareThreadStates(jvmtiEnv* jvmti, std::vector<int>& reservoir, std::unordered_map<int, jthread>& thread_lookup) {
    // fix up default values
    for (int i = 0; i < _reservoir_size * 2; i += 2) {
        _thread_states[i] = 0x7FFFFFFF;
        _thread_states[i + 1] = -1;
    }
    for (int i = 0; i < reservoir.size(); i++) {
        int tid = reservoir[i];
        _thread_states[i * 2] = tid;
        auto const& java_thread = thread_lookup.find(tid);
        if (java_thread != thread_lookup.end()) {
            int state = 0;
            if (jvmti->GetThreadState(java_thread->second, &state) == 0) {
                _thread_states[i * 2 + 1] = state;
            }
        }
    }
}

void WallClock::timerLoop() {
    if (!_enabled) {
        return;
    }
    JNIEnv* jni = VM::attachThread("datadog-wallclock-sampler");
    jvmtiEnv* jvmti = VM::jvmti();
    std::vector<int> tids;
    tids.reserve(_reservoir_size);
    std::vector<int> reservoir;
    reservoir.reserve(_reservoir_size);
    int self = OS::threadId();
    ThreadFilter* thread_filter = Profiler::instance()->threadFilter();
    thread_filter->remove(self);

    std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<double> uniform(1e-16, 1.0);
    std::uniform_int_distribution<int> random_index(0, _reservoir_size - 1);

    u64 startTime = TSC::ticks();
    WallClockEpochEvent epoch(startTime);

    std::unordered_map<int, jthread> thread_lookup;

    while (_running) {
        jthread* threads;
        jint java_thread_count = 0;
        // refresh the threads via JVMTI once every 100 iterations (1 second by default)
        int jvmtiError = jvmti->GetAllThreads(&java_thread_count, &threads);
        if (jvmtiError == 0) {
            for (int i = 0; i < java_thread_count; i++) {
                jthread thread = threads[i];
                int tid = VMThread::nativeThreadId(jni, thread);
                thread_lookup[tid] = thread;
            }
        }
        for (int i = 0; i < 100; i++) {
            if (thread_filter->enabled()) {
                thread_filter->collect(tids);
            } else {
                ThreadList* thread_list = OS::listThreads();
                int tid = thread_list->next();
                while (tid != -1) {
                    if (tid != self) {
                        tids.push_back(tid);
                    }
                    tid = thread_list->next();
                }
            }
            for (int i = 0; i < _reservoir_size && i < tids.size(); i++) {
                reservoir.push_back(tids[i]);
            }
            double weight = exp(log(uniform(generator)) / _reservoir_size);
            int target = _reservoir_size + (int) (log(uniform(generator)) / log(1 - weight));
            while (target < tids.size()) {
                reservoir[random_index(generator)] = tids[target];
                weight *= exp(log(uniform(generator)) / _reservoir_size);
                target += (int) (log(uniform(generator)) / log(1 - weight));
            }

            // get the java thread states via JVMTI to be looked up by signalled threads
            prepareThreadStates(jvmti, reservoir, thread_lookup);

            int num_failures = 0;
            int threads_already_exited = 0;
            int permission_denied = 0;
            for (int tid : reservoir) {
                if (!OS::sendSignalToThread(tid, SIGVTALRM)) {
                    num_failures++;
                    if (errno != 0) {
                        switch (errno) {
                            case ESRCH:
                                threads_already_exited++;
                                break;
                            case EPERM:
                                permission_denied++;
                                break;
                            default:
                                Log::debug("unexpected error %s", strerror(errno));
                        }
                    }
                }
            }

            epoch.updateNumSamplableThreads(tids.size());
            epoch.updateNumFailedSamples(num_failures);
            epoch.updateNumSuccessfulSamples(reservoir.size() - num_failures);
            epoch.updateNumExitedThreads(threads_already_exited);
            epoch.updateNumPermissionDenied(permission_denied);
            auto endTime = TSC::ticks();
            auto duration = (1000 * (endTime - startTime)) / TSC::frequency();
            if (epoch.hasChanged() || duration >= 1000) {
                epoch.endEpoch(duration);
                Profiler::instance()->recordWallClockEpoch(self, &epoch);
                epoch.newEpoch(endTime);
                startTime = endTime;
            } else {
                epoch.clean();
            }

            reservoir.clear();
            tids.clear();
            OS::sleep(_interval);
        }
        if (threads) {
            thread_lookup.clear();
            jvmti->Deallocate((unsigned char*)threads);
        }
    }
    VM::detachThread();
}
