/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cmath>
#include <dlfcn.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "codeCache.h"
#include "libraries.h"
#include "mallocTracer.h"
#include "os.h"
#include "pidController.h"
#include "profiler.h"
#include "symbols.h"
#include "tsc.h"
#include "vmEntry.h"

#ifdef __clang__
#  define NO_OPTIMIZE __attribute__((optnone))
#else
#  define NO_OPTIMIZE __attribute__((optimize("-fno-omit-frame-pointer,-fno-optimize-sibling-calls")))
#endif

#define SAVE_IMPORT(FUNC) \
    do { \
        void** _entry = lib->findImport(im_##FUNC); \
        if (_entry != NULL) _orig_##FUNC = (decltype(_orig_##FUNC))*_entry; \
    } while (0)

static void* (*_orig_malloc)(size_t);
static void (*_orig_free)(void*);
static void* (*_orig_calloc)(size_t, size_t);
static void* (*_orig_realloc)(void*, size_t);
static int (*_orig_posix_memalign)(void**, size_t, size_t);
static void* (*_orig_aligned_alloc)(size_t, size_t);

extern "C" void* malloc_hook(size_t size) {
    void* ret = _orig_malloc(size);
    if (MallocTracer::running() && ret && size) {
        MallocTracer::recordMalloc(ret, size);
    }
    return ret;
}

extern "C" void* calloc_hook(size_t num, size_t size) {
    void* ret = _orig_calloc(num, size);
    if (MallocTracer::running() && ret && num && size) {
        size_t total;
        if (__builtin_mul_overflow(num, size, &total)) {
            total = SIZE_MAX;
        }
        MallocTracer::recordMalloc(ret, total);
    }
    return ret;
}

// Make sure this is not optimized away (function-scoped -fno-optimize-sibling-calls)
extern "C" NO_OPTIMIZE
void* calloc_hook_dummy(size_t num, size_t size) {
    return _orig_calloc(num, size);
}

extern "C" void* realloc_hook(void* addr, size_t size) {
    void* ret = _orig_realloc(addr, size);
    if (MallocTracer::running() && ret != NULL && size > 0) {
        MallocTracer::recordMalloc(ret, size);
    }
    return ret;
}

extern "C" void free_hook(void* addr) {
    _orig_free(addr);
}

extern "C" int posix_memalign_hook(void** memptr, size_t alignment, size_t size) {
    int ret = _orig_posix_memalign(memptr, alignment, size);
    if (MallocTracer::running() && ret == 0 && memptr && *memptr && size) {
        MallocTracer::recordMalloc(*memptr, size);
    }
    return ret;
}

// Make sure this is not optimized away (function-scoped -fno-optimize-sibling-calls)
extern "C" NO_OPTIMIZE
int posix_memalign_hook_dummy(void** memptr, size_t alignment, size_t size) {
    return _orig_posix_memalign(memptr, alignment, size);
}

extern "C" void* aligned_alloc_hook(size_t alignment, size_t size) {
    void* ret = _orig_aligned_alloc(alignment, size);
    if (MallocTracer::running() && ret && size) {
        MallocTracer::recordMalloc(ret, size);
    }
    return ret;
}

volatile u64 MallocTracer::_interval;
volatile u64 MallocTracer::_bytes_until_sample;
u64 MallocTracer::_configured_interval;
volatile u64 MallocTracer::_sample_count;
volatile u64 MallocTracer::_last_config_update_ts;

Mutex MallocTracer::_patch_lock;
int MallocTracer::_patched_libs = 0;
bool MallocTracer::_initialized = false;
volatile bool MallocTracer::_running = false;
PidController MallocTracer::_pid(MallocTracer::TARGET_SAMPLES_PER_WINDOW,
    31, 511, 3, MallocTracer::CONFIG_UPDATE_CHECK_PERIOD_SECS, 15);

static pthread_t _current_thread;
static volatile bool _nested_malloc = false;
static volatile bool _nested_posix_memalign = false;

// Test if calloc() implementation calls malloc()
static void* nested_malloc_hook(size_t size) {
    if (pthread_self() == _current_thread) {
        _nested_malloc = true;
    }
    return _orig_malloc(size);
}

// Test if posix_memalign() implementation calls aligned_alloc()
static void* nested_aligned_alloc_hook(size_t alignment, size_t size) {
    if (pthread_self() == _current_thread) {
        _nested_posix_memalign = true;
    }
    return _orig_aligned_alloc(alignment, size);
}

// In some implementations, specifically on musl, calloc() calls malloc() internally,
// and posix_memalign() calls aligned_alloc(). Detect such cases to prevent double-accounting.
static void detectNestedMalloc() {
    if (_orig_malloc != NULL && _orig_calloc != NULL) {
        CodeCache* libc = Profiler::instance()->findLibraryByAddress((void*)_orig_calloc);
        if (libc != NULL) {
            libc->patchImport(im_malloc, (void*)nested_malloc_hook);

            _current_thread = pthread_self();
            free(_orig_calloc(1, 1));
            _current_thread = pthread_t(0);

            // Restore original malloc so libc doesn't carry the probe hook until patchLibraries() runs.
            libc->patchImport(im_malloc, (void*)_orig_malloc);
        }
    }

    if (_orig_posix_memalign != NULL && _orig_aligned_alloc != NULL) {
        CodeCache* libc = Profiler::instance()->findLibraryByAddress((void*)_orig_posix_memalign);
        if (libc != NULL) {
            libc->patchImport(im_aligned_alloc, (void*)nested_aligned_alloc_hook);

            _current_thread = pthread_self();
            void* pm_probe = NULL;
            _orig_posix_memalign(&pm_probe, sizeof(void*), sizeof(void*));
            _current_thread = pthread_t(0);
            if (pm_probe != NULL) _orig_free(pm_probe);

            // Restore original aligned_alloc so libc doesn't carry the probe hook.
            libc->patchImport(im_aligned_alloc, (void*)_orig_aligned_alloc);
        }
    }
}

// Call each intercepted function at least once to ensure its GOT entry is updated
static void resolveMallocSymbols() {
    static volatile intptr_t sink;

    void* p0 = malloc(1);
    void* p1 = realloc(p0, 2);
    if (p1 == NULL) {
        // realloc failed; p0 is still valid and must be freed explicitly.
        free(p0);
    }
    void* p2 = calloc(1, 1);
    void* p3 = aligned_alloc(sizeof(void*), sizeof(void*));
    void* p4 = NULL;
    if (posix_memalign(&p4, sizeof(void*), sizeof(void*)) == 0) free(p4);
    free(p3);
    free(p2);
    free(p1);

    sink = (intptr_t)p1 + (intptr_t)p2 + (intptr_t)p3 + (intptr_t)p4;
}

void MallocTracer::initialize() {
    CodeCache* lib = Profiler::instance()->findLibraryByAddress((void*)MallocTracer::initialize);
    if (lib == NULL) {
        return;
    }

    resolveMallocSymbols();

    SAVE_IMPORT(malloc);
    SAVE_IMPORT(free);
    SAVE_IMPORT(calloc);
    SAVE_IMPORT(realloc);
    SAVE_IMPORT(posix_memalign);
    SAVE_IMPORT(aligned_alloc);

    detectNestedMalloc();

    lib->mark(
        [](const char* s) -> bool {
            return strcmp(s, "malloc_hook") == 0
                || strcmp(s, "calloc_hook") == 0
                || strcmp(s, "calloc_hook_dummy") == 0
                || strcmp(s, "realloc_hook") == 0
                || strcmp(s, "free_hook") == 0
                || strcmp(s, "posix_memalign_hook") == 0
                || strcmp(s, "posix_memalign_hook_dummy") == 0
                || strcmp(s, "aligned_alloc_hook") == 0;
        },
        MARK_ASYNC_PROFILER);
}

// To avoid complexity in hooking and tracking reentrancy, a TLS-based approach is not used.
// Reentrant allocation calls would result in double-accounting. However, this does not impact
// the leak detector, as it correctly tracks memory as freed regardless of how many times
// recordMalloc is called with the same address.
void MallocTracer::patchLibraries() {
    MutexLocker ml(_patch_lock);

    const CodeCacheArray& native_libs = Libraries::instance()->native_libs();
    int native_lib_count = native_libs.count();

    while (_patched_libs < native_lib_count) {
        CodeCache* cc = native_libs[_patched_libs++];

        UnloadProtection handle(cc);
        if (!handle.isValid()) {
            continue;
        }

        if (_orig_malloc) cc->patchImport(im_malloc, (void*)malloc_hook);
        if (_orig_realloc) cc->patchImport(im_realloc, (void*)realloc_hook);
        if (_orig_free) cc->patchImport(im_free, (void*)free_hook);
        if (_orig_aligned_alloc) cc->patchImport(im_aligned_alloc, (void*)aligned_alloc_hook);

        // Use dummy hooks for functions that call another tracked function internally,
        // to prevent double-accounting. Dummy frames preserve the frame link to the caller.
        if (_orig_calloc) {
            cc->patchImport(im_calloc, _nested_malloc ? (void*)calloc_hook_dummy : (void*)calloc_hook);
        }
        if (_orig_posix_memalign) {
            cc->patchImport(im_posix_memalign, _nested_posix_memalign ? (void*)posix_memalign_hook_dummy : (void*)posix_memalign_hook);
        }
    }
}

u64 MallocTracer::nextPoissonInterval() {
    u64 s = TSC::ticks();
    s ^= s >> 12;
    s ^= s << 25;
    s ^= s >> 27;
    double u = (double)(s * 0x2545F4914F6CDD1DULL >> 11) / (double)(1ULL << 53);
    if (u < 1e-18) u = 1e-18;
    return (u64)((double)_interval * -log(u));
}

bool MallocTracer::shouldSample(size_t size) {
    if (_interval <= 1) return true;
    while (true) {
        u64 prev = _bytes_until_sample;
        if (size < prev) {
            if (__sync_bool_compare_and_swap(&_bytes_until_sample, prev, prev - size))
                return false;
        } else {
            u64 next = nextPoissonInterval();
            if (__sync_bool_compare_and_swap(&_bytes_until_sample, prev, next))
                return true;
        }
    }
}

void MallocTracer::updateConfiguration(u64 events, double time_coefficient) {
    double signal = _pid.compute(events, time_coefficient);
    int64_t new_interval = (int64_t)_interval - (int64_t)signal;
    if (new_interval < (int64_t)_configured_interval)
        new_interval = (int64_t)_configured_interval;
    if (new_interval > (int64_t)(1ULL << 40))
        new_interval = (int64_t)(1ULL << 40);
    _interval = (u64)new_interval;
}

void MallocTracer::recordMalloc(void* address, size_t size) {
    if (shouldSample(size)) {
        u64 current_interval = _interval;
        MallocEvent event;
        event._start_time = TSC::ticks();
        event._address = (uintptr_t)address;
        event._size = size;
        event._weight = (float)(size == 0 || current_interval <= 1
            ? 1.0
            : 1.0 / (1.0 - exp(-(double)size / (double)current_interval)));

        Profiler::instance()->recordSample(NULL, size, OS::threadId(), BCI_NATIVE_MALLOC, 0, &event);

        u64 current_samples = __sync_add_and_fetch(&_sample_count, 1);
        if ((current_samples % TARGET_SAMPLES_PER_WINDOW) == 0) {
            u64 now = OS::nanotime();
            u64 prev_ts = __atomic_load_n(&_last_config_update_ts, __ATOMIC_RELAXED);
            u64 time_diff = now - prev_ts;
            u64 check_period_ns = (u64)CONFIG_UPDATE_CHECK_PERIOD_SECS * 1000000000ULL;
            if (time_diff > check_period_ns) {
                if (__atomic_compare_exchange(&_last_config_update_ts, &prev_ts, &now,
                                              false, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)) {
                    __sync_fetch_and_add(&_sample_count, -current_samples);
                    updateConfiguration(current_samples,
                                        (double)check_period_ns / time_diff);
                }
            }
        }
    }
}

Error MallocTracer::start(Arguments& args) {
    _configured_interval = args._nativemem > 0 ? args._nativemem : 0;
    _interval = _configured_interval;
    _bytes_until_sample = _configured_interval > 1 ? nextPoissonInterval() : 0;
    _sample_count = 0;
    // Clear accumulated integral/derivative so a fresh session is not biased by
    // state from a prior one (relevant for tests that stop and restart the profiler).
    _pid.reset();
    __atomic_store_n(&_last_config_update_ts, OS::nanotime(), __ATOMIC_RELEASE);

    if (!_initialized) {
        initialize();
        _initialized = true;
    }

    if (_orig_malloc == NULL) {
        return Error("Failed to resolve malloc symbols; native memory profiling unavailable");
    }

    // Enable recording before patching so a concurrent dlopen() during patchLibraries()
    // sees running()==true and patches the new library via installHooks().
    // _orig_* pointers are already resolved in initialize(), so this is safe.
    _running = true;
    patchLibraries();

    return Error::OK;
}

void MallocTracer::stop() {
    // Ideally, we should reset original malloc entries, but it's not currently safe
    // in the view of library unloading. Consider using dl_iterate_phdr.
    _running = false;
}
