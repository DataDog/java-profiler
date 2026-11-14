/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "codeCache.h"
#ifdef __linux__
#include "libraries.h"
#include <dlfcn.h>
#endif

#include <atomic>
#include <thread>

#include <stdio.h>

// memoryUsage() must reflect the actual per-symbol name length, not a fixed
// per-symbol constant: adding one symbol grows the reported usage by exactly
// the allocation size of its name string.
TEST(CodeCacheTest, MemoryUsageCountsSymbolNameLength) {
    CodeCache cc("testlib");
    long long base = cc.memoryUsage();

    const char *name =
        "a_long_symbol_name_well_beyond_sizeof_NativeFunc_padding_xxxxxxxxxxxx";
    cc.add(reinterpret_cast<const void *>(0x1000), 16, name);

    EXPECT_EQ(NativeFunc::allocSize(name), (size_t)(cc.memoryUsage() - base));
}

// A longer name costs more than a shorter one — the reported size scales with
// the actual symbol-name length.
TEST(CodeCacheTest, MemoryUsageGrowsWithNameLength) {
    CodeCache shortc("lib");
    CodeCache longc("lib");
    long long short_base = shortc.memoryUsage();
    long long long_base = longc.memoryUsage();

    shortc.add(reinterpret_cast<const void *>(0x1000), 8, "f");
    longc.add(reinterpret_cast<const void *>(0x1000), 8,
              "an_extremely_long_symbol_name_padded_out_further_and_further_1234");

    EXPECT_GT(longc.memoryUsage() - long_base, shortc.memoryUsage() - short_base);
}

// A freshly-constructed, empty cache reports exactly the blob array (counted at
// the full CodeBlob size, not a pointer's worth) plus its own name — nothing
// more. An exact check so over-counting or an inflated constant would fail.
TEST(CodeCacheTest, MemoryUsageCountsFullBlobArray) {
    CodeCache cc("lib");
    EXPECT_EQ((long long)INITIAL_CODE_CACHE_CAPACITY * sizeof(CodeBlob)
                  + (long long)NativeFunc::allocSize("lib"),
              cc.memoryUsage());
}

// The DWARF unwind table contributes length * sizeof(FrameDesc). Populate it so
// a regression (e.g. * flipped to /) in that term is caught; the table is
// zero-length in the other tests.
TEST(CodeCacheTest, MemoryUsageCountsDwarfTable) {
    CodeCache cc("lib");
    long long base = cc.memoryUsage();

    const int entries = 7;
    // setDwarfTable() takes ownership; ~CodeCache frees it. Contents are
    // irrelevant here — memoryUsage() reads only the length.
    FrameDesc *table = (FrameDesc *)malloc(entries * sizeof(FrameDesc));
    cc.setDwarfTable(table, entries);

    EXPECT_EQ((long long)entries * sizeof(FrameDesc), cc.memoryUsage() - base);
}

// Copying a CodeCache must deep-copy each blob's name string. With the previous
// shallow memcpy the copy shared the originals' _name pointers, so destroying
// both double-freed them. Here both copies are populated, sized equally, and
// destroyed — a double-free would abort (or trip ASan).
TEST(CodeCacheTest, CopyIsDeepAndDoesNotDoubleFree) {
    CodeCache src("lib");
    src.add(reinterpret_cast<const void *>(0x1000), 16, "sym_one");
    src.add(reinterpret_cast<const void *>(0x2000), 16, "sym_two_longer_name");
    long long expected = src.memoryUsage();

    {
        CodeCache copy(src);
        EXPECT_EQ(expected, copy.memoryUsage());
    }  // copy destroyed — must not free src's name strings

    EXPECT_EQ(expected, src.memoryUsage());  // src's names still intact
}  // src destroyed — no double free

// CodeCacheArray::memoryUsage() is the aggregation production actually consumes
// (Profiler::dump()). Verify it sums the per-library values — guards the loop
// bound and the accumulation against regressions the per-instance tests miss.
TEST(CodeCacheTest, ArrayMemoryUsageSumsLibraries) {
    CodeCacheArray arr;
    CodeCache *a = new CodeCache("liba");
    CodeCache *b = new CodeCache("libb");
    // Populate before registering: add() must run pre-publication.
    a->add(reinterpret_cast<const void *>(0x1000), 16, "alpha_symbol");
    b->add(reinterpret_cast<const void *>(0x2000), 16, "beta_symbol_longer_name");

    long long expected = (long long)a->memoryUsage() + (long long)b->memoryUsage();
    ASSERT_TRUE(arr.add(a));
    ASSERT_TRUE(arr.add(b));
    EXPECT_EQ(expected, (long long)arr.memoryUsage());

    // CodeCacheArray does not own the entries.
    delete a;
    delete b;
}

