# Lazy jmethodID Resolution

> **Prototype notes. Remove before the PR lands.**
> Branch: `jmethodid-lazy-resolve` (off `main` @ a60c7b1cf). Flag: `fjmethodid=lazy`. Last updated 2026-10-15.

Stop preloading jmethodIDs for every loaded class. Record raw `Method*` frames while
sampling, and turn them into jmethodIDs on the dump thread, only after confirming that
the owning class is still loaded.

## Problem

Today every class gets its jmethodIDs at ClassPrepare (`GetClassMethods`). In partial
mode (`fjmethodid=false`) only system-loader classes skip this, and custom-loader, hidden
and lambda classes are still preloaded. The cost is a jmethodID per method plus a
per-class ID cache, kept until the class unloads, and contention on the JVM's
jmethodID-creation lock during class loading.

Preloading doesn't stop allocation inside the signal handler; nothing allocates there.
AGCT uses `find_jmethod_id_or_null`, and `walkVM` reads the per-class cache directly
(`VMMethod::id()`). Preloading only makes sure an ID already exists when the sampler
looks. The sampler doesn't actually need a jmethodID. It needs an identifier that can
be resolved later, safely.

## Approach

1. **Sample time (signal handler).** When the class has no jmethodID yet,
   `fillJavaFrame` stores the raw `Method*`. This existing path is reused unchanged. The
   method is on the stack, so it is valid at that moment.
2. **ClassPrepare and startup.** Instead of preloading, `HotspotSupport::registerClass`
   records `Klass* → JNI weak global ref to the mirror` in `KlassRegistry`. Array and
   primitive classes are skipped. At start, `GetLoadedClasses` registers the classes that
   already exist.
3. **Resolve time (dump thread).** Under crash protection, read only the holder `Klass*`
   and the idnum from the possibly-stale `Method*` (`readMethodHolder`). Both are treated
   as lookup keys and never trusted. Then, with protection off (`resolveViaRegistry`):
   - `pin(holder)`: a `NewLocalRef` of the weak ref. It returns null if the class is
     gone, which yields an unknown frame and bumps `method_resolve_lazy_unloaded`.
   - A strongly held mirror keeps its class loader, and so the class's metadata, alive.
     The `Klass*` can now be dereferenced safely.
   - `VMKlass::containsMethod(M, idnum)` compares pointers only against the class's
     current `_methods` array, using an idnum fast path plus a linear fallback. A miss
     yields an unknown frame and bumps `method_resolve_lazy_not_current`.
   - Only then is `M` dereferenced. If it has no ID, `loadMethodIDsIfNeededImpl(load_all)`
     allocates IDs for this one class, including the JDK 8 CLD patch. This bumps
     `method_resolve_lazy_class_loaded`.

After the first dump that touches a class, its jmethodIDs exist, so later samples carry
real IDs and skip the slow path. Lazy mode needs `cstack=vm` and
`VMStructs::hasKlassMethods()`; otherwise it falls back to partial mode. It applies to
HotSpot only, and J9 and Zing keep preloading.

### KlassRegistry

- An open-addressing table with linear probing, guarded by a mutex. It is never touched
  from a signal handler.
- Dead entries (weak ref cleared) are purged whenever the table would grow, so memory
  follows the number of live classes.
- A different mirror at a known `Klass*` replaces the entry and deletes the old weak ref.
- `pin()` calls `NewLocalRef` under the lock, so a concurrent rehash can't delete the weak
  ref out from under it. Lock ordering is safe: none of the JNI calls made under the lock
  load classes, so a ClassPrepare can't re-enter it.

## Klass* address reuse (solved: frame tags)

Class-space blocks are aligned and reused, so a new class at the exact address of an
unloaded one is likely. The current checks don't catch it:

1. `K_old.m` is sampled as raw `M`, with holder at `A`.
2. `K_old` unloads. `K_new` is allocated at `A`. A class of the same shape that gets the
   freed chunks back very likely puts its methods at the same addresses, so one of them
   lands at `M`.
