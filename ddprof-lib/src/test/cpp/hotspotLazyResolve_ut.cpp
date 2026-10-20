/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "../../main/cpp/counters.h"
#include "../../main/cpp/flightRecorder.h"
#include "../../main/cpp/frame.h"
#include "../../main/cpp/hotspot/hotspotSupport.h"
#include "../../main/cpp/hotspot/klassRegistry.h"
#include "../../main/cpp/hotspot/klassTraceId.h"
#include "../../main/cpp/hotspot/vmStructs.h"
#include "../../main/cpp/jvmSupport.h"
#include "../../main/cpp/profiler.h"
#include "../../main/cpp/threadLocalData.inline.h"
#include "../../main/cpp/vmEntry.h"

#include <cstdint>
#include <cstring>
#include <set>
#include <vector>

// fjmethodid=lazy end to end, without a JVM: a raw Method* frame is captured
// with HotspotSupport::fillJavaFrame() exactly as walkVM does, the class's
// registry entry is manipulated the way ClassPrepare and class unloading
// would, and the frame is resolved with HotspotSupport::resolve() as the dump
// thread does.
//
// The metadata is fake but laid out the way the offsets below tell
// VMStructs to read it: Method -> ConstMethod -> ConstantPool -> Klass, with
// the constant pool holding the method's name and signature Symbols and the
// Klass its name and methods array. The class has no jmethodIDs at all, as in
// lazy mode. None of it is ever freed, so no fault handling is needed and the
// tests run on every platform.
//
// The Klass*-reuse tests model what aligned, reused class space makes likely:
// a class is unloaded, and a new class of the same shape is loaded at the
// same Klass* address with its methods at the same Method* addresses. A frame
// sampled from the old class must not resolve as a method of the new one.

class VMTestAccessor {
public:
    static bool getHotspot() { return VM::_hotspot; }
    static void setHotspot(bool value) { VM::_hotspot = value; }
    static JavaVM* getVm() { return VM::_vm; }
    static void setVm(JavaVM* vm) { VM::_vm = vm; }
    static jvmtiEnv* getJvmti() { return VM::_jvmti; }
    static void setJvmti(jvmtiEnv* env) { VM::_jvmti = env; }
};

class JVMSupportTestAccessor {
public:
    using LoadState = JVMSupport::JMethodIDLoadStats;
    static LoadState getLoadState() { return JVMSupport::getLoadState(); }
    static void setLoadState(LoadState s) { JVMSupport::setLoadState(s); }
    static constexpr LoadState LazyLoaded() { return JVMSupport::Lazy_loaded; }
    static constexpr LoadState PartialLoaded() { return JVMSupport::Partial_loaded; }
};

class HotspotSupportTestAccessor {
public:
    static KlassRegistry& registry() { return HotspotSupport::_klass_registry; }
    static void setLazyUsed(bool used) { HotspotSupport::_lazy_used = used; }
    static void setRedefinitionsUntracked(bool v) { HotspotSupport::_redefinitions_untracked = v; }
    static bool dumpClassesBuilt() { return HotspotSupport::_dump_classes != nullptr; }
    static void beforeClassRedefinition(jvmtiEnv* jvmti, JNIEnv* jni, jclass klass) {
        HotspotSupport::beforeClassRedefinition(jvmti, jni, klass);
    }
    static void afterClassRedefinition(jvmtiEnv* jvmti, JNIEnv* jni, jclass klass, bool succeeded) {
        HotspotSupport::afterClassRedefinition(jvmti, jni, klass, succeeded);
    }
    static uint32_t traceIdTagBit() { return HotspotSupport::TRACE_ID_TAG; }
    static bool registerClass(jvmtiEnv* jvmti, JNIEnv* jni, jclass klass) {
        return HotspotSupport::registerClass(jvmti, jni, klass);
    }
};

class ProfilerTestAccessor {
public:
    static bool getForceJmethodID(Profiler* p) { return p->_force_jmethodID; }
    static void setForceJmethodID(Profiler* p, bool v) { p->_force_jmethodID = v; }
};

// Points VMStructs at the fake layout below for the lifetime of a test, and
// restores whatever was there before.
class VMStructsTestAccessor {
public:
    struct State {
        int method_constmethod, constmethod_constants, constmethod_idnum, pool_holder;
        int jmethod_ids, methods;
        int constmethod_name_index, constmethod_sig_index, klass_name, symbol_length, symbol_body;
        int constmethod_flags, constmethod_code_size, klass_super;
        uint64_t method_size, const_method_size, constant_pool_size, klass_size, symbol_size;
        bool can_dereference_jmethod_id;
    };

    explicit VMStructsTestAccessor(const State& s) : _saved(save()) { apply(s); }
    ~VMStructsTestAccessor() { apply(_saved); }

private:
    State _saved;

    static State save() {
        return {
            VMStructs::_method_constmethod_offset,
            VMStructs::_constmethod_constants_offset,
            VMStructs::_constmethod_idnum_offset,
            VMStructs::_pool_holder_offset,
            VMStructs::_jmethod_ids_offset,
            VMStructs::_methods_offset,
            VMStructs::_constmethod_name_index_offset,
            VMStructs::_constmethod_sig_index_offset,
            VMStructs::_klass_name_offset,
            VMStructs::_symbol_length_offset,
            VMStructs::_symbol_body_offset,
            VMStructs::_constmethod_flags_offset,
            VMStructs::_constmethod_code_size_offset,
            VMStructs::_klass_super_offset,
            VMStructs::TYPE_SIZE_NAME(VMMethod),
            VMStructs::TYPE_SIZE_NAME(VMConstMethod),
            VMStructs::TYPE_SIZE_NAME(VMConstantPool),
            VMStructs::TYPE_SIZE_NAME(VMKlass),
            VMStructs::TYPE_SIZE_NAME(VMSymbol),
            VMStructs::_can_dereference_jmethod_id,
        };
    }

