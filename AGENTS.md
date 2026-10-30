<!-- CLAUDE BOOTSTRAP INSTRUCTIONS
If you are Claude and reading this file, check if CLAUDE.md exists in the same directory.
If CLAUDE.md does not exist or only contains the redirect + Compact Instructions below, that
is correct. If CLAUDE.md contains full project instructions (not just the redirect), you should
trim it back to contain only the following canonical content — do not drop the Compact
Instructions section, and do not let this stub grow beyond it:

# CLAUDE.md

**This file redirects to AGENTS.md for tooling-agnostic project instructions.**

Read and follow all instructions in [AGENTS.md](AGENTS.md) in this directory.

All project guidance, build commands, architecture details, and development guidelines
are maintained in AGENTS.md to support multiple AI coding tools.

## Compact Instructions

When compacting this conversation, prioritize keeping: decisions made, code/config diffs,
open questions, and file:line references. Drop raw tool output that can be re-fetched on
demand — full file contents, grep/search dumps, build/test logs — summarize these to a
one-line pointer (what was read/run and the conclusion) instead of retaining them verbatim.
-->

# AGENTS.md

This file provides guidance to AI coding assistants when working with code in this
repository. It is deliberately a thin index: rules that must always be in context live
here; subsystem details live in `doc/` (start at the [doc/README.md](doc/README.md)
index).

> **⛔ MANDATORY — KEEP THIS FILE CURRENT.** Any change to the architecture — a new
> subsystem, a removed or disabled subsystem, a changed subsystem contract (buffering
> scheme, engine, storage layout, build system, module list, JDK pattern, CI layout) —
> REQUIRES updating this file in the same change set: the affected table row/section
> here, the linked `doc/` detail page, and the [doc/README.md](doc/README.md) index
> entry (add or remove). An architecture change that lands without its AGENTS.md/doc
> update is an incomplete change — treat it as a failing check, not a nice-to-have.

**What stays inline vs. what moves to `doc/`** — apply this test when updating this
file. Inline (this file): rules that must shape behavior at unpredictable moments —
invariants whose violation causes crashes/leaks/lockups, gates and checklists
(review before PR, marker validation), writing rules for high-visibility artifacts
(PRs, comments, commits). Externalized (`doc/`): reference material read only when
working on a specific subsystem — architecture pages, build/task references,
analyses. Rules stay inline even when needed only once per task if that moment is
end-of-task, when context is most exhausted and a linked page would be skipped.
Skipping a linked page silently is forbidden: if you touched code covered by a
`doc/` page you did not read (context pressure, time), you MUST disclose it in the
task summary with an explicit `SUBSYSTEM DOC NOT READ: <path>` line — the user,
not you, decides whether to compact and redo the work with the rules in context,
or accept the risk. The same applies to any instruction in this file you could not
follow: surface it, never absorb it.
Hoist a section only when it grows with examples or scope; leave a one-line
mandatory pointer behind.

## Project Overview

The Datadog Java Profiler Library — a profiler derived from async-profiler but tailored
for Datadog's needs. Java 8+ API, C++17 native engine, custom Gradle native-build plugin,
JNI integration, Google Test for C++ units.

**Modules** (`settings.gradle.kts`): `ddprof-lib` (main library, plus `:ddprof-lib:fuzz`
and `:ddprof-lib:benchmarks`), `ddprof-test` (Java integration tests), `ddprof-test-tracer`
(tracing-context tests), `ddprof-test-native`, `ddprof-stresstest` (JMH + chaos),
`malloc-shim` (Linux allocation interceptor).

**Supported JVMs:** HotSpot, J9, Zing — see [doc/architecture/JvmSupportLayer.md](doc/architecture/JvmSupportLayer.md).
**Platforms:** Linux x64/arm64 (primary), macOS arm64/x64; musl libc handled automatically.

## Operating Rules for Agent Sessions

