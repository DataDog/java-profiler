/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _LIBRARYPATCHER_H
#define _LIBRARYPATCHER_H

#include "codeCache.h"
#include "spinLock.h"

#include <atomic>
#include <vector>

#ifdef __linux__

struct dl_phdr_info;

// Patch libraries' imported function relocation slots.
typedef struct _patchEntry {
  CodeCache* _lib;
  // Library import location.
  void** _location;
  // original function
  void*  _func;
} PatchEntry;

// Native I/O patching only needs the slot and its exact pre-patch value.
// Each retained import location is tracked independently for restoration.
typedef struct _socketPatchEntry {
  void** _location;
  void*  _func;
} SocketPatchEntry;

typedef struct _socketPatchedLibrary {
  const void* _image_base;
  void* _unload_protection;
  size_t _first_patch;
  size_t _patch_count;
} SocketPatchedLibrary;

enum SocketPatchTarget : u8 {
  SOCKET_PATCH_NONE = 0,
  SOCKET_PATCH_STANDARD_JDK_NETWORK,
  SOCKET_PATCH_IBM_JCL_BRIDGE
};

const int SOCKET_BASE_TABLE_SIZE = MAX_NATIVE_LIBS * 2;
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

  // Separate tracking for native I/O patches.
  // Each library can contribute any number of retained import slots per I/O hook.
  // Protected by _lock; installs and restorations invalidate older discoveries.
  static u64 _socket_generation;
  static std::vector<SocketPatchEntry> _socket_entries;
  static std::vector<SocketPatchedLibrary> _socket_libraries;
  static const void* _socket_bases[SOCKET_BASE_TABLE_SIZE];

  // Candidates of the current LiveLibraryWalk, filled by add_live_candidate().
  // Guarded by _lock.
  static LibraryRef  _live_refs[MAX_NATIVE_LIBS];
  static int         _live_count;

  // Takes _lock, which it holds until destroyed, then calls collect(ctx) and
  // visit(lib, tag) for every candidate whose library is still loaded, and
  // clears the candidates. On glibc it does so inside a dl_iterate_phdr()
  // walk, so _lock is always taken after the loader's dl_load_write_lock (see
  // libraryPatcher_linux.cpp). Walker-owned non-socket slots are written only
  // during a live visit; those libraries are not pinned and may be dlclose()d.
  // Pinned socket transactions own disjoint slots and do not use this walk.
  // (MallocHooker patches without a walk: it pins each library with
  // UnloadProtection while writing to it, and never restores.)
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
  static bool socket_library_patched_unlocked(const void* image_base);
  static void remember_socket_library_unlocked(const void* image_base);
  static void unpatch_socket_functions_unlocked(
      std::vector<SocketPatchedLibrary>& libraries_to_release);
  static void release_socket_libraries(
      std::vector<SocketPatchedLibrary>& libraries);
public:
  // True while native I/O hooks are installed; read by library refresh paths
  // to decide whether to re-patch after a new library is loaded.
  // Set to true after the first batch of libraries is patched in patch_socket_functions().
  // Libraries loaded after profiler start are picked up on the next refresh,
  // which calls install_socket_hooks() to patch them if _socket_active is true.
  // start()/stop() and the library refresher can observe this state from different
  // threads, so keep the flag atomic even though stop normally happens at JVM shutdown.
  static std::atomic<bool> _socket_active;
  static void initialize();
  static void patch_libraries();
  static void unpatch_libraries();
  static void patch_sigaction();
  // Owner starts reserve a generation and publish activation together under _lock.
  static bool patch_socket_functions(bool require_active = false,
                                     std::atomic<bool>* activating_owner = nullptr);
  static void unpatch_socket_functions();
  static bool unpatch_socket_functions_if_inactive();
#ifdef UNIT_TEST
  // Runs outside _lock at discovery/refresh boundaries for deterministic races.
  using SocketPatchObserverForTest = void (*)(const char* phase);
  static void setSocketPatchObserverForTest(SocketPatchObserverForTest observer);
  // Called under _lock after lookup; must not reenter the patcher or loader.
  // Return true to exercise production's missing-slot rollback.
  using SocketImportFailureForTest = bool (*)(CodeCache*, ImportId, size_t);
  static SocketImportFailureForTest exchangeSocketImportFailureForTest(
      SocketImportFailureForTest failure);
  static int patch_socket_import_for_test(CodeCache* lib, ImportId import_id,
                                          void* hook, const char* name,
                                          bool retain_library = false);
  static int socket_patch_count_for_test();
  static int socket_library_count_for_test();
  static SocketPatchTarget socket_patch_target_for_test(
      CodeCache* lib, const char* library_name, bool in_jdk_directory);
  static void* socket_hook_for_target_for_test(SocketPatchTarget target,
                                                int hook_index);
#endif
  // Called after a new library is loaded and the library list is refreshed.
  // No-op when native I/O hooks are not active.
  static void install_socket_hooks();
};

#else

class LibraryPatcher {
public:
  static void initialize() { }
  static void patch_libraries() { }
  static void unpatch_libraries() { }
  static void patch_sigaction() { }
  static bool patch_socket_functions(bool require_active = false,
                                     std::atomic<bool>* activating_owner = nullptr) {
    (void)require_active;
    (void)activating_owner;
    return false;
  }
  static void unpatch_socket_functions() { }
  static bool unpatch_socket_functions_if_inactive() {
    return false;
  }
  static void install_socket_hooks() { }
};

#endif

#endif // _LIBRARYPATCHER_H
