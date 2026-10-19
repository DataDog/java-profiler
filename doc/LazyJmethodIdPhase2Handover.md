# Phase 2 prototype: hand-over

> **Prototype branch, not for merging.** Branch `proto/phase2-pending-set`, off #868's
> `investigate/lazy-jmethodid-vm-resolution`. Plan: `doc/LazyJmethodIdCombinedPlan.md` (phase 2).
> Written 2026-10-16 on macOS arm64 (JDK 25.0.1 Corretto, release build); continued the same day on
> Linux arm64 (Ubuntu 24.04, 16 cores, JDK 21.0.12 Microsoft build, g++ 13 release build).

## Goal and acceptance criterion

Give names to lazy raw frames whose class is unloaded before the dump. The user's criterion:
**worth doing only if GC pause times don't increase significantly.**

## What the prototype does (`ddprof-lib/src/main/cpp/hotspot/unloadCapture.{h,cpp}`)

Enabled with `DDPROF_CAPTURE_UNLOADING` in `fjmethodid=lazy` mode; off otherwise, so one build
measures every variant: `1` = GC hook only, `2` = background drain + GC hook, `3` = background
drain only (the recommended variant, see the Linux results). `DDPROF_CAPTURE_INTERVAL_MS` sets the
drain interval (default 100).

- **Sampler** (`HotspotSupport::fillJavaFrame` -> `UnloadCapture::onRawFrame`): a raw frame whose
  holder's `ClassLoaderData` is not the boot, platform or app loader's goes into a lock-free set of
  (`Method*`, tag) pairs: 16,384 slots, 16 linear probes. Each slot has a state word: FREE ->
  PENDING (published by the sampler) -> DRAINING (claimed by CAS, so two drainers never take the
  same pair) -> DONE (captured; the pair stays in the set so the sampler does not add it again) or
  back to FREE (refused). `endDump()` clears DONE slots, so a method is captured at most about
  once per dump interval. When all 16 probes are taken, the sampler evicts a DONE slot (DONE is
  only a dedup hint); only then is overflow counted. Permanent CLDs are learned in
  `registerClass()` (GetClassLoader + `isSystemClassLoader`).
- **Background drain** (modes 2, 3): a daemon thread attached as "java-profiler UnloadCapture"
  wakes every interval and, if anything is pending, resolves each claimed pair through
  `HotspotSupport::capturePinned()` = `readMethodHolder` under crash protection, then
  `resolveViaRegistry()` (registry `pin()` + trace-ID check + `containsMethod` + `readMethod` +
  redefinition mark), the same path as the dump but without touching the
  `method_resolve_lazy_*` counters. `cache_lock` is held only around cache lookups and inserts,
  never across the JNI pin. Started once, never stopped.
- **`GarbageCollectionStart`** (modes 1, 2; `vmEntry.cpp` forwards to it and to
  ReferenceChainTracker): one atomic load if nothing is pending. Otherwise, under `tryLock` of the
  cache: claims pending pairs and, for each not cached yet, `HotspotSupport::captureMethod()` =
  `readMethodHolder` + trace-ID check + `containsMethod` + `readMethod`, all under crash
  protection, no JNI/JVMTI/locks. Uses `initCurrentThreadSignalSafe()` (the callback runs on the
  VM thread; `acquireCurrent()` returned null on macOS, pool exhausted).
- **Dump** (`Lookup::fillRawMethod`): when `resolve()` refuses a frame, `UnloadCapture::take()`
  supplies the captured name. `endDump()` (after `writeMethods`) frees entries captured before the
  previous dump and clears DONE slots.
- Counters `unload_capture_*`: `pending_added`, `pending_evicted`, `pending_overflow`,
  `hook_calls`, `hook_busy`, `hook_drained`, `hook_ns`, `hook_max_ns`, `captured`, `refused`,
  `bg_passes`, `bg_ns` (wall), `bg_cpu_ns` (thread CPU), `bg_max_ns` (wall), `bg_captured`,
  `bg_refused`, `cache_full`, `used`. New: `method_resolve_lazy_unreadable` counts lazy frames
  whose `Method*` could not even be read at dump time (freed metadata); before it, most losses
  were not counted at all.
- Known prototype gaps: the GC-hook path has no redefinition check beyond `containsMethod`; the
  drain scans all 16,384 slots per pass (~256 KB, cheap at 10 Hz but not at every GC pause); each
  entry is 3-4 mallocs (names + line table); the cache is a `std::unordered_map` under a spinlock;
  the drain thread is never stopped or joined (it must be before dlclose / profiler restart).

