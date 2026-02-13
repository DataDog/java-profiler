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


CodeCache* VMStructs::_libjvm = NULL;

bool VMStructs::_has_class_names = false;
bool VMStructs::_has_method_structs = false;
bool VMStructs::_has_compiler_structs = false;
bool VMStructs::_has_stack_structs = false;
bool VMStructs::_has_class_loader_data = false;
bool VMStructs::_has_native_thread_id = false;
bool VMStructs::_can_dereference_jmethod_id = false;
bool VMStructs::_compact_object_headers = false;

int VMStructs::_klass_name_offset = -1;
int VMStructs::_symbol_length_offset = -1;
int VMStructs::_symbol_length_and_refcount_offset = -1;
int VMStructs::_symbol_body_offset = -1;
int VMStructs::_oop_klass_offset = -1;
int VMStructs::_class_loader_data_offset = -1;
int VMStructs::_class_loader_data_next_offset = -1;
int VMStructs::_methods_offset = -1;
int VMStructs::_jmethod_ids_offset = -1;
int VMStructs::_thread_osthread_offset = -1;
int VMStructs::_thread_anchor_offset = -1;
int VMStructs::_thread_state_offset = -1;
int VMStructs::_thread_vframe_offset = -1;
int VMStructs::_thread_exception_offset = -1;
int VMStructs::_osthread_id_offset = -1;
int VMStructs::_call_wrapper_anchor_offset = -1;
int VMStructs::_comp_env_offset = -1;
int VMStructs::_comp_task_offset = -1;
int VMStructs::_comp_method_offset = -1;
int VMStructs::_anchor_sp_offset = -1;
int VMStructs::_anchor_pc_offset = -1;
int VMStructs::_anchor_fp_offset = -1;
int VMStructs::_blob_size_offset = -1;
int VMStructs::_frame_size_offset = -1;
int VMStructs::_frame_complete_offset = -1;
int VMStructs::_code_offset = -1;
int VMStructs::_data_offset = -1;
int VMStructs::_mutable_data_offset = -1;
int VMStructs::_relocation_size_offset = -1;
int VMStructs::_scopes_pcs_offset = -1;
int VMStructs::_scopes_data_offset = -1;
int VMStructs::_nmethod_name_offset = -1;
int VMStructs::_nmethod_method_offset = -1;
int VMStructs::_nmethod_entry_offset = -1;
int VMStructs::_nmethod_state_offset = -1;
int VMStructs::_nmethod_level_offset = -1;
int VMStructs::_nmethod_metadata_offset = -1;
int VMStructs::_nmethod_immutable_offset = -1;
int VMStructs::_method_constmethod_offset = -1;
int VMStructs::_method_code_offset = -1;
int VMStructs::_constmethod_constants_offset = -1;
int VMStructs::_constmethod_idnum_offset = -1;
int VMStructs::_pool_holder_offset = -1;
int VMStructs::_array_len_offset = 0;
int VMStructs::_array_data_offset = -1;
int VMStructs::_code_heap_memory_offset = -1;
int VMStructs::_code_heap_segmap_offset = -1;
int VMStructs::_code_heap_segment_shift = -1;
int VMStructs::_heap_block_used_offset = -1;
int VMStructs::_vs_low_bound_offset = -1;
int VMStructs::_vs_high_bound_offset = -1;
int VMStructs::_vs_low_offset = -1;
int VMStructs::_vs_high_offset = -1;
int VMStructs::_flag_name_offset = -1;
int VMStructs::_flag_addr_offset = -1;
int VMStructs::_flag_origin_offset = -1;
const char* VMStructs::_flags_addr = NULL;
int VMStructs::_flag_count = 0;
char* VMStructs::_code_heap[3] = {};
const void* VMStructs::_code_heap_low = NO_MIN_ADDRESS;
const void* VMStructs::_code_heap_high = NO_MAX_ADDRESS;
char** VMStructs::_code_heap_addr = NULL;
const void** VMStructs::_code_heap_low_addr = NULL;
const void** VMStructs::_code_heap_high_addr = NULL;
int* VMStructs::_klass_offset_addr = NULL;
char** VMStructs::_narrow_klass_base_addr = NULL;
char* VMStructs::_narrow_klass_base = NULL;
int* VMStructs::_narrow_klass_shift_addr = NULL;
int VMStructs::_narrow_klass_shift = -1;
char** VMStructs::_collected_heap_addr = NULL;
int VMStructs::_region_start_offset = -1;
int VMStructs::_region_size_offset = -1;
int VMStructs::_markword_klass_shift = -1;
int VMStructs::_markword_monitor_value = -1;
int VMStructs::_entry_frame_call_wrapper_offset = -1;
int VMStructs::_interpreter_frame_bcp_offset = 0;
unsigned char VMStructs::_unsigned5_base = 0;
const void** VMStructs::_call_stub_return_addr = NULL;
const void* VMStructs::_call_stub_return = NULL;
const void* VMStructs::_interpreted_frame_valid_start = NULL;
const void* VMStructs::_interpreted_frame_valid_end = NULL;

