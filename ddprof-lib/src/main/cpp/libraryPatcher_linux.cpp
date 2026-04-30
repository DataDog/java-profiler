/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "libraryPatcher.h"

#ifdef __linux__
#include "counters.h"
#include "guards.h"
#include "nativeSocketSampler.h"
#include "profiler.h"

#include <cassert>
#include <cxxabi.h>
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
PatchEntry LibraryPatcher::_socket_entries[4 * MAX_NATIVE_LIBS];
int        LibraryPatcher::_socket_size = 0;
std::atomic<bool> LibraryPatcher::_socket_active{false};

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
    delete_routine_info(thr);
    init_tls_and_register();
    // Capture tid from TLS while it is guaranteed non-null (set by init_tls_and_register above).
    // Using a cached tid avoids the lazy-allocating ProfiledThread::current() path inside
    // the catch block, which may call 'new' at an unsafe point during forced unwind.
    int tid = ProfiledThread::currentTid();
    // IBM J9 (and glibc pthread_cancel) use abi::__forced_unwind for thread teardown.
    // Catch it explicitly so cleanup runs even during forced unwind, then re-throw
    // to allow the thread to exit properly.  A plain catch(...) without re-throw
    // would swallow the forced unwind and prevent the thread from actually exiting.
    try {
        routine(params);
    } catch (abi::__forced_unwind&) {
        Profiler::unregisterThread(tid);
        ProfiledThread::release();
        throw;
    }
    Profiler::unregisterThread(tid);
    ProfiledThread::release();
    return nullptr;
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
    int tid;
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
        tid = ProfiledThread::currentTid();
        ProfiledThread::currentSignalSafe()->startInitWindow();
        Profiler::registerThread(tid);
    }
    // IBM J9 (and glibc pthread_cancel) use abi::__forced_unwind for thread
    // teardown.  pthread_cleanup_push/pop creates a __pthread_cleanup_class
    // with an implicitly-noexcept destructor; when J9's forced-unwind
    // propagates through it, the C++ runtime calls std::terminate() → abort().
    // Replacing with an explicit catch ensures cleanup runs on forced unwind
    // without triggering terminate, and the re-throw lets the thread exit cleanly.
    // pthread_exit() is also covered: on glibc it raises its own __forced_unwind.
    try {
        routine(params);
    } catch (abi::__forced_unwind&) {
        Profiler::unregisterThread(tid);
        ProfiledThread::release();
        throw;
    }
    Profiler::unregisterThread(tid);
    ProfiledThread::release();
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

