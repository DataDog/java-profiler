/*
 * Copyright 2021, 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <algorithm>
#include <cstdint>
#include <limits>
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
#include "rcDebugLevel.h"
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
#include "xorshift.h"
#include <jni.h>
#include <string.h>

constexpr int LivenessTracker::MAX_TRACKING_TABLE_SIZE;
constexpr int LivenessTracker::MIN_SAMPLING_INTERVAL;

namespace {

// Window statistics shared by hasQualifyingGrowth() (per-klass count_ring,
// read under _table_lock) and heapFloorRising()/secondsToOOM() (the lock-free
// _heap_floor_ring, read via loadAcquire()): least-squares fit over the
// chronological window, giving the fitted value at the window's first and
// last position plus the earliest (whole-window) and recent (second-half)
// minima. The reader is templated so each caller supplies its own
// slot-access discipline.
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
  // Full-window least-squares fit: y = fitted value at position x (0 = oldest,
  // fill-1 = newest). Robust for oscillating-but-growing trends; O(fill) =
  // O(30) per scan.
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

// Recent-half corroboration for a usage ring: a rising full-window trend
// whose most recent half is flat is a plateaued step change, not ongoing
// growth. True only when the recent half has enough samples and rises.
template <typename Reader>
bool corroborateRecentHalf(u8 head, u8 fill, int ring_size, int min_fill,
                           Reader read) {
  int half_fill = fill / 2;
  RingThirdsStats recent_half_stats;
  bool have_half = ringThirdsStats(head, half_fill, ring_size, min_fill, read,
                                   &recent_half_stats);
  double half_delta = have_half
      ? recent_half_stats.recent_mean - recent_half_stats.earliest_mean
      : 0.0;
  return have_half && half_delta > 0;
}

} // namespace

void LivenessTracker::cleanup_table(bool forced, bool allow_resolve) {
  u64 current = load(_last_gc_epoch);
  u64 target_gc_epoch = load(_gc_epoch);
  TEST_LOG_SUMMARY("LivenessTracker::cleanup_table forced=%d gc_generations=%d current_epoch=%llu "
           "target_epoch=%llu table_size=%d",
           forced, _gc_generations.load(std::memory_order_relaxed), (unsigned long long)current,
           (unsigned long long)target_gc_epoch, _table_size);

  // is_epoch_owner: this call is the first (forced or not) to observe this
  // GC epoch transition. Population accounting is gated on this, not
  // !forced, so a forced sweep still folds one sample per new epoch. The
  // authoritative claim happens below under the table lock - a forced sweep
  // and a GC callback can race, and claiming up front could fold the same
  // epoch range twice (lock order is not claim order). This check stays an
  // advisory early-exit so the common no-op call never takes the lock.
  u64 advisory_current = current;
  if (target_gc_epoch != advisory_current || forced) {
    JNIEnv *env = VM::jni();

    _table_lock.lock();

    u64 claimed = load(_last_gc_epoch);
    bool is_epoch_owner = target_gc_epoch != claimed &&
        __atomic_compare_exchange_n(&_last_gc_epoch, &claimed, target_gc_epoch,
                                    false, __ATOMIC_RELAXED, __ATOMIC_RELAXED);
    int epoch_diff = (int)(target_gc_epoch - claimed);

  // Class-map reset (see _last_class_map_generation, livenessTracker.h):
  // cached klass ids from a cleared dictionary's generation can collide with a
  // newly assigned class; drop every such cache first.
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
        u32 target = newsz++;
        if (target != i) {
          _table[target] = _table[i]; // will clone TrackingEntry at 'i'
          _table[i].ref = nullptr;    // will nullify the original ref
          _table[i].call_trace_id = 0;
        }
        _table[target].age += epoch_diff;

        if (_gc_generations.load(std::memory_order_relaxed) && is_epoch_owner) {
          // Per-klass population tracking, gated on _gc_generations (paid only
          // when asked for) and on is_epoch_owner (not !forced) so a forced
          // sweep still contributes one sample per new GC epoch.
          u32 klass_id = 0;
          if (allow_resolve) {
            // Only affordable off the allocation-hot path (see
            // cleanup_table()'s header comment).
            jobject ref = env->NewLocalRef(_table[target].ref);
            if (ref != nullptr) {
              klass_id = resolveKlassId(env, ref);
              if (klass_id != 0) {
                // Cache the resolution: flush_table() re-resolves every
                // surviving entry's class right after this (an object's class
                // is immutable); later non-resolving sweeps reuse it.
                _table[target].cached_klass_id = klass_id;
              }
              env->DeleteLocalRef(ref);
            }
          } else {
            // resolveKlassId() is skipped here (see cleanup_table()'s
            // header comment); reuse an earlier sweep's cached id, or drop
            // this entry's sample for the epoch.
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

    TEST_LOG_SUMMARY("LivenessTracker::cleanup_table survivors=%u klass_count_scratch_size=%d",
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
}

u32 LivenessTracker::resolveKlassId(JNIEnv *env, jobject ref) {
  // Signature-based resolution (slash notation), NOT flush_table()'s
  // Class.getName()-based one: these ids must match the ids
  // ReferenceChainTracker resolves for discovered instances via
  // GetClassSignature + ObjectSampler::normalizeClassSignature() +
  // lookupClass() (resolveClassMap(), referenceChains.cpp) - the same
  // sequence as ObjectSampler::recordAllocation(). StringDictionary keys by
  // the exact string, and getName()'s "com.foo.Bar" (dot notation) is a
  // DIFFERENT key from the signature's "com/foo/Bar", so a getName()-based
  // id can never match across subsystems. Also a plain JVMTI call, not a
  // Java upcall that could allocate.
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
// descending, capped at MAX_OLDEST_SAMPLES (biases representatives toward
// long-lived instances).
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
  // releaseLeakTag() zeroes both fields, so a zero/zero slot means the tag was
  // released (or never acquired) - any other state is in use. (The free list
  // is a LIFO stack of indices, not an index-bounded region, so a
  // _leak_tag_free_count comparison proves nothing.)
  if (_leak_tag_info[idx].call_trace_id == 0 && _leak_tag_info[idx].tid == 0) {
    return false;
  }
  *out_call_trace_id = _leak_tag_info[idx].call_trace_id;
  *out_tid = _leak_tag_info[idx].tid;
  return true;
}

int LivenessTracker::tagLeakInstances(jvmtiEnv *jvmti,
                                       const KlassCandidate *candidates,
                                       int candidate_count) {
  if (!_enabled || _table == nullptr) {
    return 0;
  }
  JNIEnv *env = VM::jni();
  int tagged = 0;
  // Tagging priority: clearest surviving-age diversity first (a
  // continuously-leaking site keeps instances alive across many distinct GC
  // generations; a one-time burst does not), then oldest within a tid - if
  // the pool is contended, the strongest leak signal keeps the tags. The
  // (klass, tid) match scopes ranking to the leak site.
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
  // Per-poll (klass_id, tid) tag summary instead of per-instance logging,
  // which re-logged every stable pool tag every poll (256 lines/poll once the
  // pool saturates).
  struct TagSummary {
    u32 klass_id;
    jint tid;
    int tagged;
    int need_set;
    u64 min_age;
    u64 max_age;
    u64 max_size;
  };
  TagSummary summary[16];
  int summary_count = 0;
  int summary_overflow = 0;
  _table_lock.lockShared();
  u32 sz = _table_size;
  for (u32 i = 0; i < sz; i++) {
    // Skip unpublished slots (shared lock - see TrackingEntry::ready).
    if (__atomic_load_n(&_table[i].ready, __ATOMIC_ACQUIRE) != 1) {
      continue;
    }
    if (_table[i].ref == nullptr) {
      continue;
    }
    // (class, allocating thread) match: only instances a candidate's
    // QUALIFYING tids allocated are in tagging scope.
    u32 kid = _table[i].cached_klass_id;
    if (kid == 0) {
      continue;
    }
    bool match = false;
    for (int k = 0; k < candidate_count; k++) {
      if (candidates[k].klass_id != kid ||
          candidates[k].qualifying_tid_count <= 0) {
        continue;
      }
      for (int q = 0; q < candidates[k].qualifying_tid_count; q++) {
        if (candidates[k].qualifying_tids[q] == _table[i].tid) {
          match = true;
          break;
        }
      }
      if (match) {
        break;
      }
    }
    if (!match) {
      continue;
    }
    // Entries whose record already holds a pool tag are still collected: the
    // state machine below must re-act on the object's CURRENT JVMTI tag
    // (re-establish, correlate, or leave alone).
    if (n_candidates < (int)(sizeof(scratch) / sizeof(scratch[0]))) {
      scratch[n_candidates].table_idx = i;
      scratch[n_candidates].tid = _table[i].tid;
      scratch[n_candidates].age = _table[i].age;
      scratch[n_candidates].distinct_ages = 0;
      scratch[n_candidates].leak_tag_recorded = _table[i].leak_tag != 0;
      n_candidates++;
    }
  }
  // Per-tid distinct surviving ages (matching entries only, so the ranking
  // reflects exactly the population being tagged); beyond 32 tids, extras
  // share the lowest priority tier.
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
  // Entries already holding a pool tag first (correlate-or-re-establish,
  // not acquire), then highest age diversity, then oldest.
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
  // Per-candidate state machine on the object's CURRENT JVMTI tag, shared
  // with the BFS's frontier tags and never blindly overwritten (a SetTag
  // over a frontier tag would orphan that frontier entry):
  //   - leak tag: already waiting for interception - record it;
  //   - frontier tag: already admitted - correlate the entry, never retag;
  //   - no tag: plain SetTag (first tagging, or re-establishing after a
  //     search restart wiped all tags via releaseSearchTags()).
  for (int c = 0; c < n_candidates; c++) {
    u32 i = scratch[c].table_idx;
    jobject ref = env->NewLocalRef(_table[i].ref);
    if (ref == nullptr) {
      // Collected between the null check and now - the GC cleanup path
      // releases the record's tag; nothing to do.
      continue;
    }
    jlong existing = 0;
    jvmtiError tag_err = jvmti->GetTag(ref, &existing);
    jlong leak_tag = 0;
    bool need_set = false;
    if (tag_err == JVMTI_ERROR_NONE && existing >= LEAK_TAG_BASE) {
      // Already carries a leak tag - waiting for BFS interception; make
      // sure the record remembers it.
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
      // No tag: first tagging, or re-establishment after a restart wiped all
      // tags (releaseSearchTags() clears every JVMTI tag while the record
      // keeps its pool tag - reuse keeps pool accounting stable).
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
    // Accumulate into the per-poll summary instead of logging per instance.
    u32 tagged_kid = _table[i].cached_klass_id;
    jint tagged_tid = _table[i].tid;
    u64 tagged_age = _table[i].age;
    u64 tagged_size = _table[i].alloc._size;
    int g = 0;
    while (g < summary_count &&
           (summary[g].klass_id != tagged_kid || summary[g].tid != tagged_tid)) {
      g++;
    }
    if (g == summary_count && summary_count >=
            (int)(sizeof(summary) / sizeof(summary[0]))) {
      // Bounded groups exceeded (candidates <= 5, qualifying tids <= 8
      // each); overflow lumps into the counter.
      summary_overflow++;
    } else if (g == summary_count) {
      summary[g].klass_id = tagged_kid;
      summary[g].tid = tagged_tid;
      summary[g].tagged = 1;
      summary[g].need_set = (int)need_set;
      summary[g].min_age = tagged_age;
      summary[g].max_age = tagged_age;
      summary[g].max_size = tagged_size;
      summary_count++;
    } else {
      summary[g].tagged++;
      summary[g].need_set += (int)need_set;
      if (tagged_age < summary[g].min_age) {
        summary[g].min_age = tagged_age;
      }
      if (tagged_age > summary[g].max_age) {
        summary[g].max_age = tagged_age;
      }
      if (tagged_size > summary[g].max_size) {
        summary[g].max_size = tagged_size;
      }
    }
    env->DeleteLocalRef(ref);
  }
  _table_lock.unlockShared();
  for (int g = 0; g < summary_count; g++) {
    TEST_LOG("LivenessTracker::tagLeakInstances summary klass_id=%u "
             "tid=%d tagged=%d need_set=%d min_age=%llu max_age=%llu "
             "max_size=%llu",
             summary[g].klass_id, (int)summary[g].tid, summary[g].tagged,
             summary[g].need_set, (unsigned long long)summary[g].min_age,
             (unsigned long long)summary[g].max_age,
             (unsigned long long)summary[g].max_size);
  }
  if (summary_overflow > 0) {
    TEST_LOG("LivenessTracker::tagLeakInstances summary overflow=%d "
             "(groups beyond %d)",
             summary_overflow, (int)(sizeof(summary) / sizeof(summary[0])));
  }
  return tagged;
}

void LivenessTracker::insertThreadGen(KlassCountScratch &scratch,
                                      jint tid, u32 age) {
  for (int i = 0; i < scratch.thread_count; i++) {
    if (scratch.threads[i].tid == tid) {
      auto &t = scratch.threads[i];
      // Every surviving object counts toward the per-tid retained-count bar
      // (TID_RETAINED_COUNT_BAR) BEFORE the age-dedup early return below: the
      // count is per-instance, the ages are per-cohort.
      t.count++;
      for (u32 j = 0; j < t.age_count; j++) {
        if (t.ages[j] == age) {
          return; // age already counted for this thread
        }
      }
      if (t.age_count < KlassCountScratch::MAX_AGES_PER_THREAD) {
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
    scratch.threads[idx].count = 1; // this object is the tid's first this epoch
  }
  // else: thread table full - additional threads are not tracked, but
  // oldest[] still captures instances from all threads.
}

void LivenessTracker::accumulateKlassCount(u32 klass_id, jlong age,
                                           jweak sample_source,
                                           jint tid) {
  // Count distinct GC ages (generations) per klass: if new instances keep
  // arriving while old ones survive, the distinct-age count grows.
  for (int i = 0; i < _klass_count_scratch_size; i++) {
    if (_klass_count_scratch[i].klass_id == klass_id) {
      auto &entry = _klass_count_scratch[i];
      // Age dedup for the generation count only - oldest[] and per-tid
      // tracking must see EVERY surviving object.
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
      // Top-N oldest instances (Lindy bias): runs for every object, not
      // just new ages.
      insertOldestSample(entry, sample_source, (u32)age, tid);
      // Per-thread distinct surviving generations: the thread's generation
      // cardinality is the leak signal, so it must see all surviving objects.
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
  // else: scratch already holds MAX_KLASS_POPULATION_ENTRIES klasses - this
  // epoch's count for klass_id is dropped (same best-effort tradeoff
  // _klass_population accepts).
}

jweak LivenessTracker::recordKlassPopulationSampleLocked(
    u32 klass_id, u32 count, u64 epoch, int *out_slot, bool *out_created,
    jweak *out_evicted, int *out_evicted_count, int max_evicted) {
  // Linear scan is fine: MAX_KLASS_POPULATION_ENTRIES is small enough.
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
      // guaranteed set: the loop above ran at least once).
      slot = evict_slot;
      // Return evicted representatives to the caller (which owns the
      // JNIEnv) for DeleteWeakGlobalRef.
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
    // A reused (evicted) slot's previous class's per-tid trends must not
    // leak onto the new one, same as the fields above.
    _klass_population[slot].tid_trend_count = 0;
    // A reused (evicted) slot's PREVIOUS class's stable tag must not leak
    // onto the new one; minted lazily once a live instance is available.
    _klass_population[slot].stable_class_tag = 0;
  }

  KlassPopulationEntry &entry = _klass_population[slot];
  entry.count_ring[entry.ring_head] = count;
  entry.ring_head = (u8)((entry.ring_head + 1) % KLASS_POPULATION_RING_SIZE);
  if (entry.ring_fill < KLASS_POPULATION_RING_SIZE) {
    entry.ring_fill++;
  }
  entry.last_updated_epoch = epoch;

  // Updated here, not in selectLeakCandidates(), so every caller keeps
  // consecutive_positive in sync with the ring it just pushed.
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
  TEST_LOG_SUMMARY("LivenessTracker::foldKlassCountsLocked epoch=%llu scratch_size=%d",
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
  // Pure table work, no JNIEnv - runs regardless of allow_resolve.
    recordTidTrendSamplesLocked(slot, s);
    for (int r = 0; r < evicted_count; r++) {
      if (evicted[r] != nullptr) {
        env->DeleteWeakGlobalRef(evicted[r]);
      }
    }
    if (!allow_resolve) {
      // Minting is skipped on track()'s hot path (see cleanup_table()'s
      // header comment); the retry below picks it up on the next
      // allow_resolve=true sweep.
      continue;
    }
    // Also retry when an existing entry's representatives are stale (a
    // jweak's pointer never becomes nullptr when its referent dies, so each
    // must be probed); resolving every epoch bounds the gap to one epoch.
    bool need_mint = created ||
        _klass_population[slot].representative_count == 0;
    if (!need_mint) {
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
    // Dominant allocating thread = highest generation cardinality. Thread
    // id, not call_trace_id: lambda/synthetic variants of one logical site
    // produce distinct trace ids.
    jint dominant_tid = 0;
    u32 dominant_gens = 0;
    for (int ti = 0; ti < s.thread_count; ti++) {
      if (s.threads[ti].age_count > dominant_gens) {
        dominant_gens = s.threads[ti].age_count;
        dominant_tid = s.threads[ti].tid;
      }
    }
    // Re-mint if the dominant thread has >1 generation AND no current rep
    // was minted from it: startup-noise reps stay live (blocking
    // re-selection) even after the real leak thread becomes dominant.
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
      for (int r = 0; r < _klass_population[slot].representative_count; r++) {
        if (_klass_population[slot].representatives[r] != nullptr) {
          env->DeleteWeakGlobalRef(_klass_population[slot].representatives[r]);
          _klass_population[slot].representatives[r] = nullptr;
        }
        _klass_population[slot].rep_tids[r] = 0;
      }
      _klass_population[slot].representative_count = 0;
      // Mint fresh representatives, preferring the dominant thread's
      // instances; fill remaining slots with other oldest instances.
      bool minted_any = false;
      int minted = 0;
      // First pass: dominant thread's instances (only if it has >1
      // distinct generation - otherwise pure oldest-first is fine).
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
      // else: all surviving instances for this klass died before we could
      // mint - left with representative_count=0, retried next epoch.
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

  // Cached for selectLeakCandidates()'s ranking - the ring only changes on
  // push, so this is the same value a later re-scan would compute.
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

bool LivenessTracker::hasQualifyingTidGrowth(
    const KlassPopulationEntry::TidTrend &trend) const {
  RingThirdsStats stats;
  if (!ringThirdsStats(
          trend.ring_head, trend.ring_fill,
          KlassPopulationEntry::TID_TREND_RING_SIZE,
          TID_TREND_MIN_FILL_FOR_TREND,
          [&trend](int i) { return (double)trend.ring[i]; }, &stats)) {
    return false;
  }
  // Same growth bar as the klass gate: per-tid age-cardinality is the same
  // small-integer signal, so the thresholds transfer unchanged.
  double growth_bar = LEAK_GROWTH_REL_MIN * stats.earliest_mean;
  if (growth_bar < LEAK_GROWTH_ABS_MIN) {
    growth_bar = LEAK_GROWTH_ABS_MIN;
  }
  return (stats.recent_mean - stats.earliest_mean) >= growth_bar;
}

bool LivenessTracker::tidPushQualifies(
    const KlassPopulationEntry::TidTrend &trend, u32 current_count) const {
  // Second discriminator before the (usually cheaper) ring re-scan: a count
  // over the bar qualifies without any history at all.
  if (current_count >= TID_RETAINED_COUNT_BAR) {
    return true;
  }
  return hasQualifyingTidGrowth(trend);
}

void LivenessTracker::recordTidTrendSamplesLocked(
    int slot, const KlassCountScratch &scratch) {
  if (slot < 0 || slot >= _klass_population_size) {
    return;
  }
  KlassPopulationEntry &entry = _klass_population[slot];
  // Present tids: find-or-create their trend and push this epoch's
  // distinct-age count (scratch threads always carry >=1 survivor).
  for (int ti = 0; ti < scratch.thread_count; ti++) {
    jint tid = scratch.threads[ti].tid;
    KlassPopulationEntry::TidTrend *trend = nullptr;
    for (int i = 0; i < entry.tid_trend_count; i++) {
      if (entry.tid_trends[i].tid == tid) {
        trend = &entry.tid_trends[i];
        break;
      }
    }
    if (trend != nullptr && trend->synthetic) {
      // Seam-owned history: a real fold interleaving its own count would
      // reset the scenario's seeded hysteresis every System.gc().
      continue;
    }
    if (trend == nullptr) {
      if (entry.tid_trend_count < KlassPopulationEntry::MAX_TID_TRENDS) {
        trend = &entry.tid_trends[entry.tid_trend_count++];
      } else {
        // Full: evict the weakest non-synthetic trend (lowest
        // consecutive_positive, then ring_fill) - a rising leak tid resists
        // eviction. If every slot is synthetic, drop the new tid.
        int victim = -1;
        for (int i = 0; i < entry.tid_trend_count; i++) {
          if (entry.tid_trends[i].synthetic) {
            continue;
          }
          if (victim < 0 ||
              (entry.tid_trends[i].consecutive_positive <
               entry.tid_trends[victim].consecutive_positive) ||
              (entry.tid_trends[i].consecutive_positive ==
                   entry.tid_trends[victim].consecutive_positive &&
               entry.tid_trends[i].ring_fill <
                   entry.tid_trends[victim].ring_fill)) {
            victim = i;
          }
        }
        if (victim < 0) {
          continue; // all slots synthetic - drop this tid's sample
        }
        trend = &entry.tid_trends[victim];
      }
      trend->tid = tid;
      trend->ring_head = 0;
      trend->ring_fill = 0;
      trend->consecutive_positive = 0;
      trend->synthetic = false;
    }
    trend->ring[trend->ring_head] = (u8)scratch.threads[ti].age_count;
    trend->count_ring[trend->ring_head] =
        (u8)std::min<u32>(scratch.threads[ti].count, UINT8_MAX);
    trend->ring_head = (u8)((trend->ring_head + 1) %
                            KlassPopulationEntry::TID_TREND_RING_SIZE);
    if (trend->ring_fill < KlassPopulationEntry::TID_TREND_RING_SIZE) {
      trend->ring_fill++;
    }
    if (tidPushQualifies(*trend, scratch.threads[ti].count)) {
      if (trend->consecutive_positive < UINT8_MAX) {
        trend->consecutive_positive++;
      }
    } else {
      trend->consecutive_positive = 0;
    }
  }
  // Tracked tids ABSENT this epoch: a dead thread must not keep a stale
  // rising ring - push 0 so hysteresis resets. Synthetic trends are exempt
  // (see TidTrend::synthetic).
  for (int i = 0; i < entry.tid_trend_count; i++) {
    KlassPopulationEntry::TidTrend &trend = entry.tid_trends[i];
    if (trend.synthetic) {
      continue;
    }
    bool present = false;
    for (int ti = 0; ti < scratch.thread_count; ti++) {
      if (scratch.threads[ti].tid == trend.tid) {
        present = true;
        break;
      }
    }
    if (present) {
      continue;
    }
    trend.ring[trend.ring_head] = 0;
    trend.count_ring[trend.ring_head] = 0;
    trend.ring_head = (u8)((trend.ring_head + 1) %
                          KlassPopulationEntry::TID_TREND_RING_SIZE);
    if (trend.ring_fill < KlassPopulationEntry::TID_TREND_RING_SIZE) {
      trend.ring_fill++;
    }
    // A 0-count epoch cannot qualify as a rise - reset now rather than
    // deferring to the next push, so a long-absent tid does not keep
    // hysteresis from before its population died.
    trend.consecutive_positive = 0;
  }
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
  // Lock-free, single-writer-at-a-time (see _heap_floor_ring,
  // livenessTracker.h, for why onGC() cannot take _table_lock here).
  //
  // SPSC publish order: payload is a plain store; the index that gates
  // valid slots carries the release, so a loadAcquire() reader of the index
  // is guaranteed to see the payload writes too.
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
  // loadAcquire() here pairs with recordHeapFloorSample()'s storeRelease()
  // on both index fields, making the payload writes below visible.
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

  // The SHORTER projection wins: container usage includes native memory,
  // thread stacks, code cache and sibling cgroups, so a container limit
  // numerically LARGER than -Xmx can still be closer to exhaustion than the
  // heap (and vice versa). An unavailable limit is no boundary.
  u8 fill = loadAcquire(_heap_floor_ring_fill);
  u8 head = loadAcquire(_heap_floor_ring_head);
  if (fill < KLASS_POPULATION_MIN_FILL_FOR_TREND) {
    TEST_LOG("LivenessTracker::secondsToOOM -> -1 (INSUFFICIENT_FILL fill=%d need=%d)",
             (int)fill, KLASS_POPULATION_MIN_FILL_FOR_TREND);
    return -1;
  }
  RingThirdsStats time_stats;
  if (!ringThirdsStats(
          head, fill, KLASS_POPULATION_RING_SIZE,
          KLASS_POPULATION_MIN_FILL_FOR_TREND,
          [this](int i) { return (double)load(_heap_floor_time_ring[i]); },
          &time_stats)) {
    return -1;
  }
  double time_delta_ns = time_stats.recent_mean - time_stats.earliest_mean;
  if (time_delta_ns <= 0) {
    TEST_LOG("LivenessTracker::secondsToOOM -> -1 (NOT_RISING time_delta_ns=%.0f)",
             time_delta_ns);
    return -1;
  }

  double best_seconds = -1.0;
  const char *best_source = "none";
  double best_recent_mean = 0;

  RingThirdsStats heap_bytes;
  if (max_heap > 0 &&
      ringThirdsStats(head, fill, KLASS_POPULATION_RING_SIZE,
                      KLASS_POPULATION_MIN_FILL_FOR_TREND,
                      [this](int i) { return (double)load(_heap_floor_ring[i]); },
                      &heap_bytes) &&
      corroborateRecentHalf(head, fill, KLASS_POPULATION_RING_SIZE,
                            HEAP_FLOOR_RECENT_HALF_MIN_FILL,
                            [this](int i) { return (double)load(_heap_floor_ring[i]); })) {
    double remaining = (double)max_heap - heap_bytes.recent_mean;
    double secs = remaining <= 0
        ? 0
        : (remaining * time_delta_ns) /
              (heap_bytes.recent_mean - heap_bytes.earliest_mean) / 1e9;
    if (best_seconds < 0 || secs < best_seconds) {
      best_seconds = secs;
      best_source = "heap";
      best_recent_mean = heap_bytes.recent_mean;
    }
  }

  RingThirdsStats container_bytes;
  if (container_limit > 0 &&
      ringThirdsStats(head, fill, KLASS_POPULATION_RING_SIZE,
                      KLASS_POPULATION_MIN_FILL_FOR_TREND,
                      [this](int i) { return (double)load(_container_mem_ring[i]); },
                      &container_bytes) &&
      corroborateRecentHalf(head, fill, KLASS_POPULATION_RING_SIZE,
                            HEAP_FLOOR_RECENT_HALF_MIN_FILL,
                            [this](int i) { return (double)load(_container_mem_ring[i]); })) {
    double remaining = (double)container_limit - container_bytes.recent_mean;
    double secs = remaining <= 0
        ? 0
        : (remaining * time_delta_ns) /
              (container_bytes.recent_mean - container_bytes.earliest_mean) / 1e9;
    if (best_seconds < 0 || secs < best_seconds) {
      best_seconds = secs;
      best_source = "container";
      best_recent_mean = container_bytes.recent_mean;
    }
  }

  if (best_seconds < 0) {
    TEST_LOG("LivenessTracker::secondsToOOM -> -1 (no rising boundary "
             "fill=%d heap=%lld container=%lld)",
             (int)fill, (long long)max_heap, (long long)container_limit);
    return -1;
  }
  TEST_LOG("LivenessTracker::secondsToOOM source=%s limit-projection=%.3fs "
           "recent_mean=%.0f fill=%d",
           best_source, best_seconds, best_recent_mean, (int)fill);
  return best_seconds;
}

int LivenessTracker::selectLeakCandidates(KlassCandidate *out, int max) {
  int cap = max < MAX_LEAK_CANDIDATES ? max : MAX_LEAK_CANDIDATES;
  if (cap <= 0) {
    return 0;
  }

  // Top-k insertion-style selection, at most `cap` (<= 5) entries - cheaper
  // than collecting everything and sorting for N <= 256 klasses. One
  // heapFloorRising() call per scan: an aggregate, non-attributed signal only
  // moves the bar uniformly, never reorders candidates.
  const int required_hysteresis = heapFloorRising()
                                       ? LEAK_TREND_HYSTERESIS_CORROBORATED
                                       : LEAK_TREND_HYSTERESIS_BASE;

  double best_slopes[MAX_LEAK_CANDIDATES];
  int count = 0;

  // Read-only pass over _klass_population - shared-lock read against
  // cleanup_table()'s exclusive writer.
  _table_lock.lockShared();
  // This runs on every BFS-thread wake (~1s) - don't log empty scans.
  if (_klass_population_size > 0) {
    TEST_LOG("LivenessTracker::selectLeakCandidates scanning %d klass_population entries",
             _klass_population_size);
  }
  for (int i = 0; i < _klass_population_size; i++) {
    const KlassPopulationEntry &entry = _klass_population[i];
    // cached_slope was computed at the last push; the ring only changes on
    // push, so a re-scan here would just recompute the same value.
    bool has_trend = entry.ring_fill >= KLASS_POPULATION_MIN_FILL_FOR_TREND;
    double slope = entry.cached_slope;
    TEST_LOG("LivenessTracker::selectLeakCandidates entry[%d] klass_id=%u ring_fill=%u "
             "has_trend=%d slope=%f consecutive_positive=%u required=%d rep_count=%d",
             i, entry.klass_id, entry.ring_fill, has_trend, has_trend ? slope : 0.0,
             entry.consecutive_positive, required_hysteresis, entry.representative_count);
    if (!has_trend || slope <= 0 || entry.consecutive_positive < required_hysteresis) {
      // Not enough history yet, flat/shrinking, or hysteresis not met.
      continue;
    }
    // (klass,tid) qualification: a klass-level rise can come from churn
    // spread across many threads each retaining a stable handful, so at
    // least ONE tid's own trend must have held a qualifying rise for the
    // same hysteresis; the tids scope tagLeakInstances()'s tags to the
    // leak-site instances.
    jint qualifying_tids[KlassPopulationEntry::MAX_TID_TRENDS];
    int qualifying_tid_count = 0;
    for (int t = 0; t < entry.tid_trend_count &&
                    qualifying_tid_count <
                        (int)(sizeof(qualifying_tids) /
                              sizeof(qualifying_tids[0])); t++) {
      if (entry.tid_trends[t].consecutive_positive >=
          (u8)required_hysteresis) {
        qualifying_tids[qualifying_tid_count++] = entry.tid_trends[t].tid;
      }
    }
    if (qualifying_tid_count == 0) {
      TEST_LOG("LivenessTracker::selectLeakCandidates entry[%d] klass_id=%u "
               "klass trend OK but no qualifying tid - skipped",
               i, entry.klass_id);
      continue;
    }
    if (count == cap && slope <= best_slopes[cap - 1]) {
      // Already holding `cap` stronger (or equal) candidates.
      continue;
    }

    int pos = count < cap ? count++ : cap - 1;
    best_slopes[pos] = slope;
    KlassCandidate &cand = out[pos];
    cand.klass_id = entry.klass_id;
    cand.representative =
        entry.representative_count > 0 ? entry.representatives[0] : nullptr;
    cand.qualifying_tid_count = qualifying_tid_count;
    memcpy(cand.qualifying_tids, qualifying_tids,
           sizeof(jint) * (size_t)qualifying_tid_count);
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

  // Same top-k selection as selectLeakCandidates(), ranked by most-recent
  // count_ring sample instead of slope, with no hysteresis/trend gate.
  u32 best_counts[MAX_LEAK_CANDIDATES];
  int count = 0;

  _table_lock.lockShared();
  for (int i = 0; i < _klass_population_size; i++) {
    const KlassPopulationEntry &entry = _klass_population[i];
    if (entry.ring_fill == 0 || entry.stable_class_tag == 0) {
      // Never sampled, or stable_class_tag not yet minted - nothing to
      // rank or return.
      continue;
    }
    // ring_head is "next slot to write" - the latest written slot is one
    // behind it, wrapping.
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
  // Shared lock excludes cleanup_table()'s exclusive lock (the only place
  // that can DeleteWeakGlobalRef() representatives) for the whole
  // lookup+resolve, so NewLocalRef() always runs on a jweak the table still
  // owns (see selectLeakCandidates()). Returns the first live rep, oldest
  // first; resolveCandidateRepresentatives() returns all.
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
  // Returns all live representatives for klass_id, oldest first -
  // pollWatchedTargets() tags all of them, giving the canary mechanism
  // multiple chances to find a long-lived instance.
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

  // Clean up the tracking table before flushing it, so as few falsely
  // 'live' objects as possible are included.
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
        // Already resolved by cleanup_table()'s survivor loop this epoch -
        // reuse it instead of repeating the JNI class resolution.
        class_id = _table[i].cached_klass_id;
      } else {
        jclass clz = env->GetObjectClass(ref);
        jstring name_str = (jstring)env->CallObjectMethod(clz, _Class_getName);
        env->DeleteLocalRef(clz);
        jniExceptionCheck(env);
        // name_str can be null if the call above threw and jniExceptionCheck()
        // cleared the pending exception - GetStringUTFChars() requires a
        // non-null jstring.
        if (name_str != nullptr) {
          const char *name = env->GetStringUTFChars(name_str, nullptr);
          if (name != nullptr) {
            class_id = Profiler::instance()->lookupClass(name, strlen(name));
            env->ReleaseStringUTFChars(name_str, name);
          }
          env->DeleteLocalRef(name_str);
        }
      }

      // lookupClass() returns -1 at class-map capacity; assigning it to the
      // u32 event id would wrap to 0xFFFFFFFF and corrupt liveness attribution
      // - drop the sample instead.
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
  // Cached for secondsToOOM() rather than re-querying HeapUsage::getMaxHeap()
  // on every projection (see _max_heap_bytes, livenessTracker.h).
  _max_heap_bytes = max_heap;
  // Cached the same way (see _container_memory_limit, livenessTracker.h). -1
  // (unavailable) is a valid outcome here, unlike max_heap above: not every
  // JVM runs under a memory-limited cgroup.
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
  // The tracking table survives stop()/start(), and a preserved entry may
  // still own a leak tag - reclaim those first (blindly freeing every tag
  // could hand a new object a tag another live object owns; a second
  // releaseLeakTag() would push the same index twice, writing past
  // _leak_tag_free_list).
  bool tag_owned[LEAK_TAG_POOL_SIZE];
  memset(tag_owned, 0, sizeof(tag_owned));
  _table_lock.lock();
  for (u32 i = 0; i < _table_size; i++) {
    if (_table[i].leak_tag >= LEAK_TAG_BASE &&
        _table[i].leak_tag < LEAK_TAG_BASE + LEAK_TAG_POOL_SIZE) {
      tag_owned[_table[i].leak_tag - LEAK_TAG_BASE] = true;
    }
  }
  _table_lock.unlock();
  int free_w = 0;
  for (int i = 0; i < LEAK_TAG_POOL_SIZE; i++) {
    if (tag_owned[i]) {
      continue;
    }
    _leak_tag_free_list[free_w] = i;
    _leak_tag_info[i].call_trace_id = 0;
    _leak_tag_info[i].tid = 0;
    free_w++;
  }
  _leak_tag_free_count = free_w;
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

  // Gates per-klass population tracking (see _gc_generations,
  // livenessTracker.h). Updated ahead of the _initialized guard: each start
  // should observe the flag it was started with, even though the table
  // persists across recordings.
  _gc_generations.store(args._gc_generations, std::memory_order_relaxed);

  if (!_enabled) {
    return Error::OK;
  }

  // _record_heap_usage controls per-session JFR event emission only;
  // updated before the _initialized guard for the same reason.
  _record_heap_usage = args._record_heap_usage;

  if (_initialized) {
    // if the tracker was previously initialized return the stored result for
    // consistency; this also means liveness-tracking arguments from a later
    // start are ignored - required to track object liveness across many
    // recordings
    return _stored_error;
  }
  _initialized = true;

  // Sync the class-map-generation baseline to the current generation rather
  // than the constructor's 0 sentinel (see _last_class_map_generation,
  // livenessTracker.h): start() runs after Profiler::start()'s clearAll(),
  // so the 0 sentinel would trip a spurious mismatch on the first sweep,
  // wiping valid history.
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

  // Both halves replaced together; the threshold exists so the per-allocation
  // decision in track() is an integer compare rather than a double multiply.
  _subsample = SubsampleRate(args._live_samples_ratio);

  // Fresh recording: no chase is open, so no watched tids and no urgency
  // boost may leak in from a previous recording's lifecycle.
  __atomic_store_n(&_watched_tid_count, 0, __ATOMIC_RELEASE);
  __atomic_store_n(&_urgent_tracking, false, __ATOMIC_RELEASE);

  _table_size = 0;
  _table_cap =
      std::min(2048, _table_max_cap); // with default 512k sampling interval, it's
                                   // enough for 1G of heap
  _table = (TrackingEntry *)malloc(sizeof(TrackingEntry) * _table_cap);
  if (_table != NULL) {
    NativeMem::record(NM_LIVENESS, (long long)sizeof(TrackingEntry) * _table_cap);
    // Uninitialized malloc storage must never look published to a
    // shared-mode scanner (see TrackingEntry::ready).
    for (int i = 0; i < _table_cap; i++) {
      _table[i].ready = 0;
    }
  }

  _gc_epoch = 0;
  _last_gc_epoch = 0;

  return _stored_error = Error::OK;
}

// The subsampling generator's state, one u64 per thread. 0 means "not
// seeded yet": not a legal xorshift64 state, so it cannot collide with a
// live stream. No pthread-key destructor, so clearing
// (releaseThreadLocalState(), from Profiler::onThreadEnd()) returns the slot
// to the unseeded sentinel and drops the skipped-bytes accumulator.
static ThreadLocal<u64> rng;
static ThreadLocal<double> skipped;

// Chase-phase admission boost (see admitForTracking(), livenessTracker.h):
// both boost paths precede the ratio draw, so a boosted allocation never
// consumes an RNG draw and the non-boosted path keeps the exact reject-on-draw
// > ratio semantics.
bool LivenessTracker::admitForTracking(jint tid) {
  if (__atomic_load_n(&_urgent_tracking, __ATOMIC_ACQUIRE)) {
    return true;
  }
  // Count+array two-phase publish (noteSelectedCandidates() writes the slots
  // before release-storing the count): this acquire load pairs with that
  // release store, so every slot read below is at least as fresh as the
  // observed count.
  int n = __atomic_load_n(&_watched_tid_count, __ATOMIC_ACQUIRE);
  for (int i = 0; i < n; i++) {
    if (_watched_tids[i] == tid) {
      return true;
    }
  }
  if (_subsample.ratio >= 1.0) {
    return true;
  }
  u64 state = rng.get();
  if (state == 0) {
    // Seeded on a thread's first tracked allocation, kept until its TLS is
    // released; a thread that outlives a recording keeps its stream (no
    // per-recording reseed - stop/start does not clear the slot).
    state = xorshift::seed(TSC::ticks(), (u64)tid);
  }
  u64 draw = xorshift::next(state);
  rng.set(state);
  return draw < _subsample.threshold;
}

// Publishes the current poll's qualifying tids as track()'s watched-
// admission set, from pollWatchedTargets() with the FULL candidate selection
// (never the hasLeakSignal() max=1 probe - its partial view could drop other
// candidates' tids). The zero-candidate case clears the set: a tid left
// watched would keep admitting at 100% (the OS reuses tids).
void LivenessTracker::noteSelectedCandidates(const KlassCandidate *candidates,
                                              int count) {
  jint tids[KlassCandidate::MAX_QUALIFYING_TIDS];
  int n = 0;
  if (candidates != nullptr && count > 0) {
    for (int i = 0; i < count; i++) {
      const KlassCandidate &kc = candidates[i];
      for (int j = 0; j < kc.qualifying_tid_count; j++) {
        jint tid = kc.qualifying_tids[j];
        bool dup = false;
        for (int k = 0; k < n && !dup; k++) {
          dup = (tids[k] == tid);
        }
        if (!dup) {
          tids[n++] = tid;
          if (n == KlassCandidate::MAX_QUALIFYING_TIDS) {
            goto full;
          }
        }
      }
    }
  }
full:
  // Copy into the live array before publishing the count (two-phase publish
  // mirrored by admitForTracking()'s acquire load). A reader mid-scan may
  // transiently mix old and new slots below the OLD count - harmless.
  for (int i = 0; i < n; i++) {
    _watched_tids[i] = tids[i];
  }
  __atomic_store_n(&_watched_tid_count, n, __ATOMIC_RELEASE);
  if (n > 0) {
    // TEST_LOG, not Log::debug: pod-side verification of the boost engaging
    // needs the tid list in the extracted lib's logs (never the allocation hot
    // path - one line per poll on the reference-chain thread).
    TEST_LOG("LivenessTracker::noteSelectedCandidates watched tids[%d]:",
             n);
    for (int i = 0; i < n; i++) {
      TEST_LOG("  watched tid=%d", _watched_tids[i]);
    }
  }
}

void LivenessTracker::setUrgentTracking(bool urgent) {
  // Transition-only TEST_LOG: the setter runs every threadLoop() iteration.
  bool prev = __atomic_exchange_n(&_urgent_tracking, urgent, __ATOMIC_ACQ_REL);
  if (prev != urgent) {
    TEST_LOG_SUMMARY("LivenessTracker::setUrgentTracking urgent=%d", (int)urgent);
  }
}

void LivenessTracker::admissionResetForTest() {
  __atomic_store_n(&_urgent_tracking, false, __ATOMIC_RELEASE);
  __atomic_store_n(&_watched_tid_count, 0, __ATOMIC_RELEASE);
  _subsample = SubsampleRate(0.0);
  rng.clear();
  skipped.set(0);
}

void LivenessTracker::releaseThreadLocalState() {
  rng.clear();
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

  if (!admitForTracking(tid)) {
    skipped.set(skipped.get() + static_cast<double>(event._weight) * event._size);
    return;
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

  // Increment _table_size via CAS and take the new index; bails out if
  // _table_size would overflow _table_cap.
  int idx;
  do {
    idx = __atomic_load_n(&_table_size, __ATOMIC_RELAXED);
  } while (idx < _table_cap &&
           !__sync_bool_compare_and_swap(&_table_size, idx, idx + 1));

  if (idx < _table_cap) {
    // Unpublish first: a previous entry at this index may still be visible to
    // shared-mode scanners (their acquire load below then skips it instead of
    // racing the re-fill).
    __atomic_store_n(&_table[idx].ready, 0, __ATOMIC_RELEASE);
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
    // Publish: the payload is complete - release pairs with the scanners'
    // acquire loads.
    __atomic_store_n(&_table[idx].ready, 1, __ATOMIC_RELEASE);
  }

  _table_lock.unlockShared();

  if (idx == _table_cap) {
    if (!retried) {
      // guarantees we don't busy loop until memory exhaustion
      retried = true;

      // try cleanup before resizing - a good chance it frees space.
      // allow_resolve=false: this runs synchronously on the
      // allocation-sampling callback stack (see cleanup_table()'s header
      // comment).
      cleanup_table(true, false);

      if (_table_cap < _table_max_cap) {

        // Let's increase the size of the table. This should only ever happen
        // when sampling interval * size of table is smaller than maximum heap
        // size, so we only support increasing the size of the table, not
        // decreasing it.
        _table_lock.lock();

        // Only increase the size of the table to _table_max_cap elements
        int newcap = std::min(_table_cap * 2, _table_max_cap);
        if (_table_cap != newcap) {
          TrackingEntry *tmp = (TrackingEntry *)realloc(
                _table, sizeof(TrackingEntry) * newcap);
          if (tmp != nullptr) {
              NativeMem::record(NM_LIVENESS,
                  (long long)sizeof(TrackingEntry) * (newcap - _table_cap));
              // Unpublish the uninitialized growth region (see
              // TrackingEntry::ready); the realloc happens under the exclusive
              // table lock, so no scanner can observe the interim.
              for (int i = _table_cap; i < newcap; i++) {
                tmp[i].ready = 0;
              }
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
    // Nothing happened since the last sweep - re-walking an unchanged table
    // would just re-fold the same survivor counts, skewing the slope. Leave
    // _last_cleanup_ns alone so the next wake keeps checking at ~1s cadence.
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

  atomicIncRelaxed(_gc_epoch,u64(1));

  if (!HeapUsage::isLastGCUsageSupported()) {
    store(_used_after_last_gc, HeapUsage::get(false)._used);
  }

  if (_gc_generations.load(std::memory_order_relaxed)) {
    // Feeds heapFloorRising(); gated on _gc_generations like the population
    // table, since this ring exists purely to support that feature.
    size_t used = resolvePostGcHeapUsage(nullptr);
    TEST_LOG_SUMMARY("LivenessTracker::onGC recording heap floor used=%zu gc_epoch=%llu",
             used, (unsigned long long)load(_gc_epoch));
    if (used > 0) {
  // A failed read (-1, e.g. transient /sys/fs/cgroup access error) is
  // recorded as 0 rather than skipping the sample - this ring must stay
  // index-aligned with the other heap-floor rings (see _container_mem_ring,
  // livenessTracker.h).
      long container_usage = OS::getContainerMemoryUsage();
      recordHeapFloorSample((u64)used, OS::nanotime(),
                             container_usage >= 0 ? (u64)container_usage : 0);
    } else {
      TEST_LOG_SUMMARY("LivenessTracker::onGC used<=0, skipping heap floor record");
    }
  }
}

void LivenessTracker::getLiveTraceIds(CallTraceIdSet& out_buffer) {
  out_buffer.clear();
  
  if (!_enabled || !_initialized) {
    return;
  }
  
  _table_lock.lockShared();
  
  out_buffer.rehash(static_cast<size_t>(_table_size / 0.75f));
  
  for (int i = 0; i < _table_size; i++) {
    TrackingEntry* entry = &_table[i];
    // Skip unpublished slots (shared lock - see TrackingEntry::ready).
    if (__atomic_load_n(&entry->ready, __ATOMIC_ACQUIRE) != 1) {
      continue;
    }
    if (entry->ref != nullptr) {
      out_buffer.insert(entry->call_trace_id);
    }
  }
  
  _table_lock.unlockShared();
}
