/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Classification tests for the native-memory admission marker lookup against
// the native fixture DSOs built by :ddprof-lib:buildNativeLibs (real ELF
// bytes). This file contributes zero tests on non-Linux platforms.

#ifdef __linux__

#include <gtest/gtest.h>

#include <dlfcn.h>
#include <elf.h>
#include <fcntl.h>
#include <limits.h>
#include <link.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "../../main/cpp/mallocAdmission_linux.h"

namespace {

// Copies a fixture to a uniquely named file (mkstemp pattern) and returns its
// path. The caller owns the path buffer.
std::string copyFixture(const char* source) {
    char tmpl[] = "/tmp/ddprof-admission-XXXXXX";
    int fd = mkstemp(tmpl);
    if (fd < 0) return std::string();
    close(fd);
    std::string target(tmpl);
    // Copy the bytes: the load path must not depend on the original resource
    // name, and the copy is unlinked while mapped.
    FILE* in = fopen(source, "rb");
    FILE* out = fopen(target.c_str(), "wb");
    if (in == nullptr || out == nullptr) {
        if (in != nullptr) fclose(in);
        if (out != nullptr) fclose(out);
        return std::string();
    }
    char buffer[8192];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), in)) > 0) {
        if (fwrite(buffer, 1, n, out) != n) {
            fclose(in);
            fclose(out);
            return std::string();
        }
    }
    fclose(in);
    fclose(out);
    return target;
}

// Locates the program headers of a dlopen'ed object: dlinfo gives its link
// map entry, dl_iterate_phdr the matching dl_phdr_info.
struct LoadedPhdrs {
    const ElfW(Phdr)* phdrs;
    int phnum;
    uintptr_t load_bias;
};

int findLoadedObject(struct dl_phdr_info* info, size_t, void* data) {
    LoadedPhdrs* query = (LoadedPhdrs*)data;
    if ((uintptr_t)info->dlpi_addr == query->load_bias) {
        query->phdrs = info->dlpi_phdr;
        query->phnum = info->dlpi_phnum;
        return 1;
    }
    return 0;
}

// dlopens a fixture and returns its program headers through the loader's own
// reporting, not from a re-read file: classification sees the same mapping
// the process runs from.
bool loadFixture(const char* path, int flags, void** handle_out, LoadedPhdrs* phdrs_out) {
    *handle_out = dlopen(path, flags);
    if (*handle_out == nullptr) {
        const char* error = dlerror();
        ADD_FAILURE() << "dlopen(" << path << ") failed: " << (error ? error : "no error");
        return false;
    }
    struct link_map* map = nullptr;
    if (dlinfo(*handle_out, RTLD_DI_LINKMAP, &map) != 0 || map == nullptr) {
        const char* error = dlerror();
        ADD_FAILURE() << "dlinfo failed: " << (error ? error : "no error");
        return false;
    }
    phdrs_out->load_bias = (uintptr_t)map->l_addr;
    phdrs_out->phdrs = nullptr;
    phdrs_out->phnum = 0;
    dl_iterate_phdr(findLoadedObject, phdrs_out);
    if (phdrs_out->phdrs == nullptr) {
        ADD_FAILURE() << "dl_iterate_phdr found no object at load bias "
                      << (void*)phdrs_out->load_bias;
        return false;
    }
    return true;
}

std::string fixturePath(const char* variant) {
    char exe[PATH_MAX - 128];
    ssize_t len = readlink("/proc/self/exe", exe, sizeof(exe) - 1);
    if (len <= 0) return std::string();
    exe[len] = '\0';
    *strrchr(exe, '/') = '\0';
    char path[PATH_MAX];
    snprintf(path, sizeof(path),
             "%s/../../../test/resources/native-libs/ddprof-admission/libddprof-fixture-%s.so", exe,
             variant);
    struct stat st;
    if (stat(path, &st) != 0) return std::string();
    return std::string(path);
}

AdmissionVerdict classifyFixture(const LoadedPhdrs& image) {
    return ElfMarkerLookup::classifyImage(image.phdrs, image.phnum, image.load_bias);
}

