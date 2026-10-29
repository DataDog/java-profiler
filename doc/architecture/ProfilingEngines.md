<!-- Copyright 2026, Datadog, Inc. -->

# Profiling Engines

## Overview

An *engine* turns some source of events (a CPU timer, a wall-clock tick, a
JVMTI allocation callback, an intercepted `malloc`) into calls to the
`Profiler::record*()` family, which walk or look up the stack and write JFR.
Engines live in `ddprof-lib/src/main/cpp/` and, with two exceptions noted
below, derive from `Engine` (`engine.{h,cpp}`).

This document covers the CPU engines, the wall-clock engines, allocation
sampling (`ObjectSampler`), native `malloc` sampling (`MallocTracer`), the
live-heap tracker (`LivenessTracker`), and the profiler's own memory
accounting (`NativeMem`). `NativeSocketSampler` is also started by
`Profiler::start()`, but it is out of scope here.

File references use `file:line` against the tree this document was written
from. Line numbers drift over time; the function names are the stable anchor.

## The `Engine` Interface

`Engine` (`engine.h:22`) is a plain virtual base with no-op defaults
(`engine.cpp`):

| Method | Default | Purpose |
|--------|---------|---------|
| `name()` | `"None"` | CPU and wall engine names are written to JFR (`flightRecorder.cpp:1065`, `1536-1538`) |
| `check(args)` | `Error::OK` | Probe whether the engine can run, without starting it |
| `start(args)` / `stop()` | no-op | Arm / disarm the event source |
| `interval()` | `0` | Sampling period reported to JFR |
| `registerThread(tid)` / `unregisterThread(tid)` | `-1` / no-op | Per-thread setup for engines that need it |
| `enableEvents(bool)` | no-op | Flip the engine's `_enabled` gate that signal handlers check |

`Engine::updateCounter()` (`engine.h:24`) is a protected CAS helper. Nothing in `src/main/cpp` calls it.

### `cpuEngine.h` is dead code

`cpuEngine.h` declares a `CpuEngine : Engine` base "for CPU sampling engines:
PerfEvents, CTimer, ITimer" (`cpuEngine.h:14`). No translation unit includes
the header and no `CpuEngine::` member is defined anywhere. `PerfEvents`,
`CTimer`, `ITimer`, and `ITimerJvmti` derive **directly** from `Engine`
(`perfEvents.h:32`, `ctimer.h:27`, `itimer.h:23`, `itimer.h:54`).
`CTimerJvmti` derives from `CTimer` (`ctimer.h:72`).

### Engine slots in `Profiler`

`profiler.cpp:73-82` declares each engine as a file-static singleton:
`noop_engine` (a bare `Engine`, used when a mode is off), `malloc_tracer`,
`perf_events`, `wall_asgct_engine`, `wall_jvmti_engine`, `j9_engine`,
`itimer`, `itimer_jvmti`, `ctimer`, and `ctimer_jvmti`. `ObjectSampler` is a
separate singleton (`ObjectSampler::instance()`,
`objectSampler.cpp:22`). The profiler holds three engine slots:

| Slot | Chosen by | Notes |
|------|-----------|-------|
| `_cpu_engine` | `selectCpuEngine()` (`profiler.cpp:1371`) | Receives `registerThread`/`unregisterThread` and `enableEvents` |
| `_wall_engine` | `selectWallEngine()` (`profiler.cpp:1418`) | Same as above |
| `_alloc_engine` | `selectAllocEngine()` (`profiler.cpp:1453`) | `ObjectSampler` if `VM::canSampleObjects()`, else `noop_engine` |

`MallocTracer` has no slot. `Profiler::start()`/`stop()` call `malloc_tracer`
directly. `LivenessTracker` and `NativeMem` are not `Engine`s.

## Lifecycle

