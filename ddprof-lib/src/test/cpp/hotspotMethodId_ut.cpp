/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "../../main/cpp/counters.h"
#include "../../main/cpp/flightRecorder.h"
#include "../../main/cpp/hotspot/hotspotSupport.h"
#include "../../main/cpp/hotspot/vmStructs.h"
#include "../../main/cpp/os.h"
#include "../../main/cpp/profiler.h"
#include "../../main/cpp/threadLocalData.inline.h"
#include "../../main/cpp/vmEntry.h"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <new>
#include <string>

#ifdef __linux__
#include <sys/mman.h>
#include <unistd.h>
#endif

// Test-only friend accessor for VM internals. It exists solely so this test
// can exercise HotSpot's rejected-jmethodID handling.
class VMTestAccessor {
public:
    static bool getHotspot() { return VM::_hotspot; }
    static void setHotspot(bool value) { VM::_hotspot = value; }
    static JavaVM* getVm() { return VM::_vm; }
    static void setVm(JavaVM* vm) { VM::_vm = vm; }
};

// Test-only friend accessor for VMStructs protected static offsets.
// Allows the test to set up fake VM metadata layouts and exercise
// VMMethod::id() without a live JVM.
class VMStructsTestAccessor {
public:
    struct Offsets {
        int method_constmethod;
        int constmethod_constants;
        int constmethod_idnum;
        int pool_holder;
        int jmethod_ids;
    };

    VMStructsTestAccessor(const Offsets& o) {
        _saved = _save();
        VMStructs::_method_constmethod_offset = o.method_constmethod;
        VMStructs::_constmethod_constants_offset = o.constmethod_constants;
        VMStructs::_constmethod_idnum_offset = o.constmethod_idnum;
        VMStructs::_pool_holder_offset = o.pool_holder;
        VMStructs::_jmethod_ids_offset = o.jmethod_ids;
    }

    ~VMStructsTestAccessor() { _restore(_saved); }

    // Offsets beyond the id() set, needed to walk a fake Method* all the way to
    // its name/signature/class Symbols the way HotspotSupport::resolve() does.
    struct SymbolOffsets {
        int constmethod_name_index;
        int constmethod_sig_index;
        int klass_name;
        int symbol_length;
        int symbol_body;
    };

    // cast_or_null() / VMConstantPool::base() need non-zero type sizes, which
    // normally come from gHotSpotVMTypes and therefore stay 0 without a live
    // JVM. Every field is asserted > 0 by the code under test, so tests that
    // reach cast_or_null must set them.
    struct TypeSizes {
        uint64_t method;
        uint64_t const_method;
        uint64_t constant_pool;
        uint64_t klass;
        uint64_t symbol;
    };

    // Scoped override for the symbol-walk offsets and the type sizes, kept
    // separate from the ctor above so the existing id() tests are unaffected.
    class SymbolLayout {
    public:
        SymbolLayout(const SymbolOffsets& o, const TypeSizes& t) {
            _saved_offsets = {
                VMStructs::_constmethod_name_index_offset,
                VMStructs::_constmethod_sig_index_offset,
                VMStructs::_klass_name_offset,
                VMStructs::_symbol_length_offset,
                VMStructs::_symbol_body_offset,
            };
            _saved_sizes = {
                VMStructs::TYPE_SIZE_NAME(VMMethod),
                VMStructs::TYPE_SIZE_NAME(VMConstMethod),
                VMStructs::TYPE_SIZE_NAME(VMConstantPool),
                VMStructs::TYPE_SIZE_NAME(VMKlass),
                VMStructs::TYPE_SIZE_NAME(VMSymbol),
            };
            _apply(o, t);
        }

        ~SymbolLayout() { _apply(_saved_offsets, _saved_sizes); }

    private:
        SymbolOffsets _saved_offsets;
        TypeSizes _saved_sizes;

        static void _apply(const SymbolOffsets& o, const TypeSizes& t) {
            VMStructs::_constmethod_name_index_offset = o.constmethod_name_index;
            VMStructs::_constmethod_sig_index_offset = o.constmethod_sig_index;
            VMStructs::_klass_name_offset = o.klass_name;
            VMStructs::_symbol_length_offset = o.symbol_length;
            VMStructs::_symbol_body_offset = o.symbol_body;
            VMStructs::TYPE_SIZE_NAME(VMMethod) = t.method;
            VMStructs::TYPE_SIZE_NAME(VMConstMethod) = t.const_method;
            VMStructs::TYPE_SIZE_NAME(VMConstantPool) = t.constant_pool;
            VMStructs::TYPE_SIZE_NAME(VMKlass) = t.klass;
            VMStructs::TYPE_SIZE_NAME(VMSymbol) = t.symbol;
        }
    };

private:
    struct SavedOffsets {
        int method_constmethod;
        int constmethod_constants;
        int constmethod_idnum;
        int pool_holder;
        int jmethod_ids;
    };

