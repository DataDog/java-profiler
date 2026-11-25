/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Exercises Lookup::resolveMethod()'s two "fill" paths through the public
// API (fillNativeMethodInfo()/fillJavaMethodInfo() are private, and their
// ResolveMethodState parameter is a type local to flightRecorder.cpp, so
// there is no way to call them, or inspect a ResolveMethodState, directly
// from a separate translation unit -- see the note in
// lineNumberTableCopy_ut.cpp about faking JVMTI/JNI for this exact code).
//
// A. A native frame whose method_id is a mangled C++ symbol (leading "_Z")
//    drives fillNativeMethodInfo()'s demangling branch. That branch mallocs
//    state._demangled via abi::__cxa_demangle(), truncates it with
//    cutArguments(), copies the result into the symbol dictionary, then
//    frees state._demangled and nulls it out -- all before resolveMethod()
//    returns. There is no live handle left to assert against directly, so
//    this test instead asserts the *outcome* of that lifecycle: the
//    demangled-and-cut name lands in the symbol dictionary, and a second
//    resolve() of the identical frame hits the MethodMap _mark fast path
//    (proving the demangle/free cycle ran exactly once, not once per call).
//
// B. A Java frame drives fillJavaMethodInfo(), which PushLocalFrame()s a
//    JNI frame up front and records that in ResolveMethodState::_framePushed.
//    Because ResolveMethodState is a stack local of Lookup::fillMethod(),
//    its destructor runs when fillMethod() returns, popping the JNI frame
//    exactly once via release(). This test fakes jvmtiEnv/JNIEnv/JavaVM
//    (same pattern as ScopedFakeJni in hotspotMethodId_ut.cpp and
//    JVMSupportRestartTest in jvmSupport_ut.cpp) to count PushLocalFrame/
//    PopLocalFrame calls and assert they balance 1:1.

#include <gtest/gtest.h>

#include "../../main/cpp/callTraceHashTable.h"
#include "../../main/cpp/flightRecorder.h"
#include "../../main/cpp/flightRecorder.inline.h"
#include "../../main/cpp/gtest_crash_handler.h"
#include "../../main/cpp/threadLocalData.inline.h"
#include "../../main/cpp/vmEntry.h"
#include "safeAccessTestSupport.h"

#include <cstring>
#include <map>
#include <memory>
#include <new>
#include <string>
#include <vector>

static constexpr char LOOKUP_RESOLVE_METHOD_TEST_NAME[] = "LookupResolveMethodTest";
class LookupResolveMethodGlobalSetup {
public:
    LookupResolveMethodGlobalSetup() { installGtestCrashHandler<LOOKUP_RESOLVE_METHOD_TEST_NAME>(); }
    ~LookupResolveMethodGlobalSetup() { restoreDefaultSignalHandlers(); }
};
static LookupResolveMethodGlobalSetup lookup_resolve_method_global_setup;

// ---------------------------------------------------------------------------
// Test-only friend accessor for VM internals -- same pattern used by
// hotspotMethodId_ut.cpp / jvmSupport_ut.cpp / frame_ut.cpp. Each test file
// declares its own local class of this exact name; VM's `friend class
// VMTestAccessor;` grants it access regardless of which translation unit
// defines it.
// ---------------------------------------------------------------------------
class VMTestAccessor {
public:
    static bool getHotspot() { return VM::_hotspot; }
    static void setHotspot(bool v) { VM::_hotspot = v; }
    static int getHotspotVersion() { return VM::_hotspot_version; }
    static void setHotspotVersion(int v) { VM::_hotspot_version = v; }
    static bool getOpenJ9() { return VM::_openj9; }
    static void setOpenJ9(bool v) { VM::_openj9 = v; }
    static JavaVM* getVm() { return VM::_vm; }
    static void setVm(JavaVM* vm) { VM::_vm = vm; }
    static jvmtiEnv* getJvmti() { return VM::_jvmti; }
    static void setJvmti(jvmtiEnv* env) { VM::_jvmti = env; }
};

// Reaches the private static per-trace writer; Recording itself needs a live
// JVMTI environment to construct.
class RecordingTestAccessor {
public:
    static void writeStackTrace(Buffer* buf, CallTrace* trace, Lookup* lookup,
                                Recording::FlushFn flush, void* flush_ctx) {
        Recording::writeStackTrace(buf, trace, lookup, flush, flush_ctx);
    }
};

namespace {

// ===========================================================================
// A. Native mangled-symbol frame -- fillNativeMethodInfo()'s demangling
//    branch. No JVMTI/JNI involved: BCI_ERROR's method_id is read as a
//    plain native_function_name string, never as a jmethodID.
// ===========================================================================

TEST(LookupResolveMethodNativeDemangleTest, MangledCppSymbolIsDemangledCutAndCachedOnce) {
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);

    ASGCT_CallFrame frame{};
    frame.bci = BCI_ERROR;
    // Itanium-mangled `foo(int, int)`. abi::__cxa_demangle() must turn this
    // into "foo(int, int)"; Lookup::cutArguments() then truncates it at the
    // matching '(' to leave just "foo".
    frame.native_function_name = "_Z3fooii";

    MethodInfo* mi = lookup.resolveMethod(frame);
    ASSERT_NE(nullptr, mi);
    EXPECT_TRUE(mi->_mark);
    EXPECT_EQ(FRAME_CPP, mi->_type)
        << "leading _Z must route through the __cxa_demangle() branch, not "
           "the plain-native-symbol fallback";

    std::map<unsigned int, const char*> symbols;
    lookup._symbols.collect(symbols);
    ASSERT_EQ(1u, symbols.count(mi->_name));
    EXPECT_STREQ("foo", symbols[mi->_name])
        << "state._demangled, after __cxa_demangle() + cutArguments(), must "
           "be exactly what got copied into the symbol dictionary";
    ASSERT_EQ(1u, symbols.count(mi->_sig));
    EXPECT_STREQ("()L;", symbols[mi->_sig]);

