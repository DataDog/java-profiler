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
#include "threadState.h"
#include "vmEntry.h"
#include "vmStructs.h"

namespace ddprof {
  using VMStructsBase = ::VMStructs;
  using VMMethodBase = ::VMMethod;

  class HeapUsage;

  class VMStructs : public VMStructsBase {
  public:
    typedef bool (*IsValidMethodFunc)(void *);
  protected:
    static CodeCache _unsafe_to_walk;
    static int _osthread_state_offset;
    static int _flag_type_offset;
    typedef HeapUsage (*HeapUsageFunc)(const void *);
    static HeapUsageFunc _heap_usage_func;

    typedef void *(*MemoryUsageFunc)(void *, void *, bool);
    static MemoryUsageFunc _memory_usage_func;

    typedef GCHeapSummary (*GCHeapSummaryFunc)(void *);
    static GCHeapSummaryFunc _gc_heap_summary_func;

    static IsValidMethodFunc _is_valid_method_func;
  private:
    static void initOffsets();
    static void initJvmFunctions();
    static void initUnsafeFunctions();
    static void initCriticalJNINatives();

    static void checkNativeBinding(jvmtiEnv *jvmti, JNIEnv *jni, jmethodID method,
                                  void *address);
    static const void *findHeapUsageFunc();
  public:
    static void init(CodeCache* libjvm);
    static bool isSafeToWalk(uintptr_t pc);

    static void JNICALL NativeMethodBind(jvmtiEnv *jvmti, JNIEnv *jni,
                                        jthread thread, jmethodID method,
                                        void *address, void **new_address_ptr);

    inline static int thread_osthread_offset() {
      return _thread_osthread_offset;
    }

    inline static int osthread_state_offset() {
      return _osthread_state_offset;
    }

    inline static int osthread_id_offset() {
      return _osthread_id_offset;
    }

    inline static int thread_state_offset() {
      return _thread_state_offset;
    }

    inline static int flag_type_offset() {
      return _flag_type_offset;
    }
    inline static int method_constmethod_offset() {
      return _method_constmethod_offset;
    }
    inline static int constmethod_constants_offset() {
      return _constmethod_constants_offset;
    }
    inline static int pool_holder_offset() {
      return _pool_holder_offset;
    }
    inline static int class_loader_data_offset() {
      return _class_loader_data_offset;
    }
    inline static IsValidMethodFunc is_valid_method_func() {
      return _is_valid_method_func;
    }

  };

  class VMMethod : public VMMethodBase {
  private:
    static bool check_jmethodID_J9(jmethodID id);
    static bool check_jmethodID_hotspot(jmethodID id);

  public:
    static ddprof::VMMethod *fromMethodID(jmethodID id) {
      return static_cast<ddprof::VMMethod*>(VMMethod::fromMethodID(id));
    }

    static bool check_jmethodID(jmethodID id);
  };

  // Copied from JDK's globalDefinitions.hpp 'JavaThreadState' enum
  enum JVMJavaThreadState {
    _thread_uninitialized     =  0, // should never happen (missing initialization)
    _thread_new_trans         =  3, // corresponding transition state (not used, included for completeness)
    _thread_in_native         =  4, // running in native code
    _thread_in_native_trans   =  5, // corresponding transition state
    _thread_in_vm             =  6, // running in VM
    _thread_in_vm_trans       =  7, // corresponding transition state
    _thread_in_Java           =  8, // running in Java or in stub code
    _thread_in_Java_trans     =  9, // corresponding transition state (not used, included for completeness)
    _thread_blocked           = 10, // blocked in vm
    _thread_blocked_trans     = 11, // corresponding transition state
    _thread_max_state         = 12  // maximum thread state+1 - used for statistics allocation
  };

  class VMThread : public ::VMThread {
  private:
    const char* at(int offset) {
      return (const char*)this + offset;
    }
  public:
    static ddprof::VMThread* current() {
      return static_cast<ddprof::VMThread*>(::VMThread::current());
    }

    OSThreadState osThreadState() {
      if (ddprof::VMStructs::thread_osthread_offset() >= 0 && ddprof::VMStructs::osthread_state_offset() >= 0) {
        const char *osthread = *(char **)at(ddprof::VMStructs::thread_osthread_offset());
        if (osthread != nullptr) {
          // If the location is not accessible, the thread must have been terminated
          int value = SafeAccess::safeFetch32((int*)(osthread + ddprof::VMStructs::osthread_state_offset()),
                                            static_cast<int>(OSThreadState::TERMINATED));
          // Checking for bad data
          if (value > static_cast<int>(OSThreadState::SYSCALL)) {
            return OSThreadState::TERMINATED;
          }
          return static_cast<OSThreadState>(value);
        }
     }
     return OSThreadState::UNKNOWN;
    }