    static void apply(const State& s) {
        VMStructs::_method_constmethod_offset = s.method_constmethod;
        VMStructs::_constmethod_constants_offset = s.constmethod_constants;
        VMStructs::_constmethod_idnum_offset = s.constmethod_idnum;
        VMStructs::_pool_holder_offset = s.pool_holder;
        VMStructs::_jmethod_ids_offset = s.jmethod_ids;
        VMStructs::_methods_offset = s.methods;
        VMStructs::_constmethod_name_index_offset = s.constmethod_name_index;
        VMStructs::_constmethod_sig_index_offset = s.constmethod_sig_index;
        VMStructs::_klass_name_offset = s.klass_name;
        VMStructs::_symbol_length_offset = s.symbol_length;
        VMStructs::_symbol_body_offset = s.symbol_body;
        VMStructs::_constmethod_flags_offset = s.constmethod_flags;
        VMStructs::_constmethod_code_size_offset = s.constmethod_code_size;
        VMStructs::_klass_super_offset = s.klass_super;
        VMStructs::TYPE_SIZE_NAME(VMMethod) = s.method_size;
        VMStructs::TYPE_SIZE_NAME(VMConstMethod) = s.const_method_size;
        VMStructs::TYPE_SIZE_NAME(VMConstantPool) = s.constant_pool_size;
        VMStructs::TYPE_SIZE_NAME(VMKlass) = s.klass_size;
        VMStructs::TYPE_SIZE_NAME(VMSymbol) = s.symbol_size;
        VMStructs::_can_dereference_jmethod_id = s.can_dereference_jmethod_id;
    }
};

namespace {

struct FakeMethod {
    void* const_method;
};

struct FakeConstMethod {
    void* cpool;
    uint16_t idnum;
    uint16_t name_index;
    uint16_t sig_index;
    uint16_t pad;
};

// VMConstantPool::base() is `this + type_size()`, so the slots follow holder.
struct FakeConstantPool {
    void* holder;
    intptr_t symbols[3];
};

struct FakeSymbol {
    uint16_t length;
    char body[30];
};

// HotSpot's Array<Method*>: int length, then pointer-aligned elements.
struct FakeMethodArray {
    int32_t len;
    int32_t pad;
    void* data[2];
};

struct FakeKlass {
    void* ids;          // jmethodID cache; stays null
    FakeMethodArray* methods;
    uint64_t trace_id;  // JFR encoding: (id << 16) | tag bits
    FakeSymbol* name;
};

const VMStructsTestAccessor::State LAYOUT = {
    /*method_constmethod*/    (int)offsetof(FakeMethod, const_method),
    /*constmethod_constants*/ (int)offsetof(FakeConstMethod, cpool),
    /*constmethod_idnum*/     (int)offsetof(FakeConstMethod, idnum),
    /*pool_holder*/           (int)offsetof(FakeConstantPool, holder),
    /*jmethod_ids*/           (int)offsetof(FakeKlass, ids),
    /*methods*/               (int)offsetof(FakeKlass, methods),
    /*constmethod_name_index*/ (int)offsetof(FakeConstMethod, name_index),
    /*constmethod_sig_index*/ (int)offsetof(FakeConstMethod, sig_index),
    /*klass_name*/            (int)offsetof(FakeKlass, name),
    /*symbol_length*/         (int)offsetof(FakeSymbol, length),
    /*symbol_body*/           (int)offsetof(FakeSymbol, body),
    /*constmethod_flags*/     -1,  // no line number tables
    /*constmethod_code_size*/ -1,
    /*klass_super*/           -1,
    /*method_size*/           sizeof(FakeMethod),
    /*const_method_size*/     sizeof(FakeConstMethod),
    /*constant_pool_size*/    offsetof(FakeConstantPool, symbols),
    /*klass_size*/            sizeof(FakeKlass),
    /*symbol_size*/           sizeof(FakeSymbol),
    /*can_dereference*/       true,
};

// One class, com/example/Spin, with one method, spin(J)V, and no jmethodIDs.
// Klass* and Method* addresses are those of these fields, which is what lets
// a test "reload" a class at the same addresses: it only has to register a
// new mirror for the same FakeKlass.
struct FakeClass {
    static constexpr const char* KLASS_NAME = "com/example/Spin";
    static constexpr const char* METHOD_NAME = "spin";
    static constexpr const char* SIGNATURE = "(J)V";

    FakeMethod method;
    FakeConstMethod const_method;
    FakeConstantPool cpool;
    FakeKlass klass;
    FakeMethodArray methods;
    FakeSymbol klass_name, method_name, signature;

    FakeClass() {
        memset(this, 0, sizeof(*this));
        method.const_method = &const_method;
        const_method.cpool = &cpool;
        const_method.idnum = 0;
        const_method.name_index = 1;
        const_method.sig_index = 2;
        cpool.holder = &klass;
        cpool.symbols[1] = (intptr_t)&method_name;
        cpool.symbols[2] = (intptr_t)&signature;
        klass.methods = &methods;
        klass.trace_id = (uint64_t)1000 << 16;
        klass.name = &klass_name;
        methods.len = 1;
        methods.data[0] = &method;
        setSymbol(klass_name, KLASS_NAME);
        setSymbol(method_name, METHOD_NAME);
        setSymbol(signature, SIGNATURE);
    }

    static void setSymbol(FakeSymbol& sym, const char* text) {
        sym.length = (uint16_t)strlen(text);
        memcpy(sym.body, text, sym.length);
    }