    // A second resolve() of the identical frame must hit MethodMap's _mark
    // fast path in resolveMethod() and never re-enter fillNativeMethodInfo().
    // That is the only externally observable proof that the malloc'd
    // state._demangled buffer was tracked and freed exactly once on the
    // first call, rather than leaking or being re-demangled per call.
    MethodInfo* mi_again = lookup.resolveMethod(frame);
    EXPECT_EQ(mi, mi_again);
}

// A failed symbol insert must give a native frame the reserved name id and the
// reserved signature id: a signature id of UNRESOLVED_ID would be written as a
// non-descriptor. One frame per fillNativeMethodInfo() branch.
TEST(LookupResolveMethodNativeDemangleTest, FailedSymbolInsertUsesReservedNameAndSignatureIds) {
    struct Case { const char* name; int type; };
    const Case cases[] = {
        {"_Z3fooii", FRAME_CPP}, {"plain_native", FRAME_NATIVE}, {"kernel_fn_[k]", FRAME_KERNEL}};
    for (const Case& c : cases) {
        const char* name = c.name;
        MethodMap method_map;
        StringDictionary classes;
        Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
        lookup._symbols.failKeyAllocationForTest(true);

        ASGCT_CallFrame frame{};
        frame.bci = BCI_ERROR;
        frame.native_function_name = name;
        MethodInfo* mi = lookup.resolveMethod(frame);
        ASSERT_NE(nullptr, mi) << name;
        EXPECT_EQ(c.type, mi->_type) << name << ": the intended branch was not reached";
        EXPECT_GT(lookup._symbols.keyAllocFailuresForTest(), 0) << name;
        EXPECT_EQ(SymbolDictionary::UNRESOLVED_ID, mi->_name) << name;
        EXPECT_EQ(SymbolDictionary::UNRESOLVED_SIG_ID, mi->_sig) << name;
    }
}

// ===========================================================================
// B. Java frame -- fillJavaMethodInfo()'s JNI PushLocalFrame/PopLocalFrame
//    balance, faked entirely without a live JVM.
// ===========================================================================

// Bumped by the mocked JVMTI/JNI function tables below; a fresh instance per
// test via ScopedFakeJvmAndJni::SetUp().
struct FakeJvmCounters {
    int push_local_frame = 0;
    int pop_local_frame = 0;
    int deallocate = 0;
    // When set before resolveMethod() runs, pushLocalFrame() reports failure
    // (matching JNI's real contract) instead of succeeding -- drives
    // fillJavaMethodInfo()'s early "nothing to fill" return.
    bool fail_push_local_frame = false;
    // When set, getLineNumberTable() hands back a real (malloc'd) table
    // instead of JVMTI_ERROR_ABSENT_INFORMATION.
    bool provide_line_number_table = false;
    // Errors returned by the JVMTI calls fillJavaMethodInfo() makes.
    jvmtiError declaring_class_error = JVMTI_ERROR_NONE;
    jvmtiError class_signature_error = JVMTI_ERROR_NONE;
    jvmtiError method_name_error = JVMTI_ERROR_NONE;
    // When set, GetMethodDeclaringClass() hands back declaring_class.
    bool override_declaring_class = false;
    jclass declaring_class = nullptr;
    // When set, GetMethodName() hands back borrowed_method_name (possibly
    // null or unreadable) instead of a malloc'd copy; Deallocate() never frees it.
    bool borrow_method_name = false;
    char* borrowed_method_name = nullptr;
    // Same for the method signature GetMethodName() hands back.
    bool borrow_method_sig = false;
    char* borrowed_method_sig = nullptr;
    int deallocate_borrowed = 0;
    // When non-empty, GetClassSignature() returns a malloc'd copy of it.
    std::string class_signature;
};

class ScopedFakeJvmAndJni {
public:
    ScopedFakeJvmAndJni() : _saved_vm(VMTestAccessor::getVm()) {
        s_instance = this;

        _jni_tbl = JNINativeInterface_{};
        _jni_tbl.PushLocalFrame = &pushLocalFrame;
        _jni_tbl.PopLocalFrame = &popLocalFrame;
        _jni_env.functions = &_jni_tbl;

        _vm_tbl = JNIInvokeInterface_{};
        _vm_tbl.GetEnv = &getEnv;
        _vm.functions = &_vm_tbl;

        _jvmti_tbl = jvmtiInterface_1_{};
        _jvmti_tbl.GetPhase = &getPhase;
        _jvmti_tbl.GetMethodDeclaringClass = &getMethodDeclaringClass;
        _jvmti_tbl.GetClassSignature = &getClassSignature;
        _jvmti_tbl.GetMethodName = &getMethodName;
        _jvmti_tbl.GetLineNumberTable = &getLineNumberTable;
        _jvmti_tbl.Deallocate = &deallocate;
        _jvmti_env.functions = &_jvmti_tbl;

        VMTestAccessor::setVm(reinterpret_cast<JavaVM*>(&_vm));
    }

    ~ScopedFakeJvmAndJni() {
        // The profiler never Deallocate()s an unreadable class signature; free it here.
        free(_class_signature_alloc);
        VMTestAccessor::setVm(_saved_vm);
        s_instance = nullptr;
    }

    jvmtiEnv* jvmti() { return reinterpret_cast<jvmtiEnv*>(&_jvmti_env); }

    FakeJvmCounters counters;

private:
    static char* dup(const char* s) {
        size_t len = strlen(s) + 1;
        char* copy = (char*)malloc(len);
        memcpy(copy, s, len);
        return copy;
    }

