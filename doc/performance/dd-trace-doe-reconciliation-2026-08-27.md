# dd-trace-doe memory reconciliation, 27 Aug 2026

**Headline: the profiler's RSS overhead on this workload is 4.6–5.2 % of total
process RSS (≈ 75–84 MiB against a ≈ 1636 MiB baseline), and roughly 15–28 MiB
of it is still unexplained.**

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

1. **Re-run both conditions interleaved** in one window — cheapest way to
   remove the cross-time pairing weakness and narrow the residual.
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