```
Profiler::start()                              profiler.cpp:1555
  ThreadTablesFreeze                           unregisterThread() gate closed until
                                               the CPU engine sizes its table, at the
                                               latest until return
  selectCpuEngine / selectWallEngine
  _jfr.start()
  SamplerPerf::primeClock()                    before any handler can fire
  _cpu_engine->start()          (EM_CPU)       failure -> warning, continue
    CTimer/PerfEvents: openThreadRegistration() after sizing, before listing threads
    on failure: closeThreadRegistration()
  _wall_engine->enableEvents(true)             BEFORE start(): see below
  _wall_engine->start()         (EM_WALL)
  _alloc_engine = selectAllocEngine(); start() (EM_ALLOC)
  malloc_tracer.start()         (EM_NATIVEMEM) fatal only if nativemem is the sole mode
  NativeSocketSampler::start()  (EM_NATIVESOCKET)
  if anything activated:
    switchThreadEvents(JVMTI_ENABLE)
    _cpu_engine->enableEvents(true)            LAST, only if EM_CPU activated
```

- The wall engine is enabled before its thread starts because
  `timerLoopCommon()` checks `_enabled` once on entry and returns if it is
  false (`wallClock.h:50`, `profiler.cpp:1795-1801`).
- The CPU engine is enabled last (`profiler.cpp:1901`). CPU handlers check
  `_enabled` on every signal, so nothing is lost by enabling late. It is not
  enabled when its own `start()` failed, even if another mode activated, so fds
  or timers left armed by an earlier recording cannot emit CPU samples.
- A failing CPU, wall, or alloc `start()` is logged and the remaining modes
  still start. Start fails only if no mode activated.

`Profiler::stop()` (`profiler.cpp:1922`) runs in reverse:

1. `disableEngines()` calls `enableEvents(false)` on the CPU and wall engines
   only (`profiler.cpp:1106`).
2. `SignalInflight::drain()` waits until every handler that already passed its
   `_enabled` check has left. If the drain times out, `stop()` returns an error
   and tears nothing down (`profiler.cpp:1935`).
3. `closeThreadRegistration()` clears `_engines_ready` and waits until no hook
   call that passed the check is still inside an engine.
   No thread-hook call (pthread hook or JVMTI callback) can then arm a timer
   after `CTimer::stop()`, or still be using the timer table when the next
   `start()` resizes it.
4. Then, in order: `_alloc_engine->stop()`, reference-chain teardown,
   `malloc_tracer.stop()`, the socket sampler, `_wall_engine->stop()`,
   `_cpu_engine->stop()`.

`Profiler::check()` (`profiler.cpp:2075`) runs the same selection and calls
each engine's `check()` without starting anything.

### Thread registration

Per-thread engines (`CTimer`, `PerfEvents`) learn about threads in three ways:

1. **JVMTI** `ThreadStart`/`ThreadEnd` reach `Profiler::onThreadStart()`/
   `onThreadEnd()`, which call `Profiler::registerThread()`/
   `unregisterThread()`, so they share the gates described in item 2.
   When the thread's `ProfiledThread` still exists at thread end,
   unregistration runs with profiling signals blocked
   (`blockProfilingForExit()`).
2. **Native threads**: on Linux, `LibraryPatcher`'s `pthread_create` GOT hook
   wraps the start routine (`start_routine_wrapper()`) and calls
   `Profiler::registerThread()` (`libraryPatcher_linux.cpp:553`). On exit,
   `unregister_and_release()` calls `Profiler::unregisterThread()`
   (`libraryPatcher_linux.cpp:249`). The hook runs without `_state_lock`
   and is installed before the engines start, so both calls are gated:
   - `registerThread()` needs `_engines_ready`, which `CTimer::start()` and
     `PerfEvents::start()` set via `Profiler::openThreadRegistration()` once
     their table is sized and before they list threads. `stop()` clears it.
     `PerfEvents::start()` still closes the fd of every tid missing from its
     thread list, including one the hook registered after the list was taken
     (PROF-16359).
   - `unregisterThread()` needs `_thread_tables_stable`, which is cleared only
     while `start()` may replace the table (`ThreadTablesFreeze`). It stays
     set while idle, because `PerfEvents::stop()` keeps per-thread fds open
     and this call closes the fd of a thread that exits after `stop()`.
3. **`PerfEvents` only**: a `pthread_setspecific` GOT hook on the JVM library
   (`perfEvents_linux.cpp:176`), installed in `PerfEvents::start()`
   (`perfEvents_linux.cpp:988`).

