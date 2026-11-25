# Native Memory Allocation Profiling

## Overview

The native memory profiler tracks allocations made through the C allocation
functions (`malloc`, `calloc`, `realloc`, `posix_memalign`, `aligned_alloc`). While
native-memory sampling is active, it patches importing libraries' GOT (Global
Offset Table) entries and records sampled allocations without modifying application
source code or requiring a custom allocator. `free` is **not** hooked: there is no
`free_hook`, and free events are not recorded.

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
into the importing library's GOT. This avoids requiring `LD_PRELOAD` or a process
restart. It patches libraries already loaded when a native-memory session starts
and libraries discovered by `Libraries::refresh()` while sampling is active. A later
admitted start also patches libraries loaded while sampling was stopped.

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
unless running and given a non-null, nonempty allocation that `shouldSample()` selects.
A selected allocation is dropped if `ThreadExitRegistry::isCurrentExiting()` reports
that the thread is exiting.

| Hook | Calls | Passes to `maybeRecord` |
|------|-------|---------|
| `malloc_hook(size)` | `_orig_malloc(size)` | `(ret, size)` |
| `calloc_hook(num, size)` | `_orig_calloc(num, size)` | `(ret, num * size)`, only if `num != 0 && size != 0`. The product is not overflow-checked; a wrapped value is harmless because libc returns `NULL` on overflow and `maybeRecord` discards `NULL` |
| `realloc_hook(addr, size)` | `_orig_realloc(addr, size)` | `(ret, size)`, whether or not `addr` was `NULL` (a grown buffer is double-counted against its original sampled malloc, since frees are not tracked) |
| `posix_memalign_hook(memptr, align, size)` | `_orig_posix_memalign(memptr, align, size)` | `(*memptr, size)`, only if `ret == 0 && memptr != NULL` |
| `aligned_alloc_hook(align, size)` | `_orig_aligned_alloc(align, size)` | `(ret, size)` |

---

## Initialization Sequence

The GOT-patching state lives in `MallocHooker` (`_patched_libs`, `_initialized`, and
`_entries`), guarded by `LibraryPatcher::_lock` during Linux walks and by `_patch_lock`
on macOS. The platform implementations of `patchLibraries()` and `unpatchLibraries()`
are in `mallocTracer_linux.cpp` and `mallocTracer_macos.cpp`; the sampling state lives
in `MallocTracer`. For every profiler start that requests `nativemem`,
`MallocTracer::start()` resets the per-session interval, Poisson counter, sample count,
PID controller and timestamp, then calls `MallocHooker::initialize()` before publishing
`_running` or patching other libraries.

On the fresh path (`_initialized == false`), initialization:

1. Locates the profiler's own `CodeCache`. If it cannot find it, it caches the same
   resolution-failure state as a required-symbol failure and returns the existing
   malloc-symbol resolution error.
2. Calls `resolveMallocSymbols()` so the profiler's own allocator imports are resolved.
   Resolution can call allocation functions; startup is not allocation-free.
3. Reads the first two slots (PRIMARY, SECONDARY) of the profiler's five allocation
   imports with the read-only `CodeCache::peekImport(id, index)` accessor. Missing slots
   and NULL values remain absent; an import with more slots rejects as `INDETERMINATE`. The candidate forwarding values are the PRIMARY slot values.
4. If the required malloc candidate is NULL, caches `_initialized = true` and returns
   the existing resolution error. This path returns before saving pointers, probing
   nested allocators, marking hooks, seeding the PRNG, or running admission.
5. Runs admission over the current slot values and candidate forwarding values before
   changing `_orig_*`. It compares stripped addresses but never modifies stored
   callable pointers, deduplicates a fixed set of at most 15 targets, and combines
   per-target results as `DDPROF` > `INDETERMINATE` > `NOT_RECOGNIZED`.
6. On `DDPROF` or `INDETERMINATE`, returns the corresponding startup error without
   committing `_orig_*`, probing, marking hooks, seeding the PRNG, setting `_running`,
   or calling `MallocHooker::patchLibraries()`. A fresh rejection leaves
   `_initialized` false; the next request rechecks the current slots and candidates.
7. On admission, commits `_orig_*` from the captured candidate values, then runs
   `detectNestedMalloc()`, marks the five hook functions with `MARK_JAVA_PROFILER`,
   seeds the shared xoroshiro128+ PRNG from `TSC::ticks()`, and sets `_initialized`.

`detectNestedMalloc()` probes the saved `calloc` target only when both it and the saved
`malloc` target are non-NULL and its owner library has a valid `UnloadProtection` handle.
It probes the saved `posix_memalign` target only when both it and the saved `aligned_alloc`
target are non-NULL and that owner handle is valid. Each probe temporarily patches the
owner image's relevant import, makes one call, and restores the slot. If nesting is
observed, `patchLibraries()` skips patching that operation in every library; it patches
the inner `malloc` or `aligned_alloc` import instead, so the nested allocator call is
recorded once.

