#ifdef __linux__

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "codeCache.h"
#include "libraries.h"
#include "symbols.h"
#include "symbols_linux.h"
#include "log.h"
#include "../../main/cpp/gtest_crash_handler.h"

#include <unistd.h>
#include <limits.h> // For PATH_MAX

#include <fcntl.h>
#include <sys/mman.h>
#include <cstring>
#include <chrono>
#include <thread>

#include <dlfcn.h>
#include <link.h>
#include <signal.h>
#include <unistd.h>
#include <cstdio>

// Test name for crash handler
static constexpr char ELF_TEST_NAME[] = "ElfParserTest";

// Global crash handler installation (since this file uses bare TEST() macros)
class ElfParserGlobalSetup {
public:
    ElfParserGlobalSetup() {
        installGtestCrashHandler<ELF_TEST_NAME>();
    }
    ~ElfParserGlobalSetup() {
        restoreDefaultSignalHandlers();
    }
};

// Install global crash handler for all tests in this file
static ElfParserGlobalSetup global_setup;

TEST(Elf, readSymTable) {
    char cwd[PATH_MAX - 64];
    if (getcwd(cwd, sizeof(cwd)) == nullptr) {
        exit(1);    
    }
    char path[PATH_MAX];
    snprintf(path, sizeof(path) - 1, "%s/../build/test/resources/native-libs/unresolved-functions/main", cwd);
    if (access(path, R_OK) != 0) {
        fprintf(stdout, "Missing test resource %s. Skipping the test\n", path);
        exit(0);
    }
    CodeCache cc("test");
    ElfParser::parseFile(&cc, nullptr, path, false);
}

class ElfReladyn : public ::testing::Test {
  protected:
    Libraries* _libs = nullptr;
    CodeCache* _libreladyn = nullptr;

    // This method is called before each test.
    void SetUp() override {
        char cwd[PATH_MAX - 64];
        if (getcwd(cwd, sizeof(cwd)) == nullptr) {
            exit(1);
        }
        char path[PATH_MAX];
        snprintf(path, sizeof(path) - 1, "%s/../build/test/resources/native-libs/reladyn-lib/libreladyn.so", cwd);
        if (access(path, R_OK) != 0) {
            fprintf(stdout, "Missing test resource %s. Skipping the test\n", path);
            exit(0);
        }
        void* handle = dlopen(path, RTLD_NOW);
        ASSERT_THAT(handle, ::testing::NotNull());

        _libs = Libraries::instance();
        _libs->updateSymbols(false);
        _libreladyn = _libs->findLibraryByName("libreladyn");
        ASSERT_THAT(_libreladyn, ::testing::NotNull());
    }

    // This method is called after each test.
    void TearDown() override {
        // Clean up resources.
    }

    CodeCache* libreladyn() {
        return _libreladyn;
    }
};

TEST_F(ElfReladyn, resolveFromRela_plt) {
    void* sym = libreladyn()->findImport(im_pthread_create);
    ASSERT_THAT(sym, ::testing::NotNull());
}

TEST_F(ElfReladyn, resolveFromRela_dyn_R_GLOB_DAT) {
    void* sym = libreladyn()->findImport(im_pthread_setspecific);
    ASSERT_THAT(sym, ::testing::NotNull());
}

TEST_F(ElfReladyn, resolveFromRela_dyn_R_ABS64) {
    void* sym = libreladyn()->findImport(im_pthread_exit);
    ASSERT_THAT(sym, ::testing::NotNull());
}

class ElfTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset global or static state
        Symbols::clearParsingCaches();
    }

    void TearDown() override {
        // probably some free of the array cache to be done
    }
};


// Define an invalid ELF header
unsigned char invalidElfHeader[64] = {
    0x7f, 'E', 'L', 'F', // Correct magic number
    0x01,                // Invalid class (32-bit instead of 64-bit)
    0x01,                // Invalid data encoding (little-endian)
    0x01,                // Invalid version (original version of ELF)
    0,                   // OS/ABI
    0,                   // ABI version
    0, 0, 0, 0, 0, 0, 0 // Padding
    // Rest of the header can be zeroed out
};


