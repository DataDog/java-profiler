/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "../../main/cpp/counters.h"
#include "../../main/cpp/hotspot/klassRegistry.h"
#include "../../main/cpp/hotspot/vmStructs.inline.h"

#include <cstddef>
#include <cstdint>
#include <set>
#include <vector>

// KlassRegistry only talks to the JVM through five JNI functions, so a fake
// JNIEnv models the reference semantics it relies on: a weak global reference
// resolves to its referent until the referent is "collected", after which
// NewLocalRef() returns NULL and IsSameObject(ref, NULL) is true.
namespace {

struct FakeObject {
    int id;
};

struct FakeWeak {
    FakeObject* referent;
    bool deleted;
};

struct FakeHeap {
    std::set<FakeWeak*> weaks;
    int new_weak_calls = 0;
    int delete_weak_calls = 0;
    int double_deletes = 0;

    ~FakeHeap() {
        for (FakeWeak* w : weaks) {
            delete w;
        }
    }

    jobject resolve(jobject ref) {
        FakeWeak* w = reinterpret_cast<FakeWeak*>(ref);
        if (weaks.count(w) != 0) {
            return reinterpret_cast<jobject>(w->referent);
        }
        return ref;
    }

    void collect(FakeObject* obj) {
        for (FakeWeak* w : weaks) {
            if (w->referent == obj) {
                w->referent = nullptr;
            }
        }
    }

    int liveWeaks() const {
        int n = 0;
        for (FakeWeak* w : weaks) {
            n += w->deleted ? 0 : 1;
        }
        return n;
    }
};

FakeHeap* g_heap = nullptr;

jweak JNICALL fakeNewWeakGlobalRef(JNIEnv*, jobject obj) {
    g_heap->new_weak_calls++;
    FakeWeak* w = new FakeWeak{reinterpret_cast<FakeObject*>(g_heap->resolve(obj)), false};
    g_heap->weaks.insert(w);
    return reinterpret_cast<jweak>(w);
}

void JNICALL fakeDeleteWeakGlobalRef(JNIEnv*, jweak ref) {
    g_heap->delete_weak_calls++;
    FakeWeak* w = reinterpret_cast<FakeWeak*>(ref);
    if (w->deleted) {
        g_heap->double_deletes++;
    }
    w->deleted = true;
}

jboolean JNICALL fakeIsSameObject(JNIEnv*, jobject a, jobject b) {
    return g_heap->resolve(a) == g_heap->resolve(b) ? JNI_TRUE : JNI_FALSE;
}

jobject JNICALL fakeNewLocalRef(JNIEnv*, jobject ref) {
    return g_heap->resolve(ref);
}

class KlassRegistryTest : public ::testing::Test {
protected:
    FakeHeap heap;
    JNINativeInterface_ jni_tbl{};
    JNIEnv_ jni_env{};
    JNIEnv* jni = nullptr;
    KlassRegistry registry;
    std::vector<FakeObject> mirrors;

    void SetUp() override {
        g_heap = &heap;
        jni_tbl.NewWeakGlobalRef = &fakeNewWeakGlobalRef;
        jni_tbl.DeleteWeakGlobalRef = &fakeDeleteWeakGlobalRef;
        jni_tbl.IsSameObject = &fakeIsSameObject;
        jni_tbl.NewLocalRef = &fakeNewLocalRef;
        jni_env.functions = &jni_tbl;
        jni = &jni_env;
        mirrors.resize(4096);
        for (size_t i = 0; i < mirrors.size(); i++) {
            mirrors[i].id = (int)i;
        }
    }

    void TearDown() override {
        registry.clear(jni);
        g_heap = nullptr;
    }

    // Klass* values are only used as keys; any distinct, 8-byte aligned
    // addresses will do.
    static const void* klassAt(size_t i) {
        return reinterpret_cast<const void*>(0x10000 + i * 0x200);
    }

    jclass mirror(size_t i) {
        return reinterpret_cast<jclass>(&mirrors[i]);
    }
};

} // namespace

TEST_F(KlassRegistryTest, UnknownKlassIsNotContained) {
    EXPECT_FALSE(registry.contains(jni, klassAt(0)));
    ASSERT_TRUE(registry.add(jni, klassAt(1), mirror(1)));
    EXPECT_FALSE(registry.contains(jni, klassAt(0)));
    EXPECT_FALSE(registry.contains(jni, nullptr));
}

TEST_F(KlassRegistryTest, RegisteredClassesAreContained) {
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(0)));
    ASSERT_TRUE(registry.add(jni, klassAt(1), mirror(1)));
    EXPECT_TRUE(registry.contains(jni, klassAt(0)));
    EXPECT_TRUE(registry.contains(jni, klassAt(1)));
}

