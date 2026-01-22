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

#include "vmStructs_dd.h"
#include "common.h"
#include "j9Ext.h"
#include "safeAccess.h"
#include "vector"
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

namespace ddprof {
  bool HeapUsage::is_jmx_attempted = false;
  bool HeapUsage::is_jmx_supported = false; // default to not-supported

  void HeapUsage::initJMXUsage(JNIEnv *env) {
    if (is_jmx_attempted) {
      // do not re-run the initialization
      return;
    }
    is_jmx_attempted = true;
    jclass factory = env->FindClass("java/lang/management/ManagementFactory");
    if (!jniExceptionCheck(env) || factory == nullptr) {
      return;
    }
    jclass memoryBeanClass = env->FindClass("java/lang/management/MemoryMXBean");
    if (!jniExceptionCheck(env) || memoryBeanClass == nullptr) {
      return;
    }
    jmethodID get_memory = env->GetStaticMethodID(
        factory, "getMemoryMXBean", "()Ljava/lang/management/MemoryMXBean;");
    if (!jniExceptionCheck(env) || get_memory == nullptr) {
      return;
    }
    jobject memoryBean = env->CallStaticObjectMethod(factory, get_memory);
    if (!jniExceptionCheck(env) || memoryBean == nullptr) {
      return;
    }
    jmethodID get_heap = env->GetMethodID(memoryBeanClass, "getHeapMemoryUsage",
                                          "()Ljava/lang/management/MemoryUsage;");
    if (!jniExceptionCheck(env) || get_heap == nullptr) {
      return;
    }
    env->CallObjectMethod(memoryBean, get_heap);
    if (!jniExceptionCheck(env)) {
      return;
    }
    // mark JMX as supported only after we were able to retrieve the memory usage
    is_jmx_supported = true;
  }

}