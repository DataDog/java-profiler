# dd-trace-doe memory reconciliation, 27 Aug 2026

**Headline: the profiler's RSS overhead on this workload is 3.9–4.3 % of total
process RSS (≈ 64–71 MiB against a ≈ 1630 MiB baseline). The unexplained
residual is +4.6 to +11.1 MiB — statistically indistinguishable from zero, but
also indistinguishable from ~15 MiB, because RSS measurement noise (± 8.5 MiB)
now dominates.**

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

`-XX:+AlwaysPreTouch` was tried and **rejected** — it roughly doubled RSS
variance rather than reducing it (sd 9.4 → 18.2 MiB tracing-only,
12.0 → 25.9 MiB profiling) and moved the mean RSS delta down ~22 MiB in a way
neither instrument tracked. Recorded as a negative result; not used here.

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

### What now limits the answer

RSS noise, not accounting. The paired delta's sd is 26.7 MiB even with the JIT
spikes removed; per-pair deltas ranged 26–112 MiB. Since SE = sd/√n:

| target SE | pairs needed |
| --- | --- |
| 8.45 MiB (current) | 10 |
| 5 MiB | 29 |
| 3 MiB | 79 |
| 2 MiB | 178 |

Distinguishing a 5 MiB residual from zero needs ~79 pairs (≈ 11 h of runs).
`-XX:+AlwaysPreTouch` was the obvious lever on per-run RSS variance and it made
things *worse* (see Conditions). So the practical options are more reps, or a
lower-variance RSS instrument — not further correction factors.

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
