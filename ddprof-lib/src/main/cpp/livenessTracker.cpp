/*
 * Copyright 2021, 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <algorithm>
#include <cstdint>
#include <random>
#include <set>
#include <thread>

#include "arch.h"
#include "common.h"
#include "context.h"
#include "context_api.h"
#include "hotspot/vmStructs.h"
#include "incbin.h"
#include "jniHelper.h"
#include "livenessTracker.h"
#include "log.h"
#include "os.h"
#include "profiler.h"
#include "threadLocalData.h"
#include "threadLocal.h"
#include "tsc.h"
#include <jni.h>
#include <string.h>

constexpr int LivenessTracker::MAX_TRACKING_TABLE_SIZE;
constexpr int LivenessTracker::MIN_SAMPLING_INTERVAL;

void LivenessTracker::cleanup_table(bool forced, bool allow_resolve) {
  u64 current = load(_last_gc_epoch);
  u64 target_gc_epoch = load(_gc_epoch);
  TEST_LOG("LivenessTracker::cleanup_table forced=%d gc_generations=%d current_epoch=%llu "
           "target_epoch=%llu table_size=%d",
           forced, _gc_generations, (unsigned long long)current,
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

        if (_gc_generations && is_epoch_owner) {
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
            accumulateKlassCount(klass_id, _table[target].ref);
          }
        }
      } else {
        jweak tmpRef = _table[i].ref;
        _table[i].ref = nullptr;
        env->DeleteWeakGlobalRef(tmpRef);
        _table[i].call_trace_id = 0;
      }
    }

    _table_size = newsz;

    TEST_LOG("LivenessTracker::cleanup_table survivors=%u klass_count_scratch_size=%d",
             newsz, _klass_count_scratch_size);
    if (_gc_generations && is_epoch_owner && _klass_count_scratch_size > 0) {
      foldKlassCountsLocked(env, target_gc_epoch);
    }

    end = OS::nanotime();
    Log::debug("Liveness tracker cleanup took %.2fms (%.2fus/element)",
               1.0f * (end - start) / 1000 / 1000,
               1.0f * (end - start) / 1000 / sz);
  }
  _table_lock.unlock();
}

u32 LivenessTracker::resolveKlassId(JNIEnv *env, jobject ref) {
  // Mirrors flush_table()'s own class-name resolution below (GetObjectClass +
  // Class.getName() + Profiler::lookupClass()) - kept duplicated rather than
  // factored out because flush_table() also needs to build an
  // ObjectLivenessEvent around the result, which this call site does not.
  // Unlike flush_table(), this call site also DeleteLocalRef()s name_str: it
  // runs once per surviving TrackingEntry per GC epoch (cleanup_table()'s
  // survivor loop above) rather than once per JFR flush, so an unreleased
  // local ref here accumulates far faster within whatever native frame is
  // driving cleanup_table().
  jclass clz = env->GetObjectClass(ref);
  jstring name_str = (jstring)env->CallObjectMethod(clz, _Class_getName);
  env->DeleteLocalRef(clz);
  jniExceptionCheck(env);
  u32 id = 0;
  // getName() can return null (and leave name_str null) if the call above
  // threw and jniExceptionCheck() cleared the pending exception rather than
  // propagating it - GetStringUTFChars()/ReleaseStringUTFChars() require a
  // non-null jstring, so guard both calls on name_str rather than passing a
  // possibly-null reference into them.
  if (name_str != nullptr) {
    const char *name = env->GetStringUTFChars(name_str, nullptr);
    if (name != nullptr) {
      int lookup_id = Profiler::instance()->lookupClass(name, strlen(name));
      if (lookup_id > 0) {
        id = (u32)lookup_id;
      }
      env->ReleaseStringUTFChars(name_str, name);
    }
    env->DeleteLocalRef(name_str);
  }
  return id;
}

void LivenessTracker::accumulateKlassCount(u32 klass_id, jweak sample_source) {
  for (int i = 0; i < _klass_count_scratch_size; i++) {
    if (_klass_count_scratch[i].klass_id == klass_id) {
      if (_klass_count_scratch[i].count < UINT16_MAX) {
        _klass_count_scratch[i].count++;
      }
      return;
    }
  }
  if (_klass_count_scratch_size < MAX_KLASS_POPULATION_ENTRIES) {
    KlassCountScratch &slot = _klass_count_scratch[_klass_count_scratch_size++];
    slot.klass_id = klass_id;
    slot.count = 1;
    slot.sample_source = sample_source;
  }
  // else: this epoch's scratch snapshot already holds
  // MAX_KLASS_POPULATION_ENTRIES distinct surviving klasses - klass_id's
  // count for this epoch is dropped rather than growing the scratch array,
  // the same best-effort tradeoff _klass_population's own fixed capacity
  // already accepts.
}

jweak LivenessTracker::recordKlassPopulationSampleLocked(u32 klass_id,
                                                           u16 count,
                                                           u64 epoch,
                                                           int *out_slot,
                                                           bool *out_created) {
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
      evicted_ref = _klass_population[slot].representative;
    }
    _klass_population[slot].klass_id = klass_id;
    _klass_population[slot].representative = nullptr;
    _klass_population[slot].ring_head = 0;
    _klass_population[slot].ring_fill = 0;
  }

  KlassPopulationEntry &entry = _klass_population[slot];
  entry.count_ring[entry.ring_head] = count;
  entry.ring_head = (u8)((entry.ring_head + 1) % KLASS_POPULATION_RING_SIZE);
  if (entry.ring_fill < KLASS_POPULATION_RING_SIZE) {
    entry.ring_fill++;
  }
  entry.last_updated_epoch = epoch;

  *out_slot = slot;
  *out_created = created;
  return evicted_ref;
}

void LivenessTracker::foldKlassCountsLocked(JNIEnv *env, u64 epoch) {
  TEST_LOG("LivenessTracker::foldKlassCountsLocked epoch=%llu scratch_size=%d",
           (unsigned long long)epoch, _klass_count_scratch_size);
  for (int i = 0; i < _klass_count_scratch_size; i++) {
    KlassCountScratch &s = _klass_count_scratch[i];
    TEST_LOG("LivenessTracker::foldKlassCountsLocked scratch[%d] klass_id=%u count=%u", i,
             s.klass_id, s.count);
    int slot;
    bool created;
    jweak evicted = recordKlassPopulationSampleLocked(s.klass_id, s.count,
                                                       epoch, &slot, &created);
    if (evicted != nullptr) {
      env->DeleteWeakGlobalRef(evicted);
    }
    // Also retry minting when an existing entry's representative is stale:
    // either the field itself is still nullptr (a klass whose first-epoch
    // sample_source died in the brief window between cleanup_table()'s
    // survival check and the mint attempt below), or the field holds a jweak
    // handle whose referent has since died - a jweak's own pointer value
    // never becomes nullptr just because its referent was collected, so a
    // representative pinned to one specific instance that later dies (while
    // other instances of the same still-growing klass keep surviving, so
    // this entry keeps being re-selected as a leak candidate) would
    // otherwise be left permanently unresolvable: the `created ||
    // representative == nullptr` check alone can only ever be true once per
    // slot. last_updated_epoch keeps advancing every epoch this klass has
    // survivors (right below), so it is never the LRU eviction victim that
    // would otherwise let a fresh entry (and a fresh mint attempt) replace
    // it. Resolving here every epoch bounds any given gap to "one epoch with
    // no representative", not permanent.
    jweak current_rep = _klass_population[slot].representative;
    bool stale = false;
    if (current_rep != nullptr) {
      jobject probe = env->NewLocalRef(current_rep);
      stale = (probe == nullptr);
      if (probe != nullptr) {
        env->DeleteLocalRef(probe);
      }
    }
    if (created || current_rep == nullptr || stale) {
      if (stale) {
        env->DeleteWeakGlobalRef(current_rep);
        _klass_population[slot].representative = nullptr;
      }
      // Mint a fresh, independent representative jweak rather than reusing
      // s.sample_source directly - s.sample_source is the corresponding
      // TrackingEntry's own weak ref, and that table slot's jweak gets
      // deleted via DeleteWeakGlobalRef (this file's cleanup_table(), the
      // "else" branch above) the moment the tracked object dies, which
      // would leave _klass_population holding a dangling handle if it
      // aliased the same jweak instead.
      jobject strong = env->NewLocalRef(s.sample_source);
      if (strong != nullptr) {
        _klass_population[slot].representative = env->NewWeakGlobalRef(strong);
        env->DeleteLocalRef(strong);
      }
      // else: this epoch's surviving instance for this klass died before we
      // could mint a representative for it - the entry is left with
      // representative == nullptr for this epoch and retried on the next one
      // (see the retry condition's own comment above).
    }
  }
  _klass_count_scratch_size = 0;
}

bool LivenessTracker::computeKlassPopulationSlope(const KlassPopulationEntry &entry,
                                                   double *out_slope) const {
  if (entry.ring_fill < KLASS_POPULATION_MIN_FILL_FOR_TREND) {
    return false;
  }

  // Chronological (oldest-first) index of count_ring[0] within the entry's
  // currently-filled window: while the ring hasn't wrapped yet
  // (ring_fill < KLASS_POPULATION_RING_SIZE), ring_head == ring_fill and the
  // oldest sample sits at physical index 0; once wrapped, ring_head is
  // exactly the oldest (next-to-be-overwritten) slot. Both cases collapse to
  // the same modular formula.
  int start = (entry.ring_head - entry.ring_fill + KLASS_POPULATION_RING_SIZE) %
              KLASS_POPULATION_RING_SIZE;
  // Integer division deliberately drops the remainder into an untouched
  // middle third when ring_fill isn't a multiple of 3 - "earliest third vs
  // recent third" is already a cheap approximation (design doc's own
  // rationale for not using least-squares), so this extra imprecision is
  // consistent with that choice rather than a bug to round away.
  int third = entry.ring_fill / 3;

  double earliest_sum = 0;
  for (int i = 0; i < third; i++) {
    earliest_sum += entry.count_ring[(start + i) % KLASS_POPULATION_RING_SIZE];
  }
  double recent_sum = 0;
  for (int i = entry.ring_fill - third; i < entry.ring_fill; i++) {
    recent_sum += entry.count_ring[(start + i) % KLASS_POPULATION_RING_SIZE];
  }

  *out_slope = (recent_sum / third) - (earliest_sum / third);
  return true;
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
    double slope;
    bool has_trend = computeKlassPopulationSlope(entry, &slope);
    TEST_LOG("LivenessTracker::selectLeakCandidates entry[%d] klass_id=%u ring_fill=%u "
             "has_trend=%d slope=%f representative=%p",
             i, entry.klass_id, entry.ring_fill, has_trend, has_trend ? slope : 0.0,
             (void *)entry.representative);
    if (!has_trend || slope <= 0) {
      // Not enough history yet, or flat/shrinking - design doc: "Keep only
      // entries with positive slope".
      continue;
    }
    if (count == cap && slope <= best_slopes[cap - 1]) {
      // Already holding `cap` stronger (or equal) candidates - this one
      // doesn't make the cut.
      continue;
    }

    int pos = count < cap ? count++ : cap - 1;
    best_slopes[pos] = slope;
    out[pos] = KlassCandidate{entry.klass_id, entry.representative};
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

  return count;
}

jobject LivenessTracker::resolveCandidateRepresentative(JNIEnv *env, u32 klass_id) {
  // Shared lock excludes cleanup_table()'s exclusive lock (the only writer,
  // and the only place that can DeleteWeakGlobalRef() an entry's
  // representative via foldKlassCountsLocked()'s eviction path above) for
  // the whole lookup+resolve, so the value NewLocalRef() runs on here is
  // always the table's current one for klass_id, never a snapshot that
  // eviction could have invalidated in the meantime - see
  // selectLeakCandidates()'s own comment for the race this closes.
  _table_lock.lockShared();
  jobject obj = nullptr;
  for (int i = 0; i < _klass_population_size; i++) {
    if (_klass_population[i].klass_id == klass_id) {
      if (_klass_population[i].representative != nullptr) {
        obj = env->NewLocalRef(_klass_population[i].representative);
      }
      break;
    }
  }
  _table_lock.unlockShared();
  return obj;
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
    bool isLastGc = HeapUsage::isLastGCUsageSupported();
    size_t used = isLastGc ? HeapUsage::get()._used_at_last_gc
                           : loadAcquire(_used_after_last_gc);
    if (used == 0) {
      used = HeapUsage::get()._used;
      isLastGc = false;
    }
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
  if (!_enabled) {
    // disabled
    return Error::OK;
  }
  
  // Self-register with the profiler for liveness checking
  Profiler::instance()->registerLivenessChecker([this](std::unordered_set<u64>& buffer) {
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
  _gc_generations = args._gc_generations;

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

// File-scope (not track()-local) so releaseThreadLocalState() below can
// reach them from Profiler::onThreadEnd(). Relying solely on these
// ThreadLocal's own pthread-key destructors (create_mt19937/free_mt19937
// etc.) is not sufficient: pthread key destructors only fire when the
// underlying OS thread actually exits, not when a JNI-attached thread
// detaches via DetachCurrentThread. A reused pooled OS thread that
// repeatedly attaches/detaches would otherwise leak one mt19937 and one
// uniform_real_distribution allocation per attach cycle, since get() lazily
// re-creates the value on the next track() call but nothing ever frees the
// previous one until OS thread exit (which may never happen for a
// long-lived pooled thread). Hooking explicit cleanup into onThreadEnd
// matches how every other per-thread profiler state (CPU/wall engine
// registration, ProfiledThread) is already torn down.
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
  if (!_enabled || !_gc_generations) {
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
  LivenessTracker::instance()->onGC();
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
}

void LivenessTracker::getLiveTraceIds(std::unordered_set<u64>& out_buffer) {
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
