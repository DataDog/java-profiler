/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef JAVA_PROFILER_JVMTIHELPER_H
#define JAVA_PROFILER_JVMTIHELPER_H

#include <jvmti.h>

// Owns a string a JVMTI call returns through out() and Deallocates it at scope
// exit; a null value is a no-op.
class JvmtiString {
public:
  explicit JvmtiString(jvmtiEnv *jvmti) : _jvmti(jvmti), _value(nullptr) {}
  ~JvmtiString() {
    if (_value != nullptr) {
      _jvmti->Deallocate(reinterpret_cast<unsigned char *>(_value));
    }
  }
  JvmtiString(const JvmtiString &) = delete;
  JvmtiString &operator=(const JvmtiString &) = delete;
  char **out() { return &_value; }
  const char *get() const { return _value; }

private:
  jvmtiEnv *_jvmti;
  char *_value;
};

#endif
