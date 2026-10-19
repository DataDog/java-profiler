/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "hotspot/klassRegistry.h"

#include "counters.h"

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

// Called with _lock held. The entry registered for `klass`, or nullptr.
KlassRegistry::Entry* KlassRegistry::findRegistered(const void* klass) const {
  if (klass == nullptr || _capacity == 0) {
    return nullptr;
  }
  Entry* e = find(klass);
  return e->klass == klass ? e : nullptr;
}

// Moves the live entries into a table sized for them and deletes the weak
// references of dead ones. Two passes so the old table stays intact if the
// allocation fails: the first only counts live entries to size the new
// table, the second checks liveness again and drops whatever is dead by then,
// so an entry that died in between is purged too.
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
  size_t old_size = _size;
  _table = table;
  _capacity = capacity;
  _size = 0;
  for (size_t i = 0; i < old_capacity; i++) {
    Entry& e = old_table[i];
    if (e.klass == nullptr) {
      continue;
    }
    if (jni->IsSameObject(e.mirror, nullptr)) {
      jni->DeleteWeakGlobalRef(e.mirror);
    } else {
      *find(e.klass) = e;
      _size++;
    }
  }
  free(old_table);
  Counters::increment(KLASS_REGISTRY_PURGED, (long long)(old_size - _size));
  publishLocked();
  return true;
}

void KlassRegistry::publishLocked() {
  Counters::set(KLASS_REGISTRY_CAPACITY, (long long)_capacity);
  Counters::set(KLASS_REGISTRY_ENTRIES, (long long)_size);
}

void KlassRegistry::publishCounters() {
  MutexLocker ml(_lock);
  publishLocked();
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
      // A different class now lives at this address; the previous one's
      // redefinition state does not carry over.
      e->redefinitions_in_progress = 0;
      e->redefined = false;
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
  e->redefinitions_in_progress = 0;
  e->redefined = false;
  _size++;
  publishLocked();
  return true;
}

jclass KlassRegistry::pin(JNIEnv* jni, const void* klass, PinStatus* status) {
  PinStatus local_status;
  if (status == nullptr) {
    status = &local_status;
  }
  *status = PIN_ABSENT;
  MutexLocker ml(_lock);
  Entry* e = findRegistered(klass);
  if (e == nullptr) {
    return nullptr;
  }
  if (e->redefined || e->redefinitions_in_progress > 0) {
    *status = PIN_REDEFINED;
    return nullptr;
  }
  // NewLocalRef on a weak global reference returns NULL once the referent has
  // been collected. Done under the lock so a concurrent rehash() cannot delete
  // the weak reference out from under the call.
  jclass ref = (jclass)jni->NewLocalRef(e->mirror);
  if (ref != nullptr) {
    *status = PIN_OK;
  }
  return ref;
}

bool KlassRegistry::beginRedefinition(const void* klass) {
  MutexLocker ml(_lock);
  Entry* e = findRegistered(klass);
  if (e == nullptr) {
    return false;
  }
  e->redefinitions_in_progress++;
  return true;
}

void KlassRegistry::endRedefinition(const void* klass, bool succeeded) {
  MutexLocker ml(_lock);
  Entry* e = findRegistered(klass);
  if (e == nullptr) {
    return;
  }
  // Clamped: the entry may have been replaced (a new class at this address)
  // while the call was in progress, which resets the count.
  if (e->redefinitions_in_progress > 0) {
    e->redefinitions_in_progress--;
  }
  if (succeeded) {
    e->redefined = true;
  }
}

bool KlassRegistry::isRedefined(const void* klass) {
  MutexLocker ml(_lock);
  Entry* e = findRegistered(klass);
  return e != nullptr && (e->redefined || e->redefinitions_in_progress > 0);
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
  publishLocked();
}
