# Patentability Memo: The Interruptible Heap Walker

**Prepared for:** Datadog IP / patent counsel
**Prepared by:** Engineering (profiler team)
**Subject:** Technical novelty / prior-art assessment of the "interruptible heap walker" in the Datadog Java Profiler's reference-chains feature
**Status:** Internal working draft for counsel review. This is an engineer's technical read, **not** legal advice. Counsel must run a formal prior-art search (PatentScope, Espacenet, USPTO PPUBS, non-patent literature) and do claim construction before any filing decision.

---

## Part 1 — The problem space

You know the shape of this already, so this is a short orientation, not a tutorial. I include it only so the rest of the memo has shared vocabulary.

### 1.1 What we are building

A production, in-process Java profiler that, for objects suspected of leaking, reconstructs a **reference chain** (a path of references from a GC root down to the suspect object) — and does so continuously, in a live customer JVM, without imposing an unacceptable stop-the-world (STW) pause.

### 1.2 Why this is hard

Building a reference chain requires a **heap walk**: starting at the GC roots, following references outward, searching for the target object. On a real production heap (tens of millions of objects), a full walk inside a single STW pause can take hundreds of milliseconds to seconds. That is unacceptable for a continuous production profiler — it causes latency spikes, failed health checks, and visible disruption.

The naive single-freeze approach (what a heap dump does) is a non-starter in production. Even the closest existing system — OpenJDK's built-in JFR leak profiler (`jdk.OldObjectSample`) — runs its chain search as **one single walk inside one STW pause**, bounded by a wall-clock timer. When the timer fires, it **stops and discards the partial work**. It does not resume. This is the single most important piece of prior art; we return to it in Part 3.

### 1.3 The specific obstacle to pausing and resuming

The obstacle is the **moving/compacting GC**. A breadth-first walk keeps a **frontier**: the set of objects reached but not yet expanded. Between two passes, the GC can **relocate** objects (compacting collectors move them to new addresses) or **collect** them (if they became unreachable). If the frontier were a set of raw addresses, a GC between passes would invalidate it — addresses would point at moved or dead objects. You could not resume.

That is the problem our invention solves.

---

## Part 2 — The invention

One sentence:

> **Instead of one long STW walk, we break the walk into many short, independently-bounded passes, and we persist the frontier across passes using JVMTI object tags — stable identities that survive a moving GC — so we can resume exactly where we left off, with dead branches pruned automatically.**

Six mechanisms make it work. Only the first is a strong novelty candidate; the rest are supporting machinery, and I say so plainly.

### 2.1 Mechanism 1 (the heart): a tag-persisted frontier across GC cycles

We keep the frontier as a table keyed by **JVMTI object tags**, not raw addresses. A tag is a 64-bit identity attached to an object through the JVMTI interface. Two properties make this work:

1. **Tags move with the object.** A tag is an identity, not an address. If the GC relocates the object, the tag still resolves to it. So a tag-keyed frontier stays valid across a moving GC.
2. **Tags are non-retaining.** Tagging an object does not keep it alive — the GC may still collect it. (We must not cause leaks ourselves.)

The frontier table — `(tag, parent_tag, referrer_class, depth)` records — lives in our own native memory between passes. On the next pass, we resolve the tags to live objects. Any tag whose object was collected simply fails to resolve; that branch of the search prunes itself for free, with no separate liveness tracking.

**This is the key novelty candidate.** We did not find prior art that persists a graph-walk frontier as JVMTI object tags across multiple GC cycles to resume a heap walk on a moving heap. The closest art (JFR) stores raw addresses and discards the frontier on timeout.

### 2.2 Mechanism 2: cooperative abort from another thread

We sometimes must stop an in-flight walk immediately (profiler shutdown/reconfig). A started heap walk cannot be interrupted by an external signal; the JVM keeps invoking our per-object callback until the walk finishes or the callback says stop. So we use an atomic flag set by the shutdown thread and checked by the callback on every object; on seeing it set, the callback returns the JVMTI "abort" value, ending the walk within one callback.

