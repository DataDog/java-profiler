/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _LIBRARYPATCHER_H
#define _LIBRARYPATCHER_H

#include "codeCache.h"
#include "spinLock.h"
#include <atomic>

// A malloc-family function to hook: its import and the hook to install.
typedef struct _mallocHookSpec {
  ImportId _id;
  void*    _hook;
} MallocHookSpec;

// malloc, calloc, realloc, posix_memalign, aligned_alloc
const int MAX_MALLOC_HOOKS = 5;

#ifdef __linux__

struct dl_phdr_info;

// Patch libraries' @plt entries
typedef struct _patchEntry {
  CodeCache* _lib;
  // library's @plt location
  void** _location;
  // original function
  void*  _func;
} PatchEntry;

// A patched malloc-family GOT slot. Unlike PatchEntry it keeps the hook that
// was installed, so the restore can tell whether the slot still holds it.
typedef struct _mallocPatchEntry {
  CodeCache* _lib;
  void**     _location;
  void*      _func;   // original value
  void*      _hook;
} MallocPatchEntry;

// A library to visit with a LibraryPatcher::LiveLibraryWalk
typedef struct _libraryRef {
  uintptr_t  _base;  // lib->imageBase(), the sort key
  CodeCache* _lib;
  int        _tag;   // caller-defined, passed back to the visitor
} LibraryRef;

// Adds a walk's candidates with LibraryPatcher::add_live_candidate(); ctx is
// the context the walk was given.
typedef void (*LiveLibraryCollector)(void* ctx);
typedef void (*LiveLibraryVisitor)(CodeCache* lib, int tag);

class LibraryPatcher {
  friend class LibraryPatcherTestAccessor;

private:
  static SpinLock    _lock;
  // Set by initialize(), which Profiler::start() calls just before the first
  // library scan. Patching must not begin any earlier: pthread_create_hook()
  // routes newly created threads through Profiler::registerThread(), which
  // dereferences state that only exists once the profiler is running. Read from
  // the Libraries refresher thread, hence atomic with release/acquire.
  static std::atomic<bool> _initialized;
  static PatchEntry  _patched_entries[MAX_NATIVE_LIBS];
  static int         _size;
  static bool        _patch_pthread_create;

  // Separate tracking for sigaction patches
  static PatchEntry  _sigaction_entries[MAX_NATIVE_LIBS];
  static int         _sigaction_size;

  // Separate tracking for socket (send/recv/write/read) patches.
  // Each library can contribute up to 4 GOT slots (send/recv/write/read).
  static PatchEntry  _socket_entries[4 * MAX_NATIVE_LIBS];
  static int         _socket_size;

  // Malloc-family patches (see MallocHooker). A library's slots are appended
  // together in one visit, so they form a single run of entries.
  static MallocPatchEntry _malloc_entries[MAX_MALLOC_HOOKS * NUM_IMPORT_TYPES * MAX_NATIVE_LIBS];
  static int              _malloc_size;

  // Candidates of the current LiveLibraryWalk, filled by add_live_candidate().
  // Guarded by _lock.
  static LibraryRef  _live_refs[MAX_NATIVE_LIBS];
  static int         _live_count;

  // Takes _lock, which it holds until destroyed, then calls collect(ctx) and
  // visit(lib, tag) for every candidate whose library is still loaded, and
  // clears the candidates. On glibc it does so inside a dl_iterate_phdr()
  // walk, so _lock is always taken after the loader's dl_load_write_lock (see
  // libraryPatcher_linux.cpp). All of LibraryPatcher's work under _lock runs
  // in a walk, and every write it makes through a saved GOT slot comes from
  // a visit: patched libraries are not pinned and can be dlclose()d.
  class LiveLibraryWalk {
  public:
    LiveLibraryWalk(LiveLibraryCollector collect, void* ctx, LiveLibraryVisitor visit);
    ~LiveLibraryWalk() { _lock.unlock(); }
    LiveLibraryWalk(const LiveLibraryWalk&) = delete;
    LiveLibraryWalk& operator=(const LiveLibraryWalk&) = delete;
  };

  static void add_live_candidate(CodeCache* lib, int tag);
  static int visit_loaded_object(struct dl_phdr_info* info, size_t size, void* data);
  static bool needs_socket_patch(CodeCache* lib);
  static void patch_socket_slots(CodeCache* lib);
  static void patch_socket_slot(void** location, void* hook_fn, const char* fn_name, CodeCache* lib);
  static bool excluded_from_pthread_create_patch(CodeCache* lib);
  static void patch_library_unlocked(CodeCache* lib);
  static void patch_pthread_create();
  static void patch_pthread_setspecific();
  static void patch_sigaction_in_library(CodeCache* lib);
  // An address known to lie inside this library; how is_profiler_library()
  // recognises the profiler's own mapping.
  static const void* self_anchor();
  // True when `lib` is the profiler's own library, which must never be patched.
  static bool is_profiler_library(CodeCache* lib);
public:
  // True while socket hooks are installed; read by Profiler::dlopen_hook
  // to decide whether to re-patch after a new library is loaded.
  // Set to true after the first batch of libraries is patched in patch_socket_functions().
  // Libraries loaded after profiler start are picked up on the next dlopen_hook call,
  // which calls install_socket_hooks() to patch them if _socket_active is true.
  // Low-probability race: stop() is called only on JVM exit; atomic<bool> is zero-cost insurance.
  static std::atomic<bool> _socket_active;
  static void initialize();
  static void patch_libraries();
  static void unpatch_libraries();
  static void patch_sigaction();
  // initial: called from NativeSocketSampler::start(). A non-initial call
  // (after a dlopen) only patches while the hooks are active, re-checked under
  // _lock, so it cannot re-install them after unpatch_socket_functions().
  static bool patch_socket_functions(bool initial);
  static void unpatch_socket_functions();
  // Installs the given malloc-family hooks in every loaded library not
  // patched yet. Callers serialize (MallocHooker::_patch_lock).
  static void patch_malloc_functions(const MallocHookSpec* specs, int count);
  // Restores every saved malloc-family slot in the libraries that are still
  // loaded, unless another tool re-patched it since, and forgets the entries.
  static void unpatch_malloc_functions();
  // Called from Profiler::dlopen_hook after a new library is loaded.
  // No-op when socket hooks are not active.
  static inline void install_socket_hooks() {
    if (_socket_active.load(std::memory_order_acquire)) {
      patch_socket_functions(false);
    }
  }
};

#else

class LibraryPatcher {
public:
  static void initialize() { }
  static void patch_libraries() { }
  static void unpatch_libraries() { }
  static void patch_sigaction() { }
  static bool patch_socket_functions(bool initial) { return false; }
  static void unpatch_socket_functions() { }
  static void install_socket_hooks() { }
  static void patch_malloc_functions(const MallocHookSpec* specs, int count) { }
  static void unpatch_malloc_functions() { }
};

#endif

#endif // _LIBRARYPATCHER_H
