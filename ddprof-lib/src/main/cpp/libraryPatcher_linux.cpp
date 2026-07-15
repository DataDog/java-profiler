/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "libraryPatcher.h"

#ifdef __linux__
#include "counters.h"
#include "guards.h"
#include "jvmThread.h"
#include "nativeSocketInterposer.h"
#include "nativeSocketSampler.h"
#include "profiler.h"
#include "symbols.h"

#include <algorithm>
#include <cassert>
#include <dlfcn.h>
#include <new>
#include <mutex>
#include <limits.h>
#include <setjmp.h>
#include <string.h>
#include <stdlib.h>
#include <utility>

typedef void* (*func_start_routine)(void*);

SpinLock LibraryPatcher::_lock;
const char* LibraryPatcher::_profiler_name = nullptr;
PatchEntry LibraryPatcher::_patched_entries[MAX_NATIVE_LIBS];
int        LibraryPatcher::_size = 0;
PatchEntry LibraryPatcher::_sigaction_entries[MAX_NATIVE_LIBS];
int        LibraryPatcher::_sigaction_size = 0;
std::vector<SocketPatchEntry> LibraryPatcher::_socket_entries;
std::vector<SocketPatchedLibrary> LibraryPatcher::_socket_libraries;
const void* LibraryPatcher::_socket_bases[SOCKET_BASE_TABLE_SIZE] = {};
std::atomic<bool> LibraryPatcher::_socket_active{false};

static_assert(SOCKET_BASE_TABLE_SIZE > 0 &&
                  (SOCKET_BASE_TABLE_SIZE & (SOCKET_BASE_TABLE_SIZE - 1)) == 0,
              "socket DSO lookup table size must be a power of two");

bool LibraryPatcher::socket_library_patched_unlocked(const void* image_base) {
  size_t slot = (reinterpret_cast<uintptr_t>(image_base) >> 12) &
                (SOCKET_BASE_TABLE_SIZE - 1);
  for (int probe = 0; probe < SOCKET_BASE_TABLE_SIZE; probe++) {
    const void* value = _socket_bases[slot];
    if (value == nullptr) {
      return false;
    }
    if (value == image_base) {
      return true;
    }
    slot = (slot + 1) & (SOCKET_BASE_TABLE_SIZE - 1);
  }
  return false;
}

void LibraryPatcher::remember_socket_library_unlocked(const void* image_base) {
  size_t slot = (reinterpret_cast<uintptr_t>(image_base) >> 12) &
                (SOCKET_BASE_TABLE_SIZE - 1);
  while (_socket_bases[slot] != nullptr && _socket_bases[slot] != image_base) {
    slot = (slot + 1) & (SOCKET_BASE_TABLE_SIZE - 1);
  }
  _socket_bases[slot] = image_base;
}

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
// this, a SIGVTALRM delivered in that window could call current()
// and dereference a now-freed ProfiledThread.  Kept noinline so the
// SignalBlocker's sigset_t does not appear in the caller's stack frame on
// musl/aarch64 where the deopt blob may corrupt the wrapper's stack guard.
__attribute__((noinline))
static void unregister_and_release() {
    SignalBlocker blocker;
    int tid = ProfiledThread::currentTid();
    Profiler::unregisterThread(tid);
    ProfiledThread::release();
}

// pthread_cleanup_push callback for thread wrappers.
// Fires when the wrapped routine calls pthread_exit() or the thread is
// canceled.  Kept noinline so its stack frame (which may hold a SignalBlocker
// via unregister_and_release) lives outside the DEOPT-corruption zone of the
// caller on musl/aarch64, and so that the SignalBlocker's sigset_t does not
// appear in the caller's frame on platforms with stack-protector canaries.
__attribute__((noinline))
static void cleanup_unregister(void*) {
    unregister_and_release();
}