## Results on macOS (release, first prototype: GC hook only)

Harnesses in `utils/phase2-proto/` (they lived in /tmp on the Mac). The "lost" numbers in this
section undercount: they predate `method_resolve_lazy_unreadable`, see the Linux section.

**1. Is there a problem to solve?** `Bench3`: worker threads churn class loaders (10 classes per
loader, 50 ms per loader, ~800 classes dying/s), JVM unloads on its own schedule, periodic dumps.

| G1, 50 ms generations | Lost names (lazy counters: unloaded + stale + not_current) |
|---|---|
| 5 s dumps | <= 0.3% |
| 60 s dumps (dd-trace-java default) | 28% (G1), 43% (`-XX:MetaspaceSize=16m`) |
| 1 s generations (~40 classes/s) | 0: no class unloaded in 120 s |

- Most refusals are `stale`, not `unloaded`: freed metaspace is reused at once by a same-shaped
  class at the same `Klass*`, and the trace-ID check refuses the old frame (correct).
- `fjmethodid=true` loses these names too (15,241 `<unloaded>` methods in the same 60 s run;
  counted differently, not directly comparable). So phase 2 improves on today's default, it does
  not fix a lazy-mode regression.
- ZGC runs unloaded no classes at all; not explained yet.

**2. Recovery with the prototype** (same 60 s / 50 ms G1 run): `used=14811` frames named from the
capture, `captured=29174`, `pending_overflow=2`, `cache_full=0`. That is more than the lazy refusal
counters (32 unloaded + 6,815 stale), so some failures are not counted by them (probably
`readMethodHolder` failing on freed memory, or faults); the real loss was higher than the table
above.

**3. GC pause cost.** Hook time in the 60 s churn run: 30 calls, 22.6 ms total, **max 2.77 ms in
one pause** (~0.6 us per captured method). Few GCs there (21 young + 12 concurrent in 120 s), so
thousands of methods pile up between GCs and are captured in one burst.

`GcBench2` (4 allocating threads, `-Xmn32m`, ~800 young GCs/s, plus 2 churn threads),
`-Xlog:safepoint`, 3 interleaved runs of 15 s, `analyze_sp.py` ("At safepoint" of G1 operations):

| Mode | GC safepoints/run | mean ms | p50 | p99 | stopped s/run |
|---|---:|---:|---:|---:|---:|
| no profiler | 11,956 | 0.371 | 0.364 | 0.463 | 4.76 |
| lazy | 11,689 | 0.402 | 0.396 | 0.498 | 5.02 |
| lazy + capture | 11,673 | 0.405 | 0.400 | 0.500 | 5.05 |

With frequent GCs the hook adds ~nothing (few methods per pause). **The problem is the burst with
rare GCs**: up to ~2.8 ms in a single pause.

## Results on Linux arm64 (release; JDK 21 unless noted)

**Conclusion: use the background drain only (mode 3) and drop the GC hook.** It recovers the
names (0% lost in every churn run) and leaves GC pauses where plain lazy mode has them. The GC
hook costs every pause something whenever the pending set is non-empty, which it nearly always
is under class churn, and its worst burst was 8.7 ms in one pause.

**1. The loss is much larger than measured on macOS.** With `method_resolve_lazy_unreadable` added,
`Bench3` (G1, 60 s dumps, 50 ms generations, 120 s) loses **62%** of raw frames in plain lazy mode
(2 runs: resolved ~17.7k; unloaded 45-81, stale 5.4-7.6k, not_current 3-5, **unreadable 21-24k**).
With 10 ms generations: 87% lost. Most failures are `unreadable`: the `Method*` is already freed
when the dump reads it. Single-generation ZGC (`-XX:-ZGenerational`): 87% lost.

**2. Recovery** (`lost` = refused by `resolve()` and not named from the capture either):

| Bench3 run (G1, 60 s dumps, 120 s) | lost | hook max (in a pause) | drain CPU |
|---|---:|---:|---:|
| lazy, 50 ms generations | 62% | - | - |
| mode 1 (GC hook), 50 ms | 0.0% | **8.5-8.7 ms** | - |
| mode 2 (drain + hook), 50 ms | 0.0% | 0.1 ms | - |
| mode 3 (drain only), 50 ms | 0.0% | - | 0.31 s |
| mode 3, 10 ms generations | 0.0% | - | 0.32 s |
| mode 3, single-gen ZGC, 50 ms | 0.3% | - | - |