    static jint JNICALL pushLocalFrame(JNIEnv*, jint) {
        s_instance->counters.push_local_frame++;
        return s_instance->counters.fail_push_local_frame ? -1 : 0;
    }
    static jobject JNICALL popLocalFrame(JNIEnv*, jobject) {
        s_instance->counters.pop_local_frame++;
        return nullptr;
    }
    static jint JNICALL getEnv(JavaVM*, void** penv, jint) {
        *penv = reinterpret_cast<JNIEnv*>(&s_instance->_jni_env);
        return JNI_OK;
    }
    static jvmtiError JNICALL getPhase(jvmtiEnv*, jvmtiPhase* phase_ptr) {
        *phase_ptr = JVMTI_PHASE_LIVE;
        return JVMTI_ERROR_NONE;
    }
    static jvmtiError JNICALL getMethodDeclaringClass(jvmtiEnv*, jmethodID, jclass* declaring_class_ptr) {
        static int fake_class_storage = 0;
        FakeJvmCounters& c = s_instance->counters;
        if (c.declaring_class_error != JVMTI_ERROR_NONE) {
            return c.declaring_class_error;
        }
        *declaring_class_ptr = c.override_declaring_class
            ? c.declaring_class : reinterpret_cast<jclass>(&fake_class_storage);
        return JVMTI_ERROR_NONE;
    }
    static jvmtiError JNICALL getClassSignature(jvmtiEnv*, jclass, char** signature_ptr, char** generic_ptr) {
        if (s_instance->counters.class_signature_error != JVMTI_ERROR_NONE) {
            return s_instance->counters.class_signature_error;
        }
        const std::string& sig = s_instance->counters.class_signature;
        *signature_ptr = dup(sig.empty() ? "Lcom/example/Foo;" : sig.c_str());
        s_instance->_class_signature_alloc = *signature_ptr;
        if (generic_ptr != nullptr) {
            *generic_ptr = nullptr;
        }
        return JVMTI_ERROR_NONE;
    }
    static jvmtiError JNICALL getMethodName(jvmtiEnv*, jmethodID, char** name_ptr,
                                            char** signature_ptr, char** generic_ptr) {
        // Deliberately not "run"/"main" (with the exact strncmp lengths
        // fillJavaMethodInfo checks) so the Thread.run/main entry-frame
        // detection -- which would need FindClass/GetMethodID/
        // CallBooleanMethod mocked too -- never fires.
        FakeJvmCounters& c = s_instance->counters;
        if (c.method_name_error != JVMTI_ERROR_NONE) {
            return c.method_name_error;
        }
        *name_ptr = c.borrow_method_name ? c.borrowed_method_name : dup("sampleMethod");
        *signature_ptr = c.borrow_method_sig ? c.borrowed_method_sig : dup("()V");
        if (generic_ptr != nullptr) {
            *generic_ptr = nullptr;
        }
        return JVMTI_ERROR_NONE;
    }
    static jvmtiError JNICALL getLineNumberTable(jvmtiEnv*, jmethodID, jint* entry_count_ptr,
                                                 jvmtiLineNumberEntry** table_ptr) {
        if (!s_instance->counters.provide_line_number_table) {
            // No line table: exercises the (very common) "unavailable" path
            // without needing a second malloc'd buffer and a matching
            // Deallocate() for it.
            return JVMTI_ERROR_ABSENT_INFORMATION;
        }
        auto* table = (jvmtiLineNumberEntry*)malloc(sizeof(jvmtiLineNumberEntry));
        table[0].start_location = 0;
        table[0].line_number = 42;
        *entry_count_ptr = 1;
        *table_ptr = table;
        return JVMTI_ERROR_NONE;
    }
    static jvmtiError JNICALL deallocate(jvmtiEnv*, unsigned char* mem) {
        FakeJvmCounters& c = s_instance->counters;
        c.deallocate++;
        char* p = reinterpret_cast<char*>(mem);
        if ((c.borrow_method_name && p == c.borrowed_method_name) ||
            (c.borrow_method_sig && p == c.borrowed_method_sig)) {
            c.deallocate_borrowed++;
            return JVMTI_ERROR_NONE;
        }
        if (p == s_instance->_class_signature_alloc) {
            s_instance->_class_signature_alloc = nullptr;
        }
        free(mem); // matches the real JVMTI contract; a double-free here aborts the test
        return JVMTI_ERROR_NONE;
    }

    static ScopedFakeJvmAndJni* s_instance;
    char* _class_signature_alloc = nullptr;

    JavaVM* _saved_vm;
    JNINativeInterface_ _jni_tbl{};
    JNIEnv_ _jni_env{};
    JNIInvokeInterface_ _vm_tbl{};
    JavaVM_ _vm{};
    jvmtiInterface_1_ _jvmti_tbl{};
    _jvmtiEnv _jvmti_env{};
};
ScopedFakeJvmAndJni* ScopedFakeJvmAndJni::s_instance = nullptr;

class LookupResolveMethodJavaFrameTest : public ::testing::Test {
protected:
    void SetUp() override {
        _saved_hotspot = VMTestAccessor::getHotspot();
        _saved_hotspot_version = VMTestAccessor::getHotspotVersion();
        // hotspot_version() > 25 makes VMMethod::check_jmethodID_hotspot()
        // return true immediately (see vmStructs.cpp) without walking any
        // Method*/ConstMethod* fields -- exactly what lets this test use an
        // opaque, never-dereferenced jmethodID.
        VMTestAccessor::setHotspot(true);
        VMTestAccessor::setHotspotVersion(30);

        ProfiledThread::initCurrentThreadSignalSafe();

        _saved_jvmti = VMTestAccessor::getJvmti();
        _saved_openj9 = VMTestAccessor::getOpenJ9();
    }

    void TearDown() override {
        VMTestAccessor::setOpenJ9(_saved_openj9);
        VMTestAccessor::setJvmti(_saved_jvmti);
        VMTestAccessor::setHotspot(_saved_hotspot);
        VMTestAccessor::setHotspotVersion(_saved_hotspot_version);
    }

    // The string probe in fillJavaMethodInfo() needs SafeAccess fault recovery.
    ScopedSafeAccessHandler _safe_access{LOOKUP_RESOLVE_METHOD_TEST_NAME};
    jvmtiEnv* _saved_jvmti;
    bool _saved_openj9;
    bool _saved_hotspot;
    int _saved_hotspot_version;
};

