/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_CONTBOUNDARY_H
#define _HOTSPOT_CONTBOUNDARY_H

// Classification of a virtual-thread continuation boundary crossed by walkVM.
// Two independent facts are derived from it:
//   - completeness: whether the crossing proves no older Java callers remain
//     frozen in a heap StackChunk (only Thawed does; everything else marks
//     the sample truncated);
//   - layout (JDK 21-26, no ContinuationEntry in vmStructs): whether the
//     enterSpecial frame FP is the current fp (Thawed, Unverified) or the
//     saved caller FP at *fp (Frozen).
enum class ContBoundary : unsigned char {
    Thawed,      // verified: bottom VT frame returns to cont_entry_return_pc / enterSpecial
    Frozen,      // verified: bottom VT frame returns to cont_returnBarrier
    Unverified,  // speculative: unknown CodeHeap PC on a carrier; state unknown
};

// Only a verified fully-thawed boundary proves completeness. Any other value,
// including future enumerators, defaults to "not proven".
constexpr bool contBoundaryProvesComplete(ContBoundary kind) {
    return kind == ContBoundary::Thawed;
}

// JDK 21-26 entry_fp derivation: fp itself, unless verified frozen (then *fp).
constexpr bool contBoundaryEntryFpIsCurrentFp(ContBoundary kind) {
    return kind != ContBoundary::Frozen;
}

// Per-call-site classification used by walkVM. Call sites must pass one of
// these, never a bare enumerator.
inline constexpr ContBoundary CONT_BOUNDARY_AT_RETURN_BARRIER         = ContBoundary::Frozen;
inline constexpr ContBoundary CONT_BOUNDARY_AT_ENTRY_RETURN_PC        = ContBoundary::Thawed;
inline constexpr ContBoundary CONT_BOUNDARY_AT_ENTER_SPECIAL_NM       = ContBoundary::Thawed;
inline constexpr ContBoundary CONT_BOUNDARY_AT_SPECULATIVE_UNKNOWN_NM = ContBoundary::Unverified;

#endif // _HOTSPOT_CONTBOUNDARY_H
