# Implementation Plan: Reference Chains for Surviving Live Heap Samples

**Status:** Implementation plan (companion to the design proposal)
**Date:** 2026-07-07
**Jira:** [PROF-15341](https://datadoghq.atlassian.net/browse/PROF-15341)
**Design doc:** [LiveHeapReferenceChains.md](LiveHeapReferenceChains.md) — read that first; this document
does not re-derive or re-justify the design decisions, it sequences the work and pins each
step to concrete files.

## Scope reminder

This plan implements the "Chosen design" section of the design doc: an incremental,
resumable, bounded BFS over the JVMTI heap graph, using JVMTI object tags for frontier
identity and a `LivenessTracker`-style slot table for per-tag metadata
(`parent_tag`, `referrer_klass`, `depth`). Passes are executed by an agent-owned thread
calling `FollowReferences`/`IterateThroughHeap` (which pays its own transparent
safepoint); `GarbageCollectionFinish` is only a scheduling signal. Non-goals from the
design doc (exhaustive all-roots paths, field-level chains, GC-closure hooks,
`ParallelObjectIterator`) are out of scope here too.

Everything below is new code — the design doc's own gap analysis (integration-point
research) found **no existing precedent** for a `GarbageCollectionStart` callback or for
tag-based `FollowReferences`/`IterateThroughHeap` frontier walking in this codebase.
Where a precedent *does* exist (capability requests, GC-signal wiring, slot-table
locking, JFR event definition, config flags, test harness), each phase below cites it
and reuses its shape rather than inventing a new one.

## Phased breakdown

Each phase is independently buildable/testable and produces a working (if incomplete)
increment. Phases are ordered by dependency, not by priority — do not skip ahead.

### Phase 0 — Config flag and scaffolding (no behavior yet)

**Goal:** wire up the on/off switch and empty subsystem shell so later phases have a
place to land code, without touching any hot path.

- Add a new arg, following the `_record_liveness`/`memory=` composite-flag pattern at
  `ddprof-lib/src/main/cpp/arguments.h` (~line 176-179) and
  `ddprof-lib/src/main/cpp/arguments.cpp` (`CASE("memory")`, lines 199-236): a boolean
  `_reference_chains` plus room for the Phase 5 tunables (budget, hop cap, TTL,
  frontier-size cap) as a colon-delimited sub-config, e.g.
  `referencechains=true:hops=64:budget=2000`. Exact key names/defaults are placeholders
  until Phase 5's measurement work fills them in (see Open Question 2 in the design doc)
  — Phase 0 only needs the flag to parse and default to **off**.
- Create `ddprof-lib/src/main/cpp/referenceChains.h` / `.cpp` with an empty
  `ReferenceChainTracker` class, Meyer's-singleton-owned exactly like `LivenessTracker`
  (`livenessTracker.h:77-80`): `static ReferenceChainTracker *instance()`. Stub
  `Error start(Arguments &args)` / `void stop()` that just read the flag and log
  enabled/disabled (`Log::info`-style, matching existing subsystem start logs).
- No Gradle changes needed — sources under `ddprof-lib/src/main/cpp/` are glob-picked-up
  (`ddprof-lib/build.gradle.kts:26`, confirmed no explicit file list exists).
- Add `ddprof-lib/src/test/cpp/referenceChains_ut.cpp` with a single smoke test
  (`TEST_F` + `installGtestCrashHandler`, matching `livenessTracker_ut.cpp:17-18,82`)
  asserting `start()`/`stop()` don't crash with the flag on/off. New `_ut.cpp` files are
  auto-discovered by the test glob (`doc/build/NativeBuildPlugin.md:365`).

**Exit criteria:** flag parses, subsystem starts/stops cleanly, one green gtest, no
JVMTI capability or callback changes yet.

### Phase 1 — JVMTI wiring: GC signal + tag lifecycle

**Goal:** get a cheap "a GC just happened" signal into `ReferenceChainTracker`, and
confirm tag assign/clear/resolve works end-to-end, before any BFS logic exists.

- `can_tag_objects` and `can_generate_garbage_collection_events` are **already
  requested** unconditionally at `vmEntry.cpp:477,484` — no capability changes needed.
