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

#include "criticalSection.h"
#include "ctimer.h"
#include "debugSupport.h"
#include "libraries.h"
#include "profiler.h"
#include "vmStructs.h"
#include <assert.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <time.h>
#include <unistd.h>

#ifndef SIGEV_THREAD_ID
#define SIGEV_THREAD_ID 4
#endif

typedef void* (*func_start_routine)(void*);
typedef int (*func_pthread_create)(pthread_t* thread,
                                   const pthread_attr_t* attr,
                                   func_start_routine start_routine,
                                   void* arg);

//  Patching libraries' pthread_create() @plt entries
typedef struct _patchEntry {
    // library's @plt location
    func_pthread_create* _location;
    // original function
    func_pthread_create  _func;
} PatchEntry;

static PatchEntry* patched_entries = nullptr;
static volatile int num_of_entries = 0;

typedef struct _startRoutineArg {
    func_start_routine _func;
    void*              _arg;
} StartRoutineArg;

static void* start_routine_wrapper(void* args) {
    StartRoutineArg* data = (StartRoutineArg*)args;
    ProfiledThread::initCurrentThread();
    int tid = ProfiledThread::currentTid();
    Profiler::registerThread(tid);
    void* result = data->_func(data->_arg);
    Profiler::unregisterThread(tid);
    ProfiledThread::release();
    free(args);
    return result;
}

static int pthread_create_hook(pthread_t* thread,
                          const pthread_attr_t* attr,
                          func_start_routine start_routine,
                          void* arg) {
  StartRoutineArg* data = (StartRoutineArg*)malloc(sizeof(StartRoutineArg));
  data->_func = start_routine;
  data->_arg = arg;
  return pthread_create(thread, attr, start_routine_wrapper, (void*)data);
}

static Error patch_libraries() {
   Dl_info info;
   void* caller_address = __builtin_return_address(0); // Get return address of caller

   if (!dladdr(caller_address, &info)) {
      return Error("Cannot resolve current library name");
   }
   TEST_LOG("Profiler library name: %s", info.dli_fname );

  const CodeCacheArray& native_libs = Libraries::instance()->native_libs();
  int count = 0;
  int num_of_libs = native_libs.count();
  size_t size = num_of_libs * sizeof(PatchEntry);
  patched_entries = (PatchEntry*)malloc(size);
  memset((void*)patched_entries, 0, size);
  TEST_LOG("Patching libraries");

  for (int index = 0; index < num_of_libs; index++) {
     CodeCache* lib = native_libs.at(index);
     // Don't patch self
     if (strcmp(lib->name(), info.dli_fname) == 0) {
        continue;
     }

     func_pthread_create* pthread_create_addr = (func_pthread_create*)lib->findImport(im_pthread_create);
     if (pthread_create_addr != nullptr) {
       TEST_LOG("Patching %s", lib->name());

       patched_entries[count]._location = pthread_create_addr;
       patched_entries[count]._func = (func_pthread_create)__atomic_load_n(pthread_create_addr, __ATOMIC_RELAXED);
        __atomic_store_n(pthread_create_addr, (func_pthread_create)pthread_create_hook, __ATOMIC_RELAXED);
        count++;
     }
  }
  // Publish everything, including patched entries
  __atomic_store_n(&num_of_entries, count, __ATOMIC_SEQ_CST);
  return Error::OK;
}

static void unpatch_libraries() {
  int count = __atomic_load_n(&num_of_entries, __ATOMIC_RELAXED);
  PatchEntry* tmp = patched_entries;
  patched_entries = nullptr;
  __atomic_store_n(&num_of_entries, 0, __ATOMIC_SEQ_CST);

  for (int index = 0; index < count; index++) {
     if (tmp[index]._location != nullptr) {
       __atomic_store_n(tmp[index]._location, tmp[index]._func, __ATOMIC_RELAXED);
     }
  }
  __atomic_thread_fence(__ATOMIC_SEQ_CST);
  free((void*)tmp);
}


