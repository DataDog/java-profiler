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
#include "spinLock.h"
#include "vector"
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

namespace ddprof {
  using VMStructs_ = ::ddprof::VMStructs;

  int VMStructs_::_flag_type_offset = -1;
  int VMStructs_::_osthread_state_offset = -1;

  CodeCache VMStructs_::_unsafe_to_walk("unwalkable code");

  VMStructs_::HeapUsageFunc VMStructs_::_heap_usage_func = NULL;
  VMStructs_::MemoryUsageFunc VMStructs_::_memory_usage_func = NULL;
  VMStructs_::GCHeapSummaryFunc VMStructs_::_gc_heap_summary_func = NULL;
  VMStructs_::IsValidMethodFunc VMStructs_::_is_valid_method_func = NULL;


  // Run at agent load time
  void VMStructs_::init(CodeCache* libjvm) {
    VMStructsBase::init(libjvm);
    initOffsets();
    initJvmFunctions();
    initUnsafeFunctions();
    initSafeFetch(libjvm);
  }

  void VMStructs_::initOffsets() {
    uintptr_t entry = readSymbol("gHotSpotVMStructs");
    uintptr_t stride = readSymbol("gHotSpotVMStructEntryArrayStride");
    uintptr_t type_offset = readSymbol("gHotSpotVMStructEntryTypeNameOffset");
    uintptr_t field_offset = readSymbol("gHotSpotVMStructEntryFieldNameOffset");
    uintptr_t offset_offset = readSymbol("gHotSpotVMStructEntryOffsetOffset");
    uintptr_t address_offset = readSymbol("gHotSpotVMStructEntryAddressOffset");

    if (entry == 0 || stride == 0) {
      return;
    }

    for (;; entry += stride) {
      const char *type = *(const char **)(entry + type_offset);
      const char *field = *(const char **)(entry + field_offset);
      if (type == NULL || field == NULL) {
        break;
      }

      if (strcmp(type, "OSThread") == 0) {
        if (strcmp(field, "_state") == 0) {
          TEST_LOG("Setting _osthread_state_offset value");
          _osthread_state_offset = *(int *)(entry + offset_offset);
        }
      } else if (strcmp(type, "JVMFlag") == 0 || strcmp(type, "Flag") == 0) {
        if (strcmp(field, "_type") == 0 || strcmp(field, "type") == 0) {
          _flag_type_offset = *(int *)(entry + offset_offset);
        }
      }
    }
  }

  void VMStructs_::initUnsafeFunctions() {
    // see
    // https://github.com/openjdk/jdk/blob/master/src/hotspot/share/gc/z/zBarrierSetRuntime.hpp#L33
    // https://bugs.openjdk.org/browse/JDK-8302317
    std::vector<const char *> unsafeMangledPrefixes{"_ZN18ZBarrierSetRuntime",
                                                    "_ZN9JavaCalls11call_helper",
                                                    "_ZN14MM_RootScanner"};

    std::vector<const void *> symbols;
    _libjvm->findSymbolsByPrefix(unsafeMangledPrefixes, symbols);
    for (const void *symbol : symbols) {
      CodeBlob *blob = _libjvm->findBlobByAddress(symbol);
      if (blob) {
        _unsafe_to_walk.add(blob->_start,
                            ((uintptr_t)blob->_end - (uintptr_t)blob->_start),
                            blob->_name, true);
      }
    }
  }

  void VMStructs_::initSafeFetch(CodeCache* libjvm) {
    SafeAccess::initSafeFetch(libjvm);
  }

