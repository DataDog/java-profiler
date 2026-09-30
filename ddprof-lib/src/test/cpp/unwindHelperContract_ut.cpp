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
// These tests drive the helpers directly: a fabricated frame, a few bytes of
// synthetic code, and -- for unwindPrologue/unwindEpilogue, which take a
// VMNMethod* -- a byte buffer standing in for an nmethod. No JVM is started.
// That is deliberate: reaching the same helpers through walkVM means faking a
// JavaThread and a CodeHeap too, and the further the fixture drifts from a
// real JVM layout the more likely it is to pass for the wrong reason.
//
// The nmethod fixture pins the pre-JDK-23 field shape, because entry()
// branches on `_nmethod_entry_offset != -1` and the older arm is a single
// indirection rather than a code_offset/verified_entry_offset pair. What is
// under test is the addressing convention, not the field layout, so either
// arm would do -- but read these tests as covering the helpers' contract,
// not as covering both nmethod layouts.

#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <ucontext.h>
#include "arch.h"
#include "hotspot/hotspotStackFrame.h"
#include "hotspot/vmStructs.h"
#include "stackFrame.h"

// Grants access to VMStructs' private field offsets (see the
// `friend class VMStructsTestAccessor;` declaration in vmStructs.h) so the
// nmethod fixture below can describe its own layout without a live JVM.
// Mirrors the same-named accessors in hotspotMethodId_ut.cpp and
// hotspot_crash_protection_ut.cpp -- each is a separate
// translation-unit-local definition naming only the fields that file needs;
// friendship is granted by name+scope, not by a single shared type. It has to
// sit outside the anonymous namespace, since that is the scope vmStructs.h
// befriends.
class VMStructsTestAccessor {
public:
    static offset getFrameSizeOffset() { return VMStructs::_frame_size_offset; }
    static void setFrameSizeOffset(offset value) { VMStructs::_frame_size_offset = value; }
    static offset getNMethodEntryOffset() { return VMStructs::_nmethod_entry_offset; }
    static void setNMethodEntryOffset(offset value) { VMStructs::_nmethod_entry_offset = value; }
    static offset getNMethodEntryAddress() { return VMStructs::_nmethod_entry_address; }
    static void setNMethodEntryAddress(offset value) { VMStructs::_nmethod_entry_address = value; }
};

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

// The register-less overload is what getJavaTraceAsync() calls: it rewrites
// the real ucontext and hands it straight to AsyncGetCallTrace, with no
// WalkPc to adjust afterwards. On x86_64 the ucontext must therefore carry
// the address inside the call instruction; aarch64 keeps the raw one.
TEST_F(UnwindHelperContractTest, AsgctOverloadLeavesUcontextReadyForAsyncGetCallTrace) {
    HotspotStackFrame frame(&_uc);

    uintptr_t* slot = stackSlot();
    *slot = kSenderRa;

    frame.pc() = (uintptr_t)code();
    frame.sp() = (uintptr_t)slot;
    frame.fp() = (uintptr_t)slot;

    ASSERT_TRUE(frame.unwindStub(code(), "someStub"));

#if defined(__x86_64__)
    EXPECT_EQ(kSenderRa - 1, frame.pc());
#else
    EXPECT_EQ(kLinkReg, frame.pc());
#endif
}

// ---------------------------------------------------------------------------
// unwindPrologue / unwindEpilogue
//
// Same contract, but these two take a VMNMethod*, so they need a stand-in.
// Only two fields are ever read on the branches under test: entry(), to
// locate the start of the method's code, and frameSize(). The fixture is a
// byte buffer laid out to satisfy exactly those, with the offsets pointed at
// it for the duration of the test and restored afterwards -- the offsets are
// process-global, and a real JVM run would have populated them from
// vmStructs.
// ---------------------------------------------------------------------------

// Byte offsets within _nmethod. Arbitrary, beyond needing natural alignment
// for the types stored there and staying inside the buffer.
const int kEntryAddressOffset = 8;   // holds a void* to the method's code
const int kFrameSizeOffset    = 16;  // holds an int, in words

const uintptr_t kOtherSlot = 0x5a5a00003000ULL;  // a slot that must NOT be read

class UnwindNMethodHelperContractTest : public UnwindHelperContractTest {
  protected:
    void SetUp() override {
        UnwindHelperContractTest::SetUp();

        _saved_frame_size_offset = VMStructsTestAccessor::getFrameSizeOffset();
        _saved_entry_offset = VMStructsTestAccessor::getNMethodEntryOffset();
        _saved_entry_address = VMStructsTestAccessor::getNMethodEntryAddress();

        memset(_nmethod, 0, sizeof(_nmethod));
        *(const void**)(bytes() + kEntryAddressOffset) = code();
        *(int*)(bytes() + kFrameSizeOffset) = 4;

        VMStructsTestAccessor::setFrameSizeOffset(kFrameSizeOffset);
        // -1 selects entry()'s pre-JDK-23 arm: a single load of the stored
        // pointer, rather than code_offset + verified_entry_offset.
        VMStructsTestAccessor::setNMethodEntryOffset(-1);
        VMStructsTestAccessor::setNMethodEntryAddress(kEntryAddressOffset);
    }

