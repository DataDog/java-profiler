/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "../../main/cpp/frame.h"
#include "../../main/cpp/hotspot/hotspotSupport.h"
#include "../../main/cpp/hotspot/klassRegistry.h"
#include "../../main/cpp/hotspot/vmStructs.h"
#include "../../main/cpp/jvmSupport.h"
#include "../../main/cpp/profiler.h"
#include "../../main/cpp/threadLocalData.inline.h"
#include "../../main/cpp/vmEntry.h"

#include <cstdint>
#include <cstring>
#include <set>

// fjmethodid=lazy end to end, without a JVM: a raw Method* frame is captured
// with HotspotSupport::fillJavaFrame() exactly as walkVM does, the class's
// registry entry is manipulated the way ClassPrepare and class unloading
// would, and the frame is resolved with HotspotSupport::resolve() as the dump
// thread does.
//
// The metadata is fake but laid out the way the offsets below tell
// VMStructs to read it: Method -> ConstMethod -> ConstantPool -> Klass, with
// the Klass holding both its jmethodID cache and its methods array. None of
// it is ever freed, so no fault handling is needed and the tests run on every
// platform.
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
};

class JVMSupportTestAccessor {
public:
    using LoadState = JVMSupport::JMethodIDLoadStats;
    static LoadState getLoadState() { return JVMSupport::getLoadState(); }
    static void setLoadState(LoadState s) { JVMSupport::setLoadState(s); }
    static constexpr LoadState LazyLoaded() { return JVMSupport::Lazy_loaded; }
};

class HotspotSupportTestAccessor {
public:
    static KlassRegistry& registry() { return HotspotSupport::_klass_registry; }
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
        uint64_t method_size, const_method_size, constant_pool_size, klass_size;
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
            VMStructs::TYPE_SIZE_NAME(VMMethod),
            VMStructs::TYPE_SIZE_NAME(VMConstMethod),
            VMStructs::TYPE_SIZE_NAME(VMConstantPool),
            VMStructs::TYPE_SIZE_NAME(VMKlass),
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
        VMStructs::TYPE_SIZE_NAME(VMMethod) = s.method_size;
        VMStructs::TYPE_SIZE_NAME(VMConstMethod) = s.const_method_size;
        VMStructs::TYPE_SIZE_NAME(VMConstantPool) = s.constant_pool_size;
        VMStructs::TYPE_SIZE_NAME(VMKlass) = s.klass_size;
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
    uint16_t pad[3];
};

struct FakeConstantPool {
    void* holder;
};

// jmethodID cache: [length (i32), padding, id[0], id[1], ...].
struct FakeIdCache {
    int32_t len;
    int32_t pad;
    jmethodID slots[2];
};

// HotSpot's Array<Method*>: int length, then pointer-aligned elements.
struct FakeMethodArray {
    int32_t len;
    int32_t pad;
    void* data[2];
};

struct FakeKlass {
    FakeIdCache* ids;
    FakeMethodArray* methods;
};

const VMStructsTestAccessor::State LAYOUT = {
    /*method_constmethod*/    (int)offsetof(FakeMethod, const_method),
    /*constmethod_constants*/ (int)offsetof(FakeConstMethod, cpool),
    /*constmethod_idnum*/     (int)offsetof(FakeConstMethod, idnum),
    /*pool_holder*/           (int)offsetof(FakeConstantPool, holder),
    /*jmethod_ids*/           (int)offsetof(FakeKlass, ids),
    /*methods*/               (int)offsetof(FakeKlass, methods),
    /*method_size*/           sizeof(FakeMethod),
    /*const_method_size*/     sizeof(FakeConstMethod),
    /*constant_pool_size*/    sizeof(FakeConstantPool),
    /*klass_size*/            sizeof(FakeKlass),
    /*can_dereference*/       true,
};

// One class with one method whose jmethodID already exists, so resolve()
// never needs JVMTI. Klass* and Method* addresses are those of these fields,
// which is what lets a test "reload" a class at the same addresses: it only
// has to register a new mirror for the same FakeKlass.
struct FakeClass {
    FakeMethod method;
    FakeConstMethod const_method;
    FakeConstantPool cpool;
    FakeKlass klass;
    FakeIdCache ids;
    FakeMethodArray methods;
    // A jmethodID is a pointer to a slot holding the Method*; validatedId()
    // checks exactly that when _can_dereference_jmethod_id is set.
    void* jmethod_id_slot;

    FakeClass() {
        memset(this, 0, sizeof(*this));
        method.const_method = &const_method;
        const_method.cpool = &cpool;
        const_method.idnum = 0;
        cpool.holder = &klass;
        klass.ids = &ids;
        klass.methods = &methods;
        methods.len = 1;
        methods.data[0] = &method;
        jmethod_id_slot = &method;
        ids.len = 1;
        ids.slots[0] = jmethodId();
    }

    const void* klassPtr() const { return &klass; }
    VMMethod* vmMethod() { return reinterpret_cast<VMMethod*>(&method); }
    jmethodID jmethodId() { return reinterpret_cast<jmethodID>(&jmethod_id_slot); }
};

