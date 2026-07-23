/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _REFERENCECHAINS_H
#define _REFERENCECHAINS_H

#include "arch.h"
#include "arguments.h"
#include "common.h"
#include "event.h"
#include "painBudget.h"
#include "pidController.h"
#include "spinLock.h"
#include <atomic>
#include <deque>
#include <jni.h>
#include <jvmti.h>
#include <pthread.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// PROF-15341: incremental resumption across passes (see
// ReferenceChainTracker::runPass() below), building on an earlier
// proof-of-concept that established two things end-to-end:
//   1. A cheap "a GC just happened" signal reaches this subsystem via the
//      GarbageCollectionStart/Finish JVMTI callbacks (vmEntry.cpp), mirroring
//      LivenessTracker::onGC() (livenessTracker.cpp:415-426) - just bumping an
//      atomic epoch counter, nothing else.
//   2. JVMTI object tags round-trip a live object across a GC (SetTag/GetTag),
//      via the minimal tagObject()/getTag()/clearTag() helpers below.
// The tag-indexed FrontierTable was added next, followed by the actual heap
// walk (runPass() calling jvmtiEnv::FollowReferences from the heap roots,
// heapReferenceCallback() populating FrontierTable subject to the hop
// cap/budget/frontier cap) - but that walk originally ran as a single,
// non-resumable pass with no cross-pass persistence, no GC-epoch-driven
// scheduling, and no tag release. This revision makes the search resumable
// and terminating:
//   - runPass() now distinguishes a search's first pass (seed
//     FollowReferences from the heap roots, exactly as the original
//     single-pass walk did) from a resumed pass (expandFrontier() below:
//     resolve each not-yet-expanded frontier entry via GetObjectsWithTags -
//     dead ones are pruned for free - then call FollowReferences with that
//     object as initial_object to discover its own outgoing edges,
//     continuing until the per-pass budget or the frontier cap is hit).
//   - The Termination section's cutoffs are enforced across passes: the hop
//     cap already carried over via FrontierEntry::depth; this adds a
//     wall-clock TTL cutoff (_ttl_ms, from first pass) and treats the
//     frontier-size cap as immediate search abandonment rather than a
//     per-pass truncation.
//   - releaseSearchTags() clears (SetTag(obj, 0)) every live tag this search
//     still owns once it completes or is abandoned, without discarding the
//     FrontierTable's own records - reconstructChain() keeps working from
//     memory after the search ends, only the underlying JVMTI tag map entry
//     is released (design doc's Open Question 4 concern about leftover-tag
//     overhead).
//   - shouldRunPass()/threadLoop() implement the Triggering section's pass-
//     scheduling signal (GC-finish epoch advanced, or a fixed cadence
//     elapsed) - see threadLoop()'s own comment for why the thread this runs
//     on is still not spawned by start().
//
// PROF-15341 (doc/architecture/LiveHeapReferenceChains-RemainingWorkPlan.md):
// pollWatchedTargets() below is the LivenessTracker-to-ReferenceChainTracker
// target-selection bridge, closing the gap left by buildChainEvent() having
// no caller. It polls LivenessTracker::selectLeakCandidates()
// (livenessTracker.h's Open Question 3 population-slope ranking) and, for
// each candidate already tagged by an ordinary runPass() walk, reconstructs
// and emits its chain via Profiler::writeReferenceChain(). This is a READ of
// getTag(), never a SetTag seed - see pollWatchedTargets()'s own comment for
// the plan doc's "Correction to the design doc's Open Question 3 mechanism"
// this implements instead of the design doc's original seeding proposal.
//
// `can_tag_objects` and `can_generate_garbage_collection_events` are already
// requested unconditionally in vmEntry.cpp, so this bridging step only adds
// callback wiring and lazy event enablement, not capability requests.
//
// PROF-15341 (doc/architecture/LiveHeapReferenceChains-RemainingWorkPlan.md):
// the pause-time pacing controller replaces the fixed _budget/PASS_CADENCE_NS
// constants' role as the literal per-pass values with a measured
// pause-time-SLO feedback loop (design doc's Open Questions 2/5, "Proposed
// mechanism" paragraphs). runPass() now times its own FollowReferences/
// GetObjectsWithTags call (already the thread blocked inside the safepoint
// those trigger, see the Triggering section) and feeds that duration to
// updatePacing() below, which scales _effective_budget/_effective_cadence_ns
// - the values runPass()/shouldRunPass()/threadLoop() now actually use -
// via this tracker's own PidController instance (_pause_pid). _budget/
// PASS_CADENCE_NS survive as this controller's ceiling/baseline
// respectively, not as the literal per-pass values anymore. See
// updatePacing()'s own comment for the full mechanism, including why its
// gains are not copied from ObjectSampler/MallocTracer/NativeSocketSampler's
// shared triple.
//
// PROF-15341 (doc/architecture/LiveHeapReferenceChains-RemainingWorkPlan.md):
// search restart. Earlier revisions of this class only ever ran a single
// search for the tracker's entire lifetime (runPass()'s own comment used to
// read "starting a *new* search once one ends is not implemented"). That is
// a real gap: LivenessTracker::selectLeakCandidates() only trusts a klass's
// population trend once it has accumulated
// LivenessTracker::KLASS_POPULATION_MIN_FILL_FOR_TREND GC epochs of history
// (livenessTracker.cpp), which takes real wall-clock time - but a
// large-enough-budget search can finish walking the whole reachable graph,
// and permanently stop, before that time has passed. Any object allocated
// after the search already completed is then structurally undiscoverable
// forever, not just unlucky.
//
// The fix: a (re)started search's first pass is now gated on
// LivenessTracker already reporting at least one leak candidate, rather than
// starting unconditionally - by the time a candidate is flagged, the
// underlying object has necessarily survived several epochs already, so a
// fresh root-seeded walk started right then is very likely to still find it
// reachable. restartSearch() (referenceChains.cpp) resets the per-search
// state (frontier table, tag counter, emitted-target set) once a prior
// search reaches COMPLETED/ABANDONED, so shouldRunPass() can treat the next
// candidate-driven trigger exactly like a first-ever search.
//
// Restarting is still an expensive full-heap walk, so canAffordNewSearch()
// also gates it on _pain_budget (PainBudget, painBudget.h) - a leaky bucket
// over the wall-clock cost of past searches, not a fixed cooldown, so a
// search that finished cheaply can restart again soon while an expensive one
// has to wait proportionally longer. This only affects *restarts*: with
// LivenessTracker::gcGenerationsEnabled() off there is no candidate signal
// to gate on at all, so the very first search still starts unconditionally,
// exactly as before this revision - restarting without a leak-detection
// mechanism running would have no signal to justify one.
//
// JVMTI spec restriction: GarbageCollectionStart/Finish run while the VM is
// at a safepoint, and only the Memory Management category (Allocate/
// Deallocate) is allowed from inside them - Heap category calls (SetTag,
// GetTag, GetObjectsWithTags, FollowReferences, IterateThroughHeap) are not.
// onGCStart()/onGCFinish() below must therefore never call anything but the
// atomic counter bump. GCCallbackGuard (referenceChains.cpp) marks this
// thread as "inside the GC callback" for the duration of that bump; the tag
// helpers assert() (debug builds only) that they are never entered while the
// guard is active, as a self-consistency check - it does not catch every way
// this restriction could be violated, only calls routed through this class.
//
// Per-tag frontier metadata state (design doc: Frontier/EdgeStore records).
// FRONTIER->EXPANDED is driven by ReferenceChainTracker::expandFrontier()/
// markAllFrontierExpanded() once an entry's own outgoing edges have
// been visited; FRONTIER/EXPANDED->ABANDONED is driven by expandFrontier()'s
// resolve-or-drop path (dead objects) and releaseSearchTags() (search
// completion/abandonment).
namespace FrontierEntryState {
constexpr u8 FRONTIER = 0;  // discovered, not yet expanded by FollowReferences
constexpr u8 EXPANDED = 1;  // expanded; children (if any) are in the table
constexpr u8 EDGE = 2;      // on a path toward a target sample (EdgeStore)
constexpr u8 ABANDONED = 3; // tag released; entry kept only to avoid reuse
} // namespace FrontierEntryState

// Search-level outcome (design doc's Termination section), distinct from a
// single pass's per-call truncation (ReferenceChainTracker::runPass()'s
// `out_truncated`, unchanged from the original single-pass heap-walk engine):
// a pass can be truncated - budget
// or frontier cap exhausted for *that call* - without the search itself
// being ABANDONED, because there may be nothing left to do (RUNNING is still
// correct) or plenty left for the next pass to pick up. See runPass()'s own
// comment for exactly which conditions move _search_state out of RUNNING.
namespace SearchState {
constexpr u8 RUNNING = 0;   // at least one more pass may still make progress
constexpr u8 COMPLETED = 1; // reachable graph fully explored within caps
constexpr u8 ABANDONED = 2; // TTL or frontier-size cap forced an incomplete stop
} // namespace SearchState

// Records which cutoff actually moved a search from RUNNING to ABANDONED
// (runPass()'s Termination-section decision, referenceChains.cpp) - recorded
// so abandonReason() (and the T_REFERENCE_CHAIN_ABANDONED JFR event built
// from it, see buildAbandonedEvent()) can report *why*, per the design doc's
// "no silent truncation" requirement, rather than just *that* it happened.
// Values match Recording::recordReferenceChainAbandoned()'s kReasons table
// (flightRecorder.cpp) index-for-index.
namespace SearchAbandonReason {
constexpr u8 NONE = 0;         // not (yet) abandoned
constexpr u8 FRONTIER_CAP = 1; // frontier-size cap hit
constexpr u8 TTL = 2;          // wall-clock TTL exceeded with work still pending
} // namespace SearchAbandonReason