TEST_F(KlassRegistryTest, CollectedClassIsNotContained) {
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(0)));
    heap.collect(&mirrors[0]);
    EXPECT_FALSE(registry.contains(jni, klassAt(0)));
}

TEST_F(KlassRegistryTest, ReAddingSameMirrorIsNoOp) {
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(0)));
    int calls = heap.new_weak_calls;
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(0)));
    EXPECT_EQ(calls, heap.new_weak_calls);
    EXPECT_EQ(1u, registry.size());
}

TEST_F(KlassRegistryTest, ReusedKlassAddressReplacesDeadEntry) {
    // A class is unloaded and a new one is registered at the same Klass*
    // address: the new class must win, and the old weak ref be freed.
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(0)));
    heap.collect(&mirrors[0]);
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(1)));
    EXPECT_TRUE(registry.contains(jni, klassAt(0)));
    EXPECT_EQ(1u, registry.size());
    EXPECT_EQ(1, heap.liveWeaks());
}

TEST_F(KlassRegistryTest, GrowthPurgesDeadEntries) {
    const size_t first = 700;
    for (size_t i = 0; i < first; i++) {
        ASSERT_TRUE(registry.add(jni, klassAt(i), mirror(i)));
    }
    // Unload all but the first ten.
    for (size_t i = 10; i < first; i++) {
        heap.collect(&mirrors[i]);
    }
    // Enough new classes to cross the 3/4 load factor of the initial table.
    const size_t more = 200;
    for (size_t i = first; i < first + more; i++) {
        ASSERT_TRUE(registry.add(jni, klassAt(i), mirror(i)));
    }

    EXPECT_LT(registry.size(), 10 + more + 1);
    EXPECT_EQ((int)registry.size(), heap.liveWeaks());
    EXPECT_EQ(0, heap.double_deletes);
    for (size_t i = 0; i < 10; i++) {
        EXPECT_TRUE(registry.contains(jni, klassAt(i))) << i;
    }
    for (size_t i = 10; i < first; i++) {
        EXPECT_FALSE(registry.contains(jni, klassAt(i))) << i;
    }
    for (size_t i = first; i < first + more; i++) {
        EXPECT_TRUE(registry.contains(jni, klassAt(i))) << i;
    }
}

// The table is invisible to NMT, so its size and its purges are reported as
// counters: here 690 of the first 700 classes are dead when the 769th
// registration crosses the 3/4 load factor of the initial 1024 slots.
TEST_F(KlassRegistryTest, CountersReportTableSizeAndPurges) {
#ifndef COUNTERS
    GTEST_SKIP() << "debug counters are not compiled into this build";
#else
    long long purged_before = Counters::getCounter(KLASS_REGISTRY_PURGED);
    const size_t first = 700;
    for (size_t i = 0; i < first; i++) {
        ASSERT_TRUE(registry.add(jni, klassAt(i), mirror(i)));
    }
    EXPECT_EQ(1024, Counters::getCounter(KLASS_REGISTRY_CAPACITY));
    EXPECT_EQ((long long)first, Counters::getCounter(KLASS_REGISTRY_ENTRIES));
    for (size_t i = 10; i < first; i++) {
        heap.collect(&mirrors[i]);
    }
    const size_t more = 200;
    for (size_t i = first; i < first + more; i++) {
        ASSERT_TRUE(registry.add(jni, klassAt(i), mirror(i)));
    }
    EXPECT_EQ(690, Counters::getCounter(KLASS_REGISTRY_PURGED) - purged_before);
    EXPECT_EQ(1024, Counters::getCounter(KLASS_REGISTRY_CAPACITY));
    EXPECT_EQ((long long)registry.size(), Counters::getCounter(KLASS_REGISTRY_ENTRIES));
    EXPECT_EQ(10 + (long long)more, Counters::getCounter(KLASS_REGISTRY_ENTRIES));

    registry.clear(jni);
    EXPECT_EQ(0, Counters::getCounter(KLASS_REGISTRY_CAPACITY));
    EXPECT_EQ(0, Counters::getCounter(KLASS_REGISTRY_ENTRIES));
#endif
}

TEST_F(KlassRegistryTest, GrowthKeepsAllLiveEntries) {
    const size_t n = 3000;
    for (size_t i = 0; i < n; i++) {
        ASSERT_TRUE(registry.add(jni, klassAt(i), mirror(i)));
    }
    EXPECT_EQ(n, registry.size());
    for (size_t i = 0; i < n; i++) {
        EXPECT_TRUE(registry.contains(jni, klassAt(i))) << i;
    }
}

