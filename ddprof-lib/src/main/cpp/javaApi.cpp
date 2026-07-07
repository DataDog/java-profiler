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
#include "threadLocalData.h"
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
    // Thread doesn't have a slot ID yet (e.g., main thread), so register it
    // Happens when we are not enabled before thread start
    slot_id = thread_filter->registerThread();
    current->setFilterSlotId(slot_id);
  }

  if (unlikely(slot_id == -1)) {
    return;  // Failed to register thread
  }
  // Reset suppression state so a new thread occupying this slot does not inherit
  // stale state from its predecessor. Must happen before add().
  thread_filter->resetSlotRunState(slot_id);
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
  // StringDictionary reserves 0 as "no entry"; valid IDs start at 1.
  bool acceptValue = endpointLabel != 0;
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

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_parkEnter0(JNIEnv *env, jclass unused) {
  ProfiledThread *current = ProfiledThread::current();
  if (current == nullptr) {
    return;
  }
  bool first_park = current->parkEnter();
  ThreadFilter *tf = Profiler::instance()->threadFilter();
  if (first_park && tf->enabled()) {
    ThreadFilter::SlotID slot_id = current->filterSlotId();
    if (slot_id >= 0) {
      current->setParkBlockToken(
          tf->enterBlockedRun(slot_id, OSThreadState::CONDVAR_WAIT));
    }
  }
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_parkExit0(
    JNIEnv *env, jclass unused, jlong blocker, jlong unblockingSpanId) {
  ProfiledThread *current = ProfiledThread::current();
  if (current == nullptr) {
    return;
  }
  u64 park_block_token = 0;
  if (!current->parkExit(park_block_token) || park_block_token == 0) {
    return;
  }
  ThreadFilter *tf = Profiler::instance()->threadFilter();
  if (tf->enabled()) {
    ThreadFilter::SlotID slot_id = ThreadFilter::tokenSlotId(park_block_token);
    if (current->filterSlotId() == slot_id) {
      tf->exitBlockedRun(slot_id, ThreadFilter::tokenGeneration(park_block_token));
    }
  }
}

static bool decodeJavaBlockState(jint state, OSThreadState &decoded) {
  if (state == static_cast<jint>(OSThreadState::SLEEPING)) {
    decoded = OSThreadState::SLEEPING;
    return true;
  }
  decoded = OSThreadState::UNKNOWN;
  return false;
}

extern "C" DLLEXPORT jlong JNICALL
Java_com_datadoghq_profiler_JavaProfiler_blockEnter0(
    JNIEnv *env, jclass unused, jint state) {
  OSThreadState decoded;
  if (!decodeJavaBlockState(state, decoded)) {
    return 0;
  }
  ProfiledThread *current = ProfiledThread::current();
  if (current == nullptr) {
    return 0;
  }
  ThreadFilter *tf = Profiler::instance()->threadFilter();
  if (!tf->enabled()) {
    return 0;
  }
  ThreadFilter::SlotID slot_id = current->filterSlotId();
  if (slot_id < 0) {
    return 0;
  }
  return static_cast<jlong>(tf->enterBlockedRun(slot_id, decoded));
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_blockExit0(
    JNIEnv *env, jclass unused, jlong token) {
  u64 block_token = static_cast<u64>(token);
  if (block_token == 0) {
    return;
  }
  ProfiledThread *current = ProfiledThread::current();
  if (current == nullptr) {
    return;
  }
  ThreadFilter::SlotID slot_id = ThreadFilter::tokenSlotId(block_token);
  if (current->filterSlotId() != slot_id) {
    return;
  }
  ThreadFilter *tf = Profiler::instance()->threadFilter();
  if (tf->enabled()) {
    tf->exitBlockedRun(slot_id, ThreadFilter::tokenGeneration(block_token));
  }
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

// ---------------------------------------------------------------------------
// All-native context write API (OTEP #4947).
//
// Every write resolves the *current* carrier's OtelThreadContextRecord via
// ProfiledThread::current(). Because a JNI native frame pins a mounted virtual thread to its
// carrier for the duration of the call (the continuation cannot freeze across a native frame),
// the record resolved here is guaranteed live and cannot migrate mid-write — there is no cached
// per-thread buffer to dangle. This replaces the DirectByteBuffer path (see ThreadContext),
// eliminating the virtual-thread use-after-free.
//
// Signal-safety / reader coherence: the sampler (ContextApi::get, wallClock.cpp) reads the same
// record on the same carrier, gated on record->valid. Each write follows the detach -> mutate ->
// attach protocol used by ThreadContext: store valid=0, release fence, mutate, release fence,
// store valid=1. On x86 the release fence is a compiler barrier; on aarch64 it is a real barrier
// pairing with the sampler's acquire load of valid in ContextApi::get.
// ---------------------------------------------------------------------------

// Byte layout constants shared with ThreadContext (see otel_context.h / ThreadContext.java).
static const int OTEL_LRS_ENTRY_SIZE = 18; // fixed attrs_data[0] entry: key(1)+len(1)+16 hex bytes

// Writes the full fixed LRS attrs_data entry: header (key_index=0, length=16) at attrs_data[0..2)
// plus the 16 hex value bytes at attrs_data[2..18). The combined write/clear entry points
// (setTraceContext0 / clearTraceContext0) call this so they establish the LRS entry themselves
// rather than relying on the ThreadContext ctor — i.e. they work on a record that only saw the
// ProfiledThread zero-init, the phase-2 pure-native case where no DirectByteBuffer / ThreadContext
// was ever created. Mirrors ThreadContext's LRS entry layout.
//
// Note: the single-attribute path (setContextValue0) does NOT write this entry; it assumes a
// preceding setTraceContext0 has already established it (the production order — app tags are set
// after span activation). On a never-activated record it simply appends the attribute at
// attrs_data[0] with no LRS entry, which is harmless: the sampler reads LRS from the sidecar
// (_otel_local_root_span_id), and with no active span the LRS is 0 anyway.
static inline void otelWriteLrsEntry(OtelThreadContextRecord* record, u64 v) {
  static const char HEXD[16] =
      {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
  record->attrs_data[0] = 0;   // OTEP key_index reserved for LRS
  record->attrs_data[1] = 16;  // fixed LRS value length
  uint8_t* hex = record->attrs_data + 2;
  for (int i = 15; i >= 0; i--) {
    hex[i] = (uint8_t)HEXD[v & 0xF];
    v >>= 4;
  }
}

// Compacts out the attrs_data entry with the given OTEP key index; returns the new size.
// Mirrors ThreadContext.compactOtepAttribute. Record must be detached.
static int otelCompactAttr(OtelThreadContextRecord* record, int otepKeyIndex) {
  int currentSize = record->attrs_data_size;
  uint8_t* d = record->attrs_data;
  int readPos = 0, writePos = 0;
  bool found = false;
  while (readPos + 2 <= currentSize) {
    int k = d[readPos];
    int len = d[readPos + 1];
    if (readPos + 2 + len > currentSize) { currentSize = writePos; break; }
    if (k == otepKeyIndex) {
      found = true;
      readPos += 2 + len;
    } else {
      if (found && writePos < readPos) {
        memmove(d + writePos, d + readPos, 2 + len);
      }
      writePos += 2 + len;
      readPos += 2 + len;
    }
  }
  return found ? writePos : currentSize;
}

// Replaces/inserts an attribute value in attrs_data (record must be detached). Returns false on
// attrs_data overflow (nothing appended). Mirrors ThreadContext.replaceOtepAttribute.
static bool otelReplaceAttr(OtelThreadContextRecord* record, int otepKeyIndex,
                            const uint8_t* utf8, int valueLen) {
  int currentSize = otelCompactAttr(record, otepKeyIndex);
  int entrySize = 2 + valueLen;
  if (currentSize + entrySize <= OTEL_MAX_ATTRS_DATA_SIZE) {
    uint8_t* base = record->attrs_data + currentSize;
    base[0] = (uint8_t)otepKeyIndex;
    base[1] = (uint8_t)valueLen;
    memcpy(base + 2, utf8, valueLen);
    record->attrs_data_size = (uint16_t)(currentSize + entrySize);
    return true;
  }
  record->attrs_data_size = (uint16_t)currentSize;
  return false;
}

// Copies at most 255 bytes from a Java byte[] into buf; returns the length copied (0 if arr null).
// Callers (ContextValueCache.resolve) reject values whose UTF-8 exceeds 255 bytes before they
// reach here, so an oversized array is a caller-contract violation, not an expected input. The
// assert documents/enforces that in debug builds; the clamp is release-build defense that also
// bounds the copy to the 256-byte caller stack buffer. Clamping mid-sequence could split a
// multi-byte UTF-8 char, but is unreachable given the caller guard.
static inline int otelReadUtf8(JNIEnv* env, jbyteArray arr, uint8_t* buf) {
  if (arr == nullptr) {
    return 0;
  }
  jint len = env->GetArrayLength(arr);
  assert(len <= 255);
  if (len > 255) {
    len = 255;
  }
  env->GetByteArrayRegion(arr, 0, len, (jbyte*)buf);
  return (int)len;
}

// Writes one pre-resolved attribute slot (sidecar encoding + attrs_data value). Record detached.
static inline void otelWriteSlot(OtelThreadContextRecord* record, u32* enc,
                                 int slot, u32 encoding, const uint8_t* utf8, int len) {
  enc[slot] = encoding;
  if (!otelReplaceAttr(record, slot + 1, utf8, len)) {
    enc[slot] = 0;
  }
}

// Combined per-activation write: scalar trace/span/LRS context plus up to two pre-resolved
// (slot, encoding, utf8) attributes, in one detach/attach window. A negative slot skips that
// attribute (so callers with 0 or 1 activation attribute pass slot < 0). Assumes an active span
// (non-zero); clearing is clearTraceContext0. Encodings are resolved by the Java value cache.
extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_setTraceContext0(JNIEnv* env, jclass unused,
    jlong localRootSpanId, jlong spanId, jlong traceIdHigh, jlong traceIdLow,
    jint slot0, jint enc0, jbyteArray utf0, jint slot1, jint enc1, jbyteArray utf1) {
  ProfiledThread* thrd = ProfiledThread::current();
  if (thrd == nullptr) {
    return;
  }
  OtelThreadContextRecord* record = thrd->getOtelContextRecord();
  u32* enc = thrd->getOtelTagEncodingsPtr();
  u64* lrs = reinterpret_cast<u64*>(enc + DD_TAGS_CAPACITY);

  // Marshal attribute bytes before detaching, to keep the detached window minimal.
  uint8_t b0[256], b1[256];
  int len0 = 0, len1 = 0;
  bool has0 = slot0 >= 0 && slot0 < (jint)DD_TAGS_CAPACITY;
  bool has1 = slot1 >= 0 && slot1 < (jint)DD_TAGS_CAPACITY;
  if (has0) { len0 = otelReadUtf8(env, utf0, b0); }
  if (has1) { len1 = otelReadUtf8(env, utf1, b1); }

  // detach
  __atomic_store_n(&record->valid, (uint8_t)0, __ATOMIC_RELAXED);
  __atomic_thread_fence(__ATOMIC_RELEASE);

  // scalar context: trace_id / span_id are big-endian byte arrays (little-endian hosts only).
  uint64_t beHi = __builtin_bswap64((uint64_t)traceIdHigh);
  uint64_t beLo = __builtin_bswap64((uint64_t)traceIdLow);
  uint64_t beSpan = __builtin_bswap64((uint64_t)spanId);
  memcpy(record->trace_id, &beHi, 8);
  memcpy(record->trace_id + 8, &beLo, 8);
  memcpy(record->span_id, &beSpan, 8);
  memset(enc, 0, DD_TAGS_CAPACITY * sizeof(u32));       // reset per-span custom slots
  record->attrs_data_size = (uint16_t)OTEL_LRS_ENTRY_SIZE;
  *lrs = (u64)localRootSpanId;
  otelWriteLrsEntry(record, (u64)localRootSpanId);

  // activation attributes
  if (has0) { otelWriteSlot(record, enc, slot0, (u32)enc0, b0, len0); }
  if (has1) { otelWriteSlot(record, enc, slot1, (u32)enc1, b1, len1); }

  // attach
  __atomic_thread_fence(__ATOMIC_RELEASE);
  __atomic_store_n(&record->valid, (uint8_t)1, __ATOMIC_RELAXED);
}

// Combined per-deactivation clear: zeros scalar context + custom slots and leaves the record
// detached (valid=0), mirroring the DBB clear path (setContext(0,0,0,0) + clearContextValue*).
extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_clearTraceContext0(JNIEnv* env, jclass unused) {
  ProfiledThread* thrd = ProfiledThread::current();
  if (thrd == nullptr) {
    return;
  }
  OtelThreadContextRecord* record = thrd->getOtelContextRecord();
  u32* enc = thrd->getOtelTagEncodingsPtr();
  u64* lrs = reinterpret_cast<u64*>(enc + DD_TAGS_CAPACITY);

  __atomic_store_n(&record->valid, (uint8_t)0, __ATOMIC_RELAXED);
  __atomic_thread_fence(__ATOMIC_RELEASE);

  memset(record->trace_id, 0, sizeof(record->trace_id));
  memset(record->span_id, 0, sizeof(record->span_id));
  memset(enc, 0, DD_TAGS_CAPACITY * sizeof(u32));
  *lrs = 0;
  record->attrs_data_size = (uint16_t)OTEL_LRS_ENTRY_SIZE;
  otelWriteLrsEntry(record, 0);
  // clear path leaves valid=0 (no attach), mirroring ThreadContext.clearContextDirect.
}

// Single pre-resolved attribute write (sidecar encoding + attrs_data value) in one detach/attach
// window. Returns false on attrs_data overflow. Encoding resolved by the Java value cache.
extern "C" DLLEXPORT jboolean JNICALL
Java_com_datadoghq_profiler_JavaProfiler_setContextValue0(JNIEnv* env, jclass unused,
    jint slot, jint encoding, jbyteArray utf8) {
  ProfiledThread* thrd = ProfiledThread::current();
  if (thrd == nullptr || slot < 0 || slot >= (jint)DD_TAGS_CAPACITY) {
    return JNI_FALSE;
  }
  OtelThreadContextRecord* record = thrd->getOtelContextRecord();
  u32* enc = thrd->getOtelTagEncodingsPtr();

  uint8_t buf[256];
  int len = otelReadUtf8(env, utf8, buf);

  __atomic_store_n(&record->valid, (uint8_t)0, __ATOMIC_RELAXED);
  __atomic_thread_fence(__ATOMIC_RELEASE);

  enc[slot] = (u32)encoding;
  jboolean ok = JNI_TRUE;
  if (!otelReplaceAttr(record, slot + 1, buf, len)) {
    enc[slot] = 0;
    ok = JNI_FALSE;
  }

  __atomic_thread_fence(__ATOMIC_RELEASE);
  __atomic_store_n(&record->valid, (uint8_t)1, __ATOMIC_RELAXED);
  return ok;
}

// Clears a single attribute slot (zeros the sidecar encoding, compacts it out of attrs_data).
extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_clearContextValue0(JNIEnv* env, jclass unused, jint slot) {
  ProfiledThread* thrd = ProfiledThread::current();
  if (thrd == nullptr || slot < 0 || slot >= (jint)DD_TAGS_CAPACITY) {
    return;
  }
  OtelThreadContextRecord* record = thrd->getOtelContextRecord();
  u32* enc = thrd->getOtelTagEncodingsPtr();

  __atomic_store_n(&record->valid, (uint8_t)0, __ATOMIC_RELAXED);
  __atomic_thread_fence(__ATOMIC_RELEASE);

  enc[slot] = 0;
  record->attrs_data_size = (uint16_t)otelCompactAttr(record, slot + 1);

  __atomic_thread_fence(__ATOMIC_RELEASE);
  __atomic_store_n(&record->valid, (uint8_t)1, __ATOMIC_RELAXED);
}

extern "C" DLLEXPORT jint JNICALL
Java_com_datadoghq_profiler_ThreadContext_registerConstant0(JNIEnv* env, jclass unused, jstring value) {
  JniString value_str(env, value);
  u32 encoding = Profiler::instance()->contextValueMap()->bounded_lookup(
      value_str.c_str(), value_str.length(), 1 << 16);
  return encoding == 0 ? -1 : (jint)encoding;
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
