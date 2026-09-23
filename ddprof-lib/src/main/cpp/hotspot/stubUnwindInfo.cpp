/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __aarch64__

#include "hotspot/stubUnwindInfo.h"

#include <stdlib.h>

// Minimal AArch64 instruction decoder plus stub-unwind classifier.
//
// This is NOT a disassembler: it recognizes only the instruction classes that
// shape sp/fp/x30 or control flow in JVM-generated stubs. All encodings below
// were verified with an actual assembler; masks keep the fixed opcode bits
// plus Rn where required, and leave register/immediate fields free for
// extraction. Anything undecodable is assumed to preserve sp/fp/x30 -- the
// same assumption the legacy name-based heuristics make for stub bodies.

typedef unsigned int instruction_t;  // matches arch.h on aarch64

namespace {

const int INSN_SIZE = 4;
const int MAX_BRANCHES = 64;
// Sanity cap; the largest generated stubs are a few KB. Larger ranges are
// left to the legacy heuristics.
const int MAX_STUB_BYTES = 64 * 1024;

inline int32_t sext(uint32_t value, int bits) {
    uint32_t m = 1u << (bits - 1);
    return (int32_t)((value ^ m) - m);
}

inline int rt1(uint32_t insn) { return insn & 31; }          // bits 4..0
inline int rt2(uint32_t insn) { return (insn >> 10) & 31; }  // bits 14..10
inline int rn(uint32_t insn)  { return (insn >> 5) & 31; }   // bits 9..5
inline int rd(uint32_t insn)  { return insn & 31; }

// --- Load/store pair (LDP/STP) with sp base -------------------------------
//
// Encoding (assembler-verified anchors: stp x29,x30,[sp,#-16]! = 0xa9bf7bfd,
// stp x19,x20,[sp,#-32]! = 0xa9be53f3, stp q0,q1,[sp,#-32]! = 0xadbf07e0,
// stp d8,d9,[sp,#-16]! = 0x6dbf27e8, stp x29,x30,[sp],#16 = 0xa8817bfd,
// ldp x29,x30,[sp],#16 = 0xa8c17bfd, ldp x29,x30,[sp,#8] = 0xa940fbfd,
// ldp d8,d9,[sp],#16 = 0x6cc127e8):
//   bits31-27 = opc(2) 101, bit26 = V, bit25-24 = 10 (offset/pre) or 00 (post),
//   bit23 = 1 for pre-index, bit22 = L (1 = load), imm7 at bits21-15,
//   Rt2 at bits14-10, Rn at bits9-5, Rt at bits4-0.
//   GPR pairs scale imm7 by 8; SIMD q pairs by 16.
// hotspotStackFrame_aarch64.cpp isSTP() masks (0xa9a003e0 / 0x6da003e0) are
// subsets of the pre-index masks below restricted to negative immediates.

struct PairInfo {
    bool load;
    int32_t imm;   // bytes, scaled and sign-extended
    bool gpr;      // false for SIMD pairs (their Rt fields are not GPR numbers)
    int base;      // Rn field: 31 = sp, 29 = fp, anything else is untracked
};

bool decodePair(uint32_t insn, PairInfo& p) {
    static const struct { uint32_t mask, value; int scale; } forms[] = {
        // value = fixed bits 31-22; imm7/Rt2/Rn/Rt left free (Rn filtered below)
        { 0xffc00000, 0xa8000000, 8 },   // GPR post-index STP  ..., [Xn], #imm
        { 0xffc00000, 0xa8c00000, 8 },   // GPR post-index LDP
        { 0xffc00000, 0xa9000000, 8 },   // GPR offset     STP  ..., [Xn, #imm]
        { 0xffc00000, 0xa9400000, 8 },   // GPR offset     LDP
        { 0xffc00000, 0xa9800000, 8 },   // GPR pre-index  STP  ..., [Xn, #imm]!
        { 0xffc00000, 0xa9c00000, 8 },   // GPR pre-index  LDP
        { 0xffc00000, 0x6c800000, 8 },   // SIMD d post-index STP
        { 0xffc00000, 0x6cc00000, 8 },   // SIMD d post-index LDP
        { 0xffc00000, 0x6d000000, 8 },   // SIMD d offset  STP
        { 0xffc00000, 0x6d400000, 8 },   // SIMD d offset  LDP
        { 0xffc00000, 0x6d800000, 8 },   // SIMD d pre-index STP
        { 0xffc00000, 0x6dc00000, 8 },   // SIMD d pre-index LDP
        { 0xffc00000, 0xac800000, 16 },  // SIMD q post-index STP
        { 0xffc00000, 0xacc00000, 16 },  // SIMD q post-index LDP
        { 0xffc00000, 0xad000000, 16 },  // SIMD q offset  STP
        { 0xffc00000, 0xad400000, 16 },  // SIMD q offset  LDP
        { 0xffc00000, 0xad800000, 16 },  // SIMD q pre-index STP
        { 0xffc00000, 0xadc00000, 16 },  // SIMD q pre-index LDP
    };
    for (const auto& f : forms) {
        if ((insn & f.mask) != f.value) continue;
        p.imm = sext((insn >> 15) & 0x7f, 7) * f.scale;
        p.load = (insn >> 22) & 1;
        p.gpr = ((insn >> 26) & 0x3f) == 0x2a;  // opc=10, V=0
        p.base = rn(insn);
        return true;
    }
    return false;
}

// --- Single LDR/STR, 64-bit ------------------------------------------------

struct SingleInfo {
    bool load;
    int mode;     // 0 unsigned offset, 1 pre-index, 2 post-index
    int32_t imm;  // bytes (scaled by 8 for unsigned form, raw imm9 otherwise)
    int base;     // Rn field: 31 = sp, anything else is untracked
};

bool decodeSingle(uint32_t insn, SingleInfo& s) {
    if ((insn & 0xffc00000) == 0xf9000000) {  // STR unsigned imm
        s = { false, 0, sext((insn >> 10) & 0xfff, 12) * 8, rn(insn) };
        return true;
    }
    if ((insn & 0xffc00000) == 0xf9400000) {  // LDR unsigned imm
        s = { true, 0, sext((insn >> 10) & 0xfff, 12) * 8, rn(insn) };
        return true;
    }
    if ((insn & 0xffe00c00) == 0xf8000c00) {  // STR pre-index (bits 11:10 = 11)
        s = { false, 1, sext((insn >> 12) & 0x1ff, 9), rn(insn) };
        return true;
    }
    if ((insn & 0xffe00c00) == 0xf8000400) {  // STR post-index (bits 11:10 = 01)
        s = { false, 2, sext((insn >> 12) & 0x1ff, 9), rn(insn) };
        return true;
    }
    if ((insn & 0xffe00c00) == 0xf8400c00) {  // LDR pre-index
        s = { true, 1, sext((insn >> 12) & 0x1ff, 9), rn(insn) };
        return true;
    }
    if ((insn & 0xffe00c00) == 0xf8400400) {  // LDR post-index
        s = { true, 2, sext((insn >> 12) & 0x1ff, 9), rn(insn) };
        return true;
    }
    return false;
}

// LDTR/STTR (unprivileged, bits 11:10 = 10): no base writeback, but a load
// into x30 still clobbers the return-address register and must degrade the
// state instead of being silently treated as neutral.
bool isUnprivLoadStore(uint32_t insn) {
    return (insn & 0xffe00c00) == 0xf8000800 || (insn & 0xffe00c00) == 0xf8400800;
}

// --- ADD/SUB immediate ------------------------------------------------------

// add/sub sp, sp, #imm (optionally lsl #12). Masks match the ones already used
// by hotspotStackFrame_aarch64.cpp (isFrameComplete / isPollReturn).
bool decodeAddSubSp(uint32_t insn, bool& is_sub, int32_t& imm) {
    uint32_t op = insn & 0xff8003ff;  // fixes opcode + Rn=Rd=sp
    if (op == 0x910003ff) {
        is_sub = false;
    } else if (op == 0xd10003ff) {
        is_sub = true;
    } else {
        return false;
    }
    imm = (insn >> 10) & 0xfff;
    if ((insn >> 22) & 1) imm <<= 12;
    return true;
}

// ADD (immediate), 64-bit: returns Rd/Rn/imm. The lsl #12 shift form is
// accepted (bit 22 is excluded from the mask) and applied to imm -- a shifted
// 'add sp, Xn, #imm' must update the tracked sp exactly, not fall through to
// the undecodable-neutral assumption while sp actually moves.
bool decodeAddImm(uint32_t insn, int& rdn, int& rnn, int32_t& imm) {
    if ((insn & 0xff800000) != 0x91000000) return false;
    rdn = rd(insn);
    rnn = rn(insn);
    imm = (insn >> 10) & 0xfff;
    if ((insn >> 22) & 1) imm <<= 12;
    return true;
}

// mov Xd, Xm (ORR shifted register; Rn=xzr for the plain MOV alias, but any
// ORR writing Xd matters to us).
bool isOrrReg(uint32_t insn) {
    return (insn & 0x7f800000) == 0x2a000000;
}

// ADR/ADRP: writes a computed address, potentially into x30.
bool isAdrLike(uint32_t insn) {
    return (insn & 0x1f000000) == 0x10000000;
}

// MOVZ/MOVK/MOVN (wide immediates), both sizes: x30 as a data register.
// Fixed bits 28-23 = 100101 (sf and opc free above bit 28, hw free below);
// this covers every hw value, so a 'movk x30, #imm, lsl #16' clobber is
// recognized and degrades the state instead of being treated as neutral.
bool isMoveWide(uint32_t insn) {
    return (insn & 0x1f800000) == 0x12800000;
}

// Branches. Returns the target instruction index for in-range targets,
// or -1. unconditional_exit is set for B.
int decodeBranch(uint32_t insn, int index, int count, bool& unconditional_exit) {
    unconditional_exit = false;
    int64_t off;
    if ((insn >> 26) == 0x05) {  // B
        off = sext(insn & 0x03ffffff, 26);
        unconditional_exit = true;
    } else if ((insn & 0xff000010) == 0x54000000) {  // B.cond
        off = sext((insn >> 5) & 0x7ffff, 19);
    } else if ((insn & 0x7f000000) == 0x34000000) {  // CBZ/CBNZ
        off = sext((insn >> 5) & 0x7ffff, 19);
    } else if ((insn & 0x7f000000) == 0x36000000) {  // TBZ/TBNZ
        off = sext((insn >> 5) & 0x3fff, 14);
    } else {
        return -1;  // not a branch (BL/BLR/BR/RET handled by the caller)
    }
    int target = index + (int)off;
    if (target < 0 || target >= count) return -1;  // leaves the stub
    return target;
}

// --- Scan state -------------------------------------------------------------

enum RetLoc { RET_LR, RET_STACK, RET_CONT, RET_UNKNOWN };

struct ScanState {
    int32_t sp = 0;       // sp position in bytes below the entry sp
    bool sp_known = true;
    bool fp_est = false;  // x29 points at the saved-x29 slot of the current frame
    int32_t fp_abs = 0;   // position of that slot below the entry sp
    RetLoc ret = RET_LR;
    int32_t x30_abs = 0;  // position of the saved x30 slot below the entry sp

