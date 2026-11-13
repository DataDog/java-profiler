/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Linux-only owner-walk gtests for the admission target set: the fifteen
// per-operation/slot/saved-pointer ddprof-rejection cases, deduplication with
// per-attempt owner classification, and the DDPROF-over-INDETERMINATE
// precedence with an unattributable target present. Zero tests on macOS —
// evidence comes only from the Linux container gates. The ddprof images are
// the real fixture DSOs built by :ddprof-lib:buildNativeLibs; a missing
// fixture fails the test instead of skipping it.

#ifdef __linux__

#include <gtest/gtest.h>

#include <dlfcn.h>
#include <limits.h>
#include <sys/mman.h>
#include <unistd.h>

#include <string>

#include "codeCache.h"
#include "mallocAdmission.h"

namespace {

// Locates a built fixture by variant name; empty means not built, which fails
// the test (a missing fixture must never silently skip the coverage).
std::string fixturePath(const char* variant) {
    char exe[PATH_MAX - 128];
    ssize_t len = readlink("/proc/self/exe", exe, sizeof(exe) - 1);
    if (len <= 0) return std::string();
    exe[len] = '\0';
    *strrchr(exe, '/') = '\0';
    char path[PATH_MAX];
    snprintf(path, sizeof(path),
             "%s/../../../test/resources/native-libs/ddprof-admission/libddprof-fixture-%s.so", exe, variant);
    struct stat st;
    if (stat(path, &st) != 0) return std::string();
    return std::string(path);
}

// A real address inside the loaded fixture image: any exported function of
// the ddprof-recognizable fixture works as an allocation target owned by it.
const void* loadFixtureTarget(const char* variant, void** handle_out) {
    std::string path = fixturePath(variant);
    EXPECT_FALSE(path.empty()) << "Missing fixture libddprof-fixture-" << variant << ".so (built by "
                               << ":ddprof-lib:buildNativeLibs)";
    if (path.empty()) return nullptr;
    *handle_out = dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL);
    if (*handle_out == nullptr) {
        ADD_FAILURE() << "dlopen(" << path << ") failed: " << dlerror();
        return nullptr;
    }
    void* sym = dlsym(*handle_out, "ddprof_start_profiling");
    EXPECT_NE(sym, nullptr) << "Fixture " << variant << " does not export ddprof_start_profiling";
    return sym;
}

// Distinct real addresses inside this test binary: owned by the test image,
// which defines no markers. The own-hook stand-ins must be five distinct
// addresses, or a target equal to a shared stand-in trips the wrong-slot
// rule of another operation.
static void ownImageTarget1() {}
static void ownImageTarget2() {}
static void ownHookStandin1() {}
static void ownHookStandin2() {}
static void ownHookStandin3() {}
static void ownHookStandin4() {}
static void ownHookStandin5() {}

