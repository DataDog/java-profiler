/*
 * Copyright The async-profiler authors
 * Copyright 2025, 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_VMSTRUCTS_H
#define _HOTSPOT_VMSTRUCTS_H

#include <initializer_list>
#include <jni.h>
#include <jvmti.h>
#include <stdint.h>
#include <type_traits>
#include "codeCache.h"
#include "counters.h"
#include "jvmThread.h"
#include "safeAccess.h"
#include "threadState.h"
#include "vmEntry.h"

#define JMETHODID_NOT_WALKABLE  (jmethodID)((uintptr_t)-1)
inline bool isValidJMethodID(jmethodID method_id) {
  return method_id != JMETHODID_NOT_WALKABLE && method_id != nullptr;
}

class GCHeapSummary;
class HeapUsage;
class VMNMethod;


// During stack walking in the profiler's signal handler, GC or class unloading
// on another thread can free VMNMethod/VMMethod memory concurrently, making
// pointers stale between the readability check and the actual dereference.
// In release builds the setjmp/longjmp crash protection in walkVM catches the
// resulting SIGSEGV. In debug builds the assert(isReadable) fires first,
// sending SIGABRT which is uncatchable by crash protection.
// When crash protection is active the assert is redundant — any bad read will
// be caught by the SIGSEGV handler and recovered via longjmp — so we skip it.
//
// Defined at the bottom of this file after VMThread is declared so that the
// VMThread fallback path (isExceptionActive) is accessible without forward-
// declaring the full class.
inline bool crashProtectionActive();

template <typename T>
inline T* cast_to(const void* ptr);


template <typename T>
T* cast_or_null(const void* ptr) {
    assert(VM::isHotspot()); // This should only be used in HotSpot-specific code
    assert(T::type_size() > 0); // Ensure type size has been initialized
    if(ptr == nullptr || SafeAccess::isReadableRange(ptr, T::type_size())) {
        return reinterpret_cast<T*>(const_cast<void*>(ptr));
    } else {
        return nullptr;
    }
}

#define TYPE_SIZE_NAME(name)    _##name##_size

// MATCH_SYMBOLS macro expands into a string list, that is consumed by matchAny() method
#define MATCH_SYMBOLS(...)  std::initializer_list<const char*>{ __VA_ARGS__ }

/**
 * This macro defines a counterpart of a JVM class, e.g. VMKlass -> Klass.
 * By the convention, we prefix the class name with 'VM' to avoid namespace collision
 * with JVM inside a debug session. E.g.
 * gdb > p this
 * gdb > (VMKlass*)0x123456
 * gdb > p (Klass*)this
 * .... 
 *
 * The macro implicitly defines three static functions:
 *  - type_size()       Return class size defined in JVM.
 *  - cast()            It performs memory readability check before casts a void* pointer to this type.
 *                      It ensures the memory range [ptr, ptr + type_size()) is readable.
 *  - load_then_cast()  It loads a pointer from specified location, then does above cast.
 */