The mode 1 burst: 41 hook calls drained 47.8k pairs, most of them in a few pauses (G1 ran only ~21
young + ~19 concurrent cycles in 120 s). With the drain at 100 ms the hook finds ~1k pairs in total
and is not needed: mode 3 recovers as well as mode 2. Drain CPU is ~7 us per captured method in
Bench3 (~0.26% of one core); its wall time per pass is much higher than its CPU time (`bg_max_ns`
up to 37-130 ms) because the thread blocks in JNI during safepoints and on the registry lock. That
costs the application nothing, but widens the window in which a class can unload before capture.

The table is the final variant (DONE marks + eviction). Two intermediate variants, for the
record: without DONE marks each drained pair was re-added on its next sample (`pending_added` 305k
in dotty, 1.1M in finagle-http, for 14k / 9k methods); with DONE marks but no eviction the set
filled up within a dump interval in Bench3 (~47k distinct methods/min) and loss rose to 1.3-17%.

**3. GC pauses** (`GcBench2`, `gcbench.sh`, 3 interleaved runs of 15 s per mode, "At safepoint" of
G1 operations, final variant):

| `-Xmn512m` (~65 GCs/s) | GC sp/run | mean ms | p50 | p99 | stopped s/run |
|---|---:|---:|---:|---:|---:|
| no profiler | 995 | 0.836 | 0.820 | 1.136 | 0.918 |
| lazy | 976 | 0.856 | 0.845 | 1.114 | 0.913 |
| mode 1 (GC hook) | 965 | 1.031 | 1.011 | 1.289 | 1.074 |
| mode 2 (drain + hook) | 966 | 1.039 | 1.022 | 1.288 | 1.079 |
| **mode 3 (drain only)** | 978 | **0.861** | 0.846 | 1.122 | 0.921 |

| `-Xmn32m` (~650 GCs/s) | GC sp/run | mean ms | p50 | p99 | stopped s/run |
|---|---:|---:|---:|---:|---:|
| no profiler | 10,009 | 0.531 | 0.522 | 0.661 | 5.984 |
| lazy | 9,833 | 0.540 | 0.531 | 0.687 | 6.002 |
| mode 1 (GC hook) | 9,495 | 0.594 | 0.556 | 0.817 | 6.262 |
| mode 2 (drain + hook) | 9,535 | 0.595 | 0.556 | 0.823 | 6.252 |
| **mode 3 (drain only)** | 9,876 | **0.544** | 0.534 | 0.701 | 5.971 |

Max values are single outliers in every mode (3-12 ms, no pattern) and are left out. Mode 3 vs
lazy: +4-5 us mean, +8-14 us p99, inside run-to-run noise; time to safepoint is unchanged (mean
62 vs 62 us at 512m, 48 vs 58 us at 32m). Every mode with the hook adds ~55-175 us to the mean
pause: whenever the set is non-empty the hook scans all slots, and with the 16k set (needed for
DONE marks) that is the dominant cost. Before the set grew (8,192 slots, no DONE marks) the hook
modes were +15-35 us mean, +0.1 ms p99; the same direction, but smaller.