    bool operator==(const ScanState& o) const {
        return sp == o.sp && sp_known == o.sp_known && fp_est == o.fp_est &&
               fp_abs == o.fp_abs && ret == o.ret && x30_abs == o.x30_abs;
    }
    bool operator!=(const ScanState& o) const { return !(*this == o); }

    // The unwind rule that holds at a PC boundary in this state.
    void phase(StubUnwindPhase& p, int offset) const {
        p.insn_offset = (uint16_t)offset;
        p._pad = 0;
        if (!sp_known) {
            // sp moved to an unknown value; only fp-based unwinding survives,
            // and only if fp still points at our frame.
            if (fp_est) {
                p.kind = SU_FP_FRAME;
                p.arg = fp_abs;
                p.arg2 = fp_abs - x30_abs;
            } else {
                p.kind = SU_UNSUPPORTED;
                p.arg = p.arg2 = 0;
            }
            return;
        }
        if (fp_est) {
            p.kind = SU_FP_FRAME;
            p.arg = fp_abs;             // caller sp = fp + arg
            p.arg2 = fp_abs - x30_abs;  // pc slot = [fp + arg2]
        } else if (ret == RET_STACK) {
            // Return address spilled to the stack (mid-prologue, or a stub
            // that spills x30 without setting up fp). The rule stays exact
            // through the epilogue as well: the slot keeps holding the return
            // address until the stub returns.
            p.kind = SU_FP_PROLOGUE;
            p.arg = sp;             // caller sp = sp + arg
            p.arg2 = sp - x30_abs;  // pc slot = [sp + arg2]
        } else if (ret == RET_LR) {
            if (sp == 0) {
                p.kind = SU_PC_TO_LR;
                p.arg = p.arg2 = 0;
            } else {
                p.kind = SU_SP_DELTA_LR;
                p.arg = sp;
                p.arg2 = 0;
            }
        } else {
            p.kind = SU_UNSUPPORTED;
            p.arg = p.arg2 = 0;
        }
    }
};

struct Edge {
    int from;
    int to;
};

// Register effects of a load/store through a base we do not track: sp is
// untouched, but x30 moving between lr and memory we cannot name kills the
// lr rule, and a reload of x29 kills the fp rule. rt2 < 0 for single-register
// accesses.
void untrackedBase(int rt1v, int rt2v, bool load, ScanState& next) {
    bool touches_x30 = rt1v == 30 || rt2v == 30;
    bool touches_x29 = rt1v == 29 || rt2v == 29;
    if (load) {
        if (touches_x30 && next.ret == RET_LR) next.ret = RET_UNKNOWN;
        if (touches_x29) next.fp_est = false;
    } else if (touches_x30 && next.ret == RET_LR) {
        next.ret = RET_UNKNOWN;  // saved somewhere we cannot name
    }
}

}  // namespace

