/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "../../main/cpp/hotspot/vmStructs.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <initializer_list>

// Supplies exported table addresses through the real CodeCache/readSymbol path.
// Derivation exposes protected metadata initialization without changing production code.
class ContinuationMetadataTest : public ::testing::Test, protected VMStructs {
protected:
    struct Field {
        const char* type;
        const char* name;
        int32_t is_static;
        uint64_t offset;
        void* address;
    };

    struct Type {
        const char* name;
        uint64_t size;
    };

    struct JavaThreadLayout {
        uintptr_t state;
        void* continuation;
    };

    struct EntryLayout {
        void* parent;
    };

    CodeCache symbols{"continuation metadata fixture"};
    Field fields[4]{};
    Type types[2]{};
    void* barrier = nullptr;
    void* return_pc = nullptr;

    void SetUp() override {
        saved = {_libjvm, _thread_state_offset, _cont_entry_offset,
                 _cont_entry_parent_offset, _cont_return_barrier_addr,
                 _cont_entry_return_pc_addr, TYPE_SIZE_NAME(VMContinuationEntry)};
        _libjvm = &symbols;
        _thread_state_offset = -1;
        _cont_entry_offset = -1;
        _cont_entry_parent_offset = -1;
        _cont_return_barrier_addr = nullptr;
        _cont_entry_return_pc_addr = nullptr;
        TYPE_SIZE_NAME(VMContinuationEntry) = 0;

        addExport("gHotSpotVMStructs", structs_address);
        addExport("gHotSpotVMStructEntryArrayStride", structs_stride);
        addExport("gHotSpotVMStructEntryTypeNameOffset", field_type_offset);
        addExport("gHotSpotVMStructEntryFieldNameOffset", field_name_offset);
        addExport("gHotSpotVMStructEntryIsStaticOffset", field_static_offset);
        addExport("gHotSpotVMStructEntryOffsetOffset", field_offset_offset);
        addExport("gHotSpotVMStructEntryAddressOffset", field_address_offset);
        addExport("gHotSpotVMTypes", types_address);
        addExport("gHotSpotVMTypeEntryArrayStride", types_stride);
        addExport("gHotSpotVMTypeEntryTypeNameOffset", type_name_offset);
        addExport("gHotSpotVMTypeEntrySizeOffset", type_size_offset);
    }

    void TearDown() override {
        _libjvm = saved.libjvm;
        _thread_state_offset = saved.thread_state;
        _cont_entry_offset = saved.cont_entry;
        _cont_entry_parent_offset = saved.parent;
        _cont_return_barrier_addr = saved.barrier;
        _cont_entry_return_pc_addr = saved.return_pc;
        TYPE_SIZE_NAME(VMContinuationEntry) = saved.entry_size;
    }

    // Calls the production dispatcher on caller-supplied rows plus its null terminator.
    void parseFields(std::initializer_list<Field> rows) {
        ASSERT_LT(rows.size(), sizeof(fields) / sizeof(fields[0]));
        std::copy(rows.begin(), rows.end(), fields);
        fields[rows.size()] = {};
        structs_address = reinterpret_cast<uintptr_t>(fields);
        init_offsets_and_addresses();
    }

    void parseEntrySize(uint64_t size) {
        types[0] = {"ContinuationEntry", size};
        types_address = reinterpret_cast<uintptr_t>(types);
        init_type_sizes();
    }

private:
    struct Saved {
        CodeCache* libjvm;
        int thread_state;
        int cont_entry;
        int parent;
        void* barrier;
        void* return_pc;
        uint64_t entry_size;
    } saved{};

    uintptr_t structs_address = 0;
    uintptr_t structs_stride = sizeof(Field);
    uintptr_t field_type_offset = offsetof(Field, type);
    uintptr_t field_name_offset = offsetof(Field, name);
    uintptr_t field_static_offset = offsetof(Field, is_static);
    uintptr_t field_offset_offset = offsetof(Field, offset);
    uintptr_t field_address_offset = offsetof(Field, address);
    uintptr_t types_address = 0;
    uintptr_t types_stride = sizeof(Type);
    uintptr_t type_name_offset = offsetof(Type, name);
    uintptr_t type_size_offset = offsetof(Type, size);

    void addExport(const char* name, uintptr_t& value) {
        symbols.add(&value, sizeof(value), name);
    }
};

