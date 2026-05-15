/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "libraryPatcher.h"

#ifdef __linux__
#include "counters.h"
#include "profiler.h"
#include "guards.h"

#include <cassert>
#include <dlfcn.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

typedef void* (*func_start_routine)(void*);

SpinLock LibraryPatcher::_lock;
const char* LibraryPatcher::_profiler_name = nullptr;
PatchEntry LibraryPatcher::_patched_entries[MAX_NATIVE_LIBS];
int        LibraryPatcher::_size = 0;
PatchEntry LibraryPatcher::_sigaction_entries[MAX_NATIVE_LIBS];
int        LibraryPatcher::_sigaction_size = 0;

void LibraryPatcher::initialize() {
  if (_profiler_name == nullptr) {
    Dl_info info;
    void* caller_address = __builtin_return_address(0); // Get return address of caller
    bool ret = dladdr(caller_address, &info);
    assert(ret);
    _profiler_name = realpath(info.dli_fname, nullptr);
    _size = 0;
  }
}

class RoutineInfo {
private:
  func_start_routine _routine;
  void* _args;
public:
  RoutineInfo(func_start_routine routine, void* args) :
    _routine(routine), _args(args) {
  }

  func_start_routine routine() const {
    return _routine;
  }

  void* args() const {
    return _args;
  }
};

// Unregister the current thread from the profiler and release its TLS under a
// single SignalBlocker to close the race window between unregisterThread()
// returning and release() acquiring its internal guard (PROF-14603).  Without
// this, a SIGVTALRM delivered in that window could call currentSignalSafe()
// and dereference a now-freed ProfiledThread.  Kept noinline so the
// SignalBlocker's sigset_t does not appear in the caller's stack frame on
// musl/aarch64 where the deopt blob may corrupt the wrapper's stack guard.
__attribute__((noinline))
static void unregister_and_release(int tid) {
    SignalBlocker blocker;
    Profiler::unregisterThread(tid);
    ProfiledThread::release();
}

#ifdef __aarch64__
// Delete RoutineInfo with profiling signals blocked to prevent ASAN
// allocator lock reentrancy. Kept noinline so SignalBlocker's sigset_t
// does not trigger stack-protector canary in the caller on aarch64.
__attribute__((noinline))
static void delete_routine_info(RoutineInfo* thr) {
    SignalBlocker blocker;
    delete thr;
}

// Initialize the current thread's TLS, open the init window (PROF-13072), and
// register the thread with the profiler — all under a single SignalBlocker so
// profiling signals cannot fire in the gap between initCurrentThread() and
// startInitWindow().  Kept noinline for the same stack-protector reason as
// delete_routine_info: SignalBlocker's sigset_t must not appear in
// start_routine_wrapper_spec's own stack frame on musl/aarch64.
__attribute__((noinline))
static void init_tls_and_register() {
    SignalBlocker blocker;
    ProfiledThread::initCurrentThread();
    if (ProfiledThread *pt = ProfiledThread::currentSignalSafe()) {
        pt->startInitWindow();
    }
    Profiler::registerThread(ProfiledThread::currentTid());
}

// pthread_cleanup_push callback for start_routine_wrapper_spec.
// Fires when the wrapped routine calls pthread_exit() or the thread is
// canceled.  Kept noinline so its stack frame (which may hold a SignalBlocker
// via unregister_and_release) lives outside the DEOPT-corruption zone of
// start_routine_wrapper_spec.
__attribute__((noinline))
static void cleanup_unregister(void*) {
    unregister_and_release(ProfiledThread::currentTid());
}