    const void* klassPtr() const { return &klass; }
    VMMethod* vmMethod() { return reinterpret_cast<VMMethod*>(&method); }
};

// Fake JNI with weak-reference semantics, as in klassRegistry_ut.cpp, plus
// the JavaVM that VM::jni() goes through.
struct FakeObject {
    int id;
    const void* klass = nullptr;  // what java.lang.Class.klass holds, for mirrors
    bool collected = false;       // the class has been unloaded
};

struct FakeWeak {
    FakeObject* referent;
};

class FakeJvm {
public:
    FakeJvm() : _saved_vm(VMTestAccessor::getVm()) {
        s_instance = this;
        _jni_tbl.NewWeakGlobalRef = &newWeakGlobalRef;
        _jni_tbl.DeleteWeakGlobalRef = &deleteWeakGlobalRef;
        _jni_tbl.IsSameObject = &isSameObject;
        _jni_tbl.NewLocalRef = &newLocalRef;
        _jni_tbl.DeleteLocalRef = &deleteLocalRef;
        _jni_tbl.GetLongField = &getLongField;
        _jni_tbl.ExceptionCheck = &exceptionCheck;
        _jni_tbl.ExceptionClear = &exceptionClear;
        _jni_tbl.ExceptionOccurred = &exceptionOccurred;
        _jni_tbl.Throw = &throwException;
        _jni_env.functions = &_jni_tbl;
        _jvmti_tbl.GetClassStatus = &getClassStatus;
        _jvmti_tbl.GetClassMethods = &getClassMethods;
        _jvmti_tbl.Deallocate = &deallocate;
        _jvmti.functions = &_jvmti_tbl;
        _saved_jvmti = VMTestAccessor::getJvmti();
        VMTestAccessor::setJvmti(&_jvmti);
        _vm_tbl.GetEnv = &getEnv;
        _vm.functions = &_vm_tbl;
        VMTestAccessor::setVm(reinterpret_cast<JavaVM*>(&_vm));
    }

    ~FakeJvm() {
        VMTestAccessor::setJvmti(_saved_jvmti);
        VMTestAccessor::setVm(_saved_vm);
        for (FakeWeak* w : _weaks) {
            delete w;
        }
        s_instance = nullptr;
    }

    JNIEnv* jni() { return &_jni_env; }
    jvmtiEnv* jvmti() { return &_jvmti; }

    int new_local_ref_calls = 0;
    int get_class_methods_calls = 0;
    bool fail_weak_refs = false;  // NewWeakGlobalRef fails, as when out of memory
    bool exception_pending = false;  // set by a failed NewWeakGlobalRef, as JNI does
    int throws = 0;
    // JNI forbids these calls while an exception is pending.
    int calls_with_exception_pending = 0;

    jclass mirror(FakeObject& obj) { return reinterpret_cast<jclass>(&obj); }

    // Class unloading: the class is no longer among the loaded classes, and
    // the mirror's weak references are cleared.
    void collect(FakeObject& obj) {
        obj.collected = true;
        for (FakeWeak* w : _weaks) {
            if (w->referent == &obj) {
                w->referent = nullptr;
            }
        }
    }

private:
    jobject resolve(jobject ref) {
        FakeWeak* w = reinterpret_cast<FakeWeak*>(ref);
        return _weaks.count(w) != 0 ? reinterpret_cast<jobject>(w->referent) : ref;
    }

    static void checkNoException() {
        if (s_instance->exception_pending) {
            s_instance->calls_with_exception_pending++;
        }
    }
    static jweak JNICALL newWeakGlobalRef(JNIEnv*, jobject obj) {
        checkNoException();
        if (s_instance->fail_weak_refs) {
            s_instance->exception_pending = true;  // OutOfMemoryError
            return nullptr;
        }
        FakeWeak* w = new FakeWeak{reinterpret_cast<FakeObject*>(s_instance->resolve(obj))};
        s_instance->_weaks.insert(w);
        return reinterpret_cast<jweak>(w);
    }
    static void JNICALL deleteWeakGlobalRef(JNIEnv*, jweak) {}
    static jboolean JNICALL exceptionCheck(JNIEnv*) {
        return s_instance->exception_pending ? JNI_TRUE : JNI_FALSE;
    }
    static void JNICALL exceptionClear(JNIEnv*) { s_instance->exception_pending = false; }
    static jthrowable JNICALL exceptionOccurred(JNIEnv*) {
        return s_instance->exception_pending ? reinterpret_cast<jthrowable>(&s_instance->_throwable) : nullptr;
    }
    static jint JNICALL throwException(JNIEnv*, jthrowable) {
        s_instance->throws++;
        s_instance->exception_pending = true;
        return 0;
    }
    static jboolean JNICALL isSameObject(JNIEnv*, jobject a, jobject b) {
        checkNoException();
        return s_instance->resolve(a) == s_instance->resolve(b) ? JNI_TRUE : JNI_FALSE;
    }
    static jobject JNICALL newLocalRef(JNIEnv*, jobject ref) {
        checkNoException();
        s_instance->new_local_ref_calls++;
        return s_instance->resolve(ref);
    }
    static void JNICALL deleteLocalRef(JNIEnv*, jobject) {}
    // VMKlass::fromJavaClass() reads java.lang.Class.klass through this.
    static jlong JNICALL getLongField(JNIEnv*, jobject obj, jfieldID) {
        checkNoException();
        return (jlong)(uintptr_t)reinterpret_cast<FakeObject*>(obj)->klass;
    }
    // A jmethodID preload (loadMethodIDsIfNeededImpl()); only the call is
    // recorded. Resolution never makes it: only a successful redefinition
    // preloads.
    static jvmtiError JNICALL getClassMethods(jvmtiEnv*, jclass, jint* count, jmethodID** methods) {
        s_instance->get_class_methods_calls++;
        *count = 0;
        *methods = nullptr;
        return JVMTI_ERROR_NONE;
    }
    static jvmtiError JNICALL deallocate(jvmtiEnv*, unsigned char*) { return JVMTI_ERROR_NONE; }
    static jvmtiError JNICALL getClassStatus(jvmtiEnv*, jclass, jint* status) {
        *status = JVMTI_CLASS_STATUS_PREPARED;
        return JVMTI_ERROR_NONE;
    }
    static jint JNICALL getEnv(JavaVM*, void** penv, jint) {
        *penv = &s_instance->_jni_env;
        return JNI_OK;
    }

