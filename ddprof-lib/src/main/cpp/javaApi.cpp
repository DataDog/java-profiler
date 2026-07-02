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
#include "support/context_api.h"
#include "guards.h"
#include "counters.h"
#include "common.h"
#include "engine.h"
#include "hotspot/vmStructs.inline.h"
#include "incbin.h"
#include "jvmThread.h"
#include "os.h"
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
  ProfiledThread *current = ProfiledThread::currentProfiled();
  if (current == nullptr) {
    return;
  }
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
  ProfiledThread *current = ProfiledThread::currentProfiled();
  if (current == nullptr) {
    return;
  }
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
  ProfiledThread *current = ProfiledThread::currentProfiled();
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
  ProfiledThread *current = ProfiledThread::currentProfiled();
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
  ProfiledThread *current = ProfiledThread::currentProfiled();
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
  ProfiledThread *current = ProfiledThread::currentProfiled();
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