#define DECLARE(name) \
    class name : VMStructs { \
      public: \
        static uint64_t type_size() { return TYPE_SIZE_NAME(name); } \
        static name * cast(const void* ptr) { return cast_to<name>(ptr); } \
        static name * cast_or_null(const void* ptr) { return ::cast_or_null<name>(ptr); } \
        static name * cast_raw(const void* ptr) { return (name *)ptr; } \
        static name * load_then_cast(const void* ptr) {     \
            if (ptr == nullptr) return nullptr;             \
            return cast_or_null(*(const void**)ptr); }

#define DECLARE_END  };

/**
 * Defines a type and its matching symbols in vmStructs.
 * A type may match multiple names in different JVM versions.
 *  Macro expansion:
 *  - Declaration phase
 *   static uint64_t _TYPE_size;
 *   
 *   For example:
 *    f(VMClassLoaderData) -> static uint64_t _VMClassLoaderData_size;
 *
 *  - Initialization phase
 *    uint64_t VMStructs::_TYPE_size = 0;
 *
 *   For example:
 *    f(VMClassLoaderData) -> uint64_t VMStructs::_VMClassLoaderData_size = 0;
 * 
 * - Value population phase
 *   if (matchAny((char*)[]) { typeName, nullptr}) {
 *       _TYPE_size = size;
 *       continue;
 *   } 
 * 
 *  For example:
 *   f(VMClassLoaderData,    MATCH_SYMBOLS("ClassLoaderData")) ->
 *   if (matchAny((char*)[] {"ClassLoaderData", nullptr})) {
 *      _ClassLoaderData_size = size;
 *      continue;
 *    }
 * 
 * - Value verification phase
 *   assert(_TYPE_size > 0);
 * 
 *  For example:
 *  f(VMClassLoaderData,    MATCH_SYMBOLS("ClassLoaderData")) ->
 *  assert(_VMClassLoaderData_size > 0);
 */

#define DECLARE_TYPES_DO(f) \
    f(VMClassLoaderData,      MATCH_SYMBOLS("ClassLoaderData"))   \
    f(VMConstantPool,         MATCH_SYMBOLS("ConstantPool"))      \
    f(VMConstMethod,          MATCH_SYMBOLS("ConstMethod"))       \
    f(VMFlag,                 MATCH_SYMBOLS("JVMFlag", "Flag"))   \
    f(VMJavaFrameAnchor,      MATCH_SYMBOLS("JavaFrameAnchor"))   \
    f(VMKlass,                MATCH_SYMBOLS("Klass"))             \
    f(VMMethod,               MATCH_SYMBOLS("Method"))            \
    f(VMNMethod,              MATCH_SYMBOLS("nmethod"))           \
    f(VMSymbol,               MATCH_SYMBOLS("Symbol"))            \
    f(VMThread,               MATCH_SYMBOLS("Thread"))

// ContinuationEntry type. Only exported via gHotSpotVMTypes starting in
// JDK 27 (JDK-8378985); there is no mangled-symbol fallback for its size.
// On JDK <27 type_size() stays 0 and any code that needs the layout
// (contEntry(), parent()) bails out.
#define DECLARE_V27_TYPES_DO(f) \
    f(VMContinuationEntry,    MATCH_SYMBOLS("ContinuationEntry"))

// Oop-map metadata types. InstanceKlass and _nonstatic_oop_map_size are both
// real gHotSpotVMTypes/gHotSpotVMStructs entries and resolve normally. The
// per-block struct is a different story: empirically, "OopMapBlock" is not a
// gHotSpotVMTypes entry on any JDK build checked (Temurin/Microsoft/Liberica,
// versions 8 through 26) - it appears HotSpot's SA export table has never
// carried this type, presumably because its layout (two 4-byte ints) is
// treated as ABI-stable rather than SA-introspectable. VMOopMapBlock's fixed
// layout below is therefore a documented, deliberate exception to reading
// struct layout through VMStructs - see its own comment for the rationale
// and the fail-closed gate that still applies if this assumption ever breaks.
#define DECLARE_OOPMAP_TYPES_DO(f) \
    f(VMInstanceKlass,        MATCH_SYMBOLS("InstanceKlass"))

// Fields for virtual-thread / continuation support, all added to
// gHotSpotVMStructs / gHotSpotVMTypes in JDK 27 (JDK-8378985):
//   - JavaThread::_cont_entry            -> _cont_entry_offset
//   - StubRoutines::_cont_returnBarrier  -> _cont_return_barrier_addr
//   - ContinuationEntry::_return_pc      -> _cont_entry_return_pc_addr
//   - ContinuationEntry::_parent         -> _cont_entry_parent_offset
// On JDK <27 these stay at their default (-1 / nullptr).  The two stub
// *addresses* (_cont_return_barrier, _cont_entry_return_pc) are separately
// resolved via Itanium-mangled symbol lookup in resolveOffsets() so the
// cont_returnBarrier / cont_entry_return_pc frame-boundary checks still work
// on JDK 21-26; the _offset fields have no such fallback.  All entries are
// intentionally excluded from verify_offsets() so a missing entry causes
// graceful degradation rather than SIGABRT.
#define DECLARE_V27_TYPE_FIELD_DO(type_begin, field, field_with_version, type_end) \
    type_begin(VMJavaThread, MATCH_SYMBOLS("JavaThread", "Thread"))                \
        field_with_version(_cont_entry_offset, offset, 27, MAX_VERSION, MATCH_SYMBOLS("_cont_entry")) \
    type_end()                                                                     \
    type_begin(VMStubRoutine, MATCH_SYMBOLS("StubRoutines"))                      \
        field_with_version(_cont_return_barrier_addr, address, 27, MAX_VERSION, MATCH_SYMBOLS("_cont_returnBarrier")) \
    type_end()                                                                     \
    type_begin(VMContinuationEntry, MATCH_SYMBOLS("ContinuationEntry"))           \
        field_with_version(_cont_entry_return_pc_addr, address, 27, MAX_VERSION, MATCH_SYMBOLS("_return_pc")) \
        field_with_version(_cont_entry_parent_offset,  offset,  27, MAX_VERSION, MATCH_SYMBOLS("_parent"))    \
    type_end()

// No fields to resolve for OopMapBlock via VMStructs - see
// DECLARE_OOPMAP_TYPES_DO's comment above for why. This macro is now empty
// but kept (rather than removed) so the DO-list convention stays uniform
// with DECLARE_V27_TYPE_FIELD_DO/DECLARE_TYPE_FIELD_DO if a real exported
// field is ever added here.
//
// Note: this must stay empty, or add fields under a *different*
// MATCH_SYMBOLS() type-name set than any type_begin() already declared in
// DECLARE_TYPE_FIELD_DO/DECLARE_V27_TYPE_FIELD_DO. All three DO-lists expand
// into the SAME resolveOffsets() scan loop (see vmStructs.cpp), and
// type_end()/END_TYPE() expands to an unconditional `continue` - so a second
// type_begin(SameType, <same match set>) block anywhere later in that chain
// is unreachable dead code for every entry the earlier block already
// consumed (this exact duplication bug was caught and fixed once already,
// for VMKlass/InstanceKlass, during this feature's implementation).
#define DECLARE_OOPMAP_TYPE_FIELD_DO(type_begin, field, field_with_version, type_end)

/**
 * Following macros define field offsets, addresses or values of JVM classes that are exported by
 * vmStructs.
 *  - type_begin()        Start a definition of a type. The type name is not used at this moment, but
 *                        improves readability.
 *  - field()             Define a field of a class, can be either an offset, an address or a value
 *  - field_with_version  A field that only exits in the specified JVM version range
 *  - type_end()          End of a type definition
*/

typedef int offset;
typedef void* address;

#define MIN_VERSION 8

// JDK 128 :-)
#define MAX_VERSION 128

#define DECLARE_TYPE_FIELD_DO(type_begin, field, field_with_version, type_end)                                      \
    type_begin(VMMemRegion, MATCH_SYMBOLS("MemRegion"))                                                             \
        field(_region_start_offset, offset, MATCH_SYMBOLS("_start"))                                                \
        field(_region_size_offset, offset, MATCH_SYMBOLS("_word_size"))                                             \
    type_end()                                                                                                      \
    type_begin(VMNMethod, MATCH_SYMBOLS("CompiledMethod", "nmethod"))                                               \
        field(_nmethod_method_offset, offset,MATCH_SYMBOLS("_method"))                                              \
        field_with_version(_nmethod_entry_offset, offset, 23, MAX_VERSION, MATCH_SYMBOLS("_verified_entry_offset")) \
        field_with_version(_nmethod_entry_address, offset, 8, 22, MATCH_SYMBOLS("_verified_entry_point"))           \
        field(_nmethod_state_offset, offset, MATCH_SYMBOLS("_state"))                                               \
        field(_nmethod_level_offset, offset, MATCH_SYMBOLS("_comp_level"))                                          \
        field_with_version(_nmethod_metadata_offset, offset, MIN_VERSION, 24, MATCH_SYMBOLS("_metadata_offset"))    \
        field_with_version(_nmethod_immutable_offset, offset, 23, MAX_VERSION, MATCH_SYMBOLS("_immutable_data"))    \
        field(_scopes_pcs_offset, offset, MATCH_SYMBOLS("_scopes_pcs_offset"))                                      \
        field_with_version(_scopes_data_offset, offset, 23, MAX_VERSION, MATCH_SYMBOLS("_scopes_data_offset"))      \
        field_with_version(_scopes_data_address, offset, 9, 22, MATCH_SYMBOLS("_scopes_data_begin"))                \
    type_end()                                                                                                      \
    type_begin(VMMethod, MATCH_SYMBOLS("Method"))                                                                   \
        field(_method_constmethod_offset, offset, MATCH_SYMBOLS("_constMethod"))                                    \
        field(_method_code_offset, offset, MATCH_SYMBOLS("_code"))                                                  \
    type_end()                                                                                                      \
    type_begin(VMConstMethod, MATCH_SYMBOLS("ConstMethod"))                                                         \
        field(_constmethod_constants_offset, offset, MATCH_SYMBOLS("_constants"))                                   \
        field(_constmethod_idnum_offset, offset, MATCH_SYMBOLS("_method_idnum"))                                    \
        field(_constmethod_name_index_offset, offset, MATCH_SYMBOLS("_name_index"))                                 \
        field(_constmethod_sig_index_offset, offset, MATCH_SYMBOLS("_signature_index"))                             \
    type_end()                                                                                                      \
    type_begin(VMConstantPool, MATCH_SYMBOLS("ConstantPool"))                                                       \
        field(_pool_holder_offset, offset, MATCH_SYMBOLS("_pool_holder"))                                           \
    type_end()                                                                                                      \
    type_begin(VMKlass, MATCH_SYMBOLS("Klass", "InstanceKlass"))                                                    \
        field(_klass_name_offset, offset, MATCH_SYMBOLS("_name"))                                                   \
        field(_class_loader_data_offset, offset, MATCH_SYMBOLS("_class_loader_data"))                               \
        field(_methods_offset, offset, MATCH_SYMBOLS("_methods"))                                                   \
        field(_jmethod_ids_offset, offset, MATCH_SYMBOLS("_methods_jmethod_ids"))                                   \
        field(_layout_helper_offset, offset, MATCH_SYMBOLS("_layout_helper"))                                       \
        field(_nonstatic_oop_map_size_offset, offset, MATCH_SYMBOLS("_nonstatic_oop_map_size"))                     \
        field(_vtable_len_offset, offset, MATCH_SYMBOLS("_vtable_len"))                                             \
        field(_itable_len_offset, offset, MATCH_SYMBOLS("_itable_len"))                                             \
    type_end()                                                                                                      \
    type_begin(VMClassLoaderData, MATCH_SYMBOLS("ClassLoaderData"))                                                 \
        field(_class_loader_data_next_offset, offset, MATCH_SYMBOLS("_next"))                                       \
    type_end()                                                                                                      \
    type_begin(VMJavaClass, MATCH_SYMBOLS("java_lang_Class"))                                                       \
        field(_klass_offset_addr, address, MATCH_SYMBOLS("_klass_offset"))                                          \
    type_end()                                                                                                      \
    type_begin(VMSymbol, MATCH_SYMBOLS("Symbol"))                                                                   \
        field(_symbol_length_offset, offset, MATCH_SYMBOLS("_length"))                                              \
        field(_symbol_body_offset, offset, MATCH_SYMBOLS("_body"))                                                  \
    type_end()                                                                                                      \
    type_begin(VMJavaThread, MATCH_SYMBOLS("JavaThread", "Thread"))                                                 \
        field(_thread_osthread_offset, offset, MATCH_SYMBOLS("_osthread"))                                          \
        field(_thread_anchor_offset, offset, MATCH_SYMBOLS("_anchor"))                                              \
        field(_thread_state_offset, offset, MATCH_SYMBOLS("_thread_state"))                                         \
        field(_thread_vframe_offset, offset, MATCH_SYMBOLS("_vframe_array_head"))                                   \
    type_end()                                                                                                      \
    type_begin(VMOSThread, MATCH_SYMBOLS("OSThread"))                                                               \
        field(_osthread_id_offset, offset, MATCH_SYMBOLS("_thread_id"))                                             \
        field_with_version(_osthread_state_offset, offset, 10, MAX_VERSION, MATCH_SYMBOLS("_state"))                \
    type_end()                                                                                                      \
    type_begin(VMThreadShadow, MATCH_SYMBOLS("ThreadShadow"))                                                         \
        field(_thread_exception_offset, offset, MATCH_SYMBOLS("_exception_file"))                                   \
    type_end()                                                                                                      \
    type_begin(VMCompilerThread, MATCH_SYMBOLS("CompilerThread"))                                                   \
        field(_comp_env_offset, offset, MATCH_SYMBOLS("_env"))                                                      \
    type_end()                                                                                                      \
    type_begin(VMciEnv, MATCH_SYMBOLS("ciEnv"))                                                                     \
        field(_comp_task_offset, offset, MATCH_SYMBOLS("_task"))                                                    \
    type_end()                                                                                                      \
    type_begin(VMCompileTask, MATCH_SYMBOLS("CompileTask"))                                                         \
        field(_comp_method_offset, offset, MATCH_SYMBOLS("_method"))                                                \
    type_end()                                                                                                      \
    type_begin(VMJavaCallWrapper, MATCH_SYMBOLS("JavaCallWrapper"))                                                 \
        field(_call_wrapper_anchor_offset, offset, MATCH_SYMBOLS("_anchor"))                                        \
    type_end()                                                                                                      \
    type_begin(VMJavaFrameAnchor, MATCH_SYMBOLS("JavaFrameAnchor"))                                                 \
        field(_anchor_sp_offset, offset, MATCH_SYMBOLS("_last_Java_sp"))                                            \
        field(_anchor_pc_offset, offset, MATCH_SYMBOLS("_last_Java_pc"))                                            \
        field(_anchor_fp_offset, offset, MATCH_SYMBOLS("_last_Java_fp"))                                            \
    type_end()                                                                                                      \
    type_begin(VMCodeBlob, MATCH_SYMBOLS("CodeBlob"))                                                               \
        field(_blob_size_offset, offset, MATCH_SYMBOLS("_size"))                                                    \
        field(_frame_size_offset, offset, MATCH_SYMBOLS("_frame_size"))                                             \
        field(_frame_complete_offset, offset, MATCH_SYMBOLS("_frame_complete_offset"))                              \
        field_with_version(_code_offset, offset, 23, MAX_VERSION, MATCH_SYMBOLS("_code_offset"))                    \
        field_with_version(_code_address, offset, 9, 22, MATCH_SYMBOLS("_code_begin"))                              \
        field(_data_offset, offset, MATCH_SYMBOLS("_data_offset"))                                                  \
        field_with_version(_mutable_data_offset, offset, 25, MAX_VERSION, MATCH_SYMBOLS("_mutable_data"))           \
        field_with_version(_relocation_size_offset, offset, 23, MAX_VERSION, MATCH_SYMBOLS("_relocation_size"))     \
        field(_nmethod_name_offset, offset, MATCH_SYMBOLS("_name"))                                                 \
    type_end()                                                                                                      \
    type_begin(VMCodeCache, MATCH_SYMBOLS("CodeCache"))                                                             \
        field(_code_heap_addr, address, MATCH_SYMBOLS("_heap", "_heaps"))                                           \
        field_with_version(_code_heap_low_addr, address, 9, MAX_VERSION, MATCH_SYMBOLS("_low_bound"))               \
        field_with_version(_code_heap_high_addr, address, 9, MAX_VERSION, MATCH_SYMBOLS("_high_bound"))             \
    type_end()                                                                                                      \
    type_begin(VMCodeHeap, MATCH_SYMBOLS("CodeHeap"))                                                               \
        field(_code_heap_memory_offset, offset, MATCH_SYMBOLS("_memory"))                                           \
        field(_code_heap_segmap_offset, offset, MATCH_SYMBOLS("_segmap"))                                           \
        field(_code_heap_segment_shift, offset, MATCH_SYMBOLS("_log2_segment_size"))                                \
    type_end()                                                                                                      \
    type_begin(VMHeapBlock, MATCH_SYMBOLS("HeapBlock::Header"))                                                     \
        field(_heap_block_used_offset, offset, MATCH_SYMBOLS("_used"))                                              \
    type_end()                                                                                                      \
    type_begin(VMVirtualSpace, MATCH_SYMBOLS("VirtualSpace"))                                                       \
        field(_vs_low_bound_offset, offset, MATCH_SYMBOLS("_low_boundary"))                                         \
        field(_vs_high_bound_offset, offset, MATCH_SYMBOLS("_high_boundary"))                                       \
        field(_vs_low_offset, offset, MATCH_SYMBOLS("_low"))                                                        \
        field(_vs_high_offset, offset, MATCH_SYMBOLS("_high"))                                                      \
    type_end()                                                                                                      \
    type_begin(VMStubRoutine, MATCH_SYMBOLS("StubRoutines"))                                                        \
        field(_call_stub_return_addr, address, MATCH_SYMBOLS("_call_stub_return_address"))                         \
    type_end()                                                                                                      \
    type_begin(VMGrowableArray, MATCH_SYMBOLS("GrowableArrayBase", "GenericGrowableArray"))                         \
        field(_array_len_offset, offset, MATCH_SYMBOLS("_len"))                                                     \
    type_end()                                                                                                      \
    type_begin(VMGrowableArrayInt, MATCH_SYMBOLS("GrowableArray<int>"))                                             \
        field(_array_data_offset, offset, MATCH_SYMBOLS("_data"))                                                   \
    type_end()                                                                                                      \
    type_begin(VMFlag, MATCH_SYMBOLS("JVMFlag", "Flag"))                                                            \
        field(_flag_name_offset, offset, MATCH_SYMBOLS("_name", "name"))                                            \
        field(_flag_addr_offset, offset, MATCH_SYMBOLS("_addr", "addr"))                                            \
        field(_flag_origin_offset, offset, MATCH_SYMBOLS("_flags", "origin"))                                       \
        field(_flags_addr, address, MATCH_SYMBOLS("flags"))                                                         \
        field(_flag_count, address, MATCH_SYMBOLS("numFlags"))                                                      \
        field(_flag_type_offset, offset, MATCH_SYMBOLS("_type", "type"))                                            \
    type_end()                                                                                                      \
    type_begin(VMOop, MATCH_SYMBOLS("oopDesc"))                                                                     \
        field(_oop_klass_offset, offset, MATCH_SYMBOLS("_metadata._klass", "_compressed_klass"))                    \
    type_end()                                                                                                      \
    type_begin(VMUniverse, MATCH_SYMBOLS("Universe", "CompressedKlassPointers"))                                    \
        field(_narrow_klass_base_addr, address, MATCH_SYMBOLS("_narrow_klass._base", "_base"))                      \
        field(_narrow_klass_shift_addr, address, MATCH_SYMBOLS("_narrow_klass._shift", "_shift"))                   \
        field(_collected_heap_addr, address, MATCH_SYMBOLS("_collectedHeap"))                                       \
    type_end()                                                                                                      \
    /* CompressedOops::_narrow_oop is exported under its own type name, distinct from     */                        \
    /* CompressedKlassPointers (narrow klass) above - HotSpot keeps compressed-oop and     */                       \
    /* compressed-klass base/shift state in two separate AllStatic classes. JDK-8329306    */                       \
    /* (JDK 24+) flattened the nested NarrowOopStruct fields, so the exported field names  */                       \
    /* dropped the "_narrow_oop." prefix - match both spellings.                           */                       \
    type_begin(VMCompressedOops, MATCH_SYMBOLS("CompressedOops"))                                                   \
        field(_narrow_oop_base_addr, address, MATCH_SYMBOLS("_narrow_oop._base", "_base"))                          \
        field(_narrow_oop_shift_addr, address, MATCH_SYMBOLS("_narrow_oop._shift", "_shift"))                       \
    type_end()

/**
 * The following macros declare JVM constants that are exported by vmStructs
 *   - constant defines a constant of a class
 */

#define DECLARE_INT_CONSTANTS_DO(constant, constant_with_version) \
    constant(frame, entry_frame_call_wrapper_offset)

// Klass::layout_helper's tag/header-size/element-size encoding. Kept out of
// DECLARE_INT_CONSTANTS_DO/verify_offsets()'s hard assertion (same treatment
// as DECLARE_V27_TYPE_FIELD_DO) rather than assumed always-present -
// VMKlass::arrayLayoutAvailable() is the real fail-closed gate callers must
// check. _lh_header_size_mask and _lh_element_type_mask are deliberately
// NOT in this list: confirmed (via `strings` on real Temurin/Microsoft/
// Liberica libjvm.so builds, JDK 8 through 26) that gHotSpotVMIntConstants
// never carries either, even though the shift/tag constants right next to
// them in klass.hpp always do. Both masks are `right_n_bits(BitsPerByte)` =
// 0xFF by construction in every HotSpot version - same "trivial derived
// constant, not worth SA-exporting" treatment as OopMapBlock's layout (see
// its own comment) - so _lh_header_size_mask is hardcoded below rather than
// resolved. _lh_element_type_mask has no current caller in this file.
#define DECLARE_ARRAYLAYOUT_INT_CONSTANTS_DO(constant, constant_with_version) \
    constant(Klass, _lh_array_tag_shift)                          \
    constant(Klass, _lh_array_tag_type_value)                     \
    constant(Klass, _lh_array_tag_obj_value)                      \
    constant(Klass, _lh_header_size_shift)                        \
    constant(Klass, _lh_log2_element_size_shift)                  \
    constant(Klass, _lh_log2_element_size_mask)                   \
    constant(Klass, _lh_element_type_shift)

// Not resolved via VMStructs - see DECLARE_ARRAYLAYOUT_INT_CONSTANTS_DO's
// comment above.
static const int _Klass__lh_header_size_mask = 0xFF;

#define DECLARE_LONG_CONSTANTS_DO(constant, constant_with_version)  \
    constant_with_version(markWord, klass_shift, 24, MAX_VERSION)   \
    constant_with_version(markWord, monitor_value, 24, MAX_VERSION)

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
    // Collector choice can't change after JVM startup, so this is resolved
    // once in resolveOffsets() rather than re-checked per pass.
    static bool _is_g1_active;

    static int _narrow_klass_shift;
    static char* _code_heap[3];
    static const void* _code_heap_low;
    static const void* _code_heap_high;
    static char* _narrow_klass_base;
    static char* _narrow_oop_base;
    static int _narrow_oop_shift;
    static int _interpreter_frame_bcp_offset;
    static unsigned char _unsigned5_base;
    static const void* _call_stub_return;
    static const void* _cont_return_barrier;
    static const void* _cont_entry_return_pc;
    static VMNMethod*  _enter_special_nm;
    static const void* _interpreter_start;
    static VMNMethod* _interpreter_nm;
    static const void* _interpreted_frame_valid_start;
    static const void* _interpreted_frame_valid_end;


// Declare type size variables
 #define DECLARE_TYPE_SIZE_VAR(name, names) \
    static uint64_t TYPE_SIZE_NAME(name);

    DECLARE_TYPES_DO(DECLARE_TYPE_SIZE_VAR)
    DECLARE_V27_TYPES_DO(DECLARE_TYPE_SIZE_VAR)
    DECLARE_OOPMAP_TYPES_DO(DECLARE_TYPE_SIZE_VAR)
#undef DECLARE_TYPE_SIZE_VAR

// Declare vmStructs' field offsets and addresses

// Do nothing macro
#define DO_NOTHING(...)
#define DECLARE_TYPE_FIELD(var, field_type, names) \
    static field_type var;
#define DECLARE_TYPE_FIELD_WITH_VERSION(var, field_type, min_version, max_version, names) \
    static field_type var;

    DECLARE_TYPE_FIELD_DO(DO_NOTHING, DECLARE_TYPE_FIELD, DECLARE_TYPE_FIELD_WITH_VERSION, DO_NOTHING)
    DECLARE_V27_TYPE_FIELD_DO(DO_NOTHING, DECLARE_TYPE_FIELD, DECLARE_TYPE_FIELD_WITH_VERSION, DO_NOTHING)
    DECLARE_OOPMAP_TYPE_FIELD_DO(DO_NOTHING, DECLARE_TYPE_FIELD, DECLARE_TYPE_FIELD_WITH_VERSION, DO_NOTHING)
#undef DECLARE_TYPE_FIELD
#undef DECLARE_TYPE_FIELD_WITH_VERSION
#undef DO_NOTHING

// Declare int constant variables
#define DECLARE_INT_CONSTANT_VAR(type, field, ...) \
    static int _##type##_##field;
    DECLARE_INT_CONSTANTS_DO(DECLARE_INT_CONSTANT_VAR, DECLARE_INT_CONSTANT_VAR)
    DECLARE_ARRAYLAYOUT_INT_CONSTANTS_DO(DECLARE_INT_CONSTANT_VAR, DECLARE_INT_CONSTANT_VAR)
#undef DECLARE_INT_CONSTANT_VAR

// Declare long constant variables
#define DECLARE_LONG_CONSTANT_VAR(type, field, ...) \
    static long _##type##_##field;
    DECLARE_LONG_CONSTANTS_DO(DECLARE_LONG_CONSTANT_VAR, DECLARE_LONG_CONSTANT_VAR)
#undef DECLARE_LONG_CONSTANT_VAR


    static jfieldID _eetop;
    static jfieldID _klass;
    static intptr_t _env_offset;
    static void* _java_thread_vtbl[6];

    typedef void (*LockFunc)(void*);
    static LockFunc _lock_func;
    static LockFunc _unlock_func;

    // Datadog-specific extensions
    static CodeCache _unsafe_to_walk;
    typedef HeapUsage (*HeapUsageFunc)(const void *);
    static HeapUsageFunc _heap_usage_func;
    typedef void *(*MemoryUsageFunc)(void *, void *, bool);
    static MemoryUsageFunc _memory_usage_func;
    typedef GCHeapSummary (*GCHeapSummaryFunc)(void *);
    static GCHeapSummaryFunc _gc_heap_summary_func;
    static IsValidMethodFunc _is_valid_method_func;

    static uintptr_t readSymbol(const char* symbol_name);

    // Read VM information from vmStructs
    static void init_type_sizes();
    static void init_offsets_and_addresses();
    static void init_constants();
    static void initOffsets();

#ifdef DEBUG
    static void verify_offsets();
#endif

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
        assert(crashProtectionActive() || SafeAccess::isReadable(ptr));
        return ptr;
    }

    const char* at(int offset) const {
        const char* ptr = (const char*)this + offset;
        assert(crashProtectionActive() || SafeAccess::isReadable(ptr));
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

    static bool isG1Active() {
        return _is_g1_active;
    }

    // Fail-closed gate: false unless UseCompressedOops was on and both the
    // narrow-oop base and shift addresses resolved during resolveOffsets().
    static bool isCompressedOopsEnabled() {
        return _narrow_oop_shift >= 0;
    }

    // Compressed-oops decode/encode, mirroring VMKlass::fromOop()'s narrow
    // *klass* pointer handling. Callers must check isCompressedOopsEnabled()
    // first - a narrow oop is meaningless (and _narrow_oop_base is nullptr)
    // when compressed oops are off.
    static uintptr_t decodeOop(uint32_t narrow_oop) {
        assert(isCompressedOopsEnabled());
        return narrow_oop == 0 ? 0 : (uintptr_t)_narrow_oop_base + ((uintptr_t)narrow_oop << _narrow_oop_shift);
    }

    static uint32_t encodeOop(uintptr_t oop) {
        assert(isCompressedOopsEnabled());
        return oop == 0 ? 0 : (uint32_t)(((uintptr_t)oop - (uintptr_t)_narrow_oop_base) >> _narrow_oop_shift);
    }

    static bool isInterpretedFrameValidFunc(const void* pc) {
        return pc >= _interpreted_frame_valid_start && pc < _interpreted_frame_valid_end;
    }

    static bool isContReturnBarrier(const void* pc) {
        return _cont_return_barrier != nullptr && pc == _cont_return_barrier;
    }

    // True when the bottom VT frame's return PC is cont_entry_return_pc, meaning all
    // VT frames are thawed (CPU-bound VT that never yielded).
    // Available on JDK 21+ via vmStructs or symbol fallback.
    static bool isContEntryReturnPc(const void* pc) {
        return _cont_entry_return_pc != nullptr && pc == _cont_entry_return_pc;
    }

    static VMNMethod* enterSpecialNMethod() {
        return _enter_special_nm;
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
    unsigned short length() {
        assert(_symbol_length_offset >= 0);
        return *(unsigned short*) at(_symbol_length_offset);
    }

    const char* body() {
        assert(_symbol_body_offset >= 0);
        return at(_symbol_body_offset);
    }

    // Public accessors for safefetch-based dump-time resolution (no `this`
    // deref): used to compute the address of the length/body fields without
    // touching the Symbol's memory, so callers can probe with SafeAccess.
    static int lengthOffset() { return _symbol_length_offset; }
    static int bodyOffset()   { return _symbol_body_offset; }
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

// Purely a size anchor: InstanceKlass's own gHotSpotVMTypes entry, distinct
// from VMKlass::type_size() (which resolves to the base Klass size via its
// "Klass" MATCH_SYMBOLS entry). Needed because OopMapBlocks are laid out as
// a variable-length tail starting immediately after the full InstanceKlass
// object, not after the base Klass slice of it.
DECLARE(VMInstanceKlass)
DECLARE_END

// OopMapBlock's layout is NOT resolved via VMStructs (see
// DECLARE_OOPMAP_TYPES_DO's comment) - it has no gHotSpotVMTypes entry on
// any JDK build checked. HotSpot's own class (share/oops/klass.hpp) has
// been `{ int _offset; uint _count; }`, 8 bytes, no padding, since generic
// OopMapBlocks were introduced (pre-JDK 8), and this is the layout SA's own
// Java-side InstanceKlass reader hardcodes too rather than resolving via the
// struct table - so this mirrors an existing precedent, not a new risk.
// This is empirically validated end-to-end (not just assumed) by
// FieldWalkerTestSeamsTest, which walks real object graphs and compares
// discovered fields against reflection - if this layout were ever wrong on
// some JDK, that test would fail rather than silently walk garbage.
class VMOopMapBlock : VMStructs {
  public:
    static uint64_t type_size() { return 8; }
    static VMOopMapBlock* cast(const void* ptr) { return cast_to<VMOopMapBlock>(ptr); }

    int fieldOffset() {
        return *(int*) at(0);
    }

    int fieldCount() {
        return *(int*) at(4);
    }
};

DECLARE(VMKlass)
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
                    // TOCTOU: MonitorDeflationThread may free the ObjectMonitor between
                    // reading the mark word and dereferencing the monitor pointer. Use
                    // safeFetch64 so a concurrent deflation/free does not crash here.
                    // Two reads with different error values disambiguate a genuine fault
                    // from a real header word that happens to equal one sentinel value
                    // (mirrors SafeAccess::isReadable()'s double-read trick).
                    int64_t* monitor_addr = (int64_t*)(mark ^ MONITOR_BIT);
                    uintptr_t tmp = (uintptr_t)SafeAccess::safeFetch64(monitor_addr, 1);
                    if (tmp != 1) {
                        mark = tmp;
                    } else {
                        tmp = (uintptr_t)SafeAccess::safeFetch64(monitor_addr, 2);
                        if (tmp != 2) {
                            mark = tmp;
                        } else {
                            return nullptr;
                        }
                    }
                }
                narrow_klass = mark >> _markWord_klass_shift;
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

    // Fail-closed gate for the oop-map accessors below: false if any real
    // MATCH_SYMBOLS lookup they depend on came back unresolved.
    // VMOopMapBlock::type_size() is a compile-time constant (see its own
    // comment), not a resolved lookup, so it's not part of this gate.
    static bool oopMapAvailable() {
        return _nonstatic_oop_map_size_offset >= 0
            && _vtable_len_offset >= 0
            && _itable_len_offset >= 0
            && VMInstanceKlass::type_size() > 0;
    }

    // Number of OopMapBlocks in the variable-length tail. Only meaningful
    // for InstanceKlass, not the base Klass (arrays/interfaces have no
    // nonstatic oop maps); caller is expected to already know `this` is an
    // InstanceKlass, same precondition VMKlass::fromOop() callers already
    // rely on for other InstanceKlass-only fields on this same class.
    // Same sanity-bound rationale as kMaxSaneVTableLength above: no real
    // class has anywhere near this many oop-map blocks (each covers a run of
    // contiguous oop fields, not one field each).
    static constexpr int kMaxSaneOopMapCount = 1 << 16;

    int oopMapCount() {
        assert(oopMapAvailable());
        int count = *(int*) at(_nonstatic_oop_map_size_offset);
        assert(count >= 0 && count < kMaxSaneOopMapCount &&
               "_nonstatic_oop_map_size read a value outside any sane range - "
               "VMStructs field resolution is likely wrong for this JDK");
        return count;
    }

    // Sanity bound, not a real limit: HotSpot itself has nowhere near this
    // many vtable/itable slots for any real class. Catches a wrong field
    // resolved to the wrong offset (e.g. a future JDK renumbering Klass's
    // fields) reading a garbage int, loudly, instead of silently feeding a
    // huge bogus length into oopMapBlockAt()'s tail arithmetic below.
    static constexpr int kMaxSaneVTableLength = 1 << 16;

    int vtableLength() {
        assert(_vtable_len_offset >= 0);
        int len = *(int*) at(_vtable_len_offset);
        assert(len >= 0 && len < kMaxSaneVTableLength &&
               "_vtable_len read a value outside any sane range - "
               "VMStructs field resolution is likely wrong for this JDK");
        return len;
    }

    int itableLength() {
        assert(_itable_len_offset >= 0);
        int len = *(int*) at(_itable_len_offset);
        assert(len >= 0 && len < kMaxSaneVTableLength &&
               "_itable_len read a value outside any sane range - "
               "VMStructs field resolution is likely wrong for this JDK");
        return len;
    }

    // OopMapBlocks do NOT start immediately after sizeof(InstanceKlass) - per
    // HotSpot's own layout comment in instanceKlass.hpp ("InstanceKlass
    // embedded field layout (after declared fields): [EMBEDDED Java vtable]
    // [EMBEDDED nonstatic oop-map blocks]") and instanceKlass.inline.hpp's
    // start_of_itable()/start_of_nonstatic_oop_maps(), the real tail is
    // sizeof(InstanceKlass) bytes, THEN the vtable (vtable_len words), THEN
    // the itable (itable_len words), THEN the oop-map blocks. Skipping the
    // vtable/itable was an earlier, incorrect assumption that read garbage
    // as an OopMapBlock and crashed on any real object with oop fields
    // (caught by FieldWalkerTestSeamsTest, which is why that suite exists).
    VMOopMapBlock* oopMapBlockAt(int i) {
        assert(oopMapAvailable());
        const char* tail = (const char*) this + VMInstanceKlass::type_size()
            + (uint64_t)(vtableLength() + itableLength()) * sizeof(void*);
        return VMOopMapBlock::cast(tail + (uint64_t) i * VMOopMapBlock::type_size());
    }

    // Fail-closed gate for the layout_helper accessors below. Note:
    // _Klass__lh_array_tag_type_value's real resolved value is -1 by design
    // (HotSpot's array-tag encoding uses -1/-2 as the type/obj tags), which
    // collides with INIT_INT_CONSTANT's "unresolved" sentinel - so it can't
    // be used in this != -1 unresolved-check, unlike its sibling constants.
    static bool arrayLayoutAvailable() {
        return _layout_helper_offset >= 0
            && _Klass__lh_array_tag_shift != -1
            && _Klass__lh_array_tag_obj_value != -1
            && _Klass__lh_header_size_shift != -1
            && _Klass__lh_header_size_mask != -1;
    }

    int layoutHelper() {
        assert(_layout_helper_offset >= 0);
        return *(int*) at(_layout_helper_offset);
    }

    // Klass::layout_helper_is_array()/is_objArray() equivalent. The top
    // _lh_array_tag_bits bits of layout_helper are an arithmetic-shifted
    // tag; instance klasses decode to _lh_neutral_value or the slow-path
    // bit, never one of the two array tag values, so a plain tag compare
    // also rejects non-array klasses without a separate instance check.
    bool isArrayKlass() {
        assert(arrayLayoutAvailable());
        int tag = layoutHelper() >> _Klass__lh_array_tag_shift;
        return tag == _Klass__lh_array_tag_obj_value || tag == _Klass__lh_array_tag_type_value;
    }

    bool isObjectArrayKlass() {
        assert(arrayLayoutAvailable());
        return (layoutHelper() >> _Klass__lh_array_tag_shift) == _Klass__lh_array_tag_obj_value;
    }

    // arrayOopDesc::base_offset_in_bytes() equivalent. Klass::layout_helper_
    // header_size() (klass.hpp) returns this field already in BYTES, not
    // words - confirmed by HotSpot's own sanity assert on it,
    // `hsize < (int)sizeof(oopDesc)*3` (a byte-scale bound; oopDesc is the
    // 12/16-byte mark+klass header, so a plausible word count would never
    // approach that bound). No separate word->byte conversion is needed or
    // correct here.
    int arrayHeaderSizeBytes() {
        assert(isArrayKlass());
        int hsize = (layoutHelper() >> _Klass__lh_header_size_shift) & _Klass__lh_header_size_mask;
        // Mirrors Klass::layout_helper_header_size()'s own sanity assert in
        // klass.hpp (`hsize > 0 && hsize < (int)sizeof(oopDesc)*3`) - a
        // byte-scale bound. Catches a unit mismatch (e.g. reintroducing the
        // words-vs-bytes bug this field once had, or a future JDK moving
        // where this bitfield sits in layout_helper) immediately instead of
        // reading array elements from the wrong offset.
        assert(hsize > 0 && hsize < 64 &&
               "arrayHeaderSizeBytes() decoded a value outside any sane "
               "range - VMStructs layout_helper decoding is likely wrong "
               "for this JDK");
        return hsize;
    }

    // arrayOopDesc::length_offset_in_bytes() equivalent: the length field
    // sits immediately after the klass word at a fixed offset, independent
    // of any element-alignment padding baked into arrayHeaderSizeBytes()
    // above (e.g. a long[] header is padded to 8-byte alignment for its
    // elements, but the length field itself never moves).
    static int arrayLengthOffset() {
        assert(_oop_klass_offset >= 0);
        return _oop_klass_offset + (_narrow_klass_shift >= 0 ? (int) sizeof(uint32_t) : (int) sizeof(void*));
    }

    static int arrayLength(uintptr_t array_oop) {
        return *(int*) (array_oop + arrayLengthOffset());
    }

    // Decoded child oop (already unpacked from a narrow oop when compressed
    // oops are in use) at `index` of an object array. Caller must already
    // know `this` is an object-array klass (isObjectArrayKlass()) - same
    // precondition style as oopMapCount()/oopMapBlockAt() above.
    uintptr_t arrayElementAt(uintptr_t array_oop, int index) {
        assert(isObjectArrayKlass());
        int base = arrayHeaderSizeBytes();
        if (isCompressedOopsEnabled()) {
            uint32_t narrow = *(uint32_t*) (array_oop + base + (uint64_t) index * sizeof(uint32_t));
            return decodeOop(narrow);
        }
        return *(uintptr_t*) (array_oop + base + (uint64_t) index * sizeof(uintptr_t));
    }
DECLARE_END

DECLARE(VMJavaFrameAnchor)
  private:
    enum { MAX_CALL_WRAPPER_DISTANCE = 512 };

  public:
    NOADDRSANITIZE static VMJavaFrameAnchor* fromEntryFrame(uintptr_t fp) {
        assert(_frame_entry_frame_call_wrapper_offset != -1);
        assert(_call_wrapper_anchor_offset >= 0);
        const char* call_wrapper = (const char*) SafeAccess::loadPtr((void**)(fp + _frame_entry_frame_call_wrapper_offset), nullptr);
        if (!goodPtr(call_wrapper) || (uintptr_t)call_wrapper - fp > MAX_CALL_WRAPPER_DISTANCE) {
            return NULL;
        }
        return VMJavaFrameAnchor::cast((const void*)(call_wrapper + _call_wrapper_anchor_offset));
    }

    NOADDRSANITIZE uintptr_t lastJavaSP() {
        assert(_anchor_sp_offset >= 0);
        return (uintptr_t) SafeAccess::loadPtr((void**) at(_anchor_sp_offset), nullptr);
    }

    NOADDRSANITIZE uintptr_t lastJavaFP() {
        assert(_anchor_fp_offset >= 0);
        return (uintptr_t) SafeAccess::loadPtr((void**) at(_anchor_fp_offset), nullptr);
    }

    NOADDRSANITIZE const void* lastJavaPC() {
        assert(_anchor_pc_offset >= 0);
        return SafeAccess::loadPtr((void**) at(_anchor_pc_offset), nullptr);
    }

    void setLastJavaPC(const void* pc) {
        assert(_anchor_pc_offset >= 0);
        *(const void**) at(_anchor_pc_offset) = pc;
    }

    NOADDRSANITIZE bool getFrame(const void*& pc, uintptr_t& sp, uintptr_t& fp) {
        if (lastJavaPC() != NULL && lastJavaSP() != 0) {
            pc = lastJavaPC();
            sp = lastJavaSP();
            fp = lastJavaFP();
            return true;
        }
        return false;
    }
DECLARE_END

DECLARE(VMContinuationEntry)
    // Address of the enterSpecial frame's {saved_fp, return_addr} pair.
    // Layout above this address: [saved_fp][return_addr_to_carrier][carrier_sp...]
    // The ContinuationEntry struct is embedded on the carrier stack immediately
    // below enterSpecial's saved-fp slot; its size() equals the JVM's
    // ContinuationEntry::size() static method, confirmed at:
    //   https://github.com/openjdk/jdk/blob/master/src/hotspot/share/runtime/continuationEntry.hpp
    //   https://github.com/openjdk/jdk/blob/master/src/hotspot/share/runtime/continuationEntry.cpp
    uintptr_t entryFP() const {
        assert(type_size() > 0); // must not be called before ContinuationEntry is resolved
        return (uintptr_t)this + type_size();
    }

    // Returns the enclosing ContinuationEntry when continuations are nested
    // (e.g. a Continuation.run() call inside a virtual thread).  Returns
    // nullptr when there is no enclosing entry or the field is unavailable.
    VMContinuationEntry* parent() const {
        if (_cont_entry_parent_offset < 0) return nullptr;
        void* ptr = SafeAccess::loadPtr((void**) const_cast<VMContinuationEntry*>(this)->at(_cont_entry_parent_offset), nullptr);
        return ptr != nullptr ? VMContinuationEntry::cast(ptr) : nullptr;
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
  friend class JVMThread;
    static void* initialize(jthread thread);

    static inline VMThread* current();
    static inline VMThread* fromJavaThread(JNIEnv* env, jthread thread);
    static bool isJavaThread(VMThread* thread);
    static ExecutionMode getExecutionMode();
    static OSThreadState getOSThreadState();

    int osThreadId();
    JNIEnv* jni();

    OSThreadState osThreadState();

    JVMJavaThreadState state();

    bool inDeopt() {
        if (!isJavaThread(this)) return false;
        assert(_thread_vframe_offset >= 0);
        return SafeAccess::loadPtr((void**) at(_thread_vframe_offset), nullptr) != NULL;
    }

    // Check if the thread object memory is readable up to the largest used
    // offset. On some JVMs (e.g. GraalVM 25 aarch64), a wall-clock signal
    // can hit a thread whose memory is only partially mapped — the vtable
    // at offset 0 may be readable while fields deeper in the object are not.
    // On non-HotSpot JVMs (J9, Zing) offsets stay at -1; skip the check.
    bool isThreadAccessible() {
        int max_offset = -1;
        if (_thread_exception_offset > max_offset) max_offset = _thread_exception_offset;
        if (_thread_state_offset > max_offset) max_offset = _thread_state_offset;
        if (_thread_osthread_offset > max_offset) max_offset = _thread_osthread_offset;
        if (_thread_anchor_offset > max_offset) max_offset = _thread_anchor_offset;
        if (_thread_vframe_offset > max_offset) max_offset = _thread_vframe_offset;
        if (max_offset < 0) return true;
        return SafeAccess::isReadableRange(this, max_offset + sizeof(void*));
    }

    void*& exception() {
        if (_thread_exception_offset < 0) {
            static void* _null_exception = nullptr;
            return _null_exception;
        }
        return *(void**) at(_thread_exception_offset);
    }

    NOADDRSANITIZE VMJavaFrameAnchor* anchor() {
        if (!isJavaThread(this)) return NULL;
        assert(_thread_anchor_offset >= 0);
        return VMJavaFrameAnchor::cast(at(_thread_anchor_offset));
    }

    // Returns true when this thread is currently executing a virtual thread
    // (i.e. JavaThread::_cont_entry is non-null).  _cont_entry_offset is
    // only populated on JDK 27+ (from gHotSpotVMStructs, JDK-8378985); there
    // is no symbol fallback, so this returns false on JDK <27.
    // Does NOT require ContinuationEntry type_size().
    bool isCarryingVirtualThread() const {
        if (_cont_entry_offset < 0) return false;
        return SafeAccess::loadPtr((void**) const_cast<VMThread*>(this)->at(_cont_entry_offset), nullptr) != nullptr;
    }

    // Returns the innermost active ContinuationEntry for this thread, or nullptr
    // if none exists or ContinuationEntry layout is unavailable (JDK <27, where
    // neither _cont_entry_offset nor ContinuationEntry are in gHotSpotVMStructs/
    // gHotSpotVMTypes so type_size() == 0).
    // Used by stackWalker to locate the enterSpecial frame when crossing the
    // virtual-thread continuation boundary.
    VMContinuationEntry* contEntry() {
        if (_cont_entry_offset < 0 || VMContinuationEntry::type_size() == 0) return nullptr;
        void* ptr = SafeAccess::loadPtr((void**) at(_cont_entry_offset), nullptr);
        return ptr != nullptr ? VMContinuationEntry::cast(ptr) : nullptr;
    }

    inline VMMethod* compiledMethod();
private:
    static inline int nativeThreadId(JNIEnv* jni, jthread thread);
    inline void** vtable();
    inline bool hasJavaThreadVtable();

DECLARE_END

DECLARE(VMConstantPool)
    inline VMKlass* holder_or_null() const;
    inline VMSymbol* symbolAt(int index) const;
 private:
    inline intptr_t* base() const;
DECLARE_END

DECLARE(VMConstMethod)
    inline VMConstantPool* constants_or_null() const;
    inline VMSymbol* name() const;
    inline VMSymbol* signature() const;
private:
    inline u16 nameIndex() const;
    inline u16 signatureIndex() const;
 DECLARE_END


DECLARE(VMMethod)   
    private:
    static bool check_jmethodID_J9(jmethodID id);
    static bool check_jmethodID_hotspot(jmethodID id);

  public:
    inline jmethodID id();

    // Performs extra validation when VMMethod comes from incomplete frame
    inline jmethodID validatedId();

    const char* bytecode() {
        assert(_method_constmethod_offset >= 0);
        return *(const char**) at(_method_constmethod_offset) + VMConstMethod::type_size();
    }

    inline VMConstMethod* constMethod_or_null() const;
    inline VMNMethod* code();

    static bool check_jmethodID(jmethodID id);
DECLARE_END

// Inline string comparison to avoid indirect call to strncmp
template<size_t N>
static inline bool startsWith(const char* s, const char (&pattern)[N]) {
    for (size_t i = 0; i < N - 1; i++) {
        if (s[i] != pattern[i]) return false;
    }
    return true;
}

DECLARE(VMNMethod)
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
        if (_code_offset != -1) { // JDK23+
            return at(*(int*) at(_code_offset));
        } else {
            return *(const char**) at(_code_address);
        }
    }

    const char* scopes() {
        if (_scopes_data_offset != -1) { // JDK23+
            return immutableDataAt(*(int*) at(_scopes_data_offset));
        } else {
            return *(const char**) at(_scopes_data_address);
        }
    }

    const void* entry() {
        if (_nmethod_entry_offset != -1) { // JDK23+
            return at(*(int*) at(_code_offset) + *(unsigned short*) at(_nmethod_entry_offset));
        } else {
            return *(void**) at(_nmethod_entry_address);
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

    bool isInterpreter() {
        return this == _interpreter_nm;
    }

    bool isNMethod() {
        const char* n = name();
        return n != NULL && (startsWith(n, "nmethod\0") || startsWith(n, "native nmethod\0"));
    }

    bool isStub() {
        const char* n = name();
        return n != NULL && startsWith(n, "StubRoutines");
    }

    bool isVTableStub() {
        const char* n = name();
        return n != NULL && startsWith(n, "vtable chunks");
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

    static void setInterpreterStart(const void* start) {
        _interpreter_start = start;
        _interpreter_nm = findNMethod(start);
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

#endif // _HOTSPOT_VMSTRUCTS_H
