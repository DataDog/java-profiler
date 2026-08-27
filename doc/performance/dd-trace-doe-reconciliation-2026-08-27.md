# dd-trace-doe memory reconciliation, 27 Aug 2026

**The profiler adds ≈ 60 MiB to the application's anonymous memory on this
workload — about 3.8 % — and that overhead is fully accounted for. The
unexplained residual is ≈ 0 to +5 MiB, within measurement error in all six
independent variants tested.**

Two caveats bound how this figure should be quoted:

- **It is a 90-second figure, not a ceiling.** Anonymous memory never plateaus
  within the run, and the profiling arm accumulates ~26 MiB/min faster than the
  baseline. A longer workload reports more.
- **It depends on how the memory instrument is read.** Different defensible
  estimators of the same data span 20 MiB (see
  [Instrument properties](#instrument-properties)).

Harness, workload and instruments follow
`dd-trace-doe-reproduction-2026-08-05.md`; read that first for methodology.
Mechanism detail for the call-trace counter is in `memory-sweep-results-linux.md`
(§ "`NM_CALLTRACE`: counting residency at source instead of correcting for it").

---

## Conditions

| | |
| --- | --- |
| Workload | `archetype=enterprise` (Spring Boot), `duration=90`, 9000 requests |
| Reps | 12 interleaved pairs (tracing-only, tracing+profiling) |
| Heap | `-Xms2g -Xmx2g`, set by the harness entrypoint |
| Library | local build, verified by checksum end-to-end |

Harness: `memsweep/run_doe_interleaved.sh`.
Analysis: `memsweep/analyse_doe_interleaved.py`.

Four design requirements, each load-bearing:

1. **Interleave the two conditions within one window.** Measuring them in
   separate windows lets machine drift land preferentially on one arm and shifts
   the delta by ~14 MiB.
2. **Counterbalance the within-pair order** (pair 1 profiling first, pair 2
   baseline first, …). The first run in a pair carries ~7 MiB more anonymous
   memory regardless of which arm it is; counterbalancing cancels this rather
   than letting it pick a side.
3. **Exclude container-teardown samples from the analysis.** The sampler runs
   until the cgroup file disappears, so every trace ends with the JVM exiting and
   anon collapsing toward zero (1581 → 13 MiB). Eight such samples out of ~4500
   move the apparent within-run standard deviation from 19 to 72 MiB.
   `analyse_doe_interleaved.py` truncates the trailing collapse.
4. **Do not use `-XX:+AlwaysPreTouch`.** It halves precision — paired SE 4.24 →
   8.34 MiB, detrended within-run noise 6.96 → 15.34 — apparently because
   touching 2048 MiB up front puts the cgroup under enough pressure to make anon
   *more* variable. It does collapse estimator spread (20.3 → 5.9 MiB), so it
   buys robustness at the cost of precision; not worth adopting by default.

Calibration is pinned rather than re-derived: `loops_num=1712244`,
`allocs_num=408773` with `loops_cpu`/`allocs_cpu` = 0. This removes one
calibration container per invocation and, more importantly, a confound — each arm
would otherwise calibrate independently and could run a slightly different
workload. All other archetype parameters are unchanged.

### Build provenance

A checksum gate runs at both packaging stages: the `libjavaProfiler.so` inside
the published Maven artifact **and** inside the shaded `dd-java-agent` jar are
confirmed byte-identical to the locally built library (md5
`6103cb7a9cc2f8e015f25629d75a2a72`). Without this gate, Gradle can silently
resolve the upstream ddprof release instead of the local build — an exact-pinned
version does not fuzzy-match a same-numbered local `-SNAPSHOT`; use
`-PddprofUseSnapshot=true`. Keep the gate on any re-run.

---

## Reconciliation

Two independent instruments account for the delta: the JVM's **Native Memory
Tracking** (JVM-internal growth caused by the profiler being attached) and the
profiler's **own per-category counters** (allocations NMT cannot see).

NMT's *absolute* committed total is never comparable to anonymous memory — it
counts committed address space, and with a 2 GiB fully-committed heap it exceeds
anon by ~660 MiB. Only the paired *delta* is used, where the heap's
committed-versus-touched gap cancels.

Malloc-backed counter categories carry a ×1.17 chunk-overhead correction.
Call-trace is mmap-backed and measured directly, so no residency factor applies.

Reconciliation is computed from **per-pair differences**, not from a difference of
independently measured means.

| Term | MiB | SE |
| --- | --- | --- |
| Anonymous-memory paired delta (steady mean) | 60.48 | 4.24 |
| NMT committed paired delta | 27.06 | 2.96 |
| Profiler counters, raw | 24.92 | 0.08 |
| Profiler counters, corrected (live basis) | 28.56 | 0.10 |
| Profiler counters, corrected (peak basis) | 31.69 | 0.10 |
| **Explained** (live / peak) | **55.62 / 58.75** | |
| **Residual** (live / peak) | **+4.86 / +1.73** | 5.17 |

A positive residual means anonymous memory exceeds what we can name. Across all
six variants — two JVM configurations × three ways of reading anon — every
residual falls within 2 σ of zero:

| config | anon basis | residual (live) | residual (peak) |
| --- | --- | --- | --- |
| default | steady mean | +4.86 (0.94 σ) | +1.73 (0.33 σ) |
| default | synchronous t = 70 s | +9.86 (1.51 σ) | +6.73 (1.03 σ) |
| default | synchronous t = 30 s | −4.01 (1.06 σ) | −7.14 (1.89 σ) |
| pretouch | steady mean | +2.02 (0.24 σ) | −1.10 (0.13 σ) |
| pretouch | synchronous t = 70 s | +1.91 (0.20 σ) | −1.21 (0.13 σ) |
| pretouch | synchronous t = 30 s | +2.68 (0.43 σ) | −0.43 (0.07 σ) |

The live basis runs slightly positive and the peak basis slightly negative — the
signature expected if true call-trace residency lies between the live gauge
(3.48 MiB) and its peak (6.61 MiB), which is exactly what the counter's known
`clear()` limitation implies. Reading that bracket as the answer puts the
residual at **≈ 0 to +5 MiB**.

Confidence rests on agreement across variants rather than on any single number:
each variant alone carries ± 4–9 MiB.

---

## Where the profiler's memory goes

Live bytes by category, mean of 12 reps. Malloc-backed categories carry a further
×1.17 chunk overhead not shown here.

| Category | MiB | SE | Share |
| --- | --- | --- | --- |
| `native_symbols` | 11.293 | 0.0000 | 45.3 % |
| `dictionary` | 6.809 | 0.0025 | 27.3 % |
| `calltrace` | 3.484 | 0.0038 | 14.0 % |
| `jfr_buffers` | 1.158 | 0.0000 | 4.6 % |
| `liveness` | 0.750 | 0.0000 | 3.0 % |
| `method_map` | 0.699 | 0.0029 | 2.8 % |
| `line_tables` | 0.579 | 0.0040 | 2.3 % |
| `thread_local` | 0.092 | 0.0001 | 0.4 % |
| `thread_filter` | 0.039 | 0.0000 | 0.2 % |
| `thread_info` | 0.009 | 0.0001 | 0.0 % |
| `wallclock` | 0.008 | 0.0000 | 0.0 % |
| **total** | **24.919** | **0.08** | 100 % |

**`native_symbols` and `dictionary` together are 72 % of the profiler's directly
measured memory** — they, not call-trace storage, are where optimisation effort
belongs. These counters are also the most reproducible instrument in the
investigation: SE below 0.1 MiB across twelve runs, so essentially all
uncertainty in the reconciliation comes from the memory instrument, not from
counter error.

---

## Instrument properties

dd-trace-doe's `memory=` output is `max(cgroup anon)` — **anonymous memory only**
(no page cache, no file-backed pages), taken as a running **maximum** over ~900
samples across the load and stop phases (`internal/schema/output.go`). Anon is
the right quantity to reconcile against malloc/mmap counters, since it excludes
file-cache noise. The maximum is less helpful: it is an extreme-value statistic,
so it is upward-biased and latches the largest transient in the run.

`run_doe_interleaved.sh` therefore samples cgroup anon directly at 2 Hz and
records the value at the instant of each NMT snapshot. Reads come from the
**host** cgroup path; `docker exec … cat` is unsuitable because it spawns a
process inside the target's own cgroup and inflates the number being measured
(1519616 vs 1257472 bytes observed).

### Anonymous memory ramps; it does not plateau

| | raw sd | detrended sd | ramp |
| --- | --- | --- | --- |
| profiling | 19.16 | 6.96 | +57.43 MiB/min |
| tracing-only | 15.80 | 10.66 | +31.04 MiB/min |

Within-run variation is dominated by a monotonic climb, not by noise — detrended
noise is only 7–11 MiB. Two consequences: the 90-second workload never reaches
steady state, so **the overhead figure is duration-dependent**; and estimator
choice matters because each estimator samples a different point on a rising line.

### Estimator sensitivity

| estimator | paired delta | sd | SE |
| --- | --- | --- | --- |
| `max(anon)` | 71.96 | 17.18 | 4.96 |
| steady mean (t ≥ 30 s) | 60.48 | 14.70 | 4.24 |
| steady median | 63.98 | 14.83 | 4.28 |
| synchronous at t = 30 s | 51.61 | 13.00 | 3.75 |
| synchronous at t = 70 s | 65.48 | 20.23 | 5.84 |

A 20 MiB spread on a ~60 MiB quantity. The steady mean is used above as the
primary figure: it averages ~130 in-run samples and avoids both the startup ramp
and the extreme-value bias of the maximum. Two NMT snapshots are taken per run
(t = 30 s and t = 70 s) so that anon and NMT can be differenced at the same
instant; anon is still climbing at t = 30 s, so t = 70 s is the steady-state
pairing.

### Transient JIT compiler arenas

The `Arena Chunk` NMT category swings by ~20 MiB depending on whether a snapshot
lands mid-compilation (26,139 KB observed against ~5,115 KB typical). When it
does, both anon and NMT move together — cross-validating the instruments, since
those outliers are real transient memory rather than measurement error. Because
anon and NMT are now sampled synchronously, `Arena Chunk` can be differenced out
of both sides; doing so shifts the result by under 1 MiB in these runs.

### Further reps have limited value

Paired sd is ~15 MiB, so SE = sd/√n gives ~4.2 MiB at n = 12, ~2.7 at n = 29,
~1.7 at n = 79. Resolving the residual below the ~3 MiB uncertainty already
carried by the ×1.17 chunk-overhead factor would not change any conclusion.
Measuring the remaining terms directly is worth more than more repetitions.

---

## Remaining named biases

Both are small, bounded, and known:

- **Call-trace `clear()` under-count**, bounded by the 3.48 → 6.61 MiB
  live-to-peak spread. `clear()` un-records a retained chunk's bytes but does not
  unmap it, so already-touched pages stay resident while the counter forgets them.
  The dominant rotation path does unmap, bounding this at roughly one chunk.
- **The ×1.17 chunk-overhead factor is borrowed, not measured here** (~± 3 MiB).
  It came from a workload with ~650,000 live allocations at ~83 B mean. Overhead
  depends on mean allocation size per category, and the categories here differ:
  `method_map` pays 16.7 % (96 B requested → 112 B real) while large-allocation
  categories such as `jfr_buffers` pay ~0 %. The counters emit bytes but not
  allocation counts, so the correct per-category factor cannot be derived from the
  current data.

## Candidates that would explain a larger gap

These were assembled when the gap appeared larger. They now **sum to more than
the residual** (~12–18 MiB against ≈ 0–5), so they cannot all contribute at the
magnitudes estimated. The likeliest resolution is that free-but-held arena slack
is much smaller on this workload than on the synthetic sweep where it was
measured.

| Est. | Candidate |
| --- | --- |
| ≈ 7.6 MiB | **Free-but-held arena pages.** Measured on the synthetic sweep with SE 3.0 and a sign-changing range (−7.2 to +17.2). Mostly *other* subsystems' chunks stranded by interleaving, so not attributable to any profiler allocation — a process-level, allocator-specific property. |
| a few MiB | **Natively created profiler thread stacks.** Created via `pthread_create`, not by the JVM, so their resident stack pages appear in neither NMT's Thread category nor the profiler's counters — a structural blind spot between the two instruments. |
| 2–4 MiB | **The profiler library's own resident image.** Text and data pages of a 1.38 MB shared object. Not an allocation, so no counter sees it; not JVM-managed, so NMT does not either. |
| ≈ 0.9 MiB | **Unattributed profiler malloc.** Resolves only to a private `operator new`. |

---

## Recommended next steps

The governing lesson: **every correction factor is a place where a number
measured in one workload is applied to another.** One such factor remains
(×1.17), and it is a property of the *allocator*, not the profiler — as is arena
slack. Under tcmalloc or jemalloc (both selectable via `allocator=`) both behave
differently, which is an argument for reporting them explicitly rather than
folding them into "profiler cost".

1. **Measure arena waste on this workload** via `mallinfo2()` on the JFR flush
   path, reported as process-wide allocator overhead rather than profiler memory.
   This is the single most useful remaining measurement: it is the largest
   candidate above and currently rests on analogy to a different workload.
2. **Fold chunk overhead in exactly, per allocation** via
   `malloc_usable_size()`, replacing the ×1.17 average, reported per category.
   Requires runtime allocator detection: glibc adds an 8 B header (16 B for
   mmap'd chunks), jemalloc and tcmalloc add none.
3. **Close the instrument blind spots** — natively created thread stacks and the
   library's resident image are invisible to both instruments.
4. **Measure a longer workload** to quantify the duration dependence, since the
   90 s run never reaches steady state.

Full design, including three rejected alternatives and why, is in
`overhead-program-plan.md` § "Concrete next steps", item 6.
