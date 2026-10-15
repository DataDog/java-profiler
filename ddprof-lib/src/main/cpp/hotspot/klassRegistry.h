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
 * Metadata reuse: the memory of a freed class -- its Klass* and very likely
 * its Method* addresses -- goes to classes loaded later, so a Method* sampled
 * from an unloaded class can look exactly like a method of a newer class,
 * whether that one sits at the same Klass* or elsewhere. The registry
 * therefore keeps an epoch: every registration bumps it and records the new
 * value, so any class registered after a frame was sampled has a newer epoch
 * than the frame. walkVM can store epoch() in each raw frame (when no JFR
 * trace ID is available, see HotspotSupport); pin() then refuses a frame
 * whose epoch predates the entry, since that frame can only come from an
 * earlier occupant of the memory. This relies on every class being
 * registered before any of its methods can run, which ClassPrepare
 * guarantees; when registration fails, the caller must preload the class's
 * jmethodIDs instead so that no raw frame of it is ever produced.
 *
 * Redefinition: a redefined class stays alive, but its old methods array and
 * old Method*s are freed once no longer on any stack, and later allocations
 * -- including another redefinition of the same class -- can reuse them. So
 * markRedefined() is called before every redefinition, the class's
 * jmethodIDs are preloaded after it (so its later frames are not raw), and
 * pin() refuses every raw frame of a marked class.
 *
 * Except for epoch(), all operations take an internal mutex and call JNI, so
 * none of them may be used from a signal handler.
 */
class KlassRegistry {
  struct Entry {
    const void* klass;
    jweak mirror;
    uint32_t epoch;   // _epoch when this mirror was registered
    bool redefined;   // markRedefined() was called; never reset
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

  enum PinStatus {
    PIN_OK,
    PIN_ABSENT,     // not registered, or the class has been unloaded
    PIN_STALE,      // registered after the frame was sampled
    PIN_REDEFINED,  // the class has been redefined since registration
  };

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
   * nullptr -- with the reason in `*status` -- if none is registered, the
   * class has been unloaded, the registration is newer than `sampled_epoch`,
   * or the class has been redefined. Epochs compare modulo 2^EPOCH_BITS.
   * While the caller holds the reference the class cannot be unloaded; it
   * must release it with DeleteLocalRef.
   */
  jclass pin(JNIEnv* jni, const void* klass, uint32_t sampled_epoch, PinStatus* status = nullptr);

  /**
   * Marks `klass` as redefined, for good. Call before the redefinition
   * starts, so that a resolution which validated the class's metadata just
   * before the methods were swapped still sees the mark in isRedefined().
   * Returns false if `klass` is not registered.
   */
  bool markRedefined(const void* klass);

  /** Whether markRedefined() was called for `klass`. */
  bool isRedefined(const void* klass);

  /** Number of occupied slots, including dead entries not yet purged. */
  size_t size();

  /** Deletes every weak reference and frees the table. */
  void clear(JNIEnv* jni);
};

#endif // _HOTSPOT_KLASSREGISTRY_H
