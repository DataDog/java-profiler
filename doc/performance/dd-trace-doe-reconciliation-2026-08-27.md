# dd-trace-doe memory reconciliation, 27 Aug 2026

> **Revised 31 Aug 2026.** The single-number headline this document previously
> carried ("59.3 ± 9.0 MiB, residual +4.3 MiB at 0.48 σ") is superseded, and two
> of its conclusions are retracted outright — see
> [What changed in the 31 Aug revision](#what-changed-in-the-31-aug-revision).

**The profiler's anonymous-memory cost is not one number. It is a reproducible
term of 35.98 ± 0.26 MiB, plus glibc free-but-held arena waste which is fully
resident, is a real RSS cost, and varies from run to run:**

```
Δanon = 35.98 ± 0.26  +  1.0119 ± 0.0066 × Δfordblks
        R² = 0.9992,  residual SD 0.77 MiB,  20 pairs in two batches
```

The practical consequence is that **the raw total is not a stable quantity.** Two
independently measured batches gave anon deltas of **58.86 ± 8.53** (12 pairs)
and **73.90 ± 7.88** (8 pairs) — 15 MiB apart — because Δ`fordblks` moved from
+22.86 to +37.09 between them. Their *stable* terms agreed to **0.4 MiB**. Quote
the two terms separately; a single total inherits the arena term's variance and
cannot be reproduced.

**Quote the absolute figure, not the percentage.** The baseline here is 2405 MiB
because `AlwaysPreTouch` pins all 2048 MiB of heap as touched; without it the
same absolute overhead reads as ~3.9 % against a ~1580 MiB baseline. The
denominator is a measurement choice, so the percentage is not a property of the
profiler.

Four caveats bound how these figures should be quoted:

- **The overhead is bounded — there is no leak and no per-flush growth.**
  Confirmed over a 20-minute run with 10 observed flushes: see
  [Long-run behaviour](#long-run-behaviour). Anonymous memory plateaus by
  t ≈ 180 s and the paired delta is flat from t ≈ 60 s onward.
- **All the run-to-run variance is the arena term.** It is not measurement
  noise and not JVM settling in general: within a plateau a run's anon level is
  reproducible to **0.13 MiB**, while paired deltas scatter with SD 29.56 MiB.
  Δ`fordblks` explains that scatter at R² = 0.999.
- **±8.53 is the standard error of a 12-pair mean, not a per-pair SD** (that is
  29.56). So the old residual of +4.02 MiB carried a 95 % CI of
  **[−12.7, +20.7]**, and the smallest residual this design could detect at 95 %
  was **16.7 MiB**. "Not distinguishable from zero" was true but half the story:
  a ~20 MiB gap could not have been excluded either.
- **Counted bytes are not resident bytes.** NMT reports committed address space
  and the profiler's counters report bytes requested, while anon counts pages
  touched. Comparing them requires a residency factor per term — see
  [Residency factors](#residency-factors).

Harness, workload and instruments follow
`dd-trace-doe-reproduction-2026-08-05.md`; read that first for methodology.
Mechanism detail for the call-trace counter is in `memory-sweep-results-linux.md`
(§ "`NM_CALLTRACE`: counting residency at source instead of correcting for it").

---

## What changed in the 31 Aug revision

Three corrections, two of them reversals of stated conclusions. All are measured,
and where a previous claim was wrong the mechanism that made it wrong is given so
the same reasoning is not repeated.

**1. Free-but-held arena memory is resident. It was ruled out as non-resident;
that was wrong.** The original argument was that total malloc address space
(`arena` + `hblkhd` = 80.47 MiB) exceeds the anon delta (58.83) by 21.6 MiB,
matching Δ`fordblks` (22.97) almost exactly, so free-held pages must be unbacked.
The arithmetic is right and the inference does not follow: Δ`arena` (57.73) and
Δ(`uordblks`+`hblkhd`) (57.50) happen to coincide in that dataset, so matching the
*mean* cannot discriminate the two models. The *variance* can, and it is decisive
— Δ(`uordblks`+`hblkhd`) has SD 0.16 MiB against anon's 29.56 and correlates
−0.005 with it, so that model cannot explain why anon moves between pairs at all.
Regressing anon on Δ`fordblks` gives a slope of **1.0119 ± 0.0066** (20 pairs),
1.8 σ from 1.0 and 153 σ from 0. Per-mapping `smaps` confirms it independently:
glibc arena regions hold 214.9 MiB Rss against 78.7 MiB of in-use arena bytes.
**The residency split was also inverted** — the 21.6 MiB of unbacked address
space is `hblkhd`, whose mmap-served chunks measure ~0 resident.

**2. `LinearAllocator::clear()` is not a source of under-counting.** It is
reachable only from `~LinearAllocator()` and never runs in a live profiler. Full
retraction in [Remaining named biases](#remaining-named-biases); the same claim
in `memory-sweep-results-linux.md` is retracted there too, along with the
proposed per-chunk high-water fix, which is not needed.

**3. Counted bytes are not resident bytes**, and the two sides of the
reconciliation were being compared on different bases. Residency factors are now
measured per term — see [Residency factors](#residency-factors).

One hypothesis was raised during this revision and **refuted**, recorded so it is
not re-proposed: that `native_symbols` and `dictionary` over-state their RSS cost
by being mmap-served. Both are arena-served and resident. See
[Which categories are mmap-served](#which-categories-are-mmap-served).

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

> **Read this table with two corrections (31 Aug).**
>
> *The σ is the standard error of the 12-pair mean, not a per-pair SD* (29.56).
> So the residual's 95 % CI is **[−12.7, +20.7] MiB** and the smallest detectable
> residual is **16.7 MiB**. The table cannot distinguish a residual of 0 from one
> of +18; "0.48 σ from zero" should not be read as "small".
>
> *The two sides use different bases.* "Explained" sums NMT **committed** address
> space and profiler **requested** bytes; "anonymous-memory paired delta" counts
> **resident** pages. They are only comparable after a residency factor is applied
> per term — see [Residency factors](#residency-factors). Applied at the resident
> level, the model closes to ~4 MiB on the 8-pair batch (predicted 77.9 against
> measured 73.95), so the table's apparent 4.25 MiB residual and that ~4 MiB gap
> are not the same quantity and should not be equated.

Every term is now measured. The NMT delta in particular is reproducible to
± 0.11 MiB with both snapshots taken inside the plateau, so essentially all
remaining uncertainty is the anon delta's between-run variance.

**And that variance has a single named source (31 Aug).** It is glibc arena
growth, not host state or JIT decisions as previously supposed. See
[Where the variance comes from](#where-the-variance-comes-from).

Sampling mid-ramp reproduces the same delta with worse precision and 20× the
estimator sensitivity, so it is not used.

**Reproduced.** A second, independent 12-pair run (the one carrying the
LD_PRELOAD arena sampler) gives anon delta **58.83 ± 8.53**, NMT delta
**30.00 ± 0.18**, counters **23.85 + 0.96**, explained **54.82**, residual
**+4.02 ± 8.53** (0.47 σ). Two independent measurements agreeing to 0.46 MiB on
the delta and 0.23 MiB on the residual.

## Full breakdown

Everything below is from a single 12-pair interleaved run, plateau-sampled, so
the parts sum exactly to the whole. All figures are paired deltas
(tracing+profiling **minus** tracing-only), i.e. the cost of *enabling
profiling* — the same workload without it does not pay them.

**Total: 58.83 ± 8.53 MiB**

> **The percentages below are batch-specific, not properties of the profiler
> (31 Aug).** They are shares of *this* batch's 58.83 MiB total. A second batch
> measured 73.90 MiB on the same workload, so the same absolute terms would read
> as 41 % / 34 % rather than 51 % / 42 %. The difference is entirely the arena
> term. The A/B/C split also predates the finding that arena waste is resident,
> so it omits the largest varying term altogether — quote the two-term model in
> the header instead, and treat A and B as a breakdown of the *stable* side.

### A. JVM-internal — 30.00 MiB (51 %)

| NMT category | Δ MiB | |
| --- | --- | --- |
| `Tracing` | **+15.17** | JFR subsystem initialised — **no recording running** |
| `Code` | +8.36 | code cache; profiling-specific Java being JIT-compiled |
| `Metaspace` | +2.18 | |
| `Class` | +1.33 | |
| `Internal` | +1.20 | |
| `Thread` | +0.59 | JVM-created threads only |
| `Native Memory Tracking` | +0.53 | NMT's own bookkeeping |
| `Symbol` | +0.46 | |

This is memory the JVM allocates, but it appears **only when profiling is
enabled**, so it is profiler-caused overhead. What the distinction changes is who
can act on it: none of it is the native profiler's own allocation.

The `Tracing` term is JFR machinery initialised without a recording — see
[Why JFR is initialised](#why-jfr-is-initialised). It is not an artifact of this
benchmark's configuration, and in production, where JFR runs a real recording,
the cost is likely higher rather than lower.

The tracer's own bytecode-instrumentation cost does **not** appear here: both
arms run `tracing=true`, so it cancels. (For scale, it is much larger — the
tracing step alone adds ~17.6 MiB of `Code` and ~22.1 MiB of `Metaspace`.)

### B. The profiler's own allocations — 24.81 MiB (42 %)

| category | Δ MiB | measured allocator overhead |
| --- | --- | --- |
| `native_symbols` | 11.32 | +0.91 |
| `dictionary` | 6.81 | +0.01 |
| `calltrace` | 3.23 | +0.01 |
| `jfr_buffers` | 1.16 | not instrumented |
| `liveness` | 0.75 | not instrumented |
| `line_tables` | 0.22 | not instrumented |
| `method_map` | 0.22 | +0.04 |
| `thread_local`, `thread_filter` | 0.12 | |
| **allocator overhead, total** | **0.96** | |

`native_symbols` and `dictionary` are 73 % of this. Any real reduction work
starts here — it is the only part of the total that the profiler itself owns.

### C. Residual — 4.02 MiB (6.8 %)

**Superseded (31 Aug) — see the retraction note at the end of this section.**

30.00 + 24.81 + 4.02 = 58.83. **At 0.47 σ the residual is not distinguishable
from zero, so no mechanism is required to explain it** — that, not the table
below, is the load-bearing statement. The candidates below are gaps we know
exist and whose signs are right; only the last two are quantified tightly enough
to sum, so treat the table as an argument that the residual is unsurprising, not
as an accounting of it:

| candidate | bound |
| --- | --- |
| `calltrace` flush-phase sampling bias (live 3.37, all-time peak 6.59) | ≤ 3.22, loose ¹ |
| uninstrumented allocator overhead | ~0.2–0.4 |
| natively created profiler thread stacks (invisible to NMT *and* to the counters) | ~0.1–0.5 |
| the profiler `.so`'s writable pages | < 1 |

¹ **This bound is loose and must not be read as a point estimate.** It is
`max − live`, and `NativeMem::_max[]` is an all-time latch — nothing resets it in
production (`NativeMem::reset()` is tests-only). Measured across all 12 runs, the
`calltrace` peak is set during chunk 2 and then never moves again:

```
live:  5.53  3.55  3.36  3.36  3.34  3.24
max :  5.53  6.64  6.64  6.64  6.64  6.64
```

So 6.59–6.64 MiB is a high-water from the startup ramp, not the crest of the
steady-state rotation cycle — and because `max` stops moving after chunk 2, the
steady-state crest is strictly *below* it, by an unmeasured margin. The true
cycle amplitude, and hence the real size of this bias, needs the
`native_mem_post_flush_*` counters. See
[Remaining named biases](#remaining-named-biases).

> **FREE-BUT-HELD ARENA MEMORY IS RESIDENT (31 Aug).** It is a real RSS cost of
> +22.9 to +37.1 MiB — one of the two largest terms in this reconciliation. Residency measures **1.0119 ± 0.0066** over 20 pairs
> (R² = 0.9992), confirmed independently by per-mapping `smaps`. See
> [Arena waste, attributed](#arena-waste-attributed--and-confirmed-resident).
>
> **This section previously concluded the opposite** — that arena waste, though
> real and attributable, did not cost RSS — and that conclusion is **retracted**.
>
> That reverses this section's premise rather than adjusting it. With arena waste
> included, the accounting no longer under-explains by 4.02 MiB — on a
> committed basis it *over*-explains, and the two sides are not comparable until
> residency factors are applied to each term. The corrected accounting is the
> two-term model in the header; the candidate table above remains valid only as a
> list of small known gaps, not as an explanation of a 4.02 MiB residual that is
> no longer the right quantity to explain.

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

### Anonymous memory ramps during startup, then plateaus

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

All three are bounded and known. The first two are defects in the *measurement*,
not in the footprint — they are the kind of gap this exercise exists to close:

- **Flush-phase sampling bias on the rotating call-trace arena**, loosely bounded
  by the 3.37 → 6.59 MiB live-to-peak spread (12 runs, steady-state chunks only)
  — loosely, because that peak is an all-time latch set during the startup ramp,
  not the crest of the steady-state cycle; see the footnote under
  [Residual](#c-residual--402-mib-68-).

  *This supersedes an earlier claim in this document that the bias came from
  `LinearAllocator::clear()` failing to unmap already-touched pages. That claim
  was wrong and is retracted: `clear()` is reachable only from
  `~LinearAllocator()` and is never called in a running profiler. The production
  reset is `detachChunks()` + `freeChunks()`, and `freeChunks()` calls
  `OS::safeFree` (`munmap`) on every chunk while decrementing exactly the byte
  count `alloc()` recorded for it. Pages are genuinely returned to the kernel and
  cgroup `anon` drops with them, so nothing stays resident behind the counter.
  The real per-chunk under-counts in that path — the 64-byte chunk header, page
  rounding of the bump pointer, and the reserve chunk's touched first page — total
  well under 0.1 MiB.*

  The bias that *does* exist is in when the gauges are read, not in what they
  count. `NativeMem`'s `live` and `avg` are both read once per JFR chunk from
  `updateNativeMemStats()`, which runs **after** the constant pool has been
  serialized — and serializing the stack-trace pool is what rotates
  `CallTraceStorage` and unmaps its standby chunks. Every reading is therefore
  taken at the trough of the rotation cycle, which is why `calltrace` reports
  3.37 MiB live against a 6.59 MiB peak. The anon figure it is differenced
  against is a plateau **median** — a time average across the whole cycle — so
  charging `calltrace` at its flush-instant value under-credits it by up to the
  live-to-peak spread.

  `avg` is not the fix: `NativeMem::sample()` is driven from the same per-chunk
  call, so its 64-tick window averages readings that all sit at the same phase.
  Measured across the 12 profiling runs, steady-state chunks only, total `avg` is
  24.41 MiB against total `live` 24.53 MiB — re-charging every category at `avg`
  moves the residual by −0.12 MiB, the wrong direction and two orders too small.
  Pinning the true time average down needs the `native_mem_post_flush_*`
  counters, which postdate the build used here.
- **`linear_allocator_bytes` and `linear_allocator_chunks` read 0 in production**,
  in every chunk of every run, even though `CallTraceStorage` holds three
  `CallTraceHashTable`s that each keep a live 8 MiB chunk. Verified not to be a
  build or emitter problem: the counter name strings are in the shipped `.so`,
  `allocateChunk` carries the increments in the disassembly (`lock add $chunk_size,
  0xf00(%rcx)` / `lock incq 0xf80(%rcx)`), and the emitter indexes the same slots
  the writers do. The cause is ordering in `Profiler::start()`: it calls
  `_call_trace_storage.clear()` — which decrements for every freed chunk and
  re-increments for the fresh one each allocator then holds — and *only then*
  calls `Counters::reset()`, zeroing the table while those chunks are still
  mapped. The gauge is de-based by exactly the live population, so it reports the
  delta from that baseline rather than the absolute count, and it reads exactly 0
  whenever the population returns to its post-reset size — which is the state at
  every flush, for the same reason `calltrace` reads its trough there. Cumulative
  event counters are unharmed by `Counters::reset()`; live gauges like these two
  are, and can go negative if the population ever drops below the baseline.
  Consequence for reconciliation: the arena's *virtual* footprint (≥ 24 MiB) is
  invisible in production JFR. Its *resident* footprint is not affected — that is
  carried by `NM_CALLTRACE`, which has its own state and is not touched by
  `Counters::reset()`.
- **Allocator-overhead coverage is partial** (~0.2–0.4 MiB unmeasured).
  `jfr_buffers`, `liveness`, `line_tables`, `thread_local`, `thread_filter` and
  `wallclock` still record through plain `record()` and report zero overhead. The
  measured total is therefore a lower bound. The counters emit bytes but not
  allocation counts, so the correct per-category factor cannot be derived from the
  current data.

## Why JFR is initialised

`Tracing` (`mtTracing`) is the JFR category — confirmed by construction, not
assumed: a plain JVM has no `Tracing` category at all, while
`-XX:StartFlightRecording` produces 15,572 KB against our profiling arm's
15,570 KB.

**No recording is running, though.** Interrogated on a live container at the same
instant: `jcmd JFR.check` reports *"No available recordings"*, `-Xlog:jfr*=debug`
produces an empty log, yet `Tracing` holds 15,570 KB (`malloc=15506KB #221`) and
241 `jdk.jfr` classes are loaded, including `PlatformRecorder` and
`MetadataLoader`. So the JFR *subsystem* is initialised — metadata parsed,
recorder machinery constructed — without any recording being started.

The trigger is in `ProfilingAgent`, which runs before the JFR-disable flag is
ever consulted:

```java
JFRAccess.setup(inst);
Timestamper.override(JFRAccess.instance());
ControllerContext context = new ControllerContext();
final Controller controller = CompositeController.build(configProvider, context);
```

`dd.profiling.debug.jfr.disabled` gates `OpenJdkController` *inside*
`CompositeController.build()`, which runs afterwards — so it cannot prevent this.
Class-load order confirms it: the first `jdk.jfr` class loads immediately after
`JFRAccess$Factory` → `Timestamper$1` → `SimpleJFRAccess` → `JPMSJFRAccess` →
`InvocationTargetException` → `jdk.jfr.Event`.

**Priority: low.** The flag is a debugging aid, not a production setting.
Production enables JFR anyway, so this memory is paid regardless and there is
nothing here to "fix". The finding matters for two other reasons:

1. **It corrects how this benchmark's headline should be read.** Setting
   `jfr.disabled=true` was intended to measure ddprof standalone; it does not,
   and ~15.2 MiB of JVM JFR machinery sits inside the measured total.
2. **It relocates the largest single line item.** A quarter of the overhead is
   JFR initialised for a timestamp source, and it is not the native profiler's
   to reduce.

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
allocations. The profiler's counters cannot attribute it — they ride the
profiler's own JFR, so the tracing-only arm emits none and no paired delta
exists.

### Arena waste, attributed — and confirmed resident

`memsweep/mallinfo_sampler.c` closes that: an LD_PRELOAD shim that samples
`mallinfo2()` from **either** arm, since it does not care whether the profiler is
attached. Unlike `malloc_info_probe.c` it never calls `malloc_trim` (that would
alter the state being measured) and its sampling loop is allocation-free, so it
does not perturb the arena it observes.

Paired deltas over 12 pairs, plateau-sampled (65 samples/run):

| glibc term | profiling | baseline | paired Δ | SE |
| --- | --- | --- | --- | --- |
| `arena` (brk address space) | 268.36 | 210.63 | **+57.73** | 8.43 |
| — of which in use (`uordblks`) | 82.32 | 47.56 | **+34.76** | 0.51 |
| — of which free-held (`fordblks`) | 186.04 | 163.07 | **+22.97** | 8.47 |
| trimmable (`keepcost`) | 0.13 | 0.13 | +0.00 | 0.00 |
| mmap-served (`hblkhd`) | 49.96 | 27.21 | **+22.74** | 0.51 |

So **+22.97 ± 8.47 MiB of free-but-held arena space is attributable to the
profiler** (2.71 σ) — the first time this term has been measured rather than
carried over by analogy.

### Free-but-held arena memory is resident — and is one of the two largest terms

**+22.9 to +37.1 MiB of real RSS cost.** Residency measures **1.0119 ± 0.0066**
over 20 pairs, R² = 0.9992, confirmed independently by per-mapping `smaps`.

> **Retraction.** This section previously carried the heading "But it does not
> explain the residual, because it is not resident" and concluded that arena
> waste cost no RSS. That is **wrong and withdrawn.** The argument is preserved
> below, marked as retracted, because the way it failed is instructive — but
> nothing in it should be quoted as a current finding.

*The retracted argument.* `uordblks` excludes mmap-served chunks (verified:
`uordblks + fordblks = arena` exactly, while an 8 MB allocation lands wholly in
`hblkhd`), so the profiler's total malloc *address space* delta is
57.73 + 22.74 = **80.47 MiB** against an anon delta of only **58.83 MiB**. The
21.6 MiB excess matches the 22.97 MiB free-held delta almost exactly — therefore,
it concluded, free-held pages are unbacked, and malloc's *in-use* delta
(34.76 + 22.74 = 57.50 MiB) sitting within 1.3 MiB of the anon delta is where the
resident cost actually lives.

*Why it fails.* Both models fit the mean, so the mean cannot choose between them:
Δ`arena` is 57.73 and Δ(`uordblks`+`hblkhd`) is 57.50, a coincidence of this
dataset. The variance discriminates, and it is not close:

| model for Δanon | mean | SD | corr with Δanon |
| --- | --- | --- | --- |
| `arena` (in-use **+ free-held**) | +57.73 | 29.21 | **0.998** |
| `uordblks` + `hblkhd` (in use only) | +57.61 | **0.16** | **−0.005** |
| Δanon, measured | +58.86 | 29.56 | — |

The in-use-only model predicts anon should be near-constant across pairs. It
varies by 29.56 MiB, and only the model including free-held tracks it.

*Two independent confirmations.* Regressing Δanon on Δ`fordblks` over 20 pairs
gives a slope of **1.0119 ± 0.0066** — the residency fraction of free-held
memory — which is 1.8 σ from 1.0 and **153 σ from 0**, at R² = 0.9992. And
per-mapping `smaps` measures glibc arena regions holding **214.9 MiB Rss against
78.7 MiB of `uordblks`**, so ≥136 MiB of resident arena memory is free-held. The
two instruments share no code and no data source.

*The split was inverted.* The 21.6 MiB of address space that genuinely is not
backed is **`hblkhd`**, not free-held arena: 80.47 − 58.86 = 21.61 against
Δ`hblkhd` = 22.74, within 1.1 MiB, and the fitted residency factor for `hblkhd`
is ~0 against ~0.96 for the arena.

*Note on `malloc_trim`.* It is **not** a valid test of this. `keepcost` is
0.13 MiB in every run, so essentially nothing is trimmable regardless of whether
those pages are resident — a trim experiment would show no drop under either
model, and the free-held space is mid-arena fragmentation rather than
trim-threshold retention.

**Consequence for the reconciliation:** arena waste must be *added* as an
explanatory term, not excluded — the opposite of what this section previously
concluded. Because it is also the entire source of the run-to-run variance, it is
the term that makes a single-number total irreproducible.

## Where the variance comes from

The run-to-run variance is **not** measurement noise, and not host state or JIT
decisions in general as this document previously supposed. It is one term.

Within a single run's plateau, anon is extremely stable: the median over the
first half of the plateau and over the second half agree to **0.13 MiB**
(split-half, 24 runs), with an IQR of 0.55–0.82 MiB. Yet paired deltas scatter
with **SD 29.56 MiB**. A ratio of ~230× has no instrument-noise explanation —
each run pins its own anon level to about a tenth of a megabyte, and different
runs settle tens of megabytes apart.

Δ`fordblks` accounts for that scatter completely: R² = 0.9992 with a residual SD
of 0.77 MiB across 20 pairs. Nothing else needs to be invoked.

Three consequences:

- **More repetitions are a poor lever.** At SD 29.56, reaching SE = 1 MiB needs
  **873 pairs**, roughly 4–5 days of machine time, and SE only falls as √n.
- **A within-process design would not help.** The arena term would still be
  drawn per process, so it would not cancel.
- **Report the two terms separately instead.** The stable term is already known
  to ±0.26 MiB with the pairs in hand; it was only ever obscured by being summed
  with the arena term.

Two candidate mechanisms for the arena term itself were considered:

- **Secondary-arena count.** glibc creates arenas as 64 MiB-aligned mmap'd heaps,
  so a per-run "how many arenas" lottery would produce quantised deltas.
  **Ruled out:** the 24 absolute arena values (174–295 MiB) have consecutive gaps
  of 1–9 MiB with no 64 MiB steps.
- **C2 compiler-arena churn.** HotSpot's `Arena` chunks go through `os::malloc`,
  so C2's bursty allocate/free is a plausible driver of free-held growth.
  Untested. A single `-XX:TieredStopAtLevel=1` pair would be a cheap mechanism
  check, but it is *not* a measurement configuration: C1-only changes the
  compiled-method population and therefore the profiler's own symbol and
  call-trace load. The same caveat applies to a GC change and to
  `mallopt(M_ARENA_MAX)` — all of them change the thing being measured.

## Residency factors

NMT reports **committed** address space; the profiler's counters report bytes
**requested**; cgroup anon counts pages **touched**. These are three different
quantities and the reconciliation was comparing them directly. Each accounting
term needs a residency factor first.

The decomposition must be non-overlapping, and the trap is that NMT's
per-category `committed` mixes mmap'd regions with malloc'd bytes — and those
malloc'd bytes are served by glibc, so they are *already inside* mallinfo's
`arena`/`hblkhd`. Summing NMT committed alongside mallinfo terms double-counts
them. NMT reports the split per category, so JVM terms use **mmap-committed
only**. `Shared class space` is excluded as file-backed (CDS archive).

Derived from 32 run-snapshots (8 pairs × 2 arms × 2 plateau snapshots):

| term | factor | how |
| --- | --- | --- |
| Java heap | **1.000** ± 0.000 | measured (`AlwaysPreTouch`) |
| JIT code cache | **0.992** ± 0.000 | measured; matches NMT `Code` exactly |
| thread stacks | **0.875** ± 0.015 | measured, against NMT's `stack:` line |
| glibc arena | **0.957** ± 0.016 | fitted |
| `hblkhd` (mmap-served) | **≈ 0** | fitted, bounded |
| metaspace / class / GC | — | **not identifiable**, see below |

**Two identifiability traps, both real and both worth avoiding on a re-run:**

1. *Metaspace, Class and GC cannot be fitted as free terms.* NMT `GC` mmap is
   byte-identical across arms (Δ = +0.00) and metaspace barely moves, so their
   columns are effectively constant. A first fit returned metaspace **−7.55** and
   GC **+7.25** — both physically impossible — cancelling to something plausible.
   They belong in an intercept (109.9 ± 2.1 MiB, the constant JVM mmap baseline).
2. *`arena` and `hblkhd` are collinear at r = +0.925*, so ordinary least squares
   pushed `hblkhd` to −0.170. Only the **combination
   `f_arena + 0.274 × f_hblkhd ≈ 0.911`** is determined; the two factors are not
   separately identifiable. Profiling `f_hblkhd` over [0, 1] and refitting is
   monotone — residual SD 1.49 at 0 rising to 5.36 at 1 — so the data prefers
   ≈ 0. **Do not quote 0.957 as a standalone measured constant.**

*Why the average arena factor (0.91–0.96) sits below the marginal free-held slope
(1.0119 ± 0.0066):* mallinfo's `arena` counts each arena's grown extent including
an untouched top chunk — `smaps` shows arena Rss/Size ≈ 0.79. That is a roughly
constant overhead absorbed by the intercept, while *marginal* growth is fully
touched. Both numbers are correct.

*Validation.* Leave-one-pair-out prediction of Δanon is out of sample: mean error
**−0.29 MiB**, SD 3.26, max |error| 6.92. (An in-sample agreement of +0.11 MiB
also appears in the tool output; it is meaningless on its own — same data fitted
and predicted.)

**Two routes to the free-held magnitude, and they disagree — use the mallinfo
one.** `analyse_smaps_paired.py` also reports a "resident free-held arena" paired
delta of **+14.10 ± 7.91 MiB**, computed as arena Rss minus `uordblks`. That
**undercounts**: the strict 64 MiB-shape arena detector misses arenas whose
mappings the kernel split or merged, and they land in the generic
`anon 1MiB-512MiB` bucket instead. The leak is quantified — Δ(secondary arena
Rss) +49.41 plus Δ(`anon 1MiB-512MiB` Rss) +23.32 = +72.73 reproduces
Δ`arena` = +72.21, while the arena class alone does not. The authoritative
magnitude is the mallinfo term (+22.86 / +36.90); the *residency* comes from the
Δ`fordblks` slope, which needs no classification at all.

Tooling: `memsweep/run_smaps_paired.sh`, `analyse_smaps.py`,
`analyse_smaps_paired.py`, `derive_residency.py`. Validation worth noting: smaps
`Anonymous` totals equal cgroup `anon` to **0.0 MiB** in both arms.

## Which categories are mmap-served

Because mmap-served chunks measure ~0 resident, a category whose allocations
exceed glibc's mmap threshold would over-state its RSS cost. **A hypothesis that
`native_symbols` and `dictionary` do so was tested and refuted.**

The threshold cannot be assumed: glibc's `M_MMAP_THRESHOLD` is **dynamic**,
adapting upward from its 128 KiB default toward 32 MiB as mmap'd blocks are
freed. It was located empirically instead — ranking call sites by allocation size
until `malloc_live_count_mmapped` (14–15 live) is accounted for — and comes out at
**256 KiB**.

| category | total MiB | mmap-served | % |
| --- | --- | --- | --- |
| `native_symbols` | 9.19 / 9.22 / 9.90 | **0.00** | **0 %** |
| `jfr_buffers` | 1.16 | 1.16 | 100 % |

`native_symbols` is 0 % mmap-served in all three dumps. Its largest site,
`CodeCache::findSymbolByPrefix` at 4.52 MiB over 22 allocations = **210 KiB
mean**, sits just *below* the 256 KiB threshold, so it is arena-served and at
0.957 essentially all resident. `dictionary` likewise: `DictTable` is 128 rows ×
32 B ≈ 4 KiB, far below threshold, and a 4 KiB `calloc` is memset so its pages
are touched.

`CodeCache` does count `_memory_usage += _capacity * sizeof(CodeBlob)` —
*capacity*, not count — while `new CodeBlob[n]` leaves POD members uninitialised,
so a doubling array is counted fuller than it is touched. Real, but immaterial
here: the array is arena-served, and arena pages measure ~96 % resident whether
or not the caller wrote to them.

Of ~22 MiB of profiler malloc, only **~7.7 MiB is mmap-served** — `jfr_buffers`
1.16 MiB (one allocation, matching its counter exactly), ~4.5 MiB across three
512 KiB × 3 sites, and ~2.0 MiB in `otel_process_ctx.cpp`. So Δ`hblkhd` = +22.56
is mostly **not** the profiler's instrumented allocation; where the rest comes
from is open.

**Two caveats on this analysis.** The ledger dumps are the **memsweep** workload
(N = 150,000 classes), not dd-trace-doe, so the structural conclusion should
transfer but the split may not. And `addr2line` returns a function but no file
for most sites in this release build, so attribution is nearest-symbol only —
three distinct 512 KiB sites all resolve to `Profiler::stop()`, which is
certainly wrong. **Ranking by size is reliable; naming the allocator is not.**

Tooling: `memsweep/alloc_size_histogram.py`.

## Candidates that would explain a larger gap

These were assembled when the gap appeared larger, and the arithmetic that
dismissed them is superseded: it rested on free-held arena space being
non-resident, which is now measured to be false. The table below is corrected.

| Est. | Candidate |
| --- | --- |
| **+22.9 to +37.1** | **Free-but-held arena pages — CONFIRMED, and the largest term here.** ~~Ruled out as non-resident.~~ That was wrong: residency measures **1.0119 ± 0.0066** (20 pairs) and per-mapping `smaps` agrees. It is a real RSS cost and it varies between batches, which is why the total is irreproducible. See [Arena waste, attributed](#arena-waste-attributed--and-confirmed-resident). |
| ≈ 0 (inferred) | **Mmap-served malloc chunks (`hblkhd`), +22.6 MiB of address space.** The likeliest home for the address space that genuinely is not backed. Note this is *inferred under collinearity*, not measured independently: `hblkhd` and `arena` correlate at r = 0.925, so only `f_arena + 0.274 × f_hblkhd ≈ 0.911` is determined. The profile prefers ≈ 0 monotonically and the mean arithmetic agrees (80.47 − 58.86 = 21.61 against Δ`hblkhd` 22.74), but the two factors cannot be separated. Only ~7.7 MiB of it is profiler-instrumented allocation, so most is induced JVM/tracer allocation — currently unattributed. |
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

1. ~~Attribute arena waste to the profiler.~~ **Done, and it changed the
   conclusion.** Attributed at +22.86 ± 8.47 (12 pairs) and +36.90 ± 7.72
   (8 pairs) via the LD_PRELOAD sampler, and — contrary to the first reading —
   measured to be **fully resident**. It is now the largest single term and the
   sole source of the run-to-run variance. See
   [Arena waste, attributed](#arena-waste-attributed--and-confirmed-resident) and
   [Where the variance comes from](#where-the-variance-comes-from).
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
5. ~~Attack between-run variance — now the dominant uncertainty.~~ **Diagnosed.**
   It is not "run-level factors (host state, JIT decisions, container placement)"
   as guessed here — it is entirely glibc arena growth (R² = 0.9992). The fix is
   not to reduce it but to **stop summing it into the headline**: report the
   stable term (35.98 ± 0.26) and the arena term separately. Brute force is a bad
   trade at 873 pairs for SE = 1 MiB. See
   [Where the variance comes from](#where-the-variance-comes-from).

   *Remaining, and the one open question of substance:* Δ`hblkhd` is +22.6 MiB of
   allocated-but-untouched address space, of which only ~7.7 MiB is
   profiler-instrumented. The rest is induced JVM or tracer allocation and is
   currently unattributed. A cross-condition run of the alloc ledger on **this**
   workload would attribute it to call sites; the existing audit deliberately
   compares within one condition only.
6. **Confirm `-XX:+AlwaysPreTouch` with a 2×2 interleaved design** (pretouch and
   no-pretouch alternating within one window). It is already the recommended
   default on the strength of estimator-independence; what remains is to check
   whether the apparent precision cost is real or a cross-window artifact.

Full design, including three rejected alternatives and why, is in
`overhead-program-plan.md` § "Concrete next steps", item 6.
