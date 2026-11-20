/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "libraryPatcher.h"

#ifdef __linux__
#include "counters.h"
#include "guards.h"
#include "jvmThread.h"
#include "nativeSocketSampler.h"
#include "nativeSocketInterposer.h"
#include "os.h"
#include "profiler.h"
#include "symbols.h"
#include "threadExitRegistry.h"

#include <algorithm>
#include <assert.h>
#include <dlfcn.h>
#include <link.h>
#include <mutex>
#include <new>
#include <stdlib.h>
#include <unistd.h>
#include <utility>
#include <setjmp.h>
#include <stddef.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>

typedef void* (*func_start_routine)(void*);

SpinLock LibraryPatcher::_lock;
std::atomic<bool> LibraryPatcher::_initialized{false};
PatchEntry LibraryPatcher::_patched_entries[MAX_NATIVE_LIBS];
int        LibraryPatcher::_size = 0;
PatchEntry LibraryPatcher::_sigaction_entries[MAX_NATIVE_LIBS];
int        LibraryPatcher::_sigaction_size = 0;
u64 LibraryPatcher::_socket_generation = 0;
std::vector<SocketPatchEntry> LibraryPatcher::_socket_entries;
std::vector<SocketPatchedLibrary> LibraryPatcher::_socket_libraries;
const void* LibraryPatcher::_socket_bases[SOCKET_BASE_TABLE_SIZE] = {};
SocketSkippedImage LibraryPatcher::_socket_skipped_images[SOCKET_SKIPPED_IMAGE_CAPACITY] = {};
int LibraryPatcher::_socket_skipped_image_count = 0;
std::atomic<bool> LibraryPatcher::_socket_active{false};
LibraryRef LibraryPatcher::_live_refs[MAX_NATIVE_LIBS];
int        LibraryPatcher::_live_count = 0;

static int find_entry(const PatchEntry* entries, int size, CodeCache* lib) {
  for (int index = 0; index < size; index++) {
    if (entries[index]._lib == lib) return index;
  }
  return -1;
}

static bool has_entry_for(const PatchEntry* entries, int size, CodeCache* lib) {
  return find_entry(entries, size, lib) >= 0;
}

// Per pthread_create entry, parallel to _patched_entries: whether the last pass
// that looked found its library mapped. Guarded by _lock.
static bool pthread_create_entry_mapped[MAX_NATIVE_LIBS];
// The entries' libraries, sorted, for patch_pthread_create()'s collector.
// Guarded by _lock.
static CodeCache* pthread_create_entry_libs[MAX_NATIVE_LIBS];

void LibraryPatcher::add_live_candidate(CodeCache* lib, int tag) {
  // Libraries without a known image base never had their imports parsed.
  if (lib->imageBase() == nullptr) return;
  // Every caller adds at most one candidate per CodeCache, and there are at
  // most MAX_NATIVE_LIBS of them.
  assert(_live_count < MAX_NATIVE_LIBS && "more live candidates than libraries");
  if (_live_count >= MAX_NATIVE_LIBS) return;
  _live_refs[_live_count++] = {(uintptr_t)lib->imageBase(), lib, tag};
}

// Liveness is decided inside a dl_iterate_phdr() callback. glibc holds
// dl_load_write_lock for the whole iteration, and dlclose() unmaps and unlinks
// an object only while holding the same lock (_dl_close_worker in
// elf/dl-close.c, unchanged from 2.17 to current), so a library reported to the
// callback stays mapped until the callback returns.
//
// Lock order: dl_load_write_lock, then _lock. A walk takes _lock only in its
// first callback, when glibc already holds dl_load_write_lock, and keeps it
// until the walk is destroyed. The reverse order deadlocks: dl_iterate_phdr()
// runs arbitrary callbacks under dl_load_write_lock, and one that loads a
// library through the JVM (a JNI System.loadLibrary(), say) reaches
// Profiler::dlopen_hook() and a refresh that patches. In this order that
// refresh re-enters the recursive dl_load_write_lock and waits for _lock,
// whose holder waits for nothing.
//
// In turn, nothing may wait for a loader lock while holding _lock: a
// concurrent dlopen() or dlclose() holds dl_load_lock and dl_load_tls_lock
// while it waits for dl_load_write_lock, which a walk waiting for _lock may
// hold. So code under _lock must not call dlopen(), dlsym(), dladdr() or
// dlinfo(), nor touch dynamic TLS for the first time.
//
// musl's dlclose() never unmaps, so every parsed library is still loaded, and
// a walk just takes _lock.
struct LiveWalkState {
  LiveLibraryCollector collect;
  void* ctx;
  LiveLibraryVisitor visit;
  bool locked;  // _lock taken and the candidates collected
};

LibraryPatcher::LiveLibraryWalk::LiveLibraryWalk(LiveLibraryCollector collect, void* ctx,
                                                 LiveLibraryVisitor visit) {
  if (OS::isMusl()) {
    _lock.lock();
    collect(ctx);
    for (int index = 0; index < _live_count; index++) {
      visit(_live_refs[index]._lib, _live_refs[index]._tag);
    }
  } else {
    LiveWalkState state = {collect, ctx, visit, false};
    dl_iterate_phdr(visit_loaded_object, &state);
    if (!state.locked) {
      // No object was reported, so none of the candidates is provably loaded.
      _lock.lock();
      collect(ctx);
    }
  }
  _live_count = 0;
}