Every `Profiler::registerThread()`/`unregisterThread()` call counts itself in
flight (`HookCallScope`) for as long as it may be inside an engine. Closing a gate
(`closeThreadRegistration()` in `stop()`, `ThreadTablesFreeze` in `start()`) waits
for that count to reach zero, so no call is inside an engine while it is torn down
or its table is replaced. The gate flags and the counter use `seq_cst` on both
sides: either a call sees the gate closed, or the closer sees the call and waits.

Thread cancellation is disabled for the length of each call, because the engine
calls reach cancellation points (`close()`, `Log::warn()`). Acting on a
cancellation there would unwind through `~HookCallScope()`, which aborts with the
statically linked libgcc, or, on musl, skip it and leave the count raised. The
state is restored by a plain call made after every destructor-bearing scope of the
call, not by a guard. Current glibc acts on a pending asynchronous cancellation as
soon as it is re-enabled, and unwinding out of an implicitly `noexcept` destructor
terminates the process.

Each engine's `start()` also registers every thread that already exists.

## Common Signal-Handler Contract

The CPU and wall-clock signal handlers share one skeleton. Each engine's
deviations are listed in its own section.

```
ErrnoPreserver                       restore errno on exit
origin check (if available)          foreign signal -> forward to the chained handler, return
SAMPLER_PERF_PROBE(SP_CPU|SP_WALL)   optional timing (samplerPerf.h)
SIGNAL_HANDLER_GUARD_OR_DROP()       no ProfiledThread -> SAMPLES_DROPPED_THREAD_LOCAL, return
InflightGuard                        participate in SignalInflight::drain()
CriticalSection cs(current)          re-entrant on this thread -> return
_enabled (acquire)                   disabled -> return
tickInitWindowIfNeeded()             skip samples in the thread-init window (not every engine)
Profiler::recordSample[Delegated]()
```

`SIGNAL_HANDLER_GUARD_OR_DROP` is defined at `guards.h:115`. Inside
`recordSample()`, the handler tries to take one of `CONCURRENCY_LEVEL` (16)
striped spin locks with `tryLock()`, three attempts at most. If all three fail,
the sample is dropped and counted as `ticks_skipped` (`profiler.cpp:782-793`).
No handler blocks.

The `*Jvmti` variants call `recordSampleDelegated()` instead, which asks
HotSpot's JFR `RequestStackTrace` JVMTI extension to walk the stack
(`ctimer.h:66-71`). These variants require `VM::canRequestStackTrace()`.

## CPU Engines

### Selection

`selectCpuEngine()` (`profiler.cpp:1371-1416`):

```
cpu not requested and event is NULL/"noop"  -> noop_engine
cpu requested or event == "cpu":
    OpenJ9 without usable ASGCT             -> j9_engine (J9WallClock)
    jvmtistacks:  CTimerJvmti.check() ok    -> ctimer_jvmti
                  else ITimerJvmti.check()  -> itimer_jvmti
                  else warn, fall through
    CTimer.check() ok                       -> ctimer
    else PerfEvents.check() ok              -> perf_events
    else                                    -> itimer
event == "wall"                             -> noop_engine
event == "itimer"                           -> itimer
event == "ctimer"                           -> ctimer
any other event name                        -> perf_events
```

Because `CTimer` and `PerfEvents` are stubs outside Linux (`ctimer.h:86`,
`perfEvents.h:81`), their `check()` always fails there. With default
arguments, the result is:

| Platform | Default CPU engine | Signal | Timer |
|----------|--------------------|--------|-------|
| Linux | `CTimer` | `SIGPROF` | per-thread `timer_create` on the thread's CPU clock |
| Linux, `timer_create` unavailable | `PerfEvents` | `SIGPROF` | per-thread `perf_event_open` fd |
| macOS / other | `ITimer` | `SIGPROF` | process-wide `setitimer(ITIMER_PROF)` |

The default interval is `DEFAULT_CPU_INTERVAL` (10 ms, `arguments.h:28`),
resolved through `Arguments::cpuSamplerInterval()`.

### `CTimer` (`ctimer_linux.cpp`, Linux only)

