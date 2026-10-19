/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "hotspot/unloadCapture.h"

#include "common.h"
#include "counters.h"
#include "hotspot/hotspotSupport.h"
#include "hotspot/vmStructs.h"
#include "os.h"
#include "safeAccess.h"
#include "spinLock.h"
#include "vmEntry.h"

#include <pthread.h>
#include <time.h>

#include <stdlib.h>
#include <string.h>
#include <unordered_map>

bool UnloadCapture::_enabled = false;
bool UnloadCapture::_gc_hook = false;

namespace {

// (Method*, tag) pairs, filled by the sampler. A slot is claimed by a CAS on
// `method`, then published by storing `tag` and setting `state` to PENDING.
// A drainer moves PENDING -> DRAINING by CAS, so the GC hook and the
// background drain never both take a pair. A pair that has been captured
// stays in its slot as DONE, so the sampler does not add it again; endDump()
// clears DONE slots, so a method is captured at most once per dump interval.
enum SlotState : uint32_t { SLOT_FREE = 0, SLOT_PENDING = 1, SLOT_DRAINING = 2, SLOT_DONE = 3 };
struct PendingSlot {
  volatile uintptr_t method;
  volatile uint32_t tag;
  volatile uint32_t state;
};

const size_t PENDING_CAPACITY = 16384;  // power of two
const size_t PENDING_PROBES = 16;
PendingSlot pending[PENDING_CAPACITY];
volatile int pending_count = 0;

// ClassLoaderData of the boot, platform and application loaders, whose
// classes are never unloaded. Filled from registerClass().
const size_t MAX_PERMANENT_CLDS = 4;
const void* volatile permanent_clds[MAX_PERMANENT_CLDS];

struct Key {
  const void* method;
  uint32_t tag;
  bool operator==(const Key& o) const { return method == o.method && tag == o.tag; }
};
struct KeyHash {
  size_t operator()(const Key& k) const {
    return std::hash<const void*>()(k.method) ^ ((size_t)k.tag * 0x9E3779B97F4A7C15ULL);
  }
};

// Captured names, written by the GC hook, taken by the dump thread.
SpinLock cache_lock;
std::unordered_map<Key, UnloadCapture::Entry, KeyHash>* cache = nullptr;
const size_t MAX_CACHE_ENTRIES = 65536;
volatile uint64_t generation = 0;

inline size_t slotIndex(const void* method, uint32_t tag) {
  uintptr_t h = (uintptr_t)method * 0x9E3779B97F4A7C15ULL ^ ((uintptr_t)tag << 7);
  return (size_t)(h >> 17) & (PENDING_CAPACITY - 1);
}

bool isPermanent(const void* cld) {
  for (size_t i = 0; i < MAX_PERMANENT_CLDS; i++) {
    const void* p = __atomic_load_n(&permanent_clds[i], __ATOMIC_ACQUIRE);
    if (p == nullptr) {
      return false;
    }
    if (p == cld) {
      return true;
    }
  }
  return false;
}

char* dupString(const char* s) {
  size_t len = strlen(s);
  char* d = (char*)malloc(len + 1);
  if (d != nullptr) {
    memcpy(d, s, len + 1);
  }
  return d;
}


// Takes a PENDING pair for draining; the caller then calls finishSlot().
bool claimSlot(PendingSlot* s, uintptr_t* method, uint32_t* tag) {
  uint32_t expected = SLOT_PENDING;
  if (!__atomic_compare_exchange_n(&s->state, &expected, (uint32_t)SLOT_DRAINING, false,
                                   __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)) {
    return false;
  }
  *method = __atomic_load_n(&s->method, __ATOMIC_ACQUIRE);
  *tag = __atomic_load_n(&s->tag, __ATOMIC_ACQUIRE);
  __atomic_fetch_sub(&pending_count, 1, __ATOMIC_ACQ_REL);
  return true;
}

// Frees a slot its owner (state DRAINING) is done with. State first: a
// sampler that still sees the method treats a FREE state as an insert in
// progress and probes on.
void clearSlot(PendingSlot* s) {
  __atomic_store_n(&s->state, (uint32_t)SLOT_FREE, __ATOMIC_RELEASE);
  __atomic_store_n(&s->tag, 0, __ATOMIC_RELEASE);
  __atomic_store_n(&s->method, 0, __ATOMIC_RELEASE);
}

// Ends a drain of a claimed slot: DONE if the pair is in the cache, so the
// sampler skips it until endDump(); freed otherwise, so a later sample can
// retry it.
void finishSlot(PendingSlot* s, bool in_cache) {
  if (in_cache) {
    __atomic_store_n(&s->state, (uint32_t)SLOT_DONE, __ATOMIC_RELEASE);
  } else {
    clearSlot(s);
  }
}

UnloadCapture::Entry makeEntry(ResolvedMethod& resolved, uint64_t gen, bool* ok) {
  UnloadCapture::Entry e;
  e.klass_name = dupString(resolved.klassName());
  e.method_name = dupString(resolved.methodName());
  e.signature = dupString(resolved.methodSignature());
  e.is_thread_run = resolved.isThreadRun();
  e.line_table = resolved.takeLineNumberTable(&e.line_table_size);
  e.generation = gen;
  *ok = e.klass_name != nullptr && e.method_name != nullptr && e.signature != nullptr;
  return e;
}

void updateMax(CounterId id, long long value) {
  if (value > Counters::getCounter(id)) {
    Counters::set(id, value);
  }
}

volatile bool bg_running = false;
u64 bg_interval_ns = 100 * 1000 * 1000ULL;

// Background drain: every bg_interval_ns, resolves the pending pairs the way
// the dump does (registry pin + trace-ID check + containsMethod + readMethod),
// outside any pause. cache_lock is held only around cache lookups and
// inserts, never across the JNI pin, so neither the GC hook nor the dump
// waits behind a resolution.
void* bgThreadEntry(void*) {
  JNIEnv* jni = VM::attachThread("java-profiler UnloadCapture");
  if (jni == nullptr) {
    return nullptr;
  }
  ProfiledThread* prof_thread = ProfiledThread::initCurrentThreadSignalSafe();
  while (__atomic_load_n(&bg_running, __ATOMIC_ACQUIRE)) {
    OS::sleep(bg_interval_ns);
    if (prof_thread == nullptr || __atomic_load_n(&pending_count, __ATOMIC_ACQUIRE) == 0) {
      continue;
    }
    u64 start = OS::nanotime();
    struct timespec cpu_start;
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &cpu_start);
    Counters::increment(UNLOAD_CAPTURE_BG_PASSES);
    for (size_t i = 0; i < PENDING_CAPACITY; i++) {
      uintptr_t m;
      uint32_t tag;
      PendingSlot* s = &pending[i];
      if (!claimSlot(s, &m, &tag)) {
        continue;
      }
      Key key{(const void*)m, tag};
      cache_lock.lock();
      bool known = cache->find(key) != cache->end();
      bool full = cache->size() >= MAX_CACHE_ENTRIES;
      cache_lock.unlock();
      if (known || full) {
        if (full) {
          Counters::increment(UNLOAD_CAPTURE_CACHE_FULL);
        }
        finishSlot(s, known);
        continue;
      }
      ResolvedMethod resolved;
      if (!HotspotSupport::capturePinned(prof_thread, (const void*)m, tag, resolved)) {
        Counters::increment(UNLOAD_CAPTURE_BG_REFUSED);
        finishSlot(s, false);
        continue;
      }
      bool ok;
      UnloadCapture::Entry e = makeEntry(resolved, __atomic_load_n(&generation, __ATOMIC_ACQUIRE), &ok);
      if (!ok) {
        UnloadCapture::freeEntry(e);
        finishSlot(s, false);
        continue;
      }
      cache_lock.lock();
      bool inserted = cache->emplace(key, e).second;
      cache_lock.unlock();
      finishSlot(s, true);
      if (!inserted) {
        UnloadCapture::freeEntry(e);  // the GC hook got there first
        continue;
      }
      Counters::increment(UNLOAD_CAPTURE_BG_CAPTURED);
    }
    long long elapsed = (long long)(OS::nanotime() - start);
    Counters::increment(UNLOAD_CAPTURE_BG_NS, elapsed);
    struct timespec cpu_end;
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &cpu_end);
    Counters::increment(UNLOAD_CAPTURE_BG_CPU_NS,
                        (long long)(cpu_end.tv_sec - cpu_start.tv_sec) * 1000000000LL +
                            (cpu_end.tv_nsec - cpu_start.tv_nsec));
    updateMax(UNLOAD_CAPTURE_BG_MAX_NS, elapsed);
  }
  VM::detachThread();
  return nullptr;
}

} // namespace

