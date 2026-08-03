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
most significant gap in the current state and the plan explicitly calls
out closing it, not just continuing the memory work.

An initial empirical investigation (this repository,
[memory-usage-model.md](memory-usage-model.md) →
[memory-sweep-results.md](memory-sweep-results.md) (macOS) →
[memory-sweep-results-linux.md](memory-sweep-results-linux.md) (Linux,
current)) has already produced real, load-bearing findings and reusable
tooling:

- **The profiler's own tracked accounting (PR #669's `NM_*` counters) badly
  understates true overhead.** At 150,000 distinct classes, `NM_CALLTRACE`'s
  own growth is 15–25 MB, but the actual with/without-agent RSS delta is
  ~102 MB (10-rep measured, not inferred). The counters are useful signal,
  not a complete accounting.
- **Overhead is not flat and not a simple step function.** It's roughly
  linear in the number of distinct classes/methods *actually appearing in
  sampled stacks* (not raw class count, not thread count, not raw
  class-loading volume) — negligible below ~2,000 sampled classes, growing
  to ~102 MB at ~85,000 sampled classes in synthetic testing, and noisier at
  the high end (stdev comparable to the mean).
- **Attribution is now partly confirmed, not just plausible.** ~44% of the
  overhead is visible to NMT (Class/Internal/Java-Heap/NMT's-own-tracking
  categories). A toggle test (disabling jmethodID preloading —
  `JVMTI_EVENT_CLASS_PREPARE` → `GetClassMethods`, `jvmSupport.cpp:145` —
  via a one-line temporary patch, reverted after) confirmed it as the
  driver of 79% of that NMT-visible share: the Class, Internal, and NMT's-
  own-tracking deltas all collapse to noise when preloading is disabled.
  "Java Heap" remains unexplained — it moved the *opposite* direction under
  the toggle, but that specific metric swung ~240 MB across just 5 reps of
  the *same* condition, too noisy at practical rep counts to read either
  way. Separately, the remaining ~56% is invisible to NMT entirely (the
  profiler's own `malloc`/`new`), and of *that*, only 15–25 MB is explained
  by `NM_CALLTRACE` — leaving ~32–42 MB attributable to neither NMT nor
  `NM_*`. This reads as a real gap in PR #669's coverage. The leading
  suspect, `MethodMap`/`MethodInfo`, was sized directly and **ruled out** —
  it holds essentially zero entries in these runs, because its only
  inserter (`resolveMethod()`) turns out to be dead code for wall-clock
  `MethodSample` dumps on this build (same root cause as the `NM_DICTIONARY`
  finding). This part of the gap is now more open, not less — the leading
  candidate is eliminated, no replacement identified yet.
- **Single-run comparisons are dangerously unreliable at this scale.** A
  2–3 rep with/without-agent comparison at N=150,000 classes gave estimates
  ranging 91–246 MB depending on which runs happened to be paired; 10 reps
  converged on ~102 MB. Any future measurement — ours or dd-trace-doe's —
  needs to budget for repetition, not trust a single pair.
- **Reusable tooling exists**: `doc/performance/memsweep/` — synthetic
  workloads isolating thread count, call-trace diversity, class diversity,
  and allocation diversity independently; a repeated-measures with/without-
  agent harness (`run_repeated_sweep.sh`) built specifically because
  single-pair comparisons proved unreliable; NMT category-level breakdown
  methodology.
- **Known measurement gaps**: `NM_PERF` unverifiable in the sandboxed test
  environment (needs a root-accessible host with relaxed `kptr_restrict`);
  `nativemem=` (native malloc tracing) only smoke-tested; the exact
  mechanism rendering class names for wall-clock `MethodSample` stacks
  (confirmed *not* to go through `NM_DICTIONARY`) was never identified.

## Where we are today: CPU and latency

Nothing empirical yet — no synthetic sweep, no candidate driving dimensions
identified, no hypotheses tested. We do think the *methodology* from the
memory investigation transfers directly: isolate one workload property at a
time in a synthetic microbenchmark, measure with/without-agent using enough
repetitions to trust the number, then attribute the delta to a mechanism
before proposing a fix. What we don't yet know, and can't credibly guess in
advance, is *which* workload properties turn out to matter for CPU and
latency the way call-graph/class diversity turned out to dominate memory —
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

**Implication**: reconciling "our ~102 MB at high class-diversity" against
"their 150–250 MB" is not an apples-to-apples number comparison yet. Their
figure likely includes APM tracing overhead, Spring/Tomcat/dd-trace-java's
own substantial baseline class diversity (present even at `endpoints=1`),
and container-level measurement noise, on top of whatever the profiler
itself contributes. Phase 1 below includes pinning this down as an explicit
task, not assuming either number is "right."

## Phase 1 — Understand the overhead and its nuances

**Goal**: a customer-explainable model, for CPU, memory, and latency each
("your overhead is roughly X, driven by A/B/C, here's how to check where
your app falls"), backed by tooling good enough to trust, and a real
reconciliation with dd-trace-doe's numbers — not just "we found something
similar to their number." Memory is furthest along; CPU and latency are
starting close to zero and should follow the same method, not a different
one invented from scratch.

1. **Memory — close out the open threads from the current investigation**
   — each is independently actionable:
   - ~~Confirm or refute jmethodID preloading (`GetClassMethods` via
     `ClassPrepare`) as the driver of the "Class" NMT delta, by toggling it
     off and re-measuring.~~ **Done** — confirmed as the driver of the
     Class/Internal/NMT's-own-overhead deltas (79% of the NMT-visible
     share). "Java Heap" remains open: it moved opposite to expectation
     under the toggle, but that metric proved too noisy (~240 MB swing
     across 5 same-condition reps) to attribute either way at a practical
     rep count — would need many more reps to resolve, or a less noisy
     measurement approach.
   - ~~Size `MethodMap`/`MethodInfo` directly and correlate against distinct
     classes touched, to close (or at least narrow) the ~32–42 MB
     unattributed gap.~~ **Done, ruled out** — sizing instrumentation never
     fired because `resolveMethod()`, its only inserter, is dead code for
     these dumps (see below). The gap is still open; needs a different
     candidate structure, one actually exercised by wall-clock sampling.
     Still worth reporting the `resolveMethod`/`_class_map`/`_method_map`
     dead-code finding upstream as a probable real gap in PR #669's
     coverage independent of what explains this specific ~32–42 MB.
   - Get `NM_PERF` verified on a non-sandboxed host (root, relaxed
     `kptr_restrict`) — currently unverifiable by construction, not by
     absence of effort.
   - Extend the repeated-measures with/without-agent methodology (currently
     only rigorously applied to `classes` mode) to `traces`, `allocs`, and
     the CPU-sampling engine, and to higher thread counts — right now we
     only have a *statistically trustworthy* number for one dimension.
   - Characterize `nativemem=` (native malloc sampling) properly — only
     smoke-tested so far, no dedicated workload built for it.
   - Test whether the "roughly linear in sampled-class-count" finding holds
     beyond 150,000 classes, and whether it's specific to reflection-heavy
     workloads (our synthetic harness's method of invocation) or general.

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
   by confidence: jmethodID preloading strategy — **confirmed** driver of a
   real ~36 MB chunk of overhead at high class diversity, worth asking
   whether it can be lazier or bounded instead of eager-per-`ClassPrepare`
   (though the source comment already explains why it's eager: AGCT's
   signal-handler constraints, so any change here needs care, not just
   "make it lazy") — plus calltrace/dictionary initial-capacity tuning for
   high-diversity workloads, still unconfirmed. (`MethodMap`/`MethodInfo`
   sizing/lifecycle was investigated and ruled out as a fix target here —
   it's not populated in the workload tested, so there's nothing to tune.)
   No CPU/latency candidates exist yet — they're a product of item 2's
   investigation, not knowable in advance. Output: a ranked backlog (effort
   vs. expected impact) feeding Phase 4.

### Which use cases are good to measure overhead with?

This is the specific question raised, and the honest answer differs by
dimension because our depth of investigation differs by dimension:

- **Memory: we have an evidenced answer.** The dominant lever is
  *call-graph/class diversity actually touched by sampling* — not raw
  class-loading volume, not thread count. A good memory-overhead use case
  varies this directly (few endpoints/narrow call paths vs. many/wide),
  which is close to dd-trace-doe's existing `endpoints` parameter — the
  gap is that it defaults to 1 (a low-diversity point) and we don't know
  what range has actually been exercised. Thread count and allocation
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
  dimensions Phase 1 found to matter — distinct call-trace shapes recorded,
  distinct classes/methods touched, thread count/churn over a session. Some
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
  testing found thread count is close to noise, `NM_CALLTRACE`'s own resize
  is a small fraction (15–25 MB) of the actual overhead (~102 MB), and the
  real dominant driver (call-graph/class diversity, and specifically the
  *sampled* subset of it) only emerged after several rounds of "measure,
  get a confusing result, dig into source, re-measure."
- A single-pair with/without-agent comparison at realistic scale was off by
  2x+ from the true value; getting a trustworthy number required building
  new tooling (`run_repeated_sweep.sh`) *during* the investigation, not
  something we could have specified up front.
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
   predict in advance; the memory investigation's attribution work
   (jmethodID preloading confirmed, `MethodMap` sized and ruled out) took
   real digging across two separate toggle/instrumentation tests and still
   hasn't landed on the actual explanation for the ~32–42 MB gap — ruling
   out a leading candidate is real progress, but isn't the same as closing
   the question.
4. Only *then* decide which validated dimensions become permanent
   archetypes/benchmarks, and build/extend the actual measurement mechanism
   (dd-trace-doe archetype changes, or a repo-local benchmark) — this is
   where most of the "should we have new archetypes" effort lives, and its
   size depends entirely on what step 1–3 found. For memory, this looks
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
2. ~~Toggle-test the jmethodID-preloading hypothesis~~ / ~~Size
   `MethodMap`/`MethodInfo`~~ **Both done** (Phase 1.1) — preloading
   confirmed as a real driver; `MethodMap` sized and ruled out (it's
   unpopulated for this workload, same root cause as the `resolveMethod`
   dead-code finding under `NM_DICTIONARY`). Next up from the same list:
   find a replacement candidate for the ~32–42 MB gap — one actually
   reachable from wall-clock sampling — or resolve "Java Heap" with a much
   larger rep count.
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