**4. ZGC.** Generational ZGC (`-XX:+ZGenerational` on 21, the only ZGC mode on JDK 25) unloads
**no** classes in this workload, with or without the profiler (`Churn.java`: 37k
classes loaded in 40 s, 0 unloaded, on JDK 21 and 25.0.4; metaspace grows to ~128 MB; major
collections triggered by "Metadata GC Threshold" and "CodeCache GC Threshold" run "Concurrent
Process Non-Strong" but unload nothing). Not explained; it is JVM behaviour, not ours. Under it
there is nothing to recover: Bench3 lazy shows 0% lost. Single-generation ZGC on 21 unloads like
G1 (87% lost in lazy mode, 0.3% with mode 3).

**5. Real workloads (Renaissance 0.16 `dotty`, `finagle-http`, G1, `cpu=10ms,wall=50ms`, 60 s dumps,
150 s each, `RenWrap.java`).** Plain lazy mode loses **nothing** (dotty: 20,085 resolved, 14
not_current, 0 unloaded/stale/unreadable; finagle-http: 12,663 / 8). Renaissance runs each
benchmark in its own class loader, so all benchmark code counts as unloadable, as application code
would in a Spring Boot fat jar or a servlet container. In such apps the capture is pure overhead:
mode 3 captured 14.2k (dotty) / 9.3k (finagle-http) methods, used none, at 0.28 s / 0.19 s drain
CPU per run (~0.2% / ~0.1% of one core), plus ~5k cache entries with 3-4 mallocs each per dump
interval.

## Next steps (in order)

1. **Decide whether the default needs phase 2 at all.** Real workloads lost nothing; the loss is
   specific to rapid class-loader churn (generated classes, scripting engines, short-lived
   plugin loaders). The cost when it is not needed is small but not zero: ~0.1-0.3% of a core and
   one capture per sampled method per dump interval in apps whose code lives in a custom loader.
2. If kept: **mode 3 only**. Remove the GC hook, the GarbageCollectionStart forwarding and
   `captureMethod()`. Then:
   - Allocate entries from a per-generation arena (chunked bump allocator, freed whole in
     `endDump()`) instead of 3-4 mallocs per entry, to keep the malloc arena out of it.
   - Replace `std::unordered_map` + spinlock with something bounded (an open-addressing table
     sized like the pending set).
   - Stop and join the drain thread on profiler stop (as `ReferenceChainTracker::stopThread()`).
   - Consider a cheaper "unloadable" filter, so apps with a long-lived custom loader pay less, e.g.
     only capture loaders that are not `isSystemClassLoader` *and* were created after profiling
     started, or count capture usefulness (`used / captured`) and back off when it stays 0.
3. Turn `method_resolve_lazy_unreadable` into a real counter in the main lazy PR regardless:
   without it the loss is invisible.
4. Validation tests per the combined plan: `ContextClassLoaderUnloadTest` with names for frames of
   unloaded classes, and the pause benchmark as a slow test.
5. Open: why generational ZGC never unloads these loaders.

**Tests run** (Linux arm64, debug, g++): `testDebug -Ptests=*Lazy*` passes (6/6) with capture off.
With `DDPROF_CAPTURE_UNLOADING=3`, 5/6 pass (including `LazyRedefinitionStressTest`);
`LazyJmethodIdTest.framesOfUnloadedClassAreDroppedSafely` fails as expected: it asserts that a
frame of an unloaded class is *not* named after unload, and the capture names it. If phase 2
lands, that assertion becomes "named from the capture".

## How to run the harnesses

```
ASM=<asm-9.x.jar>; CLS=ddprof-lib/build/classes/java/main; LIB=ddprof-lib/build/lib/main/release/linux/<x64|arm64>/libjavaProfiler.so
cd utils/phase2-proto && javac -cp "$ASM:$CLS" -d /tmp/p2 *.java
# Linux: build with -Pnative.forceCompiler=g++ if clang++ cannot find the libstdc++ headers
# Unload / recovery: <lib> <dump_interval_s> <generation_ms> <run_s> [threads]; -Dmode=true|lazy
DDPROF_CAPTURE_UNLOADING=1 java -cp "$ASM:$CLS:/tmp/p2" Bench3 $LIB 60 50 120
# GC pauses: modes none / lazy (DDPROF_CAPTURE_UNLOADING=0) / capture (=1), 15 s each, interleaved
DDPROF_CAPTURE_UNLOADING=1 java -XX:+UseG1GC -Xmx512m -Xmn32m -Xlog:safepoint:file=R/capture-1-sp.log \
  -agentpath:$LIB=start,cpu=1ms,cstack=vm,fjmethodid=lazy,jfr,file=R/capture-1.jfr -cp "$ASM:/tmp/p2" GcBench2 15
python3 analyze_sp.py R none lazy capture
# Linux drivers (same harnesses; set ASM, CLS first; modes 0-3 as DDPROF_CAPTURE_UNLOADING):
utils/phase2-proto/bench3.sh $LIB out/m3 3 60 50 120 [-XX:+UseZGC ...]
utils/phase2-proto/gcbench.sh $LIB out/gc512 3 15 512m   # modes none lazy gc bggc bg
# Renaissance (renaissance-mit-0.16.0.jar on the class path):
DDPROF_CAPTURE_UNLOADING=3 java -cp "$CLS:/tmp/p2:renaissance-mit-0.16.0.jar" RenWrap $LIB 60 -t 150 dotty
# NMT (phase 1): java -XX:NativeMemoryTracking=summary -cp "$ASM:$CLS:/tmp/p2" Bench2 20000 <none|true|false|lazy> <load|sample> $LIB
```
