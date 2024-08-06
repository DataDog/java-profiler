#ifdef __linux__

#include <gtest/gtest.h>

#include "codeCache.h"
#include "symbols_linux.h"

#include <unistd.h>
#include <limits.h> // For PATH_MAX

#include <fcntl.h>
#include <sys/mman.h>
#include <cstring>
#include <chrono>
#include <thread>

TEST(Elf, readSymTable) {
    char cwd[PATH_MAX - 64];
    if (getcwd(cwd, sizeof(cwd)) == nullptr) {
        exit(1);
    }
    char path[PATH_MAX];
    snprintf(path, sizeof(path) - 1, "%s/../build/test/resources/unresolved-functions/main", cwd);
    if (access(path, R_OK) != 0) {
        fprintf(stdout, "Missing test resource %s. Skipping the test\n", path);
        exit(0);
    }
    CodeCache cc("test");
    ElfParser::parseFile(&cc, nullptr, path, false);
    fprintf(stdout, "CodeCache size: %d\n", cc.count());
}

class ElfTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset global or static state
        Symbols::clear_parsed_caches();
    }

    void TearDown() override {
        // Clean up if necessary
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
    ftruncate(fd, 4096);

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
    Symbols::clear_parsed_caches();
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
    Symbols::clear_parsed_caches();
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
    Symbols::clear_parsed_caches();
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
    Symbols::clear_parsed_caches();
}

TEST_F(ElfTest, invalidElfSmallMappingAfterUnmap) {
    // Create an invalid ELF mapping
    const size_t headerSize = sizeof(invalidElfHeader);
    int fd = open("/tmp/invalid_elf_small_unmap", O_RDWR | O_CREAT | O_TRUNC, 0700); // Make the file executable
    ASSERT_NE(fd, -1) << "Failed to open temporary file";

    // Write the invalid ELF header to the file
    ssize_t written = write(fd, invalidElfHeader, headerSize);
    ASSERT_EQ(written, headerSize) << "Failed to write invalid ELF header";

    // Memory map the file with a size smaller than the ELF header
    void* addr = mmap(NULL, 16, PROT_READ | PROT_EXEC, MAP_PRIVATE, fd, 0); // Map only 16 bytes
    ASSERT_NE(addr, MAP_FAILED) << "Failed to memory map the file";

    close(fd);

    const char* base = static_cast<const char*>(addr);
    const char* end = base + 16;

    // Set up the CodeCacheArray and other required structures
    CodeCacheArray cc_array;
    CodeCache* cc = new CodeCache("/tmp/invalid_elf_small_unmap", 0, false, base, end);

#ifdef MANUAL
    // Call the parsing function
    Symbols::parseLibraries(&cc_array, false);

    // Unmap the memory
    munmap(addr, 16);
    unlink("/tmp/invalid_elf_small_unmap");

    // Manually call parseProgramHeaders after unmapping to force a crash
    ElfParser::parseProgramHeaders(cc, base, end, true);
#else
    // Create a thread that will unmap the memory after 1 milliseconds
    // this is hard, because we need a timing that allows us to read the 
    // mapping, but not loop over them in the parsing function
    // I was able to reproduce with 15 ms.
    // maybe this should range from 5 to 20ms.
    std::thread unmapper([addr]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
        munmap(addr, 16);
        unlink("/tmp/invalid_elf_small_unmap");
    });
    // Call the parsing function in the main thread
    Symbols::parseLibraries(&cc_array, false);

    // Join the unmapper thread to ensure it has finished
    unmapper.join();
#endif
    delete cc;
}

#endif //__linux__