// Initialize type size to 0
#define INIT_TYPE_SIZE(name, ...) uint64_t VMStructs::TYPE_SIZE_NAME(name) = 0;
DECLARE_TYPES_DO(INIT_TYPE_SIZE)
#undef INIT_TYPE_SIZE

#define offset_value -1
#define address_value nullptr
// Do nothing macro
#define DO_NOTHING(...)
#define INIT_OFFSET_OR_ADDRESS(type, field, field_type, ...) \
    field_type VMStructs::_##type##_##field##_##field_type = field_type##_value;

DECLARE_TYPE_FILED_DO(DO_NOTHING, INIT_OFFSET_OR_ADDRESS, DO_NOTHING)

#undef INIT_OFFSET_OR_ADDRESS
#undef DO_NOTHING
#undef offset_value
#undef address_value

jfieldID VMStructs::_eetop;
jfieldID VMStructs::_tid;
jfieldID VMStructs::_klass = NULL;
int VMStructs::_tls_index = -1;
intptr_t VMStructs::_env_offset = -1;
void* VMStructs::_java_thread_vtbl[6];

VMStructs::LockFunc VMStructs::_lock_func;
VMStructs::LockFunc VMStructs::_unlock_func;

// Datadog-specific static variables
int VMStructs::_osthread_state_offset = -1;
int VMStructs::_flag_type_offset = -1;
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

