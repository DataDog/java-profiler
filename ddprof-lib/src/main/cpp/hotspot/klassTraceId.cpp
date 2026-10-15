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
bool KlassTraceId::_calibrated = false;

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

bool KlassTraceId::calibrate(JNIEnv* jni) {
  // Runs from profiler start, which is serialized, so a plain flag will do.
  if (_calibrated) {
    return offset() >= 0;
  }
  _calibrated = true;
  size_t klass_size = (size_t)VMKlass::type_size();
  if (klass_size == 0 || !VMStructs::hasKlassMethods()) {
    return false;
  }

  // "[Ljava/lang/Void;" .. "[[[[[[Ljava/lang/Void;". Resolving the deepest
  // one makes the JVM create every missing dimension in order, each getting
  // the next trace ID; java.lang.Void has no other use for such arrays.
  static const char ELEMENT[] = "Ljava/lang/Void;";
  char name[PROBE_COUNT + sizeof(ELEMENT)];
  memset(name, '[', PROBE_COUNT);
  memcpy(name + PROBE_COUNT, ELEMENT, sizeof(ELEMENT));

  const void* klasses[PROBE_COUNT];
  for (int dims = PROBE_COUNT; dims >= 1; dims--) {
    const char* dim_name = name + (PROBE_COUNT - dims);
    jclass cls = jni->FindClass(dim_name);
    if (cls == nullptr) {
      jni->ExceptionClear();
      return false;
    }
    klasses[dims - 1] = VMKlass::fromJavaClass(jni, cls);
    jni->DeleteLocalRef(cls);
    if (klasses[dims - 1] == nullptr) {
      return false;
    }
  }

  int found = findOffset(klasses, PROBE_COUNT, klass_size);
  TEST_LOG("KlassTraceId offset=%d (sizeof(Klass)=%d)", found, (int)klass_size);
  if (found < 0) {
    return false;
  }
  __atomic_store_n(&_offset, found, __ATOMIC_RELEASE);
  return true;
}
