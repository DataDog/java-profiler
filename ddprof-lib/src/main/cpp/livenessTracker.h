/*
 * Copyright 2021, 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _LIVENESSTRACKER_H
#define _LIVENESSTRACKER_H

#include "arch.h"
#include "callTraceHashTable.h"
#include "classTagAllocator.h"
#include "context.h"
#include "engine.h"
#include "event.h"
#include "spinLock.h"
#include "xorshift.h"
#include <atomic>
#include <jvmti.h>
#include <pthread.h>
#include <set>
#include <unordered_set>

class Recording;

// Tracks a sample of recently allocated objects (JVMTI jweak per entry) from
// allocation until GC death or JFR flush, feeding ObjectLivenessEvent /
// HeapUsage output and the leak-candidate ranking below.
typedef struct TrackingEntry {
  jweak ref;
  AllocEvent alloc;
  double skipped;
  u64 call_trace_id;
  jint tid;
  jlong time;
  jlong age;
  jlong leak_tag;  // 0 = untagged; otherwise a tag from the leak tag pool
  Context ctx;
  // StringDictionary id of this object's class, resolved by cleanup_table()'s
  // survivor loop when _gc_generations is enabled (0 = unresolved; 0 is
  // StringDictionary's "no entry" sentinel, so a real id is never 0).
  // flush_table() reuses it instead of re-resolving; track() resets it to 0.
  u32 cached_klass_id;
  // Publication flag for the slot payload. track() reserves a slot via a
  // _table_size CAS under only the shared lock, so a scanner can see the index
  // before the payload is written (malloc/realloc storage is uninitialized). 0
  // (release) before filling, 1 (release) after; scanners load-acquire and
  // skip anything != 1. New storage is zeroed at alloc/realloc time so garbage
  // can never publish.
  volatile int ready;
} TrackingEntry;

struct SubsampleRate {
  double ratio;
  u64 threshold;

  explicit SubsampleRate(double subsample_ratio)
      : ratio(subsample_ratio), threshold(xorshift::threshold(subsample_ratio)) {}
};

// Fixed-capacity, LRU-evicted per-klass population history keyed by klass
// StringDictionary id (Profiler::classMap()): per-epoch surviving generation
// counts plus representative instances, consumed via selectLeakCandidates()
// and referenceChains.cpp's pollWatchedTargets().
typedef struct KlassPopulationEntry {
  u32 klass_id;          // StringDictionary id; 0 = unused slot (0 is also
                          // StringDictionary's "no entry" sentinel, so a real
                          // id is never 0).
  static constexpr int MAX_REPRESENTATIVES_PER_KLASS = 3;
  jweak representatives[MAX_REPRESENTATIVES_PER_KLASS];
  jint rep_tids[MAX_REPRESENTATIVES_PER_KLASS]; // tid each rep was minted from
  int representative_count;
  u32 count_ring[30];     // per-epoch distinct GC ages among this klass's
                          // surviving tracked instances (accumulateKlassCount()).
  u8 ring_head;           // next slot to write
  u8 ring_fill;           // samples written so far, caps at 30
  // Consecutive epochs whose push passed hasQualifyingGrowth(); reset to 0 on
  // any failing push. Must reach a hysteresis threshold
  // (LEAK_TREND_HYSTERESIS_*) before selectLeakCandidates() trusts the klass -
  // an oscillating population passes a single-epoch test about half the time.
  u8 consecutive_positive;
  // Fitted recent-minus-earliest slope as of the last push, cached by
  // hasQualifyingGrowth() so ranking need not re-scan the ring. Meaningless
  // below KLASS_POPULATION_MIN_FILL_FOR_TREND - check ring_fill first.
  mutable double cached_slope;
  u64 last_updated_epoch; // _gc_epoch value as of the last write, for LRU
                          // eviction when the table is full
  // Stable per-class identifier from the negative-tag allocator shared with
  // ReferenceChainTracker (classTagAllocator.h) - NOT klass_id: the classMap
  // dictionary can be compacted/regenerated, so the same class can resolve
  // to different klass_ids from different subsystems; cross-subsystem
  // matching keys on this tag. 0 until minted; always negative once minted.
  jlong stable_class_tag;
  // Per-(klass,tid) trend qualification: a whole-klass rise can come from
  // churn spread across many threads each retaining a stable handful, so
  // selectLeakCandidates() only reports the klass if at least one tid shows a
  // sustained rise OR clears TID_RETAINED_COUNT_BAR - the age trend alone
  // cannot see one-cohort-per-thread accumulation.
  static constexpr int MAX_TID_TRENDS = 8;
  static constexpr int TID_TREND_RING_SIZE = 16;
  struct TidTrend {
    jint tid;   // allocating thread id (TrackingEntry::tid's space)
    u8 ring[TID_TREND_RING_SIZE]; // per-epoch distinct surviving age counts
    u8 count_ring[TID_TREND_RING_SIZE]; // per-epoch surviving tracked
                             // instance counts (pushed together with ring;
                             // feeds TID_RETAINED_COUNT_BAR)
    u8 ring_head;
    u8 ring_fill;
    u8 consecutive_positive; // hysteresis, same push-time update as the
                             // klass-level counter above
    // Seeded by tidTrendRecordForTest() only: the real fold exempts
    // synthetic entries from its absent-tid decay and slot eviction.
    bool synthetic;
  };
  TidTrend tid_trends[MAX_TID_TRENDS];
  int tid_trend_count;
} KlassPopulationEntry;

// One leak-candidate result from selectLeakCandidates(): the klass to
// chase, a live representative, and the qualifying tids (consumed by
// referenceChains.cpp's pollWatchedTargets()).
typedef struct KlassCandidate {
  u32 klass_id;
  jweak representative;
  // Tids whose per-tid trends cleared the same hysteresis gate that qualified
  // this klass; tagLeakInstances() only tags instances these threads
  // allocated, keeping machinery churn from burning pool tags.
  static constexpr int MAX_QUALIFYING_TIDS = KlassPopulationEntry::MAX_TID_TRENDS;
  jint qualifying_tids[MAX_QUALIFYING_TIDS];
  int qualifying_tid_count;
} KlassCandidate;

// Aligned to satisfy SpinLock's 64-byte cache-line alignment requirement.
class alignas(alignof(SpinLock)) LivenessTracker {
  friend Recording;

private:
  // pre-c++17 we should mark these inline(or out of class)
  constexpr static int MAX_TRACKING_TABLE_SIZE = 262144;
  constexpr static int MIN_SAMPLING_INTERVAL = 524288; // 512kiB

  // _klass_population/_klass_count_scratch are scanned linearly - this size
  // keeps such scans cheap.
  constexpr static int MAX_KLASS_POPULATION_ENTRIES = 256;

  constexpr static int KLASS_POPULATION_RING_SIZE = 30;
  // Minimum ring_fill before a trend over the window is trusted.
  constexpr static int KLASS_POPULATION_MIN_FILL_FOR_TREND = 10;
  // Per-tid gate's minimum fill: keeps per-tid qualification latency within
  // the klass gate's own.
  constexpr static int TID_TREND_MIN_FILL_FOR_TREND = 6;
  // Per-tid qualification's second discriminator, OR-ed with the age trend:
  // covers one-cohort-per-thread accumulation, which the age trend cannot see.
  // An order of magnitude above machinery shapes (pools retain 1-5 per
  // class/thread); ~80+ retained instances with the ~10x subsample.
  constexpr static u32 TID_RETAINED_COUNT_BAR = 8;
  // secondsToOOM() corroborates the full-window usage trend with a fit over
  // the most recent half, rejecting a one-time step change that plateaus.
  constexpr static int HEAP_FLOOR_RECENT_HALF_MIN_FILL = 5;

  // --- Sustained-trend gate (hasQualifyingGrowth() below) ---
  // count_ring holds distinct GC ages (generations) among a klass's surviving tracked
  // instances, not the raw count: survivors spanning ever more cohorts means
  // old instances are not dying as new ones arrive - the leak shape.
  constexpr static double LEAK_GROWTH_REL_MIN = 0.15;
  // Absolute floor for the growth bar.
  constexpr static int LEAK_GROWTH_ABS_MIN = 1;

  // Required consecutive qualifying epochs (consecutive_positive) before
  // selectLeakCandidates() trusts a klass; lowered (CORROBORATED) when
  // heapFloorRising() shows an independent whole-heap rise (no per-klass
  // attribution, so it only moves the bar uniformly).
  constexpr static int LEAK_TREND_HYSTERESIS_BASE = 5;
  constexpr static int LEAK_TREND_HYSTERESIS_CORROBORATED = 3;

  // --- Aggregate post-GC heap floor (heapFloorRising() below) ---
  // Same growth test as the per-klass gate, on the global _heap_floor_ring;
  // looser thresholds (the signal is diluted by every other klass's activity),
  // so it only selects the hysteresis level above.
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

  SubsampleRate _subsample;

  // Chase-phase admission-boost state (see admitForTracking()). Two-phase
  // published: slots first, then _watched_tid_count with RELEASE
  // (admitForTracking()'s ACQUIRE load pairs with it) - never trust a slot
  // beyond the observed count.
  jint _watched_tids[KlassCandidate::MAX_QUALIFYING_TIDS];
  volatile int _watched_tid_count;
  volatile bool _urgent_tracking;

  bool _record_heap_usage;

  jclass _Class;
  jmethodID _Class_getName;

  volatile u64 _gc_epoch;
  volatile u64 _last_gc_epoch;

  // OS::nanotime() of the last cleanup_table() sweep that actually ran;
  // drives maybeForceCleanup()'s time-based trigger.
  volatile u64 _last_cleanup_ns;

  size_t _used_after_last_gc;

  // Ring of post-GC live heap sizes, one sample per GC epoch, feeding
  // heapFloorRising()/secondsToOOM(). Lock-free, not _table_lock-guarded:
  // onGC() runs from the GarbageCollectionFinish callback, which can fire
  // synchronously mid-JNI-upcall while this class holds _table_lock (e.g.
  // cleanup_table()'s Class.getName() triggering a GC) - taking the same
  // non-reentrant SpinLock would self-deadlock. GCs are never concurrent, so
  // onGC() is the single writer.
  u64 _heap_floor_ring[KLASS_POPULATION_RING_SIZE];
  // OS::nanotime() paired index-for-index with _heap_floor_ring; lets
  // secondsToOOM() turn byte growth into a rate.
  u64 _heap_floor_time_ring[KLASS_POPULATION_RING_SIZE];
  // Container (cgroup) memory usage, same head/fill index as the rings
  // above; grows from native/off-heap causes the heap ring never sees.
  u64 _container_mem_ring[KLASS_POPULATION_RING_SIZE];
  volatile u8 _heap_floor_ring_head;
  volatile u8 _heap_floor_ring_fill;

  // Debug-only test seam: when true, recordHeapFloorSample() skips
  // recording so a test can seed the ring via heapFloorRecordForTest().
#ifdef DEBUG
  // Atomic so the GC thread sees the test thread's store on arm64's weak
  // memory model; checked at the write point, so a GC already past onGC()'s
  // gate still cannot corrupt the ring.
  std::atomic<bool> _heap_floor_recording_disabled_for_test{false};
#endif

  // Runtime.maxMemory(), resolved once by initialize_table(); a JVM's max
  // heap does not change at runtime. -1 if never resolved.
  jlong _max_heap_bytes;

#ifdef DEBUG
  // Atomic mirror used only by setMaxHeapBytesForTest() so the test
  // thread's store is published to secondsToOOM()'s read on arm64.
  std::atomic<jlong> _max_heap_bytes_for_test{-1};
#endif

  // OS::getContainerMemoryLimit(), resolved once by initialize_table(). -1 if
  // never resolved or not under a memory-limited cgroup - treated as "no
  // boundary".
  jlong _container_memory_limit;

#ifdef DEBUG
  // Test mirror of _container_memory_limit, same reasoning as
  // _max_heap_bytes_for_test above.
  std::atomic<jlong> _container_memory_limit_for_test{-1};
#endif

  // Gates per-klass population tracking; set from args._gc_generations in
  // initialize(), deliberately not folded into _enabled (which also covers
  // plain _record_liveness). std::atomic (relaxed): initialize() writes it
  // from the control thread while the BFS/GC-callback threads of a session
  // persisting across a restart can still read it.
  std::atomic<bool> _gc_generations;

  // Per-klass population history table (see KlassPopulationEntry above);
  // populated only from cleanup_table()'s epoch-advance pass, guarded by
  // _table_lock.
  KlassPopulationEntry _klass_population[MAX_KLASS_POPULATION_ENTRIES];
  int _klass_population_size;

  // Scratch reused across cleanup_table() calls, accumulating this epoch's
  // per-klass surviving counts before the fold into _klass_population.
  typedef struct KlassCountScratch {
    u32 klass_id;
    // Distinct GC ages (generations) of surviving tracked instances of
    // this klass at this epoch; the vector's size is the generation count.
    std::vector<u32> ages;
    // Oldest surviving instances seen this epoch, sorted by age descending;
    // representatives are minted biased toward long-lived instances.
    // Fixed-size: no heap allocation in the GC callback path.
    static constexpr int MAX_OLDEST_SAMPLES = 3;
    struct OldestSample {
      jweak ref;
      u32 age;
      jint tid;  // allocating thread of this instance
    };
    OldestSample oldest[MAX_OLDEST_SAMPLES];
    int oldest_count;
    // Per-thread distinct surviving GC ages within this klass - the
    // generation-count signal at per-thread granularity. Thread id, not
    // call_trace_id: lambda/synthetic variants of one logical site produce
    // distinct trace ids.
    static constexpr int MAX_THREADS_PER_KLASS = 16;
    static constexpr int MAX_AGES_PER_THREAD = 32;
    struct ThreadGens {
      jint tid;
      u32 ages[MAX_AGES_PER_THREAD];  // sorted distinct ages
      u32 age_count;
      u32 count;  // surviving tracked instances of this klass this epoch
                  // (counts every object) - feeds TID_RETAINED_COUNT_BAR
    };
    ThreadGens threads[MAX_THREADS_PER_KLASS];
    int thread_count;
  } KlassCountScratch;
  KlassCountScratch _klass_count_scratch[MAX_KLASS_POPULATION_ENTRIES];
  int _klass_count_scratch_size;

  // classMap()'s generation as of the last cleanup_table() check, mirroring
  // ReferenceChainTracker::_last_class_map_generation (referenceChains.h).
  // Profiler::start() clears the class map and restarts its id namespace,
  // but cached klass ids survive stop()/start() (this table persists), so a
  // stale id could collide with a newly assigned class; cleanup_table()
  // drops all cached ids on a mismatch. Re-synced in initialize() to the
  // current generation, not the constructor's 0: start() runs strictly
  // after Profiler::start()'s clearAll(), so the 0 sentinel would trip a
  // spurious mismatch on the first sweep, wiping valid history.
  u64 _last_class_map_generation;

  // --- Leak tag pool ---
  // Reusable pool of JVMTI tags for directly tagging tracked leaking
  // objects, so the BFS can find the exact leaking objects (HeapLiveObject
  // correlation).
  static constexpr int LEAK_TAG_POOL_SIZE = 256;
  static constexpr jlong LEAK_TAG_BASE = 0x40000000LL;
  int _leak_tag_free_list[LEAK_TAG_POOL_SIZE];
  int _leak_tag_free_count;
  // Per tag in the pool, the (call_trace_id, tid) of the tracked object it
  // was assigned to; used by ReferenceChainTracker for coverage tracking.
  struct LeakTagInfo {
    u64 call_trace_id;
    jint tid;
  };
  LeakTagInfo _leak_tag_info[LEAK_TAG_POOL_SIZE];

  jlong acquireLeakTag(u64 call_trace_id, jint tid);
  void releaseLeakTag(jlong tag);

  Error initialize(Arguments &args);
  Error initialize_table(JNIEnv *jni, int sampling_interval);

  // force=true bypasses the epoch-unchanged early-exit (track()'s
  // table-overflow branch runs a cleanup synchronously). allow_resolve
  // gates resolveKlassId() - a Class.getName() Java upcall - independently
  // of force: track()'s hot path passes (true, false) (too re-entrancy-prone
  // on the SampledObjectAlloc callback stack); flush_table()/stop() pass the
  // defaults; maybeForceCleanup() passes (true, true) on
  // ReferenceChainTracker's background thread. Population tracking runs on
  // both paths, once per genuinely new GC epoch (see "is_epoch_owner" in
  // livenessTracker.cpp).
  void cleanup_table(bool force = false, bool allow_resolve = true);

  void flush_table(std::set<int> *tracked_thread_ids);

  void onGC();
  void runCleanup();

  jlong getMaxMemory(JNIEnv *env);

  // Best available post-GC heap usage sample: JDK17+ exact
  // CollectedHeap::_used_at_last_gc when supported, else onGC()'s
  // _used_after_last_gc snapshot, else a live read. Shared by flush_table()'s
  // JFR event and onGC()'s heap-floor sample; *out_is_last_gc says which.
  size_t resolvePostGcHeapUsage(bool *out_is_last_gc);

  // --- Per-klass population tracking (cleanup_table()'s epoch-advance pass only) ---

  // StringDictionary id for `ref`'s class, resolved the same way
  // ObjectSampler::recordAllocation() and ReferenceChainTracker's
  // resolveClassMap() do it. Returns 0 ("no entry" sentinel) on failure.
  u32 resolveKlassId(JNIEnv *env, jobject ref);

  // Adds one surviving instance to klass_id's scratch slot for the epoch,
  // creating the slot (with sample_source) if absent. No-op if the scratch
  // table is full and klass_id is absent - same best-effort tradeoff
  // _klass_population accepts.
  void accumulateKlassCount(u32 klass_id, jlong age, jweak sample_source,
                           jint tid);
  void insertOldestSample(KlassCountScratch &scratch, jweak sample_source,
                           u32 age, jint tid);
  void insertThreadGen(KlassCountScratch &scratch, jint tid, u32 age);

  // Pushes `count` into klass_id's ring buffer, creating the entry on first
  // sight and evicting the least-recently-updated entry when full. JNI-free
  // (gtest-exercisable); evicted representative jweaks are returned via
  // out_evicted for the caller (which owns the JNIEnv) to delete. *out_created
  // is true iff a new entry was created. Precondition: _table_lock held
  // (cleanup_table()).
  jweak recordKlassPopulationSampleLocked(u32 klass_id, u32 count, u64 epoch,
                                           int *out_slot, bool *out_created,
                                           jweak *out_evicted = nullptr,
                                           int *out_evicted_count = nullptr,
                                           int max_evicted = 0);

  // Drains _klass_count_scratch into _klass_population for the epoch that just
  // finished, minting fresh representative jweaks for klasses without live
  // ones. Fresh weak refs, never aliased from sample_source (a TrackingEntry
  // jweak): that slot's jweak is deleted as soon as the tracked object dies,
  // which would leave a dangling handle. allow_resolve=false (track()'s
  // table-overflow branch) skips the minting JNI churn; retried on the next
  // allow_resolve=true sweep.
  void foldKlassCountsLocked(JNIEnv *env, u64 epoch, bool allow_resolve);

  // Get-or-mints slot's stable_class_tag from `instance`'s class, shared by
  // foldKlassCountsLocked() and the test seams. No-op if slot is out of range,
  // instance is null, or a tag is already minted.
  void mintStableClassTagIfNeeded(JNIEnv *env, int slot, jobject instance);

  // --- Slope computation and candidate ranking (selectLeakCandidates() below) ---

  // Per-tid sustained-trend gate: the same growth test hasQualifyingGrowth()
  // applies to a klass's ring, at TidTrend granularity (same LEAK_GROWTH_* bar
  // - per-tid age-cardinality is the same small-integer signal).
  bool hasQualifyingTidGrowth(const KlassPopulationEntry::TidTrend &trend) const;

  // Per-tid qualification for ONE epoch push: age-trend test OR the pushed
  // surviving count clearing TID_RETAINED_COUNT_BAR. The caller folds the
  // result into consecutive_positive, so hysteresis makes it SUSTAINED.
  bool tidPushQualifies(const KlassPopulationEntry::TidTrend &trend,
                        u32 current_count) const;

  // Folds one epoch's per-thread scratch into slot's per-tid trend rings:
  // present tids push their epoch count; absent tids push 0 (a dead thread
  // must not keep a stale rising ring); synthetic (test-seeded) trends are
  // exempt. New tids beyond MAX_TID_TRENDS evict the weakest non-synthetic
  // trend (a rising leak tid resists eviction). Best-effort: the scratch caps
  // per-klass threads at 16 > MAX_TID_TRENDS. _table_lock held by the caller
  // (foldKlassCountsLocked()).
  void recordTidTrendSamplesLocked(int slot, const KlassCountScratch &scratch);

  // The sustained-trend gate: least-squares growth test over entry's ring,
  // also updating entry.cached_slope for ranking (the ring only changes on
  // push, so a re-scan would compute the same value). Returns false
  // (cached_slope untouched) below the fill minimum; called on every push.
  bool hasQualifyingGrowth(const KlassPopulationEntry &entry) const;

  // Pushes used/timestamp_ns/container_used into the heap-floor rings (see
  // those members). Called only from onGC(), which supplies nanotime and
  // container usage explicitly, keeping this deterministic for the
  // heapFloorRecordForTest() seam.
  void recordHeapFloorSample(u64 used, u64 timestamp_ns, u64 container_used);

  // Pushes to the rings without checking
  // _heap_floor_recording_disabled_for_test; heapFloorRecordForTest() bypasses
  // the check so a test can seed the rings while real GC recording is
  // disabled.
  void recordHeapFloorSampleUnchecked(u64 used, u64 timestamp_ns, u64 container_used);

  // Whether the aggregate post-GC heap has shown a sustained rise over
  // _heap_floor_ring's horizon; selects the hysteresis level for the scan.
  bool heapFloorRising() const;

public:
  static LivenessTracker *instance() {
    static LivenessTracker instance;
    return &instance;
  }

  // Read accessor for the auto-tuner (ReferenceChainTracker::autoTuneDefaults)
  // and secondsToOOM(); see _max_heap_bytes.
  jlong maxHeapBytes() const { return _max_heap_bytes; }

  constexpr static int MAX_LEAK_CANDIDATES = 5;

  LivenessTracker(const LivenessTracker&) = delete;
  LivenessTracker& operator=(const LivenessTracker&) = delete;


  LivenessTracker()
      : _initialized(false), _enabled(false), _stored_error(Error::OK),
        _table_size(0), _table_cap(0), _table_max_cap(0), _table(NULL),
        _subsample(0.1), _watched_tid_count(0), _urgent_tracking(false),
        _record_heap_usage(false), _Class(NULL),
        _Class_getName(0), _gc_epoch(0), _last_gc_epoch(0),
        _last_cleanup_ns(0), _used_after_last_gc(0),
        _heap_floor_ring_head(0), _heap_floor_ring_fill(0),
        _max_heap_bytes(-1), _container_memory_limit(-1),
        _gc_generations(false),
        _klass_population_size(0), _klass_count_scratch_size(0),
        _last_class_map_generation(0),
        _leak_tag_free_count(LEAK_TAG_POOL_SIZE) {}

  Error start(Arguments &args);
  void stop();
  void track(JNIEnv *env, AllocEvent &event, jint tid, jobject object, u64 call_trace_id);

  // track()'s admission gate: raises the live-samples tracking probability
  // above the configured _subsample ratio during the chase phase. Two
  // advisory-only raises: watched tids (noteSelectedCandidates() publishes the
  // qualifying tids, admitted at 100% - the (klass, tid) scope
  // tagLeakInstances() tags) and urgency (setUrgentTracking() from the
  // seconds-to-OOM ramp admits everything). Fail-open: only adds admissions on
  // top of the ratio.
  bool admitForTracking(jint tid);

  // Publishes the current poll's qualifying tids as the watched set above;
  // called every wake including the zero-candidate case, which clears the set
  // (a tid left watched would keep admitting at 100% across OS tid reuse). NOT
  // called from hasLeakSignal()'s max=1 probe: its partial view could drop
  // other candidates' tids.
  void noteSelectedCandidates(const KlassCandidate *candidates, int count);

  // Urgency toggle - see admitForTracking(). Set every threadLoop()
  // iteration so the boost tracks the ramp exactly.
  void setUrgentTracking(bool urgent);

  void flush(std::set<int> &tracked_thread_ids);

  // Frees this thread's subsampling RNG state (rng/skipped ThreadLocals);
  // call from a thread about to detach/terminate.
  static void releaseThreadLocalState();

  // Writes up to `max` leak candidates into `out`: klasses with a positive
  // population trend, ranked by trend magnitude descending, capped at
  // MAX_LEAK_CANDIDATES regardless of `max`. No JNI work; shared-lock read,
  // like getLiveTraceIds().
  //
  // The `representative` jweak is a snapshot - callers MUST NOT resolve it
  // directly (e.g. NewLocalRef()) after this returns: LRU eviction can
  // DeleteWeakGlobalRef() that exact handle, and NewLocalRef() on a deleted
  // jweak is undefined behavior per the JNI spec. Use
  // resolveCandidateRepresentative(), which re-reads under lock.
  int selectLeakCandidates(KlassCandidate *out, int max);

  // Tags tracked instances of the given candidates - only those allocated by a
  // candidate's QUALIFYING tids - with leak-pool JVMTI tags, so machinery
  // churn of the same class does not burn pool tags. The BFS recognizes these
  // tags by range check (isLeakTag, referenceChains.h) and admits the objects
  // into the frontier (HeapLiveObject correlation). Returns the number of tags
  // assigned.
  int tagLeakInstances(jvmtiEnv *jvmti, const KlassCandidate *candidates,
                       int candidate_count);

  // Look up the (call_trace_id, tid) recorded for a leak tag. Returns false
  // if the tag is not a valid leak tag or has been returned to the pool.
  bool getLeakTagInfo(jlong tag, u64 *out_call_trace_id,
                      jint *out_tid) const;

  // Writes up to `max` STABLE CLASS TAGS (stable_class_tag - NOT the classMap
  // klass_id selectLeakCandidates() deals in), ranked by most recent
  // count_ring sample (generation count) descending, capped at
  // MAX_LEAK_CANDIDATES. NO trend/hysteresis gate: called only after
  // hasLeakSignal() already fired via the gated path (see referenceChains.h's
  // _watched_leak_klass_ids). Empty ring or unminted tag = skipped.
  int topKlassesByGenerationCount(u32 *out, int max);

  // Re-reads klass_id's current representative and resolves it to a fresh
  // local ref under the same _table_lock critical section, closing the race
  // described at selectLeakCandidates(). nullptr if klass_id is gone.
  jobject resolveCandidateRepresentative(JNIEnv *env, u32 klass_id);
  int resolveCandidateRepresentatives(JNIEnv *env, u32 klass_id,
                                       jobject *out, int max_out);

  // Exposes the _gc_generations gate so ReferenceChainTracker::
  // pollWatchedTargets() can skip selectLeakCandidates() when the feature is
  // off.
  bool gcGenerationsEnabled() const {
    return _gc_generations.load(std::memory_order_relaxed);
  }

  // Time-to-OOM projection against the tighter of two independent boundaries:
  // the JVM heap (_heap_floor_ring vs _max_heap_bytes) or the container memory
  // limit (absent when unavailable). The shorter time wins: container usage
  // includes native/off-heap memory, so a numerically larger container limit
  // can still be closer to exhaustion than the heap (and vice versa). Gives
  // hasLeakSignal() a rate-based signal that does not wait out the
  // fill+hysteresis gate. Negative return = no projection available; 0 = the
  // chosen boundary already reached its limit.
  double secondsToOOM() const;

  // Third trigger for cleanup_table(): the other two depend on the
  // allocation-sampling callback firing often enough, and
  // ObjectSampler::updateConfiguration()'s PID controller throttles toward a
  // fixed event rate - under sustained fast heap growth it can push the
  // interval high enough that track() stops firing, starving cleanup_table()
  // and stalling the population history. Called once per
  // ReferenceChainTracker::threadLoop wake (~1s); no-ops unless 30s passed
  // since the last sweep AND a GC happened since.
  void maybeForceCleanup(u64 now_ns);

  static void JNICALL GarbageCollectionFinish(jvmtiEnv *jvmti_env);

  // Test seams - not part of the production API; JNI-free mechanics only
  // (representative minting needs a live JVM, out of gtest's reach).
  int klassPopulationSizeForTest() const { return _klass_population_size; }

  // Leak-tag pool test seams (JNI-free pure logic).
  void leakTagPoolResetForTest() {
    for (int i = 0; i < LEAK_TAG_POOL_SIZE; i++) {
      _leak_tag_free_list[i] = i;
      _leak_tag_info[i].call_trace_id = 0;
      _leak_tag_info[i].tid = 0;
    }
    _leak_tag_free_count = LEAK_TAG_POOL_SIZE;
  }

  jlong acquireLeakTagForTest(u64 call_trace_id, jint tid) {
    return acquireLeakTag(call_trace_id, tid);
  }

  void releaseLeakTagForTest(jlong tag) { releaseLeakTag(tag); }

  int leakTagFreeCountForTest() const { return _leak_tag_free_count; }

  // Admission-boost test seams (JNI-free pure logic).
  bool admitForTrackingForTest(jint tid) { return admitForTracking(tid); }

  void setSubsampleRatioForTest(double ratio) { _subsample = SubsampleRate(ratio); }

  // Reset for tests: clears both boost paths, forces ratio=0 (threshold(0) is
  // 0, which no draw compares <, so ratio 0 can never admit), and unseeds this
  // thread's rng.
  void admissionResetForTest();

  int watchedTidCountForTest() const {
    return __atomic_load_n(&_watched_tid_count, __ATOMIC_ACQUIRE);
  }

  jint watchedTidForTest(int i) const { return _watched_tids[i]; }

  static jlong leakTagBaseForTest() { return LEAK_TAG_BASE; }

  static int leakTagPoolSizeForTest() { return LEAK_TAG_POOL_SIZE; }
  bool klassPopulationLookupForTest(u32 klass_id, KlassPopulationEntry *out) const {
    for (int i = 0; i < _klass_population_size; i++) {
      if (_klass_population[i].klass_id == klass_id) {
        *out = _klass_population[i];
        return true;
      }
    }
    return false;
  }
  // TEST-ONLY synthetic-to-real klass-id aliasing: every consumer of a
  // candidate klass id keys on the real Profiler::lookupClass() id space
  // (tagLeakInstances() scans cached_klass_id), so a synthetic seeded id would
  // match nothing; the seams alias each synthetic id to the representative's
  // real class id, established by klassPopulationSetRepresentativeForTest()
  // (the only seam holding an actual instance). The BFS thread may
  // concurrently be inside cleanup_table()'s epoch-advance pass, so the seams
  // below take _table_lock like every other _klass_population mutator.
  struct TestKlassAlias {
    u32 synthetic;
    u32 real;
  };
  static constexpr int MAX_TEST_KLASS_ALIASES = 8;
  TestKlassAlias _test_klass_aliases[MAX_TEST_KLASS_ALIASES];
  int _test_klass_alias_count = 0;

  // All three below require _table_lock held (same as every other
  // _klass_population mutator).
  u32 resolveTestKlassAliasLocked(u32 klass_id) const {
    for (int i = 0; i < _test_klass_alias_count; i++) {
      if (_test_klass_aliases[i].synthetic == klass_id) {
        return _test_klass_aliases[i].real;
      }
    }
    return klass_id;
  }

  void registerTestKlassAliasLocked(u32 synthetic, u32 real) {
    for (int i = 0; i < _test_klass_alias_count; i++) {
      if (_test_klass_aliases[i].synthetic == synthetic) {
        _test_klass_aliases[i].real = real;
        return;
      }
    }
    if (_test_klass_alias_count < MAX_TEST_KLASS_ALIASES) {
      _test_klass_aliases[_test_klass_alias_count++] = {synthetic, real};
    }
  }

  void removeKlassPopulationEntryLocked(int slot) {
    if (slot < 0 || slot >= _klass_population_size) {
      return;
    }
    memmove(&_klass_population[slot], &_klass_population[slot + 1],
            sizeof(KlassPopulationEntry) *
                (size_t)(_klass_population_size - slot - 1));
    _klass_population_size--;
  }

  jweak klassPopulationRecordForTest(u32 klass_id, u32 count, u64 epoch,
                                      int *out_slot, bool *out_created,
                                      jweak *out_evicted = nullptr,
                                      int *out_evicted_count = nullptr,
                                      int max_evicted = 0) {
    _table_lock.lock();
    klass_id = resolveTestKlassAliasLocked(klass_id);
    jweak evicted = recordKlassPopulationSampleLocked(klass_id, count, epoch,
                                                        out_slot, out_created,
                                                        out_evicted,
                                                        out_evicted_count,
                                                        max_evicted);
    _table_lock.unlock();
    return evicted;
  }

  // Seeds one per-tid trend sample for tests/scenarios: pushes `count` as
  // tid's epoch sample on klass_id's entry, marking the trend SYNTHETIC
  // (exempt from the real fold's absent-tid decay and slot eviction - see
  // TidTrend::synthetic) so a scenario's ramp survives interleaved real GC
  // folds. The tid MUST be the allocating thread's real profiler tid
  // (ProfiledThread::currentTid()'s space, JavaProfiler.getTid()) whenever the
  // test relies on tagLeakInstances(): the tagging scope is exactly the
  // qualifying-tid set, and a fake tid matches no tracked instance (gtest
  // exercises the gate only). Creates the klass entry if absent; resolves the
  // synthetic-id aliasing like klassPopulationRecordForTest().
  void tidTrendRecordForTest(u32 klass_id, jint tid, u32 count, u64 epoch) {
    _table_lock.lock();
    klass_id = resolveTestKlassAliasLocked(klass_id);
    int slot = -1;
    for (int i = 0; i < _klass_population_size; i++) {
      if (_klass_population[i].klass_id == klass_id) {
        slot = i;
        break;
      }
    }
    if (slot < 0) {
      int out_slot;
      bool created;
      recordKlassPopulationSampleLocked(klass_id, 0, 0, &out_slot, &created);
      slot = out_slot;
    }
    KlassPopulationEntry &entry = _klass_population[slot];
    KlassPopulationEntry::TidTrend *trend = nullptr;
    for (int i = 0; i < entry.tid_trend_count; i++) {
      if (entry.tid_trends[i].tid == tid) {
        trend = &entry.tid_trends[i];
        break;
      }
    }
    if (trend == nullptr && entry.tid_trend_count <
        KlassPopulationEntry::MAX_TID_TRENDS) {
      trend = &entry.tid_trends[entry.tid_trend_count++];
      trend->tid = tid;
      trend->ring_head = 0;
      trend->ring_fill = 0;
      trend->consecutive_positive = 0;
    }
    if (trend != nullptr) {
      trend->synthetic = true;
      // Seeded value lands in BOTH rings, so a test can qualify a tid either
      // way the production gate does: a rising ramp exercises the age trend,
      // one flat value over TID_RETAINED_COUNT_BAR exercises the count bar.
      trend->ring[trend->ring_head] = (u8)count;
      trend->count_ring[trend->ring_head] = (u8)count;
      trend->ring_head = (u8)((trend->ring_head + 1) %
                             KlassPopulationEntry::TID_TREND_RING_SIZE);
      if (trend->ring_fill < KlassPopulationEntry::TID_TREND_RING_SIZE) {
        trend->ring_fill++;
      }
      if (tidPushQualifies(*trend, count)) {
        if (trend->consecutive_positive < UINT8_MAX) {
          trend->consecutive_positive++;
        }
      } else {
        trend->consecutive_positive = 0;
      }
      (void)epoch; // the per-tid ring is push-ordered like the klass ring;
                   // epoch is only used for last_updated_epoch LRU
    }
    _table_lock.unlock();
  }
  // Sets an entry's representative directly - production only mints these in
  // foldKlassCountsLocked()'s JNI-dependent step (out of gtest's reach).
  // Live-JVM tests may race cleanup_table()'s epoch-advance pass on the BFS
  // thread, hence the lock. Deletes any previous representative via
  // DeleteWeakGlobalRef() first, else repeated calls leak a weak ref each.
  void klassPopulationSetRepresentativeForTest(JNIEnv *env, u32 klass_id, jweak rep) {
    // Resolve the representative's real klass id BEFORE taking _table_lock, so
    // the Class.getName() JNI upcall never runs under the lock (skipped in
    // gtest, where env/_Class_getName are unavailable).
    u32 real_id = klass_id;
    jobject strong = nullptr;
    if (env != nullptr && rep != nullptr && _Class_getName != nullptr) {
      strong = env->NewLocalRef(rep);
      if (strong != nullptr) {
        u32 resolved = resolveKlassId(env, strong);
        if (resolved != 0 && resolved != klass_id) {
          real_id = resolved;
        }
      }
    }
    _table_lock.lock();
    if (real_id != klass_id) {
      registerTestKlassAliasLocked(klass_id, real_id);
      // Re-key an already-seeded synthetic entry to the real id so its ring
      // history survives; a real-keyed entry (genuine samples) wins over a
      // synthetic one.
      int syn_slot = -1;
      int real_slot = -1;
      for (int i = 0; i < _klass_population_size; i++) {
        if (_klass_population[i].klass_id == klass_id) {
          syn_slot = i;
        } else if (_klass_population[i].klass_id == real_id) {
          real_slot = i;
        }
      }
      if (syn_slot >= 0 && real_slot < 0) {
        _klass_population[syn_slot].klass_id = real_id;
      } else if (syn_slot >= 0 && real_slot >= 0) {
        removeKlassPopulationEntryLocked(syn_slot);
      }
    }
    // Find-or-create the entry under real_id: set-representative-first is the
    // required order (scenarios must establish the alias before any seeding).
    // Creating via a count-0, epoch-0 sample reuses
    // recordKlassPopulationSampleLocked()'s creation branch; the seeded ramp
    // that follows still clears hasQualifyingGrowth() (a single 0 at the
    // ring's start only lowers the earliest fitted value, RAISING the slope).
    int slot = -1;
    for (int i = 0; i < _klass_population_size; i++) {
      if (_klass_population[i].klass_id == real_id) {
        slot = i;
        break;
      }
    }
    if (slot < 0) {
      jweak evicted[KlassPopulationEntry::MAX_REPRESENTATIVES_PER_KLASS];
      int evicted_count = 0;
      bool created = false;
      recordKlassPopulationSampleLocked(real_id, 0, 0, &slot, &created,
                                         evicted, &evicted_count,
                                         KlassPopulationEntry::MAX_REPRESENTATIVES_PER_KLASS);
      if (env != nullptr) {
        for (int r = 0; r < evicted_count; r++) {
          if (evicted[r] != nullptr) {
            env->DeleteWeakGlobalRef(evicted[r]);
          }
        }
      }
    }
    if (slot >= 0) {
      // Clean up old representatives
      for (int r = 0; r < _klass_population[slot].representative_count; r++) {
        jweak prev = _klass_population[slot].representatives[r];
        if (prev != nullptr && env != nullptr) {
          env->DeleteWeakGlobalRef(prev);
        }
      }
      _klass_population[slot].representative_count = 0;
      if (rep != nullptr) {
        _klass_population[slot].representatives[0] = rep;
        _klass_population[slot].representative_count = 1;
      }
      // Mint stable_class_tag from this same representative - without this, a
      // scenario-seeded candidate would never get a tag and
      // topKlassesByGenerationCount() would never report it (env may be
      // nullptr in gtest call sites that don't care).
      if (strong != nullptr) {
        mintStableClassTagIfNeeded(env, slot, strong);
      }
    }
    _table_lock.unlock();
    if (strong != nullptr) {
      env->DeleteLocalRef(strong);
    }
  }
  // Sets an entry's stable_class_tag directly (production only mints it in
  // foldKlassCountsLocked(), out of gtest's reach). No-op if klass_id is not
  // present.
  void klassPopulationSetStableClassTagForTest(u32 klass_id, jlong tag) {
    _table_lock.lock();
    for (int i = 0; i < _klass_population_size; i++) {
      if (_klass_population[i].klass_id == klass_id) {
        _klass_population[i].stable_class_tag = tag;
        break;
      }
    }
    _table_lock.unlock();
  }
  // Also clears _klass_count_scratch_size: a stale scratch would be folded
  // into the just-cleared table by the first real GC, filling it to capacity -
  // every seeded entry then has a synthetic last_updated_epoch far below the
  // folded entries' and is the permanent LRU-eviction victim, leaving
  // ring_fill below KLASS_POPULATION_MIN_FILL_FOR_TREND at select time.
  void klassPopulationResetForTest() {
    _table_lock.lock();
    _klass_population_size = 0;
    _klass_count_scratch_size = 0;
    _test_klass_alias_count = 0;
    _table_lock.unlock();
    // Also reset the heap-floor ring: it is read by every
    // selectLeakCandidates() scan, so leaving it populated would leak one
    // test's history into the next test's hysteresis. storeRelease(), not a
    // plain store, so the reset is visible to a reader doing loadAcquire() on
    // these same indices (arm64's weak memory model).
    storeRelease(_heap_floor_ring_head, (u8)0);
    storeRelease(_heap_floor_ring_fill, (u8)0);
  }

  // Test seams for the heap-floor ring (lock-free, like the production path).
  // timestamp_ns/container_used default to 0 for heapFloorRising() -only
  // callers; a test exercising secondsToOOM() must pass real, increasing
  // values explicitly.
  void heapFloorRecordForTest(u64 used, u64 timestamp_ns = 0, u64 container_used = 0) {
    recordHeapFloorSampleUnchecked(used, timestamp_ns, container_used);
  }
  bool heapFloorRisingForTest() const { return heapFloorRising(); }
  // Bypasses initialize_table()'s JNI-dependent HeapUsage::getMaxHeap() call
  // so secondsToOOM() can be exercised against a fake max heap size.
  void setMaxHeapBytesForTest(jlong v) {
#ifdef DEBUG
    _max_heap_bytes_for_test.store(v, std::memory_order_release);
#else
    _max_heap_bytes = v;
#endif
  }

  // Mirrors setMaxHeapBytesForTest() for secondsToOOM()'s container boundary.
  void setContainerMemoryLimitForTest(jlong v) {
#ifdef DEBUG
    _container_memory_limit_for_test.store(v, std::memory_order_release);
#else
    _container_memory_limit = v;
#endif
  }

#ifdef DEBUG
  // Temporarily disables onGC()'s recordHeapFloorSample() call so a test can
  // seed the ring via heapFloorRecordForTest(); see
  // _heap_floor_recording_disabled_for_test.
  void setHeapFloorRecordingForTest(bool enabled) {
    _heap_floor_recording_disabled_for_test.store(!enabled, std::memory_order_release);
  }
#endif

  // Sets _gc_generations directly, bypassing initialize() (which requires a
  // live JVM); e.g. referenceChains_ut.cpp's pollWatchedTargets() tests.
  void setGcGenerationsForTest(bool v) {
    _gc_generations.store(v, std::memory_order_relaxed);
  }

private:
  void getLiveTraceIds(CallTraceIdSet& out_buffer);
};

#endif // _LIVENESSTRACKER_H