Standard cooperative cancellation. Supporting machinery, not a novelty hook — the abort return value is JVMTI-spec-taught.

### 2.3 Mechanism 3: in-callback wall-clock deadline

The callback also checks a per-pass deadline periodically (every 4096 invocations) and aborts when over budget, bounding each pass's STW time regardless of heap size.

**Prior-art note:** this exact pattern (periodic counter + time check inside a heap-walk callback, abort when over) already exists in the OpenJDK JFR leak profiler, in `granularTimer.cpp`, copyright **2014**. We read the source. This mechanism is **anticipated by shipping code** — not novel.

### 2.4 Mechanism 4: array-holder batching (one walk per BFS level)

Naively, expanding the frontier one step means one heap walk per frontier object — each a separate STW operation with fixed overhead. Instead, we build a Java `Object[]`, place a batch of frontier objects in it, and issue one `FollowReferences` over the array as the starting point. One STW walk expands a whole BFS level. The callback is gated to descend only one hop past the batch.

Engineering optimization, "obvious to try" risk. Not a standalone novelty hook.

### 2.5 Mechanism 5: reverse-fill + rolling-resume cursor

When a pass is cut off mid-batch, we want to resume at the exact object we were inside, not redo the batch. We exploit a HotSpot implementation detail: `FollowReferences` visits an array's elements in LIFO order. We fill the holder in **reverse**, so the LIFO visit yields objects in **ascending** original order, giving the resume cursor a clean meaning: "got through 0..k; resume at k." We track the batch entry being visited at abort time (`_last_visited_batch_tag`) and resume there; already-processed entries are marked done, the partial entry is redone idempotently.

Narrowest, cleverest piece. Not found in art as a specific combination. But the generic "checkpoint and resume at last reachable point" is known (US10365963, below), which weakens obviousness. Best as a dependent limitation.

### 2.6 Mechanism 6: dead-branch self-pruning

A consequence of tag-keying: frontier objects collected between passes fail to resolve and are dropped, with no separate liveness bookkeeping. Natural consequence of the JVMTI tag spec (tags are non-retaining, cleared on collection). Spec-taught, likely obvious. Supporting machinery.

---

## Part 3 — Prior art (read, not just searched)

This is a starting point, not an exhaustive search. We used web search plus reading of source code we have locally. A formal search in PatentScope / Espacenet / USPTO PPUBS / non-patent literature is still required.

### 3.1 OpenJDK JFR leak profiler — closest art, shipping

Source read locally: `src/hotspot/share/jfr/leakprofiler/chains/` (`bfsClosure.cpp`, `edgeStore.cpp`, `edgeQueue.hpp`, `granularTimer.{hpp,cpp}`, `pathToGcRootsOperation.cpp`).

What it does:
- BFS from GC roots, hop cap, parent links in an `EdgeStore` for chain reconstruction. This is the structural template our own design doc cites as the starting point.
- Wall-clock bounded: `GranularTimer` (copyright **2014**) decrements a counter per iteration and checks the time; `BFSClosure::closure_impl` checks `if (GranularTimer::is_finished()) return;` per edge. **This is the same pattern as our mechanism 3.** → Mechanism 3 is anticipated by shipping code from 2014.

What it does **not** do (the gaps we fill):
- Its `EdgeQueue` stores raw `UnifiedOopRef` addresses and raw `const Edge*` parent pointers — **not** JVMTI tags. Raw addresses do not survive a moving GC.
- The entire BFS runs inside one `PathToGcRootsOperation::doit()` asserting `SafepointSynchronize::is_at_safepoint()`. When the timer fires, `process_queue()` returns and the `EdgeQueue` (a local) is destroyed. **Frontier discarded. No resume, no cross-GC persistence, no multi-pass walk.**
- No cooperative abort from another thread (it is single-pass, timer-bounded).
- No array-holder batching.

### 3.2 Oracle US10635570B2 / US20190102278A1 — "Memory leak profiling events"

