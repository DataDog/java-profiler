/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef JAVA_PROFILER_JNIHELPER_H
#define JAVA_PROFILER_JNIHELPER_H

#include <jni.h>
#include <cstddef>
#include <cstdint>
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

// Owns a JNI local reference and deletes it at scope exit; null is a no-op.
class JniLocalRef {
public:
  JniLocalRef(JNIEnv *jni, jobject ref) : _jni(jni), _ref(ref) {}
  ~JniLocalRef() {
    if (_ref != nullptr) {
      _jni->DeleteLocalRef(_ref);
    }
  }
  JniLocalRef(const JniLocalRef &) = delete;
  JniLocalRef &operator=(const JniLocalRef &) = delete;
  jobject get() const { return _ref; }

private:
  JNIEnv *_jni;
  jobject _ref;
};

// Owns the chars from GetStringUTFChars and releases them at scope exit; a
// null str, or a failed copy, gives get() == nullptr.
class JniUtfChars {
public:
  JniUtfChars(JNIEnv *jni, jstring str)
      : _jni(jni), _str(str),
        _chars(str != nullptr ? jni->GetStringUTFChars(str, nullptr) : nullptr) {}
  ~JniUtfChars() {
    if (_chars != nullptr) {
      _jni->ReleaseStringUTFChars(_str, _chars);
    }
  }
  JniUtfChars(const JniUtfChars &) = delete;
  JniUtfChars &operator=(const JniUtfChars &) = delete;
  const char *get() const { return _chars; }

private:
  JNIEnv *_jni;
  jstring _str;
  const char *_chars;
};

// Returns the length of the well-formed modified-UTF-8 sequence at p (1-3 bytes), or 0.
inline size_t modifiedUtf8SequenceLength(const unsigned char *p) {
  auto cont = [](unsigned char b) { return (b & 0xC0) == 0x80; };
  if (p[0] < 0x80) return 1;
  if ((p[0] == 0xC0 && p[1] == 0x80) || (p[0] >= 0xC2 && p[0] <= 0xDF && cont(p[1]))) return 2;
  if ((p[0] & 0xF0) == 0xE0 && cont(p[1]) && cont(p[2]) && (p[0] != 0xE0 || p[1] >= 0xA0)) {
    return 3;
  }
  return 0;
}

// Re-encodes JVMTI's modified UTF-8 as standard UTF-8 into out (3 * max_units bytes, unterminated),
// keeping at most max_units UTF-16 units without splitting a surrogate pair; returns the length.
// Only C0 80 and 6-byte surrogate pairs differ; a lone surrogate or malformed byte becomes U+FFFD.
inline size_t modifiedUtf8ToStandard(const char *name, size_t max_units, char *out) {
  const unsigned char *p = reinterpret_cast<const unsigned char *>(name);
  size_t units = 0;
  size_t length = 0;
  while (*p != '\0' && units < max_units) {
    size_t n = modifiedUtf8SequenceLength(p);
    bool surrogate = n == 3 && p[0] == 0xED && p[1] >= 0xA0;
    if (surrogate && p[1] <= 0xAF && p[3] == 0xED && p[4] >= 0xB0 && p[4] <= 0xBF &&
        (p[5] & 0xC0) == 0x80) {
      if (units + 2 > max_units) {
        break;
      }
      uint32_t c = 0x10000 + ((((p[1] & 0x0F) << 6) | (p[2] & 0x3F)) << 10) +
                   (((p[4] & 0x0F) << 6) | (p[5] & 0x3F));
      out[length++] = static_cast<char>(0xF0 | (c >> 18));
      out[length++] = static_cast<char>(0x80 | ((c >> 12) & 0x3F));
      out[length++] = static_cast<char>(0x80 | ((c >> 6) & 0x3F));
      out[length++] = static_cast<char>(0x80 | (c & 0x3F));
      p += 6;
      units += 2;
      continue;
    }
    if (n == 2 && p[0] == 0xC0) {
      out[length++] = '\0';
    } else if (n == 0 || surrogate) {
      out[length++] = static_cast<char>(0xEF);
      out[length++] = static_cast<char>(0xBF);
      out[length++] = static_cast<char>(0xBD);
      n = n == 0 ? 1 : n;
    } else {
      memcpy(out + length, p, n);
      length += n;
    }
    p += n;
    units++;
  }
  return length;
}

#endif
