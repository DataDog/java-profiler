/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_KLASSREGISTRY_H
#define _HOTSPOT_KLASSREGISTRY_H

#include "mutex.h"

#include <jni.h>
#include <stddef.h>
#include <stdint.h>

/**
 * Maps a HotSpot Klass* to a JNI weak global reference to its java.lang.Class
 * mirror, so the dump thread can tell whether the class a raw Method* frame
 * came from is still loaded -- and keep it loaded while it resolves the frame.
 *
 * Used by fjmethodid=lazy: walkVM stores a raw Method* for every frame whose
 * class has no jmethodID yet, and HotspotSupport::resolve() later reads the
 * holder Klass* out of that (possibly freed) Method*. That pointer is only a
 * lookup key here and is never dereferenced: pin() returns a strong local
 * reference only if the class registered under that address is still
 * reachable, and a strongly reachable mirror keeps its class loader -- and so
 * the class's metadata -- from being unloaded until the reference is released.
 *
 * Entries are added from ClassPrepare and never removed explicitly; dead ones
 * (weak reference cleared) are purged whenever the table would have to grow,
 * so memory tracks the number of live classes rather than every class ever
 * loaded. A Klass* address reused by a newly loaded class simply overwrites
 * the dead entry on that class's ClassPrepare.
 *
 * All operations take an internal mutex and call JNI, so none of them may be
 * used from a signal handler.
 */
class KlassRegistry {
  struct Entry {
    const void* klass;
    jweak mirror;
  };

  static const size_t INITIAL_CAPACITY = 1024;

  Mutex _lock;
  Entry* _table;
  size_t _capacity;  // Power of two, or 0 before the first add()
  size_t _size;      // Occupied slots, live or dead

  Entry* find(const void* klass) const;
  bool rehash(JNIEnv* jni);

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

  /**
   * Returns a new local reference to the mirror registered for `klass`, or
   * nullptr if none is registered or the class has been unloaded. While the
   * caller holds the reference the class cannot be unloaded; it must release
   * it with DeleteLocalRef.
   */
  jclass pin(JNIEnv* jni, const void* klass);

  /** Number of occupied slots, including dead entries not yet purged. */
  size_t size();

  /** Deletes every weak reference and frees the table. */
  void clear(JNIEnv* jni);
};

#endif // _HOTSPOT_KLASSREGISTRY_H
