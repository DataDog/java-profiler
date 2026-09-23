/*
 * Copyright 2026, Datadog, Inc
 */

#include <gtest/gtest.h>
#include "../../main/cpp/hotspot/hotspotSupport.h"
#include "../../main/cpp/hotspot/vmStructs.h"
#include "../../main/cpp/gtest_crash_handler.h"
#include "../../main/cpp/threadLocalData.h"
#include "../../main/cpp/vmEntry.h"

#include <cstddef>
#include <cstdint>

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
    static bool loadMethodIDsIfNeededImpl(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass, bool load_all, bool force_patch) {
        return HotspotSupport::loadMethodIDsIfNeededImpl(jvmti, jni, klass, load_all, force_patch);
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
        &mock_jvmti, /*jni=*/nullptr, fake_klass, /*load_all=*/true, /*force_patch=*/false);

    EXPECT_TRUE(result);
    EXPECT_EQ(1, g_get_class_methods_calls)
        << "the <clinit> resolve() fallback must go through this exact path "
           "(load_all=true), which is what now applies patchClassLoaderData() "
           "before allocating jmethodIDs";
}

// ---------------------------------------------------------------------------
// patchClassLoaderData() tag/resume regression tests
//
// patchClassLoaderData() (the JDK-8062116 preallocation workaround, only
// active on JDK 8) tags each jclass with how many of its methods have
// already been preallocated into the ClassLoaderData-wide MethodList, so a
// replayed ClassPrepare (loadAllMethodIDsIfNeeded() on profiler restart)
// patches only the new tail [already_patched, method_count) -- or skips
// entirely when method_count hasn't grown -- instead of re-prepending a full
// set of blocks every time. RedefineClasses/RetransformClasses do not get
// this tag-based skip (force_patch=true): they invalidate existing
// jmethodIDs even when method_count is unchanged, so the tag alone cannot
// tell patchClassLoaderData() whether fresh capacity is still needed. The
// test above never exercises this: it leaves VM::hotspot_version() at its
// gtest-binary default (not 8), so patchClassLoaderData() is a no-op there.
// These tests force hotspot_version 8 and fake the VMKlass/VMClassLoaderData
// memory layout so the tag/resume loop itself runs.
// ---------------------------------------------------------------------------

// Friend of VM: lets these tests force isHotspot()/hotspot_version()==8 and
// swap VM::jvmti() for a mock. patchClassLoaderData() reads VM::jvmti()
// directly -- not the jvmti argument threaded through
// loadMethodIDsIfNeededImpl -- for GetTag/SetTag, so both must point at the
// same mock.
class VMTestAccessor {
public:
    static bool getHotspot() { return VM::_hotspot; }
    static void setHotspot(bool v) { VM::_hotspot = v; }
    static int getHotspotVersion() { return VM::_hotspot_version; }
    static void setHotspotVersion(int v) { VM::_hotspot_version = v; }
    static jvmtiEnv* getJvmti() { return VM::_jvmti; }
    static void setJvmti(jvmtiEnv* env) { VM::_jvmti = env; }
};

// Friend of VMStructs: lets these tests point VMKlass::methodCount()/
// classLoaderData() and VMClassLoaderData::lock()/unlock()/methodList() at a
// fake in-memory layout instead of real HotSpot metadata.
class VMStructsTestAccessor {
public:
    struct State {
        bool has_class_loader_data;
        int methods_offset;
        int class_loader_data_offset;
        uint64_t vmklass_size;
        uint64_t vmcld_size;
        VMStructs::LockFunc lock_func;
        VMStructs::LockFunc unlock_func;
    };

    static State save() {
        return State{
            VMStructs::_has_class_loader_data,
            VMStructs::_methods_offset,
            VMStructs::_class_loader_data_offset,
            VMStructs::TYPE_SIZE_NAME(VMKlass),
            VMStructs::TYPE_SIZE_NAME(VMClassLoaderData),
            VMStructs::_lock_func,
            VMStructs::_unlock_func,
        };
    }

    static void apply(const State& s) {
        VMStructs::_has_class_loader_data = s.has_class_loader_data;
        VMStructs::_methods_offset = s.methods_offset;
        VMStructs::_class_loader_data_offset = s.class_loader_data_offset;
        VMStructs::TYPE_SIZE_NAME(VMKlass) = s.vmklass_size;
        VMStructs::TYPE_SIZE_NAME(VMClassLoaderData) = s.vmcld_size;
        VMStructs::_lock_func = s.lock_func;
        VMStructs::_unlock_func = s.unlock_func;
    }
};

// Friend of MethodList: patchClassLoaderData() prepends nodes to a private
// linked list with no production accessor. Walking _next is the only way to
// count how many nodes a given call actually prepended.
class MethodListTestAccessor {
public:
    static const MethodList* next(const MethodList* node) { return node->_next; }
};

