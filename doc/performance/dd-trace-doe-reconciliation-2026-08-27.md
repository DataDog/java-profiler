# dd-trace-doe memory reconciliation, 27 Aug 2026

**The profiler adds 59.3 ± 9.0 MiB to the application's anonymous memory on this
workload — about 2.5 % — and that overhead is accounted for with no correction
factors: the residual is +4.3 MiB, 0.48 σ from zero.**

Measured over 12 interleaved counterbalanced pairs, sampled after anonymous
memory plateaus, where the choice of estimator changes the answer by 1.0 MiB
rather than 20.

**Quote the absolute figure, not the percentage.** The baseline here is 2405 MiB
because `AlwaysPreTouch` pins all 2048 MiB of heap as touched; without it the
same absolute overhead reads as ~3.9 % against a ~1580 MiB baseline. The
denominator is a measurement choice, so the percentage is not a property of the
profiler.

Three caveats bound how this figure should be quoted:

- **The overhead is bounded — there is no leak and no per-flush growth.**
  Confirmed over a 20-minute run with 10 observed flushes: see
  [Long-run behaviour](#long-run-behaviour). Anonymous memory plateaus by
  t ≈ 180 s and the paired delta is flat from t ≈ 60 s onward.
- **Between-run variance is the dominant uncertainty**, larger than any term in
  the reconciliation. Per-pair deltas span 26–112 MiB, so single runs are not
  informative about the absolute figure.
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
| Workload | `archetype=enterprise` (Spring Boot), `duration=300`, 30000 requests |
| Reps | 12 interleaved counterbalanced pairs, sampled at t ≥ 240 s (plateau) |
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
4. **Use `-XX:+AlwaysPreTouch`.** `-Xms2g -Xmx2g` fixes the heap's *committed*
   size, but anon counts *touched* pages, so the heap's contribution is still
   time-varying. Pre-touching makes it **constant by construction** instead of
   assumed-small, which is the point: it removes a confound rather than bounding
   it. The measured effects support this — with pretouch, the answer becomes far
   less dependent on *when* you sample:

   | | no pretouch | pretouch |
   | --- | --- | --- |
   | estimator spread | 20.34 MiB | **5.87 MiB** |
   | residual across 6 variants, mean \|σ\| | 1.13 | **0.20** |
   | residual across 6 variants, max \|σ\| | 1.89 | **0.43** |
   | baseline ramp | +31.04 MiB/min | +27.71 MiB/min |

   The one figure pointing the other way — paired sd 14.70 → 28.89 — is not
   trustworthy: the two configurations ran in separate time windows (14:51–15:30
   vs 15:52–16:31), the same cross-window flaw requirement 1 exists to prevent,
   and the difference is only marginally significant (F = 3.86 against 3.47
   critical at n = 12). No mechanism for harm exists either: the container sets
   no memory limit, the host had 21 GB of 63 GB free, and swap was untouched, so
   there is no reclaim pressure to make anon more variable.

   **Still to confirm:** whether pretouch genuinely costs paired precision. That
   needs pretouch interleaved *against* no-pretouch within one window (a 2×2
   design). Until then, prefer pretouch for the estimator-independence, and treat
   the sd comparison as unresolved.

Calibration is pinned rather than re-derived: `loops_num=1712244`,
`allocs_num=408773` with `loops_cpu`/`allocs_cpu` = 0. This removes one
calibration container per invocation and, more importantly, a confound — each arm
would otherwise calibrate independently and could run a slightly different
workload. All other archetype parameters are unchanged.

### Build provenance

A checksum gate runs at both packaging stages: the `libjavaProfiler.so` inside
the published Maven artifact **and** inside the shaded `dd-java-agent` jar are
confirmed byte-identical to the locally built library (md5
`cea2dd31108c059ff39a68eb7ddfb509`). Without this gate, Gradle can silently
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

**No correction factors are applied.** Allocator overhead is measured per
allocation and reported by the profiler as
`native_mem_chunk_overhead_bytes.<category>`; call-trace residency is counted at
source. The ×1.17 multiplier this reconciliation previously used over-credited
the explained total by 2.5 MiB — see
[Measured allocator overhead](#measured-allocator-overhead).

Reconciliation is computed from **per-pair differences**, not from a difference of
independently measured means.

| Term | MiB | SE |
| --- | --- | --- |
| Anonymous-memory paired delta (plateau mean) | 59.29 | 8.95 |
| NMT committed paired delta | 30.24 | 0.11 |
| Profiler counters, logical bytes | 23.83 | — |
| Profiler counters, measured allocator overhead | 0.97 | — |
| **Explained** | **55.04** | |
| **Residual** | **+4.25** | 8.95 |

A positive residual means anonymous memory exceeds what we can name. At
**0.48 σ** it is not distinguishable from zero.

Every term is now measured. The NMT delta in particular is reproducible to
± 0.11 MiB with both snapshots taken inside the plateau, so essentially all
remaining uncertainty is the anon delta's between-run variance.

Sampling mid-ramp reproduces the same delta with worse precision and 20× the
estimator sensitivity, so it is not used.

### Measured allocator overhead

| category | logical MiB | measured overhead | % |
| --- | --- | --- | --- |
| `native_symbols` | 11.298 | 0.9125 | 8.08 |
| `dictionary` | 6.803 | 0.0088 | 0.13 |
| `calltrace` | 3.235 | 0.0062 | 0.19 |
| `jfr_buffers` | 1.158 | — | not instrumented |
| `liveness` | 0.750 | — | not instrumented |
| `line_tables` | 0.226 | — | not instrumented |
| `method_map` | 0.220 | 0.0382 | **17.36** |
| `thread_info` | 0.008 | 0.0013 | 16.10 |
| **total** | **23.828** | **0.9669** | **4.06** |

The blanket ×1.17 would have charged **3.499 MiB** against **0.967 MiB
measured** — an over-credit of 2.5 MiB, on a residual of a few MiB.

The reason a single factor cannot work is visible in the spread: `method_map`
pays 17.36 % (small tree nodes, and the one category the old factor fitted),
while `dictionary` pays 0.13 % (512 KB chunks). Overhead is a function of
per-allocation size, and these categories differ by four orders of magnitude in
allocation size.

Removing the over-credit **widens** the gap, as expected. Holding the anon delta
at the previous run's 62.62 MiB for comparability, the residual moves from
+5.46 to +7.58 MiB — a +2.1 MiB shift matching the 2.5 MiB over-credit. The
figure reported above is lower only because this run's anon delta happened to be
3.3 MiB smaller, which is between-run variance rather than a change in accounting.

**Coverage is partial**, so 0.967 MiB is a lower bound: `jfr_buffers`,
`liveness`, `line_tables`, `thread_local`, `thread_filter` and `wallclock` record
through plain `record()` and report zero. Together they are ~2.2 MiB of logical
bytes, so at the rates seen above the unmeasured remainder is ~0.2–0.4 MiB.

---

## Where the profiler's memory goes

Live bytes by category, mean of 12 reps — logical bytes only. The allocator
overhead each category additionally pays is measured and reported separately, in
[Measured allocator overhead](#measured-allocator-overhead).

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

### Anonymous memory ramps; the profiler's share has not saturated at 90 s

| | raw sd | detrended sd | mean ramp |
| --- | --- | --- | --- |
| profiling | 19.16 | 6.96 | +57.43 MiB/min |
| tracing-only | 15.80 | 10.66 | +31.04 MiB/min |

Within-run variation is dominated by a monotonic climb, not by noise — detrended
noise is only 7–11 MiB. Estimator choice therefore matters because each estimator
samples a different point on a rising line, not because of randomness.

**The ramp is not profiler overhead — it is shared JVM growth.** NMT's committed
total grows +18.77 MiB between t = 30 s and t = 70 s (≈ 28 MiB/min) and that
growth is **identical in both arms** (difference −0.00 MiB), concentrated in
`Arena Chunk` (+14.4), `Code` (+3.3) and `Metaspace` (+0.5) — JIT compilation and
code-cache fill. The observed baseline ramp (+31.0 MiB/min) matches it closely.
Despite `-Xms2g -Xmx2g` fixing the heap's *committed* size, anon counts *touched*
pages, so heap growth was a plausible contributor; it turns out to be small —
pre-touching the heap changes the baseline ramp only from +31.0 to +27.7 MiB/min.

Because the ramp is shared, it **cancels in the paired delta**, which is the
statistic that matters:

| t (s) | paired delta (MiB) | SE |
| --- | --- | --- |
| 30 | 51.61 | 3.75 |
| 40 | 50.23 | 6.51 |
| 50 | 51.60 | 5.40 |
| 60 | 66.21 | 4.54 |
| 70 | 65.48 | 5.84 |
| 80 | 66.86 | 5.00 |
| 90 | 68.84 | 5.06 |

The delta is flat at ≈ 51 MiB through t = 50 s, **steps up ~15 MiB at t ≈ 60 s**,
then is flat again within noise (+2.6 MiB over the final 30 s, against SE ≈ 5).
The step coincides with the first JFR chunk flush. The profiler's own counters
account for only ~3.5 MiB of it (`line_tables` 0 → 0.579, `method_map` 0 → 0.699,
`dictionary` +2.2), so the step's full mechanism is not pinned; what is clear is
that it is a **one-time event, not sustained growth**.

Fitting slopes to each arm separately is misleading here: it measures the shared
JVM ramp rather than anything profiler-attributable. The paired delta is the
correct statistic.

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

### Plateau measurement (12 pairs, 5-minute runs)

The headline figures above come from 12 interleaved counterbalanced pairs of
5-minute runs with `AlwaysPreTouch`, sampled over t ≥ 240 s — after anonymous
memory has plateaued. Anon is sampled at 2 Hz (130 samples per run in the
window) and NMT twice per run, both inside the plateau.

**Estimator choice is no longer material.** On a flat curve every reasonable
estimator agrees:

| estimator | delta (MiB) | sd | SE |
| --- | --- | --- | --- |
| `max(anon)` | 63.53 | 19.46 | 5.62 |
| plateau mean | 62.62 | 18.20 | 5.25 |
| plateau median | 62.64 | 18.18 | 5.25 |
| synchronous t = 250 s | 62.52 | 18.22 | 5.26 |
| synchronous t = 290 s | 62.72 | 18.16 | 5.24 |
| **spread** | **1.00** | | |

The spread was 20.34 MiB when sampling mid-ramp. Within-run plateau sd is
0.30–0.47 MiB in every run, so the anon signal itself is essentially noiseless
once settled — all remaining uncertainty is between runs.

The residual figures are in [Reconciliation](#reconciliation).

Per-pair deltas: 76.7, 62.4, 78.4, 38.9, 86.9, 53.7, 43.1, 83.9, 53.5, 74.8,
66.4, 32.8 — a 32.8–86.9 MiB range against a within-run sd of 0.35. **The
uncertainty is entirely between-run, not measurement.** The within-pair ordering
bias persists at +9.73 MiB and is cancelled by counterbalancing.

The NMT delta differs slightly between the two plateau snapshots (29.84 MiB at
t = 290 s, 27.19 at t = 250 s), which is why the t = 250 s variants show a larger
residual: JVM-internal structures are still settling marginally even once anon
has flattened. The later snapshot is the better pairing.

### Long-run behaviour

A 20-minute paired run (one pair, `AlwaysPreTouch`, ~10 JFR flushes per arm)
settles three questions the 90-second runs could not.

**No leak.** The profiler's own counters are flat after the first flush and
several are byte-identical across every subsequent one:

| | first flush | flushes 2–10 |
| --- | --- | --- |
| total | 23.413 | bounded 23.98 – 24.98 |
| `dictionary` | 4.576 | **6.803 in every flush** |
| `native_symbols` | 11.293 | **11.293 in every flush** |
| `calltrace` | 5.499 | ~3.35 (falls, then flat) |
| `method_map`, `line_tables` | rise | *decline* after t = 180 s |

**No per-flush cost.** Anonymous memory plateaus by t ≈ 180 s and shows no step
at any 60-second flush boundary: t = 180 → 660 s moves 2500.8 → 2506.1 MiB, i.e.
+0.66 MiB/min over eight minutes. The ~15 MiB step visible at t ≈ 60 s in short
runs is part of the startup transient — class loading, JIT, first flush — not a
recurring cost.

**The startup ramp cancels between arms.** The paired delta is 104.2 MiB at
t = 60 s and 104.33 at plateau — essentially unchanged. Sampling before the
plateau therefore does *not* bias the delta, because both arms ramp together.

**Measuring at plateau nearly eliminates estimator sensitivity**, which is the
main methodological gain:

| | 90 s runs | at plateau (t ≥ 240 s) |
| --- | --- | --- |
| estimator spread | 20.34 MiB | **2.69 MiB** |
| within-run sd of the delta | — | **0.47 MiB** (n = 193 samples) |

**What this run does not establish.** Its plateau delta is 104.33 MiB against a
12-pair mean of 62.89 ± 8.34, and its residual works out at +47.6 MiB rather
than ≈ 0. That is **not** a long-duration effect: the same gap is already present
at t = 60 s, before the two configurations diverge in any way, so it is
between-run variance — and 104 sits at the top of the 26–112 MiB per-pair range
already observed. With n = 1 there is no way to separate the two, and the
within-run sd of 0.47 MiB is *not* a substitute for a between-pair standard
error. No overhead figure or residual should be quoted from this run; the
12-pair result stands as the estimate.

### Further reps have limited value

Paired sd is ~15 MiB, so SE = sd/√n gives ~4.2 MiB at n = 12, ~2.7 at n = 29,
~1.7 at n = 79. With the correction factors now replaced by measurements, the
binding constraint is the anon delta's between-run variance rather than any
accounting term — and attributing arena waste is worth more than more
repetitions.

---

## Remaining named biases

Both are small, bounded, and known:

- **Call-trace `clear()` under-count**, bounded by the 3.48 → 6.61 MiB
  live-to-peak spread. `clear()` un-records a retained chunk's bytes but does not
  unmap it, so already-touched pages stay resident while the counter forgets them.
  The dominant rotation path does unmap, bounding this at roughly one chunk.
- **Allocator-overhead coverage is partial** (~0.2–0.4 MiB unmeasured).
  `jfr_buffers`, `liveness`, `line_tables`, `thread_local`, `thread_filter` and
  `wallclock` still record through plain `record()` and report zero overhead. The
  measured total is therefore a lower bound. The counters emit bytes but not
  allocation counts, so the correct per-category factor cannot be derived from the
  current data.

## Process-wide arena waste

The profiler now reports glibc's own arena accounting (`mallinfo2`) on the flush
path. Mean over the 12 profiling-arm runs:

| counter | MiB |
| --- | --- |
| `malloc_arena_bytes` | 270.67 |
| `malloc_in_use_bytes` | 82.36 |
| **`malloc_free_held_bytes`** | **188.31** |
| `malloc_trimmable_bytes` | 0.13 |
| `malloc_mmap_bytes` | 50.34 |

`in_use + free_held = arena` exactly, which is a useful internal check on the
readings. Only **0.13 MiB is trimmable**, so `malloc_trim` could reclaim almost
none of the 188 MiB: this is genuine fragmentation, not trim-threshold
retention — consistent with the interleaving mechanism, where live allocations
scattered among freed ones prevent free chunks coalescing to the arena top.

**This is process-wide, not profiler memory**, and is dominated by the JVM's own
allocations. It is reported to make the allocator's overhead visible rather than
to attribute it. Its relevance to the residual is one of scale: the residual
(+4.25 MiB) is **2.3 %** of process-wide arena waste, so a small profiler-caused
increase in fragmentation would account for it comfortably.

**It cannot be attributed from these counters.** They are emitted through the
profiler's own JFR, so the tracing-only arm produces none, and no paired delta
can be formed. Attribution needs the same figure from both arms, which
`memsweep/malloc_info_probe.c` (an LD_PRELOAD allocator-state probe, driven by
`run_mallocinfo_capture.sh`) can supply for a process with or without the
profiler attached. That is the next measurement.

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
measured in one workload is applied to another.** Both factors this
reconciliation once used are now measurements. Both were properties of the
*allocator* rather than the profiler — under tcmalloc or jemalloc (selectable via
`allocator=`) they behave differently — which is why they are reported explicitly
instead of folded into "profiler cost". What remains is attribution, not
estimation.

1. **Attribute arena waste to the profiler.** The absolute figure is now
   measured (188.31 MiB process-wide, see
   [Process-wide arena waste](#process-wide-arena-waste)), but it cannot be
   attributed from these counters: they are emitted through the profiler's own
   JFR, so the tracing-only arm produces none and no paired delta exists. Use
   `memsweep/malloc_info_probe.c` with `run_mallocinfo_capture.sh` (LD_PRELOAD,
   works with or without the profiler) to get the figure for both arms.
2. ~~Fold chunk overhead in exactly, per allocation.~~ **Done** — reported as
   `native_mem_chunk_overhead_bytes.<category>`, measured via
   `malloc_usable_size()` with the per-chunk header probed at runtime rather than
   assumed. The ×1.17 multiplier is retired. Remaining work is coverage:
   `jfr_buffers`, `liveness`, `line_tables`, `thread_local`, `thread_filter` and
   `wallclock` still record through plain `record()` and report zero overhead
   (~0.2–0.4 MiB unmeasured).
3. **Close the instrument blind spots** — natively created thread stacks and the
   library's resident image are invisible to both instruments.
4. ~~Measure a longer workload to test the flush step.~~ **Done** — see
   [Long-run behaviour](#long-run-behaviour). No leak, no per-flush growth,
   plateau by t ≈ 180 s. **Adopt ~5-minute runs sampled at t ≥ 240 s** for future
   measurement: that reaches plateau, where estimator spread falls from 20.3 to
   2.7 MiB, while keeping 12 pairs affordable (~2 h rather than the ~8 h that
   20-minute pairs would cost).
5. **Attack between-run variance — now the dominant uncertainty.** Per-pair
   deltas span 26–112 MiB while the within-run delta is stable to 0.47 MiB, so
   the variance lives in run-level factors (host state, JIT decisions, container
   placement), not in sampling. It exceeds every term in the reconciliation, so
   until it is reduced or averaged down, no refinement of the counters will
   sharpen the headline figure.
6. **Confirm `-XX:+AlwaysPreTouch` with a 2×2 interleaved design** (pretouch and
   no-pretouch alternating within one window). It is already the recommended
   default on the strength of estimator-independence; what remains is to check
   whether the apparent precision cost is real or a cross-window artifact.

Full design, including three rejected alternatives and why, is in
`overhead-program-plan.md` § "Concrete next steps", item 6.
