# dd-trace-doe memory reconciliation, 27 Aug 2026

**Headline: the profiler's memory overhead on this workload is 3.9–4.3 % of the
application's anonymous memory (≈ 64–71 MiB against a ≈ 1630 MiB baseline). The
unexplained residual is +4.6 to +11.1 MiB — statistically indistinguishable from
zero, but also indistinguishable from ~15 MiB, because the memory instrument's
own spread (± 8.5 MiB) now dominates.**

> **Terminology.** Earlier drafts of this report said "RSS" throughout. That was
> imprecise and is corrected here. dd-trace-doe's `memory=` output is
> `max(cgroup anon)` — **anonymous memory only** (no page cache, no file-backed
> pages), and a **running maximum** over ~900 samples across the load and stop
> phases (`internal/schema/output.go`). Anon is arguably the *better* quantity to
> reconcile against malloc/mmap counters, since it excludes file-cache noise. But
> "maximum" is material: see "The instrument is a maximum" below. Where this
> document says "memory delta" it means the delta in that anon figure.

> **Superseded figures.** An earlier draft of this report put the residual at
> 15–28 MiB. That came from pairing conditions measured in *separate* windows,
> which the interleaved re-run below shows was biased. The interleaved,
> counterbalanced measurement is authoritative; the 15–28 range should not be
> quoted. See "Interleaved re-run" for what changed and why.

This *reverses* the reconciliation reported earlier in this investigation. A
12-pair run had shown a residual of +2.1 ± 4.5 MiB (3 % of the RSS delta,
indistinguishable from zero) and was treated as closed. That closure was an
artifact of a correction factor borrowed from a different workload. With the
underlying counter bug fixed, the same reconciliation is 20–33 %
under-explained. **Nothing about the profiler's actual memory use changed —
only our ability to see it.**

Harness, workload and instruments are unchanged from
`dd-trace-doe-reproduction-2026-08-05.md`; read that first for methodology.
Mechanism detail for the counter fix is in `memory-sweep-results-linux.md`
(§ "`NM_CALLTRACE`: counting residency at source instead of correcting for it").

---

## Conditions

| | |
| --- | --- |
| Workload | `archetype=enterprise` (Spring Boot), `duration=90`, 9000 requests |
| Reps | 12 per condition (tracing-only, tracing+profiling) |
| Heap | `-Xms2g -Xmx2g` (set by the harness entrypoint; heap fully committed) |
| Library | local build, verified by checksum end-to-end (below) |

`-XX:+AlwaysPreTouch` was tried and rejected here — it roughly doubled the
spread (sd 9.4 → 18.2 MiB tracing-only, 12.0 → 25.9 MiB profiling) and moved the
mean delta down ~22 MiB in a way neither instrument tracked. **That rejection is
now believed to be wrong**: it was measured with the maximum estimator, which is
precisely what pre-touching inflates. See "This means `AlwaysPreTouch` was
rejected on the wrong evidence".

### Build provenance

An earlier attempt in this investigation silently resolved the *upstream*
ddprof release instead of the local build, producing misleading numbers. A
checksum gate now runs at both stages: the `libjavaProfiler.so` inside the
published Maven artifact **and** inside the shaded `dd-java-agent` jar were both
confirmed byte-identical to the locally built library
(md5 `6103cb7a9cc2f8e015f25629d75a2a72`). Any future re-run should keep this gate.

---

## Reconciliation

Two independent instruments explain part of the RSS delta: the JVM's **Native
Memory Tracking** (JVM-internal growth caused by the profiler being attached)
and the profiler's **own per-category counters** (allocations NMT cannot see).
NMT's *absolute* committed total is never RSS-comparable — it counts committed
address space, and with a 2 GiB fully-committed heap it exceeds RSS by ~660 MiB
— so only the paired *delta* is used.

Malloc-backed counter categories carry a ×1.17 chunk-overhead correction.
Call-trace is mmap-backed and is now measured directly, so **no ×0.829
residency factor is applied**.

| RSS pairing | Call-trace basis | RSS delta | Explained | Residual | % of delta |
| --- | --- | --- | --- | --- | --- |
| same-window | live 3.53 | 74.58 ± 4.39 | 56.54 | **+18.04 ± 4.50** | 24 % |
| same-window | peak 6.42 | 74.58 ± 4.39 | 59.43 | **+15.15 ± 4.50** | 20 % |
| cross-time | live 3.53 | 84.25 ± 7.84 | 56.54 | **+27.71 ± 7.91** | 33 % |
| cross-time | peak 6.42 | 84.25 ± 7.84 | 59.43 | **+24.82 ± 7.91** | 29 % |
| *prior result* | *24.23 × 0.829* | *74.58 ± 4.39* | *72.44* | *+2.14 ± 4.45* | *3 %* |

