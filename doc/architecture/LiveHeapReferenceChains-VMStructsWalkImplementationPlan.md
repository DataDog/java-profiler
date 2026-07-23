# Reference chains: VMStructs-walk implementation plan

Converts `LiveHeapReferenceChains-VMStructsWalkDesign.md` into a sequenced,
file-level plan. Each phase is independently landable and independently
testable; later phases depend on earlier ones being in place but not on the
whole plan being finished before anything ships.

Reference points in the current implementation (all in `ddprof-lib/src/main/cpp/`):

- `referenceChains.h`/`.cpp` — `FrontierTable` (tag-indexed, `referenceChains.h:234-398`),
  `ReferenceChainTracker` (`referenceChains.h:448+`), admission gate in
  `heapReferenceCallback()` (`referenceChains.cpp:1003-1121`, first-discovery
  check at line 1087), pass driver `runPass()` (`referenceChains.cpp:1335-1526`).
- `hotspot/vmStructs.h`/`.cpp` — `MATCH_SYMBOLS`/`type_begin`/`field`/`type_end`
  declaration macros, `DECLARE`/`DECLARE_END` accessor generation
  (`vmStructs.h:81-92`), `gHotSpotVMStructs` table walk in
  `VMStructs::init_offsets_and_addresses()` (`vmStructs.cpp:140-191`),
  existing collector detection via `VMFlag::find("UseG1GC", {VMFlag::Type::Bool})`
  in `VMStructs::findHeapUsageFunc()` (`vmStructs.cpp:558-583`).
- `referenceChains_ut.cpp` — ~50 existing test cases whose behavioral
  contract (frontier table semantics, hop-cap/budget/TTL termination,
  class-object exclusion, dead-object pruning, multi-pass resumption) must
  keep passing regardless of which traversal engine populates the table.

## Guiding constraint

The frontier table is the seam. Every phase below either (a) adds new
VMStructs plumbing that produces no observable behavior change yet, or (b)
swaps *how* entries get admitted into `FrontierTable` while keeping
`insert()`/`lookup()`/`markEdge()`/`markExpanded()`/`reconstructChain()`
untouched. This keeps each phase reviewable against the existing test suite
without waiting for the full walk to exist.

---

## Phase 0 — Collector gating (no new walk logic yet)

**Goal:** land the G1-vs-fallback dispatch point before any manual-walk code
exists, so later phases plug into a real decision point instead of adding it
retroactively.

1. Add `VMStructs::isG1Active()` (or extend the existing
   `findHeapUsageFunc()` pattern) in `hotspot/vmStructs.cpp` near line 558,
   reusing `VMFlag::find("UseG1GC", {VMFlag::Type::Bool})->get()`. Cache the
   result once at `resolveOffsets()` time (same phase as the existing
   compressed-oop-base/shift resolution) — collector choice can't change
   after JVM startup, so this is a one-time read, not a per-pass check.
2. In `ReferenceChainTracker::runPass()` (`referenceChains.cpp:1335`), add a
   branch point that currently always takes the existing JVMTI path
   regardless of `isG1Active()` — i.e. wire the plumbing with the fallback
   as the *only* live branch. This makes the eventual switch-over a
   one-line change in Phase 4, and lets Phase 0 land and run in CI with zero
   behavioral change.
3. Test: no `vmStructs_ut.cpp` exists today (verified: no such file in the
   repo) and `findHeapUsageFunc()` has no dedicated unit-test harness to
   mirror. Rather than invent a mocked `gHotSpotVMStructs` table for a pure
   C++ unit test, use the real-JVM test seam pattern from Phase 1/3 (see
   there): add a `#ifdef DEBUG`-gated native method
   `Java_com_datadoghq_profiler_JavaProfiler_isG1ActiveForTest0` in
   `javaApi.cpp` (same file, same `#ifdef DEBUG` pattern already used at
   lines 1073-1176 for `LivenessTracker`/`ReferenceChainTracker` test
   seams — not line 702, which is an unrelated OTel thread-context-record
   contiguity assertion, not a test seam) returning `VMStructs::isG1Active()`,
   and a JUnit test class in
   `ddprof-test/src/test/java/com/datadoghq/profiler/` asserting it matches
   the JVM's actual `-XX:+UseG1GC`/`-XX:+UseParallelGC`/etc. flag for
   whichever collector the test JVM was launched with (read via
   `ManagementFactory.getGarbageCollectorMXBeans()` names, or simply assert
   `true` when the test suite's own launch flags request G1 and `false`
   otherwise — check how `AbstractProfilerTest` parameterizes GC choice, if
   at all, before deciding the assertion shape).