bool initTypeSize(uint64_t& size, const char* type, uint64_t value, ...) {
    va_list args;
    va_start(args, value);
    const char* match_type = nullptr;
    bool found = false;
    while ((match_type = va_arg(args, const char*)) != nullptr) { 
        if (strcmp(type, match_type) == 0) {
            size = value;
            found = true;
            break;
        }
    } 
 
    va_end(args);
    return found;
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
    uintptr_t address_offset = readSymbol("gHotSpotVMStructEntryAddressOffset");

    auto read_offset = [&]() -> int {
        return *(int*)(entry + offset_offset);
    };

    auto read_address = [&]() -> const void* {
        return *(const void**)(entry + address_offset);
    };

    if (entry != 0 && stride != 0) {
        for (;; entry += stride) {
            const char* type_name = *(const char**)(entry + type_offset);
            const char* field_name = *(const char**)(entry + field_offset);
            if (type_name == NULL || field_name == NULL) {
                break;
            }
#define MATCH_TYPE_NAMES(type, ...) \
     if (matchAny(type_name, (const char*[]){ #__VA_ARGS__, nullptr})) {
#define READ_FIELD_VALUE(type, field, field_type, ...) \
        if (matchAny(field_name, (const char*[]){ #__VA_ARGS__, nullptr})) {   \
            _##type##_##field##_##field_type = read_##field_type();     \
        }
#define END_TYPE() }
            
        DECLARE_TYPE_FILED_DO(MATCH_TYPE_NAMES, READ_FIELD_VALUE, END_TYPE)
#undef MATCH_TYPE_NAMES
#undef READ_FIELD_VALUE
#undef END_TYPE
        }
    }
}

void VMStructs::initOffsets() {
    uintptr_t entry = readSymbol("gHotSpotVMStructs");
    uintptr_t stride = readSymbol("gHotSpotVMStructEntryArrayStride");
    uintptr_t type_offset = readSymbol("gHotSpotVMStructEntryTypeNameOffset");
    uintptr_t field_offset = readSymbol("gHotSpotVMStructEntryFieldNameOffset");
    uintptr_t offset_offset = readSymbol("gHotSpotVMStructEntryOffsetOffset");
    uintptr_t address_offset = readSymbol("gHotSpotVMStructEntryAddressOffset");

    if (entry != 0 && stride != 0) {
        for (;; entry += stride) {
            const char* type = *(const char**)(entry + type_offset);
            const char* field = *(const char**)(entry + field_offset);
            if (type == NULL || field == NULL) {
                break;
            }

            if (strcmp(type, "Klass") == 0) {
                if (strcmp(field, "_name") == 0) {
                    _klass_name_offset = *(int*)(entry + offset_offset);
                }
            } else if (strcmp(type, "Symbol") == 0) {
                if (strcmp(field, "_length") == 0) {
                    _symbol_length_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_length_and_refcount") == 0) {
                    _symbol_length_and_refcount_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_body") == 0) {
                    _symbol_body_offset = *(int*)(entry + offset_offset);
                }
            } else if (strcmp(type, "oopDesc") == 0) {
                if (strcmp(field, "_metadata._klass") == 0) {
                    _oop_klass_offset = *(int*)(entry + offset_offset);
                }
            } else if (strcmp(type, "Universe") == 0 || strcmp(type, "CompressedKlassPointers") == 0) {
                if (strcmp(field, "_narrow_klass._base") == 0 || strcmp(field, "_base") == 0) {
                    _narrow_klass_base_addr = *(char***)(entry + address_offset);
                } else if (strcmp(field, "_narrow_klass._shift") == 0 || strcmp(field, "_shift") == 0) {
                    _narrow_klass_shift_addr = *(int**)(entry + address_offset);
                } else if (strcmp(field, "_collectedHeap") == 0) {
                    _collected_heap_addr = *(char***)(entry + address_offset);
                }
            } else if (strcmp(type, "MemRegion") == 0) {
                if (strcmp(field, "_start") == 0) {
                    _region_start_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_word_size") == 0) {
                    _region_size_offset = *(int*)(entry + offset_offset);
                }
            } else if (strcmp(type, "CompiledMethod") == 0 || strcmp(type, "nmethod") == 0) {
                if (strcmp(field, "_method") == 0) {
                    _nmethod_method_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_verified_entry_offset") == 0) {
                    _nmethod_entry_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_verified_entry_point") == 0) {
                    _nmethod_entry_offset = - *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_state") == 0) {
                    _nmethod_state_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_comp_level") == 0) {
                    _nmethod_level_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_metadata_offset") == 0) {
                    _nmethod_metadata_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_immutable_data") == 0) {
                    _nmethod_immutable_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_scopes_pcs_offset") == 0) {
                    _scopes_pcs_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_scopes_data_offset") == 0) {
                    _scopes_data_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_scopes_data_begin") == 0) {
                    _scopes_data_offset = - *(int*)(entry + offset_offset);
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
            } else if (strcmp(type, "Thread") == 0) {
                // Since JDK 25, _osthread field belongs to Thread rather than JavaThread
                if (strcmp(field, "_osthread") == 0) {
                    _thread_osthread_offset = *(int*)(entry + offset_offset);
                }
            } else if (strcmp(type, "JavaThread") == 0) {
                if (strcmp(field, "_osthread") == 0) {
                    _thread_osthread_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_anchor") == 0) {
                    _thread_anchor_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_thread_state") == 0) {
                    _thread_state_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_vframe_array_head") == 0) {
                    _thread_vframe_offset = *(int*)(entry + offset_offset);
                }
            } else if (strcmp(type, "ThreadShadow") == 0) {
                if (strcmp(field, "_exception_file") == 0) {
                    _thread_exception_offset = *(int*)(entry + offset_offset);
                }
            } else if (strcmp(type, "OSThread") == 0) {
                if (strcmp(field, "_thread_id") == 0) {
                    _osthread_id_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_state") == 0) {
                    _osthread_state_offset = *(int*)(entry + offset_offset);
                }
            } else if (strcmp(type, "CompilerThread") == 0) {
                if (strcmp(field, "_env") == 0) {
                    _comp_env_offset = *(int*)(entry + offset_offset);
                }
            } else if (strcmp(type, "ciEnv") == 0) {
                if (strcmp(field, "_task") == 0) {
                    _comp_task_offset = *(int*)(entry + offset_offset);
                }
            } else if (strcmp(type, "CompileTask") == 0) {
                if (strcmp(field, "_method") == 0) {
                    _comp_method_offset = *(int*)(entry + offset_offset);
                }
            } else if (strcmp(type, "JavaCallWrapper") == 0) {
                if (strcmp(field, "_anchor") == 0) {
                    _call_wrapper_anchor_offset = *(int*)(entry + offset_offset);
                }
            } else if (strcmp(type, "JavaFrameAnchor") == 0) {
                if (strcmp(field, "_last_Java_sp") == 0) {
                    _anchor_sp_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_last_Java_pc") == 0) {
                    _anchor_pc_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_last_Java_fp") == 0) {
                    _anchor_fp_offset = *(int*)(entry + offset_offset);
                }
            } else if (strcmp(type, "CodeBlob") == 0) {
                if (strcmp(field, "_size") == 0) {
                    _blob_size_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_frame_size") == 0) {
                    _frame_size_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_frame_complete_offset") == 0) {
                    _frame_complete_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_code_offset") == 0) {
                    _code_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_code_begin") == 0) {
                    _code_offset = - *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_data_offset") == 0) {
                    _data_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_mutable_data") == 0) {
                    _mutable_data_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "_relocation_size") == 0) {
                    _relocation_size_offset = *(int*)(entry + offset_offset);
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
            } else if (strcmp(type, "HeapBlock::Header") == 0) {
                if (strcmp(field, "_used") == 0) {
                    _heap_block_used_offset = *(int*)(entry + offset_offset);
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
            } else if (strcmp(type, "StubRoutines") == 0) {
                if (strcmp(field, "_call_stub_return_address") == 0) {
                    _call_stub_return_addr = *(const void***)(entry + address_offset);
                }
            } else if (strcmp(type, "GrowableArrayBase") == 0 || strcmp(type, "GenericGrowableArray") == 0) {
                if (strcmp(field, "_len") == 0) {
                    _array_len_offset = *(int*)(entry + offset_offset);
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
                } else if (strcmp(field, "_flags") == 0 || strcmp(field, "origin") == 0) {
                    _flag_origin_offset = *(int*)(entry + offset_offset);
                } else if (strcmp(field, "flags") == 0) {
                    _flags_addr = **(char***)(entry + address_offset);
                } else if (strcmp(field, "numFlags") == 0) {
                    _flag_count = **(int**)(entry + address_offset);
                } else if (strcmp(field, "_type") == 0 || strcmp(field, "type") == 0) {
                    _flag_type_offset = *(int *)(entry + offset_offset);
                }
            } else if (strcmp(type, "PcDesc") == 0) {
                // TODO
            }
        }
    }

    entry = readSymbol("gHotSpotVMTypes");
    stride = readSymbol("gHotSpotVMTypeEntryArrayStride");
    type_offset = readSymbol("gHotSpotVMTypeEntryTypeNameOffset");
    uintptr_t size_offset = readSymbol("gHotSpotVMTypeEntrySizeOffset");

    if (entry != 0 && stride != 0) {
        for (;; entry += stride) {
            const char* type = *(const char**)(entry + type_offset);
            if (type == NULL) {
                break;
            }

            uint64_t size = *(uint64_t*)(entry + size_offset);
           
 #define TYPE_SIZE_MATCH(name, ...) \
    if (initTypeSize(VMStructs::TYPE_SIZE_NAME(name), type, size, ##__VA_ARGS__)) continue;

           DECLARE_TYPES_DO(TYPE_SIZE_MATCH)

#undef TYPE_SIZE_MATCH   

        }
    }

    entry = readSymbol("gHotSpotVMLongConstants");
    stride = readSymbol("gHotSpotVMLongConstantEntryArrayStride");
    uintptr_t name_offset = readSymbol("gHotSpotVMLongConstantEntryNameOffset");
    uintptr_t value_offset = readSymbol("gHotSpotVMLongConstantEntryValueOffset");

    if (entry != 0 && stride != 0) {
        for (;; entry += stride) {
            const char* name = *(const char**)(entry + name_offset);
            if (name == NULL) {
                break;
            }

            if (strncmp(name, "markWord::", 10) == 0) {
                if (strcmp(name + 10, "klass_shift") == 0) {
                    _markword_klass_shift = *(long*)(entry + value_offset);
                } else if (strcmp(name + 10, "monitor_value") == 0) {
                    _markword_monitor_value = *(long*)(entry + value_offset);
                }
            }
        }
    }

    entry = readSymbol("gHotSpotVMIntConstants");
    stride = readSymbol("gHotSpotVMIntConstantEntryArrayStride");
    name_offset = readSymbol("gHotSpotVMIntConstantEntryNameOffset");
    value_offset = readSymbol("gHotSpotVMIntConstantEntryValueOffset");

    if (entry != 0 && stride != 0) {
        for (;; entry += stride) {
            const char* name = *(const char**)(entry + name_offset);
            if (name == NULL) {
                break;
            }

            if (strcmp(name, "frame::entry_frame_call_wrapper_offset") == 0) {
                _entry_frame_call_wrapper_offset = *(int*)(entry + value_offset) * sizeof(uintptr_t);
                break;  // remove it for reading more constants
            }
        }
    }
}

void VMStructs::resolveOffsets() {
    if (VM::isOpenJ9() || VM::isZing()) {
        return;
    }

    if (_klass_offset_addr != NULL) {
        _klass = (jfieldID)(uintptr_t)(*_klass_offset_addr << 2 | 2);
    }

    VMFlag* ccp = VMFlag::find("UseCompressedClassPointers");
    if (ccp != NULL && ccp->get() && _narrow_klass_base_addr != NULL && _narrow_klass_shift_addr != NULL) {
        _narrow_klass_base = *_narrow_klass_base_addr;
        _narrow_klass_shift = *_narrow_klass_shift_addr;
    }

    VMFlag* coh = VMFlag::find("UseCompactObjectHeaders");
    if (coh != NULL && coh->get()) {
        _compact_object_headers = true;
    }

    _has_class_names = _klass_name_offset >= 0
            && (_compact_object_headers ? (_markword_klass_shift >= 0 && _markword_monitor_value == MONITOR_BIT)
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
    _entry_frame_call_wrapper_offset = -64;
#elif defined(__arm__) || defined(__thumb__)
    _interpreter_frame_bcp_offset = VM::hotspot_version() >= 11 ? -8 : 0;
    _entry_frame_call_wrapper_offset = 0;
#endif

    // JDK-8292758 has slightly changed ScopeDesc encoding
    if (VM::hotspot_version() >= 20) {
        _unsigned5_base = 1;
    }

    if (_call_stub_return_addr != NULL) {
        _call_stub_return = *_call_stub_return_addr;
    }

    // Since JDK 23, _metadata_offset is relative to _data_offset. See metadata()
    if (_nmethod_immutable_offset < 0) {
        _data_offset = 0;
    }

    _has_stack_structs = _has_method_structs
            && _call_wrapper_anchor_offset >= 0
            && _entry_frame_call_wrapper_offset != -1
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
        char* code_heaps = *_code_heap_addr;
        unsigned int code_heap_count = *(unsigned int*)(code_heaps + _array_len_offset);
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
        for (int i = 0; i < _flag_count; i++) {
            VMFlag* f = VMFlag::cast(_flags_addr + i * VMFlag::type_size());
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
        for (int i = 0; i < _flag_count; i++) {
            VMFlag* f = VMFlag::cast(_flags_addr + i * VMFlag::type_size());
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