// Visits the candidates that are the object being reported: the same image
// base and the same image fingerprint, or the same backing file for a cache
// without a fingerprint. The identity check rejects a stale CodeCache whose
// library was unloaded and replaced by a different one at the same address.
// An image with the same fingerprint at the same base is accepted, a reload
// of the same build in particular: the fingerprint covers the import layout,
// so each saved slot address holds the same import as when it was saved.
int LibraryPatcher::visit_loaded_object(struct dl_phdr_info* info, size_t size, void* data) {
  LiveWalkState* state = (LiveWalkState*)data;
  if (!state->locked) {
    // glibc holds dl_load_write_lock now, so _lock may be taken (see above).
    _lock.lock();
    state->locked = true;
    state->collect(state->ctx);
    std::sort(_live_refs, _live_refs + _live_count,
              [](const LibraryRef& a, const LibraryRef& b) { return a._base < b._base; });
  }
  if (_live_count == 0) return 1;  // nothing to visit, end the walk

  uintptr_t min_vaddr = UINTPTR_MAX;
  for (int i = 0; i < info->dlpi_phnum; i++) {
    if (info->dlpi_phdr[i].p_type == PT_LOAD && info->dlpi_phdr[i].p_vaddr < min_vaddr) {
      min_vaddr = info->dlpi_phdr[i].p_vaddr;
    }
  }
  if (min_vaddr == UINTPTR_MAX) return 0;
  uintptr_t base = (info->dlpi_addr + min_vaddr) & ~OS::page_mask;

  LibraryRef* end = _live_refs + _live_count;
  LibraryRef* ref = std::lower_bound(_live_refs, end, base,
                                     [](const LibraryRef& r, uintptr_t b) { return r._base < b; });
  if (ref == end || ref->_base != base) return 0;

  // glibc names the main executable "". It is never unloaded, so nothing else
  // can occupy its image base.
  bool main_executable = info->dlpi_name == nullptr || info->dlpi_name[0] == '\0';
  // The fingerprint decides whenever the cache has one. The backing file does
  // not identify the image: a file can be replaced by a different build that
  // reuses the freed inode (and is then not parsed, because its inode has been
  // seen), and a relative or symlinked name may now resolve to another file.
  // Both are computed lazily, at most once per object.
  u64 fingerprint = 0;
  u64 file_id = 0;
  bool file_id_known = false;
  LiveLibraryVisitor visit = state->visit;
  for (; ref != end && ref->_base == base; ref++) {
    bool same_image = main_executable;
    if (!same_image && ref->_lib->imageFingerprint() != 0) {
      if (fingerprint == 0) {
        fingerprint = Symbols::imageFingerprint(info->dlpi_phdr, info->dlpi_phnum, info->dlpi_addr);
      }
      same_image = ref->_lib->imageFingerprint() == fingerprint;
    } else if (!same_image) {
      if (!file_id_known) {
        struct stat st;
        if (stat(info->dlpi_name, &st) == 0) {
          file_id = CodeCache::makeFileId(major(st.st_dev) << 8 | minor(st.st_dev), st.st_ino);
        }
        file_id_known = true;
      }
      same_image = file_id != 0 && ref->_lib->fileId() == file_id;
    }
    if (same_image) {
      // The library may be a reload at the same address that is still
      // represented by this CodeCache (a reload is not re-parsed, its inode
      // has been seen), so its writability state cannot be trusted.
      if (ref->_lib->makeImportsWritable()) visit(ref->_lib, ref->_tag);
    }
  }
  return 0;
}

#ifdef UNIT_TEST
static std::atomic<LibraryPatcher::SocketImportFailureForTest>
    socket_import_failure_for_test{nullptr};
static std::atomic<LibraryPatcher::SocketImageFailureForTest>
    socket_image_failure_for_test{nullptr};
static std::atomic<int> socket_missing_original_for_test{-1};

static bool socket_image_fails_for_test(CodeCache* lib, const char* step) {
  LibraryPatcher::SocketImageFailureForTest failure =
      socket_image_failure_for_test.load(std::memory_order_acquire);
  return failure != nullptr && failure(lib, step);
}
#endif

static_assert(SOCKET_BASE_TABLE_SIZE > 0 &&
                  (SOCKET_BASE_TABLE_SIZE & (SOCKET_BASE_TABLE_SIZE - 1)) == 0,
              "socket DSO lookup table size must be a power of two");

static const char* library_basename(const char* path) {
  if (path == nullptr) {
    return nullptr;
  }
  const char* name = strrchr(path, '/');
  return name == nullptr ? path : name + 1;
}

static SocketPatchTarget socket_patch_target_for_library(
    CodeCache* lib, const char* name, bool in_jdk_directory) {
  if (lib == nullptr || name == nullptr) {
    return SOCKET_PATCH_NONE;
  }

  // Netty unlinks extracted images and shading renames them; use cached JNI markers.
  if (lib->hasNettyEpollMarkers()) {
    return SOCKET_PATCH_NETTY_NATIVE_EPOLL;
  }

  if (!in_jdk_directory) {
    return SOCKET_PATCH_NONE;
  }

  if (strcmp(name, "libnet.so") == 0 || strcmp(name, "libnio.so") == 0) {
    return SOCKET_PATCH_STANDARD_JDK_NETWORK;
  }

  // IBM Java 8 routes java.net through JCL_* exports in libjava before
  // reaching libc. Require the complete observed bridge signature so an
  // OpenJDK libjava or an arbitrary JNI DSO is never selected by name alone.
  if (strcmp(name, "libjava.so") == 0 &&
      lib->findSymbol("JCL_Send") != nullptr &&
      lib->findSymbol("JCL_Recv") != nullptr &&
      lib->findSymbol("JCL_Connect") != nullptr &&
      lib->findSymbol("JCL_Accept") != nullptr) {
    return SOCKET_PATCH_IBM_JCL_BRIDGE;
  }

  return SOCKET_PATCH_NONE;
}

static SocketPatchTarget socket_patch_target(
    CodeCache* lib, const char* path, const char* jdk_library_directory) {
  if (path == nullptr || jdk_library_directory == nullptr) {
    return SOCKET_PATCH_NONE;
  }
  const char* path_separator = strrchr(path, '/');
  if (path_separator == nullptr) {
    return SOCKET_PATCH_NONE;
  }
  size_t directory_length = static_cast<size_t>(path_separator - path);
  bool in_jdk_directory =
      strlen(jdk_library_directory) == directory_length &&
      strncmp(path, jdk_library_directory, directory_length) == 0;
  return socket_patch_target_for_library(
      lib, library_basename(path), in_jdk_directory);
}

static void* socket_hook_for_target(
    SocketPatchTarget target,
    const NativeSocketInterposer::NativeIoHookSpec& hook) {
  return target == SOCKET_PATCH_IBM_JCL_BRIDGE ? hook.fork_safe_hook
                                                : hook.hook;
}

