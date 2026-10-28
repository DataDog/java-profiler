# Native code

Paths in this file, including link targets, are relative to the repository root.

## Architecture — Subsystem Index

Every subsystem has a detail page under `doc/`. One-line summaries only; read the page
before working on a subsystem.

| Subsystem | Details |
|---|---|
| Call trace storage (triple-buffered ACTIVE/STANDBY/SCRATCH, 64-bit instance+slot trace IDs, lock-free rotation, freed on stop) | [doc/architecture/CallTraceStorage.md](/doc/architecture/CallTraceStorage.md) |
| String dictionary (lazily allocated arena chunks, rotation/clear/release protocols) | [doc/architecture/StringDictionary.md](/doc/architecture/StringDictionary.md) |
| RefCountGuard (lock-free RAII reader-drain before reclamation) | [doc/architecture/RefCountGuard.md](/doc/architecture/RefCountGuard.md) |
| TLS context (thread-local tracing context, distributed tracing) | [doc/architecture/TLSContext.md](/doc/architecture/TLSContext.md) |
| JVM support (HotSpot, J9, Zing) | [doc/architecture/JvmSupportLayer.md](/doc/architecture/JvmSupportLayer.md) |
| Native stack unwinding (DWARF CFA rules, arm64 temporary argument areas, JNI wrapper phases and LR/PLT, validated Linux signal-frame recovery) | [doc/architecture/JvmSupportLayer.md](/doc/architecture/JvmSupportLayer.md) |
| Profiling engines (CPU, wall-clock, allocation, native memory, liveness; allocation/liveness stack capture via `allocstack`, with JVMTI retry for unsafe frames, depth-limit truncation and separate verification scratch) | [doc/architecture/ProfilingEngines.md](/doc/architecture/ProfilingEngines.md) |
| JFR integration (FlightRecorder, metadata, constant pools, buffers) | [doc/architecture/JfrIntegration.md](/doc/architecture/JfrIntegration.md) |
| Live-heap reference chains (implementation, leak-signal gate, scheduling, design) | [doc/architecture/LiveHeapReferenceChainsImplementation.md](/doc/architecture/LiveHeapReferenceChainsImplementation.md), [doc/architecture/ReferenceChainsSignalsExplained.md](/doc/architecture/ReferenceChainsSignalsExplained.md), [doc/ReferenceChainsDesign.md](/doc/ReferenceChainsDesign.md), [doc/ReferenceChainsCollectionSummary.md](/doc/ReferenceChainsCollectionSummary.md) |
| Native memory profiling (malloc interception installed per recording and restored on stop, sampling) | [doc/architecture/NativeMemoryProfiling.md](/doc/architecture/NativeMemoryProfiling.md) |
| glibc malloc arena warning (lock-free arena walk, per-chunk rule, `MallocArenaWarning`/`MallocArenaStats` events, `arenawarn`) | [doc/architecture/MallocArenaWarning.md](/doc/architecture/MallocArenaWarning.md) |
| Startup sanity checks | [doc/architecture/SanityChecks.md](/doc/architecture/SanityChecks.md) |
| SIGSEGV-safe library patching | [doc/architecture/SigsegvPatching.md](/doc/architecture/SigsegvPatching.md) |
| Event type system | [doc/reference/EventTypeSystem.md](/doc/reference/EventTypeSystem.md) |
| Memory requirements & budgets | [doc/reference/ProfilerMemoryRequirements.md](/doc/reference/ProfilerMemoryRequirements.md) |
| Remote symbolication (+frame types) | [doc/reference/RemoteSymbolication.md](/doc/reference/RemoteSymbolication.md), [doc/reference/RemoteSymbolicationFrameTypes.md](/doc/reference/RemoteSymbolicationFrameTypes.md) |
| Per-sampler perf counters (`-PenableSamplerPerf`) | [doc/reference/SamplerPerfCounters.md](/doc/reference/SamplerPerfCounters.md) |

## Critical Invariants

These rules are load-bearing and cross-cutting: they bind any code reachable from a
signal handler or allocation hook, not only the engine handlers. Violations show up
as deadlocks, JVM crashes with our library on the hs_err stack, leaks, or arm64-only
lockups — usually only under production load, rarely in local tests.

**Async-signal safety.** Applies to everything reachable from a profiling signal
handler (SIGPROF = CPU engines, SIGVTALRM = wall clock), the SIGSEGV/SIGBUS handler,
or a malloc/free hook — that includes `Profiler::recordSample*`, the stack
walkers, `CallTraceStorage::put`, the JFR record paths and `CodeCache` lookups. Such
code can interrupt any thread at any instruction: inside the allocator, the dynamic
loader, the JVM at a safepoint, or our own code on the same thread. Socket hooks
(`send/recv/write/read` interceptors) are the deliberate exception: they run on the
calling thread, not in signal context (`nativeSocketSampler.h`), so allocation,
locking, logging and `initCurrentThreadSignalSafe()` are legal there. In
signal-reachable code, never:
- allocate: `malloc`/`new`/`free`, allocating `std::` containers or strings,
  `ProfiledThread::initCurrentThread*()`;
