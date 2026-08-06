# Reference Chain Collection: Design Summary

## Problem

Given a JVM heap with objects suspected of leaking (e.g., klasses whose live population grows monotonically across GC generations), reconstruct a **referrer chain** from a GC root down to a representative instance of the suspect klass — without pausing the JVM for longer than a small, bounded budget, and without assuming the entire heap graph can be walked in one pass.

Three constraints drive the design:

1. **Detecting *which* klasses are worth walking** must be near-free and based on survivorship trend, not raw allocation volume.
2. **The walk itself** (JVMTI `FollowReferences`) can be arbitrarily expensive on a large heap, so it must be interruptible and resumable.
3. **Total STW/JVMTI-callback time per pass** must stay under a small budget so the profiler doesn't visibly perturb the target application.

---

## Component 1: Surviving-Generation Signal (`LivenessTracker`)

Rather than triggering a heap walk on every allocation or every GC, the tracker maintains a **per-klass population history** and only nominates a klass as a "leak candidate" once it shows a **sustained positive trend across GC generations** — i.e., its live (surviving) instance count keeps growing generation over generation, not just spiking transiently.

**Mechanics:**

- Population sampling is driven off the existing allocation-sampling hot path (`track()`), but the actual **per-klass counts are only folded into history at `cleanup_table()`'s GC-epoch-advance pass** — i.e., once per GC, not once per allocation. This keeps the hot path allocation-free and cheap.
- Each klass gets a small **ring buffer of recent per-epoch surviving counts** (`KLASS_POPULATION_RING_SIZE = 30` samples). A ring, not an unbounded history, because we only care about recent trend, not lifetime totals.
- A klass's trend is only trusted once its ring has a **minimum fill (`KLASS_POPULATION_MIN_FILL_FOR_TREND = 10` samples)** — avoids false-positive trend detection on a klass that's simply new to being tracked (too few points to fit a slope to).
- `selectLeakCandidates()` computes a slope over each ring and returns the **top-N klasses by slope magnitude** (`MAX_LEAK_CANDIDATES = 5`), each paired with a live representative instance (a `jweak`) discovered during sampling — this weak reference is what seeds the walk in Component 2.
- A klass only qualifies once its growth (`hasQualifyingGrowth()`) has held for `consecutive_positive` epochs at or above a **hysteresis threshold** — `LEAK_TREND_HYSTERESIS_BASE = 5` by default, lowered to `LEAK_TREND_HYSTERESIS_CORROBORATED = 3` when the aggregate post-GC heap floor is itself rising (`heapFloorRising()`, fed by a lock-free, single-writer `_heap_floor_ring` populated from `onGC()`). Because the aggregate heap-floor signal can't attribute growth to any one klass, it only ever raises or lowers the bar uniformly for the whole scan — it never reorders or singles out individual candidates.
- The whole table (`_klass_population`, up to `MAX_KLASS_POPULATION_ENTRIES = 256` entries) is a flat array scanned linearly — deliberately no index structure, since 256 entries is cheap to scan and this stays off the allocation hot path.
- Everything under this table (population array, size counter) is guarded by a single `SpinLock` (`_table_lock`) — the *same* lock `cleanup_table()` already holds for its epoch-advance pass, rather than adding a second lock. **Any code path that mutates this table (including test-only reset seams) must take that lock — mutating `_klass_population_size` or the array unguarded is a data race against the epoch-advance pass**, discovered in practice while hardening test seams.

**Why this design:** it decouples "is this klass suspicious" (cheap, GC-cadence, statistical) from "reconstruct why it's suspicious" (expensive, JVMTI, on-demand) — the expensive walk only ever runs against klasses that have already earned a positive trend signal, not against every allocation site.

---

## Component 2: Resumable Frontier Walk (`ReferenceChainTracker`)

Once a klass is nominated, a **persistent background BFS thread** reconstructs a path from a GC root to a tagged instance of that klass, using JVMTI's `FollowReferences`/heap-tag mechanism — but broken into many small, budgeted passes rather than one unbounded walk.

**Mechanics:**