3. `K_new`'s ClassPrepare replaces the registry entry for `A`.
4. At dump, `M` reads back as holder `A`, the class at `A` is alive, and `M` is in its
   methods. The frame resolves as `K_new`'s method, which is wrong.

It also breaks trace dedup. `K_new` samples at `M` produce the same raw frames as the
old `K_old` samples, so within one dump interval they collapse into one trace ID. No
check at resolve time can separate them, so **the frame itself has to carry an
incarnation identity.** The existing modes never hit this, because unloadable classes
always get jmethodIDs.

### Option A: reuse epoch (portable fallback) — implemented

Implemented (`KlassRegistry::epoch()`/`bumpEpoch()`, `pin(…, sampled_epoch, &status)`, counter
`method_resolve_lazy_stale`). After review, **every registration bumps the epoch**, not only replacements
and purges (see "Guarantees and limits" below). It also relies on one invariant, which is now enforced: every class is
registered before any of its methods can run. ClassPrepare guarantees this; if `add()` fails,
`registerClass` preloads that class's jmethodIDs instead (`klass_registry_add_failed`), so no raw
frame of an unregistered class is ever produced. Without that, a later class at the same address
could be inserted fresh, without a bump, and accept the unregistered class's frames.


- The registry keeps a global `_epoch`, and each entry records the epoch it was
  registered at.
- ~~The epoch is bumped on a replacement and on a purge.~~ It is bumped on **every** registration.
  The original rule missed a dead class's `Method*` memory being reused by a class loaded fresh
  at a *different* `Klass*`.
- The sampler stores the current epoch in the raw frame: one acquire load, with no
  registry lookup in the handler.
- Resolve accepts only if `entry.epoch ≤ frame.epoch`, compared modularly. Live classes
  always pass, because ClassPrepare runs before their methods do. Old-incarnation frames
  fail, and old and new frames no longer dedup together.
- Cost: a stack sampled across a bump splits into two traces. With a bump per registration,
  epoch tags split traces on every class load. That's acceptable for a fallback used only
  without JFR, and trace-ID tags don't have this problem.

### Option B: HotSpot's JFR class trace ID, read by offset — implemented, preferred

Every `Klass` carries `mutable traceid _trace_id` (`JFR_ONLY(DEFINE_TRACE_ID_FIELD)`).
It is not in `gHotSpotVMStructs`. From the local OpenJDK sources:

- **Assignment:** `next_class_id()` is
  `(atomic_inc(counter) << TRACE_ID_SHIFT) | EPOCH_CLEARED_BITS`, with
  `TRACE_ID_SHIFT = 16`. It is assigned at class creation (`Jfr::on_klass_creation` on
  master, `INIT_ID(ik)` in classFileParser on 17u) and on CDS restoration, whether or not
  JFR is recording. It is globally monotonic, so it is unique per incarnation.
- **Encoding:** the low 16 bits are JFR tag/epoch bits that JFR changes while it runs.
  Use `raw >> 16` only.
- **Not present** in builds without JFR: JDK 8 before 8u262 (when JFR reached upstream 8u), and
  `--disable-jfr` builds. Option A is still needed as a fallback.

| Source tree | `_trace_id` declared after | Nearest vmStructs anchor |
|---|---|---|
| jdk17u (17.0.18) | `AccessFlags _access_flags` | `Klass::_access_flags` |
| jdk21u-dev (21.0.10) | `AccessFlags _access_flags` | `Klass::_access_flags` |
| jdk master (28) | `CDS_JAVA_HEAP_ONLY(int _archived_mirror_index)`, after `_vtable_len` | `Klass::_vtable_len` (+4 if CDS heap) |
| 8u, 11u, 25 | not checked yet: no local checkout | |

An anchor-relative offset per version range is more robust than absolute offsets, and
the repo already keys a few offsets on `VM::hotspot_version()` in `vmStructs.cpp`. The
field moves between releases, and on master its position depends on a build option (the
CDS Java heap). So the offset must be confirmed at runtime, not trusted from a table
alone.

Advantages over A: no global state, no trace splitting, and two incarnations get the same
stored bits only if a multiple of 2^N classes were created between them.

