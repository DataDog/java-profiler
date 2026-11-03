/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __APPLE__

#include "common.h"
#include "libraries.h"
#include "mallocTracer.h"
#include "mutex.h"
#include "symbols.h"

// No loader walk on macOS: each library is pinned with UnloadProtection while
// it is patched or restored, and _patch_lock guards the bookkeeping. A library
// that is no longer loaded fails the pin and is skipped.
void MallocHooker::patchLibraries() {
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
        if (!handle.isValid()) {
            TEST_LOG("MallocHooker::patchLibraries: skipping (invalid handle) %s", cc->name());
            continue;
        }
        // A reload at the same address keeps this CodeCache, so its GOT may be
        // read-only again. (On Linux the walk does this.)
        cc->makeImportsWritable();
        patchLibrary(cc);
    }
}

void MallocHooker::unpatchLibraries() {
    MutexLocker ml(_patch_lock);

    TEST_LOG("MallocHooker::unpatchLibraries: restoring %d slot(s)", _entry_count);
    sortEntriesByLibrary();
    int i = 0;
    while (i < _entry_count) {
        CodeCache* lib = _entries[i]._lib;
        int run_end = i;
        while (run_end < _entry_count && _entries[run_end]._lib == lib) run_end++;

        UnloadProtection handle(lib);
        if (handle.isValid()) {
            lib->makeImportsWritable();
            for (int j = i; j < run_end; j++) {
                restoreSlot(_entries[j]);
            }
        }
        i = run_end;
    }
    _entry_count = 0;
    _patched_libs = 0;
}

#endif // __APPLE__