TEST_F(KlassRegistryTest, ClearDeletesEveryWeakRef) {
    for (size_t i = 0; i < 50; i++) {
        ASSERT_TRUE(registry.add(jni, klassAt(i), mirror(i)));
    }
    registry.clear(jni);
    EXPECT_EQ(0u, registry.size());
    EXPECT_EQ(0, heap.liveWeaks());
    EXPECT_EQ(0, heap.double_deletes);
    EXPECT_FALSE(registry.contains(jni, klassAt(0)));
    // Usable again after clear().
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(0)));
    EXPECT_TRUE(registry.contains(jni, klassAt(0)));
}

// Redefinition: raw frames of a class are refused while a redefinition of it
// is in progress, and for good once one succeeded. A failed call leaves the
// class as it was.

TEST_F(KlassRegistryTest, SuccessfulRedefinitionIsRefusedForGood) {
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(0)));
    EXPECT_FALSE(registry.isRedefined(jni, klassAt(0)));
    ASSERT_TRUE(registry.beginRedefinition(klassAt(0)));
    EXPECT_TRUE(registry.isRedefined(jni, klassAt(0)));
    registry.endRedefinition(klassAt(0), true);
    EXPECT_TRUE(registry.isRedefined(jni, klassAt(0)));
    // Re-registering the same mirror does not clear the mark.
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(0)));
    EXPECT_TRUE(registry.isRedefined(jni, klassAt(0)));
}

TEST_F(KlassRegistryTest, RedefinitionInProgressIsRefused) {
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(0)));
    ASSERT_TRUE(registry.beginRedefinition(klassAt(0)));
    EXPECT_TRUE(registry.isRedefined(jni, klassAt(0)));
}

TEST_F(KlassRegistryTest, FailedRedefinitionLeavesClassAsBefore) {
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(0)));
    ASSERT_TRUE(registry.beginRedefinition(klassAt(0)));
    registry.endRedefinition(klassAt(0), false);
    EXPECT_FALSE(registry.isRedefined(jni, klassAt(0)));
    EXPECT_TRUE(registry.contains(jni, klassAt(0)));
}

TEST_F(KlassRegistryTest, OverlappingRedefinitionsAreTracked) {
    // Two calls on the same class overlap; the class stays refused until both
    // have returned, and a failure of one does not undo the other's success.
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(0)));
    ASSERT_TRUE(registry.beginRedefinition(klassAt(0)));
    ASSERT_TRUE(registry.beginRedefinition(klassAt(0)));
    registry.endRedefinition(klassAt(0), false);
    EXPECT_TRUE(registry.isRedefined(jni, klassAt(0)));
    registry.endRedefinition(klassAt(0), false);
    EXPECT_FALSE(registry.isRedefined(jni, klassAt(0)));

    ASSERT_TRUE(registry.beginRedefinition(klassAt(0)));
    ASSERT_TRUE(registry.beginRedefinition(klassAt(0)));
    registry.endRedefinition(klassAt(0), true);
    registry.endRedefinition(klassAt(0), false);
    EXPECT_TRUE(registry.isRedefined(jni, klassAt(0)));
}

TEST_F(KlassRegistryTest, RedefinitionOfUnregisteredClassIsIgnored) {
    EXPECT_FALSE(registry.beginRedefinition(klassAt(5)));
    registry.endRedefinition(klassAt(5), true);
    EXPECT_FALSE(registry.isRedefined(jni, klassAt(5)));
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(0)));
    EXPECT_FALSE(registry.beginRedefinition(klassAt(5)));
    // An unmatched end, e.g. for a class registered while the call ran, does
    // not underflow the count.
    registry.endRedefinition(klassAt(0), false);
    EXPECT_FALSE(registry.isRedefined(jni, klassAt(0)));
}

TEST_F(KlassRegistryTest, NewClassAtRedefinedClassAddressStartsUnmarked) {
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(0)));
    ASSERT_TRUE(registry.beginRedefinition(klassAt(0)));
    registry.endRedefinition(klassAt(0), true);
    heap.collect(&mirrors[0]);
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(1)));
    EXPECT_FALSE(registry.isRedefined(jni, klassAt(0)));
    EXPECT_TRUE(registry.contains(jni, klassAt(0)));
}

// The hooks never see this (the caller of RedefineClasses holds the class),
// but the registry alone does not rely on it: an end that finds a different
// class at the address does not mark it.
TEST_F(KlassRegistryTest, RedefinitionEndingAfterReplacementDoesNotMarkNewClass) {
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(0)));
    ASSERT_TRUE(registry.beginRedefinition(klassAt(0)));
    heap.collect(&mirrors[0]);
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(1)));
    registry.endRedefinition(klassAt(0), true);
    EXPECT_FALSE(registry.isRedefined(jni, klassAt(0)));
}

TEST_F(KlassRegistryTest, UnloadedClassIsReportedAbsent) {
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(0)));
    heap.collect(&mirrors[0]);
    EXPECT_FALSE(registry.contains(jni, klassAt(0)));
}

