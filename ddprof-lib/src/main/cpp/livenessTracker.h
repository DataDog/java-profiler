/*
 * Copyright 2021, 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _LIVENESSTRACKER_H
#define _LIVENESSTRACKER_H

#include "arch.h"
#include "callTraceHashTable.h"
#include "context.h"
#include "engine.h"
#include "event.h"
#include "spinLock.h"
#include <atomic>
#include <jvmti.h>
#include <pthread.h>
#include <set>
#include <unordered_set>

class Recording;

typedef struct TrackingEntry {
  jweak ref;
  AllocEvent alloc;
  double skipped;
  u64 call_trace_id;
  jint tid;
  jlong time;
  jlong age;
  Context ctx;
  // Set by cleanup_table()'s survivor loop via resolveKlassId() when
  // _gc_generations is enabled (0 otherwise, or if resolution failed - 0 is
  // StringDictionary's own "no entry" sentinel, so a real id is never 0).
  // flush_table() reuses this instead of re-resolving the same object's
  // class via a second GetObjectClass+Class.getName()+lookupClass() JNI
  // round-trip - an object's class never changes, so a value resolved here
  // stays valid for flush_table()'s later read of the same entry. track()
  // resets this to 0 for every newly tracked entry.
  u32 cached_klass_id;
} TrackingEntry;

// Fixed-capacity, LRU-evicted per-klass population history, keyed by klass
// StringDictionary id (Profiler::classMap(), the same id TrackingEntry/
// AllocEvent resolves lazily today only at flush time, flush_table() below).
// This is the data doc/architecture/LiveHeapReferenceChains.md's Open
// Question 3 "positive population-slope ranking" proposal needs: a rolling
// window of how many tracked instances of a klass are alive at each GC
// epoch, plus one representative instance to chase a chain for if the trend
// looks leak-shaped (see selectLeakCandidates() below for the ranking, and
// referenceChains.cpp's pollWatchedTargets() for how a ranked candidate gets
// consumed - this struct only stores the raw history).
typedef struct KlassPopulationEntry {
  u32 klass_id;          // StringDictionary id; 0 means "unused slot" (0 is
                          // also StringDictionary's own "no entry" sentinel,
                          // so a real id is never 0 - see resolveKlassId()).
  jweak representative;   // a currently-live instance of this klass, owned by
                          // this table (its own weak global ref, deliberately
                          // NOT aliasing any TrackingEntry::ref - see
                          // foldKlassCountsLocked()'s comment for why aliasing
                          // would leave a dangling handle once cleanup_table()
                          // reaps the original TrackingEntry).
  u32 count_ring[30];     // ring buffer of per-epoch generation counts: the
                          // number of distinct GC ages among a klass's
                          // surviving tracked instances that epoch (see
                          // accumulateKlassCount(), livenessTracker.cpp).
  u8 ring_head;           // next slot to write
  u8 ring_fill;           // samples written so far, caps at 30
  // Number of consecutive epochs (most recent first) for which
  // LivenessTracker::hasQualifyingGrowth() found this entry's ring to show a
  // leak-shaped rise, updated every time a new sample is pushed
  // (recordKlassPopulationSampleLocked()) - reset to 0 the moment a single
  // epoch fails the test. selectLeakCandidates() requires this to reach a
  // hysteresis threshold before trusting the klass, rather than acting on
  // one qualifying epoch alone: a population merely oscillating (no net
  // growth) satisfies a single-epoch test on roughly half of all epochs, so
  // without this counter it gets reported as a leak candidate almost as
  // often as a real leak does.
  u8 consecutive_positive;
  // Slope (recent third's mean minus earliest third's mean) as of the last
  // push, computed and cached by hasQualifyingGrowth() alongside
  // consecutive_positive above - selectLeakCandidates() reads this directly
  // for ranking instead of re-scanning the ring: the ring only changes on
  // push, so a second scan at scan time would just recompute the same
  // value. Meaningless (left at its previous value, or 0 for a newly
  // created entry) whenever ring_fill < KLASS_POPULATION_MIN_FILL_FOR_TREND
  // - callers must check ring_fill first, exactly as before this field
  // existed.
  mutable double cached_slope;
  u64 last_updated_epoch; // _gc_epoch value as of the last write, for LRU
                          // eviction when the table is full
} KlassPopulationEntry;

// One leak-candidate result from selectLeakCandidates() below: the klass to
// chase and a currently-live representative instance of it, ready to hand to
// referenceChains.cpp's pollWatchedTargets() (the design doc's Open Question
// 3 bridging step). Deliberately excludes the slope/rank that produced the
// ranking - the caller only needs identity, matching the design doc's own
// "KlassCandidate { u32 klass_id; jweak representative; }" sketch exactly.
typedef struct KlassCandidate {
  u32 klass_id;
  jweak representative;
} KlassCandidate;

// Aligned to satisfy SpinLock member alignment requirement (64 bytes)
// Required because this class contains SpinLock _table_lock member
class alignas(alignof(SpinLock)) LivenessTracker {
  friend Recording;

private:
  // pre-c++17 we should mark these inline(or out of class)
  constexpr static int MAX_TRACKING_TABLE_SIZE = 262144;
  constexpr static int MIN_SAMPLING_INTERVAL = 524288; // 512kiB

  // _klass_population/_klass_count_scratch below are both scanned linearly
  // (lookup and LRU-eviction search) - this size keeps every such scan cheap
  // enough that a plain linear scan is fine, rather than requiring an index.
  constexpr static int MAX_KLASS_POPULATION_ENTRIES = 256;
  // Design doc's Open Question 3 proposal: "ring buffer of up to 30 recent
  // population counts".
  constexpr static int KLASS_POPULATION_RING_SIZE = 30;
  // Design doc's Open Question 3 proposal: "Only trust the trend once the
  // window has a minimum fill (e.g. ≥10 samples) to avoid noise right after
  // a klass starts being tracked."
  constexpr static int KLASS_POPULATION_MIN_FILL_FOR_TREND = 10;
  // Design doc's Open Question 3 proposal: "seed only the top 3-5 by trend
  // magnitude" - this is the upper end of that range. selectLeakCandidates()
  // also honors the caller-supplied `max`, so the effective cutoff is
  // min(max, MAX_LEAK_CANDIDATES, <number of positive-slope entries found>);
  // "no separate budget constant is needed" per the design doc, this top-N
  // cutoff doubles as the per-pass seeding cap.
  // (Moved to public section for ReferenceChainTracker access.)

  // --- Sustained-trend gate (hasQualifyingGrowth() below) ---
  // count_ring holds, per epoch, the number of distinct GC ages
  // (generations) among a klass's surviving tracked instances
  // (accumulateKlassCount(), livenessTracker.cpp) rather than the raw
  // surviving instance count: a klass whose survivors keep spanning more
  // distinct allocation cohorts over time is one where old instances are
  // not dying as new ones arrive, which is the leak shape this gate looks
  // for. The gate itself is a single condition - the recent third's mean
  // generation count must exceed the earliest third's by a meaningful
  // margin (LEAK_GROWTH_REL_MIN/LEAK_GROWTH_ABS_MIN, whichever is larger).
  // An earlier revision of this gate also required the recent third's
  // *minimum* to exceed the earliest third's minimum (a floor-rise check,
  // to reject oscillations whose peak alone passes the growth test) - that
  // check was tuned for raw population counts (which can run into the
  // thousands) and does not transfer to generation counts, which are small
  // integers bounded by how many distinct cohorts a klass can realistically
  // accumulate; it was dropped rather than re-tuned.
  constexpr static double LEAK_GROWTH_REL_MIN = 0.15;
  // Absolute floor for the growth bar: the slope must exceed
  // max(LEAK_GROWTH_REL_MIN * earliest_mean, LEAK_GROWTH_ABS_MIN).
  constexpr static int LEAK_GROWTH_ABS_MIN = 1;

  // Required number of consecutive qualifying epochs
  // (KlassPopulationEntry::consecutive_positive) before selectLeakCandidates()
  // trusts a klass as a leak candidate. Lower (CORROBORATED) when the
  // aggregate post-GC live heap (heapFloorRising() below) is independently
  // showing a sustained rise of its own over the same horizon - that is
  // whole-heap evidence this klass's growth isn't an isolated artifact
  // (redistribution/churn that nets out heap-wide, or per-klass sampling
  // noise), so fewer of this klass's own epochs are needed to trust it.
  // heapFloorRising() is a single call per selectLeakCandidates() scan, not
  // per candidate: the aggregate heap has no per-klass attribution, so it
  // cannot single out which klass (if any) is responsible for its rise -
  // it can only raise or lower the bar for every candidate in that scan
  // uniformly, never reorder them against each other.
  constexpr static int LEAK_TREND_HYSTERESIS_BASE = 5;
  constexpr static int LEAK_TREND_HYSTERESIS_CORROBORATED = 3;

  // --- Aggregate post-GC heap floor (heapFloorRising() below) ---
  // Same "mean-of-thirds growth + floor rise" shape as the per-klass test
  // above, applied to a single global ring of post-GC live heap size
  // instead of one klass's sampled population - see this class's own ring
  // (_heap_floor_ring below). Its own thresholds are deliberately looser
  // (fraction-of-heap, not fraction-of-one-klass): this signal is diluted by
  // every other klass's allocation activity (a leak far smaller than these
  // thresholds is invisible against the rest of the heap), so it is not
  // sensitive enough to gate on directly - it is used only as the
  // LEAK_TREND_HYSTERESIS_BASE/CORROBORATED selector above.
  constexpr static double HEAP_FLOOR_GROWTH_REL_MIN = 0.02;
  constexpr static u64 HEAP_FLOOR_GROWTH_ABS_MIN = 1ULL << 20;   // 1MiB
  constexpr static double HEAP_FLOOR_FLOOR_REL_MIN = 0.01;
  constexpr static u64 HEAP_FLOOR_FLOOR_ABS_MIN = 1ULL << 19;    // 512KiB

  bool _initialized;
  bool _enabled;
  Error _stored_error;

  SpinLock _table_lock;
  volatile int _table_size;
  int _table_cap;
  int _table_max_cap;
  TrackingEntry *_table;

  double _subsample_ratio;

  bool _record_heap_usage;

  jclass _Class;
  jmethodID _Class_getName;

  volatile u64 _gc_epoch;
  volatile u64 _last_gc_epoch;

  // Timestamp (OS::nanotime()) of the last cleanup_table() sweep that
  // actually ran, whether organic (flush_table()'s JFR cadence) or forced
  // (track()'s table-overflow branch). Read/written only by
  // maybeForceCleanup() below - see that method's own comment for why a
  // third, time-based trigger is needed on top of those two.
  volatile u64 _last_cleanup_ns;

  size_t _used_after_last_gc;

  // Ring of post-GC live heap sizes, one sample per GC epoch, feeding
  // heapFloorRising() below - same shape as KlassPopulationEntry::count_ring
  // but a single global instance rather than one per klass, and lock-free
  // rather than _table_lock-guarded: onGC() runs from the JVMTI
  // GarbageCollectionFinish callback, which can fire synchronously mid-way
  // through a JNI upcall this class itself is making while already holding
  // _table_lock (e.g. cleanup_table()'s Class.getName() call, if that
  // allocation triggers a GC) - taking the same lock here would risk a
  // self-deadlock on a non-reentrant SpinLock. GC completions are never
  // concurrent with each other (HotSpot never runs two GCs at once), so
  // onGC() is always a single writer at a time, matching the existing
  // lock-free _gc_epoch/_used_after_last_gc fields' own assumption - see
  // recordHeapFloorSample()/heapFloorRising() (livenessTracker.cpp) for the
  // load/store ordering this relies on.
  u64 _heap_floor_ring[KLASS_POPULATION_RING_SIZE];
  // OS::nanotime() paired index-for-index with _heap_floor_ring above (same
  // head/fill, always pushed together by recordHeapFloorSample() - see that
  // method's comment) - heapFloorRising() itself has no use for elapsed
  // time, but secondsToOOM() below needs it to turn the ring's byte growth
  // into a rate rather than just a magnitude.
  u64 _heap_floor_time_ring[KLASS_POPULATION_RING_SIZE];
  // Container (cgroup) memory usage, one sample per GC epoch, pushed to the
  // same head/fill index as _heap_floor_ring/_heap_floor_time_ring above by
  // the same recordHeapFloorSample() call - so this ring shares
  // _heap_floor_time_ring's timestamps rather than needing its own. Exists
  // because container memory can grow from causes _heap_floor_ring never
  // sees at all (native/off-heap allocations - direct buffers, JNI/native
  // libraries) - see secondsToOOM()'s own comment for how this ring and
  // _heap_floor_ring are used as two independent OOM boundaries.
  u64 _container_mem_ring[KLASS_POPULATION_RING_SIZE];
  volatile u8 _heap_floor_ring_head;
  volatile u8 _heap_floor_ring_fill;

  // Debug-only test seam: when true, onGC() skips recordHeapFloorSample()
  // so a test can seed the ring exclusively via heapFloorRecordForTest()
  // without a real GC interleaving a sample with a real OS::nanotime()
  // timestamp and real heap usage, corrupting secondsToOOM()'s projection.
  // See AggressiveLeakReferenceChainTest's own comment for the race this
  // closes (a real GC firing between resetKlassPopulationForTest0() and
  // shouldRunPassForTest0()).
#ifdef DEBUG
  // Atomic (not plain bool) so the GC thread sees the test thread's store
  // on arm64's weak memory model. Checked inside recordHeapFloorSample()
  // at the actual write point, not just in onGC(), so a GC already past the
  // onGC() gate when the test sets this flag still cannot corrupt the ring.
  std::atomic<bool> _heap_floor_recording_disabled_for_test{false};
#endif

  // Runtime.maxMemory(), resolved once by initialize_table() (the same call
  // that already requires it to enable liveness tracking at all - see that
  // method's own Error path) and cached here so secondsToOOM() - polled once
  // per ReferenceChainTracker::threadLoop wake, ~1s - does not repeat
  // HeapUsage::getMaxHeap()'s handful of JNI calls on every poll. A JVM's max
  // heap does not change at runtime, so a value resolved once stays valid.
  // -1 if never resolved (mirrors getMaxHeap()'s own sentinel).
  jlong _max_heap_bytes;

#ifdef DEBUG
  // Atomic mirror used only by the setMaxHeapBytesForTest() seam so the
  // test thread's store is published to the BFS thread's secondsToOOM()
  // read on arm64's weak memory model. _max_heap_bytes above stays plain
  // for the production path (written once from the control thread during
  // initialize_table(), before the BFS thread starts, so no cross-thread
  // visibility issue there).
  std::atomic<jlong> _max_heap_bytes_for_test{-1};
#endif

  // OS::getContainerMemoryLimit(), resolved once by initialize_table() next
  // to _max_heap_bytes above (same call site, same "resolved once, does not
  // change at runtime" reasoning) and cached here so secondsToOOM() does not
  // re-walk the cgroup hierarchy on every poll. -1 if never resolved, or if
  // this process is not running under a memory-limited cgroup (bare metal,
  // macOS, cgroups disabled) - secondsToOOM() treats -1 as "unbounded" so
  // this boundary never wins over the heap-based one.
  jlong _container_memory_limit;

#ifdef DEBUG
  // Mirrors _max_heap_bytes_for_test above for the same reason: lets a test
  // exercise secondsToOOM()'s container boundary without a real cgroup.
  std::atomic<jlong> _container_memory_limit_for_test{-1};
#endif

  // Gates the per-klass population tracking below. Set from
  // args._gc_generations in initialize() - deliberately not folded into
  // _enabled (which also covers plain _record_liveness): this doesn't
  // resolve the design doc's own "still undecided" bullet under Open
  // Question 3 by itself, but the plan built on top of this table requires
  // liveness tracking *and* _gc_generations, matching the doc's stated
  // fallback of "no target-seeding" when generations tracking isn't on
  // (arguments.cpp:223-227,244). std::atomic (relaxed) since initialize()
  // writes it from the control thread while the BFS thread
  // (maybeForceCleanup()) and the GC-callback thread (cleanup_table()) can
  // still be reading it from a session that persists across a restart.
  std::atomic<bool> _gc_generations;

  // Per-klass population history table (see KlassPopulationEntry above).
  // Populated only from cleanup_table()'s GC-epoch-advance pass, never from
  // track() (the allocation sampling hot path) - see
  // accumulateKlassCount()/foldKlassCountsLocked() below. Guarded by
  // _table_lock, the same lock cleanup_table() already holds for the
  // duration of its epoch-advance pass, rather than adding a second lock.
  KlassPopulationEntry _klass_population[MAX_KLASS_POPULATION_ENTRIES];
  int _klass_population_size;

  // Scratch space reused across cleanup_table() calls (a member field, not a
  // per-call stack/heap allocation - cleanup_table() runs on a GC-signal
  // cadence, not the allocation hot path, but this codebase's
  // allocation-free preference still applies wherever avoiding an
  // allocation is cheap) to accumulate this epoch's per-klass surviving
  // counts before folding them into _klass_population's ring buffers at the
  // end of the pass.
  typedef struct KlassCountScratch {
    u32 klass_id;
    // Distinct GC ages (generations) of surviving tracked instances
    // of this klass at this epoch. The size of this vector
    // is the klass' generation count.
    std::vector<u32> ages;
    jweak sample_source; // the original TrackingEntry::ref of the first
                          // surviving instance of this klass seen this
                          // epoch; consulted only by foldKlassCountsLocked()
                          // when klass_id turns out to need a brand new
                          // KlassPopulationEntry, to derive a fresh,
                          // independent representative jweak (see that
                          // method's comment for why the original handle
                          // cannot be reused directly).
  } KlassCountScratch;
  KlassCountScratch _klass_count_scratch[MAX_KLASS_POPULATION_ENTRIES];
  int _klass_count_scratch_size;

  // Profiler::classMap()'s generation as of the last cleanup_table() call
  // that checked it, mirroring ReferenceChainTracker::_last_class_map_generation
  // (referenceChains.h). Profiler::start() calls _class_map.clearAll()
  // (profiler.cpp) whenever `reset || _start_time == 0`, restarting that
  // StringDictionary's id namespace at 1 - but TrackingEntry::cached_klass_id
  // and _klass_population's klass_id keys are ids resolved from that
  // dictionary, and both survive stop()/start() cycles (this class's table is
  // designed to persist across recordings). Left unguarded, an id cached
  // before a reset would silently collide with whatever unrelated class the
  // new generation reassigns that same id to. cleanup_table() compares this
  // against Profiler::instance()->classMap()->generation() and, on a
  // mismatch, drops every such cached id before resuming. Initialized to 0
  // (StringDictionary's own initial generation), not a sentinel, since a
  // cleanup_table() call before any clearAll() has ever run must NOT treat
  // that as a mismatch.
  u64 _last_class_map_generation;

  Error initialize(Arguments &args);
  Error initialize_table(JNIEnv *jni, int sampling_interval);

  // force=true is used by track()'s table-overflow branch to run a cleanup
  // synchronously from the allocation-sampling call stack, bypassing the
  // GC-epoch-changed check below. The per-klass population tracking below
  // (_gc_generations) runs on both paths, once per genuinely new GC epoch
  // (see "is_epoch_owner" in livenessTracker.cpp).
  //
  // allow_resolve gates resolveKlassId() - a real Class.getName()
  // Java-bytecode upcall, unlike the plain native JVMTI calls already made
  // elsewhere on track()'s callback stack - independently of force: force
  // only says "bypass the epoch-unchanged early-exit", it says nothing about
  // which call stack this is running on. track()'s hot-path call passes
  // force=true, allow_resolve=false (too costly/re-entrancy-prone to resolve
  // from the SampledObjectAlloc callback stack - reuses whatever
  // cached_klass_id an entry already picked up from an earlier resolving
  // sweep, or skips accounting for that entry this epoch if it was never
  // resolved). flush_table()/stop() pass the defaults (force=false,
  // allow_resolve=true) - the original organic, GC-cadence path. LivenessTracker::maybeForceCleanup() passes force=true,
  // allow_resolve=true: it runs on ReferenceChainTracker's own background
  // thread (referenceChains.cpp), not the allocation hot path, so the same
  // upcalls flush_table() already makes safely are just as safe there - see
  // that method's own comment for why a third caller needs both bypassing
  // the early-exit *and* resolution.
  void cleanup_table(bool force = false, bool allow_resolve = true);

  void flush_table(std::set<int> *tracked_thread_ids);

  void onGC();
  void runCleanup();

  jlong getMaxMemory(JNIEnv *env);

  // Resolves the best available post-GC heap usage sample, mirroring
  // flush_table()'s own resolution order (JDK17+ exact
  // CollectedHeap::_used_at_last_gc when supported, otherwise onGC()'s own
  // _used_after_last_gc snapshot, falling back to a live usage read if
  // neither has produced anything yet, e.g. before the first GC). Shared by
  // flush_table()'s JFR event and onGC()'s heap-floor ring sample so both
  // read the same value the same way. Returns 0 only if HeapUsage itself has
  // nothing to offer. *out_is_last_gc (if non-null) reports which case was
  // used, for callers (flush_table()) that need to say so in the JFR event.
  size_t resolvePostGcHeapUsage(bool *out_is_last_gc);

  // --- Per-klass population tracking (cleanup_table()'s epoch-advance pass only) ---

  // Resolves the StringDictionary id for `ref`'s class, mirroring
  // flush_table()'s existing class-name resolution above (GetObjectClass +
  // Class.getName() + Profiler::lookupClass()) - this is the "genuinely new
  // cost on an existing pass" the design doc flags, previously paid only at
  // JFR-flush time. Returns 0 (StringDictionary's own "no entry" sentinel)
  // if the name could not be resolved or interned.
  u32 resolveKlassId(JNIEnv *env, jobject ref);

  // Increments klass_id's running sample count in _klass_count_scratch for
  // the epoch currently being processed, creating a new scratch slot (with
  // `sample_source` remembered for a possible new KlassPopulationEntry) if
  // this is the first surviving instance of this klass seen so far this
  // epoch. No-op if the scratch table is already full and klass_id is not
  // present - the same fixed-capacity/best-effort tradeoff
  // _klass_population's own table already accepts, one level up.
  void accumulateKlassCount(u32 klass_id, jlong age, jweak sample_source);

  // Pushes `count` into klass_id's ring buffer, creating the entry (evicting
  // the least-recently-updated entry first if the table is already at
  // MAX_KLASS_POPULATION_ENTRIES capacity - the same evict-LRU-on-insert-
  // when-full shape NativeSocketSampler's fd cache already solves,
  // nativeSocketSampler.h:141-142/184's insertFdAddrLocked(), and the same
  // "single agent-owned pass, lock already held by caller" shape
  // cleanup_table() itself already uses) if klass_id has never been seen.
  // A newly-created entry's `representative` is left null - it is the
  // caller's job (foldKlassCountsLocked(), which owns the JNIEnv this
  // method deliberately does not touch) to fill it in, which keeps this
  // method free of any JNI call and therefore directly exercisable by gtest
  // without a live JVM. On return, *out_slot is the table slot used for
  // klass_id and *out_created is true iff a new entry was created (an
  // evicted-and-reused slot counts as "created", since the old klass_id's
  // data was fully replaced). Returns the evicted entry's representative
  // jweak (nullptr if nothing was evicted, or the evicted entry had none)
  // so the caller can DeleteWeakGlobalRef() it.
  // Precondition: _table_lock is held (by cleanup_table(), the only
  // production caller).
  jweak recordKlassPopulationSampleLocked(u32 klass_id, u32 count, u64 epoch,
                                           int *out_slot, bool *out_created);

  // Drains _klass_count_scratch into _klass_population for the epoch that
  // just finished, minting a fresh representative jweak (from each entry's
  // KlassCountScratch::sample_source) for klasses not already present, and
  // retrying the mint for existing entries whose representative is still
  // null (a previous epoch's mint attempt can fail if sample_source died in
  // the window between cleanup_table()'s survival check and the mint - see
  // this method's own retry-condition comment, livenessTracker.cpp) - see
  // recordKlassPopulationSampleLocked()'s comment for why that JNI work
  // happens here rather than inside it. A fresh weak global ref
  // is used instead of aliasing sample_source directly because
  // sample_source is the corresponding TrackingEntry's own jweak: that
  // entry's slot in _table is reused (and its jweak deleted via
  // DeleteWeakGlobalRef) the moment the tracked object dies and
  // cleanup_table() reaps it, which would leave _klass_population holding a
  // dangling handle if it aliased the same jweak. Resets
  // _klass_count_scratch_size to 0 once drained. Called with _table_lock
  // held, at the end of cleanup_table()'s epoch-advance pass.
  // allow_resolve mirrors resolveKlassId()'s own parameter (cleanup_table()'s
  // header comment): when false, this runs synchronously on the JVMTI
  // SampledObjectAlloc callback stack (track()'s table-overflow branch), so
  // the representative-minting NewLocalRef/NewWeakGlobalRef/DeleteLocalRef
  // churn below is skipped - the ring/count bookkeeping still happens, and a
  // missing representative is retried on the next allow_resolve=true sweep
  // (see the retry-condition comment in livenessTracker.cpp).
  void foldKlassCountsLocked(JNIEnv *env, u64 epoch, bool allow_resolve);

  // --- Slope computation and candidate ranking (selectLeakCandidates() below) ---

  // The sustained-trend gate (this class's own header comment above,
  // "Sustained-trend gate") - both-required growth-magnitude and floor-rise
  // tests, design doc's explicit "mean of thirds" choice over full
  // least-squares regression (cheap, allocation-free, one pass over the
  // ring, no sorting or extra storage). A single scan
  // (ringThirdsStats(), livenessTracker.cpp) both derives the pass/fail
  // result below AND updates entry.cached_slope (recent third's mean minus
  // earliest third's mean) for selectLeakCandidates()'s ranking, rather than
  // that method re-scanning the same unchanged ring a moment later. Returns
  // false (leaving entry.cached_slope untouched) if entry.ring_fill is below
  // KLASS_POPULATION_MIN_FILL_FOR_TREND - not enough history yet to trust a
  // trend; callers must check ring_fill themselves before trusting
  // cached_slope, exactly as they checked this method's own return value
  // before cached_slope existed.
  //
  // Called from recordKlassPopulationSampleLocked() every time a new sample
  // is pushed (both the production path,
  // foldKlassCountsLocked()->recordKlassPopulationSampleLocked(), and the
  // klassPopulationRecordForTest() test seam that calls the same method
  // directly), so KlassPopulationEntry::consecutive_positive/cached_slope
  // are always kept in sync with the ring they summarize, regardless of
  // caller.
  bool hasQualifyingGrowth(const KlassPopulationEntry &entry) const;

  // Pushes `used`/`timestamp_ns`/`container_used` into _heap_floor_ring/
  // _heap_floor_time_ring/_container_mem_ring - see those members' own
  // comments for why this is lock-free rather than _table_lock-guarded.
  // Called only from onGC() (single-writer-at-a-time, same comment), which
  // supplies OS::nanotime() and OS::getContainerMemoryUsage() explicitly
  // rather than this method calling them internally - keeps this method
  // itself deterministic for the heapFloorRecordForTest() test seam below.
  void recordHeapFloorSample(u64 used, u64 timestamp_ns, u64 container_used);

  // Internal: pushes to the rings without checking
  // _heap_floor_recording_disabled_for_test. Called by
  // recordHeapFloorSample() (after the debug-only flag check) and by
  // heapFloorRecordForTest() (which bypasses the check so a test can
  // seed the rings even while real GC recording is disabled).
  void recordHeapFloorSampleUnchecked(u64 used, u64 timestamp_ns, u64 container_used);

  // Reads whether the aggregate post-GC live heap has itself shown a
  // sustained rise over _heap_floor_ring's horizon - see
  // LEAK_TREND_HYSTERESIS_BASE/CORROBORATED's own comment above for how
  // selectLeakCandidates() uses this (a uniform hysteresis-threshold
  // selector for the whole scan, never a per-candidate veto or boost).
  bool heapFloorRising() const;

public:
  static LivenessTracker *instance() {
    static LivenessTracker instance;
    return &instance;
  }

  // Public read accessor for the auto-tuner (ReferenceChainTracker::autoTuneDefaults)
  // and secondsToOOM(). See _max_heap_bytes's own comment above.
  jlong maxHeapBytes() const { return _max_heap_bytes; }

  constexpr static int MAX_LEAK_CANDIDATES = 5;
  // Delete copy constructor and assignment operator to prevent copies
  LivenessTracker(const LivenessTracker&) = delete;
  LivenessTracker& operator=(const LivenessTracker&) = delete;

  LivenessTracker()
      : _initialized(false), _enabled(false), _stored_error(Error::OK),
        _table_size(0), _table_cap(0), _table_max_cap(0), _table(NULL),
        _subsample_ratio(0.1), _record_heap_usage(false), _Class(NULL),
        _Class_getName(0), _gc_epoch(0), _last_gc_epoch(0),
        _last_cleanup_ns(0), _used_after_last_gc(0),
        _heap_floor_ring_head(0), _heap_floor_ring_fill(0),
        _max_heap_bytes(-1), _container_memory_limit(-1),
        _gc_generations(false),
        _klass_population_size(0), _klass_count_scratch_size(0),
        _last_class_map_generation(0) {}

  Error start(Arguments &args);
  void stop();
  void track(JNIEnv *env, AllocEvent &event, jint tid, jobject object, u64 call_trace_id);
  void flush(std::set<int> &tracked_thread_ids);

  // Frees this thread's subsampling RNG state (track()'s gen/dis/skipped
  // ThreadLocals, livenessTracker.cpp). Must be called from a thread that is
  // about to detach/terminate - see those ThreadLocal's own comment for why
  // their pthread-key destructors alone cannot be relied on for JNI-attached
  // threads. Safe to call even if this thread never called track().
  static void releaseThreadLocalState();

  // Reads the per-klass population histories (_klass_population) and
  // writes up to `max` leak candidates into `out`: klasses whose recent
  // population trend is positive (growing), ranked by trend magnitude
  // descending, capped at MAX_LEAK_CANDIDATES regardless of `max` (design
  // doc's Open Question 3 "top 3-5" cutoff). Returns the number of
  // candidates written (0 if _gc_generations was never enabled -
  // _klass_population stays empty in that case, since population tracking
  // is gated on it, so no separate guard is needed here). Called on demand
  // by the BFS-pass poll, not on any timer of its own; does no JNI work, so it is safe
  // to call from any thread that can take _table_lock (mirrors
  // getLiveTraceIds()'s own shared-lock read pattern, livenessTracker.cpp).
  //
  // The `representative` jweak copied into KlassCandidate here is a snapshot
  // only - callers MUST NOT resolve it directly (e.g. via NewLocalRef())
  // after this method has returned and _table_lock released. This table's
  // LRU eviction (recordKlassPopulationSampleLocked(), livenessTracker.cpp)
  // can DeleteWeakGlobalRef() that exact handle at any point afterwards
  // (from cleanup_table()'s epoch-advance pass, running on a different
  // thread), which invalidates the handle - a later NewLocalRef() on it is
  // undefined behavior per the JNI spec, not merely "returns null". Use
  // resolveCandidateRepresentative() below instead, which re-reads the
  // table's current value for klass_id atomically with the resolve.
  int selectLeakCandidates(KlassCandidate *out, int max);

  // Re-reads klass_id's current representative from _klass_population and
  // resolves it to a fresh JNI local ref, both under the same _table_lock
  // critical section - closes the race selectLeakCandidates()'s own comment
  // above describes: a KlassCandidate snapshot returned by that method can
  // go stale (LRU-evicted and DeleteWeakGlobalRef()'d) at any point before a
  // caller gets around to resolving it. Looking the entry up again by
  // klass_id here, under lock, guarantees NewLocalRef() only ever runs on a
  // representative jweak this table still actually owns at the moment of the
  // call: if klass_id has since been evicted (or was never assigned a
  // representative), the lookup simply fails to find it and this returns
  // nullptr without ever touching the stale handle. Returns nullptr if
  // klass_id is no longer present, has no representative yet, or the
  // representative's referent has since been collected (NewLocalRef() on a
  // jweak returns null in that case, JNI spec). Mirrors the shared-lock read
  // pattern selectLeakCandidates()/getLiveTraceIds() already use.
  jobject resolveCandidateRepresentative(JNIEnv *env, u32 klass_id);

  // Exposes the _gc_generations gate (see that member's own comment) so a
  // caller outside this class - ReferenceChainTracker::pollWatchedTargets()
  // (referenceChains.cpp), PROF-15341's LivenessTracker-to-ReferenceChainTracker
  // bridging step - can skip
  // calling selectLeakCandidates() entirely when the feature isn't in use,
  // rather than relying on that method's own "returns 0" fallback to make
  // the no-op cheap. Read-only; this accessor never toggles the flag.
  bool gcGenerationsEnabled() const {
    return _gc_generations.load(std::memory_order_relaxed);
  }

  // Time-to-OOM projection against whichever of two independent boundaries
  // is tighter: the JVM heap (_heap_floor_ring vs _max_heap_bytes) or the
  // container/cgroup memory limit (_container_mem_ring vs
  // _container_memory_limit). The two rings are pushed together (same
  // head/fill index, shared _heap_floor_time_ring timestamps - see
  // _container_mem_ring's own comment) so this compares _max_heap_bytes
  // against _container_memory_limit up front (the latter treated as
  // unbounded when unavailable) and runs the "mean of thirds" rate
  // extrapolation (allocation-free, one ring scan) only once, against
  // whichever limit is smaller - not once per boundary. This matters
  // because container memory can grow from causes the heap-floor ring never
  // sees at all (native/off-heap allocations), so a heap-only projection can
  // under-warn right up until an OOM-kill from container memory pressure
  // that had nothing to do with heap occupancy.
  //
  // Exists because selectLeakCandidates()'s per-klass gate
  // (KLASS_POPULATION_MIN_FILL_FOR_TREND ring samples plus
  // LEAK_TREND_HYSTERESIS_BASE/CORROBORATED consecutive qualifying epochs)
  // can take longer to trust a candidate than a fast leak has left before
  // OOM - this gives ReferenceChainTracker::hasLeakSignal() an independent,
  // rate-based signal to start a search immediately instead of waiting on
  // that gate. Not a claim that growth stays linear, only that a
  // short-horizon linear extrapolation is a reasonable urgency signal.
  // Returns a negative value if the chosen ring is not filled enough yet
  // (gcGenerationsEnabled() is off, or too few GC epochs have happened), not
  // rising, or neither _max_heap_bytes nor _container_memory_limit was ever
  // resolved - callers must treat any non-positive return as "no projection
  // available", not "zero seconds". Returns 0 if the chosen ring's recent
  // mean has already reached its limit.
  //
  // Known limitation, inherited from heapFloorRising() rather than
  // introduced here: cleanup_table()'s class-map-reset branch clears
  // _klass_population but never _heap_floor_ring/_heap_floor_time_ring/
  // _container_mem_ring, so a stop()/start() gap with a real wall-clock
  // pause in between can still mix pre-gap and post-gap samples into the
  // same window. heapFloorRising() only risked a magnitude error from this;
  // this method additionally divides by elapsed time, so the same gap
  // understates the growth rate (overstates the projected time-to-OOM)
  // rather than the reverse - not solved here.
  double secondsToOOM() const;

  // Third trigger for cleanup_table(), alongside track()'s table-overflow
  // branch (forced) and flush_table()'s JFR-flush cadence (organic): those
  // two both depend on ObjectSampler's allocation-sampling callback firing
  // often enough. ObjectSampler::updateConfiguration()'s PID controller
  // throttles the JVMTI heap sampling interval toward a fixed target *event
  // rate*, not a fixed *byte* rate - under sustained, fast heap growth this
  // can push the interval high enough that SampledObjectAlloc (and therefore
  // track()) stops firing in practice, starving cleanup_table() of both its
  // forced trigger and the per-klass population samples
  // selectLeakCandidates()'s slope computation needs. If that happens, the
  // history cleanup_table() would otherwise have advanced goes stale and
  // ReferenceChainTracker::hasLeakSignal() can never see a positive trend
  // again, no matter how much the leaking population actually grows.
  //
  // Called once per ReferenceChainTracker::threadLoop wake (~1s cadence, see
  // referenceChains.cpp) with a live JNIEnv already in hand - a convenient,
  // already-existing periodic tick, not a new thread. No-ops unless both:
  // (a) at least 30s have passed since the last cleanup_table() sweep
  // (organic, forced, or one run by this method), and (b) at least one GC
  // has happened since then (gcEpoch() != _last_gc_epoch) - so this never
  // does a pointless sweep of an unchanged table.
  void maybeForceCleanup(u64 now_ns);

  static void JNICALL GarbageCollectionFinish(jvmtiEnv *jvmti_env);

  // Test seams - not part of the production API. Mirrors
  // NativeSocketSampler's own "for testing only" accessors
  // (nativeSocketSampler.h's fdAddrCacheSizeForTest()/
  // fdAddrCacheInsertForTest()) rather than befriending the test binary.
  // These only exercise the JNI-free ring/eviction mechanics
  // (recordKlassPopulationSampleLocked() takes no JNIEnv), never
  // foldKlassCountsLocked()'s representative-minting step, which needs a
  // live JVM and is therefore out of gtest's reach.
  int klassPopulationSizeForTest() const { return _klass_population_size; }
  bool klassPopulationLookupForTest(u32 klass_id, KlassPopulationEntry *out) const {
    for (int i = 0; i < _klass_population_size; i++) {
      if (_klass_population[i].klass_id == klass_id) {
        *out = _klass_population[i];
        return true;
      }
    }
    return false;
  }
  jweak klassPopulationRecordForTest(u32 klass_id, u32 count, u64 epoch,
                                      int *out_slot, bool *out_created) {
    return recordKlassPopulationSampleLocked(klass_id, count, epoch, out_slot,
                                              out_created);
  }
  // Sets an entry's representative directly - production code only ever
  // does this via foldKlassCountsLocked()'s JNI-dependent minting step
  // (out of gtest's reach, see the class comment above), so tests use this
  // seam instead to set up a fake representative and assert it comes back
  // out of recordKlassPopulationSampleLocked() as the evicted jweak when
  // that entry is later LRU-evicted. No-op if klass_id is not present.
  // Also called from a live-JVM test (not just gtest) while the BFS thread
  // (ReferenceChainTracker::threadLoop()) may concurrently be inside
  // cleanup_table()'s epoch-advance pass, which holds _table_lock while
  // mutating _klass_population/_klass_population_size - so this seam takes
  // the same lock rather than writing the field unguarded (mirrors
  // klassPopulationResetForTest() immediately below). Deletes any previous
  // representative via DeleteWeakGlobalRef() before overwriting, the same
  // way foldKlassCountsLocked() handles a stale representative on eviction -
  // otherwise repeated calls for the same klass_id leak a JNI weak global
  // ref per call.
  void klassPopulationSetRepresentativeForTest(JNIEnv *env, u32 klass_id, jweak rep) {
    _table_lock.lock();
    for (int i = 0; i < _klass_population_size; i++) {
      if (_klass_population[i].klass_id == klass_id) {
        jweak prev = _klass_population[i].representative;
        _klass_population[i].representative = rep;
        _table_lock.unlock();
        if (prev != nullptr) {
          env->DeleteWeakGlobalRef(prev);
        }
        return;
      }
    }
    _table_lock.unlock();
  }
  // Unlike the other klassPopulation*ForTest() seams above, this one is
  // also called from a live-JVM test (not just gtest) while the BFS thread
  // (ReferenceChainTracker::threadLoop()) may concurrently be inside
  // cleanup_table()'s epoch-advance pass, which holds _table_lock while
  // mutating _klass_population_size/_klass_population - so this seam must
  // take the same lock rather than writing the field unguarded.
  void klassPopulationResetForTest() {
    _table_lock.lock();
    _klass_population_size = 0;
    _table_lock.unlock();
    // Also reset the heap-floor ring: it is a sibling piece of the same
    // _gc_generations-gated feature, read by every selectLeakCandidates()
    // scan (heapFloorRising()), so leaving it populated across tests in the
    // same gtest binary would leak one test's heap-usage history into the
    // next test's hysteresis threshold. storeRelease() (not plain store())
    // so the reset is published to the BFS/GC thread on arm64's weak memory
    // model - a relaxed store may never be visible to a reader doing
    // loadAcquire() on these same indices.
    storeRelease(_heap_floor_ring_head, (u8)0);
    storeRelease(_heap_floor_ring_fill, (u8)0);
  }

  // Test seams for the heap-floor ring (mirrors klassPopulation*ForTest()'s
  // own seams immediately above) - lock-free, see _heap_floor_ring's own
  // comment, so no locking wrapper is needed here either. timestamp_ns
  // defaults to 0 for existing callers that only exercise
  // heapFloorRising()/heapFloorRisingForTest() (which never reads the time
  // ring) - a test exercising secondsToOOM() must pass real, increasing
  // values explicitly.
  // container_used defaults to 0 for existing callers that only exercise
  // heapFloorRising()/heapFloorRisingForTest() (which never reads
  // _container_mem_ring) - a test exercising secondsToOOM()'s container
  // boundary must pass real, increasing values explicitly.
  void heapFloorRecordForTest(u64 used, u64 timestamp_ns = 0, u64 container_used = 0) {
    recordHeapFloorSampleUnchecked(used, timestamp_ns, container_used);
  }
  bool heapFloorRisingForTest() const { return heapFloorRising(); }
  // Bypasses initialize_table()'s JNI-dependent HeapUsage::getMaxHeap() call
  // (out of gtest's reach, same reason setGcGenerationsForTest() exists) so
  // secondsToOOM() can be exercised directly against a fake max heap size.
  void setMaxHeapBytesForTest(jlong v) {
#ifdef DEBUG
    _max_heap_bytes_for_test.store(v, std::memory_order_release);
#else
    _max_heap_bytes = v;
#endif
  }

  // Mirrors setMaxHeapBytesForTest() above, for secondsToOOM()'s container
  // boundary - bypasses initialize_table()'s real OS::getContainerMemoryLimit()
  // call so a test can exercise the container-vs-heap comparison with a
  // fake, deterministic limit.
  void setContainerMemoryLimitForTest(jlong v) {
#ifdef DEBUG
    _container_memory_limit_for_test.store(v, std::memory_order_release);
#else
    _container_memory_limit = v;
#endif
  }

#ifdef DEBUG
  // Temporarily disables onGC()'s own recordHeapFloorSample() call so a
  // test can seed the ring exclusively via heapFloorRecordForTest() without
  // a real GC interleaving a sample. See _heap_floor_recording_disabled_for_test's
  // own comment above.
  void setHeapFloorRecordingForTest(bool enabled) {
    _heap_floor_recording_disabled_for_test.store(!enabled, std::memory_order_release);
  }
#endif

  // Sets _gc_generations directly, bypassing initialize() (which requires a
  // live JVM - VM::hotspot_version()/VM::jni(), see that method's own code -
  // out of gtest's reach the same way foldKlassCountsLocked()'s
  // representative-minting step is, per this seam block's own comment
  // above). Callers outside this class that only need to exercise
  // gcGenerationsEnabled()'s gate (e.g. referenceChains_ut.cpp's
  // pollWatchedTargets() tests) use this instead of standing up a full
  // initialize()/start() call.
  void setGcGenerationsForTest(bool v) {
    _gc_generations.store(v, std::memory_order_relaxed);
  }

private:
  void getLiveTraceIds(CallTraceIdSet& out_buffer);
};

#endif // _LIVENESSTRACKER_H