**Exit criteria:** `isG1Active()` correct on at least G1 and one non-G1 JVM
run; no change to `referenceChains_ut.cpp` pass/fail.

---

## Phase 1 — VMStructs plumbing: oop-map metadata

**Goal:** declare the struct layout needed to enumerate which fields of an
instance are oop-typed, without yet using it for traversal.

1. In `hotspot/vmStructs.h`, extend the `VMKlass` type block
   (`vmStructs.h:223-228`) or add a sibling `VMInstanceKlass` type with:
   - `_nonstatic_oop_map_size` (int, `MATCH_SYMBOLS("_nonstatic_oop_map_size")`)
   - a new `OopMapBlock` type: `type_begin(VMOopMapBlock, MATCH_SYMBOLS("OopMapBlock"))`
     with `field(_offset, offset, MATCH_SYMBOLS("_offset"))`,
     `field(_count, offset, MATCH_SYMBOLS("_count"))`, and `type_size()` for
     the block itself (needed to stride through the array).
   - the array's location relative to the `InstanceKlass` (HotSpot lays
     `OopMapBlock`s out as a variable-length tail immediately after the
     fixed `InstanceKlass` fields — confirm exact anchor via SA export
     table rather than assuming a named field; likely exposed as an
     `start_of_nonstatic_oop_maps()`-equivalent computed offset, not a
     plain field — check `gHotSpotVMTypes` for `InstanceKlass` size first).
2. Add `VMInstanceKlass` accessors following the `DECLARE`/`DECLARE_END`
   pattern (`vmStructs.h:81-92`, cf. `VMKlass::fromOop()` at 669-702):
   `oopMapCount()`, `oopMapBlockAt(int i)` returning offset/count pairs.
3. **Test vehicle: reuse the existing debug-native-test-seam pattern, not a
   new one.** Verified `referenceChains_ut.cpp`'s own header comment: this
   gtest binary has no live JVM attached, and its `ReferenceChainsBfsTest`
   fixtures are entirely mock-driven — not usable for testing real
   `oop`/`InstanceKlass*` layouts. But the repo already has exactly the
   needed vehicle, currently exercising unrelated internals:
   `ddprof-test/src/test/java/.../referencechains/ReferenceChainTestSeamsTest.java`
   runs against a real attached JVM (`AbstractProfilerTest`) and calls
   `#ifdef DEBUG`-gated native test-seam methods
   (`Java_com_datadoghq_profiler_JavaProfiler_tagAsReferenceChainRoot0`,
   `..._runReferenceChainPass0`, etc., `javaApi.cpp:1134-1176`) that call
   straight into `ReferenceChainTracker`/`LivenessTracker` internals,
   documented as only running under the `testdebug` native build
   (`System.getProperty("ddprof_test.config")`). Follow this exact pattern
   for Phase 1: add a `#ifdef DEBUG` native method (e.g.
   `Java_com_datadoghq_profiler_JavaProfiler_readOopMapForTest0(Object obj)`)
   that resolves the object's `InstanceKlass*` via `VMKlass::fromOop()` (the
   call site is already proven safe/correct — reuse it, don't reimplement
   klass resolution) and returns the oop-map-derived list of field offsets
   (as an `int[]`) back to Java. A new JUnit test class beside
   `ReferenceChainTestSeamsTest` then constructs a real Java object with a
   mix of reference and primitive fields, calls the seam, and asserts the
   result matches `Class.getDeclaredFields()` reflection's reference-typed
   fields. This needs one new native seam method plus one new JUnit test
   class — not new C++ test infrastructure, since the JVM-attach and
   debug-build gating machinery already exists and is already proven
   working for this exact class of "poke a C++ internal from a live JVM"
   test.
4. Unit test (using the seam from item 3): construct a Java object with a
   mix of oop and primitive fields, resolve its `InstanceKlass*` via
   existing `VMKlass::fromOop()`, and assert the oop-map-derived field
   offsets match what `Class.getDeclaredFields()` reflection reports as
   reference-typed. **This seam shares Phase 3's safepoint gap** — `VMKlass::fromOop()`
   (`vmStructs.h:669-702`) directly dereferences a raw memory address, and
   its only existing production caller (`hotspotSupport.cpp:628`, inside
   best-effort async stack-walking) treats this as inherently racy, pairing
   it with `SafeAccess::safeFetch64` elsewhere in the same function; there
   is no existing precedent for calling it on a live object's oop from an
   ordinary non-safepoint JNI method the way this seam proposes. Either
   apply the same mitigation as Phase 3 item 3 (safepoint-wrapped call or
   non-concurrent-GC test JVM config), or explicitly document the residual
   flakiness risk if left unmitigated for this narrower metadata-only read.