    SavedOffsets _saved;

    static SavedOffsets _save() {
        return {
            VMStructs::_method_constmethod_offset,
            VMStructs::_constmethod_constants_offset,
            VMStructs::_constmethod_idnum_offset,
            VMStructs::_pool_holder_offset,
            VMStructs::_jmethod_ids_offset,
        };
    }

    static void _restore(const SavedOffsets& s) {
        VMStructs::_method_constmethod_offset = s.method_constmethod;
        VMStructs::_constmethod_constants_offset = s.constmethod_constants;
        VMStructs::_constmethod_idnum_offset = s.constmethod_idnum;
        VMStructs::_pool_holder_offset = s.pool_holder;
        VMStructs::_jmethod_ids_offset = s.jmethod_ids;
    }
};

class HotspotMethodIdVMHotspotGuard {
private:
    bool _saved;

public:
    HotspotMethodIdVMHotspotGuard() : _saved(VMTestAccessor::getHotspot()) {
        VMTestAccessor::setHotspot(true);
    }

    ~HotspotMethodIdVMHotspotGuard() {
        VMTestAccessor::setHotspot(_saved);
    }
};

TEST(HotspotMethodIdTest, RejectedMethodIdStaysNonRawAndResolvesToUnknown) {
    HotspotMethodIdVMHotspotGuard hotspot;
    ASGCT_CallFrame frame{};

    // The pointer is intentionally invalid. A rejected jmethodID must retain
    // only its sentinel and must not preserve this Method* for dump-time use.
    HotspotSupport::fillJavaFrame(frame, FRAME_JIT_COMPILED, 17,
                                  JMETHODID_NOT_WALKABLE,
                                  reinterpret_cast<VMMethod*>(1));

    EXPECT_FALSE(FrameType::isRawPointer(frame.bci));
    EXPECT_EQ(frame.method_id, JMETHODID_NOT_WALKABLE);

    StringDictionary classes;
    MethodMap methods;
    Lookup lookup(nullptr, &methods, &classes);
    MethodInfo* info = lookup.resolveMethod(frame);

    ASSERT_NE(info, nullptr);
    EXPECT_EQ(info->_type, FRAME_NATIVE);
    // The sentinel is normalised to a null method_id, which resolves to the
    // shared unknown row. That row lives outside the MethodMap (see
    // Lookup::_unknown_method), so nothing is inserted for this frame.
    EXPECT_EQ(info, &lookup._unknown_method);
    EXPECT_TRUE(methods.empty());
    EXPECT_NE(info->_key, 0U);  // still needs a pool id to be referenceable}
}

// ---------------------------------------------------------------------------
// VMMethod::id() cache-state tests
//
// These tests construct fake in-memory VM metadata (VMMethod → ConstMethod →
// ConstantPool → Klass → jmethodID cache) and verify that id() returns the
// correct value for each cache state. The offsets are set to fixed values so
// the fake buffers can be simple structs with fields at known positions.
// ---------------------------------------------------------------------------

namespace {

// Offsets used across all id() tests. Fields are at fixed positions in the
// fake structs below.
constexpr VMStructsTestAccessor::Offsets ID_OFFSETS = {
    /*method_constmethod*/   0,
    /*constmethod_constants*/ 0,
    /*constmethod_idnum*/     8,
    /*pool_holder*/           0,
    /*jmethod_ids*/           0,
};

// Fake VMMethod: a pointer to ConstMethod at offset 0.
struct FakeVMMethod {
    void* const_method;
};

// Fake VMConstMethod: pointer to ConstantPool at offset 0, idnum at offset 8.
struct FakeConstMethod {
    void* cpool;
    uint16_t idnum;
    uint16_t pad;
};

// Fake VMConstantPool: pointer to VMKlass at offset 0.
struct FakeConstantPool {
    void* holder;
};

// Fake VMKlass: pointer to jmethodID array at offset 0.
struct FakeKlass {
    void* ids;
};

// jmethodID cache array: [length (i32), padding, id[0], id[1], ...]
// ids[0] is the length (read as int32_t), ids[num+1] is the jmethodID.
struct FakeIdCache {
    int32_t len;
    int32_t pad;
    jmethodID slots[4];
};

// Bundles all fake structures for a single test case.
struct FakeMetadata {
    alignas(sizeof(void*)) FakeVMMethod method;
    alignas(sizeof(void*)) FakeConstMethod const_method;
    alignas(sizeof(void*)) FakeConstantPool cpool;
    alignas(sizeof(void*)) FakeKlass klass;
    alignas(sizeof(void*)) FakeIdCache id_cache;