- Add a `GarbageCollectionStart` callback. Today only `GarbageCollectionFinish` is wired
  (`vmEntry.cpp:502`, pointing at `LivenessTracker::GarbageCollectionFinish`); the
  `GarbageCollectionStart` slot in the same `jvmtiEventCallbacks callbacks` struct is
  currently unset. Add
  `callbacks.GarbageCollectionStart = ReferenceChainTracker::GarbageCollectionStart;`
  next to the existing line, and a `GarbageCollectionFinish` counterpart that chains to
  `ReferenceChainTracker::GarbageCollectionFinish` *in addition to* the existing
  `LivenessTracker` call (both subsystems need the Finish event; do not clobber the
  existing registration — dispatch to both from a single trampoline function, or check
  whether the callback table supports only one function pointer per event and wrap it if
  so — verify current single-slot behavior against `vmEntry.cpp` around line 502 before
  writing this callback, since only one function pointer wins today).
- Per the design doc's corrected mechanism, this callback does **only** the same
  cheap thing `LivenessTracker::onGC()` does today (`livenessTracker.cpp:415-426`):
  bump an atomic epoch/"GC happened" flag. It must **not** call `SetTag`/`GetTag`/
  `FollowReferences`/`IterateThroughHeap` — those are JVMTI Heap-category functions,
  disallowed inside this callback per the JVMTI spec (cited in the design doc's
  Triggering section). Enforce this with a comment and, if feasible, a debug-only assert
  that no Heap-category call happens on this call stack.
- Event enablement: follow `LivenessTracker::start()`'s lazy-enable pattern
  (`livenessTracker.cpp:194-196`) — call `SetEventNotificationMode(JVMTI_ENABLE, ...)`
  for both `JVMTI_EVENT_GARBAGE_COLLECTION_START` and `_FINISH` only when
  `ReferenceChainTracker::start()` runs with the flag on, not unconditionally at agent
  init.
- Add a minimal tag helper: `SetTag(obj, next_tag())` / `GetTag` / clear-on-abandon
  (`SetTag(obj, 0)`, per the design doc's Termination section). No frontier/table logic
  yet — this phase just proves tag round-tripping survives a GC (write a gtest that
  allocates an object, tags it, forces a GC, and confirms the tag is still readable via
  `GetObjectsWithTags`).

**Exit criteria:** GC-start/finish signal increments a counter; a tagged object's tag
survives a GC; no Heap-category JVMTI call happens inside either callback (verified by
code review, not just tests, since this is a spec violation with no runtime crash signal
on most JVMs).

### Phase 2 — Frontier metadata table (the `LivenessTracker`-pattern reuse)

**Goal:** build the tag-indexed slot table that stores `(parent_tag, referrer_klass,
depth)`, before any BFS logic uses it, so it can be tested in isolation.

- Per the design doc's "Frontier metadata storage" section, model this directly on
  `LivenessTracker`'s `TrackingEntry` (`livenessTracker.h:21-30`) and its CAS-based
  slot allocation / doubling resize (`livenessTracker.cpp:213-278,362-403`) and
  `SpinLock` locking (`livenessTracker.h:46`, `spinLock.h`). Key structural difference:
  the index is the **tag value itself** (assigned sequentially by this subsystem when a
  frontier object is first tagged), not a `jweak`-derived slot.
- New struct, e.g. in `referenceChains.h`:
  ```cpp
  typedef struct FrontierEntry {
    jlong parent_tag;
    jclass referrer_klass;   // or a resolved klass-name id, see below
    u32 depth;
    u8 state; // FRONTIER | EXPANDED | EDGE | ABANDONED — see Phase 3
  } FrontierEntry;
  ```
  Do **not** store a live `jclass`/`jobject` reference in the table — per the design
  doc's non-retention property, storing a strong reference here would defeat the whole
  point of using non-retaining tags. Store a resolved class-name string/symbol id
  (interned once, e.g. via this codebase's existing dictionary/symbol-interning
  mechanism — reuse it rather than adding a second string table; identify the exact
  class to reuse during this phase, e.g. `Dictionary`/`SymbolTable` if one already
  exists in `ddprof-lib/src/main/cpp/`) instead of a class handle.
- Do **not** copy `LivenessTracker`'s sizing formula (`max_heap / sampling_interval`,
  `livenessTracker.cpp:152-176`) — the design doc explicitly flags this as
  non-transferable (Open Question 2). Phase 2 should take an explicit capacity
  parameter (wired from the Phase 0 config flag) rather than deriving one, leaving the
  actual default to Phase 5's measurement work. Reuse the doubling-resize mechanics,
  not the sizing heuristic.
