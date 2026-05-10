/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _MALLOCTRACER_H
#define _MALLOCTRACER_H

#include <stdint.h>
#include "engine.h"
#include "event.h"
#include "mutex.h"
#include "pidController.h"

// Manages GOT-patching for malloc interception across all loaded native libraries.
class MallocHooker {
  private:
    static Mutex _patch_lock;
    static int _patched_libs;
    static bool _initialized;
    static void* _calloc_hook_fn;
    static void* _posix_memalign_hook_fn;

    static void detectNestedMalloc();

  public:
    // Returns true if symbols were successfully resolved.
    static bool initialize();
    static void patchLibraries();
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

    static void recordMalloc(void* address, size_t size);
};

#endif // _MALLOCTRACER_H
