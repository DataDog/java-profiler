/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Platform-neutral admission gtests: import reading, target-set derivation,
// own-hook rules, deduplication and verdict combination. No platform guard —
// this file runs on macOS and Linux; the Linux-only owner-walk cases live in
// mallocAdmissionSlots_ut.cpp. Every case runs the production code paths; the
// own-hook addresses are the same function addresses MallocHooker::
// patchLibraries() writes into foreign GOTs.
//
// Every target that survives derivation must live inside a real loaded image
// (here: this test binary or the profiler library), because on Linux the
// owner walk really runs and an address inside no loaded object is
// INDETERMINATE (NO_OWNER), not NOT_RECOGNIZED.

#include <gtest/gtest.h>

#include "codeCache.h"
#include "mallocAdmission.h"
#include "mallocTracer.h"

// The hook functions MallocTracer.cpp defines and patchLibraries() writes.
// Declared here (not via a production header) because the admission input
// only needs their addresses, exactly as the patcher uses them.
extern "C" void* malloc_hook(size_t);
extern "C" void* calloc_hook(size_t, size_t);
extern "C" void* realloc_hook(void*, size_t);
extern "C" int posix_memalign_hook(void**, size_t, size_t);
extern "C" void* aligned_alloc_hook(size_t, size_t);

namespace {

// Distinct real addresses inside this test binary: the owner walk contains
// them in the test image on Linux and classifies it as marker-free.
static void foreignTarget1() {}
static void foreignTarget2() {}
static void foreignTarget3() {}

// The five own-hook addresses in binding index order.
const void* const* ownHooks() {
    static const void* hooks[5] = {(const void*)malloc_hook, (const void*)calloc_hook, (const void*)realloc_hook,
                                   (const void*)posix_memalign_hook, (const void*)aligned_alloc_hook};
    return hooks;
}

MallocAdmissionInput emptyInput() {
    MallocAdmissionInput in;
    const void* const* hooks = ownHooks();
    for (int op = 0; op < 5; op++) {
        for (int type = 0; type < NUM_IMPORT_TYPES; type++) in.current[op][type] = NULL;
        in.forwarding[op] = NULL;
        in.own_hooks[op] = hooks[op];
    }
    return in;
}

struct AdmissionsTest : public ::testing::Test {
    // Test-owned GOT cells; addImport() stores the cell addresses in the
    // cache, so the cells must outlive the CodeCache. Indexed [op][slot].
    void* _cells[5][NUM_IMPORT_TYPES];

    void resetCells() {
        for (int op = 0; op < 5; op++) {
            for (int type = 0; type < NUM_IMPORT_TYPES; type++) _cells[op][type] = NULL;
        }
    }