TEST_F(LookupResolveMethodJavaFrameTest, JniLocalFrameIsPoppedExactlyOnceOnNormalReturn) {
    ScopedFakeJvmAndJni fake;
    VMTestAccessor::setJvmti(fake.jvmti());

    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);

    int fake_method_storage = 0;
    ASGCT_CallFrame frame{};
    frame.bci = FrameType::encode(FRAME_INTERPRETED, /*bci=*/0);
    frame.method_id = reinterpret_cast<jmethodID>(&fake_method_storage);

    MethodInfo* mi = lookup.resolveMethod(frame);

    ASSERT_NE(nullptr, mi);
    EXPECT_TRUE(mi->_mark);
    EXPECT_EQ(FRAME_INTERPRETED, mi->_type);

    // fillJavaMethodInfo() pushes exactly one JNI local frame up front, and
    // ResolveMethodState's destructor (running when Lookup::fillMethod()
    // returns normally) must pop exactly that one frame via release() --
    // not zero (leaked local ref capacity) and not more than one.
    EXPECT_EQ(1, fake.counters.push_local_frame);
    EXPECT_EQ(1, fake.counters.pop_local_frame);

    // The three JVMTI-allocated strings (class signature, method name,
    // method signature) must each be deallocated exactly once via
    // ResolveMethodState::release() -- this is what class_name/method_name/
    // method_sig being copied into the *_raw locals and back into the
    // volatile state fields (see fillJavaMethodInfo) is for.
    EXPECT_EQ(3, fake.counters.deallocate);
}

// Regression test: fillJavaMethodInfo() returning early (PushLocalFrame
// failed) must not leave a marked-but-empty row for this jmethodID, and must
// not hand this frame a dangling method-pool key of 0 -- resolveMethod()
// must fall back to the shared, already-marked unknown-method row, exactly
// like every other resolution-failed path in fillMethod().
TEST_F(LookupResolveMethodJavaFrameTest, PushLocalFrameFailureFallsBackToUnknownMethodAndLeavesRowUnmarked) {
    ScopedFakeJvmAndJni fake;
    fake.counters.fail_push_local_frame = true;
    VMTestAccessor::setJvmti(fake.jvmti());

    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);

    int fake_method_storage = 0;
    jmethodID fake_method = reinterpret_cast<jmethodID>(&fake_method_storage);
    ASGCT_CallFrame frame{};
    frame.bci = FrameType::encode(FRAME_INTERPRETED, /*bci=*/0);
    frame.method_id = fake_method;

    MethodInfo* mi = lookup.resolveMethod(frame);

    ASSERT_NE(nullptr, mi);
    EXPECT_EQ(&lookup._unknown_method, mi)
        << "an unfilled row must fall back to the shared unknown-method "
           "sentinel, not hand back a row with an unallocated key";
    EXPECT_TRUE(mi->_mark);
    // PushLocalFrame failed before doing anything else, so no JVMTI calls
    // (and no matching Deallocate()s) ever happened for this attempt.
    EXPECT_EQ(1, fake.counters.push_local_frame);
    EXPECT_EQ(0, fake.counters.pop_local_frame);
    EXPECT_EQ(0, fake.counters.deallocate);

    // The frame's own MethodMap row (distinct from the shared unknown-method
    // row above) must stay unmarked and keyless so the next occurrence of
    // this jmethodID retries the fill instead of reusing a bogus entry.
    auto it = method_map.find(MethodMap::makeKey(fake_method));
    ASSERT_NE(method_map.end(), it);
    EXPECT_FALSE(it->second._mark);
    EXPECT_EQ(0u, it->second._key);
}

// Regression test: a method's line-number table, fetched once on its first
// resolve (first_time -- see the `if (first_time)` guard around
// GetLineNumberTable() in fillJavaMethodInfo()), must survive being
// re-resolved in a later chunk. writeMethods() clears only mi->_mark between
// chunks and leaves mi->_key (and thus first_time) alone, so a later resolve
// of the same jmethodID never calls GetLineNumberTable() again -- the local
// line_number_table stays null that time, and the assignment into
// mi->_line_number_table must be skipped rather than clobbering the real
// table with an empty SharedLineNumberTable(0, nullptr).
TEST_F(LookupResolveMethodJavaFrameTest, LineNumberTableSurvivesReResolveInALaterChunk) {
    ScopedFakeJvmAndJni fake;
    fake.counters.provide_line_number_table = true;
    VMTestAccessor::setJvmti(fake.jvmti());

    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);

    int fake_method_storage = 0;
    jmethodID fake_method = reinterpret_cast<jmethodID>(&fake_method_storage);
    ASGCT_CallFrame frame{};
    frame.bci = FrameType::encode(FRAME_INTERPRETED, /*bci=*/0);
    frame.method_id = fake_method;

    MethodInfo* mi = lookup.resolveMethod(frame);
    ASSERT_NE(nullptr, mi);
    ASSERT_NE(nullptr, mi->_line_number_table);
    ASSERT_EQ(42, mi->getLineNumber(0));
    u32 key_after_first_resolve = mi->_key;

    // Simulate writeMethods() moving to the next chunk: it clears _mark on
    // every marked row it serializes, but never touches _key.
    mi->_mark = false;

    MethodInfo* mi_again = lookup.resolveMethod(frame);

    ASSERT_EQ(mi, mi_again) << "same jmethodID must resolve to the same MethodMap row";
    EXPECT_TRUE(mi_again->_mark);
    EXPECT_EQ(key_after_first_resolve, mi_again->_key)
        << "first_time must be false on this second resolve";
    ASSERT_NE(nullptr, mi_again->_line_number_table)
        << "the table fetched on the first resolve must not be discarded "
           "just because this call didn't re-fetch one";
    EXPECT_EQ(42, mi_again->getLineNumber(0));
}

// ---------------------------------------------------------------------------
// "<unloaded>" causes: each skip bumps jmethodid_skipped_count and exactly one
// reason counter; a valid name next to an unreadable page is not a skip.
// ---------------------------------------------------------------------------

