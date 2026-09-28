# Sampler Performance Counters

Per-sampler timing instrumentation, compiled in only under an opt-in build flag.
Answers "how much does each sampler cost per sample?" — a question the existing
`unwinding_ticks_*` counters cannot, because they measure the shared stack
unwinder rather than any individual sampler.

## Enabling

```bash
./gradlew buildDebug   -PenableSamplerPerf
./gradlew buildRelease -PenableSamplerPerf
```

The property appends `-D__SAMPLER_PERF__` to the `release` and `debug`
configurations only (`ConfigurationPresets.kt`). It is deliberately not applied
to `asan`/`tsan`/`fuzzer`: those configs instrument every memory access, so the
per-sample times would describe the sanitizer rather than the sampler. gtest
builds inherit the flag automatically, since `GtestTaskBuilder` starts from the
configuration's own `compilerArgs`.

Without the flag the feature is entirely absent: `SAMPLER_PERF_PROBE()` expands
to `((void)0)`, `SamplerPerfProbe` does not exist, `SamplerPerf::report()` is an
empty function, and the counters occupy **no enum slot and no storage** in
`DD_COUNTER_TABLE` — they never appear in JFR or in
`JavaProfiler.getDebugCounters()`.

## Output

`SamplerPerf::report()` runs from `Profiler::stop()`, before the JFR recording is
stopped, and prints to stdout. Samplers with a zero sample count are omitted, so
only engines that actually ran are listed:

```
[java-profiler] sampler performance (elapsed wall time, not CPU time):
[java-profiler]   sampler            total (ms)        count     avg (ns)
[java-profiler]   cpu                  1204.518        61243        19668
[java-profiler]   wallclock             338.902        20104        16857
[java-profiler]   note: cpu includes unwinding_ticks_async, and alloc includes liveness; do not sum them.
```

Because the counters live in the ordinary counter table, the same values also
flow out through the two existing sinks when the flag is on: the JFR
`datadog.ProfilerCounter` events (`sampler_ticks.cpu`, `sampler_count.cpu`, …)
and `JavaProfiler.getDebugCounters()`. The average is derived, not stored.

## Measured samplers

| Slot | Engines sharing it | Probe site |
|---|---|---|
| `cpu` | `PerfEvents`, `CTimer`, `CTimerJvmti`, `ITimer`, `ITimerJvmti` | each engine's `signalHandler` |
| `wallclock` | `WallClockASGCT`, `WallClockJvmti`, `J9WallClock` | `sharedSignalHandler`; for J9, the per-thread body of `timerLoop` |
| `alloc` | `ObjectSampler` | `recordAllocation` |
| `liveness` | `LivenessTracker` | `track` |
| `nativemem` | `MallocTracer` | `recordMalloc` |
| `nativesocket` | `NativeSocketSampler` | `recordEvent` |

Only one CPU engine and one wallclock engine is ever live in a run
(`Profiler::selectCpuEngine` / `selectWallEngine`), so the variants share a slot;
per-variant slots would only ever have one of them non-zero.

There is no lock/monitor or exception sampler in this fork — the `BCI_LOCK` /
`BCI_PARK` plumbing exists but no native call site records such a sample — so
there are no slots for them.

## Reading the numbers

Five things are easy to get wrong:

1. **`sampler_ticks.*` is elapsed wall time, not CPU time.** It includes time the
   sampled thread spent descheduled, page-faulting, or waiting on the
   `Profiler::_locks[]` stripe. That is the right metric for the latency the
   sampler adds to the sampled thread, but it is not the sampler's CPU cost, and
   it inflates under load. If an average looks implausibly large, suspect
   lock-stripe contention in `Profiler::recordSample` before suspecting the
   unwinder.

2. **`sampler_ticks.cpu` already contains `unwinding_ticks_async`.** Both time
   the same unwinder. Never sum them; the unwinding counter is a strict subset
   and is the first thing to compare against.

3. **`sampler_ticks.alloc` already contains `sampler_ticks.liveness`**, because
   `LivenessTracker::track()` is called from `ObjectSampler::recordAllocation()`.
   Liveness is a nested breakdown of alloc, not a sibling to add to it.

4. **Cross-sampler nesting slightly double-counts.**
   `SIGNAL_HANDLER_GUARD_OR_DROP()` drops only when there is no `ProfiledThread`;
   it does not reject nested signals. A wallclock signal landing inside a CPU
   handler is therefore counted in both totals. The distortion is bounded and
   small — the nested handler bails almost immediately at its `CriticalSection` —
   but it is not zero.

