/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_KLASSTRACEID_H
#define _HOTSPOT_KLASSTRACEID_H

#include "safeAccess.h"

#include <jni.h>
#include <stddef.h>
#include <stdint.h>

/**
 * Locates HotSpot's per-class JFR trace ID (Klass::_trace_id) by probing,
 * since gHotSpotVMStructs does not expose it.
 *
 * In JFR-enabled builds every Klass, including array klasses, is assigned
 * `(counter << 16) | tag bits` at creation, from one global counter; the low
 * 16 bits are JFR tag/epoch bits that JFR rewrites while it runs. So
 * `raw >> 16` is unique per loaded class and identifies one particular load
 * of a class even when a later class reuses its Klass* address.
 *
 * The field's position differs between releases (after _access_flags on
 * 17u/21u, after _archived_mirror_index on mainline, where it also depends on
 * the CDS Java heap build option), so instead of a per-version offset table
 * calibrate() makes the JVM create a few array klasses back to back and
 * accepts the one 8-byte-aligned offset within sizeof(Klass) at which all of
 * them hold distinct IDs no further apart than consecutive creation allows.
 * Builds without JFR, or a layout where no single offset qualifies, leave the
 * offset unknown, and callers fall back to KlassRegistry's epoch.
 */
class KlassTraceId {
  static int _offset;
  static bool _calibrated;

public:
  // Array dimensions created by calibrate(): one probe klass per dimension.
  static const int PROBE_COUNT = 6;
  // How many trace IDs other threads may consume while the probes are
  // created, i.e. how far apart beyond PROBE_COUNT - 1 the probes' IDs may be.
  static const uint64_t ID_SLACK = 64;

  /**
   * Returns the single 8-byte-aligned offset in [8, klass_size) at which the
   * `count` klasses all hold plausible, freshly assigned trace IDs, or -1 if
   * there is none or more than one. The klasses must be readable for
   * klass_size bytes.
   */
  static int findOffset(const void* const* klasses, int count, size_t klass_size);

  /**
   * Creates the probe klasses through JNI and records the offset found. Only
   * the first call per process calibrates; later calls return its result, so
   * the tag source of raw frames (see HotspotSupport) never changes while
   * frames from an earlier profiling session may still be stored. Returns
   * true if an offset is known.
   */
  static bool calibrate(JNIEnv* jni);

  /** The calibrated offset, or -1. */
  static int offset() { return __atomic_load_n(&_offset, __ATOMIC_ACQUIRE); }

  /**
   * Reads the trace ID (`raw >> 16`) of `klass` with SafeAccess, so it is
   * usable from a signal handler on a Klass* that may be stale. Returns false
   * if not calibrated or the field is unreadable.
   */
  static inline bool read(const void* klass, uint64_t* id) {
    int off = offset();
    if (off < 0 || klass == nullptr) {
      return false;
    }
    // An all-ones raw value would mean 2^48 - 1 classes had been created, so
    // it can serve as the fault marker.
    void* const fault = (void*)UINTPTR_MAX;
    void* raw = SafeAccess::loadPtr((void**)((const char*)klass + off), fault);
    if (raw == fault) {
      return false;
    }
    *id = (uint64_t)(uintptr_t)raw >> 16;
    return true;
  }

  /** Test hook: forget or force the calibrated offset. */
  static void setOffsetForTest(int offset) { __atomic_store_n(&_offset, offset, __ATOMIC_RELEASE); }
};

#endif // _HOTSPOT_KLASSTRACEID_H