// Thread-cleanup wrapper that avoids the static-libgcc / forced-unwind crash.
//
// The crash: on glibc, pthread_cleanup_push in C++ mode expands to
// __pthread_cleanup_class (RAII), which adds a cleanup entry to the LSDA of
// this frame.  When libjavaProfiler.so is built with -static-libgcc, the
// embedded __gxx_personality_v0 is called by the dynamic libgcc_s.so.1's
// _Unwind_ForcedUnwind.  The two libgcc versions have incompatible
// _Unwind_Context layouts; calling _Unwind_SetGR (which happens when the
// personality finds a cleanup action) with a cross-version context triggers
// the cold/error path, which calls abort().
//
// The fix: use __pthread_register_cancel / __pthread_unregister_cancel
// directly — the same thing the C macro form of pthread_cleanup_push does.
// This registers cleanup via a setjmp buffer in a runtime linked-list, NOT
// via an LSDA destructor.  _Unwind_ForcedUnwind's stop function
// (__pthread_unwind_stop) handles the cleanup without ever calling
// __gxx_personality_v0 for this frame, so _Unwind_SetGR is never called and
// the cross-version incompatibility is never triggered.
//
// On musl: pthread_cleanup_push already uses the C/setjmp form (no RAII),
// and pthread_exit does not use _Unwind_ForcedUnwind, so there is no issue.
// The __GLIBC__ guard keeps the musl path unchanged.
#ifdef __GLIBC__
// On glibc, <pthread.h> declares __pthread_register_cancel etc. only inside
// the C (non-C++) conditional, so they're invisible in C++ code.  Redeclare
// them with extern "C" so we can call them directly without the header guard.
extern "C" {
    extern void __pthread_register_cancel(__pthread_unwind_buf_t*);
    extern void __pthread_unregister_cancel(__pthread_unwind_buf_t*);
    [[noreturn]] extern void __pthread_unwind_next(__pthread_unwind_buf_t*);
}
#endif

__attribute__((visibility("hidden"), noinline, no_stack_protector))
void run_with_cleanup(func_start_routine routine, void* params,
                      void (*cleanup_fn)(void*), void* cleanup_arg) {
#ifdef __GLIBC__
    __pthread_unwind_buf_t cancel_buf = {};
    // With savemask=0, __sigsetjmp only writes __jmp_buf + int __mask_was_saved;
    // it never touches __saved_mask.  The inner struct of __pthread_unwind_buf_t
    // must cover exactly that writable prefix of struct __jmp_buf_tag.
    static_assert(offsetof(__pthread_unwind_buf_t, __cancel_jmp_buf) == 0 &&
                  sizeof(cancel_buf.__cancel_jmp_buf[0]) == offsetof(struct __jmp_buf_tag, __saved_mask),
                  "glibc __pthread_unwind_buf_t inner layout incompatible with struct __jmp_buf_tag");
    // __sigsetjmp/longjmp only intercepts _Unwind_ForcedUnwind (pthread_exit /
    // cancellation).  routine(params) must NOT throw a regular C++ exception
    // across this boundary: an escaping exception would skip both
    // __pthread_unregister_cancel and cleanup_fn below, leaking the thread
    // registration and leaving cancel_buf linked against this (unwound) frame.
    // We cannot defend with a try/catch here — a handler frame adds an LSDA
    // action, which is exactly what triggers the static-libgcc abort this
    // function exists to avoid.  Production routines are JVM/native start
    // routines that handle their own exceptions and do not throw across here.
    if (__builtin_expect(
            // set __sigsetjmp's savemask=0 (the second parameter, noting that the signal mask is NOT
            // saved/restored, which is correct because the cancel mechanism does not depend on signal mask state.
            __sigsetjmp((struct __jmp_buf_tag*)(void*)cancel_buf.__cancel_jmp_buf, 0), 0)) {
        // Reached via longjmp from glibc's stop function when pthread_exit
        // (or cancellation) fires.  Run cleanup and continue unwinding.
        cleanup_fn(cleanup_arg);
        __pthread_unwind_next(&cancel_buf);
        // __pthread_unwind_next is [[noreturn]]; this fails loudly rather than
        // falling through into __pthread_register_cancel on a torn-down frame
        // should a future/variant glibc ever return from it.
        __builtin_unreachable();
    }
    // Callers must not have a pending pthread_cancel when they enter
    // run_with_cleanup: a cancellation arriving between __sigsetjmp returning
    // and __pthread_register_cancel below would unwind this frame before
    // cancel_buf is registered, silently skipping cleanup_fn.  All current
    // callers are JVM/native start routines with no pending cancellation.
    __pthread_register_cancel(&cancel_buf);
    routine(params);
    __pthread_unregister_cancel(&cancel_buf);
    cleanup_fn(cleanup_arg);
#else
    // musl / non-glibc: pthread_cleanup_push uses the C/setjmp form, no RAII.
    pthread_cleanup_push(cleanup_fn, cleanup_arg);
    routine(params);
    pthread_cleanup_pop(1);
#endif
}