static int methodListChainLength(const MethodList* head) {
    int n = 0;
    while (head != nullptr) {
        n++;
        head = MethodListTestAccessor::next(head);
    }
    return n;
}

namespace {

// Fake ClassLoaderData. VMClassLoaderData::mutex() and methodList() index at
// fixed byte offsets from `this` (sizeof(uintptr_t)*3 and *6+8 respectively)
// baked into vmStructs.h -- not offsets this test controls -- so the fake
// layout must match those exactly.
struct FakePatchCLD {
    alignas(sizeof(void*)) char pad0[sizeof(uintptr_t) * 3];
    void* mutex_ptr;  // consumed by mutex(); never dereferenced by the no-op lock/unlock mocks below.
    char pad1[sizeof(uintptr_t) * 6 + 8 - (sizeof(uintptr_t) * 3 + sizeof(void*))];
    MethodList* method_list_head;
};
static_assert(offsetof(FakePatchCLD, mutex_ptr) == sizeof(uintptr_t) * 3,
              "mutex() offset drifted");
static_assert(offsetof(FakePatchCLD, method_list_head) == sizeof(uintptr_t) * 6 + 8,
              "methodList() offset drifted");

// Fake VMKlass: a methods-table pointer (methodCount() masks its low 16
// bits) and a ClassLoaderData pointer, at offsets this test wires up via
// VMStructsTestAccessor.
struct FakePatchKlass {
    int* methods_table;
    FakePatchCLD* cld;
};

int g_lock_calls = 0;
int g_unlock_calls = 0;
void noopLock(void*) { g_lock_calls++; }
void noopUnlock(void*) { g_unlock_calls++; }

jlong g_tag = 0;
int g_get_tag_calls = 0;
int g_set_tag_calls = 0;
jlong g_last_set_tag_value = -1;

jvmtiError JNICALL mock_GetTag(jvmtiEnv*, jobject, jlong* tag_ptr) {
    g_get_tag_calls++;
    *tag_ptr = g_tag;
    return JVMTI_ERROR_NONE;
}
jvmtiError JNICALL mock_SetTag(jvmtiEnv*, jobject, jlong tag) {
    g_set_tag_calls++;
    g_tag = tag;
    g_last_set_tag_value = tag;
    return JVMTI_ERROR_NONE;
}

// Simulates a JVMTI implementation that fails GetTag but still writes through
// *tag_ptr (undefined by the spec, but not something callers may rely on
// being left untouched). The garbage value looks like "already fully
// patched" if a caller trusted it instead of falling back to 0 on error.
jvmtiError JNICALL mock_GetTag_garbage_on_error(jvmtiEnv*, jobject, jlong* tag_ptr) {
    g_get_tag_calls++;
    *tag_ptr = 999999;
    return JVMTI_ERROR_INVALID_OBJECT;
}

FakePatchKlass* g_fake_klass_for_jni = nullptr;

jlong JNICALL mock_GetLongField(JNIEnv*, jobject, jfieldID) {
    return (jlong)(intptr_t)g_fake_klass_for_jni;
}

} // namespace

class PatchClassLoaderDataTest : public ::testing::Test {
protected:
    jvmtiInterface_1_ tbl{};
    _jvmtiEnv mock_jvmti{};
    JNINativeInterface_ jni_tbl{};
    JNIEnv_ mock_jni{};

    FakePatchCLD fake_cld{};
    FakePatchKlass fake_klass{};
    int methods_header = 0;

    bool saved_hotspot = false;
    int saved_hotspot_version = 0;
    jvmtiEnv* saved_jvmti = nullptr;
    VMStructsTestAccessor::State saved_structs{};

    void SetUp() override {
        saved_hotspot = VMTestAccessor::getHotspot();
        saved_hotspot_version = VMTestAccessor::getHotspotVersion();
        saved_jvmti = VMTestAccessor::getJvmti();
        saved_structs = VMStructsTestAccessor::save();

        g_tag = 0;
        g_get_tag_calls = 0;
        g_set_tag_calls = 0;
        g_last_set_tag_value = -1;
        g_lock_calls = 0;
        g_unlock_calls = 0;
        g_get_class_methods_calls = 0;

        tbl = jvmtiInterface_1_{};
        tbl.GetTag = &mock_GetTag;
        tbl.SetTag = &mock_SetTag;
        tbl.GetClassMethods = &mock_GetClassMethods_ok;
        tbl.Deallocate = &mock_Deallocate_noop;
        mock_jvmti.functions = &tbl;

        jni_tbl = JNINativeInterface_{};
        jni_tbl.GetLongField = &mock_GetLongField;
        mock_jni.functions = &jni_tbl;

        fake_cld = FakePatchCLD{};
        fake_klass = FakePatchKlass{};
        fake_klass.cld = &fake_cld;
        fake_klass.methods_table = &methods_header;
        g_fake_klass_for_jni = &fake_klass;

        VMTestAccessor::setHotspot(true);
        VMTestAccessor::setHotspotVersion(8);
        VMTestAccessor::setJvmti(&mock_jvmti);

        VMStructsTestAccessor::State s = saved_structs;
        s.has_class_loader_data = true;
        s.methods_offset = (int)offsetof(FakePatchKlass, methods_table);
        s.class_loader_data_offset = (int)offsetof(FakePatchKlass, cld);
        s.vmklass_size = sizeof(FakePatchKlass);
        s.vmcld_size = sizeof(FakePatchCLD);
        s.lock_func = &noopLock;
        s.unlock_func = &noopUnlock;
        VMStructsTestAccessor::apply(s);
    }

