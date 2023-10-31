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

#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include "spinLock.h"
#include "vmStructs.h"
#include "j9Ext.h"
#include "vector"
#include "safeAccess.h"
#include "jniHelper.h"


CodeCache* VMStructs::_libjvm = NULL;
CodeCache VMStructs::_unsafe_to_walk("unwalkable code");

bool VMStructs::_has_class_names = false;
bool VMStructs::_has_method_structs = false;
bool VMStructs::_has_class_loader_data = false;
bool VMStructs::_has_native_thread_id = false;
bool VMStructs::_has_perm_gen = false;

int VMStructs::_klass_name_offset = -1;
int VMStructs::_symbol_length_offset = -1;
int VMStructs::_symbol_length_and_refcount_offset = -1;
int VMStructs::_symbol_body_offset = -1;
int VMStructs::_class_loader_data_offset = -1;
int VMStructs::_class_loader_data_next_offset = -1;
int VMStructs::_methods_offset = -1;
int VMStructs::_jmethod_ids_offset = -1;
int VMStructs::_thread_osthread_offset = -1;
int VMStructs::_thread_anchor_offset = -1;
int VMStructs::_thread_state_offset = -1;
int VMStructs::_osthread_id_offset = -1;
int VMStructs::_osthread_state_offset = -1;
int VMStructs::_anchor_sp_offset = -1;
int VMStructs::_anchor_pc_offset = -1;
int VMStructs::_frame_size_offset = -1;
int VMStructs::_frame_complete_offset = -1;
int VMStructs::_nmethod_name_offset = -1;
int VMStructs::_nmethod_method_offset = -1;
int VMStructs::_nmethod_entry_offset = -1;
int VMStructs::_nmethod_state_offset = -1;
int VMStructs::_nmethod_level_offset = -1;
int VMStructs::_method_constmethod_offset = -1;
int VMStructs::_method_code_offset = -1;
int VMStructs::_constmethod_constants_offset = -1;
int VMStructs::_constmethod_idnum_offset = -1;
int VMStructs::_pool_holder_offset = -1;
int VMStructs::_array_data_offset = -1;
int VMStructs::_code_heap_memory_offset = -1;
int VMStructs::_code_heap_segmap_offset = -1;
int VMStructs::_code_heap_segment_shift = -1;
int VMStructs::_vs_low_bound_offset = -1;
int VMStructs::_vs_high_bound_offset = -1;
int VMStructs::_vs_low_offset = -1;
int VMStructs::_vs_high_offset = -1;
int VMStructs::_flag_name_offset = -1;
int VMStructs::_flag_addr_offset = -1;
const char* VMStructs::_flags_addr = NULL;
int VMStructs::_flag_count = 0;
int VMStructs::_flag_size = 0;
char* VMStructs::_code_heap[3] = {};
const void* VMStructs::_code_heap_low = NO_MIN_ADDRESS;
const void* VMStructs::_code_heap_high = NO_MAX_ADDRESS;
char** VMStructs::_code_heap_addr = NULL;
const void** VMStructs::_code_heap_low_addr = NULL;
const void** VMStructs::_code_heap_high_addr = NULL;
int* VMStructs::_klass_offset_addr = NULL;

jfieldID VMStructs::_eetop;
jfieldID VMStructs::_tid;
jfieldID VMStructs::_klass = NULL;
int VMStructs::_tls_index = -1;
intptr_t VMStructs::_env_offset;

VMStructs::GetStackTraceFunc VMStructs::_get_stack_trace = NULL;
VMStructs::LockFunc VMStructs::_lock_func;
VMStructs::LockFunc VMStructs::_unlock_func;

VMStructs::HeapUsageFunc VMStructs::_heap_usage_func = NULL;
VMStructs::MemoryUsageFunc VMStructs::_memory_usage_func = NULL;
VMStructs::GCHeapSummaryFunc VMStructs::_gc_heap_summary_func = NULL;
VMStructs::FindFlagFunc VMStructs::_find_flag_func = NULL;
VMStructs::IsValidMethodFunc VMStructs::_is_valid_method_func = NULL;

