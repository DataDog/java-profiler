/*
 * Copyright 2026, Datadog, Inc
 */

#include <gtest/gtest.h>
#include "../../main/cpp/hotspot/hotspotSupport.h"
#include "../../main/cpp/gtest_crash_handler.h"
#include "../../main/cpp/hotspot/vmStructs.inline.h"

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
    static VMSymbol* captureVtableReceiver(HotspotStackFrame& frame, uintptr_t pc,
                                          uintptr_t sp, uintptr_t fp, StackWalkFeatures features) {
        return HotspotSupport::captureVtableReceiver(frame, pc, sp, fp, features);
    }

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

// Model an uncompressed oop -> Klass -> Symbol chain. These scoped overrides
// use the same VMStructs offsets as production, without requiring a live JVM.
class VMStructsTestAccessor {
    bool _has_class_names = VMStructs::_has_class_names;
    int _narrow_klass_shift = VMStructs::_narrow_klass_shift;
    int _oop_klass_offset = VMStructs::_oop_klass_offset;
    int _klass_name_offset = VMStructs::_klass_name_offset;
    uint64_t _klass_size = VMStructs::TYPE_SIZE_NAME(VMKlass);
    uint64_t _symbol_size = VMStructs::TYPE_SIZE_NAME(VMSymbol);
public:
    VMStructsTestAccessor() {
        VMStructs::_has_class_names = true;
        VMStructs::_narrow_klass_shift = -1;
        VMStructs::_oop_klass_offset = sizeof(uintptr_t);
        VMStructs::_klass_name_offset = 0;
        VMStructs::TYPE_SIZE_NAME(VMKlass) = sizeof(uintptr_t);
        VMStructs::TYPE_SIZE_NAME(VMSymbol) = sizeof(uintptr_t);
    }
    ~VMStructsTestAccessor() {
        VMStructs::_has_class_names = _has_class_names;
        VMStructs::_narrow_klass_shift = _narrow_klass_shift;
        VMStructs::_oop_klass_offset = _oop_klass_offset;
        VMStructs::_klass_name_offset = _klass_name_offset;
        VMStructs::TYPE_SIZE_NAME(VMKlass) = _klass_size;
        VMStructs::TYPE_SIZE_NAME(VMSymbol) = _symbol_size;
    }
    VMStructsTestAccessor(const VMStructsTestAccessor&) = delete;
    VMStructsTestAccessor& operator=(const VMStructsTestAccessor&) = delete;
    void disableClassNames() { VMStructs::_has_class_names = false; }
};

class VMTestAccessor {
    bool _hotspot = VM::_hotspot;
public:
    VMTestAccessor() { VM::_hotspot = true; }
    ~VMTestAccessor() { VM::_hotspot = _hotspot; }
    VMTestAccessor(const VMTestAccessor&) = delete;
    VMTestAccessor& operator=(const VMTestAccessor&) = delete;
};

class VtableReceiverCaptureTest : public ::testing::Test {
protected:
    VMTestAccessor _vm;
    VMStructsTestAccessor _layout;
    ucontext_t _ctx{};
#ifdef __APPLE__
    _STRUCT_MCONTEXT _mctx{};
#endif
    uintptr_t _symbol = 0;
    void* _klass = &_symbol;
    uintptr_t _oop[2] = {0, (uintptr_t)&_klass};
    StackWalkFeatures _features{};

    void SetUp() override {
#ifdef __APPLE__
        _ctx.uc_mcontext = &_mctx;
#endif
        HotspotStackFrame frame(&_ctx);
        frame.restore(0x1000, 0x2000, 0x3000);
        setReceiver((uintptr_t)_oop);
        _features.vtable_target = 1;
    }

    void setReceiver(uintptr_t receiver) {
#if defined(__APPLE__) && defined(__aarch64__)
        _ctx.uc_mcontext->__ss.__x[1] = receiver;
#elif defined(__APPLE__) && defined(__x86_64__)
        _ctx.uc_mcontext->__ss.__rsi = receiver;
#elif defined(__aarch64__)
        _ctx.uc_mcontext.regs[1] = receiver;
#elif defined(__x86_64__)
        _ctx.uc_mcontext.gregs[REG_RSI] = receiver;
#endif
    }

    VMSymbol* capture(uintptr_t pc = 0x1000, uintptr_t sp = 0x2000, uintptr_t fp = 0x3000) {
        HotspotStackFrame frame(&_ctx);
        return HotspotSupportTestAccessor::captureVtableReceiver(frame, pc, sp, fp, _features);
    }
};

TEST_F(VtableReceiverCaptureTest, CapturesRawSymbolFromInterruptedReceiver) {
    EXPECT_EQ(reinterpret_cast<VMSymbol*>(&_symbol), capture());
}

TEST_F(VtableReceiverCaptureTest, RejectsRecoveredCallerWithInterruptedArguments) {
    // Mimic java_ctx redirecting pc/sp/fp while the argument registers still
    // contain the interrupted leaf's receiver. Any changed coordinate rejects it.
    EXPECT_EQ(nullptr, capture(0x1004));
    EXPECT_EQ(nullptr, capture(0x1000, 0x2008));
    EXPECT_EQ(nullptr, capture(0x1000, 0x2000, 0x3010));
    HotspotStackFrame(&_ctx).restore(0x4000, 0x5000, 0x6000);
    EXPECT_EQ(nullptr, capture());
}

TEST_F(VtableReceiverCaptureTest, DisabledFeatureDoesNotReadRegisters) {
    _features.vtable_target = 0;
    HotspotStackFrame frame(nullptr);
    EXPECT_EQ(nullptr, HotspotSupportTestAccessor::captureVtableReceiver(frame, 0, 0, 0, _features));
}

TEST_F(VtableReceiverCaptureTest, MissingClassNamesDoesNotReadRegisters) {
    _layout.disableClassNames();
    HotspotStackFrame frame(nullptr);
    EXPECT_EQ(nullptr, HotspotSupportTestAccessor::captureVtableReceiver(frame, 0, 0, 0, _features));
}

TEST_F(VtableReceiverCaptureTest, NullReceiverKlassAndSymbolAreNotCaptured) {
    setReceiver(0);
    EXPECT_EQ(nullptr, capture());
    setReceiver((uintptr_t)_oop);
    _oop[1] = 0;
    EXPECT_EQ(nullptr, capture());
    _oop[1] = (uintptr_t)&_klass;
    _klass = nullptr;
    EXPECT_EQ(nullptr, capture());
}
