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

} // namespace