- block: `pthread_mutex_*`, `Mutex`/`MutexLocker`, `SpinLock::lock()`/`lockShared()`,
  `SharedLockGuard`/`ExclusiveLockGuard`. Only try-and-drop is legal —
  `SpinLock::tryLock()`, `OptionalSharedLockGuard` — because the interrupted frame on
  the same thread may already hold the lock;
- touch `thread_local`/`__thread` or a function-local static with dynamic init: the
  lazy TLS (DTV) slot and the static-init guard can `malloc` or lock (Graal aarch64
  deadlock, documented in `guards.h`). Per-thread state goes in `ProfiledThread`;
  singletons are constructed before handlers are installed;
- log: `Log::*`, `LOG_WARN`, `printf`/`snprintf`. `TEST_LOG` is async-signal-safe;
- enter the loader or the JVM: `dlopen`/`dlsym`/`dladdr`/`dl_iterate_phdr`,
  `backtrace()`, JNI functions, JVMTI — except the purpose-built ASGCT and HotSpot
  `RequestStackTrace` entry points. `VM::jni()` (`GetEnv`) is only allowed where the
  existing walk paths already call it: on HotSpot only after `VMThread::current()`
  passes `isThreadAccessible()` (JDK-8132510).

Handlers run on the interrupted thread's own stack (no `sigaltstack`): keep frames
small and put frame arrays in the pre-allocated per-stripe `CallTraceBuffer`. Mark new
async-signal-unsafe functions with `DEBUG_ASSERT_NOT_IN_SIGNAL()` (`signalSafety.h`,
active in debug and ASan builds).

