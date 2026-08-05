# dd-trace-doe Reproduction — Real-Workload Memory Overhead (2026-08-05)

This is a real-workload cross-check of the synthetic findings in
[memory-sweep-results-linux.md](memory-sweep-results-linux.md), run against
an actual Spring Boot application via
[dd-trace-doe](https://github.com/DataDog/dd-trace-doe) instead of the
synthetic `memsweep` harness. It measures dd-trace-java's (tracer) and
this profiler's (via dd-trace-java's `DatadogProfilerController`) native
memory footprint separately, using peak RSS and JVM Native Memory Tracking
(NMT), and resolves a specific question raised along the way: why does the
JVM's own native JFR engine still show activity when this profiler is
configured to write its own separate, independent JFR stream instead of
using it.

## Summary

**Tracing dominates NMT-visible growth; profiling's NMT footprint is
small, but only because most of it bypasses NMT entirely.** Enabling
dd-trace-java's tracer alone (no profiling) grows NMT-tracked committed
memory by ~70 MB, driven by bytecode instrumentation: more loaded classes,
more JIT-compiled code, more interned symbols. Turning on profiling on top
of that adds only ~18 MB more to NMT's tracked categories — but the
profiler's own `NativeMem` counters (see
[memory-usage-model.md](memory-usage-model.md)) independently report
~43-46 MB of live native memory for the same run, dominated by call-trace
storage (~25 MB) and native symbol tables (~12 MB). The profiler's
buffers are plain `malloc`/`mmap` in a separate `.so`, never routed
through HotSpot's NMT-hooked allocator, so this cost is real, additive,
and simply invisible to NMT — consistent with the "NMT undercounts the
profiler's true footprint" pattern already documented in the synthetic
sweep.

**A single-digit tens-of-MB gap remains, in the same range as the
synthetic sweep's unattributed remainder.** After accounting for NMT's
steady-state delta, the profiler's own NativeMem counters, and the
transient JIT-compiler-arena peak (NMT reports this only as a `(peak=...)`
annotation, but it's relevant here because dd-trace-doe's own memory
metric is itself a peak, not a steady-state reading), tracing-alone still
leaves **~39 MB of peak-RSS growth unexplained**, and profiling-alone
leaves **~12 MB unexplained**. The ~39 MB figure is the same order of
magnitude as the ~42-57 MB unattributed remainder in the synthetic sweep
(memory-sweep-results-linux.md). This is flagged as a *suggestive but
unconfirmed* parallel — the two experiments differ enough in methodology
(real Spring Boot workload vs. synthetic microbenchmark, peak RSS vs.
steady-state RSS) that the magnitude match could point to a shared
accounting blind spot, or could be coincidental. Not chased further here.

