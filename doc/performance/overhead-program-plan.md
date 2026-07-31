# Java Profiler Native Memory Overhead — Program Plan

## The question

**"What is the native memory overhead of java-profiler, and can we explain it to
customers?"** This has been asked before — it's what originally motivated
[dd-trace-doe](https://github.com/DataDog/dd-trace-doe), which reported
**~150–250 MB** of overhead. We don't yet know how much of that is
profiler-specific vs. APM tracing, framework/classloading diversity, or
measurement methodology, and we don't have a model that predicts overhead
for a given customer's workload shape. This document proposes a program to
close that gap: understand the overhead, build the tools to keep measuring
it, track it over time, learn what real customer workloads actually look
like, and then fix what's fixable.

## Where we are today

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
- **A first attribution pass exists but is incomplete.** ~44% of the
  overhead is visible to NMT (Class/Internal/Java-Heap/NMT's-own-tracking
  categories), with a concrete, plausible-but-unconfirmed candidate
  mechanism (jmethodID preloading via `JVMTI_EVENT_CLASS_PREPARE` →
  `GetClassMethods`, `jvmSupport.cpp:160`). The remaining ~56% is invisible
  to NMT (the profiler's own `malloc`/`new`), and of *that*, only 15–25 MB
  is explained by `NM_CALLTRACE` — leaving ~32–42 MB attributable to
  neither NMT nor `NM_*`. This reads as a real gap in PR #669's coverage
  (leading suspect: `MethodMap`/`MethodInfo`, confirmed to have zero
  `NativeMem::record` calls), not just an unexplained number.
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

## What we learned about dd-trace-doe specifically

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

**Goal**: a customer-explainable model ("your overhead is roughly X, driven
by A/B/C, here's how to check where your app falls") backed by tooling good
enough to trust, and a real reconciliation with dd-trace-doe's numbers — not
just "we found something similar to their number."

1. **Close out the open threads from the current investigation** — each is
   independently actionable:
   - Confirm or refute jmethodID preloading (`GetClassMethods` via
     `ClassPrepare`) as the driver of the "Class" NMT delta, by toggling it
     off and re-measuring.
   - Size `MethodMap`/`MethodInfo` directly and correlate against distinct
     classes touched, to close (or at least narrow) the ~32–42 MB
     unattributed gap. Treat this as a probable real coverage gap in PR
     #669, worth a fix or a follow-up PR, not just documentation.
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

2. **Reconcile with dd-trace-doe.**
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

3. **Produce the customer-facing model.** A short, publishable explanation:
   roughly what to expect at low/medium/high call-graph diversity, phrased
   in terms a customer can self-assess against their own app (e.g. "if your
   app is a small number of services with narrow, repetitive call paths,
   expect near-zero overhead; if it's a large framework-heavy monolith or a
   microservice fleet with wide call-graph diversity, expect overhead in the
   tens-to-~100MB range, scaling with how much distinct code gets sampled").
   This is the direct deliverable the original question was asking for.

4. **Identify low-hanging fruit and larger improvement opportunities**
   (deliberately sequenced *after* the above, since fixing things you don't
   understand yet risks fixing the wrong thing). Candidates already visible
   from phase-0 findings, to be validated: jmethodID preloading strategy
   (could it be lazier or bounded instead of eager-per-`ClassPrepare`?),
   `MethodMap`/`MethodInfo` sizing and lifecycle, calltrace/dictionary
   initial-capacity tuning for high-diversity workloads. Output: a ranked
   backlog (effort vs. expected impact) feeding Phase 4.

## Phase 2 — Continuous tracking

**Goal**: catch memory regressions automatically, see trends across
releases, without relying on someone remembering to run the sweep by hand.

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
  overhead of its own: the natural candidates are exactly the dimensions
  Phase 1 found to matter — distinct call-trace shapes recorded, distinct
  classes/methods touched, thread count/churn over a session. Some of this
  may already be adjacent to existing `NM_*`/debug counters; the work is
  packaging it as a "workload diversity" signal rather than a raw byte
  count, and deciding what's safe/appropriate to report (opt-in, aggregated,
  no customer-identifying data).
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

- Work the ranked backlog from Phase 1.4.
- Every change validated against Phase 2's tracking (both to confirm the
  improvement landed, and to make sure it didn't regress something else) —
  this is the payoff for building Phase 2 before or alongside this work
  rather than after.
- Feed back into the Phase 1 customer-facing model as improvements ship —
  "as of version X, overhead in the high-diversity regime dropped from ~Y to
  ~Z."

## Sequencing and dependencies

Phases 1 and 2 should start roughly together — Phase 2's tooling needs
Phase 1's benchmark-matrix decisions (which dimensions, which fixed points),
but doesn't need Phase 1 fully finished first. Phase 3 can start
independently (it's mostly agent instrumentation + telemetry pipeline work)
but its *value* — calibrating the model — depends on Phase 1 having a model
to calibrate. Phase 4 explicitly waits on Phase 1's findings; starting
improvement work before understanding the mechanism risks fixing the wrong
15% and missing the 85% (as this investigation's own NMT breakdown
illustrates — the biggest lever might not be `NM_CALLTRACE` at all).

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

## Concrete next steps

1. Get access to the dd-trace-doe run(s)/config that produced the reported
   150–250 MB figure (Phase 1.2, first task — everything else in
   reconciliation depends on knowing what was actually measured).
2. Toggle-test the jmethodID-preloading hypothesis (Phase 1.1) — cheapest,
   most concrete open thread from the current investigation.
3. Decide the Phase 2 split of responsibility between dd-trace-doe
   (end-to-end/nightly) and a java-profiler-repo-local benchmark (fast/PR
   or nightly) before building either.
4. Scope Phase 3's telemetry additions against what's already technically
   adjacent to existing counters, to estimate effort before committing.
