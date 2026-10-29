<!-- Copyright 2026, Datadog, Inc. -->

# JVM Support Layer

## Scope

The profiler runs on three JVM implementations: HotSpot, OpenJ9 (J9), and
Zing. Code that depends on one implementation lives in a subdirectory of
`ddprof-lib/src/main/cpp`:

| Directory | Implementation | Entry class |
|---|---|---|
| `hotspot/` | HotSpot (OpenJDK, Oracle, GraalVM, DCEVM) | `HotspotSupport` (`hotspot/hotspotSupport.{h,cpp}`) |
| `j9/` | OpenJ9 / IBM J9 | `J9Support` (`j9/j9Support.{h,cpp}`) |
| `zing/` | Azul Zing | `ZingSupport` (`zing/zingSupport.{h,cpp}`) |

Shared code must stay independent of the JVM implementation. When it needs
implementation-specific behavior, it calls one of the abstraction files
(`AGENTS.md`, "JVM implementation specific code"):

- `jvmSupport.h`, `jvmSupport.inline.h`, `jvmSupport.cpp`: the `JVMSupport` facade
- `jvmThread.h`, `jvmThread.cpp`: the `JVMThread` native-thread facade
- `vmEntry.h`, `vmEntry.cpp`: the `VM` class, VM detection, and the JVMTI/JNI entry points
- `javaApi.cpp`: the JNI methods behind `com.datadoghq.profiler.JavaProfiler`

