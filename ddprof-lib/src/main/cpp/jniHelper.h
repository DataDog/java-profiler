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

// Encodes UTF-16 as standard UTF-8 into out, which holds at least 3 * n bytes, and returns the
// byte length. Unlike JNI's modified UTF-8, supplementary chars take 4 bytes and U+0000 one zero
// byte; unpaired surrogates become U+FFFD. The output is not NUL-terminated.
inline size_t utf16ToUtf8(const jchar *in, jsize n, char *out) {
  size_t length = 0;
  for (jsize i = 0; i < n; i++) {
    uint32_t c = in[i];
    if (c >= 0xD800 && c <= 0xDBFF && i + 1 < n && in[i + 1] >= 0xDC00 && in[i + 1] <= 0xDFFF) {
      c = 0x10000 + ((c - 0xD800) << 10) + (in[++i] - 0xDC00);
    } else if (c >= 0xD800 && c <= 0xDFFF) {
      c = 0xFFFD;
    }
    if (c < 0x80) {
      out[length++] = static_cast<char>(c);
    } else if (c < 0x800) {
      out[length++] = static_cast<char>(0xC0 | (c >> 6));
      out[length++] = static_cast<char>(0x80 | (c & 0x3F));
    } else if (c < 0x10000) {
      out[length++] = static_cast<char>(0xE0 | (c >> 12));
      out[length++] = static_cast<char>(0x80 | ((c >> 6) & 0x3F));
      out[length++] = static_cast<char>(0x80 | (c & 0x3F));
    } else {
      out[length++] = static_cast<char>(0xF0 | (c >> 18));
      out[length++] = static_cast<char>(0x80 | ((c >> 12) & 0x3F));
      out[length++] = static_cast<char>(0x80 | ((c >> 6) & 0x3F));
      out[length++] = static_cast<char>(0x80 | (c & 0x3F));
    }
  }
  return length;
}

// Returns how many of the first `read` UTF-16 units of a `total`-unit string to keep: a trailing
// high surrogate whose low half lies past the truncation point is dropped, not split.
inline jsize utf16TruncatedLength(const jchar *units, jsize read, jsize total) {
  if (read > 0 && read < total && units[read - 1] >= 0xD800 && units[read - 1] <= 0xDBFF) {
    return read - 1;
  }
  return read;
}

#endif
