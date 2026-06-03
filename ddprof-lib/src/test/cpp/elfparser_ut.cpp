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
#include <cstdlib>
#include <vector>
#include <elf.h>
#include <chrono>
#include <thread>

#include <dlfcn.h>
#include <link.h>
#include <signal.h>
#include <unistd.h>
#include <cstdio>

// Forward declaration for ElfParser functionality from symbols_linux.cpp
// The actual implementation will be available through the patched upstream file
class ElfParser {
public:
    static bool parseFile(CodeCache* cc, const char* base, const char* file_name, bool use_debug);
};

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

// =====================================================================
// Regression tests for the ELF parser hardening (found by the fuzz_elf
// harness). Each builds a minimal ELF whose single malformed field made the
// pre-hardening parser read out of bounds. On the hardened parser they must
// return cleanly: the global crash handler installed above turns any wild or
// out-of-bounds access back into a gtest failure, so a regression fails CI.
//
// The exact byte layouts were confirmed to crash the pre-fix parser
// (ASan SEGV / heap-buffer-overflow) and to pass after the fix.
// =====================================================================

namespace {

// Minimal valid ELF64 header; callers set the malformed field afterwards.
Elf64_Ehdr validEhdr() {
    Elf64_Ehdr e;
    memset(&e, 0, sizeof(e));
    e.e_ident[EI_MAG0] = ELFMAG0;
    e.e_ident[EI_MAG1] = ELFMAG1;
    e.e_ident[EI_MAG2] = ELFMAG2;
    e.e_ident[EI_MAG3] = ELFMAG3;
    e.e_ident[EI_CLASS] = ELFCLASS64;
    e.e_ident[EI_DATA] = ELFDATA2LSB;
    e.e_ident[EI_VERSION] = EV_CURRENT;
    e.e_type = ET_DYN;
    e.e_machine = EM_X86_64;
    e.e_version = EV_CURRENT;
    e.e_ehsize = sizeof(Elf64_Ehdr);
    e.e_shstrndx = 1;  // non-zero so validHeader() accepts the image
    return e;
}

// Write the bytes to a unique temp file and run ElfParser::parseFile over it,
// mirroring how Symbols::parseLibraries() parses an on-disk library.
void parseElfBytes(const std::vector<char>& bytes) {
    char path[] = "/tmp/elf_regress_XXXXXX";
    int fd = mkstemp(path);
    ASSERT_NE(fd, -1);
    ssize_t written = write(fd, bytes.data(), bytes.size());
    close(fd);
    if (written != (ssize_t)bytes.size()) {
        unlink(path);
        FAIL() << "short write to " << path;
        return;
    }
    CodeCache cc("regress");
    ElfParser::parseFile(&cc, nullptr, path, /*use_debug=*/false);
    unlink(path);
}

}  // namespace

// Regression test for the build-id parser hardening (found by fuzz_elf).
// extractBuildIdFromMemory()'s `p_offset + p_filesz` bounds check could
// overflow, letting findBuildIdInNotes() walk a PT_NOTE past the buffer. The
// buffer is heap-allocated and sized exactly so ASan's redzone catches the
// over-read deterministically. The hardened parser must return cleanly.
TEST(ElfBuildId, noteOffsetOverflow) {
    Elf64_Ehdr e = validEhdr();
    e.e_phoff = sizeof(Elf64_Ehdr);
    e.e_phentsize = sizeof(Elf64_Phdr);
    e.e_phnum = 1;

    Elf64_Phdr p;
    memset(&p, 0, sizeof(p));
    p.p_type = PT_NOTE;
    p.p_offset = 0x70;                            // inside the buffer
    p.p_filesz = static_cast<uint64_t>(8) - p.p_offset;  // sum wraps to 8 (< size)

    const size_t size = sizeof(e) + sizeof(p);    // 120 bytes
    char* buf = new char[size];                   // exact size -> redzone right after
    memcpy(buf, &e, sizeof(e));
    memcpy(buf + sizeof(e), &p, sizeof(p));

    size_t build_id_len = 0;
    char* id = SymbolsLinux::extractBuildIdFromMemory(buf, size, &build_id_len);
    free(id);  // hardened parser returns nullptr; the point is that it must not crash
    delete[] buf;
}

// e_shoff pointing far outside the image made findSection() dereference a wild
// section-header pointer (ElfParser::at). 16 TB is reliably unmapped.
TEST_F(ElfTest, sectionHeaderOffsetOutOfBounds) {
    Elf64_Ehdr e = validEhdr();
    e.e_shoff = 0x100000000000ULL;  // 16 TB past a 64-byte file
    e.e_shentsize = sizeof(Elf64_Shdr);
    e.e_shnum = 3;
    e.e_shstrndx = 1;
    std::vector<char> bytes(reinterpret_cast<char*>(&e),
                            reinterpret_cast<char*>(&e) + sizeof(e));
    parseElfBytes(bytes);  // must not crash
}

