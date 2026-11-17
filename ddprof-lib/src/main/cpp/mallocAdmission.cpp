/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Shared (platform-neutral) native-memory admission logic: import-slot
// reading, target-set derivation with the own-hook rules, per-target owner
// classification and verdict combination. The platform-specific part is only
// MallocAdmission::classifyOwners() (mallocAdmission_linux.cpp on Linux,
// mallocAdmission_macos.cpp elsewhere).
//
// Everything here runs in ordinary profiler-start context, never in a malloc
// hook or signal handler. No function in this file allocates, locks or logs
// from inside a loader callback; the only log line is emitted after the
// owner walk has returned.

#include "mallocAdmission.h"

#include "arch.h"
#include "common.h"

namespace {

// The five allocation operations the admission check inspects, in binding
// index order (the order of current[][]/forwarding[]/own_hooks[]).
const ImportId OPERATION_IMPORTS[5] = {im_malloc, im_calloc, im_realloc, im_posix_memalign, im_aligned_alloc};

// The reason enum is asserted by tests, so the log line names it exactly.
const char* reasonName(AdmissionReason reason) {
    switch (reason) {
        case NONE:
            return "NONE";
        case NO_OWN_LIBRARY:
            return "NO_OWN_LIBRARY";
        case OWN_HOOK_WITHOUT_SAVED:
            return "OWN_HOOK_WITHOUT_SAVED";
        case OWN_HOOK_WRONG_SLOT:
            return "OWN_HOOK_WRONG_SLOT";
        case SAVED_IS_OWN_HOOK:
            return "SAVED_IS_OWN_HOOK";
        case NO_OWNER:
            return "NO_OWNER";
        case NO_DYNAMIC:
            return "NO_DYNAMIC";
        case BAD_DYNAMIC:
            return "BAD_DYNAMIC";
        case NO_HASH_TABLE:
            return "NO_HASH_TABLE";
        case BAD_HASH_TABLE:
            return "BAD_HASH_TABLE";
        case CHAIN_LIMIT:
            return "CHAIN_LIMIT";
        case BAD_SYMBOL:
            return "BAD_SYMBOL";
        case WRONG_KIND_MARKER:
            return "WRONG_KIND_MARKER";
        case AMBIGUOUS_MARKER:
            return "AMBIGUOUS_MARKER";
        case PARTIAL_MARKERS:
            return "PARTIAL_MARKERS";
    }
    return "?";
}

const char* outcomeName(AdmissionOutcome outcome) {
    switch (outcome) {
        case NOT_RECOGNIZED:
            return "NOT_RECOGNIZED";
        case DDPROF:
            return "DDPROF";
        case INDETERMINATE:
            return "INDETERMINATE";
    }
    return "?";
}

} // namespace

void MallocAdmission::readImports(const CodeCache* own, const void* current[5][NUM_IMPORT_TYPES]) {
    for (int op = 0; op < 5; op++) {
        for (int type = 0; type < NUM_IMPORT_TYPES; type++) {
            // Read-only slot access: peekImport never makes the GOT writable
            // and never changes page protection. A missing slot stores NULL;
            // an existing slot is read atomically, since a concurrent start
            // of another engine could still patch it.
            void** slot = own->peekImport(OPERATION_IMPORTS[op], (ImportType)type);
            if (slot == NULL) {
                current[op][type] = NULL;
            } else {
                current[op][type] = __atomic_load_n((void* volatile*)slot, __ATOMIC_ACQUIRE);
            }
        }
    }
}

void MallocAdmission::missingOwnLibrary(MallocAdmissionResult& out) {
    out.verdict = {INDETERMINATE, NO_OWN_LIBRARY};
    out.target_count = 0;
    out.images_classified = 0;
}