// Frontier/EdgeStore record (design doc: "Data structures" /
// "Frontier metadata storage"). Deliberately does not hold a live
// jclass/jobject: retaining either would defeat the point of using
// non-retaining JVMTI tags for frontier identity. `referrer_klass` is a
// StringDictionary id (Profiler::classMap(), profiler.h:260 - the same
// interning table LivenessTracker uses via Profiler::lookupClass(),
// livenessTracker.cpp:120-122) resolved from a class name string; the
// heap-walk engine populates it from GetClassSignature, and FrontierEntry
// only needs the field.
typedef struct FrontierEntry {
  jlong parent_tag;    // links back to the record that discovered this one
  u32 referrer_klass;  // StringDictionary id, 0 = unresolved/none
  u32 depth;           // hop count from the frontier's seed, for the hop cap
  u8 state;            // one of FrontierEntryState's constants
  // jvmtiHeapReferenceKind of the edge that admitted this entry, but only
  // meaningful when parent_tag == 0 (this entry is root-attached) - 0 (no
  // JVMTI_HEAP_REFERENCE_* value is 0) for every other entry, since a
  // non-root entry's own referrer edge kind is not what
  // reconstructChain()'s callers want to report (they want to label the
  // chain's root, not every hop). Set by heapReferenceCallback()
  // (referenceChains.cpp) at insert() time.
  u8 root_kind;
} FrontierEntry;

// Durability ranking for FrontierEntry::root_kind (design doc's "Fix for
// root-attribution staleness" point 1 / this plan's Phase 5 item 1): higher
// is more durable. Used to decide whether a newly-observed root reference to
// an already-admitted, root-attached entry should replace its recorded
// root_kind rather than keeping whichever root happened to be enumerated
// first. Only the three tiers the design doc actually names are ranked with
// confidence ("static/class/CLD > JNI global > JNI local/stack local/
// monitor"); JVMTI_HEAP_REFERENCE_THREAD and _OTHER have no documented tier
// and are conservatively bucketed with the least-durable tier rather than
// assumed durable.
inline int rootKindDurability(u8 root_kind) {
  switch (root_kind) {
  case JVMTI_HEAP_REFERENCE_STATIC_FIELD:
  case JVMTI_HEAP_REFERENCE_SYSTEM_CLASS:
    return 3;
  case JVMTI_HEAP_REFERENCE_JNI_GLOBAL:
    return 2;
  case JVMTI_HEAP_REFERENCE_MONITOR:
  case JVMTI_HEAP_REFERENCE_STACK_LOCAL:
  case JVMTI_HEAP_REFERENCE_JNI_LOCAL:
  case JVMTI_HEAP_REFERENCE_THREAD:
  case JVMTI_HEAP_REFERENCE_OTHER:
    return 1;
  default:
    return 0; // root_kind's own "not set"/non-root-attached value
  }
}

// True for the two root kinds the design doc calls "first observed via"
// rather than "rooted by" evidence (design doc point 2): a stack-local or
// JNI-local reference is only alive for as long as its owning frame/handle
// scope is on some thread's stack, so an entry admitted through one is
// always a candidate both for a durability upgrade (rootKindDurability()
// above) and for the softer output label (flightRecorder.cpp's
// rootKindName()) and for Phase 5's bounded rotating re-expansion
// (ReferenceChainTracker::collectStaleRootKindEntriesForRotation()).
inline bool isTransientRootKind(u8 root_kind) {
  return root_kind == JVMTI_HEAP_REFERENCE_STACK_LOCAL ||
         root_kind == JVMTI_HEAP_REFERENCE_JNI_LOCAL;
}

// Tag-indexed slot table storing FrontierEntry metadata, modeled on
// LivenessTracker's TrackingEntry table (livenessTracker.h:21-30): CAS-safe
// doubling resize under a signal-safe SpinLock (spinLock.h), reusing its
// shared/exclusive split so reads (lookup) never race a resize.
//
// Structural difference from LivenessTracker's table: the slot index is the
// JVMTI tag value itself (tag - 1), not an externally-assigned array
// position. This works because ReferenceChainTracker::nextTag() hands out
// tags sequentially starting at 1 and never reuses one, so each
// tag maps to exactly one slot for the table's lifetime.
//
// Capacity is an explicit constructor parameter (wired from
// Arguments::_reference_chains_frontier_cap), not derived from heap
// size the way LivenessTracker sizes its table (livenessTracker.cpp:152-176)
// - the design doc explicitly flags that sizing formula as non-transferable
// to a BFS frontier (Open Question 2: frontier width is driven by per-hop
// fan-out, not an allocation sampling rate). Only the doubling-resize
// *mechanics* are reused from LivenessTracker, not its sizing heuristic.
//
// Concurrency: unlike LivenessTracker::track() (called from the allocation
// sampling hot path, which must never block), FrontierTable::insert()/
// clear()/markEdge()/markExpanded() are only ever called from the single
// agent-owned BFS thread (design doc's Algorithm; the heap-walk engine), so
// they use the blocking exclusive lock() rather than LivenessTracker's
// non-blocking tryLockShared() bailout - exclusive, not shared, so a writer
// actually excludes a concurrent lookup() reader instead of merely
// serializing against other writers. lookup() may still be called
// concurrently from a reader walking parent_tag links (e.g. chain
// reconstruction), hence the shared lock there: shared mode only ever
// contends with other shared-mode readers, never with a writer's exclusive
// lock.
class alignas(alignof(SpinLock)) FrontierTable {
private:
  // Provisional default pending empirical tuning (see
  // doc/architecture/LiveHeapReferenceChains-ImplementationPlan.md) - not
  // benchmark-derived. Reuses LivenessTracker's doubling-resize *mechanics*
  // (growLocked() below), but this starting size is a conservative guess,
  // not scaled from LivenessTracker's own initial size (which that class
  // derives from max_heap/sampling_interval, a formula the design doc
  // explicitly flags as non-transferable to a BFS frontier - see
  // arguments.h's DEFAULT_REFERENCE_CHAINS_FRONTIER_CAP comment). Small
  // enough to avoid over-allocating for a search that never grows a wide
  // frontier, large enough to avoid the first several growLocked() calls
  // for an ordinary one; a future frontier-table peak-occupancy
  // measurement pass is the intended way to replace this guess.
  static constexpr int INITIAL_TABLE_CAPACITY = 1024;

  // mutable: capacity()/maxCapacity() below are const accessors that still
  // need to take this lock to read _table_cap/_table_max_cap safely.
  mutable SpinLock _table_lock;
  // 1 + highest index ever inserted (informational upper bound for
  // lookup(); never shrinks, since tags/slots are never reused). atomic
  // (not volatile) because insert() updates it via a CAS loop concurrently
  // with plain reads from size()/resetForRestart() - a volatile int mixed
  // with __sync_bool_compare_and_swap has no synchronizes-with edge under
  // the C++ memory model, so those plain reads and the CAS are a genuine
  // data race (caught by TSAN), even though relaxed/informational
  // semantics are all that's needed here.
  std::atomic<int> _table_size;
  int _table_cap;
  int _table_max_cap;
  FrontierEntry *_table;

  // Grows _table (doubling) until it holds at least `required_cap` slots or
  // _table_max_cap is reached. Must be called with _table_lock held
  // exclusively. Returns false (capacity exhausted) without partially
  // resizing if `required_cap` exceeds _table_max_cap.
  bool growLocked(int required_cap);

public:
  // `max_cap` <= 0 disables the table (capacity() stays 0, every insert()
  // reports exhaustion) - callers are expected to guard on the config flag
  // before constructing one, but this makes a misconfigured cap fail safe
  // rather than crash.
  explicit FrontierTable(int max_cap);
  ~FrontierTable();

  FrontierTable(const FrontierTable &) = delete;
  FrontierTable &operator=(const FrontierTable &) = delete;

  // Writes (parent_tag, referrer_klass, depth, state) into the slot for
  // `tag` (index = tag - 1), growing the table if needed. Returns false
  // without writing anything if `tag` is not positive, or the table is
  // already at max_cap and still too small for this tag - the design doc's
  // frontier-size-cap requirement is "stop admitting new entries and report
  // it", so this reports failure to the caller rather than crashing or
  // silently dropping the write.
  // `root_kind` is the jvmtiHeapReferenceKind of the admitting edge - only
  // meaningful when `parent_tag == 0` (see FrontierEntry::root_kind's own
  // comment); callers that are not admitting a root-attached entry can
  // leave it at the default 0.
  bool insert(jlong tag, jlong parent_tag, u32 referrer_klass, u32 depth,
              u8 state = FrontierEntryState::FRONTIER, u8 root_kind = 0);

  // Reads the slot for `tag` into *out. Returns false (leaving *out
  // untouched) if `tag` is not positive or has never been inserted.
  bool lookup(jlong tag, FrontierEntry *out);

  // Marks the slot for `tag` as ABANDONED in place. This is only the
  // metadata-table side of tag release (design doc's Termination section);
  // the caller is still responsible for SetTag(obj, 0) via
  // ReferenceChainTracker::clearTag() - clear() here does not touch JVMTI.
  // No-op if `tag` was never inserted.
  void clear(jlong tag);

  // Marks the slot for `tag` as EDGE in place (design doc: "on a path
  // toward a target sample (EdgeStore)"). No-op if `tag` was never
  // inserted. Used by reconstructChain() below to mark every hop it walks.
  void markEdge(jlong tag);

  // Marks the slot for `tag` as EXPANDED in place (design doc: "expanded;
  // children (if any) are in the table") - the resumed-pass counterpart to
  // markEdge(): ReferenceChainTracker::expandFrontier() calls this
  // once an entry's own outgoing edges have been fully visited by a
  // FollowReferences(initial_object=<this entry's object>) call, so a later
  // pass's scan for pending work (which only considers FRONTIER-state
  // entries) skips it. No-op if `tag` was never inserted.
  void markExpanded(jlong tag);

  // Overwrites the slot for `tag`'s root_kind in place, touching no other
  // field - the durability-upgrade counterpart to insert()'s one-time
  // root_kind write (design doc's "opportunistic upgrade during root
  // re-enumeration", Phase 5 item 1). No-op if `tag` was never inserted.
  //
  // Callers MUST only invoke this when the update itself originates from a
  // root discovery (a root callback rediscovering an already-tagged object
  // as a heap root), never from an ordinary edge admission/re-expansion -
  // and only on an entry that is already root-attached (parent_tag == 0).
  // FrontierEntry::root_kind is documented as meaningful only when
  // parent_tag == 0; this mutator does not itself touch parent_tag, so
  // calling it from a non-root discovery context (e.g. FieldWalker's
  // edge-driven re-expansion rediscovering an edge to an already-tracked,
  // non-root-attached object) would silently leave a non-zero root_kind on
  // an entry nothing else treats as root-attached. See
  // ReferenceChainTracker::maybeUpgradeRootAttachedRootKind() (the sole
  // caller) for how this is enforced.
  void updateRootKind(jlong tag, u8 root_kind);

