#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "libraries.h"
#include "codeCache.h"
#include <dlfcn.h>

class LibrariesTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset to ensure tests are isolated
        _libs = Libraries::instance();
        _libs->updateSymbols(false);
    }
    
    Libraries* _libs = nullptr;
};

TEST_F(LibrariesTest, SymbolResolution) {
    // Test resolving a known symbol from a standard library
    const void* sym = _libs->resolveSymbol("malloc");
    ASSERT_THAT(sym, ::testing::NotNull());
}

TEST_F(LibrariesTest, SymbolResolutionNonExistent) {
    // Test resolving a non-existent symbol
    const void* sym = _libs->resolveSymbol("this_symbol_should_not_exist_anywhere");
    EXPECT_THAT(sym, ::testing::IsNull());
}

TEST_F(LibrariesTest, FindLibraryByAddress) {
    // Get an address from a known function
    void* mallocAddr = dlsym(RTLD_DEFAULT, "malloc");
    ASSERT_THAT(mallocAddr, ::testing::NotNull());

    // Find the library containing this address
    CodeCache* lib = _libs->findLibraryByAddress(mallocAddr);
    EXPECT_THAT(lib, ::testing::NotNull());
}

TEST_F(LibrariesTest, FindLibraryByName) {
    // Test finding a common library by name
#ifdef __APPLE__
    CodeCache* lib = _libs->findLibraryByName("libSystem.B.dylib");
#else
    CodeCache* lib = _libs->findLibraryByName("libc.so");
#endif
    EXPECT_THAT(lib, ::testing::NotNull());
}

TEST_F(LibrariesTest, FindLibraryByInvalidAddress) {
    // Test with NULL address
    CodeCache* lib = _libs->findLibraryByAddress(nullptr);
    EXPECT_THAT(lib, ::testing::IsNull());
    
    // Test with likely invalid address (deep in kernel space or unmapped)
    CodeCache* lib2 = _libs->findLibraryByAddress(reinterpret_cast<void*>(0x1));
    EXPECT_THAT(lib2, ::testing::IsNull());
}

