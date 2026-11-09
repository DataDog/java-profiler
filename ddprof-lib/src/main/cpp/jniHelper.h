/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef JAVA_PROFILER_JNIHELPER_H
#define JAVA_PROFILER_JNIHELPER_H

#include <jni.h>
#include <cstring>

// JNI fixes IsVirtualThread at slot 234 from JDK 21 onward. Read its ABI slot
// so builds using older JNI headers can still detect virtual threads at runtime.
inline bool jniIsVirtualThread(JNIEnv *jni, jobject thread, int java_version) {
  if (java_version < 21 || jni == nullptr) {
    return false;
  }
  using IsVirtualThreadFn = jboolean (JNICALL *)(JNIEnv *, jobject);
  constexpr size_t IS_VIRTUAL_THREAD_SLOT = 234;
  IsVirtualThreadFn is_virtual;
  static_assert(sizeof(is_virtual) == sizeof(void *), "JNI function slot size");
  std::memcpy(&is_virtual, reinterpret_cast<const char *>(jni->functions) +
                  IS_VIRTUAL_THREAD_SLOT * sizeof(void *), sizeof(is_virtual));
  return is_virtual(jni, thread) == JNI_TRUE;
}

inline bool jniExceptionCheck(JNIEnv *jni, bool describe = false) {
  if (jni->ExceptionCheck()) {
    if (describe) {
      jni->ExceptionDescribe();
    }
    jni->ExceptionClear();
    return true;
  }
  return false;
}

#endif