  // Walks parent_tag links starting at `target_tag` back to a root-attached
  // entry (parent_tag == 0), appending each visited entry's referrer_klass
  // to *out_chain in leaf-to-root order, and marking each visited entry
  // EDGE via markEdge() - this table's degenerate EdgeStore (design doc:
  // "a chain can be walked back from a target sample to a root by
  // following parent_tag across EdgeStore records"). Returns false (leaving
  // *out_chain untouched) if target_tag was never inserted. Bounds the walk
  // at maxCapacity() hops as a defensive guard against a corrupted/cyclic
  // parent_tag chain - nextTag() only ever hands out a strictly larger value
  // than any tag already assigned (true across resumed passes too, not just
  // within one), so a child's parent_tag always points at an
  // already-existing, strictly smaller tag and a cycle should be
  // unreachable in practice; this is not a correctness dependency.
  //
  // `out_root_kind` (if non-null) receives the root-attached entry's own
  // FrontierEntry::root_kind - the jvmtiHeapReferenceKind of whichever edge
  // first admitted this chain into the frontier, letting a caller label the
  // chain with why it is reachable at all (JNI global, thread stack, static
  // field, ...) instead of just how (the referrer_klass hops in *out_chain).
  bool reconstructChain(jlong target_tag, std::vector<u32> *out_chain,
                        u8 *out_root_kind = nullptr);

  // Search restart (ReferenceChainTracker::restartSearch(), this class's own
  // header comment): marks every slot unoccupied again without releasing
  // _table's allocation - a new search's nextTag() sequence restarts at 1,
  // reusing these same slot indices, so lookup()/insert() must not read back
  // the previous search's now-irrelevant entries for them. Safe to call
  // only once releaseSearchTags() has already cleared every live JVMTI tag
  // this search owned (restartSearch()'s own caller ordering) - this method
  // has no way to release tags itself, it only forgets the metadata table's
  // record of them.
  void resetForRestart() {
    _table_lock.lock();
    _table_size.store(0, std::memory_order_relaxed);
    _table_lock.unlock();
  }

  // Debug-only test seam (ReferenceChainTracker::resetSearchStateForTest()).
  // Unlike resetForRestart(), which only forgets this table's occupancy,
  // this discards the table's whole allocation and rebuilds it at
  // `max_cap` - the only way to undo the "sized once, on the first start()
  // in this JVM" capacity choice (this class's own constructor comment)
  // that a differently-configured test running earlier in the same,
  // no-forkEvery JVM (ProfilerTestPlugin.kt) would otherwise leave every
  // later test permanently stuck with. Defined in referenceChains.cpp
  // alongside the constructor it mirrors.
  void resetCapacityForTest(int max_cap);

  // _table_cap/_table_max_cap are plain ints, not atomics like _table_size,
  // and resetCapacityForTest() (debug-only test seam, see its own comment)
  // rewrites both under _table_lock after freeing/reallocating _table. Every
  // other reader of these fields (growLocked() and its callers) already
  // holds _table_lock; these two accessors take it too so a concurrent
  // resetCapacityForTest() during shared-JVM test overlap can't race an
  // unsynchronized read here.
  int capacity() const {
    _table_lock.lock();
    int cap = _table_cap;
    _table_lock.unlock();
    return cap;
  }
  int maxCapacity() const {
    _table_lock.lock();
    int max_cap = _table_max_cap;
    _table_lock.unlock();
    return max_cap;
  }

  // Current upper bound on assigned slots (mirrors _table_size's own
  // comment: "1 + highest index ever inserted"). expandFrontier()
  // uses this to know how far a resumed pass's scan for FRONTIER-state
  // entries needs to go. Relaxed/informational like _table_size itself: a
  // concurrent insert() racing this read only makes the caller's scan
  // window one tag short for this call, which self-corrects on the next
  // call once _table_size has caught up.
  int size() const { return _table_size.load(std::memory_order_relaxed); }
};

// Tag-indexed table mapping a *class* tag (see
// ReferenceChainTracker::nextClassTag() - always negative, a namespace
// disjoint from the positive FrontierTable object tags above so a raw tag
// value alone always tells the heap-walk callback which table it belongs
// to) to the StringDictionary id of that class's resolved name
// (Profiler::classMap(), the same interning table LivenessTracker uses via
// Profiler::lookupClass(), livenessTracker.cpp:120-122 - see Open Item 2 in
// the implementation plan).
//
// Populated once per loaded class by
// ReferenceChainTracker::resolveLoadedClasses() - a GetLoadedClasses() +
// GetClassSignature() pass run *before* FollowReferences starts, specifically
// so heapReferenceCallback() (referenceChains.cpp) never needs a class-name
// lookup of its own: GetClassSignature is a JNI/Class-category call, and the
// JVMTI spec forbids Heap-callback functions like heapReferenceCallback from
// calling anything but "callback safe" functions (see the header comment
// above) - resolving names inline inside the callback is not an option.
//
// Concurrency: like FrontierTable, only ever touched by the single
// agent-owned BFS thread (design doc's Algorithm "Thread" bullet), so no locking is
// needed - unlike FrontierTable there is also no cross-thread reader to
// guard against (chain reconstruction only needs FrontierTable).
class ClassTagTable {
private:
  std::unordered_map<jlong, u32> _table;

public:
  void insert(jlong class_tag, u32 dict_id) { _table[class_tag] = dict_id; }

  // Returns the StringDictionary id for `class_tag`, or 0 if it was never
  // inserted (0 is StringDictionary's own "no entry" sentinel too, so this
  // composes with FrontierEntry::referrer_klass's documented 0 =
  // unresolved/none convention without a separate "found" out-parameter).
  u32 resolve(jlong class_tag) const {
    auto it = _table.find(class_tag);
    return it != _table.end() ? it->second : 0;
  }

  size_t size() const { return _table.size(); }

  // Drops every cached class_tag -> dict_id mapping - used when the
  // underlying StringDictionary itself was reset (see
  // ReferenceChainTracker::_last_class_map_generation's comment) and every
  // id here now points at a namespace that no longer exists.
  void clear() { _table.clear(); }
};

// Singleton shape mirrors LivenessTracker (livenessTracker.h).
class ReferenceChainTracker {
  // Test-only accessor (referenceChains_ut.cpp), mirroring vmEntry.h's
  // VMTestAccessor pattern: since instance() is a process-wide singleton,
  // the search-lifecycle fields (_search_state/_search_started/etc.)
  // would otherwise leak across separate TEST_F cases in the same gtest
  // binary. The accessor resets them back to their just-constructed values
  // between tests; it does not change any production behavior.
  friend class ReferenceChainsTestAccessor;

private:
  bool _enabled;

  // Frontier metadata table. Constructed lazily on the first
  // start() with the flag enabled, sized from
  // args._reference_chains_frontier_cap; like LivenessTracker's table
  // (livenessTracker.cpp:209-210) it survives stop() so it persists across
  // multiple start/stop recording cycles.
  FrontierTable *_frontier;

  // args._reference_chains_frontier_cap as of the most recent start() call -
  // recorded unconditionally (even once _frontier already exists and start()
  // itself skips reconstructing it), so resetSearchStateForTest() has
  // something to rebuild the table at other than whatever cap the first
  // start() in this JVM happened to use (see _frontier's own comment).
  int _configured_frontier_cap;

  // Class-tag -> StringDictionary id table. Populated by
  // resolveLoadedClasses(), read by heapReferenceCallback(). Survives
  // stop()/start() cycles for the same reason _frontier does - a class,
  // once resolved, does not need re-resolving just because the profiler
  // recording was restarted - UNLESS the underlying dictionary itself was
  // reset (see _last_class_map_generation below), in which case every id
  // cached here is for an id namespace that no longer exists.
  ClassTagTable _class_tags;

  // Profiler::classMap()'s generation as of the last resolveLoadedClasses()
  // call. Profiler::start() calls _class_map.clearAll() (profiler.cpp)
  // whenever `reset || _start_time == 0`, which restarts that
  // StringDictionary's id namespace at 1 - but a class's JVMTI-level
  // class-object tag (GetTag(klass, ...)) is JVM-level state, untouched by
  // that reset, so resolveLoadedClasses()'s "already tagged -> already
  // resolved, skip it" check (tag == 0) would otherwise keep _class_tags
  // pointing at ids from a dictionary generation that clearAll() already
  // wiped. resolveLoadedClasses() compares this against
  // Profiler::instance()->classMap()->generation() and, on a mismatch,
  // re-resolves every loaded class's name (reusing its existing tag rather
  // than assigning a new one) instead of only the untagged ones - see that
  // method's own comment. Initialized to 0 (StringDictionary's own initial
  // generation), not a sentinel, since a resolveLoadedClasses() call before
  // any clearAll() has ever run must NOT treat that as a mismatch.
  u64 _last_class_map_generation;

  // GetLoadedClasses() count as of the last resolveLoadedClasses() call that
  // actually ran its per-class GetTag()/GetClassSignature() scan - lets that
  // method skip the scan entirely on a resumed pass where the loaded-class
  // count has not CHANGED (see resolveLoadedClasses()'s own comment for why
  // this must be an equality check, not just a "grew" check: the count is
  // not monotonic once class unloading is in play). Survives stop()/start()
  // cycles for the same reason _class_tags does. Written and read only from
  // the single BFS thread, like _last_pass_gc_finish_epoch. Forced to -1
  // (a value class_count, always >= 0, can never equal) by a
  // _last_class_map_generation mismatch, so the scan is never skipped on the
  // very call that must re-resolve every already-tagged class.
  int _last_resolved_class_count;

  // "GC just happened" signals. Bumped only from onGCStart()/onGCFinish();
  // gcFinishEpoch() is now read by shouldRunPass() as one of the
  // two pass-scheduling triggers (design doc's Triggering section).
  volatile u64 _gc_start_epoch;
  volatile u64 _gc_finish_epoch;

  // Monotonically increasing tag source for frontier objects. 0 is reserved
  // (JVMTI convention: an untagged object reads back tag 0, and
  // SetTag(obj, 0) clears a tag), so this starts at 1. Always hands out
  // positive values - see nextClassTag() below for why classes use a
  // disjoint (negative) range instead of sharing this counter.
  volatile jlong _next_tag;