#ifdef UNIT_TEST
// Integration test entry point: exercises the full start_routine_wrapper →
// run_with_cleanup chain without calling Profiler::registerThread or
// Profiler::unregisterThread, which dereference _cpu_engine/_wall_engine and
// crash when the profiler is not started (as in gtest).
//
// The caller supplies cleanup_fn/cleanup_arg so the test can verify cleanup
// fires and observe ProfiledThread::release() without coupling to Profiler state.
//
// Thread lifecycle:
//   pthread_create_wrapped_for_test → start_routine_for_test
//     → ProfiledThread::initCurrentThread()
//     → run_with_cleanup(routine, params, cleanup_fn, cleanup_arg)
//     → pthread_exit(nullptr)
struct WrapperTestCtx {
    func_start_routine routine;
    void* params;
    void (*cleanup_fn)(void*);
    void* cleanup_arg;
};

__attribute__((visibility("hidden"), noinline, no_stack_protector))
static void* start_routine_for_test(void* raw) {
    auto* ctx = static_cast<WrapperTestCtx*>(raw);
    func_start_routine routine = ctx->routine;
    void* params = ctx->params;
    void (*cleanup_fn)(void*) = ctx->cleanup_fn;
    void* cleanup_arg = ctx->cleanup_arg;
    {
        SignalBlocker blocker;
        delete ctx;
        ProfiledThread::initCurrentThread();
    }
    run_with_cleanup(routine, params, cleanup_fn, cleanup_arg);
    pthread_exit(nullptr);
    __builtin_unreachable();
}

int pthread_create_wrapped_for_test(pthread_t* thread,
                                    func_start_routine routine, void* params,
                                    void (*cleanup_fn)(void*), void* cleanup_arg) {
    WrapperTestCtx* ctx;
    {
        SignalBlocker blocker;
        ctx = new WrapperTestCtx{routine, params, cleanup_fn, cleanup_arg};
    }
    int ret = pthread_create(thread, nullptr, start_routine_for_test, ctx);
    if (ret != 0) {
        SignalBlocker blocker;
        delete ctx;
    }
    return ret;
}