// A .symtab whose sh_size claims 256 MB in a tiny file made loadSymbolTable()
// walk the symbol table off the end of the mapping.
TEST_F(ElfTest, symbolTableSizeOutOfBounds) {
    const uint16_t NSEC = 4;
    const uint64_t shoff = sizeof(Elf64_Ehdr);
    const uint64_t shstr_off = shoff + NSEC * sizeof(Elf64_Shdr);
    // Section-header string table: names at offsets 1, 9, 17.
    const char shstrtab[] = "\0.symtab\0.strtab\0.shstrtab";
    const uint64_t sym_off = shstr_off + sizeof(shstrtab);
    Elf64_Sym sym;
    memset(&sym, 0, sizeof(sym));
    sym.st_name = 1;
    sym.st_value = 0x1000;
    const uint64_t str_off = sym_off + sizeof(sym);
    const char strtab[] = "\0main";

    Elf64_Ehdr e = validEhdr();
    e.e_shoff = shoff;
    e.e_shentsize = sizeof(Elf64_Shdr);
    e.e_shnum = NSEC;
    e.e_shstrndx = 3;

    Elf64_Shdr sh[4];
    memset(sh, 0, sizeof(sh));
    sh[1].sh_name = 1;  // ".symtab"
    sh[1].sh_type = SHT_SYMTAB;
    sh[1].sh_offset = sym_off;
    sh[1].sh_size = 0x10000000;  // 256 MB: far past the file
    sh[1].sh_link = 2;
    sh[1].sh_entsize = sizeof(Elf64_Sym);
    sh[2].sh_name = 9;  // ".strtab"
    sh[2].sh_type = SHT_STRTAB;
    sh[2].sh_offset = str_off;
    sh[2].sh_size = sizeof(strtab);
    sh[3].sh_name = 17;  // ".shstrtab"
    sh[3].sh_type = SHT_STRTAB;
    sh[3].sh_offset = shstr_off;
    sh[3].sh_size = sizeof(shstrtab);

    std::vector<char> b;
    auto app = [&](const void* p, size_t n) {
        const char* c = static_cast<const char*>(p);
        b.insert(b.end(), c, c + n);
    };
    app(&e, sizeof(e));
    app(sh, sizeof(sh));
    app(shstrtab, sizeof(shstrtab));
    app(&sym, sizeof(sym));
    app(strtab, sizeof(strtab));
    parseElfBytes(b);  // must not crash
}

// A large e_phoff causes phdrAt() to try forming a pointer past the image.
// The bounds check must reject it before any dereference.
TEST_F(ElfTest, programHeaderOffsetOutOfBounds) {
    Elf64_Ehdr e = validEhdr();
    e.e_phoff = 0x100000000000ULL;  // 16 TB: reliably unmapped
    e.e_phentsize = sizeof(Elf64_Phdr);
    e.e_phnum = 1;
    std::vector<char> bytes(reinterpret_cast<char*>(&e),
                            reinterpret_cast<char*>(&e) + sizeof(e));
    parseElfBytes(bytes);  // must not crash
}

// strAt() bounds check: a symbol whose st_name equals strtab_size (one past
// the end) must be skipped without reading out of bounds.
TEST_F(ElfTest, symbolNameOffsetOutOfBounds) {
    const uint16_t NSEC = 4;
    const uint64_t shoff = sizeof(Elf64_Ehdr);
    const uint64_t shstr_off = shoff + NSEC * sizeof(Elf64_Shdr);
    const char shstrtab[] = "\0.symtab\0.strtab\0.shstrtab";
    const uint64_t sym_off = shstr_off + sizeof(shstrtab);
    Elf64_Sym sym;
    memset(&sym, 0, sizeof(sym));
    sym.st_name = 6;  // == sizeof(strtab) below: one past the end
    sym.st_value = 0x1000;
    sym.st_size = 4;
    const uint64_t str_off = sym_off + sizeof(sym);
    const char strtab[] = "\0main\0";  // 6 bytes; index 6 is out of bounds

    Elf64_Ehdr e = validEhdr();
    e.e_shoff = shoff;
    e.e_shentsize = sizeof(Elf64_Shdr);
    e.e_shnum = NSEC;
    e.e_shstrndx = 3;

    Elf64_Shdr sh[4];
    memset(sh, 0, sizeof(sh));
    sh[1].sh_name = 1;   // ".symtab"
    sh[1].sh_type = SHT_SYMTAB;
    sh[1].sh_offset = sym_off;
    sh[1].sh_size = sizeof(sym);  // exactly one entry, within image
    sh[1].sh_link = 2;
    sh[1].sh_entsize = sizeof(Elf64_Sym);
    sh[2].sh_name = 9;   // ".strtab"
    sh[2].sh_type = SHT_STRTAB;
    sh[2].sh_offset = str_off;
    sh[2].sh_size = sizeof(strtab);
    sh[3].sh_name = 17;  // ".shstrtab"
    sh[3].sh_type = SHT_STRTAB;
    sh[3].sh_offset = shstr_off;
    sh[3].sh_size = sizeof(shstrtab);

    std::vector<char> b;
    auto app = [&](const void* p, size_t n) {
        const char* c = static_cast<const char*>(p);
        b.insert(b.end(), c, c + n);
    };
    app(&e, sizeof(e));
    app(sh, sizeof(sh));
    app(shstrtab, sizeof(shstrtab));
    app(&sym, sizeof(sym));
    app(strtab, sizeof(strtab));
    // strtab ends at image_size: also exercises inImage() equality case.
    parseElfBytes(b);  // must not crash: strAt() rejects st_name == strtab_size
}

#endif //__linux__