// The two-phase add used under JitCodeCache's stubs lock: prepareAdd() hands
// over a grown array only when the cache is full, commitAdd() returns the
// replaced array exactly then, and the result matches add()'s documented
// accounting (blob array at the grown capacity plus each name allocation).
TEST(CodeCacheTest, TwoPhaseAddGrowsOnlyWhenFull) {
    CodeCache cc("lib");
    long long names = 0;
    char name[32];
    const int ADDS = INITIAL_CODE_CACHE_CAPACITY + 1;
    for (int i = 0; i < ADDS; i++) {
        snprintf(name, sizeof(name), "sym_%d", i);
        CodeCache::PreparedAdd prepared;
        cc.prepareAdd(name, prepared);
        bool full = i == INITIAL_CODE_CACHE_CAPACITY;
        EXPECT_EQ(full, prepared.grown != nullptr) << i;
        CodeBlob *retired = cc.commitAdd(reinterpret_cast<const void *>(0x1000 + i * 16),
                                         16, prepared);
        EXPECT_EQ(full, retired != nullptr) << i;
        delete[] retired;
        names += (long long)NativeFunc::allocSize(name);
    }
    EXPECT_EQ((long long)INITIAL_CODE_CACHE_CAPACITY * 2 * sizeof(CodeBlob)
                  + (long long)NativeFunc::allocSize("lib") + names,
              cc.memoryUsage());
    for (int i = 0; i < ADDS; i++) {
        snprintf(name, sizeof(name), "sym_%d", i);
        EXPECT_EQ(reinterpret_cast<const void *>(0x1000 + i * 16), cc.findSymbol(name)) << i;
    }
}

// prepareAdd() keeps add()'s replacement of non-printable name characters.
TEST(CodeCacheTest, TwoPhaseAddReplacesNonPrintableName) {
    CodeCache cc("lib");
    CodeCache::PreparedAdd prepared;
    cc.prepareAdd("a\x01" "b", prepared);
    delete[] cc.commitAdd(reinterpret_cast<const void *>(0x1000), 16, prepared);
    EXPECT_EQ(reinterpret_cast<const void *>(0x1000), cc.findSymbol("a?b"));
}

// A PreparedAdd that is never committed frees its allocations and leaves the
// cache unchanged, including when it holds a grown blob array. LeakSanitizer
// (ASan builds) reports the allocations if the destructor does not free them.
TEST(CodeCacheTest, UncommittedPrepareFreesAndLeavesCacheUnchanged) {
    CodeCache cc("lib");
    char name[32];
    for (int i = 0; i < INITIAL_CODE_CACHE_CAPACITY; i++) {
        snprintf(name, sizeof(name), "sym_%d", i);
        cc.add(reinterpret_cast<const void *>(0x1000 + i * 16), 16, name);
    }
    long long usage = cc.memoryUsage();
    {
        CodeCache::PreparedAdd prepared;
        cc.prepareAdd("never_committed", prepared);
        EXPECT_NE(nullptr, prepared.name);
        EXPECT_NE(nullptr, prepared.grown);
    }
    EXPECT_EQ(usage, cc.memoryUsage());
    EXPECT_EQ(nullptr, cc.findSymbol("never_committed"));
}

// commitAdd() takes ownership: the PreparedAdd no longer refers to the name or
// the grown array, so its destructor cannot free storage the cache uses.
TEST(CodeCacheTest, CommitAddTakesOwnership) {
    CodeCache cc("lib");
    CodeCache::PreparedAdd prepared;
    cc.prepareAdd("owned", prepared);
    delete[] cc.commitAdd(reinterpret_cast<const void *>(0x1000), 16, prepared);
    EXPECT_EQ(nullptr, prepared.name);
    EXPECT_EQ(nullptr, prepared.grown);
    EXPECT_EQ(reinterpret_cast<const void *>(0x1000), cc.findSymbol("owned"));
}

