# dd-trace-doe Reproduction — Real-Workload Memory Overhead (2026-08-05)

This is a real-workload cross-check of the synthetic findings in
[memory-sweep-results-linux.md](memory-sweep-results-linux.md), run against
an actual Spring Boot application via
[dd-trace-doe](https://github.com/DataDog/dd-trace-doe) instead of the
synthetic `memsweep` harness. It measures dd-trace-java's (tracer) and
this profiler's native memory footprint separately, using peak RSS and
JVM Native Memory Tracking (NMT).

## What dd-trace-doe is, and how this differs from the synthetic sweep

[dd-trace-doe](https://github.com/DataDog/dd-trace-doe) runs a real
packaged application (here, the `enterprise` archetype — a Spring Boot
app with a realistic dependency/endpoint footprint) inside Docker under
sustained synthetic traffic for a fixed duration, with dd-trace-java
attached the way a customer actually would (as a `-javaagent`, doing
bytecode instrumentation, with this profiler embedded inside it rather
than run standalone). Its `memory` metric is the container process's
**peak RSS** over the whole run. This makes it good for checking whether
a claimed overhead number holds up end-to-end in something resembling
production, but it can't cleanly isolate *why* — a real app's class
count, call-graph shape, thread count, and GC behavior are all fixed by
the workload and confounded together.

The [memory-sweep-results-linux.md](memory-sweep-results-linux.md)
synthetic sweep is the opposite trade-off: small, purpose-built Java
programs with this profiler attached directly via `-agentpath` (no
tracer at all), each sweep varying exactly one dimension (thread count,
call-trace diversity, class diversity, allocation diversity) while
holding everything else fixed, read continuously via this profiler's own
live `NM_*` counters. That isolates mechanism cleanly but says nothing
about whether the isolated effects actually add up to the overhead a
real deployment sees.

This report uses dd-trace-doe for exactly what it's good for — confirming
the previously-reported ~250 MB figure is real and reproducible, and
getting a coarse tracer-vs-profiler split from a handful of on/off runs —
then leans on the synthetic sweep's already-established mechanisms
(NMT undercounting the profiler's own buffers, etc.) to explain the
pieces, rather than re-deriving mechanism from the real-workload numbers
directly.

## Summary

This reproduces the originally-reported **~250 MB memory overhead** for
the enterprise archetype: measured peak-RSS delta from baseline to
tracing+profiling is **+240.4 MB**, in line with that figure. In
absolute terms, that's a peak RSS of **1514.3 MB with nothing attached**
growing to **1754.7 MB with tracer and profiler both on** — the tracer
and profiler together add **~16%** on top of the app's own baseline
footprint.

Coarse breakdown of where that memory goes:

| Where it goes | ~MB | Driven by |
|---|---|---|
| JVM growth (classes, JIT code, symbols) | ~97 | tracer |
| JVM growth (classes, JIT code, symbols, JFR engine) | ~46 | profiler |
| Profiler agent's own native memory (outside the JVM entirely) | ~44 | profiler |
| Unexplained | ~53 | tracer ~39, profiler ~12, rounding |
| **Total measured** | **~240** | (original claim: ~250) |

The tracer's cost is almost entirely inside the JVM: enabling
dd-trace-java alone (no profiling) grows JVM-tracked (NMT) memory by
~97 MB, driven by bytecode instrumentation — more loaded classes, more
JIT-compiled code, more interned symbols, plus the transient
compiler-arena spike from JIT-compiling that injected code.

Turning on profiling on top of that adds two distinct things: (1) ~46 MB
more *inside* the JVM — more classes/code/symbols from the profiler's own
instrumentation, plus the JVM's native JFR engine starting up, which is
actually dd-trace-java's own auxiliary JFR event classes (exception
sampling, endpoint tracking, etc.) rather than this profiler, but only
shows up once profiling is turned on — and (2) ~44 MB of this profiler's
*own* native memory, entirely outside the JVM and invisible to NMT (see
[memory-usage-model.md](memory-usage-model.md)): plain `malloc`/`mmap` in
the agent's own `.so` for call-trace storage (~25 MB) and native symbol
tables (~12 MB), never routed through HotSpot's NMT-hooked allocator —
consistent with the "NMT undercounts the profiler's true footprint"
pattern already documented in the synthetic sweep.

**A single-digit tens-of-MB gap remains, in the same range as the
synthetic sweep's unattributed remainder.** Accounting for all of the
above still leaves **~39 MB of the tracer's peak-RSS delta unexplained**,
and **~12 MB of the profiler's**. The ~39 MB figure is the same order of
magnitude as the ~42-57 MB unattributed remainder in the synthetic sweep
(memory-sweep-results-linux.md). This is flagged as a *suggestive but
unconfirmed* parallel — the two experiments differ enough in methodology
(real Spring Boot workload vs. synthetic microbenchmark, peak RSS vs.
steady-state RSS) that the magnitude match could point to a shared
accounting blind spot, or could be coincidental. Not chased further here.

## Environment

| Property | Value |
|---|---|
| Harness | [dd-trace-doe](https://github.com/DataDog/dd-trace-doe), `archetype=enterprise` (real Spring Boot workload) |
| Duration | 90s per run |
| OS | Linux x86_64 (Docker containers) |
| JDK | Temurin 21 |
| dd-trace-java | 1.65.0, `libjavaProfiler.so` built from this checkout |
| Metric | dd-trace-doe's `memory` field (peak RSS), corroborated with `jcmd VM.native_memory summary` |

Getting this profiler's own `NativeMem`/`ProfilerCounter` counters to
appear at all requires `-Ddd.profiling.debug.jfr.disabled=true` (a
dd-trace-java config flag; confirmed via bytecode disassembly of
`CompositeController.build()`). Without it, dd-trace-java's default
composite mode doesn't produce those counters, which would otherwise
make this profiler's own memory cost invisible to this kind of
measurement. Do not run a second `-agentpath`-loaded instance of
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
| tracing=true, profiling=true | 1754.7 | +240.4 (profiling adds +104.3 on top of tracing) |

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

Profiling's own NMT-visible increment (+17.9 MB) is small compared to
tracing's (+69.8 MB) — see Summary for why, and for where the rest of
profiling's cost actually goes.

## Reconciling RSS against NMT + profiler counters

This is the arithmetic behind the Summary's coarse breakdown. Adding
NMT's steady-state delta, the profiler's own `NativeMem` total (~43-46 MB
— see [memory-usage-model.md](memory-usage-model.md) for what its
sub-categories mean), and the transient JIT-compiler-arena peak spike
(relevant here since dd-trace-doe's `memory` metric is itself a peak, not
a steady-state sample):

- **Tracing-alone**: 69.8 MB (NMT) + 26.7 MB (compiler-arena peak delta
  vs. baseline) = ~97 MB explained of the +136.1 MB RSS-peak delta →
  **~39 MB unexplained**.
- **Profiling-increment**: 17.9 MB (NMT) + ~44 MB (profiler `NativeMem`)
  + 27.8 MB (compiler-arena peak delta) = ~92 MB explained of the
  +104.3 MB RSS-peak delta → **~12 MB unexplained**.

## Other archetypes: is this workload-specific?

The same baseline / tracing-only / tracing+profiling measurement was
repeated against the other three dd-trace-doe archetypes (`idle`,
`latency`, `throughput`) to check whether the ~240 MB figure is specific to
the `enterprise` workload or holds more generally. All four run the same
Spring Boot app; only the traffic pattern and simulated CPU/allocation load
differ.

| Archetype | baseline | tracing-only | tracing+profiling | Δ tracing | Δ profiling | Δ total |
|---|---|---|---|---|---|---|
| enterprise | 1514.3 | 1650.4 | 1754.7 | +136.1 | +104.3 | +240.4 |
| idle | 1528.8 | 1648.8 | 1754.9 | +120.0 | +106.1 | +226.1 |
| latency | 1553.3 | 1710.0 | 1800.7 | +156.7 | +90.7 | +247.4 |
| throughput (mean of 3/3/2 reps) | 1555.2 | 1693.4 | 1811.3 | +138.2 | +117.9 | +256.1 |

**The overhead is largely workload-invariant.** `idle` (RPS=5, almost no
CPU work) lands within a few MB of `enterprise` (RPS=100) on every number,
despite the two workloads differing by orders of magnitude in traffic and
CPU usage. That's consistent with the earlier finding that the overhead is
driven by which classes/methods get touched — fixed by the app's own code,
since all four archetypes run the same Spring Boot app — rather than by
request volume, concurrency, or CPU load.

**Single-run peak-RSS numbers are noisy — repeat before treating a
difference as real.** `throughput`'s profiling-increment looked like an
outlier on the first pass (+64.3 MB vs. +90-106 MB for the other three,
each from a single run). Repeating `throughput` (3 reps of baseline and
tracing-only; 2 successful reps of tracing+profiling — the 3rd hit a
transient load-generator timeout unrelated to memory) put its mean
profiling-increment at +117.9 MB, squarely inside the other archetypes'
range. The original single-run sample (1766.0 MB) sat ~40-50 MB below both
of its own repeats (1805.5 MB, 1817.1 MB). Treat any single-run
dd-trace-doe `memory` figure — including the `enterprise` numbers earlier
in this report — as carrying roughly that much run-to-run noise.

**Confirmed directly via class counts, not just inferred from RSS.** Captured
NMT's `Class` count (`jcmd VM.native_memory summary`, mid-run) for all three
archetypes' baseline/tracing-only/tracing+profiling configs, the same way as
`enterprise` earlier:

| Archetype | baseline | tracing-only | tracing+profiling |
|---|---|---|---|
| enterprise | ~7,907 | 13,241 | 13,872 |
| idle | 7,907 | 13,232 | 13,640 |
| latency | 7,916 | 13,238 | 13,664 |
| throughput | 7,921 | 13,262 | 13,668 |

Baseline and tracing-only class counts are essentially identical across all
four archetypes (spreads of 14 and 30 classes respectively — noise).
Tracing roughly doubles the class count regardless of RPS/concurrency,
because it's driven by which classes get touched by instrumentation, not by
how many requests flow through them. `enterprise`'s tracing+profiling count
runs ~200-230 classes ahead of the other three, the one place a real (if
small) difference shows up — plausibly its higher `loops_cpu`/`off_cpu`
exercising a few extra code paths once profiling's own instrumentation is
also active. This is a more direct confirmation of the touched-methods/
fixed-cost framing than the RSS numbers alone.

## What we don't know

The specific mechanism for the ~39 MB (tracing) / ~12 MB (profiling)
unattributed remainders, and whether they share a root cause with the
~42-57 MB unattributed remainder in the synthetic sweep
(memory-sweep-results-linux.md) or are coincidental. Not investigated
further in this pass.