// Wrapper around the real start routine.
// The wrapper:
// 1. Register the newly created thread to profiler
// 2. Call real start routine
// 3. Unregister the thread from profiler once the routine is completed.
// This version works around stack corruption observed on musl/aarch64/JDK11:
//
// Empirical observation (hs_err analysis): after DEOPT PACKING fires on a
// thread running compiled lambda$measureContention$0 at sp=0x...49d0, this
// wrapper's frame (sp=0x...5020, ~144 bytes below thread stack top) shows a
// corrupted FP (odd address 0x...5001) and a corrupted stack canary.  The
// corruption is confined to the top ~224 bytes of the stack (the region between
// DEOPT PACKING sp and the thread stack top).
//
// The source of the corruption is the interpreter-frame rebuild sequence in
// HotSpot's deoptimization blob (generate_deopt_blob in
// sharedRuntime_aarch64.cpp, openjdk/jdk11u).  After popping the compiled
// frame the blob executes "sub sp, sp, caller_adjustment" followed by a loop
// of enter() calls (each doing "stp rfp, lr, [sp, #-16]!") to lay down
// replacement interpreter frames.  When musl's small thread stack places this
// wrapper immediately above the compiled frame, the enter() writes can reach
// into this wrapper's frame, corrupting the saved FP and stack canary.
// The mechanism is the same "precarious stack guard corruption" the noinline
// helpers above already defend against for SignalBlocker's sigset_t.
//
// Two symptoms arise from this corruption:
//
// (a) Stack-canary crash: -fstack-protector-strong inserts a canary whenever
//     the frame has a non-trivially destructed local (e.g. a Cleanup struct).
//     That canary lands in the corruption zone; the epilogue fires
//     __stack_chk_fail.  no_stack_protector removes the canary.
//
// (b) Corrupted-LR crash: even without a canary, `return` loads the saved LR
//     from the corrupted frame and jumps to a garbage address.  pthread_exit()
//     terminates the thread without using LR.  HotSpot on musl returns normally
//     from java_start (no forced-unwind), so no exception-based cleanup path
//     is needed.
//
// Cleanup reads tid from TLS (via ProfiledThread::currentTid()) rather than
// from a stack variable, so it is correct even after the frame is corrupted.
// pthread_cleanup_push/pop ensures unregister_and_release() also runs when the
// wrapped routine calls pthread_exit() or the thread is canceled.
__attribute__((visibility("hidden"), no_stack_protector))
static void* start_routine_wrapper_spec(void* args) {
    RoutineInfo* thr = (RoutineInfo*)args;
    func_start_routine routine = thr->routine();
    void* params = thr->args();
    delete_routine_info(thr);
    init_tls_and_register();
    // cleanup_unregister fires on pthread_exit() or cancellation from within
    // routine(params).  pthread_cleanup_pop(1) executes and removes the handler
    // on the normal return path, so unregister_and_release() is not called twice.
    pthread_cleanup_push(cleanup_unregister, nullptr);
    routine(params);
    pthread_cleanup_pop(1);
    // pthread_exit instead of 'return': the saved LR in this frame is corrupted
    // by DEOPT PACKING; returning would jump to a garbage address.
    pthread_exit(nullptr);
    __builtin_unreachable();
}

static int pthread_create_hook_spec(pthread_t* thread,
                          const pthread_attr_t* attr,
                          func_start_routine start_routine,
                          void* args) {
  RoutineInfo* thr;
  {
    SignalBlocker blocker;
    thr = new RoutineInfo(start_routine, args);
  }
  int ret = pthread_create(thread, attr, start_routine_wrapper_spec, (void*)thr);
  if (ret != 0) {
    SignalBlocker blocker;
    delete thr;
  }
  return ret;
}

#endif // __aarch64__

// Wrapper around the real start routine.
// See comments for start_routine_wrapper_spec() for details
__attribute__((visibility("hidden")))
static void* start_routine_wrapper(void* args) {
    RoutineInfo* thr = (RoutineInfo*)args;
    func_start_routine routine;
    void* params;
    {
        // Block profiling signals while accessing and freeing RoutineInfo
        // and during TLS initialization. Under ASAN, new/delete/
        // pthread_setspecific are intercepted and acquire ASAN's internal
        // allocator lock. A profiling signal during any of these calls
        // runs ASAN-instrumented code that tries to acquire the same
        // lock, causing deadlock.
        // registerThread is also kept inside the blocker so that the CPU
        // timer is armed while SIGPROF/SIGVTALRM are masked.  Any pending
        // signal fires only after signals are re-enabled (when the blocker
        // scope exits), at which point JVMThread::current() is still null
        // and the guard in CTimer::signalHandler discards the sample safely.
        SignalBlocker blocker;
        routine = thr->routine();
        params = thr->args();
        delete thr;
        ProfiledThread::initCurrentThread();
        ProfiledThread::currentSignalSafe()->startInitWindow();
        Profiler::registerThread(ProfiledThread::currentTid());
    }
    // RAII cleanup: reads tid from TLS in the destructor (same rationale as
    // start_routine_wrapper_spec: avoids storing state on a potentially corruptible frame).
    // unregister_and_release() wraps the two calls under SignalBlocker (PROF-14603).
    struct Cleanup {
        ~Cleanup() { unregister_and_release(ProfiledThread::currentTid()); }
    } cleanup;
    routine(params);
    return nullptr;
}

static int pthread_create_hook(pthread_t* thread,
                          const pthread_attr_t* attr,
                          func_start_routine start_routine,
                          void* args) {
  RoutineInfo* thr;
  {
    SignalBlocker blocker;
    thr = new RoutineInfo(start_routine, args);
  }
  int ret = pthread_create(thread, attr, start_routine_wrapper, (void*)thr);
  if (ret != 0) {
    SignalBlocker blocker;
    delete thr;
  }
  return ret;
}

void LibraryPatcher::patch_libraries() {
   // LibraryPatcher has yet initialized, only happens in Gtest
   if (_profiler_name == nullptr) {
     return;
   }

   TEST_LOG("Patching libraries");
   patch_pthread_create();
   TEST_LOG("%d libraries patched", _size);
}