  const void *VMStructs_::findHeapUsageFunc() {
    if (VM::hotspot_version() < 17) {
      // For JDK 11 it is really unreliable to find the memory_usage function -
      // just disable it
      return nullptr;
    } else {
      JVMFlag* flag = JVMFlag::find("UseG1GC", {JVMFlag::Type::Bool});
      if (flag != NULL && flag->get()) {
        // The CollectedHeap::memory_usage function is a virtual one -
        // G1, Shenandoah and ZGC are overriding it and calling the base class
        // method results in asserts triggering. Therefore, we try to locate the
        // concrete overridden method form.
          return _libjvm->findSymbol("_ZN15G1CollectedHeap12memory_usageEv");
      }
      flag = JVMFlag::find("UseShenandoahGC", {JVMFlag::Type::Bool});
      if (flag != NULL && flag->get()) {
        return _libjvm->findSymbol("_ZN14ShenandoahHeap12memory_usageEv");
      }
      flag = JVMFlag::find("UseZGC", {JVMFlag::Type::Bool});
      if (flag != NULL && flag->get() && VM::hotspot_version() < 21) {
        // acessing this method in JDK 21 (generational ZGC) wil cause SIGSEGV
        return _libjvm->findSymbol("_ZN14ZCollectedHeap12memory_usageEv");
      }
      return _libjvm->findSymbol("_ZN13CollectedHeap12memory_usageEv");
    }
  }

  void VMStructs_::initJvmFunctions() {
    _heap_usage_func = (HeapUsageFunc)findHeapUsageFunc();
    _gc_heap_summary_func = (GCHeapSummaryFunc)_libjvm->findSymbol(
        "_ZN13CollectedHeap19create_heap_summaryEv");
    _is_valid_method_func = (IsValidMethodFunc)_libjvm->findSymbol(
        "_ZN6Method15is_valid_methodEPKS_");
  }

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
    VMStructs_::IsValidMethodFunc func = VMStructs_::is_valid_method_func();
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