// Once a redefined class is unloaded, its mark is no longer reported, even
// before a new class at the same address replaces the entry: that class was
// never redefined.
TEST_F(KlassRegistryTest, MarkOfUnloadedClassIsNotReported) {
    ASSERT_TRUE(registry.add(jni, klassAt(0), mirror(0)));
    ASSERT_TRUE(registry.beginRedefinition(klassAt(0)));
    registry.endRedefinition(klassAt(0), true);
    ASSERT_TRUE(registry.isRedefined(jni, klassAt(0)));
    heap.collect(&mirrors[0]);
    EXPECT_FALSE(registry.isRedefined(jni, klassAt(0)));
}

// ---------------------------------------------------------------------------
// VMKlass::containsMethod() is what makes a Method* read from possibly-freed
// metadata trustworthy: it is only compared against the pinned class's
// current methods array, never dereferenced.
// ---------------------------------------------------------------------------

class VMStructsTestAccessor {
public:
    explicit VMStructsTestAccessor(int methods_offset) : _saved(VMStructs::_methods_offset) {
        VMStructs::_methods_offset = methods_offset;
    }
    ~VMStructsTestAccessor() { VMStructs::_methods_offset = _saved; }

private:
    int _saved;
};

namespace {

// Mirrors HotSpot's Array<Method*>: an int length, then pointer-aligned data.
struct FakeMethodArray {
    int length;
    const void* data[8];
};

struct FakeKlass {
    void* pad;
    FakeMethodArray* methods;
};

} // namespace

TEST(VMKlassContainsMethodTest, FindsCurrentMethodsOnly) {
    VMStructsTestAccessor layout(offsetof(FakeKlass, methods));
    int m[4];
    FakeMethodArray array = {3, {&m[0], &m[1], &m[2]}};
    FakeKlass klass = {nullptr, &array};
    VMKlass* vk = VMKlass::cast_raw(&klass);

    // Correct hint, wrong hint, and no hint all find a current method.
    EXPECT_TRUE(vk->containsMethod(&m[1], 1));
    EXPECT_TRUE(vk->containsMethod(&m[1], 0));
    EXPECT_TRUE(vk->containsMethod(&m[2], -1));
    // An out-of-range hint (stale idnum) must not read past the array.
    EXPECT_TRUE(vk->containsMethod(&m[0], 7));
    // A method that is not (or no longer) in the array.
    EXPECT_FALSE(vk->containsMethod(&m[3], 3));
    EXPECT_FALSE(vk->containsMethod(&m[3], -1));
}

TEST(VMKlassContainsMethodTest, NoMethodsArray) {
    VMStructsTestAccessor layout(offsetof(FakeKlass, methods));
    FakeKlass klass = {nullptr, nullptr};
    int m;
    EXPECT_FALSE(VMKlass::cast_raw(&klass)->containsMethod(&m, 0));
}

// A method that is not at its idnum's slot (e.g. after default-method
// overpasses were merged in at link time) is still found by a scan in small
// classes, but not in classes beyond MAX_METHODS_SCANNED.
TEST(VMKlassContainsMethodTest, ScanIsCappedForLargeClasses) {
    VMStructsTestAccessor layout(offsetof(FakeKlass, methods));
    for (int count : {10, VMKlass::MAX_METHODS_SCANNED, VMKlass::MAX_METHODS_SCANNED + 1, 1000}) {
        // Array<Method*>: int length, padding, then `count` pointers.
        std::vector<uintptr_t> array(1 + count, 0);
        *reinterpret_cast<int32_t*>(array.data()) = count;
        std::vector<int> methods(count);
        for (int i = 0; i < count; i++) {
            array[1 + i] = reinterpret_cast<uintptr_t>(&methods[i]);
        }
        FakeKlass klass = {nullptr, reinterpret_cast<FakeMethodArray*>(array.data())};
        VMKlass* vk = VMKlass::cast_raw(&klass);
        const void* m = &methods[count / 2];
        EXPECT_TRUE(vk->containsMethod(m, count / 2)) << count;
        bool scanned = count <= VMKlass::MAX_METHODS_SCANNED;
        bool not_scanned = false;
        EXPECT_EQ(scanned, vk->containsMethod(m, 0, &not_scanned)) << count;
        EXPECT_EQ(!scanned, not_scanned) << count;
        not_scanned = false;
        EXPECT_EQ(scanned, vk->containsMethod(m, -1, &not_scanned)) << count;
        EXPECT_EQ(!scanned, not_scanned) << count;
        // A method found at its idnum, or absent from a scanned class, is not
        // reported as unscanned.
        not_scanned = false;
        EXPECT_TRUE(vk->containsMethod(m, count / 2, &not_scanned)) << count;
        EXPECT_FALSE(not_scanned) << count;
    }
}