**Exit criteria:** standalone test passing; nothing in `referenceChains.cpp`
references this yet.

---

## Phase 2 — VMStructs plumbing: arrays and compressed oops

**Goal:** the remaining two "not yet declared" primitives from the design
doc's scope list, landed independently of oop-map work since they're
orthogonal.

1. **Array handling** — add `VMArrayKlass`/array-oop layout declarations:
   `arrayOopDesc` length offset, `layout_helper` decoding (element type +
   whether it's an oop array) via `Klass::_layout_helper` (already likely
   partially present given `VMKlass` exists — check before adding a
   duplicate field). Add a helper `bool isObjectArray(Klass*)` and
   `int arrayLength(oop)` / `oop arrayElementAt(oop, int)` (computing
   `base_offset_in_bytes(T_OBJECT)` equivalent from the SA constant table —
   this is an exported `gHotSpotVMLongConstants`/`gHotSpotVMIntConstants`
   entry, not a struct field; use `init_constants()`'s existing pattern,
   `vmStructs.cpp:230-267`).
2. **Compressed-oops decoding** — add a `VMCompressedOops` (or extend
   `VMUniverse`, `vmStructs.h:319-323`) block reading
   `CompressedOops::_narrow_oop._base`/`_shift` the same way
   `VMUniverse::_narrow_klass_base_addr`/`_narrow_klass_shift_addr` already
   do for narrow *klass* pointers (there's a direct precedent to copy,
   `vmStructs.h:319-323` and its consumer in `VMKlass::fromOop()`,
   `vmStructs.h:669-702`, which already decodes narrow klass pointers —
   mirror that for narrow *oop* pointers). Add `decodeOop(narrowOop)` /
   `encodeOop(oop)` free functions or methods, gated on
   `UseCompressedOops` (`VMFlag::find`, same pattern as Phase 0).
3. Unit tests: array-of-objects element read matches reflective
   `Array.get()`; compressed-oop decode round-trips against a real object's
   tagged identity (tag it via `SetTag`, decode a reference to it obtained
   another way, confirm `GetTag` matches) on both compressed- and
   uncompressed-oop JVM configurations (`-XX:-UseCompressedOops` in one CI
   leg if not already covered). **Shares Phase 1/3's safepoint gap** — same
   raw-oop-read-outside-a-safepoint risk applies to these seams; apply the
   same mitigation choice (safepoint-wrapped call or non-concurrent-GC test
   config) rather than treating this as a fresh, unrelated test design.

**Exit criteria:** array and compressed-oop primitives independently unit
tested; still no traversal code wired up.

---

## Phase 3 — The manual field-walker

**Goal:** build the actual N-hop walker as a self-contained component,
testable in isolation from JVMTI callback context, before integrating it
into the pass-driving code.

1. New file `referenceChainsWalker.{h,cpp}` (kept separate from
   `referenceChains.cpp` since it has a different dependency: VMStructs
   offsets, not JVMTI heap-callback machinery) implementing:
   - `struct WalkFrame { oop obj; int field_index; }` on a heap-allocated
     (`GrowableArray`-equivalent, matching the existing non-recursive
     pattern the design doc calls out) explicit stack — **not** C++
     recursion, per the design doc's "Understated, not broken" finding.
   - `class FieldWalker` with a bounded work-list (`ResourceArea`/C-heap
     allocation only — no `new`/STL containers that might reenter Java-heap
     allocation; check what allocator `FrontierTable`'s own growth path
     uses today, `referenceChains.cpp:27-242`, and reuse it for
     consistency).
   - `walkOneHop(oop parent, int depth)`: for an instance, iterate oop-map
     blocks (Phase 1) computing each field's referent oop, decoding via
     Phase 2's compressed-oop path if applicable; for an array, iterate
     elements via Phase 2's array helpers; yields `(child_oop, field_slot)`
     pairs to a caller-supplied visitor instead of admitting into the
     frontier table directly (keeps this component ignorant of
     `FrontierTable`/tag semantics — integration happens in Phase 4).
