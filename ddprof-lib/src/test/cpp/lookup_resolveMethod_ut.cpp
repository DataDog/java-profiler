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

#include "../../main/cpp/flightRecorder.h"
#include "../../main/cpp/flightRecorder.inline.h"
#include "../../main/cpp/gtest_crash_handler.h"
#include "../../main/cpp/threadLocalData.inline.h"
#include "../../main/cpp/vmEntry.h"

#include <cstring>
#include <map>
#include <string>

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
    static JavaVM* getVm() { return VM::_vm; }
    static void setVm(JavaVM* vm) { VM::_vm = vm; }
    static jvmtiEnv* getJvmti() { return VM::_jvmti; }
    static void setJvmti(jvmtiEnv* env) { VM::_jvmti = env; }
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
        *declaring_class_ptr = reinterpret_cast<jclass>(&fake_class_storage);
        return JVMTI_ERROR_NONE;
    }
    static jvmtiError JNICALL getClassSignature(jvmtiEnv*, jclass, char** signature_ptr, char** generic_ptr) {
        *signature_ptr = dup("Lcom/example/Foo;");
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
        *name_ptr = dup("sampleMethod");
        *signature_ptr = dup("()V");
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
        s_instance->counters.deallocate++;
        free(mem); // matches the real JVMTI contract; a double-free here aborts the test
        return JVMTI_ERROR_NONE;
    }

    static ScopedFakeJvmAndJni* s_instance;

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
    }

    void TearDown() override {
        VMTestAccessor::setJvmti(_saved_jvmti);
        VMTestAccessor::setHotspot(_saved_hotspot);
        VMTestAccessor::setHotspotVersion(_saved_hotspot_version);
    }

    jvmtiEnv* _saved_jvmti;
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

} // namespace
