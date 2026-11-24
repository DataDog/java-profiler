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
#include "common.h"
#include "jniHelper.h"
#include "jvmtiHelper.h"
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

J9VersionProps J9Support::readVersionProps(jvmtiEnv *jvmti, JNIEnv *jni) {
  J9VersionProps props;
  props.vm_version = readVmProperty(jvmti, "java.vm.version");
  props.runtime_version = readJavaProperty(jni, "java.runtime.version");
  return props;
}

J9SamplerRisk J9Support::assessSamplers(SamplerChoice cpu,
                                        SamplerChoice wall,
                                        bool deadlock_prone) {
  bool asgct = cpu == SamplerChoice::ASGCT || wall == SamplerChoice::ASGCT;
  bool gated = cpu == SamplerChoice::JVMTI_GATED ||
               wall == SamplerChoice::JVMTI_GATED;
  return {asgct && deadlock_prone, gated};
}

static const char *orUnknown(const std::string &value) {
  return value.empty() ? "unknown" : value.c_str();
}

J9SamplerRisk J9Support::reportSamplerRisks(SamplerChoice cpu,
                                            SamplerChoice wall,
                                            const J9VersionProps &props) {
  J9SamplerRisk risk = assessSamplers(
      cpu, wall,
      isAsgctDeadlockProneVersion(props.vm_version.c_str(),
                                  props.runtime_version.c_str()));
  if (risk.deadlock_risk) {
    LOG_WARN("J9 AsyncGetCallTrace can deadlock the JVM on this build "
             "(java.vm.version=%s, java.runtime.version=%s). Upgrade to OpenJ9 "
             "0.61+ (IBM SDK 8.0.8.75+), or set -Ddd.profiling.ddprof.j9.sampler=jvmti "
             "(an explicit itimer, ctimer or perf event also needs cpu=<interval> or "
             "event=cpu)",
             orUnknown(props.vm_version), orUnknown(props.runtime_version));
  }
  if (risk.gated_fallback) {
    LOG_WARN("AsyncGetCallTrace is enabled only on OpenJ9 8u451+, 11.0.27+, "
             "17.0.15+ and 21.0.7+; using the JVMTI sampler");
  }
  return risk;
}
