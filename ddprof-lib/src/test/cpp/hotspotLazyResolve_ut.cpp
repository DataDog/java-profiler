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
    uint64_t trace_id;  // JFR encoding: (id << 16) | tag bits
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
        klass.trace_id = (uint64_t)1000 << 16;
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
    const void* klass = nullptr;  // what java.lang.Class.klass holds, for mirrors
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

    // KlassRegistry::pin() calls NewLocalRef once per resolution.
    int new_local_ref_calls = 0;
    int get_class_methods_calls = 0;

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
    static jobject JNICALL newLocalRef(JNIEnv*, jobject ref) {
        s_instance->new_local_ref_calls++;
        return s_instance->resolve(ref);
    }
    static void JNICALL deleteLocalRef(JNIEnv*, jobject) {}
    // VMKlass::fromJavaClass() reads java.lang.Class.klass through this.
    static jlong JNICALL getLongField(JNIEnv*, jobject obj, jfieldID) {
        return (jlong)(uintptr_t)reinterpret_cast<FakeObject*>(obj)->klass;
    }
    // A jmethodID preload (loadMethodIDsIfNeededImpl()); the fake class's IDs
    // already exist, so only the call is recorded.
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
    }

    void TearDown() override {
        HotspotSupportTestAccessor::registry().clear(_jvm.jni());
        ProfiledThread::release();
        KlassTraceId::setOffsetForTest(_saved_trace_id_offset);
        ProfilerTestAccessor::setForceJmethodID(Profiler::instance(), _saved_force);
        JVMSupportTestAccessor::setLoadState(_saved_state);
        VMTestAccessor::setHotspot(_saved_hotspot);
    }

    void registerClass(FakeObject& mirror) {
        ASSERT_TRUE(HotspotSupportTestAccessor::registry().add(_jvm.jni(), _cls.klassPtr(),
                                                               _jvm.mirror(mirror)));
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

    loadNewClassAtSameAddress();

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
    ASSERT_EQ(nullptr, registry.pin(_jvm.jni(), _cls.klassPtr()))
        << "the dead entry should be gone, purged or at least unpinnable";

    _cls.klass.trace_id = ((_cls.klass.trace_id >> 16) + 37) << 16;  // the new class's ID
    registerClass(_new_mirror);

    EXPECT_EQ(nullptr, resolve(frame));
}

// Frames sampled from the new class after the reuse must still resolve.
TEST_F(HotspotLazyResolveTest, FrameFromAfterKlassReuseResolves) {
    registerClass(_old_mirror);
    loadNewClassAtSameAddress();

    ASGCT_CallFrame frame = sample();
    EXPECT_EQ(_cls.jmethodId(), resolve(frame));
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

    static FakeObject other_old{10};
    static FakeObject other_new{11};
    const void* other_klass = reinterpret_cast<const void*>(0x200000);
    KlassRegistry& registry = HotspotSupportTestAccessor::registry();
    ASSERT_TRUE(registry.add(_jvm.jni(), other_klass, _jvm.mirror(other_old)));
    _jvm.collect(other_old);
    ASSERT_TRUE(registry.add(_jvm.jni(), other_klass, _jvm.mirror(other_new)));

    ASGCT_CallFrame after = sample();
    EXPECT_EQ(before.bci, after.bci);
    EXPECT_EQ(before.method, after.method);
    EXPECT_EQ(_cls.jmethodId(), resolve(after));
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
    EXPECT_EQ(_cls.jmethodId(), resolve(before));
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

// resolve() goes by the mode the frame was sampled in, not the current one:
// a lazy-mode frame kept across a restart in partial mode still resolves
// through the registry (partial mode's FindClass lookup cannot see classes of
// custom loaders).
TEST_F(HotspotLazyResolveTest, LazyFrameResolvesByRegistryAfterSwitchToPartialMode) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    ASSERT_NE(0u, FrameType::rawTag(frame.bci, frame.method) & HotspotSupportTestAccessor::traceIdTagBit());
    JVMSupportTestAccessor::setLoadState(JVMSupportTestAccessor::PartialLoaded());
    int before = _jvm.new_local_ref_calls;
    EXPECT_EQ(_cls.jmethodId(), resolve(frame));
    EXPECT_EQ(1, _jvm.new_local_ref_calls - before);
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
    EXPECT_EQ(nullptr, resolve(before));
    // Its later frames get jmethodIDs instead of being raw.
    EXPECT_EQ(1, _jvm.get_class_methods_calls);
}