    static FakeJvm* s_instance;

    JavaVM* _saved_vm;
    JNINativeInterface_ _jni_tbl{};
    JNIEnv_ _jni_env{};
    JNIInvokeInterface_ _vm_tbl{};
    JavaVM_ _vm{};
    jvmtiInterface_1_ _jvmti_tbl{};
    _jvmtiEnv _jvmti{};
    jvmtiEnv* _saved_jvmti = nullptr;
    std::set<FakeWeak*> _weaks;
    int _throwable = 0;  // what ExceptionOccurred() returns
};
FakeJvm* FakeJvm::s_instance = nullptr;

} // namespace

class HotspotLazyResolveTest : public ::testing::Test {
protected:
    VMStructsTestAccessor _layout{LAYOUT};
    FakeJvm _jvm;
    FakeClass _cls;
    FakeObject _old_mirror{1};
    FakeObject _new_mirror{2};
    bool _saved_hotspot = false;
    bool _saved_force = true;
    int _saved_trace_id_offset = -1;
    JVMSupportTestAccessor::LoadState _saved_state{};

    void SetUp() override {
        _saved_hotspot = VMTestAccessor::getHotspot();
        VMTestAccessor::setHotspot(true);
        _saved_state = JVMSupportTestAccessor::getLoadState();
        JVMSupportTestAccessor::setLoadState(JVMSupportTestAccessor::LazyLoaded());
        // fillJavaFrame() only stores raw Method* frames when jmethodIDs are
        // not forced, which is how fjmethodid=lazy configures the profiler.
        _saved_force = ProfilerTestAccessor::getForceJmethodID(Profiler::instance());
        ProfilerTestAccessor::setForceJmethodID(Profiler::instance(), false);
        _saved_trace_id_offset = KlassTraceId::offset();
        KlassTraceId::setOffsetForTest((int)offsetof(FakeKlass, trace_id));
        // The redefinition hooks find the class through java.lang.Class.klass.
        _old_mirror.klass = _cls.klassPtr();
        _new_mirror.klass = _cls.klassPtr();
        // resolve() installs crash protection on the current ProfiledThread.
        ProfiledThread::initCurrentThread();
        ASSERT_NE(nullptr, ProfiledThread::current());
        HotspotSupportTestAccessor::setLazyUsed(true);
    }

    void TearDown() override {
        HotspotSupport::endDump();
        HotspotSupportTestAccessor::setLazyUsed(false);
        HotspotSupportTestAccessor::setRedefinitionsUntracked(false);
        HotspotSupportTestAccessor::registry().clear(_jvm.jni());
        ProfiledThread::release();
        KlassTraceId::setOffsetForTest(_saved_trace_id_offset);
        ProfilerTestAccessor::setForceJmethodID(Profiler::instance(), _saved_force);
        JVMSupportTestAccessor::setLoadState(_saved_state);
        VMTestAccessor::setHotspot(_saved_hotspot);
    }

    // Classes loaded so far; collect() unloads them.
    std::vector<FakeObject*> _loaded;

    // A class is loaded: from now on it is among the classes a dump pins.
    void registerClass(FakeObject& mirror) {
        _loaded.push_back(&mirror);
    }

    // The class list of the current dump; like finishChunk()'s, it must stay
    // valid until the dump ends.
    std::vector<jclass> _dump_classes;

    // What Recording::finishChunk() does at the start of a dump: pins the
    // classes that are loaded now.
    void beginDump() {
        HotspotSupport::endDump();
        _dump_classes.clear();
        for (FakeObject* m : _loaded) {
            if (!m->collected) {
                _dump_classes.push_back(_jvm.mirror(*m));
            }
        }
        HotspotSupport::beginDump(_jvm.jni(), _dump_classes.data(), (int)_dump_classes.size());
    }

    // The old class is unloaded and a new class of the same shape is loaded at
    // the same Klass* and Method* addresses: its mirror is new, and so is the
    // trace ID JFR assigns at creation.
    void loadNewClassAtSameAddress() {
        _jvm.collect(_old_mirror);
        _cls.klass.trace_id = ((_cls.klass.trace_id >> 16) + 37) << 16;
        registerClass(_new_mirror);
    }

    // What walkVM stores for a frame of a class without a jmethodID yet.
    ASGCT_CallFrame sample() {
        ASGCT_CallFrame frame{};
        HotspotSupport::fillJavaFrame(frame, FRAME_JIT_COMPILED, 7, nullptr, _cls.vmMethod());
        EXPECT_TRUE(FrameType::isRawPointer(frame.bci));
        return frame;
    }

    // What VM::RetransformClassesHook does around the original call.
    void redefine(bool succeeded) {
        HotspotSupportTestAccessor::beforeClassRedefinition(_jvm.jvmti(), _jvm.jni(), _jvm.mirror(_old_mirror));
        HotspotSupportTestAccessor::afterClassRedefinition(_jvm.jvmti(), _jvm.jni(), _jvm.mirror(_old_mirror),
                                                           succeeded);
    }

