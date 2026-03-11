#include "libraryPatcher.h"

#ifdef __linux__
#include "profiler.h"
#include "vmStructs.h"
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

#ifdef __aarch64__
// Initialize the current thread's TLS with profiling signals blocked.
// Kept in a separate noinline function so that SignalBlocker's 128-byte
// sigset_t lives in its own frame and does not trigger stack-protector
// canary placement in start_routine_wrapper on aarch64.
__attribute__((noinline))
static void init_thread_tls() {
    // Block profiling signals during TLS initialization: TLS init
    // (pthread_once, pthread_key_create, pthread_setspecific) is not
    // async-signal-safe. A profiling signal here can corrupt
    // internal TLS bookkeeping on the stack.
    SignalBlocker blocker;
    ProfiledThread::initCurrentThread();
}

// Wrapper around the real start routine.
// The wrapper:
// 1. Register the newly created thread to profiler
// 2. Call real start routine
// 3. Unregister the thread from profiler once the routine is completed.
// This version is to workaround a precarious stack guard corruption,
// which only happens in Linux/musl/aarch64/jdk11
__attribute__((visibility("hidden")))
static void* start_routine_wrapper_spec(void* args) {
    RoutineInfo* thr = (RoutineInfo*)args;
    func_start_routine routine = thr->routine();
    void* params = thr->args();
    delete thr;
    init_thread_tls();
    int tid = ProfiledThread::currentTid();
    Profiler::registerThread(tid);
    void* result = routine(params);
    Profiler::unregisterThread(tid);
    ProfiledThread::release();
    return result;
}

static int pthread_create_hook_spec(pthread_t* thread,
                          const pthread_attr_t* attr,
                          func_start_routine start_routine,
                          void* args) {
  RoutineInfo* thr = new RoutineInfo(start_routine, args);
  int ret = pthread_create(thread, attr, start_routine_wrapper_spec, (void*)thr);
  if (ret != 0) delete thr;
  return ret;
}

#endif // __aarch64__

static void thread_cleanup(void* arg) {
    int tid = *static_cast<int*>(arg);
    Profiler::unregisterThread(tid);
    ProfiledThread::release();
}

// Wrapper around the real start routine.
// See comments for start_routine_wrapper_spec() for details
__attribute__((visibility("hidden")))
static void* start_routine_wrapper(void* args) {
    RoutineInfo* thr = (RoutineInfo*)args;
    func_start_routine routine = thr->routine();
    void* params = thr->args();
    delete thr;
    {
        // Block profiling signals during TLS initialization: TLS init
        // (pthread_once, pthread_key_create, pthread_setspecific) is not
        // async-signal-safe. A profiling signal here can corrupt
        // internal TLS bookkeeping on the stack.
        SignalBlocker blocker;
        ProfiledThread::initCurrentThread();
    }
    int tid = ProfiledThread::currentTid();
    Profiler::registerThread(tid);
    void* result = nullptr;
    // Handle pthread_exit() bypass - the thread calls pthread_exit()
    // instead of normal termination
    pthread_cleanup_push(thread_cleanup, &tid);
    result = routine(params);
    pthread_cleanup_pop(1);
    return result;
}

static int pthread_create_hook(pthread_t* thread,
                          const pthread_attr_t* attr,
                          func_start_routine start_routine,
                          void* args) {
  RoutineInfo* thr = new RoutineInfo(start_routine, args);
  int ret = pthread_create(thread, attr, start_routine_wrapper, (void*)thr);
  if (ret != 0) delete thr;
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
#endif // __linux__




