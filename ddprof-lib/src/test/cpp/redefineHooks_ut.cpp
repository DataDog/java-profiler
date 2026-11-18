/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "../../main/cpp/hotspot/hotspotSupport.h"
#include "../../main/cpp/jvmSupport.h"
#include "../../main/cpp/vmEntry.h"

#include <cstdint>

// VM::RedefineClassesHook / RetransformClassesHook wrap the JVMTI functions
// of the same name. Whatever the caller passes, the hooks must let the
// original validate it before they touch it: a positive count with a null
// array is JVMTI_ERROR_NULL_POINTER, and an element that is not an instance
// class is rejected by JVMTI too. These tests replace the originals with
// recording stubs and check that the hooks forward such calls untouched,
// without dereferencing anything.

class VMTestAccessor {
public:
    using RedefineFn = jvmtiError(JNICALL*)(jvmtiEnv*, jint, const jvmtiClassDefinition*);
    using RetransformFn = jvmtiError(JNICALL*)(jvmtiEnv*, jint, const jclass*);

    static bool getHotspot() { return VM::_hotspot; }
    static void setHotspot(bool v) { VM::_hotspot = v; }
    static JavaVM* getVm() { return VM::_vm; }
    static void setVm(JavaVM* vm) { VM::_vm = vm; }
    static RedefineFn getRedefine() { return VM::_orig_RedefineClasses; }
    static void setRedefine(RedefineFn f) { VM::_orig_RedefineClasses = f; }
    static RetransformFn getRetransform() { return VM::_orig_RetransformClasses; }
    static void setRetransform(RetransformFn f) { VM::_orig_RetransformClasses = f; }
};

class JVMSupportTestAccessor {
public:
    using LoadState = JVMSupport::JMethodIDLoadStats;
    static LoadState getLoadState() { return JVMSupport::getLoadState(); }
    static void setLoadState(LoadState s) { JVMSupport::setLoadState(s); }
    static constexpr LoadState LazyLoaded() { return JVMSupport::Lazy_loaded; }
    static constexpr LoadState FullyLoaded() { return JVMSupport::Fully_loaded; }
};

class HotspotSupportTestAccessor {
public:
    static int untrackedCalls() { return HotspotSupport::_untracked_redefinition_calls; }
    static void setLazyUsed(bool used) { HotspotSupport::_lazy_used = used; }
};

namespace {

struct Calls {
    int redefine = 0;
    int retransform = 0;
    int get_long_field = 0;    // VMKlass::fromJavaClass()
    int get_class_methods = 0; // jmethodID preload
    jint last_count = 0;
    const void* last_array = nullptr;
    jint class_status = JVMTI_CLASS_STATUS_PREPARED;
    jvmtiError class_status_error = JVMTI_ERROR_NONE;
    int untracked_during_call = -1;  // untracked redefinition calls seen by the original
};
Calls* g_calls = nullptr;

jvmtiError JNICALL origRedefine(jvmtiEnv*, jint count, const jvmtiClassDefinition* defs) {
    g_calls->redefine++;
    g_calls->untracked_during_call = HotspotSupportTestAccessor::untrackedCalls();
    g_calls->last_count = count;
    g_calls->last_array = defs;
    return count > 0 && defs == nullptr ? JVMTI_ERROR_NULL_POINTER : JVMTI_ERROR_INVALID_CLASS;
}

jvmtiError JNICALL origRetransform(jvmtiEnv*, jint count, const jclass* classes) {
    g_calls->retransform++;
    g_calls->untracked_during_call = HotspotSupportTestAccessor::untrackedCalls();
    g_calls->last_count = count;
    g_calls->last_array = classes;
    return count > 0 && classes == nullptr ? JVMTI_ERROR_NULL_POINTER : JVMTI_ERROR_INVALID_CLASS;
}

jvmtiError JNICALL getClassStatus(jvmtiEnv*, jclass, jint* status) {
    *status = g_calls->class_status;
    return g_calls->class_status_error;
}

jvmtiError JNICALL getClassMethods(jvmtiEnv*, jclass, jint* count, jmethodID** methods) {
    g_calls->get_class_methods++;
    *count = 0;
    *methods = nullptr;
    return JVMTI_ERROR_NONE;
}

jvmtiError JNICALL deallocate(jvmtiEnv*, unsigned char*) { return JVMTI_ERROR_NONE; }

jlong JNICALL getLongField(JNIEnv*, jobject, jfieldID) {
    g_calls->get_long_field++;
    return 0;
}

JNIEnv_* g_env = nullptr;
jint JNICALL getEnv(JavaVM*, void** penv, jint) {
    *penv = g_env;
    return JNI_OK;
}

} // namespace

class RedefineHooksTest : public ::testing::TestWithParam<bool> {
protected:
    Calls _calls;
    jvmtiInterface_1_ _jvmti_tbl{};
    _jvmtiEnv _jvmti{};
    JNINativeInterface_ _jni_tbl{};
    JNIEnv_ _jni{};
    JNIInvokeInterface_ _vm_tbl{};
    JavaVM_ _vm{};

    bool _saved_hotspot = false;
    JavaVM* _saved_vm = nullptr;
    VMTestAccessor::RedefineFn _saved_redefine = nullptr;
    VMTestAccessor::RetransformFn _saved_retransform = nullptr;
    JVMSupportTestAccessor::LoadState _saved_state{};

    // The parameter: run the hooks in fjmethodid=lazy (true) or the default
    // full preload mode (false). Both must forward invalid calls untouched.
    static bool lazy() { return GetParam(); }

