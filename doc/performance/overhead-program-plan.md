# Java Profiler Overhead — Program Plan

## The question

**"What is the overhead of java-profiler — CPU, memory, and latency — and
can we explain it to customers?"** This has been asked before — it's what
originally motivated [dd-trace-doe](https://github.com/DataDog/dd-trace-doe),
which reported **~150–250 MB** of memory overhead. We don't yet know how
much of that is profiler-specific vs. APM tracing, framework/classloading
diversity, or measurement methodology, and we don't have a model that
predicts overhead for a given customer's workload shape — for any of the
three dimensions.

**Stated goal, as clarified**: measure overhead and set the baseline, for
CPU, memory, and latency. dd-trace-doe has been the mechanism for this so
far, but there's disagreement with how it measures overhead, which raises
the actual open question: **which use cases (workload shapes) are good ones
to measure overhead with, and how do we implement measuring those and use
them to set a baseline and later do routine benchmarking?**

That's a narrower framing than this document takes, deliberately. "Measure
overhead and set the baseline" is essentially Phase 1 below (understanding
+ baselining). We think it's worth scoping the effort a bit wider than that
single deliverable, for a concrete reason our own memory investigation
already demonstrates: a one-time baseline number, by itself, doesn't survive
contact with "does this help a customer" or "does this stay accurate as the
codebase changes." Our memory work found overhead ranges from ~0 to >100 MB
depending on a workload property (call-graph diversity) that a flat baseline
number can't capture — the useful output isn't "the baseline is N MB," it's
"here's what drives it, here's how to tell where your app falls, here's how
we'll know if a future change makes it worse." That requires the fuller loop
this document lays out: understand → track → calibrate against real
customers → improve. We believe this is *more* aligned with what will
actually be useful to customers and the business than a single baseline
number, not a scope creep away from the ask.

## Where we are today: memory

Everything concrete we have so far is memory-specific. CPU and latency
overhead haven't been investigated at all yet (see below) — this is the
most significant gap in the current state, and the plan explicitly calls
out closing it, not just continuing the memory work.

An initial empirical investigation (this repository,
[memory-usage-model.md](memory-usage-model.md) →
[memory-sweep-results.md](memory-sweep-results.md) (macOS) →
[memory-sweep-results-linux.md](memory-sweep-results-linux.md) (Linux,
current, has the full detail behind everything summarized here)) has
produced real findings and reusable tooling:

- **The profiler's own accounting is now trustworthy — it was not before.**
  An audit attributing every live allocation to its call site found the
  counters covered only 37 % of what the profiler actually allocates, because
  `NM_NATIVE_SYMBOLS` was a gauge that never ran during a recording and read 0
  while `CodeCache` held ~13 MB. Fixed; coverage is now **96 %**, with no
  miscounting at any instrumented site. This matters for Phase 2: continuous
  tracking can now be built on these counters rather than on RSS alone.
- **The counters still do not equal RSS, for understood reasons.** They record
  logical bytes while RSS pays for malloc chunks (~17 % inflation at this
  allocation profile), glibc holds unreclaimable free arena pages, and
  `NM_CALLTRACE` reports virtual capacity roughly 2× its resident use. Those
  three account for the difference; see the results doc.
- **Overhead is not flat and not a simple step function. It's roughly
  linear in the number of distinct *methods* (equivalently, call-trace
  shapes) actually appearing in sampled stacks — not classes, not raw
  class-loading volume, not thread count.** The original benchmark gave
  every synthetic class exactly one method, so "classes touched" and
  "methods touched" moved together and looked like the same variable; a
  follow-up holding class count fixed at 2,000 while adding methods per
  class (100 instead of 1) reached ~74 MB — in the same range as the
  85,000-sampled-class/1-method-each result (~102 MB) — confirming methods,
  not classes, drive it. Negligible below ~2,000 sampled methods, growing
  to ~102 MB by ~85,000, and noisier at the high end (stdev comparable to
  the mean).