- **Mechanism**: `registerThread(tid)` creates one POSIX timer per thread with
  the raw `__NR_timer_create` syscall. The clock is
  `((~tid) << 3) | 6`, the thread's per-thread scheduler CPU clock
  (`ctimer_linux.cpp:46-48`). The raw syscall is used because the libc wrapper
  accepts only predefined clocks (`ctimer_linux.cpp:86`). The timer notifies
  with `SIGEV_THREAD_ID` targeting `tid`, carrying
  `sival_ptr = SignalCookie::cpu()` (`ctimer_linux.cpp:73-84`). It is armed
  periodic with `timer_settime`.
- **Signal**: `SIGPROF` (`ctimer_linux.cpp:181`).
- **Origin check**: the handler accepts only `si_code == SI_TIMER` carrying
  the CPU cookie. Anything else is forwarded with `OS::forwardForeignSignal()`
  (`ctimer_linux.cpp:292-296`).
- **Per-thread table**: `_timers[tid]` holds `timer_id + 1` (0 means empty),
  sized from `OS::getMaxThreadId()`. Registration and unregistration claim
  slots with CAS, so concurrent register/unregister of one tid deletes the
  timer exactly once (`ctimer_linux.cpp:94-132`). A tid at or above
  `_max_timers` logs a warning and is not profiled.
- **`stop()`** unregisters every slot (`ctimer_linux.cpp:212-218`).
- **`CTimerJvmti`**: runs `CTimer::start()` and then replaces the `SIGPROF`
  handler with one that calls `recordSampleDelegated(ucontext, ...)`
  (`ctimer_linux.cpp:227-283`). It has no ASGCT fallback.

### `PerfEvents` (`perfEvents_linux.cpp`, Linux only)

- **Mechanism**: one `perf_event_open(attr, tid, -1, -1, 0)` fd per thread.
  `attr.sample_period = _interval`; the event type comes from
  `PerfEventType::forName(args._event)` (`perfEvents_linux.cpp:592-712`).
  The fd is made signal-driven with `F_SETFL O_ASYNC`, `F_SETSIG SIGPROF`,
  and `F_SETOWN_EX` set to the thread (`perfEvents_linux.cpp:704-706`), then
  armed with `PERF_EVENT_IOC_REFRESH 1`.
- **Signal**: `SIGPROF`. There is no cookie check. The handler only ignores
  `si_code <= 0` as an external signal (`perfEvents_linux.cpp:790`).
- **Re-arming**: `REFRESH` is one-shot. `PerfFdRearmGuard`
  (`perfEvents_linux.cpp:770`) re-arms the fd and drains the kernel ring page
  (`resetBuffer()`) on **every** handler exit, including drop paths.
- **Counter**: the sample weight comes from `readCounter()`. That is either a
  `read()` of the fd or, for probes on known functions, a register argument
  (`perfEvents_linux.cpp:734-751`).
- **Thread hook**: `start()` patches the JVM library's `pthread_setspecific`
  import so that HotSpot setting or clearing its thread TLS key registers or
  unregisters the thread (`perfEvents_linux.cpp:171-204`).
- **`stop()` is a no-op** (`perfEvents_linux.cpp:1059`): fds stay open across
  stop/start, and `registerThread()` skips threads that already have an fd.
  After stop, the cleared `_enabled` flag keeps handlers from recording.
- **Memory**: the `_events` array and any 2-page mmap ring pages are accounted
  under `NM_PERF`.
- `CSTACK_LBR` and kernel stacks (`walkKernel`) are available only with this
  engine (`profiler.cpp:1725`, `1745`).

### `ITimer` / `ITimerJvmti` (`itimer.cpp`, all platforms)

- **Mechanism**: one process-wide `setitimer(ITIMER_PROF, interval)`
  (`itimer.cpp:92-107`). `registerThread` is not overridden, so the kernel
  chooses which thread receives each `SIGPROF`.
- **Origin check**: none. `setitimer` signals arrive with no `sival` payload,
  so a foreign `SIGPROF` cannot be told apart from the profiler's own. The
  code comments call out this exposure (`itimer.cpp:44-49`).
- `ITimer` does **not** run `tickInitWindowIfNeeded()` (`itimer.cpp:63-65`).
  `ITimerJvmti` does.