    // What Lookup::fillRawMethod() does with a raw frame in a dump that
    // starts now.
    bool resolve(const ASGCT_CallFrame& frame) {
        beginDump();
        ResolvedMethod result;
        return HotspotSupport::resolve(frame.method, frame.bci, result);
    }

    // Whether `frame` resolves, and to the names of the fake class's method.
    bool resolvesToSpin(const ASGCT_CallFrame& frame) {
        beginDump();
        ResolvedMethod result;
        return HotspotSupport::resolve(frame.method, frame.bci, result) &&
               strcmp(FakeClass::KLASS_NAME, result.klassName()) == 0 &&
               strcmp(FakeClass::METHOD_NAME, result.methodName()) == 0 &&
               strcmp(FakeClass::SIGNATURE, result.methodSignature()) == 0;
    }
};

// A hidden class gets the name JVMTI GetClassSignature() reports, so its
// frames are named the same with and without jmethodIDs; other names that
// merely contain a '+' are left alone.
TEST_F(HotspotLazyResolveTest, HiddenClassNamedAsJvmtiSignature) {
    registerClass(_old_mirror);
    const struct { const char* vm_name; const char* expected; } cases[] = {
        {"a/Spin$$Lambda+0x8010a0", "a/Spin$$Lambda.0x8010a0"},
        {"a/B+0x1+0x2f", "a/B+0x1.0x2f"},
        {"a/Plus+Sign", "a/Plus+Sign"},
        {"a/Spin+0x", "a/Spin+0x"},
        {"a/Spin+0x12g", "a/Spin+0x12g"},
    };
    beginDump();
    for (const auto& c : cases) {
        SCOPED_TRACE(c.vm_name);
        FakeClass::setSymbol(_cls.klass_name, c.vm_name);
        ASGCT_CallFrame frame = sample();
        ResolvedMethod result;
        ASSERT_TRUE(HotspotSupport::resolve(frame.method, frame.bci, result));
        EXPECT_STREQ(c.expected, result.klassName());
    }
}

// The names come from VM metadata: no jmethodIDs are allocated.
TEST_F(HotspotLazyResolveTest, LiveClassResolves) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    EXPECT_TRUE(resolvesToSpin(frame));
    EXPECT_EQ(0, _jvm.get_class_methods_calls);
}

TEST_F(HotspotLazyResolveTest, UnloadedClassDoesNotResolve) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    _jvm.collect(_old_mirror);
    EXPECT_FALSE(resolve(frame));
}

// The old class is unloaded and a new one is registered at the same Klass*,
// with its method at the same Method* address. The frame was sampled from the
// old class, so it must not resolve to the new class's method.
TEST_F(HotspotLazyResolveTest, FrameFromBeforeKlassReuseDoesNotResolveToNewClass) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();

    loadNewClassAtSameAddress();

    EXPECT_FALSE(resolve(frame));
}

// Frames sampled from the new class after the reuse must still resolve.
TEST_F(HotspotLazyResolveTest, FrameFromAfterKlassReuseResolves) {
    registerClass(_old_mirror);
    loadNewClassAtSameAddress();

    ASGCT_CallFrame frame = sample();
    EXPECT_TRUE(resolvesToSpin(frame));
}

// A frame from the old class and one from the new class must be told apart
// already at capture time; otherwise the call trace storage merges them into
// one trace before resolve() ever runs.
TEST_F(HotspotLazyResolveTest, FramesFromBeforeAndAfterKlassReuseDiffer) {
    registerClass(_old_mirror);
    ASGCT_CallFrame before = sample();
    loadNewClassAtSameAddress();
    ASGCT_CallFrame after = sample();

    EXPECT_FALSE(before.bci == after.bci && before.method == after.method);
}

// Tags identify the class load itself, so another class's unloading and the
// reuse of its address leave this class's frames unchanged, and the same stack
// keeps deduplicating into one trace.
TEST_F(HotspotLazyResolveTest, UnrelatedReuseDoesNotChangeFrames) {
    registerClass(_old_mirror);
    ASGCT_CallFrame before = sample();

    static FakeKlass other_klass;
    other_klass = _cls.klass;
    other_klass.trace_id = ((_cls.klass.trace_id >> 16) + 7) << 16;
    static FakeObject other_old{10};
    static FakeObject other_new{11};
    other_old = FakeObject{10, &other_klass};
    other_new = FakeObject{11, &other_klass};
    registerClass(other_old);
    _jvm.collect(other_old);
    other_klass.trace_id += (uint64_t)1 << 16;
    registerClass(other_new);

    ASGCT_CallFrame after = sample();
    EXPECT_EQ(before.bci, after.bci);
    EXPECT_EQ(before.method, after.method);
    EXPECT_TRUE(resolvesToSpin(after));
}

// The JFR tag bits below the ID change while JFR runs; they must not affect
// the frame's tag or its resolution.
TEST_F(HotspotLazyResolveTest, JfrTagBitsDoNotAffectTraceIdTags) {
    registerClass(_old_mirror);
    ASGCT_CallFrame before = sample();
    _cls.klass.trace_id |= 0x0303;
    ASGCT_CallFrame after = sample();
    EXPECT_EQ(before.bci, after.bci);
    EXPECT_EQ(before.method, after.method);
    EXPECT_TRUE(resolvesToSpin(before));
}

// Partial mode (fjmethodid=false) stores the plain Method*, untagged, and
// never reads the holder's trace ID: a frame whose trace ID is unreadable is
// still stored raw, not turned into an unknown frame.
TEST_F(HotspotLazyResolveTest, PartialModeFramesAreStoredUntagged) {
    JVMSupportTestAccessor::setLoadState(JVMSupportTestAccessor::PartialLoaded());
    KlassTraceId::setOffsetForTest(-1);  // trace ID unreadable
    ASGCT_CallFrame frame = sample();
    EXPECT_EQ(static_cast<const void*>(_cls.vmMethod()), frame.method);
    EXPECT_EQ(0u, FrameType::rawTag(frame.bci, frame.method) & HotspotSupportTestAccessor::traceIdTagBit());
    EXPECT_EQ(static_cast<const void*>(_cls.vmMethod()), HotspotSupport::rawFrameMethod(frame.bci, frame.method));
}

