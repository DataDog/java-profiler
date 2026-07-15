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

const int SOCKET_BASE_TABLE_SIZE = MAX_NATIVE_LIBS * 2;

class LibraryPatcher {
private:
  static SpinLock    _lock;
  static const char* _profiler_name;
  static PatchEntry  _patched_entries[MAX_NATIVE_LIBS];
  static int         _size;
  static bool        _patch_pthread_create;

  // Separate tracking for sigaction patches
  static PatchEntry  _sigaction_entries[MAX_NATIVE_LIBS];
  static int         _sigaction_size;

  // Separate tracking for native I/O patches.
  // Each library can contribute any number of retained import slots per I/O hook.
  static std::vector<SocketPatchEntry> _socket_entries;
  static std::vector<SocketPatchedLibrary> _socket_libraries;
  static const void* _socket_bases[SOCKET_BASE_TABLE_SIZE];

  static void patch_library_unlocked(CodeCache* lib);
  static void patch_pthread_create();
  static void patch_pthread_setspecific();
  static void patch_sigaction_in_library(CodeCache* lib);
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
  static bool patch_socket_functions(bool require_active = false);
  static void unpatch_socket_functions();
  static bool unpatch_socket_functions_if_inactive();
#ifdef UNIT_TEST
  static int patch_socket_import_for_test(CodeCache* lib, ImportId import_id,
                                          void* hook, const char* name,
                                          bool retain_library = false);
  static int socket_patch_count_for_test();
  static int socket_library_count_for_test();
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
  static bool patch_socket_functions(bool require_active = false) {
    (void)require_active;
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