    void SetUp() override {
        g_calls = &_calls;
        _jvmti_tbl.GetClassStatus = &getClassStatus;
        _jvmti_tbl.GetClassMethods = &getClassMethods;
        _jvmti_tbl.Deallocate = &deallocate;
        _jvmti.functions = &_jvmti_tbl;
        _jni_tbl.GetLongField = &getLongField;
        _jni.functions = &_jni_tbl;
        g_env = &_jni;
        _vm_tbl.GetEnv = &getEnv;
        _vm.functions = &_vm_tbl;

        _saved_hotspot = VMTestAccessor::getHotspot();
        _saved_vm = VMTestAccessor::getVm();
        _saved_redefine = VMTestAccessor::getRedefine();
        _saved_retransform = VMTestAccessor::getRetransform();
        _saved_state = JVMSupportTestAccessor::getLoadState();
        VMTestAccessor::setHotspot(true);
        VMTestAccessor::setVm(reinterpret_cast<JavaVM*>(&_vm));
        VMTestAccessor::setRedefine(&origRedefine);
        VMTestAccessor::setRetransform(&origRetransform);
        JVMSupportTestAccessor::setLoadState(lazy() ? JVMSupportTestAccessor::LazyLoaded()
                                                    : JVMSupportTestAccessor::FullyLoaded());
    }

    void TearDown() override {
        JVMSupportTestAccessor::setLoadState(_saved_state);
        VMTestAccessor::setRetransform(_saved_retransform);
        VMTestAccessor::setRedefine(_saved_redefine);
        VMTestAccessor::setVm(_saved_vm);
        VMTestAccessor::setHotspot(_saved_hotspot);
        g_env = nullptr;
        g_calls = nullptr;
    }
};

TEST_P(RedefineHooksTest, RedefineWithNullArrayIsForwardedUntouched) {
    EXPECT_EQ(JVMTI_ERROR_NULL_POINTER, VM::RedefineClassesHook(&_jvmti, 2, nullptr));
    EXPECT_EQ(1, _calls.redefine);
    EXPECT_EQ(2, _calls.last_count);
    EXPECT_EQ(nullptr, _calls.last_array);
}

TEST_P(RedefineHooksTest, RetransformWithNullArrayIsForwardedUntouched) {
    EXPECT_EQ(JVMTI_ERROR_NULL_POINTER, VM::RetransformClassesHook(&_jvmti, 3, nullptr));
    EXPECT_EQ(1, _calls.retransform);
    EXPECT_EQ(3, _calls.last_count);
    EXPECT_EQ(nullptr, _calls.last_array);
}

// An element JVMTI does not accept as a class (JVMTI_ERROR_INVALID_CLASS) is
// neither looked up as a Klass* nor preloaded, before or after the call.
TEST_P(RedefineHooksTest, NonClassElementIsNotTouched) {
    _calls.class_status_error = JVMTI_ERROR_INVALID_CLASS;
    int not_a_class = 0;
    jclass classes[] = {reinterpret_cast<jclass>(&not_a_class)};
    jvmtiClassDefinition defs[] = {{classes[0], 0, nullptr}};

    EXPECT_EQ(JVMTI_ERROR_INVALID_CLASS, VM::RetransformClassesHook(&_jvmti, 1, classes));
    EXPECT_EQ(JVMTI_ERROR_INVALID_CLASS, VM::RedefineClassesHook(&_jvmti, 1, defs));
    EXPECT_EQ(0, _calls.get_long_field);
    EXPECT_EQ(0, _calls.get_class_methods);
}

// Array classes have no InstanceKlass fields to read; JVMTI rejects them as
// unmodifiable, and the hooks must not inspect them either.
TEST_P(RedefineHooksTest, ArrayClassElementIsNotTouched) {
    _calls.class_status = JVMTI_CLASS_STATUS_ARRAY;
    int array_class = 0;
    jclass classes[] = {reinterpret_cast<jclass>(&array_class)};

    VM::RetransformClassesHook(&_jvmti, 1, classes);
    EXPECT_EQ(1, _calls.retransform);
    EXPECT_EQ(0, _calls.get_long_field);
    EXPECT_EQ(0, _calls.get_class_methods);
}

// A call that starts before lazy mode is counted while it runs, so that the
// first lazy start can wait for it (its classes are not marked); one that
// starts after is tracked and not counted.
TEST_P(RedefineHooksTest, CallsBeforeLazyModeAreCountedWhileTheyRun) {
    jclass classes[] = {nullptr};
    jvmtiClassDefinition defs[] = {{nullptr, 0, nullptr}};
    HotspotSupportTestAccessor::setLazyUsed(false);
    VM::RetransformClassesHook(&_jvmti, 1, classes);
    EXPECT_EQ(1, _calls.untracked_during_call);
    VM::RedefineClassesHook(&_jvmti, 1, defs);
    EXPECT_EQ(1, _calls.untracked_during_call);
    EXPECT_EQ(0, HotspotSupportTestAccessor::untrackedCalls());

    HotspotSupportTestAccessor::setLazyUsed(true);
    VM::RetransformClassesHook(&_jvmti, 1, classes);
    EXPECT_EQ(0, _calls.untracked_during_call);
    VM::RedefineClassesHook(&_jvmti, 1, defs);
    EXPECT_EQ(0, _calls.untracked_during_call);
    HotspotSupportTestAccessor::setLazyUsed(false);
}

// A null element inside a valid array is skipped as before.
TEST_P(RedefineHooksTest, NullElementIsSkipped) {
    jclass classes[] = {nullptr};
    VM::RetransformClassesHook(&_jvmti, 1, classes);
    EXPECT_EQ(1, _calls.retransform);
    EXPECT_EQ(0, _calls.get_long_field);
}

INSTANTIATE_TEST_SUITE_P(Mode, RedefineHooksTest, ::testing::Bool(),
                         [](const ::testing::TestParamInfo<bool>& info) {
                             return info.param ? "Lazy" : "FullPreload";
                         });
