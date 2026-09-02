# Where the profiler's memory goes

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

---

## Two terms worth pinning down

Both of these do real work below, and neither means quite what it sounds like.

**Anonymous memory** is the memory a program allocates for itself as it runs — as
opposed to memory that mirrors a file on disk. It is the part that grows when a
program does more work, and the part a container's memory limit counts. When this
document says the profiler "adds 59–74 MiB", this is what it adds.

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

The single number never reproduced because it was never a single quantity:

```
memory added  =  35.98 ± 0.26 MiB  +  1.01 × (allocator waste)
```

This fits 20 paired runs across two independent batches to within 0.77 MiB
(R² = 0.9992).

The two batches disagreed on the total by 15 MiB — 58.9 against 73.9 MiB — while
agreeing on the stable component to 0.4 MiB. The scatter was never in the profiler.
It was entirely in the allocator term.

> **The total did not get smaller.** It is still 59–74 MiB. 35.98 is one of two
> terms, and quoting it alone understates the cost by roughly half.

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
workload the profiler adds 59–74 MiB of anonymous memory. A bare single figure is not
reproducible — the two batches differ by 15 MiB — so quote either the two components,
or the total together with its ±8 MiB bar and the batch it came from.

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
