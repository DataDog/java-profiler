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
 * Klass* reuse: class space hands a freed Klass* address -- and very likely
 * the same Method* addresses -- to the next class of the same shape, so a
 * Method* sampled from an unloaded class can look exactly like a method of
 * the class that replaced it. The registry therefore keeps an epoch: every
 * entry records the epoch it was registered at, and the epoch is bumped
 * whenever a registration may reuse the address of a class that is gone --
 * when a known Klass* gets a different mirror, and when a rehash purges dead
 * entries (after which the old address can come back as a first insert).
 * walkVM stores epoch() in each raw frame; pin() refuses a frame whose epoch
 * predates the entry, since such a frame can only come from an earlier
 * occupant of the address. This relies on every class being registered
 * before any of its methods can run, which ClassPrepare guarantees; when
 * registration fails, the caller must preload the class's jmethodIDs instead
 * so that no raw frame of it is ever produced.
 *
 * Except for epoch(), all operations take an internal mutex and call JNI, so
 * none of them may be used from a signal handler.
 */
class KlassRegistry {
  struct Entry {
    const void* klass;
    jweak mirror;
    uint32_t epoch;  // _epoch when this mirror was registered
  };

  static const size_t INITIAL_CAPACITY = 1024;

  Mutex _lock;
  Entry* _table;
  size_t _capacity;  // Power of two, or 0 before the first add()
  size_t _size;      // Occupied slots, live or dead
  volatile uint32_t _epoch;

  Entry* find(const void* klass) const;
  bool rehash(JNIEnv* jni);
  uint32_t bumpEpoch();

public:
  // Width of the epoch as stored in a frame and compared by pin(): a raw
  // frame's tag minus the bit that says which kind of tag it is (checked in
  // hotspotSupport.cpp).
  static const int EPOCH_BITS = 25;

  KlassRegistry() : _table(nullptr), _capacity(0), _size(0), _epoch(0) {}

  KlassRegistry(const KlassRegistry&) = delete;
  KlassRegistry& operator=(const KlassRegistry&) = delete;

  /**
   * Records that `klass` is the Klass* of `mirror`. Re-adding the same pair is
   * a no-op; adding a different mirror for a known Klass* replaces the entry.
   * Returns false if the weak reference or the table could not be allocated.
   */
  bool add(JNIEnv* jni, const void* klass, jclass mirror);

  /**
   * The current epoch, to be stored with a frame sampled now. Signal safe:
   * a single acquire load.
   */
  uint32_t epoch() const { return __atomic_load_n(&_epoch, __ATOMIC_ACQUIRE); }

  /**
   * Returns a new local reference to the mirror registered for `klass`, or
   * nullptr if none is registered, the class has been unloaded, or the
   * registration is newer than `sampled_epoch` (the frame came from an
   * earlier class at the same address; `*stale` is then set to true). Epochs
   * compare modulo 2^EPOCH_BITS. While the caller holds the reference the
   * class cannot be unloaded; it must release it with DeleteLocalRef.
   */
  jclass pin(JNIEnv* jni, const void* klass, uint32_t sampled_epoch, bool* stale = nullptr);

  /** Number of occupied slots, including dead entries not yet purged. */
  size_t size();

  /** Deletes every weak reference and frees the table. */
  void clear(JNIEnv* jni);
};

#endif // _HOTSPOT_KLASSREGISTRY_H