  // Monotonically increasing *magnitude* source for class tags; nextClassTag()
  // negates it before handing it out. Kept separate from _next_tag (rather
  // than tagging classes from the same positive sequence) so
  // heapReferenceCallback() can tell "is this tag a class I pre-tagged, or a
  // frontier object?" from the tag's sign alone, with no extra table lookup -
  // load-bearing for the "never expand from a class's own metadata graph"
  // rule documented on heapReferenceCallback() below.
  volatile jlong _next_class_tag_magnitude;

  // Per-pass tunables, copied from Arguments in start() (design doc: Open
  // Question 2 defaults, from the config-flag scaffolding). A future
  // measurement pass will decide whether/how these can change between passes
  // of the same search; for now this only needs one fixed value per
  // start()/stop() cycle, exactly like LivenessTracker's _subsample_ratio
  // (livenessTracker.h:52).
  int _hop_cap;
  int _budget;

  // Edge budget for just the search's one-shot, root-seeded first pass
  // (runPass()'s !_search_started branch) - copied from
  // Arguments::_reference_chains_first_pass_budget in start(), auto-scaled
  // from _budget (AUTO_FIRST_PASS_BUDGET_MULTIPLIER, capped at
  // AUTO_FIRST_PASS_BUDGET_CAP) when unset (0), rather than falling back to
  // plain _budget: a steady-state per-pass budget sized for cheap incremental
  // expansion truncates a cold root-seeded walk of a real JVM's object graph
  // long before it reaches anything interesting (see
  // ddprof-stresstest's ReferenceChainLeakDemo, whose whole class comment is
  // about exactly this trap). That single FollowReferences(0, nullptr,
  // nullptr, ...) call enumerates every GC root in one JVMTI-controlled
  // order and never gets to revisit whichever roots it did not reach before
  // this budget ran out - every later pass only expands forward from
  // already-admitted frontier entries (expandFrontier()'s own comment), so a
  // root missed here stays unreachable for the rest of the search. Unlike
  // _budget/_effective_budget, this is spent at most once per search, not
  // once per pass, so a much larger ceiling is affordable without the
  // per-pass pacing controller (updatePacing()) ever seeing it - runPass()
  // deliberately excludes the first pass's own duration from that signal
  // (see runPass()'s own comment) so a large first-pass cost cannot throttle
  // down every cheap expansion pass that follows.
  int _first_pass_budget;

  // Wall-clock TTL, copied from Arguments in start() (design doc's
  // Termination section: "a hard cap on passes-per-search or wall-clock TTL
  // from first observation"). This implements the TTL half of that
  // "or" - the config-flag scaffolding only added a TTL sub-option (no
  // separate pass-count cap), and Open Question 2 leaves the choice between
  // the two open pending a future measurement pass. <= 0 disables the TTL
  // cutoff (a search can only still end via the frontier-size cap or natural
  // completion).
  long _ttl_ms;

  // Pause-time pacing controller: pause-time-SLO ceiling copied from
  // Arguments in start() (Arguments::_reference_chains_pause_target_ms) -
  // the "single target ceiling" the plan asks for in place of guessing
  // _budget/PASS_CADENCE_NS directly. Used only to (re)construct _pause_pid
  // in start(); updatePacing() itself never reads it again, since it lives
  // inside _pause_pid's own _target once constructed.
  long _pause_target_ms;

  // Pause-time pacing controller: the actual per-pass budget runPass() passes
  // to FollowReferences/expandFrontier(), replacing _budget's old role as a
  // literal per-pass value - _budget above becomes this controller's ceiling
  // instead (never exceeded, see updatePacing()), while this field is what
  // updatePacing() actually raises/lowers pass to pass. Starts at _budget in
  // start(), so a tracker that has not measured a pass yet behaves exactly as
  // before the pacing controller was added.
  int _effective_budget;

  // Pause-time pacing controller: the actual fallback cadence
  // shouldRunPass()/threadLoop() compare against, replacing the fixed
  // PASS_CADENCE_NS constant below in that role once updatePacing() starts
  // adjusting it - see PASS_CADENCE_NS's own comment for why that constant
  // survives as this field's starting value rather than being deleted
  // outright.
  u64 _effective_cadence_ns;

  // Pause-time pacing controller: this tracker's own PidController instance -
  // see updatePacing()
  // below for the full mechanism, and PASS_CADENCE_NS's neighboring
  // constants for why its gains are not copied from ObjectSampler/
  // MallocTracer/NativeSocketSampler's shared triple. Placeholder-constructed
  // here (target=1, unit gains); start() reconstructs it once
  // _pause_target_ms is known, mirroring RateLimiter's own
  // placeholder-then-reconstruct pattern (rateLimiter.h's
  // `_pid{1, 1.0, 1.0, 1.0, 1, 1.0}` member default, replaced in
  // RateLimiter::start()).
  PidController _pause_pid;

  // Search lifecycle state. _search_started distinguishes a search's first
  // pass (seed FollowReferences from the heap roots) from a resumed pass
  // (expand the persisted frontier, see expandFrontier()) - runPass() below.
  // _search_state starts RUNNING and only ever moves forward (RUNNING ->
  // COMPLETED or RUNNING -> ABANDONED, never back) - see runPass()'s comment
  // for the exact conditions. Both fields are written only by runPass(),
  // called from the single agent-owned BFS thread, but are read cross-thread
  // by searchState()/buildAbandonedEvent() (called from Profiler::dump(),
  // e.g. profiler.cpp's JFR-flush path) - so, like _gc_start_epoch/
  // _gc_finish_epoch above, they are volatile and accessed via load()/
  // store() rather than a plain load/store the compiler could reorder or
  // cache across threads.
  bool _search_started;
  volatile u8 _search_state;

  // True once releaseSearchTags() has confirmed every live tag this search
  // owned was actually cleared (or there were none) - see that method's own
  // comment for why a GetObjectsWithTags() failure must NOT be treated as
  // "released". Starts true (nothing to release for a not-yet-run search);
  // set false the moment a search reaches a terminal state and is only ever
  // reset back to true once releaseSearchTags() itself confirms success -
  // possibly across several retried runPass() calls first, see runPass()'s
  // terminal-state branch. shouldRunPass() refuses to restartSearch() while
  // this is false, so _next_tag/the frontier table are never reset out from
  // under a search whose tags might still be live. Written and read only
  // from the single BFS thread (runPass()/shouldRunPass()), like
  // _search_started above, so no volatile/load()/store() is needed.
  bool _tags_released;

  // Set (once) at the same point runPass() moves _search_state to ABANDONED -
  // see SearchAbandonReason's own comment for why this exists and
  // buildAbandonedEvent()/abandonReason() below for how it is read. Same
  // cross-thread read pattern as _search_state above.
  volatile u8 _abandon_reason;

  // Wall-clock timestamp (OS::nanotime()) of the search's first pass -
  // baseline for the TTL cutoff above. Set once, in runPass(), the first
  // time _search_started flips true; read cross-thread by
  // buildAbandonedEvent() (elapsed-time calculation), so volatile/load()-
  // accessed like _search_state above.
  volatile u64 _search_start_ns;

  // Tags currently in FrontierEntryState::FRONTIER (admitted but not yet
  // expanded), in admission order. Pushed by heapReferenceCallback() at the
  // moment it admits a tag (both for the first pass's root-seeded walk and
  // for expandFrontier()'s own per-node FollowReferences calls, since both
  // share that one callback), popped by expandFrontier()/
  // markAllFrontierExpanded() as entries are expanded. This replaces a
  // former O(range) scan over every tag between a cursor and the frontier's
  // current size just to filter down to the FRONTIER-state subset - a scan
  // whose cost was proportional to everything admitted since the cursor
  // last advanced, not to what was actually pending, so a pass immediately
  // following a large one-shot admission (e.g. a restart's first pass) paid
  // for the whole batch just to discover a handful of genuinely pending
  // entries. Only ever touched from the single BFS thread that runs
  // heapReferenceCallback()/expandFrontier(), so no locking is needed.
  std::deque<jlong> _pending_expand;

  // Rotation cursor for collectStaleRootKindEntriesForRotation() (Phase 5
  // item 3): 1-based tag to resume scanning from on the next call, so
  // consecutive calls sweep forward through the table instead of always
  // re-examining the same low-tag entries first. Wraps back to 1 once it
  // reaches _frontier->size(). Persisted across passes (not per-search-reset
  // by ReferenceChainsTestAccessor::reset(), same as _next_tag is not reset
  // by restartSearch() logic elsewhere) since a stale cursor value only ever
  // costs one wasted scan step before self-correcting, never a correctness
  // problem.
  jlong _root_kind_rotation_cursor;

  // Per-pass cap on how many transient-root_kind entries
  // collectStaleRootKindEntriesForRotation() selects - round, provisional
  // like this subsystem's other unbenchmarked constants (see e.g.
  // MIN_EFFECTIVE_BUDGET's own comment): small enough that a pass dominated
  // by rotation work never meaningfully competes with genuinely new
  // discoveries for the same pass's budget, large enough that a search with
  // a modest number of transient roots converges to durable attribution
  // within a handful of passes rather than needing hundreds.
  static constexpr int ROOT_KIND_ROTATION_BUDGET = 16;

  // Snapshot of gcFinishEpoch() as of the end of the last pass. Written only
  // by runPass(), read only by shouldRunPass() - both always called from the
  // same thread (the BFS thread once wired up, or directly by a caller/test
  // standing in for it), so no locking is needed.
  u64 _last_pass_gc_finish_epoch;

  // OS::nanotime() as of the end of the last pass. Written by runPass() on
  // the BFS thread; also read cross-thread by buildAbandonedEvent()'s
  // elapsed-time calculation, so volatile/load()-accessed like
  // _search_state above.
  volatile u64 _last_pass_ns;

  // Total passes run this search. Written by runPass() on the BFS thread;
  // read cross-thread by passesRun()/buildAbandonedEvent(), so volatile/
  // load()-accessed like _search_state above.
  volatile int _passes_run;

