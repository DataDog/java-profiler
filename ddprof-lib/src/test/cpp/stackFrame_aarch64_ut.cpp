/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "stackFrame.h"

#ifdef __aarch64__

// Assembler-verified AArch64 sequences from C1's subtype-check callers and
// MacroAssembler::call_VM_leaf_base. The pending pop belongs to the caller's
// temporary arguments, outside the nmethod's fixed frame size.
TEST(StackFrameArgumentsTest, C1SubtypeCheckDiscardsCallerArguments) {
    instruction_t code[] = {0xa9bf07e0, 0x94000000, 0xf84107e0};
    StackFrame frame(nullptr);
    uintptr_t sp = 0x1000;
    frame.adjustSP(code, code + 2, sp);
    EXPECT_EQ(0x1010u, sp);
}

TEST(StackFrameArgumentsTest, C1PairResultDiscardsCallerArguments) {
    instruction_t code[] = {0xa9bf07e0, 0x94000000, 0xa8c103e1};
    StackFrame frame(nullptr);
    uintptr_t sp = 0x1000;
    frame.adjustSP(code, code + 2, sp);
    EXPECT_EQ(0x1010u, sp);
}

TEST(StackFrameArgumentsTest, C1FarCallDiscardsCallerArguments) {
    instruction_t code[] = {0xa9bf07e0, 0x90000008, 0x91000108, 0xd63f0100, 0xf84107e0};
    StackFrame frame(nullptr);
    uintptr_t sp = 0x1000;
    frame.adjustSP(code, code + 4, sp);
    EXPECT_EQ(0x1010u, sp);
}

TEST(StackFrameArgumentsTest, VmLeafCallDiscardsTemporaryRegisters) {
    instruction_t code[] = {0xa9bf33e8, 0xd2824688, 0xf2aacf08, 0xf2c24688, 0xd63f0100, 0xa8c133e8};
    StackFrame frame(nullptr);
    uintptr_t sp = 0x1000;
    frame.adjustSP(code, code + 5, sp);
    EXPECT_EQ(0x1010u, sp);
}

TEST(StackFrameArgumentsTest, DoesNotAdjustAfterThePop) {
    instruction_t code[] = {0xa9bf07e0, 0x94000000, 0xf84107e0, 0xd503201f};
    StackFrame frame(nullptr);
    uintptr_t sp = 0x1000;
    frame.adjustSP(code, code + 3, sp);
    EXPECT_EQ(0x1000u, sp);
}

TEST(StackFrameArgumentsTest, DoesNotTreatTheFixedFrameAsArguments) {
    instruction_t code[] = {0xa9bf7bfd, 0x94000000, 0xa8c17bfd};
    StackFrame frame(nullptr);
    uintptr_t sp = 0x1000;
    frame.adjustSP(code, code + 2, sp);
    EXPECT_EQ(0x1000u, sp);
}

TEST(StackFrameArgumentsTest, RequiresAMatchingArgumentPush) {
    instruction_t code[] = {0xd503201f, 0x94000000, 0xf84107e0};
    StackFrame frame(nullptr);
    uintptr_t sp = 0x1000;
    frame.adjustSP(code, code + 2, sp);
    EXPECT_EQ(0x1000u, sp);
}

TEST(StackFrameArgumentsTest, DoesNotSearchBeforeTheMethodEntry) {
    instruction_t code[] = {0xa9bf07e0, 0x94000000, 0xf84107e0};
    StackFrame frame(nullptr);
    uintptr_t sp = 0x1000;
    frame.adjustSP(code + 1, code + 2, sp);
    EXPECT_EQ(0x1000u, sp);
}

TEST(StackFrameArgumentsTest, RejectsUnrelatedAddressSetup) {
    instruction_t code[] = {0xa9bf07e0, 0xd503201f, 0xd63f0100, 0xf84107e0};
    StackFrame frame(nullptr);
    uintptr_t sp = 0x1000;
    frame.adjustSP(code, code + 3, sp);
    EXPECT_EQ(0x1000u, sp);
}

TEST(StackFrameArgumentsTest, RejectsSetupForADifferentCallRegister) {
    instruction_t code[] = {0xa9bf07e0, 0x90000009, 0xd63f0100, 0xf84107e0};
    StackFrame frame(nullptr);
    uintptr_t sp = 0x1000;
    frame.adjustSP(code, code + 3, sp);
    EXPECT_EQ(0x1000u, sp);
}

TEST(StackFrameArgumentsTest, RejectsADifferentPushSize) {
    instruction_t code[] = {0xa9be07e0, 0x94000000, 0xf84107e0};
    StackFrame frame(nullptr);
    uintptr_t sp = 0x1000;
    frame.adjustSP(code, code + 2, sp);
    EXPECT_EQ(0x1000u, sp);
}

TEST(StackFrameArgumentsTest, PreservesC2NativeLeafAdjustment) {
    instruction_t code[] = {0xa9bf27ff, 0xd63f0100, 0x910043ff};
    StackFrame frame(nullptr);
    uintptr_t sp = 0x1000;
    frame.adjustSP(code, code + 2, sp);
    EXPECT_EQ(0x1010u, sp);
}

#endif // __aarch64__
