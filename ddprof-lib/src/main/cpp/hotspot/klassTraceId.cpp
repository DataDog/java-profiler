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

// The class file of `public class datadog/ddprof/KlassTraceIdProbe`, with no
// fields and no methods: just enough for DefineClass() to create a Klass.
static const unsigned char PROBE_CLASS_FILE[] = {
    0xCA, 0xFE, 0xBA, 0xBE, 0x00, 0x00, 0x00, 0x32,  // magic, version 50.0
    0x00, 0x05,                                      // constant pool count
    0x01, 0x00, 0x20, 'd', 'a', 't', 'a', 'd', 'o', 'g', '/', 'd', 'd', 'p', 'r', 'o', 'f', '/',
    'K', 'l', 'a', 's', 's', 'T', 'r', 'a', 'c', 'e', 'I', 'd', 'P', 'r', 'o', 'b', 'e',  // #1 Utf8
    0x07, 0x00, 0x01,                                // #2 Class #1
    0x01, 0x00, 0x10, 'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'O', 'b', 'j', 'e', 'c', 't',  // #3 Utf8
    0x07, 0x00, 0x03,                                // #4 Class #3
    0x00, 0x21,                                      // ACC_PUBLIC | ACC_SUPER
    0x00, 0x02, 0x00, 0x04,                          // this #2, super #4
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // no interfaces, fields, methods, attributes
};
static const char PROBE_CLASS_NAME[] = "datadog/ddprof/KlassTraceIdProbe";

// Creates the probe klasses of one attempt, in creation order: arrays of
// dimensions 1 .. PROBE_COUNT of a class defined in a new class loader for
// this attempt, so none of them can have existed before. Probes that existed
// already, created far apart, would let the right field fail the check while
// another passes it (the mirrors' heap addresses, shifted right by 16, can be
// distinct and close together). Nothing keeps the loader reachable
// afterwards, so it and its classes can be unloaded. Returns false on any JNI
// failure. Must run inside a JNI local frame.
static bool createProbes(JNIEnv* jni, const void** klasses) {
  jclass loader_class = jni->FindClass("java/security/SecureClassLoader");
  jmethodID init = loader_class == nullptr ? nullptr : jni->GetMethodID(loader_class, "<init>", "(Ljava/lang/ClassLoader;)V");
  // JNI does not check access, so the protected constructor will do; the
  // parent is the bootstrap loader.
  jobject loader = init == nullptr ? nullptr : jni->NewObject(loader_class, init, (jobject)nullptr);
  jclass cls = loader == nullptr ? nullptr
                                 : jni->DefineClass(PROBE_CLASS_NAME, loader, (const jbyte*)PROBE_CLASS_FILE,
                                                    (jsize)sizeof(PROBE_CLASS_FILE));
  for (int i = 0; i < KlassTraceId::PROBE_COUNT && cls != nullptr; i++) {
    // An empty array of `cls` makes the JVM create the next dimension.
    jobjectArray array = jni->NewObjectArray(0, cls, nullptr);
    cls = array == nullptr ? nullptr : jni->GetObjectClass(array);
    klasses[i] = cls == nullptr ? nullptr : VMKlass::fromJavaClass(jni, cls);
    if (klasses[i] == nullptr) {
      cls = nullptr;
    }
  }
  if (cls == nullptr) {
    jni->ExceptionClear();
    TEST_LOG("KlassTraceId: could not create the probe classes");
    return false;
  }
  return true;
}

// One attempt: creates fresh probe klasses and looks for the offset in them.
// Returns the offset, or -1.
static int probe(JNIEnv* jni, size_t klass_size) {
  if (jni->PushLocalFrame(2 * KlassTraceId::PROBE_COUNT + 8) != JNI_OK) {
    jni->ExceptionClear();
    return -1;
  }
  const void* klasses[KlassTraceId::PROBE_COUNT];
  int found = -1;
  if (createProbes(jni, klasses)) {
    found = KlassTraceId::findOffset(klasses, KlassTraceId::PROBE_COUNT, klass_size);
    TEST_LOG("KlassTraceId offset=%d (sizeof(Klass)=%d)", found, (int)klass_size);
    if (found < 0) {
      logProbes(klasses, klass_size);
    }
  }
  jni->PopLocalFrame(nullptr);
  return found;
}

bool KlassTraceId::calibrate(JNIEnv* jni) {
  if (offset() >= 0) {
    return true;
  }
  size_t klass_size = (size_t)VMKlass::type_size();
  if (klass_size == 0 || !VMStructs::hasKlassMethods()) {
    TEST_LOG("KlassTraceId: no Klass layout from vmStructs");
    return false;
  }
  // A failed attempt usually means other threads created many classes while
  // the probes were created; that is unlikely to repeat right away.
  for (int attempt = 0; attempt < MAX_ATTEMPTS; attempt++) {
    int found = probe(jni, klass_size);
    if (found >= 0) {
      __atomic_store_n(&_offset, found, __ATOMIC_RELEASE);
      return true;
    }
  }
  return false;
}
