/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "../../main/cpp/hotspot/vmStructs.h"
#include "referenceChainsTestAccessors.h"

#include <cstddef>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <vector>

// Drives VMStructs::init() and resolveOffsets() through fake exported vmStructs tables,
// as VM::ready() does on each of its calls, and checks that a rerun keeps every field a
// stack walker reads at its final value.
class VMStructsReinitTest : public ::testing::Test, protected VMStructs {
protected:
    struct Field {
        const char* type;
        const char* name;
        int32_t is_static;
        uint64_t offset;
        void* address;
    };

    struct IntConstant {
        const char* name;
        int32_t value;
    };

    struct FakeVirtualSpace {
        const void* low;
        const void* high;
    };

    struct FakeCodeHeap {
        FakeVirtualSpace memory;
        void* segmap;
        int log2_segment_size;
    };

    struct FakeHeapArray {
        int len;
        char** data;
    };

    static constexpr int kCallWrapperWords = -2;
    static constexpr int kDataOffset = 40;

    CodeCache symbols{"vmStructs reinit fixture"};
    std::vector<Field> fields;
    std::vector<IntConstant> constants;

    FakeCodeHeap heap{};
    char* heap_slots[1] = {reinterpret_cast<char*>(&heap)};
    FakeHeapArray heaps{1, heap_slots};
    FakeHeapArray* heaps_ptr = &heaps;    // CodeCache::_heaps (JDK 9+)
    FakeCodeHeap* heap_ptr = &heap;       // CodeCache::_heap (JDK 8)
    char code[64] = {};
    const void* low_bound = nullptr;      // CodeCache::_low_bound
    const void* high_bound = nullptr;     // CodeCache::_high_bound

    void SetUp() override {
        saveAll();
        // init_constants() scales the call-wrapper constant in place, and resolveOffsets()
        // merges bounds into the current ones, so both start from their initial values.
        _initialized = false;
        _libjvm = nullptr;
        _frame_entry_frame_call_wrapper_offset = -1;
        _code_heap_low = NO_MIN_ADDRESS;
        _code_heap_high = NO_MAX_ADDRESS;
        _code_heap[0] = _code_heap[1] = _code_heap[2] = nullptr;
        _code_heap_segment_shift = -1;
        _code_heap_addr = _code_heap_low_addr = _code_heap_high_addr = nullptr;
        _code_heap_log2_segment_size_offset = -1;
        _data_offset = -1;
        _nmethod_immutable_offset = -1;
        VMTestAccessor::setHotspot(false);
        VMTestAccessor::setHotspotVersion(-1);

        addExport("gHotSpotVMStructs", structs_address);
        addExport("gHotSpotVMStructEntryArrayStride", structs_stride);
        addExport("gHotSpotVMStructEntryTypeNameOffset", field_type_offset);
        addExport("gHotSpotVMStructEntryFieldNameOffset", field_name_offset);
        addExport("gHotSpotVMStructEntryIsStaticOffset", field_static_offset);
        addExport("gHotSpotVMStructEntryOffsetOffset", field_offset_offset);
        addExport("gHotSpotVMStructEntryAddressOffset", field_address_offset);
        addExport("gHotSpotVMIntConstants", constants_address);
        addExport("gHotSpotVMIntConstantEntryArrayStride", constants_stride);
        addExport("gHotSpotVMIntConstantEntryNameOffset", constant_name_offset);
        addExport("gHotSpotVMIntConstantEntryValueOffset", constant_value_offset);
    }

    void TearDown() override {
        for (auto it = restores.rbegin(); it != restores.rend(); ++it) (*it)();
    }

    // CodeHeap rows shared by both CodeCache layouts.
    std::vector<Field> codeHeapRows() {
        return {
            {"CodeHeap", "_memory", 0, offsetof(FakeCodeHeap, memory), nullptr},
            {"CodeHeap", "_segmap", 0, offsetof(FakeCodeHeap, segmap), nullptr},
            {"CodeHeap", "_log2_segment_size", 0, offsetof(FakeCodeHeap, log2_segment_size), nullptr},
            {"HeapBlock::Header", "_used", 0, 0, nullptr},
            {"VirtualSpace", "_low_boundary", 0, offsetof(FakeVirtualSpace, low), nullptr},
            {"VirtualSpace", "_high_boundary", 0, offsetof(FakeVirtualSpace, high), nullptr},
        };
    }