const StubUnwindPhase* StubUnwindInfo::findPhase(int insn_index) const {
    // The table always holds at least the entry phase, and truncation keeps
    // one SU_UNSUPPORTED phase at the cut, so no empty-table guard is needed.
    // Clamp; the caller may pass an index past the last instruction boundary.
    if (insn_index < 0) insn_index = 0;
    int lo = 0, hi = _phase_count - 1;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (_phases[mid].insn_offset <= insn_index) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    return &_phases[lo];
}

StubUnwindInfo* analyzeStubUnwind(const void* start, int length, bool model_epilogue) {
    if (start == nullptr || length <= 0 || length > MAX_STUB_BYTES ||
        (length & (INSN_SIZE - 1)) != 0) {
        return nullptr;
    }
    const instruction_t* entry = (const instruction_t*)start;
    int count = length / INSN_SIZE;

    StubUnwindInfo* info = (StubUnwindInfo*)malloc(sizeof(StubUnwindInfo));
    if (info == nullptr) return nullptr;
    info->_start = start;
    info->_end = (const char*)start + length;
    // malloc does not zero: uninitialized _phase_count would make emit()
    // index _phases[] with garbage (observed as SIGSEGV on Linux glibc;
    // macOS zero pages masked it).
    info->_phase_count = 0;
    info->_classified = false;

    ScanState st;

    int truncate_at = count;  // first insn index whose state is untrustworthy
    bool transitions_frozen = false;
    Edge edges[MAX_BRANCHES];
    int edge_count = 0;

    auto emit = [&](const ScanState& s, int offset) {
        StubUnwindPhase p;
        s.phase(p, offset);
        int n = info->_phase_count;
        if (n > 0) {
            const StubUnwindPhase& last = info->_phases[n - 1];
            if (p.kind == last.kind && p.arg == last.arg && p.arg2 == last.arg2) {
                return;  // same rule as the open phase: extend it
            }
        }
        if (n >= StubUnwindInfo::MAX_PHASES) {
            // Too many state transitions to tabulate: keep only what was
            // recorded before this boundary.
            if (offset < truncate_at) truncate_at = offset;
            transitions_frozen = true;
            return;
        }
        info->_phases[n] = p;
        info->_phase_count = (uint8_t)(n + 1);
    };
    emit(st, 0);

    for (int i = 0; i < count; i++) {
        uint32_t insn = entry[i];
        ScanState next = st;
        bool freeze_now = false;

        PairInfo pair;
        SingleInfo single;
        if (decodePair(insn, pair)) {
            if (pair.base != 31) {
                // Untracked base (a copy loop's 'ldp x3, x4, [x0, #16]' or an
                // fp teardown 'ldp x29, x30, [x29], #16'): no writeback
                // reaches sp, so only the register effects of untrackedBase()
                // apply.
                if (pair.gpr) {
                    untrackedBase(rt1(insn), rt2(insn), pair.load, next);
                }
            } else {
                // Address of the accessed pair, in bytes below the entry sp.
                int32_t addr_abs;
                const uint32_t form = insn & 0x01800000;  // bit24, bit23
                // Anchor-verified form bits: post-index 0xa8817bfd -> b24=0,b23=1;
                // offset 0xa900fbfd -> b24=1,b23=0; pre 0xa9bf7bfd -> b24=1,b23=1.
                if (form == 0x00800000) {                 // post-index: sp moves up
                    addr_abs = next.sp;
                    next.sp -= pair.imm;
                } else if (form == 0x01800000) {          // pre-index: sp moves by imm
                    next.sp -= pair.imm;
                    addr_abs = next.sp;
                } else {                                  // offset form (b24=1,b23=0)
                    addr_abs = next.sp - pair.imm;
                }
                if (next.sp < 0) next.sp_known = false;
                if (pair.gpr) {
                    int a = rt1(insn), b = rt2(insn);
                    if (pair.load) {
                        if (a == 30 || b == 30) {
                            if (next.ret == RET_STACK && !model_epilogue) {
                                // Epilogue transitions are not modeled in this
                                // build: keep trusting the stack slot (still
                                // exact) instead of switching to lr.
                            } else if (next.ret != RET_CONT) {
                                next.ret = RET_LR;
                            }
                        }
                        if (a == 29 || b == 29) {
                            next.fp_est = false;  // x29 reloaded: no longer our frame fp
                        }
                    } else {
                        if (a == 30 || b == 30) {
                            next.ret = RET_STACK;
                            next.x30_abs = (a == 30) ? addr_abs : addr_abs - 8;
                        }
                    }
                }
            }
        } else if (decodeSingle(insn, single)) {
            if (single.base != 31) {
                // Untracked base (e.g. a copy loop's 'ldr x4, [x2], #8'):
                // only the register effects apply, as for pairs.
                untrackedBase(rd(insn), -1, single.load, next);
            } else {
                int32_t addr_abs;
                if (single.mode == 2) {  // post-index: sp moves up
                    addr_abs = next.sp;
                    next.sp -= single.imm;
                } else if (single.mode == 1) {  // pre-index
                    next.sp -= single.imm;
                    addr_abs = next.sp;
                } else {  // unsigned offset
                    addr_abs = next.sp - single.imm;
                }
                if (next.sp < 0) next.sp_known = false;
                int t = rd(insn);  // Rt field for loads/stores
                if (t == 30) {
                    if (single.load) {
                        if (next.ret == RET_STACK && !model_epilogue) {
                            // see above: keep trusting the stack slot
                        } else if (next.ret == RET_CONT) {
                            // sticky: the loaded value may be a call continuation
                        } else if (rn(insn) == 31) {
                            next.ret = RET_LR;
                        } else {
                            next.ret = RET_UNKNOWN;
                        }
                    } else if (rn(insn) == 31) {
                        next.ret = RET_STACK;
                        next.x30_abs = addr_abs;
                    } else if (next.ret == RET_LR) {
                        next.ret = RET_UNKNOWN;  // saved somewhere we cannot name
                    }
                } else if (t == 29 && single.load) {
                    next.fp_est = false;
                }
            }
        } else {
            bool is_sub;
            int32_t imm;
            int rdn, rnn, aimm;
            if (decodeAddSubSp(insn, is_sub, imm)) {
                next.sp += is_sub ? imm : -imm;
                if (next.sp < 0) next.sp_known = false;
            } else if (decodeAddImm(insn, rdn, rnn, aimm)) {
                if (rdn == 31) {
                    // add sp, sp, #imm / add sp, Xn, #imm ("mov sp, x29")
                    if (rnn == 31) {
                        next.sp -= aimm;
                    } else if (rnn == 29 && next.fp_est) {
                        next.sp = next.fp_abs - aimm;
                    } else {
                        next.sp_known = false;
                    }
                    if (next.sp < 0) next.sp_known = false;
                } else if (rdn == 29) {
                    // mov x29, sp / add x29, sp, #imm, or x29 from elsewhere
                    int32_t cand = next.sp - aimm;
                    if (rnn == 31 && next.sp_known && next.ret == RET_STACK &&
                        next.x30_abs == cand - 8) {
                        // x29 lands exactly on the saved-x29 slot: frame established
                        next.fp_est = true;
                        next.fp_abs = cand;
                    } else if (next.fp_est) {
                        next.fp_est = false;  // fp points somewhere else now
                    }
                } else if (rdn == 30 && next.ret == RET_LR) {
                    next.ret = RET_UNKNOWN;
                }
            } else if (isOrrReg(insn)) {
                int d = rd(insn);
                if (d == 29) {
                    next.fp_est = false;
                } else if (d == 30 && next.ret == RET_LR) {
                    next.ret = RET_UNKNOWN;
                }
            } else if (isAdrLike(insn) || isMoveWide(insn)) {
                if (rd(insn) == 30 && next.ret == RET_LR) {
                    next.ret = RET_UNKNOWN;
                }
            } else if ((insn >> 26) == 0x25) {  // BL
                int64_t target = i + (int64_t)sext(insn & 0x03ffffff, 26);
                if (target >= 0 && target < count) {
                    // Internal call: the target is entered with unknown state.
                    if (target < truncate_at) truncate_at = (int)target;
                }
                if (!next.fp_est && next.ret == RET_LR) {
                    // Frameless call: the return address held only in lr is
                    // overwritten by the continuation address and never
                    // restored to its original value; lr-dependent unwinding
                    // becomes impossible for the rest of the stub.
                    next.ret = RET_CONT;
                }
                // With fp established or the return address on the stack, an
                // external call does not affect unwinding: the callee returns
                // before any in-stub PC can be sampled.
            } else if ((insn & 0xfffffc1f) == 0xd63f0000) {  // BLR
                if (!next.fp_est && next.ret == RET_LR) {
                    next.ret = RET_CONT;
                }
            } else if ((insn & 0xfffffc1f) == 0xd61f0000) {  // BR
                if (i + 1 < count) {
                    // Control leaves the stub; linear state after a mid-stub
                    // branch is not trustworthy (it may be a separate entry
                    // path with unknown state).
                    if (i + 1 < truncate_at) truncate_at = i + 1;
                    freeze_now = true;
                }
            } else if (isUnprivLoadStore(insn)) {
                // LDTR/STTR: no base writeback, so sp is unchanged; a load
                // into x30 clobbers the return-address register.
                if ((insn >> 22) & 1) {
                    if (rd(insn) == 30 && next.ret == RET_LR) next.ret = RET_UNKNOWN;
                }
            } else {
                bool uncond_exit;
                int target = decodeBranch(insn, i, count, uncond_exit);
                if (target >= 0) {
                    if (edge_count < MAX_BRANCHES) {
                        edges[edge_count++] = { i, target };
                    } else {
                        // Unvalidatable branches ahead: freeze state instead of
                        // modeling transitions that cannot be cross-checked.
                        transitions_frozen = true;
                    }
                }
                // ret, nop, and all undecodable instructions: assumed neutral.
            }
        }

        if (freeze_now) {
            next = st;  // state beyond this point is not modeled
        }
        if (transitions_frozen && next != st) {
            if (i + 1 < truncate_at) truncate_at = i + 1;
            next = st;
        }
        if (next != st) {
            st = next;
            emit(st, i + 1);
        }
    }

    // Branch validation: every in-range branch edge must connect two
    // boundaries with the same unwind rule, otherwise the linear scan state
    // is not unique. The ambiguity starts at the edge target: boundaries
    // between the branch and its target are reached only by fall-through and
    // keep their scanned state, while the target (and everything after it,
    // since the divergent path never re-converges) degrades to fallback. This
    // keeps body phases intact for stubs that branch into the epilogue.
    for (int e = 0; e < edge_count; e++) {
        const StubUnwindPhase* f = info->findPhase(edges[e].from);
        const StubUnwindPhase* t = info->findPhase(edges[e].to);
        if (f->kind != t->kind || f->arg != t->arg || f->arg2 != t->arg2) {
            if (edges[e].to < truncate_at) truncate_at = edges[e].to;
        }
    }
    // Apply truncation: everything from truncate_at on is untrustworthy.
    if (truncate_at < count) {
        int keep = 0;
        while (keep < info->_phase_count && info->_phases[keep].insn_offset < truncate_at) {
            keep++;
        }
        if (keep < StubUnwindInfo::MAX_PHASES &&
            (keep == 0 || info->_phases[keep - 1].insn_offset < truncate_at)) {
            StubUnwindPhase& p = info->_phases[keep];
            p.insn_offset = (uint16_t)truncate_at;
            p.kind = SU_UNSUPPORTED;
            p._pad = 0;
            p.arg = p.arg2 = 0;
            keep++;
        }
        info->_phase_count = (uint8_t)keep;
    }

    info->_classified = info->_phase_count > 0 && info->_phases[0].kind != SU_UNSUPPORTED;
    return info;
}

#endif // __aarch64__