- **`ITimerJvmti`** passes `nullptr` as the ucontext to
  `recordSampleDelegated()`, because the receiving thread is arbitrary
  (`itimer.cpp:143-147`). Its `stop()` also resets `SIGPROF` to `SIG_IGN`
  (`itimer.cpp:190-194`). `ITimer::stop()` only disarms the timer.

### CPU engine comparison

| | CTimer | CTimerJvmti | PerfEvents | ITimer | ITimerJvmti |
|---|---|---|---|---|---|
| Platform | Linux | Linux | Linux | any | any |
| Per-thread timer | yes | yes | yes | no | no |
| Origin check | cookie + `SI_TIMER` | cookie + `SI_TIMER` | `si_code > 0` only | none | none |
| Init-window skip | yes | yes | no | no | yes |
| Stack walk | `recordSample` | JVMTI delegated | `recordSample` | `recordSample` | JVMTI delegated (`ucontext=nullptr`) |
| `stop()` | deletes timers | deletes timers | no-op | disarms timer | disarms timer, `SIG_IGN` |

## Wall-Clock Engines (`wallClock.{h,cpp}`)

Wall-clock sampling does **not** use `ctimer` or `itimer` on any platform. A
dedicated profiler pthread picks threads and signals each one directly.

### Selection

`selectWallEngine()` (`profiler.cpp:1418-1451`): on OpenJ9, either
`J9WallClock` (JVMTI polling) or `WallClockASGCT`. On HotSpot with
`jvmtistacks` and `VM::canRequestStackTrace()`, `WallClockJvmti`. Otherwise,
`WallClockASGCT`; a requested `JVMTI` sampler that is not available falls back
to ASGCT with a warning.

### `BaseWallClock` timer loop

`BaseWallClock::start()` (`wallClock.cpp:308`) sets `_interval` (default
`DEFAULT_WALL_INTERVAL`, 50 ms) and `_reservoir_size` (default
`DEFAULT_WALL_THREADS_PER_TICK`, 16; see `arguments.h:29-31`). It then calls
the subclass `initialize()`, which installs the `SIGVTALRM` handler, and
creates the timer thread. `timerLoopCommon()` (`wallClock.h:49`) runs:

```
loop while _running:
  collectThreads(threads)       ThreadFilter::collect() if the filter is on,
                                else OS::listThreads() minus self and the
                                Libraries refresher thread
  NativeMem::setLive(NM_WALLCLOCK, capacity * sizeof(entry))
  sample = ReservoirSampler(threads)     at most _reservoir_size threads
  for each: sampleThreads(t)    OS::sendSignalWithCookie(tid, SIGVTALRM,
                                SignalCookie::wallclock())
  update WallClockEpochEvent; emit it on change or every >= 1 s
  OS::sleep(normal(interval, interval/10)), clamped to [1, 2*interval-1] ns
```

`stop()` clears `_running`, wakes the thread with `pthread_kill(WAKEUP_SIGNAL)`
(`SIGIO`, `os.h:23`), and joins it (`wallClock.cpp:330-339`).

### Signal delivery per platform

| Platform | Sender | Origin check |
|----------|--------|--------------|
| Linux | `rt_tgsigqueueinfo` with `SI_QUEUE` and the cookie in `sival_ptr` (`os_linux.cpp:411`) | Accept only `SI_QUEUE` with the wallclock cookie (`wallClock.cpp:211`) |
| macOS | Raw per-thread signal syscall; no cookie (`os_macos.cpp:304-329`) | `shouldProcessSignal()` always returns true (`os_macos.cpp:339`) |

### Handler

`WallClockASGCT::sharedSignalHandler()` (`wallClock.cpp:205`) follows the
common skeleton and then:

- Applies the optional `wallprecheck` once-per-run suppression for threads
  with no active trace context (`prepareWallPrecheck()`,
  `wallClock.cpp:94`). This can suppress a sample, or weight an "unowned
  blocked" sample.
- With `_collapsing`, reuses a cached call-trace ID keyed on PC, SP, and span
  context, which skips the unwind and increments `SKIPPED_WALLCLOCK_UNWINDS`
  (`wallClock.cpp:266-281`).