2. Explicitly *not* using `Heap_lock` reacquisition or any safepoint-
   triggering call inside `walkOneHop` — this is the constraint from the
   design doc's "Understated, not broken" finding. **This needs a concrete
   enforcement mechanism, not just a prose rule** — the existing
   `GCCallbackGuard`/`t_inGCCallback` pattern (`referenceChains.h:128-137`)
   it's modeled on works because it's a thread-local flag checked by a
   small, fixed set of call sites that are themselves forbidden (specific
   Heap-category JVMTI calls); it is not a general "no allocation happened"
   detector, and nothing analogous exists for "no allocation/safepoint call"
   in general. Without an equivalent concrete check, this constraint is
   only as good as manual code review of `walkOneHop` and everything it
   calls (including transitively through `FieldWalker`'s Phase 1/2
   dependencies) — which is exactly the class of bug the design doc's own
   adversarial review caught elsewhere (asserted-but-unenforced safety
   properties). Minimum viable enforcement: a debug-build-only thread-local
   `t_inManualWalk` flag set for the duration of `walkOneHop`, checked by
   the allocation entry points `FieldWalker` is allowed to use (its
   `ResourceArea`/C-heap allocator from item 1) to assert they're the *only*
   allocation happening — this doesn't catch every possible violation (a
   JVMTI call buried in a VMStructs accessor wouldn't trip it) but at least
   catches accidental introduction of `new`/STL-container/Java-heap
   allocation in future edits to this code, which is the realistic failure
   mode once the walker exists and gets modified over time.
3. Unit tests run **without** a live safepoint (this component doesn't know
   about safepoints — that's Phase 4's job): using the same real-JVM
   debug-native-test-seam vehicle established in Phase 1 item 3
   (`javaApi.cpp`'s `#ifdef DEBUG` methods called from a JUnit test beside
   `ReferenceChainTestSeamsTest.java`), construct object graphs as real Java
   objects, call `walkOneHop` directly via a new seam method, assert
   discovered children match a reference reflective walk. **This test
   vehicle has a real safety gap that must be closed, not just noted**:
   `walkOneHop` dereferences raw oops with no JNI local-ref/handle
   protection and no safepoint. A plain `#ifdef DEBUG` JNI native method
   runs with the calling thread in `_thread_in_native` state, which does
   *not* block a concurrent STW safepoint/GC triggered by another thread —
   unlike Phase 4's real integration, which only ever calls `walkOneHop`
   while `IterateOverReachableObjects`'s `VM_Operation` already holds every
   thread at a safepoint (the same safety property `heapReferenceCallback`
   already relies on for its own raw-oop reads, per the comment at
   `referenceChains.h:128-137`). Without protection, a concurrent GC (e.g. a
   background allocation thread triggering a G1 young/mixed collection)
   could relocate the very object `walkOneHop` is mid-read on during the
   test, causing an intermittent crash or garbage read that has no bearing
   on `walkOneHop`'s real safety and would not reproduce reliably. Close
   this before relying on the test: either (a) wrap the seam call in an
   actual JVMTI Heap-category call (e.g. a minimal `FollowReferences`
   invocation) so the test genuinely runs inside a safepoint, or (b)
   restrict the test JVM to non-concurrent GC settings
   (`-XX:+UseSerialGC`) for this test class specifically, and document
   explicitly that a green result under (b) does not by itself establish
   `walkOneHop`'s safety under Phase 4's real safepoint-gated invocation —
   that remains to be validated by Phase 4's own tests, not this phase's.
   Include: plain
   object field graphs, object arrays, primitive arrays (must yield zero
   oop children), null fields (must be skipped, not crash), self-referential
   cycles (walker must not infinite-loop on a single hop — cycle detection
   is the frontier table's job via tag-already-admitted checks, not this
   component's, so this test just confirms `walkOneHop` returns the same
   child twice without hanging, not that it dedups).

**Exit criteria:** `FieldWalker` fully unit tested against real object
graphs, with zero JVMTI dependency and zero integration into
`ReferenceChainTracker` yet.

---

## Phase 4 — Root enumeration + safepoint integration

**Goal:** wire `IterateOverReachableObjects` (root callbacks only) and
`FieldWalker` into the actual pass-driving code, behind the Phase 0 gate.

1. In `referenceChains.cpp`, add a new pass path
   `runPassManualWalk(jvmtiEnv*, JNIEnv*)` parallel to the existing
   `runPass()` JVMTI-only path (don't inline into `runPass()` — keep the
   two paths textually separate so the fallback path is untouched and
   trivially diffable against its current passing test suite).
