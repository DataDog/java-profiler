/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef LIBRARY_PATCHER_TEST_ACCESSOR_H
#define LIBRARY_PATCHER_TEST_ACCESSOR_H

#if defined(__linux__)

#include "codeCache.h"
#include "libraryPatcher.h"

#include <pthread.h>
#include <string.h>

// Friend of LibraryPatcher (libraryPatcher.h): the internals the patcher tests
// need, shared by the gtest binaries that include it.
class LibraryPatcherTestAccessor {
public:
  static const void* selfAnchor() { return LibraryPatcher::self_anchor(); }

  static bool isProfilerLibrary(CodeCache* lib) {
    return LibraryPatcher::is_profiler_library(lib);
  }

  static void patchLibraryUnlocked(CodeCache* lib) {
    LibraryPatcher::patch_library_unlocked(lib);
  }

  static int patchedCount() { return LibraryPatcher::_pthread_create.size; }
  static void setPatchedCount(int count) { LibraryPatcher::_pthread_create.size = count; }

  // Whether the entry's last visit left a slot unhooked, or -1 if the library
  // has no entry.
  static int entryPending(CodeCache* lib) {
    for (int index = 0; index < LibraryPatcher::_pthread_create.size; index++) {
      if (LibraryPatcher::_pthread_create.entries[index].lib == lib) {
        return LibraryPatcher::_pthread_create.entries[index].pending;
      }
    }
    return -1;
  }

  static void* loaderPthreadCreate() { return LibraryPatcher::_loader_pthread_create; }
  static void* nextPthreadCreate() { return LibraryPatcher::_next_pthread_create; }

  // Stand in for the loader's two bindings (a preloaded interposer, say).
  static void setLoaderPthreadCreate(void* func) { LibraryPatcher::_loader_pthread_create = func; }
  static void setNextPthreadCreate(void* func) { LibraryPatcher::_next_pthread_create = func; }

  static void* pltBinding(void* global, void* next) { return LibraryPatcher::plt_binding(global, next); }

  // Drops the patch table without writing the saved originals back, unlike
  // unpatch_recording_hooks(). Tests patch GOT slots that live in the test body's
  // frame, so by the time a fixture could restore them the addresses are dead;
  // forgetting the entries is what keeps one test from reaching into the next.
  static void forgetPatchTable() {
    memset(&LibraryPatcher::_pthread_create, 0, sizeof(LibraryPatcher::_pthread_create));
    LibraryPatcher::_loader_pthread_create = reinterpret_cast<void*>(&pthread_create);
    LibraryPatcher::_next_pthread_create = nullptr;
    LibraryPatcher::_initialized.store(false);
  }
};

#endif // __linux__

#endif // LIBRARY_PATCHER_TEST_ACCESSOR_H