  // Target-selection bridging step: which FrontierTable target_tags
  // pollWatchedTargets() has already reconstructed and emitted a
  // datadog.ReferenceChain event for this search - so a klass LivenessTracker
  // keeps flagging across multiple consecutive polls does not re-emit the
  // same chain repeatedly (the plan's own de-duplication requirement for this
  // bridging step). _emitted_search_start_ns remembers which
  // search's _search_start_ns this set corresponds to; pollWatchedTargets()
  // clears the set whenever _search_start_ns no longer matches it - the
  // signal that restartSearch() (below) began a new search, so a klass whose
  // chain was already emitted by the now-finished search is eligible to be
  // re-emitted by the new one.
  std::unordered_set<jlong> _emitted_target_tags;
  u64 _emitted_search_start_ns;

  // Search restart (this class's own header comment): leaky bucket over the
  // wall-clock cost of past searches, gating how soon a *restarted* search
  // may take its first pass - see PainBudget's own comment (painBudget.h)
  // and canAffordNewSearch() below. _search_pain_ms accumulates the current
  // search's own cost (each pass's pass_wall_ticks, converted to ms) as it
  // runs; restartSearch() spends the total into _pain_budget and zeroes this
  // back out for the next search. Constructed with the configured refill
  // rate in start(), mirroring _pause_pid's own placeholder-then-reconstruct
  // pattern.
  PainBudget _pain_budget;
  u64 _search_pain_ms;

  // Queue of chain events pollWatchedTargets() has reconstructed but not
  // yet written to a Recording. pollWatchedTargets() runs on this tracker's
  // own BFS scheduling thread; Profiler::writeReferenceChain() (profiler.cpp)
  // can block that thread for up to ~50ms per event under lock contention on
  // the shared _locks[] pool, which would delay the next scheduled BFS pass
  // (its own comment on that call site explains why the blocking retry is
  // needed at all). Queuing here instead - a plain push_back under a
  // dedicated SpinLock, no JVMTI/JNI/blocking call - keeps pollWatchedTargets()
  // itself non-blocking; the actual write is drained on whatever thread calls
  // Profiler::dump(), exactly mirroring how buildAbandonedEvent()'s output is
  // already deferred to that same call site rather than written eagerly.
  // Capped at MAX_PENDING_CHAIN_EVENTS - a search that emits faster than
  // dump() is called drops the oldest queued event (best-effort, the same
  // trade-off this subsystem's other bounded tables already accept) rather
  // than growing without bound; REFERENCE_CHAIN_EVENTS_DROPPED (counters.h)
  // makes that loss observable instead of silent. 256 matches this
  // subsystem's own table-sizing convention elsewhere (livenessTracker.h's
  // MAX_KLASS_POPULATION_ENTRIES) - comfortably above the number of distinct
  // klasses selectLeakCandidates() could ever have flagged across a search's
  // lifetime (bounded by that same 256-entry table), so an ordinary dump
  // cadence should never need the eviction path at all.
  static constexpr int MAX_PENDING_CHAIN_EVENTS = 256;
  std::vector<ReferenceChainEvent> _pending_chain_events;
  SpinLock _pending_chain_events_lock;

  // Fallback cadence for shouldRunPass()'s cadence trigger (design doc's
  // Triggering section / Open Question 5). Provisional default pending
  // empirical tuning (see
  // doc/architecture/LiveHeapReferenceChains-ImplementationPlan.md) - not
  // benchmark-derived: a round one-second value chosen only so an idle
  // search still makes some progress between GC-triggered wakeups without
  // polling so tightly that an idle tracker burns CPU. The pause-time pacing
  // controller folds Open Question 5's cadence decision into updatePacing()
  // below rather than solving it separately (design doc's explicit "one
  // shared mechanism" framing): this constant now only serves as
  // _effective_cadence_ns's starting value (start()) and as the unit
  // MAX_EFFECTIVE_CADENCE_NS below scales from - shouldRunPass()/threadLoop()
  // themselves compare against _effective_cadence_ns, not this constant
  // directly, once a pass has run.
  static constexpr u64 PASS_CADENCE_NS = 1000000000ULL; // 1s

  // Auto-scaled default for _first_pass_budget when
  // Arguments::_reference_chains_first_pass_budget is unset (0) - see
  // _first_pass_budget's own comment for why plain _budget is the wrong
  // fallback. 50x is a round, provisional guess (same status as every other
  // _reference_chains* constant here), picked to comfortably clear a cold
  // JVM's root set without needing firstpassbudget spelled out explicitly for
  // every reasonably-sized heap; the cap keeps a pathologically large
  // _budget (e.g. an operator-supplied 100000) from ballooning the first
  // pass's own one-shot cost unbounded.
  static constexpr int AUTO_FIRST_PASS_BUDGET_MULTIPLIER = 50;
  static constexpr int AUTO_FIRST_PASS_BUDGET_CAP = 200000;

  // Pause-time pacing controller: bounds and conversion constants for
  // updatePacing()'s budget/cadence adjustment - see that method's own
  // comment for the full mechanism. Every value here is a round, provisional
  // guess like every other _reference_chains* constant in this codebase
  // (arguments.h's own DEFAULT_REFERENCE_CHAINS_* header comment sets the
  // pattern) - a future benchmark plan is the intended path to replacing
  // all of them with measured values, not a design decision made here.
  //
  // Floor updatePacing() will never shrink _effective_budget below (clamped
  // further down to _budget itself when the configured budget is smaller
  // than this floor - see updatePacing()). Not 0: a floor of 0 would let a
  // single pathological pass shrink the search to "admit nothing, ever",
  // stalling all progress instead of just slowing it.
  static constexpr int MIN_EFFECTIVE_BUDGET = 50;

  // Bounds for _effective_cadence_ns. The lower bound is not 0: threadLoop()
  // sleeps for exactly this many nanoseconds each loop iteration (below), so
  // a true 0 would busy-loop the BFS thread. The upper bound reuses
  // PASS_CADENCE_NS (this field's own pre-pacing-controller baseline) as the unit for
  // a round, provisional multiplier, so a search that is persistently over
  // the pause-time ceiling still makes some progress rather than backing
  // off indefinitely.
  static constexpr u64 MIN_EFFECTIVE_CADENCE_NS = 10000000ULL;      // 10ms
  static constexpr u64 MAX_EFFECTIVE_CADENCE_NS = PASS_CADENCE_NS * 4; // 4s

  // Conversion factor from "edges of budget signal updatePacing()'s clamp
  // could not absorb" to a cadence adjustment in nanoseconds - the two are
  // different units (edge count vs. wall-clock time) with no natural
  // exchange rate, so this is a round, provisional choice: large enough
  // that a sustained, deeply-saturated overflow visibly moves the cadence
  // within a handful of passes, small enough that a single borderline pass
  // does not swing the whole cadence range at once.
  static constexpr u64 CADENCE_NS_PER_EDGE_OVERFLOW = 1000000ULL; // 1ms/edge

  // Agent-owned BFS thread (design doc's Triggering section: "an agent-owned,
  // already-attached thread ... calling FollowReferences/IterateThroughHeap
  // directly; the safepoint is a side effect of that call, not something the
  // profiler builds or schedules"). threadLoop() mirrors J9WallClock's
  // pthread lifecycle (j9WallClock.cpp:28-57) rather than BaseWallClock's,
  // since J9WallClock's is the simpler of the two shapes actually used for a
  // single dedicated thread in this codebase. threadLoop() implements the
  // actual scheduling loop (shouldRunPass() below).
  //
  // start()/stop() themselves still do NOT create/join this thread -
  // threadLoop()'s VM::attachThread() call crashes on a null VM::_vm if the
  // VM is not yet attached, and referenceChains_ut.cpp calls start()
  // directly with no live JVM, so spawning unconditionally from start()
  // would crash that gtest binary. startThread()/stopThread() (public API
  // above) own the thread's lifecycle instead, and are called from
  // Profiler::start()/stop() (profiler.cpp) - the only place in this
  // codebase that also calls ReferenceChainTracker::start()/stop() itself,
  // and only once the JVM/JVMTI environment is already up. onGCFinish()
  // below wakes this thread via pthread_kill(WAKEUP_SIGNAL) whenever it is
  // running (i.e. once startThread() has been called) - inert otherwise.
  pthread_t _thread;
  volatile bool _running;

  // Cooperative-cancellation flag for an in-flight JVMTI FollowReferences
  // walk: stopThread() sets this before pthread_kill()/pthread_join()
  // (that signal alone cannot interrupt a call already inside the JVM/JVMTI
  // implementation), and heapReferenceCallback() checks it on every
  // invocation, aborting the walk within one callback rather than letting
  // pthread_join() block until the walk finishes on its own - see both
  // methods' own comments. startThread() resets it back to false, since a
  // dynamic-attach profiler can cycle through multiple start()/stop() calls
  // in one JVM lifetime and a stale abort request would instantly kill the
  // next cycle's very first pass. std::atomic<bool>: written from
  // stopThread()/startThread() on the calling (shutdown) thread and read
  // from heapReferenceCallback() on the BFS thread - the same cross-thread
  // shape _running above already has, just made explicit via atomic rather
  // than a plain volatile bool.
  std::atomic<bool> _abort_pass_requested;

  ReferenceChainTracker()
      : _enabled(false), _frontier(nullptr), _configured_frontier_cap(0),
        _last_class_map_generation(0),
        _last_resolved_class_count(0),
        _gc_start_epoch(0),
        _gc_finish_epoch(0), _next_tag(1), _next_class_tag_magnitude(1),
        _hop_cap(0), _budget(0), _first_pass_budget(0), _ttl_ms(0), _pause_target_ms(0),
        _effective_budget(0), _effective_cadence_ns(PASS_CADENCE_NS),
        _pause_pid(1, 1.0, 1.0, 1.0, 1, 1.0), _search_started(false),
        _tags_released(true), _search_state(SearchState::RUNNING),
        _abandon_reason(SearchAbandonReason::NONE), _search_start_ns(0),
        _last_pass_gc_finish_epoch(0), _last_pass_ns(0),
        _passes_run(0), _emitted_search_start_ns(0),
        _root_kind_rotation_cursor(1), _pain_budget(0.0), _search_pain_ms(0),
        _thread(), _running(false), _abort_pass_requested(false) {}

  void onGCStart();
  void onGCFinish();

  static void *threadEntry(void *self) {
    ((ReferenceChainTracker *)self)->threadLoop();
    return nullptr;
  }
  void threadLoop();

