# Design: Extract Thread Context into the Support Library

**Status:** Implemented (see commits `3858bf22d`..`7d10bc370` on `library-split`; the naming note in §5.2 documents where the shipped API diverged from this design's placeholder names)
**Date:** 2026-07-01
**Branch:** `library-split`
**Epic:** PROF-15243 (Library Split)
**Depends on:** [LibrarySplitPlan](../plans/LibrarySplitPlan.md), [LibrarySplitFeasibility](../architecture/LibrarySplitFeasibility.md)
**Companion analysis:** [ProfiledThread-LibrarySplit-Analysis](../temp/ProfiledThread-LibrarySplit-Analysis.md)

## 1. Purpose

Make OTEL/OTEP thread-context propagation usable from `libJavaSupport.so`
**without loading the profiler**, while keeping a single per-thread context
record shared with the profiler when both libraries are present.

This closes the gap identified in the companion analysis: the feasibility doc
places *context* in the support library, but the record is physically embedded in
`ProfiledThread` (a profiler type) and its JNI entry points hang off
`JavaProfiler`, so a tracer cannot reach context without the profiler.

## 2. Goals / Non-goals

**Goals**

- A support-only consumer (e.g. `dd-trace-java` doing context propagation) can:
  1. obtain the per-thread OTEP record buffer,
  2. write span ID / trace ID / local-root-span ID,
  3. have the record discoverable via the exported `otel_thread_ctx_v1` symbol,
  all with only `libJavaSupport.so` loaded.
- When the profiler library is also loaded, its signal handlers read the **same**
  record with no behavioural change and no added signal-path cost.
- Preserve the 688-byte contiguous layout contract and the musl TLS invariants.

**Also in scope (OTEP custom attributes)**

- OTEP **custom attributes** must be settable and readable with support only.
  That means the support core owns: the per-thread `attrs_data` writes (a pure
  buffer write) and the OTEP **process-level `attribute_key_map`**
  (`OTelContext.setProcessCtx0`/`readProcessCtx0`, `javaApi.cpp:429,511`). See §7.

**Non-goals**

- Moving the **DD JFR interning sidecar's producer/consumer** (the double-buffered
  `_context_value_map` + `registerConstant0` + `snapshot`) to support. That path
  exists only to attach interned tag values to *this process's* JFR events; its
  value map is rotated on JFR dump (`profiler.h:164-175`) and is
  profiler-lifecycle-bound. It stays profiler-side and is written only when the
  profiler is present (§7). Note this covers the sidecar *machinery* only — the
  `_otel_tag_encodings` **storage array** itself is part of the contiguous record
  block and therefore lives in the support `ThreadContext` (§4, §5.6); it simply
  stays zero when the profiler is absent.
- Changing the wire format of `OtelThreadContextRecord` (`otel_context.h:51-61`).
- Removing the transitional monolithic build.

### 2.1 Platform scope

This design **targets Linux (glibc and musl) on x86-64 and aarch64** — the
platforms where the library split ships and where the correctness-critical
invariants live: the exported `thread_local otel_thread_ctx_v1` symbol
(`otel_context.cpp:20`), the musl lazy-TLS-slot `SignalBlocker` guard
(`context_api.cpp:33-40`), and the ABI/symbol gates that use Linux-only tooling
(`/proc/self/maps`, `nm -D`, `nm -u`; §8). All testing (§8) — including the
sanitizer matrix (`LibrarySplitPlan.md` Phase 5) and the specifically called-out
**musl + aarch64** risk areas (§9) — is scoped to these targets.

**macOS/darwin is a supported dev platform, at possibly-degraded functionality.**
The production target is Linux only, but developer machines are macOS, so the
split **must build and the profiler must run** on darwin — the code paths here
(the `ThreadContext` base, the factory hook, the `current()` invariant, the
shared-record reads) are portable C++ and pthreads with no Linux-only dependency,
so they apply on darwin unchanged. What differs is **peripheral, not core**:

- **Symbol export / discovery.** The exported `thread_local otel_thread_ctx_v1`
  (`otel_context.cpp:20`) uses a Mach-O exported-symbols-list rather than an ELF
  version script (the split already handles this dual mechanism —
  `LibrarySplitPlan.md` notes macOS `install_name`/exported-symbols-list). The
  symbol is still exported; external-profiler discovery via `nm -D` is a
  Linux-only *test* mechanism, not a functional requirement.
- **ABI/symbol test tooling.** `/proc/self/maps` and `nm -D`/`nm -u` (§8) are
  Linux-only; the darwin equivalents (`vmmap`, `nm -gU`) are best-effort. The
  support-only "profiler not mapped" assertion (§8) may be skipped on darwin.
- **Degradation is acceptable on darwin.** Support-only context propagation is not
  a production use case there, so if a darwin-specific gap surfaces (e.g. the
  support-only load path), it may be left degraded/skipped rather than blocking —
  provided the **shared** (profiler-on) mode still works for local development.