void** VMStructs::_collected_heap_addr = NULL;

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
    _libjvm = libjvm;

    initOffsets();
    initJvmFunctions();
}

// Run when VM is initialized and JNI is available
void VMStructs::ready() {
    resolveOffsets();

    JNIEnv* env = VM::jni();
    initThreadBridge(env);
    initLogging(env);
    initMemoryUsage(env);
    _libjvm->dump();
}

void VMStructs::initOffsets() {
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
        const char* type = *(const char**)(entry + type_offset);
        const char* field = *(const char**)(entry + field_offset);
        if (type == NULL || field == NULL) {
            break;
        }

        if (strcmp(type, "Klass") == 0) {
            if (strcmp(field, "_name") == 0) {
                _klass_name_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_class_loader_data") == 0) {
                _class_loader_data_offset = *(int*)(entry + offset_offset);
            }
        } else if (strcmp(type, "Symbol") == 0) {
            if (strcmp(field, "_length") == 0) {
                _symbol_length_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_length_and_refcount") == 0) {
                _symbol_length_and_refcount_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_body") == 0) {
                _symbol_body_offset = *(int*)(entry + offset_offset);
            }
        } else if (strcmp(type, "CompiledMethod") == 0 || strcmp(type, "nmethod") == 0) {
            if (strcmp(field, "_method") == 0) {
                _nmethod_method_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_verified_entry_point") == 0) {
                _nmethod_entry_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_state") == 0) {
                _nmethod_state_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_comp_level") == 0) {
                _nmethod_level_offset = *(int*)(entry + offset_offset);
            }
        } else if (strcmp(type, "Method") == 0) {
            if (strcmp(field, "_constMethod") == 0) {
                _method_constmethod_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_code") == 0) {
                _method_code_offset = *(int*)(entry + offset_offset);
            }
        } else if (strcmp(type, "ConstMethod") == 0) {
            if (strcmp(field, "_constants") == 0) {
                _constmethod_constants_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_method_idnum") == 0) {
                _constmethod_idnum_offset = *(int*)(entry + offset_offset);
            }
        } else if (strcmp(type, "ConstantPool") == 0) {
            if (strcmp(field, "_pool_holder") == 0) {
                _pool_holder_offset = *(int*)(entry + offset_offset);
            }
        } else if (strcmp(type, "InstanceKlass") == 0) {
            if (strcmp(field, "_class_loader_data") == 0) {
                _class_loader_data_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_methods") == 0) {
                _methods_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_methods_jmethod_ids") == 0) {
                _jmethod_ids_offset = *(int*)(entry + offset_offset);
            }
        } else if (strcmp(type, "ClassLoaderData") == 0) {
            if (strcmp(field, "_next") == 0) {
                _class_loader_data_next_offset = *(int*)(entry + offset_offset);
            }
        } else if (strcmp(type, "java_lang_Class") == 0) {
            if (strcmp(field, "_klass_offset") == 0) {
                _klass_offset_addr = *(int**)(entry + address_offset);
            }
        } else if (strcmp(type, "JavaThread") == 0) {
            if (strcmp(field, "_osthread") == 0) {
                _thread_osthread_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_anchor") == 0) {
                _thread_anchor_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_thread_state") == 0) {
                _thread_state_offset = *(int*)(entry + offset_offset);
            }
        } else if (strcmp(type, "OSThread") == 0) {
            if (strcmp(field, "_thread_id") == 0) {
                _osthread_id_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_state") == 0) {
                _osthread_state_offset = *(int*)(entry + offset_offset);
            }
        } else if (strcmp(type, "JavaFrameAnchor") == 0) {
            if (strcmp(field, "_last_Java_sp") == 0) {
                _anchor_sp_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_last_Java_pc") == 0) {
                _anchor_pc_offset = *(int*)(entry + offset_offset);
            }
        } else if (strcmp(type, "CodeBlob") == 0) {
            if (strcmp(field, "_frame_size") == 0) {
                _frame_size_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_frame_complete_offset") == 0) {
                _frame_complete_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_name") == 0) {
                _nmethod_name_offset = *(int*)(entry + offset_offset);
            }
        } else if (strcmp(type, "CodeCache") == 0) {
            if (strcmp(field, "_heap") == 0) {
                _code_heap_addr = *(char***)(entry + address_offset);
            } else if (strcmp(field, "_heaps") == 0) {
                _code_heap_addr = *(char***)(entry + address_offset);
            } else if (strcmp(field, "_low_bound") == 0) {
                _code_heap_low_addr = *(const void***)(entry + address_offset);
            } else if (strcmp(field, "_high_bound") == 0) {
                _code_heap_high_addr = *(const void***)(entry + address_offset);
            }
        } else if (strcmp(type, "CodeHeap") == 0) {
            if (strcmp(field, "_memory") == 0) {
                _code_heap_memory_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_segmap") == 0) {
                _code_heap_segmap_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_log2_segment_size") == 0) {
                _code_heap_segment_shift = *(int*)(entry + offset_offset);
            }
        } else if (strcmp(type, "VirtualSpace") == 0) {
            if (strcmp(field, "_low_boundary") == 0) {
                _vs_low_bound_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_high_boundary") == 0) {
                _vs_high_bound_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_low") == 0) {
                _vs_low_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_high") == 0) {
                _vs_high_offset = *(int*)(entry + offset_offset);
            }
        } else if (strcmp(type, "GrowableArray<int>") == 0) {
            if (strcmp(field, "_data") == 0) {
                _array_data_offset = *(int*)(entry + offset_offset);
            }
        } else if (strcmp(type, "JVMFlag") == 0 || strcmp(type, "Flag") == 0) {
            if (strcmp(field, "_name") == 0 || strcmp(field, "name") == 0) {
                _flag_name_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "_addr") == 0 || strcmp(field, "addr") == 0) {
                _flag_addr_offset = *(int*)(entry + offset_offset);
            } else if (strcmp(field, "flags") == 0) {
                _flags_addr = **(char***)(entry + address_offset);
            } else if (strcmp(field, "numFlags") == 0) {
                _flag_count = **(int**)(entry + address_offset);
            }
        } else if (strcmp(type, "PermGen") == 0) {
            _has_perm_gen = true;
        } else if (strcmp(type, "Universe") == 0) {
            if (strcmp(field, "_collectedHeap") == 0) {
                _collected_heap_addr = *(void***)(entry + address_offset);
            }
        }
    }

    entry = readSymbol("gHotSpotVMTypes");
    stride = readSymbol("gHotSpotVMTypeEntryArrayStride");
    type_offset = readSymbol("gHotSpotVMTypeEntryTypeNameOffset");
    uintptr_t size_offset = readSymbol("gHotSpotVMTypeEntrySizeOffset");

    if (entry == 0 || stride == 0) {
        return;
    }

    for (;; entry += stride) {
        const char* type = *(const char**)(entry + type_offset);
        if (type == NULL) {
            break;
        }

        if (strcmp(type, "JVMFlag") == 0 || strcmp(type, "Flag") == 0) {
            _flag_size = *(int*)(entry + size_offset);
            break;
        }
    }
}

