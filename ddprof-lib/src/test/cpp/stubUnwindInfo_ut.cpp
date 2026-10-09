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
    // stp Xt, Xt2, [sp], #imm  (post-index: bits 25:23 = 001)
    return 0xa88003e0 | (uint32_t)((imm / 8) & 0x7f) << 15 | (uint32_t)rt2 << 10 | (uint32_t)rt;
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
// CBNZ/TBNZ: same classes with the Z/NZ polarity bit (bit 24) set (64-bit forms).
inline uint32_t cbnz(int rt, int offInsns) { return 0xb5000000 | (uint32_t)((offInsns & 0x7ffff) << 5) | (uint32_t)rt; }
inline uint32_t tbnz(int rt, int bit, int offInsns) { return 0xb7000000 | (uint32_t)bit << 19 | (uint32_t)((offInsns & 0x3fff) << 5) | (uint32_t)rt; }
// STNP/LDNP: non-temporal pairs, no-allocate mode (bits 25:23 = 000, offset
// addressing only, no writeback).
inline uint32_t stnpOff64(int rt, int rt2, int imm) {
    return 0xa80003e0 | (uint32_t)((imm / 8) & 0x7f) << 15 | (uint32_t)rt2 << 10 | (uint32_t)rt;
}
inline uint32_t ldnpOff64(int rt, int rt2, int imm) {
    return 0xa84003e0 | (uint32_t)((imm / 8) & 0x7f) << 15 | (uint32_t)rt2 << 10 | (uint32_t)rt;
}
inline uint32_t stnpQ(int rt, int rt2, int imm) {
    return 0xac0003e0 | (uint32_t)((imm / 16) & 0x7f) << 15 | (uint32_t)rt2 << 10 | (uint32_t)rt;
}
inline uint32_t ldnpQ(int rt, int rt2, int imm) {
    return 0xac4003e0 | (uint32_t)((imm / 16) & 0x7f) << 15 | (uint32_t)rt2 << 10 | (uint32_t)rt;
}
// sub sp, Xn, #imm (Rd=sp, Rn != sp)
inline uint32_t subSpRnImm(int rn, int imm) { return 0xd1000000 | 0x1f | (uint32_t)rn << 5 | (uint32_t)imm << 10; }
inline uint32_t call(int offInsns) { return 0x94000000 | (uint32_t)(offInsns & 0x03ffffff); }
inline uint32_t callReg(int rn) { return 0xd63f0000 | (uint32_t)rn << 5; }
inline uint32_t jumpReg(int rn) { return 0xd61f0000 | (uint32_t)rn << 5; }
// adrp Xd, #(pageImm * 4096) -- pageImm is the signed page-count offset,
// split across immlo (bits 30:29) and immhi (bits 23:5) the way the decoder
// in decodeAdrTarget() reassembles it.
inline uint32_t adrp(int rd, int pageImm) {
    uint32_t imm21 = (uint32_t)pageImm & 0x1fffffu;
    return 0x90000000u | ((imm21 & 0x3u) << 29) | (((imm21 >> 2) & 0x7ffffu) << 5) | (uint32_t)rd;
}