static bool resolve_jdk_library_directory(char* directory) {
  CodeCache* java_library = Libraries::instance()->findLibraryByName("libjava.so");
  if (java_library != nullptr && java_library->name() != nullptr &&
      strcmp(library_basename(java_library->name()), "libjava.so") == 0 &&
      realpath(java_library->name(), directory) != nullptr) {
    char* separator = strrchr(directory, '/');
    if (separator != nullptr) {
      *separator = '\0';
      return true;
    }
  }

  // libjava may be loaded lazily. Supported JDK layouts place libjvm in a
  // subdirectory immediately below the directory containing the other native
  // JDK libraries.
  CodeCache* jvm_library = Libraries::instance()->findLibraryByName("libjvm.so");
  if (jvm_library == nullptr || jvm_library->name() == nullptr ||
      strcmp(library_basename(jvm_library->name()), "libjvm.so") != 0 ||
      realpath(jvm_library->name(), directory) == nullptr) {
    return false;
  }
  char* separator = strrchr(directory, '/');
  if (separator == nullptr) {
    return false;
  }
  *separator = '\0';
  separator = strrchr(directory, '/');
  if (separator == nullptr) {
    return false;
  }
  *separator = '\0';
  return true;
}

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

bool LibraryPatcher::socket_image_skipped_unlocked(const CodeCache* lib) {
  for (int index = 0; index < _socket_skipped_image_count; index++) {
    if (_socket_skipped_images[index]._image_base == lib->imageBase() &&
        _socket_skipped_images[index]._fingerprint == lib->imageFingerprint()) {
      return true;
    }
  }
  return false;
}

bool LibraryPatcher::skip_socket_image_unlocked(CodeCache* lib, const char* reason) {
  if (socket_image_skipped_unlocked(lib)) return true;
  if (_socket_skipped_image_count == SOCKET_SKIPPED_IMAGE_CAPACITY) {
    Log::warn("native I/O hooks disabled: too many skipped Netty epoll images");
    return false;
  }
  Log::warn("native I/O hooks skipped Netty epoll image %s: %s", lib->name(), reason);
  Counters::increment(NATIVE_IO_NETTY_IMAGES_SKIPPED);
  _socket_skipped_images[_socket_skipped_image_count++] = {lib->imageBase(),
                                                           lib->imageFingerprint()};
  return true;
}

bool LibraryPatcher::skip_socket_image(CodeCache* lib, u64 generation, bool require_active,
                                       const char* reason) {
  ExclusiveLockGuard locker(&_lock);
  // A stale discovery must not record a skip into a newer installation.
  if (_socket_generation != generation ||
      (require_active && !_socket_active.load(std::memory_order_relaxed))) {
    return true;
  }
  return skip_socket_image_unlocked(lib, reason);
}

void LibraryPatcher::initialize_persistent() {
  if (!_initialized.load(std::memory_order_acquire)) {
    _size = 0;
    // Release so the reset above is visible to any thread that sees the flag.
    // Once set, pthread_create patches are persistent across stop/start cycles.
    _initialized.store(true, std::memory_order_release);
  }
}

const void* LibraryPatcher::self_anchor() {
  // Any code address in this translation unit lies inside the profiler's own
  // mapping, so its address identifies us. A function is used rather than a
  // static variable because a CodeCache spans a library's executable segments
  // (see Symbols::parseLibraries), which do not cover .data/.bss.
  return (const void*)&self_anchor;
}

// The profiler must never patch its own import table. pthread_create_hook()
// below reaches the real pthread_create() through this library's own PLT, so a
// self-patch makes the hook call itself: the recursion exhausts the thread
// stack and the process dies of SIGSEGV without even an hs_err file, because
// the JVM's crash handler needs stack of its own to run.
//
// Recognising ourselves by mapped address range is the whole check. Comparing
// realpath(lib->name()) with our own path used to be, and it silently fails:
// dd-trace-java extracts libjavaProfiler.so to a temporary file and unlinks it
// once loaded, so realpath() on the still-mapped path returns nullptr and the
// comparison reported "not self". Whether that mattered depended on a library
// re-scan landing after the unlink, which is why the crashes looked random.
//
// Every native library cache carries its mapping bounds (Symbols::parseLibraries
// builds them from /proc/self/maps), so the range test needs no fallback.
bool LibraryPatcher::is_profiler_library(CodeCache* lib) {
  return lib != nullptr && lib->contains(self_anchor());
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
    // Block before the exit mark so a sampler cannot fault on the marked
    // identity (see Profiler::onThreadEnd for the recovery-order contract).
    blockProfilingForExit();
    ThreadExitRegistry::markCurrent();
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
// This registers cleanup via a sigsetjmp buffer in a runtime linked-list, NOT
// via an LSDA destructor.  _Unwind_ForcedUnwind's stop function
// (__pthread_unwind_stop) handles the cleanup without ever calling
// __gxx_personality_v0 for this frame, so _Unwind_SetGR is never called and
// the cross-version incompatibility is never triggered.
//
// On musl: pthread_cleanup_push already uses the C/sigsetjmp form (no RAII),
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

// Returns routine's result, which the wrappers hand to pthread_exit() so that a
// pthread_join() on the thread still sees what the original routine returned.
__attribute__((visibility("hidden"), noinline, no_stack_protector))
void* run_with_cleanup(func_start_routine routine, void* params,
                       void (*cleanup_fn)(void*), void* cleanup_arg) {
#ifdef __GLIBC__
    __pthread_unwind_buf_t cancel_buf = {};
    // With savemask=0, __sigsetjmp only writes __jmp_buf + int __mask_was_saved;
    // it never touches __saved_mask.  The inner struct of __pthread_unwind_buf_t
    // must cover exactly that writable prefix of struct __jmp_buf_tag.
    static_assert(offsetof(__pthread_unwind_buf_t, __cancel_jmp_buf) == 0 &&
                  sizeof(cancel_buf.__cancel_jmp_buf[0]) == offsetof(struct __jmp_buf_tag, __saved_mask),
                  "glibc __pthread_unwind_buf_t inner layout incompatible with struct __jmp_buf_tag");
    // __sigsetjmp/siglongjmp only intercepts _Unwind_ForcedUnwind (pthread_exit /
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
        // Reached via siglongjmp from glibc's stop function when pthread_exit
        // (or cancellation) fires.  Run cleanup and continue unwinding.
        cleanup_fn(cleanup_arg);
        __pthread_unwind_next(&cancel_buf);
        // __pthread_unwind_next is [[noreturn]]; this fails loudly rather than
        // falling through into __pthread_register_cancel on a torn-down frame
        // should a future/variant glibc ever return from it.
        __builtin_unreachable();
    }
    // Callers disable cancellation around resource acquisition and registration,
    // or enter as a new thread without a pending cancellation request.
    // The routine may restore cancellation only after this registration.
    __pthread_register_cancel(&cancel_buf);
    void* result = routine(params);
    __pthread_unregister_cancel(&cancel_buf);
    cleanup_fn(cleanup_arg);
    return result;
#else
    // musl / non-glibc: pthread_cleanup_push uses the C/sigsetjmp form, no RAII.
    // result is declared outside the push/pop block, which the macros open and
    // close.
    void* result;
    pthread_cleanup_push(cleanup_fn, cleanup_arg);
    result = routine(params);
    pthread_cleanup_pop(1);
    return result;
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
//     → pthread_exit(routine's result)
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
    pthread_exit(run_with_cleanup(routine, params, cleanup_fn, cleanup_arg));
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
    // pthread_exit instead of 'return': the saved LR in this frame is corrupted
    // by DEOPT PACKING. The result goes from run_with_cleanup's return register
    // into pthread_exit, never via this frame's stack, so pthread_join() sees it.
    // cleanup_unregister has already run via run_with_cleanup's normal return
    // path, so there is no registered cancel handler left.  The forced unwind
    // raised by pthread_exit walks this frame, but it is safe because no
    // destructor-bearing local (and hence no LSDA cleanup/handler action) is
    // live at this call site: __gxx_personality_v0 returns continue-unwind
    // without ever calling _Unwind_SetGR, avoiding the static-libgcc abort.
    // WARNING: adding any RAII local with a destructor between run_with_cleanup
    // and pthread_exit would reintroduce that crash.
    pthread_exit(run_with_cleanup(routine, params, cleanup_unregister, nullptr));
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
    // Pass the routine's result on, so pthread_join() sees it.
    pthread_exit(run_with_cleanup(routine, params, cleanup_unregister, nullptr));
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
   // Set by initialize_persistent() from Profiler::init() or start(). Not set
   // in Gtest, which never initializes. The hook may run before the first
   // start(); Profiler::registerThread() tolerates that.
   if (!_initialized.load(std::memory_order_acquire)) {
     return;
   }

   TEST_LOG("Patching libraries");
   patch_pthread_create();
}