  // Combines Open Question 5's two candidate pass-scheduling triggers
  // (design doc's Triggering section) rather than picking one: true if the
  // GC-finish epoch has advanced since the last pass ("a GC just happened, a
  // pass may be worth running soon") or PASS_CADENCE_NS has elapsed since
  // the last pass, whichever comes first. Also true before the first pass
  // has ever run. A future measurement pass decides whether one of these
  // two triggers should be dropped as unnecessary once real cost data
  // exists - for now both are implemented, combined, rather than adding an
  // unmeasured config knob to switch between them.
  bool shouldRunPass(u64 now_ns);

  // Cheap probe (max=1, not the real poll pollWatchedTargets() makes) into
  // LivenessTracker's population-trend table: true if at least one klass
  // shows a positive population slope worth chasing. Always true when
  // LivenessTracker::gcGenerationsEnabled() is off, since there is no
  // candidate signal to gate on in that mode - callers fall back to their
  // pre-existing behavior in that case. Shared by canAffordNewSearch()
  // (restart gate) and threadLoop()'s own steady-state gate below, so a GC
  // with no accompanying population growth doesn't trigger either a restart
  // or a fresh pass.
  bool hasLeakSignal();

  // Search restart gate (this class's own header comment): true once
  // _pain_budget has drained back to zero (canStartNow()) *and*
  // hasLeakSignal() above reports at least one leak candidate. Always true
  // when LivenessTracker::gcGenerationsEnabled() is off, since there is no
  // candidate signal to gate on in that mode (see the header comment's last
  // paragraph) - this only ever affects restarts, so a
  // reference-chains-without-generations setup is unaffected either way.
  bool canAffordNewSearch(u64 now_ns);

  // Resets every per-search field back to its just-constructed value so the
  // next runPass() call takes the "first pass of a search" branch again,
  // exactly like a fresh ReferenceChainTracker would. Called by
  // shouldRunPass() once a terminal search's tags have already been released
  // (runPass() calls releaseSearchTags() itself before returning, so that
  // has always already happened by the time this runs) and
  // canAffordNewSearch() has approved a restart. Spends the finishing
  // search's accumulated cost into _pain_budget first, so the *next*
  // restart's gate reflects what this one actually cost. Does not touch
  // _class_tags/_next_class_tag_magnitude - classes do not change identity
  // across searches, so their resolved names stay valid and do not need
  // re-resolving (mirrors _frontier's own stop()/start()-survival
  // rationale). frontierTable()'s own resetForRestart() keeps the
  // table's allocation but marks every slot unoccupied again, so tags
  // restarting from 1 (nextTag()'s only outstanding scheme) do not read back
  // stale metadata from the previous search.
  void restartSearch();

  // Marks every entry still queued in _pending_expand EXPANDED and drains the
  // queue. Called after a *first-pass*, root-seeded FollowReferences call
  // that completed without truncation: an uninterrupted walk from the heap
  // roots already visits every admitted object's own outgoing edges inline
  // (as part of the same call, not a separate one per object - see
  // heapReferenceCallback()'s own comment), so nothing is left FRONTIER by
  // accident; this just makes that explicit so a later resumed pass has
  // nothing pending to expand.
  void markAllFrontierExpanded();

  // Resumed-pass counterpart to the first pass's root-seeded FollowReferences
  // call in runPass(): resolves every not-yet-expanded entry queued in
  // _pending_expand via GetObjectsWithTags - design doc Algorithm step 2's
  // "resolve currently-
  // live tagged frontier objects; objects that fail to resolve are dropped
  // (dead - free pruning)" - then calls FollowReferences with the resolved
  // object as initial_object to discover its own outgoing edges, exactly as
  // the root walk does inline for a first pass. Repeats over newly-
  // discovered entries within the same call, stopping the moment
  // *edges_admitted reaches `budget` or the frontier table reports capacity
  // exhaustion (the same "abort expansion past the cap rather than
  // discovering-then-discarding" rule the root-seeded path already follows)
  // - leaving the remaining range untouched for a later call to retry.
  //
  // *frontier_cap_hit distinguishes "budget for this call ran out" (normal;
  // the search stays RUNNING, more work remains for the next pass) from
  // "the frontier table itself is full" (design doc: "stop admitting new
  // entries ... report it" - runPass() treats this as grounds to ABANDON the
  // whole search, not just truncate this pass). If GetObjectsWithTags itself
  // fails, *truncated is set (there is pending work, just not resolvable
  // this call) so runPass() does not mistake that for the search having
  // reached natural completion.
  void expandFrontier(jvmtiEnv *jvmti, JNIEnv *jni, int hop_cap, int budget,
                       int *edges_admitted, bool *truncated,
                       bool *frontier_cap_hit);

  // Clears the live JVMTI tag (via clearTag(), i.e. SetTag(obj, 0)) for
  // every FrontierTable entry this search has not already marked ABANDONED -
  // design doc's Termination section: "on abandonment or completion, every
  // JVMTI tag this search assigned ... must be cleared before the search's
  // state is discarded." Does not discard the FrontierTable's own records
  // (referrer_klass/parent_tag/depth survive, so reconstructChain() keeps
  // working from memory after the search ends) - only the underlying
  // object's live JVMTI tag is released, via the same batch
  // resolve-then-clear sequence GetObjectsWithTags makes possible for
  // expandFrontier()'s resolve-or-drop path.
  //
  // Returns true if every live tag scanned this call was successfully
  // resolved-and-cleared (or there were none to begin with), false if
  // GetObjectsWithTags() itself failed - in which case NO entry is marked
  // ABANDONED (unlike a resolve failure for an individual tag, which means
  // the object is already dead and safe to treat as released): a batch
  // GetObjectsWithTags() failure tells us nothing about which, if any,
  // objects in the batch are still live, so marking them ABANDONED here
  // would let restartSearch() reset _next_tag/the frontier table while a
  // still-live object could still be holding this search's JVMTI tag,
  // corrupting the next search's tag-uniqueness invariant. Callers must not
  // allow a restart until this returns true; calling it again later safely
  // retries only the tags still not marked ABANDONED from a prior failed
  // call.
  bool releaseSearchTags(jvmtiEnv *jvmti, JNIEnv *jni);

  // Pause-time pacing controller (doc/architecture/LiveHeapReferenceChains-
  // RemainingWorkPlan.md): feeds `pass_wall_ns` - the wall-clock duration of the FollowReferences/
  // GetObjectsWithTags call runPass() just made (the safepoint-triggering
  // call itself, per the design doc's Triggering section; no new
  // instrumentation needed, since this class is already the thread blocked
  // inside it) - into `_pause_pid`, and scales `_effective_budget`/
  // `_effective_cadence_ns` from its output. Folds Open Questions 2 and 5
  // into the one controller call the plan asks for, rather than two
  // separately tuned mechanisms.
  //
  // `_pause_pid.compute()`'s sign convention (pidController.cpp): a positive
  // signal means the measured value came in *under* the controller's
  // target - here, the last pass finished comfortably inside
  // `_pause_target_ms`, so there is headroom to admit a larger budget next
  // time. This is the opposite of ObjectSampler/MallocTracer/
  // NativeSocketSampler's own usage (objectSampler.cpp:220-224,
  // mallocTracer.cpp:317-318, rateLimiter.h), which *subtract* the signal
  // from their interval because their controlled variable (a sampling
  // interval) is inversely related to their target rate; `_effective_budget`
  // is directly related to pass duration (more budget -> longer pass), so
  // the signal is *added* here instead.
  //
  // The result is clamped to [floor, _budget] - `_budget` (the config value,
  // Arguments::_reference_chains_budget) becomes this controller's ceiling
  // rather than a fixed per-pass value, per the plan's "clamped, never above
  // the frontier/hop caps": the hop cap and frontier cap stay untouched,
  // fixed correctness bounds exactly as before (design doc: "not
  // controller-tuned"). Whatever part of the signal the clamp could not
  // absorb (`overflow` below) drives `_effective_cadence_ns` instead - the
  // plan's "fold the cadence decision into the same controller output rather
  // than a second mechanism": a search still running long even at the
  // minimum budget backs off the fallback cadence instead of trying to
  // shrink the budget further (avoiding a degenerate near-zero budget just
  // to hit an aggressive cadence, per the plan's own wording); a search with
  // spare headroom even at the maximum (config) budget relaxes the cadence
  // toward MIN_EFFECTIVE_CADENCE_NS instead, letting the GC-finish-epoch
  // trigger (shouldRunPass(), already unconditional on cadence) make
  // progress as often as it fires.
  void updatePacing(u64 pass_wall_ticks);

  // Tags every not-yet-tagged loaded class (GetLoadedClasses()) with a
  // fresh nextClassTag() and resolves its name into _class_tags, via the
  // same GetClassSignature + normalizeClassSignature + Profiler::lookupClass
  // sequence ObjectSampler::recordAllocation() already uses
  // (objectSampler.cpp:76-90) - reusing that normalization helper rather
  // than re-deriving it. Run once at the start of every runPass() (before
  // FollowReferences) rather than lazily during the walk, because
  // GetClassSignature/JNI calls are not allowed from inside
  // heapReferenceCallback() (see the file header comment) - by pre-tagging,
  // every class_tag the callback sees is already resolvable with no further
  // JVMTI/JNI calls of its own. Already-tagged classes (from a previous
  // pass) are skipped, not re-resolved.
  void resolveLoadedClasses(jvmtiEnv *jvmti, JNIEnv *jni);

  // jvmtiHeapReferenceCallback for runPass()'s FollowReferences call (see
  // runPass() below for the full walk). `user_data` is a PassContext*
  // (referenceChains.cpp, private to the .cpp - the type never needs to be
  // visible here since only runPass() constructs one).
  static jint JNICALL heapReferenceCallback(
      jvmtiHeapReferenceKind reference_kind,
      const jvmtiHeapReferenceInfo *reference_info, jlong class_tag,
      jlong referrer_class_tag, jlong size, jlong *tag_ptr,
      jlong *referrer_tag_ptr, jint length, void *user_data);

