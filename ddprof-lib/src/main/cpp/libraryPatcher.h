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

// Patch libraries' imported function relocation slots. pthread_create entries
// (_patched_entries) use only _lib; _location and _func are meaningful for the
// other entry tables.
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
  SOCKET_PATCH_IBM_JCL_BRIDGE,
  SOCKET_PATCH_NETTY_NATIVE_EPOLL
};

const int SOCKET_BASE_TABLE_SIZE = MAX_NATIVE_LIBS * 2;
// Bounds the linear skip-set scan; a skip beyond it fails the installation closed.
const int SOCKET_SKIPPED_IMAGE_CAPACITY = 64;

// Several append-only caches can describe one live image; base and layout identify it.
typedef struct _socketSkippedImage {
  const void* _image_base;
  u64 _fingerprint;
} SocketSkippedImage;
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

// Uses libc cancellation cleanup, not a C++ destructor action across routine().
void* run_with_cleanup(void* (*routine)(void*), void* params,
                       void (*cleanup_fn)(void*), void* cleanup_arg);

class LibraryPatcher {
  friend class LibraryPatcherTestAccessor;
  // Patches and restores its malloc hooks with LiveLibraryWalks.
  friend class MallocHooker;

private:
  static SpinLock    _lock;
  // Set by initialize_persistent() (Profiler::init() and start()); enables the
  // pthread_create patching, which is never unpatched. Read by the Libraries
  // refresher thread, hence release/acquire.
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
  // Netty images rejected by an image-local failure. Guarded by _lock and cleared
  // with the socket patches, so they are retried by the next installation only.
  static SocketSkippedImage _socket_skipped_images[SOCKET_SKIPPED_IMAGE_CAPACITY];
  static int _socket_skipped_image_count;

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
  // MallocHooker also patches and restores its malloc hooks in walks.
  class LiveLibraryWalk {
  public:
    LiveLibraryWalk(LiveLibraryCollector collect, void* ctx, LiveLibraryVisitor visit);
    ~LiveLibraryWalk() { _lock.unlock(); }
    LiveLibraryWalk(const LiveLibraryWalk&) = delete;
    LiveLibraryWalk& operator=(const LiveLibraryWalk&) = delete;
  };

  static void add_live_candidate(CodeCache* lib, int tag);
  static int visit_loaded_object(struct dl_phdr_info* info, size_t size, void* data);
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
  static bool socket_image_skipped_unlocked(const CodeCache* lib);
  // Both return false only when the skip table is full.
  static bool skip_socket_image_unlocked(CodeCache* lib, const char* reason);
  static bool skip_socket_image(CodeCache* lib, u64 generation, bool require_active,
                                const char* reason);
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
  // Enables the persistent patches (pthread_create, sigaction). Idempotent;
  // called from Profiler::init() and from start(), which -agentpath sessions
  // reach without init(). They survive stop/start cycles and are never unpatched.
  static void initialize_persistent();
  static void patch_libraries();
  static void unpatch_recording_hooks();
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
  // Return true to report a missing slot: a Netty image is skipped before any
  // write; other images exercise production's missing-slot rollback.
  using SocketImportFailureForTest = bool (*)(CodeCache*, ImportId, size_t);
  static SocketImportFailureForTest exchangeSocketImportFailureForTest(
      SocketImportFailureForTest failure);
  // Return true to fail `step` ("pin" outside _lock, "writable" under it) for that image.
  using SocketImageFailureForTest = bool (*)(CodeCache*, const char* step);
  static SocketImageFailureForTest exchangeSocketImageFailureForTest(
      SocketImageFailureForTest failure);
  // Treats the libc original of hook_index as missing for later installs; -1 clears.
  static int exchangeSocketMissingOriginalForTest(int hook_index);
  static void fill_socket_skipped_images_for_test();
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
  static void initialize_persistent() { }
  static void patch_libraries() { }
  static void unpatch_recording_hooks() { }
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
