/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_STUBUNWINDINFO_H
#define _HOTSPOT_STUBUNWINDINFO_H

#ifdef __aarch64__

#include <stdint.h>

// Precomputed unwind metadata for HotSpot runtime stubs on AArch64.
//
// The stub ranges come from JVMTI DynamicCodeGenerated, which reports the
// exact [address, address + length) of every generated code blob when it is
// created and replays the full set on attach via GenerateEvents(). Unlike
// stub-name allowlists these bounds cannot drift between JDK versions or
// vendor builds, and the events are already delivered to the profiler (see
// vmEntry.cpp).
//
// analyzeStubUnwind() decodes every instruction of a stub -- far too slow and
// allocating for a signal handler -- so it runs in the DynamicCodeGenerated
// callback, on a normal Java thread. The result is registered under
// JitCodeCache::_stubs_lock and consulted by unwindStub() with a lock-free,
// allocation-free binary search over a small fixed table.
//
// A phase describes the exact processor state at a PC boundary: a phase with
// insn_offset = k governs PC == entry + 4*k, after instructions [0, k) have
// executed and instruction k has not. The table is built by a linear scan
// tracking sp, fp and the return address location; undecodable instructions
// are assumed to preserve sp/fp/x30, and known clobber classes (writes to
// x29/x30, calls from frameless code, mid-stub br) degrade the affected range
// to SU_UNSUPPORTED instead of guessing. Branch targets are validated so no
// PC is reachable with two different states; on any inconsistency the range
// degenerates to SU_UNSUPPORTED and unwindStub() falls back to the legacy
// name-based heuristics. The failure mode is always "fall back", never
// "guess".

enum StubUnwindKind : uint8_t {
    // pc = x30 (lr); sp and fp unchanged. Covers the not-yet-prologued entry,
    // true leaf/zero-frame stubs, and frameless states after sp restore.
    SU_PC_TO_LR = 0,
    // sp += arg; pc = x30 (lr); fp unchanged. Frameless stubs carrying a
    // fixed sp delta, and post-ldp epilogue states (return address back in
    // lr, sp possibly not yet restored).
    SU_SP_DELTA_LR = 1,
    // Return address saved on the stack, fp register not (yet) pointing at a
    // frame (mid-prologue, or a stub that spills x30 without setting up fp).
    // caller sp = sp + arg; pc = [sp + arg2] (byte offsets).
    SU_FP_PROLOGUE = 2,
    // Frame-pointer steady state: fp points at the saved x29 slot.
    // caller sp = fp + arg; pc = [fp + arg2]; new fp = [fp + arg2 - 8].
    SU_FP_FRAME = 3,
    // No safe rule derived for PCs from this offset on; unwindStub() must
    // fall back to the legacy heuristics.
    SU_UNSUPPORTED = 4,
};

struct StubUnwindPhase {
    uint16_t insn_offset;  // phase applies from entry[insn_offset] on
    uint8_t kind;          // StubUnwindKind
    uint8_t _pad;
    int32_t arg;           // kind-dependent, bytes
    int32_t arg2;          // kind-dependent, bytes
};

class StubUnwindInfo {
public:
    static const int MAX_PHASES = 16;

    const void* _start;
    const void* _end;
    StubUnwindPhase _phases[MAX_PHASES];
    uint8_t _phase_count;
    bool _classified;  // false: even the entry state could not be classified

    // Returns the phase governing entry[insn_index] (clamped into range).
    // O(log _phase_count). Async-signal-safe: read-only, no allocation.
    const StubUnwindPhase* findPhase(int insn_index) const;
};

// Analyzes the machine code in [start, start + length) -- a range received
// through JVMTI DynamicCodeGenerated -- and produces a compact phase table.
// Allocates the result with malloc; the caller registers it and it is never
// freed (same lifetime as the stub name strings held by JitCodeCache).
// Must not be called from a signal handler. Returns NULL if length is not a
// whole number of instructions; a stub whose entry state cannot be classified
// yields an info with _classified == false and a single SU_UNSUPPORTED phase,
// so that the "unclassifiable" outcome is observable through the counters.
StubUnwindInfo* analyzeStubUnwind(const void* start, int length, bool model_epilogue);

#endif // __aarch64__

#endif // _HOTSPOT_STUBUNWINDINFO_H