These files are the boundary. They may include `hotspot/`, `j9/`, and `zing/`
headers, and they dispatch on the detected VM. Other shared code should call
`JVMSupport::*`, `JVMThread::*`, or `VM::*` instead. The current exceptions are
listed under [Known boundary exceptions](#known-boundary-exceptions).

The build compiles all three implementations on every platform. The native
plugin collects `**/*.cpp` recursively under `src/main/cpp`
(`build-logic/conventions/src/main/kotlin/com/datadoghq/native/NativeBuildPlugin.kt:108`).
The implementation is chosen at run time, not at compile time. Only the
architecture-specific HotSpot files are guarded by the preprocessor, so each
compiles only on its own architecture: `hotspot/hotspotStackFrame_x64.cpp:7`
(`#ifdef __x86_64__`), `hotspot/hotspotStackFrame_aarch64.cpp:7`, and
`hotspot/stubUnwindInfo.cpp:6` (`#ifdef __aarch64__`).

## Implementation selection at load time

The VM type is detected once, in `VM::initShared()` (`vmEntry.cpp:229`). Every
load path goes through this function:

| Load path | Entry point | Calls |
|---|---|---|
| `-agentpath` at JVM start | `Agent_OnLoad` (`vmEntry.cpp:737`) | `VM::initProfilerBridge(vm, false)` (`vmEntry.cpp:747`) |
| `System.loadLibrary` | `JNI_OnLoad` (`vmEntry.cpp:755`) | `VM::initLibrary(vm)` → `initShared()` + `ready()` (`vmEntry.cpp:389-396`) |
| `JavaProfiler.init0()` | `javaApi.cpp:71` | `VM::initProfilerBridge(nullptr, true)` (`javaApi.cpp:80`) |

`initShared()` returns early once `_jvmti` is set, so the detection runs only once.

Detection steps:

1. **`java.vm.name`** (`vmEntry.cpp:250-257`). The VM is HotSpot if the name
   contains `OpenJDK`, `HotSpot`, `GraalVM`, or `Dynamic Code Evolution`. If the
   VM is not HotSpot, a name containing `Zing` sets `_zing`, and a name
   containing `OpenJ9` sets `_openj9`. The name `Zero` is recorded separately as
   `is_zero_vm`, and only affects code marking.
2. **J9 confirmation** (`vmEntry.cpp:270-271`). `_openj9` is overwritten with
   `!_hotspot && J9Support::initialize(...)`. This call looks for the
   `com.ibm.*` JVMTI extension functions. It returns true only if
   `GetOSThreadID`, `GetStackTraceExtended`, and `GetAllStackTracesExtended` are
   all present (`j9/j9Support.cpp:34-58`). So any non-HotSpot VM that exposes
   these extensions is treated as J9, whatever its `java.vm.name` says.
3. **JVM library** (`vmEntry.cpp:219-221`). On J9 the library is
   `libj9vm`. On other VMs it is the library that contains `AsyncGetCallTrace`.
4. **Code marking** (`vmEntry.cpp:360-384`). Each VM gets its own
   name-based classifiers, which mark frames as interpreter, VM runtime, or
   compiler entry:
   - J9 marks code in `libj9vm`, `libj9jit`, `libj9gc`, and `libj9jvmti`.
   - Zing marks its runtime entries.
   - Zero marks its interpreter.
   - All other VMs mark their compiler entries.

The result is available through `VM::isHotspot()`, `VM::isOpenJ9()`, and
`VM::isZing()` (`vmEntry.h:216-221`). The abstraction files branch on these
predicates. More detection-dependent setup:

- `VM::ready()` initializes `VMStructs` only on HotSpot (`vmEntry.cpp:605-612`).
  It can be called more than once. A static flag ensures that the signal
  handlers are installed only once.
- `can_retransform_any_class` is disabled on J9 (`vmEntry.cpp:502`).
- The JFR `RequestStackTrace` extension is probed only on HotSpot (`vmEntry.cpp:519-521`).
- The profiler installs its SIGSEGV/SIGBUS handlers only on HotSpot and J9
  (`profiler.cpp:1168`).
- On Zing, `GC_TRACES | LAST_JAVA_PC` is forced into `_safe_mode` (`profiler.cpp:1587`).

`JVMSupport::initialize()` (`jvmSupport.cpp:32-57`) runs after detection, from
`Profiler::start()`/`Profiler::init()` (`profiler.cpp:1417`, `profiler.cpp:1437`).
It calls `JVMThread::initialize()`, then checks the `ProfiledThread` TLS key.
If either step fails, profiling is disabled.

## `jvmSupport.h` / `jvmSupport.inline.h`: the `JVMSupport` facade

`JVMSupport` has only static members. It declares `HotspotSupport` as a friend
(`jvmSupport.h:35`), so HotSpot code can read its private jmethodID load state.

| Function | HotSpot | J9 / Zing |
|---|---|---|
| `initialize()` | shared (`JVMThread` + `ProfiledThread` TLS) | shared |
| `initExecution(args, jvmti, jni)` | selects `Fully_loaded`, `Partial_loaded`, or `Lazy_loaded` via `HotspotSupport::shouldPreloadJmethodIDs` / `canResolveLazily` / `initLazyResolution` (`jvmSupport.cpp:79-94`) | always `Fully_loaded`. `fjmethodid=lazy` only logs a warning (`jvmSupport.cpp:95-97`) |
| `walkJavaStack(request)` | `HotspotSupport::walkJavaStack` | ASGCT through `asyncGetCallTrace()`. Debug builds assert that the event is CPU, wall, native malloc, or native socket (`jvmSupport.cpp:112-117`) |
| `canUnwind(frame, pc)` (inline) | `HotspotStackFrame::unwindAtomicStub` | `false` |
| `isJitCode(pc)` (inline) | `JitCodeCache::isJitCode` | `false` |
| `runtimeStubsMemoryUsage()` (inline) | `JitCodeCache::runtimeStubsMemoryUsage` | `0` |
| `loadAllMethodIDsIfNeeded` / `loadMethodIDsIfNeeded` | `HotspotSupport::loadMethodIDsIfNeededImpl` or `registerClass` (lazy) | `loadMethodIDsImpl`: `GetClassMethods` on every class (`jvmSupport.cpp:229-247`) |
| `enterRedefinitionCall` / `exitRedefinitionCall` / `beforeClassRedefinition` / `afterClassRedefinition` | forwarded to `HotspotSupport` | no-op, except that `afterClassRedefinition` reloads the class's jmethodIDs after a successful redefinition |
| `beginDump` / `endDump` | forwarded to `HotspotSupport` | no-op |
| `resolve(method, bci, result)` (inline) | `HotspotSupport::resolve` (raw `Method*` frames) | `assert(false)` and returns `false`. Raw frames come only from HotSpot `walkVM` |
| `isHidden(modifiers)` (inline) | shared modifier-mask test | shared |

`jvmSupport.inline.h` includes `hotspot/hotspotSupport.h` directly
(`jvmSupport.inline.h:9`). Any file that includes the inline header therefore
gets HotSpot declarations, but it should still call only `JVMSupport::*`.

Callers in shared code:

- Stack walking calls `walkJavaStack` (`profiler.cpp:717`).
- `stackWalker.cpp:80-82` and `perfEvents_linux.cpp` call `isJitCode` and
  `canUnwind`. Both are signal-handler paths, and on non-HotSpot VMs they
  reduce to constant returns.
- The JFR writer calls `resolve`, `beginDump`, and `endDump`
  (`flightRecorder.cpp:764`, `flightRecorder.cpp:1035-1037`).
- The class hooks in `vmEntry.cpp` call the load and redefinition functions:
  `ClassPrepare` at `vmEntry.cpp:641-645`, and the
  `RedefineClasses`/`RetransformClasses` hooks at `vmEntry.cpp:687-731`.

## `jvmThread.h` / `jvmThread.cpp`: the `JVMThread` facade

`JVMThread` keeps a pointer to the VM's own thread structure for the current
thread in a `ThreadLocal`. It also keeps the `java.lang.Thread.tid` field ID.

- `initialize()` (`jvmThread.cpp:16-30`) resolves the current thread through
  `currentThreadSlow()` (`jvmThread.cpp:36-57`):
  - J9: `J9Support::j9thread_self()`
  - Zing: `ZingSupport::initialize(thread)`, which reads `Thread.eetop`
    (`zing/zingSupport.cpp:21-27`)
  - HotSpot: `VMThread::initialize(thread)`, which also reads `eetop` and
    calibrates `VMThread` offsets (`hotspot/vmStructs.cpp:650-670`)
- `current()` / `key()` give access to the cached pointer and its pthread key.
  `perfEvents_linux.cpp:177` compares this key with its own.
- `nativeThreadId(jni, thread)` (`jvmThread.cpp:32-34`) calls
  `J9Support::GetOSThreadID` on J9. On all other VMs it calls
  `VMThread::nativeThreadId`.
- `javaThreadId()` reads `Thread.tid`. `hasJavaThreadId()` reports whether that
  field was found.

## What each implementation directory provides

### `hotspot/`

This is the largest implementation. It is the only one with its own stack
walker, with raw `Method*` frames, and with lazy jmethodID resolution.

| File | Role |
|---|---|
| `hotspotSupport.{h,cpp}` | `HotspotSupport`: `walkJavaStack`/`walkVM`, ASGCT with fault recovery (`withUcontextFaultRecovery`), jmethodID preload policy, `fjmethodid=lazy` (`registerClass`, `resolve`, redefinition tracking, dump-time class pinning). `JVMSupport` is a friend (`hotspotSupport.h:131`), and the walker internals are private |
| `hotspotStackFrame.h`, `hotspotStackFrame_{x64,aarch64}.cpp` | `HotspotStackFrame`: unwinds through compiled frames, stubs, prologues, epilogues and sampled continuation-entry phases, and saves and restores the `JavaFrameAnchor` on fault recovery |
| `vmStructs.{h,inline.h,cpp}` | Reads `gHotSpotVMStructs` offsets, and defines `VMThread`, `VMMethod`, `VMFlag`, `CodeHeap`, and related types |
| `jitCodeCache.{h,cpp}` | JIT and runtime-stub address ranges from `CompiledMethodLoad`/`DynamicCodeGenerated`, used by `isJitCode` and `runtimeStubsMemoryUsage` |
| `stubUnwindInfo.{h,cpp}` | Per-PC unwind phases for HotSpot runtime stubs (aarch64 only). They are computed in the `DynamicCodeGenerated` callback, and the walker reads them without locks |
| `klassRegistry.{h,cpp}` | Redefinition marks keyed by `Klass*` for `fjmethodid=lazy` (`HotspotSupport::_klass_registry`, `hotspotSupport.h:161`) |
| `klassTraceId.{h,cpp}` | Finds `Klass::_trace_id` by probing, so a stale raw frame can be told apart from a class that reused the same `Klass*` |

Directly sampled `enterSpecial` frames use
`HotspotStackFrame::continuationEntryFrameWords()` to locate the carrier SP.
The helper distinguishes the prologue's register save and storage allocation,
the complete frame, and the normal epilogue's storage deallocation and register
restore. The walker checks bounds and alignment before reading saved FP/PC;
before the save and after the restore it uses the sampled FP and LR (aarch64)
or return-PC stack slot (x64). Unknown prologues fail rather than applying the
complete-frame size. Pointer-authentication instructions are recognized on
arm64, and recovered PCs have PAC bits stripped.

On x64, `continuationEntryExceptionLayout()` decodes the generated exception
section separately from the scalar normal-frame helper. A bounded scan identifies
the normal epilogue, then validates the exception cleanup, resolver arguments,
stack-alignment branches, calls and final `pop rax; pop rdx; jmp rbx` sequence.
The layout distinguishes saved RBP from restored RBP: after `push rax`, the old
saved-RBP slot contains an exception object, not a frame pointer. The carrier PC
is the last live stack word until `pop rdx`; a direct sample at the final jump
uses interrupted RDX instead. Both near calls and full-address RAX calls are
recognized, including HotSpot's byte-test optimization for stack alignment.

A native unwind returning to a recognized x64 resolver call uses its reconstructed
SP and RBP and the still-stacked carrier PC. Only actual call-return instruction
boundaries qualify; an older PC after `pop rdx` must not borrow interrupted RDX.
Recovery does not follow `JavaThread::_cont_entry`, which can already name a
parent, or advance the nested-entry cursor to the retiring spill. Unknown code,
invalid branch targets, non-instruction PCs and out-of-blob reads fail with
truthful error/truncation. Carrier SP alignment/bounds and FP/PC admission checks
remain shared with normal recovery.

Interpreter-only execution uses a separate entry before the verified compiled
entry on both architectures. The decoder locates that entry's recognized frame
setup with a bounded scan before the compiled entry. Its prologue and established
frame then use their own setup rather than the later compiled frame-complete
offset. Unknown setup sequences fail conservatively.

On arm64 the exception epilogue finishes with `mov x3, lr; br x1` after
`leave()` has restored SP and FP/LR. A sample at either instruction uses the
restored FP and LR, including when `leave()` authenticates LR. The decoder
requires both instructions and bounds the forward read to the same code blob.
An isolated move or branch does not select this recovery path.

During arm64 exception-handler resolution, `call_VM_leaf_base()` temporarily
spills `x8` and `x12`. The decoder recognizes the bounded spill, target-load,
call and restore sequence and adds two words while the spill is live. The
ordinary entry-frame size applies before the spill and after its restoration.
This adjustment reads code only and also applies when native unwinding recovers
a return PC into the spilled entry. It does not use sampled register values at
that recovered PC.

Normal prologue/epilogue phase recovery applies only to the exact sampled PC.
Apart from recognized VM-leaf resolver layouts, recovered return addresses keep
the existing continuation-entry metadata and stack-argument recovery. During
entry publication and removal, `JavaThread::_cont_entry` can name the enclosing
entry; a sampled entry only advances the nested-entry cursor when the published
entry matches its own saved-register slots. The carrier validation and
continuation truncation policy are shared by both recovery paths.

On HotSpot JDK 21+, initialization recognizes the return-barrier prefix that
loads `JavaThread::_cont_entry` into SP: `ldr x8, [x28, #offset]; mov sp, x8`
on arm64, or `mov rsp, [r15 + offset]` on x64. It copies a bounded eight bytes,
checks the instruction shape and the field's alignment and bounds within the
exported `JavaThread` size, then publishes the inferred offset with release
semantics. Bounds use `JavaThread` independently of the smaller `Thread` base
type used by `VMThread` casts. Walkers acquire-load the offset. Unknown prefixes leave the capability
unavailable. This inferred offset stays separate from the JDK 27 exported
fields and does not change anchor redirection or nested-entry handling.

A sample at the return barrier, including one reached through a native signal
trampoline, may have no decoded Java frame providing its stack-argument count.
When exported entry metadata is unavailable, that verified frozen boundary can
use the inferred offset to read the current entry pointer. The `enterSpecial`
nmethod's validated frame size locates its saved FP/PC pair; stack range,
alignment and carrier admission checks apply before proceeding. Walks with a
known argument count retain SP-based recovery. Missing or invalid metadata
still rejects the walk, and frozen boundaries remain marked truncated.

Recognized arm64 VM-leaf spills also recover an entry that exception cleanup has
already unlinked from the thread. Exported layouts must agree with the entry FP
derived from the nmethod size. The nested-entry cursor records that physical entry
so the next crossing follows its parent once.

Native thaw calls return inside the barrier stub, where SP has already changed.
The runtime-stub lookup identifies these PCs by matching the registered stub's
start to the known return-barrier entry. They use the current thread's entry
metadata, independently of any earlier Java frame's stack-argument count.
Both stopping at the synthetic root and continuing onto the carrier retain the
frozen-boundary truncation flag. Missing entry metadata still rejects recovery.

Every continuation crossing retires both the live Java frame anchor and its saved
recovery SP. The post-loop anchor fallback must not append frames from the consumed
continuation again, whether the walk stops at the synthetic root or continues onto
the carrier.

Caveats:

- **Architecture-specific unwinding.** `unwindAtomicStub` always returns
  `false` on x86_64 (`hotspot/hotspotStackFrame_x64.cpp:213-215`). On aarch64 it
  unwinds through generated `Stub*` code when the link register points into
  libjvm (`hotspot/hotspotStackFrame_aarch64.cpp:370-379`). The unwind helpers
  return the raw return address on every architecture. When the result is
  written back into the ucontext for an ASGCT retry,
  `stepIntoCallForAsgct()` subtracts one only on x86_64
  (`hotspot/hotspotStackFrame.h:133-139`).
- **Stub unwind tables.** `StubUnwindInfo` exists only on aarch64. On x64,
  `unwindStub()` ignores the `info` argument (`hotspot/hotspotStackFrame.h`,
  comment on `unwindStub`).
- **`klassRegistry` is not signal-safe.** Every operation takes an internal
  mutex and calls JNI (`hotspot/klassRegistry.h`, class comment). It is used
  from the redefinition hooks and at dump time, never from a signal handler.
- **Lazy mode depends on `KlassTraceId`.** If calibration finds no offset
  (for example, a build without JFR), `initLazyResolution()` fails, and
  `initExecution()` falls back to `Partial_loaded` (`jvmSupport.cpp:86-91`).
- **`cstack=vm` needs `VMStructs`.** If `VMStructs::hasStackStructs()` is false,
  `cstack=vm` is downgraded to DWARF or `no` (`profiler.cpp:1625-1629`).

#### Continuation completeness

HotSpot can leave older virtual-thread callers frozen in heap `StackChunk` objects
after a partial thaw. `walkVM` classifies continuation boundaries with `ContBoundary`:
a verified thawed boundary proves no callers remain frozen; return barriers and
unverified crossings mark the trace truncated. This walker does not recover heap
callers, so reaching a carrier does not clear that flag.

`Recording::writeStackTraceHeader` preserves the walker flag even when the final
Java frame is an entry method such as `Thread.run`. A verified thawed crossing also
preserves truncation established earlier in the walk. The blocking virtual-thread
wall-clock regression requires carrier ancestry. `FrozenVirtualThreadStackTest`
separately compares logical callers and verifies truthful completeness reporting.

### `j9/`

| File | Role |
|---|---|
| `j9Support.{h,cpp}` | `J9Support`: resolves the `com.ibm.*` JVMTI extensions, `j9thread_self`, `GetOSThreadID`, `GetStackTraceExtended`/`GetAllStackTracesExtended`, the frame-type mapping (`sanitizeJ9FrameType`), and the sampler policy |
| `j9WallClock.{h,cpp}` | `J9WallClock` engine: a dedicated thread (`"java-profiler Sampler"`) that calls `GetAllStackTracesExtended` on each tick (`j9/j9WallClock.cpp:82-99`) |

Caveats:

- **The ASGCT-or-JVMTI choice is made per engine.** `Profiler::selectCpuEngine`
  and `selectWallEngine` choose `J9WallClock` (the JVMTI path) when any of these
  holds (`profiler.cpp:1274-1285`, `profiler.cpp:1321-1333`):
  - `J9Support::shouldUseAsgct()` is false. The system property
    `dd.profiling.ddprof.j9.sampler` set to `jvmti` makes it false
    (`j9/j9Support.h:108-126`).
  - `J9Support::can_use_ASGCT()` is false. J9's ASGCT is not
    async-signal-safe before OpenJ9 0.51, so the profiler requires at least
    8u451, 11.0.27, 17.0.15, or 21.0.7 (`j9/j9Support.h:88-100`).
  - For wall clock only: `wallsampler=jvmti` is set.
- **`J9WallClock` names itself by mode.** In CPU mode `name()` is
  `J9Execution` and it skips threads that are not RUNNABLE. In wall mode it
  calls `sampleIdleThreads()`, `name()` becomes `J9WallClock`, and every thread
  is recorded (`j9/j9WallClock.h:44-50`, `j9/j9WallClock.cpp:110-148`).
  Sampling runs on a normal attached thread, not in a signal handler.
- **jmethodID safety.** Only JDK 8 J9 is considered safe for deferred jmethodID
  resolution (`J9Support::is_jvmti_jmethodid_safe`, `j9/j9Support.h:102-106`).
  On other versions the profiler warns and suggests `-XX:+KeepJNIIDs=true`.
- **Friends.** `J9Support` declares `JVMThread` and `J9WallClock` as friends,
  so they can call the private `GetOSThreadID` (`j9/j9Support.h:75-76`).

### `zing/`

`ZingSupport` has a single function, `initialize(jthread)`. It returns the VM
thread pointer from `Thread.eetop` (`zing/zingSupport.cpp:12-27`). All other Zing
behavior is shared code that branches on `VM::isZing()`:

- Java stacks are collected with ASGCT (`jvmSupport.cpp:112-117`).
- Runtime entries are marked (`vmEntry.cpp:378-379`).
- `_safe_mode` is forced (`profiler.cpp:1587`).

Caveat: `JVMThread::nativeThreadId()` sends Zing to
`VMThread::nativeThreadId()`. That function returns -1 unless
`_has_native_thread_id` is set (`hotspot/vmStructs.inline.h:77-83`). The flag is
set only in `VMThread::initialize()` (`hotspot/vmStructs.cpp:667`), and Zing
never calls that function. This is from reading the code and has not been
checked on a Zing JVM. Zing is also currently disabled in the CI JDK matrix
(`.github/workflows/test_workflow.yml:54-56`).

## Known boundary exceptions

In these shared files, outside the abstraction files, `grep -E '#include ["<](hotspot|j9|zing)/'`
finds direct includes of implementation headers:

| File | Includes |
|---|---|
| `profiler.cpp:23-26` | `hotspot/vmStructs.inline.h`, `hotspot/hotspotSupport.h`, `j9/j9Support.h`, `j9/j9WallClock.h` (engine selection, `VMStructs::hasStackStructs`) |
| `flightRecorder.cpp:43` | `hotspot/vmStructs.h` |
| `livenessTracker.cpp:17-18` | `hotspot/vmStructs.h`, `hotspot/vmStructs.inline.h` |
| `sanityCheck.cpp:12-13` | `hotspot/vmStructs.h`, `hotspot/vmStructs.inline.h` |
| `threadState.inline.h:11` | `hotspot/vmStructs.h` |

New code should not add to this list. If shared code needs a new
implementation-specific query, add it to `JVMSupport` (or to `JVMThread`/`VM`).
Add a branch for each VM there, and include a non-HotSpot fallback, as the
inline functions in `jvmSupport.inline.h` do.

## Adding a capability

1. Declare a static function in `jvmSupport.h`. If it is called from a signal
   handler, make it `inline` in `jvmSupport.inline.h`.
2. Branch on `VM::isHotspot()` / `VM::isOpenJ9()` / `VM::isZing()`. Call the
   implementation class and return a safe default for VMs that lack the feature.
3. Put the implementation in `hotspot/`, `j9/`, or `zing/`. If an
   implementation function must stay private, declare `JVMSupport` as a friend,
   as `HotspotSupport` does.
4. Shared callers include `jvmSupport.h` (or `jvmSupport.inline.h`), not the
   implementation header.