// Variant that passes the production cleanup_unregister as the cleanup function.
// Exercises the full chain: start_routine_for_test → run_with_cleanup →
// cleanup_unregister → Profiler::unregisterThread + ProfiledThread::release.
// Profiler::unregisterThread is null-safe under UNIT_TEST (see profiler.cpp).
int pthread_create_with_cleanup_unregister_for_test(pthread_t* thread,
                                                    func_start_routine routine,
                                                    void* params) {
    return pthread_create_wrapped_for_test(thread, routine, params,
                                           cleanup_unregister, nullptr);
}
#endif  // UNIT_TEST

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
    ProfiledThread* pt = ProfiledThread::initCurrentThread();
    if (pt != nullptr) {
        pt->startInitWindow();
    }
    Profiler::registerThread(ProfiledThread::currentTid());
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
    // routine(params).  The push/pop pair lives inside run_with_cleanup so
    // that __pthread_unwind_buf_t (glibc) / struct __ptcb (musl) does not land
    // in this frame's DEOPT-corruption zone.
    run_with_cleanup(routine, params, cleanup_unregister, nullptr);
    // pthread_exit instead of 'return': the saved LR in this frame is corrupted
    // by DEOPT PACKING; returning would jump to a garbage address.
    // cleanup_unregister has already run via run_with_cleanup's normal return
    // path, so there is no registered cancel handler left.  The forced unwind
    // raised by pthread_exit walks this frame, but it is safe because no
    // destructor-bearing local (and hence no LSDA cleanup/handler action) is
    // live at this call site: __gxx_personality_v0 returns continue-unwind
    // without ever calling _Unwind_SetGR, avoiding the static-libgcc abort.
    // WARNING: adding any RAII local with a destructor between run_with_cleanup
    // and pthread_exit would reintroduce that crash.
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
__attribute__((visibility("hidden"), no_stack_protector))
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
        ProfiledThread* pt = ProfiledThread::initCurrentThread();
        if (pt != nullptr) {
          pt->startInitWindow();
        }
        Profiler::registerThread(ProfiledThread::currentTid());
    }
    // Use POSIX cleanup instead of C++ RAII to handle pthread_exit(): see run_with_cleanup.
    // cleanup_unregister has already run on run_with_cleanup's normal return path.
    // The pthread_exit forced unwind is safe here for the same reason as in
    // start_routine_wrapper_spec: no destructor-bearing local is live at this
    // call site, so __gxx_personality_v0 never calls _Unwind_SetGR.
    run_with_cleanup(routine, params, cleanup_unregister, nullptr);
    pthread_exit(nullptr);
    __builtin_unreachable();
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

class SocketPatchCandidate {
public:
  CodeCache* _lib;
  UnloadProtection _protection;
  size_t _patch_count;

  SocketPatchCandidate(CodeCache* lib, UnloadProtection&& protection,
                       size_t patch_count)
      : _lib(lib), _protection(std::move(protection)),
        _patch_count(patch_count) {}

  SocketPatchCandidate(const SocketPatchCandidate&) = delete;
  SocketPatchCandidate& operator=(const SocketPatchCandidate&) = delete;
  SocketPatchCandidate(SocketPatchCandidate&&) noexcept = default;
  SocketPatchCandidate& operator=(SocketPatchCandidate&&) noexcept = default;
};

static bool mappingMatches(const CodeCache* lib) {
  if (lib->imageBase() == nullptr) {
    return false;
  }
  Dl_info info;
  return dladdr(lib->imageBase(), &info) != 0 &&
         info.dli_fbase == lib->imageBase();
}