// A raw frame is later looked up by its Method* with the bits above 2^48
// masked off, so a Method* that uses them is stored as an unknown frame in
// every mode instead of one that would resolve to another address.
TEST_F(HotspotLazyResolveTest, RawFrameAboveTaggableAddressesIsStoredUnknown) {
    const VMMethod* high = reinterpret_cast<const VMMethod*>((uintptr_t)1 << 52 | (uintptr_t)_cls.vmMethod());
    for (bool lazy : {true, false}) {
        JVMSupportTestAccessor::setLoadState(lazy ? JVMSupportTestAccessor::LazyLoaded()
                                                  : JVMSupportTestAccessor::PartialLoaded());
        ASGCT_CallFrame frame{};
        HotspotSupport::fillJavaFrame(frame, FRAME_JIT_COMPILED, 7, nullptr, high);
        EXPECT_FALSE(FrameType::isRawPointer(frame.bci)) << "lazy=" << lazy;
        EXPECT_EQ(JMETHODID_NOT_WALKABLE, frame.method_id) << "lazy=" << lazy;
    }
}

// resolve() goes by the mode the frame was sampled in, not the current one:
// a lazy-mode frame kept across a restart in partial mode still resolves
// against the classes the dump pins, which is what keeps a custom loader's
// class from being unloaded while its metadata is read.
TEST_F(HotspotLazyResolveTest, LazyFrameResolvesAgainstPinnedClassesAfterSwitchToPartialMode) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    ASSERT_NE(0u, FrameType::rawTag(frame.bci, frame.method) & HotspotSupportTestAccessor::traceIdTagBit());
    JVMSupportTestAccessor::setLoadState(JVMSupportTestAccessor::PartialLoaded());
    EXPECT_TRUE(resolvesToSpin(frame));
}

// A dump collects the pinned classes' Klass*s only when it resolves its first
// lazy frame, so a dump without lazy frames pays nothing for them.
TEST_F(HotspotLazyResolveTest, DumpCollectsPinnedClassesOnlyForLazyFrames) {
    registerClass(_old_mirror);
    beginDump();
    EXPECT_FALSE(HotspotSupportTestAccessor::dumpClassesBuilt());
    ASGCT_CallFrame frame = sample();
    ResolvedMethod result;
    EXPECT_TRUE(HotspotSupport::resolve(frame.method, frame.bci, result));
    EXPECT_TRUE(HotspotSupportTestAccessor::dumpClassesBuilt());
    HotspotSupport::endDump();
    EXPECT_FALSE(HotspotSupportTestAccessor::dumpClassesBuilt());
}

// A redefined class that is unloaded leaves its mark behind in the registry;
// a new class at the same address was never redefined, and its frames resolve.
TEST_F(HotspotLazyResolveTest, RedefinitionMarkDoesNotCarryOverToNewClassAtSameAddress) {
    registerClass(_old_mirror);
    redefine(true);
    ASSERT_FALSE(resolve(sample()));
    loadNewClassAtSameAddress();
    EXPECT_TRUE(resolvesToSpin(sample()));
}

// A dump whose GetLoadedClasses() failed passes no list; it must not fall back
// to an earlier dump's list, whose local references are gone.
TEST_F(HotspotLazyResolveTest, DumpWithoutClassListPinsNothing) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    ASSERT_TRUE(resolvesToSpin(frame));  // an earlier dump, ended without endDump()
    HotspotSupport::beginDump(_jvm.jni(), nullptr, 0);
    ResolvedMethod result;
    EXPECT_FALSE(HotspotSupport::resolve(frame.method, frame.bci, result));
}

// Enough pinned classes to grow the set past its minimum size, so lookups
// probe across a larger table.
TEST_F(HotspotLazyResolveTest, ClassIsFoundAmongManyPinnedClasses) {
    static FakeKlass others[3000];
    static FakeObject other_mirrors[3000];
    for (int i = 0; i < 3000; i++) {
        others[i] = _cls.klass;
        other_mirrors[i] = FakeObject{100 + i, &others[i]};
        registerClass(other_mirrors[i]);
    }
    registerClass(_old_mirror);
    EXPECT_TRUE(resolvesToSpin(sample()));
}

// If a redefinition cannot be marked, nothing tells its class's frames apart
// any more, so every lazy frame is refused from then on.
TEST_F(HotspotLazyResolveTest, UnmarkableRedefinitionRefusesAllLazyFrames) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    _jvm.fail_weak_refs = true;
    redefine(false);
    _jvm.fail_weak_refs = false;
    // The failed allocation's OutOfMemoryError must not reach the caller of
    // RedefineClasses.
    EXPECT_FALSE(_jvm.exception_pending);
    EXPECT_FALSE(resolve(frame));
}

// JVMTI allows a redefinition with a Java exception pending. The hooks set it
// aside instead of calling JNI with it pending, mark the class as usual, and
// throw it again for the caller of RedefineClasses.
TEST_F(HotspotLazyResolveTest, RedefinitionWithPendingExceptionIsMarked) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    long long add_failed = Counters::getCounter(KLASS_REGISTRY_ADD_FAILED);
    _jvm.exception_pending = true;
    redefine(true);
    EXPECT_TRUE(_jvm.exception_pending);
    EXPECT_EQ(2, _jvm.throws);  // once per hook
    EXPECT_EQ(0, _jvm.calls_with_exception_pending);
    _jvm.exception_pending = false;
    EXPECT_EQ(1u, HotspotSupportTestAccessor::registry().size());
    EXPECT_FALSE(resolve(frame));
    EXPECT_EQ(add_failed, Counters::getCounter(KLASS_REGISTRY_ADD_FAILED));
}

