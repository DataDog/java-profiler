# Design note: all-native OTEL context storage (eliminating the carrier-owned DirectByteBuffer)

- **Status:** Proposal (for review by java-profiler + dd-trace-java owners)
- **Date:** 2026-07-02
- **Related:** PROF-15271 (carrier-scoping fix, commit `94686da`), dd-trace-java #11646 (reapply-on-mount)
- **Scope:** cross-repo — `java-profiler` (this repo) and `dd-trace-java`

## TL;DR

The OTEL trace-context write path assumes native OS threads map 1:1 to Java threads. Virtual
threads break that assumption and cause a use-after-free that can crash the JVM. The shipped
carrier-scoping fix (`94686da`) shrinks the crash window but does not close it.

This note proposes making every context write go through a **native (JNI) call that resolves the
current carrier inside the call** — where the mounted virtual thread is *pinned to its carrier for
the duration by the native frame*, making the write **race-free by construction**. This deletes the
`DirectByteBuffer` / `CarrierThreadLocal` / reflection machinery entirely rather than adding more to
it.

A JMH campaign (six benchmark classes, JDK 21, glibc x64) establishes the key result: the all-native
path is a **modest net win (~7–10%) on the real per-scope-activation cycle** — but only when the
per-activation context is written in **one combined call**. With the current fine-grained call
sequence it would regress ~1.6×. The recommendation is therefore all-native **plus a combined
per-activation API**, rolled out via expand → migrate → contract.

Consumer audit: the entire public context API has **exactly one production consumer** (the
dd-trace-java profiler bridge) and no in-repo external consumers, so the migration risk is internal
coordination only.

---

## 1. Background & problem

The OTEL context record (`OtelThreadContextRecord`, 640 B + tag-encoding sidecar + LRS = 688 B) is
embedded in the **carrier's** native `ProfiledThread`. It is written by Java (through a
`DirectByteBuffer` "window" over that native memory) and read by the sampler (an async-signal
handler bound to the carrier OS thread, via `ProfiledThread::getOtelContextRecord()` — the sampler
never touches the Java buffer).

The write path was designed for platform threads, where a Java thread == a native thread for life.
Under Loom this breaks:

- A `DirectByteBuffer` cached per *virtual* thread is bound to whatever carrier was mounted at first
  use. When the vthread migrates, writes land on the wrong carrier (misattribution — the
  "split-context" problem).
- Worse: when the original carrier's OS thread exits, its `ProfiledThread` is `delete`d
  (`thread.cpp` `freeKey`), freeing the record. The dangling buffer keeps being written — a
  **use-after-free** into memory the JVM has reused, observed as a SIGSEGV in
  `ThreadsSMRSupport::free_list`.

**What shipped (`94686da`, PROF-15271):** context storage was moved to
`jdk.internal.misc.CarrierThreadLocal`, so a mounted vthread resolves to its *current* carrier's
record per call. This eliminates the steady-state misattribution and shrinks the UAF window.

**Why it's incomplete:** there is still a TOCTOU window between resolving the buffer and the write
completing. Today that window is effectively closed on the write path (the writes are plain
`ByteBuffer` ops with no yield point, and JDK 21 does not preemptively unmount vthreads at arbitrary
safepoints). But it reopens if/when Loom adds general preemptive scheduling — which is on the
roadmap. We want a fix that is correct by construction, not one that depends on current scheduler
behavior.

---

## 2. Core insight

Two observations reframe the problem:

1. **Crash-safety is about record *lifetime*, not write *timing*.** A write landing on the "wrong"
   carrier is only misattribution (non-fatal). The *only* fatal case is writing into a record whose
   backing `ProfiledThread` has been freed. So the fix must ensure the write never targets freed
   memory — either by never freeing it (arena) or by resolving a live target at write time (native).

2. **A native frame pins a mounted virtual thread to its carrier.** JDK's freeze logic returns
   `freeze_pinned_native` the moment it walks onto a native/JNI frame
   (`continuationFreezeThaw.cpp`). So *while a JNI call executes, the vthread cannot unmount* — not
   by voluntary yield, not by forced preemption. A native method that resolves
   `ProfiledThread::current()` and writes the record therefore targets the **live current carrier**,
   with no cached pointer and no migration window. Race-free by construction.

This is why "all-native" is not just a performance question — it is the *most correct* design: it
removes the cached-buffer concept that caused the bug.

---

## 3. Options considered

