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

  /**
   * jmethodIDs are unreliable, even if the profiler has created strong global JNI
   * references to the classes containing methods with those jmethodIDs. This is
   * affecting particularly hard the 'record-on-shutdown' feature when the VM
   * class structures seem to be aggressively cleaned-up despite JNI global
   * references pointing to them are still there. This check is attempting to
   * validate that all data structures required to reconstruct the method metadata
   * from a jmethodID are still readable at this point.
   */
  bool VMMethod::check_jmethodID(jmethodID id) {
    if (id == NULL) {
      return false;
    }
    if (VM::isOpenJ9()) {
      return check_jmethodID_J9(id);
    }
    return check_jmethodID_hotspot(id);
  }

  bool VMMethod::check_jmethodID_hotspot(jmethodID id) {
    const char *method_ptr = (const char *)SafeAccess::load((void **)id);
    // check for NULL ptr and 'empty' ptr (JNIMethodBlock::_free_method)
    if (method_ptr == NULL || (size_t)method_ptr == 55) {
      return false;
    }
    VMStructs::IsValidMethodFunc func = VMStructs::is_valid_method_func();
    if (func != NULL) {
      if (!func((void *)method_ptr)) {
        return false;
      }
    }
    // we can only perform the extended validity check if there are expected
    // vmStructs in place

    const char *const_method = NULL;
    const char *cpool = NULL;
    const char *cpool_holder = NULL;
    const char *cl_data = NULL;

    if (VMStructs::method_constmethod_offset() >= 0) {
      const_method = (const char *)SafeAccess::load(
          (void **)(method_ptr + VMStructs::method_constmethod_offset()));
      if (const_method == NULL) {
        return false;
      }
    }
    if (VMStructs::constmethod_constants_offset() >= 0) {
      cpool = (const char *)SafeAccess::load(
          (void **)(const_method + VMStructs::constmethod_constants_offset()));
      if (cpool == NULL) {
        return false;
      }
    }
    if (VMStructs::pool_holder_offset() >= 0) {
      cpool_holder =
          (const char *)SafeAccess::load((void **)(cpool + VMStructs::pool_holder_offset()));
      if (cpool_holder == NULL) {
        return false;
      }
    }
    if (VMStructs::class_loader_data_offset() >= 0) {
      cl_data = (const char *)SafeAccess::load(
          (void **)(cpool_holder + VMStructs::class_loader_data_offset()));
      if (cl_data == NULL) {
        return false;
      }
    }
    return true;
  }

  bool VMMethod::check_jmethodID_J9(jmethodID id) {
    // the J9 jmethodid check is not working properly, so we just check for NULL
    return id != NULL && *((void **)id) != NULL;
  }
}