struct SkipCounters {
    long long skipped = Counters::getCounter(JMETHODID_SKIPPED);
    long long invalid_id = Counters::getCounter(METHOD_RESOLVE_SKIPPED_INVALID_ID);
    long long jvmti_error = Counters::getCounter(METHOD_RESOLVE_SKIPPED_JVMTI_ERROR);
    long long unreadable_name = Counters::getCounter(METHOD_RESOLVE_SKIPPED_UNREADABLE_NAME);
};

// Resolves one interpreted frame for `method` and returns its row.
MethodInfo* resolveJavaFrame(Lookup& lookup, jmethodID method) {
    ASGCT_CallFrame frame{};
    frame.bci = FrameType::encode(FRAME_INTERPRETED, /*bci=*/0);
    frame.method_id = method;
    return lookup.resolveMethod(frame);
}

// Asserts mi is an "<unloaded>" row counted once, under `reason` only.
void expectSkippedFor(Lookup& lookup, MethodInfo* mi, const SkipCounters& before, CounterId reason) {
    if (mi == nullptr) {
        ADD_FAILURE() << "resolveMethod() returned no row";
        return;
    }
    EXPECT_EQ(lookup.getSymbol("<unloaded>"), mi->_name);
    SkipCounters after;
    EXPECT_EQ(before.skipped + 1, after.skipped);
    EXPECT_EQ(before.invalid_id + (reason == METHOD_RESOLVE_SKIPPED_INVALID_ID ? 1 : 0), after.invalid_id);
    EXPECT_EQ(before.jvmti_error + (reason == METHOD_RESOLVE_SKIPPED_JVMTI_ERROR ? 1 : 0), after.jvmti_error);
    EXPECT_EQ(before.unreadable_name + (reason == METHOD_RESOLVE_SKIPPED_UNREADABLE_NAME ? 1 : 0),
              after.unreadable_name);
}

TEST_F(LookupResolveMethodJavaFrameTest, ValidNameJustBeforeUnreadablePageResolves) {
    GuardedPage region;
    ASSERT_TRUE(region.ok());
    ScopedFakeJvmAndJni fake;
    fake.counters.borrow_method_name = true;
    fake.counters.borrowed_method_name = region.placeAtEnd("sampleMethod");
    // The fixed 256-byte probe this replaces rejected exactly this name.
    ASSERT_FALSE(SafeAccess::isReadableRange(fake.counters.borrowed_method_name, 256));
    VMTestAccessor::setJvmti(fake.jvmti());

    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    int fake_method_storage = 0;
    SkipCounters before;

    MethodInfo* mi = resolveJavaFrame(lookup, reinterpret_cast<jmethodID>(&fake_method_storage));

    ASSERT_NE(nullptr, mi);
    EXPECT_EQ(lookup.getSymbol("sampleMethod"), mi->_name);
    EXPECT_EQ(before.skipped, Counters::getCounter(JMETHODID_SKIPPED));
    EXPECT_EQ(1, fake.counters.deallocate_borrowed);
}

TEST_F(LookupResolveMethodJavaFrameTest, InvalidJmethodIdCountsInvalidId) {
    // hotspot_version <= 25 makes check_jmethodID_hotspot() read the slot,
    // and a NULL slot is a freed jmethodID.
    VMTestAccessor::setHotspotVersion(25);
    ScopedFakeJvmAndJni fake;
    VMTestAccessor::setJvmti(fake.jvmti());
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    void* null_slot = nullptr;
    SkipCounters before;

    MethodInfo* mi = resolveJavaFrame(lookup, reinterpret_cast<jmethodID>(&null_slot));

    expectSkippedFor(lookup, mi, before, METHOD_RESOLVE_SKIPPED_INVALID_ID);
}

TEST_F(LookupResolveMethodJavaFrameTest, J9UnloadedLoaderClassCountsInvalidId) {
    VMTestAccessor::setOpenJ9(true);
    VMTestAccessor::setHotspot(false);
    ScopedFakeJvmAndJni fake;
    fake.counters.override_declaring_class = true;
    fake.counters.declaring_class = reinterpret_cast<jclass>(-1);
    VMTestAccessor::setJvmti(fake.jvmti());
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    // check_jmethodID_J9() only requires a non-null slot.
    int fake_method = 0;
    void* slot = &fake_method;
    SkipCounters before;

    MethodInfo* mi = resolveJavaFrame(lookup, reinterpret_cast<jmethodID>(&slot));

    expectSkippedFor(lookup, mi, before, METHOD_RESOLVE_SKIPPED_INVALID_ID);
}

TEST_F(LookupResolveMethodJavaFrameTest, DeclaringClassErrorCountsJvmtiError) {
    ScopedFakeJvmAndJni fake;
    fake.counters.declaring_class_error = JVMTI_ERROR_INVALID_METHODID;
    VMTestAccessor::setJvmti(fake.jvmti());
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    int fake_method_storage = 0;
    SkipCounters before;

    MethodInfo* mi = resolveJavaFrame(lookup, reinterpret_cast<jmethodID>(&fake_method_storage));

    expectSkippedFor(lookup, mi, before, METHOD_RESOLVE_SKIPPED_JVMTI_ERROR);
}

TEST_F(LookupResolveMethodJavaFrameTest, NullDeclaringClassCountsJvmtiError) {
    ScopedFakeJvmAndJni fake;
    fake.counters.override_declaring_class = true;
    fake.counters.declaring_class = nullptr;
    VMTestAccessor::setJvmti(fake.jvmti());
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    int fake_method_storage = 0;
    SkipCounters before;

    MethodInfo* mi = resolveJavaFrame(lookup, reinterpret_cast<jmethodID>(&fake_method_storage));

    expectSkippedFor(lookup, mi, before, METHOD_RESOLVE_SKIPPED_JVMTI_ERROR);
}

TEST_F(LookupResolveMethodJavaFrameTest, ClassSignatureErrorCountsJvmtiError) {
    ScopedFakeJvmAndJni fake;
    fake.counters.class_signature_error = JVMTI_ERROR_INVALID_CLASS;
    VMTestAccessor::setJvmti(fake.jvmti());
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    int fake_method_storage = 0;
    SkipCounters before;

    MethodInfo* mi = resolveJavaFrame(lookup, reinterpret_cast<jmethodID>(&fake_method_storage));

    expectSkippedFor(lookup, mi, before, METHOD_RESOLVE_SKIPPED_JVMTI_ERROR);
}