#### Offset discovery — implemented

Offsets can move even between minor releases, so there is no version table. `KlassTraceId::calibrate()`
(hotspot/klassTraceId.{h,cpp}) runs when lazy mode is selected:

- It resolves `[[[[[[Ljava/lang/Void;`, which makes the JVM create up to six array klasses back
  to back, each getting the next trace ID. No classes of our own are defined.
- It scans every 8-byte-aligned offset in `[8, sizeof(Klass))` and accepts one only if all six
  probes hold nonzero `raw >> 16` values, pairwise distinct, within `5 + ID_SLACK (64)` of each
  other. This rejects pointers (a few hundred bytes apart, so `>> 16` collapses them), equal small
  ints, and compressed-klass bits in a mark word (far apart). More than one match means failure.
- The result goes to the `klass_trace_id_offset` gauge: the offset, -1 on failure, 0 if
  calibration hasn't run.

**Assumptions it relies on, swept across 36 GA tags** (17 GA – 17.0.17, 21 GA – 21.0.9, 22–26, 28+18):
`_trace_id` is declared in `class Klass` (so array klasses have it, and it lies inside
`sizeof(Klass)`); `arrayKlass.cpp` has `INIT_ID(this)`; `TRACE_ID_SHIFT` is 16; `next_class_id`
shifts the counter by it. All hold on every tag. The field's neighbour was `_access_flags` through
24 (with different preceding fields in 24) and `_archived_mirror_index` from 25 on. LTS lines
swept too, from blob-less partial clones of openjdk/jdk8u, jdk11u and jdk25u:

| Line | GA tags | Result | Declared after |
|---|---|---|---|
| 8u | 8u201 – 8u252 (7) | no `_trace_id` (pre-JFR): calibration fails, epoch fallback | — |
| 8u | 8u262 – 8u504 (29) | all assumptions hold | `_biased_lock_revocation_count` |
| 11u | 11.0.2 – 11.0.32.1 (36) | all assumptions hold | `_access_flags` |
| 25u | 25 GA – 25.0.4.1 (6) | all assumptions hold | `_archived_mirror_index` |

So 107 GA tags in total. The sweep compares neighbouring declarations, not absolute byte offsets.
That's enough, since calibration assumes none. Script: `/tmp/jfrsweep/sweep2.sh <repo> <tag>...`
(Mac), with `P=hotspot/src/share/vm/` for 8u.

#### Confirming the offset — CI only

Self-calibration is the only production gate. JFR's own class IDs confirm it in CI, never at runtime.

**Why not a runtime cross-check against `JVM.getClassId()`:** prototyped and dropped after it
crashed the JVM (SIGSEGV in `JfrTraceIdKlassQueue::enqueue`, called from `getClassId`'s load
barrier).
- `getClassId()` tags a class JFR hasn't tagged yet, and adds it to JFR's class queue.
- That queue only exists once JFR's recorder has been created (`JfrRecorder::create_components`
  → `JfrCheckpointManager::initialize` → `JfrTraceIdLoadBarrier::initialize`).
- "`jdk.jfr.internal.JVM` is initialized" doesn't mean the recorder exists. The profiler itself
  initializes that class: `tsc.cpp` does `FindClass("jdk/jfr/internal/JVM")` for JFR's tick
  frequency. So every lazy-mode session crashed on its first dump.
- A safe precondition would be "recorder exists and won't be destroyed during the call". There's
  no race-free way to check that from native code:
  - `JVM.isRecording()` differs by release: static native on 25+, instance native on 17u,
    instance Java wrapper on 8u/11u.
  - JFR's shutdown hook calls `destroyJFR()`, which tears those structures down while the VM is
    still running.
  - Our crash protection only recovers faults inside our own library, not inside the JVM.

**CI validation instead:** `LazyTraceIdJfrValidationTest`, which needs a debug build.
- A child JVM (`ExternalLauncher lazy-trace-id`) runs the profiler in lazy mode alongside JFR's
  own sampler (`-XX:StartFlightRecording=…,settings=profile`) while it spins in a probe class.
