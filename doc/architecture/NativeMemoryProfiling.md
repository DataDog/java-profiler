# Native Memory Allocation Profiling

## Overview

The native memory profiler tracks heap allocations made through the C standard
library (`malloc`, `calloc`, `realloc`, `posix_memalign`, `aligned_alloc`). It
instruments these functions at the GOT (Global Offset Table) level so that every
intercepted call is accounted for without modifying application source code or
requiring a custom allocator. The `free` function is also hooked (to forward calls
correctly through the GOT) but free events are not recorded.

Sampled allocation events carry a full Java + native stack trace and are emitted as
`profiler.Malloc` JFR events.

The feature is activated by passing `nativemem=<interval>` to the profiler, where
`<interval>` is the byte-sampling interval (e.g. `nativemem=524288` samples roughly
one event per 512 KiB allocated). Passing `nativemem=0` records every allocation.

---

## Component Map

```
  Application code
        │  malloc() / calloc() / realloc() / free() / …
        ▼
  ┌─────────────┐  GOT patch   ┌──────────────────────────┐
  │  libc / musl│ ◄────────── │  malloc_hook / free_hook  │  mallocTracer.cpp
  └─────────────┘             │  calloc_hook / …          │
                              └────────────┬─────────────┘
                                           │ recordMalloc
                                           ▼
                              ┌──────────────────────────┐
                              │  MallocTracer::           │  mallocTracer.cpp/h
                              │  shouldSample()           │
                              │  recordSample() ──────►  │  profiler.cpp
                              └────────────┬─────────────┘
                                           │ walkVM (CSTACK_VM)
                                           ▼
                              ┌──────────────────────────┐
                              │  JFR buffer               │  flightRecorder.cpp
                              │  profiler.Malloc          │
                              └──────────────────────────┘
```

---

## GOT Patching

The profiler redirects allocator calls by writing hook function addresses directly
into the importing library's GOT. This is cheaper than `LD_PRELOAD` (no process
restart) and works for libraries loaded at any time.

### Import IDs

`codeCache.h` defines an `ImportId` enum with one entry per hooked symbol:

```
im_malloc, im_calloc, im_realloc, im_free, im_posix_memalign, im_aligned_alloc
```

`CodeCache::patchImport(ImportId, void*)` walks the library's PLT/GOT and overwrites
the matching entry.

### Hook signatures

Each hook calls the saved original function first, then records the event:

| Hook | Calls | Records |
|------|-------|---------|
| `malloc_hook(size)` | `_orig_malloc(size)` | `recordMalloc(ret, size)` if `ret != NULL && size != 0` |
| `calloc_hook(num, size)` | `_orig_calloc(num, size)` | `recordMalloc(ret, num*size)` if `ret != NULL` |
| `realloc_hook(addr, size)` | `_orig_realloc(addr, size)` | `recordMalloc(ret, size)` if `ret != NULL && size > 0` |
| `free_hook(addr)` | `_orig_free(addr)` | — (forwards only) |
| `posix_memalign_hook(…)` | `_orig_posix_memalign(…)` | `recordMalloc(*memptr, size)` if `ret == 0` |
| `aligned_alloc_hook(align, size)` | `_orig_aligned_alloc(align, size)` | `recordMalloc(ret, size)` if `ret != NULL` |

---

## Initialization Sequence

`MallocTracer::start()` (called once per profiler session) runs:

1. **`resolveMallocSymbols()`** — calls each intercepted function at least once so
   the profiler library's own PLT stubs are resolved by the dynamic linker. This
   ensures that subsequent `SAVE_IMPORT` reads get the real libc function pointers
   rather than the PLT resolver.

2. **`SAVE_IMPORT(func)`** — reads the resolved GOT entry for each symbol from the
   profiler library's own import table and stores it in the corresponding
   `_orig_<func>` static pointer.