void VMStructs::resolveOffsets() {
    if (_klass_offset_addr != NULL) {
        _klass = (jfieldID)(uintptr_t)(*_klass_offset_addr << 2 | 2);
    }

    _has_class_names = _klass_name_offset >= 0
            && (_symbol_length_offset >= 0 || _symbol_length_and_refcount_offset >= 0)
            && _symbol_body_offset >= 0
            && _klass != NULL;

    _has_method_structs = _jmethod_ids_offset >= 0
            && _nmethod_method_offset >= 0
            && _nmethod_entry_offset >= 0
            && _nmethod_state_offset >= 0
            && _method_constmethod_offset >= 0
            && _method_code_offset >= 0
            && _constmethod_constants_offset >= 0
            && _constmethod_idnum_offset >= 0
            && _pool_holder_offset >= 0;

    _has_class_loader_data = _class_loader_data_offset >= 0
        && _class_loader_data_next_offset == sizeof(uintptr_t) * 8 + 8
        && _methods_offset >= 0
        && _klass != NULL
        && _lock_func != NULL && _unlock_func != NULL;

    if (_code_heap_addr != NULL && _code_heap_low_addr != NULL && _code_heap_high_addr != NULL) {
        char* code_heaps = *_code_heap_addr;
        unsigned int code_heap_count = *(unsigned int*)code_heaps;
        if (code_heap_count <= 3 && _array_data_offset >= 0) {
            char* code_heap_array = *(char**)(code_heaps + _array_data_offset);
            memcpy(_code_heap, code_heap_array, code_heap_count * sizeof(_code_heap[0]));
        }
        _code_heap_low = *_code_heap_low_addr;
        _code_heap_high = *_code_heap_high_addr;
    } else if (_code_heap_addr != NULL && _code_heap_memory_offset >= 0) {
        _code_heap[0] = *_code_heap_addr;
        _code_heap_low = *(const void**)(_code_heap[0] + _code_heap_memory_offset + _vs_low_bound_offset);
        _code_heap_high = *(const void**)(_code_heap[0] + _code_heap_memory_offset + _vs_high_bound_offset);
    }

    // Invariant: _code_heap[i] != NULL iff all CodeHeap structures are available
    if (_code_heap[0] != NULL && _code_heap_segment_shift >= 0) {
        _code_heap_segment_shift = *(int*)(_code_heap[0] + _code_heap_segment_shift);
    }
    if (_code_heap_memory_offset < 0 || _code_heap_segmap_offset < 0 ||
        _code_heap_segment_shift < 0 || _code_heap_segment_shift > 16) {
        memset(_code_heap, 0, sizeof(_code_heap));
    }
}

