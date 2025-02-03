/*
 * Copyright 2017 Andrei Pangin
 * Copyright 2022, 2023 Datadog, Inc
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

#ifndef _VMSTRUCTS_H
#define _VMSTRUCTS_H

#include "codeCache.h"
#include "jniHelper.h"
#include "jvmHeap.h"
#include "safeAccess.h"
#include "threadState.h"
#include "vmEntry.h"

#include <initializer_list>
#include <jvmti.h>
#include <stdint.h>
#include <string.h>

class HeapUsage;

class VMStructs {
protected:
  static CodeCache *_libjvm;
  static CodeCache _unsafe_to_walk;

  static bool _has_class_names;
  static bool _has_method_structs;
  static bool _has_compiler_structs;
  static bool _has_stack_structs;
  static bool _has_class_loader_data;
  static bool _has_native_thread_id;
  static bool _has_perm_gen;

  static int _klass_name_offset;
  static int _symbol_length_offset;
  static int _symbol_length_and_refcount_offset;
  static int _symbol_body_offset;
  static int _class_loader_data_offset;
  static int _class_loader_data_next_offset;
  static int _methods_offset;
  static int _jmethod_ids_offset;
  static int _thread_osthread_offset;
  static int _thread_anchor_offset;
  static int _thread_state_offset;
  static int _thread_vframe_offset;
  static int _thread_exception_offset;
  static int _osthread_id_offset;
  static int _osthread_state_offset;
  static int _call_wrapper_anchor_offset;
  static int _comp_env_offset;
  static int _comp_task_offset;
  static int _comp_method_offset;
  static int _anchor_sp_offset;
  static int _anchor_pc_offset;
  static int _anchor_fp_offset;
  static int _frame_size_offset;
  static int _frame_complete_offset;
  static int _code_offset;
  static int _data_offset;
  static int _scopes_pcs_offset;
  static int _scopes_data_offset;
  static int _nmethod_name_offset;
  static int _nmethod_method_offset;
  static int _nmethod_entry_offset;
  static int _nmethod_state_offset;
  static int _nmethod_level_offset;
  static int _nmethod_metadata_offset;
  static int _nmethod_immutable_offset;
  static int _method_constmethod_offset;
  static int _method_code_offset;
  static int _constmethod_constants_offset;
  static int _constmethod_idnum_offset;
  static int _constmethod_size;
  static int _pool_holder_offset;
  static int _array_data_offset;
  static int _code_heap_memory_offset;
  static int _code_heap_segmap_offset;
  static int _code_heap_segment_shift;
  static int _heap_block_used_offset;
  static int _vs_low_bound_offset;
  static int _vs_high_bound_offset;
  static int _vs_low_offset;
  static int _vs_high_offset;
  static int _flag_type_offset;
  static int _flag_name_offset;
  static int _flag_addr_offset;
  static const char *_flags_addr;
  static int _flag_count;
  static int _flag_size;
  static char *_code_heap[3];
  static const void *_code_heap_low;
  static const void *_code_heap_high;
  static char **_code_heap_addr;
  static const void **_code_heap_low_addr;
  static const void **_code_heap_high_addr;
  static int *_klass_offset_addr;
  static char **_narrow_klass_base_addr;
  static char *_narrow_klass_base;
  static int *_narrow_klass_shift_addr;
  static int _narrow_klass_shift;
  static char **_collected_heap_addr;
  static char *_collected_heap;
  static int _collected_heap_reserved_offset;
  static int _region_start_offset;
  static int _region_size_offset;
  static int _markword_klass_shift;
  static int _markword_monitor_value;
  static int _entry_frame_call_wrapper_offset;
  static int _interpreter_frame_bcp_offset;
  static unsigned char _unsigned5_base;
  static const void **_call_stub_return_addr;
  static const void *_call_stub_return;
  static const void *_interpreted_frame_valid_start;
  static const void *_interpreted_frame_valid_end;

  static jfieldID _eetop;
  static jfieldID _tid;
  static jfieldID _klass;
  static int _tls_index;

  typedef void (*LockFunc)(void *);
  static LockFunc _lock_func;
  static LockFunc _unlock_func;

  typedef HeapUsage (*HeapUsageFunc)(const void *);
  static HeapUsageFunc _heap_usage_func;

  typedef void *(*MemoryUsageFunc)(void *, void *, bool);
  static MemoryUsageFunc _memory_usage_func;

  typedef GCHeapSummary (*GCHeapSummaryFunc)(void *);
  static GCHeapSummaryFunc _gc_heap_summary_func;

  typedef void *(*FindFlagFunc)(const char *, size_t, bool, bool);
  static FindFlagFunc _find_flag_func;

  typedef bool (*IsValidMethodFunc)(void *);
  static IsValidMethodFunc _is_valid_method_func;

  static uintptr_t readSymbol(const char *symbol_name);
  static void initOffsets();
  static void resolveOffsets();
  static void patchSafeFetch();
  static void initJvmFunctions();
  static void initTLS(void *vm_thread);
  static void initThreadBridge(JNIEnv *env);
  static void initLogging(JNIEnv *env);
  static void initUnsafeFunctions();
  static void initMemoryUsage(JNIEnv *env);

  static bool goodPtr(const void* ptr) {
    return (uintptr_t)ptr >= 0x1000 && ((uintptr_t)ptr & (sizeof(uintptr_t) - 1)) == 0;
  }

  const char *at(int offset) { return (const char *)this + offset; }

  static bool aligned(const void *ptr) {
    return ((uintptr_t)ptr & (sizeof(uintptr_t) - 1)) == 0;
  }

  template <typename T> static T align(const void *ptr) {
    return (T)((uintptr_t)ptr & ~(sizeof(T) - 1));
  }

  static void checkNativeBinding(jvmtiEnv *jvmti, JNIEnv *jni, jmethodID method,
                                 void *address);

private:
  static const void *findHeapUsageFunc();
  static bool isFlagTrue(const char *name);

public:
  static void init(CodeCache *libjvm);
  static void ready();

  static CodeCache *libjvm() { return _libjvm; }

  static bool hasClassNames() { return _has_class_names; }

  static bool hasMethodStructs() { return _has_method_structs; }

  static bool hasCompilerStructs() { return _has_compiler_structs; }

  static bool hasStackStructs() { return _has_stack_structs; }

  static bool hasClassLoaderData() { return _has_class_loader_data; }

  static bool hasJavaThreadId() { return _tid != NULL; }

  static bool isInterpretedFrameValidFunc(const void *pc) {
    return pc >= _interpreted_frame_valid_start &&
           pc < _interpreted_frame_valid_end;
  }

  static bool isSafeToWalk(uintptr_t pc);

  static void JNICALL NativeMethodBind(jvmtiEnv *jvmti, JNIEnv *jni,
                                       jthread thread, jmethodID method,
                                       void *address, void **new_address_ptr);
};

class MethodList {
public:
  enum { SIZE = 8 };

private:
  intptr_t _method[SIZE];
  int _ptr;
  MethodList *_next;
  int _padding;

public:
  MethodList(MethodList *next) : _ptr(0), _next(next), _padding(0) {
    for (int i = 0; i < SIZE; i++) {
      _method[i] = 0x37;
    }
  }
};

class NMethod;

class VMSymbol : VMStructs {
public:
  unsigned short length() {
    if (_symbol_length_offset >= 0) {
      return *(unsigned short *)at(_symbol_length_offset);
    } else {
      return *(unsigned int *)at(_symbol_length_and_refcount_offset) >> 16;
    }
  }

  const char *body() { return at(_symbol_body_offset); }
};

class ClassLoaderData : VMStructs {
private:
  void *mutex() { return *(void **)at(sizeof(uintptr_t) * 3); }

public:
  void lock() { _lock_func(mutex()); }

  void unlock() { _unlock_func(mutex()); }

  MethodList **methodList() {
    return (MethodList **)at(sizeof(uintptr_t) * 6 + 8);
  }
};

class VMKlass : VMStructs {
public:
  static VMKlass *fromJavaClass(JNIEnv *env, jclass cls) {
    if (_has_perm_gen) {
      jobject klassOop = env->GetObjectField(cls, _klass);
      return (VMKlass *)(*(uintptr_t **)klassOop + 2);
    } else if (sizeof(VMKlass *) == 8) {
      return (VMKlass *)(uintptr_t)env->GetLongField(cls, _klass);
    } else {
      return (VMKlass *)(uintptr_t)env->GetIntField(cls, _klass);
    }
  }

  static VMKlass *fromHandle(uintptr_t handle) {
    if (_has_perm_gen) {
      // On JDK 7 KlassHandle is a pointer to klassOop, hence one more
      // indirection
      return (VMKlass *)(*(uintptr_t **)handle + 2);
    } else {
      return (VMKlass *)handle;
    }
  }

  VMSymbol *name() { return *(VMSymbol **)at(_klass_name_offset); }

  ClassLoaderData *classLoaderData() {
    return *(ClassLoaderData **)at(_class_loader_data_offset);
  }

  int methodCount() {
    int *methods = *(int **)at(_methods_offset);
    return methods == NULL ? 0 : *methods & 0xffff;
  }

  jmethodID *jmethodIDs() {
    return __atomic_load_n((jmethodID **)at(_jmethod_ids_offset),
                           __ATOMIC_ACQUIRE);
  }
};

class VMMethod : VMStructs {
private:
  static bool check_jmethodID_J9(jmethodID id);
  static bool check_jmethodID_hotspot(jmethodID id);

public:
  static VMMethod *fromMethodID(jmethodID id) { return *(VMMethod **)id; }

  jmethodID id();

  static bool check_jmethodID(jmethodID id);

  const char *bytecode() {
    return *(const char **)at(_method_constmethod_offset) + _constmethod_size;
  }

  NMethod *code() { return *(NMethod **)at(_method_code_offset); }
};

class NMethod : VMStructs {
public:
  int frameSize() { return *(int *)at(_frame_size_offset); }

  short frameCompleteOffset() { return *(short *)at(_frame_complete_offset); }

  void setFrameCompleteOffset(int offset) {
    if (_nmethod_immutable_offset > 0) {
      // _frame_complete_offset is short on JDK 23+
      *(short*) at(_frame_complete_offset) = offset;
    } else {
      *(int*) at(_frame_complete_offset) = offset;
    }
  }

  const char* immutableDataAt(int offset) {
    if (_nmethod_immutable_offset > 0) {
      return *(const char**) at(_nmethod_immutable_offset) + offset;
    }
    return at(offset);
  }

  const char *code() {
    if (_code_offset > 0) {
      return at(*(int *)at(_code_offset));
    } else {
      return *(const char **)at(-_code_offset);
    }
  }

  const char *scopes() {
    if (_scopes_data_offset > 0) {
      return immutableDataAt(*(int*) at(_scopes_data_offset));
    } else {
      return *(const char **)at(-_scopes_data_offset);
    }
  }

  const void *entry() {
    if (_nmethod_entry_offset > 0) {
      return at(*(int *)at(_code_offset) +
                *(unsigned short *)at(_nmethod_entry_offset));
    } else {
      return *(void **)at(-_nmethod_entry_offset);
    }
  }

  bool isFrameCompleteAt(const void *pc) {
    return pc >= code() + frameCompleteOffset();
  }

  bool isEntryFrame(const void *pc) { return pc == _call_stub_return; }

  const char *name() { return *(const char **)at(_nmethod_name_offset); }

  bool isNMethod() {
    const char *n = name();
    return n != NULL &&
           (strcmp(n, "nmethod") == 0 || strcmp(n, "native nmethod") == 0);
  }

  bool isInterpreter() {
    const char *n = name();
    return n != NULL && strcmp(n, "Interpreter") == 0;
  }

  VMMethod *method() { return *(VMMethod **)at(_nmethod_method_offset); }

  char state() { return *at(_nmethod_state_offset); }

  bool isAlive() { return state() >= 0 && state() <= 1; }

  int level() {
    return _nmethod_level_offset >= 0
               ? *(signed char *)at(_nmethod_level_offset)
               : 0;
  }

  VMMethod **metadata() {
    if (_data_offset > 0) {
      return (VMMethod**) at(*(int*) at(_data_offset) + *(unsigned short*) at(_nmethod_metadata_offset));
    }
    return (VMMethod **)at(*(int *)at(_nmethod_metadata_offset));
  }

  int findScopeOffset(const void *pc);
};

// Copied from JDK's globalDefinitions.hpp 'JavaThreadState' enum
enum JVMJavaThreadState {
  _thread_uninitialized     =  0, // should never happen (missing initialization)
  _thread_new               =  2, // just starting up, i.e., in process of being initialized
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

class JavaFrameAnchor : VMStructs {
  private:
    enum { MAX_CALL_WRAPPER_DISTANCE = 512 };

  public:
    static JavaFrameAnchor* fromEntryFrame(uintptr_t fp) {
        const char* call_wrapper = *(const char**)(fp + _entry_frame_call_wrapper_offset);
        if (!goodPtr(call_wrapper) || (uintptr_t)call_wrapper - fp > MAX_CALL_WRAPPER_DISTANCE) {
            return NULL;
        }
        return (JavaFrameAnchor*)(call_wrapper + _call_wrapper_anchor_offset);
    }

    uintptr_t lastJavaSP() {
        return _anchor_sp_offset != -1 ? *(uintptr_t*) at(_anchor_sp_offset) : 0;
    }

    uintptr_t lastJavaFP() {
        return _anchor_fp_offset != -1 ? *(uintptr_t*) at(_anchor_fp_offset) : 0;
    }

    const void* lastJavaPC() {
        return _anchor_pc_offset != -1 ? *(const void**) at(_anchor_pc_offset) : nullptr;
    }

    void setLastJavaPC(const void* pc) {
        *(const void**) at(_anchor_pc_offset) = pc;
    }
};

class VMThread : VMStructs {
public:
  static VMThread *current();

  static int key() { return _tls_index; }

  static VMThread *fromJavaThread(JNIEnv *env, jthread thread) {
    return _eetop != NULL && thread != NULL
               ? (VMThread *)(uintptr_t)env->GetLongField(thread, _eetop)
               : NULL;
  }

  static jlong javaThreadId(JNIEnv *env, jthread thread) {
    return env->GetLongField(thread, _tid);
  }

  static int nativeThreadId(JNIEnv *jni, jthread thread);

  int osThreadId() {
    const char *osthread = *(const char **)at(_thread_osthread_offset);
    return *(int *)(osthread + _osthread_id_offset);
  }

  int state() {
    return _thread_state_offset >= 0 ? *(int *)at(_thread_state_offset) : 0;
  }

  bool inJava() { return state() == 8; }

  bool inDeopt() { return *(void **)at(_thread_vframe_offset) != NULL; }

  void *&exception() { return *(void **)at(_thread_exception_offset); }

  ThreadState osThreadState() {
    if (_thread_osthread_offset >= 0 && _osthread_state_offset >= 0) {
      const char *osthread = *(const char **)at(_thread_osthread_offset);
      if (osthread != nullptr) {
        return static_cast<ThreadState>(
            *(int *)(osthread + _osthread_state_offset));
      }
    }
    return ThreadState::UNKNOWN;
  }

  JavaFrameAnchor* anchor() {
    return (JavaFrameAnchor*) at(_thread_anchor_offset);
  }

  VMMethod *compiledMethod() {
    const char *env = *(const char **)at(_comp_env_offset);
    if (env != NULL) {
      const char *task = *(const char **)(env + _comp_task_offset);
      if (task != NULL) {
        return *(VMMethod **)(task + _comp_method_offset);
      }
    }
    return NULL;
  }
};

class CodeHeap : VMStructs {
private:
  static bool contains(char *heap, const void *pc) {
    return heap != NULL &&
           pc >= *(const void **)(heap + _code_heap_memory_offset +
                                  _vs_low_offset) &&
           pc < *(const void **)(heap + _code_heap_memory_offset +
                                 _vs_high_offset);
  }

  static NMethod *findNMethod(char *heap, const void *pc);

public:
  static bool available() { return _code_heap_addr != NULL; }

  static bool contains(const void *pc) {
    return _code_heap_low <= pc && pc < _code_heap_high;
  }

  static void updateBounds(const void *start, const void *end) {
    for (const void *low = _code_heap_low;
         start < low &&
         !__sync_bool_compare_and_swap(&_code_heap_low, low, start);
         low = _code_heap_low)
      ;
    for (const void *high = _code_heap_high;
         end > high &&
         !__sync_bool_compare_and_swap(&_code_heap_high, high, end);
         high = _code_heap_high)
      ;
  }

  static NMethod *findNMethod(const void *pc) {
    if (contains(_code_heap[0], pc))
      return findNMethod(_code_heap[0], pc);
    if (contains(_code_heap[1], pc))
      return findNMethod(_code_heap[1], pc);
    if (contains(_code_heap[2], pc))
      return findNMethod(_code_heap[2], pc);
    return NULL;
  }
};

class JVMFlag : VMStructs {
private:
  static void *find(const char *name, int type_mask);
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

  static void *find(const char *name);
  static void *find(const char *name, std::initializer_list<Type> types);

  const char *name() { return *(const char **)at(_flag_name_offset); }
  int type();

  void *addr() { return *(void **)at(_flag_addr_offset); }
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
            ((CollectedHeap *)*_collected_heap_addr)->_used_at_last_gc;
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

class PcDesc {
public:
  int _pc;
  int _scope_offset;
  int _obj_offset;
  int _flags;
};

class ScopeDesc : VMStructs {
private:
  const unsigned char* _scopes;
  VMMethod** _metadata;
  const unsigned char *_stream;
  int _method_offset;
  int _bci;

  int readInt();

public:
  ScopeDesc(NMethod *nm) {
    _scopes = (const unsigned char*)nm->scopes();
    _metadata = nm->metadata();
  }

  int decode(int offset) {
    _stream = _scopes + offset;
    int sender_offset = readInt();
    _method_offset = readInt();
    _bci = readInt() - 1;
    return sender_offset;
  }

  VMMethod *method() {
    return _method_offset > 0 ? _metadata[_method_offset - 1] : NULL;
  }

  int bci() { return _bci; }
};

class InterpreterFrame : VMStructs {
public:
  enum { sender_sp_offset = -1, method_offset = -3 };

  static int bcp_offset() { return _interpreter_frame_bcp_offset; }
};

#endif // _VMSTRUCTS_H