On the cached path, a NULL `_orig_malloc` retains the existing resolution error. Otherwise,
initialization locates its own `CodeCache`; if it is unavailable, it returns
`INDETERMINATE` with `NO_OWN_LIBRARY`. It then reads the current PRIMARY and SECONDARY
slots again and re-evaluates them together with the saved `_orig_*` forwarding pointers.
It does not cache an admission verdict or rewrite saved pointers. A rejection returns
before `_running` is published; an admitted request continues to `patchLibraries()`.

Linux admission identifies the live owner of each target inside one
`dl_iterate_phdr()` callback. It checks the loader-reported `PT_LOAD` ranges, then reads
that image's in-memory dynamic symbol/hash tables only from file-backed, `PF_R`
segments. An image is `DDPROF` only when it defines each marker exactly once as a
`STT_FUNC` with `STB_GLOBAL` or `STB_WEAK` binding and `STV_DEFAULT` or `STV_PROTECTED`
visibility. Undefined, local, hidden or internal same-name entries are ignored. If
neither marker has a qualifying or owned wrong-kind definition, the image is
`NOT_RECOGNIZED`; a partial pair, an owned exported wrong-kind definition, a duplicate
qualifying definition, or unreadable/malformed metadata yields `INDETERMINATE`. A target with no owning object
is `INDETERMINATE` (`NO_OWNER`). All read ranges and derived addresses are checked
before dereference.

The owner walk holds no loader handle: the lifetime basis was source-checked for glibc
2.39, which holds its loader write lock through the iteration and unmaps on `dlclose()`
under that lock, and musl 1.2.5, whose `dlclose()` does not unmap. The callback and
classifier use profiler-local code, inline accessors and compiler builtins; they make
no PLT/GOT calls, allocate, explicitly lock, log, touch TLS, call an inspected target,
marker function or IFUNC resolver. The loader lifetime source check covers the named
versions; it is not a source review of every supported libc release.

On non-Linux platforms, the shared target derivation and own-hook consistency checks
still run, but the platform owner classifier returns `NOT_RECOGNIZED` for every target;
only inconsistent own-hook state can therefore cause a new indeterminate rejection.

After admission, `MallocTracer::start()` sets `_running = true` **before** patching, so a
`dlopen()` that races with `patchLibraries()` already sees `running() == true` and patches
the new library itself.

**`MallocHooker::patchLibraries()`** — writes the hook addresses into the GOT of
   every native library from index `_patched_libs` on, covering every relocation slot
   a symbol has (`findImport(id, index)` for each of `importCount(id)`), and records each written
   slot (library, slot address, hook, original pointer) in `_entries` so `stop()` can
   restore it. A slot that cannot be recorded (table full) is left unhooked rather than
   hooked for good. On Linux the patching runs inside a
   `LibraryPatcher::LiveLibraryWalk`: a library is visited only while the loader keeps
   it mapped and only if it is still the image its `CodeCache` describes, so a slot
   address saved in a stale cache is never written through. On macOS each library is
   pinned with `UnloadProtection` under `_patch_lock`, and is used only if `dladdr()`
   on the cache's start (its Mach-O header) reports an image that starts there with the
   cache's path and, when the parser recorded one, the same `LC_UUID`
   (`isCurrentImage()`): the pin resolves a library by name, so it also succeeds after
   the same path was reloaded elsewhere, or as another build at the same base, which the
   parser never re-parses. `dladdr()` resolves under dyld's
   lock; dyld's image indexes shift under concurrent unloads. Either way the walk re-checks
   `MallocTracer::running()` under its lock, so a refresh that raced `stop()` does not
   re-hook after the restore.

The admission check is a startup snapshot; it does not prevent ddprof from activating later
or concurrently. If a mixed request can start another engine, rejection of native-memory
profiling does not prevent that request from starting. A native-memory-only request returns
the native-memory error.

`stop()` restores every recorded slot and resets `_patched_libs` to 0, so the next
`start()` patches every library again (see "Stopping" below).

---

## Stopping

`MallocTracer::stop()` clears `_running` first, so a hook invocation already past its
GOT load records nothing, then calls **`MallocHooker::unpatchLibraries()`**:

- On Linux, in a `LiveLibraryWalk` (one visit per library, entries sorted by library),
  each recorded slot is restored with a compare-and-swap from the hook back to the
  saved original, so a slot something else has re-patched since is left alone.
  On macOS each library is pinned with `UnloadProtection` and checked with
  `isCurrentImage()` for the restore.