bool LibraryPatcher::excluded_from_pthread_create_patch(CodeCache* lib) {
  if (lib->name() == nullptr) return true;

  if (is_profiler_library(lib)) { // Don't patch self
    return true;
  }

  // Don't patch sanitizer runtime libraries — intercepting their internal
  // pthread_create calls causes reentrancy and heap corruption under ASAN.
  const char* base = strrchr(lib->name(), '/');
  base = (base != nullptr) ? base + 1 : lib->name();
  return strncmp(base, "libasan", 7) == 0 ||
         strncmp(base, "libtsan", 7) == 0 ||
         strncmp(base, "libubsan", 8) == 0;
}

void LibraryPatcher::patch_library_unlocked(CodeCache* lib) {
  if (excluded_from_pthread_create_patch(lib)) return;

  // Every slot (JUMP_SLOT and GLOB_DAT): a thread created through either must
  // reach the hook.
  size_t slot_count = lib->importCount(im_pthread_create);
  if (slot_count == 0) {
    return;
  }

  void* func = (void*)pthread_create_hook;

#ifdef __aarch64__
  // Workaround stack guard corruption in Linux/aarch64/musl/jdk11
  if (VM::isHotspot() && OS::isMusl() && VM::java_version() == 11) {
    func = (void*)pthread_create_hook_spec;
  }
#endif

  // An entry outlives its library: a reload at the same base keeps its
  // CodeCache and entry, but its fresh GOT holds the real pthread_create. The
  // walk verified it is the same image, so the saved slots are valid.
  int entry = find_entry(_patched_entries, _size, lib);
  bool reload = entry >= 0;
  if (reload) {
    pthread_create_entry_mapped[entry] = true;  // this walk found it mapped
  }
  void* real = reinterpret_cast<void*>(&pthread_create);
  // A reload's fresh GOT holds the real pthread_create or, with lazy binding,
  // the library's own PLT stub. Anything else was hooked by someone after us:
  // leave it rather than take their interception away.
  auto should_patch = [&](void** slot) {
    if (slot == nullptr) return false;
    void* current = __atomic_load_n(slot, __ATOMIC_RELAXED);
    return current != func && (!reload || current == real || lib->contains(current));
  };
  bool any_patch = false;
  for (size_t index = 0; index < slot_count && !any_patch; index++) {
    any_patch = should_patch(lib->findImport(im_pthread_create, index));
  }
  if (!any_patch) {
    return;
  }
  if (!reload) {
    if (_size >= MAX_NATIVE_LIBS) {
      TEST_LOG("Patching: entry table full, %s is not routed through the hook", lib->name());
      return;
    }
    // Only _lib is meaningful for pthread_create entries: the slots are found
    // again through lib->findImport().
    pthread_create_entry_mapped[_size] = true;
    _patched_entries[_size++]._lib = lib;
  }
  TEST_LOG("Patching: %s", lib->name());
  for (size_t index = 0; index < slot_count; index++) {
    void** slot = lib->findImport(im_pthread_create, index);
    if (should_patch(slot)) {
      __atomic_store_n(slot, func, __ATOMIC_RELAXED);
    }
  }
}

void LibraryPatcher::unpatch_recording_hooks() {
  // Only the socket patches are per recording; pthread_create and sigaction
  // stay installed for the process lifetime.
  // Native I/O owners stop first; an owner still active keeps its patches.
  TEST_LOG("Unpatch libraries: only socket hooks");
  unpatch_socket_functions_if_inactive();
}

// The loader's dlpi_adds/dlpi_subs, or false if it does not report them. Not
// with _lock held: dl_iterate_phdr() takes dl_load_write_lock (lock order above).
struct LoaderCounts {
  unsigned long long adds;
  unsigned long long subs;
};