    void TearDown() override {
        VMStructsTestAccessor::setFrameSizeOffset(_saved_frame_size_offset);
        VMStructsTestAccessor::setNMethodEntryOffset(_saved_entry_offset);
        VMStructsTestAccessor::setNMethodEntryAddress(_saved_entry_address);
    }

    VMNMethod* nmethod() {
        // cast_raw, not cast: the latter asserts the buffer is as large as the
        // JVM-reported type size, which is zero here because no JVM populated
        // it.
        return VMNMethod::cast_raw(_nmethod);
    }

    // uintptr_t rather than char, so the buffer is aligned for the void* and
    // int the layout above stores in it.
    char* bytes() { return (char*)_nmethod; }

    static uintptr_t _nmethod[4];

  private:
    offset _saved_frame_size_offset;
    offset _saved_entry_offset;
    offset _saved_entry_address;
};

uintptr_t UnwindNMethodHelperContractTest::_nmethod[4];

// pc sitting on the method's first instruction: nothing of the frame has been
// built yet, so the sender pc is still wherever the call left it.
TEST_F(UnwindNMethodHelperContractTest, UnwindPrologueAtEntryRecoversTheRawSenderPc) {
    HotspotStackFrame frame(&_uc);

    uintptr_t* slot = stackSlot();
    slot[0] = kSenderRa;

    uintptr_t pc = (uintptr_t)code();  // == nm->entry()
    uintptr_t sp = (uintptr_t)slot;
    uintptr_t fp = (uintptr_t)slot;

    ASSERT_TRUE(frame.unwindPrologue(nmethod(), pc, sp, fp));

#if defined(__x86_64__)
    EXPECT_EQ(kSenderRa, pc)
        << "the pushed return address comes back exactly as it sat in the slot";
    EXPECT_EQ((uintptr_t)slot + sizeof(void*), sp);
#elif defined(__aarch64__)
    EXPECT_EQ(kLinkReg, pc) << "the link register comes back verbatim";
    EXPECT_EQ((uintptr_t)slot, sp);
#endif
}

// One instruction further in, past the push/stp that saved the caller's fp:
// both architectures now source the sender pc from the *second* stack slot and
// pop two. This is the branch where x86_64's folded adjustment used to sit at a
// different slot than its sibling's, so it is worth pinning separately.
TEST_F(UnwindNMethodHelperContractTest, UnwindPrologueAfterFrameSetupRecoversTheRawSenderPc) {
    HotspotStackFrame frame(&_uc);

    uintptr_t* slot = stackSlot();
    slot[0] = kOtherSlot;  // the saved fp, not a return address
    slot[1] = kSenderRa;

#if defined(__x86_64__)
    code()[0] = 0x55;  // push %rbp
#elif defined(__aarch64__)
    code()[0] = 0xa9bf7bfd;  // stp  x29, x30, [sp, #-16]!
    code()[1] = 0x910003fd;  // mov  x29, sp
#endif

    uintptr_t pc = (uintptr_t)&code()[1];
    uintptr_t sp = (uintptr_t)slot;
    uintptr_t fp = (uintptr_t)slot;

    ASSERT_TRUE(frame.unwindPrologue(nmethod(), pc, sp, fp));

    EXPECT_EQ(kSenderRa, pc)
        << "expected the raw return address from the second slot; got 0x"
        << std::hex << pc << " (adjacent slot holds 0x" << kOtherSlot << ")";
    EXPECT_EQ((uintptr_t)slot + 2 * sizeof(void*), sp)
        << "and both slots are popped";
}

// pc on the `ret` itself: the frame is already torn down, so the sender pc is
// back where the prologue found it.
TEST_F(UnwindNMethodHelperContractTest, UnwindEpilogueAtReturnRecoversTheRawSenderPc) {
    HotspotStackFrame frame(&_uc);

    uintptr_t* slot = stackSlot();
    slot[0] = kSenderRa;

    // Placed a couple of instructions in so the ip[-1] reads on the branches
    // this does not take stay inside the buffer.
    const size_t ret_index = 2;
#if defined(__x86_64__)
    code()[ret_index] = 0xc3;  // ret
#elif defined(__aarch64__)
    code()[ret_index] = 0xd65f03c0;  // ret
#endif

    uintptr_t pc = (uintptr_t)&code()[ret_index];
    uintptr_t sp = (uintptr_t)slot;
    uintptr_t fp = (uintptr_t)slot;

    ASSERT_TRUE(frame.unwindEpilogue(nmethod(), pc, sp, fp));

#if defined(__x86_64__)
    EXPECT_EQ(kSenderRa, pc)
        << "the return address about to be consumed by `ret` is handed back "
        << "unmodified";
    EXPECT_EQ((uintptr_t)slot + sizeof(void*), sp);
#elif defined(__aarch64__)
    EXPECT_EQ(kLinkReg, pc) << "the link register comes back verbatim";
    EXPECT_EQ((uintptr_t)slot, sp);
#endif
}

}  // namespace
