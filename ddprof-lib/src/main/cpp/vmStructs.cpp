/*
 * Copyright The async-profiler authors
 * SPDX-License-Identifier: Apache-2.0
 */

#include <pthread.h>
#include <unistd.h>
#include <stdarg.h>
#include "vmStructs.h"
#include "vmEntry.h"
#include "j9Ext.h"
#include "jniHelper.h"
#include "jvmHeap.h"
#include "safeAccess.h"
#include "spinLock.h"
#include "common.h"

CodeCache* VMStructs::_libjvm = nullptr;
bool VMStructs::_has_class_names = false;
bool VMStructs::_has_method_structs = false;
bool VMStructs::_has_compiler_structs = false;
bool VMStructs::_has_stack_structs = false;
bool VMStructs::_has_class_loader_data = false;
bool VMStructs::_has_native_thread_id = false;
bool VMStructs::_can_dereference_jmethod_id = false;
bool VMStructs::_compact_object_headers = false;

char* VMStructs::_code_heap[3] = {};
const void* VMStructs::_code_heap_low = NO_MIN_ADDRESS;
const void* VMStructs::_code_heap_high = NO_MAX_ADDRESS;
char* VMStructs::_narrow_klass_base = nullptr;
int VMStructs::_narrow_klass_shift = -1;
int VMStructs::_interpreter_frame_bcp_offset = 0;
unsigned char VMStructs::_unsigned5_base = 0;
const void* VMStructs::_call_stub_return = nullptr;
const void* VMStructs::_interpreted_frame_valid_start = nullptr;
const void* VMStructs::_interpreted_frame_valid_end = nullptr;


// Initialize type size to 0
#define INIT_TYPE_SIZE(name, names) uint64_t VMStructs::TYPE_SIZE_NAME(name) = 0;
DECLARE_TYPES_DO(INIT_TYPE_SIZE)
#undef INIT_TYPE_SIZE

#define offset_value -1
#define address_value nullptr

// Initialize field variables
// offset = -1
// address = nullptr

// Do nothing macro
#define DO_NOTHING(...)
#define INIT_OFFSET_OR_ADDRESS(var, field_type, names) \
    field_type VMStructs::var = field_type##_value;

DECLARE_TYPE_FILED_DO(DO_NOTHING, INIT_OFFSET_OR_ADDRESS, INIT_OFFSET_OR_ADDRESS, DO_NOTHING)

#undef INIT_OFFSET_OR_ADDRESS
#undef DO_NOTHING
#undef offset_value
#undef address_value

// Initialize constant variables to -1
#define INIT_INT_CONSTANT(type, field) \
    int VMStructs::_##type##_##field = -1;
#define INIT_LONG_CONSTANT(type, field) \
    long VMStructs::_##type##_##field = -1;

DECLARE_INT_CONSTANTS_DO(INIT_INT_CONSTANT)
DECLARE_LONG_CONSTANTS_DO(INIT_LONG_CONSTANT)
#undef INIT_INT_CONSTANT
#undef INIT_LONG_CONSTANT


jfieldID VMStructs::_eetop;
jfieldID VMStructs::_tid;
jfieldID VMStructs::_klass = NULL;
int VMStructs::_tls_index = -1;
intptr_t VMStructs::_env_offset = -1;
void* VMStructs::_java_thread_vtbl[6];

VMStructs::LockFunc VMStructs::_lock_func;
VMStructs::LockFunc VMStructs::_unlock_func;

// Datadog-specific static variables
CodeCache VMStructs::_unsafe_to_walk("unwalkable code");
VMStructs::HeapUsageFunc VMStructs::_heap_usage_func = NULL;
VMStructs::MemoryUsageFunc VMStructs::_memory_usage_func = NULL;
VMStructs::GCHeapSummaryFunc VMStructs::_gc_heap_summary_func = NULL;
VMStructs::IsValidMethodFunc VMStructs::_is_valid_method_func = NULL;


