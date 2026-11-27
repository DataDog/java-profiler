/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <ucontext.h>
#include "dwarfStep.inline.h"

namespace {

const void* const PC = reinterpret_cast<const void*>(0x5a6000001000ULL);

// walkDwarf may unwind an atomic stub through frame.link() at any depth at which the
// frame's registers describe the walk cursor, which a signal-frame recovery re-establishes.
TEST(AtInterruptedContextTest, RequiresAnExactCursorAtTheFramesPc) {
    ucontext_t context{};
#ifdef __APPLE__
    _STRUCT_MCONTEXT64 machine_context{};
    context.uc_mcontext = &machine_context;
#endif
    StackFrame frame(&context);
    frame.pc() = reinterpret_cast<uintptr_t>(PC);
    WalkPc walk_pc;

    walk_pc.setExactAddress(PC);
    EXPECT_TRUE(atInterruptedContext(frame, walk_pc));

    walk_pc.setReturnAddress(PC);
    EXPECT_FALSE(atInterruptedContext(frame, walk_pc)) << "a return address is a caller, not this context";

    walk_pc.setExactAddress(static_cast<const char*>(PC) + 4);
    EXPECT_FALSE(atInterruptedContext(frame, walk_pc)) << "the frame describes another PC";
}

TEST(AtInterruptedContextTest, RejectsAFrameWithoutContext) {
    StackFrame frame(nullptr);
    WalkPc walk_pc;
    walk_pc.setExactAddress(PC);
    EXPECT_FALSE(atInterruptedContext(frame, walk_pc));
}

TEST(AtInterruptedContextTest, RestoredLinkIsExportedOnlyForSignalRestoredContexts) {
#ifndef __aarch64__
    GTEST_SKIP() << "x64 has no link register to export";
#else
    ucontext_t context{};
#ifdef __APPLE__
    _STRUCT_MCONTEXT64 machine_context{};
    context.uc_mcontext = &machine_context;
#endif
    StackFrame frame(&context);
    frame.pc() = reinterpret_cast<uintptr_t>(PC);
    frame.setLink(0x5a6000002000ULL);
    WalkPc walk_pc;
    walk_pc.setExactAddress(PC);
    EXPECT_EQ(0u, restoredLink(frame, walk_pc, 0)) << "the sampled context keeps its own LR";
    EXPECT_EQ(0x5a6000002000ULL, restoredLink(frame, walk_pc, 2));
    walk_pc.setReturnAddress(PC);
    EXPECT_EQ(0u, restoredLink(frame, walk_pc, 2));
#endif
}

// Malloc hooks snapshot a NULL ucontext; restoring it must not write the link register.
// A missing guard crashes this test binary rather than failing an assertion.
TEST(AtInterruptedContextTest, RegisterSnapshotOfNoContextRestoresNothing) {
    { StackFrame::RegisterSnapshot snapshot(nullptr); }
    EXPECT_EQ(0u, StackFrame::RegisterSnapshot(nullptr).pc());
}

TEST(AtInterruptedContextTest, RegisterSnapshotRestoresTheLinkRegister) {
    ucontext_t context{};
#ifdef __APPLE__
    _STRUCT_MCONTEXT64 machine_context{};
    context.uc_mcontext = &machine_context;
#endif
    StackFrame frame(&context);
    frame.setLink(0x5a6000002000ULL);
    {
        StackFrame::RegisterSnapshot snapshot(&context);
        frame.setLink(0x5a6000003000ULL);
    }
#ifdef __aarch64__
    EXPECT_EQ(0x5a6000002000ULL, frame.link());
#else
    EXPECT_EQ(0u, frame.link()) << "x64 has no link register";
#endif
}

} // namespace