- Concurrency: a single agent thread drives BFS expansion (Phase 3), but table reads may
  race against tag-cleanup happening from an abandonment path. Reuse `SpinLock`'s
  shared/exclusive split (as `LivenessTracker` does) rather than inventing new locking.
- gtest coverage: insert/lookup/resize/clear round-trip, concurrent insert-while-resize
  (mirroring whatever concurrency tests `livenessTracker_ut.cpp` already has, if any —
  check and match its style), and a "capacity exhausted" path that reports (not crashes)
  per the design doc's frontier-size-cap requirement.

**Exit criteria:** table supports insert/lookup/clear/resize under concurrent access,
verified by gtest; no BFS logic yet.

### Phase 3 — Single-pass bounded BFS engine (no persistence across passes yet)

**Goal:** implement one BFS pass from GC roots to a fixed budget, using
`FollowReferences` (or `IterateThroughHeap` if that fits the referrer-only requirement
better — decide based on which JVMTI call actually gives referrer-class information at
lowest overhead; `FollowReferences` is the design doc's stated choice, mirroring JFR's
leak profiler, so start there) — but treat it as a single, non-resumable pass for this
phase, i.e. defer cross-pass frontier persistence to Phase 4. This isolates "does the
BFS/EdgeStore logic work at all" from "does resumption work," per the design doc's own
staging of Approach B before its incremental refinement.

- Thread: an agent-owned thread, not a JVM mutator. Reuse the `attachThread`/
  `detachThread` pattern (`vmEntry.h:191-197`) exactly as `J9WallClock` does
  (`j9WallClock.cpp:46,53-57,81`) for `pthread_create`/`pthread_kill`/`pthread_join`
  lifecycle, and `VM::attachThread("java-profiler ReferenceChains")` for
  `AttachCurrentThreadAsDaemon`. Confirm during implementation whether this thread needs
  a real `JNIEnv*` at all (JVMTI heap-walk calls take a `jvmtiEnv*`, not `JNIEnv*`) — if
  no JNI call is made from this thread (e.g. class-name resolution can go through
  `jvmtiEnv->GetClassSignature` instead of a JNI call), prefer the lighter-weight
  `BaseWallClock`-style thread with no JNI attach (`wallClock.cpp:317-331`), matching the
  design doc's own note that this avoids unnecessary JNI dependency.
- Implement the `jvmtiHeapCallbacks`/`jvmtiHeapReferenceCallback` needed by
  `FollowReferences`, filtering to tagged frontier objects and recording
  `(referrer_klass, parent_tag, depth)` into the Phase 2 table when an edge is
  discovered. Respect the design doc's Algorithm steps 1-4 (seed from roots, resolve
  live tagged objects, expand up to a fixed per-pass budget, tag newly discovered
  objects) — but for this phase, run to completion or hop-cap within one pass (no
  persist-and-return yet).
- EdgeStore construction: walk `parent_tag` links from a target sample's tag back to a
  root-reachable entry, per the design doc's Data Structures section, to produce the
  final referrer-type chain.
