# Native Memory Sweep — Empirical Results (Linux x86_64)

> Follow-up to [memory-sweep-results.md](memory-sweep-results.md) (macOS arm64)
> and [memory-usage-model.md](memory-usage-model.md), running the same
> `memsweep/` harness on Linux x86_64 (OpenJDK 21.0.10) against
> `libjavaProfiler.so` built from this checkout, to resolve the open questions
> in [memory-sweep-handoff.md](memory-sweep-handoff.md). Ran in a sandboxed
> container, which matters for one result (`NM_PERF`, see below).

**Headline results:**
1. **`NM_THREAD_LOCAL` does scale with thread count on Linux — the macOS
   "flat" reading (and Linux's own reading via the unmodified harness) is a
   measurement-methodology artifact, not an instrumentation gap.** It's a
   *live* counter, decremented via a pthread TLS destructor when each thread
   exits (`threadLocalData.cpp:56`). The harness's `threads N` workload joins
   every worker before the JFR chunk (and its counter snapshot) is finalized
   at process exit — by then, almost all `ProfiledThread` structures are
   already freed, so the "final" reading mostly reflects a handful of
   long-lived JVM-internal threads, not the N workers. Sampling mid-run
   (while all N threads are still alive) shows clean, roughly-linear scaling
   at ~824–980 B/thread, matching the model's ~650B/thread estimate.
2. **`NM_DICTIONARY` genuinely does not grow under wall-clock sampling**, even
   at 150,000 distinct classes over 180s (well past the tested macOS ceiling
   of 2,000, and past the ~35–40K theoretical chunk threshold) — this rules
   out "just needs more data" as macOS left open. But it **does** grow under
   the allocation-sampling engine (`memory=`) at only 2,000 distinct object
   shapes, confirmed via a same-N, same-duration, same-machine A/B against
   `classes` mode. Allocation sampling populates the dictionary through a
   path wall-clock+reflection sampling doesn't exercise.
3. **The macOS `addThread()` requirement is confirmed to reproduce on
   Linux** — wall-clock sampling produces zero `MethodSample` events for
   unregistered threads here too (`WallClockSamplingEpoch` fires; no
   `MethodSample`). This is very likely intentional fork behavior (every
   thread must self-register), not a platform-specific auto-registration gap.
4. **`cpu=` initializes successfully on Linux** (unlike macOS, where
   `Agent_OnLoad` failed outright) and produces real `ExecutionSample`
   events. `NM_PERF` still reads 0 here, but for an explained, environment-
   specific reason (see below) rather than remaining fully unexplored.
5. **`jcmd` attach is reliable on Linux with the agent attached, even at
   1000 threads** — once a harness timing bug (below) was fixed. This is a
   strictly better setup than macOS's agent-free workaround: NMT and RSS
   were measured in the *same process*, at the same moment, with the agent
   running.

## Harness

Same `MemSweepMain` harness as the macOS pass (see memory-sweep-results.md
for the full description of the `threads`/`traces`/`classes` modes). Two
changes were made on this branch:

- **New `allocs N` mode**, added to `GenSources.java`/`MemSweepMain.java`/
  `run_sweep.sh` to fill the "allocation profiling never exercised" gap
  flagged in the handoff doc. It precompiles N distinct short-lived object
  shapes (varying field count, so each is a genuinely different allocation
  size) and repeatedly allocates+discards them in a cycle. `run_sweep.sh`
  now drives this mode with `memory=<interval>:a` instead of `wall=<interval>`
  (4th positional arg is the allocation-sampling interval in bytes, default
  `1024`, instead of a wall-clock period).
- **Three harness bugs fixed** (all in the shell scripts, not the profiler):
  - `run_sweep.sh`/`run_nmt.sh`'s `DDPROF_LIB` auto-detection glob
    (`libjavaProfiler.*`) matched the `.debug` symbols file as readily as the
    real `.so` — `find | head -1` ordering is unspecified, so this could
    silently pick the wrong file. Fixed with `-not -name '*.debug'`.
  - `run_nmt.sh` checked for the literal string `"Baseline succeeded"` after
    `jcmd VM.native_memory baseline`, but this JDK (21.0.10) prints
    `"Baseline taken"` instead — the wording is JDK-version-dependent. Fixed
    to match either.
  - `run_nmt.sh`'s `SAMPLE_AT` sleep was computed as `(DURATION_MS-300)/1000`
    seconds from the *start of the sleep*, without accounting for the ~1s+
    already spent in the baseline retry loop before it. Total elapsed time
    could exceed the workload's own deadline by a few hundred ms, so the
    process had already exited by the time the second `jcmd` call ran —
    surfacing as `jcmd: java.io.IOException: No such process` despite the
    workload having genuinely run for its full requested duration. This
    reproduced deterministically, **even fully agent-free, at n=1 thread,
    with 60s of margin** — ruling out any connection to thread count or the
    agent's signal handling. Fixed to compute a target absolute time from
    actual launch time and sleep only the remaining delta.

  This matters for interpreting the finding below about `jcmd` reliability:
  the *initial* symptom (second `jcmd` attach failing) looked identical to
  macOS's finding, and it was tempting to file it as "confirms the macOS
  attach-interference hypothesis on Linux" — but the actual cause was
  unrelated to the agent or thread count entirely. The macOS report's error
  text ("state is not ready to participate in attach handshake") is also
  literally different from what was seen here (`IOException: No such
  process`, i.e. attach failing because the process had already exited) —
  they may not be the same phenomenon. Whether macOS's original finding
  holds up was not re-tested here and remains unconfirmed either way.

## Results: threads sweep (final-flush read, i.e. the methodology used throughout the macOS pass)

| N threads | max RSS (MiB) | calltrace | dictionary | thread_filter | thread_local | native_symbols |
|---|---|---|---|---|---|---|
| 1 | 70 | 24.5 MiB | 4.55 MiB | 40 KiB | 4944 B | 11.9 MiB |
| 4–24 | 71–79 | 24.5 MiB | 4.55 MiB | 40 KiB | 4120 B | 11.9 MiB |
| 32–48 | 82–88 | 24.5 MiB | 4.55 MiB | 40 KiB | 4944 B | 11.9 MiB |
| 64–96 | 99–111 | 24.5 MiB | 4.55 MiB | 40 KiB | 14832 B | 11.9 MiB |
| 256 | 172 | 24.5 MiB | 4.55 MiB | **72 KiB** | 14008 B | 11.9 MiB |
| 1000 | 442 | 24.5 MiB | 4.55 MiB | **136 KiB** | 14008 B | 11.9 MiB |

`calltrace`/`dictionary`/`native_symbols`/`line_tables`/`jfr_buffers`/`perf`/
`misc` are bit-for-bit identical to the macOS baseline values in every row
(same struct layouts, same initial capacities — machine-independent). The
`thread_filter` staircase (40→72→136 KiB) exactly matches macOS's, confirming
the chunked-allocation model. RSS still scales clearly with thread count
(~380–400 KB/thread from 1→1000, same order of magnitude as macOS's
~400 KB/thread, off a much lower baseline — 70 MiB here vs. ~357 MiB on
macOS, plausibly macOS's larger dyld/shared-cache footprint).

**`NM_NATIVE_SYMBOLS` is ~25× smaller on Linux (11.9 MiB vs. macOS's
294.6 MiB)**, both flat across the whole thread sweep. Consistent with the
macOS report's own hypothesis that this counter is dominated by the indexed
symbol tables of the JVM's own shared libraries — Linux's `.so`/ELF symbol
tables for the JDK are apparently far smaller than macOS's `.dylib`/Mach-O
equivalent, or are indexed differently. Not further investigated.

**`NM_THREAD_LOCAL` is *not* flat here either, but the pattern (4944 → 4120
→ 4944 → 14832 → 14008 across the sweep) is non-monotonic in N** — it isn't
tracking our own worker threads at all in this reading. See below for why.

## Follow-up: why `NM_THREAD_LOCAL` looked flat/non-monotonic — live counter, not cumulative

`ProfiledThread::forTid()` increments `NM_THREAD_LOCAL` by `sizeof(ProfiledThread)`
on allocation; `ProfiledThread::freeValue()` (a pthread TLS destructor,
`threadLocalData.cpp:56`) decrements it by the same amount when a thread
exits. **This is a live/current count, not a cumulative one** — unlike, say,
`ThreadInfo`'s name/id maps (per memory-usage-model.md), which do grow with
threads *ever seen*.

The harness's `threads N` mode calls `t.join()` on every worker before
returning from `main()`, and the JFR chunk (and its `NM_*` counter snapshot)
is only finalized at process exit, afterward. By the time the counter is
read, essentially every worker's `ProfiledThread` has already been freed by
its own thread-exit TLS destructor — the "final" reading mostly reflects
whatever small number of long-lived JVM-internal threads (compiler/GC/etc.)
happened to have live `ProfiledThread` instances at that exact moment, which
varies run-to-run based on JIT/GC scheduling and has no particular relation
to N. **This fully explains both the macOS "flat at 4120 bytes" result and
Linux's own non-monotonic final-flush numbers — they're measuring the same
kind of leftover, not a genuine per-thread cost.**

To measure the true per-thread cost, a small standalone test
(`ThreadLocalLiveTest`, not checked in — see below) calls the public
`JavaProfiler.dump(Path)` API to force a JFR chunk **while all N worker
threads are still alive and busy-looping**, instead of after they've joined:

| N threads (live at dump time) | `NM_THREAD_LOCAL` |
|---|---|
| 1 | 6,592 B |
| 64 | 68,392 B |
| 256 | 226,600 B |

Per-thread delta from 64→256: `(226600 - 68392) / (256 - 64) = 824.0` B/thread
— a clean, consistent value, plausibly `sizeof(ProfiledThread)` itself (the
struct's OTel context record alone is ~688 bytes per the comment in
`threadLocalData.h`, plus the preceding scalar fields and vtable pointer).
This matches the ~650B/thread estimate in memory-usage-model.md closely.
**Takeaway for anyone measuring this counter going forward: read it while
the threads you care about are still alive (e.g. via a mid-run `dump()`), not
after they've exited — a final-chunk read after joining/exit systematically
undercounts, in some cases down to nearly zero.** This wasn't checked in as
part of the harness since it required a one-off ad-hoc program calling the
public `dump()` API; worth adding as a proper harness mode if this dimension
needs revisiting.

## Follow-up: `NM_DICTIONARY` at far larger N — genuinely flat, not "just needs more"

Handoff open question #2 asked whether an even larger N (150,000 was
suggested) and/or longer duration would finally move `NM_DICTIONARY`, given
that macOS's 40,000-class/97,661-sample run left it flat. Ran
`classes 150000` for 180s at `wall=~1ms`:

| | before | after |
|---|---|---|
| RSS | — | 2.08 GiB |
| `calltrace` | 25,692,672 B | **50,858,496 B** (doubled — crossed a resize threshold) |
| `dictionary` | 4,774,032 B | **4,774,032 B (unchanged)** |

The call-trace hash table *did* grow (each distinct class's `compute()`
method is a distinct call-trace shape here, same as the macOS `traces`
sweep's confirmed-growth case), confirming real, diverse sampled activity
reached the profiler at this scale — but `NM_DICTIONARY` stayed
bit-for-bit identical to every other run in this document, including tiny
ones. **150,000 classes and 180 seconds is unambiguously "enough" by every
measure that moved other counters; the dictionary counter's flatness is a
real finding, not an under-sampling artifact.** This leaves the two original
hypotheses (threshold estimate too low vs. `StringDictionaryBuffer` batching
never flushing far enough) still not distinguished from each other, but does
rule out the "just needs more" explanation entirely for the *wall-clock*
sampling path specifically.

## Follow-up: allocation sampling moves `NM_DICTIONARY` where wall-clock didn't

Handoff open question #4: allocation profiling (`memory=<interval>[:a]`) and
native-malloc tracing (`nativemem=<bytes>`) were never exercised in the
original macOS pass. This pass adds a new `allocs` harness mode (see above)
to test this properly — `threads`/`traces`/`classes` don't allocate any Java
objects at all, so `memory=` had nothing to sample against them.

Direct A/B, same machine, same N=2000, same 15s duration, only the mode
(and correspondingly the sampling engine) differs:

| mode | engine | `dictionary` | ObjectSample/MethodSample events | distinct classes covered |
|---|---|---|---|---|
| `classes` | `wall=~5ms` | 4,774,032 B (baseline, flat) | (MethodSample, not counted here) | — |
| `allocs` | `memory=512:a` | **6,334,608 B (+1.56 MiB)** | 2,593 `ObjectSample` | 1,115 / 2,000 |

**Allocation sampling grew the dictionary at 2,000 distinct object shapes —
smaller than the 40,000-class run that never moved it under wall-clock
sampling.** This confirms the two engines populate `NM_DICTIONARY` through
genuinely different code paths with different effective thresholds/batching
behavior; the class/method-diversity gap documented for wall-clock sampling
in memory-usage-model.md and memory-sweep-results.md does **not** carry over
to allocation-sampling-driven class-name interning.

`nativemem=<bytes>` (native malloc tracing) was also smoke-tested: it
initializes cleanly and produces real `datadog.NativeMemoryAllocation`
events (292 in a 5s/16-thread run) even against the non-allocating `threads`
workload — the events come from generic JVM-internal native `malloc` calls,
not anything the workload does directly. No `NM_*` counter movement was
observed with that workload, which is expected (`Math.sqrt`-only busy-loops
don't drive native malloc traffic beyond baseline JVM activity). Testing
this dimension properly would need a native-malloc-heavy workload (e.g. a
`DirectByteBuffer.allocateDirect()` loop, or JNI calls) — analogous to how
`allocs` was needed for `memory=`; left as further harness work.

## Follow-up: `cpu=` works on Linux; `NM_PERF` still reads 0, but for an explained reason

Handoff open question #3. `cpu=10ms` initializes without error here (macOS
failed at `Agent_OnLoad`) and produces real `datadog.ExecutionSample` events
(88 in a 5s/16-thread run). `NM_PERF`, however, still reads 0 — traced this
to source, not left as unexplored territory this time:

```
// perfEvents_linux.cpp:874
if ((_ring & RING_KERNEL) && !Symbols::haveKernelSymbols()) {
  _ring = RING_USER;   // falls back silently
}
// perfEvents_linux.cpp:885
_use_mmap_page = _cstack != CSTACK_NO &&
                 (_ring != RING_USER || _cstack == CSTACK_DEFAULT || _cstack == CSTACK_LBR);
// perfEvents_linux.cpp:678 — NM_PERF only recorded here, guarded by `page != NULL`
```

`NM_PERF` is only incremented when a kernel-ring mmap page is actually
allocated per registered thread. That requires `RING_KERNEL` *and* readable
kernel symbols. This sandboxed test container has `kptr_restrict=1`
(`/proc/kallsyms` addresses all read as zero for non-root), so
`haveKernelSymbols()` returns false, `_ring` silently downgrades to
`RING_USER`, and with `cstack=fp` (not `CSTACK_DEFAULT`/`CSTACK_LBR`) that
combination sets `_use_mmap_page = false` — no page, no `NM_PERF`, regardless
of sample rate or thread count, even though `perf_event_open` itself
succeeds and real samples are recorded via the signal-delivery path. This is
a host/container permission gate (would need `sysctl kernel.kptr_restrict=0`,
i.e. root, to exercise), not a profiler bug, and not something this session
attempted to change (a system-wide sysctl change is out of scope for a
sandboxed investigation session). **Anyone re-running this on a Linux host
with root and relaxed `kptr_restrict`/`perf_event_paranoid` should check
`NM_PERF` again — the code path exists and looks correct; it's just gated
off here.**

## Follow-up: reconciling RSS with NMT + `NM_*`, same-process this time

Handoff open question #5. Unlike macOS, `jcmd` attach proved reliable here
with the agent attached even at 1000 threads (once the harness timing bug
above was fixed), so NMT and RSS were sampled in the *same* process, mid-run,
with the agent active — a strictly better measurement than macOS's
agent-free-control-run workaround.

| N threads | NMT "Thread" committed | Process RSS | RSS Δ from n=1 | NMT Thread Δ/thread | RSS Δ/thread | % explained by NMT Thread |
|---|---|---|---|---|---|---|
| 1 | 966 KB | 72,240 KB | — | — | — | — |
| 256 | 28,524 KB | 176,908 KB | +104,668 KB | 108.1 KB | 410.5 KB | 26.3% |
| 1000 | 87,960 KB | 453,648 KB | +381,408 KB | 87.1 KB | 381.8 KB | 22.8% |

Total NMT `committed` across *all* categories (not just "Thread") explains
almost exactly the same fraction (~26–27%) — other categories barely move
with thread count, so essentially all of NMT's thread-scaling signal is in
the Thread bucket. **This closely matches the macOS finding (~17–20%
explained there) in kind, if not in exact fraction**: the majority of
per-thread RSS growth (roughly three-quarters here, four-fifths on macOS) is
invisible to both NMT and the profiler's own `NM_THREAD_LOCAL` counter (even
read correctly, live — 824 B/thread is a rounding error against a ~400
KB/thread RSS delta) — almost certainly OS/kernel-level per-thread
bookkeeping (pthread structures, stack guard pages, kernel task
scheduling structures) outside any userspace instrumentation's reach on
either platform.

## Caveats

- **Single sandboxed Linux x86_64 container, single run per point** — same
  caveat as the macOS pass: indicative, not statistically rigorous.
- **`NM_PERF` remains unverified in practice** — the code path is understood
  and looks correct, but this environment's `kptr_restrict=1` prevented
  actually exercising it. A root-accessible bare-metal or VM Linux host would
  be needed to close this out.
- **The `allocs` mode is new and only lightly calibrated** (one N=2000 data
  point plus the A/B above) — unlike `threads`/`traces`/`classes`, it hasn't
  been swept across multiple N/duration combinations, and the coupon-collector
  coverage math from memory-sweep-results.md's "was 2,000 too small" section
  hasn't been redone for allocation-sampling's apparently different/lower
  threshold.
- **The three harness bugs above were real and would have produced wrong or
  missing data for anyone re-running the original macOS-authored scripts
  as-is on Linux** — they're now fixed in this branch, but worth keeping in
  mind that some of the original macOS session's own numbers were collected
  before these fixes existed (on macOS, `find | head -1`'s directory
  ordering may happen to have avoided the `.debug`-file bug by chance, and
  the macOS pass avoided `run_nmt.sh` with the agent attached entirely, so
  its own `SAMPLE_AT` bug never triggered there since the diff/summary calls
  in the agent-free-only runs typically completed comfortably inside the
  margin — but this wasn't independently re-verified against the original
  macOS run logs, which aren't checked in).
