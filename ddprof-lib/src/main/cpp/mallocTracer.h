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
  void* _orig;          // Original function pointer before patching
};

// Manages GOT-patching for malloc interception across all loaded native libraries.
// Unlike pthread_create hooks (persistent), malloc hooks are recording-specific
// and are unpatched on stop() to minimize overhead when not profiling.
class MallocHooker {
  private:
    // Guards the patching bookkeeping below off Linux. On Linux patching and
    // restoring run in LibraryPatcher walks, whose lock guards it instead.
    static Mutex _patch_lock;
    static int _patched_libs;
    static bool _initialized;

    // Up to 5 imports per library (malloc, calloc, realloc, posix_memalign,
    // aligned_alloc), each with up to NUM_IMPORT_TYPES relocation slots
    static const int MAX_MALLOC_ENTRIES = 5 * NUM_IMPORT_TYPES * MAX_NATIVE_LIBS;
    static MallocPatchEntry _entries[MAX_MALLOC_ENTRIES];
    static int _entry_count;

    static void detectNestedMalloc();
    static void patchImport(CodeCache* cc, ImportId id, void* hook_fn, void* orig_fn);
    static void patchSlot(CodeCache* cc, void** location, void* hook_fn, void* orig_fn);
    static void patchLibrary(CodeCache* cc);
    static void dropRestoredEntries();

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