- In debug builds, `resolveViaRegistry` logs `Lazy jmethodIDs for <sig>, trace id N` for every
  class it allocates jmethodIDs for.
- The child records only `jdk.ClassDefine` (a `.jfc` written by the test). JFR emits it once
  when the probe class is created (`define_instance_class` on 8u/11u, `Jfr::on_klass_creation`
  on mainline); its `definedClass` is the probe's `RecordedClass`. The test reads it through
  `jdk.jfr.consumer` (by reflection, because the test sources compile with `--release 8`) and
  requires `getId()` to equal the logged ID.
- `jdk.ExecutionSample` was tried first. Before JDK 25, JFR's own sampler recorded almost no
  samples for the spinning probe, even with our profiler not started, so it couldn't serve.
- Results, profiler ID = JFR ID: 8u (musl) 2077, 11 (musl) 2152, 17 2065, 21 2154, 25 2211;
  macOS 25 2210.

**Tag kind bit:** kept from the prototype. The tag's top bit records whether a frame carries a
trace ID or an epoch, so the epoch keeps 25 bits. `resolve()` goes by each frame's own kind, not by
the current tag source. That keeps frames self-describing; nothing switches sources at runtime any
more.

### Frame bits — implemented

`FrameType::encodeRaw` / `tagPointer` / `rawTag` / `untagPointer` (frame.h) carry a 26-bit tag:
the low 10 bits in bci bits 16–19 and 24–29, and the high 16 bits in pointer bits 48–63. A
`Method*` with any of those pointer bits set is stored as `JMETHODID_NOT_WALKABLE` and counted
(`walkvm_raw_frame_untaggable`), never stored without its tag. `resolve()` now takes
`(method, bci)` so it can take the tag back out. The JFR writer masks bci to 16 bits and the
type to 3 bits, so tag bits never reach the recording. `hasTheSameMethod` compares untagged
pointers.

The original budget analysis:


- The bci field has 10 spare bits: 16–19 and 24–29. Bit 31 must stay clear, because
  `isRawPointer()` requires `bci > 0`.
- The top 16 bits of `Method*` look free for 48-bit user-space addresses. arm64 can hand
  out 52-bit addresses when asked, so this needs a startup VA check, falling back to the
  10 bci bits.
- 10 bits alone is too few under heavy churn for either option. Resolving from a
  background thread shrinks the window between sample and resolve, and helps both.

## Guarantees and limits (after review)

A review of `a9b67775` found four issues. All have been checked against the OpenJDK sources
and fixed or bounded:

1. **Methods array read without protection after pinning.** Redefinition swaps `_methods` at a
   safepoint (`the_class->set_methods(_new_methods)`) and frees previous versions later, at another
   safepoint (`ClassLoaderDataGraph::clean_deallocate_lists`). The dump thread is in native and
   holds up neither. Fixed: every load in `VMKlass::containsMethod()` goes through `SafeAccess`,
   so a fault reads as "not a member".
2. **`Method*` reuse within a live class (repeated redefinition).** The class's mirror, trace ID
   and epoch don't change, so no tag can tell the frames apart. Fixed: the redefine/retransform
   hooks call `KlassRegistry::markRedefined()` *before* the original JVMTI function, and preload
   the class's jmethodIDs afterwards, so its later frames aren't raw. `pin()` refuses raw frames
   of a marked class (`method_resolve_lazy_redefined`), and `resolveViaRegistry()` checks the
   mark again after its metadata reads. If the mark is still absent then, every read happened
   before the methods were swapped. The same analysis found the epoch-mode hole fixed by
   per-registration bumps (above).
3. **`klassRegistry_ut` didn't link in release** (missing `vmStructs.inline.h`). Fixed; all
   new gtest binaries pass in release.