bool LibraryPatcher::patch_socket_functions(bool require_active) {
  auto disable_and_unpatch = []() {
    NativeSocketInterposer::instance()->disableAfterPatchFailure();
    NativeSocketSampler::disableAfterPatchFailure();
    LibraryPatcher::unpatch_socket_functions();
    return false;
  };

  // Resolve the real libc symbols ONCE at first call and cache them.  On a
  // restart cycle (stop()→start()) we MUST NOT re-resolve via RTLD_NEXT: if
  // any GOT slot in another DSO was missed during unpatch (e.g. its CodeCache
  // disappeared), dlsym(RTLD_NEXT) could now resolve to the still-installed
  // hook in that other DSO's GOT — the assignment to _orig_* would become
  // self-referential and the next hook call would infinite-loop.
  //
  // RTLD_NEXT finds the first definition after this DSO in load order,
  // bypassing unresolved lazy-binding stubs that would otherwise trigger
  // _dl_runtime_resolve and silently overwrite the hook in the GOT.
  // May resolve to an LD_PRELOAD interposer (e.g. libasan) — intentional.
  // On musl, RTLD_NEXT returns NULL when libc is loaded before this DSO in the
  // link map; fall back to RTLD_DEFAULT which finds symbols globally.
  // The cached originals and the `has_cached_original` flag are written once
  // and then read-only.  They live outside the ExclusiveLockGuard intentionally
  // (dlsym must not be called while holding _lock because dlsym may acquire the
  // linker lock, which is also acquired during dlopen — inverting the order
  // would deadlock).  Guard the one-time init with a dedicated once_flag so
  // that concurrent callers serialise on the dlsym block rather than racing
  // to write the statics.
  static void* cached_originals[NativeSocketInterposer::NUM_NATIVE_IO_HOOKS] = {};
  static bool has_cached_original = false;
  static std::once_flag dlsym_once;

  const NativeSocketInterposer::NativeIoHookSpec* hooks =
      NativeSocketInterposer::hookSpecs();

  std::call_once(dlsym_once, [&]() {
    for (int hook_index = 0; hook_index < NativeSocketInterposer::NUM_NATIVE_IO_HOOKS;
         hook_index++) {
      void* original = dlsym(RTLD_NEXT, hooks[hook_index].name);
      if (original == nullptr) {
        original = dlsym(RTLD_DEFAULT, hooks[hook_index].name);
      }
      if (original == hooks[hook_index].hook) {
        TEST_LOG("patch_socket_functions dlsym returned hook address for %s",
                 hooks[hook_index].name);
        // If dlsym resolves to one of our own hooks the linker is already serving
        // the patched copy.  Null this pointer so the hook is not installed.
        original = nullptr;
      }
      cached_originals[hook_index] = original;
      has_cached_original |= original != nullptr;
      if (original != nullptr) {
        NativeSocketInterposer::setOriginalFunction(hook_index, original);
      }
    }
    NativeSocketSampler::setOriginalFunctions(
        reinterpret_cast<NativeSocketSampler::send_fn>(
            cached_originals[NativeSocketInterposer::HOOK_SEND]),
        reinterpret_cast<NativeSocketSampler::recv_fn>(
            cached_originals[NativeSocketInterposer::HOOK_RECV]),
        reinterpret_cast<NativeSocketSampler::write_fn>(
            cached_originals[NativeSocketInterposer::HOOK_WRITE]),
        reinterpret_cast<NativeSocketSampler::read_fn>(
            cached_originals[NativeSocketInterposer::HOOK_READ]));
  });

  if (!has_cached_original) {
    Log::warn("native I/O hooks disabled: all original symbol lookups failed");
    return disable_and_unpatch();
  }

  const CodeCacheArray& native_libs = Libraries::instance()->native_libs();
  int num_of_libs = native_libs.count();

  int capped = num_of_libs <= MAX_NATIVE_LIBS ? num_of_libs : MAX_NATIVE_LIBS;
  std::vector<SocketPatchCandidate> candidates;
  try {
    candidates.reserve(capped);
  } catch (const std::bad_alloc&) {
    Log::warn("native I/O hooks disabled: unable to allocate DSO candidate table");
    return disable_and_unpatch();
  }

  for (int index = 0; index < capped; index++) {
    CodeCache* lib = native_libs.at(index);
    if (lib == nullptr || lib->name() == nullptr) {
      continue;
    }
    char path[PATH_MAX];
    char* resolved_path = realpath(lib->name(), path);
    if (_profiler_name != nullptr && resolved_path != nullptr &&
        strcmp(resolved_path, _profiler_name) == 0) {
      continue;
    }

    size_t patch_count = 0;
    for (int hook_index = 0; hook_index < NativeSocketInterposer::NUM_NATIVE_IO_HOOKS;
         hook_index++) {
      ImportId import_id = hooks[hook_index].import_id;
      size_t count = lib->importCount(import_id);
      if (count == 0) {
        continue;
      }
      if (!lib->importsComplete(import_id)) {
        Log::warn("native I/O hooks disabled: incomplete %s imports in %s",
                  hooks[hook_index].name, lib->name());
        return disable_and_unpatch();
      }
      if (cached_originals[hook_index] == nullptr) {
        Log::warn("native I/O hooks disabled: no original for imported %s in %s",
                  hooks[hook_index].name, lib->name());
        return disable_and_unpatch();
      }
      patch_count += count;
    }
    if (patch_count == 0 || !mappingMatches(lib)) {
      continue;
    }

    UnloadProtection protection(lib);
    if (!protection.isValid()) {
      if (!mappingMatches(lib)) {
        continue;
      }
      Log::warn("native I/O hooks disabled: cannot retain mapped DSO %s",
                lib->name());
      return disable_and_unpatch();
    }
    try {
      candidates.emplace_back(lib, std::move(protection),
                              patch_count);
    } catch (const std::bad_alloc&) {
      Log::warn("native I/O hooks disabled: unable to retain DSO candidate %s",
                lib->name());
      return disable_and_unpatch();
    }
  }

  std::vector<SocketPatchedLibrary> libraries_to_release;
  bool success = true;
  {
    ExclusiveLockGuard locker(&_lock);
    if (require_active &&
        !_socket_active.load(std::memory_order_relaxed)) {
      return false;
    }

    size_t additional_patches = 0;
    size_t additional_libraries = 0;
    for (SocketPatchCandidate& candidate : candidates) {
      if (!socket_library_patched_unlocked(candidate._lib->imageBase())) {
        additional_patches += candidate._patch_count;
        additional_libraries++;
      }
    }

    try {
      _socket_entries.reserve(_socket_entries.size() + additional_patches);
      _socket_libraries.reserve(_socket_libraries.size() + additional_libraries);
    } catch (const std::bad_alloc&) {
      Log::warn("native I/O hooks disabled: unable to reserve patch transaction");
      success = false;
    }

    if (success) {
      for (SocketPatchCandidate& candidate : candidates) {
        if (!socket_library_patched_unlocked(candidate._lib->imageBase()) &&
            !candidate._lib->prepareImportsForPatch()) {
          Log::warn("native I/O hooks disabled: cannot make imports writable in %s",
                    candidate._lib->name());
          success = false;
          break;
        }
      }
    }

    if (success) {
      for (SocketPatchCandidate& candidate : candidates) {
        CodeCache* lib = candidate._lib;
        if (socket_library_patched_unlocked(lib->imageBase())) {
          continue;
        }
        size_t first_patch = _socket_entries.size();
        for (int hook_index = 0;
             hook_index < NativeSocketInterposer::NUM_NATIVE_IO_HOOKS;
             hook_index++) {
          ImportId import_id = hooks[hook_index].import_id;
          size_t count = lib->importCount(import_id);
          for (size_t import_index = 0; import_index < count; import_index++) {
            void** location = lib->findImport(import_id, import_index);
            void* original =
                reinterpret_cast<void*>(__atomic_load_n(location, __ATOMIC_ACQUIRE));
            _socket_entries.push_back({location, original});
            __atomic_store_n(location, hooks[hook_index].hook, __ATOMIC_RELEASE);
          }
        }
        _socket_libraries.push_back(
            {lib->imageBase(), candidate._protection.release(), first_patch,
             _socket_entries.size() - first_patch});
        remember_socket_library_unlocked(lib->imageBase());
      }
      _socket_active.store(true, std::memory_order_release);
    } else {
      unpatch_socket_functions_unlocked(libraries_to_release);
    }
  }

  release_socket_libraries(libraries_to_release);
  if (!success) {
    NativeSocketInterposer::instance()->disableAfterPatchFailure();
    NativeSocketSampler::disableAfterPatchFailure();
    return false;
  }

  TEST_LOG("patch_socket_functions DONE total_slots=%zu num_libs_scanned=%d",
           _socket_entries.size(), capped);
  return true;
}