void LibraryPatcher::patch_library_unlocked(CodeCache* lib) {
  if (lib->name() == nullptr) return;

  char path[PATH_MAX];
  char* resolved_path = realpath(lib->name(), path);
  if (resolved_path != nullptr &&     //  filter out virtual file, e.g. [vdso], etc.
      strcmp(resolved_path, _profiler_name) == 0) { // Don't patch self
    return;
  }

  // Don't patch sanitizer runtime libraries — intercepting their internal
  // pthread_create calls causes reentrancy and heap corruption under ASAN.
  const char* base = strrchr(lib->name(), '/');
  base = (base != nullptr) ? base + 1 : lib->name();
  if (strncmp(base, "libasan", 7) == 0 ||
      strncmp(base, "libtsan", 7) == 0 ||
      strncmp(base, "libubsan", 8) == 0) {
    return;
  }

  void** pthread_create_location = (void**)lib->findImport(im_pthread_create);
  if (pthread_create_location == nullptr) {
    return;
  }

  for (int index = 0; index < _size; index++) {
    // Already patched
    if (_patched_entries[index]._lib == lib) {
      return;
    }
  }
  TEST_LOG("Patching: %s", lib->name());
  void* func = (void*)pthread_create_hook;

#ifdef __aarch64__
  // Workaround stack guard corruption in Linux/aarch64/musl/jdk11
  if (VM::isHotspot() && OS::isMusl() && VM::java_version() == 11) {
    func = (void*)pthread_create_hook_spec;
  }
#endif
  _patched_entries[_size]._lib = lib;
  _patched_entries[_size]._location = pthread_create_location;
  _patched_entries[_size]._func = (void*)__atomic_load_n(pthread_create_location, __ATOMIC_RELAXED);
  __atomic_store_n(pthread_create_location, func, __ATOMIC_RELAXED);
  _size++;
}

void LibraryPatcher::unpatch_libraries() {
  TEST_LOG("Restore libraries");
  ExclusiveLockGuard locker(&_lock);
  for (int index = 0; index < _size; index++) {
    __atomic_store_n(_patched_entries[index]._location, _patched_entries[index]._func, __ATOMIC_RELAXED);
  }
  _size = 0;
}

void LibraryPatcher::patch_pthread_create() {
  const CodeCacheArray& native_libs = Libraries::instance()->native_libs();
  int num_of_libs = native_libs.count();
  ExclusiveLockGuard locker(&_lock);
  for (int index = 0; index < num_of_libs; index++) {
     CodeCache* lib = native_libs.at(index);
     if (lib != nullptr) {
       patch_library_unlocked(lib);
     }
  }
}

// Patch sigaction in all libraries to prevent any library from overwriting
// our SIGSEGV/SIGBUS handlers. This protects against misbehaving libraries
// (like wasmtime) that install broken signal handlers calling malloc().
void LibraryPatcher::patch_sigaction_in_library(CodeCache* lib) {
  if (lib->name() == nullptr) return;
  if (_profiler_name == nullptr) return;  // Not initialized yet

  // Don't patch ourselves
  char path[PATH_MAX];
  char* resolved_path = realpath(lib->name(), path);
  if (resolved_path != nullptr && strcmp(resolved_path, _profiler_name) == 0) {
    return;
  }

  // Note: We intentionally patch sanitizer libraries (libasan, libtsan, libubsan) here.
  // This keeps our handler on top for recoverable SIGSEGVs (e.g., safefetch) while
  // still chaining to the sanitizer's handler for unexpected crashes.

  void** sigaction_location = (void**)lib->findImport(im_sigaction);
  if (sigaction_location == nullptr) {
    return;
  }

  // Check if already patched or array is full
  if (_sigaction_size >= MAX_NATIVE_LIBS) {
    return;
  }
  for (int index = 0; index < _sigaction_size; index++) {
    if (_sigaction_entries[index]._lib == lib) {
      return;
    }
  }

  void* hook = OS::getSigactionHook();
  _sigaction_entries[_sigaction_size]._lib = lib;
  _sigaction_entries[_sigaction_size]._location = sigaction_location;
  _sigaction_entries[_sigaction_size]._func = (void*)__atomic_load_n(sigaction_location, __ATOMIC_RELAXED);
  __atomic_store_n(sigaction_location, hook, __ATOMIC_RELAXED);
  _sigaction_size++;
  Counters::increment(SIGACTION_PATCHED_LIBS);
}

void LibraryPatcher::patch_sigaction() {
  const CodeCacheArray& native_libs = Libraries::instance()->native_libs();
  int num_of_libs = native_libs.count();
  ExclusiveLockGuard locker(&_lock);
  for (int index = 0; index < num_of_libs; index++) {
    CodeCache* lib = native_libs.at(index);
    if (lib != nullptr) {
      patch_sigaction_in_library(lib);
    }
  }
}

#endif // __linux__