2. Call `jvmti->IterateOverReachableObjects(heap_root_callback,
   stack_ref_callback, /*object_ref_callback=*/nullptr, &ctx)`. Implement
   `heap_root_callback`/`stack_ref_callback` as new static functions (new
   surface — nothing to copy from `heapReferenceCallback`, since that one
   is driven by `FollowReferences`'s different callback shape). Each root
   callback:
   - **Enum-space fix, required before anything else in this phase**:
     `IterateOverReachableObjects`'s root callbacks report a
     `jvmtiHeapRootKind` (ordinals ~1-7 per the JVMTI spec — `JVMTI_HEAP_ROOT_JNI_GLOBAL`,
     `_SYSTEM_CLASS`, `_MONITOR`, `_STACK_LOCAL`, `_JNI_LOCAL`, `_THREAD`,
     `_OTHER`), a *different, disjoint* enum from the `jvmtiHeapReferenceKind`
     `FrontierEntry::root_kind` is typed for today (ordinals 8, 21-27,
     `JVMTI_HEAP_REFERENCE_STATIC_FIELD`/`_JNI_GLOBAL`/etc.). Confirmed: the
     only consumer, `flightRecorder.cpp`'s `rootKindName()` (~line 2010),
     switches on the `jvmtiHeapReferenceKind` numbering and has no cases for
     the root-kind numbering — storing a raw `jvmtiHeapRootKind` value into
     `root_kind` unmodified would make every G1-path root-attached chain
     report `"unknown"`, silently breaking the tool's primary output for
     exactly the collector this design targets. Fix: add an explicit
     `jvmtiHeapRootKind → jvmtiHeapReferenceKind`-numbering translation
     table (e.g. `JVMTI_HEAP_ROOT_JNI_GLOBAL → JVMTI_HEAP_REFERENCE_JNI_GLOBAL`,
     `_STACK_LOCAL → _STACK_LOCAL`, `_SYSTEM_CLASS → _SYSTEM_CLASS`,
     `_MONITOR → _MONITOR`, `_JNI_LOCAL → _JNI_LOCAL`, `_THREAD → _THREAD`,
     `_OTHER → _OTHER`; there's no root-kind equivalent of
     `_STATIC_FIELD`, so that value only ever arises from the existing
     `FollowReferences` path and is left untouched) at the point each root
     callback writes `root_kind`, and add it as its own reviewable unit
     (table plus a test asserting `rootKindName()` never returns
     `"unknown"` for any value either callback path can produce) before
     wiring the rest of admission.
   - reads root-kind directly from the callback's own `root_kind` parameter
     (translated per above) (or thread/depth/method/slot for stack refs)
     instead of inferring it — this is the "root-kind info directly from
     JVMTI" improvement the design doc calls out in step 2 of its own
     design section.
   - performs the **admission-time durability tie-break** (design doc,
     "Fix for root-attribution staleness" point 1): if the object is
     already tagged this pass from an earlier root callback, only overwrite
     `root_kind` if the new root is more durable than the recorded one, per
     a fixed durability ranking (e.g. static/class/CLD > JNI global >
     JNI local/stack local/monitor — this ranking needs to be an explicit
     ordered table added near the `FrontierEntry` definition,
     `referenceChains.h:145-201`, not inferred from raw
     `jvmtiHeapReferenceKind` ordinal values, which aren't ordered by
     durability).
   - on first discovery, calls `_frontier->insert(...)` exactly as
     `heapReferenceCallback`'s admission branch does today
     (`referenceChains.cpp:1087-1121`) — same tag allocation
     (`nextTag()`), same budget check, same `_pending_expand` push. This is
     the direct reuse the design doc's "Fix for stack-root resumability"
     section calls for: stack-local discoveries go through the *same*
     tag-indexed admission path as every other root kind, no separate
     mechanism.
   - then, still inside the safepoint, invokes `FieldWalker::walkOneHop`
     (Phase 3) repeatedly up to the pass's hop budget, admitting each
     discovered child the same way (reuse the admission helper — consider
     factoring `heapReferenceCallback`'s admission branch, lines 1087-1121,
     into a shared `admitObject(tag_ptr, parent_tag, depth, referrer_klass,
     root_kind)` helper callable from both the old `FollowReferences`
     callback and the new root-callback-driven walk, so both paths stay in
     sync against `FrontierTable`'s contract by construction rather than by
     copy-paste). **This factoring is not a mechanical extraction, and the
     asymmetry differs by callback, verified against the real `jvmti.h`
     typedefs**:
     - `jvmtiHeapReferenceCallback` (`heapReferenceCallback`'s signature,
       driving `FollowReferences`) is `(jvmtiHeapReferenceKind, const
       jvmtiHeapReferenceInfo*, jlong class_tag, jlong referrer_class_tag,
       jlong size, jlong* tag_ptr, jlong* referrer_tag_ptr, jint length,
       void* user_data)` — both the object's own tag *and* its referrer's
       tag arrive as JVMTI-owned out-parameters.
     - `jvmtiHeapRootCallback`/`jvmtiStackReferenceCallback` (driving
       `IterateOverReachableObjects`, used for Phase 4's root enumeration)
       are `(jvmtiHeapRootKind root_kind, jlong class_tag, jlong size,
       jlong* tag_ptr, void* user_data)` and `(..., jlong thread_tag, jint
       depth, jmethodID method, jint slot, void* user_data)` respectively —
       **these do supply a `tag_ptr` out-param for the object itself**
       (good: root-discovery admission can reuse the same
       tag-write-through shape `heapReferenceCallback` already uses), but
       supply **no `referrer_tag_ptr` at all**, which is fine since root
       entries already use `parent_tag = 0` (declared at
       `referenceChains.cpp:1052`; the value is tested, not assigned, at
       line 1099 via `root_kind = parent_tag == 0 ? (u8)reference_kind :
       0`) — there is no referrer to record.
     - The manual `FieldWalker`-driven hop (Phase 3), by contrast, is not a
       JVMTI callback at all — it has no `tag_ptr*` out-param of any kind
       for the *child* it just found, and must resolve/assign that child's
       tag itself (`GetTag`/`SetTag` called directly), while sourcing
       `referrer_klass`/`parent_tag` from the parent object it's currently
       expanding rather than from any JVMTI-supplied value.
     Net: root-callback admission and `FollowReferences`-callback admission
     are close enough in shape (both get a real `tag_ptr*`) that a shared
     helper taking `jlong* tag_ptr` is plausible for those two. The
     `FieldWalker`-driven hop is the genuinely different case and likely
     needs its own thin adapter that calls `GetTag`/`SetTag` and passes the
     *address of a local* to satisfy a shared `jlong* tag_ptr` parameter,
     rather than a third copy of the core admission logic. Write out all
     three call sites' actual argument availability before finalizing the
     helper's signature — this is a small but real design decision, not a
     given.
3. Pacing/budget integration: reuse `_budget`/`_effective_budget`/`_hop_cap`
   fields as-is; the manual walker just needs to decrement the same counters
   `heapReferenceCallback` decrements today, so `updatePacing()`
   (referenced near `runPass()`, `referenceChains.cpp:1465-1482`) keeps
   working unmodified.
4. Wire Phase 0's gate: `runPass()` calls `runPassManualWalk(...)` only when
   the **composite** fail-closed condition holds — `isG1Active() &&
   VMInstanceKlass::available() && <array/compressed-oops availability from
   Phase 2>` — not `isG1Active()` alone. This is the same composite check
   the "Cross-cutting risks" section requires; it must be wired here, in
   the actual dispatch step, not left as prose in that section only (an
   engineer implementing Phase 4 from its numbered steps alone would
   otherwise wire `isG1Active()` unconditionally and silently reintroduce
   the "hollow fail-closed claim" class of bug this plan already fixed
   once). Add a corresponding Phase 4 exit criterion: on a G1 JVM with a
   simulated/forced offset-resolution failure (e.g. `available()` returns
   false), the pass still takes the existing JVMTI path.
5. **Cross-pass resumption for manual-walk frontier entries — not yet
   specified, and not free to assume.** `expandFrontier()`
   (`referenceChains.cpp:1134-1232`) resumes the JVMTI path across passes by
   re-resolving each `FRONTIER`-state *tag* to a live oop via
   `GetObjectsWithTags` at the start of every pass — it never persists a raw
   oop across a pass boundary, because G1 can move/reclaim objects between
   safepoints even though it never moves them within one.
   `FieldWalker::walkOneHop` (Phase 3) instead operates on raw `oop` values
   held in an explicit `WalkFrame` stack. If the pass's hop budget is
   exhausted mid-walk, any not-yet-expanded frontier entries **must** be
   left recorded by tag only (the existing `_pending_expand`/`FrontierEntry`
   contract already stores tags, not oops, so this falls out naturally
   *as long as the manual-walk integration never stashes a raw oop
   anywhere that survives past the current pass's safepoint*) — the next
   pass must re-resolve those tags to fresh addresses before resuming,
   exactly as `expandFrontier()` does today. State this explicitly as a
   Phase 4 action item and add it as an exit criterion (e.g. a test that
   exhausts the hop budget mid-pass, forces a GC between passes, and
   asserts the next pass's resumed walk reads valid, current addresses)
   rather than leaving it implicit in "invokes `walkOneHop` repeatedly up to
   the pass's hop budget."

**Exit criteria:** on a G1 JVM, a pass populates `FrontierTable` via the
manual walk with root-kind attribution at least as correct as today; on a
non-G1 JVM, behavior is byte-for-byte identical to pre-Phase-0 (verified by
running the full existing `referenceChains_ut.cpp` suite unmodified against
non-G1 CI legs). **Any end-to-end test for this criterion must account for
`ReferenceChainTracker`'s process-wide-singleton, one-root-walk-per-process-
lifetime constraint** — `runPass()` only performs a real root-seeded walk
on its very first call (`_search_started` guard,
`referenceChains.h:~615-620`, `referenceChains.cpp:~1392`), a constraint
`ExternalProcessReferenceChainTest.java`'s own header comment documents in
detail as the reason it runs its scenario in a genuinely separate child
process rather than in-process alongside other tests. A new in-process test
for this exit criterion must either follow that same separate-process
pattern, or explicitly call the existing `resetSearchStateForTest0` seam
(`referenceChains.cpp:721`) before invoking `runPass()` — otherwise it will
silently receive a no-op, non-root-seeded pass whenever it happens to run
after another test's search in the same JVM, passing locally while being
flaky or vacuously green under real CI test ordering.

---

## Phase 5 — Correctness hardening: durability re-verification

**Goal:** the design doc's "opportunistic upgrade" and "bounded rotating
re-expansion" fixes for stale root attribution — these are refinements on
top of Phase 4's admission logic, landable separately since they only
affect *labeling*, not traversal correctness.

**Prerequisite this phase actually requires, not yet built by Phase 0-4**:
both items 1 and 3 below need to overwrite `FrontierEntry::root_kind` on an
entry that was already admitted in an earlier pass — a capability that does
not exist anywhere in the codebase today. `FrontierTable::insert()`
(`referenceChains.h:294-295`) is the *only* writer of `root_kind`, and it is
only ever invoked from `heapReferenceCallback`'s first-discovery branch
(`referenceChains.cpp:1087-1100`). This phase must add a new mutator (e.g.
`FrontierTable::updateRootKind(tag, root_kind)`) — which means amending the
"Guiding constraint" section's list of untouched functions
(`insert()`/`lookup()`/`markEdge()`/`markExpanded()`/`reconstructChain()`)
to add this one, explicitly, rather than treating Phase 5 as a pure
labeling change with "no new state" (see item 2's own claim below, which is
still true for item 2 alone but not for items 1/3). Separately,
`root_kind` is documented (`referenceChains.h:290-291`) as meaningful only
when `parent_tag == 0` — i.e. only for root-attached entries. Item 3's
re-expansion case has a *non-root* entry Y (with its own non-zero
`parent_tag`) rediscovering an edge to an already-tracked X; overwriting
X's `root_kind` from that context does not, by itself, make X root-attached
(X's `parent_tag` is unrelated to Y and stays whatever it already was).
Before implementing items 1/3, decide explicitly: either (a) restrict the
new mutator so it only ever writes a non-zero `root_kind` when the updating
context is itself a root (i.e. only apply the "durable root" upgrade when
re-enumerating roots directly, not during arbitrary edge re-expansion), or
(b) redefine and re-document the `parent_tag == 0` invariant to cover this
case. Whichever is chosen, Phase 5's test 4 (item 4 below) as written only
exercises the root-vs-root upgrade path (a synthetic stack-local root
losing its frame, then a durable root attaching) — add a second test
exercising the edge-based, non-root-Y re-expansion path from item 3, since
that is the case the invariant conflict actually applies to and it would
otherwise ship untested.

1. **Opportunistic upgrade during root re-enumeration** (design doc point
   3): since Phase 4's root callbacks already run every pass, extend the
   durability tie-break (Phase 4, item 2) to also apply when the object was
   tagged in a *previous* pass, not just within the current pass — i.e.
   drop the "only compare against this pass's admissions" restriction once
   Phase 4 is stable, so a durable root discovered in pass N+1 can overwrite
   a transient `root_kind` recorded in pass N.
2. **Honest labeling in output** (design doc point 2): wherever
   `reconstructChain()`'s `out_root_kind` is surfaced to the event-emission
   path (check `referenceChains.cpp` for callers of `reconstructChain`,
   likely near chain-event construction), tag transient root kinds
   (`STACK_LOCAL`/`JNI_LOCAL`) as "first observed via" rather than "rooted
   by" in whatever user-facing schema/string formatting exists. This is a
   presentation-layer change with no new state.
3. **Bounded rotating re-expansion** (design doc's closing section): add a
   small selection policy that, each pass, feeds a budgeted subset of
   already-`EXPANDED` entries whose `root_kind` is transient back into
   `_pending_expand` (or an equivalent second queue) alongside genuinely new
   frontier entries. Needs:
   - a rotation cursor (persisted across passes, e.g. last-checked tag) so
     the same entries aren't repeatedly picked at the expense of others —
     simplest correct version: iterate `FrontierTable` slots in tag order,
     wrapping, taking up to `R` transient-`root_kind` `EXPANDED` entries per
     pass.
   - reuse of the *same* admission callback (Phase 4 item 2's shared
     `admitObject`/tie-break helper) so re-discovering an edge to an
     already-tracked object during re-expansion applies the same durability
     tie-break instead of being a no-op — this requires checking that the
     "already tagged" branch of the shared admission helper isn't currently
     a hard no-op (per the design doc's explicit callout that today it is,
     for the `FollowReferences` path) and fixing that branch to call the
     tie-break unconditionally, not just on first discovery.
4. Tests: new `ReferenceChainsBfsTest.StaleRootAttributionUpgradesOnRediscovery`-
   style case — admit an object via a synthetic stack-local root, let the
   "frame" go away (no longer enumerable), attach a durable root to the same
   object, run another pass, assert `root_kind` upgraded. Plus a rotation
   coverage test: N transient entries, rotation size R, assert every entry
   gets checked within `ceil(N/R)` passes.

**Exit criteria:** stale-attribution regression test passes; existing
`referenceChains_ut.cpp` suite still green (rotation/upgrade logic must not
change frontier-cap/budget/TTL semantics).

---

## Phase 6 — Shenandoah v1.5 follow-up (explicitly out of v1 scope)

Not part of this implementation pass. Tracked here only so it isn't lost:
per the design doc's addendum, Shenandoah forwarding is plausibly tractable
via a 3-state mark-word check (`get_forwardee_raw_unchecked()`-equivalent,
with the documented null-forwardee guard) since no concurrent mutator races
exist at a safepoint. Would need its own VMStructs declarations for the
mark-word bit layout and its own gating flag alongside `isG1Active()`. ZGC
remains excluded indefinitely (colored-pointer decode is runtime/phase-
dependent state, not a static offset problem — no VMStructs-only solution
exists per the design doc's analysis).

---

## Cross-cutting risks to watch across all phases

- **HotSpot version drift**: every new VMStructs entry (Phases 1-2) is a new
  point of breakage across JDK versions/GC configs. There is **no
  centralized fail-closed convention to copy** — `init_offsets_and_addresses()`
  (`vmStructs.cpp:140-191`) just walks the SA table and fills in whatever it
  finds; it does not itself decide what "unresolved" means for a given
  consumer or fall back to anything. Each existing consumer (e.g.
  `VMKlass::fromOop()`) guards independently at the point of use. This plan
  must therefore *define* a convention for the new oop-map/array/
  compressed-oop entries rather than "match an existing one": expose an
  explicit `bool VMInstanceKlass::available()` (and equivalents for the new
  array/compressed-oops blocks) set false if any required `MATCH_SYMBOLS`
  lookup came back unresolved during `resolveOffsets()`, and make Phase
  0/4's gate check `isG1Active() && VMInstanceKlass::available() && ...`
  before ever taking the manual-walk path — i.e. the new fail-closed
  mechanism is new work for this plan, not a reuse of existing plumbing.
- **CI coverage matrix**: phases 0-4 need CI legs on at least one G1 JDK and
  one non-G1 JDK (Shenandoah or ZGC) to exercise both branches of the Phase
  0 gate. Verified: no `.github/workflows/*.yml` file sets any GC-selecting
  JVM flag today (`grep -rn 'UseG1GC\|UseParallelGC\|UseZGC\|UseShenandoah\|UseSerialGC'
  .github/workflows/` returns zero matches; all JDK legs specify only
  `distribution: zulu`/`java-version: 21` and run on JDK 21's default GC,
  which is G1). A non-G1 leg must be **added from scratch**, not identified
  and wired up from an existing one.
- **Shared-helper refactor risk** (Phase 4 item 2's `admitObject` factoring
  out of `heapReferenceCallback`): this touches the currently-stable
  `FollowReferences` path. Land it as its own small PR with the existing
  test suite as the sole diff-check, before adding any new caller.
