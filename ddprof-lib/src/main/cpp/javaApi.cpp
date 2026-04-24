/*
 * Copyright 2016 Andrei Pangin
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

#include <assert.h>

#include "arch.h"
#include "context.h"
#include "context_api.h"
#include "guards.h"
#include "counters.h"
#include "common.h"
#include "engine.h"
#include "hotspot/vmStructs.inline.h"
#include "incbin.h"
#include "jvmThread.h"
#include "os.h"
#include "otel_process_ctx.h"
#include "profiler.h"
#include "thread.h"
#include "tsc.h"
#include "vmEntry.h"
#include <errno.h>
#include <fstream>
#include <sstream>
#include <string.h>

static void throwNew(JNIEnv *env, const char *exception_class,
                     const char *message) {
  jclass cls = env->FindClass(exception_class);
  if (cls != NULL) {
    env->ThrowNew(cls, message);
  }
}

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

extern "C" DLLEXPORT jboolean JNICALL
Java_com_datadoghq_profiler_JavaProfiler_init0(JNIEnv *env, jclass unused) {
  // JavaVM* has already been stored when the native library was loaded so we can pass nullptr here
  return VM::initProfilerBridge(nullptr, true);
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_stop0(JNIEnv *env, jobject unused) {
  Error error = Profiler::instance()->stop();

  if (error) {
    throwNew(env, "java/lang/IllegalStateException", error.message());
  }
}

extern "C" DLLEXPORT jint JNICALL
Java_com_datadoghq_profiler_JavaProfiler_getTid0(JNIEnv *env, jclass unused) {
  return OS::threadId();
}

extern "C" DLLEXPORT jstring JNICALL
Java_com_datadoghq_profiler_JavaProfiler_execute0(JNIEnv *env, jobject unused,
                                                  jstring command) {
  Arguments args;
  JniString command_str(env, command);
  Error error = args.parse(command_str.c_str());

  if (error) {
    throwNew(env, "java/lang/IllegalArgumentException", error.message());
    return NULL;
  }

  Log::open(args);

  std::ostringstream out;
  error = Profiler::instance()->runInternal(args, out);
  if (!error) {
    if (out.tellp() >= 0x3fffffff) {
      throwNew(env, "java/lang/IllegalStateException",
               "Output exceeds string size limit");
      return NULL;
    }
    return env->NewStringUTF(out.str().c_str());
  }

  throwNew(env, "java/lang/IllegalStateException", error.message());
  return NULL;
}

extern "C" DLLEXPORT jstring JNICALL
Java_com_datadoghq_profiler_JavaProfiler_getStatus0(JNIEnv* env,
                                                    jclass unused) {
  char msg[2048];
  Profiler::instance()->status((char*)msg, sizeof(msg) - 1);
  return env->NewStringUTF(msg);
}

extern "C" DLLEXPORT jlong JNICALL
Java_com_datadoghq_profiler_JavaProfiler_getSamples(JNIEnv *env,
                                                    jclass unused) {
  return (jlong)Profiler::instance()->total_samples();
}

// some duplication between add and remove, though we want to avoid having an extra branch in the hot path

// JavaCritical is faster JNI, but more restrictive - parameters and return value have to be
// primitives or arrays of primitive types.
// We direct corresponding JNI calls to JavaCritical to make sure the parameters/return value
// still compatible in the event of signature changes in the future.
extern "C" DLLEXPORT void JNICALL
JavaCritical_com_datadoghq_profiler_JavaProfiler_filterThreadAdd0() {
  ProfiledThread *current = ProfiledThread::current();
  assert(current != nullptr);
  int tid = current->tid();
  if (unlikely(tid < 0)) {
    return;
  }
  ThreadFilter *thread_filter = Profiler::instance()->threadFilter();
  if (unlikely(!thread_filter->enabled())) {
    return;
  }
  
  int slot_id = current->filterSlotId();
  if (unlikely(slot_id == -1)) {
    // Thread doesn't have a slot ID yet (e.g., main thread or profiler started
    // after thread creation). Register now.
    slot_id = thread_filter->registerThread();
    current->setFilterSlotId(slot_id);
  }

  if (unlikely(slot_id == -1)) {
    return;  // Failed to register thread
  }
  // Refresh HotSpot VMThread* for wall thread-filter precheck (vmStructs OS state).
  // HotSpot only: VMThread::current() asserts VM::isHotspot(). OpenJ9/Zing: leave null.
  thread_filter->setVMThread(slot_id, VM::isHotspot() ? VMThread::current() : nullptr);
  thread_filter->add(tid, slot_id);
}

extern "C" DLLEXPORT void JNICALL
JavaCritical_com_datadoghq_profiler_JavaProfiler_filterThreadRemove0() {
  ProfiledThread *current = ProfiledThread::current();
  assert(current != nullptr);
  int tid = current->tid();
  if (unlikely(tid < 0)) {
    return;
  }
  ThreadFilter *thread_filter = Profiler::instance()->threadFilter();
  if (unlikely(!thread_filter->enabled())) {
    return;
  }

  int slot_id = current->filterSlotId();
  if (unlikely(slot_id == -1)) {
    // Thread doesn't have a slot ID yet - nothing to remove
    return;
  }
  thread_filter->remove(slot_id);
}


extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_filterThreadAdd0(JNIEnv *env,
                                                          jclass unused) {
  JavaCritical_com_datadoghq_profiler_JavaProfiler_filterThreadAdd0();
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_filterThreadRemove0(JNIEnv *env,
                                                             jclass unused) {
  JavaCritical_com_datadoghq_profiler_JavaProfiler_filterThreadRemove0();
}

extern "C" DLLEXPORT jboolean JNICALL
Java_com_datadoghq_profiler_JavaProfiler_recordTrace0(
    JNIEnv *env, jclass unused, jlong rootSpanId, jstring endpoint,
    jstring operation, jint sizeLimit) {
  JniString endpoint_str(env, endpoint);
  u32 endpointLabel = Profiler::instance()->stringLabelMap()->bounded_lookup(
      endpoint_str.c_str(), endpoint_str.length(), sizeLimit);
  bool acceptValue = endpointLabel != INT_MAX;
  if (acceptValue) {
    u32 operationLabel = 0;
    if (operation != NULL) {
      JniString operation_str(env, operation);
      operationLabel = Profiler::instance()->contextValueMap()->bounded_lookup(
          operation_str.c_str(), operation_str.length(), 1 << 16);
    }
    TraceRootEvent event(rootSpanId, endpointLabel, operationLabel);
    int tid = ProfiledThread::currentTid();
    Profiler::instance()->recordTraceRoot(tid, &event);
  }
  return acceptValue;
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_dump0(JNIEnv *env, jclass unused,
                                               jstring path) {
  JniString path_str(env, path);
  Profiler::instance()->dump(path_str.c_str(), path_str.length());
}

extern "C" DLLEXPORT jobject JNICALL
Java_com_datadoghq_profiler_JavaProfiler_getDebugCounters0(JNIEnv *env,
                                                           jclass unused) {
#ifdef COUNTERS
  return env->NewDirectByteBuffer((void *)Counters::getCounters(),
                                  (jlong)Counters::size());
#else
  return env->NewDirectByteBuffer(nullptr, 0);
#endif // COUNTERS
}

extern "C" DLLEXPORT jobjectArray JNICALL
Java_com_datadoghq_profiler_JavaProfiler_describeDebugCounters0(
    JNIEnv *env, jclass unused) {
#ifdef COUNTERS
  std::vector<const char *> counter_names = Counters::describeCounters();
  jobjectArray array = (jobjectArray)env->NewObjectArray(
      counter_names.size(), env->FindClass("java/lang/String"),
      env->NewStringUTF(""));
  for (int i = 0; i < counter_names.size(); i++) {
    env->SetObjectArrayElement(array, i,
                               env->NewStringUTF(counter_names.at(i)));
  }
  return array;
#else
  return nullptr;
#endif // COUNTERS
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_recordSettingEvent0(
    JNIEnv *env, jclass unused, jstring name, jstring value, jstring unit) {
  int tid = ProfiledThread::currentTid();
  if (tid < 0) {
    return;
  }
  int length = 0;
  JniString name_str(env, name);
  length += name_str.length();
  JniString value_str(env, value);
  length += value_str.length();
  JniString unit_str(env, unit);
  length += unit_str.length();
  Profiler::instance()->writeDatadogProfilerSetting(
      tid, length, name_str.c_str(), value_str.c_str(), unit_str.c_str());
}

static int dictionarizeClassName(JNIEnv* env, jstring className) {
    JniString str(env, className);
    return Profiler::instance()->lookupClass(str.c_str(), str.length());
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_recordQueueEnd0(
    JNIEnv *env, jclass unused, jlong startTime, jlong endTime, jstring task,
    jstring scheduler, jthread origin, jstring queueType, jint queueLength) {
  int tid = ProfiledThread::currentTid();
  if (tid < 0) {
    return;
  }
  int origin_tid = JVMThread::nativeThreadId(env, origin);
  if (origin_tid < 0) {
    return;
  }
  JniString queue_type_str(env, queueType);
  int task_offset = dictionarizeClassName(env, task);
  if (task_offset < 0) {
    return;
  }
  int scheduler_offset = dictionarizeClassName(env, scheduler);
  if (scheduler_offset < 0) {
    return;
  }
  int queue_type_offset = dictionarizeClassName(env, queueType);
  if (queue_type_offset < 0) {
    return;
  }
  QueueTimeEvent event;
  event._start = startTime;
  event._end = endTime;
  event._task = task_offset;
  event._scheduler = scheduler_offset;
  event._origin = origin_tid;
  event._queueType = queue_type_offset;
  event._queueLength = queueLength;
  Profiler::instance()->recordQueueTime(tid, &event);
}

extern "C" DLLEXPORT jlong JNICALL
Java_com_datadoghq_profiler_JavaProfiler_currentTicks0(JNIEnv *env,
                                                       jclass unused) {
  return TSC::ticks();
}

extern "C" DLLEXPORT jlong JNICALL
Java_com_datadoghq_profiler_JavaProfiler_tscFrequency0(JNIEnv *env,
                                                       jclass unused) {
  return TSC::frequency();
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_mallocArenaMax0(JNIEnv *env,
                                                         jclass unused,
                                                         jint maxArenas) {
  OS::mallocArenaMax(maxArenas);
}

extern "C" DLLEXPORT jstring JNICALL
Java_com_datadoghq_profiler_JVMAccess_findStringJVMFlag0(JNIEnv *env,
                                                         jobject unused,
                                                         jstring flagName) {
  JniString flag_str(env, flagName);
  VMFlag *f = VMFlag::find(flag_str.c_str(), {VMFlag::Type::String, VMFlag::Type::Stringlist});
  if (f) {
    char** value = static_cast<char**>(f->addr());
    if (value != NULL && *value != NULL) {
      return env->NewStringUTF(*value);
    }
  }
  return NULL;
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JVMAccess_setStringJVMFlag0(JNIEnv *env,
                                                         jobject unused,
                                                         jstring flagName,
                                                         jstring flagValue) {
  JniString flag_str(env, flagName);
  JniString value_str(env, flagValue);
  VMFlag *f = VMFlag::find(flag_str.c_str(), {VMFlag::Type::String, VMFlag::Type::Stringlist});
  if (f) {
    char** value = static_cast<char**>(f->addr());
    if (value != NULL) {
      *value = strdup(value_str.c_str());
    }
  }
}

extern "C" DLLEXPORT jboolean JNICALL
Java_com_datadoghq_profiler_JVMAccess_findBooleanJVMFlag0(JNIEnv *env,
                                                         jobject unused,
                                                         jstring flagName) {
  JniString flag_str(env, flagName);
  VMFlag *f = VMFlag::find(flag_str.c_str(), {VMFlag::Type::Bool});
  if (f) {
    char* value = static_cast<char*>(f->addr());
    if (value != NULL) {
      return ((*value) & 0xff) == 1;
    }
  }
  return false;
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JVMAccess_setBooleanJVMFlag0(JNIEnv *env,
                                                         jobject unused,
                                                         jstring flagName,
                                                         jboolean flagValue) {
  JniString flag_str(env, flagName);
  VMFlag *f = VMFlag::find(flag_str.c_str(), {VMFlag::Type::Bool});
  if (f) {
    char* value = static_cast<char*>(f->addr());
    if (value != NULL) {
      *value = flagValue ? 1 : 0;
    }
  }
}

extern "C" DLLEXPORT jlong JNICALL
Java_com_datadoghq_profiler_JVMAccess_findIntJVMFlag0(JNIEnv *env,
                                                         jobject unused,
                                                         jstring flagName) {
  JniString flag_str(env, flagName);
  VMFlag *f = VMFlag::find(flag_str.c_str(), {VMFlag::Type::Int, VMFlag::Type::Uint, VMFlag::Type::Intx, VMFlag::Type::Uintx, VMFlag::Type::Uint64_t, VMFlag::Type::Size_t});
  if (f) {
    long* value = static_cast<long*>(f->addr());
    if (value != NULL) {
      return *value;
    }
  }
  return 0;
}

extern "C" DLLEXPORT jdouble JNICALL
Java_com_datadoghq_profiler_JVMAccess_findFloatJVMFlag0(JNIEnv *env,
                                                         jobject unused,
                                                         jstring flagName) {
  JniString flag_str(env, flagName);
  VMFlag *f = VMFlag::find(flag_str.c_str(),{ VMFlag::Type::Double});
  if (f) {
    double* value = static_cast<double*>(f->addr());
    if (value != NULL) {
      return *value;
    }
  }
  return 0.0;
}

extern "C" DLLEXPORT jboolean JNICALL
Java_com_datadoghq_profiler_JVMAccess_healthCheck0(JNIEnv *env,
                                                         jobject unused) {
  return true;
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_OTelContext_setProcessCtx0(JNIEnv *env,
                                                         jclass unused,
                                                         jstring env_data,
                                                         jstring hostname,
                                                         jstring runtime_id,
                                                         jstring service,
                                                         jstring version,
                                                         jstring tracer_version
                                                        ) {
  JniString env_str(env, env_data);
  JniString hostname_str(env, hostname);
  JniString runtime_id_str(env, runtime_id);
  JniString service_str(env, service);
  JniString version_str(env, version);
  JniString tracer_version_str(env, tracer_version);

  const char *host_name_attrs[] = {"host.name", hostname_str.c_str(), NULL};

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
    .thread_ctx_config = NULL  // Set later by ContextApi::registerAttributeKeys() when keys are known
  };

  otel_process_ctx_result result = otel_process_ctx_publish(&data);
  if (!result.success) {
    Log::warn("Failed to publish process context: %s", result.error_message);
  }
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

  otel_process_ctx_read_drop(&result);

  // Find the ProcessContext class
  jclass processContextClass = env->FindClass("com/datadoghq/profiler/OTelContext$ProcessContext");
  if (!processContextClass) {
    return nullptr;
  }

  // Find the constructor
  jmethodID constructor = env->GetMethodID(processContextClass, "<init>",
    "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
  if (!constructor) {
    return nullptr;
  }

  // Create the ProcessContext object
  jobject processContext = env->NewObject(processContextClass, constructor,
    jDeploymentEnvironmentName, jHostName, jServiceInstanceId, jServiceName, jServiceVersion, jTelemetrySdkLanguage, jTelemetrySdkVersion, jTelemetrySdkName);

  return processContext;
#else
  // If OTEL_PROCESS_CTX_NO_READ is defined, return null
  return nullptr;
#endif
}

extern "C" DLLEXPORT jobject JNICALL
Java_com_datadoghq_profiler_JavaProfiler_initializeContextTLS0(JNIEnv* env, jclass unused, jlongArray metadata) {
  ProfiledThread* thrd = ProfiledThread::current();
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

extern "C" DLLEXPORT jint JNICALL
Java_com_datadoghq_profiler_ThreadContext_registerConstant0(JNIEnv* env, jclass unused, jstring value) {
  JniString value_str(env, value);
  u32 encoding = Profiler::instance()->contextValueMap()->bounded_lookup(
      value_str.c_str(), value_str.length(), 1 << 16);
  return encoding == INT_MAX ? -1 : encoding;
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_OTelContext_registerAttributeKeys0(JNIEnv* env, jclass unused, jobjectArray keys) {
  int count = (keys != nullptr) ? env->GetArrayLength(keys) : 0;
  int n = count < (int)DD_TAGS_CAPACITY ? count : (int)DD_TAGS_CAPACITY;
  if (count > n) {
    LOG_WARN("registerAttributeKeys: %d keys requested but capacity is %d; extra keys will be ignored",
             count, (int)DD_TAGS_CAPACITY);
  }

  const char* key_ptrs[DD_TAGS_CAPACITY];
  JniString* jni_strings[DD_TAGS_CAPACITY];

  for (int i = 0; i < n; i++) {
    jstring jstr = (jstring)env->GetObjectArrayElement(keys, i);
    if (jstr == nullptr) {
      for (int j = 0; j < i; j++) delete jni_strings[j];
      return;
    }
    jni_strings[i] = new JniString(env, jstr);
    key_ptrs[i] = jni_strings[i]->c_str();
  }

  // Always call registerAttributeKeys even with n==0 so the reserved
  // datadog.local_root_span_id key (index 0) is published in the process context.
  ContextApi::registerAttributeKeys(key_ptrs, n);

  for (int i = 0; i < n; i++) delete jni_strings[i];
}

// ---- test and debug utilities
extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_testlog(JNIEnv* env, jclass unused, jstring msg) {
  JniString msg_str(env, msg);

  TEST_LOG("%s", msg_str.c_str());
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_dumpContext(JNIEnv* env, jclass unused) {
  u64 spanId = 0, rootSpanId = 0;
  ContextApi::get(spanId, rootSpanId);
  TEST_LOG("===> Context: tid:%lu, spanId=%lu, rootSpanId=%lu", OS::threadId(), spanId, rootSpanId);
}