    // The address range is arbitrary: the admission check never uses the
    // cache's code range, only its import slots.
    CodeCache makeCache(const char* const* names, int count) {
        resetCells();
        CodeCache lib("/test/libadmissions.so", -1, (const void*)0x1000, (const void*)0x2000, nullptr,
                      /* imports_patchable */ true);
        for (int i = 0; i < count; i++) {
            lib.addImport(&_cells[i][PRIMARY], names[i]);
        }
        return lib;
    }
};

TEST_F(AdmissionsTest, ReadImportsMirrorsCellsAndAbsentSlotsAreNull) {
    static const char* names[5] = {"malloc", "calloc", "realloc", "posix_memalign", "aligned_alloc"};
    CodeCache lib = makeCache(names, 5);
    const void* foreign = (const void*)&foreignTarget1;
    _cells[0][PRIMARY] = (void*)foreign;

    const void* current[5][NUM_IMPORT_TYPES];
    MallocAdmission::readImports(&lib, current);
    EXPECT_EQ(current[0][PRIMARY], foreign);
    // No secondary cell was ever saved for malloc, and aligned_alloc has no
    // import at all: both read as NULL without writing anything.
    EXPECT_EQ(current[0][SECONDARY], nullptr);
    EXPECT_EQ(current[4][PRIMARY], nullptr);
}

TEST_F(AdmissionsTest, ForeignTargetsAdmitWithPerTargetVerdicts) {
    static const char* names[5] = {"malloc", "calloc", "realloc", "posix_memalign", "aligned_alloc"};
    CodeCache lib = makeCache(names, 2);
    _cells[0][PRIMARY] = (void*)&foreignTarget1;
    _cells[1][PRIMARY] = (void*)&foreignTarget2;

    MallocAdmissionInput in = emptyInput();
    MallocAdmission::readImports(&lib, in.current);

    MallocAdmissionResult out;
    MallocAdmission::evaluate(in, out);
    EXPECT_EQ(out.verdict.outcome, NOT_RECOGNIZED);
    EXPECT_EQ(out.verdict.reason, NONE);
    EXPECT_EQ(out.target_count, 2);
    EXPECT_EQ(out.target_verdicts[0].outcome, NOT_RECOGNIZED);
    EXPECT_EQ(out.target_verdicts[1].outcome, NOT_RECOGNIZED);
}

TEST_F(AdmissionsTest, OwnHookWithoutSavedIsIndeterminate) {
    static const char* names[5] = {"malloc", "calloc", "realloc", "posix_memalign", "aligned_alloc"};
    CodeCache lib = makeCache(names, 5);
    // A rewritten slot holding our own malloc hook with no saved forwarding
    // value: the target set is incomplete, fail closed.
    _cells[0][PRIMARY] = (void*)malloc_hook;

    MallocAdmissionInput in = emptyInput();
    MallocAdmission::readImports(&lib, in.current);

    MallocAdmissionResult out;
    MallocAdmission::evaluate(in, out);
    EXPECT_EQ(out.verdict.outcome, INDETERMINATE);
    EXPECT_EQ(out.verdict.reason, OWN_HOOK_WITHOUT_SAVED);
    EXPECT_EQ(out.target_count, 0);
}

TEST_F(AdmissionsTest, OwnHookInAnotherOperationsSlotIsIndeterminate) {
    static const char* names[5] = {"malloc", "calloc", "realloc", "posix_memalign", "aligned_alloc"};
    CodeCache lib = makeCache(names, 5);
    // The malloc slot holds the calloc hook: our hook in the wrong operation.
    _cells[0][PRIMARY] = (void*)calloc_hook;

    MallocAdmissionInput in = emptyInput();
    MallocAdmission::readImports(&lib, in.current);

    MallocAdmissionResult out;
    MallocAdmission::evaluate(in, out);
    EXPECT_EQ(out.verdict.outcome, INDETERMINATE);
    EXPECT_EQ(out.verdict.reason, OWN_HOOK_WRONG_SLOT);
    EXPECT_EQ(out.target_count, 0);
}

TEST_F(AdmissionsTest, SavedPointerEqualOwnHookIsIndeterminate) {
    static const char* names[5] = {"malloc", "calloc", "realloc", "posix_memalign", "aligned_alloc"};
    CodeCache lib = makeCache(names, 5);
    _cells[0][PRIMARY] = (void*)&foreignTarget1;

    MallocAdmissionInput in = emptyInput();
    MallocAdmission::readImports(&lib, in.current);
    in.forwarding[0] = (const void*)malloc_hook;

    MallocAdmissionResult out;
    MallocAdmission::evaluate(in, out);
    EXPECT_EQ(out.verdict.outcome, INDETERMINATE);
    EXPECT_EQ(out.verdict.reason, SAVED_IS_OWN_HOOK);
    // The foreign slot value is still classified (derivation failures never
    // short-circuit), only the saved pointer is not a target.
    EXPECT_EQ(out.target_count, 1);
}

TEST_F(AdmissionsTest, RewrittenSlotFollowsSavedForwardingValue) {
    static const char* names[5] = {"malloc", "calloc", "realloc", "posix_memalign", "aligned_alloc"};
    CodeCache lib = makeCache(names, 5);
    _cells[0][PRIMARY] = (void*)malloc_hook;
    _cells[1][PRIMARY] = (void*)&foreignTarget2;

    MallocAdmissionInput in = emptyInput();
    MallocAdmission::readImports(&lib, in.current);
    in.forwarding[0] = (const void*)&foreignTarget1;

    MallocAdmissionResult out;
    MallocAdmission::evaluate(in, out);
    // The own-hook slot value contributes nothing itself; the saved
    // forwarding value is the target and classifies as marker-free.
    EXPECT_EQ(out.verdict.outcome, NOT_RECOGNIZED);
    EXPECT_EQ(out.target_count, 2);
    // Current-slot values are appended before forwarding values.
    EXPECT_EQ(out.targets[0], (const void*)&foreignTarget2);
    EXPECT_EQ(out.targets[1], (const void*)&foreignTarget1);
}

TEST_F(AdmissionsTest, DuplicateValuesDeduplicateToOneTarget) {
    static const char* names[5] = {"malloc", "calloc", "realloc", "posix_memalign", "aligned_alloc"};
    CodeCache lib = makeCache(names, 5);
    // Same foreign address in both malloc slots and as the saved forwarding
    // value: three candidates, one target.
    _cells[0][PRIMARY] = (void*)&foreignTarget1;
    lib.addImport(&_cells[0][SECONDARY], "malloc");
    _cells[0][SECONDARY] = (void*)&foreignTarget1;

    MallocAdmissionInput in = emptyInput();
    MallocAdmission::readImports(&lib, in.current);
    in.forwarding[0] = (const void*)&foreignTarget1;

    MallocAdmissionResult out;
    MallocAdmission::evaluate(in, out);
    EXPECT_EQ(out.verdict.outcome, NOT_RECOGNIZED);
    EXPECT_EQ(out.target_count, 1);
    EXPECT_EQ(out.targets[0], (const void*)&foreignTarget1);
}

TEST_F(AdmissionsTest, MissingOptionalImportAdmits) {
    // Only three of the five operations are imported (a libc without
    // aligned_alloc): the absent slots are NULL, admit, and keep current
    // behavior for the missing operations.
    static const char* names[3] = {"malloc", "calloc", "realloc"};
    CodeCache lib = makeCache(names, 3);
    _cells[0][PRIMARY] = (void*)&foreignTarget1;
    _cells[2][PRIMARY] = (void*)&foreignTarget2;

    MallocAdmissionInput in = emptyInput();
    MallocAdmission::readImports(&lib, in.current);
    EXPECT_EQ(in.current[3][PRIMARY], nullptr);
    EXPECT_EQ(in.current[4][PRIMARY], nullptr);

    MallocAdmissionResult out;
    MallocAdmission::evaluate(in, out);
    EXPECT_EQ(out.verdict.outcome, NOT_RECOGNIZED);
    EXPECT_EQ(out.target_count, 2);
}

// The profiler's own image must admit: it defines neither marker name (the
// released libjavaProfiler has no ddprof_start/stop_profiling export), so a
// target inside our own library classifies NOT_RECOGNIZED. This exercises the
// real own-image path on Linux and the platform-neutral fallback elsewhere.
TEST_F(AdmissionsTest, TargetInOwnImageAdmits) {
    static const char* names[5] = {"malloc", "calloc", "realloc", "posix_memalign", "aligned_alloc"};
    CodeCache lib = makeCache(names, 5);
    // Any address inside the profiler's own image: the library the hooks live
    // in also contains MallocTracer::recordMalloc.
    _cells[0][PRIMARY] = (void*)&MallocTracer::recordMalloc;

    MallocAdmissionInput in = emptyInput();
    MallocAdmission::readImports(&lib, in.current);

    MallocAdmissionResult out;
    MallocAdmission::evaluate(in, out);
    EXPECT_EQ(out.verdict.outcome, NOT_RECOGNIZED);
    EXPECT_EQ(out.verdict.reason, NONE);
    EXPECT_EQ(out.target_count, 1);
    EXPECT_EQ(out.target_verdicts[0].outcome, NOT_RECOGNIZED);
}

// The rejection literals are static and exact: tests and the Profiler::start()
// warning surface them verbatim.
TEST_F(AdmissionsTest, ErrorLiteralsAreExact) {
    EXPECT_STREQ(MallocAdmission::errorMessage(DDPROF),
                 "Native-memory profiling was not started: an allocation target points to a ddprof hook. "
                 "Enable only one native-memory allocation profiler for this process.");
    EXPECT_STREQ(MallocAdmission::errorMessage(INDETERMINATE),
                 "Native-memory profiling was not started: allocation-target ownership could not be determined.");
    EXPECT_EQ(MallocAdmission::errorMessage(NOT_RECOGNIZED), nullptr);
}

} // namespace