void VMStructs::initUnsafeFunctions() {
    // see https://github.com/openjdk/jdk/blob/master/src/hotspot/share/gc/z/zBarrierSetRuntime.hpp#L33
    // https://bugs.openjdk.org/browse/JDK-8302317
    std::vector<const char*> unsafeMangledPrefixes {
            "_ZN18ZBarrierSetRuntime",
            "_ZN9JavaCalls11call_helper",
            "_ZN14MM_RootScanner"
    };

    std::vector<const void*> symbols;
    _libjvm->findSymbolsByPrefix(unsafeMangledPrefixes, symbols);
    for (const void* symbol : symbols) {
        CodeBlob *blob = _libjvm->find(symbol);
        if (blob) {
            _unsafe_to_walk.add(blob->_start, ((uintptr_t) blob->_end - (uintptr_t) blob->_start), blob->_name, true);
        }
    }
}

bool VMStructs::isFlagTrue(const char* name) {
    // ! This is only valid for boolean flags !
    // The memory layout of JVMFlag puts the pointer to the value at the beginning of the flag structure
    // so we can just dereference and cast it properly.
    bool** ptr = (bool**)_find_flag_func(name, strlen(name), true, true);
    if (ptr != NULL) {
        return **ptr;
    }
    return false;
}

const void* VMStructs::findHeapUsageFunc() {
    if (_find_flag_func != NULL) {
        // The CollectedHeap::memory_usage function is a virtual one -
        // G1, Shenandoah and ZGC are overriding it and calling the base class method results
        // in asserts triggering. Therefore, we try to locate the concrete overridden method form.
        if (isFlagTrue("UseG1GC")) {
            return _libjvm->findSymbol("_ZN15G1CollectedHeap12memory_usageEv");
        } else if (isFlagTrue("UseShenandoahGC")) {
            return _libjvm->findSymbol("_ZN14ShenandoahHeap12memory_usageEv");
        } else if (isFlagTrue("UseZGC") && VM::java_version() < 21) {
            // acessing this method in JDK 21 (generational ZGC) wil cause SIGSEGV 
            return _libjvm->findSymbol("_ZN14ZCollectedHeap12memory_usageEv");
        }
    }
    return _libjvm->findSymbol("_ZN13CollectedHeap12memory_usageEv");
}

