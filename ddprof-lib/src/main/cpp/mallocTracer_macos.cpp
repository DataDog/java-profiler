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

#include <mach-o/dyld.h>
#include <string.h>

// UnloadProtection pins a library by name only, so it also succeeds for a
// cache whose library was unloaded and the same path loaded at another
// address. Accept the cache only while dyld lists its path at its slide (the
// cache's text base). Call it while the library is pinned.
static bool isCurrentImage(const CodeCache* cc) {
    uint32_t images = _dyld_image_count();
    for (uint32_t i = 0; i < images; i++) {
        const char* name = _dyld_get_image_name(i);
        if (name != nullptr && strcmp(name, cc->name()) == 0 &&
            reinterpret_cast<const char*>(_dyld_get_image_vmaddr_slide(i)) == cc->textBase()) {
            return true;
        }
    }
    return false;
}

// No loader walk on macOS: each library is pinned with UnloadProtection while
// it is patched or restored, and _patch_lock guards the bookkeeping. A library
// that is no longer loaded at its cache's slide is skipped (isCurrentImage()).
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
    MutexLocker ml(_patch_lock);

    TEST_LOG("MallocHooker::unpatchLibraries: restoring %d slot(s)", _entry_count);
    sortEntriesByLibrary();
    int i = 0;
    while (i < _entry_count) {
        CodeCache* lib = _entries[i]._lib;
        int run_end = i;
        while (run_end < _entry_count && _entries[run_end]._lib == lib) run_end++;

        UnloadProtection handle(lib);
        if (handle.isValid() && isCurrentImage(lib)) {
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