void UnloadCapture::init(jvmtiEnv* jvmti) {
  // 1: GC hook only; 2: background drain + GC hook; 3: background drain only.
  const char* env = getenv("DDPROF_CAPTURE_UNLOADING");
  int mode = env != nullptr ? atoi(env) : 0;
  _enabled = mode >= 1 && mode <= 3;
  if (!_enabled) {
    return;
  }
  _gc_hook = mode != 3;
  TEST_LOG("UnloadCapture mode %d", mode);
  if (cache == nullptr) {
    cache = new std::unordered_map<Key, Entry, KeyHash>();
  }
  if (_gc_hook) {
    jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_GARBAGE_COLLECTION_START, nullptr);
  }
  const char* interval = getenv("DDPROF_CAPTURE_INTERVAL_MS");
  if (interval != nullptr && atoi(interval) > 0) {
    bg_interval_ns = (u64)atoi(interval) * 1000 * 1000;
  }
  // PROTOTYPE: started once and never stopped; it is a daemon thread.
  if (mode >= 2 && !__atomic_exchange_n(&bg_running, true, __ATOMIC_ACQ_REL)) {
    pthread_t thread;
    if (pthread_create(&thread, nullptr, bgThreadEntry, nullptr) != 0) {
      __atomic_store_n(&bg_running, false, __ATOMIC_RELEASE);
    } else {
      pthread_detach(thread);
    }
  }
}

