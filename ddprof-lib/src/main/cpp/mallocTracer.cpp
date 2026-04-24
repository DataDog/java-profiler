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

// Inline helper to avoid repeating the running+ret+size guard in each hook.
static inline void maybeRecord(void* ret, size_t size) {
    if (MallocTracer::running() && ret && size) {
        MallocTracer::recordMalloc(ret, size);
    }
}

extern "C" void* malloc_hook(size_t size) {
    void* ret = _orig_malloc(size);
    maybeRecord(ret, size);
    return ret;
}

extern "C" void* calloc_hook(size_t num, size_t size) {
    void* ret = _orig_calloc(num, size);
    // ret != NULL guarantees no overflow per POSIX, so num * size is safe.
    if (MallocTracer::running() && ret && num && size) {
        MallocTracer::recordMalloc(ret, num * size);
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
    maybeRecord(ret, size);
    return ret;
}

volatile u64 MallocTracer::_interval;
volatile u64 MallocTracer::_bytes_until_sample;
u64 MallocTracer::_configured_interval;
volatile u64 MallocTracer::_sample_count;
volatile u64 MallocTracer::_last_config_update_ts;
volatile bool MallocTracer::_running = false;
PidController MallocTracer::_pid(MallocTracer::TARGET_SAMPLES_PER_WINDOW,
    31, 511, 3, MallocTracer::CONFIG_UPDATE_CHECK_PERIOD_SECS, 15);

Mutex MallocHooker::_patch_lock;
int MallocHooker::_patched_libs = 0;
bool MallocHooker::_initialized = false;
void* MallocHooker::_calloc_hook_fn = nullptr;
void* MallocHooker::_posix_memalign_hook_fn = nullptr;

// xoroshiro128+ PRNG state — shared, relaxed atomics.
// Benign races are acceptable: occasional duplicate output is harmless
// for a sampling PRNG and thread_local cannot be used on the malloc path.
static u64 _xo_state[2];

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
void MallocHooker::detectNestedMalloc() {
    if (_orig_malloc != NULL && _orig_calloc != NULL) {
        CodeCache* libc = Libraries::instance()->findLibraryByAddress((void*)_orig_calloc);
        if (libc != NULL) {
            UnloadProtection handle(libc);
            if (handle.isValid()) {
                libc->patchImport(im_malloc, (void*)nested_malloc_hook);

                _current_thread = pthread_self();
                free(_orig_calloc(1, 1));
                _current_thread = pthread_t(0);

                // Restore original malloc so libc doesn't carry the probe hook until patchLibraries() runs.
                libc->patchImport(im_malloc, (void*)_orig_malloc);
            }
        }
    }

    if (_orig_posix_memalign != NULL && _orig_aligned_alloc != NULL) {
        CodeCache* libc = Libraries::instance()->findLibraryByAddress((void*)_orig_posix_memalign);
        if (libc != NULL) {
            UnloadProtection handle(libc);
            if (handle.isValid()) {
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

// Seed xoroshiro128+ state from a 64-bit value using splitmix64.
static void splitmix64_seed(u64 seed) {
    seed += 0x9e3779b97f4a7c15ULL;
    seed = (seed ^ (seed >> 30)) * 0xbf58476d1ce4e5b9ULL;
    seed = (seed ^ (seed >> 27)) * 0x94d049bb133111ebULL;
    __atomic_store_n(&_xo_state[0], seed ^ (seed >> 31), __ATOMIC_RELAXED);
    seed += 0x9e3779b97f4a7c15ULL;
    seed = (seed ^ (seed >> 30)) * 0xbf58476d1ce4e5b9ULL;
    seed = (seed ^ (seed >> 27)) * 0x94d049bb133111ebULL;
    __atomic_store_n(&_xo_state[1], seed ^ (seed >> 31), __ATOMIC_RELAXED);
}

bool MallocHooker::initialize() {
    if (_initialized) return _orig_malloc != NULL;

    CodeCache* lib = Libraries::instance()->findLibraryByAddress((void*)MallocTracer::recordMalloc);
    if (lib == NULL) {
        _initialized = true;
        return false;
    }

    resolveMallocSymbols();

    SAVE_IMPORT(malloc);
    SAVE_IMPORT(free);
    SAVE_IMPORT(calloc);
    SAVE_IMPORT(realloc);
    SAVE_IMPORT(posix_memalign);
    SAVE_IMPORT(aligned_alloc);

    detectNestedMalloc();

    // Pre-compute hook pointers so patchLibraries() avoids repeated conditionals.
    _calloc_hook_fn = _nested_malloc ? (void*)calloc_hook_dummy : (void*)calloc_hook;
    _posix_memalign_hook_fn = _nested_posix_memalign ? (void*)posix_memalign_hook_dummy : (void*)posix_memalign_hook;

    lib->mark(
        [](const char* s) -> bool {
            return strcmp(s, "malloc_hook") == 0
                || strcmp(s, "calloc_hook") == 0
                || strcmp(s, "calloc_hook_dummy") == 0
                || strcmp(s, "realloc_hook") == 0
                || strcmp(s, "posix_memalign_hook") == 0
                || strcmp(s, "posix_memalign_hook_dummy") == 0
                || strcmp(s, "aligned_alloc_hook") == 0;
        },
        MARK_ASYNC_PROFILER);

    splitmix64_seed(TSC::ticks());
    _initialized = true;
    return _orig_malloc != NULL;
}

// To avoid complexity in hooking and tracking reentrancy, a TLS-based approach is not used.
// Reentrant allocation calls would result in double-accounting. However, this does not impact
// the leak detector, as it correctly tracks memory as freed regardless of how many times
// recordMalloc is called with the same address.
void MallocHooker::patchLibraries() {
    // If initialize() hasn't resolved _orig_malloc yet, advancing _patched_libs here
    // would consume library slots without patching them, causing a later real call
    // (from MallocTracer::start) to find _patched_libs == native_lib_count and skip
    // all libraries. This happens when dlopen_hook fires during a non-nativemem session.
    if (_orig_malloc == NULL) return;

    MutexLocker ml(_patch_lock);

    const CodeCacheArray& native_libs = Libraries::instance()->native_libs();
    int native_lib_count = native_libs.count();

    // _patched_libs is intentionally monotonic: hooks are permanent and cannot be
    // uninstalled safely (library unloading races). On profiler restart, only
    // newly-loaded libraries need patching.
    TEST_LOG("MallocHooker::patchLibraries: _patched_libs=%d native_lib_count=%d _orig_malloc=%p",
             _patched_libs, native_lib_count, (void*)_orig_malloc);
    while (_patched_libs < native_lib_count) {
        CodeCache* cc = native_libs[_patched_libs++];

        UnloadProtection handle(cc);
        if (!handle.isValid()) {
            TEST_LOG("MallocHooker::patchLibraries: skipping (invalid handle) %s", cc->name());
            continue;
        }

        TEST_LOG("MallocHooker::patchLibraries: patching %s has_malloc=%d",
                 cc->name(), cc->findImport(im_malloc) != nullptr);
        if (_orig_malloc) cc->patchImport(im_malloc, (void*)malloc_hook);
        if (_orig_realloc) cc->patchImport(im_realloc, (void*)realloc_hook);
        if (_orig_aligned_alloc) cc->patchImport(im_aligned_alloc, (void*)aligned_alloc_hook);
        if (_orig_calloc) cc->patchImport(im_calloc, _calloc_hook_fn);
        if (_orig_posix_memalign) cc->patchImport(im_posix_memalign, _posix_memalign_hook_fn);
    }
}

void MallocHooker::installHooks() {
    patchLibraries();
}

static inline u64 xo_rotl(u64 x, int k) {
    return (x << k) | (x >> (64 - k));
}

u64 MallocTracer::nextPoissonInterval() {
    // xoroshiro128+ — relaxed atomics tolerate benign races on the shared state.
    u64 s0 = __atomic_load_n(&_xo_state[0], __ATOMIC_RELAXED);
    u64 s1 = __atomic_load_n(&_xo_state[1], __ATOMIC_RELAXED);
    u64 result = s0 + s1;
    s1 ^= s0;
    __atomic_store_n(&_xo_state[0], xo_rotl(s0, 55) ^ s1 ^ (s1 << 14), __ATOMIC_RELAXED);
    __atomic_store_n(&_xo_state[1], xo_rotl(s1, 36), __ATOMIC_RELAXED);
    double u = (double)(result >> 11) / (double)(1ULL << 53);
    if (u < 1e-18) u = 1e-18;
    return (u64)(__atomic_load_n(&_interval, __ATOMIC_ACQUIRE) * -log(u));
}

bool MallocTracer::shouldSample(size_t size) {
    if (__atomic_load_n(&_interval, __ATOMIC_ACQUIRE) <= 1) return true;
    while (true) {
        u64 prev = __atomic_load_n(&_bytes_until_sample, __ATOMIC_RELAXED);
        if (size < prev) {
            if (__atomic_compare_exchange_n(&_bytes_until_sample, &prev, prev - size,
                                            false, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED))
                return false;
        } else {
            u64 next = nextPoissonInterval();
            if (__atomic_compare_exchange_n(&_bytes_until_sample, &prev, next,
                                            false, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED))
                return true;
        }
    }
}

void MallocTracer::updateConfiguration(u64 events, double time_coefficient) {
    double signal = _pid.compute(events, time_coefficient);
    int64_t new_interval = (int64_t)__atomic_load_n(&_interval, __ATOMIC_ACQUIRE) - (int64_t)signal;
    if (new_interval < (int64_t)_configured_interval)
        new_interval = (int64_t)_configured_interval;
    if (new_interval > (int64_t)(1ULL << 40))
        new_interval = (int64_t)(1ULL << 40);
    __atomic_store_n(&_interval, (u64)new_interval, __ATOMIC_RELEASE);
}

void MallocTracer::recordMalloc(void* address, size_t size) {
    if (shouldSample(size)) {
        u64 current_interval = __atomic_load_n(&_interval, __ATOMIC_ACQUIRE);
        MallocEvent event;
        event._start_time = TSC::ticks();
        event._address = (uintptr_t)address;
        event._size = size;
        // _interval == 0 means sample every allocation; weight is 1.0.
        if (size == 0 || current_interval <= 1) {
            event._weight = 1.0f;
        } else {
            event._weight = (float)(1.0 / (1.0 - exp(-(double)size / (double)current_interval)));
        }

        Profiler::instance()->recordSample(NULL, size, OS::threadId(), BCI_NATIVE_MALLOC, 0, &event);

        u64 current_samples = __atomic_add_fetch(&_sample_count, 1, __ATOMIC_RELAXED);
        if ((current_samples % TARGET_SAMPLES_PER_WINDOW) == 0) {
            u64 now = OS::nanotime();
            u64 prev_ts = __atomic_load_n(&_last_config_update_ts, __ATOMIC_ACQUIRE);
            u64 time_diff = now - prev_ts;
            u64 check_period_ns = (u64)CONFIG_UPDATE_CHECK_PERIOD_SECS * 1000000000ULL;
            if (time_diff > check_period_ns) {
                if (__atomic_compare_exchange_n(&_last_config_update_ts, &prev_ts, now,
                                               false, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)) {
                    __atomic_fetch_sub(&_sample_count, current_samples, __ATOMIC_RELEASE);
                    updateConfiguration(current_samples,
                                        (double)check_period_ns / time_diff);
                }
            }
        }
    }
}

Error MallocTracer::start(Arguments& args) {
    _configured_interval = args._nativemem > 0 ? args._nativemem : 0;
    __atomic_store_n(&_interval, _configured_interval, __ATOMIC_RELEASE);
    __atomic_store_n(&_bytes_until_sample,
                     _configured_interval > 1 ? nextPoissonInterval() : 0,
                     __ATOMIC_RELEASE);
    __atomic_store_n(&_sample_count, (u64)0, __ATOMIC_RELEASE);
    // Clear accumulated integral/derivative so a fresh session is not biased by
    // state from a prior one (relevant for tests that stop and restart the profiler).
    _pid.reset();
    __atomic_store_n(&_last_config_update_ts, OS::nanotime(), __ATOMIC_RELEASE);

    // initialize() is idempotent and returns false when symbol resolution fails.
    if (!MallocHooker::initialize()) {
        return Error("Failed to resolve malloc symbols; native memory profiling unavailable");
    }

    // Enable recording before patching so a concurrent dlopen() during patchLibraries()
    // sees running()==true and patches the new library via installHooks().
    // _orig_* pointers are already resolved in initialize(), so this is safe.
    __atomic_store_n(&_running, true, __ATOMIC_RELEASE);
    MallocHooker::patchLibraries();

    return Error::OK;
}

void MallocTracer::stop() {
    // Ideally, we should reset original malloc entries, but it's not currently safe
    // in the view of library unloading. Consider using dl_iterate_phdr.
    __atomic_store_n(&_running, false, __ATOMIC_RELEASE);
}