#ifdef UNIT_TEST
int LibraryPatcher::patch_socket_import_for_test(CodeCache* lib, ImportId import_id,
                                                 void* hook, const char* name,
                                                 bool retain_library) {
  (void)name;
  UnloadProtection protection(lib);
  if (retain_library &&
      (!mappingMatches(lib) || !protection.isValid())) {
    return -1;
  }
  ExclusiveLockGuard locker(&_lock);
  if (!lib->importsComplete(import_id) || !lib->prepareImportsForPatch()) {
    return -1;
  }
  size_t count = lib->importCount(import_id);
  size_t initial_size = _socket_entries.size();
  try {
    _socket_entries.reserve(initial_size + count);
    if (retain_library) {
      _socket_libraries.reserve(_socket_libraries.size() + 1);
    }
  } catch (const std::bad_alloc&) {
    return -1;
  }
  for (size_t index = 0; index < count; index++) {
    void** location = lib->findImport(import_id, index);
    bool already_patched = std::any_of(
        _socket_entries.begin(), _socket_entries.end(),
        [location](const SocketPatchEntry& entry) {
          return entry._location == location;
        });
    if (already_patched) {
      continue;
    }
    void* original =
        reinterpret_cast<void*>(__atomic_load_n(location, __ATOMIC_ACQUIRE));
    _socket_entries.push_back({location, original});
    __atomic_store_n(location, hook, __ATOMIC_RELEASE);
  }
  size_t patched = _socket_entries.size() - initial_size;
  if (retain_library && patched != 0) {
    _socket_libraries.push_back(
        {lib->imageBase(), protection.release(), initial_size, patched});
    remember_socket_library_unlocked(lib->imageBase());
  }
  return static_cast<int>(patched);
}