TEST_F(ElfTest, invalidElf) {
    // Create an invalid ELF mapping
    const size_t headerSize = sizeof(invalidElfHeader);
    int fd = open("/tmp/invalid_elf", O_RDWR | O_CREAT | O_TRUNC, 0700); // Make the file executable
    ASSERT_NE(fd, -1) << "Failed to open temporary file";

    // Write the invalid ELF header to the file
    ssize_t written = write(fd, invalidElfHeader, headerSize);
    ASSERT_EQ(written, headerSize) << "Failed to write invalid ELF header";

    // Extend the file to a reasonable size
    int res = ftruncate(fd, 4096);
    ASSERT_EQ(res, 0) << "Failed to extend the file";

    // Memory map the file with PROT_EXEC
    void* addr = mmap(NULL, 4096, PROT_READ | PROT_EXEC, MAP_PRIVATE, fd, 0);
    ASSERT_NE(addr, MAP_FAILED) << "Failed to memory map the file";

    close(fd);

    // Set up the CodeCacheArray and other required structures
    CodeCacheArray cc_array;

    // Call the parsing function with the invalid ELF mapping
    Symbols::parseLibraries(&cc_array, false);

    munmap(addr, 4096);
    unlink("/tmp/invalid_elf");
}

// Additional test cases for other invalid ELF scenarios
TEST_F(ElfTest, nonElfFile) {
    // Create a non-ELF file mapping
    const char* nonElfContent = "This is not an ELF file";
    const size_t contentSize = strlen(nonElfContent) + 1;
    int fd = open("/tmp/non_elf", O_RDWR | O_CREAT | O_TRUNC, 0700); // Make the file executable
    ASSERT_NE(fd, -1) << "Failed to open temporary file";

    // Write the non-ELF content to the file
    ssize_t written = write(fd, nonElfContent, contentSize);
    ASSERT_EQ(written, contentSize) << "Failed to write non-ELF content";

    // Memory map the file with PROT_EXEC
    void* addr = mmap(NULL, contentSize, PROT_READ | PROT_EXEC, MAP_PRIVATE, fd, 0);
    ASSERT_NE(addr, MAP_FAILED) << "Failed to memory map the file";

    close(fd);

    // Set up the CodeCacheArray and other required structures
    CodeCacheArray cc_array;

    // Call the parsing function with the non-ELF mapping
    Symbols::parseLibraries(&cc_array, false);

    // we could add checks here, though I am mainly relying on asan to crash
    // if something is wrong
    munmap(addr, contentSize);
    unlink("/tmp/non_elf");
}

TEST_F(ElfTest, invalidElfSmallMapping) {
    // Create an invalid ELF mapping
    const size_t headerSize = sizeof(invalidElfHeader);
    int fd = open("/tmp/invalid_elf_small", O_RDWR | O_CREAT | O_TRUNC, 0700); // Make the file executable
    ASSERT_NE(fd, -1) << "Failed to open temporary file";

    // Write the invalid ELF header to the file
    ssize_t written = write(fd, invalidElfHeader, headerSize);
    ASSERT_EQ(written, headerSize) << "Failed to write invalid ELF header";

    // Memory map the file with a size smaller than the ELF header
    void* addr = mmap(NULL, 16, PROT_READ | PROT_EXEC, MAP_PRIVATE, fd, 0); // Map only 16 bytes
    ASSERT_NE(addr, MAP_FAILED) << "Failed to memory map the file";

    close(fd);

    // Set up the CodeCacheArray and other required structures
    CodeCacheArray cc_array;

    // Call the parsing function with the small invalid ELF mapping
    Symbols::parseLibraries(&cc_array, false);

    munmap(addr, 16);
    unlink("/tmp/invalid_elf_small");
}

TEST_F(ElfTest, nonElfFileSmallMapping) {
    // Create a non-ELF file mapping
    const char* nonElfContent = "Not ELF";
    const size_t contentSize = strlen(nonElfContent);
    int fd = open("/tmp/non_elf_small", O_RDWR | O_CREAT | O_TRUNC, 0700); // Make the file executable
    ASSERT_NE(fd, -1) << "Failed to open temporary file";

    // Write the non-ELF content to the file
    ssize_t written = write(fd, nonElfContent, contentSize);
    ASSERT_EQ(written, contentSize) << "Failed to write non-ELF content";

    // Memory map the file with a size smaller than expected
    void* addr = mmap(NULL, contentSize, PROT_READ | PROT_EXEC, MAP_PRIVATE, fd, 0); // Map only the content size
    ASSERT_NE(addr, MAP_FAILED) << "Failed to memory map the file";

    close(fd);

    // Set up the CodeCacheArray and other required structures
    CodeCacheArray cc_array;

    // Call the parsing function with the small non-ELF mapping
    Symbols::parseLibraries(&cc_array, false);
    munmap(addr, contentSize);
    unlink("/tmp/non_elf_small");
}