TEST_F(ContinuationMetadataTest, ReadsExistingJavaThreadField) {
    parseFields({{"JavaThread", "_thread_state", 0, offsetof(JavaThreadLayout, state), nullptr}});

    EXPECT_EQ(offsetof(JavaThreadLayout, state), _thread_state_offset);
}

TEST_F(ContinuationMetadataTest, ReadsContinuationEntryFields) {
    parseFields({{"ContinuationEntry", "_parent", 0, offsetof(EntryLayout, parent), nullptr},
                 {"ContinuationEntry", "_return_pc", 1, 0, &return_pc}});

    EXPECT_EQ(offsetof(EntryLayout, parent), _cont_entry_parent_offset);
    EXPECT_EQ(&return_pc, _cont_entry_return_pc_addr);
}

TEST_F(ContinuationMetadataTest, ReadsJavaThreadContinuationEntry) {
    parseEntrySize(64);
    parseFields({{"JavaThread", "_cont_entry", 0, offsetof(JavaThreadLayout, continuation), nullptr}});

    ASSERT_EQ(64u, VMContinuationEntry::type_size());
    EXPECT_EQ(offsetof(JavaThreadLayout, continuation), _cont_entry_offset)
        << "B01: the original JavaThread group must allow later continuation fields to be read";
}

TEST_F(ContinuationMetadataTest, ReadsThreadAliasContinuationEntry) {
    parseFields({{"Thread", "_cont_entry", 0, offsetof(JavaThreadLayout, continuation), nullptr}});

    EXPECT_EQ(offsetof(JavaThreadLayout, continuation), _cont_entry_offset)
        << "B01: the exported Thread alias must reach the continuation field group";
}

TEST_F(ContinuationMetadataTest, ReadsStubRoutinesContinuationReturnBarrier) {
    parseFields({{"StubRoutines", "_cont_returnBarrier", 1, 0, &barrier}});

    EXPECT_EQ(&barrier, _cont_return_barrier_addr)
        << "B01: the original StubRoutines group must allow its later continuation field";
}

TEST_F(ContinuationMetadataTest, MissingContinuationMetadataRemainsUnavailable) {
    parseFields({{"JavaThread", "_thread_state", 0, offsetof(JavaThreadLayout, state), nullptr}});

    EXPECT_EQ(-1, _cont_entry_offset);
    EXPECT_EQ(nullptr, _cont_return_barrier_addr);
    EXPECT_EQ(0u, VMContinuationEntry::type_size());
}

TEST_F(ContinuationMetadataTest, EntryFpUsesAlignedSizeWithoutPadding) {
    alignas(16) std::array<uintptr_t, 12> stack{};
    parseEntrySize(64);
    VMContinuationEntry* entry = VMContinuationEntry::cast_raw(stack.data());

    EXPECT_EQ(reinterpret_cast<uintptr_t>(&stack[8]), entry->entryFP());
}

TEST_F(ContinuationMetadataTest, EntryFpSkipsPaddingIn56ByteLayout) {
    // OpenJDK ContinuationEntry::size() rounds sizeof to 2*wordSize; entry_fp()
    // adds that size on x86 and aarch64. The installed JDK 27 exports sizeof=56.
    // https://github.com/openjdk/jdk/blob/jdk-25-ga/src/hotspot/share/runtime/continuationEntry.hpp
    // https://github.com/openjdk/jdk/blob/jdk-25-ga/src/hotspot/cpu/aarch64/continuationEntry_aarch64.inline.hpp
    alignas(16) std::array<uintptr_t, 12> stack{};
    uintptr_t saved_fp = reinterpret_cast<uintptr_t>(&stack[11]);
    uintptr_t saved_pc = reinterpret_cast<uintptr_t>(&barrier);
    stack[7] = 0xabad1dea;  // padding between the exported object size and the saved FP
    stack[8] = saved_fp;
    stack[9] = saved_pc;
    parseEntrySize(56);
    VMContinuationEntry* entry = VMContinuationEntry::cast_raw(stack.data());
    uintptr_t* actual_fp = reinterpret_cast<uintptr_t*>(entry->entryFP());

    EXPECT_EQ(reinterpret_cast<uintptr_t>(&stack[8]), entry->entryFP())
        << "B02: exported sizeof=56 needs an eight-byte pad before the entry frame";
    EXPECT_EQ(saved_fp, actual_fp[0]) << "entryFP must point at the saved frame pointer";
    EXPECT_EQ(saved_pc, actual_fp[1]) << "the following slot must contain the return address";
}