static bool loader_counts(LoaderCounts* counts) {
  struct Result { bool known; LoaderCounts counts; } result = {false, {0, 0}};
  dl_iterate_phdr(
      [](struct dl_phdr_info* info, size_t size, void* data) -> int {
        Result* r = static_cast<Result*>(data);
        if (size >= offsetof(struct dl_phdr_info, dlpi_subs) + sizeof(info->dlpi_subs)) {
          r->known = true;
          r->counts.adds = info->dlpi_adds;
          r->counts.subs = info->dlpi_subs;
        }
        return 1;  // the counters are global; the first object is enough
      },
      &result);
  *counts = result.counts;
  return result.known;
}

// The loader counts as of the last pass that re-checked the unmapped (adds) or
// all (subs) patched libraries; ~0 before the first. Written without _lock: each
// store is a count read before its walk, so one that loses a race only causes a
// re-check.
static std::atomic<unsigned long long> pthread_create_checked_adds{~0ULL};
static std::atomic<unsigned long long> pthread_create_checked_subs{~0ULL};

void LibraryPatcher::patch_pthread_create() {
  // A patched library needs another look only once reloaded (an unload, then
  // a load, possibly in later passes): after an unload re-check them all and
  // note the unmapped; after a load re-check only those. musl never unmaps.
  enum Recheck { NONE, UNMAPPED, ALL };
  LoaderCounts counts = {0, 0};
  bool counts_known = !OS::isMusl() && loader_counts(&counts);
  Recheck recheck = NONE;
  if (!OS::isMusl()) {
    if (!counts_known ||
        counts.subs != pthread_create_checked_subs.load(std::memory_order_acquire)) {
      recheck = ALL;
    } else if (counts.adds != pthread_create_checked_adds.load(std::memory_order_acquire)) {
      recheck = UNMAPPED;
    }
  }

  struct Context { const CodeCacheArray* native_libs; Recheck recheck; };
  Context ctx = {&Libraries::instance()->native_libs(), recheck};
  {
    LiveLibraryWalk walk(
        [](void* data) {
          const Context& c = *static_cast<const Context*>(data);
          for (int index = 0; index < _size; index++) {
            pthread_create_entry_libs[index] = _patched_entries[index]._lib;
            if (c.recheck == ALL) {
              // patch_library_unlocked() sets it again if this walk visits it.
              pthread_create_entry_mapped[index] = false;
            } else if (c.recheck == NONE || pthread_create_entry_mapped[index]) {
              continue;
            }
            add_live_candidate(_patched_entries[index]._lib, 0);
          }
          CodeCache** libs_end = pthread_create_entry_libs + _size;
          std::sort(pthread_create_entry_libs, libs_end);
          int num_of_libs = c.native_libs->count();
          for (int index = 0; index < num_of_libs; index++) {
            CodeCache* lib = c.native_libs->at(index);
            // Filter out everything patch_library_unlocked() would decline, so
            // that libraries never patched are not re-checked for liveness on
            // every pass.
            if (lib != nullptr && lib->peekImport(im_pthread_create) != nullptr
                && !excluded_from_pthread_create_patch(lib)
                && !std::binary_search(pthread_create_entry_libs, libs_end, lib)) {
              add_live_candidate(lib, 0);
            }
          }
        },
        &ctx,
        [](CodeCache* lib, int) { patch_library_unlocked(lib); });
    // The walk holds _lock until it is destroyed, so _size is stable here.
    TEST_LOG("%d libraries patched", _size);
  }
  if (recheck != NONE && counts_known) {
    pthread_create_checked_adds.store(counts.adds, std::memory_order_release);
    if (recheck == ALL) {
      pthread_create_checked_subs.store(counts.subs, std::memory_order_release);
    }
  }
}

