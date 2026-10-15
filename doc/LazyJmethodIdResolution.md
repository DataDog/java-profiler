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

## Open problem: Klass* address reuse (blocking)

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

### Option A: reuse epoch (portable fallback)

- The registry keeps a global `_epoch`, and each entry records the epoch it was
  registered at.
- The epoch is bumped on a replacement (known key, different mirror) and whenever a
  rehash purges dead entries, because a purged key can come back looking like a fresh
  insert.
- The sampler stores the current epoch in the raw frame: one acquire load, with no
  registry lookup in the handler.
- Resolve accepts only if `entry.epoch ≤ frame.epoch`, compared modularly. Live classes
  always pass, because ClassPrepare runs before their methods do. Old-incarnation frames
  fail, and old and new frames no longer dedup together.
- Cost: a stack sampled across a bump splits into two traces. In heavy churn, bumps
  follow the reuse rate. A "seen since last bump" flag can reduce how often it bumps.

### Option B: HotSpot's JFR class trace ID, read by offset (preferred)

Every `Klass` carries `mutable traceid _trace_id` (`JFR_ONLY(DEFINE_TRACE_ID_FIELD)`).
It is not in `gHotSpotVMStructs`. From the local OpenJDK sources:

- **Assignment:** `next_class_id()` is
  `(atomic_inc(counter) << TRACE_ID_SHIFT) | EPOCH_CLEARED_BITS`, with
  `TRACE_ID_SHIFT = 16`. It is assigned at class creation (`Jfr::on_klass_creation` on
  master, `INIT_ID(ik)` in classFileParser on 17u) and on CDS restoration, whether or not
  JFR is recording. It is globally monotonic, so it is unique per incarnation.
- **Encoding:** the low 16 bits are JFR tag/epoch bits that JFR changes while it runs.
  Use `raw >> 16` only.
- **Not present** in builds without JFR: JDK 8 before the 8u272 backport, and
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

#### Confirming the offset

**Self-calibration (decides at startup).** Register a few probe classes we define in a
known order. Check that `(raw >> 16)` at the candidate offset is distinct for each and
strictly increasing in load order. This has to decide before the first sample, because
the sampler must know which bits to store from then on.

**Cross-check against JFR (confirms later).** dd-trace-java runs a real
`jdk.jfr.Recording` next to ddprof (`OpenJdkOngoingRecording`; when ddprof is enabled it
only turns off the overlapping JFR events). So in most production JVMs JFR gets
initialized, and its own answer can confirm our offset:

- **Detect JFR by watching, not by loading.** Don't call JNI `FindClass`: HotSpot's
  `jni_FindClass` passes `init=true`, which would run `JVM.<clinit>` (`registerNatives`,
  JFR log-level setup, `Options.ensureInitialized()`). Reflection from Java has the same
  problem. Lazy mode already sees every class through ClassPrepare and `GetLoadedClasses`.
  When `Ljdk/jfr/internal/JVM;` shows up, keep a global ref to it, and call into it only
  once `GetClassStatus` reports `JVMTI_CLASS_STATUS_INITIALIZED`.
- **`getClassId` is not a pure read.** `jfr_class_id` goes through
  `JfrTraceIdLoadBarrier::load(klass)`. If the class isn't tagged yet, the barrier marks
  it used for the current epoch and adds it to JFR's class queue, so the class ends up in
  the user's recording. Probe only classes that are certainly tagged already
  (`java.lang.Object`, `java.lang.Thread`); for those `should_tag()` is false and the
  call is effectively a read. It returns `TRACE_ID(klass)`, which is `raw >> 16`, so the
  check is a direct equality test.
- **Mismatch handling.** Switch new samples to Option A. Treat raw frames captured under
  the unconfirmed offset as unresolvable (unknown) rather than resolve them. Wrong names
  are worse than dropped frames. Add a counter for both outcomes.
- JNI calls ignore module encapsulation, so `jdk.jfr.internal` not being exported shouldn't
  matter. Verify this when implementing.

### Frame bit budget (both options)

- The bci field has 10 spare bits: 16–19 and 24–29. Bit 31 must stay clear, because
  `isRawPointer()` requires `bci > 0`.
- The top 16 bits of `Method*` look free for 48-bit user-space addresses. arm64 can hand
  out 52-bit addresses when asked, so this needs a startup VA check, falling back to the
  10 bci bits.
- 10 bits alone is too few under heavy churn for either option. Resolving from a
  background thread shrinks the window between sample and resolve, and helps both.

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
| `fjmethodid=lazy` parsing, `Lazy_loaded` state, registry, resolve path, counters | done |
| gtests: `klassRegistry_ut` (10), lazy cases in `jvmSupport_ut` and `arguments_ut` | pass (macOS) |
| `LazyJmethodIdTest`: custom-loader frames resolve; frames of unloaded class dropped (`method_resolve_lazy_unloaded=5`) | pass (macOS) |
| Deterministic ABA gtest (re-register a new mirror at the same `Klass*` with `M` in its methods; fails before the fix) | open |
| Frame bits: bci spare bits plus `Method*` top bits with VA check | open |
| Option A (epoch fallback) | open |
| Option B (trace-ID offset, self-calibration, JFR cross-check) | open |
| Linux runs: Linux-only `hotspotMethodId_ut` cases, ASan, aarch64, musl, benchmark | open |
| Per-dump cache for repeated raw frames (each occurrence currently re-pins) | open |
| `JmethodIdOverheadBenchTest.java`: temporary harness, don't commit | uncommitted |

### Files touched

```
ddprof-lib/src/main/cpp/hotspot/klassRegistry.{h,cpp}   new: Klass* → weak mirror registry
ddprof-lib/src/main/cpp/hotspot/hotspotSupport.{h,cpp}  registerClass, readMethodHolder, resolveViaRegistry
ddprof-lib/src/main/cpp/hotspot/vmStructs{.h,.inline.h} VMKlass::containsMethod, VMConstMethod::idnum, hasKlassMethods
ddprof-lib/src/main/cpp/jvmSupport.{h,cpp}              Lazy_loaded state and dispatch
ddprof-lib/src/main/cpp/arguments.{h,cpp}               fjmethodid=lazy
ddprof-lib/src/main/cpp/counters.h                      method_resolve_lazy_{unloaded,not_current,class_loaded}
ddprof-lib/src/test/cpp/{klassRegistry,jvmSupport,arguments}_ut.cpp
ddprof-test/src/test/java/com/datadoghq/profiler/cpu/LazyJmethodIdTest.java
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

`-Ptests` takes a single pattern. Comma-separated lists don't match.

## Alternatives set aside

- **JVMTI ObjectFree on tagged mirrors** as an unload signal: it needs
  `can_tag_objects`, and the events are posted later from the service thread, so they
  don't tell you when the metadata is freed.
- **GC start/finish callbacks** to resolve before unloading: JNI isn't allowed inside
  them, and they aren't known to cover unloading by concurrent collectors.
- **Copying names in the handler:** too expensive, and Symbols can be freed too.
- **JFR's own sampler (JDK 25+):** it solves this inside the VM, but it doesn't cover
  JDK 8–21, J9 or Zing.