- Sets the thread state from `getOSThreadState()`. When that state is
  `UNKNOWN`, it uses `inSyscall(ucontext)` to choose between `SYSCALL` and
  `RUNNABLE`.
- Calls `recordSample(..., BCI_WALL, ...)`.

`WallClockJvmti` is identical except that it calls `recordSampleDelegated()`
with `ucontext = nullptr` and has no collapsing (`wallClock.cpp:448-493`).

### `J9WallClock` (`j9/j9WallClock.cpp`)

This engine uses no signals. A thread attached to the JVM polls
`J9Support::GetAllStackTracesExtended()` every interval and calls
`recordExternalSample()`. It records `BCI_CPU` for RUNNABLE threads and, when
idle-thread sampling is on, `BCI_WALL` for all threads
(`j9WallClock.cpp:99-148`). The same `j9_engine` object can fill both the CPU
slot and the wall slot. `start()` returns early if the engine is already
running.

## Allocation Sampling (`ObjectSampler`, `objectSampler.{h,cpp}`)

The source tree has no TLAB-specific engine class. Heap allocation sampling is
JVMTI `SampledObjectAlloc`. `BCI_ALLOC_OUTSIDE_TLAB` exists in `vmEntry.h:27`
and is handled in `profiler.cpp:430` and `hotspot/hotspotSupport.cpp:123`, but no
engine produces it; `ObjectSampler` always records `BCI_ALLOC`.

- **Capability**: `VM::canSampleObjects()` requires
  `can_generate_sampled_object_alloc_events` and, on HotSpot, JDK 11 or later
  (`vmEntry.cpp:492-494`). The callback is registered at
  `vmEntry.cpp:532`.
- **`start()`** (`objectSampler.cpp:185`): `_interval = max(args._memory,
  256 KiB)` (`objectSampler.cpp:167-170`). It starts `LivenessTracker` first,
  then calls `SetHeapSamplingInterval(_interval)`, enables
  `JVMTI_EVENT_SAMPLED_OBJECT_ALLOC`, and sets `_active`.
- **Callback** `SampledObjectAlloc()` → `recordAllocation()`
  (`objectSampler.cpp:51-154`), on the allocating Java thread, outside any
  signal handler:
  1. Resolves the class with `GetClassSignature` and `lookupClass()`. An
     unresolvable class drops the sample.
  2. If allocations or liveness are being recorded, computes
     `weight = 1 / (1 - exp(-size / interval))` and calls
     `recordJVMTISample()`. When only liveness is recorded, the sample is
     deferred (`deferred = !_record_allocations`).
  3. Rate control: every `_target_samples_per_window` (100) samples, if more
     than 1 s has passed, one thread wins a CAS and runs a `PidController`
     that adjusts `_interval` within `[configured, INT32_MAX]` and re-applies
     it (`objectSampler.cpp:122-147`, `227-261`). The environment variable
     `DDPROF_TEST_DISABLE_RATE_LIMIT=1` turns this off.
  4. Hands the object to `LivenessTracker::track()` when liveness or GC
     generations are enabled.
- **Thread safety**: `_active` is read relaxed. The rate-control counter and
  timestamp use atomics and CAS. Stack recording takes the same striped
  `tryLock` as the signal paths.
- **`stop()`**: clears `_active`, disables the JVMTI event, and calls
  `LivenessTracker::stop()`.

## Live Heap (`LivenessTracker`, `livenessTracker.{h,cpp}`)

`LivenessTracker` is **not** an `Engine` (`livenessTracker.h:209`). It is
driven by `ObjectSampler` and by JVMTI `GarbageCollectionFinish`. This
section covers only its tracking core. Leak-candidate selection and reference
chains are described in
[LiveHeapReferenceChainsImplementation.md](LiveHeapReferenceChainsImplementation.md).

- **Enablement**: `_enabled = gc_generations || record_liveness`. The tracking
  table is set up once per process and **persists across recordings**
  (`_initialized`; `livenessTracker.cpp:2095-2140`). Later starts get back the
  stored initialization result. Liveness tracking turns itself off (by setting
  `_table_max_cap = 0`) on HotSpot older than 11, when the max heap size is
  unknown, or when `Class.getName` cannot be resolved.