5. **The count includes samples that bailed out** (reentrancy reject, disabled
   engine, init-window tick), which dilutes the average downward. Foreign signals
   are excluded by construction: each probe is declared after its handler's
   signal-origin check, so a stray `SIGPROF` — and the foreign handler that
   `OS::forwardForeignSignal()` runs for it — is never timed as our work.
   `ITimer` is the exception, having no origin check to sit behind (see its own
   NOTE in `itimer.cpp`). Use the `SAMPLES_DROPPED_*` / `WC_SIGNAL_*` counters to
   quantify the bail-outs.

6. **`report()` can undercount the very last sample of a run.** The probe is
   declared before `InflightGuard` (see caveat 5), so at handler exit
   `InflightGuard`'s destructor — which `Profiler::stop()`'s drain waits on —
   runs before the probe's destructor, which is the one that updates the
   counters. A handler still unwinding when the drain observes zero can have
   its counters land after `report()` already read them. The teardown work
   between the drain and `report()` dwarfs the few instructions between those
   two destructors, so this is a real but vanishingly unlikely race, and its
   only effect is under-reporting by at most one sample.

## Implementation notes

`SAMPLER_PERF_PROBE(SP_CPU)` declares a `SamplerPerfProbe`: the constructor takes
a `os::nanotime()` timestamp, the destructor adds the elapsed ticks to
`sampler_ticks.<name>` and bumps `sampler_count.<name>`.

- **Why RAII rather than a manual start/stop pair.** Every instrumented handler
  has several early returns, so a manual pair would have to be repeated at each
  exit and would silently miss any newly added one.
- **Async-signal safety.** All probe state is on the stack. No `thread_local` —
  one here would risk the lazy DTV-slot `malloc` that deadlocked against the
  JVMCI compiler on Graal aarch64 (see `guards.h`). The destructor only reads
  `OS::nanotime()` and issues two relaxed atomic adds, which land on separate
  cache lines because `Counters` pads every slot to 128 bytes.
- **Guard ordering.** The probe is declared *after* any `ErrnoPreserver`, which
  must stay the first-declared local so it destructs last — `OS::nanotime()`
  calls `clock_gettime()`, which may set `errno`. In `PerfEvents::signalHandler`
  the probe sits between
  `ErrnoPreserver` and `PerfFdRearmGuard` on purpose, so the guard's rearm
  `ioctl`s are inside the measured window.
- **Crash recovery does not lose samples.** The `sigsetjmp` landing pad is inside
  `HotspotSupport::walkJavaStack`, which the handler calls via `recordSample`, so
  a `checkFault` → `siglongjmp` unwinds only to that frame — above the probe. The
  destructor is not bypassed.
- **Layout coupling.** The probe addresses its two slots as
  `SAMPLER_TICKS_CPU + 2*id` (+1 for the count), the same base-plus-offset scheme
  the `DICTIONARY_*` group uses. `samplerPerf.h` generates `static_assert`s from
  `DD_SAMPLER_LIST` that pin this layout, so reordering
  `DD_COUNTER_TABLE_SAMPLER_PERF` in `counters.h` — or inserting an unrelated
  counter between its entries — is a compile error rather than silent
  misattribution.

Converting ticks to nanoseconds uses `SamplerPerf::ticksToNanos()`, which splits
into whole seconds plus remainder. The naive `ticks * 1e9 / frequency()`
overflows `u64` well inside a normal recording: at 3 GHz, one hour is ~1.08e13
ticks and `ticks * 1e9` is ~1.08e22, so it silently reports 2.88 seconds instead
of 3600.

## Adding a sampler

1. Add an entry to `DD_SAMPLER_LIST` in `samplerPerf.h`.
2. Add the matching `sampler_ticks.<name>` / `sampler_count.<name>` pair to
   `DD_COUNTER_TABLE_SAMPLER_PERF` in `counters.h`, **in the same position and
   with ticks before count**. The `static_assert`s will fail the build if they
   disagree.
3. Place `SAMPLER_PERF_PROBE(SP_<ID>)` at the sampler's entry point, after any
   `ErrnoPreserver` and after its signal-origin check.

## Tests

`ddprof-lib/src/test/cpp/samplerPerf_ut.cpp` is dual-mode, following
`faultInjection_ut.cpp`. Without the flag it asserts the probe is inert and that
no `sampler_*` counter exists in the table — the guard that protects production.
With the flag it covers the offset addressing, accumulation, counting on early
return, cross-sampler nesting, and the `ticksToNanos` overflow case.

```bash
./gradlew :ddprof-lib:gtestDebug                       # inert-build assertions
./gradlew :ddprof-lib:gtestDebug -PenableSamplerPerf   # enabled-build assertions
```