- **~35 MB of the ~102 MB has a confirmed mechanism.** It's visible to
  NMT and driven by jmethodID preloading (`JVMTI_EVENT_CLASS_PREPARE` →
  `GetClassMethods`, `jvmSupport.cpp:145`) — the agent eagerly
  preallocates jmethodIDs for every prepared class, which AsyncGetCallTrace's
  signal-handler safety requires. Confirmed with a toggle test: disabling
  the mechanism collapses the relevant NMT category deltas to noise.
- **The rest is accounted for, and it is not a missing allocation site.** A
  whole-process allocation ledger showed the RSS delta decomposes with no
  meaningful remainder — two independent instruments disagreeing by
  −0.06 MiB (SE 0.16) over 9 paired runs. It is malloc chunk overhead
  invisible to logical counters (+6.4 MiB, the most reproducible figure in
  the study), unreclaimable glibc arena slack (real but variable), and
  `NM_CALLTRACE` reporting virtual capacity rather than residency. This was
  the biggest open item in the memory track and is now closed; full detail
  in the results doc.
- **A separate, additive cost exists at JFR chunk write time.** Wall-clock
  sampling's class-name dictionary growth is only reflected in the
  *following* chunk's counter reading, by design — so the steady-state
  ~102 MB figure above doesn't include it. Measured directly at
  ~140–235 MB (construction-dependent; the measurement itself perturbs the
  system, so the unperturbed magnitude isn't pinned down precisely), paid
  once per JFR chunk write. For the default single-continuous-recording
  mode this happens once, at process exit; for any config that rotates
  chunks periodically, it recurs.
- **Single-run comparisons are unreliable at this scale.** A 2–3 rep
  with/without-agent comparison at N=150,000 classes gave estimates ranging
  91–246 MB depending on which runs happened to be paired; 10 reps
  converged on ~102 MB. Any future measurement — ours or dd-trace-doe's —
  needs to budget for repetition, not trust a single pair.
- **Reusable tooling exists**: `doc/performance/memsweep/` — synthetic
  workloads isolating thread count, call-trace diversity, class diversity,
  methods-per-class (isolates methods touched from classes touched, which
  the class-diversity workload alone can't do), and allocation diversity
  independently; a repeated-measures with/without-agent harness
  (`run_repeated_sweep.sh`) built specifically because
  single-pair comparisons proved unreliable; NMT category-level breakdown
  methodology.
- **Known measurement gaps**: `NM_PERF` unverifiable in the sandboxed test
  environment (needs a root-accessible host with relaxed `kptr_restrict`);
  `nativemem=` (native malloc tracing) only smoke-tested; ~0.9 MB of the
  profiler's own malloc still unattributed; the final JFR chunk's own
  serialization cost is emitted nowhere.

## Where we are today: CPU and latency

Nothing empirical yet — no synthetic sweep, no candidate driving dimensions
identified, no hypotheses tested. We do think the *methodology* from the
memory investigation transfers directly: isolate one workload property at a
time in a synthetic microbenchmark, measure with/without-agent using enough
repetitions to trust the number, then attribute the delta to a mechanism
before proposing a fix. What we don't yet know, and can't credibly guess in
advance, is *which* workload properties turn out to matter for CPU and
latency the way call-graph diversity (distinct methods actually sampled)
turned out to dominate memory —
that's exploratory work still ahead of us (see Phase 1 below). Plausible
starting hypotheses worth testing early, none validated: sampling
frequency/engine choice (wall-clock vs. CPU-time vs. allocation), thread
count and contention (signal-delivery cost scales with active threads),
safepoint-biasing effects from JVMTI stack walking, and interaction with GC
pause timing. Latency specifically may also need tail-latency-sensitive
measurement (p99/p999) rather than averages, since profiling's overhead is
plausibly bursty (tied to sample ticks and chunk rotations) rather than
uniform per-request.

## What we learned about dd-trace-doe specifically

- **Already measures overhead across CPU, memory, and latency** — its
  output schema records `cpu`, `memory`, `latency_p50`, `latency_p99`, and
  `startup_wall` per run, each independently correlatable against the
  `tracing`/`profiling` toggles. The stated goal above ("measure overhead
  for CPU, memory, and latency") isn't a scope dd-trace-doe is missing —
  the friction is with *how* it measures (which workload shapes, how
  reliably), not *what* it measures.
- Measures **peak cgroup `anon` memory** of the whole container, sampled
  during load and stop phases, `tracing`/`profiling` each independently
  toggleable (`internal/schema/output.go`).
- The test app is a **real Spring Boot service running the full
  `dd-java-agent.jar`** — i.e. APM tracing (bytecode instrumentation across
  many libraries) plus this profiler, not the profiler in isolation.
- It has an **`endpoints` parameter** (default 1, tested up to 1000+ in the
  codegen tooling) that generates N separate `@GetMapping` controller
  methods — structurally close to our own `classes`/`traces` sweep
  dimension, but we don't yet know what value(s) produced the reported
  150–250 MB.
- It runs on **real EC2 instances via nightly GitLab CI**, results reported
  to Datadog — i.e., it already does most of what "phase 2" below describes,
  at the language/archetype level, just not with the granularity (or
  profiler-only isolation) our investigation needs.

**Implication**: reconciling "our ~102 MB at high method/call-graph-
diversity" against "their 150–250 MB" is not an apples-to-apples number
comparison yet. Their figure likely includes APM tracing overhead,
Spring/Tomcat/dd-trace-java's own substantial baseline diversity of
distinct methods actually invoked (present even at `endpoints=1`, and
potentially large regardless of how few *classes* that involves — our own
finding that methods, not classes, drive this cost means a framework-heavy
app's baseline could be higher than a naive class-count estimate would
suggest), and container-level measurement noise, on top of whatever the
profiler itself contributes. Phase 1 below includes pinning this down as
an explicit task, not assuming either number is "right."

## Phase 1 — Understand the overhead and its nuances

**Goal**: a customer-explainable model, for CPU, memory, and latency each
("your overhead is roughly X, driven by A/B/C, here's how to check where
your app falls"), backed by tooling good enough to trust, and a real
reconciliation with dd-trace-doe's numbers — not just "we found something
similar to their number." Memory is furthest along; CPU and latency are
starting close to zero and should follow the same method, not a different
one invented from scratch.

1. **Memory — close out the open threads from the current investigation**:
   - jmethodID preloading confirmed as the driver of the Class/Internal/
     NMT's-own-overhead deltas (~35 MB of the ~102 MB). "Java Heap"
     remains open — it moved opposite to expectation under the toggle
     test, but that metric is too noisy (~240 MB swing across 5 same-
     condition reps) to attribute either way at a practical rep count;
     would need many more reps or a less noisy measurement approach.
   - **RESOLVED: the unattributed remainder.** A whole-process allocation
     ledger showed the RSS delta decomposes with no meaningful remainder
     (two independent instruments disagreeing by −0.06 MiB, SE 0.16, over
     9 paired runs). It was never a missing allocation site: it is malloc
     chunk overhead invisible to logical counters, unreclaimable glibc arena
     slack, and `NM_CALLTRACE` reporting capacity rather than residency. See
     "Where the RSS delta goes" in the results doc.
   - **RESOLVED: why the chunk-flush burst is ~80x raw string content.** It is
     `StringDictionary`'s overflow chaining, not string storage: 154.98 MiB of
     the growth arrives as 26,450 allocations of exactly `sizeof(SBTable)`
     (6,144 B) from `StringDictionaryBuffer::insert_with_id`. A row holds 3
     keys; the fourth chains a whole 128-row table for it. It does not fall
     back afterwards because `rotate()` copies the interned set forward by
     design, so the grown buffer is the live dictionary. This is now an
     optimization opportunity rather than an open question — see "Chunk-flush
     cost" in the results doc.
   - Get `NM_PERF` verified on a non-sandboxed host (root, relaxed
     `kptr_restrict`) — currently unverifiable by construction, not by
     absence of effort.
   - Extend the repeated-measures with/without-agent methodology (currently
     only rigorously applied to `classes` mode) to `traces`, `allocs`, and
     the CPU-sampling engine, and to higher thread counts — right now we
     only have a *statistically trustworthy* number for one dimension.
   - Characterize `nativemem=` (native malloc sampling) properly — only
     smoke-tested so far, no dedicated workload built for it.
   - Test whether the "roughly linear in sampled-method-count" finding
     holds beyond ~100,000 touched methods, and whether it's specific to
     reflection-heavy workloads (our synthetic harness's method of
     invocation) or general.

2. **CPU and latency — start from zero, using the memory investigation as
   the method template, not by guessing the answer up front.** Concretely:
   build isolated synthetic microbenchmarks varying one candidate dimension
   at a time (the hypotheses listed under "Where we are today: CPU and
   latency" above are a reasonable starting list, not a final one), measure
   with/without-agent with enough repetitions to trust the number (we
   learned this the hard way on memory — see below), and only *then* decide
   which dimensions are worth turning into permanent benchmarks. Expect this
   to surface a different dominant driver than memory's — no reason to
   assume class/call-graph diversity is also the main CPU/latency lever —
   so avoid reusing the memory benchmark matrix for CPU/latency without
   checking it's actually the right one first.

3. **Reconcile with dd-trace-doe.**
   - Find the specific run/config that produced the reported 150–250 MB
     (archetype, `endpoints` value, `tracing`/`profiling` flag combination,
     library version) — this needs someone with access to dd-trace-doe's
     stored results/dashboards, not just the repo.
   - Run dd-trace-doe with `profiling=true,false` at matched `tracing`
     settings across a range of `endpoints` values, to see whether their
     measured delta tracks class/endpoint-count the way our model predicts.
   - Estimate (or directly measure, e.g. via a debug/whitebox build) the
     baseline distinct-class/distinct-call-trace-shape count a Spring Boot
     app plus dd-trace-java's own instrumentation touches even at
     `endpoints=1` — this may already be large enough to explain a
     meaningful chunk of the reported overhead on its own, independent of
     the endpoints parameter.
   - Where their container-level `anon` memory metric and our `ps`-based
     RSS diverge, understand why before treating the two as comparable.

4. **Produce the customer-facing model**, per dimension as each matures
   (memory first). A short, publishable explanation: roughly what to expect
   at low/medium/high diversity on whatever the dominant driver turns out to
   be, phrased in terms a customer can self-assess against their own app
   (e.g., for memory: "if your app is a small number of services with
   narrow, repetitive call paths, expect near-zero overhead; if it's a large
   framework-heavy monolith or a microservice fleet with wide call-graph
   diversity, expect overhead in the tens-to-~100MB range, scaling with how
   much distinct code gets sampled"). This is the direct deliverable the
   original question was asking for.

5. **Identify low-hanging fruit and larger improvement opportunities**
   (deliberately sequenced *after* the above, since fixing things you don't
   understand yet risks fixing the wrong thing). Memory candidates, ranked
   by confidence: **DONE — ported `origin/main`'s `#ifdef DEBUG` gate on
   `ProfiledThread`'s `UnwindFailures` field** (`e1de4cf08`, #734, cherry-picked
   with zero conflicts). Was confirmed by direct measurement to cost ~296 KB
   per distinct thread ever profiled on this branch's release builds
   (`memory-usage-model.md`, "Thread count / thread churn"); the port also
   fixes a real infinite-loop bug in `HotspotSupport::walkVM` for unwindable
   stub frames. Next, jmethodID preloading strategy — confirmed driver of a
   real ~36 MB chunk of overhead at high class diversity (this specific
   mechanism fires per loaded class, independent of sampling, so "class"
   is the mechanistically accurate word here even though the *aggregate*
   overhead figure is method-driven — see "Where we are today: memory"),
   worth asking
   whether it can be lazier or bounded instead of eager-per-`ClassPrepare`
   (though the source comment already explains why it's eager: AGCT's
   signal-handler constraints, so any change here needs care) — plus
   calltrace/dictionary initial-capacity tuning for high-diversity
   workloads, a stronger candidate given the confirmed real (if not yet
   precisely quantified under normal conditions) chunk-flush dictionary
   growth. **INVESTIGATED AND CLOSED — unconditional `parseDwarfInfo()`
   table-building.** Implemented and tested (fixing a real correctness bug
   along the way — a naive gate would have silently broken DWARF unwinding
   for `libjvm.so` itself; see `memory-sweep-results-linux.md`), but the
   measured benefit on our benchmark dropped to ~0.07 MiB once fixed
   correctly, not worth the added complexity now. Submitted and closed
   without merging as
   [DataDog/java-profiler#755](https://github.com/DataDog/java-profiler/pull/755)
   for reference. **SIZED, NOT YET ATTEMPTED — `MethodMap`'s node-per-method
   `std::map`.** Confirmed 96 B logical / 112 B real RSS per node (two
   independent measurements agreeing exactly); a flat/open-addressing
   alternative barely changes the per-entry byte count (~98.5 B with
   load-factor headroom) but would eliminate per-node chunk-header overhead
   and the fragmentation this structure's continuous insert/prune cycle
   causes across chunk rotations (see `memory-sweep-results-linux.md`'s
   `MethodMap` section for the full sizing and the growth-strategy design
   notes — needs the `CallTraceHashTable` doubling pattern, not
   `SBTable`'s chaining pattern, plus a deletion story neither existing
   precedent has). More engineering than the two items above; worth
   returning to only if `MethodMap`'s growth becomes a measured problem in
   a real long-running/many-rotation deployment, which this document's
   single-flush tests can't observe. No CPU/latency candidates exist yet — they're a product of
   item 2's investigation, not knowable in advance. Output: a ranked backlog
   (effort vs. expected impact) feeding Phase 4.

### Which use cases are good to measure overhead with?

This is the specific question raised, and the honest answer differs by
dimension because our depth of investigation differs by dimension:

- **Memory: we have an evidenced answer.** The dominant lever is *distinct
  methods (call-trace shapes) actually touched by sampling* — confirmed to
  be methods rather than classes specifically (varying methods-per-class
  at a fixed, small class count reproduced the same overhead a 75x larger
  class count did), and not raw class-loading volume or thread count
  either. A good memory-overhead use case varies this directly (few
  endpoints/narrow call paths vs. many/wide), which is close to
  dd-trace-doe's existing `endpoints` parameter — the gap is that it
  defaults to 1 (a low-diversity point) and we don't know what range has
  actually been exercised, nor how many distinct methods (as opposed to
  classes) that range actually touches. Thread count and allocation
  diversity are secondary levers, worth a smaller number of fixed
  benchmark points rather than a full sweep.
- **CPU and latency: we don't have an evidenced answer yet, and shouldn't
  pretend to.** Item 2 above is how we get one. Until then, any specific
  archetype recommendation for these two would be a guess dressed up as a
  plan.
- **What we can commit to now**: the *method* for answering "which use
  cases" (isolate one candidate dimension at a time, measure with enough
  repetition to trust the delta, only promote validated dominant drivers to
  permanent archetypes), not a final list for all three dimensions today.
  See "Path to implementation" below for why we think this has to be the
  answer rather than a fixed archetype list up front.

## Phase 2 — Continuous tracking

**Goal**: catch regressions automatically and see trends across releases,
without relying on someone remembering to run a sweep by hand — for memory
first (it's the dimension with a benchmark matrix to build one from), then
CPU and latency once Phase 1's exploratory work identifies theirs.

- Decide split of responsibility with dd-trace-doe rather than building a
  parallel system from scratch: dd-trace-doe is already positioned for
  realistic, end-to-end, language/archetype-level tracking (real app, real
  load, nightly, reported to Datadog) — likely the right place for
  "does a dd-trace-java release regress overall memory overhead." This
  repo's `memsweep` harness is faster and dimension-isolated (single
  workload property varied at a time) — likely the right place for
  "does a java-profiler change regress the profiler's own footprint,"
  probably runnable per-PR or nightly on this repo specifically.
- Whichever mechanism: budget for repetition. This investigation directly
  demonstrated single-run comparisons can be off by 2x+ at realistic scale;
  a regression-tracking signal built on single runs will be too noisy to
  trust (false positives) or too insensitive to catch real regressions
  (drowned in noise).
- Define concrete regression thresholds and a small, stable benchmark
  matrix (e.g. a handful of fixed class-diversity/thread-count points
  spanning the range characterized in Phase 1) rather than the full
  exploratory sweep — the full sweep is a research tool, not a CI gate.
- Alert on regression beyond threshold; separately, keep a durable trend
  view (e.g. a Datadog dashboard, consistent with dd-trace-doe's existing
  reporting path) so "did this get worse over the last 6 months" is
  answerable without re-running old benchmarks.

## Phase 3 — Real-world telemetry

**Goal**: know what actual customer workloads look like, so the Phase 1
model is calibrated against reality instead of only synthetic benchmarks —
and so "is my app going to see the high end of this range" is answerable
from data, not guesswork.

- Identify what's cheap to report from the live agent without adding
  overhead of its own: for memory, the natural candidates are exactly the
  dimensions Phase 1 found to matter — distinct call-trace shapes/methods
  touched (the confirmed dominant driver, not raw class count), thread
  count/churn over a session. Some
  of this may already be adjacent to existing `NM_*`/debug counters; the
  work is packaging it as a "workload diversity" signal rather than a raw
  byte count, and deciding what's safe/appropriate to report (opt-in,
  aggregated, no customer-identifying data). CPU/latency-relevant telemetry
  is a placeholder until their Phase 1 dimensions are known.
- Report into Datadog's own telemetry so the *distribution* of workload
  diversity across the real customer fleet is visible — not just "what did
  our synthetic benchmark assume."
- Use this to validate (or correct) the Phase 1 model, and to build
  something more actionable than a single number: e.g. "based on fleet
  telemetry, N% of customers fall in the low-overhead regime, M% in the
  high; here's roughly where a given customer's app sits."

## Phase 4 — Improvement efforts

**Goal**: actually reduce overhead, guided by Phase 1's findings rather than
guessing.

- Work the ranked backlog from Phase 1.5.
- Every change validated against Phase 2's tracking (both to confirm the
  improvement landed, and to make sure it didn't regress something else) —
  this is the payoff for building Phase 2 before or alongside this work
  rather than after.
- Feed back into the Phase 1 customer-facing model as improvements ship —
  "as of version X, overhead in the high-diversity regime dropped from ~Y to
  ~Z."

## Path to implementation: iterative, not waterfall

The natural way to ask "what's the path to implementation" is as a
specification: decide the archetypes, then build them, then run them. We
don't think that will work here, and we have direct evidence from the
memory work, not just a general preference for agile-sounding language:

- We started the memory investigation assuming (per the static-analysis
  model in `memory-usage-model.md`) that thread count and the
  `NM_CALLTRACE` hash-table resize were likely the dominant costs. Empirical
  testing at the time found thread count close to noise — but that
  measurement itself turned out stale (see `memory-usage-model.md`'s "Thread
  count / thread churn" section): a later commit added an unconditional
  ~296 KB/thread allocation (`UnwindFailures`) that the thread-count sweep
  was never re-run against, so "thread count is noise" held only until it
  didn't. `NM_CALLTRACE`'s own resize is a small fraction (15–25 MB) of the
  actual overhead (~102 MB), and the real dominant driver (distinct
  methods/call-trace shapes actually *sampled* — not distinct classes, which
  the first benchmark design couldn't distinguish from methods since it gave
  every class exactly one) only emerged after several rounds of "measure, get
  a confusing result, dig into source, re-measure." Even that process needed
  a later re-check to catch a stale sub-result — which is itself further
  evidence for this section's point, not against it.
- A single-pair with/without-agent comparison at realistic scale was off by
  2x+ from the true value; getting a trustworthy number required building
  new tooling (`run_repeated_sweep.sh`) *during* the investigation, not
  something we could have specified up front.
- Attributing the ~102 MB to specific mechanisms took multiple rounds of
  cross-checking with independent tools (a debugger, a purpose-built
  allocation tracker, direct `/proc` memory inspection) before a result was
  trustworthy enough to act on — an initially-plausible-looking explanation
  turned out to be measuring something else on more than one occasion.
  Budget for this kind of repeated verification, not just a single
  instrumentation pass.
- We have no reason to expect CPU and latency to be more predictable than
  memory turned out to be. Committing now to specific new archetypes for
  them would be guessing, not planning.

**What we propose instead is a loop, run per dimension (CPU, memory,
latency), currently at different stages for each:**

1. Hypothesize candidate drivers (source reading + intuition) — cheap, fast
   (memory: done; CPU/latency: listed above as a starting point, not final).
2. Build isolated synthetic microbenchmarks and measure with/without-agent,
   repeated enough to trust the delta — this is investigative work, days
   per dimension based on the memory experience, not weeks, *if* the
   dimension turns out to matter; ruling one out is faster than confirming
   one.
3. Attribute the delta to a mechanism where practical (NMT category
   breakdown, source instrumentation) — this is where effort is hardest to
   predict in advance and where cross-checking matters most (see above).
4. Only *then* decide which validated dimensions become permanent
   archetypes/benchmarks, and build/extend the actual measurement mechanism
   (dd-trace-doe archetype changes, or a repo-local benchmark) — this is
   where most of the "should we have new archetypes" effort lives, and its
   size depends entirely on what steps 1–3 found. For memory, this looks
   like extending dd-trace-doe's existing `endpoints` parameter (a schema
   change plus benchmark-matrix definition, not new infrastructure) — a
   reasonable proxy for "small," but not yet scoped in detail. For CPU and
   latency, we can't size this yet because we don't know the dimension.
5. Feed findings into the customer-facing model and the tracking mechanism
   (Phase 2); repeat the loop as new findings (including Phase 3's
   real-world telemetry) surface dimensions we didn't think to test.

Phases 1 and 2 should start roughly together for the memory track (it's far
enough along to define an initial benchmark matrix), but CPU and latency
need at least one pass through steps 1–3 above before Phase 2 tooling can
be usefully defined for them. Phase 3 can start independently (it's mostly
agent instrumentation + telemetry pipeline work) but its *value* —
calibrating the model — depends on each dimension already having a model to
calibrate. Phase 4 explicitly waits on Phase 1's findings, per dimension;
starting improvement work before understanding the mechanism risks fixing
the wrong 15% and missing the 85% (as this investigation's own NMT
breakdown illustrates — the biggest memory lever might not be
`NM_CALLTRACE` at all, and we still don't know the CPU/latency equivalent).

## Open risks

- **dd-trace-doe's number may never fully reconcile** if it's measuring a
  meaningfully different thing (container `anon` memory including APM
  tracing and framework overhead, vs. profiler-only RSS delta). The goal
  should be "understand and explain the gap," not "make the numbers match."
- **Platform coverage**: this investigation's Linux pass ran in a sandboxed
  container with real limitations (`NM_PERF` unverifiable, some findings
  single-run). Production-representative hosts are needed before any number
  here is treated as final.
- **Measurement cost**: statistically trustworthy repeated-measures testing
  at high class-diversity is slow (the N=150,000 10-rep sweep took ~17
  minutes just for one N value, one dimension). Phase 2's CI-friendly
  benchmark matrix needs to be deliberately smaller than Phase 1's
  exploratory sweep, or it won't run often enough to be useful.
- **CPU and latency may turn out to need fundamentally different tooling
  than memory did.** Memory benefited from a fairly clean with/without-agent
  RSS diff; CPU overhead may be dominated by transient/bursty costs (sample
  ticks, signal delivery, JFR chunk writes) that a steady-state comparison
  doesn't capture well, and latency likely needs tail-percentile-aware
  measurement from the start rather than an average. Budget Phase 1.2 as
  genuinely exploratory, including "what should we even measure" as an open
  question, not just "run the memory harness with a different metric."

## Concrete next steps

1. Get access to the dd-trace-doe run(s)/config that produced the reported
   150–250 MB figure (Phase 1.3, first task — everything else in
   reconciliation depends on knowing what was actually measured).
2. Decide whether to act on the chunk-flush burst, now that its mechanism is
   known: `StringDictionary` chains a whole 6 KB `SBTable` per collision
   cluster, giving ~10.2 M allocated slots for a few hundred thousand interned
   strings. Growing by rehashing into a larger table, or raising `CELLS` from
   3, would cut the ~200 MB peak substantially. This is a scoped optimization,
   not an investigation — the memory track no longer has an open
   root-cause question.
3. Kick off Phase 1.2 for CPU and latency: pick 1–2 of the candidate
   hypotheses above, build the smallest synthetic microbenchmark that
   isolates one, and get a first with/without-agent number — the goal at
   this step is learning whether the memory methodology transfers cleanly,
   not landing a final answer.
4. Decide the Phase 2 split of responsibility between dd-trace-doe
   (end-to-end/nightly) and a java-profiler-repo-local benchmark (fast/PR
   or nightly) before building either — for memory first, since it's the
   only dimension far enough along to make this decision concretely.
5. Scope Phase 3's telemetry additions against what's already technically
   adjacent to existing counters, to estimate effort before committing.
6. **Make the allocator's own overhead measurable instead of corrected for.**
   Agreed design, not yet implemented. `NM_CALLTRACE` has already been fixed
   at source (it now counts bump-allocated bytes rather than reserved chunk
   capacity — see `memory-sweep-results-linux.md`), which removes the ×0.829
   residency factor. The two remaining correction factors are both properties
   of the *allocator*, not of the profiler, and should be surfaced as such —
   under tcmalloc or jemalloc (both selectable in dd-trace-doe via
   `allocator=`) they would behave differently, and that difference should be
   visible rather than folded into a constant:
   - **Per-category chunk overhead, as its own counter.** Capture
     `malloc_usable_size(p)` at record time and report the overhead
     *separately* from logical bytes, so `native_mem_live_bytes` stays
     comparable against `sizeof()` arithmetic. Keep it per-category: that is
     where the actionable signal lives (`MethodMap` is 96 B requested → 104
     usable → 112 real, 16.7 %, while large-allocation categories round to
     ~0 %; an aggregate hides exactly the ratio that motivates flattening).
     This replaces the blanket ×1.17.
   - **Runtime allocator detection** driving the header term: glibc adds 8 B
     per normal chunk (16 B for mmap'd, ≳128 KB), while jemalloc and tcmalloc
     have no per-object header at all — size-class metadata is out-of-band, so
     footprint ≈ `usable`. Hardcoding +8 would invent ~5.2 MB of overhead that
     does not exist on those allocators at the ~650,000-live-allocation scale
     measured here. The header cannot simply be dropped either: of the
     measured 10.4 B/alloc mean overhead, ~8 B is header and only ~2.4 B is
     16-byte alignment rounding. Probe via `dlsym` and emit the detected
     allocator name alongside the counters.
   - **Process-wide arena waste from `mallinfo2()`**, sampled on the JFR flush
     path only (it takes arena locks; never async-signal-safe). Report it
     honestly as *process-wide allocator overhead*, NOT as profiler cost:
     free-but-held arena pages are mostly other subsystems' chunks stranded by
     interleaving, so they are not attributable to any profiler allocation.
     Together with the profiler-only counters this yields a bracket — lower
     bound = profiler counters + chunk overhead; upper bound = that plus
     `fordblks` (worst case, every retained free byte in the process blamed on
     the profiler). Wide, but rigorous and honestly labelled.

   Rejected alternatives, with reasons: an *arithmetic estimate* of arena
   slack (it is a function of allocation history and arena/thread assignment,
   not of current live state — measured SE 3.0 on a mean of 7.6 MiB, range
   −7.2 to +17.2, sign-changing, so no formula over current state can predict
   it); *proportional attribution* of process slack by the profiler's share of
   live bytes (assumes slack accrues uniformly per byte, but it depends on
   size-class mix, and the profiler's ~83 B mean profile differs sharply from
   the JVM's — systematically wrong in an unknown direction); and using
   `max − live` as an upper bound on stranded profiler bytes (empirically
   fails by ~500×: the fixed build shows `max − live` = 0.015 MiB against
   measured arena slack of +7.6 MiB, because the slack consists of bytes the
   profiler never owned).

   Before landing: benchmark `malloc_usable_size` on the `CountingAllocator`
   path rather than assuming it is free. The `NM_CALLTRACE` work is the
   cautionary precedent — `record()` looked like a cheap relaxed atomic add,
   but its peak-update CAS turned out to be 7.4 ns of a 13 ns increase.
   Open when picking this up: whether `keepcost` deserves separate reporting
   (it separates glibc's trim-threshold retention from genuine fragmentation),
   and whether to emit `fordblks` from the tracing-only side too, so the
   paired-delta attribution is visible.