- **Table size**: `min(MAX_TRACKING_TABLE_SIZE (262144), max_heap /
  interval)`. It grows by doubling up to that cap (`livenessTracker.cpp:1985`).
  Memory is accounted under `NM_LIVENESS`.
- **`track()`** (`livenessTracker.cpp:2354`) runs from the allocation
  callback:
  1. Admission subsampling (`admitForTracking()`). The weight of rejected
     allocations accumulates in a thread-local `skipped` value.
  2. `NewWeakGlobalRef(object)`.
  3. `_table_lock.tryLockShared()`. If the lock is not available, the weak ref
     is deleted and the sample is dropped (`livenessTracker.cpp:2381`).
  4. Reserves a slot by CASing `_table_size`, fills it, and publishes it with
     a release store to `ready`.
  5. When the table is full, runs one forced reap-only `cleanup_table()`, may
     grow the table under the exclusive lock, and retries once.
- **GC hook**: `vmEntry.cpp:454` fans `GarbageCollectionFinish` out to
  `LivenessTracker` and `ReferenceChainTracker`. `onGC()` only bumps
  `_gc_epoch` and records heap-usage samples (`livenessTracker.cpp:2526`). The
  work happens later in `cleanup_table()`, which holds the exclusive lock,
  drops entries whose weak ref is cleared, compacts the table, and ages
  survivors. `cleanup_table()` runs from `flush()`, `stop()`, the overflow path
  in `track()`, and `maybeForceCleanup()` (called from the reference-chain
  thread).
- **Output**: `Profiler::dump()` calls `flush()` (`profiler.cpp:2153`). The
  flush runs a cleanup and then, under the exclusive lock, emits one
  `BCI_LIVENESS` deferred sample per surviving entry through
  `recordDeferredSample()` (`livenessTracker.cpp:1962`). When heap-usage
  recording is enabled, it also writes a heap-usage event.
- **Trace retention**: when enabled, `start()` registers a liveness checker
  with `CallTraceStorage` (`livenessTracker.cpp:2071`). The checker returns the
  `call_trace_id` of every published entry, so the stacks of live objects
  survive trace-storage rotation (see [CallTraceStorage.md](CallTraceStorage.md)).
  Production code never calls `CallTraceStorage::clearLivenessCheckers()`, so
  each enabled `start()` appends another checker.
- **`stop()`** cleans up and flushes the table, but deliberately leaves GC
  notifications enabled (`livenessTracker.cpp:2083-2093`).

## Native Malloc Sampling (`MallocTracer`, `mallocTracer.{h,cpp}`)

The full design is in [NativeMemoryProfiling.md](NativeMemoryProfiling.md).
In summary:

- **Classes**: `MallocHooker` owns GOT patching (`_patch_lock`,
  `_patched_libs`, `_initialized`; `mallocTracer.h:17`). `MallocTracer :
  Engine` owns the sampling state (`mallocTracer.h:32`). There is no
  `free_hook` and no `calloc_hook_dummy`. The hooks are `malloc_hook`,
  `calloc_hook`, `realloc_hook`, `posix_memalign_hook`, and
  `aligned_alloc_hook` (`mallocTracer.cpp:38-83`). `free` is not intercepted.
- **Interception**: `MallocHooker::patchLibraries()` rewrites the
  `im_malloc`/`im_realloc`/`im_aligned_alloc` GOT entries of every native
  library. It also rewrites `im_calloc`/`im_posix_memalign` unless the libc
  implements them on top of `malloc`/`aligned_alloc`
  (`detectNestedMalloc()`). `_patched_libs` only grows; hooks are never
  removed. Libraries loaded later are patched by `Libraries::refresh()`
  (`libraries.cpp:90-91`).
