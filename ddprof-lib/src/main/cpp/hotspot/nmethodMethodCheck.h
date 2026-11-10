/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_NMETHOD_METHOD_CHECK_H
#define _HOTSPOT_NMETHOD_METHOD_CHECK_H

#include <jni.h>

// Reads, for each compiled body of `method` that JVMTI reports, the values the
// profiler obtains through its own vmStructs offsets: the JVMTI code address,
// whether the code-heap lookup found an nmethod (0) or not (1), and the
// jmethodID read from the nmethod's _method field. The result holds the
// target's jmethodID at index 0, then up to 16 (code_addr, status, read)
// triples. Returns nullptr when the profiler has no code heap; throws
// IllegalArgumentException when `method` is not a Method object and
// IllegalStateException when a JVMTI call fails.
class NMethodMethodCheck {
  public:
    static jlongArray readsForTest(JNIEnv* jni, jobject method);
};

#endif // _HOTSPOT_NMETHOD_METHOD_CHECK_H
