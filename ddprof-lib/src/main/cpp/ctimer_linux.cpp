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
#include <stdlib.h>
#include <sys/syscall.h>
#include <time.h>
#include <unistd.h>

#ifndef SIGEV_THREAD_ID
#define SIGEV_THREAD_ID 4
#endif

static inline clockid_t thread_cpu_clock(unsigned int tid) {
  return ((~tid) << 3) | 6; // CPUCLOCK_SCHED | CPUCLOCK_PERTHREAD_MASK
}

typedef void* (*func_start_routine)(void*);
typedef int (*func_pthread_create)(pthread_t* thread,
                          	   const pthread_attr_t* attr,
                          	   func_start_routine start_routine,
                                   void* arg);
typedef int (*func_pthread_setspecific)(pthread_key_t key, const void *value);


static func_pthread_setspecific *_pthread_setspecific_entry = nullptr;

// Intercept thread creation/termination by patching libjvm's GOT entry for
// pthread_setspecific(). HotSpot puts VMThread into TLS on thread start, and
// resets on thread end.
static int pthread_setspecific_hook(pthread_key_t key, const void *value) {
  if (key != static_cast<pthread_key_t>(VMThread::key())) {
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

typedef struct startRoutineData {
    func_start_routine _func;
    void*              _arg;
} StartRoutineData;


static void* start_routine_wrapper(void* args) {
    StartRoutineData* data = (StartRoutineData*)args;
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
  StartRoutineData* data = (StartRoutineData*)malloc(sizeof(StartRoutineData));
  data->_func = start_routine;
  data->_arg = arg;
  return pthread_create(thread, attr, start_routine_wrapper, (void*)data);
}

static void **lookupJVMEntry(enum ImportId im_id) {
  // Depending on Zing version, pthread_setspecific is called either from
  // libazsys.so or from libjvm.so
  if (VM::isZing()) {
    CodeCache *libazsys = Libraries::instance()->findLibraryByName("libazsys");
    if (libazsys != NULL) {
      void **entry = libazsys->findImport(im_id);
      if (entry != NULL) {
        return entry;
      }
    }
  }

  CodeCache *lib = Libraries::instance()->findJvmLibrary("libj9thr");
  return lib != NULL ? lib->findImport(im_id) : NULL;
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

struct PatchedEntry {
   func_pthread_create* _location;
   func_pthread_create  _original_func;
};

static PatchedEntry* patched_entries = nullptr;
static volatile int entry_count = 0;
static const char* excluded_libraries[] = {"libstdc++.so", "libjavaProfiler"};

static bool exclude_library(const char* libname) {
 const char* java_home = VM::java_home();
  // exclude JDK libraries
  if (strstr(libname, java_home) != nullptr) {
    return true;
  }
  size_t count = sizeof(excluded_libraries) / sizeof(const char*);

  for (int index = 0; index < count; index++) {
     if (strstr(libname, excluded_libraries[index]) != nullptr) {
       return true;
     }
  }
  return false;
}

static Error patch_libraries() {
  // Patch JVM
  if (_pthread_setspecific_entry == nullptr &&
      (_pthread_setspecific_entry = (func_pthread_setspecific*)lookupJVMEntry(im_pthread_setspecific)) == NULL) {
    return Error("Could not set pthread_setspecific hook");
  }

  // Enable pthread hook before traversing currently running threads
  __atomic_store_n(_pthread_setspecific_entry, (func_pthread_setspecific)pthread_setspecific_hook,
                   __ATOMIC_RELAXED);

  const CodeCacheArray& native_libs = Libraries::instance()->native_libs();
  int count = native_libs.count();
  size_t size = count * sizeof(PatchedEntry);
  patched_entries = (struct PatchedEntry*)malloc(size);
  memset((void*)patched_entries, 0, size);
  TEST_LOG("Patching libraris\n");
  const char* java_home = VM::java_home();
  size_t java_home_len = strlen(java_home);

  for (int index = 0; index < count; index++) {
     CodeCache* lib = native_libs.at(index);
     if (exclude_library(lib->name())) continue;

     func_pthread_create* pthread_create_addr = (func_pthread_create*)lib->findImport(im_pthread_create);
     if (pthread_create_addr != nullptr) {
       TEST_LOG("Patching %s\n", lib->name());

       patched_entries[index]._location = pthread_create_addr;
       patched_entries[index]._original_func = (func_pthread_create)__atomic_load_n(pthread_create_addr, __ATOMIC_RELAXED);
        __atomic_store_n(pthread_create_addr, (func_pthread_create)pthread_create_hook, __ATOMIC_RELAXED);
     }
  }
  __atomic_store_n(&entry_count, count, __ATOMIC_SEQ_CST);
  return Error::OK;
}

static void unpatch_libraries() {
   __atomic_store_n(_pthread_setspecific_entry, (func_pthread_setspecific)pthread_setspecific,
                    __ATOMIC_RELAXED);
  int count = __atomic_load_n(&entry_count, __ATOMIC_RELAXED);
  __atomic_store_n(&entry_count, 0, __ATOMIC_SEQ_CST);

  for (int index = 0; index < count; index++) {
     if (patched_entries[index]._location != nullptr) {
       __atomic_store_n(patched_entries[index]._location, patched_entries[index]._original_func, __ATOMIC_RELAXED);
     }
  }
  PatchedEntry* tmp = patched_entries;
  patched_entries = nullptr;
  __atomic_thread_fence(__ATOMIC_SEQ_CST);
  free((void*)tmp);
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

  Error res = patch_libraries();
  if (res != Error::OK) {
    return res;
  }

  OS::installSignalHandler(_signal, signalHandler);

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