  // Outcome of admitObject() below - lets each of its three call sites
  // (heapReferenceCallback() above, the IterateOverReachableObjects root/
  // stack-ref callbacks, and the FieldWalker-hop-driven child admission,
  // all in referenceChains.cpp) translate the same admission decision into
  // its own callback-shape-appropriate return value/truncation flag,
  // instead of duplicating the decision three times.
  enum class AdmitResult {
    ALREADY_ADMITTED, // *tag_ptr != 0: nothing to do, not a truncation
    HOP_CAP,          // depth >= hop_cap: not admitted, not a truncation
    BUDGET_EXHAUSTED,  // edges_admitted >= budget: this pass's cap
    FRONTIER_CAP_HIT,  // FrontierTable::insert() itself is full: abandon-worthy
    ADMITTED,
  };

  // First-discovery admission core (implementation plan's Phase 4 item 2):
  // factored out of heapReferenceCallback()'s inline admission branch so the
  // manual-walk driver's root/stack-ref callbacks and FieldWalker-hop child
  // admission stay in sync with FollowReferences' own admission by
  // construction, not by copy-paste. `*tag_ptr` is the in/out tag slot each
  // call site already has in a different shape - a real JVMTI out-parameter
  // for the first two, a local variable standing in for one (see
  // referenceChains.cpp's manualExpandVisitor()) for the third - `*edges_admitted`
  // is likewise each call site's own running counter for this call. On
  // AdmitResult::ADMITTED, `*tag_ptr` is filled with the freshly assigned tag
  // and the tag is queued onto _pending_expand exactly as heapReferenceCallback()
  // already did inline.
  AdmitResult admitObject(FrontierTable *frontier, int hop_cap, int budget,
                           int *edges_admitted, jlong *tag_ptr,
                           jlong parent_tag, u32 referrer_klass, u32 depth,
                           u8 root_kind);

  // Durability tie-break (design doc's "Fix for root-attribution staleness"
  // point 1 / Phase 5 item 1) for an object rediscovered as a heap root by
  // heapRootCallback()/stackRefCallback() while already admitted (same pass
  // or a previous one) - factored out of those callbacks, rather than
  // inlined, so it is unit-testable without a PassContext/JVMTI mock (both
  // callbacks' user_data type is private to referenceChains.cpp). Only ever
  // overwrites root_kind - never parent_tag - and only for an entry that is
  // already root-attached (entry.parent_tag == 0); this is the option (a)
  // resolution of the parent_tag==0/root_kind invariant conflict (Phase 5's
  // own callout): a re-expansion-driven, non-root rediscovery of an edge to
  // some already-tracked, non-root-attached object must never reach this
  // method at all (FieldWalker-driven child admission always passes
  // root_kind=0, which loses every tie-break, so it structurally cannot
  // trigger an upgrade even if it were mistakenly routed here). Returns true
  // if an upgrade was applied, false otherwise (already at least as durable,
  // not root-attached, or not found) - purely informational for callers/
  // tests, not required for correctness.
  bool maybeUpgradeRootAttachedRootKind(FrontierTable *frontier, jlong tag,
                                        u8 new_root_kind);

  // Bounded rotating re-expansion (design doc's closing section / Phase 5
  // item 3): each manual-walk pass, feed up to `max_count` already-EXPANDED,
  // root-attached entries whose root_kind is still transient
  // (isTransientRootKind()) back into _pending_expand so
  // expandFrontierManual() re-walks their fields - giving a stale root_kind
  // another chance to be superseded by a durable root discovered elsewhere
  // in the interim, via the same admitObject()/tie-break machinery every
  // other admission uses. Scans FrontierTable slots in tag order starting
  // from _root_kind_rotation_cursor, wrapping at size(), so repeated calls
  // sweep the whole table over time instead of only ever revisiting the
  // first `max_count` transient entries. Pure table scan/queue push - no
  // JVMTI/FieldWalker call of its own - so it is unit-testable directly.
  // Returns the tags selected (also already pushed onto _pending_expand).
  std::vector<jlong> collectStaleRootKindEntriesForRotation(int max_count);

  // jvmtiHeapRootCallback/jvmtiStackReferenceCallback for runPassManualWalk()'s
  // IterateOverReachableObjects call (referenceChains.cpp). `user_data` is a
  // PassContext* (the same private-to-the-.cpp type heapReferenceCallback()
  // already uses above) - both callbacks only ever admit a root-attached
  // entry (parent_tag=0, depth=0), translating the JVMTI-owned
  // jvmtiHeapRootKind into FrontierEntry::root_kind's jvmtiHeapReferenceKind
  // numbering first (see referenceChains.cpp's translateHeapRootKind() for
  // why this translation is required, not optional).
  static jvmtiIterationControl JNICALL
  heapRootCallback(jvmtiHeapRootKind root_kind, jlong class_tag, jlong size,
                    jlong *tag_ptr, void *user_data);
  static jvmtiIterationControl JNICALL stackRefCallback(
      jvmtiHeapRootKind root_kind, jlong class_tag, jlong size,
      jlong *tag_ptr, jlong thread_tag, jint depth, jmethodID method,
      jint slot, void *user_data);

  // jvmtiHeapReferenceCallback shape reused purely as a safepoint-pinning
  // vehicle for expandFrontierManual()'s FieldWalker-driven expansion (see
  // that method's own comment in referenceChains.cpp for why a raw-oop-
  // reading FieldWalker::walkOneHop() call is only safe from inside a real
  // JVMTI Heap-category callback, mirroring javaApi.cpp's
  // walkOneHopForTest0 test seam). `user_data` is a ManualExpandCtx*
  // (referenceChains.cpp, private to the .cpp).
  static jint JNICALL manualExpandSafepointPin(
      jvmtiHeapReferenceKind reference_kind,
      const jvmtiHeapReferenceInfo *reference_info, jlong class_tag,
      jlong referrer_class_tag, jlong size, jlong *tag_ptr,
      jlong *referrer_tag_ptr, jint length, void *user_data);

  // FieldWalker::Visitor for manualExpandSafepointPin()'s walkOneHop() calls -
  // admits each discovered child via admitObject(), assigning/persisting its
  // JVMTI tag directly (GetTag/SetTag - see manualExpandSafepointPin()'s own
  // comment for why this call site, unlike the other two, has no JVMTI-owned
  // tag_ptr of its own to write through).
  static void manualExpandVisitor(uintptr_t child, int field_slot,
                                   void *user_data);

  // Manual-walk counterpart to expandFrontier() above: drains _pending_expand
  // via FieldWalker::walkOneHop() instead of FollowReferences, one
  // safepoint-pinning FollowReferences(initial_object=<resolved object>) call
  // per frontier entry being expanded (manualExpandSafepointPin() above) -
  // see referenceChains.cpp for the full rationale, including why this
  // cannot be folded into a single batch call the way FollowReferences'
  // own graph walk can.
  void expandFrontierManual(jvmtiEnv *jvmti, JNIEnv *jni, int hop_cap,
                             int budget, int *edges_admitted, bool *truncated,
                             bool *frontier_cap_hit);

  // Manual-walk pass driver (implementation plan Phase 4): seeds/refreshes
  // root-attached frontier entries via IterateOverReachableObjects
  // (heapRootCallback()/stackRefCallback() above), then drains
  // _pending_expand via expandFrontierManual() up to `budget` - see
  // referenceChains.cpp for why, unlike the FollowReferences fallback, this
  // is the same two-step shape on *every* pass (root enumeration alone,
  // unlike a root-seeded FollowReferences call, never itself discovers a
  // root's transitive children - IterateOverReachableObjects's root/stack-ref
  // callbacks are given no oop to walk from, only a tag_ptr - so there is no
  // "first pass does it all inline" shortcut here the way there is on the
  // JVMTI fallback path).
  void runPassManualWalk(jvmtiEnv *jvmti, JNIEnv *jni, int budget,
                          int *edges_admitted, bool *truncated,
                          bool *frontier_cap_hit);

  // Pushes `event` onto _pending_chain_events, evicting the oldest entry
  // (and counting it via REFERENCE_CHAIN_EVENTS_DROPPED) if already at
  // MAX_PENDING_CHAIN_EVENTS - see that field's own comment and this
  // method's definition (referenceChains.cpp) for the full rationale.
  void enqueueChainEvent(ReferenceChainEvent &&event);

public:
  static ReferenceChainTracker *instance() {
    static ReferenceChainTracker instance;
    return &instance;
  }

  ReferenceChainTracker(const ReferenceChainTracker &) = delete;
  ReferenceChainTracker &operator=(const ReferenceChainTracker &) = delete;

  Error start(Arguments &args);
  void stop();

  // Spawns the BFS thread (threadEntry()/threadLoop()) if reference chain
  // tracking is enabled and no thread is already running. Deliberately kept
  // separate from start() itself: start() must stay safely callable with no
  // live JVM attached (referenceChains_ut.cpp calls it directly against a
  // mocked jvmtiEnv, with VM::_vm never set), while startThread()'s
  // threadLoop() calls VM::attachThread() unconditionally - safe only once
  // the JVM is actually up. Wired from Profiler::start() (profiler.cpp),
  // which only calls this after the JVM/JVMTI environment is fully
  // initialized, resolving the ordering concern start()'s own comment used
  // to raise. No-op if disabled or already running.
  void startThread();

  // Stops and joins the BFS thread started by startThread(), mirroring
  // BaseWallClock::stop()'s pthread_kill(WAKEUP_SIGNAL) + pthread_join()
  // shape (wallClock.cpp) - WAKEUP_SIGNAL is already installed
  // unconditionally in vmEntry.cpp, so no extra signal setup is needed here.
  // No-op if the thread was never started.
  void stopThread();

  bool enabled() const { return _enabled; }

  u64 gcStartEpoch() { return load(_gc_start_epoch); }
  u64 gcFinishEpoch() { return load(_gc_finish_epoch); }

  // Tag round-trip helpers, reused by resolveLoadedClasses()/
  // heapReferenceCallback() (the heap-walk engine) to drive FrontierTable's tag-indexed
  // slots.
  jlong nextTag() { return atomicIncRelaxed(_next_tag, (jlong)1); }
  jlong tagObject(jvmtiEnv *jvmti, jobject obj);
  jlong getTag(jvmtiEnv *jvmti, jobject obj);
  void clearTag(jvmtiEnv *jvmti, jobject obj);