    void TearDown() override {
        VMStructsTestAccessor::apply(saved_structs);
        VMTestAccessor::setJvmti(saved_jvmti);
        VMTestAccessor::setHotspotVersion(saved_hotspot_version);
        VMTestAccessor::setHotspot(saved_hotspot);
        g_fake_klass_for_jni = nullptr;
        ProfiledThread::release();
    }

    void setMethodCount(int count) { methods_header = count; }

    void callPatch(bool force_patch = false) {
        jclass fake_jclass = reinterpret_cast<jclass>(0x1);
        HotspotSupportTestAccessor::loadMethodIDsIfNeededImpl(
            &mock_jvmti, reinterpret_cast<JNIEnv*>(&mock_jni), fake_jclass, /*load_all=*/true, force_patch);
    }
};

// The simple case: nothing patched yet (tag defaults to 0), method_count is
// an exact multiple of MethodList::SIZE so already_patched lands exactly on
// method_count -- the boundary the next test replays.
TEST_F(PatchClassLoaderDataTest, FirstCallPatchesFromZeroAndTagsMethodCount) {
    setMethodCount(MethodList::SIZE);

    callPatch();

    EXPECT_EQ(1, g_get_tag_calls);
    EXPECT_EQ(1, g_set_tag_calls);
    EXPECT_EQ(MethodList::SIZE, g_last_set_tag_value);
    EXPECT_EQ(1, methodListChainLength(fake_cld.method_list_head));
    EXPECT_EQ(1, g_lock_calls);
    EXPECT_EQ(1, g_unlock_calls);
}

// The boundary case: a replayed call (same class, unchanged method_count)
// finds already_patched == method_count and must skip the patch block
// entirely -- no lock, no new MethodList node, no SetTag. A mutant that
// widens `method_count > already_patched` to `>=` would re-enter here.
TEST_F(PatchClassLoaderDataTest, SecondCallWithUnchangedMethodCountSkipsPatchEntirely) {
    setMethodCount(MethodList::SIZE);
    callPatch();
    ASSERT_EQ(1, methodListChainLength(fake_cld.method_list_head));
    ASSERT_EQ(MethodList::SIZE, g_tag);

    g_get_tag_calls = 0;
    g_set_tag_calls = 0;
    g_lock_calls = 0;
    g_unlock_calls = 0;

    callPatch();

    EXPECT_EQ(1, g_get_tag_calls);
    EXPECT_EQ(0, g_set_tag_calls)
        << "method_count == already_patched must skip the whole patch block, including SetTag";
    EXPECT_EQ(0, g_lock_calls) << "the ClassLoaderData lock must not be taken when nothing needs patching";
    EXPECT_EQ(1, methodListChainLength(fake_cld.method_list_head))
        << "no new MethodList node should be prepended when nothing changed";
}

// Simulates RedefineClasses/RetransformClasses re-invoking the patch on a
// class whose method_count hasn't changed since the first call -- see the
// file comment above for why force_patch must bypass the tag here. A mutant
// that let force_patch fall through to the GetTag-based skip would leave
// this second call a no-op -- exactly the bug this test guards against.
TEST_F(PatchClassLoaderDataTest, ForcePatchRepatchesEvenWithUnchangedMethodCount) {
    setMethodCount(MethodList::SIZE);
    callPatch(/*force_patch=*/false);
    ASSERT_EQ(1, methodListChainLength(fake_cld.method_list_head));
    ASSERT_EQ(MethodList::SIZE, g_tag);

    g_get_tag_calls = 0;
    g_set_tag_calls = 0;
    g_lock_calls = 0;
    g_unlock_calls = 0;

    callPatch(/*force_patch=*/true);

    EXPECT_EQ(0, g_get_tag_calls)
        << "force_patch must bypass the persisted tag entirely, not just override its outcome";
    EXPECT_EQ(1, g_lock_calls) << "a forced re-patch must take the ClassLoaderData lock";
    EXPECT_EQ(2, methodListChainLength(fake_cld.method_list_head))
        << "a forced re-patch must prepend fresh capacity even though method_count is unchanged";
    EXPECT_EQ(1, g_set_tag_calls);
    EXPECT_EQ(MethodList::SIZE, g_last_set_tag_value);
}