class ElfTestParam : public ::testing::TestWithParam<int> {
protected:
    void SetUp() override {
        // Reset global or static state
        Symbols::clearParsingCaches();
    }

    void TearDown() override {
        // probably some free of the array cache to be done
    }
};


#ifdef UNMAP_DOES_NOT_CRASH // for now we only have a lock on dl_close. unmapping will still crash
// This test does not repro 100% of the time.
// However over a few runs, I get it to reproduce the race condition.
TEST_P(ElfTestParam, invalidElfSmallMappingAfterUnmap) {
    // This does not work as expected. There is a follow up to improve logging.
    Log::open("stderr", "WARN");
    // Create an invalid ELF mapping (it could be valid for this case, it is not relevant)
    const size_t headerSize = sizeof(invalidElfHeader);
    int fd = open("/tmp/invalid_elf_small_unmap", O_RDWR | O_CREAT | O_TRUNC, 0700); // Make the file executable
    ASSERT_NE(fd, -1) << "Failed to open temporary file";
    ssize_t written = write(fd, invalidElfHeader, headerSize);
    ASSERT_EQ(written, headerSize) << "Failed to write invalid ELF header";
    // Memory map the file
    void* addr = mmap(NULL, 16, PROT_READ | PROT_EXEC, MAP_PRIVATE, fd, 0); // Map only 16 bytes
    ASSERT_NE(addr, MAP_FAILED) << "Failed to memory map the file";

    close(fd);

    const char* base = static_cast<const char*>(addr);
    const char* end = base + 16;

    // Set up the CodeCacheArray and other required structures
    CodeCacheArray cc_array;
    int delay = GetParam();
    fprintf(stderr, "-- Test Delay = %d ms\n", delay);
    // Create a thread that will unmap the memory after X milliseconds
    // We need a timing that allows us to read the
    // mapping, but not loop over them in the parsing function
    // I was able to reproduce with ~15 ms in asan mode.
    std::thread unmapper([addr, delay]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        munmap(addr, 16);
        unlink("/tmp/invalid_elf_small_unmap");
    });

    // Call the parsing function in the main thread
    Symbols::parseLibraries(&cc_array, false);

    // Join the unmapper thread to ensure it has finished
    unmapper.join();
}

INSTANTIATE_TEST_SUITE_P(
    DelayedUnmapTest,
    ElfTestParam,
    ::testing::Range(3, 21) // This will test delays from 5 to 20 milliseconds inclusive
);

#else
TEST_P(ElfTestParam, invalidElfSmallMappingAfterUnmap) {
    char cwd[PATH_MAX - 64];
    if (getcwd(cwd, sizeof(cwd)) == nullptr) {
        exit(1);
    }

    // Configure logging (assuming Log is defined elsewhere)
    Log::open("stderr", "WARN");

    // Construct the path to the test resource
    char path[PATH_MAX];
    snprintf(path, sizeof(path) - 1, "%s/../build/test/resources/native-libs/small-lib/libsmall-lib.so", cwd);
    if (access(path, R_OK) != 0) {
        fprintf(stdout, "Missing test resource %s. Skipping the test\n", path);
        exit(1);
    }
    void* handle = dlopen(path, RTLD_NOW);
    if (!handle) {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        exit(1);
    }

    CodeCacheArray cc_array;
    int delay = GetParam();
    fprintf(stderr, "-- Test Delay = %d ms\n", delay);

    // Create a thread that will unmap (close) the shared library after a delay
    std::thread unmapper([handle, delay]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        // Unload the shared library using dlclose
        dlclose(handle);
    });

    // Call the parsing function in the main thread, this is where we can crash
    Symbols::parseLibraries(&cc_array, false);
    unmapper.join();
}

INSTANTIATE_TEST_SUITE_P(
    DelayedUnmapTest,
    ElfTestParam,
    ::testing::Range(3, 21) // This will test delays from 5 to 20 milliseconds inclusive
);
#endif
#endif //__linux__