**Windows remains out of scope** — not a dev or prod target for this component.

## 3. Current architecture (as-is)

### 3.1 Storage

The context record and its sidecar are fields of `ProfiledThread`
(`thread.h:69-76`), forming one 688-byte contiguous block:

```
[ OtelThreadContextRecord (640) | _otel_tag_encodings[] | _otel_local_root_span_id (8) ]
```

Contiguity is asserted at `javaApi.cpp:600-610` and relied on by the Java
`DirectByteBuffer` view (`ThreadContext.java:83-99`).

### 3.2 TLS management

`ProfiledThread` owns the pthread key and lifecycle
(`thread.cpp:14-93`): `initCurrentThread` (eager, signal-safe), `current` (lazy,
allocating, **non**-signal-safe by design, `thread.cpp:80`), `currentSignalSafe`
(never allocates), `release`.

### 3.3 Read/write data flow

- **Writes** are Java-only, straight into the `DirectByteBuffer` returned by
  `initializeContextTLS0` (`ThreadContext.java:99,115-127`). There is no C++
  write API.
- **Reads** are via `ContextApi::get` / `ContextApi::snapshot`
  (`context_api.cpp:43-68`). All C++ callers are profiler-side:
  `wallClock.cpp:262`, `flightRecorder.cpp:1762`, `livenessTracker.cpp:358`,
  plus `thread.cpp:99` and the `dumpContext` test hook.

### 3.4 Profiler coupling in the context surface

- `ContextApi::snapshot()` → `Profiler::instance()->numContextAttributes()`
  (`context_api.cpp:66`).
- `Java_..._ThreadContext_registerConstant0` → `Profiler::instance()->contextValueMap()`
  (`javaApi.cpp:636`).
- `initializeContextTLS0` is a `JavaProfiler` native (`JavaProfiler.java:445`).
- `otel_thread_ctx_v1` is defined in `otel_context.cpp:20` (profiler-side TU per
  the current move-list).

## 4. Design overview (to-be)

Introduce a **support-owned base type** that owns the record and the TLS key.
`ProfiledThread` becomes a subclass that adds profiler-only state. A single
**factory hook** lets the profiler substitute the derived type at allocation
time. The context *core* (`get`, `initializeContextTLS`, the exported symbol, the
buffer JNI) moves to support; the *attribute* machinery and `snapshot()` stay
profiler-side.

```
libJavaSupport.so
  ThreadContext            ← record storage (incl. attrs_data + sidecar array), TLS key
  otel_thread_ctx_v1       ← exported OTEP discovery symbol
  ContextApi::get / initializeContextTLS
  contextApi JNI (buffer)  ← span/trace/LRS + OTEP attrs_data writes
  otel_process_ctx JNI     ← process attribute_key_map (setProcessCtx0/readProcessCtx0)
        ▲  (link-time NEEDED)
        │  profiler registers TLS factory at load; reads same record
libjavaProfiler.so
  ProfiledThread : ThreadContext   ← sampling caches, crash/signal depth, filter slot
  ContextApi::snapshot + _context_value_map + registerConstant0 + JfrMetadata
    (DD sidecar interning — produces/consumes _otel_tag_encodings for JFR only)
  wallClock / flightRecorder / livenessTracker readers
```

Key insight that shrinks the work: the OTEP surface a tracer needs — span/trace
IDs, `attrs_data`, and the process `attribute_key_map` — is all **pure buffer /
process-context work with no `Profiler::instance()` dependency**
(`context_api.cpp:43-59`; the `attrs_data` write is a straight `ByteBuffer` put,
`ThreadContext.java:318`). The only profiler-coupled pieces (`snapshot`, the DD
sidecar interning via `registerConstant0`) stay profiler-side and are simply not
exercised in tracer-only mode. So the context core needs **no probe hook** — only
the TLS factory registration (§5.2) and a Java-side "profiler present" gate on the
sidecar write (§5.5).

## 5. Detailed design

### 5.1 Support-owned `ThreadContext` base

New support type (proposed `support/threadContext.{h,cpp}`) owning:

- the 688-byte contiguous block (record + tag-encodings + LRS), preserving the
  `alignas(8)` and static-assert contract currently in `thread.h:66-76`;
- `_ctx_initialized` flag;
- accessors currently on `ProfiledThread`: `getOtelContextRecord`,
  `getOtelTagEncodingsPtr`, `getOtelTagEncoding`, `getOtelLocalRootSpanId`,
  `markContextInitialized`, `isContextInitialized`, `clearOtelSidecar`
  (`thread.h:224-268`);
- the pthread key + `initTLSKey`/`doInitTLSKey`/`freeKey` and
  `initCurrentThread`/`current`/`currentSignalSafe`/`release`
  (moved verbatim from `thread.cpp:14-93`).

