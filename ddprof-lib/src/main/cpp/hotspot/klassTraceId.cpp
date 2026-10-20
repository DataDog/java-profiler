/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "hotspot/klassTraceId.h"

#include "common.h"
#include "counters.h"
#include "hotspot/vmStructs.inline.h"

#include <string.h>

int KlassTraceId::_offset = -1;

// JFR stores the ID shifted left by TRACE_ID_SHIFT (16) above its tag bits.
static const int TRACE_ID_SHIFT = 16;

static inline uint64_t idAt(const void* klass, size_t offset) {
  uint64_t raw;
  memcpy(&raw, (const char*)klass + offset, sizeof(raw));
  return raw >> TRACE_ID_SHIFT;
}

// The probes were created back to back by one thread, so their IDs are
// distinct and lie within a narrow window: PROBE_COUNT consecutive values
// plus whatever other threads took meanwhile. Pointers to neighbouring
// metadata fail this (they are hundreds of bytes apart, so `>> 16` mostly
// collapses them to one value); so do small integers (equal across probes)
// and compressed-klass bits in a mark word (far more than ID_SLACK apart).
static bool plausibleIds(const void* const* klasses, int count, size_t offset) {
  uint64_t min = UINT64_MAX;
  uint64_t max = 0;
  for (int i = 0; i < count; i++) {
    uint64_t id = idAt(klasses[i], offset);
    if (id == 0) {
      return false;
    }
    for (int j = 0; j < i; j++) {
      if (idAt(klasses[j], offset) == id) {
        return false;
      }
    }
    min = id < min ? id : min;
    max = id > max ? id : max;
  }
  return max - min <= (uint64_t)(count - 1) + KlassTraceId::ID_SLACK;
}

int KlassTraceId::findOffset(const void* const* klasses, int count, size_t klass_size) {
  if (count < 2) {
    return -1;
  }
  int found = -1;
  // Offset 0 is the C++ vtable pointer.
  for (size_t offset = 8; offset + sizeof(uint64_t) <= klass_size; offset += 8) {
    if (plausibleIds(klasses, count, offset)) {
      if (found >= 0) {
        return -1;  // Ambiguous: refuse rather than guess.
      }
      found = (int)offset;
    }
  }
  return found;
}

// Highest dimension any attempt has created so far; the next attempt probes
// the PROBE_COUNT dimensions above it.
static int _probed_dims = 0;
// The offset the last successful attempt found, waiting for a second attempt
// to confirm it.
static int _candidate = -1;

// Dumps what each probe holds at every offset findOffset() looked at, so a
// release whose layout calibration rejects can be diagnosed from a debug CI
// log.
static void logProbes(const void* const* klasses, size_t klass_size) {
#ifdef DEBUG
  for (size_t offset = 8; offset + sizeof(uint64_t) <= klass_size; offset += 8) {
    uint64_t raw[KlassTraceId::PROBE_COUNT];
    for (int i = 0; i < KlassTraceId::PROBE_COUNT; i++) {
      memcpy(&raw[i], (const char*)klasses[i] + offset, sizeof(raw[i]));
    }
    TEST_LOG("KlassTraceId probe @%3d: %016llx %016llx %016llx %016llx %016llx %016llx%s", (int)offset,
             (unsigned long long)raw[0], (unsigned long long)raw[1], (unsigned long long)raw[2],
             (unsigned long long)raw[3], (unsigned long long)raw[4], (unsigned long long)raw[5],
             plausibleIds(klasses, KlassTraceId::PROBE_COUNT, offset) ? " plausible" : "");
  }
#endif
}

// One attempt: makes the JVM create array klasses of java.lang.Void with
// dimensions first_dim .. first_dim + PROBE_COUNT - 1 and looks for the
// offset in them. Resolving the deepest one creates every missing dimension
// in order, each getting the next trace ID; java.lang.Void has no other use
// for such arrays. Earlier attempts (or other code) may have created lower
// dimensions already, so only the top PROBE_COUNT dimensions are probed, and
// those are new. Returns the offset, or -1.
static int probe(JNIEnv* jni, int first_dim, size_t klass_size) {
  static const char ELEMENT[] = "Ljava/lang/Void;";
  const int top_dim = first_dim + KlassTraceId::PROBE_COUNT - 1;
  char name[KlassTraceId::MAX_DIMENSIONS + sizeof(ELEMENT)];
  assert(first_dim >= 1 && top_dim <= KlassTraceId::MAX_DIMENSIONS);
  memset(name, '[', top_dim);
  memcpy(name + top_dim, ELEMENT, sizeof(ELEMENT));

  const void* klasses[KlassTraceId::PROBE_COUNT];
  for (int i = KlassTraceId::PROBE_COUNT - 1; i >= 0; i--) {
    const int dims = first_dim + i;
    jclass cls = jni->FindClass(name + (top_dim - dims));
    if (cls == nullptr) {
      jni->ExceptionClear();
      TEST_LOG("KlassTraceId: FindClass failed for %d dimensions", dims);
      return -1;
    }
    klasses[i] = VMKlass::fromJavaClass(jni, cls);
    jni->DeleteLocalRef(cls);
    if (klasses[i] == nullptr) {
      TEST_LOG("KlassTraceId: no Klass* for %d dimensions", dims);
      return -1;
    }
  }

  int found = KlassTraceId::findOffset(klasses, KlassTraceId::PROBE_COUNT, klass_size);
  TEST_LOG("KlassTraceId offset=%d (sizeof(Klass)=%d, dimensions %d-%d)", found, (int)klass_size,
           first_dim, top_dim);
  if (found < 0) {
    logProbes(klasses, klass_size);
  }
  return found;
}

bool KlassTraceId::calibrate(JNIEnv* jni) {
  // Runs from Profiler::start() with _state_lock held, so plain statics will
  // do.
  if (offset() >= 0) {
    return true;
  }
  size_t klass_size = (size_t)VMKlass::type_size();
  if (klass_size == 0 || !VMStructs::hasKlassMethods()) {
    TEST_LOG("KlassTraceId: no Klass layout from vmStructs");
    return false;
  }
  // A failed attempt usually means the probes' IDs were not consecutive:
  // other threads created many classes meanwhile, or some of the dimensions
  // already existed. Fresh dimensions make either unlikely to repeat.
  // If all of an attempt's dimensions already existed, created far apart,
  // their trace IDs fail the check while another field can pass it: the
  // mirrors' heap addresses, shifted right by 16, can be distinct and close
  // together. Probes created back to back have adjacent mirrors, which that
  // shift makes equal, so an offset is only taken once two attempts on
  // different dimensions agree on it.
  for (int attempt = 0; attempt < MAX_ATTEMPTS && _probed_dims + PROBE_COUNT <= MAX_DIMENSIONS; attempt++) {
    const int first_dim = _probed_dims + 1;
    _probed_dims += PROBE_COUNT;
    int found = probe(jni, first_dim, klass_size);
    if (found >= 0 && found == _candidate) {
      __atomic_store_n(&_offset, found, __ATOMIC_RELEASE);
      return true;
    }
    if (found >= 0) {
      _candidate = found;
    }
  }
  return false;
}