- Entries of a library the walk did not visit (unloaded, or no longer verifiably the
  image they were saved from) are not written. They are kept, up to a cap, so a later
  `patchSlot()` of the same slot reuses the saved original. Over the cap, the entries
  whose original `patchSlot()` can rebuild are dropped first; one holding a PLT stub or
  another interposer's wrapper survives.
- `_patched_libs` is reset and the restored entries are discarded; the kept orphans
  move to the front (`[0, _kept_count)`), and the next `start()` re-patches the rest
  from scratch.

`Profiler::stop()` stops the libraries refresher **before** `malloc_tracer.stop()`,
because the refresher re-installs malloc hooks (`Libraries::refresh()` →
`installHooks()`). A thread that loaded a hook address before the restore still runs
the hook, which only calls the saved `_orig_*` pointer and sees `running() == false`.


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
`REFRESH_INTERVAL_NS` (500 ms). While native-memory sampling is active, either path
hooks newly loaded libraries without restarting the profiler.

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
    const u32 session = Profiler::instance()->recordingSession();
    if (!running() || ret == nullptr || size == 0 || !shouldSample(size)) {
        return;
    }
    if (ThreadExitRegistry::isCurrentExiting()) {
        Counters::increment(MALLOC_SAMPLES_DROPPED);
        return;
    }
    ProfiledThread* prof_thread = ProfiledThread::acquireCurrent();
    if (prof_thread == nullptr) {
        Counters::increment(SAMPLES_DROPPED_THREAD_LOCAL);
        return;
    }
    CriticalSection cs(prof_thread);
    if (cs.entered()) {
        recordMalloc(ret, size, prof_thread->tid(), session);
    } else {
        Counters::increment(MALLOC_SAMPLES_DROPPED);
    }
}
```

`shouldSample()` runs first because it reads no TLS. An unsampled allocation therefore
skips the exit-registry lookup, which costs a raw `gettid` syscall, and skips TLS.

The raw identity outlives its thread, so an exit mark can match a new thread
that reuses the tid. A marked thread counts as exiting only if it holds a
`ProfiledThread` (acquiring TLS clears stale marks) or has SIGPROF and SIGVTALRM
blocked (every mark site blocks them first). Otherwise the identity was reused:
the mark is cleared and the allocation is sampled.
Only a sampled allocation claims a thread-local slot with `acquireCurrent()` (the
allocation-adjacent-hook variant, which may claim a slot from the priming pool and never
mallocs).

The `CriticalSection` is the reentrancy guard. Allocations made by the profiler while it
records a sample re-enter the hooks through the patched GOT and fail to enter the
critical section. They advance the byte countdown, and a sample that lands on one is
dropped and counted in `MALLOC_SAMPLES_DROPPED`. This does not bias the recorded weights:
each countdown crossing draws a fresh exponential interval, so an application allocation
of `size` bytes is still sampled with probability `1 - exp(-size / interval)`, the
inverse of its weight.

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
| GOT patching and restoring across threads | Linux: `LibraryPatcher::_lock`, held by the `LiveLibraryWalk` that patches or restores; macOS: `MallocHooker::_patch_lock` (Mutex) |
| Library unload during patching or restoring | Linux: the walk visits only libraries the loader keeps mapped, after an identity check; macOS: an `UnloadProtection` handle per library |
| Refresher re-hooking after `stop()` | Refresher stopped before `malloc_tracer.stop()`; `running()` re-checked under the walk's lock |
| Allocation byte counter | Lock-free CAS loop in `shouldSample` |
| Reentrant allocations from the profiler | `CriticalSection` in `maybeRecord` — nested calls do not record |
| Recording / JFR buffer writes | Per-lock-index try-lock with 3 attempts in `Profiler::recordSample`; samples dropped on contention |
| Hook enable / disable | `_running`, stored with release and read with acquire (`running()`) before every recording call |
| Admission import capture | Reads both current import slots and saved forwarding pointers at each start; admission results are not cached |
| Linux owner-image lifetime | Classifies within one `dl_iterate_phdr()` callback; no loader handle is acquired (source-checked glibc 2.39 and musl 1.2.5 only) |
| Late or concurrent ddprof activation | Not prevented or arbitrated; the check is a startup snapshot |
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

**Hooks are uninstalled on `stop()`, but a restore can miss a library.** A library
that was unloaded and reloaded, or replaced at the same base, is not verifiably the
image its saved slots came from, so its entries are not restored. They are kept, up to `MAX_ORPHAN_ENTRIES`, for a
later `patchSlot()`. In
practice such a library has a fresh GOT that never held the hook. A thread already
inside a hook when the restore runs finishes it normally (the hook code stays mapped).

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