4. **Tag collisions.** Bounded and monitored, not eliminated:
   - **Can't crash:** after pinning, only `SafeAccess` reads and JNI/JVMTI on a live class remain.
   - **Trace-ID tags** can only collide once two classes' trace IDs are ≥ 2^25 apart. A JVM that
     has created fewer than 2^25 (33,554,432) classes can't misattribute.
   - **After that** (extreme class churn after long uptime), a stale frame can resolve to a live
     method of the wrong class. That needs all of: the sampled class is unloaded before the frame
     is resolved; a newer class takes over its exact `Method*` address; and the two IDs differ by
     an exact multiple of 2^25. The result is one misattributed frame.
   - **Epoch tags** need 2^24 registrations while one trace is still unresolved.
   - **Tripwire:** `klass_trace_id_beyond_tag_range` counts registrations of classes whose trace
     ID exceeds the tag range. If it ever fires in practice, the planned fix is a 64-bit registry
     epoch per `CallTrace`, checked as "holder registered no later than the trace". That makes
     misattribution impossible and leaves dropped frames as the worst case. A trace-lifetime bound
     would *not* help trace-ID tags, since collisions depend on the classes' age difference, not
     the frame's.

Correctness also rests on two invariants: every class is registered before its methods can run
(ClassPrepare; registration failure falls back to preloading), and every redefinition goes
through the hooked `RedefineClasses`/`RetransformClasses`.

Size correction: `KlassRegistry::Entry` is 24 bytes on 64-bit (`Klass*`, `jweak`, `uint32_t`
epoch, `bool`), not 16.

## Measurements

20,000 classes × 50 static methods (1M methods), 100 classes per custom loader, all kept
reachable. JDK 25.0.1 (Corretto), macOS arm64, debug build of the profiler,
`cpu=10ms,cstack=vm`. Figures are the NMT `summary.diff` against a baseline taken just
before loading.

| Mode | Class, committed Δ | Total committed Δ | Load time |
|---|---:|---:|---:|
| no profiler | +13.6 MB | +722 MB | 393 ms |
| `fjmethodid=true` | +22.1 MB | +748 MB | 420 ms |
| `fjmethodid=false` | +22.1 MB | +739 MB | 446 ms |
| **`fjmethodid=lazy`** | **+13.6 MB** | **+721 MB** | 420 ms |

Preloading costs about 8.4 MB of committed memory per million methods. Partial mode saves
nothing in this workload, because every custom-loader class is still preloaded. Lazy mode
matches the no-profiler baseline. Load-time differences are within noise. In-process RSS
deltas (about 375–390 MB in every mode) were too noisy to show any of this. Linux numbers
are still to do.

The harness is a standalone `Bench.java`: ASM on the classpath, the profiler loaded with
`-agentpath:…=start,cpu=10ms,cstack=vm,fjmethodid=<mode>`, and the JVM run with
`-XX:NativeMemoryTracking=summary`. It reads `vmNativeMemory baseline` / `summary.diff`
through the `com.sun.management:type=DiagnosticCommand` MBean. It lives in
`/tmp/jmbench` on the Mac and isn't in the repo.

## Status

| Item | State |
|---|---|
| `fjmethodid=lazy`, `KlassRegistry`, resolve path, counters | done |
| Frame tags: 26 bits (tag-kind bit + 25-bit value) in spare bci bits and `Method*` top bits | done |
| Epoch tags (fallback) and trace-ID tags (when calibrated) | done |
| Trace-ID offset calibration; source sweep over 107 GA tags (8u–28) | done |
| gtests: `klassRegistry_ut`, `klassTraceId_ut`, `hotspotLazyResolve_ut` (every reuse case under both tag sources), `frame_ut`, `jvmSupport_ut`, `arguments_ut` | pass (macOS; Linux debug + ASan before the trace-ID commits) |
| `LazyJmethodIdTest` on JDK 8u462, 11.0.28 (musl) and 17.0.16, 21.0.8, 25.0.2 (glibc), aarch64 | pass, trace-ID tags on all five |
| Calibrated offsets: 8u462 → 184, 11.0.28 → 168, 17.0.16 → 168, 21.0.8 → 184, 25.0.2 → 192 | measured |
| `LazyTraceIdJfrValidationTest` (CI cross-check against JFR) | pass on JDK 8, 11 (musl), 17, 21, 25 (glibc) and macOS 25: profiler ID = JFR ID on each |
| Runtime JFR cross-check | dropped, see "Confirming the offset" |
| Review fixes: `SafeAccess` in `containsMethod`, redefinition marking, per-registration epoch, release link fix, tag-range tripwire | done |
| Per-dump cache for raw frame resolutions (`Lookup::_raw_method_cache`) | done: first dump with nearly every frame raw went from 60.3 ms to 34.3 ms (27,956 hits, ~0.9 µs saved each; macOS debug build, single run); later dumps unchanged (~20 ms) |
| Redefinition hooks forward invalid arguments to JVMTI untouched (`redefineHooks_ut`) | done |
| Live-JVM redefinition stress test (`LazyRedefinitionStressTest`: ~1000 redefinitions racing ~47 dumps; every redefinition marked, stale raw frames refused, later frames resolve by name) | pass on JDK 17, 21, 25 (glibc), 21 under ASan, 11 (musl), macOS 25 |
| Release-build dump latency and memory on a real workload, x64 runs | open |
| `JmethodIdOverheadBenchTest.java`: temporary harness, don't commit | uncommitted |

