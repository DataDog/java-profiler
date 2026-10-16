# Phase 2 prototype: hand-over

> **Prototype branch, not for merging.** Branch `proto/phase2-pending-set`, off #868's
> `investigate/lazy-jmethodid-vm-resolution`. Plan: `doc/LazyJmethodIdCombinedPlan.md` (phase 2).
> Written 2026-10-16 on macOS arm64 (JDK 25.0.1 Corretto, release build) for continuing on Linux.

## Goal and acceptance criterion

Give names to lazy raw frames whose class is unloaded before the dump. The user's criterion:
**worth doing only if GC pause times don't increase significantly.**

## What the prototype does (`ddprof-lib/src/main/cpp/hotspot/unloadCapture.{h,cpp}`)

Enabled with `DDPROF_CAPTURE_UNLOADING=1` in `fjmethodid=lazy` mode; off otherwise, so one build
measures both.

- **Sampler** (`HotspotSupport::fillJavaFrame` -> `UnloadCapture::onRawFrame`): a raw frame whose
  holder's `ClassLoaderData` is not the boot, platform or app loader's goes into a lock-free set of
  (`Method*`, tag) pairs: 8,192 slots, 16 linear probes, duplicates skipped, overflow counted.
  Permanent CLDs are learned in `registerClass()` (GetClassLoader + `isSystemClassLoader`).
- **`GarbageCollectionStart`** (`vmEntry.cpp` forwards to it and to ReferenceChainTracker): one
  atomic load if nothing is pending. Otherwise, under `tryLock` of the cache: drains the set and,
  for each pair not cached yet, `HotspotSupport::captureMethod()` = `readMethodHolder` + trace-ID
  check + `containsMethod` + `readMethod`, all under crash protection, no JNI/JVMTI/locks. Copies
  names and line table into a cache entry (malloc). Uses `initCurrentThreadSignalSafe()` (the
  callback runs on the VM thread; `acquireCurrent()` returned null on macOS, pool exhausted).
- **Dump** (`Lookup::fillRawMethod`): when `resolve()` refuses a frame, `UnloadCapture::take()`
  supplies the captured name. `endDump()` (after `writeMethods`) frees entries captured before the
  previous dump.
- Counters `unload_capture_*`: `pending_added`, `pending_overflow`, `hook_calls`, `hook_busy`,
  `hook_ns`, `hook_max_ns`, `captured`, `refused`, `cache_full`, `used`.
- Known prototype gaps: no redefinition check at capture beyond `containsMethod`; slot drain can
  race an insert into the same slot (loses that pair); the drain scans all 8,192 slots whenever
  anything is pending; the cache is a std::unordered_map under a spinlock.

## Results so far (macOS, release)

Harnesses in `utils/phase2-proto/` (they lived in /tmp on the Mac).

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

## Next steps (in order)

1. **Background drain** (the proposed fix for bursts): a profiler thread drains the pending set
   every ~100 ms *outside* any pause, resolving pairs the normal way (registry `pin()` + trace-ID
   check + `containsMethod` + `readMethod`, as `resolveViaRegistry` does) into the same cache. A
   name is then lost only if its class unloads within ~100 ms of the sample, instead of within the
   dump interval. Keep the GC hook only for what is left (at most ~100 ms of new methods), or drop
   it and measure what that costs in recovered names. Measure both.
2. Re-measure on Linux x64 with both harnesses: `Bench3` (lost / recovered, hook max) and
   `GcBench2` (pause table), plus a low-GC-rate variant of `GcBench2` (e.g. `-Xmn512m`) to provoke
   bursts. Acceptance: no visible change in p99/max pause vs `lazy`, and hook max well below a
   young pause.
3. Count every resolution failure (add a counter where `readMethodHolder` fails), so "lost" is
   measured directly.
4. ZGC: find out why `Bench3` unloads nothing (needs a major cycle with class unloading; try
   `-XX:ZCollectionInterval` or more metaspace pressure), then measure there too.
5. Renaissance (`dotty`, `finagle-http`): `method_resolve_lazy_{resolved,unloaded,stale,not_current}`
   and `unload_capture_used` at the normal dump interval, to see whether real workloads lose names.

## How to run the harnesses

```
ASM=<asm-9.x.jar>; CLS=ddprof-lib/build/classes/java/main; LIB=ddprof-lib/build/lib/main/release/linux/x64/libjavaProfiler.so
cd utils/phase2-proto && javac -cp "$ASM:$CLS" -d /tmp/p2 Bench2.java Bench3.java GcBench2.java
# Unload / recovery: <lib> <dump_interval_s> <generation_ms> <run_s> [threads]; -Dmode=true|lazy
DDPROF_CAPTURE_UNLOADING=1 java -cp "$ASM:$CLS:/tmp/p2" Bench3 $LIB 60 50 120
# GC pauses: modes none / lazy (DDPROF_CAPTURE_UNLOADING=0) / capture (=1), 15 s each, interleaved
DDPROF_CAPTURE_UNLOADING=1 java -XX:+UseG1GC -Xmx512m -Xmn32m -Xlog:safepoint:file=R/capture-1-sp.log \
  -agentpath:$LIB=start,cpu=1ms,cstack=vm,fjmethodid=lazy,jfr,file=R/capture-1.jfr -cp "$ASM:/tmp/p2" GcBench2 15
python3 analyze_sp.py R none lazy capture
# NMT (phase 1): java -XX:NativeMemoryTracking=summary -cp "$ASM:$CLS:/tmp/p2" Bench2 20000 <none|true|false|lazy> <load|sample> $LIB
```
