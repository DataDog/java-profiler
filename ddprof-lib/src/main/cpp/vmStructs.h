/*
 * Copyright The async-profiler authors
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _VMSTRUCTS_H
#define _VMSTRUCTS_H

#include <jvmti.h>
#include <stdint.h>
#include <string.h>
#include <type_traits>
#include "codeCache.h"
#include "safeAccess.h"
#include "threadState.h"
#include "vmEntry.h"

class GCHeapSummary;
class HeapUsage;

#define TYPE_SIZE_NAME(name)    _##name##_size

template <typename T>
inline T* cast_to(const void* ptr) {
    assert(T::type_size() > 0); // Ensure type size has been initialized
    assert(ptr == nullptr || SafeAccess::isReadableRange(ptr, T::type_size()));
    return reinterpret_cast<T*>(const_cast<void*>(ptr));
}

#define DECLARE(name) \
    class name : VMStructs { \
      public: \
        static uint64_t type_size() { return TYPE_SIZE_NAME(name); } \
        static name * cast(const void* ptr) { return cast_to<name>(ptr); } \
        static name * load_then_cast(const void* ptr) { \
            assert(ptr != nullptr); \
            return cast(*(const void**)ptr); }

#define DECLARE_END  };

#define MATCH_SYMBOLS(...) __VA_ARGS__, nullptr

// Defines a type and its matching symbols in vmStructs.
// A type may match multiple names in different JVM versions.
#define DECLARE_TYPES_DO(f) \
    f(VMClassLoaderData,    MATCH_SYMBOLS("ClassLoaderData")) \
    f(VMConstantPool,       MATCH_SYMBOLS("ConstantPool")) \
    f(VMConstMethod,        MATCH_SYMBOLS("ConstMethod")) \
    f(VMFlag,               MATCH_SYMBOLS("JVMFlag", "Flag")) \
    f(VMJavaFrameAnchor,    MATCH_SYMBOLS("JavaFrameAnchor")) \
    f(VMKlass,              MATCH_SYMBOLS("Klass")) \
    f(VMMethod,             MATCH_SYMBOLS("Method")) \
    f(VMNMethod,            MATCH_SYMBOLS("nmethod")) \
    f(VMSymbol,             MATCH_SYMBOLS("Symbol")) \
    f(VMThread,             MATCH_SYMBOLS("Thread"))

class VMStructs {
  public:
    typedef bool (*IsValidMethodFunc)(void *);

  protected:
    enum { MONITOR_BIT = 2 };

    static CodeCache* _libjvm;

    static bool _has_class_names;
    static bool _has_method_structs;
    static bool _has_compiler_structs;
    static bool _has_stack_structs;
    static bool _has_class_loader_data;
    static bool _has_native_thread_id;
    static bool _can_dereference_jmethod_id;
    static bool _compact_object_headers;

    static int _klass_name_offset;
    static int _symbol_length_offset;
    static int _symbol_length_and_refcount_offset;
    static int _symbol_body_offset;
    static int _oop_klass_offset;
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
    static int _call_wrapper_anchor_offset;
    static int _comp_env_offset;
    static int _comp_task_offset;
    static int _comp_method_offset;
    static int _anchor_sp_offset;
    static int _anchor_pc_offset;
    static int _anchor_fp_offset;
    static int _blob_size_offset;
    static int _frame_size_offset;
    static int _frame_complete_offset;
    static int _code_offset;
    static int _data_offset;
    static int _mutable_data_offset;
    static int _relocation_size_offset;
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
    static int _pool_holder_offset;
    static int _array_len_offset;
    static int _array_data_offset;
    static int _code_heap_memory_offset;
    static int _code_heap_segmap_offset;
    static int _code_heap_segment_shift;
    static int _heap_block_used_offset;
    static int _vs_low_bound_offset;
    static int _vs_high_bound_offset;
    static int _vs_low_offset;
    static int _vs_high_offset;
    static int _flag_name_offset;
    static int _flag_addr_offset;
    static int _flag_origin_offset;
    static const char* _flags_addr;
    static int _flag_count;
    static char* _code_heap[3];
    static const void* _code_heap_low;
    static const void* _code_heap_high;
    static char** _code_heap_addr;
    static const void** _code_heap_low_addr;
    static const void** _code_heap_high_addr;
    static int* _klass_offset_addr;
    static char** _narrow_klass_base_addr;
    static char* _narrow_klass_base;
    static int* _narrow_klass_shift_addr;
    static int _narrow_klass_shift;
    static char** _collected_heap_addr;
    static int _region_start_offset;
    static int _region_size_offset;
    static int _markword_klass_shift;
    static int _markword_monitor_value;
    static int _entry_frame_call_wrapper_offset;
    static int _interpreter_frame_bcp_offset;
    static unsigned char _unsigned5_base;
    static const void** _call_stub_return_addr;
    static const void* _call_stub_return;
    static const void* _interpreted_frame_valid_start;
    static const void* _interpreted_frame_valid_end;

// Declare type size variables
 #define DECLARE_TYPE_SIZE_VAR(name, ...) \
    static uint64_t TYPE_SIZE_NAME(name);
    
    DECLARE_TYPES_DO(DECLARE_TYPE_SIZE_VAR)

#undef DECLARE_TYPE_SIZE_VAR
    

    static jfieldID _eetop;
    static jfieldID _tid;
    static jfieldID _klass;
    static int _tls_index;
    static intptr_t _env_offset;
    static void* _java_thread_vtbl[6];

    typedef void (*LockFunc)(void*);
    static LockFunc _lock_func;
    static LockFunc _unlock_func;

    // Datadog-specific extensions
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

    static uintptr_t readSymbol(const char* symbol_name);
    static void initOffsets();
    static void resolveOffsets();
    static void patchSafeFetch();
    static void initJvmFunctions();
    static void initTLS(void* vm_thread);
    static void initThreadBridge();

    // Datadog-specific private methods
    static void initUnsafeFunctions();
    static void initCriticalJNINatives();
    static void checkNativeBinding(jvmtiEnv *jvmti, JNIEnv *jni, jmethodID method, void *address);
    static const void *findHeapUsageFunc();

    const char* at(int offset) {
        const char* ptr = (const char*)this + offset;
        assert(SafeAccess::isReadable(ptr));
        return ptr;
    }

    static bool goodPtr(const void* ptr) {
        return (uintptr_t)ptr >= 0x1000 && ((uintptr_t)ptr & (sizeof(uintptr_t) - 1)) == 0;
    }

    template<typename T>
    static T align(const void* ptr) {
        static_assert(std::is_pointer<T>::value, "T must be a pointer type");
        return (T)((uintptr_t)ptr & ~(sizeof(T) - 1));
    }

  public:
    static void init(CodeCache* libjvm);
    static void ready();

    static CodeCache* libjvm() {
        return _libjvm;
    }

    static bool hasClassNames() {
        return _has_class_names;
    }

    static bool hasMethodStructs() {
        return _has_method_structs;
    }

    static bool hasCompilerStructs() {
        return _has_compiler_structs;
    }

    static bool hasStackStructs() {
        return _has_stack_structs;
    }

    static bool hasClassLoaderData() {
        return _has_class_loader_data;
    }

    static bool hasNativeThreadId() {
        return _has_native_thread_id;
    }

    static bool hasJavaThreadId() {
        return _tid != NULL;
    }

    static bool isInterpretedFrameValidFunc(const void* pc) {
        return pc >= _interpreted_frame_valid_start && pc < _interpreted_frame_valid_end;
    }

    // Datadog-specific extensions
    static bool isSafeToWalk(uintptr_t pc);
    static void JNICALL NativeMethodBind(jvmtiEnv *jvmti, JNIEnv *jni,
                                         jthread thread, jmethodID method,
                                         void *address, void **new_address_ptr);

    static int thread_osthread_offset() {
        return _thread_osthread_offset;
    }

    static int osthread_state_offset() {
        return _osthread_state_offset;
    }

    static int osthread_id_offset() {
        return _osthread_id_offset;
    }

    static int thread_state_offset() {
        return _thread_state_offset;
    }

    static int flag_type_offset() {
        return _flag_type_offset;
    }

    static int method_constmethod_offset() {
      return _method_constmethod_offset;
    }

    static int constmethod_constants_offset() {
      return _constmethod_constants_offset;
    }

    static int pool_holder_offset() {
      return _pool_holder_offset;
    }

    static int class_loader_data_offset() {
      return _class_loader_data_offset;
    }

    static IsValidMethodFunc is_valid_method_func() {
        return _is_valid_method_func;
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

    static bool isLastGCUsageSupported();
    static bool needsNativeBindingInterception();
    static jlong getMaxHeap(JNIEnv *env);
    static HeapUsage get();
    static HeapUsage get(bool allow_jmx);
};

class MethodList {
  public:
    enum { SIZE = 8 };

  private:
    intptr_t _method[SIZE];
    int _ptr;
    MethodList* _next;
    int _padding;

  public:
    MethodList(MethodList* next) : _ptr(0), _next(next), _padding(0) {
        for (int i = 0; i < SIZE; i++) {
            _method[i] = 0x37;
        }
    }
};


class VMNMethod;
class VMMethod;

DECLARE(VMSymbol)
  public:
    unsigned short length() {
        if (_symbol_length_offset >= 0) {
          return *(unsigned short*) at(_symbol_length_offset);
        } else {
          return *(unsigned int*) at(_symbol_length_and_refcount_offset) >> 16;
        }
    }

    const char* body() {
        return at(_symbol_body_offset);
    }
DECLARE_END

DECLARE(VMClassLoaderData)
  private:
    void* mutex() {
        return *(void**) at(sizeof(uintptr_t) * 3);
    }

  public:
    void lock() {
        _lock_func(mutex());
    }

    void unlock() {
        _unlock_func(mutex());
    }

    MethodList** methodList() {
        return (MethodList**) at(sizeof(uintptr_t) * 6 + 8);
    }
DECLARE_END

DECLARE(VMKlass)    
  public:
    static VMKlass* fromJavaClass(JNIEnv* env, jclass cls) {
        if (sizeof(VMKlass*) == 8) {
            return VMKlass::cast((const void*)(intptr_t)env->GetLongField(cls, _klass));
        } else {
            return VMKlass::cast((const void*)(intptr_t)env->GetIntField(cls, _klass));
        }
    }

    static VMKlass* fromHandle(uintptr_t handle) {
        return VMKlass::cast((const void*)handle);
    }

    static VMKlass* fromOop(uintptr_t oop) {
        if (_narrow_klass_shift >= 0) {
            uintptr_t narrow_klass;
            if (_compact_object_headers) {
                uintptr_t mark = *(uintptr_t*)oop;
                if (mark & MONITOR_BIT) {
                    mark = *(uintptr_t*)(mark ^ MONITOR_BIT);
                }
                narrow_klass = mark >> _markword_klass_shift;
            } else {
                narrow_klass = *(unsigned int*)(oop + _oop_klass_offset);
            }
            return VMKlass::cast((const void*)(_narrow_klass_base + (narrow_klass << _narrow_klass_shift)));
        } else {
            return VMKlass::load_then_cast((const void*)(oop + _oop_klass_offset));
        }
    }

    VMSymbol* name() {
        assert(_klass_name_offset >= 0);
        return VMSymbol::load_then_cast(at(_klass_name_offset));
    }

    VMClassLoaderData* classLoaderData() {
        assert(_class_loader_data_offset >= 0);
        return VMClassLoaderData::load_then_cast(at(_class_loader_data_offset));
    }

    int methodCount() {
        assert(_methods_offset >= 0);
        int* methods = *(int**) at(_methods_offset);
        return methods == NULL ? 0 : *methods & 0xffff;
    }

    jmethodID* jmethodIDs() {
        assert(_jmethod_ids_offset >= 0);
        return __atomic_load_n((jmethodID**) at(_jmethod_ids_offset), __ATOMIC_ACQUIRE);
    }
DECLARE_END

DECLARE(VMJavaFrameAnchor)
  private:
    enum { MAX_CALL_WRAPPER_DISTANCE = 512 };

  public:
    static VMJavaFrameAnchor* fromEntryFrame(uintptr_t fp) {
        assert(_entry_frame_call_wrapper_offset != -1);
        assert(_call_wrapper_anchor_offset >= 0);
        const char* call_wrapper = (const char*) SafeAccess::loadPtr((void**)(fp + _entry_frame_call_wrapper_offset), nullptr);
        if (!goodPtr(call_wrapper) || (uintptr_t)call_wrapper - fp > MAX_CALL_WRAPPER_DISTANCE) {
            return NULL;
        }
        return VMJavaFrameAnchor::cast((const void*)(call_wrapper + _call_wrapper_anchor_offset));
    }

    uintptr_t lastJavaSP() {
        assert(_anchor_sp_offset >= 0);
        return (uintptr_t) SafeAccess::loadPtr((void**) at(_anchor_sp_offset), nullptr);
    }

    uintptr_t lastJavaFP() {
        assert(_anchor_fp_offset >= 0);
        return (uintptr_t) SafeAccess::loadPtr((void**) at(_anchor_fp_offset), nullptr);
    }

    const void* lastJavaPC() {
        assert(_anchor_pc_offset >= 0);
        return SafeAccess::loadPtr((void**) at(_anchor_pc_offset), nullptr);
    }

    void setLastJavaPC(const void* pc) {
        assert(_anchor_pc_offset >= 0);
        *(const void**) at(_anchor_pc_offset) = pc;
    }

    bool getFrame(const void*& pc, uintptr_t& sp, uintptr_t& fp) {
        if (lastJavaPC() != NULL && lastJavaSP() != 0) {
            pc = lastJavaPC();
            sp = lastJavaSP();
            fp = lastJavaFP();
            return true;
        }
        return false;
    }
DECLARE_END

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

DECLARE(VMThread)
  public:
    static VMThread* current();

    static int key() {
        return _tls_index;
    }

    static VMThread* fromJavaThread(JNIEnv* env, jthread thread) {
        return VMThread::cast((const void*)env->GetLongField(thread, _eetop));
    }

    static jlong javaThreadId(JNIEnv* env, jthread thread) {
        return env->GetLongField(thread, _tid);
    }

    static int nativeThreadId(JNIEnv* jni, jthread thread);

    int osThreadId();

    JNIEnv* jni();

    const void** vtable() {
        assert(SafeAccess::isReadable(this));
        return *(const void***)this;
    }

    // This thread is considered a JavaThread if at least 2 of the selected 3 vtable entries
    // match those of a known JavaThread (which is either application thread or AttachListener).
    // Indexes were carefully chosen to work on OpenJDK 8 to 25, both product an debug builds.
    bool isJavaThread() {
        const void** vtbl = vtable();
        return (vtbl[1] == _java_thread_vtbl[1]) +
               (vtbl[3] == _java_thread_vtbl[3]) +
               (vtbl[5] == _java_thread_vtbl[5]) >= 2;
    }

    OSThreadState osThreadState();

    int state();

    bool inJava() {
        return state() == 8;
    }

    bool inDeopt() {
        assert(_thread_vframe_offset >= 0);
        return SafeAccess::loadPtr((void**) at(_thread_vframe_offset), nullptr) != NULL;
    }

    void*& exception() {
        assert(_thread_exception_offset >= 0);
        return *(void**) at(_thread_exception_offset);
    }

    VMJavaFrameAnchor* anchor() {
        assert(_thread_anchor_offset >= 0);
        return VMJavaFrameAnchor::cast(at(_thread_anchor_offset));
    }

    inline VMMethod* compiledMethod();
DECLARE_END

DECLARE(VMConstMethod)
DECLARE_END


DECLARE(VMMethod)   
    private:
    static bool check_jmethodID_J9(jmethodID id);
    static bool check_jmethodID_hotspot(jmethodID id);

  public:
    jmethodID id();

    // Performs extra validation when VMMethod comes from incomplete frame
    jmethodID validatedId();

    // Workaround for JDK-8313816
    static bool isStaleMethodId(jmethodID id) {
        if (!_can_dereference_jmethod_id) return false;

        VMMethod* vm_method = VMMethod::load_then_cast((const void*)id);
        return vm_method == NULL || vm_method->id() == NULL;
    }

    const char* bytecode() {
        assert(_method_constmethod_offset >= 0);
        return *(const char**) at(_method_constmethod_offset) + VMConstMethod::type_size();
    }

    inline VMNMethod* code();

    static bool check_jmethodID(jmethodID id);
DECLARE_END

DECLARE(VMNMethod)
  public:
    int size() {
        assert(_blob_size_offset >= 0);
        return *(int*) at(_blob_size_offset);
    }

    int frameSize() {
        assert(_frame_size_offset >= 0);
        return *(int*) at(_frame_size_offset);
    }

    short frameCompleteOffset() {
        assert(_frame_complete_offset >= 0);
        return *(short*) at(_frame_complete_offset);
    }

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

    const char* code() {
        if (_code_offset > 0) {
            return at(*(int*) at(_code_offset));
        } else {
            return *(const char**) at(-_code_offset);
        }
    }

    const char* scopes() {
        if (_scopes_data_offset > 0) {
            return immutableDataAt(*(int*) at(_scopes_data_offset));
        } else {
            return *(const char**) at(-_scopes_data_offset);
        }
    }

    const void* entry() {
        if (_nmethod_entry_offset > 0) {
            return at(*(int*) at(_code_offset) + *(unsigned short*) at(_nmethod_entry_offset));
        } else {
            return *(void**) at(-_nmethod_entry_offset);
        }
    }

    bool contains(const void* pc) {
        return pc >= this && pc < at(size());
    }

    bool isFrameCompleteAt(const void* pc) {
        return pc >= code() + frameCompleteOffset();
    }

    bool isEntryFrame(const void* pc) {
        return pc == _call_stub_return;
    }

    const char* name() {
        assert(_nmethod_name_offset >= 0);
        return *(const char**) at(_nmethod_name_offset);
    }

    bool isNMethod() {
        const char* n = name();
        return n != NULL && (strcmp(n, "nmethod") == 0 || strcmp(n, "native nmethod") == 0);
    }

    bool isInterpreter() {
        const char* n = name();
        return n != NULL && strcmp(n, "Interpreter") == 0;
    }

    bool isStub() {
        const char* n = name();
        return n != NULL && strncmp(n, "StubRoutines", 12) == 0;
    }

    bool isVTableStub() {
        const char* n = name();
        return n != NULL && strcmp(n, "vtable chunks") == 0;
    }

    VMMethod* method() {
        assert(_nmethod_method_offset >= 0);
        return VMMethod::load_then_cast((const void*)at(_nmethod_method_offset));
    }

    char state() {
        return *at(_nmethod_state_offset);
    }

    bool isAlive() {
        return state() >= 0 && state() <= 1;
    }

    int level() {
        return _nmethod_level_offset >= 0 ? *(signed char*) at(_nmethod_level_offset) : 0;
    }

    VMMethod** metadata() {
        if (_mutable_data_offset >= 0) {
            // Since JDK 25
            assert(_relocation_size_offset >= 0);
            return (VMMethod**) (*(char**) at(_mutable_data_offset) + *(int*) at(_relocation_size_offset));
        } else if (_data_offset > 0) {
            // since JDK 23
            assert(_nmethod_metadata_offset >= 0);
            assert(_data_offset >= 0);
            return (VMMethod**) at(*(int*) at(_data_offset) + *(unsigned short*) at(_nmethod_metadata_offset));
        }
        assert(_nmethod_metadata_offset >= 0);
        return (VMMethod**) at(*(int*) at(_nmethod_metadata_offset));
    }

    int findScopeOffset(const void* pc);
DECLARE_END

class CodeHeap : VMStructs {
  private:
    static bool contains(char* heap, const void* pc) {
        return heap != NULL &&
               pc >= *(const void**)(heap + _code_heap_memory_offset + _vs_low_offset) &&
               pc <  *(const void**)(heap + _code_heap_memory_offset + _vs_high_offset);
    }

    static VMNMethod* findNMethod(char* heap, const void* pc);

  public:
    static bool available() {
        return _code_heap_addr != NULL;
    }

    static bool contains(const void* pc) {
        return _code_heap_low <= pc && pc < _code_heap_high;
    }

    static void updateBounds(const void* start, const void* end) {
        for (const void* low = _code_heap_low;
             start < low && !__sync_bool_compare_and_swap(&_code_heap_low, low, start);
             low = _code_heap_low);
        for (const void* high = _code_heap_high;
             end > high && !__sync_bool_compare_and_swap(&_code_heap_high, high, end);
             high = _code_heap_high);
    }

    static VMNMethod* findNMethod(const void* pc) {
        if (contains(_code_heap[0], pc)) return findNMethod(_code_heap[0], pc);
        if (contains(_code_heap[1], pc)) return findNMethod(_code_heap[1], pc);
        if (contains(_code_heap[2], pc)) return findNMethod(_code_heap[2], pc);
        return NULL;
    }
};

DECLARE(VMFlag)
  private:
    enum {
        ORIGIN_DEFAULT = 0,
        ORIGIN_MASK    = 15,
        SET_ON_CMDLINE = 1 << 17
    };
    static VMFlag* find(const char *name, int type_mask);

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

    static VMFlag* find(const char* name);
    static VMFlag *find(const char* name, std::initializer_list<Type> types);

    const char* name() {
        assert(_flag_name_offset >= 0);
        return *(const char**) at(_flag_name_offset);
    }

    int type();

    void* addr() {
        assert(_flag_addr_offset >= 0);
        return *(void**) at(_flag_addr_offset);
    }

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
DECLARE_END

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
    const unsigned char* _stream;
    int _method_offset;
    int _bci;

    int readInt();

  public:
    ScopeDesc(VMNMethod* nm) {
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

    VMMethod* method() {
        return _method_offset > 0 ? _metadata[_method_offset - 1] : NULL;
    }

    int bci() {
        return _bci;
    }
};

class InterpreterFrame : VMStructs {
  public:
    enum {
        sender_sp_offset = -1,
        method_offset = -3
    };

    static int bcp_offset() {
        return _interpreter_frame_bcp_offset;
    }
};

#endif // _VMSTRUCTS_H