    void link(uint16_t idnum, int32_t cache_len) {
        method.const_method = &const_method;
        const_method.cpool = &cpool;
        const_method.idnum = idnum;
        cpool.holder = &klass;
        klass.ids = &id_cache;
        id_cache.len = cache_len;
        // Zero the slots so SafeAccess::loadPtr returns the default.
        memset(id_cache.slots, 0, sizeof(id_cache.slots));
    }
};

} // namespace

TEST(HotspotMethodIdTest, IdReturnsNullptrForUnprimedCache) {
    HotspotMethodIdVMHotspotGuard hotspot;
    VMStructsTestAccessor offsets(ID_OFFSETS);

    FakeMetadata md{};
    md.method.const_method = &md.const_method;
    md.const_method.cpool = &md.cpool;
    md.const_method.idnum = 0;
    md.cpool.holder = &md.klass;
    md.klass.ids = nullptr; // deliberately unprimed

    VMMethod* vm_method = reinterpret_cast<VMMethod*>(&md.method);
    EXPECT_EQ(vm_method->id(), nullptr);
}

TEST(HotspotMethodIdTest, IdReturnsNullptrForShrunkCache) {
    HotspotMethodIdVMHotspotGuard hotspot;
    VMStructsTestAccessor offsets(ID_OFFSETS);

    FakeMetadata md{};
    md.link(/*idnum*/ 2, /*cache_len*/ 1); // num >= len → post-invalidation

    VMMethod* vm_method = reinterpret_cast<VMMethod*>(&md.method);
    // id() returns nullptr (not the sentinel) so that fillJavaFrame can decide
    // based on fjmethodid whether to use the raw Method* fallback.
    EXPECT_EQ(vm_method->id(), nullptr);
}

TEST(HotspotMethodIdTest, IdReturnsNullForEmptySlot) {
    HotspotMethodIdVMHotspotGuard hotspot;
    VMStructsTestAccessor offsets(ID_OFFSETS);

    FakeMetadata md{};
    md.link(/*idnum*/ 0, /*cache_len*/ 2); // num < len, slot value is null
    // SafeAccess::loadPtr reads the actual value (null) from valid memory;
    // the JMETHODID_NOT_WALKABLE default only fires on a fault.

    VMMethod* vm_method = reinterpret_cast<VMMethod*>(&md.method);
    EXPECT_EQ(vm_method->id(), nullptr);
}

TEST(HotspotMethodIdTest, IdReturnsValidIdForPopulatedSlot) {
    HotspotMethodIdVMHotspotGuard hotspot;
    VMStructsTestAccessor offsets(ID_OFFSETS);

    FakeMetadata md{};
    md.link(/*idnum*/ 1, /*cache_len*/ 3);
    jmethodID expected = reinterpret_cast<jmethodID>(0x1234);
    md.id_cache.slots[1] = expected; // ids[num+1] = ids[2]

    VMMethod* vm_method = reinterpret_cast<VMMethod*>(&md.method);
    EXPECT_EQ(vm_method->id(), expected);
}

#ifdef __linux__

// ---------------------------------------------------------------------------
// HotspotSupport::resolve() crash protection
//
// resolve() turns a raw Method* captured at sample time into a jmethodID on the
// JFR dump thread. GC or class unloading can free that metadata in between, so
// every dereference in the walk (constMethod -> constants -> name/signature ->
// holder -> klass->name, then Symbol length/body) can fault. resolve() installs
// a sigsetjmp landing pad via JmpCtxScope so Profiler::checkFault() recovers and
// resolve() reports the method as unresolved (nullptr) instead of taking the JVM
// down mid-dump.
//
// checkFault() gates recovery on the faulting pc lying inside the profiler
// library's address range. setupSignalHandlers() never runs in this gtest binary
// (the library sources are linked straight into the executable), so the range
// stays (0, 0) and checkFault takes its "not initialized" fallback, recovering
// unconditionally without ever evaluating the comparison. SetUp() therefore
// installs a fabricated range via the UNIT_TEST-only
// Profiler::setAddressRangeForTest(), anchored on two exported symbols from
// hotspotSupport.cpp so it brackets that translation unit's whole text --
// including the file-static helpers, whose addresses a test cannot take. This
// covers the acceptance half of the gate only; the rejection half is already
// tested for real by
// StackWalkerCrashRecoveryTest.CheckFaultRejectsFaultOutsideProfilerRange.
//
// In a DEBUG build these tests additionally pin the crashProtectionActive()
// interaction (vmStructs.h:33-45): VMStructs::at() asserts
// `crashProtectionActive() || SafeAccess::isReadable(ptr)`, which without an
// installed jmp ctx raises SIGABRT -- uncatchable by crash protection -- so
// DEBUG builds used to die here where release survived. Passing in both
// gtestDebug_ and gtestRelease_ is the evidence that the two now converge.
// ---------------------------------------------------------------------------

