/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_KLASSREGISTRY_H
#define _HOTSPOT_KLASSREGISTRY_H

#include "common.h"
#include "mutex.h"

#include <jni.h>
#include <stddef.h>
#include <stdint.h>

/**
 * Redefinition marks for fjmethodid=lazy, keyed by Klass*: which classes are
 * being, or have been, redefined.
 *
 * A redefined class stays alive, but its old methods array and old Method*s
 * are freed once no longer on any stack, and later allocations -- including
 * another redefinition of the same class -- can reuse them. So the
 * RedefineClasses/RetransformClasses hooks call beginRedefinition() before
 * every redefinition and endRedefinition() after it, and the dump refuses raw
 * frames of a class while one is in progress, and for good once one has
 * succeeded. (After a successful redefinition the class's jmethodIDs are
 * preloaded, so its later frames are not raw.) A failed call leaves the
 * methods untouched, and the class as it was.
 *
 * Only classes passed to a redefinition call are added, including calls
 * that JVMTI then rejects; such an entry has no mark. Each entry holds a JNI weak global
 * reference to the class's mirror, so a mark is only reported while that
 * class is alive: once it is unloaded, a new class at the same Klass* address
 * does not inherit it, and if that class is redefined too, its add()
 * replaces the entry. Dead
 * entries are purged whenever the table would have to grow.
 *
 * All operations take an internal mutex and call JNI, so none of them may be
 * used from a signal handler.
 */
// The home slot of `klass` in an open-addressing table of `capacity` (a power
// of two) slots, probed linearly from there. Shared by KlassRegistry and the
// per-dump class set in HotspotSupport, whose inserts and lookups must agree.
static inline size_t klassSlot(const void* klass, size_t capacity) {
  // Klass* is at least 8-byte aligned; drop the always-zero bits before mixing.
  uint64_t h = ((uintptr_t)klass >> 3) * KNUTH_MULTIPLICATIVE_CONSTANT;
  return (size_t)(h >> 32) & (capacity - 1);
}

class KlassRegistry {
  struct Entry {
    const void* klass;
    jweak mirror;
    uint32_t redefinitions_in_progress;
    bool redefined;  // a redefinition succeeded; never reset
  };

  static const size_t INITIAL_CAPACITY = 1024;

  Mutex _lock;
  Entry* _table;
  size_t _capacity;  // Power of two, or 0 before the first add()
  size_t _size;      // Occupied slots, live or dead

  Entry* find(const void* klass) const;
  Entry* findRegistered(const void* klass) const;
  bool rehash(JNIEnv* jni);
  void publishLocked();

public:
  KlassRegistry() : _table(nullptr), _capacity(0), _size(0) {}

  KlassRegistry(const KlassRegistry&) = delete;
  KlassRegistry& operator=(const KlassRegistry&) = delete;

  /**
   * Records that `klass` is the Klass* of `mirror`. Re-adding the same pair is
   * a no-op; adding a different mirror for a known Klass* replaces the entry.
   * Returns false if the weak reference or the table could not be allocated.
   */
  bool add(JNIEnv* jni, const void* klass, jclass mirror);

  /** Whether `klass` is registered and its class is still alive. */
  bool contains(JNIEnv* jni, const void* klass);

  /**
   * Call before a redefinition of `klass` starts, so that a resolution which
   * validated the class's metadata just before the methods are swapped still
   * sees it in isRedefined(). Returns false if `klass` is not registered.
   */
  bool beginRedefinition(const void* klass);

  /**
   * Call after the redefinition call has returned, once for every
   * beginRedefinition() that returned true. `succeeded` makes the mark
   * permanent; otherwise the class is treated as it was before the call.
   */
  void endRedefinition(const void* klass, bool succeeded);

  /**
   * Whether the class at `klass` is being or has been redefined. False once
   * the marked class has been unloaded, so a new class at the same address
   * starts unmarked.
   */
  bool isRedefined(JNIEnv* jni, const void* klass);

  /** Number of occupied slots, including dead entries not yet purged. */
  size_t size();

  /**
   * Sets the klass_registry_capacity and klass_registry_entries gauges.
   * They are updated on every change; call this after counters are reset.
   */
  void publishCounters();

  /** Deletes every weak reference and frees the table. */
  void clear(JNIEnv* jni);
};

#endif // _HOTSPOT_KLASSREGISTRY_H
