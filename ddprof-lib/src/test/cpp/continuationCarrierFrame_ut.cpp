/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <climits>
#include "hotspot/vmStructs.inline.h"

class VMStructsTestAccessor {
    int _frame_size = VMStructs::_frame_size_offset;
    int _stack_args = VMStructs::_constmethod_stack_arg_slots_offset;
    const void* _return_pc = VMStructs::_cont_entry_return_pc;
    address _return_pc_addr = VMStructs::_cont_entry_return_pc_addr;

public:
    VMStructsTestAccessor() {
        VMStructs::_frame_size_offset = 0;
        VMStructs::_constmethod_stack_arg_slots_offset = 0;
        VMStructs::_cont_entry_return_pc = nullptr;
        VMStructs::_cont_entry_return_pc_addr = nullptr;
    }

    ~VMStructsTestAccessor() {
        VMStructs::_frame_size_offset = _frame_size;
        VMStructs::_constmethod_stack_arg_slots_offset = _stack_args;
        VMStructs::_cont_entry_return_pc = _return_pc;
        VMStructs::_cont_entry_return_pc_addr = _return_pc_addr;
    }

    static void setReturnPcAddress(const void** value) { VMStructs::_cont_entry_return_pc_addr = value; }
    static void clearStackArgOffset() { VMStructs::_constmethod_stack_arg_slots_offset = -1; }
};

class ContinuationCarrierFrameTest : public ::testing::Test {
protected:
    VMStructsTestAccessor _layout;
    int _frame_size = 10;
    alignas(16) uintptr_t _stack[64] = {};

    VMNMethod* entryMethod() { return VMNMethod::cast_raw(&_frame_size); }
};

TEST_F(ContinuationCarrierFrameTest, RecoversSavedCarrierSlotsWithoutAFramePointerChain) {
    _stack[8] = (uintptr_t)&_stack[32];
    _stack[9] = (uintptr_t)&_stack[40];
    // The thawed frame's saved FP need not point to the entry frame.
    _stack[0] = 0;
    uintptr_t entry_fp = entryMethod()->continuationEntryFP((uintptr_t)_stack, 0);
    ASSERT_EQ((uintptr_t)&_stack[8], entry_fp);
    EXPECT_EQ((uintptr_t)&_stack[32], *(uintptr_t*)entry_fp);
    EXPECT_EQ((uintptr_t)&_stack[40], ((uintptr_t*)entry_fp)[1]);
}

TEST_F(ContinuationCarrierFrameTest, AccountsForStackArgumentsAndAlignment) {
    _stack[12] = (uintptr_t)&_stack[32];
    _stack[13] = (uintptr_t)&_stack[40];
    // Three argument words require four words below the aligned entry SP.
    uintptr_t entry_fp = entryMethod()->continuationEntryFP((uintptr_t)_stack, 3);
    ASSERT_EQ((uintptr_t)&_stack[12], entry_fp);
    EXPECT_EQ((uintptr_t)&_stack[32], *(uintptr_t*)entry_fp);
    EXPECT_EQ((uintptr_t)&_stack[40], ((uintptr_t*)entry_fp)[1]);
}

TEST_F(ContinuationCarrierFrameTest, ConvertsExportedArgumentSlotsToWords) {
    for (unsigned short slots : {0, 1, 2, 3, 17}) {
        VMConstMethod* method = VMConstMethod::cast_raw(&slots);
        EXPECT_EQ((slots + 1) / 2, method->stackArgWords());
    }
    VMStructsTestAccessor::clearStackArgOffset();
    EXPECT_EQ(-1, VMConstMethod::cast_raw(_stack)->stackArgWords());
}

TEST_F(ContinuationCarrierFrameTest, RejectsUnknownOrInvalidArgumentCounts) {
    for (int args : {-1, 129, INT_MAX}) {
        EXPECT_EQ(0u, entryMethod()->continuationEntryFP((uintptr_t)_stack, args));
    }
}

TEST_F(ContinuationCarrierFrameTest, RejectsInvalidEntryFrameSizes) {
    for (int size : {-1, 0, 1, 2, 3, 11, 257, INT_MAX}) {
        _frame_size = size;
        EXPECT_EQ(0u, entryMethod()->continuationEntryFP((uintptr_t)_stack, 0));
    }
}

TEST_F(ContinuationCarrierFrameTest, RejectsMisalignmentAndAddressOverflow) {
    EXPECT_EQ(0u, entryMethod()->continuationEntryFP((uintptr_t)_stack + sizeof(uintptr_t), 0));
    EXPECT_EQ(0u, entryMethod()->continuationEntryFP(UINTPTR_MAX & ~(uintptr_t)15, 0));
}

TEST_F(ContinuationCarrierFrameTest, ObservesEntryWrapperGeneratedAfterInitialization) {
    const void* return_pc = nullptr;
    const void* expected_pc = &_stack[9];
    VMStructsTestAccessor::setReturnPcAddress(&return_pc);
    EXPECT_FALSE(VMStructs::isContEntryReturnPc(expected_pc));
    return_pc = expected_pc;
    EXPECT_TRUE(VMStructs::isContEntryReturnPc(expected_pc));
    EXPECT_FALSE(VMStructs::isContEntryReturnPc(&_stack[10]));
}
