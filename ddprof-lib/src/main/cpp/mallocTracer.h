/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _MALLOCTRACER_H
#define _MALLOCTRACER_H

#include <stdint.h>
#include "codeCache.h"
#include "engine.h"
#include "event.h"
#include "mutex.h"
#include "pidController.h"

// Tracks a patched GOT slot for malloc hooks, enabling safe restoration.
struct MallocPatchEntry {
  CodeCache* _lib;      // Library containing the patched slot
  void** _location;     // Address of the GOT slot
  void* _hook;          // Hook written to the slot
  void* _orig;          // Slot content before patching (original, PLT stub or other interposer); the
                        // resolved original only if the entry of a stale hook was lost (orphan table full)
  bool _orig_resolved;  // _orig is the resolved original: patchSlot() can rebuild it without the entry
};

// Manages GOT-patching for malloc interception across all loaded native libraries.
// Unlike pthread_create hooks (persistent), malloc hooks are recording-specific
// and are unpatched on stop() to minimize overhead when not profiling.
class MallocHooker {
  friend class MallocHookerTestAccessor;

  private:
    // Guards the patching bookkeeping below off Linux. On Linux patching and
    // restoring run in LibraryPatcher walks, whose lock guards it instead.
    static Mutex _patch_lock;
    static int _patched_libs;
    static bool _initialized;

    // Imports patchLibrary() hooks (malloc, calloc, realloc, posix_memalign,
    // aligned_alloc); a static_assert there keeps it equal to its table.
    static const int NUM_HOOKED_IMPORTS = 5;
    // Each import has up to NUM_IMPORT_TYPES relocation slots per library
    static const int MAX_MALLOC_ENTRIES = NUM_HOOKED_IMPORTS * NUM_IMPORT_TYPES * MAX_NATIVE_LIBS;
    // Entries of libraries a restore pass could not visit stay at the front of
    // _entries (see keepUnrestoredEntries()). patchSlot() takes the original of a
    // slot still holding our hook from them; a later stop() restores one only if
    // its walk visits the entry's library again.
    static const int MAX_ORPHAN_ENTRIES = MAX_MALLOC_ENTRIES / 8;
    static MallocPatchEntry _entries[MAX_MALLOC_ENTRIES];
    static int _entry_count;
    // _entries[0, _kept_count) were kept by the last restore pass; later ones are
    // this recording's.
    static int _kept_count;

    static void detectNestedMalloc();
    static void patchImport(CodeCache* cc, ImportId id, void* hook_fn, void* orig_fn);
    static void patchSlot(CodeCache* cc, void** location, void* hook_fn, void* orig_fn);
    static void patchLibrary(CodeCache* cc);
    // Shared by the per-platform patchLibraries()/unpatchLibraries()
    // (mallocTracer_linux.cpp, mallocTracer_macos.cpp).
    static bool symbolsResolved();
    static void restoreSlot(const MallocPatchEntry& entry);
    static void sortEntriesByLibrary();
    // After a restore pass (restored entries have _lib == nullptr): keeps the
    // unrestored ones, up to MAX_ORPHAN_ENTRIES, so patchSlot() can recover the
    // true original of a slot that still holds our hook. Over the cap it drops
    // _orig_resolved entries first.
    static void keepUnrestoredEntries();

  public:
    // Returns true if symbols were successfully resolved.
    static bool initialize();
    static void patchLibraries();
    static void unpatchLibraries();
    static void installHooks();
};

class MallocTracer : public Engine {
  private:
    static volatile u64 _interval;
    static volatile u64 _bytes_until_sample;

    static u64 _configured_interval;
    static volatile u64 _sample_count;
    static volatile u64 _last_config_update_ts;
    static const int CONFIG_UPDATE_CHECK_PERIOD_SECS = 1;
    static const int TARGET_SAMPLES_PER_WINDOW = 100;

    static volatile bool _running;
    static PidController _pid;

    static u64 nextPoissonInterval();
    static bool shouldSample(size_t size);
    static void updateConfiguration(u64 events, double time_coefficient);

  public:
    const char* name() {
        return "MallocTracer";
    }

    Error start(Arguments& args);
    void stop();

    static inline bool running() {
        return __atomic_load_n(&_running, __ATOMIC_ACQUIRE);
    }

    static inline void installHooks() {
        MallocHooker::installHooks();
    }

    static void recordMalloc(void* address, size_t size, int tid);

    // Entry point for the malloc hooks (mallocTracer.cpp): gates on the
    // sampling decision before touching thread-local state.
    static void maybeRecord(void* ret, size_t size);
};

#endif // _MALLOCTRACER_H