void UnloadCapture::notePermanentLoaderData(const void* cld) {
  if (cld == nullptr) {
    return;
  }
  for (size_t i = 0; i < MAX_PERMANENT_CLDS; i++) {
    const void* expected = nullptr;
    if (__atomic_compare_exchange_n(&permanent_clds[i], &expected, cld, false,
                                    __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)) {
      return;
    }
    if (expected == cld) {
      return;
    }
  }
}

void UnloadCapture::onRawFrame(const void* method, const void* holder, uint32_t tag) {
  if (!_enabled || holder == nullptr || VMStructs::class_loader_data_offset() < 0) {
    return;
  }
  const void* cld = SafeAccess::load((void**)((const char*)holder + VMStructs::class_loader_data_offset()));
  if (cld == nullptr || isPermanent(cld)) {
    return;
  }
  size_t index = slotIndex(method, tag);
  for (size_t i = 0; i < PENDING_PROBES; i++) {
    PendingSlot* s = &pending[(index + i) & (PENDING_CAPACITY - 1)];
    uintptr_t m = __atomic_load_n(&s->method, __ATOMIC_ACQUIRE);
    if (m == 0) {
      uintptr_t expected = 0;
      if (__atomic_compare_exchange_n(&s->method, &expected, (uintptr_t)method, false,
                                      __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)) {
        __atomic_store_n(&s->tag, tag, __ATOMIC_RELEASE);
        __atomic_fetch_add(&pending_count, 1, __ATOMIC_RELEASE);
        __atomic_store_n(&s->state, (uint32_t)SLOT_PENDING, __ATOMIC_RELEASE);
        Counters::increment(UNLOAD_CAPTURE_PENDING_ADDED);
        return;
      }
      m = expected;
    }
    // A published slot (state not FREE) with the same pair is pending, being
    // drained, or already captured: nothing to do.
    if (m == (uintptr_t)method && __atomic_load_n(&s->state, __ATOMIC_ACQUIRE) != SLOT_FREE &&
        __atomic_load_n(&s->tag, __ATOMIC_ACQUIRE) == tag) {
      return;
    }
  }
  // No free slot. DONE slots only keep the sampler from adding a captured
  // pair again, so take one over rather than drop this pair.
  for (size_t i = 0; i < PENDING_PROBES; i++) {
    PendingSlot* s = &pending[(index + i) & (PENDING_CAPACITY - 1)];
    uint32_t expected = SLOT_DONE;
    if (__atomic_compare_exchange_n(&s->state, &expected, (uint32_t)SLOT_DRAINING, false,
                                    __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)) {
      // Tag before method: a sampler that sees the new method sees its tag.
      __atomic_store_n(&s->tag, tag, __ATOMIC_RELEASE);
      __atomic_store_n(&s->method, (uintptr_t)method, __ATOMIC_RELEASE);
      __atomic_fetch_add(&pending_count, 1, __ATOMIC_RELEASE);
      __atomic_store_n(&s->state, (uint32_t)SLOT_PENDING, __ATOMIC_RELEASE);
      Counters::increment(UNLOAD_CAPTURE_PENDING_ADDED);
      Counters::increment(UNLOAD_CAPTURE_PENDING_EVICTED);
      return;
    }
  }
  Counters::increment(UNLOAD_CAPTURE_PENDING_OVERFLOW);
}