TEST_F(LookupResolveMethodJavaFrameTest, MethodNameErrorCountsJvmtiError) {
    ScopedFakeJvmAndJni fake;
    fake.counters.method_name_error = JVMTI_ERROR_INVALID_METHODID;
    VMTestAccessor::setJvmti(fake.jvmti());
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    int fake_method_storage = 0;
    SkipCounters before;

    MethodInfo* mi = resolveJavaFrame(lookup, reinterpret_cast<jmethodID>(&fake_method_storage));

    expectSkippedFor(lookup, mi, before, METHOD_RESOLVE_SKIPPED_JVMTI_ERROR);
    // The class signature fetched before the failing call is still freed.
    EXPECT_EQ(1, fake.counters.deallocate);
}

TEST_F(LookupResolveMethodJavaFrameTest, NullMethodNameCountsUnreadableName) {
    ScopedFakeJvmAndJni fake;
    fake.counters.borrow_method_name = true;
    fake.counters.borrowed_method_name = nullptr;
    VMTestAccessor::setJvmti(fake.jvmti());
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    int fake_method_storage = 0;
    SkipCounters before;

    MethodInfo* mi = resolveJavaFrame(lookup, reinterpret_cast<jmethodID>(&fake_method_storage));

    expectSkippedFor(lookup, mi, before, METHOD_RESOLVE_SKIPPED_UNREADABLE_NAME);
}

// A corrupt JVMTI string pointer, as seen in crash telemetry, is rejected
// without faulting and never handed to Deallocate(); its siblings still are.
TEST_F(LookupResolveMethodJavaFrameTest, UnreadableNamePointerIsSkippedAndNotDeallocated) {
    GuardedPage region;
    ASSERT_TRUE(region.ok());
    ScopedFakeJvmAndJni fake;
    fake.counters.borrow_method_name = true;
    fake.counters.borrowed_method_name = region.guardStart();
    VMTestAccessor::setJvmti(fake.jvmti());
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    int fake_method_storage = 0;
    SkipCounters before;

    MethodInfo* mi = resolveJavaFrame(lookup, reinterpret_cast<jmethodID>(&fake_method_storage));

    expectSkippedFor(lookup, mi, before, METHOD_RESOLVE_SKIPPED_UNREADABLE_NAME);
    EXPECT_EQ(0, fake.counters.deallocate_borrowed);
    EXPECT_EQ(2, fake.counters.deallocate);
}

TEST_F(LookupResolveMethodJavaFrameTest, J9OrdinaryClassResolves) {
    VMTestAccessor::setOpenJ9(true);
    VMTestAccessor::setHotspot(false);
    ScopedFakeJvmAndJni fake;
    VMTestAccessor::setJvmti(fake.jvmti());
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    int fake_method = 0;
    void* slot = &fake_method;
    SkipCounters before;

    MethodInfo* mi = resolveJavaFrame(lookup, reinterpret_cast<jmethodID>(&slot));

    ASSERT_NE(nullptr, mi);
    EXPECT_EQ(lookup.getSymbol("sampleMethod"), mi->_name);
    EXPECT_EQ(before.skipped, Counters::getCounter(JMETHODID_SKIPPED));
}

// The (jclass)-1 sentinel means "loader unloaded" only on J9; HotSpot resolves it.
TEST_F(LookupResolveMethodJavaFrameTest, MinusOneClassOutsideJ9Resolves) {
    VMTestAccessor::setOpenJ9(false);
    ScopedFakeJvmAndJni fake;
    fake.counters.override_declaring_class = true;
    fake.counters.declaring_class = reinterpret_cast<jclass>(-1);
    VMTestAccessor::setJvmti(fake.jvmti());
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    int fake_method_storage = 0;
    SkipCounters before;

    MethodInfo* mi = resolveJavaFrame(lookup, reinterpret_cast<jmethodID>(&fake_method_storage));

    ASSERT_NE(nullptr, mi);
    EXPECT_EQ(lookup.getSymbol("sampleMethod"), mi->_name);
    EXPECT_EQ(before.invalid_id, Counters::getCounter(METHOD_RESOLVE_SKIPPED_INVALID_ID));
    EXPECT_EQ(before.skipped, Counters::getCounter(JMETHODID_SKIPPED));
}

// A failed probe does not skip the probes after it, so a later unreadable
// pointer is also kept from Deallocate().
TEST_F(LookupResolveMethodJavaFrameTest, EveryUnreadableStringIsKeptFromDeallocate) {
    GuardedPage region;
    ASSERT_TRUE(region.ok());
    ScopedFakeJvmAndJni fake;
    fake.counters.borrow_method_name = true;
    fake.counters.borrowed_method_name = region.guardStart();
    fake.counters.borrow_method_sig = true;
    fake.counters.borrowed_method_sig = region.guardStart() + 8;
    VMTestAccessor::setJvmti(fake.jvmti());
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    int fake_method_storage = 0;
    SkipCounters before;

    MethodInfo* mi = resolveJavaFrame(lookup, reinterpret_cast<jmethodID>(&fake_method_storage));

    expectSkippedFor(lookup, mi, before, METHOD_RESOLVE_SKIPPED_UNREADABLE_NAME);
    EXPECT_EQ(0, fake.counters.deallocate_borrowed);
    EXPECT_EQ(1, fake.counters.deallocate);  // the class signature only
}

// The longest legal class signature: a 65535-byte name plus "L" and ";".
TEST_F(LookupResolveMethodJavaFrameTest, LongestLegalClassSignatureResolves) {
    ScopedFakeJvmAndJni fake;
    fake.counters.class_signature = "L" + std::string(65535, 'a') + ";";
    VMTestAccessor::setJvmti(fake.jvmti());
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    int fake_method_storage = 0;
    SkipCounters before;

    MethodInfo* mi = resolveJavaFrame(lookup, reinterpret_cast<jmethodID>(&fake_method_storage));

    ASSERT_NE(nullptr, mi);
    EXPECT_EQ(lookup.getSymbol("sampleMethod"), mi->_name);
    EXPECT_EQ(before.skipped, Counters::getCounter(JMETHODID_SKIPPED));
}