    if (VMStructs_::method_constmethod_offset() >= 0) {
      const_method = (const char *)SafeAccess::load(
          (void **)(method_ptr + VMStructs_::method_constmethod_offset()));
      if (const_method == NULL) {
        return false;
      }
    }
    if (VMStructs_::constmethod_constants_offset() >= 0) {
      cpool = (const char *)SafeAccess::load(
          (void **)(const_method + VMStructs_::constmethod_constants_offset()));
      if (cpool == NULL) {
        return false;
      }
    }
    if (VMStructs_::pool_holder_offset() >= 0) {
      cpool_holder =
          (const char *)SafeAccess::load((void **)(cpool + VMStructs_::pool_holder_offset()));
      if (cpool_holder == NULL) {
        return false;
      }
    }
    if (VMStructs_::class_loader_data_offset() >= 0) {
      cl_data = (const char *)SafeAccess::load(
          (void **)(cpool_holder + VMStructs_::class_loader_data_offset()));
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

  JVMFlag *JVMFlag::find(const char *name) {
    if (_flags_addr != NULL && _flag_size > 0) {
      for (int i = 0; i < _flag_count; i++) {
        JVMFlag *f = (JVMFlag *)(_flags_addr + i * _flag_size);
        if (f->name() != NULL && strcmp(f->name(), name) == 0&& f->addr() != NULL) {
          return f;
        }
      }
    }
    return NULL;
  }

  JVMFlag *JVMFlag::find(const char *name, std::initializer_list<JVMFlag::Type> types) {
    int mask = 0;
    for (int type : types) {
      mask |= 0x1 << type;
    }
    return find(name, mask);
  }

  int JVMFlag::type() {
    if (VM::hotspot_version() < 16) { // in JDK 16 the JVM flag implementation has changed
      char* type_name = *(char **)at(_flag_type_offset);
      if (type_name == NULL) {
        return JVMFlag::Type::Unknown;
      }
      if (strcmp(type_name, "bool") == 0) {
        return JVMFlag::Type::Bool;
      } else if (strcmp(type_name, "int") == 0) {
        return JVMFlag::Type::Int;
      } else if (strcmp(type_name, "uint") == 0) {
        return JVMFlag::Type::Uint;
      } else if (strcmp(type_name, "intx") == 0) {
        return JVMFlag::Type::Intx;
      } else if (strcmp(type_name, "uintx") == 0) {
        return JVMFlag::Type::Uintx;
      } else if (strcmp(type_name, "uint64_t") == 0) {
        return JVMFlag::Type::Uint64_t;
      } else if (strcmp(type_name, "size_t") == 0) {
        return JVMFlag::Type::Size_t;
      } else if (strcmp(type_name, "double") == 0) {
          return JVMFlag::Type::Double;
      } else if (strcmp(type_name, "ccstr") == 0) {
        return JVMFlag::Type::String;
      } else if (strcmp(type_name, "ccstrlist") == 0) {
        return JVMFlag::Type::Stringlist;
      } else {
        return JVMFlag::Type::Unknown;
      }
    } else {
      return *(int *)at(_flag_type_offset);
    }
  }

  JVMFlag *JVMFlag::find(const char *name, int type_mask) {
    if (_flags_addr != NULL && _flag_size > 0) {
      for (int i = 0; i < _flag_count; i++) {
        JVMFlag *f = (JVMFlag *)(_flags_addr + i * _flag_size);
        if (f->name() != NULL && strcmp(f->name(), name) == 0) {
          int masked = 0x1 << f->type();
          if (masked & type_mask) {
              return (JVMFlag*)f;
          }
        }
      }
    }
    return NULL;
  }

  bool VMStructs_::isSafeToWalk(uintptr_t pc) {
    return !(_unsafe_to_walk.contains((const void *)pc) &&
            _unsafe_to_walk.findFrameDesc((const void *)pc));
  }

  void VMStructs_::NativeMethodBind(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
                                  jmethodID method, void *address,
                                  void **new_address_ptr) {
    static SpinLock _lock;
    static int delayedCounter = 0;
    static void **delayed = (void **)malloc(512 * sizeof(void *) * 2);

    if (_memory_usage_func == NULL) {
      if (jvmti != NULL && jni != NULL) {
        checkNativeBinding(jvmti, jni, method, address);
        void **tmpDelayed = NULL;
        int tmpCounter = 0;
        _lock.lock();
        if (delayed != NULL && delayedCounter > 0) {
          // in order to minimize the lock time, we copy the delayed list, free it
          // and release the lock
          tmpCounter = delayedCounter;
          tmpDelayed = (void **)malloc(tmpCounter * sizeof(void *) * 2);
          memcpy(tmpDelayed, delayed, tmpCounter * sizeof(void *) * 2);
          delayedCounter = 0;
          delayed = NULL;
          free(delayed);
        }
        _lock.unlock();
        // if there was a delayed list, we check it now, not blocking on the lock
        if (tmpDelayed != NULL) {
          for (int i = 0; i < tmpCounter; i += 2) {
            checkNativeBinding(jvmti, jni, (jmethodID)tmpDelayed[i],
                              tmpDelayed[i + 1]);
          }
          // don't forget to free the tmp list
          free(tmpDelayed);
        }
      } else {
        _lock.lock();
        if (delayed != NULL) {
          delayed[delayedCounter] = method;
          delayed[delayedCounter + 1] = address;
          delayedCounter += 2;
        }
        _lock.unlock();
      }
    }
  }

  void VMStructs_::checkNativeBinding(jvmtiEnv *jvmti, JNIEnv *jni,
                                    jmethodID method, void *address) {
    char *method_name;
    char *method_sig;
    int error = 0;
    if ((error = jvmti->GetMethodName(method, &method_name, &method_sig, NULL)) ==
        0) {
      if (strcmp(method_name, "getMemoryUsage0") == 0 &&
          strcmp(method_sig, "(Z)Ljava/lang/management/MemoryUsage;") == 0) {
        _memory_usage_func = (MemoryUsageFunc)address;
      }
    }
    jvmti->Deallocate((unsigned char *)method_sig);
    jvmti->Deallocate((unsigned char *)method_name);
  }
}