3. **`detectNestedMalloc()`** — probes whether the platform's `calloc` implementation
   calls `malloc` internally (as musl does). If so, `calloc_hook` and
   `posix_memalign_hook` are replaced with dummy variants (`calloc_hook_dummy`,
   `posix_memalign_hook_dummy`) that forward to the originals without recording, to
   prevent double-accounting. The dummy hooks preserve the caller frame pointer so
   that the actual call site is not obscured.

4. **`patchLibraries()`** — iterates over all currently loaded native libraries and
   writes the hook addresses into each library's GOT, under `_patch_lock`.
   `_patched_libs` is a monotonic counter so that already-patched libraries are
   skipped on subsequent calls.

`_initialized` is set to `true` after the first successful `initialize()` call.
`patchLibraries()` is called again on every subsequent `start()` to pick up any
libraries loaded between profiler sessions.

---

## Dynamic Library Handling

When the application calls `dlopen`, the profiler's `dlopen_hook` (installed as a
GOT hook for `dlopen`) calls `MallocTracer::installHooks()` after the library is
loaded:

```cpp
// profiler.cpp
void* Profiler::dlopen_hook(const char* filename, int flags) {
    void* result = dlopen(filename, flags);
    if (result != NULL) {
        Libraries::instance()->updateSymbols(false);
        MallocTracer::installHooks();
    }
    return result;
}
```

`installHooks()` calls `patchLibraries()` only if `_running` is `true`, so newly
loaded libraries are automatically hooked without requiring a profiler restart.

---

## Sampling

Allocation recording uses Poisson-interval sampling via `MallocTracer::shouldSample()`:

```cpp
// mallocTracer.cpp — lock-free CAS loop with Poisson jitter
static bool shouldSample(size_t size) {
    if (_interval <= 1) return true;         // nativemem=0: record every allocation
    while (true) {
        u64 prev = _bytes_until_sample;
        if (prev > size) {
            if (__sync_bool_compare_and_swap(&_bytes_until_sample, prev, prev - size))
                return false;
        } else {
            if (__sync_bool_compare_and_swap(&_bytes_until_sample, prev, nextPoissonInterval()))
                return true;
        }
    }
}
```

`_bytes_until_sample` is a shared volatile counter decremented by each allocation's
size. When exhausted, a new Poisson-distributed interval is generated via
`nextPoissonInterval()` (using `-interval * ln(uniform_random)`), providing random
jitter that avoids synchronization artifacts. Multiple threads compete via CAS so no
mutex is needed.

A PID controller (`updateConfiguration()`) periodically adjusts `_interval` to
maintain approximately `TARGET_SAMPLES_PER_WINDOW` (100) samples per second.

---

## Stack Trace Capture

### Why `CSTACK_VM` is needed

The malloc hooks execute on the calling thread with no signal context (`ucontext ==
NULL`). Native stack unwinding via frame pointers or DWARF requires a signal context
as the starting point, so neither `CSTACK_DEFAULT` nor `CSTACK_FP` can produce
useful traces for malloc events.

`CSTACK_VM` starts from `__builtin_return_address` for the initial frame and walks
native frames via DWARF. It then uses HotSpot's `JavaFrameAnchor` (lastJavaPC /
lastJavaSP / lastJavaFP) to transition from native to Java frames. This works
correctly from inside a malloc hook because the anchor is set whenever the JVM has
transitioned from Java to native.

### Default stack mode

`CSTACK_DEFAULT` is the initial default (`arguments.h`). At profiler start,
`profiler.cpp` promotes it to `CSTACK_VM` when VMStructs are available on the
platform. If VMStructs are not available, it stays at `CSTACK_DEFAULT`:

```cpp
} else if (_cstack == CSTACK_VM) {
    if (!VMStructs::hasStackStructs()) {
        _cstack = CSTACK_DEFAULT;
        Log::warn("VMStructs stack walking is not supported …");
    }
}
```

### Code path in `recordSample`