// A redefinition JVMTI rejects (e.g. an unmodifiable class) changes nothing:
// the class's raw frames stay resolvable and no jmethodIDs are preloaded.
TEST_F(HotspotLazyResolveTest, FailedRedefinitionLeavesFramesResolvable) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    redefine(false);
    EXPECT_EQ(_cls.jmethodId(), resolve(frame));
    EXPECT_EQ(0, _jvm.get_class_methods_calls);
}

// While the redefinition call runs, the methods may be swapped at any moment.
TEST_F(HotspotLazyResolveTest, FramesAreRefusedWhileRedefinitionRuns) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    HotspotSupportTestAccessor::beforeClassRedefinition(_jvm.jvmti(), _jvm.jni(), _jvm.mirror(_old_mirror));
    EXPECT_EQ(nullptr, resolve(frame));
    HotspotSupportTestAccessor::afterClassRedefinition(_jvm.jvmti(), _jvm.jni(), _jvm.mirror(_old_mirror), false);
    EXPECT_EQ(_cls.jmethodId(), resolve(frame));
}

// Redefinitions are tracked in every mode once the registry has entries:
// raw frames of a lazy session can outlive a restart in another mode, and a
// later lazy session must not trust a class redefined in between.
TEST_F(HotspotLazyResolveTest, RedefinitionIsTrackedOutsideLazyMode) {
    registerClass(_old_mirror);
    ASGCT_CallFrame frame = sample();
    JVMSupportTestAccessor::setLoadState(JVMSupportTestAccessor::PartialLoaded());
    redefine(true);
    EXPECT_TRUE(HotspotSupportTestAccessor::registry().isRedefined(_cls.klassPtr()));
    EXPECT_EQ(nullptr, resolve(frame));
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
    ASSERT_TRUE(HotspotSupportTestAccessor::registry().add(_jvm.jni(), &other_klass,
                                                           _jvm.mirror(_new_mirror)));

    EXPECT_EQ(nullptr, resolve(frame));
}

// Tripwire for tag collisions: counts registrations of classes whose trace
// ID no longer fits in the 25-bit tag, the first point at which a stale frame
// could match a newer class by its tag.
TEST_F(HotspotLazyResolveTest, CountsClassesWithTraceIdBeyondTagRange) {
#ifndef COUNTERS
    GTEST_SKIP() << "debug counters are not compiled into this build";
#else
    long long before = Counters::getCounter(KLASS_TRACE_ID_BEYOND_TAG_RANGE);
    _cls.klass.trace_id = ((uint64_t)(1u << 25) - 1) << 16;  // largest ID that still fits
    ASSERT_TRUE(HotspotSupportTestAccessor::registerClass(_jvm.jvmti(), _jvm.jni(), _jvm.mirror(_old_mirror)));
    EXPECT_EQ(before, Counters::getCounter(KLASS_TRACE_ID_BEYOND_TAG_RANGE));

    static FakeKlass big_klass;
    big_klass = _cls.klass;
    big_klass.trace_id = ((uint64_t)1 << 25) << 16;
    _new_mirror.klass = &big_klass;
    ASSERT_TRUE(HotspotSupportTestAccessor::registerClass(_jvm.jvmti(), _jvm.jni(), _jvm.mirror(_new_mirror)));
    EXPECT_EQ(before + 1, Counters::getCounter(KLASS_TRACE_ID_BEYOND_TAG_RANGE));
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
    int before = _jvm.new_local_ref_calls;
    EXPECT_EQ(_cls.jmethodId(), lookup.resolveRawMethod(a));
    EXPECT_EQ(_cls.jmethodId(), lookup.resolveRawMethod(a));
    EXPECT_EQ(_cls.jmethodId(), lookup.resolveRawMethod(b));
    EXPECT_EQ(1, _jvm.new_local_ref_calls - before);

    // The next dump starts with an empty cache.
    Lookup next(nullptr, &methods, &classes);
    EXPECT_EQ(_cls.jmethodId(), next.resolveRawMethod(a));
    EXPECT_EQ(2, _jvm.new_local_ref_calls - before);
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
    EXPECT_EQ(nullptr, lookup.resolveRawMethod(before));
    EXPECT_EQ(_cls.jmethodId(), lookup.resolveRawMethod(after));
    EXPECT_EQ(nullptr, lookup.resolveRawMethod(before));
}