TEST(CodeCacheTest, PeekImportFinalizesVariableCountLayoutWithoutWritingMappings) {
    CodeCache cache("non-writing-imports");
    void** read_slot = reinterpret_cast<void**>(1);
    void** second_read_slot = reinterpret_cast<void**>(2);
    void** recv_slot = reinterpret_cast<void**>(3);
    cache.addImport(recv_slot, "recv");
    cache.addImport(second_read_slot, "read");
    cache.addImport(read_slot, "read");
    cache.addImport(read_slot, "read");

    EXPECT_EQ(read_slot, cache.peekImport(im_read));
    EXPECT_EQ(2u, cache.importCount(im_read));
    EXPECT_EQ(recv_slot, cache.peekImport(im_recv));
    EXPECT_EQ(nullptr, cache.peekImport(im_sigaction));
    // Negative values are outside ImportId's C++ enum domain; use a valid upper outlier.
    EXPECT_EQ(nullptr, cache.peekImport(static_cast<ImportId>(NUM_IMPORTS + 1)));
    EXPECT_EQ(nullptr, cache.peekImport(NUM_IMPORTS));
}

TEST(CodeCacheTest, PublishedImportsPreserveLookupAndDeduplication) {
    CodeCache cache("published-imports");
    void** read_slot = reinterpret_cast<void**>(1);
    void** recv_slot = reinterpret_cast<void**>(2);
    cache.addImport(recv_slot, "recv");
    cache.addImport(read_slot, "read");
    cache.addImport(recv_slot, "recv");
    cache.markPublished();

    EXPECT_EQ(read_slot, cache.peekImport(im_read));
    EXPECT_EQ(recv_slot, cache.peekImport(im_recv));
    EXPECT_EQ(1u, cache.importCount(im_read));
    EXPECT_EQ(1u, cache.importCount(im_recv));
}

#ifdef __linux__
TEST(CodeCacheTest, ConcurrentImportLookupAndReprotectionUseIndependentWriterDomains) {
    const char* paths[] = {
        "build/test/resources/native-libs/patch-target-lib/libpatchtarget.so",
        "../build/test/resources/native-libs/patch-target-lib/libpatchtarget.so",
    };
    void* handle = nullptr;
    for (const char* path : paths) {
        handle = dlopen(path, RTLD_NOW | RTLD_LOCAL);
        if (handle != nullptr) break;
    }
    ASSERT_NE(nullptr, handle) << dlerror();
    void* symbol = dlsym(handle, "patch_target_write");
    ASSERT_NE(nullptr, symbol);
    Libraries::instance()->updateSymbols(false);
    CodeCache* cache = Libraries::instance()->findLibraryByAddress(symbol);
    ASSERT_NE(nullptr, cache);
    void** slot = cache->findImport(im_write);
    ASSERT_NE(nullptr, slot);
    void* original = __atomic_load_n(slot, __ATOMIC_ACQUIRE);
    std::atomic<bool> start{false};
    std::atomic<bool> lookup_ok{true};
    std::atomic<bool> reprotect_ok{true};
    std::thread lookup([&]() {
        while (!start.load(std::memory_order_acquire)) std::this_thread::yield();
        for (int i = 0; i < 2000; i++) {
            if (cache->findImport(im_write) != slot ||
                __atomic_load_n(slot, __ATOMIC_ACQUIRE) != original) {
                lookup_ok.store(false, std::memory_order_release);
            }
        }
    });
    std::thread reprotect([&]() {
        while (!start.load(std::memory_order_acquire)) std::this_thread::yield();
        for (int i = 0; i < 2000; i++) {
            if (!cache->makeImportsWritable()) {
                reprotect_ok.store(false, std::memory_order_release);
            }
        }
    });
    start.store(true, std::memory_order_release);
    lookup.join();
    reprotect.join();
    EXPECT_TRUE(lookup_ok.load(std::memory_order_acquire));
    EXPECT_TRUE(reprotect_ok.load(std::memory_order_acquire));
    EXPECT_EQ(original, __atomic_load_n(slot, __ATOMIC_ACQUIRE));
    EXPECT_EQ(0, dlclose(handle));
}
#endif
