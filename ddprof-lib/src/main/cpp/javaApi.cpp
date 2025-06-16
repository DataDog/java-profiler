/*
 * Copyright 2016 Andrei Pangin
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

#include "context.h"
#include "counters.h"
#include "engine.h"
#include "incbin.h"
#include "os.h"
#include "profiler.h"
#include "thread.h"
#include "tsc.h"
#include "vmEntry.h"
#include "vmStructs_dd.h"
#include "wallClock.h"
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
Java_com_datadoghq_profiler_JavaProfiler_getTid0(JNIEnv *env, jobject unused) {
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
                                                    jobject unused) {
  char msg[2048];
  int ret = Profiler::instance()->status((char*)msg, sizeof(msg) - 1);
  return env->NewStringUTF(msg);
}

extern "C" DLLEXPORT jlong JNICALL
Java_com_datadoghq_profiler_JavaProfiler_getSamples(JNIEnv *env,
                                                    jobject unused) {
  return (jlong)Profiler::instance()->total_samples();
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_filterThread0(JNIEnv *env,
                                                       jobject unused,
                                                       jboolean enable) {
  int tid = ProfiledThread::currentTid();
  if (tid < 0) {
    return;
  }
  ThreadFilter *thread_filter = Profiler::instance()->threadFilter();
  if (enable) {
    thread_filter->add(tid);
  } else {
    thread_filter->remove(tid);
  }
}

extern "C" DLLEXPORT jobject JNICALL
Java_com_datadoghq_profiler_JavaProfiler_getContextPage0(JNIEnv *env,
                                                         jobject unused,
                                                         jint tid) {
  ContextPage page = Contexts::getPage((int)tid);
  if (page.storage == 0) {
    return NULL;
  }
  return env->NewDirectByteBuffer((void *)page.storage, (jlong)page.capacity);
}

extern "C" DLLEXPORT jlong JNICALL
Java_com_datadoghq_profiler_JavaProfiler_getContextPageOffset0(JNIEnv *env,
                                                               jobject unused,
                                                               jint tid) {
  ContextPage page = Contexts::getPage((int)tid);
  return (jlong)page.storage;
}

extern "C" DLLEXPORT jint JNICALL
Java_com_datadoghq_profiler_JavaProfiler_getMaxContextPages0(JNIEnv *env,
                                                             jobject unused) {
  return (jint)Contexts::getMaxPages();
}

extern "C" DLLEXPORT jboolean JNICALL
Java_com_datadoghq_profiler_JavaProfiler_recordTrace0(
    JNIEnv *env, jobject unused, jlong rootSpanId, jstring endpoint,
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

extern "C" DLLEXPORT jint JNICALL
Java_com_datadoghq_profiler_JavaProfiler_registerConstant0(JNIEnv *env,
                                                           jobject unused,
                                                           jstring value) {
  JniString value_str(env, value);
  u32 encoding = Profiler::instance()->contextValueMap()->bounded_lookup(
      value_str.c_str(), value_str.length(), 1 << 16);
  return encoding == INT_MAX ? -1 : encoding;
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_dump0(JNIEnv *env, jobject unused,
                                               jstring path) {
  JniString path_str(env, path);
  Profiler::instance()->dump(path_str.c_str(), path_str.length());
}

extern "C" DLLEXPORT jobject JNICALL
Java_com_datadoghq_profiler_JavaProfiler_getDebugCounters0(JNIEnv *env,
                                                           jobject unused) {
#ifdef COUNTERS
  return env->NewDirectByteBuffer((void *)Counters::getCounters(),
                                  (jlong)Counters::size());
#else
  return env->NewDirectByteBuffer(nullptr, 0);
#endif // COUNTERS
}

extern "C" DLLEXPORT jobjectArray JNICALL
Java_com_datadoghq_profiler_JavaProfiler_describeDebugCounters0(
    JNIEnv *env, jobject unused) {
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
    JNIEnv *env, jobject unused, jstring name, jstring value, jstring unit) {
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
    JNIEnv *env, jobject unused, jlong startTime, jlong endTime, jstring task,
    jstring scheduler, jthread origin, jstring queueType, jint queueLength) {
  int tid = ProfiledThread::currentTid();
  if (tid < 0) {
    return;
  }
  int origin_tid = VMThread::nativeThreadId(env, origin);
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
                                                       jobject unused) {
  return TSC::ticks();
}

extern "C" DLLEXPORT jlong JNICALL
Java_com_datadoghq_profiler_JavaProfiler_tscFrequency0(JNIEnv *env,
                                                       jobject unused) {
  return TSC::frequency();
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_mallocArenaMax0(JNIEnv *env,
                                                         jobject unused,
                                                         jint maxArenas) {
  OS::mallocArenaMax(maxArenas);
}

extern "C" DLLEXPORT jstring JNICALL
Java_com_datadoghq_profiler_JVMAccess_findStringJVMFlag0(JNIEnv *env,
                                                         jobject unused,
                                                         jstring flagName) {
  JniString flag_str(env, flagName);
  ddprof::JVMFlag *f = ddprof::JVMFlag::find(flag_str.c_str(), {ddprof::JVMFlag::Type::String, ddprof::JVMFlag::Type::Stringlist});
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
  ddprof::JVMFlag *f = ddprof::JVMFlag::find(flag_str.c_str(), {ddprof::JVMFlag::Type::String, ddprof::JVMFlag::Type::Stringlist});
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
  ddprof::JVMFlag *f = ddprof::JVMFlag::find(flag_str.c_str(), {ddprof::JVMFlag::Type::Bool});
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
  ddprof::JVMFlag *f = ddprof::JVMFlag::find(flag_str.c_str(), {ddprof::JVMFlag::Type::Bool});
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
  ddprof::JVMFlag *f = ddprof::JVMFlag::find(flag_str.c_str(), {ddprof::JVMFlag::Type::Int, ddprof::JVMFlag::Type::Uint, ddprof::JVMFlag::Type::Intx, ddprof::JVMFlag::Type::Uintx, ddprof::JVMFlag::Type::Uint64_t, ddprof::JVMFlag::Type::Size_t});
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
  ddprof::JVMFlag *f = ddprof::JVMFlag::find(flag_str.c_str(),{ ddprof::JVMFlag::Type::Double});
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

extern "C" DLLEXPORT jlong JNICALL
Java_com_datadoghq_profiler_ActiveBitmap_bitmapAddressFor0(JNIEnv *env,
		                                     jclass unused,
						     jint tid) {
  u64* bitmap = Profiler::instance()->threadFilter()->bitmapAddressFor((int)tid);
  return (jlong)bitmap;
}

extern "C" DLLEXPORT jboolean JNICALL
Java_com_datadoghq_profiler_ActiveBitmap_isActive0(JNIEnv *env,
                                                   jclass unused,
                                                   jint tid) {
  return Profiler::instance()->threadFilter()->accept((int)tid) ? JNI_TRUE : JNI_FALSE;
}

extern "C" DLLEXPORT jlong JNICALL
Java_com_datadoghq_profiler_ActiveBitmap_getActiveCountAddr0(JNIEnv *env,
                                                              jclass unused) {
  return (jlong)Profiler::instance()->threadFilter()->addressOfSize();
}