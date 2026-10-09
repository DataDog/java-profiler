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
//   bits31-27 = opc(2) 101, bit26 = V,
//   bits25-23 = addressing mode (000 no-allocate STNP/LDNP, 001 post-index,
//   010 offset, 011 pre-index; no-allocate forms use offset addressing only),
//   bit22 = L (1 = load), imm7 at bits21-15,
//   Rt2 at bits14-10, Rn at bits9-5, Rt at bits4-0.
//   GPR pairs scale imm7 by 8; SIMD q pairs by 16.
// hotspotStackFrame_aarch64.cpp isSTP() masks (0xa9a003e0 / 0x6da003e0) are
// subsets of the pre-index masks below restricted to negative immediates.

struct PairInfo {
    bool load;
    int32_t imm;   // bytes, scaled and sign-extended
    bool gpr;      // false for SIMD pairs (their Rt fields are not GPR numbers)
    int base;      // Rn field: 31 = sp, 29 = fp, anything else is untracked
    int size;      // bytes per register (8 or 16); the pair covers 2 * size
};

bool decodePair(uint32_t insn, PairInfo& p) {
    static const struct { uint32_t mask, value; int scale; } forms[] = {
        // value = fixed bits 31-22; imm7/Rt2/Rn/Rt left free (Rn filtered below)
        { 0xffc00000, 0xa8800000, 8 },   // GPR post-index STP  ..., [Xn], #imm
        { 0xffc00000, 0xa8c00000, 8 },   // GPR post-index LDP
        { 0xffc00000, 0xa9000000, 8 },   // GPR offset     STP  ..., [Xn, #imm]
        { 0xffc00000, 0xa9400000, 8 },   // GPR offset     LDP
        { 0xffc00000, 0xa9800000, 8 },   // GPR pre-index  STP  ..., [Xn, #imm]!
        { 0xffc00000, 0xa9c00000, 8 },   // GPR pre-index  LDP
        { 0xffc00000, 0xa8000000, 8 },   // GPR offset     STNP ..., [Xn, #imm]
        { 0xffc00000, 0xa8400000, 8 },   // GPR offset     LDNP ..., [Xn, #imm]
        { 0xffc00000, 0x6c800000, 8 },   // SIMD d post-index STP
        { 0xffc00000, 0x6cc00000, 8 },   // SIMD d post-index LDP
        { 0xffc00000, 0x6d000000, 8 },   // SIMD d offset  STP
        { 0xffc00000, 0x6d400000, 8 },   // SIMD d offset  LDP
        { 0xffc00000, 0x6d800000, 8 },   // SIMD d pre-index STP
        { 0xffc00000, 0x6dc00000, 8 },   // SIMD d pre-index LDP
        { 0xffc00000, 0x6c000000, 8 },   // SIMD d offset  STNP
        { 0xffc00000, 0x6c400000, 8 },   // SIMD d offset  LDNP
        { 0xffc00000, 0xac800000, 16 },  // SIMD q post-index STP
        { 0xffc00000, 0xacc00000, 16 },  // SIMD q post-index LDP
        { 0xffc00000, 0xad000000, 16 },  // SIMD q offset  STP
        { 0xffc00000, 0xad400000, 16 },  // SIMD q offset  LDP
        { 0xffc00000, 0xad800000, 16 },  // SIMD q pre-index STP
        { 0xffc00000, 0xadc00000, 16 },  // SIMD q pre-index LDP
        { 0xffc00000, 0xac000000, 16 },  // SIMD q offset  STNP
        { 0xffc00000, 0xac400000, 16 },  // SIMD q offset  LDNP
    };
    for (const auto& f : forms) {
        if ((insn & f.mask) != f.value) continue;
        p.imm = sext((insn >> 15) & 0x7f, 7) * f.scale;
        p.load = (insn >> 22) & 1;
        p.gpr = ((insn >> 26) & 0x3f) == 0x2a;  // opc=10, V=0
        p.base = rn(insn);
        p.size = f.scale;
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
        s = { false, 0, static_cast<int32_t>((insn >> 10) & 0xfff) * 8, rn(insn) };
        return true;
    }
    if ((insn & 0xffc00000) == 0xf9400000) {  // LDR unsigned imm
        s = { true, 0, static_cast<int32_t>((insn >> 10) & 0xfff) * 8, rn(insn) };
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

// ADD/SUB (immediate), 64-bit: returns Rd/Rn/imm and the op. The lsl #12
// shift form is accepted (bit 22 is excluded from the mask) and applied to
// imm -- a shifted 'add/sub sp, Xn, #imm' must update the tracked sp exactly,
// not fall through to the undecodable-neutral assumption while sp actually
// moves. (Rn=Rd=sp is matched earlier by decodeAddSubSp.)
bool decodeAddSubImm(uint32_t insn, bool& is_sub, int& rdn, int& rnn, int32_t& imm) {
    uint32_t op = insn & 0xff800000;
    if (op == 0x91000000) {
        is_sub = false;
    } else if (op == 0xd1000000) {
        is_sub = true;
    } else {
        return false;
    }
    rdn = rd(insn);
    rnn = rn(insn);
    imm = (insn >> 10) & 0xfff;
    if ((insn >> 22) & 1) imm <<= 12;
    return true;
}

// An unmodeled 64-bit add/subtract register-form write to sp (shifted or
// extended: 0x8b...... / 0xcb......; the S bit in the mask excludes the
// flag-setting ADDS/SUBS forms, whose Rd=31 is a discarded XZR) makes the
// tracked sp untrustworthy -- degrade, never guess. Logical (shifted
// register) and move-wide forms are not covered: per the Arm Architecture
// Reference Manual their Rd=31 is XZR, not SP. Logical (immediate) forms do
// write SP at Rd=31 and are handled by decodeLogicalImm64().
bool isAddSubRegSp(uint32_t insn) {
    return (insn & 0xbf000000) == 0x8b000000 && rd(insn) == 31;
}

// Bitmask of the general-purpose registers (x0-x30; writes to register 31
// are ignored, sp writeback is handled by the sp-base paths) that an
// instruction may write, for the classes the decoders above do not model:
// data processing (register: shifted/extended add/sub, logical, adc, csel,
// one/two/three-source; immediate: bitfield, extract) and GPR loads of every
// addressing mode (literal, exclusive/acquire, register offset, unscaled,
// narrower sizes, atomics), including base-register writeback, also for
// SIMD&FP loads/stores. Conservative:
// prefetches and the status register of store-exclusive count as writes. An
// x29 or x30 write that no decoder recognized would otherwise leave fp_est or
// the lr rule stale ('ldur x29, [x0, #-8]', 'csel x30, ...').
uint32_t otherGprWrites(uint32_t insn) {
    auto bit = [](int r) { return r == 31 ? 0u : 1u << r; };
    if ((insn & 0x0e000000) == 0x0a000000 ||   // data processing (register)
        (insn & 0x1c000000) == 0x10000000) {   // data processing (immediate)
        return bit(rd(insn));
    }
    if ((insn & 0x0a000000) != 0x08000000) {
        return 0;  // not a load/store
    }
    bool load;
    uint32_t m = 0;
    if ((insn >> 26) & 1) {
        // SIMD&FP transfer: the data registers are not GPRs, but the GPR
        // base is written back by the pre/post-index forms ('ldr q0, [x29],
        // #16', 'ld1 {v0.2d}, [x29], #16').
        switch ((insn >> 27) & 7) {  // bits 29:27
            case 1:  // structure load/store: bit 23 = post-index
            case 5:  // pair: bit 23 = pre/post-index
                return ((insn >> 23) & 1) ? bit(rn(insn)) : 0;
            case 7:  // single register: bits 11:10 = x1 for pre/post-index
                return (((insn >> 24) & 1) == 0 && ((insn >> 21) & 1) == 0 && ((insn >> 10) & 1) != 0)
                           ? bit(rn(insn)) : 0;
            default:
                return 0;
        }
    }
    switch ((insn >> 27) & 7) {  // bits 29:27
        case 1:  // load/store exclusive, load-acquire/store-release
            load = (insn >> 22) & 1;
            if (load) return bit(rt1(insn)) | bit(rt2(insn));
            return bit((insn >> 16) & 31);  // store-exclusive status Ws
        case 3:  // load register (literal), PRFM (literal)
            return bit(rt1(insn));
        case 5:  // load/store pair, all addressing modes
            if (((insn >> 23) & 1) != 0) m |= bit(rn(insn));  // pre/post-index writeback
            if ((insn >> 22) & 1) m |= bit(rt1(insn)) | bit(rt2(insn));
            return m;
        case 7:  // load/store register: unscaled, pre/post, register offset, atomics
            if (((insn >> 24) & 1) == 0 && ((insn >> 21) & 1) == 0 && ((insn >> 10) & 1) != 0) {
                m |= bit(rn(insn));  // pre/post-index writeback (bits 11:10 = x1)
            }
            if (((insn >> 24) & 1) == 0 && ((insn >> 21) & 1) == 1 && ((insn >> 10) & 3) == 0) {
                return m | bit(rt1(insn));  // atomic memory operation / swap
            }
            load = ((insn >> 22) & 3) != 0;  // opc 00 is the only store
            if (load) m |= bit(rt1(insn));
            return m;
        default:
            return 0;
    }
}

// Load/store instruction class (any register file). Used to drop the x29
// save-slot fact on memory accesses that are not modeled as sp-relative.
inline bool isLoadStore(uint32_t insn) {
    return (insn & 0x0a000000) == 0x08000000;
}

// In-stub targets of ADR (exact) and whether any ADRP addresses a page that
// overlaps the stub. Either is how generated code materializes a code address
// it may later reach through 'br' ('adr x9, L; ...; br x9', the computed jump
// into the unrolled loops of the *_fill and large_arrays_hashcode_* stubs, or
// 'adr lr, L; br xN; L: ...'); such a target may be entered with a state the
// fall-through scan cannot know, and it is not a branch target the edge
// validation could check. Returns the ADR target index for in-range ADR, -1
// otherwise; sets adrp_into_stub for ADRP pages overlapping the stub.
int decodeAdrTarget(uint32_t insn, const instruction_t* entry, int index, int count,
                    bool& adrp_into_stub) {
    if ((insn & 0x1f000000) != 0x10000000) return -1;
    int64_t imm = sext(((insn >> 3) & 0x1ffffc) | ((insn >> 29) & 3), 21);
    uintptr_t pc = (uintptr_t)(entry + index);
    uintptr_t start = (uintptr_t)entry, end = (uintptr_t)(entry + count);
    if ((insn >> 31) == 0) {  // ADR
        uintptr_t target = pc + imm;
        if (target < start || target >= end || ((target - start) & (INSN_SIZE - 1)) != 0) return -1;
        return (int)((target - start) / INSN_SIZE);
    }
    uintptr_t page = (pc & ~(uintptr_t)0xfff) + (uintptr_t)(imm << 12);  // ADRP
    if (page < end && page + 0x1000 > start) adrp_into_stub = true;
    return -1;
}

// An ADR target reached in the fall-through state, so it needs no validation:
// the return point of an in-stub call (set_last_Java_frame's last_Java_pc in
// the runtime-call blobs is 'adr x8, L; ...; blr xN; L:', reached by the
// callee's ret with the state after the call) and the ADR's own address
// ('adr x8, .' in the throw and jfr blobs). Self targets are filtered out by
// the caller; any other target degrades.
bool isAdrSafeTarget(const instruction_t* entry, int index) {
    if (index == 0) return false;
    uint32_t prev = entry[index - 1];
    return (prev >> 26) == 0x25 || (prev & 0xfffffc1f) == 0xd63f0000;  // BL, BLR
}

// AdvSIMD LD1-4/ST1-4 (multiple or single structure, including LDnR), with
// or without post-index writeback. Assembler-verified anchors:
// 'st1 {v28.1d-v31.1d}, [sp], x8' = 0x0c882ffc, 'ld1 {v0.1d-v3.1d}, [sp], #32'
// = 0x0cdf2fe0, 'st1 {v0.2d}, [sp]' = 0x4c007fe0, 'ld1 {v0.d}[1], [sp], #8' =
// 0x4ddf87e0, 'st4 {v0.4s-v3.4s}, [sp], #64' = 0x4c9f0be0. Bits 31-23 =
// 0 Q 0011 0 S P: S (bit 24) selects single vs multiple structure, P (bit 23)
// post-index writeback (Rm at bits 20-16, Rm = 31 for the immediate form),
// L (bit 22) = load. Their bits 29:27 are 001, so the sp-base guard for the
// immediate load/store space (bits 29:27 = 111) does not see them. HotSpot's
// push_CPU_state/pop_CPU_state emit them with an sp base, e.g. in the
// I2C/C2I adapters' c2i entry barrier and patch_callers_callsite.
struct SimdStructInfo {
    bool load;
    bool post;    // post-index writeback of Rn
    int rm;       // offset register for the post-index form, 31 = immediate
    int32_t len;  // bytes transferred, -1 if not modeled (single structure)
};

bool decodeSimdStruct(uint32_t insn, SimdStructInfo& v) {
    if ((insn & 0xbe000000) != 0x0c000000) return false;
    v.load = (insn >> 22) & 1;
    v.post = (insn >> 23) & 1;
    v.rm = (insn >> 16) & 31;
    v.len = -1;
    if (((insn >> 24) & 1) == 0) {  // multiple structures: opcode -> registers
        int regs;
        switch ((insn >> 12) & 0xf) {
            case 0x0: case 0x2: regs = 4; break;  // LD4/ST4, LD1/ST1 x4
            case 0x4: case 0x6: regs = 3; break;  // LD3/ST3, LD1/ST1 x3
            case 0x8: case 0xa: regs = 2; break;  // LD2/ST2, LD1/ST1 x2
            case 0x7:           regs = 1; break;  // LD1/ST1 x1
            default:            regs = -1; break; // unallocated
        }
        if (regs > 0) v.len = regs * (((insn >> 30) & 1) ? 16 : 8);
    }
    return true;
}

// Logical (immediate), 64-bit: AND/ORR/EOR/ANDS Xd, Xn, #bitmask. Rd = 31 is
// sp for AND/ORR/EOR ('and sp, x8, #-16' aligns sp in the i2c adapter of a
// method with stack arguments) and xzr for ANDS (TST). Decodes the bitmask
// (DecodeBitMasks() pseudocode in the Arm Architecture Reference Manual) so
// that 'mov x8, #-32' (= orr x8, xzr, #-32, 0xb27bebe8) yields its constant.
// Returns false for other encodings and for the reserved immediate patterns.
bool decodeLogicalImm64(uint32_t insn, int& opc, int& rdn, int& rnn, uint64_t& imm) {
    if ((insn & 0x9f800000) != 0x92000000) return false;  // sf=1, bits 28:23 = 100100
    opc = (insn >> 29) & 3;
    rdn = rd(insn);
    rnn = rn(insn);
    uint32_t n = (insn >> 22) & 1, immr = (insn >> 16) & 0x3f, imms = (insn >> 10) & 0x3f;
    uint32_t combined = (n << 6) | (~imms & 0x3f);
    // HighestSetBit(N:NOT(imms)); 'combined | 1' keeps clz defined for 0.
    int len = 31 - __builtin_clz(combined | 1);
    if (len < 1) return false;  // N = 0 with imms = 0b11111x: unallocated
    uint32_t levels = (1u << len) - 1;
    uint32_t sbits = imms & levels, r = immr & levels;
    if (sbits == levels) return false;  // reserved
    int esize = 1 << len;
    uint64_t emask = esize == 64 ? ~0ull : ((1ull << esize) - 1);
    uint64_t welem = (sbits + 1 == 64) ? ~0ull : ((1ull << (sbits + 1)) - 1);
    uint64_t elem = r == 0 ? welem : (((welem >> r) | (welem << (esize - r))) & emask);
    imm = 0;
    for (int b = 0; b < 64; b += esize) imm |= elem << b;
    return true;
}

// Does a store of len bytes whose lowest address sits at position a (bytes
// below the entry sp) overlap the 8-byte slot at position s? Positions grow
// downwards, so the store covers (a - len, a] and the slot (s - 8, s].
inline bool overlapsSlot(int32_t a, int32_t len, int32_t s) {
    return a > s - 8 && a < s + len;
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
// or -1.
int decodeBranch(uint32_t insn, int index, int count) {
    int64_t off;
    if ((insn >> 26) == 0x05) {  // B
        off = sext(insn & 0x03ffffff, 26);
    } else if ((insn & 0xff000010) == 0x54000000) {  // B.cond
        off = sext((insn >> 5) & 0x7ffff, 19);
    } else if ((insn & 0x7e000000) == 0x34000000) {  // CBZ/CBNZ (bits 30:25;
        // bit 24 is the Z/NZ polarity and must stay free)
        off = sext((insn >> 5) & 0x7ffff, 19);
    } else if ((insn & 0x7e000000) == 0x36000000) {  // TBZ/TBNZ
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

// fp_est is only set when x29 lands on a frame record (saved x29 with the
// saved x30 8 bytes above it), so the return address of an fp frame is
// always at fp + 8. A later spill of x30 elsewhere ('str x30, [sp, #-16]!'
// inside the frame) moves x30_abs but not the frame record; once that spill
// is popped it lies below the live sp and must not be used.
const int32_t FRAME_RECORD_PC_OFFSET = 8;

struct ScanState {
    int32_t sp = 0;       // sp position in bytes below the entry sp
    bool sp_known = true;
    bool fp_est = false;  // x29 points at the saved-x29 slot of the current frame
    int32_t fp_abs = 0;   // position of that slot below the entry sp
    RetLoc ret = RET_LR;
    int32_t x30_abs = 0;  // position of the saved x30 slot below the entry sp
    // Facts that only refine the tracking of sp and fp and are not part of the
    // unwind rule. Branch validation compares unwind rules, so these are
    // dropped at every in-stub branch target and only ever derive from
    // straight-line code.
    int const_reg = -1;     // GPR holding const_val ('mov x8, #-32' before
    int64_t const_val = 0;  // push_CPU_state's 'st1 {...}, [sp], x8')
    bool fp_saved = false;  // the frame's x29 value is stored in the sp slot
    int32_t fp_slot_abs = 0;  // at this position below the entry sp

    bool operator==(const ScanState& o) const {
        return sp == o.sp && sp_known == o.sp_known && fp_est == o.fp_est &&
               fp_abs == o.fp_abs && ret == o.ret && x30_abs == o.x30_abs &&
               const_reg == o.const_reg && const_val == o.const_val &&
               fp_saved == o.fp_saved && fp_slot_abs == o.fp_slot_abs;
    }
    bool operator!=(const ScanState& o) const { return !(*this == o); }
    // Equality of the fields the unwind rule derives from (excludes the
    // auxiliary facts above).
    bool sameUnwindState(const ScanState& o) const {
        return sp == o.sp && sp_known == o.sp_known && fp_est == o.fp_est &&
               fp_abs == o.fp_abs && ret == o.ret && x30_abs == o.x30_abs;
    }

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
                p.arg2 = FRAME_RECORD_PC_OFFSET;
            } else {
                p.kind = SU_UNSUPPORTED;
                p.arg = p.arg2 = 0;
            }
            return;
        }
        if (fp_est && fp_abs > sp) {
            // The frame record lies below the live sp: the stub no longer
            // owns that memory and nothing guarantees it is preserved, so a
            // signal may have overwritten it. Degrade instead of pointing the
            // handler at it. (Reachable for pops that stay at/below the entry
            // sp; a pop beyond it clears sp_known and takes the branch above.)
            p.kind = SU_UNSUPPORTED;
            p.arg = p.arg2 = 0;
        } else if (fp_est) {
            p.kind = SU_FP_FRAME;
            p.arg = fp_abs;             // caller sp = fp + arg
            p.arg2 = FRAME_RECORD_PC_OFFSET;  // pc slot = [fp + arg2]
        } else if (ret == RET_STACK && x30_abs > sp) {
            // Same ownership rule for the saved return-address slot: below
            // the live sp it is unowned memory.
            p.kind = SU_UNSUPPORTED;
            p.arg = p.arg2 = 0;
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

StubUnwindInfo* analyzeStubUnwind(const void* start, int length, bool multi_entry) {
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
        // Reserve the last slot for the SU_UNSUPPORTED terminator the
        // truncation step writes at the cut. If the table filled up
        // completely, truncation could not append the terminator and PCs
        // past the cut would resolve to the last real phase -- a stale rule
        // silently applied instead of degrading to fallback.
        if (n >= StubUnwindInfo::MAX_PHASES - 1) {
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

    // In-stub branch targets, where the auxiliary ScanState facts are
    // dropped, and in-stub ADR targets (see decodeAdrTarget()).
    uint64_t targets[MAX_STUB_BYTES / INSN_SIZE / 64] = {};
    uint64_t adr_targets[MAX_STUB_BYTES / INSN_SIZE / 64] = {};
    bool adrp_into_stub = false;
    for (int i = 0; i < count; i++) {
        int target = decodeBranch(entry[i], i, count);
        if (target >= 0) targets[target >> 6] |= 1ull << (target & 63);
        int adr = decodeAdrTarget(entry[i], entry, i, count, adrp_into_stub);
        if (adr >= 0 && adr != i) adr_targets[adr >> 6] |= 1ull << (adr & 63);
    }

    for (int i = 0; i < count; i++) {
        uint32_t insn = entry[i];
        if (targets[i >> 6] & (1ull << (i & 63))) {
            st.const_reg = -1;
            st.fp_saved = false;
        }
        if ((adr_targets[i >> 6] & (1ull << (i & 63))) && !isAdrSafeTarget(entry, i) &&
            i < truncate_at) {
            truncate_at = i;
        }
        ScanState next = st;
        // Instructions known not to write const_reg; any other instruction
        // drops the tracked constant.
        bool keeps_const = false;
        int def_reg = -1;
        int64_t def_val = 0;
        // Set by the paths that model an sp-relative memory access exactly;
        // any other load/store may alias the x29 save slot.
        bool sp_access = false;
        // GPR writes found by otherGprWrites() or base writeback: an x29
        // write moves fp off the frame, an x30 write clobbers the lr rule.
        auto clobber = [&](uint32_t mask) {
            if (mask & (1u << 29)) next.fp_est = false;
            if ((mask & (1u << 30)) && next.ret == RET_LR) next.ret = RET_UNKNOWN;
        };

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
                if ((insn >> 23) & 1) {
                    clobber(1u << pair.base);  // pre/post-index writeback of the base
                }
            } else {
                sp_access = true;
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
                if (!pair.load) {
                    keeps_const = true;
                    if (!st.sp_known || overlapsSlot(addr_abs, 2 * pair.size, next.fp_slot_abs)) {
                        next.fp_saved = false;
                    }
                }
                if (pair.gpr) {
                    int a = rt1(insn), b = rt2(insn);
                    if (pair.load) {
                        if (a == 30 || b == 30) {
                            if (next.ret != RET_CONT) {
                                // The restored lr holds the return address:
                                // switch to it. The abandoned stack slot lies
                                // below the restored sp and AArch64 has no red
                                // zone, so signal delivery and the handler may
                                // have overwritten it -- the lr captured in the
                                // sampled ucontext is authoritative.
                                next.ret = RET_LR;
                            }
                        }
                        if (a == 29 || b == 29) {
                            // x29 reloaded: still our frame fp only if it
                            // comes back from the slot it was saved to
                            int32_t slot = (a == 29) ? addr_abs : addr_abs - 8;
                            if (!(st.sp_known && next.fp_saved && slot == next.fp_slot_abs)) {
                                next.fp_est = false;
                            }
                        }
                    } else {
                        if (a == 30 || b == 30) {
                            next.ret = RET_STACK;
                            next.x30_abs = (a == 30) ? addr_abs : addr_abs - 8;
                        }
                        if ((a == 29 || b == 29) && next.fp_est && st.sp_known) {
                            // push_CPU_state saves x29 with the other GPRs
                            next.fp_saved = true;
                            next.fp_slot_abs = (a == 29) ? addr_abs : addr_abs - 8;
                        }
                    }
                }
            }
        } else if (decodeSingle(insn, single)) {
            if (single.base != 31) {
                // Untracked base (e.g. a copy loop's 'ldr x4, [x2], #8'):
                // only the register effects apply, as for pairs.
                untrackedBase(rd(insn), -1, single.load, next);
                if (single.mode != 0) {
                    clobber(1u << single.base);  // pre/post-index writeback of the base
                }
            } else {
                sp_access = true;
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
                if (!single.load) {
                    keeps_const = true;
                    if (!st.sp_known || overlapsSlot(addr_abs, 8, next.fp_slot_abs)) {
                        next.fp_saved = false;
                    }
                    if (t == 29 && next.fp_est && st.sp_known) {
                        next.fp_saved = true;
                        next.fp_slot_abs = addr_abs;
                    }
                }
                if (t == 30) {
                    if (single.load) {
                        if (next.ret != RET_CONT) {
                            // RET_CONT is sticky: the loaded value may be a
                            // call continuation. Otherwise the restored lr
                            // holds the return address (same reasoning as the
                            // pair path above); rn is always sp here.
                            next.ret = RET_LR;
                        }
                    } else if (rn(insn) == 31) {
                        next.ret = RET_STACK;
                        next.x30_abs = addr_abs;
                    } else if (next.ret == RET_LR) {
                        next.ret = RET_UNKNOWN;  // saved somewhere we cannot name
                    }
                } else if (t == 29 && single.load &&
                           !(st.sp_known && next.fp_saved && addr_abs == next.fp_slot_abs)) {
                    next.fp_est = false;
                }
            }
        } else {
            bool is_sub;
            int32_t imm;
            int rdn, rnn, aimm;
            int opc;
            uint64_t limm;
            SimdStructInfo simd;
            if (decodeAddSubSp(insn, is_sub, imm)) {
                keeps_const = true;
                next.sp += is_sub ? imm : -imm;
                if (next.sp < 0) next.sp_known = false;
            } else if (decodeAddSubImm(insn, is_sub, rdn, rnn, aimm)) {
                if (rdn == 31) {
                    // add/sub sp, Xn, #imm ("mov sp, x29"). (Rn=Rd=sp is
                    // matched earlier; the rnn == 31 sub-branch below is
                    // unreachable in practice and kept defensively.)
                    if (rnn == 31) {
                        next.sp += is_sub ? aimm : -aimm;
                    } else if (rnn == 29 && next.fp_est) {
                        // fp_est holds only while no decoded instruction
                        // has written x29 (otherGprWrites() covers the
                        // classes without a dedicated decoder), so x29 is
                        // the exact frame address and sp is known again even
                        // after an unmodeled sp update inside the frame.
                        next.sp = is_sub ? next.fp_abs + aimm : next.fp_abs - aimm;
                        next.sp_known = true;
                    } else {
                        next.sp_known = false;
                    }
                    if (next.sp < 0) next.sp_known = false;
                } else if (rdn == 29) {
                    // mov x29, sp / add/sub x29, sp, #imm, or x29 from elsewhere
                    int32_t cand = is_sub ? next.sp + aimm : next.sp - aimm;
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
                if (rnn == 31 && rdn != 31 && rdn != 29) {
                    // An sp-derived pointer in a GPR ('mov x1, sp') lets later
                    // stores or a callee write the x29 save slot unseen.
                    next.fp_saved = false;
                }
            } else if (isOrrReg(insn)) {
                int d = rd(insn);
                if (d == 29) {
                    next.fp_est = false;
                } else if (d == 30 && next.ret == RET_LR) {
                    next.ret = RET_UNKNOWN;
                }
            } else if (decodeLogicalImm64(insn, opc, rdn, rnn, limm)) {
                if (rdn == 31) {
                    if (opc != 3) next.sp_known = false;  // AND/ORR/EOR write sp; ANDS writes xzr
                } else if (rdn == 29) {
                    next.fp_est = false;
                } else if (rdn == 30 && next.ret == RET_LR) {
                    next.ret = RET_UNKNOWN;
                }
                if (opc == 1 && rnn == 31 && rdn != 31) {  // mov Xd, #bitmask
                    def_reg = rdn;
                    def_val = (int64_t)limm;
                }
            } else if (isAdrLike(insn) || isMoveWide(insn)) {
                int d = rd(insn);
                if (d == 29) {
                    next.fp_est = false;
                } else if (d == 30 && next.ret == RET_LR) {
                    next.ret = RET_UNKNOWN;
                }
                int mov_opc = (insn >> 29) & 3;
                if (isMoveWide(insn) && (insn >> 31) && (mov_opc == 0 || mov_opc == 2) && d != 31) {
                    // 64-bit MOVN (opc 00) / MOVZ (opc 10); MOVK (11) keeps
                    // the other bits and is not a constant definition
                    int64_t v = (int64_t)((uint64_t)((insn >> 5) & 0xffff) << (16 * ((insn >> 21) & 3)));
                    def_reg = d;
                    def_val = mov_opc == 0 ? ~v : v;
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
                // Control leaves through a register jump, so the next
                // instruction is not reached by fall-through. In a
                // multi_entry blob it is a further entry point, entered like
                // the blob start with the return address in lr and the
                // caller's sp (the I2C/C2I adapters blob holds the i2c entry,
                // whose shuffle ends in 'br', followed by the c2i entries),
                // or a target of an in-stub branch: restart from the entry
                // state, and the branch validation below degrades the target
                // if a branch reaches it in a different state. Elsewhere, and
                // when an ADRP materializes a code address in the stub that
                // cannot be checked against the restart points, the state
                // after the br is unknown: cut there.
                if (multi_entry && !adrp_into_stub) {
                    next = ScanState();
                } else {
                    if (i + 1 < count && i + 1 < truncate_at) truncate_at = i + 1;
                    next = st;
                }
            } else if (isUnprivLoadStore(insn)) {
                // LDTR/STTR: no base writeback, so sp is unchanged; a load
                // into x30 clobbers the return-address register.
                if ((insn >> 22) & 1) {
                    clobber(1u << rd(insn));
                }
            } else if ((insn & 0x38000000) == 0x38000000 && rn(insn) == 31) {
                // An undecoded load/store with an sp base: the immediate
                // load/store encoding space (bits 29:27 = 111) covers SIMD
                // single-register pre/post-index forms ('str q0, [sp, #-16]!'),
                // unscaled LDUR/STUR, and narrower GPR sizes -- any of them can
                // write back sp or move x30 between lr and memory. The scanned
                // state can no longer be trusted: truncate everything from the
                // next boundary on (SU_UNSUPPORTED -> legacy heuristics), the
                // same degradation as a mid-stub br. Branches, system
                // instructions, pairs, exclusive forms, and literal loads all
                // have bits 29:27 != 111; LDTR/STTR were handled above.
                if (i + 1 < truncate_at) truncate_at = i + 1;
                transitions_frozen = true;
            } else if (decodeSimdStruct(insn, simd) && rn(insn) == 31) {
                // Writes only SIMD registers (and sp on writeback).
                keeps_const = true;
                sp_access = true;
                if (!simd.load && (simd.len < 0 || !st.sp_known ||
                                   overlapsSlot(next.sp, simd.len, next.fp_slot_abs))) {
                    next.fp_saved = false;
                }
                if (simd.post) {
                    // sp += transfer size (immediate form) or += Xm. An
                    // unmodeled step makes sp unknown; an established fp
                    // frame keeps the fp rule exact and 'mov sp, x29' makes
                    // sp known again.
                    if (simd.rm == 31 && simd.len > 0) {
                        next.sp -= simd.len;
                    } else if (simd.rm != 31 && simd.rm == st.const_reg &&
                               st.const_val > -MAX_STUB_BYTES && st.const_val < MAX_STUB_BYTES) {
                        next.sp -= (int32_t)st.const_val;
                    } else {
                        next.sp_known = false;
                    }
                    if (next.sp < 0) next.sp_known = false;
                }
            } else if (isAddSubRegSp(insn)) {
                // Unmodeled register-form sp write (e.g. 'add sp, sp, x0'):
                // the tracked sp can no longer be trusted.
                next.sp_known = false;
            } else {
                int target = decodeBranch(insn, i, count);
                if (target >= 0) {
                    if (edge_count < MAX_BRANCHES) {
                        edges[edge_count++] = { i, target };
                    } else {
                        // Unvalidatable branches ahead: freeze state instead of
                        // modeling transitions that cannot be cross-checked.
                        transitions_frozen = true;
                    }
                }
                // Classes without a dedicated decoder that can still write
                // x29/x30 ('ldur x29, [x0, #-8]', 'csel x30, ...').
                clobber(otherGprWrites(insn));
                // ret, nop, and all remaining undecodable instructions:
                // assumed neutral.
            }
        }

        if (!keeps_const) next.const_reg = -1;
        if (def_reg >= 0) {
            next.const_reg = def_reg;
            next.const_val = def_val;
        }
        if (!next.fp_est || next.fp_abs != st.fp_abs) next.fp_saved = false;
        if (isLoadStore(insn) && !sp_access) next.fp_saved = false;
        // A popped save slot lies below the live sp: unowned memory a signal
        // may overwrite (the same rule as FRAME_RECORD_PC_OFFSET for x30).
        if (next.fp_saved && (!next.sp_known || next.fp_slot_abs > next.sp)) next.fp_saved = false;

        // Frozen transitions forbid a new unwind rule; the auxiliary facts
        // may still change without truncating.
        if (transitions_frozen && !next.sameUnwindState(st)) {
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
        // keep < MAX_PHASES always holds here: emit() reserves the last
        // slot, so at most MAX_PHASES - 1 real phases are stored and the
        // terminator always fits. The loop has also already verified that
        // every counted phase starts below the cut.
        if (keep < StubUnwindInfo::MAX_PHASES) {
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