`ThreadContext` extends the existing `ThreadLocalData` base (`threadLocalData.h`),
which is already polymorphic (`virtual is_unwinding_Java`), so adding one virtual
(see §5.2) costs nothing new.

### 5.2 Factory hook and safe downcast

The TLS allocation site must produce a `ProfiledThread` when the profiler is
loaded and a plain `ThreadContext` otherwise. Use the same registration pattern
the split already uses for `crashProtectionActive` / `isJavaThread`
(`LibrarySplitPlan.md` Tasks 1.2–1.3):

```cpp
// support/threadContext.h
typedef ThreadContext* (*ThreadContextFactory)(int tid);
extern std::atomic<ThreadContextFactory> g_thread_context_factory; // default: base

// support/threadContext.cpp
static ThreadContext* defaultFactory(int tid) { return new ThreadContext(tid); }
std::atomic<ThreadContextFactory> g_thread_context_factory{defaultFactory};
```

The profiler registers its factory in `VM::initProfilerBridge` (`vmEntry.cpp`),
alongside the existing probe registrations. This runs from `Agent_OnLoad`
(JVMTI agent attach — `premain`/dynamic attach), **not** from `JNI_OnLoad`
(`VM::initLibrary`, the native-library-load entry point run for every
`System.load`) — the two are distinct JVM callbacks that fire at different
times:

```cpp
g_thread_context_factory.store(
    [](int tid) -> ThreadContext* { return new ProfiledThread(tid); },
    std::memory_order_release);
```

**Record access never downcasts.** All context reads use the `ThreadContext*`
base (`getOtelContextRecord`, etc.), so they are correct regardless of the
concrete type. Profiler-only sampling state requires the derived type; expose it
via a cheap virtual instead of a `static_cast`:

```cpp
// ThreadContext (base)
virtual ProfiledThread* asProfiledThread() { return nullptr; }
// ProfiledThread (derived)
ProfiledThread* asProfiledThread() override { return this; }
```

Signal-handler pattern becomes:

```cpp
ThreadContext* tc = ThreadContext::currentSignalSafe();
if (tc == nullptr) return;                       // tracer thread never initialised
OtelThreadContextRecord* rec = tc->getOtelContextRecord();   // always valid
if (ProfiledThread* pt = tc->asProfiledThread()) {           // sampling extras
    // collapsing cache, crash depth, filter slot ...
}
```

This is async-signal-safe (the object is already vtable-backed; a virtual call is
just an indirect load, no malloc/lock) and remains correct on the **defensive,
out-of-scope delayed-init shape** (§5.7, §8) where a thread could hold a base
object created before the profiler loaded — a path that cannot arise under the
committed init-at-`premain` scope (base-object population empty, §5.7/§11), so
this handles it as defensive-only insurance rather than a supported mode.

**Crash/signal-safety is *not* lost on base objects.** The guard machinery
(`SignalHandlerScope`, `CriticalSection`) already has a fallback for threads with
no `ProfiledThread` — a hash-based bitmap keyed by thread, used today for stress
tests and uninstrumented threads that can still receive signals
(`guards.h:45-59,109-112`). In the split, the guards route through
`asProfiledThread()`: when it returns a derived object they use its
`_signal_depth`/`_in_critical_section` (zero-overhead as today); when it returns
`null` (a base object) they transparently use the existing bitmap fallback. So a
base-only thread sampled by a late-started profiler retains full reentrancy/crash
protection — **only the wall-clock collapsing cache degrades** (§5.7), and that is
a pure optimization. No profiler safety field needs to migrate to the base type.

**Naming note.** This section (and §5.7 below) analyzes the invariant under a
placeholder name, `ProfiledThread::current()`, coined for this design. The
shipped implementation (`thread.cpp`) does not export a symbol with that name;
it exposes the same non-null contract as two separate accessors —
`ProfiledThread::currentProfiled()` (`ThreadContext::current()->asProfiledThread()`)
and `ProfiledThread::currentSignalSafe()`
(`ThreadContext::currentSignalSafe()->asProfiledThread()`) — so every
`ProfiledThread::current()` reference below should be read as "whichever of
those two accessors the call site requires."

**Critical constraint — `ProfiledThread::current()` must stay non-null.** Several
call sites dereference the result unconditionally: `filterThreadAdd0`/
`filterThreadRemove0` (`javaApi.cpp:140,170`) and `profiler.cpp:1356` `assert`
non-null then deref; `onThreadStart` (`profiler.cpp:78`) derefs with no check at
all. The `assert` compiles out under `NDEBUG`, so a null return is an
unconditional crash in release. (Other callers — the park/block hooks
`javaApi.cpp:322,340,373,395` and `wallClock.h:67` — *do* null-check and would
degrade gracefully, not crash; they are not the hazard.) The tempting wrapper

```cpp
// WRONG: base objects (pre-profiler-init threads) make this null → deref crash
inline ProfiledThread* ProfiledThread::current() {
    return ThreadContext::current()->asProfiledThread();
}
```