// Simulates a ClassPrepare replay where the class gained methods since the
// last patch (e.g. RetransformClasses): the second call must patch only the
// new tail [already_patched, method_count), not restart from 0. A mutant
// that restarts the loop at 0 would prepend 3 nodes on the second call
// (ceil(20/8)) instead of 2 (ceil((20-8)/8)), re-walking the already-patched
// [0, 8) range.
TEST_F(PatchClassLoaderDataTest, SecondCallPatchesOnlyNewMethodRange) {
    setMethodCount(MethodList::SIZE);  // 8
    callPatch();
    ASSERT_EQ(1, methodListChainLength(fake_cld.method_list_head));
    ASSERT_EQ(MethodList::SIZE, g_tag);

    setMethodCount(2 * MethodList::SIZE + 4);  // 20
    g_set_tag_calls = 0;

    callPatch();

    EXPECT_EQ(1, g_set_tag_calls);
    EXPECT_EQ(2 * MethodList::SIZE + MethodList::SIZE, g_last_set_tag_value);  // 24: next block boundary past 20
    EXPECT_EQ(3, methodListChainLength(fake_cld.method_list_head))
        << "second call must add exactly ceil((20-8)/8) = 2 new nodes on top of the first call's 1";
}

// Degraded case: VMKlass::classLoaderData() returns null (e.g. a klass whose
// CLD pointer field hasn't settled yet). patchClassLoaderData() must bail out
// before taking the CLD lock or touching the tag -- there is nothing to patch
// and nothing to record. A mutant that removed the cld==nullptr guard would
// dereference a null FakePatchCLD* here and crash under the gtest crash
// handler installed at file scope.
TEST_F(PatchClassLoaderDataTest, NullClassLoaderDataSkipsPatchAndSetTag) {
    fake_klass.cld = nullptr;
    setMethodCount(MethodList::SIZE);

    callPatch();

    EXPECT_EQ(0, g_lock_calls) << "no ClassLoaderData to lock when cld is null";
    EXPECT_EQ(0, g_unlock_calls);
    EXPECT_EQ(0, g_set_tag_calls) << "nothing was patched, so no tag should be persisted";
}

// Degraded case: GetTag fails but still writes a garbage value through
// *tag_ptr. patchClassLoaderData() must not trust that value -- it has to
// fall back to already_patched=0 and patch the class from scratch, the same
// as if it had never been tagged. A mutant that used the garbage tag_ptr
// value regardless of the return code would treat 999999 as "already fully
// patched" and skip patching (and prepend 0 nodes) instead of 1.
TEST_F(PatchClassLoaderDataTest, GetTagFailureIgnoresGarbageAndRestartsFromZero) {
    tbl.GetTag = &mock_GetTag_garbage_on_error;
    setMethodCount(MethodList::SIZE);

    callPatch();

    EXPECT_EQ(1, g_get_tag_calls);
    EXPECT_EQ(1, g_lock_calls)
        << "a failed GetTag must not be mistaken for method_count <= already_patched";
    EXPECT_EQ(1, methodListChainLength(fake_cld.method_list_head))
        << "patching must restart from 0, not from the garbage *tag_ptr value";
    EXPECT_EQ(MethodList::SIZE, g_last_set_tag_value);
}

// Degraded case: VM::jvmti() is null (e.g. torn down mid-shutdown).
// patchClassLoaderData() still preallocates capacity defensively -- the CLD
// lock and MethodList prepend do not depend on JVMTI at all -- but it must
// skip GetTag/SetTag entirely rather than dereferencing a null jvmtiEnv*. A
// mutant that dropped the jvmti==nullptr checks would crash calling
// GetTag/SetTag through a null functions table.
TEST_F(PatchClassLoaderDataTest, NullVMJvmtiStillPatchesButSkipsSetTag) {
    VMTestAccessor::setJvmti(nullptr);
    setMethodCount(MethodList::SIZE);

    callPatch();

    EXPECT_EQ(0, g_get_tag_calls) << "GetTag must not be attempted when VM::jvmti() is null";
    EXPECT_EQ(1, g_lock_calls)
        << "the patch itself must still run even when the tag can't be read or written";
    EXPECT_EQ(1, methodListChainLength(fake_cld.method_list_head));
    EXPECT_EQ(0, g_set_tag_calls) << "SetTag must be skipped when VM::jvmti() is null";
}