**Signal-handler skeleton.** New or changed handlers follow the shared skeleton in
[ProfilingEngines.md](/doc/architecture/ProfilingEngines.md#common-signal-handler-contract):
`ErrnoPreserver` as the first local → origin check (`OS::shouldProcessSignal()` with a
`SignalCookie`; forward foreign signals via `OS::forwardForeignSignal()`) →
`SIGNAL_HANDLER_GUARD_OR_DROP()` → `InflightGuard` → `CriticalSection` → `_enabled`
acquire-load → work. Do not hand-roll `acquireCurrent()` in a handler: the macro also
maintains the per-thread signal depth that `Profiler::dlopen_hook()` uses to keep
`Libraries::refresh()` (Mutex + malloc) off the signal path. Handlers nest (SIGVTALRM
can interrupt SIGPROF; SIGSEGV is `SA_NODEFER` and can hit inside either), so:
- per-thread state shared between a handler and the code it interrupted needs a single
  atomic RMW (a handler can land between a load and a store);
- plain fields shared that way need `volatile` or `__atomic_*` so the compiler doesn't
  cache or tear them. Hardware ordering is irrelevant on the same thread.

The profiling signals (SIGPROF, SIGVTALRM) are hard-coded in `SignalBlocker` and
`blockProfilingForExit()`; a new profiling signal must be added to both.

**ProfiledThread acquisition.** A sampled thread must have a `ProfiledThread` in TLS —
it owns the `sigjmp_buf` landing pad, the `CriticalSection` flag and the signal depth.
Without one, drop the sample and count `SAMPLES_DROPPED_THREAD_LOCAL`. Pick the
accessor by context:
- signal handlers: `SIGNAL_HANDLER_GUARD_OR_DROP()` (non-sampling handlers:
  `SIGNAL_HANDLER_GUARD_NO_SAMPLE()`), then `SIGNAL_HANDLER_CURRENT_THREAD()`;
- malloc/free hooks and stack walkers: `ProfiledThread::acquireCurrent()` —
  claims a slot from a pre-allocated pool, never allocates, may return null;
- JNI entry points, JVMTI callbacks, non-signal samplers, socket hooks:
  `ProfiledThread::initCurrentThreadSignalSafe()`. Despite the name it is **not**
  async-signal-safe: it `new`s a `ProfiledThread` with profiling signals blocked. Never
  call it from a handler or a malloc hook;
- thread teardown and read-only checks: `ProfiledThread::current()` (never creates).

**Crash protection.** Stack walks and VM-structure reads fault by design. Recovery is
done by our SIGSEGV/SIGBUS handler, which is installed **only on HotSpot and OpenJ9**
(`Profiler::setupSignalHandlers()`); elsewhere treat any fault in profiler code as
fatal.
- Single reads/writes of untrusted memory: `SafeAccess::load*/store*/safeCopy`. They
  must stay `NOINLINE` (the fault is matched by PC).
- Whole walks: `sigsetjmp` + `JmpCtxScope` (`guards.h`), used exactly as documented
  there — construct the scope before `sigsetjmp(ctx, 1)` (savemask must be 1); at the
  landing pad call `SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP()` then `restore()` before
  anything else; locals written after `sigsetjmp` and read at the landing pad must be
  `volatile`. `Profiler::checkFault()` only `siglongjmp`s when the faulting PC is
  inside `libjavaProfiler`. A fault in libc (`memcpy`, `strlen`, or a compiler-emitted
  `memcpy` for a struct copy) or in JVM code inside a protected region is **not**
  recovered and crashes the JVM. Use inline loads or `SafeAccess::safeCopy` on
  untrusted memory. Enforced in CI: the `qualityChecks` task verifies every
  `sigsetjmp` site uses the `JmpCtxScope` shape (scope before the call, savemask 1,
  `SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP()` + `restore()` at the landing pad).
- `siglongjmp` skips every C++ destructor between the fault and the landing pad. No
  RAII guard, held lock, or counter may be live across it unless the landing pad
  compensates. Call `SIGNAL_HANDLER_GUARD_RELEASE()` before chaining to a foreign
  SIGSEGV handler (J9's may `siglongjmp` past us).

**Lifetime under live signals.** A handler may be mid-flight on any thread when the
profiler stops or rotates. Never free, reset, or reuse memory a handler can reach
until (a) the owning engine's `_enabled` flag is cleared with release semantics and
(b) `SignalInflight::drain()` has succeeded — on timeout, do not tear down (see
`Profiler::stop()`). Structures that rotate while recording (call-trace storage,
string dictionaries) drain their signal-context readers with
[RefCountGuard](/doc/architecture/RefCountGuard.md). Every handler that can write JFR
holds an `InflightGuard`.

**Thread termination.** An exiting thread calls `blockProfilingForExit()` before
unregistering from the engines and before releasing its `ProfiledThread`
(`Profiler::onThreadEnd()`, `unregister_and_release()` in `libraryPatcher_linux.cpp`).
Otherwise a signal can sample a half-torn-down thread, or re-acquire a
`ProfiledThread` that is never freed. The block is never undone: calling it on a
thread that keeps running silently stops profiling that thread — use `SignalBlocker`
for a temporary window.

**Thread registration.** Thread hooks (`pthread_create`, JVMTI `ThreadStart`/`ThreadEnd`)
run without `_state_lock` and overlap `start()`/`stop()`. Reach engines only through
`Profiler::registerThread()`/`unregisterThread()`, never `_cpu_engine->…` directly. An
engine with a per-thread table sizes it before `openThreadRegistration()` and frees or
replaces it only under `ThreadTablesFreeze`; that freeze closes unregistration only around
the replacement or release, never for a whole `start()` or `stop()` (CTimer frees its
table at the end of `stop()`). Details:
[ProfilingEngines.md](/doc/architecture/ProfilingEngines.md#thread-registration).

**JVMTI callbacks.** They run on any JVM thread, including ones that never went through
our `pthread_create` hook: call `ProfiledThread::initCurrentThreadSignalSafe()` first.
`GarbageCollectionStart`/`Finish` run with the VM stopped: no JNI and almost no JVMTI,
so keep them to lock-free bookkeeping and defer the rest to a profiler thread.
Profiler threads that need JNI use `VM::attachThread()`/`detachThread()`. Details:
[ProfilingEngines.md](/doc/architecture/ProfilingEngines.md#jvmti-callbacks).

**JNI/JVMTI resource cleanup.** Release every JNI local reference and JVMTI-allocated
buffer (e.g. the `GetAllThreads()` array, freed with `Deallocate`) on every exit path —
break, early return, skip — not only on the main path. On long-lived native threads (e.g.
the reference-chain BFS thread) local refs are not freed until detach.

**Clocks.** Use a monotonic clock for deadlines, TTLs and elapsed time, and convert with
the helper matching the clock that produced the timestamp (`OS::nanotime()` values are
nanoseconds; `TSC::ticks_to_millis()` takes TSC ticks). Never mix the two.

**Recording lifecycle (stop/start/restart).** State that outlives `Profiler::stop()`
(caches, tracking tables, cached class-map ids, clocks and deadlines, JNI global refs)
must be cleared in `stop()`/`start()` or be tagged with a generation and re-validated
on use; a released or cleared dictionary bumps its `generation()`. Recording-scoped
memory is freed at the end of `stop()` by `Profiler::releaseRecordingMemory()`. Anything
a late writer can still reach after `stop()` must find it null or zero-capacity under
the same lock it writes under, and must decide ownership of what it inserted while
holding that lock, never by re-reading shared state after unlocking. Write queued events
before `stop()` discards them. `_context_value_map` is deliberately kept across
`stop()` (its ids survive `ACTION_RESUME`); the class and string-label maps are
released at every stop and keep only their id counter, so ids are never reused but
entries are re-interned. Details:
[ProfilingEngines.md](/doc/architecture/ProfilingEngines.md#recording-scoped-state).

**Persistent hooks.** The `pthread_create` and `sigaction` GOT hooks are installed once
(`LibraryPatcher::initialize_persistent()`) and never unpatched, so they run before the
first `start()` and between recordings. They must stay transparent (the `pthread_create`
wrapper passes the routine's return value to `pthread_exit()`), and code they reach must
tolerate an idle profiler, including one that never started: go through the registration
gates and skip a `NULL` engine slot. Details:
[ProfilingEngines.md](/doc/architecture/ProfilingEngines.md#thread-registration),
[SigsegvPatching.md](/doc/architecture/SigsegvPatching.md#initialization-flow).

**Atomic memory ordering (arm64).** arm64 is weakly ordered (x86 is TSO); relaxed-ordering
bugs are silent arm64-only lockups. Cross-thread reads: acquire ordering
(`__ATOMIC_ACQUIRE` / `std::memory_order_acquire`), including loads of pointers published
by a release `compare_exchange`; relaxed only with a proof of no ordering dependency,
stated in a comment. Cross-thread writes: `__ATOMIC_RELEASE`, including `volatile` or plain
flags (e.g. `_running`) and configuration fields written in `start()` — a plain `volatile`
access emits no barrier on arm64, so use `__atomic_store_n(..., __ATOMIC_RELEASE)` and
`__atomic_load_n(..., __ATOMIC_ACQUIRE)`. Match every release store with an acquire load of
the same variable. Count + pointer two-phase publication: both the count load and the
pointer load need acquire semantics. Default stance: acquire for loads, release for
stores; `acq_rel` only on read-modify-write operations that both consume and publish
data; relaxed only for counters or flags with no dependent data, with a comment saying so. Beyond ordering: return addresses can carry
PAC bits — pass them through `stripPointer()` (`arch.h`) before comparing, looking up or
recording. At the sampled leaf the return address is still in LR (take it from the
`ucontext`). On Linux aarch64 there is no red zone, so memory below the sampled SP may be
overwritten by signal delivery.

**Resource discipline.** Minimize allocations — we fight malloc-arena fragmentation. This
applies to Java code on context/sampling paths too: avoid string concatenation, boxing and
varargs there, including when building error or label strings. O(N)
linear scans only for small sets (cutoff ~256 elements); larger sets need an index or binary
search. Do not resolve symbols or line tables eagerly in hot paths.

**Concurrent data structure iteration.** When iterating a concurrent array (e.g.
`CodeCacheArray`), NULL-check every slot — a slot may be count-allocated but
pointer-not-yet-stored. Never permanently advance an iteration cursor past NULL gaps; stop
at the first NULL or track the last contiguous non-NULL entry so missing entries are
retried.

**Stack completeness.** A successful carrier crossing does not establish a complete
virtual-thread stack. Preserve walker-reported truncation through JFR serialization;
see [JvmSupportLayer.md](/doc/architecture/JvmSupportLayer.md#continuation-completeness).

**JVM abstraction.** Shared code must not refer to JVM-implementation-specific code directly,
only through the abstraction files: `jvmSupport.{h,inline.h,cpp}`, `jvmThread.{h,cpp}`,
`vmEntry.{h,cpp}`, `javaApi.cpp`. Implementation-specific code lives under `hotspot/`,
`j9/`, `zing/`. When analyzing profiler issues, consult the OpenJDK sources; for OpenJ9,
the OpenJ9 GitHub project. A few legacy files (`profiler.cpp`, `flightRecorder.cpp`,
`livenessTracker.cpp`, `sanityCheck.cpp`) directly include implementation headers — the
list is in [JvmSupportLayer.md](/doc/architecture/JvmSupportLayer.md#known-boundary-exceptions);
do not add new ones and do not refactor existing ones unless asked. Enforced in CI:
the `qualityChecks` task fails on any boundary include outside the documented
exception list.

**Test logging.** `TEST_LOG` (`common.h`, debug builds only) logs lines that
`ddprof-test` can assert on; it is async-signal-safe.
