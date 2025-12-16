#include "libraryPatcher.h"

#ifdef __linux__
#include "profiler.h"
#include "vmStructs.h"

#include <cassert>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>

typedef void* (*func_start_routine)(void*);

SpinLock LibraryPatcher::_lock;
const char* LibraryPatcher::_profiler_name = nullptr;
PatchEntry LibraryPatcher::_patched_entries[MAX_NATIVE_LIBS];
int        LibraryPatcher::_size = 0;
bool       LibraryPatcher::_patch_pthread_create = false;

void LibraryPatcher::initialize() {
  assert(_profiler_name == nullptr);
  Dl_info info;
  void* caller_address = __builtin_return_address(0); // Get return address of caller
  bool ret = dladdr(caller_address, &info);
  assert(ret);
  _profiler_name = strdup(info.dli_fname);
  _size = 0;

  _patch_pthread_create = (VM::isHotspot() || VM::isZing()) && !OS::isMusl();
}

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



void LibraryPatcher::patch_libraries() {
   // LibraryPatcher has yet initialized, only happens in Gtest
   if (_profiler_name == nullptr) {
     return;
   }

   TEST_LOG("Patching libraries");
   if (_patch_pthread_create) {
     patch_pthread_create();
   } else {
     patch_pthread_setspecific();
   }
   TEST_LOG("%d libraries patched", _size);
}

void LibraryPatcher::patch_library_unlocked(CodeCache* lib) {
  if (_patch_pthread_create) {
    // Don't patch self
    if(strcmp(lib->name(), _profiler_name) == 0) {
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
    _patched_entries[_size]._lib = lib;
    _patched_entries[_size]._location = pthread_create_location;
    _patched_entries[_size]._func = (void*)__atomic_load_n(pthread_create_location, __ATOMIC_RELAXED);
    __atomic_store_n(pthread_create_location, (void*)pthread_create_hook, __ATOMIC_RELAXED);
    _size++;
  }
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
     patch_library_unlocked(lib);
  }
}

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

void LibraryPatcher::patch_pthread_setspecific() {
   ExclusiveLockGuard locker(&_lock);
   // Already patched
   if (_size != 0) return;
   CodeCache *lib = Libraries::instance()->findJvmLibrary("libj9thr");
   void** func_location = lib->findImport(im_pthread_setspecific);
   if (func_location != nullptr) {
     TEST_LOG("Patching %s", lib->name());
     _patched_entries[0]._lib = lib;
     _patched_entries[0]._location = func_location;
     _patched_entries[0]._func = (void*)__atomic_load_n(func_location, __ATOMIC_RELAXED);
     __atomic_store_n(func_location, (void*)pthread_setspecific_hook, __ATOMIC_RELAXED);
     _size = 1;
  }
}

#else
void LibraryPatcher::initialize() { }
void LibraryPatcher::patch_libraries() { }
void LibraryPatcher::unpatch_libraries() { }

#endif // __linux__