```cpp
// profiler.cpp — stack walking for malloc events
if (event_type == BCI_NATIVE_MALLOC && _cstack >= CSTACK_VM) {
    // walkVM walks native frames via DWARF/FP and, when native unwinding
    // fails, falls back to the JavaFrameAnchor to reach Java frames.
    int vm_frames = StackWalker::walkVM(ucontext /*NULL*/, frames + num_frames,
                                        max_remaining, _features,
                                        eventTypeFromBCI(event_type),
                                        lock_index, &truncated);
    num_frames += vm_frames;
}
```

`getNativeTrace` returns 0 immediately for `_cstack >= CSTACK_VM` (line 316), so
native frames from `walkFP`/`walkDwarf` are not collected — `walkVM` is the sole
source of both native and Java frames for malloc events.

---

## JFR Event Format

A single event type is defined in `jfrMetadata.cpp` under the
`Java Virtual Machine / Native Memory` category:

### `profiler.Malloc` (`T_MALLOC`)

| Field | Type | Description |
|-------|------|-------------|
| `startTime` | `long` (ticks) | TSC timestamp of the allocation |
| `eventThread` | thread ref | Thread that performed the allocation |
| `stackTrace` | stack trace ref | Call stack at the allocation site |
| `address` | `long` (address) | Returned pointer value |
| `size` | `long` (bytes) | Requested allocation size |
| `weight` | `float` | Statistical sample weight based on Poisson sampling probability |

Events are written by `Recording::recordMallocSample()` in `flightRecorder.cpp`:

```cpp
buf->putVar64(T_MALLOC);
buf->putVar64(event->_start_time);
buf->putVar32(tid);
buf->putVar64(call_trace_id);
buf->putVar64(event->_address);
buf->putVar64(event->_size);
buf->putFloat(event->_weight);
writeContext(buf, Contexts::get());
```

---

## Concurrency and Thread Safety

| Concern | Mechanism |
|---------|-----------|
| GOT patching across threads | `_patch_lock` (Mutex) in `patchLibraries()` |
| Library unload during patching | `UnloadProtection` handle per library |
| Allocation byte counter | Lock-free CAS loop in `shouldSample` |
| JFR buffer writes | Per-lock-index try-lock with 3 attempts; events dropped on contention |
| Hook enable / disable | `volatile bool _running` — checked before every recording call |
| `_initialized` write ordering | Serialized by the profiler's outer state lock (caller responsibility) |

---

## Known Limitations and Design Trade-offs

**No reentrancy guard.** As documented in `mallocTracer.cpp`:

> To avoid complexity in hooking and tracking reentrancy, a TLS-based approach is
> not used. Reentrant allocation calls would result in double-accounting.

When `recordMalloc` calls into the profiler (stack walking, JFR buffer writes), any
allocations made by the profiler itself will re-enter the hooks. Infinite recursion
is prevented because the hook functions call `_orig_malloc` (a saved direct function
pointer) instead of going through the GOT, but profiler-internal allocations may be
double-counted as application allocations.
Leak detection is unaffected: the same address being recorded multiple times is
handled correctly by the tracking logic.

**Hooks are never uninstalled.** `stop()` only sets `_running = false`. The GOT
entries remain patched for the lifetime of the process. After stopping, every
malloc/free incurs the overhead of one function-pointer indirection plus a volatile
bool read, which is negligible in practice. Uninstalling hooks safely would require
iterating all libraries again under `_patch_lock`, which is deferred.

**`nativemem=0` records every allocation.** When `_interval == 0`,
`shouldSample` returns `true` on every call (the `interval <= 1` fast path). This
is intentional for 100% sampling but can produce very high event volumes.

**No free event tracking.** Free calls are hooked (to forward through the GOT
correctly) but not recorded. Sampled mallocs mean most frees would match nothing,
and the immense event volume with no stack traces provides no actionable insight.

**HotSpot / Linux only for full stack traces.** `CSTACK_VM` requires
`VMStructs::hasStackStructs()`, which is only true on HotSpot JVMs on Linux. On other
platforms the profiler falls back to `CSTACK_DEFAULT` and malloc events will have
empty stack traces.