void VMStructs::initJvmFunctions() {
    _get_stack_trace = (GetStackTraceFunc)_libjvm->findSymbolByPrefix("_ZN8JvmtiEnv13GetStackTraceEP10JavaThreadiiP");

    if (VM::java_version() == 8) {
        _lock_func = (LockFunc)_libjvm->findSymbol("_ZN7Monitor28lock_without_safepoint_checkEv");
        _unlock_func = (LockFunc)_libjvm->findSymbol("_ZN7Monitor6unlockEv");
    }

    _find_flag_func =(FindFlagFunc) _libjvm->findSymbol("_ZN7JVMFlag9find_flagEPKcmbb");
    _heap_usage_func = (HeapUsageFunc) findHeapUsageFunc();
    _gc_heap_summary_func = (GCHeapSummaryFunc)_libjvm->findSymbol("_ZN13CollectedHeap19create_heap_summaryEv");
    _is_valid_method_func = (IsValidMethodFunc)_libjvm->findSymbol("_ZN6Method15is_valid_methodEPKS_");
    initUnsafeFunctions();
}

void VMStructs::initTLS(void* vm_thread) {
    for (int i = 0; i < 1024; i++) {
        if (pthread_getspecific((pthread_key_t)i) == vm_thread) {
            _tls_index = i;
            break;
        }
    }
}

void VMStructs::initThreadBridge(JNIEnv* env) {
    jthread thread;
    if (VM::jvmti()->GetCurrentThread(&thread) != 0) {
        return;
    }

    // Get eetop field - a bridge from Java Thread to VMThread
    jclass thread_class = env->GetObjectClass(thread);
    if ((_tid = env->GetFieldID(thread_class, "tid", "J")) == NULL ||
        (_eetop = env->GetFieldID(thread_class, "eetop", "J")) == NULL) {
        // No such field - probably not a HotSpot JVM
        env->ExceptionClear();

        void* j9thread = J9Ext::j9thread_self();
        if (j9thread != NULL) {
            initTLS(j9thread);
        }
    } else {
        // HotSpot
        VMThread* vm_thread = VMThread::fromJavaThread(env, thread);
        if (vm_thread != NULL) {
            _env_offset = (intptr_t)env - (intptr_t)vm_thread;
            _has_native_thread_id = _thread_osthread_offset >= 0 && _osthread_id_offset >= 0;
            initTLS(vm_thread);
        }
    }
}

void VMStructs::initLogging(JNIEnv* env) {
    // Workaround for JDK-8238460
    // Can not be used for OpenJ9 because it will crash the VM
    if (VM::java_version() >= 15 && !VM::isOpenJ9()) {
        VMManagement* management = VM::management();
        if (management != NULL) {
            jstring log_config = management->ExecuteDiagnosticCommand(env, env->NewStringUTF("VM.log list"));
            if (log_config != NULL) {
                char cmd[128] = "VM.log what=jni+resolve=error decorators=";
                const char* s = env->GetStringUTFChars(log_config, NULL);
                if (s != NULL) {
                    const char* p = strstr(s, "#0: ");
                    const char* q;
                    if (p != NULL && (p = strchr(p + 4, ' ')) != NULL && (p = strchr(p + 1, ' ')) != NULL &&
                        (q = strchr(p + 1, '\n')) != NULL && q - p < sizeof(cmd) - 41) {
                        memcpy(cmd + 41, p + 1, q - p - 1);
                    }
                    env->ReleaseStringUTFChars(log_config, s);
                }
                management->ExecuteDiagnosticCommand(env, env->NewStringUTF(cmd));
            }
        }
        env->ExceptionClear();
    }
}