void MallocAdmission::evaluate(const MallocAdmissionInput& in, MallocAdmissionResult& out) {
    out.target_count = 0;
    out.images_classified = 0;

    // First derivation/owner verdict with each winning outcome: the combined
    // reason is the first verdict with the winning outcome, so a derivation
    // failure is retained (not short-circuited) while the remaining targets
    // are still classified — a DDPROF elsewhere takes diagnostic precedence.
    bool has_ddprof = false;
    AdmissionVerdict first_ddprof = {NOT_RECOGNIZED, NONE};
    bool has_indeterminate = false;
    AdmissionVerdict first_indeterminate = {NOT_RECOGNIZED, NONE};

    // Derivation: every non-NULL current slot value and every non-NULL saved
    // forwarding value is a candidate target, except the values the own-hook
    // rules reject with a retained INDETERMINATE. All comparisons go through
    // stripPointer() on both sides; stored values are never modified.
    for (int op = 0; op < 5; op++) {
        for (int type = 0; type < NUM_IMPORT_TYPES; type++) {
            const void* v = in.current[op][type];
            if (v == NULL) continue;
            if (stripPointer(v) == stripPointer(in.own_hooks[op])) {
                // A slot we rewrote ourselves forwards to the saved value;
                // the forwarding value itself is handled below. Nothing saved
                // means the rewritten slot has nowhere defined to forward:
                // the target set is incomplete, fail closed.
                if (in.forwarding[op] == NULL) {
                    if (!has_indeterminate) {
                        first_indeterminate.outcome = INDETERMINATE;
                        first_indeterminate.reason = OWN_HOOK_WITHOUT_SAVED;
                        has_indeterminate = true;
                    }
                }
                continue;
            }
            bool wrong_slot = false;
            for (int j = 0; j < 5; j++) {
                if (j != op && stripPointer(v) == stripPointer(in.own_hooks[j])) {
                    wrong_slot = true;
                    break;
                }
            }
            if (wrong_slot) {
                if (!has_indeterminate) {
                    first_indeterminate.outcome = INDETERMINATE;
                    first_indeterminate.reason = OWN_HOOK_WRONG_SLOT;
                    has_indeterminate = true;
                }
                continue;
            }
            out.targets[out.target_count++] = v;
        }
    }
    for (int op = 0; op < 5; op++) {
        const void* f = in.forwarding[op];
        if (f == NULL) continue;
        bool own = false;
        for (int j = 0; j < 5; j++) {
            if (stripPointer(f) == stripPointer(in.own_hooks[j])) {
                own = true;
                break;
            }
        }
        if (own) {
            // A saved forwarding value pointing back at an own hook is not a
            // target; never followed, so no cycle is possible.
            if (!has_indeterminate) {
                first_indeterminate.outcome = INDETERMINATE;
                first_indeterminate.reason = SAVED_IS_OWN_HOOK;
                has_indeterminate = true;
            }
            continue;
        }
        out.targets[out.target_count++] = f;
    }

    // Dedup the whole candidate array in place by stripped address, keeping
    // the first occurrence of each: the same address may arrive from both
    // import slots, or from a current value and a forwarding value. The
    // candidate bound (5 slots + 5 forwarding) cannot exceed the fixed
    // capacity before this pass, and the pass only shrinks it.
    int unique = 0;
    for (int i = 0; i < out.target_count; i++) {
        uintptr_t stripped = (uintptr_t)stripPointer(out.targets[i]);
        bool dup = false;
        for (int j = 0; j < unique; j++) {
            if ((uintptr_t)stripPointer(out.targets[j]) == stripped) {
                dup = true;
                break;
            }
        }
        if (!dup) out.targets[unique++] = out.targets[i];
    }
    out.target_count = unique;

    if (out.target_count > 0) {
        out.images_classified = classifyOwners(out.targets, out.target_count, out.target_verdicts);
    } else {
        out.images_classified = 0;
    }

    for (int i = 0; i < out.target_count; i++) {
        if (out.target_verdicts[i].outcome == DDPROF) {
            if (!has_ddprof) {
                first_ddprof = out.target_verdicts[i];
                has_ddprof = true;
            }
        } else if (out.target_verdicts[i].outcome == INDETERMINATE) {
            if (!has_indeterminate) {
                first_indeterminate = out.target_verdicts[i];
                has_indeterminate = true;
            }
        }
    }

    if (has_ddprof) {
        out.verdict = first_ddprof;
    } else if (has_indeterminate) {
        out.verdict = first_indeterminate;
    } else {
        out.verdict.outcome = NOT_RECOGNIZED;
        out.verdict.reason = NONE;
    }

    // Emitted only after the walk has returned, never inside a callback.
    TEST_LOG("MallocAdmission: outcome=%s reason=%s targets=%d images=%d", outcomeName(out.verdict.outcome),
             reasonName(out.verdict.reason), out.target_count, out.images_classified);
}

const char* MallocAdmission::errorMessage(AdmissionOutcome outcome) {
    switch (outcome) {
        case DDPROF:
            return "Native-memory profiling was not started: an allocation target points to a ddprof hook. "
                   "Enable only one native-memory allocation profiler for this process.";
        case INDETERMINATE:
            return "Native-memory profiling was not started: allocation-target ownership could not be determined.";
        case NOT_RECOGNIZED:
            return NULL;
    }
    return NULL;
}
