# Native Memory Allocation Profiling

## Overview

The native memory profiler tracks heap allocations made through the C standard
library (`malloc`, `calloc`, `realloc`, `posix_memalign`, `aligned_alloc`). It
instruments these functions at the GOT (Global Offset Table) level so that every
intercepted call is accounted for without modifying application source code or
requiring a custom allocator. `free` is **not** hooked: there is no `free_hook`, and
free events are not recorded.

Sampled allocation events carry a full Java + native stack trace and are emitted as
`datadog.NativeMemoryAllocation` JFR events.

The feature is activated by passing `nativemem=<interval>` to the profiler, where
`<interval>` is the byte-sampling interval (e.g. `nativemem=524288` samples roughly
one event per 512 KiB allocated). Passing `nativemem=0` records every allocation.

---

## Component Map

```
  Application code
        │  malloc() / calloc() / realloc() / posix_memalign() / aligned_alloc()
        ▼
  ┌─────────────┐  GOT patch   ┌──────────────────────────┐
  │  libc / musl│ ◄────────── │  malloc_hook / calloc_hook│  mallocTracer.cpp
  └─────────────┘  (MallocHooker)│  realloc_hook / …      │
                              └────────────┬─────────────┘
                                           │ maybeRecord
                                           ▼
                              ┌──────────────────────────┐
                              │  MallocTracer::           │  mallocTracer.cpp/h
                              │  maybeRecord()            │
                              │   → shouldSample()        │
                              │   → recordMalloc() ────►  │  Profiler::recordSample()
                              └────────────┬─────────────┘
                                           │ walkVM (CSTACK_VM)
                                           ▼
                              ┌────────────────────────────────────┐
                              │  JFR buffer                         │  flightRecorder.cpp
                              │  datadog.NativeMemoryAllocation     │
                              └────────────────────────────────────┘
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

(`im_free` exists in the enum, but the malloc tracer never patches it.)
`CodeCache::patchImport(ImportId, void*)` overwrites the matching GOT entry
located via `CodeCache::findImport()`.

### Hook signatures

Each hook calls the saved original function first, then hands the result to
`MallocTracer::maybeRecord(ret, size)`. `maybeRecord` is the common gate: it does nothing
unless `running() && ret != NULL && size != 0`.

| Hook | Calls | Passes to `maybeRecord` |
|------|-------|---------|
| `malloc_hook(size)` | `_orig_malloc(size)` | `(ret, size)` |
| `calloc_hook(num, size)` | `_orig_calloc(num, size)` | `(ret, num * size)`, only if `num != 0 && size != 0`. The product is not overflow-checked; a wrapped value is harmless because libc returns `NULL` on overflow and `maybeRecord` discards `NULL` |
| `realloc_hook(addr, size)` | `_orig_realloc(addr, size)` | `(ret, size)`, whether or not `addr` was `NULL` (a grown buffer is double-counted against its original sampled malloc, since frees are not tracked) |
| `posix_memalign_hook(memptr, align, size)` | `_orig_posix_memalign(memptr, align, size)` | `(*memptr, size)`, only if `ret == 0 && memptr != NULL` |
| `aligned_alloc_hook(align, size)` | `_orig_aligned_alloc(align, size)` | `(ret, size)` |

---

## Initialization Sequence

The GOT-patching state lives in `MallocHooker` (`_patch_lock`, `_patched_libs`,
`_initialized`); the sampling state lives in `MallocTracer`. `MallocTracer::start()`
(called on every profiler start that requests `nativemem`) runs:

1. Resets per-session sampling state: `_configured_interval` / `_interval` (from
   `nativemem`), `_bytes_until_sample` (a fresh Poisson draw, or 0 when the interval
   is ≤ 1), `_sample_count`, the PID controller (`_pid.reset()`), and
   `_last_config_update_ts`.

2. Calls **`MallocHooker::initialize()`**, which does its work only on the first call
   (later calls return the cached result). If it fails to resolve the symbols,
   `start()` returns an error and native memory profiling is unavailable. On the first
   call it:

   a. **`resolveMallocSymbols()`** — calls each intercepted function at least once so
      the profiler library's own PLT stubs are resolved by the dynamic linker. This
      ensures that subsequent `SAVE_IMPORT` reads get the real libc function pointers
      rather than the PLT resolver.

   b. **`SAVE_IMPORT(func)`** — reads the resolved GOT entry for each symbol from the
      profiler library's own import table and stores it in the corresponding
      `_orig_<func>` static pointer.

   c. **`detectNestedMalloc()`** — probes whether the platform's `calloc`
      implementation calls `malloc` internally (as musl does), and whether
      `posix_memalign` calls `aligned_alloc` internally. It temporarily patches libc's
      own `malloc` / `aligned_alloc` import with a probe hook, makes one call, and
      restores the original entry. When nesting is detected, `patchLibraries()` later
      leaves that library's `calloc` / `posix_memalign` GOT entry untouched, so the
      allocation is recorded once, by the inner `malloc` / `aligned_alloc` hook.

   d. **`lib->mark(...)`** — marks the five hook functions with `MARK_JAVA_PROFILER`
      in the profiler's code cache, so the stack walker can find the hook boundary and
      drop the profiler-internal frames above it.

   e. Seeds the shared xoroshiro128+ PRNG state via splitmix64 from `TSC::ticks()`.

3. Sets `_running = true` **before** patching, so a `dlopen()` that races with
   `patchLibraries()` already sees `running() == true` and patches the new library
   itself.

4. **`MallocHooker::patchLibraries()`** — under `_patch_lock`, walks the native
   libraries not yet patched and writes the hook addresses into each library's GOT.
   `_patched_libs` is a monotonic index, so already-patched libraries are skipped on
   subsequent calls.

`patchLibraries()` is called again on every `start()` to pick up any libraries
loaded between profiler sessions.

---

## Dynamic Library Handling

New libraries are hooked through `Libraries::refresh()` (`libraries.cpp`), which
re-parses the loaded libraries and then, if `MallocTracer::running()`, calls
`MallocTracer::installHooks()` → `MallocHooker::patchLibraries()`:

```cpp
// libraries.cpp
void Libraries::refresh() {
    _dirty.store(false, std::memory_order_release);
    updateSymbols(false);
    LibraryPatcher::patch_sigaction();
    LibraryPatcher::install_socket_hooks();
    if (MallocTracer::running()) {
        MallocTracer::installHooks();
    }
    ...
}
```

`refresh()` runs from two places. The profiler's `dlopen_hook` (`profiler.cpp`) calls it
synchronously after a successful `dlopen` when it is not running inside one of the
profiler's own signal handlers. Inside a signal handler it only calls
`Libraries::markDirty()`, and the libraries refresher thread picks the change up within
`REFRESH_INTERVAL_NS` (500 ms). Either way, newly loaded libraries are hooked without a
profiler restart.

---

## Sampling

Allocation recording uses Poisson-interval sampling via `MallocTracer::shouldSample()`:

```cpp
// mallocTracer.cpp — lock-free CAS loop with Poisson jitter
bool MallocTracer::shouldSample(size_t size) {
    if (__atomic_load_n(&_interval, __ATOMIC_ACQUIRE) <= 1) return true;  // nativemem=0 or 1
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
```

`_bytes_until_sample` is a shared counter decremented by each allocation's size. When
exhausted, a new exponentially distributed interval is drawn by `nextPoissonInterval()`
as `-interval * ln(u)`, where `u` is a uniform value from a process-wide xoroshiro128+
generator (seeded once via splitmix64 from `TSC::ticks()`; its state is shared and
updated with relaxed atomics because `thread_local` cannot be used on the malloc path).
The jitter avoids synchronization artifacts. Multiple threads compete via CAS, so no
mutex is needed.

Each sampled event carries `weight = 1 / (1 - exp(-size / interval))`, or 1.0 when the
interval is ≤ 1.

A PID controller (`updateConfiguration()`) adjusts `_interval` toward
`TARGET_SAMPLES_PER_WINDOW` (100) samples per `CONFIG_UPDATE_CHECK_PERIOD_SECS` (1 s).
The update is evaluated every 100th sample, and only when more than one period has
passed since the last update. The interval is clamped to
`[configured nativemem interval, 2^40]`, so it never drops below what the user asked for.

### Entry gate (`maybeRecord`)

```cpp
void MallocTracer::maybeRecord(void* ret, size_t size) {
    if (running() && ret && size) {
        ProfiledThread* prof_thread = ProfiledThread::acquireCurrent();
        if (prof_thread == nullptr) {
            Counters::increment(SAMPLES_DROPPED_THREAD_LOCAL);
            return;
        }
        CriticalSection cs(prof_thread);
        if (cs.entered() && shouldSample(size)) {
            recordMalloc(ret, size, prof_thread->tid());
        }
    }
}
```

The `ProfiledThread` is obtained with `acquireCurrent()` (the allocation-adjacent-hook
variant, which may claim a slot from the priming pool and never mallocs). Because that
happens before `shouldSample()`, every allocation that passes the
`running()`/`ret`/`size` gate claims a thread-local slot on first touch, even when it is
then not sampled. The `CriticalSection` is the reentrancy guard: allocations made by
the profiler while it records a sample re-enter the hooks through the patched GOT, fail
to enter the critical section, and are not recorded.

---

## Stack Trace Capture

### Why `CSTACK_VM` is needed

The malloc hooks execute on the calling thread with no signal context (`ucontext ==
NULL`). Two distinct levels of stack capture are possible:

- **Separate native + Java stacks** (`CSTACK_DEFAULT`, `CSTACK_FP`, `CSTACK_DWARF`):
  `getNativeTrace()` walks the native frames with `StackWalker::walkFP()` /
  `walkDwarf()`. With `ucontext == NULL` both seed the walk from `callerPC()` /
  `callerFP()` / `callerSP()` (`stackWalker.cpp`), so no signal context is needed.
  Java frames are then collected separately via ASGCT
  (`asyncJavaTraceWithPostProcessing()`), and the two parts are concatenated rather
  than interleaved.

- **Interleaved native + Java stacks** (`CSTACK_VM` only): `HotspotSupport::walkVM`
  walks native and Java frames in one pass and switches from native to Java frames
  through HotSpot's `JavaFrameAnchor` (lastJavaPC / lastJavaSP / lastJavaFP). This
  works from inside a malloc hook because the anchor is set whenever the JVM has
  transitioned from Java to native.

With `ucontext == NULL`, `walkVM` seeds the walk from `callerPC()` / `callerSP()` /
`callerFP()` (`hotspot/hotspotSupport.cpp`). `callerPC()` is
`__builtin_return_address(0)` on x86_64 (a return address) and an `adr %0, .` read of
the current PC on aarch64 (`arch.h`; `CALLER_PC_IS_RETURN_ADDRESS` records which one).

In every mode the native frames above the hook boundary (the `MARK_JAVA_PROFILER`-marked
hook functions and the profiler-internal frames they call) are discarded, so the trace
starts at the real call site (`Profiler::convertNativeTrace()` for FP/DWARF,
`HotspotSupport::walkVM` for `CSTACK_VM`). If the boundary frame is never found,
`NATIVE_TRACE_HOOK_PREFIX_NOT_FOUND` is incremented.

### Default stack mode

`CSTACK_DEFAULT` is the initial default (`arguments.h`). At profiler start,
`Profiler::start()` promotes it to `CSTACK_VM` when VMStructs are available **and the
OS is Linux**. Otherwise it switches to `CSTACK_DWARF` if DWARF is supported, and
leaves `CSTACK_DEFAULT` (frame-pointer walking for hook samples) in place if it is not:

```cpp
if (_cstack == CSTACK_DEFAULT) {
    if (VMStructs::hasStackStructs() && OS::isLinux()) {
        _cstack = CSTACK_VM;
    } else if (DWARF_SUPPORTED) {
        _cstack = CSTACK_DWARF;
    }
}
```

If `CSTACK_VM` is explicitly requested but `VMStructs` are not available, the
profiler resets to `CSTACK_DWARF` (if supported) or `CSTACK_NO` and logs an error:

```cpp
} else if (_cstack == CSTACK_VM) {
    if (!VMStructs::hasStackStructs()) {
        _cstack = DWARF_SUPPORTED ? CSTACK_DWARF : CSTACK_NO;
        Log::error("VMStructs stack walking is not supported on this JVM/platform, defaulting to the default native call stack unwinding mode.");
    }
}
```

### Code path for malloc stack walking

`MallocTracer::recordMalloc()` calls `Profiler::recordSample(NULL, size, tid,
BCI_NATIVE_MALLOC, 0, &event)`. `recordSample` takes one of the `CONCURRENCY_LEVEL`
per-lock-index locks (up to 3 `tryLock()` attempts; on failure the sample is dropped and
counted in `ticks_skipped`), then calls `getNativeTrace()` first. For
`_cstack >= CSTACK_VM`, `getNativeTrace` returns 0 immediately (native frames are
not collected via `walkFP`/`walkDwarf`). Then `JVMSupport::walkJavaStack()` is
called, which on HotSpot dispatches to `HotspotSupport::walkJavaStack()`:

```cpp
// hotspot/hotspotSupport.cpp — HotspotSupport::walkJavaStack()
if (features.mixed) {
    return walkVM(ucontext, frames, max_depth, features, eventTypeFromBCI(request.event_type), lock_index, truncated);
}
if (isHookPrefixedSample(request.event_type) || request.event_type == BCI_CPU || request.event_type == BCI_WALL) {
    if (cstack >= CSTACK_VM) {
        return walkVM(ucontext, frames, max_depth, features, eventTypeFromBCI(request.event_type), lock_index, truncated);
    }
    return asyncJavaTraceWithPostProcessing(ucontext, frames, max_depth, java_ctx, truncated, prof_thread);
}
return 0;
```

`isHookPrefixedSample()` (`profiler.h`) is true for `BCI_NATIVE_MALLOC` and
`BCI_NATIVE_SOCKET`. Under `CSTACK_VM`, `HotspotSupport::walkVM` is the sole source of
both native and Java frames for malloc events.

---

## JFR Event Format

A single event type is defined in `jfrMetadata.cpp` under the
`Datadog / Profiling` category:

### `datadog.NativeMemoryAllocation` (`T_MALLOC`)

| Field | Type | Description |
|-------|------|-------------|
| `startTime` | `long` (ticks) | TSC timestamp of the allocation |
| `eventThread` | thread ref | Thread that performed the allocation |
| `stackTrace` | stack trace ref | Call stack at the allocation site |
| `address` | `long` (address) | Returned pointer value |
| `size` | `long` (bytes) | Requested allocation size |
| `weight` | `float` | Statistical sample weight based on Poisson sampling probability |
| `spanId` | `long` | Span ID from the current thread context (0 when there is none) |
| `localRootSpanId` | `long` | Local root span ID from the current thread context (0 when there is none) |

The registered context attributes (`contextAttributes`) follow as additional fields.

Events are written by `Recording::recordMallocSample()` in `flightRecorder.cpp`:

```cpp
buf->putVar64(T_MALLOC);
buf->putVar64(event->_start_time);
buf->putVar64(tid);
buf->putVar64(call_trace_id);
buf->putVar64(event->_address);
buf->putVar64(event->_size);
buf->putFloat(event->_weight);
writeCurrentContext(buf);
```

---

## Concurrency and Thread Safety

| Concern | Mechanism |
|---------|-----------|
| GOT patching across threads | `MallocHooker::_patch_lock` (Mutex) in `patchLibraries()` |
| Library unload during patching | `UnloadProtection` handle per library |
| Allocation byte counter | Lock-free CAS loop in `shouldSample` |
| Reentrant allocations from the profiler | `CriticalSection` in `maybeRecord` — nested calls do not record |
| Recording / JFR buffer writes | Per-lock-index try-lock with 3 attempts in `Profiler::recordSample`; samples dropped on contention |
| Hook enable / disable | `_running`, stored with release and read with acquire (`running()`) before every recording call |
| `MallocHooker::_initialized` write ordering | Not atomic; relies on `start()` calls being serialized by the profiler's state lock (caller responsibility) |

---

## Known Limitations and Design Trade-offs

**Reentrancy is handled per thread.** Allocations the profiler makes while recording a
sample (stack walking, JFR buffer writes) re-enter the hooks through the patched GOT.
Infinite recursion cannot happen because each hook calls its saved `_orig_*` pointer,
not the GOT. Double-counting is prevented by the `CriticalSection` in `maybeRecord`:
the nested call fails `cs.entered()` and is not recorded. The critical section also
blocks same-thread timer samples (SIGPROF/SIGVTALRM) for the short duration of
`recordMalloc`.

**Hooks are never uninstalled.** `stop()` only sets `_running = false`. The GOT
entries remain patched for the lifetime of the process, because restoring them is not
safe while libraries may be unloaded concurrently (`mallocTracer.cpp`, `stop()`). After
stopping, every hooked allocation pays one extra function-pointer indirection plus an
acquire load of `_running`.

**`nativemem=0` records every allocation.** When `_interval == 0`,
`shouldSample` returns `true` on every call (the `interval <= 1` fast path). This
is intentional for 100% sampling but can produce very high event volumes.

**No free event tracking.** `free` is not hooked and frees are not recorded. Sampled
mallocs mean most frees would match nothing, and the immense event volume with no stack
traces provides no actionable insight. One consequence: a `realloc` that grows a sampled
buffer is recorded again and double-counted against the original allocation.

**HotSpot / Linux only for interleaved native+Java stack traces.** `CSTACK_VM`
requires `VMStructs::hasStackStructs() && OS::isLinux()`, which is only true on
HotSpot JVMs on Linux. On other platforms the profiler falls back to `CSTACK_DWARF`
(if supported) or stays on `CSTACK_DEFAULT`. Native frames are still captured via
FP/DWARF unwinding and Java frames via ASGCT, but they are not interleaved through
`JavaFrameAnchor` as they are with `CSTACK_VM`.
