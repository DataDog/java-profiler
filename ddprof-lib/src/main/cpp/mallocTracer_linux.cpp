/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __linux__

#include "common.h"
#include "libraries.h"
#include "libraryPatcher.h"
#include "mallocTracer.h"

// Patching and restoring run inside a LibraryPatcher::LiveLibraryWalk, which
// writes only through libraries still mapped as the image their CodeCache saw.
// Its _lock guards _entries/_entry_count/_patched_libs here: no dlopen() & co.
void MallocHooker::patchLibraries() {
    // Defensive guard: the malloc symbols are resolved by initialize(), which runs in
    // MallocTracer::start() before _running is set and this path is reached.
    // Guards against stale or unexpected direct calls.
    if (!symbolsResolved()) return;

    LibraryPatcher::LiveLibraryWalk walk(
        [](void*) {
            // A refresher that saw running() before stop() may get here after
            // stop()'s restore walk, which this walk serializes with: do not
            // re-hook then.
            if (!MallocTracer::running()) return;
            const CodeCacheArray& native_libs = Libraries::instance()->native_libs();
            int native_lib_count = native_libs.count();
            TEST_LOG("MallocHooker::patchLibraries: _patched_libs=%d native_lib_count=%d",
                     _patched_libs, native_lib_count);
            // A library that is no longer loaded, or whose image was replaced,
            // is not visited and stays unpatched for this recording.
            while (_patched_libs < native_lib_count) {
                CodeCache* cc = native_libs[_patched_libs++];
                if (cc != nullptr) {
                    LibraryPatcher::add_live_candidate(cc, 0);
                }
            }
        },
        nullptr,
        [](CodeCache* lib, int) { patchLibrary(lib); });
}

void MallocHooker::unpatchLibraries() {
    LibraryPatcher::LiveLibraryWalk walk(
        [](void*) {
            TEST_LOG("MallocHooker::unpatchLibraries: restoring %d slot(s)", _entry_count);
            sortEntriesByLibrary();
            // One candidate per library: the first entry of its run.
            for (int i = 0; i < _entry_count; i++) {
                if (i == 0 || _entries[i]._lib != _entries[i - 1]._lib) {
                    LibraryPatcher::add_live_candidate(_entries[i]._lib, i);
                }
            }
        },
        nullptr,
        [](CodeCache* lib, int first) {
            for (int i = first; i < _entry_count && _entries[i]._lib == lib; i++) {
                restoreSlot(_entries[i]);
            }
            // Mark them restored only after the run, which is keyed on _lib.
            for (int i = first; i < _entry_count && _entries[i]._lib == lib; i++) {
                _entries[i]._lib = nullptr;
            }
        });
    // Still under the walk's lock. Entries the walk did not visit are kept: a
    // slot may still hold our hook, and patchSlot() needs its true original.
    keepUnrestoredEntries();
    // Every library is patched again, identity-checked, on the next start().
    _patched_libs = 0;
}

#endif // __linux__