    // JDK 9+ layout: a GrowableArray of heaps plus the static CodeCache bounds.
    std::vector<Field> segmentedRows() {
        std::vector<Field> rows = codeHeapRows();
        rows.push_back({"CodeCache", "_heaps", 1, 0, &heaps_ptr});
        rows.push_back({"CodeCache", "_low_bound", 1, 0, &low_bound});
        rows.push_back({"CodeCache", "_high_bound", 1, 0, &high_bound});
        rows.push_back({"GrowableArrayBase", "_len", 0, offsetof(FakeHeapArray, len), nullptr});
        rows.push_back({"GrowableArray<int>", "_data", 0, offsetof(FakeHeapArray, data), nullptr});
        return rows;
    }

    // JDK 8 layout: one CodeHeap whose VirtualSpace holds the bounds.
    std::vector<Field> jdk8Rows() {
        std::vector<Field> rows = codeHeapRows();
        rows.push_back({"CodeCache", "_heap", 1, 0, &heap_ptr});
        return rows;
    }

    // Runs the production init() on the given rows plus their null terminator.
    void init(std::vector<Field> rows, std::initializer_list<IntConstant> ints = {}) {
        fields = std::move(rows);
        fields.push_back({});
        structs_address = reinterpret_cast<uintptr_t>(fields.data());
        constants.assign(ints.begin(), ints.end());
        constants.push_back({});
        constants_address = reinterpret_cast<uintptr_t>(constants.data());
        VMStructs::init(&symbols);
    }

    // resolveOffsets() asserts HotSpot; versions below 21 skip the JDK 21+ symbol fallbacks.
    void resolve(int hotspot_version = 17) {
        VMTestAccessor::setHotspot(true);
        VMTestAccessor::setHotspotVersion(hotspot_version);
        resolveOffsets();
        VMTestAccessor::setHotspot(false);
        VMTestAccessor::setHotspotVersion(-1);
    }

private:
    std::vector<std::function<void()>> restores;
    uintptr_t structs_address = 0;
    uintptr_t structs_stride = sizeof(Field);
    uintptr_t field_type_offset = offsetof(Field, type);
    uintptr_t field_name_offset = offsetof(Field, name);
    uintptr_t field_static_offset = offsetof(Field, is_static);
    uintptr_t field_offset_offset = offsetof(Field, offset);
    uintptr_t field_address_offset = offsetof(Field, address);
    uintptr_t constants_address = 0;
    uintptr_t constants_stride = sizeof(IntConstant);
    uintptr_t constant_name_offset = offsetof(IntConstant, name);
    uintptr_t constant_value_offset = offsetof(IntConstant, value);

    template <typename T> void save(T& field) {
        T value = field;
        restores.push_back([&field, value]() { field = value; });
    }

    void saveAll() {
        save(_initialized);
        save(_libjvm);
        save(_frame_entry_frame_call_wrapper_offset);
        save(_code_heap_low);
        save(_code_heap_high);
        save(_code_heap[0]);
        save(_code_heap[1]);
        save(_code_heap[2]);
        save(_code_heap_segment_shift);
        save(_code_heap_addr);
        save(_code_heap_low_addr);
        save(_code_heap_high_addr);
        save(_code_heap_memory_offset);
        save(_code_heap_segmap_offset);
        save(_code_heap_log2_segment_size_offset);
        save(_heap_block_used_offset);
        save(_vs_low_bound_offset);
        save(_vs_high_bound_offset);
        save(_array_len_offset);
        save(_array_data_offset);
        save(_data_offset);
        save(_nmethod_immutable_offset);
        bool hotspot = VMTestAccessor::getHotspot();
        int hotspot_version = VMTestAccessor::getHotspotVersion();
        restores.push_back([hotspot_version]() { VMTestAccessor::setHotspotVersion(hotspot_version); });
        restores.push_back([hotspot]() { VMTestAccessor::setHotspot(hotspot); });
    }

