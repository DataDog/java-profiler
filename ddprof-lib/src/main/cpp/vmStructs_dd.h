/*
 * Copyright 2021, 2025 Datadog, Inc
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

#ifndef _VMSTRUCTS_DD_H
#define _VMSTRUCTS_DD_H

#include "common.h"
#include "jniHelper.h"
#include "jvmHeap.h"
#include "safeAccess.h"
#include "vmEntry.h"
#include "vmStructs.h"

namespace ddprof {
  class HeapUsage : VMStructs {
  private:
    static bool is_jmx_attempted;
    static bool is_jmx_supported; // default to not-supported
  public:


    size_t _initSize = -1;
    size_t _used = -1;
    size_t _committed = -1;
    size_t _maxSize = -1;
    size_t _used_at_last_gc = -1;

    static void initJMXUsage(JNIEnv* env);

    static bool isJMXSupported() {
      initJMXUsage(VM::jni());
      return is_jmx_supported;
    }


    static bool isLastGCUsageSupported() {
      // only supported for JDK 17+
      // the CollectedHeap structure is vastly different in JDK 11 and earlier so
      // we can't support it
      return _collected_heap_addr != NULL && _heap_usage_func != NULL;
    }

    static bool needsNativeBindingInterception() {
      return _collected_heap_addr == NULL ||
            (_heap_usage_func == NULL && _gc_heap_summary_func == NULL);
    }

    static jlong getMaxHeap(JNIEnv *env) {
      static jclass _rt;
      static jmethodID _get_rt;
      static jmethodID _max_memory;

      if (!(_rt = env->FindClass("java/lang/Runtime"))) {
        jniExceptionCheck(env);
        return -1;
      }

      if (!(_get_rt = env->GetStaticMethodID(_rt, "getRuntime",
                                            "()Ljava/lang/Runtime;"))) {
        jniExceptionCheck(env);
        return -1;
      }

      if (!(_max_memory = env->GetMethodID(_rt, "maxMemory", "()J"))) {
        jniExceptionCheck(env);
        return -1;
      }

      jobject rt = (jobject)env->CallStaticObjectMethod(_rt, _get_rt);
      jlong ret = (jlong)env->CallLongMethod(rt, _max_memory);
      if (jniExceptionCheck(env)) {
        return -1;
      }
      return ret;
    }

    static HeapUsage get() { return get(true); }

    static HeapUsage get(bool allow_jmx) {
      HeapUsage usage;
      if (_collected_heap_addr != NULL) {
        if (_heap_usage_func != NULL) {
          // this is the JDK 17+ path
          usage = _heap_usage_func(*_collected_heap_addr);
          usage._used_at_last_gc =
              ((CollectedHeapWrapper *)*_collected_heap_addr)->_used_at_last_gc;
        } else if (_gc_heap_summary_func != NULL) {
          // this is the JDK 11 path
          // we need to collect GCHeapSummary information first
          GCHeapSummary summary = _gc_heap_summary_func(*_collected_heap_addr);
          usage._initSize = -1;
          usage._used = summary.used();
          usage._committed = -1;
          usage._maxSize = summary.maxSize();
        }
      }
      if (usage._maxSize == -1 && _memory_usage_func != NULL && allow_jmx && isJMXSupported()) {
        // this path is for non-hotspot JVMs
        // we need to patch the native method binding for JMX GetMemoryUsage to
        // capture the native method pointer first also, it requires JMX and
        // allocating new objects so it really should not be used in a GC callback
        JNIEnv *env = VM::jni();
        if (env == NULL) {
          return usage;
        }
        jobject m_usage =
            (jobject)_memory_usage_func(env, (jobject)NULL, (jboolean) true);
        jclass cls = env->GetObjectClass(m_usage);
        jfieldID init_fid = env->GetFieldID(cls, "init", "J");
        jfieldID max_fid = env->GetFieldID(cls, "max", "J");
        jfieldID used_fid = env->GetFieldID(cls, "used", "J");
        jfieldID committed_fid = env->GetFieldID(cls, "committed", "J");
        if (init_fid == NULL || max_fid == NULL || used_fid == NULL ||
            committed_fid == NULL) {
          return usage;
        }
        usage._initSize = env->GetLongField(m_usage, init_fid);
        usage._maxSize = env->GetLongField(m_usage, max_fid);
        usage._used = env->GetLongField(m_usage, used_fid);
        usage._committed = env->GetLongField(m_usage, committed_fid);
      }
      return usage;
    }
  };
}

#endif // _VMSTRUCTS_DD_H
