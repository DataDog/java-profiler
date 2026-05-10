/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "../../main/cpp/codeCache.h"
#include "../../main/cpp/findLibraryImpl.h"
#include "../../main/cpp/gtest_crash_handler.h"

static constexpr char LIBRARIES_TEST_NAME[] = "LibrariesTest";

// Three static buffers to serve as fake "text segments".
// Using static storage ensures the addresses are stable and non-overlapping.
static char g_lib0_text[1024];
static char g_lib1_text[1024];
static char g_lib2_text[1024];

class LibrariesTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<LIBRARIES_TEST_NAME>();

        _lib0 = new CodeCache("libfake0.so", 0, g_lib0_text, g_lib0_text + sizeof(g_lib0_text));
        _lib1 = new CodeCache("libfake1.so", 1, g_lib1_text, g_lib1_text + sizeof(g_lib1_text));
        _lib2 = new CodeCache("libfake2.so", 2, g_lib2_text, g_lib2_text + sizeof(g_lib2_text));

        _libs.add(_lib0);
        _libs.add(_lib1);
        _libs.add(_lib2);
    }

    void TearDown() override {
        restoreDefaultSignalHandlers();
        delete _lib0;
        delete _lib1;
        delete _lib2;
    }

    CodeCacheArray _libs;
    CodeCache* _lib0 = nullptr;
    CodeCache* _lib1 = nullptr;
    CodeCache* _lib2 = nullptr;
};

TEST_F(LibrariesTest, KnownAddress) {
    // Address inside lib1's range should return lib1.
    const void* addr = g_lib1_text + 512;
    CodeCache* result = findLibraryByAddressImpl<CodeCache>(_libs, addr);
    EXPECT_EQ(result, _lib1);
}

TEST_F(LibrariesTest, NullAddress) {
    // NULL should return nullptr without crashing.
    CodeCache* result = findLibraryByAddressImpl<CodeCache>(_libs, nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(LibrariesTest, InvalidAddress) {
    // An address outside all known ranges should return nullptr.
    const void* addr = reinterpret_cast<const void*>(0x1);
    CodeCache* result = findLibraryByAddressImpl<CodeCache>(_libs, addr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(LibrariesTest, FirstLibrary) {
    const void* addr = g_lib0_text + 100;
    CodeCache* result = findLibraryByAddressImpl<CodeCache>(_libs, addr);
    EXPECT_EQ(result, _lib0);
}

TEST_F(LibrariesTest, LastLibrary) {
    const void* addr = g_lib2_text + 900;
    CodeCache* result = findLibraryByAddressImpl<CodeCache>(_libs, addr);
    EXPECT_EQ(result, _lib2);
}

TEST_F(LibrariesTest, CacheHitOnRepeatedLookup) {
    // First lookup primes the cache for lib1.
    const void* addr = g_lib1_text + 256;
    CodeCache* first = findLibraryByAddressImpl<CodeCache>(_libs, addr);
    EXPECT_EQ(first, _lib1);

    // Second lookup with the same range should still return lib1 (cache hit path).
    CodeCache* second = findLibraryByAddressImpl<CodeCache>(_libs, g_lib1_text + 700);
    EXPECT_EQ(second, _lib1);
}

TEST_F(LibrariesTest, CacheMissFallsBackToLinearScan) {
    // Prime cache for lib0.
    findLibraryByAddressImpl<CodeCache>(_libs, g_lib0_text + 10);

    // Now look up an address in lib2 — cache miss, linear scan must find it.
    const void* addr = g_lib2_text + 500;
    CodeCache* result = findLibraryByAddressImpl<CodeCache>(_libs, addr);
    EXPECT_EQ(result, _lib2);
}
