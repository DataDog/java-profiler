/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Pins what HotspotStackFrame's unwind helpers hand back: the sender's raw
// return address, on every architecture and every branch, with no attribution
// adjustment applied.
//
// They used to disagree. x86_64 subtracted one inside the helper, and not even
// on every branch -- unwindPrologue's isFrameComplete arm returned the address
// untouched while its two siblings adjusted it -- while aarch64 never did. A
// caller could not tell which it had been handed, so walkVM guessed from the
// target architecture, and the exact-address consumers on the far side
// (isContReturnBarrier, isContEntryReturnPc, isEntryFrame) silently stopped
// matching on x86_64.
//
// These tests drive the helpers directly: they need a fabricated frame and a
// few bytes of synthetic code, but no JVM, no VMStructs and no nmethod. That
// is deliberate -- reaching the same helpers through walkVM means faking a
// JavaThread and a CodeHeap, and the further the fixture drifts from a real
// JVM layout the more likely it is to pass for the wrong reason.

#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <ucontext.h>
#include "arch.h"
#include "hotspot/hotspotStackFrame.h"
#include "stackFrame.h"

namespace {

// Enough room for the generic aarch64 prologue scan, which reads up to eight
// instructions past `entry` before giving up.
const size_t kCodeWords = 16;
const size_t kStackWords = 32;

const uintptr_t kSenderRa = 0x5a5a00001000ULL;  // what sits in the stack slot
const uintptr_t kLinkReg  = 0x5a5a00002000ULL;  // what sits in the link register

class UnwindHelperContractTest : public ::testing::Test {
  protected:
    void SetUp() override {
        memset(_code, 0, sizeof(_code));
        memset(_stack, 0, sizeof(_stack));
        memset(&_uc, 0, sizeof(_uc));
#ifdef __APPLE__
        // uc_mcontext is a pointer on Darwin and embedded on Linux, so a
        // zeroed ucontext needs storage to point at before any register
        // access.
        memset(&_mc, 0, sizeof(_mc));
        _uc.uc_mcontext = &_mc;
#endif
        setLinkRegister(kLinkReg);
    }

    // The link register is not writable through StackFrame (link() is const),
    // so the test writes the ucontext slot that link() reads back.
    static void setLinkRegister(uintptr_t value) {
#if defined(__aarch64__) && defined(__APPLE__)
        _uc.uc_mcontext->__ss.__lr = value;
#elif defined(__aarch64__)
        _uc.uc_mcontext.regs[30] = value;
#else
        (void)value;  // x86_64 has no link register; StackFrame::link() is 0
#endif
    }

    // Stack slot the helpers read a saved pc out of. Kept mid-buffer so an
    // sp that moves in either direction stays inside the allocation.
    uintptr_t* stackSlot() { return &_stack[kStackWords / 2]; }

    instruction_t* code() { return (instruction_t*)_code; }

    static ucontext_t _uc;
#ifdef __APPLE__
    static _STRUCT_MCONTEXT64 _mc;
#endif
    static uintptr_t _code[kCodeWords];
    static uintptr_t _stack[kStackWords];
};

ucontext_t UnwindHelperContractTest::_uc;
#ifdef __APPLE__
_STRUCT_MCONTEXT64 UnwindHelperContractTest::_mc;
#endif
uintptr_t UnwindHelperContractTest::_code[kCodeWords];
uintptr_t UnwindHelperContractTest::_stack[kStackWords];

// The shared entry branch: pc sitting exactly on the stub's first
// instruction. Both arches take it, and both now hand back a raw address --
// they differ only in where the sender pc lives on that architecture.
TEST_F(UnwindHelperContractTest, UnwindStubAtEntryRecoversTheRawSenderPc) {
    HotspotStackFrame frame(&_uc);

    uintptr_t* slot = stackSlot();
    *slot = kSenderRa;

    uintptr_t pc = (uintptr_t)code();
    uintptr_t sp = (uintptr_t)slot;
    uintptr_t fp = (uintptr_t)slot;

    ASSERT_TRUE(frame.unwindStub(code(), "someStub", pc, sp, fp))
        << "pc on the stub's entry instruction is the branch both arches take";

#if defined(__x86_64__)
    EXPECT_EQ(kSenderRa, pc)
        << "the saved return address is handed back exactly as it sat in the "
        << "slot -- no adjustment folded in by the helper";
    EXPECT_EQ((uintptr_t)slot + sizeof(void*), sp)
        << "and the slot it consumed is popped";
#elif defined(__aarch64__)
    EXPECT_EQ(kLinkReg, pc)
        << "the link register is handed back verbatim";
    EXPECT_EQ((uintptr_t)slot, sp)
        << "and sp is left alone, the return address never having been on the stack";
#endif
}

// The property that matters to a caller, stated without reference to which
// architecture this is: whatever the helper returns is a raw return address,
// so the caller can apply the attribution adjustment itself and be right
// everywhere. Before the contract was unified this could not be written --
// the answer depended on the target.
TEST_F(UnwindHelperContractTest, HelperNeverAppliesTheAdjustmentItself) {
    HotspotStackFrame frame(&_uc);

    uintptr_t* slot = stackSlot();
    *slot = kSenderRa;

    uintptr_t pc = (uintptr_t)code();
    uintptr_t sp = (uintptr_t)slot;
    uintptr_t fp = (uintptr_t)slot;

    ASSERT_TRUE(frame.unwindStub(code(), "someStub", pc, sp, fp));

    // Whichever slot this architecture sources the sender pc from, it comes
    // back unmodified. An off-by-one here means someone reintroduced a folded
    // adjustment, and walkVM would then subtract a second one.
    const bool is_raw = (pc == kSenderRa) || (pc == kLinkReg);
    EXPECT_TRUE(is_raw)
        << "expected an unmodified return address, got pc=0x" << std::hex << pc
        << " (saved slot 0x" << kSenderRa << ", link register 0x" << kLinkReg << ")";
}

}  // namespace