namespace {

// Two adjacent pages; the second is PROT_NONE. Fake metadata lives at the start
// of the first, so an offset of kPageSize() lands on the guard page.
// Must be the real OS page size, not a hardcoded 4096: mmap()/mprotect() need
// page-aligned addresses and sizes, and on arm64 Linux the page size can be
// 16384 or 65536, not 4096. A function rather than a namespace-scope const:
// OS::page_size is itself a dynamically-initialized static in another
// translation unit, and cross-TU static init order is unspecified, so caching
// it in another static here could read it before it's set. Calling through a
// function defers the read to test-run time, well after all static init.
size_t kPageSize() { return OS::page_size; }

// Layout of the fake metadata used by the resolve() tests. Sizes are the values
// VMConstantPool::base() and cast_or_null() need; they only have to be non-zero
// and consistent with the struct layouts below.
constexpr VMStructsTestAccessor::TypeSizes RESOLVE_TYPE_SIZES = {
    /*method*/        sizeof(void*),
    /*const_method*/  2 * sizeof(void*),
    /*constant_pool*/ sizeof(void*),   // base() = cpool + this, i.e. &symbols[0]
    /*klass*/         sizeof(void*),
    /*symbol*/        8,
};

constexpr VMStructsTestAccessor::SymbolOffsets RESOLVE_SYMBOL_OFFSETS = {
    /*constmethod_name_index*/ 8,
    /*constmethod_sig_index*/  10,
    /*klass_name*/             0,
    /*symbol_length*/          0,
    /*symbol_body*/            2,
};

// jmethod_ids deliberately points at a separate, always-null field rather than
// aliasing klass_name at offset 0: VMMethod::id() reads the jmethodID cache
// through that offset, and pointing it at the class-name Symbol would make id()
// read a length and a "jmethodID" out of the Symbol's body. That value passes
// isValidJMethodID(), so resolve() would early-return with garbage and never
// reach the symbol-copy code these tests are about.
constexpr VMStructsTestAccessor::Offsets RESOLVE_OFFSETS = {
    /*method_constmethod*/    0,
    /*constmethod_constants*/ 0,
    /*constmethod_idnum*/     12,
    /*pool_holder*/           0,
    /*jmethod_ids*/           sizeof(void*),
};

// Mirrors RESOLVE_*_OFFSETS above. `symbols` must directly follow `holder`
// because VMConstantPool::base() is `this + VMConstantPool::type_size()`.
struct ResolveFakes {
    struct Method {
        void* const_method;
    } method;
    struct ConstMethod {
        void* cpool;
        uint16_t name_index;
        uint16_t sig_index;
        uint16_t idnum;
        uint16_t pad;
    } const_method;
    struct ConstantPool {
        void* holder;
        intptr_t symbols[4];
    } cpool;
    struct Klass {
        void* name_symbol;   // klass_name offset 0
        void* jmethod_ids;   // stays null so VMMethod::id() reports "no cache"
    } klass;
    struct Symbol {
        uint16_t length;
        char body[64];
    } name_sym, sig_sym, klass_sym;

    // Wires the chain up so resolve() walks Method -> ConstMethod -> ConstantPool
    // -> {name, signature} Symbols and ConstantPool -> Klass -> class-name Symbol.
    void link() {
        method.const_method = &const_method;
        const_method.cpool = &cpool;
        const_method.name_index = 1;
        const_method.sig_index = 2;
        const_method.idnum = 0;
        cpool.holder = &klass;
        cpool.symbols[1] = (intptr_t)&name_sym;
        cpool.symbols[2] = (intptr_t)&sig_sym;
        klass.name_symbol = &klass_sym;
    }