- Enforce the hop cap (design doc: mirror the ~200/100-100 JFR precedent, but tunable
  via Phase 0's flag) directly in the callback — abort expansion past the cap rather
  than discovering-then-discarding.
- gtest coverage: build a small live-object graph in a test JVM (via JNI from the test),
  run a pass, and assert the reconstructed referrer-type chain matches the known graph
  shape. Use `livenessTracker_ut.cpp`'s fixture style as a template.

**Exit criteria:** a single bounded BFS pass correctly reconstructs a referrer-type
chain for a small synthetic object graph, with a hop cap enforced.

### Phase 4 — Incremental resumption across passes

**Goal:** the actual "chosen design" novelty — persist frontier state across passes so
no single pass needs to cover the whole search.

- Persist the Phase 2/3 frontier state in agent-owned native memory (not thread-local
  scratch, per the design doc's Algorithm step 5) so a later pass — potentially
  triggered by a different invocation of the BFS thread's main loop — can resume from
  where the last one left off.
- Wire the Phase 1 GC-signal (epoch counter) as the trigger to schedule the next pass:
  the BFS thread's main loop wakes (timer-driven, matching `BaseWallClock`'s
  `pthread_kill(WAKEUP_SIGNAL)` wake mechanism) when either a fixed cadence elapses or
  the GC-epoch counter has advanced since the last pass, per Open Question 5's two
  candidate policies — implement both behind the Phase 0 flag's sub-options so this can
  be measured rather than guessed (see Phase 5).
- Implement resolve-or-drop for frontier objects at the start of each resumed pass
  (design doc Algorithm step 2): a tag that no longer resolves via `GetObjectsWithTags`
  is dead and its subtree is pruned for free — no extra bookkeeping.
- Implement the full Termination section from the design doc:
  - Hop cap (already enforced per-pass in Phase 3; confirm it also holds across
    resumed passes, i.e. `depth` in `FrontierEntry` must carry over correctly).
  - Passes-per-search / wall-clock TTL cutoff.
  - Frontier-size/memory cap — stop admitting new entries once hit, mark the search
    abandoned/truncated rather than silently dropping.
  - Explicit abandoned-search reporting (no silent truncation) — this needs a
    reporting surface; see Phase 6 for the JFR event that carries this signal.
  - Tag release on abandonment/completion (`SetTag(obj, 0)` for every tag the search
    owns) before its table entries are freed — verify no tag leak across repeated
    abandoned searches via a longevity gtest (run N searches to abandonment, assert
    `GetObjectsWithTags` count returns to baseline).

**Exit criteria:** a search that would exceed one pass's budget correctly resumes across
multiple passes and still reconstructs the right chain; an abandoned search cleans up
its tags completely (no leak).

### Phase 5 — Tuning and cutover from placeholders

**Goal:** replace every "TBD, needs measurement" placeholder from Phase 0-4 with a real
default, per Open Question 2 in the design doc.

- **Harness**: drive this with the repo's existing `java-performance-investigator`
  agent/workflow (JMH-benchmark design + async-profiler validation), not an ad-hoc
  script — it already owns "design/validate a benchmark, run it, profile it, interpret
  results" for this codebase. Build a synthetic heap-graph generator (extend the
  Phase 3 test graph rather than writing a second one) parameterized by size, fan-out,
  and chain depth, so the same generator seeds both the benchmark and the Phase 3/4/7
  tests.
- **Heap-shape matrix**: at minimum, cross {narrow-deep chain, wide-shallow fan-out,
  mixed} × {G1, ZGC} × {small (~256MB live set), large (~4GB live set)} — collector
  choice matters here because the transparent-safepoint cost `FollowReferences`/
  `IterateThroughHeap` incurs is collector-dependent (per the design doc's Triggering
  section citing per-collector `VM_Operation` assert sites). Shenandoah is a stretch
  goal, not a blocker, if the matrix above already shows a consistent trend.
- For each cell, measure and record: per-pass wall-clock pause distribution (p50/p99),
  passes needed to reach a target sample at various depths, and frontier-table peak
  occupancy — from these, pick: per-pass budget (edge count vs. time slice), hop cap
  default, passes/TTL abandonment cutoff, frontier-size/memory cap, and the frontier
  table's initial capacity and growth ceiling (this subsystem's analog of
  `MAX_TRACKING_TABLE_SIZE`, `livenessTracker.h:39`, but derived from the graph-search
  model, not the allocation sample-rate model).
- **Decision rule, not just data**: a placeholder only counts as "resolved" once a
  specific value is chosen and the measurement that justified it is written down (see
  Exit criteria) — collecting numbers without picking a default does not close this
  phase.
- Resolve Open Question 3 (one search per sample vs. batched multi-target BFS sharing a
  frontier) empirically if time permits; otherwise ship the simpler one-search-per-
  sample model first and note batching as explicit future work, consistent with the
  design doc's non-goals framing (don't silently expand scope).
- Resolve Open Question 5's pass-scheduling policy with a real cost model: using the
  same harness/matrix above, measure safepoints/second and per-pause duration at the
  candidate cadence, and compare the resulting p99 pause against a single-pass
  (non-incremental) run covering the same total work. The design doc's claim is a
  latency-*distribution* win, not a total-STW win — so the bar to clear is "p99 pause
  drops materially versus the single-pass baseline," not "aggregate STW improves" (it
  is expected to be flat or worse, per the design doc's Cost/benefit summary). If the
  measured p99 does *not* improve, that is a real signal to revisit the incremental
  design, not a result to explain away.

**Exit criteria:** every placeholder default is backed by a measurement, documented in
this plan (add a short "Tuning results" appendix) or in the design doc's Open Questions
section (mark each resolved with the chosen value and evidence).

### Phase 6 — Reporting surface (JFR event) and public exposure

**Goal:** make discovered chains (and abandoned searches) visible to consumers.

