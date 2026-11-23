/*
 * Copyright 2022 Andrei Pangin
 * Copyright 2024, 2026 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "j9/j9Support.h"
#include "jniHelper.h"
#include "os.h"
#include <string.h>

jvmtiEnv *J9Support::_jvmti;

void *(*J9Support::_j9thread_self)() = NULL;

jvmtiExtensionFunction J9Support::_GetOSThreadID = NULL;
jvmtiExtensionFunction J9Support::_GetJ9vmThread = NULL;
jvmtiExtensionFunction J9Support::_GetStackTraceExtended = NULL;
jvmtiExtensionFunction J9Support::_GetAllStackTracesExtended = NULL;

int J9Support::InstrumentableObjectAlloc_id = -1;

// Look for OpenJ9-specific JVM TI extension
bool J9Support::initialize(jvmtiEnv *jvmti, const void *j9thread_self) {
  _jvmti = jvmti;
  _j9thread_self = (void *(*)())j9thread_self;

  jint ext_count;
  jvmtiExtensionFunctionInfo *ext_functions;
  if (jvmti->GetExtensionFunctions(&ext_count, &ext_functions) == 0) {
    for (int i = 0; i < ext_count; i++) {
      if (strcmp(ext_functions[i].id, "com.ibm.GetOSThreadID") == 0) {
        _GetOSThreadID = ext_functions[i].func;
      } else if (strcmp(ext_functions[i].id, "com.ibm.GetJ9vmThread") == 0) {
        _GetJ9vmThread = ext_functions[i].func;
      } else if (strcmp(ext_functions[i].id, "com.ibm.GetStackTraceExtended") ==
                 0) {
        _GetStackTraceExtended = ext_functions[i].func;
      } else if (strcmp(ext_functions[i].id,
                        "com.ibm.GetAllStackTracesExtended") == 0) {
        _GetAllStackTracesExtended = ext_functions[i].func;
      }
    }
    jvmti->Deallocate((unsigned char *)ext_functions);
  }

  return _GetOSThreadID != NULL && _GetStackTraceExtended != NULL &&
         _GetAllStackTracesExtended != NULL;
}

namespace {

constexpr int FIRST_DEADLOCK_PRONE_IBM_FIX_PACK = 70;
constexpr int FIRST_FIXED_IBM_FIX_PACK = 75;

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

class JniUtfChars {
public:
  JniUtfChars(JNIEnv *jni, jstring str)
      : _jni(jni), _str(str), _chars(jni->GetStringUTFChars(str, nullptr)) {}
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

bool isDigit(char c) { return c >= '0' && c <= '9'; }

bool isDeadlockProneOpenJ9Release(const char *vm_version) {
  static const char TAG[] = "openj9-0.60";
  const char *match = strstr(vm_version, TAG);
  return match != nullptr && !isDigit(match[sizeof(TAG) - 1]);
}

bool isDeadlockProneIbmFixPack(const char *runtime_version) {
  static const char TAG[] = "(SR8 FP";
  const char *p = strstr(runtime_version, TAG);
  if (p == nullptr) {
    return false;
  }
  p += sizeof(TAG) - 1;
  int fix_pack = 0;
  int digits = 0;
  // Four digits exceed every fix-pack number and keep fix_pack from overflowing.
  for (; isDigit(*p) && digits < 4; p++, digits++) {
    fix_pack = fix_pack * 10 + (*p - '0');
  }
  return digits > 0 && !isDigit(*p) &&
         fix_pack >= FIRST_DEADLOCK_PRONE_IBM_FIX_PACK &&
         fix_pack < FIRST_FIXED_IBM_FIX_PACK;
}

std::string readVmProperty(jvmtiEnv *jvmti, const char *key) {
  JvmtiString value(jvmti);
  if (jvmti == nullptr || jvmti->GetSystemProperty(key, value.out()) != JVMTI_ERROR_NONE ||
      value.get() == nullptr) {
    return std::string();
  }
  return std::string(value.get());
}

std::string readJavaProperty(JNIEnv *jni, const char *key) {
  // JNI calls other than exception handling are illegal while one is pending.
  if (jni == nullptr || jni->ExceptionCheck()) {
    return std::string();
  }
  JniLocalRef system(jni, jni->FindClass("java/lang/System"));
  if (jniExceptionCheck(jni) || system.get() == nullptr) {
    return std::string();
  }
  jclass system_class = static_cast<jclass>(system.get());
  jmethodID get_property = jni->GetStaticMethodID(
      system_class, "getProperty", "(Ljava/lang/String;)Ljava/lang/String;");
  if (jniExceptionCheck(jni) || get_property == nullptr) {
    return std::string();
  }
  JniLocalRef name(jni, jni->NewStringUTF(key));
  if (jniExceptionCheck(jni) || name.get() == nullptr) {
    return std::string();
  }
  JniLocalRef value(jni, jni->CallStaticObjectMethod(system_class, get_property,
                                                     name.get()));
  if (jniExceptionCheck(jni) || value.get() == nullptr) {
    return std::string();
  }
  JniUtfChars chars(jni, static_cast<jstring>(value.get()));
  if (jniExceptionCheck(jni) || chars.get() == nullptr) {
    return std::string();
  }
  return std::string(chars.get());
}

} // namespace

bool J9Support::isAsgctDeadlockProneVersion(const char *vm_version,
                                            const char *runtime_version) {
  return (vm_version != nullptr && isDeadlockProneOpenJ9Release(vm_version)) ||
         (runtime_version != nullptr &&
          isDeadlockProneIbmFixPack(runtime_version));
}

J9VersionProps J9Support::readVersionProps() {
  J9VersionProps props;
  props.vm_version = readVmProperty(_jvmti, "java.vm.version");
  props.runtime_version = readJavaProperty(VM::jni(), "java.runtime.version");
  return props;
}

J9SamplerRisk J9Support::assessSamplers(J9SamplerChoice cpu,
                                        J9SamplerChoice wall,
                                        bool deadlock_prone) {
  bool asgct = cpu == J9SamplerChoice::ASGCT || wall == J9SamplerChoice::ASGCT;
  bool gated = cpu == J9SamplerChoice::JVMTI_GATED ||
               wall == J9SamplerChoice::JVMTI_GATED;
  return {asgct && deadlock_prone, gated};
}

const char *J9Support::choiceName(J9SamplerChoice choice) {
  switch (choice) {
  case J9SamplerChoice::NONE:
    return "none";
  case J9SamplerChoice::ASGCT:
    return "asgct";
  case J9SamplerChoice::JVMTI_REQUESTED:
    return "jvmti_requested";
  case J9SamplerChoice::JVMTI_GATED:
    return "jvmti_gated";
  }
  return "unknown";
}