  // Hands out a fresh negative class tag (see _next_class_tag_magnitude
  // above for why negative). Exposed (not just used internally by
  // resolveLoadedClasses()) so tests can drive class tagging directly
  // against a mocked jvmtiEnv without going through GetLoadedClasses.
  jlong nextClassTag() {
    return -atomicIncRelaxed(_next_class_tag_magnitude, (jlong)1);
  }

  // Returns the frontier metadata table, or nullptr if the subsystem was
  // never started with the flag enabled.
  FrontierTable *frontierTable() { return _frontier; }

  // Returns the class-tag resolution table. Exposed for testing in
  // isolation, matching frontierTable()'s existing rationale.
  ClassTagTable *classTags() { return &_class_tags; }

  // Runs exactly one bounded BFS pass and returns. The first call for a
  // search seeds FollowReferences from the heap roots (heap_filter=0,
  // klass=NULL, initial_object=NULL - see this method's own comment in
  // referenceChains.cpp for why FollowReferences rather than
  // IterateThroughHeap); every later call resumes from the persisted
  // frontier via expandFrontier() instead of re-walking from the roots (see
  // expandFrontier()'s comment for why - re-walking from the roots each call
  // would re-traverse the entire already-discovered subgraph every pass,
  // defeating the point of a per-pass budget). Newly discovered objects are
  // admitted into frontierTable() up to _hop_cap/_budget/the frontier
  // table's own capacity cap.
  //
  // Returns false if reference chain tracking is disabled, jvmti is null, or
  // the frontier table was never constructed (start() never ran with the
  // flag enabled). A pass that hits its budget/hop/frontier cap is still a
  // *successful* call (returns true) - *out_truncated (if non-null) reports
  // whether *this pass* ran to full exhaustion of the currently-known
  // reachable graph or was cut short, per the design doc's "no silent
  // truncation" requirement; this is call-scoped, unlike searchState()
  // below which reports the whole search's outcome.
  //
  // Once searchState() is no longer RUNNING (the reachable graph was fully
  // explored within caps, or the search was abandoned - see the Termination
  // section implemented below), further calls are no-ops that return true
  // immediately, *unless* shouldRunPass() has already called restartSearch()
  // to begin a fresh search (this class's own header comment) - in that case
  // _search_started is false again and this method takes the first-pass
  // branch exactly as it would for a brand-new tracker.
  bool runPass(jvmtiEnv *jvmti, JNIEnv *jni, bool *out_truncated = nullptr);

  // Search-level outcome (SearchState's constants) - see runPass()'s comment
  // for exactly when this leaves RUNNING.
  u8 searchState() { return load(_search_state); }

  // Total passes run for the current/most recent search. Exposed for tests
  // to confirm multi-pass resumption actually happened.
  int passesRun() { return load(_passes_run); }

  // Which SearchAbandonReason cutoff moved the search out of RUNNING, or
  // SearchAbandonReason::NONE if it never left RUNNING or left via
  // SearchState::COMPLETED instead.
  u8 abandonReason() { return load(_abandon_reason); }

  // Reference-chain JFR event surface: fills *out from frontierTable()->
  // reconstructChain(target_tag, ...) (see that method's own comment for
  // the leaf-to-root ordering and the parent_tag walk it performs). Returns
  // false (leaving *out untouched) if target_tag was never inserted into
  // the frontier table - the same failure case reconstructChain() itself
  // reports, just wrapped into the JFR-event shape
  // Recording::recordReferenceChain() (flightRecorder.cpp) expects.
  //
  // Deliberately does not decide *when* to call this or *which* target_tag
  // to use - this codebase has no target-sample feed into
  // ReferenceChainTracker yet (see runPass()'s own comment), so wiring an
  // automatic call site here would have to invent
  // that feed rather than reuse one. A future consumer that knows which
  // tag it is chasing (e.g. an ObjectSampler-driven target) calls this
  // directly once that feed exists.
  bool buildChainEvent(jlong target_tag, ReferenceChainEvent *out) {
    if (_frontier == nullptr || out == nullptr) {
      return false;
    }
    FrontierEntry entry{};
    if (!_frontier->lookup(target_tag, &entry)) {
      return false;
    }
    std::vector<u32> chain;
    u8 root_kind = 0;
    if (!_frontier->reconstructChain(target_tag, &chain, &root_kind)) {
      return false;
    }
    TEST_LOG("ReferenceChainTracker::buildChainEvent target_tag=%lld chain_size=%zu "
             "chain[0]=%u depth=%u root_kind=%u",
             (long long)target_tag, chain.size(), chain.empty() ? 0u : chain[0],
             entry.depth, (unsigned)root_kind);
    out->_target_tag = (u64)target_tag;
    out->_depth = entry.depth;
    out->_root_kind = root_kind;
    out->_chain = std::move(chain);
    return true;
  }

  // Abandoned-search JFR event surface for the design doc's "explicit reporting of
  // abandoned searches" requirement - unlike buildChainEvent() above, this
  // needs no target_tag: it reports the search's own termination state,
  // which runPass() (referenceChains.cpp) already tracks unconditionally.
  // Returns false (leaving *out untouched) if the search was never
  // abandoned (searchState() != SearchState::ABANDONED). Called from
  // Profiler::dump() (profiler.cpp), mirroring LivenessTracker::flush()'s
  // own call site there, whenever a dump is requested while the search is
  // ABANDONED - unlike LivenessTracker's table this does not clear any
  // state, so a dump taken after the search already abandoned reports the
  // same event again; this is a read of current state, not a queue drain.
  bool buildAbandonedEvent(ReferenceChainAbandonedEvent *out) {
    if (out == nullptr || load(_search_state) != SearchState::ABANDONED) {
      return false;
    }
    out->_reason = load(_abandon_reason);
    out->_passes_run = (u32)load(_passes_run);
    out->_frontier_size = _frontier != nullptr ? (u32)_frontier->size() : 0;
    out->_hop_cap = _hop_cap;
    out->_budget = _budget;
    out->_ttl_ms = _ttl_ms;
    out->_elapsed_ns = load(_last_pass_ns) - load(_search_start_ns);
    return true;
  }

  // Target-selection bridging step (design doc's Open Question 3, corrected
  // mechanism - see this class's own header comment's bridging-step note and
  // doc/architecture/LiveHeapReferenceChains-RemainingWorkPlan.md's
  // "Correction to the design doc's Open Question 3 mechanism"): polls
  // LivenessTracker::selectLeakCandidates() and, for each candidate whose
  // representative instance has already been discovered by an ordinary
  // runPass() walk (getTag() > 0 - a read, never a SetTag seed), builds and
  // enqueues its datadog.ReferenceChain event into _pending_chain_events -
  // see that field's own comment for why this pushes onto a queue rather
  // than calling Profiler::writeReferenceChain() directly: that call can
  // block this method's caller (the BFS scheduling thread) for up to ~50ms
  // per event, which drainPendingChainEvents() below avoids by deferring the
  // actual write to whatever thread calls Profiler::dump(). A candidate
  // still at tag 0 (not yet discovered) is left for a later poll to retry,
  // since runPass()'s whole-graph walk eventually visits every
  // root-reachable object, barring the hop/budget/frontier caps.
  // De-duplicates via _emitted_target_tags above so a klass flagged across
  // multiple consecutive polls does not re-emit the same chain repeatedly.
  // Called from threadLoop() once per scheduling cycle, after runPass(), so
  // this poll always sees the most recent pass's tagging. No-op if
  // disabled, or if jvmti/jni is null (mirrors runPass()'s own null-safety,
  // so a test can call this directly without a live JVM attached, the same
  // way referenceChains_ut.cpp already does for runPass()).
  void pollWatchedTargets(jvmtiEnv *jvmti, JNIEnv *jni);

  // Moves every event pollWatchedTargets() has queued so far into *out
  // (appended, not overwritten) and empties the queue - a drain, not a
  // peek, mirroring the "flush" semantics of LivenessTracker::flush()'s own
  // table rather than buildAbandonedEvent()'s repeatable read. Called from
  // Profiler::dump() (profiler.cpp), which then calls
  // Profiler::writeReferenceChain() for each drained event on its own
  // thread - never the BFS scheduling thread, see _pending_chain_events'
  // comment for why that separation matters. A no-op (leaves *out
  // untouched) if the queue is currently empty, so a dump taken between
  // polls costs one lock/unlock and nothing else.
  void drainPendingChainEvents(std::vector<ReferenceChainEvent> *out);

  static void JNICALL GarbageCollectionStart(jvmtiEnv *jvmti_env);
  static void JNICALL GarbageCollectionFinish(jvmtiEnv *jvmti_env);

  // Test seam - not part of the production API. Mirrors LivenessTracker's
  // own "Test seams" block (livenessTracker.h). Production code only ever
  // discovers frontier roots via runPass()'s root-seeded FollowReferences
  // walk; this lets a test tag and insert one specific, caller-chosen live
  // object as a frontier root directly, so runPass()/pollWatchedTargets()/
  // buildChainEvent() can be exercised end-to-end against a known target
  // without depending on LivenessTracker's probabilistic allocation sampler
  // to organically select and surface the same object. Returns the assigned
  // tag (matching the value buildChainEvent()'s target_tag expects), or 0 on
  // failure (obj/jvmti/jni null, SetTag failed, or the frontier table is at
  // capacity).
  jlong tagAsRootForTest(jvmtiEnv *jvmti, JNIEnv *jni, jobject obj);

  // Test seam - not part of the production API. Since ReferenceChainTracker
  // is a process-wide singleton (ExternalProcessReferenceChainTest's own
  // class javadoc explains why that matters: only the *first* test to ever
  // call runPass() in a shared JVM gets a real root-seeded walk, since
  // runPass() only re-walks from the roots once per search's whole
  // lifetime), an in-process test that needs its own genuine first-ever
  // root walk calls this at the start of its test body to force exactly
  // that - releasing any tags a previous test's search still held, then
  // resetting search/frontier state to the same "brand-new tracker" state
  // restartSearch() (referenceChains.cpp) produces, plus the target-
  // dedup/pending-event state restartSearch() itself intentionally leaves
  // for pollWatchedTargets()/drainPendingChainEvents() to self-clear (this
  // is an immediate, out-of-band reset - there is no next real pass here to
  // observe the change and clear them the ordinary way).
  void resetSearchStateForTest(jvmtiEnv *jvmti, JNIEnv *jni);
};

#endif // _REFERENCECHAINS_H