    static void setSymbol(Symbol& s, const char* text) {
        s.length = (uint16_t)strlen(text);
        memcpy(s.body, text, s.length);
    }
};

// Minimal fake JavaVM/JNIEnv so HotspotSupport::resolve()'s unprotected JNI
// phase (lookupMethodIdViaJni) can run to completion without a live JVM.
// FindClass always reports success against an opaque, never-dereferenced
// jclass; GetMethodID/GetStaticMethodID record the name/signature they were
// called with and report "not found" -- the same real-world path resolve()
// takes for a method it can't find -- so nothing beyond that is exercised.
// Recording the arguments is what lets a test prove the malloc-fallback path
// copied the right bytes, rather than just checking resolve() didn't crash.
class ScopedFakeJni {
public:
    ScopedFakeJni() : _saved_vm(VMTestAccessor::getVm()) {
        _jni_tbl = JNINativeInterface_{};
        _jni_tbl.FindClass = &findClass;
        _jni_tbl.ExceptionClear = &exceptionClear;
        _jni_tbl.GetMethodID = &getMethodId;
        _jni_tbl.GetStaticMethodID = &getMethodId;
        _jni_tbl.DeleteLocalRef = &deleteLocalRef;
        _jni_env.functions = &_jni_tbl;

        _vm_tbl = JNIInvokeInterface_{};
        _vm_tbl.GetEnv = &getEnv;
        _vm.functions = &_vm_tbl;

        s_instance = this;
        VMTestAccessor::setVm(reinterpret_cast<JavaVM*>(&_vm));
    }

    ~ScopedFakeJni() {
        VMTestAccessor::setVm(_saved_vm);
        s_instance = nullptr;
    }

    int getMethodIdCalls() const { return _get_method_id_calls; }
    const std::string& lastMethodName() const { return _last_method_name; }
    const std::string& lastMethodSignature() const { return _last_method_sig; }

private:
    static jclass JNICALL findClass(JNIEnv*, const char*) {
        return reinterpret_cast<jclass>(&s_instance->_fake_class);
    }
    static jmethodID JNICALL getMethodId(JNIEnv*, jclass, const char* name, const char* sig) {
        s_instance->_get_method_id_calls++;
        s_instance->_last_method_name = name != nullptr ? name : "";
        s_instance->_last_method_sig = sig != nullptr ? sig : "";
        return nullptr;
    }
    static void JNICALL exceptionClear(JNIEnv*) {}
    static void JNICALL deleteLocalRef(JNIEnv*, jobject) {}
    static jint JNICALL getEnv(JavaVM*, void** penv, jint) {
        *penv = reinterpret_cast<JNIEnv*>(&s_instance->_jni_env);
        return JNI_OK;
    }

    static ScopedFakeJni* s_instance;

    JavaVM* _saved_vm;
    JNINativeInterface_ _jni_tbl{};
    JNIEnv_ _jni_env{};
    JNIInvokeInterface_ _vm_tbl{};
    JavaVM_ _vm{};
    int _fake_class = 0;  // address-only sentinel; never dereferenced
    int _get_method_id_calls = 0;
    std::string _last_method_name;
    std::string _last_method_sig;
};
ScopedFakeJni* ScopedFakeJni::s_instance = nullptr;

} // namespace

class HotspotResolveCrashProtectionTest : public ::testing::Test {
protected:
    // Generous enough to bracket hotspotSupport.cpp's compiled text in any build
    // config, while staying far below the distance to unrelated libraries.
    static constexpr uintptr_t kRangeMargin = 512 * 1024;

