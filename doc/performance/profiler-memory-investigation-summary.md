# Where the profiler's memory overhead goes

*A summary of the Java profiler memory investigation, Aug–Sep 2026.*

**For readers who want to know what this work found and what it means, without the
technical detail.** Full detail, including the arguments that turned out to be wrong
and why, is in [`dd-trace-doe-reconciliation-2026-08-27.md`](dd-trace-doe-reconciliation-2026-08-27.md)
and [`memory-sweep-results-linux.md`](memory-sweep-results-linux.md).

| | |
| --- | --- |
| Overhead measured | **59–74 MiB** of anonymous memory |
| Stable component | **35.98 ± 0.26 MiB** |
| Accounting now closes to | **±0.77 MiB** (R² 0.999) |
| Requested but never actually used | **~25 MiB** of profiler allocation |

> **A note on what is being counted.** Everything in this document is *memory
> overhead caused by enabling the profiler* — the difference between running with it
> and without it. That is deliberately broader than "memory the profiler allocates".
> Only about a third of it is memory the profiler itself holds; the rest is memory it
> *causes* — the JVM commits more, and the C allocator retains more. All of it goes
> away when profiling is switched off, so all of it counts.
>
> **The tracer is not in these numbers, and the tracer is the bigger cost.** Every
> measurement here compares *tracing + profiling* against *tracing only*, so
> dd-trace-java's own overhead runs in both arms and cancels out entirely. For scale:
> on this same workload the tracer costs roughly **136 MB** against a no-APM baseline,
> against the profiler's ~104 MB by that same older measurement. So if someone asks
> "what does APM cost", the answer is not in this document — this only covers the
> profiler's marginal share on top of a tracer that is already running.

---

## Two terms worth pinning down

Both of these do real work below, and neither means quite what it sounds like.

**Anonymous memory** is the memory a program allocates for itself as it runs — as
opposed to memory that mirrors a file on disk. It is the part that grows when a
program does more work, and the part a container's memory limit counts. When this
document says profiling "costs 59–74 MiB", this is what it costs.

**Resident** means *actually occupying physical RAM right now*. This is the crucial
distinction, because **asking the operating system for memory and actually using it
are two different things.** Linux hands over real memory only when a program first
writes to a page. Memory that has been requested but never written to is not
resident: it has an address, but no RAM behind it.

That gap between *requested* and *resident* is where most of this investigation's
surprises lived — in both directions.

---

## The problem

Turning the profiler on adds memory to the application. Getting a *trustworthy number*
for how much has never been easy — it is the reason the dd-trace-doe project exists, a
harness for running controlled, repeatable A/B comparisons on realistic application
workloads instead of ad-hoc measurements that cannot be compared with each other.

This investigation began from that harness, and ran into two further problems. The
accounting had a gap no instrument claimed — a residual of a few megabytes. And even
with a purpose-built harness the total still moved: run the same experiment twice and
get answers tens of megabytes apart. With both problems live, there was no way to tell
a genuine regression from ordinary scatter.

Both are now resolved, and the second turned out to have a single, nameable cause.

**The goal was never to shrink the footprint.** It was to be able to account for it —
to name every megabyte, so that a future change costing 20 MiB shows up as a 20 MiB
change instead of disappearing into the noise.

### If you have "150–250 MB" in your head