- **Signals**: none. Hooks run synchronously on the allocating thread.
- **Sampling**: `maybeRecord()` (`mallocTracer.cpp:312`) acquires the
  thread's `ProfiledThread` (if there is none, it increments
  `SAMPLES_DROPPED_THREAD_LOCAL`), enters a `CriticalSection` to block
  re-entry from the profiler's own allocations, then calls `shouldSample()`.
  That function is a lock-free CAS on a shared `_bytes_until_sample`, with
  Poisson-distributed intervals from a shared xoroshiro128+ state.
  `recordMalloc()` records `BCI_NATIVE_MALLOC` through `recordSample(NULL,
  ...)`. A `PidController` retunes `_interval` about once per second.
- **Lifecycle**: `start()` sets `_running` **before** patching, so a
  concurrent `dlopen` also patches the new library (`mallocTracer.cpp:400`).
  `stop()` only clears `_running`; the GOT patches stay in place.
  `MallocTracer` does not override `check()`, so it inherits `Engine::check()`,
  which always returns OK.

## Profiler Self-Accounting (`NativeMem`, `nativeMem.{h,cpp}`)

`nativeMem.{h,cpp}` is **not** a profiling engine and does not observe
application allocations. It tracks the profiler's **own** native memory in 14
categories, defined in `nativeMem.h`: `NM_CALLTRACE`, `NM_DICTIONARY`, ...,
`NM_PERF`, `NM_LIVENESS`, `NM_WALLCLOCK`, `NM_CTIMER`, `NM_MISC`.

- `record(cat, delta)` is a relaxed atomic add plus a lock-free CAS on the
  per-category peak. It is async-signal-safe, which matters because the
  call-trace arena calls it from inside sampling handlers.
- `recordAlloc()` and `recordFreeBefore()` also track allocator overhead and
  are not signal-safe on first use. `setLive()` sets a gauge to an absolute
  value and is not for signal context.
- `sample()` updates a 64-tick moving average and is single-threaded. It is
  called once per chunk: `Recording::finishChunk()` calls
  `updateNativeMemStats()`, which calls `sample()` (`flightRecorder.cpp:1082`,
  `2210`). The totals are
  exported as the `NATIVE_MEM_LIVE_BYTES`, `NATIVE_MEM_AVG_BYTES`, and
  `NATIVE_MEM_MAX_BYTES` counters (`flightRecorder.cpp:2201-2203`).

The engines above feed it: `PerfEvents` reports `NM_PERF`, `CTimer` reports
its tid-indexed timer table (`pid_max × sizeof(int)`) as `NM_CTIMER`,
`timerLoopCommon()` reports `NM_WALLCLOCK`, and `LivenessTracker` reports
`NM_LIVENESS`.

## Counters by Engine

| Engine | Counters incremented in the engine's own file | `SamplerPerf` slot |
|--------|-----------------------------------------------|--------------------|
| CTimer / CTimerJvmti | `CTIMER_SIGNAL_OWN`, `CTIMER_SIGNAL_FOREIGN` | `SP_CPU` |
| PerfEvents, ITimer, ITimerJvmti | none (the guard may increment `SAMPLES_DROPPED_THREAD_LOCAL`) | `SP_CPU` |
| WallClockASGCT / WallClockJvmti | `WALLCLOCK_SIGNAL_OWN`, `WALLCLOCK_SIGNAL_FOREIGN`, `WC_SIGNAL_QUEUE_FULL`, `WC_SIGNAL_SUPPRESSED_SAMPLED_RUN`, `WC_UNOWNED_BLOCKED_SUPPRESSED`, `WC_UNOWNED_BLOCKED_RECORDED`, `SKIPPED_WALLCLOCK_UNWINDS` (ASGCT only) | `SP_WALL` |
| J9WallClock | none | `SP_CPU` and `SP_WALL` |
| ObjectSampler | none | `SP_ALLOC` (includes `SP_LIVENESS`) |
| LivenessTracker | `LIVENESS_URGENT_BOOST_ADMITS`, `LIVENESS_URGENT_BOOST_BACKED_OFF` | `SP_LIVENESS` |
| MallocTracer | `SAMPLES_DROPPED_THREAD_LOCAL` | `SP_NATIVEMEM` |

Every engine that records through `Profiler::recordSample()` can also
increment `_failures[-ticks_skipped]` when all three lock attempts fail. The
`SamplerPerf` slots are described in
[SamplerPerfCounters.md](../reference/SamplerPerfCounters.md).
