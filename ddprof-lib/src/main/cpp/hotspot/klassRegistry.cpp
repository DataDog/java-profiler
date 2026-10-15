/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "hotspot/klassRegistry.h"

#include <stdlib.h>

static inline size_t slotFor(const void* klass, size_t capacity) {
  // Klass* is at least 8-byte aligned; drop the always-zero bits before mixing.
  uint64_t h = ((uintptr_t)klass >> 3) * 0x9E3779B97F4A7C15ULL;
  return (size_t)(h >> 32) & (capacity - 1);
}

// Linear probing. Returns the slot holding `klass`, or the empty slot where it
// would go. The table is never full (rehash() keeps the load factor <= 3/4),
// so the probe always terminates.
KlassRegistry::Entry* KlassRegistry::find(const void* klass) const {
  size_t i = slotFor(klass, _capacity);
  while (_table[i].klass != nullptr && _table[i].klass != klass) {
    i = (i + 1) & (_capacity - 1);
  }
  return &_table[i];
}

// Called with _lock held. The release store pairs with epoch()'s acquire
// load: a thread that runs a method of a class registered here, and then
// samples it, observes at least the epoch that class was registered at.
uint32_t KlassRegistry::bumpEpoch() {
  uint32_t next = _epoch + 1;
  __atomic_store_n(&_epoch, next, __ATOMIC_RELEASE);
  return next;
}

// Moves the live entries into a table sized for them and deletes the weak
// references of dead ones. Two passes so the old table stays intact if the
// allocation fails: liveness is only counted in the first, and an entry that
// dies between the passes is just carried over and purged next time.
bool KlassRegistry::rehash(JNIEnv* jni) {
  size_t live = 0;
  for (size_t i = 0; i < _capacity; i++) {
    if (_table[i].klass != nullptr && !jni->IsSameObject(_table[i].mirror, nullptr)) {
      live++;
    }
  }

  size_t capacity = INITIAL_CAPACITY;
  while (capacity < (live + 1) * 2) {
    capacity <<= 1;
  }
  Entry* table = (Entry*)calloc(capacity, sizeof(Entry));
  if (table == nullptr) {
    return false;
  }

  Entry* old_table = _table;
  size_t old_capacity = _capacity;
  _table = table;
  _capacity = capacity;
  _size = 0;
  bool purged = false;
  for (size_t i = 0; i < old_capacity; i++) {
    Entry& e = old_table[i];
    if (e.klass == nullptr) {
      continue;
    }
    if (jni->IsSameObject(e.mirror, nullptr)) {
      jni->DeleteWeakGlobalRef(e.mirror);
      purged = true;
    } else {
      *find(e.klass) = e;
      _size++;
    }
  }
  free(old_table);
  if (purged) {
    // A purged address may be handed to a new class whose add() then looks
    // like a first insert; frames of the purged class must stay older.
    bumpEpoch();
  }
  return true;
}

bool KlassRegistry::add(JNIEnv* jni, const void* klass, jclass mirror) {
  if (klass == nullptr || mirror == nullptr) {
    return false;
  }
  MutexLocker ml(_lock);

  if (_capacity != 0) {
    Entry* e = find(klass);
    if (e->klass == klass) {
      if (jni->IsSameObject(e->mirror, mirror)) {
        return true;
      }
      jweak ref = jni->NewWeakGlobalRef(mirror);
      if (ref == nullptr) {
        return false;
      }
      jni->DeleteWeakGlobalRef(e->mirror);
      e->mirror = ref;
      // A different class now lives at this address; frames sampled from the
      // previous one must not match it.
      e->epoch = bumpEpoch();
      return true;
    }
  }

  if ((_size + 1) * 4 > _capacity * 3 && !rehash(jni)) {
    return false;
  }
  jweak ref = jni->NewWeakGlobalRef(mirror);
  if (ref == nullptr) {
    return false;
  }
  Entry* e = find(klass);
  e->klass = klass;
  e->mirror = ref;
  e->epoch = _epoch;
  _size++;
  return true;
}

jclass KlassRegistry::pin(JNIEnv* jni, const void* klass, uint32_t sampled_epoch, bool* stale) {
  if (stale != nullptr) {
    *stale = false;
  }
  if (klass == nullptr) {
    return nullptr;
  }
  MutexLocker ml(_lock);
  if (_capacity == 0) {
    return nullptr;
  }
  Entry* e = find(klass);
  if (e->klass != klass) {
    return nullptr;
  }
  // Serial-number comparison: the frame is at least as new as the entry iff
  // (sampled - registered) mod 2^EPOCH_BITS lies in the lower half.
  const uint32_t mask = (1u << EPOCH_BITS) - 1;
  if (((sampled_epoch - e->epoch) & mask) >= (1u << (EPOCH_BITS - 1))) {
    if (stale != nullptr) {
      *stale = true;
    }
    return nullptr;
  }
  // NewLocalRef on a weak global reference returns NULL once the referent has
  // been collected. Done under the lock so a concurrent rehash() cannot delete
  // the weak reference out from under the call.
  return (jclass)jni->NewLocalRef(e->mirror);
}

size_t KlassRegistry::size() {
  MutexLocker ml(_lock);
  return _size;
}

void KlassRegistry::clear(JNIEnv* jni) {
  MutexLocker ml(_lock);
  for (size_t i = 0; i < _capacity; i++) {
    if (_table[i].klass != nullptr) {
      jni->DeleteWeakGlobalRef(_table[i].mirror);
    }
  }
  free(_table);
  _table = nullptr;
  _capacity = 0;
  _size = 0;
}
