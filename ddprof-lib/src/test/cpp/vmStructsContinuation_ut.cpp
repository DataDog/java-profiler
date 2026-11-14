/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstddef>
#include "codeCache.h"
#include "hotspot/vmStructs.h"

class VMStructsTestAccessor {
    CodeCache* saved_lib = VMStructs::_libjvm;
    int saved_anchor = VMStructs::_thread_anchor_offset;
    int saved_cont_entry = VMStructs::_cont_entry_offset;
    void* saved_call_stub = VMStructs::_call_stub_return_addr;
    void* saved_barrier = VMStructs::_cont_return_barrier_addr;
    uint64_t saved_cont_entry_size = VMStructs::_VMContinuationEntry_size;

public:
    explicit VMStructsTestAccessor(CodeCache* lib) {
        VMStructs::_libjvm = lib;
        VMStructs::_thread_anchor_offset = -1;
        VMStructs::_cont_entry_offset = -1;
        VMStructs::_call_stub_return_addr = nullptr;
        VMStructs::_cont_return_barrier_addr = nullptr;
    }

    ~VMStructsTestAccessor() {
        VMStructs::_libjvm = saved_lib;
        VMStructs::_thread_anchor_offset = saved_anchor;
        VMStructs::_cont_entry_offset = saved_cont_entry;
        VMStructs::_call_stub_return_addr = saved_call_stub;
        VMStructs::_cont_return_barrier_addr = saved_barrier;
        VMStructs::_VMContinuationEntry_size = saved_cont_entry_size;
    }

    static void setContinuationSize(uint64_t size) { VMStructs::_VMContinuationEntry_size = size; }
    static void readFields() { VMStructs::init_offsets_and_addresses(); }
    static int anchor() { return VMStructs::_thread_anchor_offset; }
    static int contEntry() { return VMStructs::_cont_entry_offset; }
    static void* callStub() { return VMStructs::_call_stub_return_addr; }
    static void* barrier() { return VMStructs::_cont_return_barrier_addr; }
};

namespace {
struct Entry {
    const char* type;
    const char* field;
    int32_t is_static;
    uintptr_t offset;
    void* address;
};

// Exercise the actual exported-table reader, including its symbol indirection.
struct ExportedTable {
    CodeCache symbols{"vmStructs-continuation-fixture"};
    uintptr_t entries;
    uintptr_t stride = sizeof(Entry);
    uintptr_t type_offset = offsetof(Entry, type);
    uintptr_t field_offset = offsetof(Entry, field);
    uintptr_t static_offset = offsetof(Entry, is_static);
    uintptr_t offset_offset = offsetof(Entry, offset);
    uintptr_t address_offset = offsetof(Entry, address);

    explicit ExportedTable(Entry* table) : entries(reinterpret_cast<uintptr_t>(table)) {
        symbols.add(&entries, sizeof(entries), "gHotSpotVMStructs");
        symbols.add(&stride, sizeof(stride), "gHotSpotVMStructEntryArrayStride");
        symbols.add(&type_offset, sizeof(type_offset), "gHotSpotVMStructEntryTypeNameOffset");
        symbols.add(&field_offset, sizeof(field_offset), "gHotSpotVMStructEntryFieldNameOffset");
        symbols.add(&static_offset, sizeof(static_offset), "gHotSpotVMStructEntryIsStaticOffset");
        symbols.add(&offset_offset, sizeof(offset_offset), "gHotSpotVMStructEntryOffsetOffset");
        symbols.add(&address_offset, sizeof(address_offset), "gHotSpotVMStructEntryAddressOffset");
        symbols.sort();
    }
};
}

TEST(VMStructsContinuationTest, JavaThreadSupplementalFieldDoesNotStopAtPrimaryType) {
    Entry entries[] = {
        {"JavaThread", "_anchor", 0, 24, nullptr},
        {"JavaThread", "_unrecognized", 0, 48, nullptr},
        {"JavaThread", "_cont_entry", 0, 80, nullptr},
        {},
    };
    ExportedTable table(entries);
    VMStructsTestAccessor state(&table.symbols);
    VMStructsTestAccessor::readFields();
    EXPECT_EQ(24, VMStructsTestAccessor::anchor());
    EXPECT_EQ(80, VMStructsTestAccessor::contEntry());
}

TEST(VMStructsContinuationTest, StubRoutinesSupplementalAddressIsRead) {
    int call_stub = 0;
    int barrier = 0;
    Entry entries[] = {
        {"StubRoutines", "_call_stub_return_address", 1, 0, &call_stub},
        {"StubRoutines", "_cont_returnBarrier", 1, 0, &barrier},
        {},
    };
    ExportedTable table(entries);
    VMStructsTestAccessor state(&table.symbols);
    VMStructsTestAccessor::readFields();
    EXPECT_EQ(&call_stub, VMStructsTestAccessor::callStub());
    EXPECT_EQ(&barrier, VMStructsTestAccessor::barrier());
}

TEST(VMStructsContinuationTest, ContinuationEntryFPRoundsExportedSizeToTwoWords) {
    alignas(16) unsigned char entry[128] = {};
    VMStructsTestAccessor state(nullptr);
    VMStructsTestAccessor::setContinuationSize(7 * sizeof(uintptr_t));
    auto* continuation = VMContinuationEntry::cast_raw(entry);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(entry + 8 * sizeof(uintptr_t)), continuation->entryFP());
}

TEST(VMStructsContinuationTest, ContinuationEntryFPKeepsAlignedExportedSize) {
    alignas(16) unsigned char entry[128] = {};
    VMStructsTestAccessor state(nullptr);
    VMStructsTestAccessor::setContinuationSize(8 * sizeof(uintptr_t));
    auto* continuation = VMContinuationEntry::cast_raw(entry);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(entry + 8 * sizeof(uintptr_t)), continuation->entryFP());
}

TEST(VMStructsContinuationTest, AbsentSupplementalFieldsRetainUnavailableSentinels) {
    Entry entries[] = {{"JavaThread", "_anchor", 0, 24, nullptr}, {}};
    ExportedTable table(entries);
    VMStructsTestAccessor state(&table.symbols);
    VMStructsTestAccessor::readFields();
    EXPECT_EQ(24, VMStructsTestAccessor::anchor());
    EXPECT_EQ(-1, VMStructsTestAccessor::contEntry());
    EXPECT_EQ(nullptr, VMStructsTestAccessor::barrier());
}