static inline clockid_t thread_cpu_clock(unsigned int tid) {
  return ((~tid) << 3) | 6; // CPUCLOCK_SCHED | CPUCLOCK_PERTHREAD_MASK
}

long CTimer::_interval;
int CTimer::_max_timers = 0;
int *CTimer::_timers = NULL;
CStack CTimer::_cstack;
bool CTimer::_enabled = false;
int CTimer::_signal;

int CTimer::registerThread(int tid) {
  if (tid >= _max_timers) {
    Log::warn("tid[%d] > pid_max[%d]. Restart profiler after changing pid_max",
              tid, _max_timers);
    return -1;
  }

  struct sigevent sev;
  sev.sigev_value.sival_ptr = NULL;
  sev.sigev_signo = _signal;
  sev.sigev_notify = SIGEV_THREAD_ID;
  ((int *)&sev.sigev_notify)[1] = tid;

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
  // Atomic acquire to avoid possible leak when unregistering
  // This was raised by tsan, with registers and unregisters done in separate
  // threads.
  int timer = __atomic_load_n(&_timers[tid], __ATOMIC_ACQUIRE);
  if (timer != 0 && __sync_bool_compare_and_swap(&_timers[tid], timer--, 0)) {
    syscall(__NR_timer_delete, timer);
  }
}

Error CTimer::check(Arguments &args) {
  timer_t timer;
  if (timer_create(CLOCK_THREAD_CPUTIME_ID, NULL, &timer) < 0) {
    return Error("Failed to create CPU timer");
  }
  timer_delete(timer);

  return Error::OK;
}

Error CTimer::start(Arguments &args) {
  if (args._interval < 0) {
    return Error("interval must be positive");
  }

  _interval = args.cpuSamplerInterval();
  _cstack = args._cstack;
  _signal = SIGPROF;

  int max_timers = OS::getMaxThreadId();
  if (max_timers != _max_timers) {
    free(_timers);
    _timers = (int *)calloc(max_timers, sizeof(int));
    _max_timers = max_timers;
  }

  OS::installSignalHandler(_signal, signalHandler);

  Error err = patch_libraries();
  if (err) {
    return err;
  }

  // Register all existing threads
  Error result = Error::OK;
  ThreadList *thread_list = OS::listThreads();
  while (thread_list->hasNext()) { 
    int tid = thread_list->next();
    int err = registerThread(tid);
    if (err != 0) {
      result = Error("Failed to register thread");
    }
  }
  delete thread_list;

  return Error::OK;
}

void CTimer::stop() {
  unpatch_libraries();
  for (int i = 0; i < _max_timers; i++) {
    unregisterThread(i);
  }
}

void CTimer::signalHandler(int signo, siginfo_t *siginfo, void *ucontext) {
  // Atomically try to enter critical section - prevents all reentrancy races
  CriticalSection cs;
  if (!cs.entered()) {
    return;  // Another critical section is active, defer profiling
  }
  // Save the current errno value
  int saved_errno = errno;
  // we want to ensure memory order because of the possibility the instance gets
  // cleared
  if (!__atomic_load_n(&_enabled, __ATOMIC_ACQUIRE))
    return;
  int tid = 0;
  ProfiledThread *current = ProfiledThread::currentSignalSafe();
  assert(current == nullptr || !current->isDeepCrashHandler());
  if (current != NULL) {
    current->noteCPUSample(Profiler::instance()->recordingEpoch());
    tid = current->tid();
  } else {
    tid = OS::threadId();
  }
  Shims::instance().setSighandlerTid(tid);

  ExecutionEvent event;
  VMThread *vm_thread = VMThread::current();
  if (vm_thread) {
    event._execution_mode = VM::jni() != NULL
                                ? convertJvmExecutionState(vm_thread->state())
                                : ExecutionMode::JVM;
  }
  Profiler::instance()->recordSample(ucontext, _interval, tid, BCI_CPU, 0,
                                     &event);
  Shims::instance().setSighandlerTid(-1);
  // we need to avoid spoiling the value of errno (tsan report)
  errno = saved_errno;
}

#endif // __linux__
