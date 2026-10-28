/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "codeCache.h"
#include "dwarfStep.inline.h"
#include "libraries.h"
#include <array>
#include <new>
#include <signal.h>

#if defined(__linux__) && defined(__aarch64__)
namespace {
alignas(16) uint32_t trampoline_code[] = {0xd503201f, 0xd2801168, 0xd4000001, 0xd503201f};
alignas(16) uint32_t ordinary_code[] = {0xd503201f, 0xd2801168, 0xd4000001, 0xd503201f};
alignas(16) uint32_t leaf_code[] = {0xd503201f, 0xd65f03c0};
const void* const caller_pc = (const void*)0x5a5f00000108ULL;

void registerLibraries() {
    static const bool registered = [] {
        static CodeCache vdso("[vdso]", -1, (const char*)trampoline_code,
                              (const char*)(trampoline_code + 4));
        static CodeCache ordinary("ordinary-syscall", -1, (const char*)ordinary_code,
                                  (const char*)(ordinary_code + 4));
        static CodeCache leaf("native-clock-leaf", -1, (const char*)leaf_code,
                              (const char*)(leaf_code + 2));
        static const FrameDesc leaf_row{0, DW_REG_SP, DW_SAME_FP, DW_LINK_REGISTER};
        leaf.setDwarfTable(nullptr, 0, leaf_row);
        bool ok = Libraries::instance()->addLibraryForTest(&vdso);
        ok = Libraries::instance()->addLibraryForTest(&ordinary) && ok;
        return Libraries::instance()->addLibraryForTest(&leaf) && ok;
    }();
    ASSERT_TRUE(registered);
}

class SignalFrameTest : public ::testing::Test {
protected:
    static constexpr size_t context_size = sizeof(siginfo_t) + sizeof(ucontext_t);
    using SignalStack = std::array<unsigned char, context_size + 256>;

    void SetUp() override { registerLibraries(); }

    // A kernel rt_sigframe precedes the interrupted stack on Linux arm64.
    static ucontext_t* savedContext(SignalStack& stack) {
        auto* context = new (stack.data() + sizeof(siginfo_t)) ucontext_t{};
        context->uc_mcontext.pc = (uintptr_t)leaf_code;
        context->uc_mcontext.sp = (uintptr_t)(stack.data() + context_size);
        context->uc_mcontext.regs[29] = 1; // compiled Java can use FP as a general register
        context->uc_mcontext.regs[30] = (uintptr_t)caller_pc;
        return context;
    }