    void addExport(const char* name, uintptr_t& value) {
        symbols.add(&value, sizeof(value), name);
    }
};

TEST_F(VMStructsReinitTest, SecondInitKeepsTableFields) {
    std::vector<Field> rows = segmentedRows();
    rows.push_back({"CodeBlob", "_data_offset", 0, kDataOffset, nullptr});
    rows.push_back({"nmethod", "_immutable_data", 0, 8, nullptr});
    init(rows, {{"frame::entry_frame_call_wrapper_offset", kCallWrapperWords}});
    const int log2_offset = _code_heap_log2_segment_size_offset;
    const int call_wrapper = _frame_entry_frame_call_wrapper_offset;
    ASSERT_EQ(static_cast<int>(offsetof(FakeCodeHeap, log2_segment_size)), log2_offset);
    ASSERT_EQ(kDataOffset, _data_offset);

    // A rerun that parsed again would pick up every changed value below.
    std::vector<Field> changed = segmentedRows();
    changed[2].offset = 0;
    changed.push_back({"CodeBlob", "_data_offset", 0, kDataOffset + 8, nullptr});
    init(changed, {{"frame::entry_frame_call_wrapper_offset", kCallWrapperWords - 1}});

    EXPECT_EQ(log2_offset, _code_heap_log2_segment_size_offset);
    EXPECT_EQ(kDataOffset, _data_offset) << "rerun must not reparse or re-force _data_offset";
    EXPECT_EQ(call_wrapper, _frame_entry_frame_call_wrapper_offset)
        << "rerun must not rescale the call-wrapper constant";
}

TEST_F(VMStructsReinitTest, InitWithoutLibraryStaysUninitialized) {
    VMStructs::init(nullptr);
    init(segmentedRows());

    EXPECT_EQ(static_cast<int>(offsetof(FakeCodeHeap, log2_segment_size)),
              _code_heap_log2_segment_size_offset)
        << "a call without libjvm must not mark the tables as parsed";
}

TEST_F(VMStructsReinitTest, DataOffsetForcedToZeroAtInitBeforeJdk23) {
    std::vector<Field> rows = segmentedRows();
    rows.push_back({"CodeBlob", "_data_offset", 0, kDataOffset, nullptr});
    init(rows);

    EXPECT_EQ(0, _data_offset) << "without _immutable_data (JDK < 23) init must store the final 0";
}

TEST_F(VMStructsReinitTest, AArch64CallWrapperOffsetFinalAtInit) {
#ifdef __aarch64__
    init(segmentedRows(), {{"frame::entry_frame_call_wrapper_offset", kCallWrapperWords}});

    EXPECT_EQ(-64, _frame_entry_frame_call_wrapper_offset)
        << "the aarch64 override must follow the word-size scaling";
#else
    GTEST_SKIP() << "the call-wrapper override exists only on aarch64";
#endif
}

TEST_F(VMStructsReinitTest, ResolveRereadsShiftFromLiveHeap) {
    heap.log2_segment_size = 6;
    init(segmentedRows());

    resolve();
    ASSERT_EQ(6, _code_heap_segment_shift);
    resolve();
    EXPECT_EQ(6, _code_heap_segment_shift) << "a rerun must not reinterpret the converted shift";

    heap.log2_segment_size = 7;
    resolve();
    EXPECT_EQ(7, _code_heap_segment_shift) << "each call must read the live heap";
}

TEST_F(VMStructsReinitTest, ResolveAcceptsShiftLimits) {
    init(segmentedRows());
    for (int shift : {0, 16}) {
        heap.log2_segment_size = shift;
        resolve();
        EXPECT_EQ(shift, _code_heap_segment_shift);
        EXPECT_EQ(reinterpret_cast<char*>(&heap), _code_heap[0]) << "shift " << shift;
    }
}

