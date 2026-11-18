/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __APPLE__

#include "common.h"
#include "libraries.h"
#include "mallocTracer.h"
#include "signalSafety.h"
#include "mutex.h"
#include "symbols.h"

#include <dlfcn.h>
#include <string.h>

// UnloadProtection pins by name only. dladdr() (under dyld's lock) must find an
// image at minAddress() with the cache's path and, if recorded, LC_UUID, so a
// rebuild reloaded at the same base is left unhooked. Call it while pinned.
static bool isCurrentImage(const CodeCache* cc) {
    Dl_info info;
    if (cc->minAddress() == NO_MIN_ADDRESS || dladdr(cc->minAddress(), &info) == 0 ||
        info.dli_fbase != cc->minAddress() || info.dli_fname == NULL ||
        strcmp(info.dli_fname, cc->name()) != 0) {
        return false;
    }
    if (cc->imageFingerprint() != 0 &&
        Symbols::imageFingerprint(info.dli_fbase) != cc->imageFingerprint()) {
        TEST_LOG("MallocHooker: %s was reloaded at the same base as another build; left unhooked",
                 cc->name());
        return false;
    }
    return true;
}

// No loader walk on macOS: each library is pinned with UnloadProtection while
// it is patched or restored, and _patch_lock guards the bookkeeping. A library
// that is no longer loaded where its cache describes is skipped (isCurrentImage()).
void MallocHooker::patchLibraries() {
    DEBUG_ASSERT_NOT_IN_SIGNAL();
    // See mallocTracer_linux.cpp.
    if (!symbolsResolved()) return;

    MutexLocker ml(_patch_lock);
    // See mallocTracer_linux.cpp.
    if (!MallocTracer::running()) return;

    const CodeCacheArray& native_libs = Libraries::instance()->native_libs();
    int native_lib_count = native_libs.count();
    while (_patched_libs < native_lib_count) {
        CodeCache* cc = native_libs[_patched_libs++];

        UnloadProtection handle(cc);
        if (!handle.isValid() || !isCurrentImage(cc)) {
            TEST_LOG("MallocHooker::patchLibraries: skipping (not loaded) %s", cc->name());
            continue;
        }
        // A reload at the same address keeps this CodeCache, so its GOT may be
        // read-only again. (On Linux the walk does this.)
        cc->makeImportsWritable();
        patchLibrary(cc);
    }
}

void MallocHooker::unpatchLibraries() {
    DEBUG_ASSERT_NOT_IN_SIGNAL();
    MutexLocker ml(_patch_lock);

    TEST_LOG("MallocHooker::unpatchLibraries: restoring %d slot(s)", _entry_count);
    sortEntriesByLibrary();
    int i = 0;
    while (i < _entry_count) {
        CodeCache* lib = _entries[i]._lib;
        int run_end = i;
        while (run_end < _entry_count && _entries[run_end]._lib == lib) {
            run_end++;
        }

        UnloadProtection handle(lib);
        if (handle.isValid() && isCurrentImage(lib)) {
            lib->makeImportsWritable();
            for (int j = i; j < run_end; j++) {
                restoreSlot(_entries[j]);
            }
            for (int j = i; j < run_end; j++) {
                _entries[j]._lib = nullptr;  // restored
            }
        }
        i = run_end;
    }
    // Entries of an unvisited library are kept: see keepUnrestoredEntries().
    keepUnrestoredEntries();
    _patched_libs = 0;
}

#endif // __APPLE__