bool LibraryPatcher::patch_socket_functions() {
  // Pre-resolve the real libc symbols via RTLD_NEXT *before* acquiring _lock.
  // RTLD_NEXT finds the first definition after this DSO in load order,
  // bypassing unresolved lazy-binding stubs that would otherwise trigger
  // _dl_runtime_resolve and silently overwrite the hook in the GOT.
  // May resolve to an LD_PRELOAD interposer (e.g. libasan) — intentional.
  // On musl, RTLD_NEXT returns NULL when libc is loaded before this DSO in the
  // link map; fall back to RTLD_DEFAULT which finds symbols globally.
  auto pre_send   = (NativeSocketSampler::send_fn)  dlsym(RTLD_NEXT, "send");
  if (!pre_send)  pre_send  = (NativeSocketSampler::send_fn)  dlsym(RTLD_DEFAULT, "send");
  auto pre_recv   = (NativeSocketSampler::recv_fn)  dlsym(RTLD_NEXT, "recv");
  if (!pre_recv)  pre_recv  = (NativeSocketSampler::recv_fn)  dlsym(RTLD_DEFAULT, "recv");
  auto pre_write  = (NativeSocketSampler::write_fn) dlsym(RTLD_NEXT, "write");
  if (!pre_write) pre_write = (NativeSocketSampler::write_fn) dlsym(RTLD_DEFAULT, "write");
  auto pre_read   = (NativeSocketSampler::read_fn)  dlsym(RTLD_NEXT, "read");
  if (!pre_read)  pre_read  = (NativeSocketSampler::read_fn)  dlsym(RTLD_DEFAULT, "read");
  TEST_LOG("patch_socket_functions dlsym send=%p recv=%p write=%p read=%p",
           (void*)pre_send, (void*)pre_recv, (void*)pre_write, (void*)pre_read);
  if (!pre_send || !pre_recv || !pre_write || !pre_read) {
    TEST_LOG("patch_socket_functions EARLY RETURN: at least one dlsym returned NULL");
    return false;
  }

  const CodeCacheArray& native_libs = Libraries::instance()->native_libs();
  int num_of_libs = native_libs.count();

  // Pre-resolve all library paths before acquiring the lock: realpath() may
  // block on I/O and must not be called while holding _lock.
  // We only need the is-self flag per library, so avoid a huge stack allocation.
  static_assert(MAX_NATIVE_LIBS > 0, "MAX_NATIVE_LIBS must be positive");
  bool is_self[MAX_NATIVE_LIBS];
  int capped = (num_of_libs <= MAX_NATIVE_LIBS) ? num_of_libs : MAX_NATIVE_LIBS;
  for (int index = 0; index < capped; index++) {
    CodeCache* lib = native_libs.at(index);
    is_self[index] = false;
    if (lib == nullptr || lib->name() == nullptr) continue;
    char path[PATH_MAX];
    char* rp = realpath(lib->name(), path);
    is_self[index] = (rp != nullptr && strcmp(rp, _profiler_name) == 0);
  }

  ExclusiveLockGuard locker(&_lock);
  // Only assign orig pointers on the first call (no hooks installed yet).
  // On re-entry via dlopen, RTLD_NEXT would resolve to the hook itself.
  if (_socket_size == 0) {
    NativeSocketSampler::setOriginalFunctions(pre_send, pre_recv, pre_write, pre_read);
  }
  // TODO: hook table (name + hook fn) should be owned by NativeSocketSampler;
  // LibraryPatcher should iterate an externally-provided table rather than
  // hardcoding the four socket hooks here.
  auto try_patch_slot = [&](void** location, void* hook_fn, const char* fn_name, CodeCache* lib) {
    if (location == nullptr) return;
    for (int i = 0; i < _socket_size; i++) {
      if (_socket_entries[i]._location == location) return;
    }
    if (_socket_size < 4 * MAX_NATIVE_LIBS) {
      void* orig = (void*)__atomic_load_n(location, __ATOMIC_ACQUIRE);
      _socket_entries[_socket_size]._lib      = lib;
      _socket_entries[_socket_size]._location = location;
      _socket_entries[_socket_size]._func     = orig;
      __atomic_store_n(location, hook_fn, __ATOMIC_RELEASE);
      _socket_size++;
    } else {
      Log::warn("socket patch table full (%d slots), skipping %s in %s", 4 * MAX_NATIVE_LIBS, fn_name, lib ? lib->name() : "?");
    }
  };
  for (int index = 0; index < capped; index++) {
    CodeCache* lib = native_libs.at(index);
    if (lib == nullptr) continue;
    if (lib->name() == nullptr) continue;

    if (is_self[index]) {
      continue;
    }

    void** send_location  = (void**)lib->findImport(im_send);
    void** recv_location  = (void**)lib->findImport(im_recv);
    void** write_location = (void**)lib->findImport(im_write);
    void** read_location  = (void**)lib->findImport(im_read);

    if (send_location == nullptr && recv_location == nullptr
        && write_location == nullptr && read_location == nullptr) continue;

    TEST_LOG("patch_socket_functions PATCH %s send=%p recv=%p write=%p read=%p",
             lib->name(), (void*)send_location, (void*)recv_location,
             (void*)write_location, (void*)read_location);

    // The _lock is held during patching to protect _socket_entries and _socket_size.
    // Concurrent dlopen_hook calls serialize via the same lock in install_socket_hooks(),
    // ensuring slot_patched checks and updates are atomic with respect to each other.
    try_patch_slot(send_location,  (void*)NativeSocketSampler::send_hook,  "send",  lib);
    try_patch_slot(recv_location,  (void*)NativeSocketSampler::recv_hook,  "recv",  lib);
    try_patch_slot(write_location, (void*)NativeSocketSampler::write_hook, "write", lib);
    try_patch_slot(read_location,  (void*)NativeSocketSampler::read_hook,  "read",  lib);
  }

  TEST_LOG("patch_socket_functions DONE total_slots=%d num_libs_scanned=%d",
           _socket_size, capped);
  _socket_active.store(true, std::memory_order_release);
  return true;
}

void LibraryPatcher::unpatch_socket_functions() {
  ExclusiveLockGuard locker(&_lock);
  _socket_active.store(false, std::memory_order_release);
  TEST_LOG("unpatch_socket_functions restoring %d slot(s)", _socket_size);
  for (int index = 0; index < _socket_size; index++) {
    __atomic_store_n(_socket_entries[index]._location, _socket_entries[index]._func, __ATOMIC_RELEASE);
  }
  _socket_size = 0;
  // _orig_send/_orig_recv/_orig_write/_orig_read are intentionally NOT nulled.
  // In-flight hook invocations that entered before PLT entries were restored
  // above may still be executing and will dereference these pointers.
  // They remain valid (pointing to the real libc functions) until the next
  // patch_socket_functions() call.
}

#endif // __linux__