Inventors: Erik Gahlin, Marcus Hirt (the JFR authors). Priority 2017-09-29, granted 2020-04-28, assigned to Oracle. Covers the JFR leak profiler's *sampling* side.

Claims: allocation sampling, a threshold-constrained priority queue, GC-triggered queue updates (removing dead samples, redistributing allocation span), and **a single BFS at dump time** to find the shortest path to a GC root.

Does **not** claim or describe: a resumable multi-pass walk, a frontier persisted across GC cycles, mid-walk interruption from another thread, or batched holder traversal.

→ Anticipates the *sampling + single dump-time BFS* concept (overlaps our candidate-selection side), but leaves the entire *interruptible/resumable walk* delta untouched. Most likely to be cited against our sampling parts; does not cover walk interruption.

### 3.3 US10365963B2 — "Accessing damaged heaps using combined linear heap slot based and object graph walking"

Post-mortem walk of a **crashed/dead** heap with corrupted regions; resumes at the nearest reachable slot after damage. Teaches generic "store last reachable point and resume."

Off-point for our core novelty: the heap is static (dead process, no moving GC, no live collection between passes); it is about corruption robustness, not live STW bounding. Relevant only as generic checkpoint-resume prior art, which weakens obviousness for our cursor pieces (4, 5) but does not teach the tag-persisted frontier across live GCs (1).

### 3.4 Other patents checked, ruled out

- **US7971010B2** "Loitering trace" — sampling of GC survivors, not a resumable walk.
- **US20100223433A1**, **US11221947B2** — traversal *inside* the GC itself (collector internals, not an external attached agent).
- **US6286016B1** — incremental heap *expansion* (sizing), not traversal.
- **US8543987B2** — GC + profiler allocation callbacks, not a resumable walk.

### 3.5 Non-patent art checked

- **async-profiler "live mode" (2.9+)** — allocation sampling + LRU live-object tracking. No resumable `FollowReferences`, no tag-persisted frontier.
- **.NET gcdump** — single induced GC walks live objects, emits events inline. Not resumable across passes.
- **Eclipse MAT / IBM HeapAnalyzer** — offline heap-dump analysis, not live.
- **JVMTI specification** — documents the abort return value and that tags are identity-based, GC-move-transparent, non-retaining (cleared on collection). These spec-taught facts feed obviousness against mechanisms 2 and 6.

---

## Part 4 — Per-mechanism novelty verdict

| # | Mechanism | Prior art | Novelty |
|---|---|---|---|
| 1 | Resumable BFS via tag-persisted frontier across GCs | JFR discards frontier; Oracle patent single-pass; US10365963 dead heap | **Not found — strongest candidate** |
| 5 | Reverse-fill + rolling-resume cursor (exploit HotSpot LIFO visit order) | Not found; US10365963 teaches generic checkpoint-resume | Narrow, cleverest; some obviousness exposure |
| 4 | Array-holder batching (one walk per BFS level) | Not found | Engineering opt; "obvious to try" risk |
| 3 | In-callback wall-clock deadline | **JFR `GranularTimer` (2014)** — same pattern | **Anticipated** |
| 2 | Cooperative abort (atomic flag + callback + abort return) | Abort value is spec-taught; cooperative cancellation textbook | Weak, likely obvious |
| 6 | Dead-branch self-pruning (tags vanish on GC) | JVMTI spec (tags cleared on collection) | Spec-taught, likely obvious |

---

## Part 5 — Assessment and recommendation

### What is most likely patentable

The one piece that survives the closest art is **mechanism 1: persisting the BFS frontier as JVMTI object tags so the walk resumes across GC cycles on a moving heap.** Neither the shipping JFR leak profiler (raw addresses, single STW, frontier destroyed on timeout) nor the Oracle JFR patent (single dump-time BFS) nor US10365963 (post-mortem dead heap) teach this.

Mechanisms 4 and 5 (batched holder + reverse-fill resumable cursor) are also not found in the art, but are engineering optimizations with "obvious to try" exposure, and US10365963's generic checkpoint-resume weakens them. Best as **dependent limitations** narrowing an independent claim built around mechanism 1, not as standalone inventions.

