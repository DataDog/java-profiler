/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _MALLOC_ADMISSION_H
#define _MALLOC_ADMISSION_H

#include "codeCache.h"

/**
 * Startup admission check for native-memory allocation profiling.
 *
 * Before the profiler rewrites any GOT slot it derives the set of allocation
 * targets the process currently uses (current GOT entries plus previously
 * saved forwarding pointers), classifies the loaded image that owns each
 * target, and rejects the start when a target belongs to a recognized ddprof
 * image. Classification is conservative: an indeterminate owner inspection
 * also rejects, never admits.
 *
 * The whole check is startup-only: it runs inside
 * MallocHooker::initialize() before any probe, marker or seed is written and
 * never touches the allocation hot path. All admission state lives on the
 * stack in fixed-size arrays (MALLOC_ADMISSION_MAX_TARGETS entries); no
 * admission function allocates, locks or logs from inside a loader callback.
 */

// Whether an inspected allocation target set admits the start.
enum AdmissionOutcome {
    NOT_RECOGNIZED, // no target belongs to a known ddprof image: admit
    DDPROF,         // a target belongs to a recognized ddprof image: reject
    INDETERMINATE   // ownership could not be determined: reject conservatively
};

// Why the outcome was reached. The exact value is asserted by tests, so
// adding a member means naming the scenario that produces it.
enum AdmissionReason {
    NONE, // NOT_RECOGNIZED
    NO_OWN_LIBRARY, // own CodeCache not found: nothing to inspect
    OWN_HOOK_WITHOUT_SAVED, // a current slot holds an own hook but the saved forwarding value is absent
    OWN_HOOK_WRONG_SLOT, // a current slot holds an own hook of a different operation
    SAVED_IS_OWN_HOOK, // a saved forwarding value is itself an own hook
    NO_OWNER, // no loaded object contains the target (anonymous memory or unloaded before the walk)
    NO_DYNAMIC, // owner image has no PT_DYNAMIC segment
    BAD_DYNAMIC, // owner image's dynamic section is unreadable or incomplete
    NO_HASH_TABLE, // owner image has neither DT_GNU_HASH nor DT_HASH
    BAD_HASH_TABLE, // owner image's hash table is malformed or unreadable
    CHAIN_LIMIT, // hash-chain walk exceeded MAX_HASH_CHAIN_STEPS or the SysV nchain cycle bound
    BAD_SYMBOL, // a matched symbol or its name is unreadable or out of range
    WRONG_KIND_MARKER, // a symbol named like a marker has the wrong ELF symbol type
    AMBIGUOUS_MARKER, // the same marker name is defined more than once in one image
    PARTIAL_MARKERS // only one of the two marker names is defined in one image
};

struct AdmissionVerdict {
    AdmissionOutcome outcome;
    AdmissionReason reason;
};

// Fixed capacity of the deduplicated target set: every operation contributes
// at most one value per import slot (NUM_IMPORT_TYPES) plus one saved
// forwarding value, so the bound is arithmetic, not a tuning constant; the
// set cannot overflow by construction.
constexpr int MALLOC_ADMISSION_MAX_TARGETS = 5 * (NUM_IMPORT_TYPES + 1);

struct MallocAdmissionInput {
    // Current GOT-slot values per operation (binding index order:
    // 0 malloc, 1 calloc, 2 realloc, 3 posix_memalign, 4 aligned_alloc) and
    // import slot; NULL for a missing slot or a NULL value.
    const void* current[5][NUM_IMPORT_TYPES];
    // Previously saved forwarding values (what a rewritten slot forwards to);
    // NULL when nothing was saved for that operation.
    const void* forwarding[5];
    // The profiler's own hook addresses, the same expressions
    // MallocHooker::patchLibraries() writes.
    const void* own_hooks[5];
};

struct MallocAdmissionResult {
    // Combined verdict: DDPROF > INDETERMINATE > NOT_RECOGNIZED; the reason is
    // the first verdict with the winning outcome.
    AdmissionVerdict verdict;
    // Number of deduplicated targets (<= MALLOC_ADMISSION_MAX_TARGETS).
    int target_count;
    // Deduplicated targets, compared by stripped address.
    const void* targets[MALLOC_ADMISSION_MAX_TARGETS];
    // One verdict per target, parallel to targets[].
    AdmissionVerdict target_verdicts[MALLOC_ADMISSION_MAX_TARGETS];
    // Number of loaded images classified during the owner walk.
    int images_classified;
};

// Static-only: the admission check has no per-instance state; every call
// works on caller-provided arrays.
class MallocAdmission {
  public:
    // Fills current[][] from the own library's import slots: _imports[id][type]
    // for each of the five allocation operations, read-only (no GOT write, no
    // page-protection change). A missing slot or NULL value stores NULL.
    static void readImports(const CodeCache* own, const void* current[5][NUM_IMPORT_TYPES]);

    // Sets INDETERMINATE/NO_OWN_LIBRARY and clears the target and image counts.
    static void missingOwnLibrary(MallocAdmissionResult& out);

    // Derives the deduplicated target set from current/forwarding/own_hooks,
    // applies the own-hook rules, classifies each target's owner image and
    // combines the verdicts. Never modifies a stored value.
    static void evaluate(const MallocAdmissionInput& in, MallocAdmissionResult& out);

    // Per-OS owner classification: one verdict per target, returns the number
    // of images classified. Defined in mallocAdmission_linux.cpp (Linux) and
    // mallocAdmission_macos.cpp (non-Linux).
    static int classifyOwners(const void* const* targets, int count, AdmissionVerdict* verdicts);

    // The static rejection literal for DDPROF or INDETERMINATE; NULL for
    // NOT_RECOGNIZED (nothing to report).
    static const char* errorMessage(AdmissionOutcome outcome);
};

#endif // _MALLOC_ADMISSION_H