    void SetUp() override {
        ProfiledThread::initCurrentThread();
        _pt = ProfiledThread::current();
        ASSERT_NE(nullptr, _pt);
        ASSERT_FALSE(_pt->isProtected());

        _orig_segv = OS::replaceSigsegvHandler(Profiler::segvHandler);
        _orig_bus = OS::replaceSigbusHandler(Profiler::busHandler);

        _region = mmap(nullptr, 2 * kPageSize(), PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        ASSERT_NE(MAP_FAILED, _region);
        ASSERT_EQ(0, mprotect((char*)_region + kPageSize(), kPageSize(), PROT_NONE));

        // Two exported symbols from hotspotSupport.cpp, far apart in that TU.
        uintptr_t a = (uintptr_t)&HotspotSupport::resolve;
        uintptr_t b = (uintptr_t)&HotspotSupport::walkJavaStack;
        _range_lo = std::min(a, b) - kRangeMargin;
        _range_hi = std::max(a, b) + kRangeMargin;
        Profiler::setAddressRangeForTest(_range_lo, _range_hi);
    }

    void TearDown() override {
        Profiler::resetAddressRangeForTest();
        munmap(_region, 2 * kPageSize());
        OS::replaceSigsegvHandler(_orig_segv);
        OS::replaceSigbusHandler(_orig_bus);
        ProfiledThread::release();
    }

    ProfiledThread* _pt = nullptr;
    void* _region = nullptr;
    SigAction _orig_segv = nullptr;
    SigAction _orig_bus = nullptr;
    uintptr_t _range_lo = 0;
    uintptr_t _range_hi = 0;
};

// The core guarantee: a SIGSEGV on stale metadata inside resolve() comes back as
// nullptr ("unknown method") rather than killing the process.
//
// How this test fails if the protection is ever removed differs by config, so
// don't read a clean release run as the only evidence: in DEBUG the at() assert
// aborts, while in release neither orig_segvHandler nor OS::getSegvChainTarget()
// is set in a gtest binary, so segvHandler returns, the faulting instruction
// re-executes and the test hangs instead of failing.
TEST_F(HotspotResolveCrashProtectionTest, ResolveRecoversFromFaultInsteadOfCrashing) {
    HotspotMethodIdVMHotspotGuard hotspot;
    // method_constmethod = kPageSize puts the very first raw dereference of the
    // walk on the guard page. cast_or_null() still succeeds beforehand because it
    // only validates [ptr, ptr + VMMethod::type_size()), which stays on the
    // readable page -- the fault comes from the offset, not the pointer.
    VMStructsTestAccessor::Offsets faulting = RESOLVE_OFFSETS;
    faulting.method_constmethod = (int)kPageSize();
    VMStructsTestAccessor offsets(faulting);
    VMStructsTestAccessor::SymbolLayout layout(RESOLVE_SYMBOL_OFFSETS, RESOLVE_TYPE_SIZES);

    long long before = Counters::getCounter(METHOD_RESOLVE_FAULT_RECOVERED);

    // VMMethod::id() reads the same offset through SafeAccess first, so it
    // returns the sentinel rather than faulting; resolve() then falls through to
    // constMethod_or_null(), whose raw *(void**) deref is what actually faults.
    EXPECT_EQ(nullptr, HotspotSupport::resolve(_region));

    EXPECT_EQ(before + 1, Counters::getCounter(METHOD_RESOLVE_FAULT_RECOVERED));
    // The landing pad must hand the previous (here: absent) context back.
    EXPECT_FALSE(_pt->isProtected());
}

// Recovery must be repeatable: checkFault() calls resetCrashHandler() before
// jumping precisely because the siglongjmp skips exitCrashHandler(), so a run of
// faults must not exhaust CRASH_HANDLER_NESTING_LIMIT.
TEST_F(HotspotResolveCrashProtectionTest, ResolveRecoversRepeatedly) {
    HotspotMethodIdVMHotspotGuard hotspot;
    VMStructsTestAccessor::Offsets faulting = RESOLVE_OFFSETS;
    faulting.method_constmethod = (int)kPageSize();
    VMStructsTestAccessor offsets(faulting);
    VMStructsTestAccessor::SymbolLayout layout(RESOLVE_SYMBOL_OFFSETS, RESOLVE_TYPE_SIZES);

    long long before = Counters::getCounter(METHOD_RESOLVE_FAULT_RECOVERED);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(nullptr, HotspotSupport::resolve(_region));
        EXPECT_FALSE(_pt->isProtected());
    }
    EXPECT_EQ(before + 10, Counters::getCounter(METHOD_RESOLVE_FAULT_RECOVERED));
}