A **positive** residual means RSS exceeds what we can account for. Every
combination leaves a gap several times its own standard error — the gap is real,
its magnitude is not yet pinned.

Component terms (n = 12, ± 1 SE):

| Term | Mean (MiB) | SE | Confidence |
| --- | --- | --- | --- |
| Profiler counters, total (raw) | 25.06 | 0.08 | solid |
| Profiler counters, corrected | 28.72 – 31.61 | 0.10 | solid |
| NMT committed delta | 27.82 | 1.02 | solid |
| RSS delta | 74.6 – 84.3 | 4.4 – 7.8 | **noisy** |
| *(reference)* chunk overhead behind the ×1.17 | +6.44 | 0.10 | solid |
| *(reference)* free-but-held arena pages | +7.6 | 3.0 | **unattributable** |

The last two are measured in the synthetic sweep, not here; they are listed for
scale. Note the two-order-of-magnitude spread in reproducibility between them —
chunk overhead is the most reproducible figure in the whole investigation, while
arena slack changes sign between runs.

The profiler's own counters are the most reproducible instrument here — SE
below 0.1 MiB across twelve runs. **Essentially all uncertainty in this
reconciliation is RSS measurement noise, not counter error.**

### Caveat on the RSS delta — read before quoting it

RSS standard deviation more than doubled between the morning and afternoon
batches (11.9 → 25.5 MiB) with no code change capable of affecting it, and this
run's profiling condition was paired against a baseline captured several hours
earlier. Machine-level drift is the likely cause. **Quote the RSS delta as a
range (74.6–84.3 MiB), not a point estimate.** Re-running both conditions
interleaved in a single window would settle it, and is the cheapest way to
narrow the residual.

---

## Interleaved re-run — the authoritative measurement

The block design above measured the two conditions in separate windows, leaving
the RSS delta ambiguous between 74.6 and 84.3 MiB. The re-run alternates the
conditions **within one window**, so drift cannot land preferentially on one arm,
and **counterbalances the within-pair order** (pair 1: profiling first; pair 2:
tracing-only first; …) so any ordering effect cancels instead of biasing.

Two further changes: `loops_num`/`allocs_num` are pinned to the values
calibration produced (`loops_cpu`/`allocs_cpu` = 0), which removes 24 calibration
containers **and** a confound — previously each arm calibrated independently, so
the two could run slightly different workloads. All other archetype parameters
are unchanged, and NMT is still captured 30 s after container start.

Reconciliation is computed as **per-pair differences**, not as a difference of
independently measured means.

| | n = 12 (all) | n = 10 (JIT spikes excluded) |
| --- | --- | --- |
| RSS paired delta | 70.62 ± 8.39 | 63.84 ± 8.45 |
| NMT paired delta | 30.95 ± 2.30 | 27.55 ± 0.19 |
| — of which `Arena Chunk` | 4.31 ± 2.23 | 1.10 ± 0.64 |
| NativeMem raw | 24.926 ± 0.006 | 24.929 ± 0.007 |
| NativeMem corrected (live basis) | 28.57 | 28.57 |
| NativeMem corrected (peak basis) | 31.72 | 31.73 |
| **residual, live basis** | **+11.10 ± 8.70** (15.7 %) | **+7.72 ± 8.45** (12.1 %) |
| **residual, peak basis** | **+7.95 ± 8.70** (11.3 %) | **+4.56 ± 8.45** (7.1 %) |
| overhead vs tracing-only RSS | 4.34 % | 3.92 % |

Every variant is within ~1.3 σ of zero (0.54–1.28 σ). **The residual is no longer
statistically demonstrable** — but neither is its absence, and that is the honest
statement.

### Two effects the interleaving exposed

**A within-pair ordering bias of ≈ 7.1 MiB.** Pairs where profiling ran first
gave a mean delta of 77.73 MiB; pairs where tracing-only ran first gave 63.50 —
a 14.23 MiB swing, i.e. the *first* run in a pair carries ≈ 7.1 MiB more RSS
regardless of which arm it is. Counterbalancing cancelled it exactly (the
12-pair mean, 70.62, is the midpoint of the two orders to 0.01 MiB). Every
earlier design absorbed this bias silently.