void VMStructs::initMemoryUsage(JNIEnv* env) {
    jclass factory = env->FindClass("java/lang/management/ManagementFactory");
    jclass memoryBeanClass = env->FindClass("java/lang/management/MemoryMXBean");
    jmethodID get_memory = env->GetStaticMethodID(factory, "getMemoryMXBean", "()Ljava/lang/management/MemoryMXBean;");
    jobject memoryBean = env->CallStaticObjectMethod(factory, get_memory);
    jniExceptionCheck(env);
    jmethodID get_heap = env->GetMethodID(memoryBeanClass, "getHeapMemoryUsage", "()Ljava/lang/management/MemoryUsage;");
    env->CallObjectMethod(memoryBean, get_heap);
    jniExceptionCheck(env);
}

VMThread* VMThread::current() {
    return (VMThread*)pthread_getspecific((pthread_key_t)_tls_index);
}

int VMThread::nativeThreadId(JNIEnv* jni, jthread thread) {
    if (_has_native_thread_id) {
        VMThread* vm_thread = fromJavaThread(jni, thread);
        return vm_thread != NULL ? vm_thread->osThreadId() : -1;
    }
    return J9Ext::GetOSThreadID(thread);
}

jmethodID VMMethod::id() {
    // We may find a bogus NMethod during stack walking, it does not always point to a valid VMMethod
    const char* const_method = (const char*) SafeAccess::load((void**) at(_method_constmethod_offset));
    if (const_method == NULL) {
        return NULL;
    }

    const char* cpool = *(const char**) (const_method + _constmethod_constants_offset);
    unsigned short num = *(unsigned short*) (const_method + _constmethod_idnum_offset);
    if (cpool != NULL) {
        VMKlass* holder = *(VMKlass**)(cpool + _pool_holder_offset);
        if (holder != NULL) {
            jmethodID* ids = holder->jmethodIDs();
            if (ids != NULL && num < (size_t)ids[0]) {
                return ids[num + 1];
            }
        }
    }
    return NULL;
}

/**
 * jmethodIDs are unreliable, even if the profiler has created strong global JNI references to the classes
 * containing methods with those jmethodIDs. This is affecting particularly hard the 'record-on-shutdown' feature
 * when the VM class structures seem to be aggressively cleaned-up despite JNI global references pointing to them
 * are still there.
 * This check is attempting to validate that all data structures required to reconstruct the method metadata
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
    const char* method_ptr = (const char*) SafeAccess::load((void**) id);
    // check for NULL ptr and 'empty' ptr (JNIMethodBlock::_free_method)
    if (method_ptr == NULL || (size_t)method_ptr == 55) {
        return false;
    }
    if (_is_valid_method_func != NULL) {
        if (!_is_valid_method_func((void*)method_ptr)) {
            return false;
        }
    }
    // we can only perform the extended validity check if there are expected vmStructs in place

    const char* const_method = NULL;
    const char* cpool = NULL;
    const char* cpool_holder = NULL;
    const char* cl_data = NULL;

    if (_method_constmethod_offset >= 0) {
        const_method = (const char*) SafeAccess::load((void**) (method_ptr + _method_constmethod_offset));
        if (const_method == NULL) {
            return false;
        }
    }
    if (_constmethod_constants_offset >= 0) {
        cpool = (const char*) SafeAccess::load((void**) (const_method + _constmethod_constants_offset));
        if (cpool == NULL) {
            return false;
        }
    }
    if (_pool_holder_offset >= 0) {
        cpool_holder = (const char*) SafeAccess::load((void**) (cpool + _pool_holder_offset));
        if (cpool_holder == NULL) {
            return false;
        }
    }
    if (_class_loader_data_offset >= 0) {
        cl_data = (const char*) SafeAccess::load((void**) (cpool_holder + _class_loader_data_offset));
        if (cl_data == NULL) {
            return false;
        }
    }
    return true;
}

bool VMMethod::check_jmethodID_J9(jmethodID id) {
    /*
    The id can be cast to J9JNIMethodID*
    The J9JNIMethodID structure is:
    - J9Method* method
    - UDATA vTableIndex
    */
    void* j9methodIDPtr = SafeAccess::load((void**) id); //*(void**)id;
    if (j9methodIDPtr == nullptr) {
        return false;
    }

    void* j9methodPtr = SafeAccess::load((void**) j9methodIDPtr); //*(void**)j9methodIDPtr;

    if (j9methodPtr == nullptr) {
        return false;
    }

    /*
    The J9Method structure:
    - U_8* bytecodes
	- J9ConstantPool* constantPool
	- void* methodRunAddress
    */
    void* constantPoolPtr = SafeAccess::load((void**) j9methodPtr + 1);
    if (constantPoolPtr == nullptr) {
        return false;
    }

    /*
    The J9ConstantPool structure:
    - J9Class* ramClass;
	- J9ROMConstantPoolItem* romConstantPool;
    */
    void* ramClassPtr = SafeAccess::load((void**) constantPoolPtr);
    if (ramClassPtr == nullptr) {
        return false;
    }
    return true;
}