// A rejected call with an exception pending leaves the class as it was: no
// mark is left behind, so its frames still resolve.
TEST_F(HotspotLazyResolveTest, RejectedRedefinitionWithPendingExceptionLeavesFramesResolvable) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    _jvm.exception_pending = true;
    redefine(false);
    EXPECT_TRUE(_jvm.exception_pending);
    EXPECT_EQ(0, _jvm.calls_with_exception_pending);
    _jvm.exception_pending = false;
    EXPECT_TRUE(resolvesToSpin(frame));
}

// Before lazy mode has started there are no lazy frames, so redefinitions
// are not tracked.
TEST_F(HotspotLazyResolveTest, RedefinitionBeforeLazyModeIsNotTracked) {
    HotspotSupportTestAccessor::setLazyUsed(false);
    redefine(true);
    EXPECT_EQ(0u, HotspotSupportTestAccessor::registry().size());
}

// Outside a dump no class is pinned, so a lazy frame is never read.
TEST_F(HotspotLazyResolveTest, FrameIsRefusedOutsideADump) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    HotspotSupport::endDump();
    ResolvedMethod result;
    EXPECT_FALSE(HotspotSupport::resolve(frame.method, frame.bci, result));
}

// ClassPrepare registers nothing: a class enters the registry only when it is
// redefined, to hold its redefinition mark.
TEST_F(HotspotLazyResolveTest, ClassPrepareRegistersNothing) {
    ASSERT_TRUE(HotspotSupportTestAccessor::registerClass(_jvm.jvmti(), _jvm.jni(), _jvm.mirror(_old_mirror)));
    EXPECT_EQ(0u, HotspotSupportTestAccessor::registry().size());
    registerClass(_old_mirror);
    redefine(false);
    EXPECT_EQ(1u, HotspotSupportTestAccessor::registry().size());
}

// A redefinition frees the class's old Method*s once they are off every
// stack, and a later redefinition of the same class can allocate a new method
// at the same address. The class, its mirror and its trace ID all
// stay the same, so nothing but the redefinition itself tells the frames
// apart: raw frames of a class marked before its redefinition are refused.
TEST_F(HotspotLazyResolveTest, FrameOfRedefinedClassIsRefused) {
    registerClass(_old_mirror);
    ASGCT_CallFrame before = sample();
    // Afterwards the Method* at the sampled address is (still, or again)
    // among the class's methods.
    redefine(true);
    EXPECT_FALSE(resolve(before));
    // Its later frames get jmethodIDs instead of being raw.
    EXPECT_EQ(1, _jvm.get_class_methods_calls);
}

// A redefinition JVMTI rejects (e.g. an unmodifiable class) changes nothing:
// the class's raw frames stay resolvable and no jmethodIDs are preloaded.
TEST_F(HotspotLazyResolveTest, FailedRedefinitionLeavesFramesResolvable) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    redefine(false);
    EXPECT_TRUE(resolvesToSpin(frame));
    EXPECT_EQ(0, _jvm.get_class_methods_calls);
}

// While the redefinition call runs, the methods may be swapped at any moment.
TEST_F(HotspotLazyResolveTest, FramesAreRefusedWhileRedefinitionRuns) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    HotspotSupportTestAccessor::beforeClassRedefinition(_jvm.jvmti(), _jvm.jni(), _jvm.mirror(_old_mirror));
    EXPECT_FALSE(resolve(frame));
    HotspotSupportTestAccessor::afterClassRedefinition(_jvm.jvmti(), _jvm.jni(), _jvm.mirror(_old_mirror), false);
    EXPECT_TRUE(resolvesToSpin(frame));
}

// Redefinitions are tracked in every mode once the registry has entries:
// raw frames of a lazy session can outlive a restart in another mode, and a
// later lazy session must not trust a class redefined in between.
TEST_F(HotspotLazyResolveTest, RedefinitionIsTrackedOutsideLazyMode) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    JVMSupportTestAccessor::setLoadState(JVMSupportTestAccessor::PartialLoaded());
    redefine(true);
    EXPECT_TRUE(HotspotSupportTestAccessor::registry().isRedefined(_jvm.jni(), _cls.klassPtr()));
    EXPECT_FALSE(resolve(frame));
    // The other modes load jmethodIDs their own way (JVMSupport).
    EXPECT_EQ(0, _jvm.get_class_methods_calls);
}

// The sampled class is unloaded and its Method* memory goes to a class loaded
// later at a different Klass* address. Reading the holder from the stale
// Method* now yields the new class, which is alive and lists the method.
TEST_F(HotspotLazyResolveTest, MethodMemoryReusedByClassAtOtherAddressDoesNotResolve) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();

    _jvm.collect(_old_mirror);
    static FakeKlass other_klass;
    static FakeMethodArray other_methods;
    other_klass = _cls.klass;
    other_klass.methods = &other_methods;
    other_klass.trace_id = ((_cls.klass.trace_id >> 16) + 41) << 16;
    other_methods = *_cls.klass.methods;
    _cls.cpool.holder = &other_klass;  // the reused Method* now belongs to it
    _new_mirror.klass = &other_klass;
    registerClass(_new_mirror);

    EXPECT_FALSE(resolve(frame));
}

