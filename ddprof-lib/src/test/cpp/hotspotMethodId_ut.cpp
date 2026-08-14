/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "../../main/cpp/flightRecorder.h"
#include "../../main/cpp/hotspot/hotspotSupport.h"
#include "../../main/cpp/hotspot/vmStructs.h"

#include <cstdint>
#include <cstring>

// Test-only friend accessor for VM internals. It exists solely so this test
// can exercise HotSpot's rejected-jmethodID handling.
class VMTestAccessor {
public:
    static bool getHotspot() { return VM::_hotspot; }
    static void setHotspot(bool value) { VM::_hotspot = value; }
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
    EXPECT_NE(info->_key, 0U);  // still needs a pool id to be referenceable
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