// One byte past the longest legal class signature: no NUL within the bound.
TEST_F(LookupResolveMethodJavaFrameTest, ClassSignaturePastTheBoundCountsUnreadableName) {
    ScopedFakeJvmAndJni fake;
    fake.counters.class_signature = "L" + std::string(65536, 'a') + ";";
    VMTestAccessor::setJvmti(fake.jvmti());
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    int fake_method_storage = 0;
    SkipCounters before;

    MethodInfo* mi = resolveJavaFrame(lookup, reinterpret_cast<jmethodID>(&fake_method_storage));

    expectSkippedFor(lookup, mi, before, METHOD_RESOLVE_SKIPPED_UNREADABLE_NAME);
}

// ---------------------------------------------------------------------------
// countUnresolvedFrame(): one count per written frame of an "<unloaded>" row
// or the shared unknown row, none for a resolved row.
// ---------------------------------------------------------------------------

struct FrameCounters {
    long long unloaded = Counters::getCounter(METHOD_RESOLVE_FRAMES_UNLOADED);
    long long unknown = Counters::getCounter(METHOD_RESOLVE_FRAMES_UNKNOWN);
};

TEST_F(LookupResolveMethodJavaFrameTest, UnloadedRowIsCountedOncePerFrame) {
    ScopedFakeJvmAndJni fake;
    fake.counters.declaring_class_error = JVMTI_ERROR_INVALID_METHODID;
    VMTestAccessor::setJvmti(fake.jvmti());
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    int fake_method_storage = 0;
    jmethodID method = reinterpret_cast<jmethodID>(&fake_method_storage);
    FrameCounters before;

    // Two traces that share one unresolved method: one row, two frames.
    MethodInfo* first = resolveJavaFrame(lookup, method);
    lookup.countUnresolvedFrame(first);
    MethodInfo* second = resolveJavaFrame(lookup, method);
    lookup.countUnresolvedFrame(second);

    ASSERT_EQ(first, second);
    FrameCounters after;
    EXPECT_EQ(before.unloaded + 2, after.unloaded);
    EXPECT_EQ(before.unknown, after.unknown);
}

TEST_F(LookupResolveMethodJavaFrameTest, UnknownRowIsCountedAsUnknown) {
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    FrameCounters before;

    MethodInfo* mi = resolveJavaFrame(lookup, nullptr);
    lookup.countUnresolvedFrame(mi);

    ASSERT_EQ(&lookup._unknown_method, mi);
    FrameCounters after;
    EXPECT_EQ(before.unknown + 1, after.unknown);
    EXPECT_EQ(before.unloaded, after.unloaded);
}

TEST_F(LookupResolveMethodJavaFrameTest, ResolvedRowIsNotCounted) {
    ScopedFakeJvmAndJni fake;
    VMTestAccessor::setJvmti(fake.jvmti());
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    int fake_method_storage = 0;
    FrameCounters before;

    MethodInfo* mi = resolveJavaFrame(lookup, reinterpret_cast<jmethodID>(&fake_method_storage));
    lookup.countUnresolvedFrame(mi);

    ASSERT_EQ(lookup.getSymbol("sampleMethod"), mi->_name);
    FrameCounters after;
    EXPECT_EQ(before.unloaded, after.unloaded);
    EXPECT_EQ(before.unknown, after.unknown);
}

// ---------------------------------------------------------------------------
// Recording::writeStackTrace(): the per-trace writer counts each written
// frame once, including a root it resolves a second time for the header.
// ---------------------------------------------------------------------------

// Owns a CallTrace with room for frames.size() frames (CallTrace ends in
// frames[1], so the storage is allocated past sizeof(CallTrace)).
class OwnedTrace {
public:
    OwnedTrace(u64 trace_id, const std::vector<ASGCT_CallFrame>& frames)
        : _storage(new char[sizeof(CallTrace) + frames.size() * sizeof(ASGCT_CallFrame)]) {
        _trace = new (_storage.get()) CallTrace(false, static_cast<int>(frames.size()), trace_id);
        for (size_t i = 0; i < frames.size(); i++) {
            _trace->frames[i] = frames[i];
        }
    }
    CallTrace* get() { return _trace; }

private:
    std::unique_ptr<char[]> _storage;
    CallTrace* _trace;
};

void countFlush(void* flush_ctx, Buffer*) {
    ++*static_cast<int*>(flush_ctx);
}

