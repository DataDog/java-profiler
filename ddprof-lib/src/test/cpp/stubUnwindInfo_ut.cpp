/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "hotspot/stubUnwindInfo.h"

// Unit tests for the AArch64 runtime-stub unwind classifier. All instruction
// encodings below were verified with the system assembler; the builders
// reproduce them bit-exactly so the tests exercise real machine encodings.
//
// This file must always contain at least one registered test on every host:
// with a fully empty TU nothing pulls members from -lgtest before -lgtest_main
// introduces undefined testing:: symbols, and the static-archive left-to-right
// link fails on Linux. The placeholder keeps the archive ordering valid.
TEST(StubUnwindInfo, ClassifierIsAarch64Only) {}

#ifdef __aarch64__

#include <string.h>
#include <vector>

namespace {

const uint32_t NOP = 0xd503201f;
const uint32_t RET = 0xd65f03c0;

inline uint32_t stpPre64(int rt, int rt2, int imm) {
    // stp Xt, Xt2, [sp, #-imm]!
    return 0xa98003e0 | (uint32_t)((imm / 8) & 0x7f) << 15 | (uint32_t)rt2 << 10 | (uint32_t)rt;
}
inline uint32_t stpPreD(int rt, int rt2, int imm) {
    // stp Dt, Dt2, [sp, #-imm]!  (64-bit SIMD)
    return 0x6d8003e0 | (uint32_t)((imm / 8) & 0x7f) << 15 | (uint32_t)rt2 << 10 | (uint32_t)rt;
}
inline uint32_t stpPreQ(int rt, int rt2, int imm) {
    // stp Qt, Qt2, [sp, #-imm]!  (128-bit SIMD)
    return 0xad8003e0 | (uint32_t)((imm / 16) & 0x7f) << 15 | (uint32_t)rt2 << 10 | (uint32_t)rt;
}
inline uint32_t stpPost64(int rt, int rt2, int imm) {
    // stp Xt, Xt2, [sp], #imm
    return 0xa80003e0 | (uint32_t)((imm / 8) & 0x7f) << 15 | (uint32_t)rt2 << 10 | (uint32_t)rt;
}
inline uint32_t ldpPost64(int rt, int rt2, int imm) {
    // ldp Xt, Xt2, [sp], #imm
    return 0xa8c003e0 | (uint32_t)((imm / 8) & 0x7f) << 15 | (uint32_t)rt2 << 10 | (uint32_t)rt;
}
inline uint32_t ldpOff64(int rt, int rt2, int imm) {
    // ldp Xt, Xt2, [sp, #imm]
    return 0xa94003e0 | (uint32_t)((imm / 8) & 0x7f) << 15 | (uint32_t)rt2 << 10 | (uint32_t)rt;
}
inline uint32_t subSp(int imm) { return 0xd10003ff | (uint32_t)imm << 10; }
inline uint32_t addSp(int imm) { return 0x910003ff | (uint32_t)imm << 10; }
// add Xd, sp, #imm (covers "mov x29, sp" with an offset)
inline uint32_t addRdSpImm(int rd, int imm) { return 0x91000000 | 0x3e0 | (uint32_t)rd | (uint32_t)imm << 10; }
// add sp, Xn, #imm (covers "mov sp, xN")
inline uint32_t addSpRnImm(int rn, int imm) { return 0x91000000 | 0x1f | (uint32_t)rn << 5 | (uint32_t)imm << 10; }
inline uint32_t stpOff64(int rt, int rt2, int imm) {
    // stp Xt, Xt2, [sp, #imm]
    return 0xa90003e0 | (uint32_t)((imm / 8) & 0x7f) << 15 | (uint32_t)rt2 << 10 | (uint32_t)rt;
}
inline uint32_t movReg(int rd, int rm) { return 0xaa0003e0 | (uint32_t)rm << 16 | (uint32_t)rd; }
inline uint32_t strPreSp(int rt, int imm9) { return 0xf8000fe0 | (uint32_t)(imm9 & 0x1ff) << 12 | (uint32_t)rt; }
// ldr Xt, [sp, #imm] -- Rn=sp must be encoded (31 << 5 = 0x3e0)
inline uint32_t ldrOffSp(int rt, int imm) { return 0xf94003e0 | (uint32_t)(imm / 8) << 10 | (uint32_t)rt; }
inline uint32_t strPostSp(int rt, int imm9) { return 0xf80007e0 | (uint32_t)(imm9 & 0x1ff) << 12 | (uint32_t)rt; }
inline uint32_t ldrPostSp(int rt, int imm9) { return 0xf84007e0 | (uint32_t)(imm9 & 0x1ff) << 12 | (uint32_t)rt; }
// ldtr Xt, [sp, #imm9] (unprivileged, bits 11:10 = 10)
inline uint32_t ldtrSp(int rt, int imm9) { return 0xf8400be0 | (uint32_t)(imm9 & 0x1ff) << 12 | (uint32_t)rt; }
// add sp, Xn, #imm, lsl #12 (sh bit set)
inline uint32_t addSpRnImmLsl12(int rn, int imm) { return 0x91400000 | (uint32_t)rn << 5 | 0x1f | (uint32_t)imm << 10; }// movk Xd, #imm, lsl #shift (hw = shift/16); 64-bit (sf=1) and 32-bit (sf=0)
inline uint32_t movk(int rd, int imm, int shift, bool sixty_four = true) {
    return (sixty_four ? 0xf2800000 : 0x72800000) | (uint32_t)(shift / 16) << 21
         | (uint32_t)(imm & 0xffff) << 5 | (uint32_t)rd;
}
inline uint32_t ldpX29BasePost(int rt, int rt2, int imm) {
    // ldp Xt, Xt2, [x29], #imm  (anchor: ldp x29,x30,[x29],#16 = 0xa8c17bfd)
    return 0xa8c00000 | 29 << 5 | (uint32_t)((imm / 8) & 0x7f) << 15 | (uint32_t)rt2 << 10 | (uint32_t)rt;
}
inline uint32_t branch(int offInsns) { return 0x14000000 | (uint32_t)(offInsns & 0x03ffffff); }
inline uint32_t branchCond(int offInsns) { return 0x54000000 | (uint32_t)((offInsns & 0x7ffff) << 5); }
inline uint32_t cbz(int rt, int offInsns) { return 0xb4000000 | (uint32_t)((offInsns & 0x7ffff) << 5) | (uint32_t)rt; }
inline uint32_t call(int offInsns) { return 0x94000000 | (uint32_t)(offInsns & 0x03ffffff); }
inline uint32_t callReg(int rn) { return 0xd63f0000 | (uint32_t)rn << 5; }
inline uint32_t jumpReg(int rn) { return 0xd61f0000 | (uint32_t)rn << 5; }

class StubUnwindTest : public ::testing::Test {
protected:
    // Classifies an instruction sequence; frees the info on scope exit.
    StubUnwindInfo* analyze(const std::vector<uint32_t>& code, bool model_epilogue = false) {
        StubUnwindInfo* info =
            analyzeStubUnwind(code.data(), (int)code.size() * 4, model_epilogue);
        _owned.push_back(info);
        return info;
    }
    ~StubUnwindTest() override {
        for (auto* p : _owned) free(p);
    }
    static void expectPhase(const StubUnwindInfo* info, int insn_index, int kind, int arg,
                            int arg2 = 0) {
        const StubUnwindPhase* p = info->findPhase(insn_index);
        EXPECT_EQ(p->kind, kind) << "at insn " << insn_index;
        EXPECT_EQ(p->arg, arg) << "at insn " << insn_index;
        EXPECT_EQ(p->arg2, arg2) << "at insn " << insn_index;
    }
    std::vector<StubUnwindInfo*> _owned;
};

TEST_F(StubUnwindTest, InvalidInputs) {
    EXPECT_EQ(analyzeStubUnwind(nullptr, 64, false), nullptr);
    std::vector<uint32_t> code = {NOP, RET};
    EXPECT_EQ(analyzeStubUnwind(code.data(), 0, false), nullptr);
    EXPECT_EQ(analyzeStubUnwind(code.data(), 3, false), nullptr);   // not a whole insn
    EXPECT_EQ(analyzeStubUnwind(code.data(), -8, false), nullptr);
}

// Classic FP frame: entry state, mid-prologue state, steady state.
TEST_F(StubUnwindTest, FpFrameSimple) {
    // 0: stp x29,x30,[sp,#-16]!
    // 1: mov x29,sp
    // 2: nop (body)
    // 3: ret
    StubUnwindInfo* info = analyze({stpPre64(29, 30, -16), 0x910003fd, NOP, RET});
    ASSERT_NE(info, nullptr);
    EXPECT_TRUE(info->_classified);
    EXPECT_EQ(info->_phase_count, 3);
    expectPhase(info, 0, SU_PC_TO_LR, 0);
    expectPhase(info, 1, SU_FP_PROLOGUE, 16, 8);
    expectPhase(info, 2, SU_FP_FRAME, 16, 8);
    expectPhase(info, 3, SU_FP_FRAME, 16, 8);
}

// Larger push: caller sp is fp + 96, x30 still at fp + 8.
TEST_F(StubUnwindTest, FpFrameLargePush) {
    StubUnwindInfo* info = analyze({stpPre64(29, 30, -96), 0x910003fd, NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_FP_FRAME, 96, 8);
    expectPhase(info, 1, SU_FP_PROLOGUE, 96, 8);
}

// Callee-saved pushed before the frame link: fp_abs must account for it.
TEST_F(StubUnwindTest, FpFrameCalleeSavedFirst) {
    // 0: stp d8,d9,[sp,#-16]!
    // 1: stp x29,x30,[sp,#-16]!
    // 2: mov x29,sp
    // 3: ret
    StubUnwindInfo* info = analyze({stpPreD(8, 9, -16), stpPre64(29, 30, -16), 0x910003fd, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_SP_DELTA_LR, 16);  // only the d8/d9 push so far
    expectPhase(info, 2, SU_FP_PROLOGUE, 32, 8);
    // fp at 32 below caller sp; x30 saved 8 bytes above fp
    expectPhase(info, 3, SU_FP_FRAME, 32, 8);
}

// Frameless stub with a sub sp frame: delta only after the sub executes.
TEST_F(StubUnwindTest, FramelessSubSp) {
    // 0: sub sp,sp,#64
    // 1: nop
    // 2: add sp,sp,#64
    // 3: ret
    StubUnwindInfo* info = analyze({subSp(64), NOP, addSp(64), RET});
    ASSERT_NE(info, nullptr);
    EXPECT_TRUE(info->_classified);
    expectPhase(info, 0, SU_PC_TO_LR, 0);
    expectPhase(info, 1, SU_SP_DELTA_LR, 64);
    expectPhase(info, 2, SU_SP_DELTA_LR, 64);  // add not yet executed at PC=2
    expectPhase(info, 3, SU_PC_TO_LR, 0);
}

// Fixed-size push frame (legacy isFixedSizeFrame class).
TEST_F(StubUnwindTest, FramelessPush) {
    StubUnwindInfo* info = analyze({stpPre64(19, 20, -32), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 0, SU_PC_TO_LR, 0);
    expectPhase(info, 1, SU_SP_DELTA_LR, 32);
    expectPhase(info, 2, SU_SP_DELTA_LR, 32);
}

// True zero-frame/leaf stub (legacy isZeroSizeFrame class).
TEST_F(StubUnwindTest, ZeroFrame) {
    StubUnwindInfo* info = analyze({movReg(0, 1), NOP, RET});
    ASSERT_NE(info, nullptr);
    EXPECT_TRUE(info->_classified);
    EXPECT_EQ(info->_phase_count, 1);
    expectPhase(info, 0, SU_PC_TO_LR, 0);
    expectPhase(info, 2, SU_PC_TO_LR, 0);
}

// 128-bit SIMD pushes accumulate in the sp delta.
TEST_F(StubUnwindTest, FramelessSimdPushes) {
    StubUnwindInfo* info = analyze({stpPreQ(0, 1, -32), stpPreD(8, 9, -16), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_SP_DELTA_LR, 32);
    expectPhase(info, 2, SU_SP_DELTA_LR, 48);
}

// The legacy "fixed size frame" entry rule misapplies the delta at PC == entry;
// the phase table keeps entry exact.
TEST_F(StubUnwindTest, EntryPcBeforePush) {
    StubUnwindInfo* info = analyze({stpPre64(19, 20, -32), NOP, RET});
    expectPhase(info, 0, SU_PC_TO_LR, 0);
}

// A call from a frameless stub makes lr-dependent unwinding impossible.
TEST_F(StubUnwindTest, FramelessCallDegrades) {
    // 0: nop
    // 1: bl .+2 (out of range)
    // 2: nop
    // 3: ret
    StubUnwindInfo* info = analyze({NOP, call(2), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_PC_TO_LR, 0);
    expectPhase(info, 2, SU_UNSUPPORTED, 0);
    expectPhase(info, 3, SU_UNSUPPORTED, 0);
}

TEST_F(StubUnwindTest, FramelessCallRegDegrades) {
    StubUnwindInfo* info = analyze({callReg(9), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_UNSUPPORTED, 0);
}

// A call with fp established (or the return address on the stack) is harmless.
TEST_F(StubUnwindTest, FpFrameCallIsFine) {
    StubUnwindInfo* info =
        analyze({stpPre64(29, 30, -16), 0x910003fd, call(10), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 3, SU_FP_FRAME, 16, 8);
    expectPhase(info, 4, SU_FP_FRAME, 16, 8);
}

// x30 clobbered mid-body of a frameless stub degrades to fallback; an FP-frame
// stub keeps unwinding from the stack slot.
TEST_F(StubUnwindTest, X30Clobber) {
    StubUnwindInfo* frameless = analyze({movReg(30, 8), NOP, RET});
    expectPhase(frameless, 1, SU_UNSUPPORTED, 0);

    StubUnwindInfo* fp = analyze({stpPre64(29, 30, -16), 0x910003fd, movReg(30, 8), NOP, RET});
    expectPhase(fp, 3, SU_FP_FRAME, 16, 8);
    expectPhase(fp, 4, SU_FP_FRAME, 16, 8);
}

// A frameless spill of x30 creates a stack-slot rule (kind 2).
TEST_F(StubUnwindTest, FramelessX30Spill) {
    // 0: str x30,[sp,#-16]!
    // 1: nop
    // 2: ret
    StubUnwindInfo* info = analyze({strPreSp(30, -16), NOP, RET});
    ASSERT_NE(info, nullptr);
    // single-register spill: x30 stored at [sp_new], so the slot is at sp + 0
    expectPhase(info, 1, SU_FP_PROLOGUE, 16, 0);
}

// Mid-stub br: state after it is a separate entry path -> fallback.
TEST_F(StubUnwindTest, MidStubBrDegrades) {
    StubUnwindInfo* info = analyze({NOP, jumpReg(8), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 0, SU_PC_TO_LR, 0);
    expectPhase(info, 1, SU_PC_TO_LR, 0);
    expectPhase(info, 2, SU_UNSUPPORTED, 0);
}

// Canonical straight-line epilogue: with epilogue modeling disabled the stack
// slot keeps holding the return address, so the rules stay exact.
TEST_F(StubUnwindTest, EpiloguePostIndexLdp) {
    // 0: stp x29,x30,[sp,#-16]!
    // 1: mov x29,sp
    // 2: nop (body)
    // 3: ldp x29,x30,[sp],#16
    // 4: ret
    StubUnwindInfo* info =
        analyze({stpPre64(29, 30, -16), 0x910003fd, NOP, ldpPost64(29, 30, 16), RET},
                /*model_epilogue=*/false);
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_FP_FRAME, 16, 8);
    expectPhase(info, 3, SU_FP_FRAME, 16, 8);   // ldp not yet executed
    // after ldp: sp restored (delta 0), x30 slot still 8 bytes above old sp
    expectPhase(info, 4, SU_FP_PROLOGUE, 0, -8);
}

// Shape-B epilogue: ldp with offset, sp restored by a later add.
TEST_F(StubUnwindTest, EpilogueOffsetLdpThenAdd) {
    // 0: stp x29,x30,[sp,#-32]!
    // 1: mov x29,sp
    // 2: sub sp,sp,#16
    // 3: ldp x29,x30,[sp,#16]
    // 4: add sp,sp,#48
    // 5: ret
    StubUnwindInfo* info = analyze({stpPre64(29, 30, -32), 0x910003fd, subSp(16),
                                    ldpOff64(29, 30, 16), addSp(48), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_FP_FRAME, 32, 8);
    expectPhase(info, 3, SU_FP_FRAME, 32, 8);
    // after ldp: fp/lr restored, sp still framed (delta 48); slot at abs 24
    expectPhase(info, 4, SU_FP_PROLOGUE, 48, 24);
    // after add: sp back to caller
    expectPhase(info, 5, SU_FP_PROLOGUE, 0, -24);
}

// A branch jumping from the body into the epilogue makes the linear state
// non-unique: the epilogue range must degrade to fallback.
TEST_F(StubUnwindTest, BranchIntoEpilogueTruncates) {
    // 0: stp x29,x30,[sp,#-16]!
    // 1: mov x29,sp
    // 2: b.cond .+3  (target 5 = the ret, past the ldp transition)
    // 3: nop
    // 4: ldp x29,x30,[sp],#16
    // 5: ret
    StubUnwindInfo* info = analyze({stpPre64(29, 30, -16), 0x910003fd, branchCond(3), NOP,
                                    ldpPost64(29, 30, 16), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_FP_FRAME, 16, 8);
    // fall-through boundaries between the branch and its target keep their
    // scanned state; only the ambiguous target degrades. The ldp sits at
    // insn 4, so its transition lands at boundary 5 -- which is truncated.
    expectPhase(info, 3, SU_FP_FRAME, 16, 8);
    expectPhase(info, 4, SU_FP_FRAME, 16, 8);
    expectPhase(info, 5, SU_UNSUPPORTED, 0);
}

// Loop branches inside a stable body are consistent and change nothing.
TEST_F(StubUnwindTest, LoopBodyStaysClassified) {
    // 0: sub sp,sp,#64
    // 1: nop            <- loop body
    // 2: cbz x0, .+2    (target 4)
    // 3: b .-2          (target 1)
    // 4: add sp,sp,#64
    // 5: ret
    StubUnwindInfo* info = analyze({subSp(64), NOP, cbz(0, 2), branch(-2), addSp(64), RET});
    ASSERT_NE(info, nullptr);
    EXPECT_TRUE(info->_classified);
    expectPhase(info, 1, SU_SP_DELTA_LR, 64);
    expectPhase(info, 3, SU_SP_DELTA_LR, 64);
    expectPhase(info, 4, SU_SP_DELTA_LR, 64);
    expectPhase(info, 5, SU_PC_TO_LR, 0);
}

// mov sp, x29 (shape-A epilogue step) keeps the fp rule exact.
TEST_F(StubUnwindTest, MovSpX29) {
    // 0: stp x29,x30,[sp,#-16]!
    // 1: mov x29,sp
    // 2: sub sp,sp,#32
    // 3: mov sp,x29
    // 4: ldp x29,x30,[sp],#16
    // 5: ret
    StubUnwindInfo* info = analyze({stpPre64(29, 30, -16), 0x910003fd, subSp(32), 0x910003bf,
                                    ldpPost64(29, 30, 16), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_FP_FRAME, 16, 8);
    expectPhase(info, 3, SU_FP_FRAME, 16, 8);
    expectPhase(info, 4, SU_FP_FRAME, 16, 8);
    expectPhase(info, 5, SU_FP_PROLOGUE, 0, -8);
}

// add sp, x29, #imm restores sp from the frame pointer.
TEST_F(StubUnwindTest, AddSpFromFp) {
    StubUnwindInfo* info =
        analyze({stpPre64(29, 30, -16), 0x910003fd, subSp(48), addSpRnImm(29, 48), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_FP_FRAME, 16, 8);
    expectPhase(info, 3, SU_FP_FRAME, 16, 8);
    expectPhase(info, 4, SU_FP_FRAME, 16, 8);
}

// add x29, sp, #imm (non-zero offset) still establishes the frame when the
// saved pair sits exactly at the computed position.
TEST_F(StubUnwindTest, AddX29WithOffset) {
    // 0: sub sp,sp,#48
    // 1: stp x29,x30,[sp,#32]   pair at 16/8 below caller sp
    // 2: add x29,sp,#32         fp exactly at the saved x29 slot
    // 3: ret
    StubUnwindInfo* info =
        analyze({subSp(48), stpOff64(29, 30, 32), addRdSpImm(29, 32), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_SP_DELTA_LR, 48);
    expectPhase(info, 2, SU_FP_PROLOGUE, 48, 40);
    expectPhase(info, 3, SU_FP_FRAME, 16, 8);
}

// x29 written from a non-sp register: fp rule degrades, stack-slot rule stays.
TEST_F(StubUnwindTest, FpClobberKeepsStackSlotRule) {
    StubUnwindInfo* info =
        analyze({stpPre64(29, 30, -16), 0x910003fd, movReg(29, 0), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_FP_FRAME, 16, 8);
    expectPhase(info, 3, SU_FP_PROLOGUE, 16, 8);
    expectPhase(info, 4, SU_FP_PROLOGUE, 16, 8);
}

// mov sp, x8 (unknown source): fp rule survives, sp-based rules do not.
TEST_F(StubUnwindTest, SpClobberKeepsFpRule) {
    StubUnwindInfo* info =
        analyze({stpPre64(29, 30, -16), 0x910003fd, addSpRnImm(8, 0), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_FP_FRAME, 16, 8);
    expectPhase(info, 3, SU_FP_FRAME, 16, 8);
}

// Completely unclassifiable stub (undecodable entry with immediate x30 clobber).
TEST_F(StubUnwindTest, UnclassifiedStub) {
    StubUnwindInfo* info = analyze({callReg(9), NOP, RET});
    EXPECT_TRUE(info->_classified);  // entry state is PC_TO_LR -- classifiable
    // Force a truly unclassifiable case: an internal call whose target is the
    // stub entry truncates the table down to a single UNSUPPORTED phase.
    StubUnwindInfo* info2 = analyze({call(0), NOP});
    ASSERT_NE(info2, nullptr);
    EXPECT_FALSE(info2->_classified);
    EXPECT_EQ(info2->_phase_count, 1);
    EXPECT_EQ(info2->_phases[0].kind, SU_UNSUPPORTED);
}

// findPhase clamps out-of-range indices.
TEST_F(StubUnwindTest, FindPhaseClamps) {
    StubUnwindInfo* info = analyze({subSp(64), NOP, addSp(64), RET});
    EXPECT_EQ(info->findPhase(-3), &info->_phases[0]);
    EXPECT_EQ(info->findPhase(100000), &info->_phases[info->_phase_count - 1]);
}

// A real-shape arraycopy-like wrapper: FP frame, body call, epilogue.
TEST_F(StubUnwindTest, ArraycopyShape) {
    // 0: stp x29,x30,[sp,#-16]!
    // 1: mov x29,sp
    // 2: bl .+10      (external element copy helper, out of stub range)
    // 3: ldp x29,x30,[sp],#16
    // 4: ret
    StubUnwindInfo* info =
        analyze({stpPre64(29, 30, -16), 0x910003fd, call(10), ldpPost64(29, 30, 16), RET});
    ASSERT_NE(info, nullptr);
    EXPECT_TRUE(info->_classified);
    expectPhase(info, 0, SU_PC_TO_LR, 0);
    expectPhase(info, 1, SU_FP_PROLOGUE, 16, 8);
    expectPhase(info, 2, SU_FP_FRAME, 16, 8);
    expectPhase(info, 3, SU_FP_FRAME, 16, 8);
    expectPhase(info, 4, SU_FP_PROLOGUE, 0, -8);
}

// movk x30 with hw != 0 (a real lr clobber) must degrade the frameless state
// instead of keeping the lr rule. All wide-move encodings (sf, opc, hw) are
// recognized; here hw=1 hits the SU_UNSUPPORTED degradation path.
TEST_F(StubUnwindTest, MoveWideHighShiftClobbersLr) {
    // movk x30, #0x1234, lsl #16 = 0xf2a1235e
    StubUnwindInfo* info = analyze({movk(30, 0x1234, 16), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 0, SU_PC_TO_LR, 0);
    expectPhase(info, 1, SU_UNSUPPORTED, 0);
    // 32-bit form (movk w30) is recognized the same way
    StubUnwindInfo* info32 = analyze({movk(30, 0x1234, 16, /*sixty_four=*/false), NOP, RET});
    expectPhase(info32, 1, SU_UNSUPPORTED, 0);
}

// hw=0 64-bit wide moves were recognized before; they still are, via the
// corrected mask.
TEST_F(StubUnwindTest, MoveWideLowShiftStillRecognized) {
    StubUnwindInfo* info = analyze({movk(30, 0x1234, 0), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_UNSUPPORTED, 0);
}

// add sp, Xn, #imm, lsl #12 scales the immediate. The exposed path is the
// fp-relative restore ('add sp, x29, #imm'): 'add sp, sp, #imm' is decoded by
// decodeAddSubSp first, which already handles the shift. With the fix the
// scaled restore lands beyond the entry sp, marks sp unknown, and the range
// degrades; without it a wrong 12-bit-raw delta would be tracked as known.
TEST_F(StubUnwindTest, AddSpShiftedImmediate) {
    // 0: stp x29,x30,[sp,#-16]!
    // 1: mov x29,sp
    // 2: add sp, x29, #1, lsl #12   (sp = fp + 4096, far above the entry sp)
    // 3: mov x29, x0                (clobber fp: the sp rule must stand alone)
    // 4: nop
    // 5: ret
    StubUnwindInfo* info = analyze({stpPre64(29, 30, -16), 0x910003fd, addSpRnImmLsl12(29, 1),
                                    movReg(29, 0), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 3, SU_FP_FRAME, 16, 8);
    // sp is not 15 below the entry sp; it is 4080 above it: unknown, degrade
    expectPhase(info, 5, SU_UNSUPPORTED, 0);
}

// Post-index single loads/stores decode the genuine encoding (bits 11:10 = 01).
TEST_F(StubUnwindTest, PostIndexLdrRestoresLr) {
    // 0: sub sp,sp,#16
    // 1: ldr x30, [sp], #16   (modeled epilogue-like restore; sp back to 0)
    // 2: ret
    StubUnwindInfo* info = analyze({subSp(16), ldrPostSp(30, 16), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_SP_DELTA_LR, 16);
    expectPhase(info, 2, SU_PC_TO_LR, 0);
}

TEST_F(StubUnwindTest, PostIndexStrSpills) {
    // str x30, [sp, #-16]! has its own test (FramelessX30Spill); here the
    // post-index store form after a frame push keeps the slot exact.
    // 0: sub sp,sp,#32
    // 1: str x30, [sp], #16   (store at the pushed slot, then sp moves up 16)
    StubUnwindInfo* info = analyze({subSp(32), strPostSp(30, 16), NOP, RET});
    ASSERT_NE(info, nullptr);
    // the store happened at sp=32 below entry; sp is now 16 below entry
    expectPhase(info, 2, SU_FP_PROLOGUE, 16, -16);
}

// ldtr (unprivileged load, bits 11:10 = 10) into x30 clobbers lr: degrade.
TEST_F(StubUnwindTest, LdtrX30Degrades) {
    StubUnwindInfo* info = analyze({NOP, ldtrSp(30, 0), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_PC_TO_LR, 0);
    expectPhase(info, 2, SU_UNSUPPORTED, 0);
}

// A pair load through an untracked base moves x29/x30 into registers: the
// fp rule dies (x29 reloaded from untracked memory) but the stack-slot rule
// stays exact -- the slot still holds the return address.
TEST_F(StubUnwindTest, X29BasePairTeardownKeepsStackSlot) {
    // 0: stp x29,x30,[sp,#-16]!
    // 1: mov x29,sp
    // 2: ldp x29,x30,[x29],#16
    // 3: ret
    StubUnwindInfo* info =
        analyze({stpPre64(29, 30, -16), 0x910003fd, ldpX29BasePost(29, 30, 16), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_FP_FRAME, 16, 8);
    expectPhase(info, 3, SU_FP_PROLOGUE, 16, 8);
}

// A frameless spill of x30 through an untracked base loses the lr rule: the
// slot cannot be named, so the range degrades.
TEST_F(StubUnwindTest, UntrackedBasePairStoreDegradesFrameless) {
    // 0: stp x30, x1, [x19, #16]  (Rt x30 -> saved somewhere untracked)
    // 1: nop
    // 2: ret
    uint32_t stpX19x30 = 0xa9000000 | 19 << 5 | 1 << 10 | 30;
    StubUnwindInfo* info = analyze({stpX19x30, NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 0, SU_PC_TO_LR, 0);
    expectPhase(info, 1, SU_UNSUPPORTED, 0);
}

// A pair load through an untracked base with harmless registers (a copy
// loop's 'ldp x3, x4, [x0, #16]') is neutral: sp and the return address are
// untouched.
TEST_F(StubUnwindTest, UntrackedBasePairNeutral) {
    // 0: sub sp,sp,#16
    // 1: ldp x3, x4, [x0, #16]
    // 2: add sp,sp,#16
    // 3: ret
    uint32_t ldpX0 = 0xa9400000 | 0 << 5 | 4 << 10 | 3;
    StubUnwindInfo* info = analyze({subSp(16), ldpX0, addSp(16), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_SP_DELTA_LR, 16);
    expectPhase(info, 2, SU_SP_DELTA_LR, 16);
    expectPhase(info, 3, SU_PC_TO_LR, 0);
}

// Unsigned-offset LDR from sp uses the Rn=sp encoding; a helper that drops
// the Rn field would encode an xzr-based load and degrade instead.
TEST_F(StubUnwindTest, LdrOffSpEncoding) {
    // 0: sub sp,sp,#16
    // 1: ldr x30, [sp, #0]
    // 2: ret
    StubUnwindInfo* info = analyze({subSp(16), ldrOffSp(30, 0), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_SP_DELTA_LR, 16);
}

// A post-index load through an untracked base must not touch the tracked sp.
TEST_F(StubUnwindTest, PostIndexUntrackedBaseKeepsSp) {
    // 0: sub sp,sp,#16
    // 1: ldr x4, [x2], #8     (copy-loop shape; base x2, Rt x4)
    // 2: ret
    uint32_t ldrX2Post = 0xf8400400 | 2 << 5 | 4 | 8 << 12;
    StubUnwindInfo* info = analyze({subSp(16), ldrX2Post, NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_SP_DELTA_LR, 16);
    expectPhase(info, 2, SU_SP_DELTA_LR, 16);  // sp unchanged by the copy load
    expectPhase(info, 3, SU_SP_DELTA_LR, 16);
}

// A post-index load of x30 from an untracked base clobbers lr: degrade.
TEST_F(StubUnwindTest, PostIndexUntrackedBaseLdrX30Degrades) {
    uint32_t ldrX2PostX30 = 0xf8400400 | 2 << 5 | 30 | 8 << 12;
    StubUnwindInfo* info = analyze({NOP, ldrX2PostX30, NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_PC_TO_LR, 0);
    expectPhase(info, 2, SU_UNSUPPORTED, 0);
}

// With epilogue modeling enabled, a sp-relative ldp of x29/x30 switches the
// return address to the restored lr and drops the fp rule.
TEST_F(StubUnwindTest, ModelEpilogueSwitchesToLr) {
    // 0: stp x29,x30,[sp,#-16]!
    // 1: mov x29,sp
    // 2: ldp x29,x30,[sp],#16
    // 3: ret
    StubUnwindInfo* info =
        analyze({stpPre64(29, 30, -16), 0x910003fd, ldpPost64(29, 30, 16), RET},
                /*model_epilogue=*/true);
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_FP_FRAME, 16, 8);
    // after ldp: lr holds the return address, sp restored to the caller
    expectPhase(info, 3, SU_PC_TO_LR, 0);
}

// Shape-B epilogue with modeling: after the offset ldp the rule is the sp
// delta; after the add it is plain pc-to-lr.
TEST_F(StubUnwindTest, ModelEpilogueOffsetLdpThenAdd) {
    StubUnwindInfo* info = analyze({stpPre64(29, 30, -32), 0x910003fd, subSp(16),
                                    ldpOff64(29, 30, 16), addSp(48), RET},
                                   /*model_epilogue=*/true);
    ASSERT_NE(info, nullptr);
    expectPhase(info, 3, SU_FP_FRAME, 32, 8);
    expectPhase(info, 4, SU_SP_DELTA_LR, 48);
    expectPhase(info, 5, SU_PC_TO_LR, 0);
}

}  // namespace

#endif // __aarch64__