// Tripwire for tag collisions: each dump reports how many of the classes it
// pins have a trace ID that no longer fits in the 25-bit tag, the point from
// which a stale frame could match a newer class by its tag.
TEST_F(HotspotLazyResolveTest, CountsClassesWithTraceIdBeyondTagRange) {
#ifndef COUNTERS
    GTEST_SKIP() << "debug counters are not compiled into this build";
#else
    _cls.klass.trace_id = ((uint64_t)(1u << 25) - 1) << 16;  // largest ID that still fits
    registerClass(_old_mirror);
    EXPECT_TRUE(resolve(sample()));
    EXPECT_EQ(0, Counters::getCounter(KLASS_TRACE_ID_BEYOND_TAG_RANGE));

    static FakeKlass big_klass;
    big_klass = _cls.klass;
    big_klass.trace_id = ((uint64_t)1 << 25) << 16;
    _new_mirror.klass = &big_klass;
    registerClass(_new_mirror);
    EXPECT_TRUE(resolve(sample()));
    EXPECT_EQ(1, Counters::getCounter(KLASS_TRACE_ID_BEYOND_TAG_RANGE));
    EXPECT_EQ(2, Counters::getCounter(LAZY_DUMP_CLASSES));
#endif
}

// A frame whose Method* metadata was freed after the sample (here: its
// ConstMethod pointer cleared) cannot even be traced to a class. It is
// refused and counted as unreadable, not as any of the registry outcomes.
TEST_F(HotspotLazyResolveTest, FrameWithFreedMethodIsCountedUnreadable) {
#ifndef COUNTERS
    GTEST_SKIP() << "debug counters are not compiled into this build";
#else
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    _jvm.collect(_old_mirror);
    _cls.method.const_method = nullptr;

    const CounterId registry_outcomes[] = {METHOD_RESOLVE_LAZY_UNLOADED, METHOD_RESOLVE_LAZY_STALE,
                                           METHOD_RESOLVE_LAZY_NOT_CURRENT, METHOD_RESOLVE_LAZY_CLASS_TOO_LARGE,
                                           METHOD_RESOLVE_LAZY_REDEFINED, METHOD_RESOLVE_LAZY_RESOLVED};
    long long before[6];
    for (int i = 0; i < 6; i++) {
        before[i] = Counters::getCounter(registry_outcomes[i]);
    }
    long long unreadable = Counters::getCounter(METHOD_RESOLVE_LAZY_UNREADABLE);

    EXPECT_FALSE(resolve(frame));

    EXPECT_EQ(unreadable + 1, Counters::getCounter(METHOD_RESOLVE_LAZY_UNREADABLE));
    for (int i = 0; i < 6; i++) {
        EXPECT_EQ(before[i], Counters::getCounter(registry_outcomes[i])) << "counter " << registry_outcomes[i];
    }
    _cls.method.const_method = &_cls.const_method;
#endif
}

// Lookup resolves each distinct raw method once per dump, however often it
// recurs, and whatever bci or frame type the occurrences carry.
TEST_F(HotspotLazyResolveTest, LookupResolvesEachRawMethodOncePerDump) {
    registerClass(_old_mirror);
    ASGCT_CallFrame a = sample();
    ASGCT_CallFrame b{};
    HotspotSupport::fillJavaFrame(b, FRAME_INTERPRETED, 42, nullptr, _cls.vmMethod());
    ASSERT_TRUE(FrameType::isRawPointer(b.bci));
    ASSERT_NE(a.bci, b.bci);

    StringDictionary classes;
    MethodMap methods;
    Lookup lookup(nullptr, &methods, &classes);
    beginDump();
#ifdef COUNTERS
    long long before = Counters::getCounter(METHOD_RESOLVE_LAZY_RESOLVED);
#endif
    MethodInfo* row = lookup.resolveMethod(a);
    ASSERT_NE(&lookup._unknown_method, row);
    EXPECT_EQ(lookup.getSymbol(FakeClass::METHOD_NAME), row->_name);
    EXPECT_EQ(lookup.getSymbol(FakeClass::SIGNATURE), row->_sig);
    EXPECT_EQ(row, lookup.resolveMethod(a));
    EXPECT_EQ(row, lookup.resolveMethod(b));
#ifdef COUNTERS
    EXPECT_EQ(1, Counters::getCounter(METHOD_RESOLVE_LAZY_RESOLVED) - before);
#endif

    // The next dump starts with an empty cache, resolves the frame again and
    // refills the same row.
    row->_mark = false;  // what writeMethods() does at the end of a chunk
    Lookup next(nullptr, &methods, &classes);
    beginDump();
    EXPECT_EQ(row, next.resolveMethod(a));
    EXPECT_TRUE(row->_mark);
#ifdef COUNTERS
    EXPECT_EQ(2, Counters::getCounter(METHOD_RESOLVE_LAZY_RESOLVED) - before);
#endif
    EXPECT_EQ(0, _jvm.get_class_methods_calls);
}

// Frames from two loads of a class at the same addresses carry different tags,
// so the cache keeps their outcomes apart.
TEST_F(HotspotLazyResolveTest, LookupCacheSeparatesFramesOfDifferentClassLoads) {
    registerClass(_old_mirror);
    ASGCT_CallFrame before = sample();
    loadNewClassAtSameAddress();
    ASGCT_CallFrame after = sample();

    StringDictionary classes;
    MethodMap methods;
    Lookup lookup(nullptr, &methods, &classes);
    beginDump();
    EXPECT_EQ(&lookup._unknown_method, lookup.resolveMethod(before));
    MethodInfo* row = lookup.resolveMethod(after);
    EXPECT_NE(&lookup._unknown_method, row);
    EXPECT_EQ(&lookup._unknown_method, lookup.resolveMethod(before));
    EXPECT_EQ(row, lookup.resolveMethod(after));
}