    static bool step(WalkPc& pc, uintptr_t& sp, uintptr_t& fp, uintptr_t bottom,
                     int depth, StackFrame& frame) {
        return advanceDwarfFrame(pc, sp, fp, bottom, depth, frame, Profiler::instance());
    }
};

TEST_F(SignalFrameTest, RestoresExactPcAndRegistersThenUsesInterruptedLr) {
    for (int instruction : {1, 2}) {
        alignas(16) SignalStack stack{};
        auto* saved = savedContext(stack);
        ucontext_t sampled{};
        sampled.uc_mcontext.pc = (uintptr_t)(trampoline_code + instruction);
        sampled.uc_mcontext.regs[30] = 0x5a5f00000908ULL; // handler LR must not escape
        StackFrame frame(&sampled);
        WalkPc pc;
        pc.setReturnAddress(trampoline_code + instruction);
        uintptr_t sp = (uintptr_t)stack.data(), fp = 0;
        uintptr_t bottom = (uintptr_t)(stack.data() + stack.size());
        ASSERT_TRUE(step(pc, sp, fp, bottom, 2, frame));
        EXPECT_EQ((const void*)leaf_code, pc.raw());
        EXPECT_FALSE(pc.isReturnAddress());
        EXPECT_EQ(saved->uc_mcontext.sp, sp);
        EXPECT_EQ(1u, fp);
        EXPECT_EQ((uintptr_t)caller_pc, frame.link());
        ASSERT_TRUE(step(pc, sp, fp, bottom, 3, frame));
        EXPECT_EQ(caller_pc, pc.raw());
        EXPECT_TRUE(pc.isReturnAddress());
        EXPECT_EQ((uintptr_t)(trampoline_code + instruction), sampled.uc_mcontext.pc);
        EXPECT_EQ(0x5a5f00000908ULL, sampled.uc_mcontext.regs[30]);
    }
}

TEST_F(SignalFrameTest, RejectsIncompleteOrMisalignedSignalFrame) {
    alignas(16) SignalStack stack{};
    savedContext(stack);
    for (int invalid : {0, 1}) {
        ucontext_t sampled{};
        StackFrame frame(&sampled);
        WalkPc pc;
        pc.setReturnAddress(trampoline_code + 1);
        uintptr_t sp = (uintptr_t)stack.data() + invalid, fp = 0;
        uintptr_t bottom = invalid == 0 ? sp + sizeof(siginfo_t) : (uintptr_t)(stack.data() + stack.size());
        EXPECT_FALSE(step(pc, sp, fp, bottom, 2, frame));
        EXPECT_EQ((const void*)(trampoline_code + 1), pc.raw());
    }
}

TEST_F(SignalFrameTest, RejectsBackwardMisalignedOrOutOfRangeInterruptedSp) {
    alignas(16) SignalStack stack{};
    auto* saved = savedContext(stack);
    uintptr_t base = (uintptr_t)stack.data(), bottom = base + stack.size();
    for (uintptr_t interrupted_sp : {base, base - 16, bottom, base + context_size + 1}) {
        saved->uc_mcontext.sp = interrupted_sp;
        ucontext_t sampled{};
        StackFrame frame(&sampled);
        WalkPc pc;
        pc.setReturnAddress(trampoline_code + 1);
        uintptr_t sp = base, fp = 0;
        EXPECT_FALSE(step(pc, sp, fp, bottom, 2, frame));
        EXPECT_EQ(base, sp);
    }
}

TEST_F(SignalFrameTest, RejectsMissingOrMisalignedInterruptedPc) {
    alignas(16) SignalStack stack{};
    auto* saved = savedContext(stack);
    for (uintptr_t interrupted_pc : {uintptr_t(0), (uintptr_t)leaf_code + 1}) {
        saved->uc_mcontext.pc = interrupted_pc;
        ucontext_t sampled{};
        StackFrame frame(&sampled);
        WalkPc pc;
        pc.setReturnAddress(trampoline_code + 1);
        uintptr_t sp = (uintptr_t)stack.data(), fp = 0;
        EXPECT_FALSE(step(pc, sp, fp, (uintptr_t)(stack.data() + stack.size()), 2, frame));
    }
}

TEST_F(SignalFrameTest, DoesNotRestoreAtUnrecognizedVdsoInstruction) {
    alignas(16) SignalStack stack{};
    savedContext(stack);
    ucontext_t sampled{};
    sampled.uc_mcontext.pc = (uintptr_t)(trampoline_code + 3);
    StackFrame frame(&sampled);
    WalkPc pc;
    pc.setReturnAddress(trampoline_code + 3);
    uintptr_t sp = (uintptr_t)stack.data(), fp = 0;
    EXPECT_FALSE(step(pc, sp, fp, (uintptr_t)(stack.data() + stack.size()), 2, frame));
    EXPECT_TRUE(frame.isInterruptedPC(trampoline_code + 3));
}

TEST_F(SignalFrameTest, DoesNotTreatOrdinarySyscallCodeAsSignalTrampoline) {
    alignas(16) SignalStack stack{};
    savedContext(stack);
    ucontext_t sampled{};
    sampled.uc_mcontext.pc = (uintptr_t)(ordinary_code + 1);
    StackFrame frame(&sampled);
    WalkPc pc;
    pc.setReturnAddress(ordinary_code + 1);
    uintptr_t sp = (uintptr_t)stack.data(), fp = 0;
    EXPECT_FALSE(step(pc, sp, fp, (uintptr_t)(stack.data() + stack.size()), 2, frame));
    EXPECT_TRUE(frame.isInterruptedPC(ordinary_code + 1));
}
} // namespace
#else
TEST(SignalFrameTest, RequiresLinuxAarch64SignalAbi) {
    GTEST_SKIP() << "Linux arm64 signal trampoline ABI";
}
#endif