- The tracker is a **process-wide singleton** with its own thread (`threadLoop()`), woken on a fixed cadence (`effectiveCadenceNs`) rather than synchronously from allocation or GC callbacks — decouples walk progress from the rate of GC/allocation events.
- `runPass()` dispatches on `_search_started`:
  - **First pass for a search**: does a real root-seeded `FollowReferences(0, nullptr, nullptr, ...)` call — full JVMTI heap-root walk, tagging objects as it goes.
  - **Every subsequent pass**: calls `expandFrontier()`, which resumes from a **persisted frontier** (the previous pass's boundary tags) instead of re-walking from roots. This is the resumability mechanism: each pass advances the frontier outward by one bounded increment and stops.
- Each pass is capped by an **edge-admission budget** (`effectiveBudget`, e.g. `edges_admitted` capped at a configured value like 4000/200000/500 depending on test config) — `expandFrontier()`'s nested loops (`while (!ctx.truncated && progress)` outer, `for (jlong tag : candidate_tags)` inner) both check a truncation flag and bail out the moment the budget is exhausted, so a single pass's JVMTI-callback time is bounded regardless of heap size.
- **Cooperative abort**: an `std::atomic<bool> _abort_pass_requested` flag, checked inside `heapReferenceCallback()` (the JVMTI callback invoked per edge), lets `stopThread()` interrupt an **in-flight** walk promptly — set before `pthread_kill(WAKEUP_SIGNAL)`/`pthread_join()`, cleared by `startThread()`. Without this, a `FollowReferences` call already in progress at JVM shutdown or profiler restart can't be interrupted, and `pthread_join()` blocks indefinitely (a real, previously-diagnosed shutdown hang).
- Search state is a small state machine: `RUNNING → {ABANDONED | COMPLETED}`. `RUNNING` can **restart itself** (fresh root walk) once a candidate's chain is found and its tags released, gated by `canAffordNewSearch()`'s **pacing budget** — self-throttling, not unconditional: a search won't restart back-to-back if it would blow the perturbation budget. Once a search reaches a terminal state (`ABANDONED`/`COMPLETED`) it stays there — restarts only happen from within `RUNNING`.
- A search is marked `ABANDONED` (with a reason code) if it runs out of frontier budget without completing — e.g. hitting a frontier-cap under a tiny configured budget. This is a deliberate, observable outcome, not a silent failure — surfaced so operators can distinguish "the walk gave up" from "the walk is still in progress."

**Why this design:** treating the walk as a resumable state machine (persisted frontier + tags) rather than one atomic call means a heap graph of unbounded size never forces an unbounded pause — cost is amortized across many cheap passes, each individually bounded and individually abortable.

---

## Component 3: Latency Budget Enforcement

The system enforces its "don't perturb the app" guarantee at **three independent layers**, not just one:

1. **Per-pass edge budget** (`effectiveBudget`) — caps JVMTI callback invocations per pass (Component 2).
2. **Pain budget** (`_pain_budget`/`_search_pain_ms`, spent via `_pain_budget.spend(...)`) — tracks cumulative walk cost against a wall-clock ceiling; used by `canAffordNewSearch()` to decide whether a new search/restart is affordable right now, not just whether the current pass fit its edge budget. This is what prevents "many cheap passes" from silently adding up to an expensive aggregate cost.
3. **Pass cadence** (`effectiveCadenceNs`) — the background thread only wakes and attempts a pass on a fixed cadence (plus GC-epoch-triggered wakeups), rather than continuously spinning, bounding CPU overhead between passes.

Together these mean: a single pass is bounded (edge budget), a sequence of passes is bounded (pain budget), and idle overhead between passes is bounded (cadence) — the three layers target three different ways an unbounded-cost walk could otherwise leak into the target application's latency.

---

## Output Path

Once a candidate's chain is fully reconstructed, `pollWatchedTargets()` builds a chain event (`buildChainEvent()`), which is enqueued (`enqueueChainEvent()`) and later drained (`drainPendingChainEvents()`, called from `Profiler::dump()`, not from the BFS scheduling thread) into `Profiler::writeReferenceChain()` — ultimately surfaced as a `datadog.ReferenceChain` JFR event on the next `Profiler::dump()`. This keeps the expensive walk and the (comparatively cheap, already-existing) JFR-write path decoupled — the walk never blocks on JFR I/O, and JFR writes never trigger a walk.