// Patch sigaction in all libraries to prevent any library from overwriting
// our SIGSEGV/SIGBUS handlers. This protects against misbehaving libraries
// (like wasmtime) that install broken signal handlers calling malloc().
void LibraryPatcher::patch_sigaction_in_library(CodeCache* lib) {
  if (lib->name() == nullptr) return;
  if (!_initialized.load(std::memory_order_acquire)) return;  // Not initialized yet

  // Don't patch ourselves
  if (is_profiler_library(lib)) {
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
  if (has_entry_for(_sigaction_entries, _sigaction_size, lib)) {
    return;
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
  if (!_initialized.load(std::memory_order_acquire)) return;
  LiveLibraryWalk walk(
      [](void* ctx) {
        const CodeCacheArray& native_libs = *(const CodeCacheArray*)ctx;
        int num_of_libs = native_libs.count();
        for (int index = 0; index < num_of_libs; index++) {
          CodeCache* lib = native_libs.at(index);
          // Same filtering as in patch_pthread_create(), for patch_sigaction_in_library().
          if (lib != nullptr && lib->name() != nullptr && lib->peekImport(im_sigaction) != nullptr
              && !is_profiler_library(lib)
              && !has_entry_for(_sigaction_entries, _sigaction_size, lib)) {
            add_live_candidate(lib, 0);
          }
        }
      },
      (void*)&Libraries::instance()->native_libs(),
      [](CodeCache* lib, int) { patch_sigaction_in_library(lib); });
}

class SocketPatchCandidate {
public:
  CodeCache* _lib;
  UnloadProtection _protection;
  size_t _patch_count;
  SocketPatchTarget _target;

  SocketPatchCandidate(CodeCache* lib, UnloadProtection&& protection,
                       size_t patch_count, SocketPatchTarget target)
      : _lib(lib), _protection(std::move(protection)),
        _patch_count(patch_count), _target(target) {}

  SocketPatchCandidate(const SocketPatchCandidate&) = delete;
  SocketPatchCandidate& operator=(const SocketPatchCandidate&) = delete;
  SocketPatchCandidate(SocketPatchCandidate&&) noexcept = default;
  SocketPatchCandidate& operator=(SocketPatchCandidate&&) noexcept = default;
};

#ifdef UNIT_TEST
static std::atomic<LibraryPatcher::SocketPatchObserverForTest> socket_patch_observer{nullptr};

void LibraryPatcher::setSocketPatchObserverForTest(SocketPatchObserverForTest observer) {
  socket_patch_observer.store(observer, std::memory_order_release);
}

static void observeSocketPatchForTest(const char* phase) {
  auto observer = socket_patch_observer.load(std::memory_order_acquire);
  if (observer != nullptr) observer(phase);
}
#endif

static void** socket_import_slot(CodeCache* lib, ImportId import_id, size_t index) {
  void** location = lib->findImport(import_id, index);
#ifdef UNIT_TEST
  LibraryPatcher::SocketImportFailureForTest failure =
      socket_import_failure_for_test.load(std::memory_order_acquire);
  if (failure != nullptr && failure(lib, import_id, index)) location = nullptr;
#endif
  return location;
}

static bool socket_import_slots_present(CodeCache* lib,
                                        const NativeSocketInterposer::NativeIoHookSpec* hooks,
                                        int unhooked_index) {
  for (int hook_index = 0; hook_index < NativeSocketInterposer::NUM_NATIVE_IO_HOOKS;
       hook_index++) {
    if (hook_index == unhooked_index) continue;
    ImportId import_id = hooks[hook_index].import_id;
    for (size_t index = 0; index < lib->importCount(import_id); index++) {
      if (socket_import_slot(lib, import_id, index) == nullptr) return false;
    }
  }
  return true;
}

static bool socket_image_pinned(CodeCache* lib, UnloadProtection& protection) {
#ifdef UNIT_TEST
  // Models a mapped image that dlopen(RTLD_NOLOAD) rejects.
  if (protection.isValid() && socket_image_fails_for_test(lib, "pin")) {
    void* handle = protection.release();
    if (handle != nullptr) dlclose(handle);
  }
#endif
  return protection.isValid();
}

static bool socket_imports_writable(CodeCache* lib) {
#ifdef UNIT_TEST
  if (socket_image_fails_for_test(lib, "writable")) return false;
#endif
  return lib->makeImportsWritable();
}

// The loader walk owns the headers and pathname until the callback returns.
static bool mappingMatches(const CodeCache* lib, char* loader_name = nullptr) {
  if (lib->imageBase() == nullptr || lib->imageFingerprint() == 0) return false;
  struct Query {
    const CodeCache* lib;
    char* loader_name;
  } query{lib, loader_name};
  return dl_iterate_phdr([](struct dl_phdr_info* info, size_t, void* data) {
    Query* query = static_cast<Query*>(data);
    const CodeCache* lib = query->lib;
    uintptr_t min_vaddr = UINTPTR_MAX;
    for (int i = 0; i < info->dlpi_phnum; i++) {
      if (info->dlpi_phdr[i].p_type == PT_LOAD) {
        min_vaddr = std::min(min_vaddr, static_cast<uintptr_t>(info->dlpi_phdr[i].p_vaddr));
      }
    }
    if (min_vaddr == UINTPTR_MAX ||
        ((info->dlpi_addr + min_vaddr) & ~OS::page_mask) !=
            reinterpret_cast<uintptr_t>(lib->imageBase())) return 0;
    // A loader alias may no longer exist; base plus layout identifies the slots.
    u64 fingerprint = Symbols::imageFingerprint(info->dlpi_phdr, info->dlpi_phnum,
                                                 info->dlpi_addr);
    if (fingerprint != lib->imageFingerprint()) return 2;
    if (query->loader_name != nullptr && info->dlpi_name != nullptr) {
      size_t length = strlen(info->dlpi_name);
      if (length < PATH_MAX) memcpy(query->loader_name, info->dlpi_name, length + 1);
    }
    return 1;
  }, &query) == 1;
}

bool LibraryPatcher::patch_socket_functions(bool require_active,
                                            std::atomic<bool>* activating_owner) {
#ifdef UNIT_TEST
  if (!require_active) observeSocketPatchForTest("before_start_snapshot");
#endif
  u64 generation;
  {
    ExclusiveLockGuard locker(&_lock);
    if (require_active && !_socket_active.load(std::memory_order_relaxed)) {
      return false;
    }
    if (!require_active) {
      // Invalidate older refreshes before the requesting owner becomes visible.
      _socket_generation++;
      if (activating_owner != nullptr) {
        activating_owner->store(true, std::memory_order_release);
      }
    }
    generation = _socket_generation;
  }
#ifdef UNIT_TEST
  if (!require_active) observeSocketPatchForTest("start_snapshot");
#endif
  auto disable_and_unpatch = [generation, require_active]() {
    std::vector<SocketPatchedLibrary> libraries_to_release;
    {
      ExclusiveLockGuard locker(&_lock);
      // Discovery may outlive stop/restart. Only its own installation may fail.
      if (_socket_generation != generation ||
          (require_active && !_socket_active.load(std::memory_order_relaxed))) {
        return false;
      }
      NativeSocketInterposer::instance()->disableAfterPatchFailure();
      NativeSocketSampler::disableAfterPatchFailure();
      unpatch_socket_functions_unlocked(libraries_to_release);
    }
    release_socket_libraries(libraries_to_release);
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
      if (original == hooks[hook_index].hook ||
          original == hooks[hook_index].fork_safe_hook) {
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
  bool epoll_pwait2_original =
      cached_originals[NativeSocketInterposer::HOOK_EPOLL_PWAIT2] != nullptr;
#ifdef UNIT_TEST
  if (socket_missing_original_for_test.load(std::memory_order_acquire) ==
      NativeSocketInterposer::HOOK_EPOLL_PWAIT2) {
    epoll_pwait2_original = false;
  }
#endif
  // Before glibc 2.35 libc has no epoll_pwait2. Its optional imports, including
  // non-NULL lazy-binding stubs, then stay untouched instead of disabling the hooks.
  const int unhooked_index =
      epoll_pwait2_original ? -1 : static_cast<int>(NativeSocketInterposer::HOOK_EPOLL_PWAIT2);

  // Publish the process that owns profiler state before any fork-safe hook can
  // become reachable. A post-fork child observes a different getpid() value
  // and calls the original libc function without touching profiler state.
  NativeSocketInterposer::setHookOwnerPid(getpid());

  const CodeCacheArray& native_libs = Libraries::instance()->native_libs();
  int num_of_libs = native_libs.count();

  int capped = num_of_libs <= MAX_NATIVE_LIBS ? num_of_libs : MAX_NATIVE_LIBS;
  char jdk_library_directory[PATH_MAX];
  if (!resolve_jdk_library_directory(jdk_library_directory)) {
    Log::warn("native I/O hooks disabled: cannot locate the JDK native library directory");
    return disable_and_unpatch();
  }
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
    // Checked here rather than in a pre-pass keyed by index: the library array
    // can grow between the two, and a flag applied to the wrong entry could let
    // us patch ourselves.
    if (is_profiler_library(lib)) {
      continue;
    }
    SocketPatchTarget target = socket_patch_target_for_library(
        lib, library_basename(lib->name()), false);
    if (target == SOCKET_PATCH_NONE) {
      char path[PATH_MAX];
      char* resolved_path = realpath(lib->name(), path);
      if (resolved_path == nullptr) continue;
      target = socket_patch_target(lib, resolved_path, jdk_library_directory);
      if (target == SOCKET_PATCH_NONE) continue;
    }
    // Failures local to one Netty image skip that image; JDK images stay fail-closed.
    bool netty_image = target == SOCKET_PATCH_NETTY_NATIVE_EPOLL;
    if (netty_image) {
      ExclusiveLockGuard locker(&_lock);
      if (socket_image_skipped_unlocked(lib)) continue;
    }

    // Optional weak GOT entries may be NULL; retain the image before reading them.
    UnloadProtection protection(lib);
    if (!socket_image_pinned(lib, protection)) {
      char loader_name[PATH_MAX] = {};
      if (!mappingMatches(lib, loader_name)) continue;
#ifdef UNIT_TEST
      observeSocketPatchForTest("loader_name_lookup");
#endif
      // NOLOAD needs the loader's alias when the cached maps pathname is gone.
      // Copy it outside _lock, then revalidate identity after acquiring the pin.
      if (loader_name[0] != '\0') protection = UnloadProtection(lib, loader_name);
      if (!socket_image_pinned(lib, protection)) {
        if (!mappingMatches(lib)) continue;
        if (netty_image) {
          if (!skip_socket_image(lib, generation, require_active, "cannot retain mapped DSO")) {
            return disable_and_unpatch();
          }
          continue;
        }
        Log::warn("native I/O hooks disabled: cannot retain mapped DSO %s",
                  lib->name());
        return disable_and_unpatch();
      }
    }
#ifdef UNIT_TEST
    observeSocketPatchForTest("mapping_lookup");
#endif
    if (!mappingMatches(lib)) continue;
    size_t patch_count = 0;
    bool imports_incomplete = false;
    for (int hook_index = 0; hook_index < NativeSocketInterposer::NUM_NATIVE_IO_HOOKS;
         hook_index++) {
      if (hook_index == unhooked_index) continue;
      ImportId import_id = hooks[hook_index].import_id;
      if (!lib->importsComplete(import_id)) {
        if (netty_image) {
          imports_incomplete = true;
          break;
        }
        Log::warn("native I/O hooks disabled: incomplete %s imports in %s",
                  hooks[hook_index].name, lib->name());
        return disable_and_unpatch();
      }
      size_t count = lib->importCount(import_id);
      if (count == 0) continue;
      if (hook_index == NativeSocketInterposer::HOOK_EPOLL_PWAIT2) {
        for (size_t i = 0; i < lib->importCount(import_id); i++) {
          void** location = lib->findImport(import_id, i);
          if (location != nullptr && __atomic_load_n(location, __ATOMIC_ACQUIRE) == nullptr) {
            count--;
          }
        }
        if (count == 0) continue;
      }
      if (cached_originals[hook_index] == nullptr) {
        Log::warn("native I/O hooks disabled: no original for imported %s in %s",
                  hooks[hook_index].name, lib->name());
        return disable_and_unpatch();
      }
      patch_count += count;
    }
    if (imports_incomplete) {
      if (!skip_socket_image(lib, generation, require_active, "incomplete imports")) {
        return disable_and_unpatch();
      }
      continue;
    }
    if (patch_count == 0) continue;

    try {
      candidates.emplace_back(lib, std::move(protection), patch_count, target);
    } catch (const std::bad_alloc&) {
      Log::warn("native I/O hooks disabled: unable to retain DSO candidate %s",
                lib->name());
      return disable_and_unpatch();
    }
  }

#ifdef UNIT_TEST
  observeSocketPatchForTest("before_commit");
#endif
  std::vector<SocketPatchedLibrary> libraries_to_release;
  bool success = true;
  size_t standard_slots_patched = 0;
  size_t ibm_bridge_slots_patched = 0;
  size_t total_slots_patched = 0;
  {
    ExclusiveLockGuard locker(&_lock);
    if (_socket_generation != generation ||
        (require_active && !_socket_active.load(std::memory_order_relaxed))) {
      return false;
    }

    // Validate every new image before any write, so a skipped Netty image has no
    // partial patch. Its pin is released with the candidate table.
    auto skipped = [](const SocketPatchCandidate& candidate) {
      return candidate._target == SOCKET_PATCH_NETTY_NATIVE_EPOLL &&
             socket_image_skipped_unlocked(candidate._lib);
    };
    for (SocketPatchCandidate& candidate : candidates) {
      CodeCache* lib = candidate._lib;
      if (socket_library_patched_unlocked(lib->imageBase()) || skipped(candidate)) continue;
      bool netty_image = candidate._target == SOCKET_PATCH_NETTY_NATIVE_EPOLL;
      const char* failure = nullptr;
      // A released pin permits an identical-base reload whose full-RELRO GOT
      // is read-only again, even though this append-only cache says writable.
      if (!socket_imports_writable(lib)) {
        failure = "cannot make imports writable";
      } else if (netty_image && !socket_import_slots_present(lib, hooks, unhooked_index)) {
        failure = "missing import slot";
      }
      if (failure == nullptr) continue;
      if (netty_image && skip_socket_image_unlocked(lib, failure)) continue;
      Log::warn("native I/O hooks disabled: %s in %s", failure, lib->name());
      success = false;
      break;
    }

    size_t additional_patches = 0;
    size_t additional_libraries = 0;
    for (SocketPatchCandidate& candidate : candidates) {
      if (!skipped(candidate) && !socket_library_patched_unlocked(candidate._lib->imageBase())) {
        additional_patches += candidate._patch_count;
        additional_libraries++;
      }
    }

    if (success) {
      try {
        _socket_entries.reserve(_socket_entries.size() + additional_patches);
        _socket_libraries.reserve(_socket_libraries.size() + additional_libraries);
      } catch (const std::bad_alloc&) {
        Log::warn("native I/O hooks disabled: unable to reserve patch transaction");
        success = false;
      }
    }

    if (success) {
      for (SocketPatchCandidate& candidate : candidates) {
        CodeCache* lib = candidate._lib;
        if (skipped(candidate) || socket_library_patched_unlocked(lib->imageBase())) {
          continue;
        }
        size_t first_patch = _socket_entries.size();
        for (int hook_index = 0;
             hook_index < NativeSocketInterposer::NUM_NATIVE_IO_HOOKS && success;
             hook_index++) {
          if (hook_index == unhooked_index) continue;
          ImportId import_id = hooks[hook_index].import_id;
          size_t count = lib->importCount(import_id);
          for (size_t import_index = 0; import_index < count; import_index++) {
            void** location = socket_import_slot(lib, import_id, import_index);
            // Netty images were validated above; a hit here still rolls back every image.
            if (location == nullptr) {
              Log::warn("native I/O hooks disabled: missing import slot for "
                        "%s in %s", hooks[hook_index].name, lib->name());
              success = false;
              break;
            }
            void* original =
                reinterpret_cast<void*>(__atomic_load_n(location, __ATOMIC_ACQUIRE));
            // A weak NULL import must remain NULL: Netty uses it as an availability probe.
            if (hook_index == NativeSocketInterposer::HOOK_EPOLL_PWAIT2 && original == nullptr) {
              continue;
            }
            _socket_entries.push_back({location, original});
            void* hook = socket_hook_for_target(candidate._target,
                                                hooks[hook_index]);
            // Compose above the JDK 8 libnet adapter without changing other poll imports.
            if (import_id == im_poll &&
                original == reinterpret_cast<void*>(Symbols::restartablePoll)) {
              hook = reinterpret_cast<void*>(NativeSocketInterposer::restartable_poll_hook);
            }
            __atomic_store_n(location, hook, __ATOMIC_RELEASE);
            if (candidate._target == SOCKET_PATCH_IBM_JCL_BRIDGE) {
              ibm_bridge_slots_patched++;
            } else {
              standard_slots_patched++;
            }
          }
        }
        if (!success) {
          break;
        }
        _socket_libraries.push_back(
            {lib->imageBase(), candidate._protection.release(), first_patch,
             _socket_entries.size() - first_patch});
        remember_socket_library_unlocked(lib->imageBase());
      }
      if (success) {
        _socket_active.store(true, std::memory_order_release);
      }
    }
    if (!success) {
      // Keep owner disable and restoration in the same installation generation.
      // Releasing DSO handles below must not disable owners installed afterward.
      NativeSocketInterposer::instance()->disableAfterPatchFailure();
      NativeSocketSampler::disableAfterPatchFailure();
      unpatch_socket_functions_unlocked(libraries_to_release);
    }
    total_slots_patched = _socket_entries.size();
  }

  release_socket_libraries(libraries_to_release);
  if (!success) {
    return false;
  }

  Counters::increment(NATIVE_IO_STANDARD_HOOKS_PATCHED,
                      standard_slots_patched);
  Counters::increment(NATIVE_IO_IBM_BRIDGE_HOOKS_PATCHED,
                      ibm_bridge_slots_patched);
  TEST_LOG("patch_socket_functions DONE total_slots=%zu standard_new=%zu "
           "ibm_bridge_new=%zu num_libs_scanned=%d",
           total_slots_patched, standard_slots_patched,
           ibm_bridge_slots_patched, capped);
#ifdef UNIT_TEST
  observeSocketPatchForTest("committed");
#endif
  return true;
}

#ifdef UNIT_TEST
LibraryPatcher::SocketImportFailureForTest
LibraryPatcher::exchangeSocketImportFailureForTest(SocketImportFailureForTest failure) {
  return socket_import_failure_for_test.exchange(failure, std::memory_order_acq_rel);
}

LibraryPatcher::SocketImageFailureForTest
LibraryPatcher::exchangeSocketImageFailureForTest(SocketImageFailureForTest failure) {
  return socket_image_failure_for_test.exchange(failure, std::memory_order_acq_rel);
}

int LibraryPatcher::exchangeSocketMissingOriginalForTest(int hook_index) {
  return socket_missing_original_for_test.exchange(hook_index, std::memory_order_acq_rel);
}

void LibraryPatcher::fill_socket_skipped_images_for_test() {
  ExclusiveLockGuard locker(&_lock);
  // A NULL base with fingerprint 0 never matches a validated image.
  while (_socket_skipped_image_count < SOCKET_SKIPPED_IMAGE_CAPACITY) {
    _socket_skipped_images[_socket_skipped_image_count++] = {nullptr, 0};
  }
}

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
  if (!lib->importsComplete(import_id) || !lib->makeImportsWritable()) {
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
    if (location == nullptr) {
      continue;
    }
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

SocketPatchTarget LibraryPatcher::socket_patch_target_for_test(
    CodeCache* lib, const char* library_name, bool in_jdk_directory) {
  return socket_patch_target_for_library(lib, library_name, in_jdk_directory);
}

void* LibraryPatcher::socket_hook_for_target_for_test(
    SocketPatchTarget target, int hook_index) {
  if (hook_index < 0 ||
      hook_index >= NativeSocketInterposer::NUM_NATIVE_IO_HOOKS) {
    return nullptr;
  }
  return socket_hook_for_target(target,
                                NativeSocketInterposer::hookSpecs()[hook_index]);
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
  _socket_generation++;
  TEST_LOG("unpatch_socket_functions restoring %zu slot(s)", _socket_entries.size());
  for (const SocketPatchEntry& entry : _socket_entries) {
    __atomic_store_n(entry._location, entry._func,
                     __ATOMIC_RELEASE);
  }
  _socket_entries.clear();
  memset(_socket_bases, 0, sizeof(_socket_bases));
  _socket_skipped_image_count = 0;
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
  if (!_socket_active.load(std::memory_order_acquire)) return;
  // patch_socket_functions owns generation-checked failure cleanup. A cancelled
  // refresh must never disable owners published by a later start.
  patch_socket_functions(true);
#ifdef UNIT_TEST
  observeSocketPatchForTest("refresh_result");
#endif
}

#endif // __linux__