int LibraryPatcher::socket_patch_count_for_test() {
  ExclusiveLockGuard locker(&_lock);
  return static_cast<int>(_socket_entries.size());
}

int LibraryPatcher::socket_library_count_for_test() {
  ExclusiveLockGuard locker(&_lock);
  return static_cast<int>(_socket_libraries.size());
}
#endif

void LibraryPatcher::unpatch_socket_functions_unlocked(
    std::vector<SocketPatchedLibrary>& libraries_to_release) {
  // Clear _socket_active FIRST so that any concurrent install_socket_hooks()
  // thread that already passed the acquire-load on _socket_active (before we
  // acquired the lock) will see false when it checks again after acquiring the
  // lock — preventing it from re-patching slots we are about to restore.
  // Hooks that already entered the hook body before this store are benign: they
  // hold no lock and will complete normally using the still-valid orig pointers.
  _socket_active.store(false, std::memory_order_release);
  TEST_LOG("unpatch_socket_functions restoring %zu slot(s)", _socket_entries.size());
  for (const SocketPatchEntry& entry : _socket_entries) {
    __atomic_store_n(entry._location, entry._func,
                     __ATOMIC_RELEASE);
  }
  _socket_entries.clear();
  memset(_socket_bases, 0, sizeof(_socket_bases));
  _socket_libraries.swap(libraries_to_release);
  // Original function pointers are intentionally NOT nulled.
  // In-flight hook invocations that entered before PLT entries were restored
  // above may still be executing and will dereference these pointers.
  // They remain valid (pointing to the real libc functions) until the next
  // patch_socket_functions() call.
}

void LibraryPatcher::release_socket_libraries(
    std::vector<SocketPatchedLibrary>& libraries) {
  for (const SocketPatchedLibrary& library : libraries) {
    if (library._unload_protection != nullptr) {
      dlclose(library._unload_protection);
    }
  }
  libraries.clear();
}

void LibraryPatcher::unpatch_socket_functions() {
  std::vector<SocketPatchedLibrary> libraries_to_release;
  {
    ExclusiveLockGuard locker(&_lock);
    unpatch_socket_functions_unlocked(libraries_to_release);
  }
  release_socket_libraries(libraries_to_release);
}

bool LibraryPatcher::unpatch_socket_functions_if_inactive() {
  std::vector<SocketPatchedLibrary> libraries_to_release;
  {
    ExclusiveLockGuard locker(&_lock);
    if (NativeSocketInterposer::instance()->active() || NativeSocketSampler::active()) {
      return false;
    }
    if (!_socket_active.load(std::memory_order_relaxed) &&
        _socket_entries.empty()) {
      return false;
    }
    unpatch_socket_functions_unlocked(libraries_to_release);
  }
  release_socket_libraries(libraries_to_release);
  return true;
}

void LibraryPatcher::install_socket_hooks() {
  if (_socket_active.load(std::memory_order_acquire) &&
      !patch_socket_functions(true)) {
    NativeSocketInterposer::instance()->disableAfterPatchFailure();
    NativeSocketSampler::disableAfterPatchFailure();
  }
}

#endif // __linux__