is therefore **unsafe** in the delayed-init window: a thread that allocated a base
`ThreadContext` before the profiler registered its factory would return null here.

The two current-lookups have different, non-interchangeable contracts:

| Lookup | Contract | Split behaviour |
|---|---|---|
| `ThreadContext::currentSignalSafe()` | may return null; callers null-check | returns base-or-derived; profiler paths use `asProfiledThread()` and tolerate null (§5.2 signal pattern) — **unchanged, safe** |
| `ProfiledThread::current()` | **never null**; callers deref unconditionally | must return a real `ProfiledThread`, which is only sound if the TLS object is already derived |

The `current()` invariant holds **iff** the profiler factory is registered before
any thread on which a profiler-side `current()` runs allocated its context object.
That is exactly what **init-at-`premain`** guarantees (§5.7) — making it a
**prerequisite for correctness of `current()`**, not merely an optimization. Under
today's delayed init the invariant can break; see §5.7 for the two ways out
(init-at-`premain`, recommended; or in-place upgrade in `current()`, complex).

### 5.3 `ContextApi` decomposition

- **To support:** `ContextApi::get` (`context_api.cpp:43-59`) and
  `ContextApi::initializeContextTLS` (`context_api.cpp:33-41`). Neither touches
  `Profiler`; both operate purely on the `ThreadContext` record.
- **Stays profiler-side:** `ContextApi::snapshot` (`context_api.cpp:61-68`). Its
  only caller is `livenessTracker.cpp:358` (profiler), and it needs
  `numContextAttributes`. Move it into a profiler TU (e.g. a
  `profilerContextApi.cpp`) so support carries no `Profiler::instance()`
  reference. `ProfiledThread::snapshotContext` (`thread.cpp:96-108`) can stay on
  the derived type since it is only reached via `snapshot()`.

Net: support's `ContextApi` has zero profiler symbols; no probe hook required for
the context core.

### 5.4 Exported OTEP symbol

Move `otel_context.{h,cpp}` into `support/`. `otel_thread_ctx_v1`
(`otel_context.cpp:20`) is then defined in the support TU and exported from
`libJavaSupport.so`, satisfying external-profiler discovery for support-only
loads. Add its (unmangled, C-linkage `thread_local`) name to the support ABI
symbol list `support/vmstructs-abi.symbols` (`LibrarySplitPlan.md` Task 2.1).

### 5.5 JNI and Java surface

- Move `initializeContextTLS0` (`javaApi.cpp:589-631`) into a support JNI TU
  (proposed `support/contextApi.cpp`). Its body already depends only on
  `ThreadContext`/record accessors after §5.1–5.3, plus `offsetof` on the OTEP
  record — no profiler symbols.
- Expose it from a **support-loadable Java class**. Two options:
  - **(a)** Add `com.datadoghq.profiler.ContextStorage` in support, holding the
    `initializeContextTLS0` native and returning a `ThreadContext` (Java) from a
    support-loaded library. `JavaProfiler` delegates to it.
  - **(b)** Keep `ThreadContext.java` as the public type but relocate its native
    method to be resolved from `libJavaSupport.so`, loaded via
    `LibraryLoader.builder().library(SUPPORT).load()` (`LibrarySplitPlan.md`
    Task 4.1).
  Recommendation: **(a)** — keeps `JavaProfiler` optional for the tracer and
  mirrors the `JVMAccess` precedent (self-contained support Java type).
- Move the OTEP process-context natives `OTelContext.setProcessCtx0` /
  `readProcessCtx0` (`javaApi.cpp:429,511`) into support. They publish/read the
  process `attribute_key_map` via `otel_process_ctx_*` and have no profiler
  dependency; a tracer must publish the key map for its `attrs_data` key indices
  to resolve. `OTelContext.java` already loads via `LibraryLoader`
  (`OTelContext.java:111`) — retarget it to `SUPPORT`.
- **Sidecar decoupling (Java).** Today `setContextAttributeDirect`
  (`ThreadContext.java:285-321`) writes the OTEP `attrs_data` value *and* the DD
  sidecar encoding together, obtaining the encoding from `registerConstant0`
  first and treating a negative return (dictionary full) as a reason to **clear
  the whole attribute** (`ThreadContext.java:304-308`). This must be split so the
  mandatory OTEP `attrs_data` write never depends on the sidecar:
  - always write `attrs_data` (support);
  - write the sidecar encoding only when the profiler is present. When absent,
    `registerConstant0` is not called and the sidecar slot stays 0.
  This also removes a latent OTEP-correctness bug in the monolith: a full DD
  dictionary currently suppresses the OTEP attribute too, which is wrong for
  external interop. `registerConstant0` (`javaApi.cpp:633-639`) itself **stays a
  profiler native** — it is only reached on the profiler-present branch.

### 5.6 What does *not* move

