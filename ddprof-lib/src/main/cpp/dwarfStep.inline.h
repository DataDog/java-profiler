/*
 * Copyright The async-profiler authors
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _DWARFSTEP_INLINE_H
#define _DWARFSTEP_INLINE_H

#include "codeCache.h"
#include "dwarf.h"
#include "faultInjection.h"
#include "profiler.h"
#include "safeAccess.h"
#include "stackFrame.h"
#include "stackWalker.inline.h"

// One step of the DWARF unwind, shared by StackWalker::walkDwarf and
// HotspotSupport::walkVM. The two had drifted into separate copies; 61959b06f
// and the commit that added this reconciled the last of the differences so
// that this could be a pure move rather than a merge of two behaviours.
//
// Advances sp/fp/walk_pc from the current frame to its caller. Returns false
// where the walk must stop -- an unusable CFA rule, an implausible sp or fp,
// or no forward progress -- and true when the caller may record another frame.
// On a false return sp/fp/walk_pc may already have been partly updated; both
// callers stop the walk, so no caller observes that.
//
// always_inline is load-bearing, not an optimisation. AddressSanitizer
// instruments per function *after* inlining, so an inlined body takes its
// caller's sanitizer attribute: walkVM is no_sanitize("address") because it
// reads arbitrary stack memory while sampling, walkDwarf is deliberately
// instrumented, and both have been that way since before the two were split
// apart. Left out of line, this body would carry one attribute for both --
// either dropping walkDwarf's instrumentation or adding to walkVM the
// instrumentation it exists to avoid.
//
// `depth` is passed rather than tracked here because the two callers do not
// agree on it: walkVM's fp-chain fallback reaches this step via
// `goto dwarf_unwind`, which skips its fillFrame(frames[depth++], ...), so on
// that path walkVM arrives one lower than walkDwarf does at the same logical
// position. Passing it through is what keeps this a pure move; do not
// "correct" it to a value derived here.
__attribute__((always_inline))
inline bool advanceDwarfFrame(WalkPc& walk_pc, uintptr_t& sp, uintptr_t& fp,
                              uintptr_t bottom, int depth,
                              const StackFrame& frame, Profiler* profiler) {
    using StackWalkValidation::inDeadZone;
    using StackWalkValidation::aligned;
    using StackWalkValidation::MAX_FRAME_SIZE;

    // Past the leaf, `pc` is usually a return address, so row and symbol
    // selection go through the attribution address: a call that is the last
    // instruction of its caller would otherwise select the following
    // function's CFA row, derive a sender sp from it, and miss a
    // MARK_THREAD_ENTRY sitting on the caller. The raw pc is still what the
    // DW_PC_OFFSET arithmetic and the no-progress guard below operate on.
    const void* attribution_pc = walk_pc.attribution();
    uintptr_t prev_sp = sp;
    CodeCache* cc = profiler->findLibraryByAddress(attribution_pc);
    FrameDesc f = cc != NULL ? cc->findFrameDesc(attribution_pc) : FrameDesc::fallback_default_frame();

    u8 cfa_reg = (u8)f.cfa;
    int cfa_off = f.cfa >> 8;
    if (cfa_reg == DW_REG_SP) {
        sp = sp + cfa_off;
    } else if (cfa_reg == DW_REG_FP) {
        // Sanity-check FP before deriving CFA from it. A corrupted FP can
        // produce a phantom CFA and cause the walk to record spurious
        // frames before breaking. We cannot check fp < sp here because on
        // aarch64 the frame pointer is set to SP at function entry, which
        // is typically less than the previous CFA.
        if (fp >= bottom || !aligned(fp)) {
            return false;
        }
        sp = fp + cfa_off;
    } else if (cfa_reg == DW_REG_PLT) {
        // Which of the stub's two CFA rules applies depends on the position
        // within the 16-byte PLT stub, so it must be evaluated at the same
        // address the row above was selected at (attribution_pc). Mixing the
        // two would pair the row chosen for one stub offset with the CFA
        // doubling decided for another.
        sp += ((uintptr_t)attribution_pc & 15) >= 11 ? cfa_off * 2 : cfa_off;
    } else {
        return false;
    }

    // Check if the next frame is below on the current stack
    if (sp < prev_sp || sp >= prev_sp + MAX_FRAME_SIZE || sp >= bottom) {
        return false;
    }

    // Stack pointer must be word aligned
    if (!aligned(sp)) {
        return false;
    }

    const void* prev_pc = walk_pc.raw();
    if (f.fp_off & DW_PC_OFFSET) {
        // f.fp_off carries the offset of a DW_CFA_val_expression of the form
        // DW_OP_breg<PC> + K on the return-address register column
        // (DwarfParser::parseExpression). DW_OP_breg names the *register
        // value*, which is the raw walking pc, so the offset is applied to
        // that and not to the row-lookup address.
        walk_pc.setRecoveredPc((const char*)walk_pc.raw() + (f.fp_off >> 1),
                               f.isSignalFrame());
    } else {
        if (f.fp_off != DW_SAME_FP && f.fp_off < MAX_FRAME_SIZE && f.fp_off > -MAX_FRAME_SIZE) {
            uintptr_t fp_addr = sp + f.fp_off;
            if (!aligned(fp_addr)) {
                return false;
            }
            fp = (uintptr_t)SafeAccess::load(INJECT_FAULT_ADDRESS_LIKELY((void**)fp_addr));
        }

        if (EMPTY_FRAME_SIZE > 0 || f.pc_off != DW_LINK_REGISTER) {
            uintptr_t pc_addr = sp + f.pc_off;
            if (!aligned(pc_addr)) {
                return false;
            }
            walk_pc.setRecoveredPc(
                stripPointer(SafeAccess::load(INJECT_FAULT_ADDRESS_LIKELY((void**)pc_addr))),
                f.isSignalFrame());
        } else if (depth == 1) {
            // Matches the memory-slot path above: StackFrame::link() returns
            // the raw link register, which carries PAC bits on aarch64 and
            // would otherwise be fed to findFrameDesc as a nonsense address.
            walk_pc.setRecoveredPc(stripPointer((const void*)frame.link()),
                                   f.isSignalFrame());
        } else {
            return false;
        }

        if (EMPTY_FRAME_SIZE == 0 && cfa_off == 0 && f.fp_off != DW_SAME_FP) {
            // AArch64 default_frame
            sp = defaultSenderSP(sp, fp);
            if (sp < prev_sp || sp >= bottom || !aligned(sp)) {
                return false;
            }
        }
    }

    if (inDeadZone(walk_pc.raw()) || (walk_pc.raw() == prev_pc && sp == prev_sp)) {
        return false;
    }

    return true;
}

#endif // _DWARFSTEP_INLINE_H
