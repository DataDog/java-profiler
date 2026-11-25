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

// Modified UTF-8 (JNI, JVMTI) differs from standard UTF-8 only in C0 80 (U+0000) and the
// ED-led surrogate halves of supplementary characters. Without those bytes it is already
// standard UTF-8. BMP characters U+D000-U+D7FF also start with ED: converting them is correct,
// only unnecessary.
inline bool modifiedUtf8IsStandard(const char *s) {
  for (; *s != '\0'; s++) {
    unsigned char c = static_cast<unsigned char>(*s);
    if (c == 0xC0 || c == 0xED) return false;
  }
  return true;
}

// Returns the byte length of the first max_units UTF-16 units of modified UTF-8 s. Each
// modified-UTF-8 byte sequence encodes exactly one UTF-16 unit, so the cut never splits a sequence.
inline size_t modifiedUtf8PrefixLength(const char *s, size_t max_units) {
  size_t units = 0;
  size_t i = 0;
  for (; s[i] != '\0'; i++) {
    if ((static_cast<unsigned char>(s[i]) & 0xC0) != 0x80 && units++ == max_units) {
      break;
    }
  }
  return i;
}

// Converts JVMTI's modified-UTF-8 name to standard UTF-8 of at most max_units UTF-16 units and
// returns its byte length; *utf8 is set to name or out. units holds max_units, out 3 * max_units.
// If the JVM cannot decode the name, the JVMTI bytes are kept under the same cap.
inline size_t modifiedUtf8ToStandard(JNIEnv *jni, const char *name, jsize max_units,
                                     jchar *units, char *out, const char **utf8) {
  *utf8 = name;
  if (modifiedUtf8IsStandard(name)) {
    // Most names need no conversion: no JNI call or Java allocation.
    return modifiedUtf8PrefixLength(name, max_units);
  }
  jstring str = jni->NewStringUTF(name);
  JniLocalRef ref(jni, str);
  if (str == nullptr) {
    jniExceptionCheck(jni);
    return modifiedUtf8PrefixLength(name, max_units);
  }
  jsize total = jni->GetStringLength(str);
  jsize read = total < max_units ? total : max_units;
  jni->GetStringRegion(str, 0, read, units);
  if (jniExceptionCheck(jni)) {
    return modifiedUtf8PrefixLength(name, max_units);
  }
  *utf8 = out;
  return utf16ToUtf8(units, utf16TruncatedLength(units, read, total), out);
}

#endif