// A Symbol whose body straddles the guard page is rejected by copySymbolBody's
// SafeAccess::isReadableRange() probe before memcpy() is reached -- a fault
// inside an out-of-line libc memcpy would have a pc outside the profiler range
// and so would NOT be recoverable. No JNI is reached on this path, which is why
// the test is safe without a live JVM.
TEST_F(HotspotResolveCrashProtectionTest, ResolveReturnsNullForUnreadableSymbolBody) {
    HotspotMethodIdVMHotspotGuard hotspot;
    VMStructsTestAccessor offsets(RESOLVE_OFFSETS);
    VMStructsTestAccessor::SymbolLayout layout(RESOLVE_SYMBOL_OFFSETS, RESOLVE_TYPE_SIZES);

    ResolveFakes* f = new (_region) ResolveFakes{};
    f->link();
    ResolveFakes::setSymbol(f->name_sym, "someMethod");
    ResolveFakes::setSymbol(f->sig_sym, "()V");
    // Put the class-name Symbol's header flush against the end of the readable
    // page: exactly VMSymbol::type_size() bytes, so VMSymbol::cast_or_null()'s
    // own isReadableRange() check still passes and the rejection has to come from
    // copySymbolBody(). The declared length then runs the body off the page.
    char* edge = (char*)_region + kPageSize() - RESOLVE_TYPE_SIZES.symbol;
    *(uint16_t*)(edge + RESOLVE_SYMBOL_OFFSETS.symbol_length) = 100;
    f->klass.name_symbol = edge;

    long long before = Counters::getCounter(METHOD_RESOLVE_SYMBOL_UNREADABLE);
    long long faults_before = Counters::getCounter(METHOD_RESOLVE_FAULT_RECOVERED);

    EXPECT_EQ(nullptr, HotspotSupport::resolve(&f->method));

    EXPECT_EQ(before + 1, Counters::getCounter(METHOD_RESOLVE_SYMBOL_UNREADABLE));
    // Rejected by the readability probe, not by recovering from a real fault.
    EXPECT_EQ(faults_before, Counters::getCounter(METHOD_RESOLVE_FAULT_RECOVERED));
    EXPECT_FALSE(_pt->isProtected());
}

// A method name longer than the fixed inline buffer (MAX_METHOD_NAME_LEN,
// 512 bytes) but fully readable must take ResolvedNames::setImpl()'s malloc
// fallback and still resolve successfully through to the JNI phase, with the
// full, correctly NUL-terminated name -- not get rejected the way a name
// this size would be by the *unreadable*-body case below.
TEST_F(HotspotResolveCrashProtectionTest, ResolveUsesMallocFallbackForOversizedButReadableName) {
    HotspotMethodIdVMHotspotGuard hotspot;
    VMStructsTestAccessor offsets(RESOLVE_OFFSETS);
    VMStructsTestAccessor::SymbolLayout layout(RESOLVE_SYMBOL_OFFSETS, RESOLVE_TYPE_SIZES);

    ResolveFakes* f = new (_region) ResolveFakes{};
    f->link();
    ResolveFakes::setSymbol(f->sig_sym, "()V");
    ResolveFakes::setSymbol(f->klass_sym, "java/lang/Object");

    // Longer than MAX_METHOD_NAME_LEN (512) but well under the 16-bit range a
    // real Symbol::length() can report, and fully readable. Written past
    // ResolveFakes' own footprint in the same mapped page so it doesn't
    // clobber sig_sym/klass_sym, then wired in as the name Symbol in place of
    // f->name_sym (whose fixed body[64] is too small to hold it).
    const std::string long_name(600, 'm');
    char* long_symbol = (char*)_region + 1024;
    *(uint16_t*)(long_symbol + RESOLVE_SYMBOL_OFFSETS.symbol_length) = (uint16_t)long_name.size();
    memcpy(long_symbol + RESOLVE_SYMBOL_OFFSETS.symbol_body, long_name.data(), long_name.size());
    f->cpool.symbols[1] = (intptr_t)long_symbol;  // name_index slot, see link()

    ScopedFakeJni fake_jni;

    long long unreadable_before = Counters::getCounter(METHOD_RESOLVE_SYMBOL_UNREADABLE);
    long long fault_before = Counters::getCounter(METHOD_RESOLVE_FAULT_RECOVERED);

    // The fake JNI's GetMethodID reports "not found", so resolve() itself
    // still returns nullptr -- the point of this test is what it does on the
    // way there, checked below.
    EXPECT_EQ(nullptr, HotspotSupport::resolve(&f->method));

    // Phase 1 accepted the name via the malloc fallback (no rejection, no
    // fault) and reached phase 2, which called GetMethodID with the fully
    // copied name -- proof the fallback copied all 600 bytes and
    // NUL-terminated them correctly rather than truncating to the inline
    // buffer or leaving it uninitialized.
    EXPECT_EQ(unreadable_before, Counters::getCounter(METHOD_RESOLVE_SYMBOL_UNREADABLE));
    EXPECT_EQ(fault_before, Counters::getCounter(METHOD_RESOLVE_FAULT_RECOVERED));
    // GetMethodID and GetStaticMethodID share this mock and both report "not
    // found", so lookupMethodIdViaJni() falls through from one to the other --
    // two calls, both carrying the same (correct) captured name/signature.
    EXPECT_EQ(2, fake_jni.getMethodIdCalls());
    EXPECT_EQ(long_name, fake_jni.lastMethodName());
    EXPECT_EQ("()V", fake_jni.lastMethodSignature());
    EXPECT_FALSE(_pt->isProtected());
}