// Reads an exported uint64_t counter from a loaded fixture; the counters are
// dlsym'ed, not linked, because the fixtures are dlopen'ed test resources.
uint64_t readCounter(void* handle, const char* name) {
    void* sym = dlsym(handle, name);
    EXPECT_NE(sym, nullptr) << "Missing counter " << name;
    if (sym == nullptr) return UINT64_MAX;
    return *(uint64_t*)sym;
}

class MallocAdmissionElfTest : public ::testing::Test {};

// A recognized ddprof image classifies as DDPROF even when copied to a
// random path and unlinked while mapped: identity follows the image, not the
// pathname (AC-5).
TEST(MallocAdmissionElfTest, RenamedAndUnlinkedFixtureIsDDProf) {
    std::string source = fixturePath("gnu");
    ASSERT_FALSE(source.empty()) << "Missing fixture libddprof-fixture-gnu.so (built by "
                                    ":ddprof-lib:buildNativeLibs)";
    std::string copy = copyFixture(source.c_str());
    ASSERT_FALSE(copy.empty());
    void* handle = nullptr;
    LoadedPhdrs image = {};
    ASSERT_TRUE(loadFixture(copy.c_str(), RTLD_NOW, &handle, &image));
    unlink(copy.c_str());
    AdmissionVerdict verdict = classifyFixture(image);
    EXPECT_EQ(verdict.outcome, DDPROF);
    EXPECT_EQ(verdict.reason, NONE);
    dlclose(handle);
}

// The hash-table kind must not matter: GNU-only, SysV-only and both-table
// builds of the same markers all classify as DDPROF.
TEST(MallocAdmissionElfTest, HashTableVariantsAreDDProf) {
    const char* variants[] = {"gnu", "sysv", "both"};
    for (const char* variant : variants) {
        std::string path = fixturePath(variant);
        ASSERT_FALSE(path.empty()) << "Missing fixture " << path;
        void* handle = nullptr;
        LoadedPhdrs image = {};
        ASSERT_TRUE(loadFixture(path.c_str(), RTLD_NOW, &handle, &image));
        AdmissionVerdict verdict = classifyFixture(image);
        EXPECT_EQ(verdict.outcome, DDPROF) << variant;
        EXPECT_EQ(verdict.reason, NONE) << variant;
        dlclose(handle);
    }
}

// A hook-only image (same allocation imports, no markers) is not recognized.
TEST(MallocAdmissionElfTest, NoMarkerFixtureIsNotRecognized) {
    std::string path = fixturePath("nomark");
    ASSERT_FALSE(path.empty()) << "Missing fixture " << path;
    void* handle = nullptr;
    LoadedPhdrs image = {};
    ASSERT_TRUE(loadFixture(path.c_str(), RTLD_NOW, &handle, &image));
    AdmissionVerdict verdict = classifyFixture(image);
    EXPECT_EQ(verdict.outcome, NOT_RECOGNIZED);
    EXPECT_EQ(verdict.reason, NONE);
    dlclose(handle);
}

// Markers that exist only as undefined imports of a dependency are not owned
// definitions: the importing image is NOT_RECOGNIZED, the defining dependency
// is DDPROF.
TEST(MallocAdmissionElfTest, DependencyOnlyMarkersAreNotRecognized) {
    std::string dep = fixturePath("dep");
    std::string deponly = fixturePath("deponly");
    ASSERT_FALSE(dep.empty()) << "Missing fixture " << dep;
    ASSERT_FALSE(deponly.empty()) << "Missing fixture " << deponly;
    void* dep_handle = nullptr;
    LoadedPhdrs dep_image = {};
    // RTLD_GLOBAL so the dependent fixture's undefined markers resolve from it.
    ASSERT_TRUE(loadFixture(dep.c_str(), RTLD_NOW | RTLD_GLOBAL, &dep_handle, &dep_image));
    void* deponly_handle = nullptr;
    LoadedPhdrs deponly_image = {};
    ASSERT_TRUE(loadFixture(deponly.c_str(), RTLD_NOW, &deponly_handle, &deponly_image));
    AdmissionVerdict deponly_verdict = classifyFixture(deponly_image);
    EXPECT_EQ(deponly_verdict.outcome, NOT_RECOGNIZED);
    EXPECT_EQ(deponly_verdict.reason, NONE);
    AdmissionVerdict dep_verdict = classifyFixture(dep_image);
    EXPECT_EQ(dep_verdict.outcome, DDPROF);
    EXPECT_EQ(dep_verdict.reason, NONE);
    dlclose(deponly_handle);
    dlclose(dep_handle);
}