The **DD JFR interning sidecar** stays entirely profiler-side: `snapshot()`, the
double-buffered `StringDictionary _context_value_map` (`profiler.h:86,190`) with
its JFR-dump rotation (`profiler.h:164-175`), `_num_context_attributes`
(`profiler.h:120`, set at `profiler.cpp:1424`), `registerConstant0`,
`JfrMetadata`, and all signal-handler readers. The wall-clock collapsing caches
`_span_id`, `_call_trace_id` (`thread.h:49-56`) stay on `ProfiledThread` — they
are profiler-only optimizations that *read* the support-owned
`_otel_local_root_span_id`.

Note the storage for the sidecar (`_otel_tag_encodings`, `thread.h:75`) is part
of the contiguous record block and therefore physically lives in the support
`ThreadContext` (§5.1). Only its *producer* (value map) and *consumer*
(`snapshot`/JFR) are profiler-side. In tracer-only mode the array simply stays
zero — allocated but unused — which the buffer layout already tolerates
(`ThreadContext.java:113-115` zeroes it on init).

### 5.7 Lifecycle in each mode

| Mode | TLS type | Init path | Record reachable? |
|---|---|---|---|
| Tracer-only (profiler lib absent) | `ThreadContext` (base) | lazy `current()` on first Java context call | Yes — Java-only, non-signal context, lazy alloc is correct |
| Profiler, **init-at-`premain`** (recommended) | `ProfiledThread` (derived) everywhere — base-object population is empty (see invariant below) | eager `initCurrentThread` in `onThreadStart` (`profiler.cpp:76-77`); factory registered at init | Yes — signal-safe reads, `current()` always non-null |
| Profiler, **delayed init** (today's `dd-trace-java`) | mixed: base objects on context-touching threads created pre-init | lazy/eager mix | `ProfiledThread::current()` can crash on a base object — **out of scope; the committed init-at-`premain` approach eliminates this mode** |

#### The base-object invariant

The factory (§5.2) governs **every** lazy allocation — both
`ThreadContext::current()` (context op) and `ProfiledThread::current()` (profiler
op) go through it. So once the factory is registered, every newly-allocated object
is a `ProfiledThread`. Therefore:

> A base `ThreadContext` object can exist **only** on a thread that touched context
> **before the factory was registered** (before profiler init).

The `ProfiledThread::current()` non-null invariant (§5.2) holds iff no such base
object is ever observed by a profiler-side `current()`. Whether that can happen is
entirely determined by init ordering.

#### Init-at-`premain` — the committed approach (necessary and sufficient)

> **DECISION:** the split commits to **init-at-`premain` + deferred profiling-start**.
> The delayed-init crash path and the in-place-upgrade fallback below are recorded
> as motivation and rejected-alternative only; they are **not** implemented.

Register the TLS factory as the **first action of profiler init**, and run profiler
*init* at agent `premain` while keeping profiling *start* (signal registration,
hook installation via `switchThreadEvents`, `profiler.cpp:1702-1708`) deferred.

Terminology matters here: the agent is loaded via `-javaagent`, so `premain` runs
**after** the JVM has left its primordial phase — the main thread and the JVM's own
system threads (compiler, GC) already exist by then. The correctness condition is
therefore **not** "factory registered before any thread is created" (false — those
threads predate the agent) but the weaker, sufficient **"factory registered before
any thread *touches context*."** That holds because the two relevant thread classes
are **disjoint** in time:

- **Threads that set context** — traced application/worker threads — do so during
  application execution, *after* `premain`, hence *after* factory registration →
  their context object is allocated as a `ProfiledThread`.
- **Threads that predate the factory** (main + JVM system threads alive at
  `premain`) run no traced code before `premain` → they never touch context in that
  window → no base object. Their first `current()` (whenever it comes, always after
  registration) allocates a `ProfiledThread`.

Confirmed against `dd-trace-java` behaviour: the tracer does **not** set context on
the main thread before profiler init. So the base-object population is **empty**,
the `current()` invariant holds unconditionally, and **neither an upgrade path nor a
pthread hold-back is required**. This design treats init-at-`premain` as the
**necessary-and-sufficient correctness condition**.

**Intra-`premain` ordering requirement:** within the agent's `premain`, profiler
init (factory registration) must complete **before** the tracer's context
propagation is enabled. Both run in `premain`, so the agent controls the order —
but it is a hard ordering constraint, not an incidental one.

#### The init / start boundary (what moves where)

The commitment splits the profiler's current load-and-run into two clearly-timed
phases:

| Phase | When | Actions |
|---|---|---|
| **Init** (at agent `premain`) | profiler library load / `VM::initProfilerBridge` | register the TLS factory (§5.2); register the `crashProtectionActive` / `isJavaThread` probes (`LibrarySplitPlan.md` Tasks 1.2–1.3); resolve `VMStructs`. **No** signal handlers, **no** thread events, **no** library trap. |
| **Start** (deferred) | `Profiler::start()` / `runInternal` ACTION_START | `switchThreadEvents(JVMTI_ENABLE)` (`profiler.cpp:1702-1708`), signal-handler installation, `switchLibraryTrap(true)` (`profiler.cpp:1420`), engine start. |

The factory must be registered in the **Init** phase, and Init must run at
`premain`, before context propagation is enabled. The invariant that matters is
*factory-registered before any thread touches context* — Init-at-`premain`
delivers it (the main and JVM system threads that predate `premain` do not touch
context in that window).

#### Cross-repo prerequisite

This is **not** solely a `java-profiler` change. `dd-trace-java` must **load and
init the profiler native library during agent `premain`** (so
`VM::initProfilerBridge` runs and the factory registers before any traced context
write), while continuing to defer the profiling *start* action to its existing
trigger. Today it delays the whole thing. Two constraints:

1. Within `premain`, profiler init must run **before** context propagation is
   switched on (intra-`premain` ordering, above).
2. The native `initProfilerBridge` must perform **only** Init-phase work and
   install nothing that samples.

Both changes must land before the library split ships; the split's correctness
depends on them.

#### Known Init-phase exception: `WAKEUP_SIGNAL` handler

**FLAGGED — needs design review.** `VM::initProfilerBridge` (`vmEntry.cpp`)
installs a `SIGIO` (`WAKEUP_SIGNAL`) handler via `OS::installSignalHandler`
before returning. This predates the init/start split and is not a *sampling*
signal handler — it exists solely so `wallClock.cpp` can `pthread_kill()` the
sampler thread to interrupt a blocking syscall once profiling actually starts
— but it is nonetheless a signal-handler installation happening in the Init
phase, which contradicts the "no signal handlers" rule stated above and in the
Init/Start table. It has not been moved as part of the factory-registration
work in this document; doing so (e.g. deferring the `installSignalHandler`
call to `Profiler::start()`) needs its own review of wakeup-thread lifecycle
ordering and is out of scope here.

#### Why today's delayed init is unsafe for the split

Under *delayed* profiler init (current `dd-trace-java`), the disjointness breaks:
worker threads created before the late init **do** set context (base objects) and
then hit an **assert-then-deref** `current()` caller once profiling starts. The
park/block hooks (`parkEnter0`/`parkExit0`/`blockEnter0`/`blockExit0`,
`javaApi.cpp:322,340,373,395`) are **not** the crash vector — they all guard
`if (current == nullptr) return;` and tolerate a null `current()`. The real hazard
is the filter registration path (`filterThreadAdd0`/`filterThreadRemove0`,
`javaApi.cpp:140,170`, and `profiler.cpp:1356`), which `assert(current != nullptr)`
then dereference — the `assert` compiles out under `NDEBUG` — and `onThreadStart`
(`profiler.cpp:78`), which derefs (`current->setJavaThread(...)`) with no check at
all. Base object → unconditional deref → **crash**. So the split cannot ship on the
delayed-init path as-is.

#### Rejected alternative — in-place upgrade (recorded for completeness)

Had delayed init needed to persist, `ProfiledThread::current()` could upgrade a
base object it finds: under `SignalBlocker`, allocate a `ProfiledThread`, copy the
record, re-point `otel_thread_ctx_v1` and the pthread TLS slot, then free the base.
Feasible (`current()` is never called from a signal handler, `thread.cpp:80`, so
blocking is safe) but complex: it races an OTEP external reader on the
`otel_thread_ctx_v1` swap (the pointer swap must be atomic; record contents are
gated by `valid`). **Not pursued** — init-at-`premain` is the committed approach and
makes this unnecessary.

> The pthread thread-start interceptor (`libraryPatcher_linux.cpp:253-261`,
> installed at profiling *start* via `switchLibraryTrap`, `profiler.cpp:1420`) was
> considered as a "hold back new threads until init" mechanism. Rejected: it is
> installed too late (at start, not init) to cover the pre-init window, and it
> cannot catch threads that predate `pthread_create` interception. Init-at-`premain`
> makes it unnecessary: it leaves no residual delayed-init case to cover (the
> base-object population is empty, §5.7), so no upgrade path is implemented or
> required.

#### The signal-safe read path is unaffected either way

`currentSignalSafe()` + `asProfiledThread()` already tolerates a base object (§5.2),
and crash/signal guards fall back to the null-`ProfiledThread` bitmap
(`guards.h:109-112`). The virtual `asProfiledThread()` remains as cheap, correct
defensive insurance even though init-at-`premain` means it should never return null
on a sampled thread in practice.

### 5.8 Signal-safety and musl invariants (preserved verbatim)

- The "set `otel_thread_ctx_v1` once, never touch on detach/attach, gate reads on
  `valid`" invariant (`otel_context.h:66-79`, `context_api.cpp:33-41`) is
  unchanged — `initializeContextTLS` moves as-is.
- `SignalBlocker` around the first TLS write (musl lazy-slot deadlock,
  `context_api.cpp:33-40`) moves with the function.
- `currentSignalSafe()` still gates on `_tls_key_initialized` with acquire/release
  ordering (`thread.cpp:88-93`) — moved unchanged to the support type.

## 6. Build / packaging changes

- Add `support/threadContext.{h,cpp}`, `support/contextApi.cpp`, and move
  `context_api.{h}`, `otel_context.{h,cpp}` under `support/` (extends
  `LibrarySplitPlan.md` Task 3.1's move-list, which currently omits these).
- `thread.{h,cpp}` stay profiler-side but `ProfiledThread` now `#include`s
  `support/threadContext.h` and drops the migrated members.
- Add `otel_thread_ctx_v1` and the context JNI symbols to the support export set.
- Register the TLS factory in `VM::initProfilerBridge`; reset it at profiler
  teardown (mirror `crashProtectionProbeReset`, `LibrarySplitPlan.md` Step 1.2.3).
- Java: add support-side context Java class (§5.5) and wire `LibraryLoader`
  `SUPPORT` target (already planned, Task 4.1).

## 7. Attributes: what is OTEP vs. what is DD-internal

Custom attributes involve **two distinct regions** written together today
(`ThreadContext.java:315-319`) but serving different consumers:

| Region | Written by | Read by | Home |
|---|---|---|---|
| OTEP `attrs_data` (in the 640-B record) | Java buffer put (`ThreadContext.java:318`) | **external** profilers via the record | **Support** |
| OTEP process `attribute_key_map` | `OTelContext.setProcessCtx0` (`javaApi.cpp:429`) | external profilers (resolve key indices) | **Support** |
| DD sidecar `_otel_tag_encodings` (u32) | `registerConstant0` → `_context_value_map` | **this process's** JFR emission (`snapshot`→flightRecorder) | **Profiler** |

OTEP custom attributes are therefore **fully supported in tracer-only mode**: the
`attrs_data` write is a pure `ByteBuffer` put and the key map is published via the
process-context natives — neither touches `Profiler`. What stays profiler-side is
only the *DD interning sidecar*: a `u32` per slot produced by the double-buffered
`_context_value_map` (rotated on JFR dump, `profiler.h:164-175`) so the DD signal
handler can cheaply attach interned tag values to JFR events. A process with no
profiler emits no JFR, so the sidecar has no reader there and is skipped (§5.5).

This split honours "OTEP supports custom attributes" (they propagate fully via
support) while keeping the JFR-lifecycle-bound value map — which would drag
`StringDictionary` rotation, `_num_context_attributes`, and `JfrMetadata` into
support — on the profiler side. It requires **no** `numContextAttributes` probe
hook: `snapshot()` (the only reader that needs the count) stays profiler-side.

## 8. Testing

- **Support-only propagation test** (extends `SupportOnlyLoadTest`,
  `LibrarySplitPlan.md` Task 4.4): with only `libJavaSupport.so` loaded, obtain
  the buffer, write span/trace/LRS, assert `/proc/self/maps` shows no
  `libjavaProfiler`, and read the values back.
- **Support-only OTEP custom-attribute test:** with only support loaded, publish
  a process `attribute_key_map` (`setProcessCtx0`), set a custom attribute, and
  verify the OTEP `attrs_data` bytes are correct (external-reader view). Assert
  the DD sidecar slot stays 0 and that a would-be dictionary-full condition does
  **not** clear the OTEP attribute.
- **Shared-mode attribute test (profiler on):** existing attribute tests must
  pass — both `attrs_data` and the sidecar encoding written atomically as today.
- **Symbol test:** `nm -D libJavaSupport.so | grep otel_thread_ctx_v1` present;
  `nm -u libJavaSupport.so | grep -E 'ProfiledThread|Profiler::'` empty
  (extends the Task 1.5 / 3.5 ABI gate).
- **Shared-record test (profiler on):** existing wall-clock / liveness /
  flight-recorder context tests must pass unchanged — they now read through the
  base accessor.
- **Base-object defensive-path test:** the committed init-at-`premain` scope
  (§5.7) makes the base-object population empty, so this exercises the
  *defensive* path only — not a shipping mode. Deliberately construct the
  out-of-scope delayed-init shape: create threads, load support and write context
  *before* registering the profiler factory, then register it and sample those
  pre-existing base objects. Assert samples read correct span/root IDs through the
  base accessor and the process does not crash (base object routed via
  `asProfiledThread()`/guard bitmap, §5.2 — no bad downcast). This validates the
  §5.2/§5.7 defensive machinery; it does **not** re-open late-attach as a
  supported mode.
- **musl + debug/ASan/TSan:** run the existing sanitizer matrix
  (`LibrarySplitPlan.md` Phase 5); the TLS-key move and virtual downcast are the
  highest-risk areas.

## 9. Risks

| Risk | Severity | Mitigation |
|---|---|---|
| `ProfiledThread::current()` non-null invariant broken by a pre-init base object — **confirmed**: callers `assert` then deref (`javaApi.cpp:140-142`), so null = release crash. Realizable only under delayed init | **High → mitigated by decision** | **Committed: init-at-`premain`** makes the base-object population empty (disjoint-set argument, §5.7) → invariant holds unconditionally. Residual risk moves to the cross-repo prerequisite landing (§5.7). |
| Signal-path type mismatch (base object in a handler) — only possible under delayed init | **Low** | Virtual `asProfiledThread()` (§5.2); record via base accessor never casts; crash/signal guards fall back to the null-`ProfiledThread` bitmap (`guards.h:109-112`). Empty under init-at-`premain`. |
| TLS-key relocation regresses musl/aarch64 ordering | **Medium** | Move `thread.cpp:14-93` verbatim incl. atomics; sanitizer matrix |
| Layout contract broken by moving fields to base | **Medium** | Keep `alignas(8)` + static_asserts with the fields; `javaApi.cpp:600-610` runtime check retained |
| Virtual call in signal handler | **Low** | Object already polymorphic; indirect load only, AS-safe |
| Support export set grows (new context symbols become ABI) | **Low** | Curated symbol list, CI ABI gate |

## 10. Alternatives considered

- **Keep context profiler-side, fix the feasibility doc (Option 1 in the
  analysis).** Cheapest; abandons the tracer-without-profiler goal. Rejected only
  if that goal is confirmed required.
- **Pointer-to-record instead of inheritance.** `ProfiledThread` holds a
  `ThreadContext*` allocated separately. Rejected: two allocations per thread,
  two TLS lookups, and it complicates the single-`DirectByteBuffer` contiguity.
  Inheritance keeps one object, one key, one buffer.
- **Probe-inject `numContextAttributes` into a support `snapshot()`.** Rejected as
  unnecessary — `snapshot()` has only profiler callers, so it simply stays
  profiler-side (§5.3), avoiding the hook entirely.
- **Move the DD value map (`_context_value_map`) to support** so the sidecar is
  always written. Rejected: the map is double-buffered and rotated on JFR dump
  (`profiler.h:164-175`), so it is bound to the profiler's recording lifecycle;
  moving it drags rotation, `_num_context_attributes`, and `JfrMetadata` into
  support for a sidecar that has no reader without the profiler. The §5.5
  decoupling (write `attrs_data` always, sidecar only when profiler present)
  delivers full OTEP attribute support without it.

## 11. Open questions

1. ~~Is late-attach a required scenario?~~ **Resolved — decided.** The team has
   committed to **init-at-`premain` + deferred profiling-start** (§5.7), the
   necessary-and-sufficient correctness condition: base-object population is empty,
   `current()` is always non-null, no upgrade path or interceptor. Remaining work
   is the cross-repo prerequisite (§5.7 "init / start boundary"): `dd-trace-java`
   loads+inits the profiler native lib during agent `premain`; the native `initProfilerBridge`
   does Init-phase work only. Both must land before the split ships.
2. Support-side Java surface: new `ContextStorage` class (5.5a) vs. relocated
   `ThreadContext` native (5.5b)?
3. ~~Is `otel_process_ctx` (`otel_process_ctx.h`) already free of profiler symbols,
   so `setProcessCtx0`/`readProcessCtx0` can move to support unchanged?~~
   **Resolved — audit done (parallel to `LibrarySplitPlan.md` Task 1.4).** The
   §5.5/§7 claim is confirmed:
   - `otel_process_ctx.{h,cpp}` is a self-contained C reference implementation. It
     includes only libc/system headers (`stdbool`, `stdio`, `stdatomic`, `stdlib`,
     `string`, `sys/mman`, `sys/prctl`, `sys/syscall`, `time`, `unistd`) and
     references no `Profiler`, `ProfiledThread`, or any profiler symbol.
   - The two JNI wrappers `setProcessCtx0`/`readProcessCtx0`
     (`javaApi.cpp:429,511`) depend only on: the `otel_process_ctx_*` C API;
     `JniString` (a local helper already duplicated support-side in
     `support/jvmAccessApi.cpp`); `Log` (`support/log.h`, already support-side); and
     `DD_TAGS_CAPACITY` (a plain `static const u32` constant in `context.h`,
     `context.h:22`). Neither wrapper references `Profiler::instance()` or
     `ProfiledThread`.
   Conclusion: both natives can move to support unchanged, subject only to carrying
   the `DD_TAGS_CAPACITY` constant (or its header) along. §5.5/§7 are settled on
   this point.
4. Changing `setContextAttribute` so a full DD dictionary no longer clears the
   OTEP attribute (§5.5) alters existing monolith behaviour. Confirm no consumer
   relies on the current "dictionary full ⇒ attribute cleared" coupling before
   changing it.
