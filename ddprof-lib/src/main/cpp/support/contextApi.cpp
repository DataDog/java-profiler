/*
 * Copyright 2026 Datadog, Inc
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

#include "context.h"
#include "context_api.h"
#include "log.h"
#include "otel_process_ctx.h"
#include "threadContext.h"

#include <cassert>
#include <cstddef>
#include <cstring>
#include <jni.h>

#ifndef DLLEXPORT
#define DLLEXPORT __attribute__((visibility("default")))
#endif

// RAII wrapper for JNI string conversion. Duplicated from javaApi.cpp /
// support/jvmAccessApi.cpp on purpose (see LibrarySplitPlan Task 4.3) so this
// TU has no dependency on profiler-only headers.
class JniString {
private:
  JNIEnv *_env;
  const char *_c_string;
  jstring _java_string;
  int _length;

public:
  JniString(JNIEnv *env, jstring java_string) {
    _env = env;
    _c_string = _env->GetStringUTFChars(java_string, NULL);
    _length = _env->GetStringUTFLength(java_string);
    _java_string = java_string;
  }
  JniString(JniString &jniString) = delete;
  ~JniString() { _env->ReleaseStringUTFChars(_java_string, _c_string); }
  const char *c_str() const { return _c_string; }
  int length() const { return _length; }
};

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_OTelContext_setProcessCtx0(JNIEnv *env,
                                                         jclass unused,
                                                         jstring env_data,
                                                         jstring hostname,
                                                         jstring runtime_id,
                                                         jstring service,
                                                         jstring version,
                                                         jstring tracer_version,
                                                         jobjectArray attribute_keys
                                                        ) {
  JniString env_str(env, env_data);
  JniString hostname_str(env, hostname);
  JniString runtime_id_str(env, runtime_id);
  JniString service_str(env, service);
  JniString version_str(env, version);
  JniString tracer_version_str(env, tracer_version);

  const char *host_name_attrs[] = {"host.name", hostname_str.c_str(), NULL};

  // Build the thread context attribute_key_map published alongside the process
  // context: index 0 is the reserved datadog.local_root_span_id slot, followed by
  // the caller-provided keys (clipped to DD_TAGS_CAPACITY)
  int count = (attribute_keys != nullptr) ? env->GetArrayLength(attribute_keys) : 0;
  int n = count < (int)DD_TAGS_CAPACITY ? count : (int)DD_TAGS_CAPACITY;
  if (count > n) {
    Log::warn("setProcessContext: %d attribute keys requested but capacity is %d; extra keys will be ignored",
              count, (int)DD_TAGS_CAPACITY);
  }

  const char *key_ptrs[DD_TAGS_CAPACITY + 2]; // +1 reserved slot, +1 NULL terminator
  JniString *jni_keys[DD_TAGS_CAPACITY];
  int built = 0;
  key_ptrs[0] = "datadog.local_root_span_id";
  for (int i = 0; i < n; i++) {
    jstring jstr = (jstring)env->GetObjectArrayElement(attribute_keys, i);
    if (jstr == nullptr) {
      // A null key would corrupt the index mapping; abort the publish.
      for (int j = 0; j < built; j++) delete jni_keys[j];
      Log::warn("setProcessContext: null attribute key at index %d; skipping publish", i);
      return;
    }
    jni_keys[built] = new JniString(env, jstr);
    if (jni_keys[built]->c_str() == nullptr) {
      // GetStringUTFChars failed (e.g. OOM); a NULL key pointer would truncate
      // the published map mid-array, so abort the publish.
      delete jni_keys[built];
      for (int j = 0; j < built; j++) delete jni_keys[j];
      Log::warn("setProcessContext: failed to read attribute key at index %d; skipping publish", i);
      return;
    }
    key_ptrs[i + 1] = jni_keys[built]->c_str();
    built++;
  }
  key_ptrs[n + 1] = nullptr;

  otel_thread_ctx_config_data thread_ctx_config = {
    .schema_version = "tlsdesc_v1_dev",
    .attribute_key_map = key_ptrs,
  };

  otel_process_ctx_data data = {
    .deployment_environment_name = env_str.c_str(),
    .service_instance_id = runtime_id_str.c_str(),
    .service_name = service_str.c_str(),
    .service_version = version_str.c_str(),
    .telemetry_sdk_language = "java",
    .telemetry_sdk_version = tracer_version_str.c_str(),
    .telemetry_sdk_name = "dd-trace-java",
    .resource_attributes = host_name_attrs,
    .extra_attributes = NULL,
    .thread_ctx_config = &thread_ctx_config
  };

  otel_process_ctx_result result = otel_process_ctx_publish(&data);
  if (!result.success) {
    Log::warn("Failed to publish process context: %s", result.error_message);
  }

  for (int i = 0; i < built; i++) delete jni_keys[i];
}

extern "C" DLLEXPORT jobject JNICALL
Java_com_datadoghq_profiler_OTelContext_readProcessCtx0(JNIEnv *env, jclass unused) {
#ifndef OTEL_PROCESS_CTX_NO_READ
  otel_process_ctx_read_result result = otel_process_ctx_read();

  if (!result.success) {
    // Return null if reading failed
    return nullptr;
  }

  // Convert C strings to Java strings
  jstring jDeploymentEnvironmentName = result.data.deployment_environment_name ?
    env->NewStringUTF(result.data.deployment_environment_name) : nullptr;
  jstring jServiceInstanceId = result.data.service_instance_id ?
    env->NewStringUTF(result.data.service_instance_id) : nullptr;
  jstring jServiceName = result.data.service_name ?
    env->NewStringUTF(result.data.service_name) : nullptr;
  jstring jServiceVersion = result.data.service_version ?
    env->NewStringUTF(result.data.service_version) : nullptr;
  jstring jTelemetrySdkLanguage = result.data.telemetry_sdk_language ?
    env->NewStringUTF(result.data.telemetry_sdk_language) : nullptr;
  jstring jTelemetrySdkVersion = result.data.telemetry_sdk_version ?
    env->NewStringUTF(result.data.telemetry_sdk_version) : nullptr;
  jstring jTelemetrySdkName = result.data.telemetry_sdk_name ?
    env->NewStringUTF(result.data.telemetry_sdk_name) : nullptr;

  // Extract host.name from resource_attributes
  jstring jHostName = nullptr;
  if (result.data.resource_attributes != NULL) {
    for (int i = 0; result.data.resource_attributes[i] != NULL; i += 2) {
      if (strcmp(result.data.resource_attributes[i], "host.name") == 0 && result.data.resource_attributes[i + 1] != NULL) {
        jHostName = env->NewStringUTF(result.data.resource_attributes[i + 1]);
        break;
      }
    }
  }

  // Extract attribute_key_map from thread_ctx_config (NULL if no config was published)
  jobjectArray jAttributeKeyMap = nullptr;
  if (result.data.thread_ctx_config != NULL && result.data.thread_ctx_config->attribute_key_map != NULL) {
    int n = 0;
    while (result.data.thread_ctx_config->attribute_key_map[n] != NULL) n++;
    jclass stringClass = env->FindClass("java/lang/String");
    if (stringClass != nullptr) {
      jAttributeKeyMap = env->NewObjectArray(n, stringClass, nullptr);
      for (int i = 0; i < n; i++) {
        jstring jKey = env->NewStringUTF(result.data.thread_ctx_config->attribute_key_map[i]);
        env->SetObjectArrayElement(jAttributeKeyMap, i, jKey);
        env->DeleteLocalRef(jKey);
      }
    }
  }

  otel_process_ctx_read_drop(&result);

  // Find the ProcessContext class
  jclass processContextClass = env->FindClass("com/datadoghq/profiler/OTelContext$ProcessContext");
  if (!processContextClass) {
    return nullptr;
  }

  // Find the constructor
  jmethodID constructor = env->GetMethodID(processContextClass, "<init>",
    "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;)V");
  if (!constructor) {
    return nullptr;
  }

  // Create the ProcessContext object
  jobject processContext = env->NewObject(processContextClass, constructor,
    jDeploymentEnvironmentName, jHostName, jServiceInstanceId, jServiceName, jServiceVersion, jTelemetrySdkLanguage, jTelemetrySdkVersion, jTelemetrySdkName, jAttributeKeyMap);

  return processContext;
#else
  // If OTEL_PROCESS_CTX_NO_READ is defined, return null
  return nullptr;
#endif
}

extern "C" DLLEXPORT jobject JNICALL
Java_com_datadoghq_profiler_ContextStorage_initializeContextTLS0(JNIEnv* env, jclass unused, jlongArray metadata) {
  ThreadContext* thrd = ThreadContext::current();
  assert(thrd != nullptr);

  if (!thrd->isContextInitialized()) {
    ContextApi::initializeContextTLS(thrd);
  }

  OtelThreadContextRecord* record = thrd->getOtelContextRecord();

  // Contiguity of record + tag_encodings + LRS is enforced by alignas(8) on _otel_ctx_record
  // plus sizeof(OtelThreadContextRecord) being a multiple of 8 (see thread.h).
  // Compile-time alignment check always runs; runtime pointer-layout check is debug-only.
  static_assert(DD_TAGS_CAPACITY * sizeof(u32) % alignof(u64) == 0,
      "tag encodings array size must be aligned to u64 for contiguous sidecar layout");
#ifdef DEBUG
  uint8_t* record_start = reinterpret_cast<uint8_t*>(record);
  uint8_t* sidecar_start = reinterpret_cast<uint8_t*>(thrd->getOtelTagEncodingsPtr());
  assert(sidecar_start == record_start + OTEL_MAX_RECORD_SIZE
         && "_otel_ctx_record and _otel_tag_encodings must be contiguous");
#endif

  // Fill metadata[6]: [VALID_OFFSET, TRACE_ID_OFFSET, SPAN_ID_OFFSET,
  //                    ATTRS_DATA_SIZE_OFFSET, ATTRS_DATA_OFFSET, LRS_OFFSET].
  // All offsets are absolute within the unified buffer returned below.
  if (metadata != nullptr && env->GetArrayLength(metadata) >= 6) {
    jlong meta[6];
    meta[0] = (jlong)offsetof(OtelThreadContextRecord, valid);
    meta[1] = (jlong)offsetof(OtelThreadContextRecord, trace_id);
    meta[2] = (jlong)offsetof(OtelThreadContextRecord, span_id);
    meta[3] = (jlong)offsetof(OtelThreadContextRecord, attrs_data_size);
    meta[4] = (jlong)offsetof(OtelThreadContextRecord, attrs_data);
    meta[5] = (jlong)(OTEL_MAX_RECORD_SIZE + DD_TAGS_CAPACITY * sizeof(u32));
    env->SetLongArrayRegion(metadata, 0, 6, meta);
  }

  // Single contiguous view over [record | tag_encodings | LRS] — used for per-field
  // access and for bulk snapshot/restore. All three regions are in one ProfiledThread
  // memory block.
  size_t totalSize = OTEL_MAX_RECORD_SIZE + DD_TAGS_CAPACITY * sizeof(u32) + sizeof(u64);
  return env->NewDirectByteBuffer((void*)record, (jlong)totalSize);
}
