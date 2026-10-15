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
 * Whether the pinned class is the same load of a class as the one sampled is
 * checked separately, through the class's JFR trace ID (see HotspotSupport).
 *
 * Entries are added from ClassPrepare and never removed explicitly; dead ones
 * (weak reference cleared) are purged whenever the table would have to grow,
 * so memory tracks the number of live classes rather than every class ever
 * loaded. A Klass* address reused by a newly loaded class simply overwrites
 * the dead entry on that class's ClassPrepare.
 *
 * Redefinition: a redefined class stays alive, but its old methods array and
 * old Method*s are freed once no longer on any stack, and later allocations
 * -- including another redefinition of the same class -- can reuse them. So
 * beginRedefinition() is called before every redefinition and
 * endRedefinition() after it. While one is in progress, and for good once one
 * has succeeded, pin() refuses the class's raw frames. (After a successful
 * redefinition the class's jmethodIDs are preloaded, so its later frames are
 * not raw.) A failed call leaves the methods untouched, and the class as it
 * was.
 *
 * All operations take an internal mutex and call JNI, so none of them may be
 * used from a signal handler.
 */
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

public:
  enum PinStatus {
    PIN_OK,
    PIN_ABSENT,     // not registered, or the class has been unloaded
    PIN_REDEFINED,  // the class is being or has been redefined
  };

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
   * nullptr -- with the reason in `*status` -- if none is registered, the
   * class has been unloaded, or it is being or has been redefined. While the
   * caller holds the reference the class cannot be unloaded; it must release
   * it with DeleteLocalRef.
   */
  jclass pin(JNIEnv* jni, const void* klass, PinStatus* status = nullptr);

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

  /** Whether `klass` is being or has been redefined. */
  bool isRedefined(const void* klass);

  /** Number of occupied slots, including dead entries not yet purged. */
  size_t size();

  /** Deletes every weak reference and frees the table. */
  void clear(JNIEnv* jni);
};

#endif // _HOTSPOT_KLASSREGISTRY_H