void JNICALL UnloadCapture::GarbageCollectionStart(jvmtiEnv* jvmti) {
  if (!_enabled || !_gc_hook || __atomic_load_n(&pending_count, __ATOMIC_ACQUIRE) == 0) {
    return;
  }
  u64 start = OS::nanotime();
  Counters::increment(UNLOAD_CAPTURE_HOOK_CALLS);
  if (!cache_lock.tryLock()) {
    // The dump thread or the background drain holds the cache; the pairs
    // stay pending.
    Counters::increment(UNLOAD_CAPTURE_HOOK_BUSY);
    return;
  }
  // A JVMTI callback, so initCurrentThreadSignalSafe() (AGENTS.md). The GC
  // callbacks run on the VM thread, which keeps its ProfiledThread afterwards.
  ProfiledThread* prof_thread = ProfiledThread::initCurrentThreadSignalSafe();
  if (prof_thread == nullptr) {
    Counters::increment(SAMPLES_DROPPED_THREAD_LOCAL);
    cache_lock.unlock();
    return;
  }
  uint64_t gen = __atomic_load_n(&generation, __ATOMIC_ACQUIRE);
  for (size_t i = 0; i < PENDING_CAPACITY; i++) {
    uintptr_t m;
    uint32_t tag;
    PendingSlot* s = &pending[i];
    if (!claimSlot(s, &m, &tag)) {
      continue;
    }
    Counters::increment(UNLOAD_CAPTURE_HOOK_DRAINED);
    Key key{(const void*)m, tag};
    if (cache->find(key) != cache->end()) {
      finishSlot(s, true);
      continue;
    }
    if (cache->size() >= MAX_CACHE_ENTRIES) {
      Counters::increment(UNLOAD_CAPTURE_CACHE_FULL);
      finishSlot(s, false);
      continue;
    }
    ResolvedMethod resolved;
    if (!HotspotSupport::captureMethod(prof_thread, (const void*)m, tag, resolved)) {
      Counters::increment(UNLOAD_CAPTURE_REFUSED);
      finishSlot(s, false);
      continue;
    }
    bool ok;
    Entry e = makeEntry(resolved, gen, &ok);
    if (!ok) {
      freeEntry(e);
      finishSlot(s, false);
      continue;
    }
    cache->emplace(key, e);
    finishSlot(s, true);
    Counters::increment(UNLOAD_CAPTURE_CAPTURED);
  }
  cache_lock.unlock();
  long long elapsed = (long long)(OS::nanotime() - start);
  Counters::increment(UNLOAD_CAPTURE_HOOK_NS, elapsed);
  updateMax(UNLOAD_CAPTURE_HOOK_MAX_NS, elapsed);
}

bool UnloadCapture::take(const void* method, uint32_t tag, Entry* out) {
  if (!_enabled || cache == nullptr) {
    return false;
  }
  cache_lock.lock();
  auto it = cache->find(Key{method, tag});
  bool found = it != cache->end();
  if (found) {
    *out = it->second;
    cache->erase(it);
  }
  cache_lock.unlock();
  return found;
}

void UnloadCapture::endDump() {
  if (!_enabled || cache == nullptr) {
    return;
  }
  cache_lock.lock();
  uint64_t gen = __atomic_load_n(&generation, __ATOMIC_ACQUIRE);
  for (auto it = cache->begin(); it != cache->end();) {
    if (it->second.generation < gen) {
      freeEntry(it->second);
      it = cache->erase(it);
    } else {
      ++it;
    }
  }
  __atomic_store_n(&generation, gen + 1, __ATOMIC_RELEASE);
  cache_lock.unlock();
  // Lets the sampler add this interval's methods again, so the next interval
  // gets fresh entries for classes that are still loaded.
  for (size_t i = 0; i < PENDING_CAPACITY; i++) {
    uint32_t expected = SLOT_DONE;
    if (__atomic_compare_exchange_n(&pending[i].state, &expected, (uint32_t)SLOT_DRAINING, false,
                                    __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)) {
      clearSlot(&pending[i]);
    }
  }
}

void UnloadCapture::freeEntry(Entry& e) {
  free(e.klass_name);
  free(e.method_name);
  free(e.signature);
  free(e.line_table);
  e.klass_name = e.method_name = e.signature = nullptr;
  e.line_table = nullptr;
}