- Never run `./gradlew` directly. Always invoke the wrapper:
  `./.claude/commands/build-and-summarize <gradle-task...>`. It runs Gradle with
  `--console=plain -i`, captures the full output into `build/logs/<timestamp>-<task>.log`,
  and prints only the status line. On failure, read the wrapper's extracted
  "What went wrong" section and the failing task/test lines; grep the log for anything
  rarer. If no log path is given, use the newest `build/logs/*.log`.
- Never paste large log chunks into chat. If more than ~30 lines are needed, write to a
  file and point at it.
- If a step fails, print the failing command and a one-line hint, then stop.
- "build assembleDebugJar" means `./.claude/commands/build-and-summarize assembleDebugJar`.
- When renaming a symbol or concept, grep for the old name and update function names, comments and the PR title/description to the new name before requesting review.

## Build & Test Quick Reference

Configurations: `release`, `debug`, plus `asan`/`tsan`/`fuzzer` when the sanitizer runtime
is found for the selected compiler (inactive on macOS and musl), plus opt-in `coverage`
with `-PenableCoverage` (`:ddprof-lib:coverageReport`; the C++ report covers only the
`-O0 -DDEBUG` build — see [doc/building/CodeCoverage.md](doc/building/CodeCoverage.md)).

```bash
./.claude/commands/build-and-summarize buildRelease      # release library + JAR
./.claude/commands/build-and-summarize assembleAll       # all active configurations
./.claude/commands/build-and-summarize :ddprof-test:testDebug -Ptests=ClassName.methodName
./.claude/commands/build-and-summarize :ddprof-lib:gtestDebug            # all C++ tests (debug)
./.claude/commands/build-and-summarize :ddprof-lib:gtestDebug_test_callTraceStorage
JAVA_TEST_HOME=/path/to/test/jdk ./.claude/commands/build-and-summarize :ddprof-test:testDebug
```

- `buildRelease`/`buildDebug`/`buildAsan`/`buildTsan` are Gradle base-plugin
  rule-resolved aliases (`build<ConfigurationName>`) for
  `compile{Config} → link{Config} → assemble{Config}Jar`. They do not appear in
  `tasks --all`. Do not use the bare `assemble` task.
- Single Java test: `-Ptests=ClassName` / `-Ptests=ClassName.methodName` / `-Ptests="*.Pattern"`
  — unified across glibc, macOS and musl platforms.
- Useful properties: `-Pskip-native`, `-Pskip-tests`, `-Pskip-gtest`, `-PkeepJFRs`,
  `-PenableFaultInjection`, `-PenableSamplerPerf` (the last two only affect
  release/debug builds). There is **no** `-Pskip-debug-extraction` property: debug-symbol
  extraction and stripping happen unconditionally inside `linkRelease`.
- Code quality: `spotlessApply` (always before committing), `scanBuild` (Linux only),
  `:ddprof-stresstest:runStressTests`, `:ddprof-lib:runBenchmarks`.
- Container-based testing (ASan, aarch64, musl, CI repro): `./utils/run-containers-tests.sh`
  — defaults to podman; on macOS use either podman or Docker through colima
  (`--container=docker` after `colima start` — check availability with
  `podman info` / `docker info` and pick the runtime whose daemon answers).
  Full flags in
  [doc/building/TestingGuide.md](doc/building/TestingGuide.md).

Full task reference: [doc/building/GradleTasks.md](doc/building/GradleTasks.md). Native issues:
debug symbols via `buildDebug`, memory errors via ASan, suppressions in
`gradle/sanitizers/*.supp`, and `sudo sysctl vm.mmap_rnd_bits=28` if ASan crashes occur.

## Build System Architecture

Custom Kotlin-based native build plugin (`build-logic/`) instead of Gradle's
`cpp-library`/`cpp-application` plugins; it invokes `clang++`/`g++` directly. Build
configurations are discovered dynamically from `ConfigurationPresets.kt`, never hardcoded.
Two-JDK pattern: `JAVA_HOME` (build, JDK 17+, Gradle runs on 21 LTS) runs Gradle;
`JAVA_TEST_HOME` runs tests against the target JDK; target bytecode is Java 8 via
`--release 8`.