uintptr_t VMStructs::readSymbol(const char* symbol_name) {
    const void* symbol = _libjvm->findSymbol(symbol_name);
    if (symbol == NULL) {
        // Avoid JVM crash in case of missing symbols
        return 0;
    }
    return *(uintptr_t*)symbol;
}

// Run at agent load time
void VMStructs::init(CodeCache* libjvm) {
    if (libjvm != NULL) {
        _libjvm = libjvm;
        initOffsets();
        initJvmFunctions();
        initUnsafeFunctions();
        initCriticalJNINatives();
    }
}

// Run when VM is initialized and JNI is available
void VMStructs::ready() {
    resolveOffsets();
    patchSafeFetch();
    initThreadBridge();
}

bool matchAny(const char* target_name, const char** names) {
    for (const char** name = names; *name != nullptr; name++) {
        if (strcmp(target_name, *name) == 0) {
            return true;
        }
    }
    return false;
}

void VMStructs::init_offsets_and_addresses() {
    uintptr_t entry = readSymbol("gHotSpotVMStructs");
    uintptr_t stride = readSymbol("gHotSpotVMStructEntryArrayStride");
    uintptr_t type_offset = readSymbol("gHotSpotVMStructEntryTypeNameOffset");
    uintptr_t field_offset = readSymbol("gHotSpotVMStructEntryFieldNameOffset");
    uintptr_t offset_offset = readSymbol("gHotSpotVMStructEntryOffsetOffset");
    uintptr_t isStatic_offset = readSymbol("gHotSpotVMStructEntryIsStaticOffset");
    uintptr_t address_offset = readSymbol("gHotSpotVMStructEntryAddressOffset");
    bool isStatic;

    auto read_offset = [&]() -> int {
        assert(!isStatic);
        return *(int*)(entry + offset_offset);
    };

    auto read_address = [&]() -> address {
        assert(isStatic);
        return *(address*)(entry + address_offset);
    };

    if (entry != 0 && stride != 0) {
        for (;; entry += stride) {
            const char* type_name = *(const char**)(entry + type_offset);
            const char* field_name = *(const char**)(entry + field_offset);
            isStatic = *(int32_t*)(entry + isStatic_offset) != 0;
 
            if (type_name == nullptr || field_name == nullptr) {
                break;
            }
#define MATCH_TYPE_NAMES(type, type_names)                                     \
     if (matchAny(type_name, type_names)) {
#define READ_FIELD_VALUE(var, field_type, field_names) \
        if (matchAny(field_name, field_names)) {    \
            var = read_##field_type();              \
            continue;                                                   \
        }
#define END_TYPE() continue; }
        DECLARE_TYPE_FILED_DO(MATCH_TYPE_NAMES, READ_FIELD_VALUE, READ_FIELD_VALUE, END_TYPE)
#undef MATCH_TYPE_NAMES
#undef READ_FIELD_VALUE
#undef END_TYPE
        }
    }
}

void VMStructs::init_type_sizes() {
    uintptr_t entry = readSymbol("gHotSpotVMTypes");
    uintptr_t stride = readSymbol("gHotSpotVMTypeEntryArrayStride");
    uintptr_t type_offset = readSymbol("gHotSpotVMTypeEntryTypeNameOffset");
    uintptr_t size_offset = readSymbol("gHotSpotVMTypeEntrySizeOffset");

    if (entry != 0 && stride != 0) {
        for (;; entry += stride) {
            const char* type = *(const char**)(entry + type_offset);
            if (type == NULL) {
                break;
            }

            uint64_t size = *(uint64_t*)(entry + size_offset);
           
 #define READ_TYPE_SIZE(name, names)                                      \
        if (matchAny(type, names)) {          \
            TYPE_SIZE_NAME(name) = size;                                \
            continue;                                                   \
        }

        DECLARE_TYPES_DO(READ_TYPE_SIZE)

#undef READ_TYPE_SIZE   

        }
    }
}

#define READ_CONSTANT(type, field)                                                      \
            if (strcmp(type_name, #type "::" #field) == 0) {                            \
                _##type##_##field = value;                                              \
                continue;                                                               \
            }


void VMStructs::init_constants() {
    // Int constants
    uintptr_t entry = readSymbol("gHotSpotVMIntConstants");
    uintptr_t stride = readSymbol("gHotSpotVMIntConstantEntryArrayStride");
    uintptr_t name_offset = readSymbol("gHotSpotVMIntConstantEntryNameOffset");
    uintptr_t value_offset = readSymbol("gHotSpotVMIntConstantEntryValueOffset");
    if (entry != 0 && stride != 0) {
        for (;; entry += stride) {
            const char* type_name = *(const char**)(entry + name_offset);
            if (type_name == nullptr) {
                break;
            }
            int value = *(int*)(entry + value_offset);
            DECLARE_INT_CONSTANTS_DO(READ_CONSTANT)
        }
    }
    // Sepcial case
    _frame_entry_frame_call_wrapper_offset *= sizeof(uintptr_t);


    // Long constants
    entry = readSymbol("gHotSpotVMLongConstants");
    stride = readSymbol("gHotSpotVMLongConstantEntryArrayStride");
    name_offset = readSymbol("gHotSpotVMLongConstantEntryNameOffset");
    value_offset = readSymbol("gHotSpotVMLongConstantEntryValueOffset");

    if (entry != 0 && stride != 0) {
        for (;; entry += stride) {
            const char* type_name = *(const char**)(entry + name_offset);
            if (type_name == nullptr) {
                break;
            }

            long value = *(long*)(entry + value_offset);
            DECLARE_LONG_CONSTANTS_DO(READ_CONSTANT)
        }
    }
}

#undef READ_CONSTANT


#ifdef DEBUG
void VMStructs::verify_offsets() {
// Verify type sizes
#define VERIFY_TYPE_SIZE(name, names) assert(TYPE_SIZE_NAME(name) > 0);
    DECLARE_TYPES_DO(VERIFY_TYPE_SIZE);
#undef VERIFY_TYPE_SIZE


// Verify offsets and addresses
#define offset_value -1
#define address_value nullptr
#define off_value_value -1
#define addr_value_value -1

// Do nothing macro
#define DO_NOTHING(...)
#define VERIFY_OFFSET_OR_ADDRESS(var, field_type, names) \
    assert(var != field_type##_value);

    DECLARE_TYPE_FILED_DO(DO_NOTHING, VERIFY_OFFSET_OR_ADDRESS, DO_NOTHING, DO_NOTHING)
#undef VERIFY_OFFSET_OR_ADDRESS
#undef DO_NOTHING
#undef offset_value
#undef address_value
#undef off_value_value
#undef addr_value_value

// Verify constants
// Initialize constant variables to -1
#define VERIFY_CONSTANT(type, field) \
    // assert(_##type##_##field != -1);

    DECLARE_INT_CONSTANTS_DO(VERIFY_CONSTANT)
    DECLARE_LONG_CONSTANTS_DO(VERIFY_CONSTANT)
#undef INIT_CONSTANT
}

#endif // DEBUG

void VMStructs::initOffsets() {
    init_type_sizes();
    init_offsets_and_addresses();
    init_constants();


#ifdef DEBUG
   verify_offsets();
#endif
}

void VMStructs::resolveOffsets() {
    if (VM::isOpenJ9() || VM::isZing()) {
        return;
    }

    if (_klass_offset_addr != NULL) {
        _klass = (jfieldID)(uintptr_t)(*(int*)_klass_offset_addr << 2 | 2);
    }

    VMFlag* ccp = VMFlag::find("UseCompressedClassPointers");
    if (ccp != NULL && ccp->get() && _narrow_klass_base_addr != NULL && _narrow_klass_shift_addr != nullptr) {
        _narrow_klass_base = *(char**)_narrow_klass_base_addr;
        _narrow_klass_shift = *(int*)_narrow_klass_shift_addr;
    }

    VMFlag* coh = VMFlag::find("UseCompactObjectHeaders");
    if (coh != NULL && coh->get()) {
        _compact_object_headers = true;
    }

    _has_class_names = _klass_name_offset >= 0
            && (_compact_object_headers ? (_markWord_klass_shift >= 0 && _markWord_monitor_value == MONITOR_BIT)
                                        : _oop_klass_offset >= 0)
            && (_symbol_length_offset >= 0 || _symbol_length_and_refcount_offset >= 0)
            && _symbol_body_offset >= 0
            && _klass != NULL;

    _has_method_structs = _jmethod_ids_offset >= 0
            && _nmethod_method_offset >= 0
            && _nmethod_entry_offset != -1
            && _nmethod_state_offset >= 0
            && _method_constmethod_offset >= 0
            && _method_code_offset >= 0
            && _constmethod_constants_offset >= 0
            && _constmethod_idnum_offset >= 0
            && VMConstMethod::type_size() > 0
            && _pool_holder_offset >= 0;

    _has_compiler_structs = _comp_env_offset >= 0
            && _comp_task_offset >= 0
            && _comp_method_offset >= 0;

    _has_class_loader_data = _class_loader_data_offset >= 0
            && _class_loader_data_next_offset == sizeof(uintptr_t) * 8 + 8
            && _methods_offset >= 0
            && _klass != NULL
            && _lock_func != NULL && _unlock_func != NULL;

#if defined(__x86_64__) || defined(__i386__)
    _interpreter_frame_bcp_offset = VM::hotspot_version() >= 11 ? -8 : VM::hotspot_version() == 8 ? -7 : 0;
#elif defined(__aarch64__)
    _interpreter_frame_bcp_offset = VM::hotspot_version() >= 11 ? -9 : VM::hotspot_version() == 8 ? -7 : 0;
    // The constant is missing on ARM, but fortunately, it has been stable for years across all JDK versions
    _frame_entry_frame_call_wrapper_offset = -64;
#elif defined(__arm__) || defined(__thumb__)
    _interpreter_frame_bcp_offset = VM::hotspot_version() >= 11 ? -8 : 0;
    _frame_entry_frame_call_wrapper_offset = 0;
#endif

    // JDK-8292758 has slightly changed ScopeDesc encoding
    if (VM::hotspot_version() >= 20) {
        _unsigned5_base = 1;
    }

    if (_call_stub_return_addr != NULL) {
        _call_stub_return = *(const void**)_call_stub_return_addr;
    }

    // Since JDK 23, _metadata_offset is relative to _data_offset. See metadata()
    if (_nmethod_immutable_offset < 0) {
        _data_offset = 0;
    }

    _has_stack_structs = _has_method_structs
            && _call_wrapper_anchor_offset >= 0
            && _frame_entry_frame_call_wrapper_offset != -1
            && _interpreter_frame_bcp_offset != 0
            && _code_offset != -1
            && _data_offset >= 0
            && _scopes_data_offset != -1
            && _scopes_pcs_offset >= 0
            && ((_mutable_data_offset >= 0 && _relocation_size_offset >= 0) || _nmethod_metadata_offset >= 0)
            && _thread_vframe_offset >= 0
            && _thread_exception_offset >= 0
            && VMThread::type_size() > 0;

    // Since JDK-8268406, it is no longer possible to get VMMethod* by dereferencing jmethodID
    _can_dereference_jmethod_id = _has_method_structs && VM::hotspot_version() <= 25;

    if (_code_heap_addr != NULL && _code_heap_low_addr != NULL && _code_heap_high_addr != NULL) {
        char* code_heaps = *(char**)_code_heap_addr;
        unsigned int code_heap_count = *(unsigned int*)(code_heaps + _array_len_offset);
        if (code_heap_count <= 3 && _array_data_offset >= 0) {
            char* code_heap_array = *(char**)(code_heaps + _array_data_offset);
            memcpy(_code_heap, code_heap_array, code_heap_count * sizeof(_code_heap[0]));
        }
        _code_heap_low = *(const void**)_code_heap_low_addr;
        _code_heap_high = *(const void**)_code_heap_high_addr;
    } else if (_code_heap_addr != NULL && _code_heap_memory_offset >= 0) {
        _code_heap[0] = *(char**)_code_heap_addr;
        _code_heap_low = *(const void**)(_code_heap[0] + _code_heap_memory_offset + _vs_low_bound_offset);
        _code_heap_high = *(const void**)(_code_heap[0] + _code_heap_memory_offset + _vs_high_bound_offset);
    }

    // Invariant: _code_heap[i] != NULL iff all CodeHeap structures are available
    if (_code_heap[0] != NULL && _code_heap_segment_shift >= 0) {
        _code_heap_segment_shift = *(int*)(_code_heap[0] + _code_heap_segment_shift);
    }
    if (_code_heap_memory_offset < 0 || _code_heap_segmap_offset < 0 ||
        _code_heap_segment_shift < 0 || _code_heap_segment_shift > 16 ||
        _heap_block_used_offset < 0) {
        memset(_code_heap, 0, sizeof(_code_heap));
    }
}

void VMStructs::initJvmFunctions() {
    if (VM::hotspot_version() == 8) {
        _lock_func = (LockFunc)_libjvm->findSymbol("_ZN7Monitor28lock_without_safepoint_checkEv");
        _unlock_func = (LockFunc)_libjvm->findSymbol("_ZN7Monitor6unlockEv");
    }

    if (VM::hotspot_version() > 0) {
        CodeBlob* blob = _libjvm->findBlob("_ZNK5frame26is_interpreted_frame_validEP10JavaThread");
        if (blob != NULL) {
            _interpreted_frame_valid_start = blob->_start;
            _interpreted_frame_valid_end = blob->_end;
        }
    }

    // Datadog-specific function pointer resolution
    _heap_usage_func = (HeapUsageFunc)findHeapUsageFunc();
    _gc_heap_summary_func = (GCHeapSummaryFunc)_libjvm->findSymbol(
        "_ZN13CollectedHeap19create_heap_summaryEv");
    _is_valid_method_func = (IsValidMethodFunc)_libjvm->findSymbol(
        "_ZN6Method15is_valid_methodEPKS_");
}

void VMStructs::patchSafeFetch() {
    // Workarounds for JDK-8307549 and JDK-8321116
    if (WX_MEMORY && VM::hotspot_version() == 17) {
        void** entry = (void**)_libjvm->findSymbol("_ZN12StubRoutines18_safefetch32_entryE");
        if (entry != NULL) {
            *entry = (void*)SafeAccess::load32;
        }
    } else if (WX_MEMORY && VM::hotspot_version() == 11) {
        void** entry = (void**)_libjvm->findSymbol("_ZN12StubRoutines17_safefetchN_entryE");
        if (entry != NULL) {
            *entry = (void*)SafeAccess::load;
        }
    }
}

void VMStructs::initTLS(void* vm_thread) {
    for (int i = 0; i < 1024; i++) {
        if (pthread_getspecific((pthread_key_t)i) == vm_thread) {
            _tls_index = i;
            break;
        }
    }
}

void VMStructs::initThreadBridge() {
    jthread thread;
    if (VM::jvmti()->GetCurrentThread(&thread) != 0) {
        return;
    }

    JNIEnv* env = VM::jni();
    jclass thread_class = env->FindClass("java/lang/Thread");
    if (thread_class == NULL || (_tid = env->GetFieldID(thread_class, "tid", "J")) == NULL) {
        env->ExceptionClear();
        return;
    }

    if (VM::isOpenJ9()) {
        void* j9thread = J9Ext::j9thread_self();
        if (j9thread != NULL) {
            initTLS(j9thread);
        }
    } else {
        // Get eetop field - a bridge from Java Thread to VMThread
        if ((_eetop = env->GetFieldID(thread_class, "eetop", "J")) == NULL) {
            // No such field - probably not a HotSpot JVM
            env->ExceptionClear();
            return;
        }

        VMThread* vm_thread = VMThread::fromJavaThread(env, thread);
        if (vm_thread != NULL) {
            _has_native_thread_id = _thread_osthread_offset >= 0 && _osthread_id_offset >= 0;
            initTLS(vm_thread);
            _env_offset = (intptr_t)env - (intptr_t)vm_thread;
            memcpy(_java_thread_vtbl, vm_thread->vtable(), sizeof(_java_thread_vtbl));
        }
    }
}

// ===== Datadog-specific VMStructs extensions =====

void VMStructs::initUnsafeFunctions() {
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

void VMStructs::initCriticalJNINatives() {
#ifdef __aarch64__
    // aarch64 does not support CriticalJNINatives
    VMFlag* flag = VMFlag::find("CriticalJNINatives", {VMFlag::Type::Bool});
    if (flag != nullptr && flag->get()) {
        flag->set(0);
    }
#endif // __aarch64__
}

const void *VMStructs::findHeapUsageFunc() {
    if (VM::hotspot_version() < 17) {
        // For JDK 11 it is really unreliable to find the memory_usage function -
        // just disable it
        return nullptr;
    } else {
        VMFlag* flag = VMFlag::find("UseG1GC", {VMFlag::Type::Bool});
        if (flag != NULL && flag->get()) {
            // The CollectedHeap::memory_usage function is a virtual one -
            // G1, Shenandoah and ZGC are overriding it and calling the base class
            // method results in asserts triggering. Therefore, we try to locate the
            // concrete overridden method form.
            return _libjvm->findSymbol("_ZN15G1CollectedHeap12memory_usageEv");
        }
        flag = VMFlag::find("UseShenandoahGC", {VMFlag::Type::Bool});
        if (flag != NULL && flag->get()) {
            return _libjvm->findSymbol("_ZN14ShenandoahHeap12memory_usageEv");
        }
        flag = VMFlag::find("UseZGC", {VMFlag::Type::Bool});
        if (flag != NULL && flag->get() && VM::hotspot_version() < 21) {
            // acessing this method in JDK 21 (generational ZGC) wil cause SIGSEGV
            return _libjvm->findSymbol("_ZN14ZCollectedHeap12memory_usageEv");
        }
        return _libjvm->findSymbol("_ZN13CollectedHeap12memory_usageEv");
    }
}

bool VMStructs::isSafeToWalk(uintptr_t pc) {
    // Check if PC is in the unsafe-to-walk code region
    // Note: findFrameDesc now returns by value instead of pointer, but it always returns
    // a valid FrameDesc (either from table or default_frame), so the old pointer check
    // was always true. The effective logic is simply checking if pc is in _unsafe_to_walk.
    return !_unsafe_to_walk.contains((const void *)pc);
}

void JNICALL VMStructs::NativeMethodBind(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
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
            _lock.unlock();
            if (delayed != NULL) {
                delayed[delayedCounter] = method;
                delayed[delayedCounter + 1] = address;
                delayedCounter += 2;
            }
            _lock.unlock();
        }
    }
}

void VMStructs::checkNativeBinding(jvmtiEnv *jvmti, JNIEnv *jni,
                                   jmethodID method, void *address) {
    char *method_name;
    char *method_sig;
    int error = jvmti->GetMethodName(method, &method_name, &method_sig, NULL);
    if (error == 0) {
        if (strcmp(method_name, "getMemoryUsage0") == 0 &&
            strcmp(method_sig, "(Z)Ljava/lang/management/MemoryUsage;") == 0) {
            _memory_usage_func = (MemoryUsageFunc)address;
        }
    }
    jvmti->Deallocate((unsigned char *)method_sig);
    jvmti->Deallocate((unsigned char *)method_name);
}

VMThread* VMThread::current() {
    return _tls_index >= 0 ? (VMThread*)pthread_getspecific((pthread_key_t)_tls_index) : NULL;
}

int VMThread::nativeThreadId(JNIEnv* jni, jthread thread) {
    if (_has_native_thread_id) {
        VMThread* vm_thread = fromJavaThread(jni, thread);
        return vm_thread != NULL ? vm_thread->osThreadId() : -1;
    }
    return VM::isOpenJ9() ? J9Ext::GetOSThreadID(thread) : -1;
}

int VMThread::osThreadId() {
    const char* osthread = *(const char**) at(_thread_osthread_offset);
    if (osthread != NULL) {
        // Java thread may be in the middle of termination, and its osthread structure just released
        return SafeAccess::load32((int32_t*)(osthread + _osthread_id_offset), -1);
    }
    return -1;
}

JNIEnv* VMThread::jni() {
    if (_env_offset < 0) {
        return VM::jni();  // fallback for non-HotSpot JVM
    }
    return isJavaThread() ? (JNIEnv*) at(_env_offset) : NULL;
}

jmethodID VMMethod::id() {
    // We may find a bogus NMethod during stack walking, it does not always point to a valid VMMethod
    const char* const_method = (const char*) SafeAccess::load((void**) at(_method_constmethod_offset));
    if (!goodPtr(const_method)) {
        return NULL;
    }

    const char* cpool = (const char*) SafeAccess::load((void**)(const_method + _constmethod_constants_offset));
    unsigned short num = (unsigned short) SafeAccess::load32((int32_t*)(const_method + _constmethod_idnum_offset), 0);
    if (goodPtr(cpool)) {
        VMKlass* holder = *(VMKlass**)(cpool + _pool_holder_offset);
        if (goodPtr(holder)) {
            jmethodID* ids = holder->jmethodIDs();
            if (ids != NULL && num < (size_t)ids[0]) {
                return ids[num + 1];
            }
        }
    }
    return NULL;
}

jmethodID VMMethod::validatedId() {
    jmethodID method_id = id();
    if (!_can_dereference_jmethod_id || (goodPtr(method_id) && *(VMMethod**)method_id == this)) {
        return method_id;
    }
    return NULL;
}

VMNMethod* CodeHeap::findNMethod(char* heap, const void* pc) {
    unsigned char* heap_start = *(unsigned char**)(heap + _code_heap_memory_offset + _vs_low_offset);
    unsigned char* segmap = *(unsigned char**)(heap + _code_heap_segmap_offset + _vs_low_offset);
    size_t idx = ((unsigned char*)pc - heap_start) >> _code_heap_segment_shift;

    if (segmap[idx] == 0xff) {
        return NULL;
    }
    while (segmap[idx] > 0) {
        idx -= segmap[idx];
    }

    unsigned char* block = heap_start + (idx << _code_heap_segment_shift) + _heap_block_used_offset;
    return *block ? align<VMNMethod*>(block + sizeof(uintptr_t)) : NULL;
}

int VMNMethod::findScopeOffset(const void* pc) {
    intptr_t pc_offset = (const char*)pc - code();
    if (pc_offset < 0 || pc_offset > 0x7fffffff) {
        return -1;
    }

    const int* scopes_pcs = (const int*) at(_scopes_pcs_offset);
    PcDesc* pcd = (PcDesc*) immutableDataAt(scopes_pcs[0]);
    PcDesc* pcd_end = (PcDesc*) immutableDataAt(scopes_pcs[1]);
    int low = 0;
    int high = (pcd_end - pcd) - 1;

    while (low <= high) {
        int mid = (unsigned int)(low + high) >> 1;
        if (pcd[mid]._pc < pc_offset) {
            low = mid + 1;
        } else if (pcd[mid]._pc > pc_offset) {
            high = mid - 1;
        } else {
            return pcd[mid]._scope_offset;
        }
    }

    return pcd + low < pcd_end ? pcd[low]._scope_offset : -1;
}

int ScopeDesc::readInt() {
    unsigned char c = *_stream++;
    unsigned int n = c - _unsigned5_base;
    if (c >= 192) {
        for (int shift = 6; ; shift += 6) {
            c = *_stream++;
            n += (c - _unsigned5_base) << shift;
            if (c < 192 || shift >= 24) break;
        }
    }
    return n;
}

VMFlag* VMFlag::find(const char* name) {
    if (_flags_addr != NULL && VMFlag::type_size() > 0) {
        size_t count = *(size_t*)_flag_count;

        for (size_t i = 0; i < count; i++) {
            VMFlag* f = VMFlag::cast(*(const char**)_flags_addr + i * VMFlag::type_size());
            if (f->name() != NULL && strcmp(f->name(), name) == 0 && f->addr() != NULL) {
                return f;
            }
        }
    }
    return NULL;
}

VMFlag *VMFlag::find(const char *name, std::initializer_list<VMFlag::Type> types) {
    int mask = 0;
    for (int type : types) {
        mask |= 0x1 << type;
    }
    return find(name, mask);
}

VMFlag *VMFlag::find(const char *name, int type_mask) {
    if (_flags_addr != NULL && VMFlag::type_size() > 0) {
        size_t count = *(size_t*)_flag_count;
        for (size_t i = 0; i < count; i++) {
            VMFlag* f = VMFlag::cast(*(const char**)_flags_addr + i * VMFlag::type_size());
            if (f->name() != NULL && strcmp(f->name(), name) == 0) {
                int masked = 0x1 << f->type();
                if (masked & type_mask) {
                    return (VMFlag*)f;
                }
            }
        }
    }
    return NULL;
}

int VMFlag::type() {
    if (VM::hotspot_version() < 16) { // in JDK 16 the JVM flag implementation has changed
        char* type_name = *(char **)at(_flag_type_offset);
        if (type_name == NULL) {
            return Unknown;
        }
        if (strcmp(type_name, "bool") == 0) {
            return Bool;
        }
        if (strcmp(type_name, "int") == 0) {
            return Int;
        }
        if (strcmp(type_name, "uint") == 0) {
            return Uint;
        }
        if (strcmp(type_name, "intx") == 0) {
            return Intx;
        }
        if (strcmp(type_name, "uintx") == 0) {
            return Uintx;
        }
        if (strcmp(type_name, "uint64_t") == 0) {
            return Uint64_t;
        }
        if (strcmp(type_name, "size_t") == 0) {
            return Size_t;
        }
        if (strcmp(type_name, "double") == 0) {
            return Double;
        }
        if (strcmp(type_name, "ccstr") == 0) {
            return String;
        }
        if (strcmp(type_name, "ccstrlist") == 0) {
            return Stringlist;
        }
        return Unknown;
    }
    return *(int *)at(_flag_type_offset);
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

OSThreadState VMThread::osThreadState() {
    if (VMStructs::thread_osthread_offset() >= 0 && VMStructs::osthread_state_offset() >= 0) {
        const char *osthread = *(char **)at(VMStructs::thread_osthread_offset());
        if (osthread != nullptr) {
            // If the location is not accessible, the thread must have been terminated
            int value = SafeAccess::safeFetch32((int*)(osthread + VMStructs::osthread_state_offset()),
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

int VMThread::state() {
    int offset = VMStructs::thread_state_offset();
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

bool HeapUsage::isLastGCUsageSupported() {
    // only supported for JDK 17+
    // the CollectedHeap structure is vastly different in JDK 11 and earlier so
    // we can't support it
    return _collected_heap_addr != NULL && _heap_usage_func != NULL;
}

bool HeapUsage::needsNativeBindingInterception() {
    return _collected_heap_addr == NULL ||
           (_heap_usage_func == NULL && _gc_heap_summary_func == NULL);
}

jlong HeapUsage::getMaxHeap(JNIEnv *env) {
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

HeapUsage HeapUsage::get() {
    return get(true);
}

HeapUsage HeapUsage::get(bool allow_jmx) {
    HeapUsage usage;
    if (_collected_heap_addr != NULL) {
        if (_heap_usage_func != NULL) {
            // this is the JDK 17+ path
            usage = _heap_usage_func(*(char**)_collected_heap_addr);
            usage._used_at_last_gc =
                ((CollectedHeapWrapper *)*(char**)_collected_heap_addr)->_used_at_last_gc;
        } else if (_gc_heap_summary_func != NULL) {
            // this is the JDK 11 path
            // we need to collect GCHeapSummary information first
            GCHeapSummary summary = _gc_heap_summary_func(*(char**)_collected_heap_addr);
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