NMethod* CodeHeap::findNMethod(char* heap, const void* pc) {
    unsigned char* heap_start = *(unsigned char**)(heap + _code_heap_memory_offset + _vs_low_offset);
    unsigned char* segmap = *(unsigned char**)(heap + _code_heap_segmap_offset + _vs_low_offset);
    size_t idx = ((unsigned char*)pc - heap_start) >> _code_heap_segment_shift;

    if (segmap[idx] == 0xff) {
        return NULL;
    }
    while (segmap[idx] > 0) {
        idx -= segmap[idx];
    }

    unsigned char* block = heap_start + (idx << _code_heap_segment_shift);
    return block[sizeof(size_t)] ? (NMethod*)(block + 2 * sizeof(size_t)) : NULL;
}

void* JVMFlag::find(const char* name) {
    if (_flags_addr != NULL && _flag_size > 0) {
        for (int i = 0; i < _flag_count; i++) {
            JVMFlag* f = (JVMFlag*)(_flags_addr + i * _flag_size);
            if (f->name() != NULL && strcmp(f->name(), name) == 0) {
                return f->addr();
            }
        }
    }
    return NULL;
}

bool VMStructs::isSafeToWalk(uintptr_t pc) {
    return !(_unsafe_to_walk.contains((const void*) pc) && _unsafe_to_walk.findFrameDesc((const void*) pc));
}

void VMStructs::NativeMethodBind(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread, jmethodID method, void *address, void **new_address_ptr) {
    static SpinLock _lock;
    static int delayedCounter = 0;
    static void** delayed = (void**)malloc(512 * sizeof(void*) * 2);

    if (_memory_usage_func == NULL) {
        if (jvmti != NULL && jni != NULL) {
            checkNativeBinding(jvmti, jni, method, address);
            void** tmpDelayed = NULL;
            int tmpCounter = 0;
            _lock.lock();
            if (delayed != NULL && delayedCounter > 0) {
                // in order to minimize the lock time, we copy the delayed list, free it and release the lock
                tmpCounter = delayedCounter;
                tmpDelayed = (void**)malloc(tmpCounter * sizeof(void*) * 2);
                memcpy(tmpDelayed, delayed, tmpCounter * sizeof(void*) * 2);
                delayedCounter = 0;
                delayed = NULL;
                free(delayed);
            }
            _lock.unlock();
            // if there was a delayed list, we check it now, not blocking on the lock
            if (tmpDelayed != NULL) {
                for (int i = 0; i < tmpCounter; i += 2) {
                    checkNativeBinding(jvmti, jni, (jmethodID)tmpDelayed[i], tmpDelayed[i + 1]);
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

void VMStructs::checkNativeBinding(jvmtiEnv *jvmti, JNIEnv *jni, jmethodID method, void *address) {
    char* method_name;
    char* method_sig;
    int error = 0;
    if ((error = jvmti->GetMethodName(method, &method_name, &method_sig, NULL)) == 0) {
        if (strcmp(method_name, "getMemoryUsage0") == 0 && strcmp(method_sig, "(Z)Ljava/lang/management/MemoryUsage;") == 0) {
            _memory_usage_func = (MemoryUsageFunc) address;
        }
    }
    jvmti->Deallocate((unsigned char*)method_sig);
    jvmti->Deallocate((unsigned char*)method_name);
}
