/*
 * Copyright 2023 Andrei Pangin
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

#ifdef __linux__

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "ctimer.h"
#include "debugSupport.h"
#include "profiler.h"
#include "vmStructs.h"
#include "FrameSampler.h"


#ifndef SIGEV_THREAD_ID
#define SIGEV_THREAD_ID  4
#endif

static inline clockid_t thread_cpu_clock(unsigned int tid) {
    return ((~tid) << 3) | 6;  // CPUCLOCK_SCHED | CPUCLOCK_PERTHREAD_MASK
}

static void** _pthread_entry = NULL;

// Intercept thread creation/termination by patching libjvm's GOT entry for pthread_setspecific().
// HotSpot puts VMThread into TLS on thread start, and resets on thread end.
static int pthread_setspecific_hook(pthread_key_t key, const void* value) {
    if (key != VMThread::key()) {
        return pthread_setspecific(key, value);
    }
    if (pthread_getspecific(key) == value) {
        return 0;
    }

    if (value != NULL) {
        ProfiledThread::initCurrentThread();
        int result = pthread_setspecific(key, value);
        Profiler::registerThread(ProfiledThread::currentTid());
        return result;
    } else {
        int tid = ProfiledThread::currentTid();
        Profiler::unregisterThread(tid);
        ProfiledThread::release();
        return pthread_setspecific(key, value);
    }
}

static void** lookupThreadEntry() {
    // Depending on Zing version, pthread_setspecific is called either from libazsys.so or from libjvm.so
    if (VM::isZing()) {
        CodeCache* libazsys = Profiler::instance()->findLibraryByName("libazsys");
        if (libazsys != NULL) {
            void** entry = libazsys->findImport(im_pthread_setspecific);
            if (entry != NULL) {
                return entry;
            }
        }
    }

    CodeCache* lib = Profiler::instance()->findJvmLibrary("libj9thr");
    return lib != NULL ? lib->findImport(im_pthread_setspecific) : NULL;
}

long CTimer::_interval;
int CTimer::_max_timers = 0;
int* CTimer::_timers = NULL;
CStack CTimer::_cstack;
volatile bool CTimer::_enabled = false;
int CTimer::_signal;
bool CTimer::_frame_samples;

int CTimer::registerThread(int tid) {
    if (tid >= _max_timers) {
        Log::warn("tid[%d] > pid_max[%d]. Restart profiler after changing pid_max", tid, _max_timers);
        return -1;
    }

    struct sigevent sev;
    sev.sigev_value.sival_ptr = NULL;
    sev.sigev_signo = _signal;
    sev.sigev_notify = SIGEV_THREAD_ID;
    ((int*)&sev.sigev_notify)[1] = tid;

    // Use raw syscalls, since libc wrapper allows only predefined clocks
    clockid_t clock = thread_cpu_clock(tid);
    int timer;
    if (syscall(__NR_timer_create, clock, &sev, &timer) < 0) {
        return -1;
    }

    // Kernel timer ID may start with zero, but we use zero as an empty slot
    if (!__sync_bool_compare_and_swap(&_timers[tid], 0, timer + 1)) {
        // Lost race
        syscall(__NR_timer_delete, timer);
        return -1;
    }

    struct itimerspec ts;
    ts.it_interval.tv_sec = (time_t)(_interval / 1000000000);
    ts.it_interval.tv_nsec = _interval % 1000000000;
    ts.it_value = ts.it_interval;
    syscall(__NR_timer_settime, timer, 0, &ts, NULL);
    return 0;
}

void CTimer::unregisterThread(int tid) {
    if (tid >= _max_timers) {
        return;
    }

    int timer = _timers[tid];
    if (timer != 0 && __sync_bool_compare_and_swap(&_timers[tid], timer--, 0)) {
        syscall(__NR_timer_delete, timer);
    }
}

Error CTimer::check(Arguments& args) {
    if (_pthread_entry == NULL && (_pthread_entry = lookupThreadEntry()) == NULL) {
        return Error("Could not set pthread hook");
    }

    timer_t timer;
    if (timer_create(CLOCK_THREAD_CPUTIME_ID, NULL, &timer) < 0) {
        return Error("Failed to create CPU timer");
    }
    timer_delete(timer);

    return Error::OK;
}

Error CTimer::start(Arguments& args) {
    if (args._interval < 0) {
        fprintf(stderr, "===> interval must be positive\n");
        return Error("interval must be positive");
    }
    if (_pthread_entry == NULL && (_pthread_entry = lookupThreadEntry()) == NULL) {
        fprintf(stderr, "===> Could not set pthread hook\n");
        return Error("Could not set pthread hook");
    }
    _interval = args.cpuSamplerInterval();
    _cstack = args._cstack;
    _signal = SIGPROF;
    _frame_samples = args._frame_samples;

    int max_timers = OS::getMaxThreadId();
    if (max_timers != _max_timers) {
        free(_timers);
        _timers = (int*)calloc(max_timers, sizeof(int));
        _max_timers = max_timers;
    }

    OS::installSignalHandler(_signal, signalHandler);

    // Enable pthread hook before traversing currently running threads
    __atomic_store_n(_pthread_entry, (void*)pthread_setspecific_hook, __ATOMIC_RELEASE);

    // Register all existing threads
    Error result = Error::OK;
    ThreadList* thread_list = OS::listThreads();
    for (int tid; (tid = thread_list->next()) != -1; ) {
        int err = registerThread(tid);
        if (err != 0) {
            fprintf(stderr, "===> Failed to register thread %d => %d\n", tid, err);
            result = Error("Failed to register thread");
        }
    }
    delete thread_list;

    return Error::OK;
}

void CTimer::stop() {
    __atomic_store_n(_pthread_entry, (void*)pthread_setspecific, __ATOMIC_RELEASE);
    for (int i = 0; i < _max_timers; i++) {
        unregisterThread(i);
    }
}

void CTimer::signalHandler(int signo, siginfo_t* siginfo, void* ucontext) {
    if (!_enabled) return;
    int tid = 0;
    ProfiledThread* current = ProfiledThread::current();
    if (current != NULL) {
        current->noteCPUSample();
        tid = current->tid();
    } else {
        tid = OS::threadId();
    }
    Shims::instance().setSighandlerTid(tid);

    if (_frame_samples) {
        FrameSampler::sample(tid, _interval, ucontext);
    }

    ExecutionEvent event;
    VMThread* vm_thread = VMThread::current();
    if (vm_thread) {
        event._execution_mode = VM::jni() != NULL
                ? convertJvmExecutionState(vm_thread->state())
                : ExecutionMode::JVM;
    }
    Profiler::instance()->recordSample(ucontext, _interval, tid, BCI_CPU, &event);
    Shims::instance().setSighandlerTid(-1);
}

#endif // __linux__