| Option | Idea | Verdict |
|---|---|---|
| **A. Arena records** | Allocate records from a slab never returned to the allocator; `freeKey` recycles a slot instead of freeing memory. Stale writes then hit valid profiler memory (UAF → bounded misattribution). | Viable fallback. Keeps the fast zero-JNI DBB writes and is crash-safe with **no tracer change** — but adds an allocator (the "buffer management" we want to avoid) and keeps `CarrierThreadLocal`. |
| **B. All-native writes** | Every context write is a JNI call that resolves the current carrier (pinned by the native frame) and writes in C. | **Recommended.** Race-free by construction; deletes the DBB/CTL/reflection subsystem. Net perf win with a combined API (§4–5). |
| **C. JVMTI mount/unmount events** | Use `VirtualThreadMount/Unmount` extension events to refresh a cached buffer on mount. | Rejected. Cannot close the TOCTOU (the event can't reach a value already loaded into a Java frame), and enabling `can_support_virtual_threads` imposes a process-wide slow-path tax on *all* vthread transitions. |
| **D. In-buffer handshake** | A lock/generation word in the record; writer acquires it, `freeKey` waits for release before freeing. | Rejected. The lock lives in the memory being freed (bootstrap UAF: you can't safely touch the lock to learn the object is dead), and making `freeKey` wait converts the safety bug into a liveness stall under preemption. Collapses into "A + seqlock." |
| **E. Reflective pinning** (`disableSuspendAndPreempt`) | Borrow the JVM's own `notifyJvmtiDisableSuspend` + `Continuation.pin` to make the write critical-section unmount-proof. | Rejected. `notifyJvmtiDisableSuspend` is a private, boolean-**toggle**-with-assert (not a nesting counter) — driving it from outside `java.lang` risks corrupting per-thread VM state; unstable internals; per-call overhead on a hot path. |

Option B is chosen because it is simultaneously the most-correct (native-frame pinning), the
lowest-maintenance (deletes code rather than adding an allocator), and — per the benchmarks — at
least perf-neutral on the real production surface.

---

## 4. Benchmark evidence

Full campaign: JDK 21 (`21.0.10`), glibc linux-x64, JMH `AverageTime` ns/op, 3 forks × 3+3 iters,
carrier vs thread storage mode confirmed per fork (no silent fallback). Prototypes are
benchmark-only (`*Native0` methods, not wired into the production API). Numbers are carrier mode
unless noted; treat as order-of-magnitude (per-fork JIT variance is ~1–6 ns on the sub-50 ns paths).

**Component costs (corrected from initial estimates):**

- `CarrierThreadLocal.get()` ≈ **3.9 ns** (plain `ThreadLocal` ≈ 3.3 ns) — the lookup is cheap, not
  the ~10–25 ns first guessed. Carrier-scoping added ~no per-call cost.
- A Java→native JNI transition ≈ **~15 ns** (backed out from the scalar native path). So a
  transition is *more* expensive than the TL lookup, not less.
- The DBB `setContext` *write* ≈ **18.8 ns** — ~30 bounds-checked `ByteBuffer` ops + 2 fences. This
  (not the lookup) is where the DBB scalar cost lives.

**Path-by-path (DBB vs all-native):**

| Path | DBB | all-native | Verdict |
|---|---|---|---|
| scalar `setContext` (per span) | ~30 | ~27 | native wins ~11% |
| single `setContextAttribute` (cache hit) | **28.5** (zero-JNI) | 59.0 | native **loses ~2.1×** |
| single `clearContextAttribute` (fair) | **9.4** (zero-JNI) | 21.0 | native **loses ~2.2×** |
| batch reapply, 5 attrs, per-slot | 337 | 480 | native loses (object-array JNI) |
| batch reapply, 5 attrs, **flattened** | 337 | **81** precomp / 109 rebuild | native wins **3–4×** |
| `snapshot`+`restore` (688 B pair) | **45** (inlined memcpy) | 137 | native **loses ~3×** |
| **combined activate+deactivate cycle** | **138.5** | **128.3** | **native wins ~7% (carrier), ~10% (thread)** |

Sub-results for the combined cycle: native *activate* alone loses (105.8 vs 73.5 — one combined call
vs 3 zero-JNI writes), but native *deactivate* wins decisively (~22 ns for one `clearFullContext` vs
~65 ns for `setContext(0,0,0,0)` + 2× `clearContextAttribute`); the full cycle nets in native's
favor. vthread mirrors platform (native 131.3 vs DBB 140.8), with a ~1–3 ns mount penalty; native is
mount- and mode-independent throughout.

**The unifying principle (holds across all six classes):**

> All-native **wins** when one JNI call replaces *multiple* DBB operations; it **loses** when it adds
> a JNI transition to a *single* operation the DBB already does zero-JNI.

This is why batching matters: the per-activation context (4 longs + a couple of named attributes) is
a natural batch, so one combined native call amortizes the transition and beats the fine-grained DBB
sequence. Conversely, `snapshot/restore` is already a single inlined `memcpy` on the DBB side, so
native can only add cost there — but (see §6) that path is unused in production.

---

## 5. Proposed design

**Make context writes all-native, and expose a combined per-activation API.**

Production per scope activation/deactivation (verified in §6) is:

- activate: `setContext(rootSpan, span, trHi, trLo)` + `setContextValue(spanName)` +
  `setContextValue(resourceName)`
- deactivate: `setContext(0,0,0,0)` + 2× `clearContextValue`

Replace this fine-grained sequence with two batched native calls. The activation attributes are a
*variable, config-derived* set, so the API must not hardcode which/how many attributes there are:
dd-trace-java's attribute list is configurable (`orderedContextAttributes` = the `attributes=`
config plus appended `operation`/`resource`), and the operation/resource **slot offsets come from
`offsetOf(...)`, not fixed indices**. Today activation writes exactly two span-derived attributes
(operation + resource — the only values available from the `ProfilerContext`; other configured
attributes like `http.route` are set outside activation by instrumentations and are wiped per
activation so they don't leak between spans). So the combined call carries the scalar context plus a
small set of `(offset, value)` pairs:

```
// activate: one JNI call writes scalar context + N span-derived (offset,value) attributes,
// under one detach/attach. Explicit-arity overload for the common case avoids per-call allocation:
void setTraceContext(long rootSpanId, long spanId, long traceIdHigh, long traceIdLow,
                     int off0, CharSequence val0, int off1, CharSequence val1);
// deactivate: one JNI call clears
void clearTraceContext();
```

- **Do not** hardcode `spanName`/`resourceName` or their slots — pass explicit offsets (the tracer
  gets them from `operationNameOffset()`/`resourceNameOffset()`), so the API tracks the configurable
  attribute model and survives a future third span-derived attribute (service, span kind).
- **Avoid per-activation allocation.** Prefer allocation-free explicit-arity overloads (the 2-pair
  form above matches today exactly) over a naive `int[]`/`Object[]` variant, which would add GC
  pressure on the activation hot path. If the span-derived attribute count ever grows past what
  overloads cover, add a general array form backed by a tracer-reused scratch buffer.
- The `CharSequence → (encoding, utf8)` value cache (today inside `ThreadContext`) moves to a small
  Java-side helper in `java-profiler` that resolves each value and invokes the native call — keeping
  the OTEP record layout and the cache encapsulated; the tracer passes offsets + values.
- App-driven, sporadic attributes (e.g. `http.route`, set by instrumentations after activation)
  keep a single-attribute native setter. This is the one path where native is ~2× the zero-JNI DBB
  write — accepted because it is *not* per-activation (see §7).
- Reads (`getSpanId`, etc.) become JNI calls (~20 ns) — fine, they are cold/test-only (§6).
- The sampler is unchanged: it already reads the native record directly, not via the DBB.
- The OTEP record layout and the `otel_thread_ctx_v1` discovery symbol are unchanged, so external /
  eBPF readers are unaffected.

Why combined rather than keeping the fine-grained API all-native: the benchmarks show the
fine-grained all-native cycle regresses ~1.6× (~6 transitions/cycle), while the combined cycle wins
~7–10% (2 transitions/cycle). Batching is what makes all-native a win rather than a regression.

---

## 6. Consumer audit (de-risking removal)

Callers of the public context API were enumerated across `java-profiler` (all modules) and
`dd-trace-java`. Result:

- **Exactly one production consumer:** the dd-trace-java bridge
  (`DatadogProfilingIntegration` / `DatadogProfiler` / `ContextSetter`), which calls only
  `setContext(4-arg)` and single `setContextValue`/`clearContextValue`.
- **No other production consumers** in either repo. No in-repo non-Datadog consumers. Classes live
  in `com.datadoghq.profiler`; the jar is bundled into `dd-java-agent` (no `module-info` exports
  found).
- **Verified unused by production** (contradicting an earlier automated pass): the batch setter
  `setContextAttributesByIdAndBytes` (grep-empty outside tests), `DatadogProfiler.snapshot()` (the
  `int[]` tag snapshot — no production callers), and `ThreadContext.snapshot/restore` + java-profiler's
  `ScopeStack` (dd-trace-java has its own `ScopeStack` and re-derives parent context by re-calling
  `setContext`; it never calls the profiler's snapshot/restore).
- **Test/benchmark-only:** `getThreadContext`, `resetThreadContext`, `contextStorageMode`,
  `readContextAttribute`, `readTraceId`, `getSpanId`, `getRootSpanId`.

**Removal risk:** entirely internal Datadog coordination (java-profiler ↔ dd-trace-java). No
external breakage identified. Caveat: if `ddprof-lib` is published as a standalone Maven artifact
that external users could compile against, add a deprecation window as insurance (§7).

Consequence for the design: the `snapshot/restore` ~3× regression and the per-slot batch regression
are **moot** — neither path is on the production tracer surface. The only production paths that
matter are the ones the combined API covers, plus the sporadic single app-attribute.

---

## 7. Migration plan (expand → migrate → contract)

1. **Expand (java-profiler).** Add the all-native combined API (`setTraceContext` /
   `clearTraceContext`), the single-attribute native setter for app tags, and native reads,
   alongside the existing DBB APIs. Mark the DBB context methods `@Deprecated` pointing at the new
   API. Release. Additive and backward-compatible — bumping to this version changes nothing
   operationally.
2. **Migrate (dd-trace-java).** Switch `DatadogProfilingIntegration` to the combined API. Requires
   java-profiler ≥ the phase-1 version. **This is where the crash fix and the perf win land.**
3. **Contract (java-profiler).** Once all consumers are on the new API, delete the
   DBB / `CarrierThreadLocal` / `OtelContextStorage` subsystem (and, if desired, the unused
   `ScopeStack` / `snapshot` / `restore` / batch-setter). Breaking release, gated on a
   consumers-migrated confirmation.

**Sequencing notes / caveats:**

- **The crash fix lands in phase 2, not phase 1.** Phase 1 is purely additive; the UAF persists on
  the old DBB path until the tracer switches. Until then, carrier-scoping (`94686da`) remains the
  mitigation. If crash urgency is high, phase 2 is the milestone.
- **Coexistence is safe.** Old (DBB) and new (native) paths write the *same* underlying record; the
  native path ignores the DBB; the tracer switches wholesale, so no thread interleaves both. No
  dual-write coherence problem.
- **aarch64 memory model.** The native detach/attach uses a release fence + relaxed `valid` store,
  mirroring `Unsafe.storeFence` + plain put. Trivially equivalent on x86; verify on aarch64 before
  shipping the native path there.
- **Accepted minor regression.** Sporadic app-driven single attributes are ~2× the zero-JNI DBB
  write on native. They are not per-activation, so the absolute impact is small; not designed around.

---

## 8. Alternatives explicitly rejected (and why)

- **Keep DBB + arena (Option A)** — perf-optimal and crash-safe with no tracer change, but adds an
  allocator and keeps `CarrierThreadLocal`; contradicts the "no buffer management / most-correct"
  goal. Retain as the fallback if the tracer API cannot change.
- **Reflective JVM pinning (Option E)** — corrupts VM state risk (toggle-with-assert), unstable
  internals, hot-path overhead.
- **JVMTI mount events (Option C)** — cannot close the TOCTOU; global transition tax.
- **Fine-grained all-native (no combined call)** — measured ~1.6× per-cycle regression; batching is
  required.

## 9. Open questions / follow-ups

- Confirm `ddprof-lib` Maven publication policy (external-consumer risk for phase 3).
- Decide whether to also remove the unused `ScopeStack` / `snapshot` / `restore` / batch setter in
  phase 3, or retain for a possible future reapply-on-mount design (#11646).
- Re-run the combined-cycle benchmark on aarch64 and on a real dd-trace-java workload (chaos harness
  under a patched `dd-java-agent`) to validate the ~7–10% win outside the microbenchmark.
- Split-context coherence (#11646) remains a separate tracer-side concern; this change makes it safe
  but does not address it.

## Appendix: benchmark classes

All under `ddprof-stresstest/src/jmh/.../throughput/` (benchmark-only; run with
`./gradlew :ddprof-stresstest:jmh -PjmhInclude="<Class>"`):
`ContextWritePathBenchmark`, `ContextAttrBenchmark`, `ContextVThreadBenchmark`,
`ContextScopeBenchmark`, `ContextSingleAttrBenchmark`, `ContextCombinedBenchmark`. Native prototypes
live in `ddprof-lib/src/main/cpp/javaApi.cpp` (`*Native0`) with wrappers in `JavaProfiler.java`.