Details and troubleshooting:
[build-logic/README.md](build-logic/README.md),
[doc/building/NativeBuildPlugin.md](doc/building/NativeBuildPlugin.md) (task DSL, debug-symbol
extraction, artifact layout),
[doc/building/BuildSystemGuide.md](doc/building/BuildSystemGuide.md),
[doc/building/Versioning.md](doc/building/Versioning.md) (version from git tags),
[doc/building/JdkUpgrades.md](doc/building/JdkUpgrades.md) (JDK upgrade touchpoints).

## Architecture — Subsystem Index

Every subsystem has a detail page under `doc/`. One-line summaries only; read the page
before working on a subsystem.

| Subsystem | Details |
|---|---|
| Call trace storage (triple-buffered ACTIVE/STANDBY/SCRATCH, 64-bit instance+slot trace IDs, lock-free rotation) | [doc/architecture/CallTraceStorage.md](doc/architecture/CallTraceStorage.md) |
| String dictionary (arena chunks, rotation/clear protocols) | [doc/architecture/StringDictionary.md](doc/architecture/StringDictionary.md) |
| RefCountGuard (lock-free RAII reader-drain before reclamation) | [doc/architecture/RefCountGuard.md](doc/architecture/RefCountGuard.md) |
| TLS context (thread-local tracing context, distributed tracing) | [doc/architecture/TLSContext.md](doc/architecture/TLSContext.md) |
| Profiling engines (CPU, wall-clock, allocation, native memory, liveness) | [doc/architecture/ProfilingEngines.md](doc/architecture/ProfilingEngines.md) |
| JFR integration (FlightRecorder, metadata, constant pools, buffers) | [doc/architecture/JfrIntegration.md](doc/architecture/JfrIntegration.md) |
| Live-heap reference chains (implementation, signal scheduling, design) | [doc/architecture/LiveHeapReferenceChainsImplementation.md](doc/architecture/LiveHeapReferenceChainsImplementation.md), [doc/architecture/ReferenceChainsSignalsExplained.md](doc/architecture/ReferenceChainsSignalsExplained.md), [doc/ReferenceChainsDesign.md](doc/ReferenceChainsDesign.md), [doc/ReferenceChainsCollectionSummary.md](doc/ReferenceChainsCollectionSummary.md) |
| Native memory profiling (malloc/free interception, sampling) | [doc/architecture/NativeMemoryProfiling.md](doc/architecture/NativeMemoryProfiling.md) |
| Startup sanity checks | [doc/architecture/SanityChecks.md](doc/architecture/SanityChecks.md) |
| SIGSEGV-safe library patching | [doc/architecture/SigsegvPatching.md](doc/architecture/SigsegvPatching.md) |
| Event type system | [doc/reference/EventTypeSystem.md](doc/reference/EventTypeSystem.md) |
| Memory requirements & budgets | [doc/reference/ProfilerMemoryRequirements.md](doc/reference/ProfilerMemoryRequirements.md) |
| Remote symbolication (+frame types) | [doc/reference/RemoteSymbolication.md](doc/reference/RemoteSymbolication.md), [doc/reference/RemoteSymbolicationFrameTypes.md](doc/reference/RemoteSymbolicationFrameTypes.md) |
| Per-sampler perf counters (`-PenableSamplerPerf`) | [doc/reference/SamplerPerfCounters.md](doc/reference/SamplerPerfCounters.md) |
| Test flakiness analysis | [doc/reference/TestFlakinessAnalysis.md](doc/reference/TestFlakinessAnalysis.md) |