**Transient JIT compiler arenas, ≈ 20 MiB, in 2 of 12 pairs.** Pairs 4 and 7
showed NMT committed ~20 MiB above an otherwise very tight cluster
(2325.8–2327.4 MiB). The cause is `Arena Chunk`: 26,139 KB and 25,497 KB against
~5,115 KB normally — the snapshot landed mid-compilation. These are the same two
pairs with the largest RSS deltas (96.6 and 112.5 MiB), so **the two instruments
moved together**, which cross-validates them: those RSS outliers are real
transient memory, not measurement error. The memory is JIT activity unrelated to
the profiler, which happened to hit the profiling arm twice.

Excluding those two pairs (one odd, one even, so the counterbalance is preserved)
collapses NMT's paired SE from 2.30 to **0.19 MiB** — the `Arena Chunk` transient
was essentially the *entire* source of NMT noise. Both variants are reported
above rather than choosing one, because the exclusion is justified by an
independently identified mechanism, not by the points being inconvenient.

### The instrument is a maximum — and that explains most of the noise

`memory=` is `max(cgroup anon)` over ~900 samples per run, not a point sample or
an average. That single fact accounts for much of what this report has been
calling "measurement noise":

- **A maximum is an extreme-value statistic** — upward-biased, high-variance, and
  it permanently latches the largest transient in the run. One JIT compiler
  arena burst or GC spike sets the run's number for good.
- **It explains the 26–112 MiB per-pair spread**, and why the two JIT-spike pairs
  read so high: those transients *are* the maximum.
- **It explains why `AlwaysPreTouch` made variance worse** rather than better:
  pre-touching adds a page-fault storm and raises peak anon.
- **It is temporally incoherent with the other instruments.** The anon figure is
  a max over 0–90 s; the NMT snapshot is a point at t = 30 s; NativeMem is read
  at JFR flush. Three different moments, one of them a peak — which is precisely
  why JIT arena memory cannot simply be subtracted from both sides.

Measured on one pair by sampling cgroup anon directly at 2 Hz, the estimator
choice moves the delta by 25 MiB:

| estimator | profiling | tracing-only | delta |
| --- | --- | --- | --- |
| max (doe's method) | 1716.02 | 1610.99 | **105.03** |
| whole-run median | 1657.21 | 1577.64 | 79.57 |
| steady-state mean (t ≥ 30 s) | 1682.20 | 1581.15 | 101.05 |
| synchronous at NMT snapshot | 1647.63 | 1559.53 | 88.10 |

The whole-run median is dragged down by the startup ramp; anon is still climbing
at t = 30 s, so the NMT snapshot used by every measurement above is **not** in
steady state. Within the steady window the per-sample sd is 25.4 MiB (profiling)
and 10.5 MiB (tracing-only), so the profiling arm genuinely fluctuates more —
GC, JIT, and call-trace arena rotation.

`memsweep/run_doe_interleaved.sh` now samples cgroup anon directly at 2 Hz from
the **host** cgroup path (`docker exec … cat` was rejected: it spawns a process
inside the target's own cgroup and inflates the number being measured — observed
1519616 vs 1257472 bytes), records the value at the exact instant of each NMT
snapshot, and takes **two** NMT snapshots (t = 30 s for comparability with the
batches above, t = 70 s in steady state). That yields a max comparable to doe's,
a low-variance steady-state mean, and a temporally coherent point value against
which `Arena Chunk` can validly be differenced.

### What now limits the answer

Instrument spread, not accounting. The paired delta's sd is 26.7 MiB even with
the JIT spikes removed; per-pair deltas ranged 26–112 MiB. Since SE = sd/√n:

| target SE | pairs needed |
| --- | --- |
| 8.45 MiB (current) | 10 |
| 5 MiB | 29 |
| 3 MiB | 79 |
| 2 MiB | 178 |

Distinguishing a 5 MiB residual from zero needs ~79 pairs (≈ 11 h of runs) *if
the instrument stays as it is*.

### The estimator prediction was wrong — and the real problem is the heap

The prediction above was that replacing the maximum with a steady-state mean
would shrink the paired SE without extra reps. **It did not.** Measured over a
fresh set of 12 interleaved pairs with cgroup anon sampled directly at 2 Hz:

| estimator | paired delta | sd | SE |
| --- | --- | --- | --- |
| doe `max(anon)` | 72.27 | 17.01 | 4.911 |
| our `max(anon)` | 71.96 | 17.18 | 4.959 |
| whole-run median | 51.36 | 19.13 | 5.523 |
| steady mean (t ≥ 30 s) | 57.09 | 17.87 | 5.159 |
| steady median | 63.99 | 14.84 | 4.283 |
| synchronous at t = 30 s | 51.61 | 13.00 | 3.754 |
| synchronous at t = 70 s | 65.48 | 20.23 | 5.841 |

The maximum was **not** the dominant noise source: the steady-state mean is
marginally *worse* (sd 17.87 vs 17.01). The between-run spread is largely
genuine, not an extreme-value artifact.

Worse, **estimator choice moves the answer by 21 MiB** (51.4 → 72.3) — roughly a
third of the quantity being measured, and larger than the residual this report
set out to explain.

**The reason is that anon is mostly Java heap.** The heap is 2048 MiB committed
(`-Xms2g -Xmx2g`), and the tracing-only steady-state anon is ≈ 1580 MiB — so anon
is dominated by *touched heap pages*, and it moves with GC activity. Measured
within-run steady-state fluctuation is **± 72 MiB** on the profiling arm (± 37 on
tracing-only), against a profiler native footprint of ≈ 25 MiB. Signal-to-noise
is about **0.35**: the instrument is measuring the heap's GC dynamics far more
than it is measuring the profiler.

That is why every estimator disagrees. They are each sampling a different part
of a large, GC-driven oscillation.

### This means `AlwaysPreTouch` was rejected on the wrong evidence

`-XX:+AlwaysPreTouch` was dismissed earlier because it doubled the spread — but
that was measured with the **maximum** estimator, which is exactly what
pre-touching inflates (it adds a startup page-fault storm that sets a high max).

With the heap diagnosis above, pre-touching should *help* decisively: it pins
touched heap pages at the full 2048 MiB from startup, so GC can no longer move
them, removing the dominant noise term. `AlwaysPreTouch` **plus** a steady-state
estimator is plausibly the combination that makes this measurable — the pairing
never tried, because the flag was judged against the one estimator guaranteed to
punish it.

**Recommended next experiment**, before spending 79 pairs on the current setup:
12 interleaved pairs with `-XX:+AlwaysPreTouch` and a steady-state estimator. If
the heap term is pinned, the paired sd should fall from ~17 MiB toward the
non-heap variation alone, and a 5–10 MiB residual becomes resolvable at n = 12
rather than n = 79.

### Coherent reconciliation, now that anon and NMT are synchronous

With anon sampled at the exact instant of each NMT snapshot, `Arena Chunk` can
be differenced validly from both sides. Doing so barely moves anything this run
(`Arena Chunk` delta +0.87 ± 3.73 MiB at t = 70 s, +0.16 ± 0.20 at t = 30 s) —
the JIT bursts that hit two pairs in the previous run did not recur. The
machinery is validated but was not needed here.

| anon basis | NMT | residual (live) | residual (peak) |
| --- | --- | --- | --- |
| steady mean | t = 70 s | **+1.47 ± 5.95** (0.25 σ) | −1.66 ± 5.95 (0.28 σ) |
| synchronous | t = 70 s | +9.86 ± 6.55 (1.51 σ) | +6.73 ± 6.55 (1.03 σ) |
| synchronous | t = 30 s | −4.01 ± 3.77 (1.06 σ) | −7.14 ± 3.77 (1.89 σ) |

Every variant is within 2 σ of zero, but they span −7.1 to +9.9 MiB. **The
residual cannot be pinned more tightly than the instrument allows**, and the
instrument is currently limited by heap/GC noise, not by accounting. The
within-pair ordering bias also persists at +5.95 MiB (was +7.11), still
cancelled by counterbalancing.

## Where the profiler's own memory goes

Live bytes by category, mean of 12 reps, fixed counter:

| Category | Mean (MiB) | SE | Share |
| --- | --- | --- | --- |
| `native_symbols` | 11.293 | 0.000 | 45.1 % |
| `dictionary` | 6.806 | 0.002 | 27.2 % |
| `calltrace` | 3.531 | 0.005 | 14.1 % |
| `jfr_buffers` | 1.158 | 0.000 | 4.6 % |
| `liveness` | 0.875 | 0.084 | 3.5 % |
| `method_map` | 0.686 | 0.003 | 2.7 % |
| `line_tables` | 0.567 | 0.003 | 2.3 % |
| `thread_local` | 0.092 | 0.000 | 0.4 % |
| `thread_filter` | 0.039 | 0.000 | 0.2 % |
| `thread_info` | 0.009 | 0.000 | 0.0 % |
| `wallclock` | 0.008 | 0.000 | 0.0 % |
| **total** | **25.064** | **0.082** | 100 % |

**This reorders the optimisation targets.** Call-trace storage was previously
the largest category by a wide margin; corrected, it is third, and
`native_symbols` + `dictionary` together account for **72 %** of the profiler's
directly measured memory.

---

## What changed in the counter, and what it cost

`LinearAllocator` recorded a whole 8 MiB `CALL_TRACE_CHUNK` into `NM_CALLTRACE`
the moment it was `mmap`'d — before any byte was touched — and `reserveChunk()`
pre-reserves the next chunk at 50 % fill, so at any instant at least one
fully-counted chunk was essentially untouched. The counter now records the bytes
`alloc()` actually hands out, which tracks touched (resident) memory directly.

Effect on the real workload: call-trace fell from **24.23 → 3.53 MiB**, a 6.9×
over-report. Peak touched bytes never exceeded 6.42 MiB, so this is not a
sampling-phase artifact. In an isolated synthetic sweep the same change moved
the counter 24.53 → 5.38 MiB with every other category byte-identical.

Cost, isolated allocator microbenchmark (3 runs each, sd < 1 ns):

| Scenario | Before | After | After, peak established |
| --- | --- | --- | --- |
| single thread | 12.62 ns | 25.66 ns | 18.15 ns |
| 8 threads, contended | 64.87 ns | 116.3 ns | ~78.3 ns |

Relative cost roughly doubles, but `alloc()` is reached only for a
*previously unseen* call trace — repeat samples of a known stack never allocate
— so the real cost is low milliseconds per 90-second run. About 7.4 ns of the
single-thread increase is `record()`'s peak high-water CAS, which fires on every
allocation only during pure growth; rotation avoids it (third column).

`linearAllocator_nativemem_ut.cpp` pins the new behaviour and fails against the
old code (reporting a full 1 MiB chunk where 12,800 B were handed out).

---

## Candidates for the remaining gap

Named hypotheses, not yet measured on this workload:

| Est. | Candidate |
| --- | --- |
| ≈ 7.6 MiB | **Free-but-held arena pages.** glibc retaining rather than returning memory. Measured in the synthetic sweep but SE 3.0, range −7.2 to +17.2, sign-changing. Mostly *other* subsystems' chunks stranded by interleaving, so **not attributable to any profiler allocation** — a process-level, allocator-specific property. |
| a few MiB | **Natively created profiler thread stacks.** Created via `pthread_create`, not by the JVM, so their resident stack pages appear in *neither* NMT's Thread category *nor* the profiler's allocation counters — a structural blind spot between the two instruments. |
| 2–4 MiB | **The profiler library's own resident image.** Text and data pages of a 1.38 MB shared object. Not an allocation, so no counter sees it; not JVM-managed, so NMT does not either. |
| ≈ 0.9 MiB | **Unattributed profiler malloc.** Known from earlier call-site auditing; resolves only to a private `operator new`. |
| ≤ 2.9 MiB | **Call-trace pages the counter forgets.** `clear()` un-records a retained chunk's bytes, but its already-touched pages stay resident until unmapped. Bounded by the live-to-peak spread (3.53 → 6.42 MiB). |

These plausibly reach the lower end of the range. They do not obviously reach
28 MiB, which is a further reason to settle the RSS pairing before treating the
upper figure as real.

---

## Recommended next steps

The general lesson: **every correction factor is a place where a number measured
in one workload gets applied to another.** Two remain, and both are properties of
the *allocator*, not the profiler — which is why they should be reported as such
rather than folded into "profiler cost". Under tcmalloc or jemalloc (both
selectable in dd-trace-doe via `allocator=`) they would behave differently, and
that difference should be visible.

1. ~~Re-run both conditions interleaved.~~ **Done** — see "Interleaved re-run".
   It narrowed the residual to +4.6…+11.1 MiB and exposed a 7.1 MiB ordering
   bias. Any future re-measurement should keep the counterbalanced interleaving
   and the pinned `loops_num`/`allocs_num`; the harness is committed as
   `memsweep/run_doe_interleaved.sh`.
2. **Fold chunk overhead in exactly, per allocation** via
   `malloc_usable_size()`, replacing the ×1.17 average; report it per category,
   since `method_map` pays 16.7 % (96 B requested → 112 B real) while
   large-allocation categories pay ~0 %, and that ratio is what identifies a
   target. Requires runtime allocator detection: glibc adds an 8 B header
   (16 B for mmap'd), jemalloc and tcmalloc add none.
3. **Report process-wide arena waste as what it is**, from `mallinfo2()` on the
   flush path, labelled process-wide allocator overhead — giving an honest
   bracket rather than a false point estimate.
4. **Close the instrument blind spots** — natively created thread stacks and the
   library's resident image are invisible to both instruments today.

Full design, including three rejected alternatives and why, is in
`overhead-program-plan.md` § "Concrete next steps", item 6.