### What is not patentable / weak

- Mechanism 3 (in-callback deadline) is anticipated by JFR's `GranularTimer` (2014).
- Mechanisms 2 and 6 are spec-taught or textbook.

### Risks counsel should weigh

1. **§101 / Alice.** Software on a generic JVM doing "incremental graph traversal with checkpoints." Post-Alice, survival is best when tied to a *specific technical improvement to the computer itself*, not "do the known thing in smaller chunks." Our design doc's own framing — "trading one long pause for several short ones … a latency-distribution improvement, not a total-STW reduction" — is a *performance optimization*, the weakest category post-Alice / *Enfish* / *Berkheimer*. Consider framing the tag-persisted frontier as a *specific technical mechanism* (identity-based, GC-move-surviving tags solving a concrete moving-heap problem) rather than an abstract "resume a search in pieces."

2. **Obviousness.** The primitives (tags, abort, BFS, batching, checkpoints) are each known. Novelty is in the *specific combination* for moving-heap resumption. Assess "obvious to try" under KSR, and whether the tag-persisted-across-GC frontier is a non-obvious specific solution.

3. **Disclosure cost.** Filing publishes the reverse-fill trick and the tag-frontier design. If the patent is later rejected or narrowed, we disclose engineering cleverness for limited protection. Weigh trade-secret on the batching/resume trick against a likely-narrowed patent.

### Suggested next step for counsel

- Run a focused search on the strongest claim: **"persisting a graph-traversal frontier as object identity tags that survive a moving/compacting GC, to resume an incremental heap walk across GC cycles on a live JVM."** Search terms: "resumable heap walk", "tag-persisted frontier", "incremental reachability across GC", "object tag resume", "multi-pass heap traversal moving collector". Targets: PatentScope, Espacenet, USPTO PPUBS, Google Patents full text, non-patent literature (incremental/graph-traversal profiler papers, IBM/OpenJ9 tooling docs, OpenJDK JFR history).
- If it clears, consider an independent claim around mechanism 1, with mechanisms 4 and 5 as dependent limitations; **avoid** claiming mechanism 3 (anticipated) or 2/6 (spec-taught) as standalone.
- Do **not** rely on the broad framing "interruptible/resumable heap walking with bounded pauses" — JFR + the Oracle patent likely render that obvious, and §101 will bite.

---

## Appendix A — Code locators

- Implementation: `ddprof-lib/src/main/cpp/referenceChains.cpp` and `referenceChains.h`. The interruptible heap walker is the `ReferenceChainTracker` class; key methods `runPass`, `expandFrontier`, `admitStaticFieldRoots`, `heapReferenceCallback`.
- Design docs: `doc/reference-chains-design.md`, `doc/reference-chains-collection-summary.md`.
- Closest prior art (OpenJDK JFR leak profiler): `src/hotspot/share/jfr/leakprofiler/chains/` in the OpenJDK repo — `bfsClosure.cpp`, `edgeStore.cpp`, `edgeQueue.hpp`, `granularTimer.{hpp,cpp}`, `pathToGcRootsOperation.cpp`.

## Appendix B — Prior-art references

| Reference | Number / location | Relevance |
|---|---|---|
| OpenJDK JFR leak profiler (shipping) | `src/hotspot/share/jfr/leakprofiler/chains/` | Closest art; anticipates mechanism 3 (`GranularTimer`, 2014); does not teach resumable tag-frontier |
| Oracle "Memory leak profiling events" | US10635570B2 / US20190102278A1 (priority 2017-09-29, granted 2020-04-28; Gahlin & Hirt) | Anticipates sampling + single dump-time BFS; leaves resumable walk untouched |
| "Accessing damaged heaps …" | US10365963B2 | Generic checkpoint-resume on a dead heap; off-point for live tag-frontier |
| "Loitering trace" | US7971010B2 | Sampling of GC survivors; off-point |
| JVMTI specification | Oracle JVMTI 1.2.3 / 11 | Teaches the abort return value; tag identity / move-transparency / non-retention |