TEST_F(LookupResolveMethodJavaFrameTest, StackTraceWriterCountsEachUnresolvedFrameOnce) {
    ScopedFakeJvmAndJni fake;
    fake.counters.declaring_class_error = JVMTI_ERROR_INVALID_METHODID;  // jmethodID frames -> <unloaded>
    VMTestAccessor::setJvmti(fake.jvmti());
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);

    int fake_method_storage = 0;
    ASGCT_CallFrame unloaded{};
    unloaded.bci = FrameType::encode(FRAME_INTERPRETED, /*bci=*/0);
    unloaded.method_id = reinterpret_cast<jmethodID>(&fake_method_storage);
    ASGCT_CallFrame unknown{};  // null method_id -> shared unknown row
    unknown.bci = FrameType::encode(FRAME_INTERPRETED, /*bci=*/0);
    ASGCT_CallFrame resolved{};  // a native frame name: resolves, never counted
    resolved.bci = BCI_ERROR;
    resolved.native_function_name = "resolved_native_frame";

    // The root is the last frame. Trace 1 has an unknown root, trace 2 an
    // <unloaded> root, and both share the <unloaded> method.
    OwnedTrace trace1(1, {unloaded, resolved, unknown});
    OwnedTrace trace2(2, {resolved, unloaded});
    FrameCounters before;
    Buffer buffer1;
    Buffer buffer2;
    int flushes = 0;

    RecordingTestAccessor::writeStackTrace(&buffer1, trace1.get(), &lookup, countFlush, &flushes);
    RecordingTestAccessor::writeStackTrace(&buffer2, trace2.get(), &lookup, countFlush, &flushes);

    FrameCounters after;
    EXPECT_EQ(before.unloaded + 2, after.unloaded);
    EXPECT_EQ(before.unknown + 1, after.unknown);
    EXPECT_EQ(5, flushes) << "one flush check per written frame";
    // Header: trace id, truncated flag, frame count, each one byte here (values < 128).
    // These traces are not walker-truncated, so the flag comes from the root (the
    // last frame) alone: set for a non-entry Java root.
    const unsigned char* header1 = reinterpret_cast<const unsigned char*>(buffer1.data());
    EXPECT_EQ(1, header1[0]);
    EXPECT_EQ(0, header1[1]) << "trace 1's root is the native unknown row";
    EXPECT_EQ(3, header1[2]);
    const unsigned char* header2 = reinterpret_cast<const unsigned char*>(buffer2.data());
    EXPECT_EQ(2, header2[0]);
    EXPECT_EQ(1, header2[1]) << "trace 2's root is the <unloaded> Java row";
    EXPECT_EQ(2, header2[2]);
    // Every written row is marked referenced, so ageing keeps the map rows.
    // resolveMethod() returns the already-filled row and leaves the flag alone.
    EXPECT_TRUE(lookup.resolveMethod(unloaded)->_referenced);
    EXPECT_TRUE(lookup.resolveMethod(unknown)->_referenced);
    EXPECT_TRUE(lookup.resolveMethod(resolved)->_referenced);
}

// A one-frame trace: its only frame is also its root, resolved for the header.
TEST_F(LookupResolveMethodJavaFrameTest, StackTraceWriterResolvesTheRootOfAOneFrameTrace) {
    ScopedFakeJvmAndJni fake;
    fake.counters.declaring_class_error = JVMTI_ERROR_INVALID_METHODID;  // -> <unloaded>
    VMTestAccessor::setJvmti(fake.jvmti());
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    int fake_method_storage = 0;
    ASGCT_CallFrame unloaded{};
    unloaded.bci = FrameType::encode(FRAME_INTERPRETED, /*bci=*/0);
    unloaded.method_id = reinterpret_cast<jmethodID>(&fake_method_storage);
    OwnedTrace single(4, {unloaded});
    FrameCounters before;
    Buffer buffer;
    int flushes = 0;

    RecordingTestAccessor::writeStackTrace(&buffer, single.get(), &lookup, countFlush, &flushes);

    EXPECT_EQ(before.unloaded + 1, Counters::getCounter(METHOD_RESOLVE_FRAMES_UNLOADED));
    EXPECT_EQ(before.unknown, Counters::getCounter(METHOD_RESOLVE_FRAMES_UNKNOWN));
    EXPECT_EQ(1, flushes);
    // 3 header bytes (trace id, truncated flag, frame count) + 4 frame bytes (key,
    // line, bci, type), each one byte here; without a resolved root the flag is absent.
    ASSERT_EQ(7, buffer.offset()) << "the single frame must be resolved as the root";
    const unsigned char* header = reinterpret_cast<const unsigned char*>(buffer.data());
    EXPECT_EQ(4, header[0]);
    EXPECT_EQ(1, header[1]) << "truncated: the root is a non-entry Java row";
    EXPECT_EQ(1, header[2]);
}

// A trace with no frames writes only its header and resolves nothing.
TEST_F(LookupResolveMethodJavaFrameTest, StackTraceWriterWritesEmptyTraceWithoutResolving) {
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    OwnedTrace empty(3, {});
    FrameCounters before;
    Buffer buffer;
    int flushes = 0;

    RecordingTestAccessor::writeStackTrace(&buffer, empty.get(), &lookup, countFlush, &flushes);

    EXPECT_TRUE(method_map.empty());
    EXPECT_FALSE(lookup._unknown_method._mark) << "no frame may be resolved";
    FrameCounters after;
    EXPECT_EQ(before.unloaded, after.unloaded);
    EXPECT_EQ(before.unknown, after.unknown);
    EXPECT_EQ(0, flushes);
    ASSERT_EQ(2, buffer.offset()) << "trace id and frame count, no truncated flag without a root";
    const unsigned char* header = reinterpret_cast<const unsigned char*>(buffer.data());
    EXPECT_EQ(3, header[0]);
    EXPECT_EQ(0, header[1]);
}

// A row is re-filled in each chunk; one that resolves in a later chunk must
// no longer count as "<unloaded>".
TEST_F(LookupResolveMethodJavaFrameTest, SuccessfulRefillClearsUnloaded) {
    ScopedFakeJvmAndJni fake;
    fake.counters.declaring_class_error = JVMTI_ERROR_INVALID_METHODID;
    VMTestAccessor::setJvmti(fake.jvmti());
    MethodMap method_map;
    StringDictionary classes;
    Lookup lookup(/*rec=*/nullptr, &method_map, &classes);
    int fake_method_storage = 0;
    jmethodID method = reinterpret_cast<jmethodID>(&fake_method_storage);

    MethodInfo* mi = resolveJavaFrame(lookup, method);
    ASSERT_TRUE(mi->_unloaded);

    // Next chunk: writeMethods() cleared _mark, and the method now resolves.
    mi->_mark = false;
    fake.counters.declaring_class_error = JVMTI_ERROR_NONE;
    FrameCounters before;
    MethodInfo* again = resolveJavaFrame(lookup, method);
    lookup.countUnresolvedFrame(again);

    ASSERT_EQ(mi, again);
    EXPECT_FALSE(again->_unloaded);
    EXPECT_EQ(lookup.getSymbol("sampleMethod"), again->_name);
    EXPECT_EQ(before.unloaded, Counters::getCounter(METHOD_RESOLVE_FRAMES_UNLOADED));
}

} // namespace