const void* const* ownHooks() {
    // Real own-hook addresses are not needed here: the fixtures provide the
    // ddprof image, and the slots hold fixture addresses, so the own-hook
    // rules never fire.
    static const void* hooks[5] = {(const void*)ownHookStandin1, (const void*)ownHookStandin2,
                                   (const void*)ownHookStandin3, (const void*)ownHookStandin4,
                                   (const void*)ownHookStandin5};
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

const char* const OPERATION_NAMES[5] = {"malloc", "calloc", "realloc", "posix_memalign", "aligned_alloc"};

MallocAdmissionResult evaluateWith(const MallocAdmissionInput& in) {
    MallocAdmissionResult out;
    MallocAdmission::evaluate(in, out);
    return out;
}

class MallocAdmissionSlotsTest : public ::testing::Test {};

// Every operation's current PRIMARY slot, current SECONDARY slot and saved
// forwarding pointer independently triggers DDPROF: 5 x 3 = 15 rejection
// cases over real fixture images (AC-4).
TEST(MallocAdmissionSlotsTest, EveryOperationAndSlotRejectsOnFixtureAddress) {
    for (int op = 0; op < 5; op++) {
        for (int slot = 0; slot < 3; slot++) {
            void* handle = nullptr;
            const void* fixture = loadFixtureTarget("gnu", &handle);
            ASSERT_NE(fixture, nullptr);

            // The own library stand-in carries the slots; the fixture address
            // is what a GOT rewritten by the other profiler would hold.
            void* primary = NULL;
            void* secondary = NULL;
            CodeCache lib("/test/libadmissionslots.so", -1, (const void*)0x1000, (const void*)0x2000, nullptr,
                          /* imports_patchable */ true);
            MallocAdmissionInput in = emptyInput();
            if (slot == 0) {
                lib.addImport(&primary, OPERATION_NAMES[op]);
                primary = (void*)fixture;
                in.current[op][PRIMARY] = fixture;
            } else if (slot == 1) {
                lib.addImport(&primary, OPERATION_NAMES[op]);
                lib.addImport(&secondary, OPERATION_NAMES[op]);
                secondary = (void*)fixture;
                in.current[op][SECONDARY] = fixture;
            } else {
                lib.addImport(&primary, OPERATION_NAMES[op]);
                in.forwarding[op] = fixture;
            }

            const void* current[5][NUM_IMPORT_TYPES];
            MallocAdmission::readImports(&lib, current);
            for (int o = 0; o < 5; o++) {
                for (int t = 0; t < NUM_IMPORT_TYPES; t++) {
                    if (o == op && (slot == 0 ? t == (int)PRIMARY : slot == 1 ? t == (int)SECONDARY : false)) {
                        in.current[o][t] = current[o][t];
                    }
                }
            }

            MallocAdmissionResult out = evaluateWith(in);
            EXPECT_EQ(out.verdict.outcome, DDPROF) << "op=" << op << " slot=" << slot;
            EXPECT_EQ(out.verdict.reason, NONE) << "op=" << op << " slot=" << slot;
            dlclose(handle);
        }
    }
}

// The same fixture address arriving through several candidates deduplicates
// to one target, and the containing image is classified exactly once per
// attempt.
TEST(MallocAdmissionSlotsTest, SharedAddressIsOneTargetAndOwnerClassifiedOnce) {
    void* handle = nullptr;
    const void* fixture = loadFixtureTarget("gnu", &handle);
    ASSERT_NE(fixture, nullptr);

    void* cell = NULL;
    CodeCache lib("/test/libadmissionslots.so", -1, (const void*)0x1000, (const void*)0x2000, nullptr,
                  /* imports_patchable */ true);
    lib.addImport(&cell, "malloc");
    lib.addImport(&cell, "malloc");
    cell = (void*)fixture;

    MallocAdmissionInput in = emptyInput();
    const void* current[5][NUM_IMPORT_TYPES];
    MallocAdmission::readImports(&lib, current);
    in.current[0][PRIMARY] = current[0][PRIMARY];
    in.current[0][SECONDARY] = current[0][SECONDARY];
    in.forwarding[0] = fixture;

    MallocAdmissionResult out = evaluateWith(in);
    EXPECT_EQ(out.verdict.outcome, DDPROF);
    EXPECT_EQ(out.target_count, 1);
    // Every candidate stripped-compares equal to the fixture address.
    ASSERT_EQ(out.targets[0], fixture);
    // One unassigned target in one owner image: exactly one classification.
    EXPECT_EQ(out.images_classified, 1);
    dlclose(handle);
}

// Two targets in two distinct marker-free images: both owners are classified
// in one attempt, each once, and the set admits. (A DDPROF owner ends the
// walk early by contract, so the owner-once assertion needs marker-free
// images; the fixture without markers is the second one.)
TEST(MallocAdmissionSlotsTest, TwoImagesClassifiedOnceEach) {
    void* handle = nullptr;
    const void* nomark = nullptr;
    std::string path = fixturePath("nomark");
    ASSERT_FALSE(path.empty()) << "Missing fixture libddprof-fixture-nomark.so (built by "
                               << ":ddprof-lib:buildNativeLibs)";
    handle = dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL);
    ASSERT_NE(handle, nullptr) << dlerror();
    // The exported counter object is a data symbol inside the nomark image;
    // its address is contained by one of the image's PT_LOADs.
    void* sym = dlsym(handle, "fixture_start_marker_calls");
    ASSERT_NE(sym, nullptr);
    nomark = sym;

    void* cell = NULL;
    CodeCache lib("/test/libadmissionslots.so", -1, (const void*)0x1000, (const void*)0x2000, nullptr,
                  /* imports_patchable */ true);
    lib.addImport(&cell, "malloc");
    cell = (void*)nomark;

    MallocAdmissionInput in = emptyInput();
    const void* current[5][NUM_IMPORT_TYPES];
    MallocAdmission::readImports(&lib, current);
    in.current[0][PRIMARY] = current[0][PRIMARY];
    in.current[1][PRIMARY] = (const void*)&ownImageTarget1;

    MallocAdmissionResult out = evaluateWith(in);
    EXPECT_EQ(out.verdict.outcome, NOT_RECOGNIZED);
    EXPECT_EQ(out.target_count, 2);
    // The nomark fixture and the test image were both classified, each once.
    EXPECT_EQ(out.images_classified, 2);
    dlclose(handle);
}

// A mixed set with one target in anonymous executable memory (no owner) and
// one fixture target yields DDPROF: the recognized owner takes diagnostic
// precedence over the unattributable one, whatever order the loader reports
// the objects in (AC-11).
TEST(MallocAdmissionSlotsTest, NoOwnerTargetDoesNotMaskFixtureDDProf) {
    void* handle = nullptr;
    const void* fixture = loadFixtureTarget("gnu", &handle);
    ASSERT_NE(fixture, nullptr);

    void* anon = mmap(nullptr, 4096, PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    ASSERT_NE(anon, MAP_FAILED);

    void* cell = NULL;
    CodeCache lib("/test/libadmissionslots.so", -1, (const void*)0x1000, (const void*)0x2000, nullptr,
                  /* imports_patchable */ true);
    lib.addImport(&cell, "malloc");
    cell = (void*)fixture;

    MallocAdmissionInput in = emptyInput();
    const void* current[5][NUM_IMPORT_TYPES];
    MallocAdmission::readImports(&lib, current);
    in.current[0][PRIMARY] = current[0][PRIMARY];
    in.current[1][PRIMARY] = anon;

    MallocAdmissionResult out = evaluateWith(in);
    EXPECT_EQ(out.verdict.outcome, DDPROF);
    EXPECT_EQ(out.verdict.reason, NONE);
    EXPECT_EQ(out.target_count, 2);
    // The unattributable target stays NO_OWNER while the fixture target
    // carries the DDPROF verdict.
    int ddprof_targets = 0, no_owner_targets = 0;
    for (int i = 0; i < out.target_count; i++) {
        if (out.target_verdicts[i].outcome == DDPROF) ddprof_targets++;
        if (out.target_verdicts[i].outcome == INDETERMINATE && out.target_verdicts[i].reason == NO_OWNER) {
            no_owner_targets++;
        }
    }
    EXPECT_EQ(ddprof_targets, 1);
    EXPECT_EQ(no_owner_targets, 1);
    munmap(anon, 4096);
    dlclose(handle);
}

} // namespace

#endif // __linux__