// Fake JNI with weak-reference semantics, as in klassRegistry_ut.cpp, plus
// the JavaVM that VM::jni() goes through.
struct FakeObject {
    int id;
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
        _jni_env.functions = &_jni_tbl;
        _vm_tbl.GetEnv = &getEnv;
        _vm.functions = &_vm_tbl;
        VMTestAccessor::setVm(reinterpret_cast<JavaVM*>(&_vm));
    }

    ~FakeJvm() {
        VMTestAccessor::setVm(_saved_vm);
        for (FakeWeak* w : _weaks) {
            delete w;
        }
        s_instance = nullptr;
    }

    JNIEnv* jni() { return &_jni_env; }

    jclass mirror(FakeObject& obj) { return reinterpret_cast<jclass>(&obj); }

    // Class unloading as far as the registry can observe it: the mirror's
    // weak references are cleared.
    void collect(FakeObject& obj) {
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

    static jweak JNICALL newWeakGlobalRef(JNIEnv*, jobject obj) {
        FakeWeak* w = new FakeWeak{reinterpret_cast<FakeObject*>(s_instance->resolve(obj))};
        s_instance->_weaks.insert(w);
        return reinterpret_cast<jweak>(w);
    }
    static void JNICALL deleteWeakGlobalRef(JNIEnv*, jweak) {}
    static jboolean JNICALL isSameObject(JNIEnv*, jobject a, jobject b) {
        return s_instance->resolve(a) == s_instance->resolve(b) ? JNI_TRUE : JNI_FALSE;
    }
    static jobject JNICALL newLocalRef(JNIEnv*, jobject ref) { return s_instance->resolve(ref); }
    static void JNICALL deleteLocalRef(JNIEnv*, jobject) {}
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
    std::set<FakeWeak*> _weaks;
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
        // resolve() installs crash protection on the current ProfiledThread.
        ProfiledThread::initCurrentThread();
        ASSERT_NE(nullptr, ProfiledThread::current());
    }

    void TearDown() override {
        HotspotSupportTestAccessor::registry().clear(_jvm.jni());
        ProfiledThread::release();
        ProfilerTestAccessor::setForceJmethodID(Profiler::instance(), _saved_force);
        JVMSupportTestAccessor::setLoadState(_saved_state);
        VMTestAccessor::setHotspot(_saved_hotspot);
    }

    void registerClass(FakeObject& mirror) {
        ASSERT_TRUE(HotspotSupportTestAccessor::registry().add(_jvm.jni(), _cls.klassPtr(),
                                                               _jvm.mirror(mirror)));
    }

    // What walkVM stores for a frame of a class without a jmethodID yet.
    ASGCT_CallFrame sample() {
        ASGCT_CallFrame frame{};
        HotspotSupport::fillJavaFrame(frame, FRAME_JIT_COMPILED, 7, nullptr, _cls.vmMethod());
        EXPECT_TRUE(FrameType::isRawPointer(frame.bci));
        return frame;
    }

    // What Lookup::fillMethod() does with a raw frame at dump time.
    static jmethodID resolve(const ASGCT_CallFrame& frame) {
        return HotspotSupport::resolve(frame.method, frame.bci);
    }
};

TEST_F(HotspotLazyResolveTest, LiveClassResolves) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    EXPECT_EQ(_cls.jmethodId(), resolve(frame));
}

TEST_F(HotspotLazyResolveTest, UnloadedClassDoesNotResolve) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    _jvm.collect(_old_mirror);
    EXPECT_EQ(nullptr, resolve(frame));
}

// The old class is unloaded and a new one is registered at the same Klass*,
// with its method at the same Method* address. The frame was sampled from the
// old class, so it must not resolve to the new class's method.
TEST_F(HotspotLazyResolveTest, FrameFromBeforeKlassReuseDoesNotResolveToNewClass) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();

    _jvm.collect(_old_mirror);
    registerClass(_new_mirror);

    EXPECT_EQ(nullptr, resolve(frame));
}

// Same, but the dead entry was purged by a registry rehash before the new
// class arrived, so the new class's registration looks like a first insert
// rather than a replacement.
TEST_F(HotspotLazyResolveTest, FrameFromBeforeKlassReuseAfterPurgeDoesNotResolveToNewClass) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    _jvm.collect(_old_mirror);

    // Enough other classes to push the table past its initial capacity's load
    // factor, so the dead entry is purged.
    static FakeObject others[1024];
    KlassRegistry& registry = HotspotSupportTestAccessor::registry();
    for (size_t i = 0; i < 1024; i++) {
        others[i].id = 100 + (int)i;
        const void* key = reinterpret_cast<const void*>(0x100000 + i * 0x200);
        ASSERT_TRUE(registry.add(_jvm.jni(), key, _jvm.mirror(others[i])));
    }
    ASSERT_EQ(nullptr, registry.pin(_jvm.jni(), _cls.klassPtr(), registry.epoch()))
        << "the dead entry should be gone, purged or at least unpinnable";

    registerClass(_new_mirror);

    EXPECT_EQ(nullptr, resolve(frame));
}

// Frames sampled from the new class after the reuse must still resolve.
TEST_F(HotspotLazyResolveTest, FrameFromAfterKlassReuseResolves) {
    registerClass(_old_mirror);
    _jvm.collect(_old_mirror);
    registerClass(_new_mirror);

    ASGCT_CallFrame frame = sample();
    EXPECT_EQ(_cls.jmethodId(), resolve(frame));
}

// A frame from the old class and one from the new class must be told apart
// already at capture time; otherwise the call trace storage merges them into
// one trace before resolve() ever runs.
TEST_F(HotspotLazyResolveTest, FramesFromBeforeAndAfterKlassReuseDiffer) {
    registerClass(_old_mirror);
    ASGCT_CallFrame before = sample();
    _jvm.collect(_old_mirror);
    registerClass(_new_mirror);
    ASGCT_CallFrame after = sample();

    EXPECT_FALSE(before.bci == after.bci && before.method == after.method);
}