TEST_F(VMStructsReinitTest, ResolveRejectsInvalidShift) {
    init(segmentedRows());
    heap.log2_segment_size = 6;
    resolve();
    ASSERT_EQ(6, _code_heap_segment_shift);

    for (int shift : {-1, 17}) {
        heap.log2_segment_size = shift;
        resolve();
        EXPECT_EQ(nullptr, _code_heap[0]) << "shift " << shift << " must disable the code heap";
        EXPECT_EQ(6, _code_heap_segment_shift) << "an invalid shift must not be stored";
    }
}

TEST_F(VMStructsReinitTest, SegmentedAgentLoadThenVmInit) {
    // Agent_OnLoad: CodeCache::_heaps exists but is empty and the bounds are null.
    heaps.len = 0;
    heap.log2_segment_size = 6;
    init(segmentedRows());
    resolve();
    ASSERT_EQ(nullptr, _code_heap[0]);
    ASSERT_EQ(-1, _code_heap_segment_shift);
    EXPECT_EQ(NO_MIN_ADDRESS, _code_heap_low);

    // VMInit: the heaps and bounds are set up.
    heaps.len = 1;
    low_bound = code;
    high_bound = code + sizeof(code);
    resolve();
    EXPECT_EQ(reinterpret_cast<char*>(&heap), _code_heap[0]);
    EXPECT_EQ(6, _code_heap_segment_shift);
    EXPECT_EQ(static_cast<const void*>(code), _code_heap_low);
    EXPECT_EQ(static_cast<const void*>(code + sizeof(code)), _code_heap_high);
}

TEST_F(VMStructsReinitTest, ResolveWithoutSegmentSizeRowDisablesHeap) {
    std::vector<Field> rows = segmentedRows();
    rows.erase(rows.begin() + 2);
    heap.log2_segment_size = 6;
    init(rows);
    resolve();

    EXPECT_EQ(nullptr, _code_heap[0]);
    EXPECT_EQ(-1, _code_heap_segment_shift);
}

TEST_F(VMStructsReinitTest, Jdk8AgentLoadThenVmInit) {
    // Agent_OnLoad: the CodeHeap object exists but is not initialized yet.
    init(jdk8Rows());
    resolve(8);
    ASSERT_EQ(0, _code_heap_segment_shift);
    EXPECT_EQ(NO_MIN_ADDRESS, _code_heap_low) << "null JVM bounds must not be published";
    EXPECT_EQ(NO_MAX_ADDRESS, _code_heap_high);

    // VMInit: the heap is reserved.
    heap.log2_segment_size = 6;
    heap.memory = {code, code + sizeof(code)};
    resolve(8);
    EXPECT_EQ(6, _code_heap_segment_shift);
    EXPECT_EQ(static_cast<const void*>(code), _code_heap_low);
    EXPECT_EQ(static_cast<const void*>(code + sizeof(code)), _code_heap_high);
}

TEST_F(VMStructsReinitTest, ResolveSkipsNullBounds) {
    heap.log2_segment_size = 6;
    init(segmentedRows());
    resolve();
    EXPECT_EQ(NO_MIN_ADDRESS, _code_heap_low);
    EXPECT_EQ(NO_MAX_ADDRESS, _code_heap_high);

    low_bound = code;
    resolve();
    EXPECT_EQ(NO_MIN_ADDRESS, _code_heap_low) << "one null bound must skip both";
    EXPECT_EQ(NO_MAX_ADDRESS, _code_heap_high);
}

TEST_F(VMStructsReinitTest, ResolveKeepsWidenedBounds) {
    heap.log2_segment_size = 6;
    low_bound = code + 16;
    high_bound = code + 32;
    init(segmentedRows());
    resolve();
    ASSERT_EQ(static_cast<const void*>(code + 16), _code_heap_low);
    ASSERT_EQ(static_cast<const void*>(code + 32), _code_heap_high);

    CodeHeap::updateBounds(code, code + sizeof(code));
    resolve();
    EXPECT_EQ(static_cast<const void*>(code), _code_heap_low) << "a rerun must not narrow the bounds";
    EXPECT_EQ(static_cast<const void*>(code + sizeof(code)), _code_heap_high);
}