### Files touched

```
ddprof-lib/src/main/cpp/hotspot/klassRegistry.{h,cpp}   new: Klass* → weak mirror registry, epoch
ddprof-lib/src/main/cpp/hotspot/klassTraceId.{h,cpp}    new: Klass::_trace_id calibration and signal-safe read
ddprof-lib/src/main/cpp/frame.h                         raw-frame tag encoding
ddprof-lib/src/main/cpp/hotspot/hotspotSupport.{h,cpp}  registerClass, readMethodHolder, resolveViaRegistry
ddprof-lib/src/main/cpp/hotspot/vmStructs{.h,.inline.h} VMKlass::containsMethod, VMConstMethod::idnum, hasKlassMethods
ddprof-lib/src/main/cpp/jvmSupport.{h,cpp}              Lazy_loaded state and dispatch
ddprof-lib/src/main/cpp/arguments.{h,cpp}               fjmethodid=lazy
ddprof-lib/src/main/cpp/counters.h                      method_resolve_lazy_{unloaded,not_current,class_loaded}
ddprof-lib/src/test/cpp/{klassRegistry,jvmSupport,arguments}_ut.cpp
ddprof-test/src/test/java/com/datadoghq/profiler/cpu/LazyJmethodIdTest.java
ddprof-test/src/test/java/com/datadoghq/profiler/cpu/LazyTraceIdJfrValidationTest.java
ddprof-test/src/test/java/com/datadoghq/profiler/SpinClasses.java + ExternalLauncher lazy-trace-id
ddprof-lib/src/test/cpp/{klassTraceId,hotspotLazyResolve,frame}_ut.cpp
```

## Continuing on Linux

```
git fetch && git switch jmethodid-lazy-resolve
./.claude/commands/build-and-summarize :ddprof-lib:gtestDebug
./.claude/commands/build-and-summarize :ddprof-test:testDebug -Ptests='*Jmethod*'
# or, from any host with podman/docker:
./utils/run-containers-tests.sh --config=asan --libc=glibc --jdk=21 --tests='*Jmethod*'
./utils/run-containers-tests.sh --arch=aarch64 --config=debug --jdk=21 --tests='*Jmethod*'
```

`-Ptests` takes a single pattern. Comma-separated lists don't match. The musl runner treats it as a regex (`*Foo` fails there); a plain class name works for both.

## Alternatives set aside

- **JVMTI ObjectFree on tagged mirrors** as an unload signal: it needs
  `can_tag_objects`, and the events are posted later from the service thread, so they
  don't tell you when the metadata is freed.
- **GC start/finish callbacks** to resolve before unloading: JNI isn't allowed inside
  them, and they aren't known to cover unloading by concurrent collectors.
- **Copying names in the handler:** too expensive, and Symbols can be freed too.
- **JFR's own sampler (JDK 25+):** it solves this inside the VM, but it doesn't cover
  JDK 8–21, J9 or Zing.