**"JFR disabled" changes which independent JFR stream carries this
profiler's data — it does not disable the JVM's native JFR engine.**
There is no single "main" JFR recording that one implementation owns:
the JVM has its own native JFR engine (producing the JVM's own events,
plus whatever dd-trace-java's auxiliary `jdk.jfr.Event` classes emit),
and this profiler has its own, completely separate and independently
implemented JFR-format writer. Normally, dd-trace-java's
`CompositeController` builds both an `OpenJdkController` and this
profiler's `DatadogProfilerController` side by side, and this profiler
can be told to enable specific JVM JFR events (e.g. `CPUTimeSample`)
that then go out through the JVM's own stream — the two never merge or
interleave; `CompositeController` just concatenates whatever independent
byte streams each controller produces. Setting
`-Ddd.profiling.debug.jfr.disabled=true` skips building
`OpenJdkController` entirely, so this profiler instead runs standalone
and writes only its own independent stream — which is why
`NativeMem`/`ProfilerCounter` events (specific to this profiler's own
format) only show up in that configuration. But the NMT `Tracing`
(`mtTracing`) category still grew by ~16 MB under this config, and `jcmd
Thread.print` confirmed a live `JFR Recorder Thread` and `JFR Periodic
Tasks` thread — the JVM's native JFR engine was genuinely running
regardless. Root cause: dd-trace-java defines several real
`jdk.jfr.Event` subclasses for signals unrelated to continuous profiling
(exception sampling, endpoint tracking, queue time, deadlock detection,
direct allocation sampling), and these always go through the JVM's own
engine, independent of this profiler's mode. This profiler's own JFR
writer (`flightRecorder.cpp`/`jfrMetadata.cpp`) was confirmed to be fully
self-contained and structurally incapable of driving the JVM's engine —
it never calls into HotSpot's internal `Jfr::`/`JfrChunkWriter`
machinery.

## Environment

| Property | Value |
|---|---|
| Harness | [dd-trace-doe](https://github.com/DataDog/dd-trace-doe), `archetype=enterprise` (real Spring Boot workload) |
| Duration | 90s per run |
| OS | Linux x86_64 (Docker containers) |
| JDK | Temurin 21 |
| dd-trace-java | 1.65.0, `libjavaProfiler.so` built from this checkout |
| Metric | dd-trace-doe's `memory` field (peak RSS), corroborated with `jcmd VM.native_memory summary` |

Getting this profiler's own independent stream to carry its
`NativeMem`/`ProfilerCounter` events requires
`-Ddd.profiling.debug.jfr.disabled=true` — confirmed via bytecode
disassembly of dd-trace-java's `CompositeController.build()` that this
flag skips constructing `OpenJdkController`/`OracleJdkController`, so
this profiler's `DatadogProfilerController` runs standalone instead of
alongside it. Do not run a second `-agentpath`-loaded instance of
`libjavaProfiler.so` alongside dd-trace-java's already-loaded one as an
alternative — two independent native-agent instances of the same shared
library in one JVM crashed it (SIGSEGV, corrupt partial JFR file) in
testing.

## RSS peak numbers

dd-trace-doe's own `memory` field, itself a peak measurement:

| Run | memory (MB) | Δ vs baseline |
|---|---|---|
| baseline (no tracer, no profiler) | 1514.3 | — |
| tracing=true, profiling=false | 1650.4 | +136.1 |
| tracing=true, profiling=true (this profiler standalone, its own stream) | 1754.7 | +240.4 (profiling adds +104.3 on top of tracing) |

Tracing-only mode loads none of dd-trace-java's bundled native libraries
— no `libddwaf.so` (AppSec/WAF), no `libjnidispatch.so` (JNA), no
`libjavaProfiler.so` — confirmed via `/proc/1/maps` inside the container.
In this configuration dd-trace-java is doing pure bytecode
instrumentation; its native libraries are tied to AppSec and profiling
being enabled separately.

## NMT steady-state diff

`jcmd VM.native_memory summary`, captured ~40s into each 90s run:

| Category (committed) | baseline | tracing-only | tracing+profiling |
|---|---|---|---|
| Total | 2,294,959 KB | 2,366,454 KB (+69.8 MB) | 2,384,758 KB (+87.7 MB) |
| Class | 5,226 KB | 9,244 KB | 10,751 KB |
| Code | 19,387 KB | 37,425 KB | 46,230 KB |
| Symbol | 11,114 KB | 18,790 KB | 19,363 KB |
| Metaspace | 29,226 KB | 51,907 KB | 54,672 KB |
| Tracing (mtTracing) | ~0 | 32 KB | 16,181 KB |
| Compiler arena, `(peak=...)` | 53,462 KB | 80,802 KB | 109,235 KB |

Tracing alone accounts for most of the NMT-visible growth — more loaded
classes, more JIT-compiled code, more interned symbols from bytecode
instrumentation — which dominates over profiling's own cost at the NMT
level. Profiling's own NMT-visible increment is only +17.9 MB on top of
that.

## Reconciling RSS against NMT + profiler counters

Adding NMT's steady-state delta, the profiler's own `NativeMem` total
(~43-46 MB, dominated by `calltrace` ~25.3 MB, `native_symbols` ~11.7 MB,
`dictionary` ~7.1 MB — see [memory-usage-model.md](memory-usage-model.md)
for what these categories mean), and the transient JIT-compiler-arena
peak spike (relevant here since dd-trace-doe's `memory` metric is itself
a peak, not a steady-state sample):

- **Tracing-alone**: ~97 MB explained of the +136.1 MB RSS-peak delta →
  **~39 MB unexplained**.
- **Profiling-increment**: ~92 MB explained of the +104.3 MB RSS-peak
  delta → **~12 MB unexplained**.

## Resolved: does disabling JFR actually disable the JVM's JFR engine?

No. This was checked properly rather than assumed, after the NMT diff
showed the `Tracing` category still growing substantially under
`profiling.debug.jfr.disabled=true`:

- `jcmd JFR.check` reported "No available recordings" — but this only
  queries the *public* `FlightRecorder`/`jdk.jfr.Recording` registry, not
  whether the underlying native engine is active.
- `jcmd Thread.print` showed live **`JFR Recorder Thread`** and **`JFR
  Periodic Tasks`** threads (absent when profiling was off entirely) —
  proof the real native JFR engine was running.
- This profiler's own source (`flightRecorder.cpp`, `jfrMetadata.cpp`,
  and every file using `dlsym` in `ddprof-lib`) was checked end-to-end:
  no calls into HotSpot's internal `Jfr::`/`JfrChunkWriter` classes
  anywhere, and no lookups of JFR-related native symbols. This profiler's
  JFR writer is fully self-contained C++ and structurally incapable of
  causing this.
- dd-trace-java's `DatadogProfiler`/`DatadogProfilerController`/
  `CompositeController` classes were checked directly against source
  (`github.com/DataDog/dd-trace-java`) and never touch
  `jdk.jfr.Recording`/`FlightRecorder` either.
- Root cause: dd-trace-java defines several genuine `jdk.jfr.Event`
  subclasses for signals that have nothing to do with this profiler at
  all — `ExceptionSampleEvent` / `ExceptionCountEvent` (exception
  profiling), `EndpointEvent`, `QueueTimeEvent`, `DeadlockEvent` /
  `DeadlockedThreadEvent`, `BackpressureSampleEvent`,
  `DirectAllocationSampleEvent` / `DirectAllocationTotalEvent`. These
  always go through the JVM's own native JFR engine, regardless of
  whether this profiler is running standalone or alongside
  `OpenJdkController`. Loading or using any of these bootstraps the JVM's
  native JFR engine (recorder thread + periodic-task thread) as a side
  effect, with no corresponding user-visible `Recording` — exactly
  matching what was observed.

**Conclusion**: there is no single "main" JFR engine that either side
owns. The JVM has its own native JFR engine — used for the JVM's own
events, for whichever of this profiler's events are enabled to run
through it when composited with `OpenJdkController`, and for
dd-trace-java's own auxiliary events unconditionally — and this profiler
has a second, entirely separate and independently implemented JFR-format
writer that it uses when running standalone. Neither implementation
"owns" or interacts with the other; they're just two unrelated sources
of JFR-formatted output that happen to coexist in the same process.
`profiling.debug.jfr.disabled=true` only chooses whether this profiler's
own samples go out via the JVM's engine or via its own separate one; it
was never going to silence the JVM's JFR subsystem, since dd-trace-java's
always-on auxiliary events use that engine independently of this flag.

## What we don't know

The specific mechanism for the ~39 MB (tracing) / ~12 MB (profiling)
unattributed remainders, and whether they share a root cause with the
~42-57 MB unattributed remainder in the synthetic sweep
(memory-sweep-results-linux.md) or are coincidental. Not investigated
further in this pass.
