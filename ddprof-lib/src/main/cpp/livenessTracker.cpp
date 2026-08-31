/*
 * Copyright 2021, 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <algorithm>
#include <cstdint>
#include <limits>
#include <random>
#include <set>
#include <thread>

#include "arch.h"
#include "common.h"
#include "context.h"
#include "context_api.h"
#include "hotspot/vmStructs.h"
#include "hotspot/vmStructs.inline.h"
#include "incbin.h"
#include "jniHelper.h"
#include "livenessTracker.h"
#include "objectSampler.h"
#include "vmEntry.h"
#include "referenceChains.h"
#include "log.h"
#include "nativeMem.h"
#include "os.h"
#include "profiler.h"
#include "threadLocalData.h"
#include "threadLocal.h"
#include "tsc.h"
#include <jni.h>
#include <string.h>

constexpr int LivenessTracker::MAX_TRACKING_TABLE_SIZE;
constexpr int LivenessTracker::MIN_SAMPLING_INTERVAL;

namespace {

// Earliest-third/recent-third mean and minimum of a chronological ring
// window - the one computation hasQualifyingGrowth() (per-klass count_ring)
// and heapFloorRising() (the aggregate _heap_floor_ring) both need, factored
// out so the window/index derivation and the two aggregation loops exist in
// exactly one place rather than three near-identical copies. Templated on
// the reader rather than the ring's element type or storage: the per-klass
// ring is a plain array read under the caller's already-held _table_lock,
// while the heap-floor ring is lock-free and read via loadAcquire() (see
// _heap_floor_ring's own comment, livenessTracker.h) - `read(i)` lets each
// caller supply its own access discipline for physical slot `i` without
// this shared loop needing to know which one applies.
struct RingThirdsStats {
  double earliest_mean;
  double recent_mean;
  double earliest_min;
  double recent_min;
};

template <typename Reader>
bool ringThirdsStats(int head, int fill, int ring_size, int min_fill,
                      Reader read, RingThirdsStats *out) {
  if (fill < min_fill) {
    return false;
  }
  // Chronological (oldest-first) index of the window's first sample.
  int start = (head - fill + ring_size) % ring_size;
  // Full-window least-squares linear regression: y = a + b*x.
  // x = sample position within the window (0 = oldest, fill-1 = newest),
  // y = population count. This uses all samples (not just first/last
  // halves or thirds) and is far more robust for oscillating-but-
  // growing trends than comparing two sub-windows. O(fill) = O(30) per
  // klass per scan — negligible.
  int n = fill;
  if (n < 2) {
    return false;
  }
  double sum_x = 0, sum_y = 0, sum_xx = 0, sum_xy = 0;
  double earliest_min = std::numeric_limits<double>::max();
  double recent_min = std::numeric_limits<double>::max();
  for (int i = 0; i < n; i++) {
    double v = read((start + i) % ring_size);
    sum_x += i;
    sum_y += v;
    sum_xx += (double)i * i;
    sum_xy += (double)i * v;
    if (v < earliest_min) {
      earliest_min = v;
    }
    if (i >= n / 2 && v < recent_min) {
      recent_min = v;
    }
  }
  double denom = (double)n * sum_xx - sum_x * sum_x;
  if (denom == 0) {
    return false;
  }
  double slope = ((double)n * sum_xy - sum_x * sum_y) / denom;
  double intercept = (sum_y - slope * sum_x) / n;
  out->earliest_mean = intercept;
  out->recent_mean = intercept + slope * (n - 1);
  out->earliest_min = earliest_min;
  out->recent_min = recent_min;
  return true;
}

} // namespace

void LivenessTracker::cleanup_table(bool forced, bool allow_resolve) {
  u64 current = load(_last_gc_epoch);
  u64 target_gc_epoch = load(_gc_epoch);
  TEST_LOG("LivenessTracker::cleanup_table forced=%d gc_generations=%d current_epoch=%llu "
           "target_epoch=%llu table_size=%d",
           forced, _gc_generations.load(std::memory_order_relaxed), (unsigned long long)current,
           (unsigned long long)target_gc_epoch, _table_size);

  // is_epoch_owner is true iff this call is the one that moves _last_gc_epoch
  // to target_gc_epoch - i.e. the first cleanup_table() call (forced or not)
  // to observe this particular GC epoch transition. Population accounting
  // below is gated on this rather than on !forced, so a forced (table-
  // overflow) sweep still folds one sample per genuinely new epoch instead
  // of either skipping it entirely or double-counting the same epoch across
  // repeated forced sweeps.
  bool is_epoch_owner = target_gc_epoch != current &&
      __atomic_compare_exchange_n(&_last_gc_epoch, &current, target_gc_epoch,
                                   false, __ATOMIC_RELAXED, __ATOMIC_RELAXED);

  if (!is_epoch_owner && !forced) {
    // if the last processed GC epoch hasn't changed, or if we failed to update
    // it, there's nothing to do
    TEST_LOG("LivenessTracker::cleanup_table early-exit: epoch unchanged and not forced");
    return;
  }

  JNIEnv *env = VM::jni();

  int epoch_diff = (int)(target_gc_epoch - current);

  _table_lock.lock();

  // Detect a class-map reset the same way
  // ReferenceChainTracker::resolveLoadedClasses() does (referenceChains.cpp)
  // - see _last_class_map_generation's own comment (livenessTracker.h).
  // cached_klass_id and _klass_population's klass_id keys are
  // StringDictionary ids from whatever generation was current when they were
  // resolved; once Profiler::start() clears that dictionary and restarts its
  // id namespace, those cached ids can silently collide with a newly
  // assigned, unrelated class. Drop every such cache before this pass reads
  // or writes any of them.
  u64 current_class_map_generation = Profiler::instance()->classMap()->generation();
  if (current_class_map_generation != _last_class_map_generation) {
    for (u32 i = 0; i < _table_size; i++) {
      _table[i].cached_klass_id = 0;
    }
    for (int i = 0; i < _klass_population_size; i++) {
      for (int r = 0; r < _klass_population[i].representative_count; r++) {
        jweak rep = _klass_population[i].representatives[r];
        if (rep != nullptr) {
          env->DeleteWeakGlobalRef(rep);
        }
      }
    }
    _klass_population_size = 0;
    _klass_count_scratch_size = 0;
    _last_class_map_generation = current_class_map_generation;
  }

  u32 sz = _table_size;
  if (sz > 0) {
    u64 start = OS::nanotime(), end;
    u32 newsz = 0;
    std::set<jclass> kept_classes;
    for (u32 i = 0; i < sz; i++) {
      if (_table[i].ref != nullptr &&
          !env->IsSameObject(_table[i].ref, nullptr)) {
        // it survived one more GarbageCollectionFinish event
        u32 target = newsz++;
        if (target != i) {
          _table[target] = _table[i]; // will clone TrackingEntry at 'i'
          _table[i].ref = nullptr;    // will nullify the original ref
          _table[i].call_trace_id = 0;
        }
        _table[target].age += epoch_diff;

        if (_gc_generations.load(std::memory_order_relaxed) && is_epoch_owner) {
          // Per-klass population tracking (design doc's Open Question 3) -
          // gated on _gc_generations so this new cost is paid only when the
          // caller actually asked for generation/survival-shaped data
          // (arguments.cpp:223-227,244), not for every liveness-tracking
          // session. Gated on is_epoch_owner (not !forced) so a forced
          // (table-overflow) sweep still contributes one population sample
          // per genuinely new GC epoch instead of silently dropping it.
          u32 klass_id = 0;
          if (allow_resolve) {
            // GetObjectClass + Class.getName() + StringDictionary lookup per
            // surviving entry, previously paid only at JFR-flush time (see
            // flush_table() below). Only affordable off the allocation-hot
            // path - flush_table()/stop()'s cadence and
            // LivenessTracker::maybeForceCleanup()'s background-thread tick
            // both pass allow_resolve=true; track()'s hot-path forced sweep
            // does not (see cleanup_table()'s own header comment).
            jobject ref = env->NewLocalRef(_table[target].ref);
            if (ref != nullptr) {
              klass_id = resolveKlassId(env, ref);
              if (klass_id != 0) {
                // Cache the resolution: flush_table() runs its own
                // GetObjectClass+Class.getName()+lookupClass() sequence for
                // every surviving entry immediately after cleanup_table()
                // returns (flush_table() always calls cleanup_table() first),
                // which would otherwise repeat this exact JNI round-trip for
                // the same object. An object's class is immutable, so this
                // value stays valid for flush_table()'s read below, and for
                // a later non-resolving sweep's read right below.
                _table[target].cached_klass_id = klass_id;
              }
              env->DeleteLocalRef(ref);
            }
          } else {
            // track()'s table-overflow branch calls cleanup_table(true,
            // false) synchronously from the allocation-sampling call stack
            // (JVMTI SampledObjectAlloc callback). resolveKlassId() calls
            // Class.getName(), a genuine Java-bytecode upcall (unlike the
            // plain native jvmti->GetClassSignature() call
            // ObjectSampler::recordAllocation already makes on this same
            // callback stack) - too costly, and too re-entrancy-prone via
            // the String allocation it can trigger, to run from there. Reuse
            // whatever class id an earlier resolving sweep already resolved
            // for this entry instead; if it was never resolved, this entry's
            // sample for this epoch is dropped rather than resolving now.
            klass_id = _table[target].cached_klass_id;
          }
          if (klass_id != 0) {
            accumulateKlassCount(klass_id, _table[target].age, _table[target].ref,
                                 _table[target].tid);
          }
        }
      } else {
        jweak tmpRef = _table[i].ref;
        _table[i].ref = nullptr;
        env->DeleteWeakGlobalRef(tmpRef);
        _table[i].call_trace_id = 0;
        if (_table[i].leak_tag != 0) {
          releaseLeakTag(_table[i].leak_tag);
          _table[i].leak_tag = 0;
        }
      }
    }

    _table_size = newsz;

    TEST_LOG("LivenessTracker::cleanup_table survivors=%u klass_count_scratch_size=%d",
             newsz, _klass_count_scratch_size);
    if (_gc_generations.load(std::memory_order_relaxed) && is_epoch_owner &&
        _klass_count_scratch_size > 0) {
      foldKlassCountsLocked(env, target_gc_epoch, allow_resolve);
    }

    end = OS::nanotime();
    Log::debug("Liveness tracker cleanup took %.2fms (%.2fus/element)",
               1.0f * (end - start) / 1000 / 1000,
               1.0f * (end - start) / 1000 / sz);
  }
  _table_lock.unlock();
}

u32 LivenessTracker::resolveKlassId(JNIEnv *env, jobject ref) {
  // Deliberately NOT flush_table()'s own Class.getName()-based resolution
  // below: the ids this returns are the CANDIDATE klass ids that
  // ReferenceChainTracker matches discovered instances' classes against, and
  // RCT resolves those with the GetClassSignature +
  // ObjectSampler::normalizeClassSignature() + lookupClass() sequence
  // (resolveClassMap(), referenceChains.cpp). StringDictionary keys its
  // entries by the exact string, and getName()'s "com.foo.Bar" (dot
  // notation) is a DIFFERENT key from the signature's "com/foo/Bar" (slash
  // notation) - so a getName()-based id can never equal the signature-based
  // id the same class resolves to on the RCT side, and every candidate vs
  // discovered-instance comparison failed (observed live on the pod: every
  // auto-mark "resolved but no candidate match", and locally:
  // LivenessTracker id 63 vs ReferenceChainTracker id 2 for the same class;
  // only array classes accidentally matched, since "[B" is notation-
  // identical). Same sequence as ObjectSampler::recordAllocation()
  // therefore - the third user of it, after recordAllocation() and
  // resolveClassMap(). Also strictly cheaper than the old getName() path:
  // a plain JVMTI call instead of a Class.getName() JNI upcall that could
  // allocate.
  jclass clz = env->GetObjectClass(ref);
  u32 id = 0;
  jvmtiEnv *jvmti = VM::jvmti();
  if (clz != nullptr && jvmti != nullptr) {
    char *class_name = nullptr;
    if (jvmti->GetClassSignature(clz, &class_name, nullptr) ==
            JVMTI_ERROR_NONE &&
        class_name != nullptr) {
      const char *name_slice = nullptr;
      size_t name_len = 0;
      if (ObjectSampler::normalizeClassSignature(class_name, &name_slice,
                                                  &name_len)) {
        int lookup_id = Profiler::instance()->lookupClass(name_slice, name_len);
        if (lookup_id > 0) {
          id = (u32)lookup_id;
        }
      }
      jvmti->Deallocate((unsigned char *)class_name);
    }
  }
  if (clz != nullptr) {
    env->DeleteLocalRef(clz);
  }
  return id;
}

// Inserts (sample_source, age) into scratch.oldest[], sorted by age
// descending, capped at MAX_OLDEST_SAMPLES. Called from accumulateKlassCount()
// to bias representative selection toward long-lived instances.
void LivenessTracker::insertOldestSample(KlassCountScratch &scratch,
                                          jweak sample_source, u32 age,
                                          jint tid) {
  int pos = scratch.oldest_count;
  for (int i = 0; i < scratch.oldest_count; i++) {
    if (age > scratch.oldest[i].age) {
      pos = i;
      break;
    }
  }
  if (pos < KlassCountScratch::MAX_OLDEST_SAMPLES) {
    if (scratch.oldest_count < KlassCountScratch::MAX_OLDEST_SAMPLES) {
      scratch.oldest_count++;
    }
    for (int i = scratch.oldest_count - 1; i > pos; i--) {
      scratch.oldest[i] = scratch.oldest[i - 1];
    }
    scratch.oldest[pos].ref = sample_source;
    scratch.oldest[pos].age = age;
    scratch.oldest[pos].tid = tid;
  }
}

jlong LivenessTracker::acquireLeakTag(u64 call_trace_id, jint tid) {
  if (_leak_tag_free_count <= 0) {
    return 0; // pool exhausted
  }
  int idx = _leak_tag_free_list[--_leak_tag_free_count];
  _leak_tag_info[idx].call_trace_id = call_trace_id;
  _leak_tag_info[idx].tid = tid;
  return LEAK_TAG_BASE + idx;
}

void LivenessTracker::releaseLeakTag(jlong tag) {
  if (tag < LEAK_TAG_BASE || tag >= LEAK_TAG_BASE + LEAK_TAG_POOL_SIZE) {
    return;
  }
  int idx = (int)(tag - LEAK_TAG_BASE);
  _leak_tag_info[idx].call_trace_id = 0;
  _leak_tag_info[idx].tid = 0;
  _leak_tag_free_list[_leak_tag_free_count++] = idx;
}

bool LivenessTracker::getLeakTagInfo(jlong tag, u64 *out_call_trace_id,
                                     jint *out_tid) const {
  if (tag < LEAK_TAG_BASE || tag >= LEAK_TAG_BASE + LEAK_TAG_POOL_SIZE) {
    return false;
  }
  int idx = (int)(tag - LEAK_TAG_BASE);
  if (idx >= _leak_tag_free_count &&
      _leak_tag_info[idx].call_trace_id == 0) {
    return false; // tag is in free list
  }
  // Check if tag is still in use (not in free list)
  // Simple check: if call_trace_id is 0 and tid is 0, it's been released
  if (_leak_tag_info[idx].call_trace_id == 0 && _leak_tag_info[idx].tid == 0) {
    return false;
  }
  *out_call_trace_id = _leak_tag_info[idx].call_trace_id;
  *out_tid = _leak_tag_info[idx].tid;
  return true;
}

int LivenessTracker::tagLeakInstances(jvmtiEnv *jvmti, const u32 *klass_ids,
                                       int klass_count) {
  if (!_enabled || _table == nullptr) {
    return 0;
  }
  JNIEnv *env = VM::jni();
  int tagged = 0;
  // Tagging priority: instances from allocation sites (tids) with the
  // clearest surviving-age diversity go first, then oldest within a tid.
  // A continuously-leaking site keeps instances alive across many distinct
  // GC generations (many distinct surviving ages), while a one-time burst
  // or noise site survives at few distinct ages regardless of how old its
  // oldest instance is. If the pool is contended or GC churn races the
  // tagging, this ordering makes sure the strongest leak signal keeps the
  // tags rather than whichever entry the table scan happens to reach first.
  struct TagCandidate {
    u32 table_idx;
    jint tid;
    u32 age;
    int distinct_ages; // age diversity of this entry's tid (computed below)
    bool leak_tag_recorded; // record already holds a pool tag (reused below)
  };
  // Stack scratch: matching entries are bounded by the tracking table's
  // small live population (~hundreds); tag in scan order beyond capacity.
  TagCandidate scratch[512];
  int n_candidates = 0;
  _table_lock.lockShared();
  u32 sz = _table_size;
  for (u32 i = 0; i < sz; i++) {
    if (_table[i].ref == nullptr) {
      continue;
    }
    // Check if this entry's class matches any candidate
    u32 kid = _table[i].cached_klass_id;
    if (kid == 0) {
      continue;
    }
    bool match = false;
    for (int k = 0; k < klass_count; k++) {
      if (klass_ids[k] == kid) {
        match = true;
        break;
      }
    }
    if (!match) {
      continue;
    }
    // Entries whose record already holds a pool tag are still collected:
    // their tag survives the JVMTI tag only until the object is admitted
    // or the search restarts, and the state machine below must re-act on
    // the CURRENT JVMTI tag (re-establish, correlate, or leave alone).
    if (n_candidates < (int)(sizeof(scratch) / sizeof(scratch[0]))) {
      scratch[n_candidates].table_idx = i;
      scratch[n_candidates].tid = _table[i].tid;
      scratch[n_candidates].age = _table[i].age;
      scratch[n_candidates].distinct_ages = 0;
      scratch[n_candidates].leak_tag_recorded = _table[i].leak_tag != 0;
      n_candidates++;
    }
  }
  // Compute per-tid distinct surviving ages (matching entries only - the
  // same diversity signal the epoch fold uses for clustering, computed here
  // directly from the tracked entries so the ranking reflects exactly the
  // population being tagged). Distinct-tid count is bounded by
  // MAX_THREADS_PER_KLASS logic elsewhere but here just use a small array;
  // beyond 32 tids, extras share the lowest priority tier.
  struct TidAges {
    jint tid;
    u32 ages[32];
    int age_count;
  } tid_ages[32];
  int tid_count = 0;
  for (int c = 0; c < n_candidates; c++) {
    TidAges *t = nullptr;
    for (int ti = 0; ti < tid_count; ti++) {
      if (tid_ages[ti].tid == scratch[c].tid) {
        t = &tid_ages[ti];
        break;
      }
    }
    if (t == nullptr && tid_count < (int)(sizeof(tid_ages) / sizeof(tid_ages[0]))) {
      t = &tid_ages[tid_count++];
      t->tid = scratch[c].tid;
      t->age_count = 0;
    }
    if (t != nullptr) {
      bool seen = false;
      for (int a = 0; a < t->age_count; a++) {
        if (t->ages[a] == scratch[c].age) {
          seen = true;
          break;
        }
      }
      if (!seen && t->age_count < (int)(sizeof(t->ages) / sizeof(t->ages[0]))) {
        t->ages[t->age_count++] = scratch[c].age;
      }
    }
  }
  for (int c = 0; c < n_candidates; c++) {
    for (int ti = 0; ti < tid_count; ti++) {
      if (tid_ages[ti].tid == scratch[c].tid) {
        scratch[c].distinct_ages = tid_ages[ti].age_count;
        break;
      }
    }
  }
  // Sort: entries whose record already holds a pool tag first (they cost
  // no pool resources - their work below is correlate-or-re-establish, not
  // acquire), then highest age diversity, then oldest age. Small n,
  // insertion sort is fine (n <= 512 but in practice tens).
  for (int c = 1; c < n_candidates; c++) {
    TagCandidate key = scratch[c];
    int j = c - 1;
    while (j >= 0 &&
           ((!scratch[j].leak_tag_recorded && key.leak_tag_recorded) ||
            (scratch[j].leak_tag_recorded == key.leak_tag_recorded &&
             (scratch[j].distinct_ages < key.distinct_ages ||
              (scratch[j].distinct_ages == key.distinct_ages &&
               scratch[j].age < key.age))))) {
      scratch[j + 1] = scratch[j];
      j--;
    }
    scratch[j + 1] = key;
  }
  // Per-candidate state machine on the object's CURRENT JVMTI tag. The
  // tag on the object is shared state with ReferenceChainTracker's BFS
  // (frontier tags) and must never be blindly overwritten: an object
  // admitted by the BFS carries its FRONTIER tag on the object, and a
  // SetTag(leak_tag) here would orphan that frontier entry (the BFS could
  // never resolve it again) while making correlation depend on a parent
  // re-walk ever happening. Instead:
  //   - leak tag on object: already waiting for interception - just make
  //     sure the record knows it;
  //   - frontier tag on object: already admitted - correlate the entry
  //     (ReferenceChainTracker stores the leak tag ON the entry and marks
  //     the instance discovered), never retag;
  //   - no tag: plain SetTag (first tagging, or re-establishing after a
  //     search restart wiped all tags via releaseSearchTags()).
  for (int c = 0; c < n_candidates; c++) {
    u32 i = scratch[c].table_idx;
    jobject ref = env->NewLocalRef(_table[i].ref);
    if (ref == nullptr) {
      // Object was collected between the null check and now - its record's
      // tag (if any) is released by the GC cleanup path, nothing to do.
      continue;
    }
    jlong existing = 0;
    jvmtiError tag_err = jvmti->GetTag(ref, &existing);
    jlong leak_tag = 0;
    bool need_set = false;
    if (tag_err == JVMTI_ERROR_NONE && existing >= LEAK_TAG_BASE) {
      // Already carries a leak tag (ours, or one adopted below) - waiting
      // for the BFS interception. Make sure the record remembers it.
      leak_tag = _table[i].leak_tag != 0 ? _table[i].leak_tag : existing;
    } else if (tag_err == JVMTI_ERROR_NONE && existing > 0) {
      // Frontier tag: the BFS already admitted this object. Correlate the
      // existing entry rather than retagging - see the block comment above.
      leak_tag = _table[i].leak_tag;
      if (leak_tag == 0) {
        leak_tag = acquireLeakTag(_table[i].call_trace_id, _table[i].tid);
        if (leak_tag == 0) {
          env->DeleteLocalRef(ref);
          continue; // pool exhausted - other candidates may still correlate
        }
      }
      if (!ReferenceChainTracker::instance()->correlateAdmittedLeakTag(
              existing, leak_tag, _table[i].cached_klass_id)) {
        // Not a live frontier tag after all (search just restarted) -
        // fall back to plain tagging.
        need_set = true;
      }
    } else {
      // No tag: first tagging, or re-establishment after a restart wiped
      // all tags (releaseSearchTags() clears every JVMTI tag while the
      // record keeps its pool tag - reusing it keeps pool accounting
      // stable across restarts).
      leak_tag = _table[i].leak_tag;
      if (leak_tag == 0) {
        leak_tag = acquireLeakTag(_table[i].call_trace_id, _table[i].tid);
        if (leak_tag == 0) {
          env->DeleteLocalRef(ref);
          break; // pool exhausted
        }
      }
      need_set = true;
    }
    if (need_set) {
      jvmti->SetTag(ref, leak_tag);
    }
    _table[i].leak_tag = leak_tag;
    tagged++;
    // TEMP DIAGNOSTIC: which instances won the tagging priority - the
    // allocation size distinguishes a scenario's deliberately-big leaked
    // chunks from JVM-machinery survivors of the same class (observed:
    // tagged=5 stable across every poll with ZERO interceptions, because
    // the age-priority kept re-selecting old machinery byte[]s while the
    // young leak chunks churned out of the tracking table first).
    TEST_LOG("LivenessTracker::tagLeakInstances tagged leak_tag=%llu "
             "klass_id=%u tid=%d age=%lld size=%llu need_set=%d",
             (unsigned long long)leak_tag, _table[i].cached_klass_id,
             (int)_table[i].tid, (long long)_table[i].age,
             (unsigned long long)(_table[i].alloc._size), (int)need_set);
    env->DeleteLocalRef(ref);
  }
  _table_lock.unlockShared();
  return tagged;
}

void LivenessTracker::insertThreadGen(KlassCountScratch &scratch,
                                      jint tid, u32 age) {
  // Find or create the thread entry for this tid
  for (int i = 0; i < scratch.thread_count; i++) {
    if (scratch.threads[i].tid == tid) {
      // Insert age into the thread's sorted distinct-age array
      auto &t = scratch.threads[i];
      for (u32 j = 0; j < t.age_count; j++) {
        if (t.ages[j] == age) {
          return; // age already counted for this thread
        }
      }
      if (t.age_count < KlassCountScratch::MAX_AGES_PER_THREAD) {
        // Insert sorted (small array, linear scan + shift)
        u32 pos = t.age_count;
        for (u32 j = 0; j < t.age_count; j++) {
          if (age < t.ages[j]) {
            pos = j;
            break;
          }
        }
        for (u32 j = t.age_count; j > pos; j--) {
          t.ages[j] = t.ages[j - 1];
        }
        t.ages[pos] = age;
        t.age_count++;
      }
      return;
    }
  }
  if (scratch.thread_count < KlassCountScratch::MAX_THREADS_PER_KLASS) {
    int idx = scratch.thread_count++;
    scratch.threads[idx].tid = tid;
    scratch.threads[idx].ages[0] = age;
    scratch.threads[idx].age_count = 1;
  }
  // else: thread table full — additional threads are not tracked, but
  // the oldest[] array still captures instances from all threads.
}

void LivenessTracker::accumulateKlassCount(u32 klass_id, jlong age,
                                           jweak sample_source,
                                           jint tid) {
  // Count distinct GC ages (generations) per klass: group surviving
  // tracked objects by klass, then for each klass count the
  // number of unique age values. This is the "generation
  // count" — if new instances keep arriving while old ones
  // survive, the number of distinct ages grows.
  for (int i = 0; i < _klass_count_scratch_size; i++) {
    if (_klass_count_scratch[i].klass_id == klass_id) {
      auto &entry = _klass_count_scratch[i];
      // Per-class age dedup: only count each age once for the klass'
      // generation count. But per-site tracking and oldest[] must see
      // EVERY surviving object, not just the first per age — so those
      // run unconditionally below, outside this dedup check.
      bool age_seen = false;
      for (u32 a : entry.ages) {
        if (a == (u32)age) {
          age_seen = true;
          break;
        }
      }
      if (!age_seen) {
        entry.ages.push_back((u32)age);
      }
      // Track top-N oldest instances (Lindy bias): insert this sample
      // into the oldest[] array, sorted by age descending, capped at
      // MAX_OLDEST_SAMPLES. Runs for every object, not just new ages.
      insertOldestSample(entry, sample_source, (u32)age, tid);
      // Track per-thread distinct surviving generations (Cork/Swat
      // heuristic): add this object's age to its thread's age set.
      // Runs for every object — the thread's generation cardinality is
      // the leak signal, and it must see all surviving objects to be
      // accurate.
      insertThreadGen(entry, tid, (u32)age);
      return;
    }
  }
  if (_klass_count_scratch_size < MAX_KLASS_POPULATION_ENTRIES) {
    KlassCountScratch &slot = _klass_count_scratch[_klass_count_scratch_size++];
    slot.klass_id = klass_id;
    slot.ages.clear();
    slot.ages.push_back((u32)age);
    slot.oldest_count = 0;
    slot.thread_count = 0;
    insertOldestSample(slot, sample_source, (u32)age, tid);
    insertThreadGen(slot, tid, (u32)age);
  }
  // else: this epoch's scratch snapshot already holds
  // MAX_KLASS_POPULATION_ENTRIES distinct surviving klasses - klass_id's
  // count for this epoch is dropped rather than growing the scratch array,
  // the same best-effort tradeoff _klass_population's own fixed capacity
  // already accepts.
}

jweak LivenessTracker::recordKlassPopulationSampleLocked(
    u32 klass_id, u32 count, u64 epoch, int *out_slot, bool *out_created,
    jweak *out_evicted, int *out_evicted_count, int max_evicted) {
  // Linear scan is fine: MAX_KLASS_POPULATION_ENTRIES is small enough that a
  // full scan is cheap, the same shape NativeSocketSampler's fd LRU
  // (nativeSocketSampler.h:141-142) and this class's own cleanup_table()
  // pass already accept for bounded tables.
  int slot = -1;
  int evict_slot = -1;
  for (int i = 0; i < _klass_population_size; i++) {
    if (_klass_population[i].klass_id == klass_id) {
      slot = i;
      break;
    }
    if (evict_slot < 0 ||
        _klass_population[i].last_updated_epoch <
            _klass_population[evict_slot].last_updated_epoch) {
      evict_slot = i;
    }
  }

  jweak evicted_ref = nullptr;
  bool created = false;
  if (slot < 0) {
    created = true;
    if (_klass_population_size < MAX_KLASS_POPULATION_ENTRIES) {
      slot = _klass_population_size++;
    } else {
      // Table full - evict the least-recently-updated entry (evict_slot is
      // guaranteed set here since MAX_KLASS_POPULATION_ENTRIES > 0 implies
      // at least one iteration of the loop above ran).
      slot = evict_slot;
      // Return evicted representatives to caller for DeleteWeakGlobalRef.
      // recordKlassPopulationSampleLocked has no JNIEnv*, so it cannot
      // delete them itself. The caller (foldKlassCountsLocked) has env.
      // At most MAX_REPRESENTATIVES_PER_KLASS refs to return.
      if (out_evicted != nullptr) {
        for (int r = 0; r < _klass_population[slot].representative_count &&
                *out_evicted_count < max_evicted; r++) {
          out_evicted[(*out_evicted_count)++] =
              _klass_population[slot].representatives[r];
        }
      }
    }
    _klass_population[slot].klass_id = klass_id;
    _klass_population[slot].representative_count = 0;
    memset(_klass_population[slot].representatives, 0, sizeof(_klass_population[slot].representatives));
    memset(_klass_population[slot].rep_tids, 0, sizeof(_klass_population[slot].rep_tids));
    _klass_population[slot].ring_head = 0;
    _klass_population[slot].ring_fill = 0;
    _klass_population[slot].consecutive_positive = 0;
    _klass_population[slot].cached_slope = 0.0;
    // A reused (evicted) slot's PREVIOUS class's stable tag must not leak
    // onto the new one - see KlassPopulationEntry::stable_class_tag's own
    // comment. Minted lazily in foldKlassCountsLocked() once a live
    // instance is available to resolve the class from.
    _klass_population[slot].stable_class_tag = 0;
  }

  KlassPopulationEntry &entry = _klass_population[slot];
  entry.count_ring[entry.ring_head] = count;
  entry.ring_head = (u8)((entry.ring_head + 1) % KLASS_POPULATION_RING_SIZE);
  if (entry.ring_fill < KLASS_POPULATION_RING_SIZE) {
    entry.ring_fill++;
  }
  entry.last_updated_epoch = epoch;

  // Updated here (not in selectLeakCandidates()) so both the production path
  // (foldKlassCountsLocked(), once per genuine GC epoch) and the
  // klassPopulationRecordForTest() test seam - which calls this method
  // directly - keep consecutive_positive in sync with the ring they just
  // pushed, rather than requiring every caller to remember to do it (see
  // this class's own header comment on hasQualifyingGrowth()).
  if (hasQualifyingGrowth(entry)) {
    if (entry.consecutive_positive < UINT8_MAX) {
      entry.consecutive_positive++;
    }
  } else {
    entry.consecutive_positive = 0;
  }

  *out_slot = slot;
  *out_created = created;
  return evicted_ref;
}

void LivenessTracker::mintStableClassTagIfNeeded(JNIEnv *env, int slot,
                                                  jobject instance) {
  if (slot < 0 || slot >= _klass_population_size || instance == nullptr ||
      _klass_population[slot].stable_class_tag != 0) {
    return;
  }
  jvmtiEnv *jvmti = VM::jvmti();
  jclass klass = env->GetObjectClass(instance);
  if (jvmti != nullptr && klass != nullptr) {
    jlong tag = 0;
    if (jvmti->GetTag(klass, &tag) == JVMTI_ERROR_NONE) {
      if (tag == 0) {
        tag = ClassTagAllocator::next();
        jvmti->SetTag(klass, tag);
      }
      _klass_population[slot].stable_class_tag = tag;
    }
  }
  if (klass != nullptr) {
    env->DeleteLocalRef(klass);
  }
}

void LivenessTracker::foldKlassCountsLocked(JNIEnv *env, u64 epoch,
                                             bool allow_resolve) {
  TEST_LOG("LivenessTracker::foldKlassCountsLocked epoch=%llu scratch_size=%d",
           (unsigned long long)epoch, _klass_count_scratch_size);
  for (int i = 0; i < _klass_count_scratch_size; i++) {
    KlassCountScratch &s = _klass_count_scratch[i];
    TEST_LOG("LivenessTracker::foldKlassCountsLocked scratch[%d] klass_id=%u gen_count=%zu "
             "thread_count=%d oldest_count=%d",
             i, s.klass_id, s.ages.size(), s.thread_count, s.oldest_count);
    for (int ti = 0; ti < s.thread_count; ti++) {
      TEST_LOG("  thread[%d] tid=%d age_count=%u", ti, (int)s.threads[ti].tid,
               s.threads[ti].age_count);
    }
    int slot;
    bool created;
    jweak evicted[KlassPopulationEntry::MAX_REPRESENTATIVES_PER_KLASS];
    int evicted_count = 0;
    recordKlassPopulationSampleLocked(s.klass_id, (u32)s.ages.size(),
                                       epoch, &slot, &created,
                                       evicted, &evicted_count,
                                       KlassPopulationEntry::MAX_REPRESENTATIVES_PER_KLASS);
    for (int r = 0; r < evicted_count; r++) {
      if (evicted[r] != nullptr) {
        env->DeleteWeakGlobalRef(evicted[r]);
      }
    }
    if (!allow_resolve) {
      // track()'s table-overflow branch calls cleanup_table(true, false)
      // synchronously from the JVMTI SampledObjectAlloc callback stack - the
      // same reason resolveKlassId() is skipped there (cleanup_table()'s own
      // comment above). The representative-minting NewLocalRef/
      // NewWeakGlobalRef/DeleteLocalRef churn below is no Java-bytecode
      // upcall, but it is still avoidable JNI work on that hot path; leaving
      // the representative unset here is safe because the retry condition
      // right below picks it up again on the next allow_resolve=true sweep.
      continue;
    }
    // Also retry minting when an existing entry's representatives are
    // stale: either the count is zero, or all stored jweaks refer to
    // collected objects. A jweak's pointer value never becomes nullptr
    // just because its referent was collected, so we must probe each one.
    // Resolving here every epoch bounds any given gap to "one epoch with
    // no representative", not permanent.
    //
    // Mint up to MAX_REPRESENTATIVES_PER_KLASS representatives from the
    // oldest surviving instances (Lindy bias: oldest = most likely to be
    // leaks). Fresh independent jweaks are minted rather than reusing
    // s.oldest[].ref directly — those are TrackingEntry jweaks that get
    // deleted when cleanup_table() reaps the original entry.
    bool need_mint = created ||
        _klass_population[slot].representative_count == 0;
    if (!need_mint) {
      // Check if all representatives are stale
      bool any_live = false;
      for (int r = 0; r < _klass_population[slot].representative_count; r++) {
        jweak rep = _klass_population[slot].representatives[r];
        if (rep != nullptr) {
          jobject probe = env->NewLocalRef(rep);
          if (probe != nullptr) {
            any_live = true;
            env->DeleteLocalRef(probe);
            break;
          }
          env->DeleteLocalRef(probe);
        }
      }
      need_mint = !any_live;
    }
    // Compute the dominant allocating thread (highest generation
    // cardinality — most distinct surviving GC ages). This reuses
    // the same generation-count signal that selectLeakCandidates()
    // uses per-class, applied at per-thread granularity within a
    // class. A thread with 12 distinct surviving ages (continuous
    // leak) outscores a thread with 1 age (one-time burst),
    // regardless of raw instance count or size (Cork/Swat
    // heuristic). Thread ID is used instead of call_trace_id because
    // lambdas fragment call_trace_id — synthetic methods produce
    // slightly different stack hashes for what is logically one
    // allocation site.
    jint dominant_tid = 0;
    u32 dominant_gens = 0;
    for (int ti = 0; ti < s.thread_count; ti++) {
      if (s.threads[ti].age_count > dominant_gens) {
        dominant_gens = s.threads[ti].age_count;
        dominant_tid = s.threads[ti].tid;
      }
    }
    // Re-mint if the dominant thread has >1 generation AND none of
    // the current reps were minted from it. This handles the startup-
    // cache problem: reps minted from noise threads during startup
    // stay live even after the real leak thread becomes dominant,
    // blocking re-selection because need_mint=false. By checking
    // whether reps match the dominant thread, we replace stale reps
    // with instances from the actual leak thread.
    if (!need_mint && dominant_gens > 1) {
      bool rep_matches_dominant = false;
      for (int r = 0; r < _klass_population[slot].representative_count; r++) {
        if (_klass_population[slot].rep_tids[r] == dominant_tid) {
          rep_matches_dominant = true;
          break;
        }
      }
      if (!rep_matches_dominant) {
        need_mint = true;
        TEST_LOG("LivenessTracker::foldKlassCountsLocked re-minting klass_id=%u: "
                 "dominant_tid=%d dominant_gens=%u but no rep matches",
                 s.klass_id, (int)dominant_tid, dominant_gens);
      }
    }
    if (need_mint) {
      // Clean up old representatives
      for (int r = 0; r < _klass_population[slot].representative_count; r++) {
        if (_klass_population[slot].representatives[r] != nullptr) {
          env->DeleteWeakGlobalRef(_klass_population[slot].representatives[r]);
          _klass_population[slot].representatives[r] = nullptr;
        }
        _klass_population[slot].rep_tids[r] = 0;
      }
      _klass_population[slot].representative_count = 0;
      // Mint fresh representatives, preferring instances from the
      // dominant allocating thread. If the dominant thread has fewer
      // than MAX_REPRESENTATIVES_PER_KLASS instances in oldest[], fill
      // the remaining slots with other oldest instances.
      bool minted_any = false;
      int minted = 0;
      // First pass: instances from the dominant thread (only if it has
      // >1 distinct generation — otherwise all threads are equally
      // uninteresting and pure oldest-first is fine)
      if (dominant_gens > 1) {
        for (int r = 0; r < s.oldest_count &&
                minted < KlassPopulationEntry::MAX_REPRESENTATIVES_PER_KLASS; r++) {
          if (s.oldest[r].tid != dominant_tid) continue;
          jobject strong = env->NewLocalRef(s.oldest[r].ref);
          if (strong != nullptr) {
            jweak rep = env->NewWeakGlobalRef(strong);
            int idx = _klass_population[slot].representative_count++;
            _klass_population[slot].representatives[idx] = rep;
            _klass_population[slot].rep_tids[idx] = dominant_tid;
            if (!minted_any) {
              mintStableClassTagIfNeeded(env, slot, strong);
              minted_any = true;
            }
            env->DeleteLocalRef(strong);
            minted++;
          }
        }
      }
      // Second pass: fill remaining slots with other oldest instances
      for (int r = 0; r < s.oldest_count &&
              minted < KlassPopulationEntry::MAX_REPRESENTATIVES_PER_KLASS; r++) {
        if (dominant_gens > 1 && s.oldest[r].tid == dominant_tid) continue;
        jobject strong = env->NewLocalRef(s.oldest[r].ref);
        if (strong != nullptr) {
          jweak rep = env->NewWeakGlobalRef(strong);
          int idx = _klass_population[slot].representative_count++;
          _klass_population[slot].representatives[idx] = rep;
          _klass_population[slot].rep_tids[idx] = s.oldest[r].tid;
          if (!minted_any) {
            mintStableClassTagIfNeeded(env, slot, strong);
            minted_any = true;
          }
          env->DeleteLocalRef(strong);
          minted++;
        }
      }
      // else: all surviving instances for this klass died before we
      // could mint a representative - left with representative_count=0
      // for this epoch, retried on the next one.
      TEST_LOG("LivenessTracker::foldKlassCountsLocked minted=%d for klass_id=%u "
               "dominant_tid=%d dominant_gens=%u",
               minted, s.klass_id, (int)dominant_tid, dominant_gens);
    }
  }
  _klass_count_scratch_size = 0;
}

bool LivenessTracker::hasQualifyingGrowth(const KlassPopulationEntry &entry) const {
  RingThirdsStats stats;
  if (!ringThirdsStats(
          entry.ring_head, entry.ring_fill, KLASS_POPULATION_RING_SIZE,
          KLASS_POPULATION_MIN_FILL_FOR_TREND,
          [&entry](int i) { return (double)entry.count_ring[i]; }, &stats)) {
    TEST_LOG("LivenessTracker::hasQualifyingGrowth klass_id=%u ring_fill=%u "
             "INSUFFICIENT_FILL (need %d)",
             entry.klass_id, entry.ring_fill,
             KLASS_POPULATION_MIN_FILL_FOR_TREND);
    return false;
  }

  // Cached for selectLeakCandidates()'s ranking (KlassPopulationEntry::
  // cached_slope's own comment, livenessTracker.h) - the ring only changes
  // on push, so this is the same value a later re-scan would compute.
  entry.cached_slope = stats.recent_mean - stats.earliest_mean;

  double growth_bar = LEAK_GROWTH_REL_MIN * stats.earliest_mean;
  if (growth_bar < LEAK_GROWTH_ABS_MIN) {
    growth_bar = LEAK_GROWTH_ABS_MIN;
  }
  if (entry.cached_slope < growth_bar) {
    TEST_LOG("LivenessTracker::hasQualifyingGrowth klass_id=%u "
             "SLOPE_TOO_SMALL slope=%f growth_bar=%f",
             entry.klass_id, entry.cached_slope, growth_bar);
    return false;
  }

  TEST_LOG("LivenessTracker::hasQualifyingGrowth klass_id=%u "
           "SLOPE_OK slope=%f growth_bar=%f",
           entry.klass_id, entry.cached_slope, growth_bar);
  return true;
}

void LivenessTracker::recordHeapFloorSample(u64 used, u64 timestamp_ns, u64 container_used) {
  TEST_LOG("LivenessTracker::recordHeapFloorSample called used=%llu disabled=%d",
           (unsigned long long)used,
           (int)_heap_floor_recording_disabled_for_test.load(std::memory_order_acquire));
#ifdef DEBUG
  if (_heap_floor_recording_disabled_for_test.load(std::memory_order_acquire)) {
    TEST_LOG("LivenessTracker::recordHeapFloorSample SKIPPED (disabled for test)");
    return;
  }
#endif
  recordHeapFloorSampleUnchecked(used, timestamp_ns, container_used);
}

void LivenessTracker::recordHeapFloorSampleUnchecked(u64 used, u64 timestamp_ns, u64 container_used) {
  TEST_LOG("LivenessTracker::recordHeapFloorSample used=%llu timestamp_ns=%llu container_used=%llu",
           (unsigned long long)used, (unsigned long long)timestamp_ns,
           (unsigned long long)container_used);
  // Lock-free, single-writer-at-a-time - see _heap_floor_ring's own comment
  // (livenessTracker.h) for why onGC() cannot take _table_lock here.
  //
  // Standard SPSC publish order: the payload is a plain store, and the index
  // that gates which slots are valid is what carries the release. A reader
  // that loadAcquire()s the index is then guaranteed to see this payload
  // write too, since it precedes the index's storeRelease() in program
  // order and a release store cannot be reordered before an earlier store.
  // (The previous version had this backwards - storeRelease() on the
  // payload with a plain store on the index - which does not establish any
  // ordering between "the index says this slot is valid" and "the payload
  // for that slot is visible".) _heap_floor_time_ring's and
  // _container_mem_ring's payload writes below are plain stores for the
  // same reason - they precede the same storeRelease() in program order.
  u8 head = load(_heap_floor_ring_head);
  store(_heap_floor_ring[head], used);
  store(_heap_floor_time_ring[head], timestamp_ns);
  store(_container_mem_ring[head], container_used);
  storeRelease(_heap_floor_ring_head, (u8)((head + 1) % KLASS_POPULATION_RING_SIZE));
  u8 fill = load(_heap_floor_ring_fill);
  if (fill < KLASS_POPULATION_RING_SIZE) {
    storeRelease(_heap_floor_ring_fill, (u8)(fill + 1));
  }
}

bool LivenessTracker::heapFloorRising() const {
  // Matches recordHeapFloorSample()'s storeRelease() on both index fields -
  // loadAcquire() here is what makes the payload writes below visible.
  u8 fill = loadAcquire(_heap_floor_ring_fill);
  u8 head = loadAcquire(_heap_floor_ring_head);
  RingThirdsStats stats;
  if (!ringThirdsStats(
          head, fill, KLASS_POPULATION_RING_SIZE,
          KLASS_POPULATION_MIN_FILL_FOR_TREND,
          [this](int i) { return (double)load(_heap_floor_ring[i]); },
          &stats)) {
    return false;
  }

  double growth_bar = HEAP_FLOOR_GROWTH_REL_MIN * stats.earliest_mean;
  if (growth_bar < (double)HEAP_FLOOR_GROWTH_ABS_MIN) {
    growth_bar = (double)HEAP_FLOOR_GROWTH_ABS_MIN;
  }
  bool mean_rising = (stats.recent_mean - stats.earliest_mean) >= growth_bar;
  if (!mean_rising) {
    TEST_LOG("LivenessTracker::heapFloorRising MEAN_NOT_RISING "
             "recent_mean=%.0f earliest_mean=%.0f growth_bar=%.0f",
             stats.recent_mean, stats.earliest_mean, growth_bar);
    return false;
  }

  double floor_bar = HEAP_FLOOR_FLOOR_REL_MIN * stats.earliest_min;
  if (floor_bar < (double)HEAP_FLOOR_FLOOR_ABS_MIN) {
    floor_bar = (double)HEAP_FLOOR_FLOOR_ABS_MIN;
  }
  bool floor_rising = (stats.recent_min - stats.earliest_min) >= floor_bar;
  TEST_LOG("LivenessTracker::heapFloorRising %s "
           "recent_mean=%.0f earliest_mean=%.0f recent_min=%.0f earliest_min=%.0f "
           "floor_bar=%.0f floor_rising=%d",
           floor_rising ? "FLOOR_RISING" : "FLOOR_NOT_RISING",
           stats.recent_mean, stats.earliest_mean,
           stats.recent_min, stats.earliest_min,
           floor_bar, (int)floor_rising);
  return floor_rising;
}

double LivenessTracker::secondsToOOM() const {
#ifdef DEBUG
  jlong max_heap = _max_heap_bytes_for_test.load(std::memory_order_acquire);
  if (max_heap <= 0) {
    max_heap = _max_heap_bytes;
  }
  jlong container_limit = _container_memory_limit_for_test.load(std::memory_order_acquire);
  if (container_limit <= 0) {
    container_limit = _container_memory_limit;
  }
#else
  jlong max_heap = _max_heap_bytes;
  jlong container_limit = _container_memory_limit;
#endif
  if (!_gc_generations.load(std::memory_order_relaxed) || max_heap <= 0) {
    TEST_LOG("LivenessTracker::secondsToOOM -> -1 (gc_generations=%d max_heap=%lld)",
             (int)_gc_generations.load(std::memory_order_relaxed), (long long)max_heap);
    return -1;
  }

  // Project against whichever of the JVM heap or the container memory
  // limit is tighter, rather than projecting both and comparing results -
  // an unavailable container limit (bare metal, macOS, cgroups disabled) is
  // treated as unbounded so it never wins this comparison. See this
  // method's own comment (livenessTracker.h) for why the two are
  // independent boundaries worth checking at all.
  jlong effective_container_limit =
      container_limit > 0 ? container_limit : std::numeric_limits<jlong>::max();
  bool use_container = effective_container_limit < max_heap;
  jlong limit = use_container ? container_limit : max_heap;

  u8 fill = loadAcquire(_heap_floor_ring_fill);
  u8 head = loadAcquire(_heap_floor_ring_head);
  TEST_LOG("LivenessTracker::secondsToOOM ring fill=%d head=%d source=%s limit=%lld",
           (int)fill, (int)head, use_container ? "container" : "heap", (long long)limit);

  RingThirdsStats byte_stats;
  bool have_byte_stats = use_container
      ? ringThirdsStats(
            head, fill, KLASS_POPULATION_RING_SIZE,
            KLASS_POPULATION_MIN_FILL_FOR_TREND,
            [this](int i) { return (double)load(_container_mem_ring[i]); },
            &byte_stats)
      : ringThirdsStats(
            head, fill, KLASS_POPULATION_RING_SIZE,
            KLASS_POPULATION_MIN_FILL_FOR_TREND,
            [this](int i) { return (double)load(_heap_floor_ring[i]); },
            &byte_stats);
  if (!have_byte_stats) {
    TEST_LOG("LivenessTracker::secondsToOOM -> -1 (INSUFFICIENT_FILL fill=%d need=%d)",
             (int)fill, KLASS_POPULATION_MIN_FILL_FOR_TREND);
    return -1;
  }
  RingThirdsStats time_stats;
  ringThirdsStats(
      head, fill, KLASS_POPULATION_RING_SIZE, KLASS_POPULATION_MIN_FILL_FOR_TREND,
      [this](int i) { return (double)load(_heap_floor_time_ring[i]); },
      &time_stats);

  double bytes_delta = byte_stats.recent_mean - byte_stats.earliest_mean;
  double time_delta_ns = time_stats.recent_mean - time_stats.earliest_mean;
  TEST_LOG("LivenessTracker::secondsToOOM bytes_delta=%.0f time_delta_ns=%.0f "
           "earliest_mean=%.0f recent_mean=%.0f earliest_min=%.0f recent_min=%.0f",
           bytes_delta, time_delta_ns,
           byte_stats.earliest_mean, byte_stats.recent_mean,
           byte_stats.earliest_min, byte_stats.recent_min);
  if (bytes_delta <= 0 || time_delta_ns <= 0) {
    TEST_LOG("LivenessTracker::secondsToOOM -> -1 (NOT_RISING bytes_delta=%.0f time_delta_ns=%.0f)",
             bytes_delta, time_delta_ns);
    return -1;
  }

  // Corroborate with a fit over just the most recent half of the window
  // (HEAP_FLOOR_RECENT_HALF_MIN_FILL's own comment) - a one-time step
  // change that has already plateaued still passes the full-window check
  // above for as long as any of its samples remain in the window, but its
  // own recent half is flat.
  int half_fill = fill / 2;
  RingThirdsStats recent_half_stats;
  bool have_recent_half = use_container
      ? ringThirdsStats(
            head, half_fill, KLASS_POPULATION_RING_SIZE,
            HEAP_FLOOR_RECENT_HALF_MIN_FILL,
            [this](int i) { return (double)load(_container_mem_ring[i]); },
            &recent_half_stats)
      : ringThirdsStats(
            head, half_fill, KLASS_POPULATION_RING_SIZE,
            HEAP_FLOOR_RECENT_HALF_MIN_FILL,
            [this](int i) { return (double)load(_heap_floor_ring[i]); },
            &recent_half_stats);
  double recent_half_delta =
      have_recent_half ? recent_half_stats.recent_mean - recent_half_stats.earliest_mean : 0;
  if (!have_recent_half || recent_half_delta <= 0) {
    TEST_LOG("LivenessTracker::secondsToOOM -> -1 (RECENT_HALF_FLAT "
             "half_fill=%d have_recent_half=%d recent_half_delta=%.0f)",
             half_fill, (int)have_recent_half, recent_half_delta);
    return -1;
  }

  double bytes_per_ns = bytes_delta / time_delta_ns;
  double remaining_bytes = (double)limit - byte_stats.recent_mean;
  if (remaining_bytes <= 0) {
    // The chosen ring's own recent mean has already reached (or passed) its
    // limit - exhaustion is not "in N seconds", it's now.
    return 0;
  }
  return (remaining_bytes / bytes_per_ns) / 1e9; // ns -> seconds
}

int LivenessTracker::selectLeakCandidates(KlassCandidate *out, int max) {
  int cap = max < MAX_LEAK_CANDIDATES ? max : MAX_LEAK_CANDIDATES;
  if (cap <= 0) {
    return 0;
  }

  // Kept sorted descending by slope magnitude, at most `cap` (<=
  // MAX_LEAK_CANDIDATES == 5) entries - not one per klass - so an
  // insertion-sort-style insert per candidate (O(cap) per insert, O(N*cap)
  // overall for N <= MAX_KLASS_POPULATION_ENTRIES == 256 klasses) is cheaper
  // and simpler than collecting every qualifying candidate and calling
  // std::sort.
  // A single call, shared by every candidate this scan considers - see
  // LEAK_TREND_HYSTERESIS_BASE/CORROBORATED's own comment (livenessTracker.h)
  // for why an aggregate, non-attributed signal can only raise or lower the
  // bar uniformly, never reorder candidates against each other. Lock-free
  // (heapFloorRising()'s own comment), so no relation to _table_lock below.
  const int required_hysteresis = heapFloorRising()
                                       ? LEAK_TREND_HYSTERESIS_CORROBORATED
                                       : LEAK_TREND_HYSTERESIS_BASE;

  double best_slopes[MAX_LEAK_CANDIDATES];
  int count = 0;

  // Read-only pass over _klass_population - mirrors getLiveTraceIds()'s own
  // shared-lock read pattern above, the same table cleanup_table() writes
  // under the exclusive lock this shared lock is taken against.
  _table_lock.lockShared();
  // Only log when there is actually something to scan - this runs on every
  // BFS-thread wake (once per second), so logging an empty scan turns the
  // steady, idle state into per-second noise.
  if (_klass_population_size > 0) {
    TEST_LOG("LivenessTracker::selectLeakCandidates scanning %d klass_population entries",
             _klass_population_size);
  }
  for (int i = 0; i < _klass_population_size; i++) {
    const KlassPopulationEntry &entry = _klass_population[i];
    // cached_slope was computed by hasQualifyingGrowth() the last time this
    // entry was pushed (recordKlassPopulationSampleLocked()) - the ring only
    // changes on push, so re-scanning it here would just recompute the same
    // value a moment later.
    bool has_trend = entry.ring_fill >= KLASS_POPULATION_MIN_FILL_FOR_TREND;
    double slope = entry.cached_slope;
    TEST_LOG("LivenessTracker::selectLeakCandidates entry[%d] klass_id=%u ring_fill=%u "
             "has_trend=%d slope=%f consecutive_positive=%u required=%d rep_count=%d",
             i, entry.klass_id, entry.ring_fill, has_trend, has_trend ? slope : 0.0,
             entry.consecutive_positive, required_hysteresis, entry.representative_count);
    if (!has_trend || slope <= 0 || entry.consecutive_positive < required_hysteresis) {
      // Not enough history yet, flat/shrinking, or hasn't shown a
      // qualifying rise (hasQualifyingGrowth()) for enough consecutive
      // epochs yet to trust it over sampling/oscillation noise.
      continue;
    }
    if (count == cap && slope <= best_slopes[cap - 1]) {
      // Already holding `cap` stronger (or equal) candidates - this one
      // doesn't make the cut.
      continue;
    }

    int pos = count < cap ? count++ : cap - 1;
    best_slopes[pos] = slope;
    out[pos] = KlassCandidate{entry.klass_id, entry.representative_count > 0 ? entry.representatives[0] : nullptr};
    while (pos > 0 && best_slopes[pos - 1] < best_slopes[pos]) {
      double tmp_slope = best_slopes[pos - 1];
      best_slopes[pos - 1] = best_slopes[pos];
      best_slopes[pos] = tmp_slope;
      KlassCandidate tmp_cand = out[pos - 1];
      out[pos - 1] = out[pos];
      out[pos] = tmp_cand;
      pos--;
    }
  }
  _table_lock.unlockShared();
  TEST_LOG("LivenessTracker::selectLeakCandidates returning %d candidates (required_hysteresis=%d, heapFloorRising=%d)",
           count, required_hysteresis,
           (int)heapFloorRising());
  return count;
}

int LivenessTracker::topKlassesByGenerationCount(u32 *out, int max) {
  int cap = max < MAX_LEAK_CANDIDATES ? max : MAX_LEAK_CANDIDATES;
  if (cap <= 0) {
    return 0;
  }

  // Same insertion-sort-style top-k selection as selectLeakCandidates()
  // above (small, fixed cap - cheaper than collecting everything and
  // sorting), ranked by most-recent count_ring sample instead of slope, and
  // with no hysteresis/trend gate at all - see this method's own header
  // comment (livenessTracker.h).
  u32 best_counts[MAX_LEAK_CANDIDATES];
  int count = 0;

  _table_lock.lockShared();
  for (int i = 0; i < _klass_population_size; i++) {
    const KlassPopulationEntry &entry = _klass_population[i];
    if (entry.ring_fill == 0 || entry.stable_class_tag == 0) {
      // Never sampled, or a live instance has not been resolved yet to mint
      // its stable_class_tag from (foldKlassCountsLocked()'s own comment) -
      // nothing usable to rank or return in either case.
      continue;
    }
    // ring_head is "next slot to write" (recordKlassPopulationSampleLocked(),
    // livenessTracker.cpp) - the most recently written slot is one behind it,
    // wrapping.
    u32 latest = entry.count_ring[(entry.ring_head + KLASS_POPULATION_RING_SIZE - 1) %
                                   KLASS_POPULATION_RING_SIZE];
    if (count == cap && latest <= best_counts[cap - 1]) {
      continue;
    }
    int pos = count < cap ? count++ : cap - 1;
    best_counts[pos] = latest;
    out[pos] = (u32)entry.stable_class_tag;
    while (pos > 0 && best_counts[pos - 1] < best_counts[pos]) {
      u32 tmp_count = best_counts[pos - 1];
      best_counts[pos - 1] = best_counts[pos];
      best_counts[pos] = tmp_count;
      u32 tmp_id = out[pos - 1];
      out[pos - 1] = out[pos];
      out[pos] = tmp_id;
      pos--;
    }
  }
  _table_lock.unlockShared();
  TEST_LOG("LivenessTracker::topKlassesByGenerationCount returning %d klass_ids", count);
  return count;
}

jobject LivenessTracker::resolveCandidateRepresentative(JNIEnv *env, u32 klass_id) {
  // Shared lock excludes cleanup_table()'s exclusive lock (the only writer,
  // and the only place that can DeleteWeakGlobalRef() an entry's
  // representatives via foldKlassCountsLocked()'s eviction path above) for
  // the whole lookup+resolve, so the value NewLocalRef() runs on here is
  // always the table's current one for klass_id, never a snapshot that
  // eviction could have invalidated in the meantime - see
  // selectLeakCandidates()'s own comment for the race this closes.
  //
  // Returns the first live representative (oldest first, per the Lindy
  // bias in KlassCountScratch::oldest[]). Callers that need all live
  // representatives (e.g. pollWatchedTargets() tagging all of them)
  // use resolveCandidateRepresentatives() instead.
  _table_lock.lockShared();
  jobject obj = nullptr;
  for (int i = 0; i < _klass_population_size; i++) {
    if (_klass_population[i].klass_id == klass_id) {
      for (int r = 0; r < _klass_population[i].representative_count; r++) {
        jweak rep = _klass_population[i].representatives[r];
        if (rep != nullptr) {
          obj = env->NewLocalRef(rep);
          if (obj != nullptr) {
            break;
          }
        }
      }
      break;
    }
  }
  _table_lock.unlockShared();
  return obj;
}

int LivenessTracker::resolveCandidateRepresentatives(
    JNIEnv *env, u32 klass_id, jobject *out, int max_out) {
  // Returns all live representatives for klass_id, oldest first.
  // Used by pollWatchedTargets() to tag all representatives with marker
  // tags so the canary mechanism has multiple chances to find a
  // long-lived instance. See KlassCountScratch::oldest's comment for
  // why multiple representatives matter.
  _table_lock.lockShared();
  int count = 0;
  for (int i = 0; i < _klass_population_size; i++) {
    if (_klass_population[i].klass_id == klass_id) {
      for (int r = 0; r < _klass_population[i].representative_count &&
              count < max_out; r++) {
        jweak rep = _klass_population[i].representatives[r];
        if (rep != nullptr) {
          jobject obj = env->NewLocalRef(rep);
          if (obj != nullptr) {
            out[count++] = obj;
          }
        }
      }
      break;
    }
  }
  _table_lock.unlockShared();
  return count;
}

void LivenessTracker::flush(std::set<int> &tracked_thread_ids) {
  if (!_enabled) {
    // disabled
    return;
  }
  flush_table(&tracked_thread_ids);
}

void LivenessTracker::flush_table(std::set<int> *tracked_thread_ids) {
  JNIEnv *env = VM::jni();
  u64 start = OS::nanotime(), end;

  // make sure that the tracking table is cleaned up before we start flushing it
  // this is to make sure we are including as few false 'live' objects as
  // possible
  cleanup_table();

  _table_lock.lock();

  u32 sz;
  for (u32 i = 0; i < (sz = _table_size); i++) {
    jobject ref = env->NewLocalRef(_table[i].ref);
    if (ref != nullptr) {
      if (tracked_thread_ids != nullptr) {
        tracked_thread_ids->insert(_table[i].tid);
      }
      ObjectLivenessEvent event;
      event._start_time = _table[i].time;
      event._age = _table[i].age;
      event._alloc = _table[i].alloc;
      event._skipped = _table[i].skipped;
      event._ctx = _table[i].ctx;
      event.leak_tag = _table[i].leak_tag;

      int class_id = 0;
      if (_table[i].cached_klass_id != 0) {
        // Already resolved by cleanup_table()'s survivor loop this epoch
        // (resolveKlassId(), only when _gc_generations is enabled) - reuse
        // it instead of repeating the GetObjectClass+Class.getName()+
        // lookupClass() JNI round-trip for the same object.
        class_id = _table[i].cached_klass_id;
      } else {
        jclass clz = env->GetObjectClass(ref);
        jstring name_str = (jstring)env->CallObjectMethod(clz, _Class_getName);
        env->DeleteLocalRef(clz);
        jniExceptionCheck(env);
        // name_str can be null if the call above threw and
        // jniExceptionCheck() cleared the pending exception rather than
        // propagating it - GetStringUTFChars()/ReleaseStringUTFChars()
        // require a non-null jstring (mirrors resolveKlassId()'s own guard).
        if (name_str != nullptr) {
          const char *name = env->GetStringUTFChars(name_str, nullptr);
          if (name != nullptr) {
            class_id = Profiler::instance()->lookupClass(name, strlen(name));
            env->ReleaseStringUTFChars(name_str, name);
          }
          env->DeleteLocalRef(name_str);
        }
      }

      // lookupClass() returns -1 when the class map is at capacity; do not
      // assign it to the u32 event id (it would wrap to 0xFFFFFFFF and
      // corrupt liveness attribution in the JFR output) — drop the sample
      // instead, matching ObjectSampler's convention for the same failure.
      if (class_id >= 0) {
        event._id = class_id;
        Profiler::instance()->recordDeferredSample(_table[i].tid, _table[i].call_trace_id, BCI_LIVENESS, &event);
      }
    }

    env->DeleteLocalRef(ref);
  }

  _table_lock.unlock();

  if (_record_heap_usage) {
    bool isLastGc;
    size_t used = resolvePostGcHeapUsage(&isLastGc);
    Profiler::instance()->writeHeapUsage(used, isLastGc);
  }

  end = OS::nanotime();
  if (sz) {
    Log::debug("Liveness tracker flush took %.2fms (%.2fus/element)",
               1.0f * (end - start) / 1000 / 1000,
               1.0f * (end - start) / 1000 / sz);
  }
}

Error LivenessTracker::initialize_table(JNIEnv *jni, int sampling_interval) {
  _table_max_cap = 0;
  jlong max_heap = HeapUsage::getMaxHeap(jni);
  if (max_heap == -1) {
    return Error("Can not track liveness for allocation samples without heap "
                 "size information.");
  }
  // Cached for secondsToOOM() - see _max_heap_bytes' own comment
  // (livenessTracker.h) for why this is resolved once here rather than
  // re-querying HeapUsage::getMaxHeap() on every projection.
  _max_heap_bytes = max_heap;
  // Cached the same way and for the same reason - see _container_memory_limit's
  // own comment (livenessTracker.h). -1 (unavailable) is a valid outcome
  // here, unlike max_heap above: not every JVM runs under a memory-limited
  // cgroup.
  _container_memory_limit = OS::getContainerMemoryLimit();

  int required_table_capacity =
      sampling_interval > 0 ? max_heap / sampling_interval : max_heap;

  if (required_table_capacity > MAX_TRACKING_TABLE_SIZE) {
    Log::warn("Tracking liveness for allocation samples with interval %d can "
              "not cover full heap.",
              sampling_interval);
  }
  _table_max_cap = std::min(MAX_TRACKING_TABLE_SIZE, required_table_capacity);

  _table_cap = std::max(
      2048,
      _table_max_cap /
          8); // the table will grow at most 3 times before fully covering heap

  return Error::OK;
}

Error LivenessTracker::start(Arguments &args) {
  Error err = initialize(args);
  if (err) {
    return err;
  }
  // Initialize leak tag free list
  for (int i = 0; i < LEAK_TAG_POOL_SIZE; i++) {
    _leak_tag_free_list[i] = i;
    _leak_tag_info[i].call_trace_id = 0;
    _leak_tag_info[i].tid = 0;
  }
  _leak_tag_free_count = LEAK_TAG_POOL_SIZE;
  if (!_enabled) {
    // disabled
    return Error::OK;
  }
  
  // Self-register with the profiler for liveness checking
  Profiler::instance()->registerLivenessChecker([this](CallTraceIdSet& buffer) {
    this->getLiveTraceIds(buffer);
  });
  
  // Enable Java Object Sample events
  jvmtiEnv *jvmti = VM::jvmti();
  jvmti->SetEventNotificationMode(
      JVMTI_ENABLE, JVMTI_EVENT_GARBAGE_COLLECTION_FINISH, nullptr);

  return Error::OK;
}

void LivenessTracker::stop() {
  if (!_enabled) {
    // disabled
    return;
  }
  cleanup_table();
  flush_table(nullptr);

  // do not disable GC notifications here - the tracker is supposed to survive
  // multiple recordings
}

Error LivenessTracker::initialize(Arguments &args) {
  _enabled = args._gc_generations || args._record_liveness;

  // Gates per-klass population tracking (see the _gc_generations member's
  // own comment in livenessTracker.h). Updated unconditionally alongside
  // _record_heap_usage below, ahead of the _initialized guard, for the same
  // reason: each profiler start should observe the flag it was actually
  // started with, even though the tracking table itself persists across
  // recordings.
  _gc_generations.store(args._gc_generations, std::memory_order_relaxed);

  if (!_enabled) {
    return Error::OK;
  }

  // _record_heap_usage controls per-session JFR event emission only, not the
  // tracking table. Update it before the _initialized guard so each profiler
  // start gets the correct setting even when the table persists across recordings.
  _record_heap_usage = args._record_heap_usage;

  if (_initialized) {
    // if the tracker was previously initialized return the stored result for
    // consistency this hack also means that if the profiler is started with
    // different arguments for liveness tracking those will be ignored it is
    // required in order to be able to track the object liveness across many
    // recordings
    return _stored_error;
  }
  _initialized = true;

  // Sync the class-map-generation baseline to what it already is by this
  // point, rather than leaving it at the constructor's 0 sentinel (see
  // _last_class_map_generation's own comment, livenessTracker.h). By the time
  // this runs, ObjectSampler::start() -> LivenessTracker::start() has already
  // happened strictly after Profiler::start()'s own _class_map.clearAll()
  // (referenceChains.cpp's own comment on this same ordering) - so
  // classMap()->generation() here already reflects this process's first
  // recording, not the pre-clearAll() baseline the 0 sentinel implies.
  // Without this, cleanup_table()'s class-map-reset branch always sees a
  // spurious mismatch (0 vs. whatever generation() has already reached) the
  // very first time it runs after ANY start() - regardless of how much
  // genuinely post-reset, still-valid population/leak-tracking history has
  // already accumulated in _klass_population by then - and wipes it all,
  // found the hard way via StaticFieldGrowingCollectionScenario silently
  // losing its seeded candidate the moment the first post-start GC finished.
  // A real subsequent generation bump (a later recording's own clearAll())
  // still trips the mismatch correctly, since by then this field holds
  // whatever value cleanup_table() last actually observed, not this sentinel.
  _last_class_map_generation = Profiler::instance()->classMap()->generation();

  if (VM::hotspot_version() < 11) {
    Log::warn("Liveness tracking requires Java 11+");
    // disable liveness tracking
    _table_max_cap = 0;
    return _stored_error = Error::OK;
  }

  JNIEnv *env = VM::jni();

  Error err = initialize_table(env, args._memory);
  if (err) {
    Log::warn("Liveness tracking requires heap size information");
    // disable liveness tracking
    _table_max_cap = 0;
    return _stored_error = Error::OK;
  }
  if (!(_Class = env->FindClass("java/lang/Class"))) {
    jniExceptionCheck(env, true);
    err = Error("Unable to find java/lang/Class");
  } else if (!(_Class_getName = env->GetMethodID(_Class, "getName",
                                                 "()Ljava/lang/String;"))) {
    jniExceptionCheck(env, true);
    err = Error("Unable to find java/lang/Class.getName");
  }
  if (err) {
    Log::warn("Liveness tracking requires access to java.lang.Class#getName()");
    // disable liveness tracking
    _table_max_cap = 0;
    return _stored_error = Error::OK;
  }

  _subsample_ratio = args._live_samples_ratio;

  _table_size = 0;
  _table_cap =
      std::min(2048, _table_max_cap); // with default 512k sampling interval, it's
                                   // enough for 1G of heap
  _table = (TrackingEntry *)malloc(sizeof(TrackingEntry) * _table_cap);
  if (_table != NULL) {
    NativeMem::record(NM_LIVENESS, (long long)sizeof(TrackingEntry) * _table_cap);
  }

  _gc_epoch = 0;
  _last_gc_epoch = 0;

  return _stored_error = Error::OK;
}

static void* create_mt19937() {
  // std::mt19937 itself is noexcept, but std::random_device and `new` may throw.
  // If that happens we let the failure terminate the process (same outcome as
  // failing thread_local initialization previously).
  return static_cast<void*>(new std::mt19937(std::random_device{}()));
}

static void* create_uniform_real_distribution() {
  // std::uniform_real_distribution<> construction is noexcept, but `new` may throw.
  // If allocation fails the process is likely to abort anyway.
  return static_cast<void*>(new std::uniform_real_distribution<>(0, 1.0));
}

static void free_mt19937(void* p) {
  std::mt19937* mt = static_cast<std::mt19937*>(p);
  delete mt;
}

static void free_uniform_real_distribution(void* p) {
  std::uniform_real_distribution<>* urd = static_cast<std::uniform_real_distribution<>*>(p);
  delete urd;
}

// File-scope (not track()-local) so releaseThreadLocalState() below can reach
// them from Profiler::onThreadEnd(). Relying solely on these ThreadLocal's own
// pthread-key destructors is not sufficient: pthread key destructors only fire
// when the underlying OS thread actually exits, not when a JNI-attached thread
// detaches via DetachCurrentThread. A reused pooled OS thread that repeatedly
// attaches/detaches would otherwise leak one mt19937 and one
// uniform_real_distribution allocation per attach cycle, since get() lazily
// re-creates the value on the next track() call but nothing ever frees the
// previous one until OS thread exit (which may never happen). Hooking explicit
// cleanup into onThreadEnd matches how every other per-thread profiler state
// (CPU/wall engine registration, ProfiledThread) is already torn down.
static ThreadLocal<std::mt19937*, create_mt19937, free_mt19937> gen;
static ThreadLocal<std::uniform_real_distribution<>*, create_uniform_real_distribution, free_uniform_real_distribution> dis;
static ThreadLocal<double> skipped;

void LivenessTracker::releaseThreadLocalState() {
  gen.clear();
  dis.clear();
  skipped.clear();
}

void LivenessTracker::track(JNIEnv *env, AllocEvent &event, jint tid,
                            jobject object, u64 call_trace_id) {
  if (!_enabled) {
    // disabled
    return;
  }
  if (_table_max_cap == 0) {
    // we are not to store any objects
    return;
  }

  if (_subsample_ratio < 1.0) {
    std::mt19937* genp = gen.get();
    std::uniform_real_distribution<>* disp = dis.get();
    if (disp->operator()(*genp) > _subsample_ratio) {
      skipped.set(skipped.get() + static_cast<double>(event._weight) * event._size);
      return;
    }
  }

  jweak ref = env->NewWeakGlobalRef(object);
  if (ref == nullptr) {
    return;
  }
  bool retried = false;
retry:
  if (!_table_lock.tryLockShared()) {
    // we failed to add the weak reference to the table so it won't get cleaned
    // up otherwise
    env->DeleteWeakGlobalRef(ref);
    return;
  }

  // Increment _table_size in a thread-safe manner (CAS) and store the new value
  // in idx It bails out if _table_size would overflow _table_cap
  int idx;
  do {
    idx = __atomic_load_n(&_table_size, __ATOMIC_RELAXED);
  } while (idx < _table_cap &&
           !__sync_bool_compare_and_swap(&_table_size, idx, idx + 1));

  if (idx < _table_cap) {
    _table[idx].tid = tid;
    _table[idx].time = TSC::ticks();
    _table[idx].ref = ref;
    _table[idx].alloc = event;
    _table[idx].skipped = skipped.get();
    skipped.set(0);
    _table[idx].age = 0;
    _table[idx].call_trace_id = call_trace_id;
    _table[idx].leak_tag = 0;
    _table[idx].ctx = ContextApi::snapshot();
    _table[idx].cached_klass_id = 0;
  }

  _table_lock.unlockShared();

  if (idx == _table_cap) {
    if (!retried) {
      // guarantees we don't busy loop until memory exhaustion
      retried = true;

      // try cleanup before resizing - there is a good chance it will free some
      // space. allow_resolve=false: this runs synchronously on the
      // allocation-sampling callback stack (see cleanup_table()'s own header
      // comment for why resolveKlassId() is unsafe here).
      cleanup_table(true, false);

      if (_table_cap < _table_max_cap) {

        // Let's increase the size of the table
        // This should only ever happen when sampling interval * size of table
        // is smaller than maximum heap size. So we only support increasing
        // the size of the table, not decreasing it.
        _table_lock.lock();

        // Only increase the size of the table to _table_max_cap elements
        int newcap = std::min(_table_cap * 2, _table_max_cap);
        if (_table_cap != newcap) {
          TrackingEntry *tmp = (TrackingEntry *)realloc(
                _table, sizeof(TrackingEntry) * newcap);
          if (tmp != nullptr) {
              NativeMem::record(NM_LIVENESS,
                  (long long)sizeof(TrackingEntry) * (newcap - _table_cap));
              _table = tmp;
              _table_cap = newcap;
              Log::debug(
                 "Increased size of Liveness tracking table to %d entries",
                  _table_cap);
          } else {
              Log::debug("Cannot add sampled object to Liveness tracking table, "
                         "resize attempt failed, the table is overflowing");
          }
        }

        _table_lock.unlock();

        goto retry;
      } else {
        Log::debug("Cannot add sampled object to Liveness tracking table, it's "
                   "overflowing");
        env->DeleteWeakGlobalRef(ref);
      }
    } else {
      env->DeleteWeakGlobalRef(ref);
    }
    skipped.set(0); // reset the subsampling skipped bytes
  }
}

void LivenessTracker::maybeForceCleanup(u64 now_ns) {
  if (!_enabled || !_gc_generations.load(std::memory_order_relaxed)) {
    return;
  }
  constexpr u64 FORCE_CLEANUP_INTERVAL_NS = 30ULL * 1000 * 1000 * 1000;
  u64 last_cleanup_ns = load(_last_cleanup_ns);
  if (now_ns - last_cleanup_ns < FORCE_CLEANUP_INTERVAL_NS) {
    return;
  }
  if (load(_gc_epoch) == load(_last_gc_epoch)) {
    // Nothing happened since the last sweep (organic, forced, or a prior
    // call to this method) - re-walking an unchanged table would just
    // re-fold the same survivor counts into this epoch's scratch, skewing
    // the slope computed from it. Leave _last_cleanup_ns alone so the next
    // wake keeps checking at the same ~1s cadence rather than restarting a
    // fresh 30s wait with nothing to show for it.
    return;
  }
  store(_last_cleanup_ns, now_ns);
  cleanup_table(true, true);
}

void JNICALL LivenessTracker::GarbageCollectionFinish(jvmtiEnv *jvmti_env) {
  ProfiledThread::initCurrentThreadSignalSafe();
  LivenessTracker::instance()->onGC();
}

size_t LivenessTracker::resolvePostGcHeapUsage(bool *out_is_last_gc) {
  bool isLastGc = HeapUsage::isLastGCUsageSupported();
  size_t used = isLastGc ? HeapUsage::get()._used_at_last_gc
                        : loadAcquire(_used_after_last_gc);
  TEST_LOG("LivenessTracker::resolvePostGcHeapUsage isLastGc=%d used_at_last_gc=%zu",
           (int)isLastGc, used);
  if (used == 0) {
    used = HeapUsage::get(false)._used;
    isLastGc = false;
    TEST_LOG("LivenessTracker::resolvePostGcHeapUsage used==0, falling back to HeapUsage::get(false)._used=%zu",
             used);
  }
  if (out_is_last_gc != nullptr) {
    *out_is_last_gc = isLastGc;
  }
  return used;
}

void LivenessTracker::onGC() {
  if (!_initialized) {
    return;
  }

  // just increment the epoch
  atomicIncRelaxed(_gc_epoch,u64(1));

  if (!HeapUsage::isLastGCUsageSupported()) {
    store(_used_after_last_gc, HeapUsage::get(false)._used);
  }

  if (_gc_generations.load(std::memory_order_relaxed)) {
    // Feeds heapFloorRising()'s corroboration check (selectLeakCandidates())
    // - gated on _gc_generations, same as the per-klass population table
    // itself, since this ring exists purely to support that feature.
    // recordHeapFloorSample() itself checks _heap_floor_recording_disabled_for_test
    // (debug-only) so a test can seed the ring exclusively.
    size_t used = resolvePostGcHeapUsage(nullptr);
    TEST_LOG("LivenessTracker::onGC recording heap floor used=%zu gc_epoch=%llu",
             used, (unsigned long long)load(_gc_epoch));
    if (used > 0) {
      // A failed read (-1, e.g. transient /sys/fs/cgroup access error) is
      // recorded as 0 rather than skipping the sample outright - see
      // _container_mem_ring's own comment (livenessTracker.h) for why this
      // ring must stay index-aligned with _heap_floor_ring/
      // _heap_floor_time_ring. Harmless when _container_memory_limit is
      // itself unavailable (secondsToOOM() never selects this ring then),
      // and a rare, self-correcting blip otherwise (the next successful
      // read re-establishes the real growth rate).
      long container_usage = OS::getContainerMemoryUsage();
      recordHeapFloorSample((u64)used, OS::nanotime(),
                             container_usage >= 0 ? (u64)container_usage : 0);
    } else {
      TEST_LOG("LivenessTracker::onGC used<=0, skipping heap floor record");
    }
  }
}

void LivenessTracker::getLiveTraceIds(CallTraceIdSet& out_buffer) {
  out_buffer.clear();
  
  if (!_enabled || !_initialized) {
    return;
  }
  
  // Lock the table to iterate over tracking entries
  _table_lock.lockShared();
  
  // Reserve space to avoid reallocations during filling
  // Note: unordered_set uses rehash for capacity management
  out_buffer.rehash(static_cast<size_t>(_table_size / 0.75f));
  
  // Collect call_trace_id values from all live tracking entries
  for (int i = 0; i < _table_size; i++) {
    TrackingEntry* entry = &_table[i];
    if (entry->ref != nullptr) {
      out_buffer.insert(entry->call_trace_id);
    }
  }
  
  _table_lock.unlockShared();
}