    int osThreadId() {
      if (ddprof::VMStructs::thread_osthread_offset() >= 0 && ddprof::VMStructs::osthread_id_offset() >=0) {
        const char* osthread = *(const char**) at(ddprof::VMStructs::thread_osthread_offset());
        if (osthread == nullptr) {
          return -1;
        } else {
          return SafeAccess::safeFetch32((int*)(osthread + ddprof::VMStructs::osthread_id_offset()), -1);
        }
      }
      return -1;
    }

    int state() {
      int offset = ddprof::VMStructs::thread_state_offset();
      if (offset >= 0) {
          int* state = (int*)at(offset);
          if (state == nullptr) {
            return 0;
          } else {
            int value = SafeAccess::safeFetch32(state, 0);
            // Checking for bad data
            if (value > _thread_max_state) {
              value = 0;
            }
            return value;
          }
      }
      return 0;
    }
  };

  // Bootstrape class loader is immortal. Therefore, classes/methods
  // that are loaded by it, are safe to walk.
  class BootstrapClassLoader : public ::VMStructs {
    private:
      // java.lang.Object must be loaded by bootstrap class loader.
      // _object_klass points to java/lang/Object instanceKlass stored in vmClasses,
      // and we use it to figure out if classes/methods are loaded by bootstrap classloader
      static ::VMKlass** _object_klass_addr;
    
    public:
      static void set_object_klass_location(::VMKlass** addr) {
        _object_klass_addr = addr;
      }

      // If a Method is loaded by BootstrapClassLoader
      static bool loaded_by(::VMMethod* method) {
        return loaded_by(method->method_holder());
      }

      static bool loaded_by(::VMKlass* klass) {
        VMKlass* object_klass = *_object_klass_addr;
        assert(object_klass != nullptr);
        assert(klass != nullptr);
        return object_klass->classLoaderData() == klass->classLoaderData();
      }
  };

  class PlatformClassLoader : public ::VMStructs {
    private:
      static ::VMKlass* _class_loader;
    
    public:
      static void set_platform_classloader(JNIEnv* env, jclass cls) {
        _class_loader = ::VMKlass::fromJavaClass(env, cls);
      }
      static bool loaded_by(::VMKlass* klass) {
        return _class_loader != nullptr && _class_loader->classLoaderData() == klass->classLoaderData();
      }
      static bool loaded_by(::VMMethod* method) {
        return loaded_by(method->method_holder());
      }
  };

  class ApplicationClassLoader : public ::VMStructs {
    private:
      static ::VMKlass* _class_loader;
    
    public:
      static void set_application_classloader(JNIEnv* env, jclass cls) {
        _class_loader = ::VMKlass::fromJavaClass(env, cls);
      }

      static bool loaded_by(::VMKlass* klass) {
        return _class_loader != nullptr && _class_loader->classLoaderData() == klass->classLoaderData();
      }

      static bool loaded_by(::VMMethod* method) {
        return loaded_by(method->method_holder());
      }
  };

  class ClassLoader {
    public:
      static bool loaded_by_known_classloader(JNIEnv* env, jclass cls) {
        ::VMKlass* klass = ::VMKlass::fromJavaClass(env, cls);
        return BootstrapClassLoader::loaded_by(klass) ||
               PlatformClassLoader::loaded_by(klass) ||
               ApplicationClassLoader::loaded_by(klass);
      }

      static bool loaded_by_known_classloader(::VMMethod* method) {
        return BootstrapClassLoader::loaded_by(method) ||
               PlatformClassLoader::loaded_by(method) ||
               ApplicationClassLoader::loaded_by(method);
      }
  };

  class JVMFlag : public VMStructs {
  private:
    enum {
        ORIGIN_DEFAULT = 0,
        ORIGIN_MASK    = 15,
        SET_ON_CMDLINE = 1 << 17
    };
    static JVMFlag* find(const char *name, int type_mask);
  public:
    enum Type {
      Bool = 0,
      Int = 1,
      Uint = 2,
      Intx = 3,
      Uintx = 4,
      Uint64_t = 5,
      Size_t = 6,
      Double = 7,
      String = 8,
      Stringlist = 9,
      Unknown = -1
    };

    static JVMFlag* find(const char *name);
    static JVMFlag *find(const char *name, std::initializer_list<Type> types);

    const char *name() { return *(const char **)at(_flag_name_offset); }
    int type();

    void *addr() { return *(void **)at(_flag_addr_offset); }

    char origin() {
        return _flag_origin_offset >= 0 ? (*(char*) at(_flag_origin_offset)) & 15 : 0;
    }

    bool isDefault() {
        return _flag_origin_offset < 0 || (*(int*) at(_flag_origin_offset) & ORIGIN_MASK) == ORIGIN_DEFAULT;
    }

    void setCmdline() {
        if (_flag_origin_offset >= 0) {
            *(int*) at(_flag_origin_offset) |= SET_ON_CMDLINE;
        }
    }

    char get() {
        return *((char*)addr());
    }

    void set(char value) {
        *((char*)addr()) = value;
    }
  };

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