// NOTE for reviewers: a companion test asserting the *hard* MAX_SYMBOL_LEN
// ceiling (`len >= MAX_SYMBOL_LEN` in ResolvedNames::setImpl) rejects a
// symbol is intentionally not included here. VMSymbol::length() returns
// `unsigned short` (vmStructs.h), so the largest value it can ever produce is
// 65535 -- which is already below MAX_SYMBOL_LEN (64 * 1024 = 65536). That
// branch cannot be reached through a real Symbol length field as currently
// typed; forging a >=65536 "length" in the test would require bypassing the
// u2 width the fake is deliberately modeling, which would pin a value that
// can't occur in production rather than real cap behavior. Flagging this as
// a probable dead branch (or a MAX_SYMBOL_LEN that should be 65536 -> 65535,
// or the comparison that should be `>` semantics some other way) rather than
// writing a test around it -- worth confirming with whoever added the check
// what it was meant to guard against.
//
// What *is* pinned below is the related, reachable case: a Symbol at the
// largest value the field can actually hold (0xFFFF) whose body is not fully
// readable is rejected by the SafeAccess probe in copySymbolBody(), the same
// mechanism as ResolveReturnsNullForUnreadableSymbolBody above, just at the
// boundary length instead of a short one.
TEST_F(HotspotResolveCrashProtectionTest, ResolveRejectsUnreadableSymbolAtMaxLength) {
    HotspotMethodIdVMHotspotGuard hotspot;
    VMStructsTestAccessor offsets(RESOLVE_OFFSETS);
    VMStructsTestAccessor::SymbolLayout layout(RESOLVE_SYMBOL_OFFSETS, RESOLVE_TYPE_SIZES);

    ResolveFakes* f = new (_region) ResolveFakes{};
    f->link();
    ResolveFakes::setSymbol(f->sig_sym, "()V");
    ResolveFakes::setSymbol(f->klass_sym, "java/lang/Object");
    f->name_sym.length = 0xFFFF;  // max value a real u2 length field can hold

    long long before = Counters::getCounter(METHOD_RESOLVE_SYMBOL_UNREADABLE);

    EXPECT_EQ(nullptr, HotspotSupport::resolve(&f->method));

    EXPECT_EQ(before + 1, Counters::getCounter(METHOD_RESOLVE_SYMBOL_UNREADABLE));
    EXPECT_FALSE(_pt->isProtected());
}

// An empty Symbol means the slot has been recycled; treat it as unresolvable
// rather than handing FindClass an empty string.
TEST_F(HotspotResolveCrashProtectionTest, ResolveReturnsNullForEmptySymbol) {
    HotspotMethodIdVMHotspotGuard hotspot;
    VMStructsTestAccessor offsets(RESOLVE_OFFSETS);
    VMStructsTestAccessor::SymbolLayout layout(RESOLVE_SYMBOL_OFFSETS, RESOLVE_TYPE_SIZES);

    ResolveFakes* f = new (_region) ResolveFakes{};
    f->link();
    ResolveFakes::setSymbol(f->sig_sym, "()V");
    ResolveFakes::setSymbol(f->klass_sym, "java/lang/Object");
    f->name_sym.length = 0;

    long long before = Counters::getCounter(METHOD_RESOLVE_SYMBOL_UNREADABLE);

    EXPECT_EQ(nullptr, HotspotSupport::resolve(&f->method));

    EXPECT_EQ(before + 1, Counters::getCounter(METHOD_RESOLVE_SYMBOL_UNREADABLE));
    EXPECT_FALSE(_pt->isProtected());
}

// The sentinel is mapped to nullptr before any metadata is touched, so it must
// not acquire a ProfiledThread or install a landing pad at all.
TEST_F(HotspotResolveCrashProtectionTest, ResolveShortCircuitsSentinelWithoutProtection) {
    HotspotMethodIdVMHotspotGuard hotspot;
    long long before = Counters::getCounter(METHOD_RESOLVE_FAULT_RECOVERED);

    EXPECT_EQ(nullptr, HotspotSupport::resolve((const void*)JMETHODID_NOT_WALKABLE));

    EXPECT_EQ(before, Counters::getCounter(METHOD_RESOLVE_FAULT_RECOVERED));
    EXPECT_FALSE(_pt->isProtected());
}

#endif // __linux__