// One marker alone is partial recognition: INDETERMINATE, never a clean
// DDPROF or a silent NOT_RECOGNIZED.
TEST(MallocAdmissionElfTest, OneMarkerIsIndeterminatePartial) {
    std::string path = fixturePath("onemark");
    ASSERT_FALSE(path.empty()) << "Missing fixture " << path;
    void* handle = nullptr;
    LoadedPhdrs image = {};
    ASSERT_TRUE(loadFixture(path.c_str(), RTLD_NOW, &handle, &image));
    AdmissionVerdict verdict = classifyFixture(image);
    EXPECT_EQ(verdict.outcome, INDETERMINATE);
    EXPECT_EQ(verdict.reason, PARTIAL_MARKERS);
    dlclose(handle);
}

// A marker with the wrong ELF symbol type fails the image closed.
TEST(MallocAdmissionElfTest, ObjectMarkerIsIndeterminateWrongKind) {
    std::string path = fixturePath("object");
    ASSERT_FALSE(path.empty()) << "Missing fixture " << path;
    void* handle = nullptr;
    LoadedPhdrs image = {};
    ASSERT_TRUE(loadFixture(path.c_str(), RTLD_NOW, &handle, &image));
    AdmissionVerdict verdict = classifyFixture(image);
    EXPECT_EQ(verdict.outcome, INDETERMINATE);
    EXPECT_EQ(verdict.reason, WRONG_KIND_MARKER);
    dlclose(handle);
}

// An STT_GNU_IFUNC marker is also wrong-kind. The fixture is glibc-only; on
// musl the admission rules are still covered by the synthesized-image tests.
TEST(MallocAdmissionElfTest, IfuncMarkerIsIndeterminateWrongKind) {
    std::string path = fixturePath("ifunc");
    if (path.empty()) {
        GTEST_SKIP() << "libddprof-fixture-ifunc.so is glibc-only (musl has no ifunc support)";
    }
    void* handle = nullptr;
    LoadedPhdrs image = {};
    ASSERT_TRUE(loadFixture(path.c_str(), RTLD_NOW, &handle, &image));
    AdmissionVerdict verdict = classifyFixture(image);
    EXPECT_EQ(verdict.outcome, INDETERMINATE);
    EXPECT_EQ(verdict.reason, WRONG_KIND_MARKER);

    // Classification must never execute a marker or an IFUNC resolver
    // (AC-13): glibc resolved the resolver once at relocation time, and the
    // admission check must not have added a call.
    uint64_t resolver_calls = readCounter(handle, "fixture_resolver_calls");
    ASSERT_NE(resolver_calls, UINT64_MAX);
    (void)classifyFixture(image);
    EXPECT_EQ(readCounter(handle, "fixture_resolver_calls"), resolver_calls);
    dlclose(handle);
}

// Classifying a recognized image must not execute its markers (AC-13).
TEST(MallocAdmissionElfTest, ClassificationDoesNotCallMarkers) {
    std::string path = fixturePath("gnu");
    ASSERT_FALSE(path.empty()) << "Missing fixture " << path;
    void* handle = nullptr;
    LoadedPhdrs image = {};
    ASSERT_TRUE(loadFixture(path.c_str(), RTLD_NOW, &handle, &image));
    uint64_t start_calls = readCounter(handle, "fixture_start_marker_calls");
    uint64_t stop_calls = readCounter(handle, "fixture_stop_marker_calls");
    ASSERT_NE(start_calls, UINT64_MAX);
    ASSERT_NE(stop_calls, UINT64_MAX);
    AdmissionVerdict verdict = classifyFixture(image);
    EXPECT_EQ(verdict.outcome, DDPROF);
    EXPECT_EQ(readCounter(handle, "fixture_start_marker_calls"), start_calls);
    EXPECT_EQ(readCounter(handle, "fixture_stop_marker_calls"), stop_calls);
    dlclose(handle);
}

}  // namespace

#endif  // __linux__
