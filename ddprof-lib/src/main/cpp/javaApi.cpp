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

#include <fstream>
#include <sstream>
#include <errno.h>
#include <string.h>
#include "incbin.h"
#include "os.h"
#include "profiler.h"
#include "vmStructs.h"
#include "context.h"
#include "engine.h"
#include "thread.h"
#include "wallClock.h"
#include "counters.h"

static void throwNew(JNIEnv* env, const char* exception_class, const char* message) {
    jclass cls = env->FindClass(exception_class);
    if (cls != NULL) {
        env->ThrowNew(cls, message);
    }
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_stop0(JNIEnv* env, jobject unused) {
    Error error = Profiler::instance()->stop();

    if (error) {
        throwNew(env, "java/lang/IllegalStateException", error.message());
    }
}

extern "C" DLLEXPORT jint JNICALL
Java_com_datadoghq_profiler_JavaProfiler_getTid0(JNIEnv* env, jobject unused) {
    return OS::threadId();
}

extern "C" DLLEXPORT jstring JNICALL
Java_com_datadoghq_profiler_JavaProfiler_execute0(JNIEnv* env, jobject unused, jstring command) {
    Arguments args;
    const char* command_str = env->GetStringUTFChars(command, NULL);
    Error error = args.parse(command_str);
    env->ReleaseStringUTFChars(command, command_str);

    if (error) {
        throwNew(env, "java/lang/IllegalArgumentException", error.message());
        return NULL;
    }

    Log::open(args);

    std::ostringstream out;
    error = Profiler::instance()->runInternal(args, out);
    if (!error) {
        if (out.tellp() >= 0x3fffffff) {
            throwNew(env, "java/lang/IllegalStateException", "Output exceeds string size limit");
            return NULL;
        }
        return env->NewStringUTF(out.str().c_str());
    }

    throwNew(env, "java/lang/IllegalStateException", error.message());
    return NULL;
}

extern "C" DLLEXPORT jlong JNICALL
Java_com_datadoghq_profiler_JavaProfiler_getSamples(JNIEnv* env, jobject unused) {
    return (jlong)Profiler::instance()->total_samples();
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_filterThread0(JNIEnv* env, jobject unused, jboolean enable) {
    int tid = ProfiledThread::currentTid();
    if (tid < 0) {
        return;
    }
    ThreadFilter* thread_filter = Profiler::instance()->threadFilter();
    if (enable) {
        thread_filter->add(tid);
    } else {
        thread_filter->remove(tid);
    }
}

extern "C" DLLEXPORT jobject JNICALL
Java_com_datadoghq_profiler_JavaProfiler_getContextPage0(JNIEnv* env, jobject unused, jint tid) {
    ContextPage page = Contexts::getPage((int) tid);
    return env->NewDirectByteBuffer((void*) page.storage, (jlong) page.capacity);
}

extern "C" DLLEXPORT jlong JNICALL
Java_com_datadoghq_profiler_JavaProfiler_getContextPageOffset0(JNIEnv* env, jobject unused, jint tid) {
    ContextPage page = Contexts::getPage((int) tid);
    return (jlong) page.storage;
}

extern "C" DLLEXPORT jint JNICALL
Java_com_datadoghq_profiler_JavaProfiler_getMaxContextPages0(JNIEnv* env, jobject unused) {
    return (jint) Contexts::getMaxPages();
}

extern "C" DLLEXPORT jboolean JNICALL
Java_com_datadoghq_profiler_JavaProfiler_recordTrace0(JNIEnv* env, jobject unused, jlong rootSpanId, jstring endpoint,
                                                      jint sizeLimit) {
    const char* endpoint_str = env->GetStringUTFChars(endpoint, NULL);
    jint length = env->GetStringUTFLength(endpoint);
    u32 label = Profiler::instance()->stringLabelMap()->bounded_lookup(endpoint_str, length, sizeLimit);
    bool acceptValue = label != INT_MAX;
    if (acceptValue) {
        TraceRootEvent event(rootSpanId, label);
        int tid = ProfiledThread::currentTid();
        Profiler::instance()->recordTraceRoot(tid, &event);
    }
    env->ReleaseStringUTFChars(endpoint, endpoint_str);
    return acceptValue;
}

extern "C" DLLEXPORT jint JNICALL
Java_com_datadoghq_profiler_JavaProfiler_registerConstant0(JNIEnv* env, jobject unused, jstring value) {
    const char* value_str = env->GetStringUTFChars(value, NULL);
    jint length = env->GetStringUTFLength(value);
    u32 encoding = Profiler::instance()->contextValueMap()->bounded_lookup(value_str, length, 1 << 16);
    env->ReleaseStringUTFChars(value, value_str);
    return encoding == INT_MAX ? -1 : encoding;
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_dump0(JNIEnv* env, jobject unused, jstring path) {
    const char* path_str = env->GetStringUTFChars(path, NULL);
    Profiler::instance()->dump(path_str, env->GetStringUTFLength(path));
    env->ReleaseStringUTFChars(path, path_str);
}

extern "C" DLLEXPORT jobject JNICALL
Java_com_datadoghq_profiler_JavaProfiler_getDebugCounters0(JNIEnv* env, jobject unused) {
    #ifdef COUNTERS
    return env->NewDirectByteBuffer((void*) Counters::getCounters(), (jlong) Counters::size());
    #else
    return env->NewDirectByteBuffer(nullptr, 0);
    #endif // COUNTERS
}

extern "C" DLLEXPORT jobjectArray JNICALL
Java_com_datadoghq_profiler_JavaProfiler_describeDebugCounters0(JNIEnv *env, jobject unused) {
    #ifdef COUNTERS
    std::vector<const char*> counter_names = Counters::describeCounters();
    jobjectArray array = (jobjectArray) env->NewObjectArray(counter_names.size(),
                                                            env->FindClass("java/lang/String"),env->NewStringUTF(""));
    for (int i = 0; i < counter_names.size(); i++) {
        env->SetObjectArrayElement(array, i, env->NewStringUTF(counter_names.at(i)));
    }
    return array;
    #else
    return nullptr;
    #endif // COUNTERS
}

extern "C" DLLEXPORT void JNICALL
Java_com_datadoghq_profiler_JavaProfiler_recordSettingEvent0(JNIEnv *env, jobject unused, jstring name, jstring value, jstring unit) {
    int tid = ProfiledThread::currentTid();
    if (tid < 0) {
        return;
    }
    int length = 0;
    const char* name_str = env->GetStringUTFChars(name, NULL);
    length += env->GetStringUTFLength(name);
    const char* value_str = env->GetStringUTFChars(value, NULL);
    length += env->GetStringUTFLength(value);
    const char* unit_str = env->GetStringUTFChars(unit, NULL);
    length += env->GetStringUTFLength(unit);
    Profiler::instance()->writeDatadogProfilerSetting(tid, length, name_str, value_str, unit_str);
    env->ReleaseStringUTFChars(name, name_str);
    env->ReleaseStringUTFChars(value, value_str);
    env->ReleaseStringUTFChars(unit, unit_str);
}
