/*
 * Copyright 2026, Datadog, Inc
 */

#include <gtest/gtest.h>
#include "../../main/cpp/hotspot/hotspotSupport.h"
#include "../../main/cpp/gtest_crash_handler.h"

static constexpr char HOTSPOT_SUPPORT_TEST_NAME[] = "HotspotSupportTest";
class HotspotSupportGlobalSetup {
public:
    HotspotSupportGlobalSetup()  { installGtestCrashHandler<HOTSPOT_SUPPORT_TEST_NAME>(); }
    ~HotspotSupportGlobalSetup() { restoreDefaultSignalHandlers(); }
};
static HotspotSupportGlobalSetup hotspot_support_global_setup;

// ---------------------------------------------------------------------------
// HotspotSupportTestAccessor — friend of HotspotSupport, exposes the private
// loadMethodIDsIfNeededImpl() so the regression test for the <clinit>
// resolve() fallback (which now routes through it, instead of calling
// jvmti->GetClassMethods directly) can exercise it without a live JVM.
// ---------------------------------------------------------------------------
class HotspotSupportTestAccessor {
public:
    static bool loadMethodIDsIfNeededImpl(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass, bool load_all) {
        return HotspotSupport::loadMethodIDsIfNeededImpl(jvmti, jni, klass, load_all);
    }
};

// ---------------------------------------------------------------------------
// Mock JVMTI infrastructure. With load_all=true, loadMethodIDsIfNeededImpl()
// skips its hidden-class/system-classloader checks entirely and calls
// patchClassLoaderData() (a no-op here, since VM::hotspot_version() defaults
// to 0 -- not 8 -- in this gtest binary with no live JVM attached) followed
// by JVMSupport::loadMethodIDsImpl(), whose only JVMTI calls are
// GetClassMethods and Deallocate.
// ---------------------------------------------------------------------------
static int g_get_class_methods_calls = 0;

static jvmtiError JNICALL mock_GetClassMethods_ok(jvmtiEnv*, jclass, jint* method_count_ptr, jmethodID** methods_ptr) {
    g_get_class_methods_calls++;
    *method_count_ptr = 0;
    *methods_ptr = nullptr;
    return JVMTI_ERROR_NONE;
}
static jvmtiError JNICALL mock_Deallocate_noop(jvmtiEnv*, unsigned char*) {
    return JVMTI_ERROR_NONE;
}

class HotspotSupportLoadMethodIDsTest : public ::testing::Test {
protected:
    jvmtiInterface_1_ tbl{};
    _jvmtiEnv mock_jvmti{};

    void SetUp() override {
        g_get_class_methods_calls = 0;
        tbl = jvmtiInterface_1_{};
        tbl.GetClassMethods = &mock_GetClassMethods_ok;
        tbl.Deallocate = &mock_Deallocate_noop;
        mock_jvmti.functions = &tbl;
    }
};

TEST_F(HotspotSupportLoadMethodIDsTest, LoadAllSucceedsAndCallsGetClassMethodsOnce) {
    jclass fake_klass = reinterpret_cast<jclass>(0x1);

    bool result = HotspotSupportTestAccessor::loadMethodIDsIfNeededImpl(
        &mock_jvmti, /*jni=*/nullptr, fake_klass, /*load_all=*/true);

    EXPECT_TRUE(result);
    EXPECT_EQ(1, g_get_class_methods_calls)
        << "the <clinit> resolve() fallback must go through this exact path "
           "(load_all=true), which is what now applies patchClassLoaderData() "
           "before allocating jmethodIDs";
}