Key source locations: Java API `ddprof-lib/src/main/java/com/datadoghq/profiler/JavaProfiler.java`;
C++ engine `ddprof-lib/src/main/cpp/` (implementation-specific code under `hotspot/`, `j9/`,
`zing/`); native libraries `ddprof-lib/build/lib/main/{config}/{os}/{arch}/`; gtest tests
`ddprof-lib/src/test/cpp/`; Java tests `ddprof-test/src/test/java/`.

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
[ProfilingEngines.md](doc/architecture/ProfilingEngines.md#common-signal-handler-contract):
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
[RefCountGuard](doc/architecture/RefCountGuard.md). Every handler that can write JFR
holds an `InflightGuard`.

**Thread termination.** An exiting thread calls `blockProfilingForExit()` before
unregistering from the engines and before releasing its `ProfiledThread`
(`Profiler::onThreadEnd()`, `unregister_and_release()` in `libraryPatcher_linux.cpp`).
Otherwise a signal can sample a half-torn-down thread, or re-acquire a
`ProfiledThread` that is never freed. The block is never undone: calling it on a
thread that keeps running silently stops profiling that thread — use `SignalBlocker`
for a temporary window.

**JVMTI callbacks.** Callbacks run on whichever JVM thread triggers the event —
including compiler, VM and GC threads that never went through our `pthread_create`
hook — so call `ProfiledThread::initCurrentThreadSignalSafe()` first.
`GarbageCollectionStart`/`Finish` run while the VM is stopped: no JNI, and no JVMTI
beyond the raw-monitor, memory-management and environment-local-storage functions
(JVMTI spec). Keep them to lock-free bookkeeping and defer work to a profiler thread
(see `ReferenceChainTracker::onGCStart()`). Profiler threads that need JNI attach with
`VM::attachThread()` and call `VM::detachThread()` before they exit.

**JNI/JVMTI resource cleanup.** Release every JNI local reference and JVMTI-allocated
buffer (e.g. the `GetAllThreads()` array, freed with `Deallocate`) on every exit path —
break, early return, skip — not only on the main path. On long-lived native threads (e.g.
the reference-chain BFS thread) local refs are not freed until detach.

**Clocks.** Use a monotonic clock for deadlines, TTLs and elapsed time, and convert with
the helper matching the clock that produced the timestamp (`OS::nanotime()` values are
nanoseconds; `TSC::ticks_to_millis()` takes TSC ticks). Never mix the two.

**Recording lifecycle (stop/start/restart).** State that outlives `Profiler::stop()`
(caches, frontier/tracking tables, cached class-map ids, clocks and deadlines, JNI global
refs) must either be cleared in `stop()`/`start()` or be tagged with a generation and
re-validated on use. `Profiler::start()` clears `_class_map` only on a reset start
(`ACTION_START` or the first start); `ACTION_RESUME` keeps it. A cleared dictionary
invalidates every stored class id, so state that caches ids must be re-validated on a
reset start. If the `RefCountGuard` drain times out, `clearAll()` leaves the dictionary
unchanged. Events queued since the last `dump()` must be written before
`stop()` discards them.

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
see [JvmSupportLayer.md](doc/architecture/JvmSupportLayer.md#continuation-completeness).

**JVM abstraction.** Shared code must not refer to JVM-implementation-specific code directly,
only through the abstraction files: `jvmSupport.{h,inline.h,cpp}`, `jvmThread.{h,cpp}`,
`vmEntry.{h,cpp}`, `javaApi.cpp`. Implementation-specific code lives under `hotspot/`,
`j9/`, `zing/`. When analyzing profiler issues, consult the OpenJDK sources; for OpenJ9,
the OpenJ9 GitHub project. A few legacy files (`profiler.cpp`, `flightRecorder.cpp`,
`livenessTracker.cpp`, `sanityCheck.cpp`) directly include implementation headers — the
list is in [JvmSupportLayer.md](doc/architecture/JvmSupportLayer.md#known-boundary-exceptions);
do not add new ones and do not refactor existing ones unless asked. Enforced in CI:
the `qualityChecks` task fails on any boundary include outside the documented
exception list.

**Test logging.** `TEST_LOG` (`common.h`, debug builds only) logs lines that
`ddprof-test` can assert on; it is async-signal-safe.

## Development Guidelines

- Never replace the code you work on with stubs. Never "fix" tests by testing constants
  against constants. Never claim success until all affected tests pass: `testDebug` for
  Java-visible behaviour, `:ddprof-lib:gtestDebug` for C++. For changes to
  signal-handler paths, atomics, crash protection or thread lifecycle, also run the ASan
  configuration where available (`gtestAsan`, `testAsan`) and, without arm64 hardware,
  the aarch64 container (`./utils/run-containers-tests.sh --arch=aarch64`).
  `assert()` is compiled out of release builds (`-DNDEBUG`): never rely on it for safety
  and never put side effects in it.
- Platform-specific code goes in per-OS implementation files (`os_linux.cpp`,
  `os_macos.cpp`, `libraryPatcher_linux.cpp`, etc.), never in a single shared file guarded
  by `#ifdef`. Name new files `<module>_<os>.cpp`.
- Provide javadoc for public classes and methods, and for non-trivial private/package-private
  code, including C++ algorithms (probing/compaction loops, index management,
  randomization): state the invariant and why the approach is needed. Verify every javadoc
  claim (thread safety, ownership, nullability, return values, clearing semantics, failure
  modes) against the implementation; public Javadoc must not reference private symbols.
- Provide comprehensive tests for new functionality: every branch, marker and error path
  (including CI and shell scripts) needs a test that fails when that branch is removed or
  mistyped — every new guard and boundary branch (null inputs, exact size/index limits,
  first value rejected past a capacity), counter label and RAII guard contract, and every
  new branch in concurrency, eviction, overflow and aging logic. Tests that exercise only
  an empty or trivial state, and manual runs, do not count. Each test must assert its
  claim (no print-only checks), fail if the behavior it names is removed, and not
  duplicate another test's assertions. Tests must fail fast on missing data: assert that
  JFR fields and accessors the event requires are non-null before any loop, and cover
  every event field and code path the feature writes.
- Bug fixes need a test in the same PR, not a follow-up: it fails before the fix and
  passes after. Native-only fixes need a gtest in `ddprof-lib/src/test/cpp`. Assert that
  the scenario was actually reached (e.g. threshold crossed, signals suppressed), not just
  that some result exists.
- Treat caller contract violations (null arguments, mismatched array lengths, an operation
  that must never fail in a test) as bugs: throw instead of returning false or
  incrementing a failure counter, and do not add validation that duplicates what the loop
  already checks.
- Explain in a comment why a non-obvious call, init-order assumption, sentinel return value
  (e.g. 0 meaning miss/full), omitted lock, unsynchronized access or read of a specific
  buffer (e.g. standby) is safe, and why a workaround or test exclusion exists.
- Keep code lean and easy to follow; factor self-contained code into short functions with
  explicit names. Datadog-specific extensions are integrated directly into base files (e.g.
  `stackWalker.h`); exclude `ddprof-lib/build/async-profiler` from usage searches.
- Copyright: new source files (including tests) start with the short header
  `Copyright <current year>, Datadog, Inc.` — no full license text block. When modifying
  an existing Datadog copyright, update the end year (e.g. `2025, 2026, Datadog`) in every
  file the change touches, including test, moved and refactored files. Preserve all other
  copyrights. Add a copyright line to modified C/C++/Java/Kotlin files missing one; CI and
  config files (Dockerfiles, `.gitlab/**`) are exempt.
- Commits: logical chunks, messages based solely on the actual diff. Always run
  `spotlessApply` before committing. Never commit files from other projects or scratch files.
  **Never commit design artifacts automatically** — plans, specs, review reports, audit
  findings, session notes, analysis dumps — even when they live in the repo tree. Always
  ask for permission first and commit them only if the user explicitly says so.
- Scope: keep each PR scoped to its stated purpose. Put unrelated production changes
  (e.g. a separate bug fix found while working), renames and cleanups in their own PR, do
  not add code with no production caller (stage it in the PR that needs it), and do not
  delete passing tests without stating why. When a change alters behavior described in
  `doc/` or in comments, update those in the same PR.
- Before requesting review, self-check the diff for unused variables, unused or duplicated
  macros, dead code (methods, JNI entry points, fields, no-op functions, empty files left
  without callers; test-only helpers stay only if marked as such) and misspelled
  identifiers/comments. Write the PR title and description from the actual diff, re-check
  them after the scope changes, and describe crash or bug mechanisms only as far as the
  code and tests confirm.
- C/C++ style: match the surrounding indentation and spacing exactly; don't split inline
  logic into helpers unless reused or genuinely hard to follow; extract code that appears a
  second time (e.g. in copy constructors, assignment operators) into one shared helper; use
  `static_cast`/`reinterpret_cast`, not C-style casts; give file-local helpers internal
  linkage (`static`); no commented-out code, redundant `inline` on in-class or constexpr
  definitions, redundant access specifiers, or redundant conditions — a disjunct equivalent
  to an adjacent check is dead; remove it, or keep it only as a deliberate defensive guard
  whose comment does not claim it catches a distinct case; add duplicated fast-path variants
  (e.g. `JavaCritical_*`) only for demonstrably performance-critical methods.
- **Comment budget (mechanical gate).** Before finishing any change, run a prune pass
  over every comment and javadoc you wrote: each comment ≤3 lines, and each line must
  state a distinct constraint (a non-obvious mechanism, invariant, or consequence) that
  the reader could not get from the code. A comment that needs more than 3 lines
  requires per-line justification in the task summary. Prefer spending the effort on
  cutting — a verbose comment is review surface, not safety. The same cut applies to
  paragraphs in `doc/` pages and PR descriptions: fewer sentences that each carry a
  fact beat more sentences that carry emphasis. This gate complements the comment
  rules above; it does not replace them.
- Comments: "why" comments must reference concrete mechanisms (e.g. "ASAN's allocator
  lock is reentrant"), never speculative claims about HotSpot/glibc/ASAN/ISA internals — if
  unsure, describe the observable symptom. Describe current behavior, not history; cite no
  tickets, plan documents, design docs or line numbers (refer to symbols). Name each
  thread or actor explicitly. Scope words ("only", "every", "never blocks", "single-threaded",
  "no lock needed") and invariants (e.g. "always leaves a terminator") must hold on every
  branch and for every caller thread, including early returns, timeouts and `siglongjmp`.
  Check the actual callers before claiming a context (signal handler vs JNI). Prefer a
  named `constexpr` over a comment restating a magic number. Comments on workarounds state
  what breaks without them (symptom, JDK/arch/libc) and when they can be removed. State
  each fact once, and omit comments that restate an obvious bounds check. After any
  change, refactor or API rename, re-read the nearby comments against the final diff and
  grep for the old name or behavior (including headers, tests and callers' comments).
  Proofread comments, javadoc and exception messages. Hold user-facing operational
  messages (error/warning logs, script and CLI output) to the same standard of accuracy:
  state only what is known to be true, and recommend only next steps that can actually
  succeed — never advise a retry that cannot clear the condition, never report a pending
  state (e.g. a run awaiting approval) as failed, and never warn that something may still
  be running when it is known to be terminal.
- **RAII for every acquire/release pair** (C/C++). A lock, a heap allocation, or a flag
  that must be restored is released by a guard or owner destructor, not by a manual call
  at each exit. Reuse `SharedLockGuard`, `ExclusiveLockGuard`, `OptionalSharedLockGuard`,
  `MutexLocker`, `CriticalSection` before you add a type. A new owner type is non-copyable
  and hands over ownership explicitly (the receiver sets the owner's pointer to `nullptr`).
  A manual pair needs a comment that says why a guard scope cannot express it. In code that
  shares a lock with signal handlers, end an owner that frees memory outside the exclusive
  critical section, because its destructor frees at scope end.
- Always challenge proposals with deep analysis when you have hard evidence.
- CI and automation scripts: before rewriting a script invoked from `.gitlab-ci.yml` or
  `.gitlab/**/*.yml`, run `git log -p -- <script>` and enumerate every behavior branch
  (fallbacks, env-var-driven paths, error exits); preserve all unless asked to drop one.
  Grep the calling jobs for how it is invoked (env vars, expected exit codes). When
  removing an item from a default list or config (an antagonist, a test tag, a feature
  flag) or deleting a script or file, grep the whole repo (including `.gitlab/**`) and cite
  the file/line proving it is unused. After changing a CI-invoked script, run `bash -n` and
  trace each CI job that calls it.

## Work Tracking

Work runs in four phases — Intent → Design → Build and Test → Deploy — with the
tracker ticket as the system of record: decisions and evidence land there, so anyone
can pick the work up without reconstructing a conversation. Datadog engineers
track work in Jira (`PROF-<n>`); external contributors use GitHub issues — every
rule applies to whichever tracker holds the ticket. **Read
[doc/WorkTracking.md](doc/WorkTracking.md) before starting tracked work** — it is
the phase-by-phase process reference; skipping it must be disclosed per the rule
at the top of this file.

**Verification first.** No transition happens on claims: actionable ticket before
work, acceptance criteria before code, tests and review before merge, production
verification before closure. Agents must be able to test, observe, and iterate
against clear acceptance criteria; the loop Build → Run/Deploy → Exercise →
Inspect → Revise closes with a rule — **fix the code, not the expectation** (and a
criterion changes only with the engineer's sign-off). Agents own execution; humans
own judgment: they approve the intent, the acceptance criteria, the merge, and any
rollout/rollback. The PR template and CI gates are the part neither humans nor
agents can bypass.

- **Evidence states.** Every check is reported as `passed` / `failed` / `blocked` /
  `inconclusive` — never prose summaries; observed results are kept separate from
  their interpretation; missing evidence means unverified. Evidence binds to the
  exact candidate — a changed candidate invalidates it. "It merged" is not done:
  closure requires the acceptance criteria demonstrably met and, for user-facing
  changes, verified in production.
- **Never weaken a gate.** The agent fixes failures — it never disables a required
  check, weakens an agreed expectation, or changes a tolerance to pass. Hooks,
  CI, and access control are authoritative even when a local hook does not fire;
  `AGENTS.md` and skills are advisory guidance.
- **Isolation and attribution.** One task per workspace/worktree; subagents for
  bounded jobs; checks from separate branches never validate the merged result —
  re-verify it. Parallel sessions never broaden authority: they inherit the
  starter's permissions and stay attributable to that engineer; evidence
  identifies the session, candidate, and configuration that produced it. Claim no
  more parallel work than you can drive to a verified state.

Mechanical gate: a PR must reference its tracker ticket — a Jira `PROF-<n>` key or
a GitHub issue `#<n>` — validated in CI. The rest of the tracking contract
([doc/WorkTracking.md](doc/WorkTracking.md)) is enforced by review discipline.
Existing production-change guidelines and review rules still apply in full; the
tracking rules add requirements on top, they replace nothing.

## Agentic Code Review (mandatory before opening a PR)

No pull request is opened until an agentic code review — run over the full change
set intended for the PR — has completed and its findings have been fixed or
explicitly waived by the user. Use whatever review capability the current harness
provides; if several options exist, prefer the `sphinx` skill (`/sphinx review`).
If the harness has none, say so plainly and get explicit user sign-off before
opening the PR without a review — never silently skip it.

Whether a review ran for the *current* change set is tracked by a marker file,
because review state does not survive into a fresh session.
1. **Marker.** After a completed review, write a marker file —
   `<worktree>/.sphinx/review-state.json` in this setup (`.sphinx/` is gitignored;
   if your harness's ignored paths differ, use any gitignored location) — so the
   marker is worktree-local and never committed. Record in it: the review tool
   used, the base ref
   the diff was reviewed against, the head commit SHA, the review session id
   (`slr…`/handle), the diff digest, and the date. Diff digest =
   `git diff <base> | git hash-object --stdin` combined with
   `git ls-files --others --exclude-standard | git hash-object --stdin` (untracked
   files count too). Whoever drives the review writes the marker — including when
   the user ran `/sphinx review` manually and reports it back; in that case record
   it before proceeding.
2. **Validation.** Before opening a PR, recompute both digests and compare with the
   marker. Missing marker, different base, different head SHA, or different digests
   → the review is stale: re-run `/sphinx review` over the current change set. Do
   not silently skip the re-check.
3. **Findings.** Critical/High findings are fixed (or user-waived) before the PR is
   opened; the review tool's fix/addressing flow handles the loop when it has one.
   Mention the review outcome in the PR description.

## Pull Request Descriptions and Comments

These rules apply to PR descriptions and to every comment a session writes — PR
comments, review replies, Jira work-item comments. Only the PR-template rule is
description-specific:

- **Follow the PR template strictly** (descriptions only) — every section it
  defines is filled in or explicitly marked N/A; do not invent a different
  structure.
- **Professional typesetting and layout.** Structure the description for scanning:
  short sections with meaningful headings, bullets for enumerations, tables for
  comparisons, `code spans` for identifiers and commands, fenced blocks for code/logs.
  Keep paragraphs to 2-4 sentences; never walls of text. Bold sparingly, for key
  terms only.
- **Write concisely and to the point**, in Simplified Technical English: short
  declarative sentences, one idea per sentence, no filler, no marketing tone.
  A reviewer reads the description before the diff — optimize for that first read.
- **Explain the WHYs, not the WHATs.** Focus on non-obvious motivation and
  limitations: why this approach was chosen, what alternatives were rejected and
  why, what constraints shaped the design, what the change does NOT fix. Do not
  reiterate what the code obviously shows. When a change deliberately alters
  behavior with user-visible impact (JFR event schema, signal volume, resident
  memory, suppression scopes) or accepts a recurring per-call or footprint cost,
  state the decision and the accepted cost explicitly and flag it for reviewer
  acknowledgment — never leave it implicit in code, a test rename, or a leftover
  template marker in the description.
- **Only the final state matters.** Never include ephemeral working knowledge —
  investigation detours, dead-end hypotheses, intermediate states, tool runs,
  session history. If a detail did not survive into the final change, it does not
  belong in the description.

## CI / Automation Script Changes

- Before rewriting or replacing a script invoked from `.gitlab-ci.yml`, `.gitlab/**/*.yml`,
  `.github/workflows/*.yml`, or any CI job, run `git log -p -- <script>` (or diff against the
  version being replaced) and enumerate every behavior branch it has — fallbacks,
  env-var-driven paths, error exits. Preserve all of them unless explicitly asked to drop
  one; do not silently narrow behavior while refactoring.
- Grep the calling CI files for how the script is invoked (env vars set, exit codes expected)
  and confirm the rewrite still satisfies every caller, not just the common/local case.
- When removing an item from a default list or config (an antagonist, a test tag, a feature
  flag), cite the exact file/line proving it is inert or unused in that context before
  removing it — never remove based on assumption alone.
- After changing a CI-invoked script, run a syntax check (e.g. `bash -n <script>`) and trace
  through each CI job that calls it before considering the change complete.

## Documentation Rules

- All documentation files in `doc/` use PascalCase naming (e.g. `BuildSystemGuide.md`);
  `doc/README.md` is the only lowercase exception. New subsystem docs go in
  `doc/architecture/` or `doc/reference/`; build docs in `doc/building/`.
- Every doc page must be indexed in [doc/README.md](doc/README.md). Both rules are
  enforced in CI by the `qualityChecks` task; design artifacts under `docs/sphinx/`,
  `.sphinx/`, and similar scratch paths must never be tracked.
- Documentation reflects the current state — never transient/historical notes, and never
  claims that aren't true of the code. Verify numbers before writing them down. Preserved
  historical sections of landed design/handover docs ("Suggested next steps", unverified
  hypotheses, open items) must be rewritten or deleted once the work they instruct is done:
  a reader must never be pointed at already-finished work.
- Update this file from repeated failures: when an agent repeats a mistake or needs
  the same undocumented explanation twice, it proposes a concise correction here
  (or to the affected `doc/` page); the responsible team reviews it, and stale
  instructions are removed. Link to deeper sources instead of copying large
  documents into this file.
- Never mention internal plan/design/implementation phases or artifacts in docs or code
  comments — no references to plan files, task lists, review/audit reports, "phase N",
  "as designed in…", "this used to…". They are meaningless outside the session that
  produced them. State the current behavior, the concrete mechanism, and (where
  warranted) the incident or constraint that motivates it — nothing about how the
  change came to be.