class StubUnwindTest : public ::testing::Test {
protected:
    // Classifies an instruction sequence; frees the info on scope exit.
    StubUnwindInfo* analyze(const std::vector<uint32_t>& code, bool multi_entry = false) {
        StubUnwindInfo* info =
            analyzeStubUnwind(code.data(), (int)code.size() * 4, multi_entry);
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
    EXPECT_EQ(analyzeStubUnwind(nullptr, 64), nullptr);
    std::vector<uint32_t> code = {NOP, RET};
    EXPECT_EQ(analyzeStubUnwind(code.data(), 0), nullptr);
    EXPECT_EQ(analyzeStubUnwind(code.data(), 3), nullptr);   // not a whole insn
    EXPECT_EQ(analyzeStubUnwind(code.data(), -8), nullptr);
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

// More distinct phases than the table holds: the scan must truncate while
// reserving one slot, so the SU_UNSUPPORTED terminator at the cut always
// lands. Without the reserved slot the table stayed full and PCs past the cut
// silently resolved to the last real phase (a stale rule, counted as a hit).
TEST_F(StubUnwindTest, PhaseTableOverflowKeepsTerminator) {
    // Each sub with a distinct immediate is a distinct phase; 20 of them
    // exceed the 16-slot table with room to spare.
    std::vector<uint32_t> code;
    for (int i = 1; i <= 20; i++) {
        code.push_back(subSp(8 * i));
    }
    code.push_back(NOP);
    code.push_back(RET);
    StubUnwindInfo* info = analyze(code);
    ASSERT_NE(info, nullptr);
    // 15 real phases (entry + 14 subs); the 16th slot is the terminator.
    // Local constexpr copy: the header declares MAX_PHASES without a
    // definition, so passing it to EXPECT_EQ (by reference) would be an
    // ODR-use with no symbol to link against.
    static constexpr int kMaxPhases = StubUnwindInfo::MAX_PHASES;
    EXPECT_EQ(info->_phase_count, kMaxPhases);
    // After 14 subs the sp delta is cumulative: 8*(1+2+...+14).
    expectPhase(info, 14, SU_SP_DELTA_LR, 8 * (14 * 15) / 2);
    // The cut and everything past it degrades instead of guessing.
    expectPhase(info, 15, SU_UNSUPPORTED, 0);
    expectPhase(info, 20, SU_UNSUPPORTED, 0);
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

// Outside multi-entry blobs the state after a mid-stub br is unknown (a
// jump-table entry, a return point reached through a register): fallback.
TEST_F(StubUnwindTest, MidStubBrDegrades) {
    StubUnwindInfo* info = analyze({NOP, jumpReg(8), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 0, SU_PC_TO_LR, 0);
    expectPhase(info, 1, SU_PC_TO_LR, 0);
    expectPhase(info, 2, SU_UNSUPPORTED, 0);
}

// Multi-entry blob (I2C/C2I adapters): the instruction after a mid-stub br is
// a further entry point, entered with the return address in lr and the
// caller's sp -- the state before the br (sp lowered by 16) must not leak
// into it.
TEST_F(StubUnwindTest, MidStubBrRestartsAtEntryState) {
    // 0: sub sp,sp,#16
    // 1: br x8
    // 2: nop             (second entry)
    // 3: ret
    StubUnwindInfo* info = analyze({subSp(16), jumpReg(8), NOP, RET}, true);
    ASSERT_NE(info, nullptr);
    EXPECT_TRUE(info->_classified);
    expectPhase(info, 0, SU_PC_TO_LR, 0);
    expectPhase(info, 1, SU_SP_DELTA_LR, 16);
    expectPhase(info, 2, SU_PC_TO_LR, 0);
    expectPhase(info, 3, SU_PC_TO_LR, 0);
}

// A branch from inside an fp frame into the code after a mid-stub br reaches
// it in a different state than the restarted entry state: the target must
// degrade instead of claiming the entry rule.
TEST_F(StubUnwindTest, MidStubBrFramedBranchTargetDegrades) {
    // 0: stp x29,x30,[sp,#-16]!
    // 1: mov x29,sp
    // 2: cbz x0, 5
    // 3: ldp x29,x30,[sp],#16
    // 4: br x8
    // 5: nop             (reached from 2 with the frame established)
    // 6: ret
    StubUnwindInfo* info = analyze({stpPre64(29, 30, -16), 0x910003fd, cbz(0, 3),
                                    ldpPost64(29, 30, 16), jumpReg(8), NOP, RET},
                                   true);
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_FP_FRAME, 16, 8);
    expectPhase(info, 4, SU_PC_TO_LR, 0);
    expectPhase(info, 5, SU_UNSUPPORTED, 0);
    expectPhase(info, 6, SU_UNSUPPORTED, 0);
}

// SIMD multiple-structure post-index with an immediate moves sp by the
// transfer size ('st1 {v0.2d}, [sp], #16': one Q register = 16 bytes).
TEST_F(StubUnwindTest, SimdStructPostIndexImmTracksSp) {
    // 0: sub sp,sp,#32
    // 1: st1 {v0.2d}, [sp], #16   = 0x4c9f7fe0
    // 2: ld1 {v0.1d-v3.1d}, [sp], #32 = 0x0cdf2fe0 (4 D registers: sp moves past entry)
    // 3: nop
    // 4: ret
    StubUnwindInfo* info = analyze({subSp(32), 0x4c9f7fe0, 0x0cdf2fe0, NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_SP_DELTA_LR, 32);
    expectPhase(info, 2, SU_SP_DELTA_LR, 16);
    // 16 - 32 < 0: popped beyond the entry sp, which is never a valid state
    expectPhase(info, 3, SU_UNSUPPORTED, 0);
}

// push_CPU_state shape: 'mov x8, #-32' then register-form post-index stores
// stepping sp by x8, popped by immediate-form loads. Both the ORR (HotSpot's
// choice on JDK 21) and the MOVN encoding of the constant are tracked.
TEST_F(StubUnwindTest, SimdStructPostIndexRegWithConstantTracksSp) {
    for (uint32_t mov : {0xb27bebe8u /* orr x8, xzr, #-32 */, 0x928003e8u /* movn x8, #31 */}) {
        // 0: mov x8, #-32
        // 1: sub sp,sp,#32
        // 2: st1 {v28.1d-v31.1d}, [sp], x8   = 0x0c882ffc
        // 3: st1 {v0.1d-v3.1d}, [sp]         = 0x0c002fe0 (no writeback)
        // 4: ld1 {v0.1d-v3.1d}, [sp], #32    = 0x0cdf2fe0
        // 5: ld1 {v4.1d-v7.1d}, [sp], #32    = 0x0cdf2fe4
        // 6: ret
        StubUnwindInfo* info =
            analyze({mov, subSp(32), 0x0c882ffc, 0x0c002fe0, 0x0cdf2fe0, 0x0cdf2fe4, RET});
        ASSERT_NE(info, nullptr);
        expectPhase(info, 2, SU_SP_DELTA_LR, 32);
        expectPhase(info, 3, SU_SP_DELTA_LR, 64);
        expectPhase(info, 4, SU_SP_DELTA_LR, 64);
        expectPhase(info, 5, SU_SP_DELTA_LR, 32);
        expectPhase(info, 6, SU_PC_TO_LR, 0);
    }
}

// The constant is only trusted on straight-line code that cannot write it:
// an intervening write to x8, or a branch target between definition and use,
// drops it and the register-form step degrades.
TEST_F(StubUnwindTest, SimdStructPostIndexConstantDropped) {
    // 0: mov x8, #-32
    // 1: add x8, x8, #0        = 0x91000108 (writes x8)
    // 2: sub sp,sp,#32
    // 3: st1 {v28.1d-v31.1d}, [sp], x8
    // 4: nop
    // 5: ret
    StubUnwindInfo* info = analyze({0xb27bebe8, 0x91000108, subSp(32), 0x0c882ffc, NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 3, SU_SP_DELTA_LR, 32);
    expectPhase(info, 4, SU_UNSUPPORTED, 0);

    // 0: mov x8, #-32
    // 1: cbz x0, 2              (branch target at 2: x8 unknown on that path)
    // 2: sub sp,sp,#32
    // 3: st1 {v28.1d-v31.1d}, [sp], x8
    // 4: nop
    // 5: ret
    info = analyze({0xb27bebe8, cbz(0, 1), subSp(32), 0x0c882ffc, NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 3, SU_SP_DELTA_LR, 32);
    expectPhase(info, 4, SU_UNSUPPORTED, 0);
}

// Single-structure post-index forms and register-form steps without a known
// constant are not modeled: sp becomes unknown and frameless code degrades.
TEST_F(StubUnwindTest, SimdStructPostIndexUnmodeledFormsDegrade) {
    // ld1 {v0.d}[1], [sp], #8      = 0x4ddf87e0
    // st1 {v0.s}[0], [sp], x3      = 0x0d8383e0
    // st1 {v28.1d-v31.1d}, [sp], x8 = 0x0c882ffc
    for (uint32_t insn : {0x4ddf87e0u, 0x0d8383e0u, 0x0c882ffcu}) {
        StubUnwindInfo* info = analyze({subSp(32), insn, NOP, RET});
        ASSERT_NE(info, nullptr);
        expectPhase(info, 2, SU_UNSUPPORTED, 0);
    }
}

// pop_CPU_state reloads x29 together with the other GPRs. Reloaded from the
// slot it was saved to, x29 still holds the frame address, so 'mov sp, x29'
// and the epilogue keep exact rules.
TEST_F(StubUnwindTest, X29ReloadFromSaveSlotKeepsFrame) {
    // 0: stp x29,x30,[sp,#-16]!
    // 1: mov x29,sp
    // 2: stp x28,x29,[sp,#-16]!   = 0xa9bf77fc (x29 saved at 24 below entry)
    // 3: ldp x28,x29,[sp],#16     = 0xa8c177fc
    // 4: mov sp,x29
    // 5: ldp x29,x30,[sp],#16
    // 6: ret
    StubUnwindInfo* info = analyze({stpPre64(29, 30, -16), 0x910003fd, 0xa9bf77fc, 0xa8c177fc,
                                    0x910003bf, ldpPost64(29, 30, 16), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 3, SU_FP_FRAME, 16, 8);
    expectPhase(info, 4, SU_FP_FRAME, 16, 8);
    expectPhase(info, 5, SU_FP_FRAME, 16, 8);
    expectPhase(info, 6, SU_PC_TO_LR, 0);
}

// Negative controls: x29 reloaded from another slot, or from its save slot
// after that slot was overwritten, no longer establishes the frame.
TEST_F(StubUnwindTest, X29ReloadFromOtherOrClobberedSlotDropsFrame) {
    // 3: ldp x29,x28,[sp],#16     = 0xa8c173fd (x29 from the x28 slot)
    StubUnwindInfo* info = analyze({stpPre64(29, 30, -16), 0x910003fd, 0xa9bf77fc, 0xa8c173fd,
                                    NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 4, SU_FP_PROLOGUE, 16, 8);

    // 3: str x0,[sp,#8]           = 0xf90007e0 (overwrites the x29 slot)
    // 4: ldp x28,x29,[sp],#16
    info = analyze({stpPre64(29, 30, -16), 0x910003fd, 0xa9bf77fc, 0xf90007e0, 0xa8c177fc,
                    NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 4, SU_FP_FRAME, 16, 8);
    expectPhase(info, 5, SU_FP_PROLOGUE, 16, 8);
}

// Logical immediates: 'and sp, x8, #-16' (i2c stack-argument alignment)
// writes sp; 'tst' (ANDS with Rd = xzr) does not.
TEST_F(StubUnwindTest, LogicalImmSpWrite) {
    // 1: and sp, x8, #-16         = 0x927ced1f
    StubUnwindInfo* info = analyze({NOP, 0x927ced1f, NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_PC_TO_LR, 0);
    expectPhase(info, 2, SU_UNSUPPORTED, 0);

    // 1: tst x8, #-16             = 0xf27ced1f
    info = analyze({subSp(16), 0xf27ced1f, addSp(16), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_SP_DELTA_LR, 16);
    expectPhase(info, 3, SU_PC_TO_LR, 0);
}

// A move-wide write to x29 ('mov x29, #0') moves fp off the frame.
TEST_F(StubUnwindTest, MoveWideX29DropsFrame) {
    // 2: movz x29, #0             = 0xd280001d
    StubUnwindInfo* info = analyze({stpPre64(29, 30, -16), 0x910003fd, 0xd280001d, NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_FP_FRAME, 16, 8);
    expectPhase(info, 3, SU_FP_PROLOGUE, 16, 8);
}

// Negative controls: no-writeback SIMD structure stores to sp, and post-index
// forms with a base other than sp, leave the tracked sp alone.
TEST_F(StubUnwindTest, SimdStructNoWritebackOrOtherBaseNeutral) {
    // 1: st1 {v0.2d}, [sp]         = 0x4c007fe0
    // 2: st1 {v0.2d}, [x0], #16    = 0x4c9f7c00
    StubUnwindInfo* info = analyze({subSp(16), 0x4c007fe0, 0x4c9f7c00, addSp(16), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_SP_DELTA_LR, 16);
    expectPhase(info, 3, SU_SP_DELTA_LR, 16);
    expectPhase(info, 4, SU_PC_TO_LR, 0);
}

// Inside an fp frame an unmodeled sp writeback keeps the fp rule, and
// 'mov sp, x29' makes sp exact again so the epilogue still unwinds.
TEST_F(StubUnwindTest, MovSpX29RecoversUnknownSp) {
    // 0: stp x29,x30,[sp,#-16]!
    // 1: mov x29,sp
    // 2: ld1 {v0.1d-v3.1d}, [sp], #32   = 0x0cdf2fe0
    // 3: mov sp,x29
    // 4: ldp x29,x30,[sp],#16
    // 5: ret
    StubUnwindInfo* info = analyze({stpPre64(29, 30, -16), 0x910003fd, 0x0cdf2fe0, 0x910003bf,
                                    ldpPost64(29, 30, 16), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 3, SU_FP_FRAME, 16, 8);
    expectPhase(info, 4, SU_FP_FRAME, 16, 8);
    expectPhase(info, 5, SU_PC_TO_LR, 0);
}

// 'adr xN, L; br xM; L:' materializes a return point right after the br: L
// is reached through a register, not as a fresh entry, so even in a
// multi-entry blob the restart must not claim the entry rule there (as for
// every ADR target that is not a call's return point).
TEST_F(StubUnwindTest, AdrTargetAfterRestartDegrades) {
    // 0: adr x9, #8        = 0x10000049 (-> 2)
    // 1: br x8
    // 2: nop
    // 3: ret
    StubUnwindInfo* info = analyze({0x10000049, jumpReg(8), NOP, RET}, true);
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_PC_TO_LR, 0);
    expectPhase(info, 2, SU_UNSUPPORTED, 0);
}

// ADR targets degrade before any br as well: 'adr x9, L; sub sp, sp, #16;
// ...; br x9; L:' may enter L with the caller's sp while the fall-through scan
// says sp + 16 (PR 842 review).
TEST_F(StubUnwindTest, AdrTargetBeforeBrDegrades) {
    // 0: adr x9, #12       = 0x10000069 (-> 3)
    // 1: sub sp,sp,#16
    // 2: nop
    // 3: nop             (L)
    // 4: add sp,sp,#16
    // 5: ret
    StubUnwindInfo* info = analyze({0x10000069, subSp(16), NOP, NOP, addSp(16), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_SP_DELTA_LR, 16);
    expectPhase(info, 3, SU_UNSUPPORTED, 0);
}

// The return point of an in-stub call (set_last_Java_frame's last_Java_pc) and
// an ADR of its own address ('adr x8, .') are reached in the fall-through
// state: they keep their rules.
TEST_F(StubUnwindTest, AdrReturnPointAndSelfKeepRules) {
    // 2: adr x8, #8        = 0x10000048 (-> 4, the return point of 3)
    // 3: blr x9
    // 4: nop             (L)
    StubUnwindInfo* info = analyze({stpPre64(29, 30, -16), 0x910003fd, 0x10000048, callReg(9), NOP,
                                    ldpPost64(29, 30, 16), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 4, SU_FP_FRAME, 16, 8);
    expectPhase(info, 6, SU_PC_TO_LR, 0);

    // 1: adr x8, #0        = 0x10000008 (its own address)
    info = analyze({subSp(16), 0x10000008, NOP, addSp(16), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_SP_DELTA_LR, 16);
    expectPhase(info, 2, SU_SP_DELTA_LR, 16);
}

// An ADRP into the stub's own pages hides the exact code address it builds,
// so even a multi-entry blob keeps the conservative cut after a mid-stub br.
TEST_F(StubUnwindTest, AdrpIntoStubDisablesRestart) {
    // 0: adrp x9, #0       = 0x90000009 (own page)
    // 1: br x8
    // 2: nop
    // 3: ret
    StubUnwindInfo* info = analyze({0x90000009, jumpReg(8), NOP, RET}, true);
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_PC_TO_LR, 0);
    expectPhase(info, 2, SU_UNSUPPORTED, 0);
}

// Regression: decodeAdrTarget() computes an ADRP's target page as
// pc_page + (imm << 12), and imm is frequently negative (a page behind the
// current instruction, as here). Left-shifting a negative signed value is
// undefined behavior, and this build is compiled with
// -fno-sanitize-recover=all, so UBSan aborts the process the first time this
// path runs -- before this test's own assertions ever get to run. A target
// page outside the stub must also leave the mid-stub-br restart enabled,
// the same way AdrpIntoStubDisablesRestart's own-page target disables it.
TEST_F(StubUnwindTest, AdrpNegativePageOffsetAllowsRestart) {
    // 0: adrp x9, #-4096  (one page behind this instruction -- outside the stub)
    // 1: br x8
    // 2: nop              (second entry)
    // 3: ret
    StubUnwindInfo* info = analyze({adrp(9, -1), jumpReg(8), NOP, RET}, true);
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_PC_TO_LR, 0);
    expectPhase(info, 2, SU_PC_TO_LR, 0);
}

// x29/x30 writes from classes without a dedicated decoder: unscaled and
// register-offset loads, conditional select, base writeback.
TEST_F(StubUnwindTest, UndecodedGprWritesDropFrameOrLr) {
    // 2: ldur x29, [x0, #-8]   = 0xf85f801d
    // 2: ldr x29, [x0, x1]     = 0xf861681d
    // 2: ldr x0, [x29], #8     = 0xf84087a0 (x29 written back)
    for (uint32_t insn : {0xf85f801du, 0xf861681du, 0xf84087a0u}) {
        StubUnwindInfo* info = analyze({stpPre64(29, 30, -16), 0x910003fd, insn, NOP, RET});
        ASSERT_NE(info, nullptr);
        expectPhase(info, 2, SU_FP_FRAME, 16, 8);
        expectPhase(info, 3, SU_FP_PROLOGUE, 16, 8);
    }
    // 1: csel x30, x0, x1, eq  = 0x9a81001e (frameless: lr clobbered)
    StubUnwindInfo* info = analyze({NOP, 0x9a81001e, NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_PC_TO_LR, 0);
    expectPhase(info, 2, SU_UNSUPPORTED, 0);
}

// The x29 save slot is dropped by a store through another base (it may alias
// the slot) and by an sp-derived pointer reaching a GPR.
TEST_F(StubUnwindTest, X29SaveSlotDroppedByUnmodeledAccess) {
    // 3: str x0, [x9]          = 0xf9000120
    // 3: mov x1, sp            = 0x910003e1
    for (uint32_t insn : {0xf9000120u, 0x910003e1u}) {
        StubUnwindInfo* info = analyze({stpPre64(29, 30, -16), 0x910003fd, 0xa9bf77fc, insn,
                                        0xa8c177fc, NOP, RET});
        ASSERT_NE(info, nullptr);
        expectPhase(info, 4, SU_FP_FRAME, 16, 8);
        expectPhase(info, 5, SU_FP_PROLOGUE, 16, 8);
    }
}

// An unprivileged store (STTR) overwriting the x29 save slot is a load/store
// the save-slot tracking does not model exactly, so the later reload no longer
// re-establishes the frame (PR 842 review).
TEST_F(StubUnwindTest, X29SaveSlotDroppedBySttr) {
    // 3: sttr x0, [sp, #8]     = 0xf8008be0 (overwrites the x29 slot)
    StubUnwindInfo* info = analyze({stpPre64(29, 30, -16), 0x910003fd, 0xa9bf77fc, 0xf8008be0,
                                    0xa8c177fc, NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 5, SU_FP_PROLOGUE, 16, 8);
}

// A nested spill of x30 inside an established frame moves the tracked x30
// slot, but the frame record (and the return address in it) stays at fp + 8.
// After the nested slot is popped it lies below the live sp, so the fp rule
// must keep using the frame record (PR 842 review).
TEST_F(StubUnwindTest, NestedX30SpillKeepsFrameRecordSlot) {
    // 2: stp x29,x30,[sp,#-16]!   (nested pair spill; x29 save slot)
    // 3: ldp x29,x30,[sp],#16     (reload from the save slot)
    StubUnwindInfo* info = analyze({stpPre64(29, 30, -16), 0x910003fd, 0xa9bf7bfd, 0xa8c17bfd,
                                    NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 3, SU_FP_FRAME, 16, 8);
    expectPhase(info, 4, SU_FP_FRAME, 16, 8);

    // 2: str x30,[sp,#-16]!       = 0xf81f0ffe (nested single spill)
    // 3: ldr x30,[sp],#16         = 0xf84107fe
    info = analyze({stpPre64(29, 30, -16), 0x910003fd, 0xf81f0ffe, 0xf84107fe, NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 3, SU_FP_FRAME, 16, 8);
    expectPhase(info, 4, SU_FP_FRAME, 16, 8);
}

// The x29 save slot is unowned once popped: a later reload from that position
// (after sp moves back down without a new store) may read memory a signal
// overwrote, so it must not re-establish the frame (PR 842 review).
TEST_F(StubUnwindTest, X29SaveSlotDroppedWhenPopped) {
    // 2: stp x28,x29,[sp,#-16]!   (x29 saved at 24 below entry)
    // 3: ldp x28,x29,[sp],#16     (reload, slot now below the live sp)
    // 4: sub sp,sp,#16
    // 5: ldp x28,x29,[sp]         = 0xa94077fc (same position, no new store)
    StubUnwindInfo* info = analyze({stpPre64(29, 30, -16), 0x910003fd, 0xa9bf77fc, 0xa8c177fc,
                                    subSp(16), 0xa94077fc, NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 4, SU_FP_FRAME, 16, 8);
    expectPhase(info, 6, SU_FP_PROLOGUE, 32, 24);
}

// SIMD&FP loads/stores write their GPR base on pre/post-index writeback; with
// x29 as the base the frame pointer moves (PR 842 review).
TEST_F(StubUnwindTest, SimdBaseWritebackX29DropsFrame) {
    // ldr q0, [x29], #16           = 0x3cc107a0
    // ldp q0, q1, [x29], #32       = 0xacc107a0
    // ld1 {v0.2d}, [x29], #16      = 0x4cdf7fa0
    // ldr d0, [x29, #-8]!          = 0xfc5f8fa0
    for (uint32_t insn : {0x3cc107a0u, 0xacc107a0u, 0x4cdf7fa0u, 0xfc5f8fa0u}) {
        StubUnwindInfo* info = analyze({stpPre64(29, 30, -16), 0x910003fd, insn, NOP, RET});
        ASSERT_NE(info, nullptr);
        expectPhase(info, 2, SU_FP_FRAME, 16, 8);
        expectPhase(info, 3, SU_FP_PROLOGUE, 16, 8);
    }
}

// Once more than MAX_BRANCHES edges freeze the transitions, a change of the
// auxiliary facts alone (here 'mov x8, #1' defining a constant) is not a new
// unwind rule and must not truncate the table.
TEST_F(StubUnwindTest, FrozenTransitionsIgnoreAuxiliaryFacts) {
    const int kBranches = 70;
    std::vector<uint32_t> code;
    for (int i = 0; i < kBranches; i++) {
        code.push_back(cbz(0, kBranches + 3 - i));  // all to the final ret
    }
    code.push_back(0xd2800028);  // mov x8, #1
    code.push_back(NOP);
    code.push_back(NOP);
    code.push_back(RET);
    StubUnwindInfo* info = analyze(code);
    ASSERT_NE(info, nullptr);
    expectPhase(info, kBranches + 1, SU_PC_TO_LR, 0);
    expectPhase(info, kBranches + 3, SU_PC_TO_LR, 0);
}

// Regression fixture: an 'I2C/C2I adapters' blob as reported by JVMTI
// DynamicCodeGenerated on JDK 21.0.12 aarch64 (G1), captured from a profiled
// JVM. Layout: i2c entry (frameless, ends in 'br x8' at 0x28), c2i unverified
// entry (0x2c), c2i entry with class-init barrier (0x54), c2i entry barrier
// (0x88: 'stp x10,xzr' then an fp frame around a runtime call, with
// push_CPU_state's SIMD post-index stores), patch_callers_callsite (0x1a0,
// fp frame) and skip_fixup (0x294: 'sub sp,#16' then 'br' to the
// interpreter). Out-of-blob branch targets and embedded addresses are kept
// verbatim; they do not affect the analysis. Before the mid-stub br restart
// every PC after 0x28 was SU_UNSUPPORTED and samples there ended in
// break_unwind_stub_failed.
TEST_F(StubUnwindTest, Jdk21I2CC2IAdaptersBlob) {
    static const uint32_t blob[] = {
    0xf9402188, 0xf9400281, 0xaa0803e9, 0xf942a388, 0xeb2863ff, 0x54000069,
    0x910003e8, 0xf902a388, 0xaa0903e8, 0xf901fb8c, 0xd61f0100, 0xb9400828,
    0xf2c00a08, 0xf940052a, 0xeb0a011f, 0xf940012c, 0x54000040, 0x17ffeccf,
    0xf9402588, 0xb4001248, 0x17ffeccc, 0xb9402988, 0x721d011f, 0x54000160,
    0xf9400589, 0xf9400529, 0xf9400d29, 0x3944c528, 0xf100111f, 0x540000a0,
    0xf9409d28, 0xeb08039f, 0x54000040, 0x17ffeb3f, 0xb40008ac, 0xf9400588,
    0xf9400508, 0xf9400d08, 0xf9404d08, 0xb9402509, 0xb5000809, 0xa9bf7fea,
    0xf940010a, 0xb400072a, 0xf940014a, 0xa9bf7bfd, 0x910003fd, 0x39410388,
    0x34000648, 0xb400062a, 0xf9401788, 0xb40000e8, 0xd1002108, 0xf9001788,
    0xf9401f89, 0x8b090108, 0xf900010a, 0x14000029, 0xa9b707e0, 0xa9010fe2,
    0xa90217e4, 0xa9031fe6, 0xa9042fea, 0xa90537ec, 0xa9063fee, 0xa90747f0,
    0xa9087ff2, 0xd10083ff, 0xb27bebe8, 0x0c882ffc, 0x0c882ff8, 0x0c882ff4,
    0x0c882ff0, 0x0c882fe4, 0x0c002fe0, 0xaa1c03e1, 0xaa0a03e0, 0xa9bf33e8,
    0xd283ce08, 0xf2a217e8, 0xf2df7f48, 0xd63f0100, 0xa8c133e8, 0x0cdf2fe0,
    0x0cdf2fe4, 0x0cdf2ff0, 0x0cdf2ff4, 0x0cdf2ff8, 0x0cdf2ffc, 0xa9410fe2,
    0xa94217e4, 0xa9431fe6, 0xa9442fea, 0xa94537ec, 0xa9463fee, 0xa94747f0,
    0xa9487ff2, 0xa8c907e0, 0x910003bf, 0xa8c17bfd, 0xaa0a03e8, 0xa8c17fea,
    0xb5000048, 0x17ffeaf9, 0xf9402588, 0xb4000788, 0xa9bf7bfd, 0x910003fd,
    0xa9b107e0, 0xa9010fe2, 0xa90217e4, 0xa9031fe6, 0xa90427e8, 0xa9052fea,
    0xa90637ec, 0xa9073fee, 0xa90847f0, 0xa9094ff2, 0xa90a57f4, 0xa90b5ff6,
    0xa90c67f8, 0xa90d6ffa, 0xa90e77fc, 0xb27bebe8, 0xd10083ff, 0x0c882ffc,
    0x0c882ff8, 0x0c882ff4, 0x0c882ff0, 0x0c882fec, 0x0c882fe8, 0x0c882fe4,
    0x0c002fe0, 0xaa0c03e0, 0xaa1e03e1, 0xd2875688, 0xf2a22308, 0xf2df7f48,
    0xd63f0100, 0xd5033fdf, 0x0cdf2fe0, 0x0cdf2fe4, 0x0cdf2fe8, 0x0cdf2fec,
    0x0cdf2ff0, 0x0cdf2ff4, 0x0cdf2ff8, 0x0cdf2ffc, 0xa9410fe2, 0xa94217e4,
    0xa9431fe6, 0xa94427e8, 0xa9452fea, 0xa94637ec, 0xa9473fee, 0xa94847f0,
    0xa8c907e0, 0xa94157f4, 0xa9425ff6, 0xa94367f8, 0xa9446ffa, 0xa94577fc,
    0xa8c64ff2, 0x910003bf, 0xa8c17bfd, 0x910003f3, 0xd10043ff, 0xf90003e1,
    0x910003f4, 0xf9401d88, 0xd61f0100, 0x00000000,
    };
    std::vector<uint32_t> code(blob, blob + sizeof(blob) / sizeof(blob[0]));
    // Analyzed as any other blob, everything after the i2c entry's br falls
    // back (the behavior before multi_entry).
    StubUnwindInfo* single = analyze(code);
    ASSERT_NE(single, nullptr);
    expectPhase(single, 0x28 / 4, SU_PC_TO_LR, 0);
    expectPhase(single, 0x2c / 4, SU_UNSUPPORTED, 0);
    StubUnwindInfo* info = analyze(code, true);
    ASSERT_NE(info, nullptr);
    EXPECT_TRUE(info->_classified);
    // i2c (frameless)
    expectPhase(info, 0x00 / 4, SU_PC_TO_LR, 0);
    expectPhase(info, 0x28 / 4, SU_PC_TO_LR, 0);
    // c2i unverified entry and class-init barrier: every PC sampled with
    // break_unwind_stub_failed in the captured profile
    for (int off : {0x2c, 0x38, 0x54, 0x58, 0x68, 0x74, 0x98, 0x9c, 0xa0, 0xa4}) {
        expectPhase(info, off / 4, SU_PC_TO_LR, 0);
    }
    // c2i entry barrier: x10 spill, then fp frame (x29/x30 below the spill)
    expectPhase(info, 0xa8 / 4, SU_SP_DELTA_LR, 16);
    expectPhase(info, 0xb8 / 4, SU_FP_PROLOGUE, 32, 8);
    expectPhase(info, 0xbc / 4, SU_FP_FRAME, 32, 8);
    expectPhase(info, 0x114 / 4, SU_FP_FRAME, 32, 8);   // SIMD post-index stores
    expectPhase(info, 0x148 / 4, SU_FP_FRAME, 32, 8);   // after the runtime call
    expectPhase(info, 0x18c / 4, SU_FP_FRAME, 32, 8);   // after 'mov sp, x29'
    expectPhase(info, 0x190 / 4, SU_SP_DELTA_LR, 16);
    expectPhase(info, 0x198 / 4, SU_PC_TO_LR, 0);
    // patch_callers_callsite
    expectPhase(info, 0x1a0 / 4, SU_PC_TO_LR, 0);
    expectPhase(info, 0x1ac / 4, SU_FP_PROLOGUE, 16, 8);
    expectPhase(info, 0x1b0 / 4, SU_FP_FRAME, 16, 8);
    expectPhase(info, 0x22c / 4, SU_FP_FRAME, 16, 8);
    expectPhase(info, 0x290 / 4, SU_FP_FRAME, 16, 8);
    // skip_fixup
    expectPhase(info, 0x294 / 4, SU_PC_TO_LR, 0);
    expectPhase(info, 0x2a0 / 4, SU_SP_DELTA_LR, 16);
    expectPhase(info, 0x2a8 / 4, SU_SP_DELTA_LR, 16);
}

// Canonical straight-line epilogue: after the sp-restoring ldp the return
// address lives in the restored lr -- the abandoned stack slot lies below the
// restored sp (no red zone on AArch64) and must not be trusted.
TEST_F(StubUnwindTest, EpiloguePostIndexLdp) {
    // 0: stp x29,x30,[sp,#-16]!
    // 1: mov x29,sp
    // 2: nop (body)
    // 3: ldp x29,x30,[sp],#16
    // 4: ret
    StubUnwindInfo* info =
        analyze({stpPre64(29, 30, -16), 0x910003fd, NOP, ldpPost64(29, 30, 16), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_FP_FRAME, 16, 8);
    expectPhase(info, 3, SU_FP_FRAME, 16, 8);   // ldp not yet executed
    // after ldp: sp restored (delta 0), return address back in lr
    expectPhase(info, 4, SU_PC_TO_LR, 0);
}

// Shape-B epilogue: ldp with offset, sp restored by a later add. After the
// offset ldp the rule is the sp delta (return address in lr); after the add
// it is plain pc-to-lr.
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
    // after ldp: fp/lr restored, sp still framed (delta 48)
    expectPhase(info, 4, SU_SP_DELTA_LR, 48);
    // after add: sp back to caller
    expectPhase(info, 5, SU_PC_TO_LR, 0);
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
    expectPhase(info, 5, SU_PC_TO_LR, 0);
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
    // after ldp: return address back in lr, sp restored
    expectPhase(info, 4, SU_PC_TO_LR, 0);
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
    // post-index store form pops sp above the slot it just wrote: the slot
    // (depth 32) ends up below the live sp (depth 16), i.e. in unowned
    // memory, so the stack-slot rule must degrade instead of pointing the
    // handler at it.
    // 0: sub sp,sp,#32
    // 1: str x30, [sp], #16   (store at the pushed slot, then sp moves up 16)
    // 2: nop
    // 3: ret
    StubUnwindInfo* info = analyze({subSp(32), strPostSp(30, 16), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_SP_DELTA_LR, 32);
    expectPhase(info, 2, SU_UNSUPPORTED, 0);
    expectPhase(info, 3, SU_UNSUPPORTED, 0);
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

// With epilogue modeling unconditional, a sp-relative ldp of x29/x30
// switches the return address to the restored lr and drops the fp rule.
TEST_F(StubUnwindTest, ModelEpilogueSwitchesToLr) {
    // 0: stp x29,x30,[sp,#-16]!
    // 1: mov x29,sp
    // 2: ldp x29,x30,[sp],#16
    // 3: ret
    StubUnwindInfo* info =
        analyze({stpPre64(29, 30, -16), 0x910003fd, ldpPost64(29, 30, 16), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_FP_FRAME, 16, 8);
    // after ldp: lr holds the return address, sp restored to the caller
    expectPhase(info, 3, SU_PC_TO_LR, 0);
}

// Shape-B epilogue with modeling: after the offset ldp the rule is the sp
// delta; after the add it is plain pc-to-lr.
TEST_F(StubUnwindTest, ModelEpilogueOffsetLdpThenAdd) {
    StubUnwindInfo* info = analyze({stpPre64(29, 30, -32), 0x910003fd, subSp(16),
                                    ldpOff64(29, 30, 16), addSp(48), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 3, SU_FP_FRAME, 32, 8);
    expectPhase(info, 4, SU_SP_DELTA_LR, 48);
    expectPhase(info, 5, SU_PC_TO_LR, 0);
}

// Unsigned-offset immediates are zero-extended: imm12 = 0x7ff (16376 bytes)
// must record the slot exactly 16376 bytes above the current sp. A sign
// extension bug would decode it as -8 bytes and put the slot below sp.
TEST_F(StubUnwindTest, UnsignedImm12Boundary0x7ff) {
    // 0: sub sp,sp,#2048
    // 1: str x30, [sp, #16376]
    // 2: ret
    StubUnwindInfo* info =
        analyze({subSp(2048), 0xf90003e0 | (uint32_t)(16376 / 8) << 10 | 30, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_SP_DELTA_LR, 2048);
    expectPhase(info, 2, SU_FP_PROLOGUE, 2048, 16376);
}

// Same boundary at imm12 = 0x800: the offset is +16384 bytes, never negative.
TEST_F(StubUnwindTest, UnsignedImm12Boundary0x800) {
    // 0: sub sp,sp,#2048
    // 1: str x30, [sp, #16384]
    // 2: ret
    StubUnwindInfo* info =
        analyze({subSp(2048), 0xf90003e0 | (uint32_t)(16384 / 8) << 10 | 30, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_SP_DELTA_LR, 2048);
    expectPhase(info, 2, SU_FP_PROLOGUE, 2048, 16384);
}

// An unsigned-offset LDR with a >= 16 KiB offset decodes without degrading:
// the load restores lr from the (correctly addressed) slot.
TEST_F(StubUnwindTest, UnsignedImm12LdrBoundary) {
    // 0: sub sp,sp,#2048
    // 1: ldr x30, [sp, #16384]
    // 2: ret
    StubUnwindInfo* info =
        analyze({subSp(2048), 0xf94003e0 | (uint32_t)(16384 / 8) << 10 | 30, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_SP_DELTA_LR, 2048);
    expectPhase(info, 2, SU_SP_DELTA_LR, 2048);
}

// A SIMD single-register pre-index store with an sp base ('str q0,
// [sp, #-16]!') is outside the decoded forms but writes back sp: everything
// from the next boundary on must degrade to fallback instead of being
// treated as neutral with a stale sp.
TEST_F(StubUnwindTest, UndecodedSpBaseSimdStoreDegrades) {
    // 0: str q0, [sp, #-16]!   = 0x3d9f0fe0
    // 1: nop
    // 2: ret
    StubUnwindInfo* info = analyze({0x3d9f0fe0, NOP, RET});
    ASSERT_NE(info, nullptr);
    EXPECT_TRUE(info->_classified);  // entry state is still PC_TO_LR
    expectPhase(info, 0, SU_PC_TO_LR, 0);
    expectPhase(info, 1, SU_UNSUPPORTED, 0);
    expectPhase(info, 2, SU_UNSUPPORTED, 0);
}

// An unscaled LDUR of x30 with an sp base is likewise undecoded but can move
// the return address out of lr: degrade instead of staying neutral.
TEST_F(StubUnwindTest, UndecodedSpBaseLdurX30Degrades) {
    // 0: nop
    // 1: ldur x30, [sp, #-8]   = 0xf85f83fe (unscaled: bits 11:10 = 00)
    // 2: ret
    StubUnwindInfo* info = analyze({NOP, 0xf85f83fe, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_PC_TO_LR, 0);
    expectPhase(info, 2, SU_UNSUPPORTED, 0);
}

// Negative control: the degrade triggers on the sp base register, not on the
// encoding class -- an unsigned-offset load through an untracked base stays
// neutral.
TEST_F(StubUnwindTest, UntrackedBaseUnsignedOffsetStaysNeutral) {
    // 0: sub sp,sp,#16
    // 1: ldr x4, [x0, #8]      = 0xf9400804
    // 2: ret
    StubUnwindInfo* info = analyze({subSp(16), 0xf9400804, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_SP_DELTA_LR, 16);
    expectPhase(info, 2, SU_SP_DELTA_LR, 16);
}

// STNP (no-allocate pair, bits 25:23 = 000) uses offset addressing only:
// sp must not move and the x30 spill is recorded at its exact slot. (Pre-fix
// the mode classification happened to route this encoding to the offset
// branch too -- this test pins that the explicit decode keeps it exact.)
TEST_F(StubUnwindTest, StnpOffsetPairNoWriteback) {
    // 0: sub sp,sp,#16
    // 1: stnp x29,x30,[sp,#0]
    // 2: nop
    // 3: ret
    StubUnwindInfo* info = analyze({subSp(16), stnpOff64(29, 30, 0), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 0, SU_PC_TO_LR, 0);
    expectPhase(info, 1, SU_SP_DELTA_LR, 16);
    expectPhase(info, 2, SU_FP_PROLOGUE, 16, 8);
    expectPhase(info, 3, SU_FP_PROLOGUE, 16, 8);
}

// Genuine post-index STP (bits 25:23 = 001, 0xa88.....) moves sp and is no
// longer invisible: pre-fix the encoding was undecoded (treated neutral),
// leaving a stale tracked sp after the pair's writeback.
TEST_F(StubUnwindTest, PostIndexStpTracksSp) {
    // 0: sub sp,sp,#32
    // 1: stp x19,x20,[sp],#16
    // 2: nop
    // 3: ret
    StubUnwindInfo* info = analyze({subSp(32), stpPost64(19, 20, 16), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_SP_DELTA_LR, 32);
    expectPhase(info, 2, SU_SP_DELTA_LR, 16);
    expectPhase(info, 3, SU_SP_DELTA_LR, 16);
}

// A post-index STP spilling x30 records the exact slot (post-index with a
// negative immediate: the store happens first, then sp moves further down, so
// the slot stays above the live sp and stays owned).
TEST_F(StubUnwindTest, PostIndexStpSpillExactSlot) {
    // 0: sub sp,sp,#16
    // 1: stp x29,x30,[sp],#-16
    // 2: nop
    // 3: ret
    StubUnwindInfo* info = analyze({subSp(16), stpPost64(29, 30, -16), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_SP_DELTA_LR, 16);
    expectPhase(info, 2, SU_FP_PROLOGUE, 32, 24);
    expectPhase(info, 3, SU_FP_PROLOGUE, 32, 24);
}

// LDNP (non-temporal pair load) must decode like its LDP sibling: loading x30
// switches the return address to the restored lr; loading x29 drops the fp
// rule (same as ldp). Pre-fix the encoding was neutral.
TEST_F(StubUnwindTest, LdnpRestoresLr) {
    // 0: stp x29,x30,[sp,#-16]!
    // 1: mov x29,sp
    // 2: ldnp x29,x30,[sp,#0]
    // 3: ret
    StubUnwindInfo* info =
        analyze({stpPre64(29, 30, -16), 0x910003fd, ldnpOff64(29, 30, 0), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_FP_FRAME, 16, 8);
    expectPhase(info, 3, SU_SP_DELTA_LR, 16);
}

// SIMD non-temporal pairs decode as offset-mode with no writeback and no GPR
// side effects: sp stays put and no x29/x30 tracking occurs.
TEST_F(StubUnwindTest, SimdNonTemporalPairsNeutral) {
    // 0: sub sp,sp,#64
    // 1: stnp q0,q1,[sp,#-32]
    // 2: ldnp q2,q3,[sp,#32]
    // 3: add sp,sp,#64
    // 4: ret
    StubUnwindInfo* info =
        analyze({subSp(64), stnpQ(0, 1, -32), ldnpQ(2, 3, 32), addSp(64), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_SP_DELTA_LR, 64);
    expectPhase(info, 2, SU_SP_DELTA_LR, 64);
    expectPhase(info, 3, SU_SP_DELTA_LR, 64);
    expectPhase(info, 4, SU_PC_TO_LR, 0);
}

// CBNZ/TBNZ (bit 24 = Z/NZ polarity, so the mask must leave it free) must be
// collected like CBZ/TBZ: an edge into a boundary with a different unwind
// rule degrades from the target on. Pre-fix CBNZ/TBNZ were invisible and the
// divergent edge went unvalidated.
TEST_F(StubUnwindTest, CbnzEdgeValidated) {
    // 0: nop
    // 1: cbnz x0, .+2   (target 3; the sub at insn 2 makes boundary 3 --
    // 2: sub sp,sp,#16    the target's boundary -- diverge from insn 1's rule)
    // 3: nop
    // 4: ret
    StubUnwindInfo* info = analyze({NOP, cbnz(0, 2), subSp(16), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 0, SU_PC_TO_LR, 0);
    expectPhase(info, 1, SU_PC_TO_LR, 0);
    expectPhase(info, 2, SU_PC_TO_LR, 0);
    expectPhase(info, 3, SU_UNSUPPORTED, 0);
    expectPhase(info, 4, SU_UNSUPPORTED, 0);
}

TEST_F(StubUnwindTest, TbnzEdgeValidated) {
    // 0: nop
    // 1: tbnz x0, #0, .+2  (target 3; divergence at the target's boundary)
    // 2: sub sp,sp,#16
    // 3: nop
    // 4: ret
    StubUnwindInfo* info = analyze({NOP, tbnz(0, 0, 2), subSp(16), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 0, SU_PC_TO_LR, 0);
    expectPhase(info, 1, SU_PC_TO_LR, 0);
    expectPhase(info, 2, SU_PC_TO_LR, 0);
    expectPhase(info, 3, SU_UNSUPPORTED, 0);
    expectPhase(info, 4, SU_UNSUPPORTED, 0);
}

// Negative control: a CBNZ edge whose target boundary has the same unwind
// rule is consistent and must not truncate anything.
TEST_F(StubUnwindTest, CbnzConsistentEdgeNoTruncation) {
    // 0: sub sp,sp,#16
    // 1: nop
    // 2: cbnz x0, .+1   (target 3)
    // 3: add sp,sp,#16
    // 4: ret
    StubUnwindInfo* info = analyze({subSp(16), NOP, cbnz(0, 1), addSp(16), RET});
    ASSERT_NE(info, nullptr);
    EXPECT_TRUE(info->_classified);
    expectPhase(info, 2, SU_SP_DELTA_LR, 16);
    expectPhase(info, 3, SU_SP_DELTA_LR, 16);
    expectPhase(info, 4, SU_PC_TO_LR, 0);
}

// fp_est with the frame record below the live sp (sp popped past it, staying
// inside the entry frame): the fp-based slot lies below sp in unowned memory
// and must degrade instead of being handed to the signal handler.
TEST_F(StubUnwindTest, FpOwnershipGuardDegrades) {
    // 0: stp x29,x30,[sp,#-32]!
    // 1: mov x29,sp
    // 2: add sp,sp,#16   (sp above the frame record, still below entry sp)
    // 3: ret
    StubUnwindInfo* info = analyze({stpPre64(29, 30, -32), 0x910003fd, addSp(16), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_FP_PROLOGUE, 32, 8);
    expectPhase(info, 2, SU_FP_FRAME, 32, 8);
    expectPhase(info, 3, SU_UNSUPPORTED, 0);
}

// Same ownership rule for the RET_STACK slot: a pop that leaves the saved
// return address below the live sp must degrade.
TEST_F(StubUnwindTest, StackSlotOwnershipGuardDegrades) {
    // 0: str x30,[sp,#-32]!
    // 1: add sp,sp,#16
    // 2: ret
    StubUnwindInfo* info = analyze({strPreSp(30, -32), addSp(16), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_FP_PROLOGUE, 32, 0);
    expectPhase(info, 2, SU_UNSUPPORTED, 0);
}

// sub sp, x29, #imm with fp established tracks sp exactly (mirror of the ADD
// case); the exact delta becomes visible once fp is clobbered. Pre-fix the
// encoding was neutral, leaving a stale sp.
TEST_F(StubUnwindTest, SubSpFromFpExact) {
    // 0: stp x29,x30,[sp,#-32]!
    // 1: mov x29,sp
    // 2: sub sp,x29,#16
    // 3: mov x29,x0        (clobber fp: expose the tracked sp)
    // 4: ret
    StubUnwindInfo* info =
        analyze({stpPre64(29, 30, -32), 0x910003fd, subSpRnImm(29, 16), movReg(29, 0), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 2, SU_FP_FRAME, 32, 8);
    expectPhase(info, 3, SU_FP_FRAME, 32, 8);
    expectPhase(info, 4, SU_FP_PROLOGUE, 48, 24);
}

// sub sp, x0, #imm (unknown source register): sp becomes unknown and the
// range degrades instead of keeping a stale sp. Pre-fix: neutral.
TEST_F(StubUnwindTest, SubSpUnknownSourceDegrades) {
    // 0: nop
    // 1: sub sp,x0,#16
    // 2: nop
    // 3: ret
    StubUnwindInfo* info = analyze({NOP, subSpRnImm(0, 16), NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_PC_TO_LR, 0);
    expectPhase(info, 2, SU_UNSUPPORTED, 0);
    expectPhase(info, 3, SU_UNSUPPORTED, 0);
}

// A register-form add writing sp (add sp, sp, x0) is unmodeled: sp becomes
// unknown and the range degrades instead of keeping a stale sp. Pre-fix: the
// encoding fell through to the neutral assumption.
TEST_F(StubUnwindTest, AddSubRegSpDegrades) {
    // 0: sub sp,sp,#16
    // 1: add sp,sp,x0     = 0x8b0003ff
    // 2: nop
    // 3: ret
    StubUnwindInfo* info = analyze({subSp(16), 0x8b0003ff, NOP, RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_SP_DELTA_LR, 16);
    expectPhase(info, 2, SU_UNSUPPORTED, 0);
    expectPhase(info, 3, SU_UNSUPPORTED, 0);
}

// Negative control: flag-setting (ADDS) and logical (ORR) forms write XZR/NZCV
// at Rd=31, not SP -- they must stay neutral (no degradation).
TEST_F(StubUnwindTest, AddsAndLogicalXzrStayNeutral) {
    // 0: sub sp,sp,#16
    // 1: adds xzr, xzr, x0  = 0xab0003ff
    // 2: orr xzr, xzr, x0   = 0xaa0003ff
    // 3: add sp,sp,#16
    // 4: ret
    StubUnwindInfo* info = analyze({subSp(16), 0xab0003ff, 0xaa0003ff, addSp(16), RET});
    ASSERT_NE(info, nullptr);
    expectPhase(info, 1, SU_SP_DELTA_LR, 16);
    expectPhase(info, 2, SU_SP_DELTA_LR, 16);
    expectPhase(info, 3, SU_SP_DELTA_LR, 16);
    expectPhase(info, 4, SU_PC_TO_LR, 0);
}

}  // namespace

#endif // __aarch64__