- Follow the existing `ObjectLivenessEvent`/`datadog.HeapLiveObject` pattern exactly:
  - `Event` subclass in `event.h` (cf. `ObjectLivenessEvent`, `event.h:83-90`) holding
    the reconstructed chain (e.g. an ordered list of referrer-klass ids/names, target
    sample identity, depth reached, resolved/abandoned status).
  - New `T_xxx` id in `jfrMetadata.h` (cf. `T_HEAP_LIVE_OBJECT = 105`,
    `jfrMetadata.h:60`).
  - Schema block in `jfrMetadata.cpp` (cf. lines 174-186) — likely two event types:
    one for a successfully reconstructed chain, one for an abandoned/truncated search
    (per the design doc's explicit "no silent truncation" requirement — this needs its
    own visible signal, not a reused success-event with a null field).
  - `Recording::recordXxx` writer in `flightRecorder.cpp`/`.h` (cf.
    `recordHeapLiveObject`, `flightRecorder.cpp:1914-1934`), plus a boolean setting
    event following `writeBoolSetting(buf, T_HEAP_LIVE_OBJECT, "enabled", ...)`
    (`flightRecorder.cpp:1142`).
  - Every field/comment in the new event's JFR label/description must describe only
    what the code actually produces (referrer-type sequence, best-effort, historical —
    per the design doc's Correctness Note) — do not word it as an exact/complete
    retainer path.
- Decide (does not block Phase 0-5) whether any Java-side API surface is needed beyond
  "the JFR event exists and can be read by existing tooling," or whether this is
  JFR-only like `LivenessTracker`'s output. Default to JFR-only unless a concrete
  consumer requires a Java API — keep scope minimal per this codebase's stated
  allocation-free/minimal-surface preference.

**Exit criteria:** a successfully reconstructed chain and an abandoned search each
produce a distinct, correctly labeled JFR event; existing JFR tooling in this repo can
read both.

### Phase 7 — End-to-end test and documentation

- Java-side integration test modeled on
  `ddprof-test/src/test/java/com/datadoghq/profiler/memleak/LivenessTrackingTest.java`
  (`AbstractProfilerTest` subclass, `@RetryingTest`, JFR-parsing assertions via
  `JfrLoaderToolkit`) — construct a live object graph with a known referrer-type chain
  to a GC root, enable the new flag, and assert the emitted JFR event's chain matches.
- Add a second test exercising the abandonment path (e.g. artificially tiny hop cap or
  frontier-size cap) asserting the abandoned-search event fires instead of silent
  truncation.
- Update the design doc's Open Questions section to mark every question resolved with
  its shipped value (cross-reference Phase 5), and add a short "Implemented" status
  note at the top of the design doc pointing at this plan and the shipping flag name.

**Exit criteria:** CI-green end-to-end test for both the success and abandonment paths;
design doc and this plan cross-reference the final shipped state.

## Open items to resolve before starting Phase 1

These are implementation-plan-level details the design doc doesn't pin down and which
block Phase 1/2 specifics — resolve during Phase 0/1, not before, since they need a
quick look at current code rather than up-front research:

1. **Single vs. multi-callback slot**: confirm whether `jvmtiEventCallbacks` allows
   only one function pointer per event (it does — it's a flat struct with one field per
   event type) and design the `GarbageCollectionFinish` trampoline so both
   `LivenessTracker` and `ReferenceChainTracker` get the signal without one subsystem's
   future removal silently breaking the other's wiring.
2. **Class-name interning**: identify whether an existing symbol/string dictionary in
   `ddprof-lib/src/main/cpp/` should be reused for `referrer_klass` storage in
   `FrontierEntry` (Phase 2) instead of a bespoke string table or a raw `jclass` — avoid
   inventing a second interning mechanism if one already exists (e.g. this codebase's
   existing class-name dictionary used for stack-trace symbolization).
3. **`FollowReferences` vs. `IterateThroughHeap`**: Phase 3 should do a short spike
   comparing which JVMTI call gives referrer-class info most cheaply for this
   referrer-type-only use case before committing — the design doc assumes
   `FollowReferences` (mirroring JFR) but doesn't rule out `IterateThroughHeap` being
   cheaper for a referrer-type-only (not identity-level) use case.

## Non-goals (carried over from the design doc, restated for implementers)

- No exhaustive all-GC-roots search, no field-level chains, no GC-internal-closure
  hooks, no `ParallelObjectIterator` use — none of these should appear as incidental
  scope creep in any phase above. If a phase's implementation seems to need one of
  these, stop and revisit the design doc rather than proceeding.
