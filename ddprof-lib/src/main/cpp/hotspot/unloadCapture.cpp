/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "hotspot/unloadCapture.h"

#include "counters.h"
#include "hotspot/hotspotSupport.h"
#include "hotspot/vmStructs.h"
#include "os.h"
#include "safeAccess.h"
#include "spinLock.h"

#include <stdlib.h>
#include <string.h>
#include <unordered_map>

bool UnloadCapture::_enabled = false;

namespace {

// Pending (Method*, tag) pairs, filled by the sampler. A slot is claimed by a
// CAS on `method`, then published by storing a non-zero `tag` (lazy tags
// always have HotspotSupport::TRACE_ID_TAG set).
struct PendingSlot {
  volatile uintptr_t method;
  volatile uint32_t tag;
};

const size_t PENDING_CAPACITY = 8192;  // power of two
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

} // namespace

void UnloadCapture::init(jvmtiEnv* jvmti) {
  const char* env = getenv("DDPROF_CAPTURE_UNLOADING");
  _enabled = env != nullptr && strcmp(env, "1") == 0;
  if (!_enabled) {
    return;
  }
  if (cache == nullptr) {
    cache = new std::unordered_map<Key, Entry, KeyHash>();
  }
  jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_GARBAGE_COLLECTION_START, nullptr);
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
    if (m == (uintptr_t)method) {
      if (__atomic_load_n(&s->tag, __ATOMIC_ACQUIRE) == tag) {
        return;  // already pending
      }
      continue;
    }
    if (m == 0) {
      uintptr_t expected = 0;
      if (__atomic_compare_exchange_n(&s->method, &expected, (uintptr_t)method, false,
                                      __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)) {
        __atomic_store_n(&s->tag, tag, __ATOMIC_RELEASE);
        __atomic_fetch_add(&pending_count, 1, __ATOMIC_RELEASE);
        Counters::increment(UNLOAD_CAPTURE_PENDING_ADDED);
        return;
      }
      if (expected == (uintptr_t)method && __atomic_load_n(&s->tag, __ATOMIC_ACQUIRE) == tag) {
        return;
      }
    }
  }
  Counters::increment(UNLOAD_CAPTURE_PENDING_OVERFLOW);
}

void JNICALL UnloadCapture::GarbageCollectionStart(jvmtiEnv* jvmti) {
  if (!_enabled || __atomic_load_n(&pending_count, __ATOMIC_ACQUIRE) == 0) {
    return;
  }
  u64 start = OS::nanotime();
  Counters::increment(UNLOAD_CAPTURE_HOOK_CALLS);
  if (!cache_lock.tryLock()) {
    // The dump thread is reading the cache; the pairs stay pending.
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
    PendingSlot* s = &pending[i];
    uintptr_t m = __atomic_load_n(&s->method, __ATOMIC_ACQUIRE);
    if (m == 0) {
      continue;
    }
    uint32_t tag = __atomic_load_n(&s->tag, __ATOMIC_ACQUIRE);
    if (tag == 0) {
      continue;  // being inserted; the next GC sees it
    }
    __atomic_store_n(&s->tag, 0, __ATOMIC_RELEASE);
    __atomic_store_n(&s->method, 0, __ATOMIC_RELEASE);
    __atomic_fetch_sub(&pending_count, 1, __ATOMIC_ACQ_REL);

    Key key{(const void*)m, tag};
    if (cache->find(key) != cache->end()) {
      continue;
    }
    if (cache->size() >= MAX_CACHE_ENTRIES) {
      Counters::increment(UNLOAD_CAPTURE_CACHE_FULL);
      continue;
    }
    ResolvedMethod resolved;
    if (!HotspotSupport::captureMethod(prof_thread, (const void*)m, tag, resolved)) {
      Counters::increment(UNLOAD_CAPTURE_REFUSED);
      continue;
    }
    Entry e;
    e.klass_name = dupString(resolved.klassName());
    e.method_name = dupString(resolved.methodName());
    e.signature = dupString(resolved.methodSignature());
    e.is_thread_run = resolved.isThreadRun();
    e.line_table = resolved.takeLineNumberTable(&e.line_table_size);
    e.generation = gen;
    if (e.klass_name == nullptr || e.method_name == nullptr || e.signature == nullptr) {
      freeEntry(e);
      continue;
    }
    cache->emplace(key, e);
    Counters::increment(UNLOAD_CAPTURE_CAPTURED);
  }
  cache_lock.unlock();
  u64 elapsed = OS::nanotime() - start;
  Counters::increment(UNLOAD_CAPTURE_HOOK_NS, (long long)elapsed);
  long long max = Counters::getCounter(UNLOAD_CAPTURE_HOOK_MAX_NS);
  if ((long long)elapsed > max) {
    Counters::set(UNLOAD_CAPTURE_HOOK_MAX_NS, (long long)elapsed);
  }
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
}

void UnloadCapture::freeEntry(Entry& e) {
  free(e.klass_name);
  free(e.method_name);
  free(e.signature);
  free(e.line_table);
  e.klass_name = e.method_name = e.signature = nullptr;
  e.line_table = nullptr;
}