Many people do — that is the figure in the
[APM overhead overview](https://benchmarks.datadoghq.com/notebook/14677323/apm-overhead-overview),
and it is where this work started. It does not contradict 59–74 MiB. It measures
something broader, in three ways at once:

| | The reported figure | This document |
| --- | --- | --- |
| **What is included** | Tracer **and** profiler together | Profiler only, on top of tracing |
| **What is measured** | Peak RSS over the whole run | Anonymous memory once it has plateaued |
| **Compared against** | Nothing attached | Tracing already on |

The August reproduction confirmed the ~250 MB figure end-to-end and split it: against
a no-APM baseline of 1514 MB peak RSS, the **tracer accounted for ~136 MB and the
profiler for ~104 MB**. So the profiler's share of the headline number was never 250 —
it was around 104 MB.

This document measures 59–74 MiB (≈62–78 MB) for that same share. Three things
plausibly account for the remaining difference, and they are **not equally well
established** — which matters, because the temptation is to read the gap as the
profiler having got cheaper.

**1. The older runs never reached steady state.** *Verified.* They were **90 seconds
long**, with NMT captured about 40 s in. This investigation established that anonymous
memory does not plateau until **t ≈ 180 s**. A 90 s run therefore ends before memory
has settled — and `memory=` reports the *maximum* over that window, so it captures the
peak of the startup ramp rather than the level the application actually runs at.
Estimator choice alone moves the answer by up to 20 MiB when sampling mid-ramp.

**2. The profiler may genuinely have improved in the interval.** *Suspected, not
proven.* Real work landed on the profiler between the two measurements and some of it
plausibly reduced footprint. Nothing in this investigation isolates that, so it cannot
be claimed — but it cannot be ruled out either, and an earlier draft of this document
wrongly asserted that nothing had changed.

**3. Scope and method.** Profiler-only rather than tracer-plus-profiler; anonymous
memory rather than total RSS, which also counts file-backed pages; and a considerably
more precise attribution of what belongs to whom.

> **How to settle (2), if it matters.** Run the *current* build under the *old*
> methodology — 90 s, peak RSS, no-APM baseline — and see whether the profiler's share
> still comes out near 104 MB. If it does, the whole gap is measurement. If it comes
> out lower, the difference is a real improvement and can be claimed as one. A couple
> of hours of machine time; nobody has done it.

What can be said without qualification: the two figures are **answers to different
questions**, and the newer one is not a replacement. For "what does enabling APM cost
a customer", the overview figure remains the one to quote.

## The approach

The workload and the A/B mechanism come from dd-trace-doe. This investigation added
two things on top of it: a stricter experimental design, and instrument redundancy.

On design — the two arms are **interleaved and counterbalanced**, so that machine
drift and run-order effects cannot land preferentially on one side, and sampling
happens only after memory has plateaued. Both mattered: measuring the arms in separate
windows shifts the answer by ~14 MiB, and the first run of a pair carries ~7 MiB more
than the second regardless of which arm it is. Roughly forty pairs underpin the
findings.

The methodological rule that did the real work: **no single instrument settles
anything.** A finding had to be confirmed by at least two that share no code and no
data source.

| Instrument | What it sees |
| --- | --- |
| Container memory usage | What the kernel reports the container occupying (cgroup `anon`) — the ground truth being explained |
| JVM NMT | The JVM's own account of memory it commits on the profiler's behalf |
| Profiler counters | The profiler's per-category record of what it allocates |
| glibc `mallinfo` | The C allocator's view: in use, free-but-retained, mmap-served |
| Per-mapping `smaps` | Residency region by region — which pages are genuinely backed by RAM |
| Allocation ledger | Every allocation in the process, attributed to the code that made it |

That redundancy is what caught the errors. Three of the four conclusions we
overturned had looked convincing because an *average* matched.

---

## Finding 1 — The overhead is two things, not one

The profiler's memory cost had always been reported as **one figure with a wide error
bar** — "about 59 MiB, give or take 9". That figure would not reproduce. Measure it
again, changing nothing about the profiler or the workload, and you get 74 MiB.

It would not reproduce because it was never one quantity. It is the sum of two, and
they behave nothing like each other:

| | What it is | How big | How stable |
| --- | --- | --- | --- |
| **Term 1** — memory directly in use | What the profiler itself occupies, **plus** the extra the JVM commits because profiling is switched on | **35.98 MiB** | ± 0.26 MiB — essentially fixed |
| **Term 2** — allocator retention | Memory the C library took from the operating system while serving those allocations, then held onto for reuse instead of giving back (see Finding 2) | **23–37 MiB** | different in every batch |

> **Both terms are the cost of enabling the profiler.** Term 2 is not background
> noise that happens to coincide — it exists *because* of the profiler's allocation
> pattern, it is real physical memory (Finding 3), and it disappears when profiling
> is off. It is an indirect cost rather than a smaller one.

**Add them together and you get the range in the summary table:**

```
             Term 1     Term 2        predicted     actually measured

  batch 1     35.98  +   23.1     =     59.1  MiB        58.9  MiB
  batch 2     35.98  +   37.5     =     73.5  MiB        73.9  MiB
```

That is the entire story of the irreproducible number. Term 1 is stable to a quarter
of a megabyte across two batches measured days apart. Term 2 moved by 14 MiB between
them. **All of the apparent instability was Term 2** — and none of it was the
profiler's own behaviour changing.

Stated precisely, the relationship holds across 20 paired runs to within 0.77 MiB:

```
memory added  =  35.98 ± 0.26 MiB  +  1.01 × (allocator retention)
```

The 1.01 multiplier matters more than it looks: it says allocator retention converts
to real memory very nearly one-for-one. That was not the prior belief, and Finding 3
is about how it was established.

### How much of Term 1 is actually the profiler?

Less than you would guess. Attributing every allocation to the code that made it
(Finding 4) splits Term 1 roughly one-third / two-thirds:

| | MiB | Share of Term 1 |
| --- | --- | --- |
| The profiler's own resident memory | **12.1** | 33 % |
| Extra memory the JVM commits because profiling is on | **24.7** | 67 % |
| *sum* | *36.8* | *vs 35.98 measured — agrees to 0.8 MiB* |

The JVM-side share is JIT code cache the profiler causes to grow, plus the JVM's own
bookkeeping for the instrumentation it is now running. So of the ~59–74 MiB
total, only about **12 MiB is memory the profiler itself occupies**. The rest is
memory it *causes* — the JVM commits it, or the C allocator retains it.

*Indicative rather than exact: the allocation-ledger figures come from probe-instrumented
runs and the code-cache figure from a different batch, which is why the split closes to
0.8 MiB rather than exactly.*

> **A caution, because this is easy to misread.** Splitting the number in two did not
> make the profiler cheaper. The overhead is still 59–74 MiB — both terms are real
> memory the application pays for. **35.98 MiB is one of two terms, not the total**,
> and quoting it on its own understates the cost by roughly half.

## Finding 2 — All the variance is the C allocator

Within a single run, memory settles to a level reproducible to **0.13 MiB**. Across
runs, the paired difference scatters with a standard deviation of **29.6 MiB** — a
ratio of about 230×, which no amount of measurement noise explains.

The cause is **free-but-retained allocator memory**: pages glibc has taken from the
kernel, used, freed internally, and kept for reuse rather than returning. How much
accumulates depends on the fine-grained interleaving of allocations and frees, which
differs between otherwise identical runs.

This matters practically: **more repetitions cannot fix it.** Reaching ±1 MiB by
averaging would take about 873 paired runs — four to five days of machine time.
Separating the two terms achieves the same precision immediately.

## Finding 3 — Retained allocator memory is real

This reversed a documented conclusion, and it is the most consequential result here.

| | |
| --- | --- |
| **Previously concluded** | Not a real cost. It looked like address space the allocator merely reserves — bookkeeping, not pages the process pays for. The totals matched that reading almost exactly. |
| **Measured** | A real cost — essentially **100 % resident**. Every byte is backed by physical memory. At 23–37 MiB it is one of the two largest terms in the whole account. |

The original argument matched on averages. It could not, however, explain why the
measured memory *moved between runs* — and the model including retained memory tracks
that movement almost perfectly. Two independent instruments then agreed: a statistical
fit across 20 pairs, and direct region-by-region residency measurement.

The same evidence inverted the picture in the other direction too. Memory the profiler
requests in large blocks — which we had assumed was a real cost — turns out to be
largely *untouched*, and therefore free.

## Finding 4 — Requested is not resident

Counting bytes you asked for is not the same as counting memory you occupy. The two
sides of the reconciliation had been compared as though they were.

Large allocations are served by their own mapping, and those pages cost nothing until
written to. A component can therefore report tens of megabytes and occupy almost none
of it. Every term now carries a measured residency factor:

| Memory region | Actually resident | |
| --- | --- | --- |
| Java heap | 100 % | full cost |
| JIT code cache | 99 % | full cost |
| Thread stacks | 88 % | near-full |
| Allocator arena | 96 % | near-full |
| Large mapped blocks | **~0 %** | **no cost** |

Tracing every allocation back to the code that made it settled who owns that last row,
and the answer was not what we expected:

| Allocated by | Total requested | Of which never written to |
| --- | --- | --- |
| The profiler | +37.5 MiB | **+25.4 MiB** |
| The JVM itself | +16.0 MiB | 0.0 MiB |

**Roughly two-thirds of the profiler's own heap allocation is requested and then never
written to.** The JVM's additional allocation, by contrast, is fully resident.
Reproducible to ±0.01 MiB across three paired runs.

### What "never written to" actually means here

It is worth being exact, because the phrase sounds either impossible or unimportant
and is neither.

**What it does not cost.** Those 25 MiB occupy no physical RAM. They do not count
toward the container's memory limit, do not appear in the process's memory footprint,
and cannot contribute to an out-of-memory kill. On a 64-bit system the address space
they consume is not a meaningful resource. In the sense that matters operationally,
they are free.

**What it does cost.** Two things, both real:

- **It makes our own numbers wrong.** The profiler's internal counters report what it
  *requested*, so they overstate its actual memory footprint by roughly this amount.
  That is a reporting defect, not a memory defect — but it is precisely the kind of
  thing that made the overhead hard to account for in the first place.
- **It is latent, not absent.** These pages become real the moment anything writes to
  them. Today's cost is zero because the memory goes unused, not because it was
  cheaply obtained.

**Why allocate it at all, then?** Because it is a side effect rather than a decision.
When a program asks for a large enough block, the C library satisfies it with a fresh
region from the operating system rather than from its recycled pool. Ask for more than
you go on to fill, and the remainder is simply never touched. Nobody chose to reserve
25 MiB; it is the accumulated tail of many generously-sized requests.

---

## Conclusions for Java

**Quote the overhead as two terms, or with its error bar.** On a realistic Spring Boot
workload, enabling the profiler causes 59–74 MiB of additional anonymous memory. A bare
single figure is not reproducible — the two batches differ by 15 MiB — so quote either
the two components, or the total together with its ±8 MiB bar and the batch it came
from.

**Do not set this against the 150–250 MB APM figure as though one replaced the other.**
That figure covers tracer *and* profiler, as peak RSS, against a no-APM baseline; the
profiler's share of it was ~104 MB. The 59–74 MiB here is that same share measured at
steady state. Both are correct answers to different questions — for "what does enabling
APM cost a customer", the overview figure is still the one to quote. See
[If you have "150–250 MB" in your head](#if-you-have-150250-mb-in-your-head).

**Quote absolute megabytes, never a percentage.** The same overhead reads as 2.5 % or
3.9 % depending purely on how the baseline heap is configured. The denominator is a
measurement choice, not a property of the profiler.

**The accounting now closes.** There is no large unexplained gap left. Memory is
predicted to within 0.77 MiB, every term is named, and each carries a measured
residency factor. A future 20 MiB regression would now be unmissable.

**There is a real footprint opportunity, precisely located.** The profiler allocates
roughly 23–25 MiB it never touches. It costs no memory today, but it is the profiler's
own allocation and is therefore addressable if that becomes worthwhile.

**Much of the cost is the C allocator, not the profiler.** The largest variable term is
glibc retaining freed pages. That is an allocator property — under a different allocator
it behaves differently — so it belongs in reported measurements rather than folded into
"profiler cost".

**The measurement recipe is settled.** Interleaved counterbalanced pairs, a pre-touched
heap, sampling only after memory plateaus, and cross-checking against an independent
instrument. Captured in reusable tooling under [`memsweep/`](memsweep/).

### Two code defects surfaced along the way

A diagnostic counter reports zero in production because it is reset after the resources
it tracks are already allocated. And a measurement bias was found in how call-trace
memory is sampled — readings are taken immediately after the data is discarded, so they
capture the trough of a cycle rather than its average. Neither affects users; both make
internal numbers misleading.

---

## The lesson worth keeping

Three of the four conclusions overturned here failed the same way: an **average
agreed**, and that was taken as confirmation, when the data could not actually
distinguish between competing explanations.

In each case the wrong answer survived until something with discriminating power was
applied — comparing variances rather than means, testing on a second workload, or
simply attaching a proper error bar. Matching averages is weak evidence. It should not
settle anything on its own.

---

**Scope.** One workload (Spring Boot, enterprise archetype), Linux, JDK 21, glibc.
Approximately forty paired runs across several batches. All figures are paired deltas —
the cost of *enabling* profiling, not total process memory.
