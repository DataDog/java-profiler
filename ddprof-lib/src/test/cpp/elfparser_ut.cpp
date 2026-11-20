// Copyright 2026, Datadog, Inc
#ifdef __linux__

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "arch.h"
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
#include <memory>
#include <elf.h>
#include <chrono>
#include <thread>
#include <utility>

#include <dlfcn.h>
#include <link.h>
#include <signal.h>
#include <unistd.h>
#include <cstdio>

// Forward declaration for ElfParser functionality from symbols_linux.cpp
class ElfParser {
public:
    static void parseProgramHeaders(CodeCache* cc, const char* base, const char* end, bool relocate_dyn);
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

// Resolve a path under ddprof-lib/build/test/resources. The Gradle test task
// runs from the build directory, but the GitLab runner invokes binaries from
// the repo root, so a cwd-based lookup misses there; derive it from the
// executable, which is always three levels under ddprof-lib/build.
static bool findTestResource(const char* relative, char* out, size_t outSize) {
    char exe[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", exe, sizeof(exe) - 1);
    // readlink truncates silently at the buffer bound; a truncated path could
    // still resolve to a wrong existing directory, so refuse it.
    if (len <= 0 || (size_t)len >= sizeof(exe) - 1) {
        return false;
    }
    exe[len] = '\0';
    char* slash = strrchr(exe, '/');
    if (slash == nullptr) {
        return false;
    }
    *slash = '\0';
    int written = snprintf(out, outSize, "%s/../../../test/resources/%s", exe, relative);
    return written > 0 && (size_t)written < outSize && access(out, R_OK) == 0;
}

TEST(Elf, readSymTable) {
    char path[PATH_MAX];
    if (!findTestResource("native-libs/unresolved-functions/main", path, sizeof(path))) {
        GTEST_SKIP() << "Missing test resource native-libs/unresolved-functions/main";
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
        char path[PATH_MAX];
        if (!findTestResource("native-libs/reladyn-lib/libreladyn.so", path, sizeof(path))) {
            GTEST_SKIP() << "Missing test resource native-libs/reladyn-lib/libreladyn.so";
        }
        void* handle = dlopen(path, RTLD_NOW);
        ASSERT_THAT(handle, ::testing::NotNull());

        _libs = Libraries::instance();
        // Local-array parses also fill the global inode cache; rebuild the singleton independently.
        Symbols::clearParsingCaches();
        _libs->updateSymbols(false);
        _libreladyn = _libs->findLibraryByName("libreladyn");
        ASSERT_THAT(_libreladyn, ::testing::NotNull());
    }

    // This method is called after each test.
    void TearDown() override {
        if (_libs == nullptr) {
            return;  // SetUp skipped (missing resource): nothing was parsed
        }
        // parseLibraries skips inodes already in _parsed_inodes; clearing here
        // lets the next parse (a later SetUp or a local array) reparse them.
        Symbols::clearParsingCaches();
        _libs->freeNativeLibsForTest();
        _libreladyn = nullptr;  // freed above; a mid-test TearDown() must not leave it dangling
    }

    CodeCache* libreladyn() {
        return _libreladyn;
    }
};

TEST_F(ElfReladyn, resolveFromRela_plt) {
    void* sym = libreladyn()->findImport(im_pthread_create);
    ASSERT_THAT(sym, ::testing::NotNull());
}

// A local-array parse between fixture tests must not break the next SetUp
// reparse of the global library array.
TEST_F(ElfReladyn, reinitializeAfterLocalLibraryParse) {
    const u64 reladyn_file_id = libreladyn()->fileId();
    TearDown();

    {
        CodeCacheArray local_libraries;
        auto free_libraries = [](CodeCacheArray* libs) { libs->freeForTest(); };
        std::unique_ptr<CodeCacheArray, decltype(free_libraries)> cleanup(&local_libraries, free_libraries);
        Symbols::parseLibraries(&local_libraries, false);

        bool parsed_reladyn = false;
        for (int i = 0; i < local_libraries.count(); i++) {
            CodeCache* lib = local_libraries[i];
            if (lib != nullptr && lib->fileId() == reladyn_file_id) {
                parsed_reladyn = true;
                break;
            }
        }
        ASSERT_TRUE(parsed_reladyn);
    }

    ASSERT_NO_FATAL_FAILURE(SetUp());
    ASSERT_THAT(libreladyn()->findImport(im_pthread_create), ::testing::NotNull());
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

    // The binary's own mapping is always collected and parsed.
    const int parsed = cc_array.count();
    cc_array.freeForTest();
    EXPECT_GT(parsed, 0);

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

    const int parsed = cc_array.count();
    cc_array.freeForTest();
    EXPECT_GT(parsed, 0);

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

    const int parsed = cc_array.count();
    cc_array.freeForTest();
    EXPECT_GT(parsed, 0);

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
    const int parsed = cc_array.count();
    cc_array.freeForTest();
    EXPECT_GT(parsed, 0);
    munmap(addr, contentSize);
    unlink("/tmp/non_elf_small");
}

class ElfTestParam : public ::testing::TestWithParam<int> {
protected:
    void SetUp() override {
        // Reset global or static state
        Symbols::clearParsingCaches();
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

    const int parsed = cc_array.count();
    cc_array.freeForTest();
    EXPECT_GT(parsed, 0);
}

INSTANTIATE_TEST_SUITE_P(
    DelayedUnmapTest,
    ElfTestParam,
    ::testing::Range(3, 21) // This will test delays from 5 to 20 milliseconds inclusive
);

#else
TEST_P(ElfTestParam, invalidElfSmallMappingAfterUnmap) {
    char path[PATH_MAX];
    if (!findTestResource("native-libs/small-lib/libsmall-lib.so", path, sizeof(path))) {
        GTEST_SKIP() << "Missing test resource native-libs/small-lib/libsmall-lib.so";
    }

    // Configure logging (assuming Log is defined elsewhere)
    Log::open("stderr", "WARN");

    void* handle = dlopen(path, RTLD_NOW);
    if (!handle) {
        ADD_FAILURE() << "dlopen failed: " << dlerror();
        return;
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

    const int parsed = cc_array.count();
    cc_array.freeForTest();
    EXPECT_GT(parsed, 0);
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
// mirroring an on-disk library parse. The caller-visible CodeCache lets tests
// assert what the parser resolved.
void parseElfBytes(const std::vector<char>& bytes, CodeCache* cc, bool use_debug) {
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
    ElfParser::parseFile(cc, nullptr, path, use_debug);
    unlink(path);
}

void parseElfBytes(const std::vector<char>& bytes) {
    CodeCache cc("regress");
    parseElfBytes(bytes, &cc, /*use_debug=*/false);
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

// strAt() bounds check: symbols whose st_name is strtab_size (one past the end) or
// beyond must be skipped without reading out of bounds; an in-bounds name still loads.
TEST_F(ElfTest, symbolNameOffsetOutOfBounds) {
    const uint16_t NSEC = 4;
    const uint64_t shoff = sizeof(Elf64_Ehdr);
    const uint64_t shstr_off = shoff + NSEC * sizeof(Elf64_Shdr);
    const char shstrtab[] = "\0.symtab\0.strtab\0.shstrtab";
    const uint64_t sym_off = shstr_off + sizeof(shstrtab);
    const char strtab[] = "\0main";  // sizeof includes the literal's terminating NUL
    Elf64_Sym sym[3];
    memset(sym, 0, sizeof(sym));
    const uint32_t names[] = {1, sizeof(strtab), sizeof(strtab) + 1};  // "main", one past, beyond
    for (int i = 0; i < 3; i++) {
        sym[i].st_name = names[i];
        sym[i].st_value = 0x1000 * (i + 1);
        sym[i].st_size = 4;
        sym[i].st_shndx = 1;  // defined, so the filter does not drop it before strAt()
    }
    const uint64_t str_off = sym_off + sizeof(sym);

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
    sh[1].sh_size = sizeof(sym);  // within image
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
    app(sym, sizeof(sym));
    app(strtab, sizeof(strtab));
    // strtab ends at image_size: also exercises inImage() equality case.
    CodeCache cc("regress");
    ASSERT_NO_FATAL_FAILURE(parseElfBytes(b, &cc, /*use_debug=*/true));
    EXPECT_EQ(cc.findSymbol("main"), reinterpret_cast<const void*>(0x1000));  // table was read
    EXPECT_EQ(cc.count(), 1);  // strAt() rejected both out-of-bounds names
}

// Misaligned .symtab and .rela.plt must still resolve symbols and the PLT name.
// Only -fsanitize=alignment (asan config) catches a regression: arm64 and
// x86-64 perform the unaligned loads in hardware.
TEST_F(ElfTest, symbolTableMisalignedEntries) {
    const uint16_t NSEC = 6;
    const uint64_t shoff = sizeof(Elf64_Ehdr);
    const uint64_t shstr_off = shoff + NSEC * sizeof(Elf64_Shdr);
    const char shstrtab[] = "\0.symtab\0.strtab\0.shstrtab\0.plt\0.rela.plt";
    const uint64_t sym_off = shstr_off + sizeof(shstrtab);
    ASSERT_NE(sym_off % alignof(Elf64_Sym), 0u);  // layout must stay misaligned

    Elf64_Sym sym[2];
    memset(sym, 0, sizeof(sym));
    sym[0].st_name = 1;   // "mis_main"
    sym[0].st_value = 0x20000;
    sym[0].st_size = 4;
    sym[0].st_shndx = 1;  // defined, so the filter does not drop it
    sym[1].st_name = 10;  // "mis_helper"
    sym[1].st_value = 0x21000;
    sym[1].st_size = 4;
    sym[1].st_shndx = 1;
    const uint64_t str_off = sym_off + sizeof(sym);
    const char strtab[] = "\0mis_main\0mis_helper\0";  // 22 bytes: names at 1 and 10
    // 4 pad bytes push .rela.plt off its natural alignment too, so the
    // relocation entry read in addRelocationSymbols() is misaligned as well.
    const char rela_pad[4] = {0, 0, 0, 0};
    const uint64_t rela_off = str_off + sizeof(strtab) + sizeof(rela_pad);
    ASSERT_NE(rela_off % alignof(Elf64_Rela), 0u);
    Elf64_Rela rela;
    memset(&rela, 0, sizeof(rela));
    rela.r_offset = 0x4000;
    rela.r_info = ELF64_R_INFO(1, 1026);  // JUMP_SLOT-like; type is not interpreted

    Elf64_Ehdr e = validEhdr();
    e.e_shoff = shoff;
    e.e_shentsize = sizeof(Elf64_Shdr);
    e.e_shnum = NSEC;
    e.e_shstrndx = 3;

    Elf64_Shdr sh[6];
    memset(sh, 0, sizeof(sh));
    sh[1].sh_name = 1;   // ".symtab"
    sh[1].sh_type = SHT_SYMTAB;
    sh[1].sh_offset = sym_off;
    sh[1].sh_size = sizeof(sym);
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
    sh[4].sh_name = 27;  // ".plt"
    sh[4].sh_type = SHT_PROGBITS;
    sh[4].sh_addr = 0x3000;
    sh[4].sh_size = 32;
    sh[5].sh_name = 32;  // ".rela.plt"
    sh[5].sh_type = SHT_RELA;
    sh[5].sh_offset = rela_off;
    sh[5].sh_size = sizeof(rela);
    sh[5].sh_link = 1;
    sh[5].sh_entsize = sizeof(Elf64_Rela);

    std::vector<char> b;
    auto app = [&](const void* p, size_t n) {
        const char* c = static_cast<const char*>(p);
        b.insert(b.end(), c, c + n);
    };
    app(&e, sizeof(e));
    app(sh, sizeof(sh));
    app(shstrtab, sizeof(shstrtab));
    app(sym, sizeof(sym));
    app(strtab, sizeof(strtab));
    app(rela_pad, sizeof(rela_pad));
    app(&rela, sizeof(rela));

    CodeCache cc("regress");
    ASSERT_NO_FATAL_FAILURE(parseElfBytes(b, &cc, /*use_debug=*/true));
    // Both misaligned .symtab entries resolved at their st_value addresses.
    EXPECT_EQ(cc.findSymbol("mis_main"), (const void*)0x20000);
    EXPECT_EQ(cc.findSymbol("mis_helper"), (const void*)0x21000);
    // The PLT name came from the misaligned symbol-index lookup in
    // addRelocationSymbols(): symbol 1 resolves to "mis_helper@plt", placed at
    // the first stub after the PLT header.
    EXPECT_EQ(cc.findSymbol("mis_helper@plt"), (const void*)(0x3000 + PLT_HEADER_SIZE));
}

// Loaded image with misaligned .dynsym, .rela.plt and .rela.dyn: both imports
// must resolve and both relocation tables must be hashed into the fingerprint.
// As above, only the asan config catches an alignment regression.
TEST_F(ElfTest, dynamicSectionMisalignedEntries) {
#if defined(__x86_64__)
    const uint32_t glob_dat = R_X86_64_GLOB_DAT;
#elif defined(__aarch64__)
    const uint32_t glob_dat = R_AARCH64_GLOB_DAT;
#else
    GTEST_SKIP() << "R_GLOB_DAT imports are only recorded on x86-64 and aarch64";
    const uint32_t glob_dat = 0;
#endif
    const size_t IMAGE_SIZE = 4096;
    const uint64_t GOT_PLT_SLOT = 0x800;
    const uint64_t GOT_DAT_SLOT = 0x808;
    const int NPH = 2;
    const int NDYN = 10;

    const uint64_t ph_off = sizeof(Elf64_Ehdr);
    const uint64_t dyn_off = ph_off + NPH * sizeof(Elf64_Phdr);  // ElfDyn stays aligned
    const char strtab[] = "\0pthread_create\0pthread_setspecific";  // names at 1 and 16
    const uint64_t str_off = dyn_off + NDYN * sizeof(Elf64_Dyn);
    const uint64_t sym_off = str_off + sizeof(strtab);
    const uint64_t jmprel_off = sym_off + 3 * sizeof(Elf64_Sym);
    const uint64_t rela_off = jmprel_off + sizeof(Elf64_Rela);
    ASSERT_LE(rela_off + sizeof(Elf64_Rela), GOT_PLT_SLOT);
    // Layout must stay misaligned for every table under test.
    ASSERT_NE(sym_off % alignof(Elf64_Sym), 0u);
    ASSERT_NE(jmprel_off % alignof(Elf64_Rela), 0u);
    ASSERT_NE(rela_off % alignof(Elf64_Rela), 0u);

    // The image itself must be aligned so only the table offsets misalign.
    std::unique_ptr<void, decltype(&free)> mem(aligned_alloc(IMAGE_SIZE, IMAGE_SIZE), &free);
    ASSERT_THAT(mem.get(), ::testing::NotNull());
    char* image = static_cast<char*>(mem.get());
    memset(image, 0, IMAGE_SIZE);

    Elf64_Ehdr e = validEhdr();
    e.e_phoff = ph_off;
    e.e_phentsize = sizeof(Elf64_Phdr);
    e.e_phnum = NPH;
    memcpy(image, &e, sizeof(e));

    Elf64_Phdr ph[NPH];
    memset(ph, 0, sizeof(ph));
    ph[0].p_type = PT_LOAD;
    ph[0].p_filesz = IMAGE_SIZE;
    ph[0].p_memsz = IMAGE_SIZE;
    ph[1].p_type = PT_DYNAMIC;
    ph[1].p_vaddr = dyn_off;
    ph[1].p_offset = dyn_off;
    ph[1].p_filesz = NDYN * sizeof(Elf64_Dyn);
    ph[1].p_memsz = NDYN * sizeof(Elf64_Dyn);
    memcpy(image + ph_off, ph, sizeof(ph));

    // Unrelocated (vaddr) d_ptr values, as musl leaves them; both parsers
    // rebase pointers that fall below the image.
    const Elf64_Dyn dyn[NDYN] = {
        {DT_SYMTAB, {sym_off}},
        {DT_STRTAB, {str_off}},
        {DT_SYMENT, {sizeof(Elf64_Sym)}},
        {DT_STRSZ, {sizeof(strtab)}},
        {DT_JMPREL, {jmprel_off}},
        {DT_PLTRELSZ, {sizeof(Elf64_Rela)}},
        {DT_RELA, {rela_off}},
        {DT_RELASZ, {sizeof(Elf64_Rela)}},
        {DT_RELAENT, {sizeof(Elf64_Rela)}},
        {DT_NULL, {0}},
    };
    memcpy(image + dyn_off, dyn, sizeof(dyn));
    memcpy(image + str_off, strtab, sizeof(strtab));

    Elf64_Sym sym[3];
    memset(sym, 0, sizeof(sym));
    sym[1].st_name = 1;   // "pthread_create"
    sym[2].st_name = 16;  // "pthread_setspecific"
    memcpy(image + sym_off, sym, sizeof(sym));

    Elf64_Rela jmprel;
    memset(&jmprel, 0, sizeof(jmprel));
    jmprel.r_offset = GOT_PLT_SLOT;
    jmprel.r_info = ELF64_R_INFO(1, 0);  // .rela.plt entries are not type-checked
    memcpy(image + jmprel_off, &jmprel, sizeof(jmprel));

    Elf64_Rela rela;
    memset(&rela, 0, sizeof(rela));
    rela.r_offset = GOT_DAT_SLOT;
    rela.r_info = ELF64_R_INFO(2, glob_dat);
    memcpy(image + rela_off, &rela, sizeof(rela));

    CodeCache cc("inmem");
    ElfParser::parseProgramHeaders(&cc, image, image + IMAGE_SIZE, /*relocate_dyn=*/false);

    // parseDynamicSection(): both misaligned relocations resolved their
    // misaligned symbols and recorded the GOT slot they name.
    EXPECT_EQ(cc.peekImport(im_pthread_create), (void**)(image + GOT_PLT_SLOT));
    EXPECT_EQ(cc.peekImport(im_pthread_setspecific), (void**)(image + GOT_DAT_SLOT));

    // hashSymbolRelocations(): a fingerprint of 0 means a table was rejected.
    const Elf64_Phdr* phdrs = reinterpret_cast<const Elf64_Phdr*>(image + ph_off);
    const u64 fingerprint = Symbols::imageFingerprint(phdrs, NPH, (uintptr_t)image);
    EXPECT_NE(fingerprint, 0u);
    EXPECT_EQ(cc.imageFingerprint(), fingerprint);

    // Both misaligned relocation tables are part of the hash: moving either
    // entry's GOT slot must change the fingerprint.
    jmprel.r_offset = GOT_PLT_SLOT + 2 * sizeof(void*);
    memcpy(image + jmprel_off, &jmprel, sizeof(jmprel));
    const u64 plt_moved = Symbols::imageFingerprint(phdrs, NPH, (uintptr_t)image);
    EXPECT_NE(plt_moved, 0u);
    EXPECT_NE(plt_moved, fingerprint);

    rela.r_offset = GOT_DAT_SLOT + 2 * sizeof(void*);
    memcpy(image + rela_off, &rela, sizeof(rela));
    const u64 both_moved = Symbols::imageFingerprint(phdrs, NPH, (uintptr_t)image);
    EXPECT_NE(both_moved, 0u);
    EXPECT_NE(both_moved, plt_moved);

    // DT_RELASZ ends 8 bytes into a second entry whose GLOB_DAT r_info lies past
    // the table; the in-table entry is not a GLOB_DAT, so any recorded import
    // means the walk read past DT_RELASZ.
    const int RELASZ_INDEX = 7;
    ASSERT_EQ(dyn[RELASZ_INDEX].d_tag, DT_RELASZ);
    ASSERT_LE(rela_off + sizeof(Elf64_Rela) + sizeof(Elf64_Rel), GOT_PLT_SLOT);
    Elf64_Dyn truncated = {DT_RELASZ, {sizeof(Elf64_Rela) + sizeof(uint64_t)}};
    memcpy(image + dyn_off + RELASZ_INDEX * sizeof(Elf64_Dyn), &truncated, sizeof(truncated));
    rela.r_info = 0;
    memcpy(image + rela_off, &rela, sizeof(rela));
    Elf64_Rel stray;
    stray.r_offset = GOT_DAT_SLOT;
    stray.r_info = ELF64_R_INFO(2, glob_dat);
    memcpy(image + rela_off + sizeof(Elf64_Rela), &stray, sizeof(stray));
    CodeCache truncated_cc("truncated");
    ElfParser::parseProgramHeaders(&truncated_cc, image, image + IMAGE_SIZE, /*relocate_dyn=*/false);
    EXPECT_EQ(truncated_cc.peekImport(im_pthread_setspecific), nullptr);
}

// An undersized, a near-SIZE_MAX, and a table-truncating DT_RELAENT/PLTRELSZ:
// no walk may read an entry that does not fit in the table, record imports the
// fingerprint skips, or wrap its offset back before the table.
TEST_F(ElfTest, dynamicSectionInvalidRelocationEntrySize) {
    const size_t IMAGE_SIZE = 4096;
    const uint64_t GOT_PLT_SLOT = 0x800;
    const int NPH = 2;
    const int NDYN = 8;

    const uint64_t ph_off = sizeof(Elf64_Ehdr);
    const uint64_t dyn_off = ph_off + NPH * sizeof(Elf64_Phdr);
    const char strtab[] = "\0pthread_create";
    const uint64_t str_off = dyn_off + NDYN * sizeof(Elf64_Dyn);
    const uint64_t sym_off = (str_off + sizeof(strtab) + 7) & ~(uint64_t)7;
    const uint64_t jmprel_off = sym_off + 2 * sizeof(Elf64_Sym);
    // Room for a full entry plus the 16 bytes the truncated-table case reads.
    ASSERT_LE(jmprel_off + sizeof(Elf64_Rela) + sizeof(Elf64_Rel), GOT_PLT_SLOT);

    std::unique_ptr<void, decltype(&free)> mem(aligned_alloc(IMAGE_SIZE, IMAGE_SIZE), &free);
    ASSERT_THAT(mem.get(), ::testing::NotNull());
    char* image = static_cast<char*>(mem.get());
    memset(image, 0, IMAGE_SIZE);

    Elf64_Ehdr e = validEhdr();
    e.e_phoff = ph_off;
    e.e_phentsize = sizeof(Elf64_Phdr);
    e.e_phnum = NPH;
    memcpy(image, &e, sizeof(e));

    Elf64_Phdr ph[NPH];
    memset(ph, 0, sizeof(ph));
    ph[0].p_type = PT_LOAD;
    ph[0].p_filesz = IMAGE_SIZE;
    ph[0].p_memsz = IMAGE_SIZE;
    ph[1].p_type = PT_DYNAMIC;
    ph[1].p_vaddr = dyn_off;
    ph[1].p_offset = dyn_off;
    ph[1].p_filesz = NDYN * sizeof(Elf64_Dyn);
    ph[1].p_memsz = NDYN * sizeof(Elf64_Dyn);
    memcpy(image + ph_off, ph, sizeof(ph));

    const int PLTRELSZ_INDEX = 5;
    const int RELAENT_INDEX = 6;
    const Elf64_Dyn dyn[NDYN] = {
        {DT_SYMTAB, {sym_off}},
        {DT_STRTAB, {str_off}},
        {DT_SYMENT, {sizeof(Elf64_Sym)}},
        {DT_STRSZ, {sizeof(strtab)}},
        {DT_JMPREL, {jmprel_off}},
        {DT_PLTRELSZ, {sizeof(Elf64_Rela)}},  // PLTRELSZ_INDEX
        {DT_RELAENT, {8}},  // RELAENT_INDEX: half an Elf64_Rel
        {DT_NULL, {0}},
    };
    memcpy(image + dyn_off, dyn, sizeof(dyn));
    memcpy(image + str_off, strtab, sizeof(strtab));

    Elf64_Sym sym[2];
    memset(sym, 0, sizeof(sym));
    sym[1].st_name = 1;  // "pthread_create"
    // The last 8 bytes before .rela.plt. Read as an r_info by a relocation walk
    // that wraps back before the table, they name symbol 0xffffffff, which lies
    // outside the image (see the huge-stride case below).
    sym[1].st_size = 0xffffffff00000000ULL;
    memcpy(image + sym_off, sym, sizeof(sym));

    // A well-formed entry: with the 8-byte stride the first iteration still
    // reads it whole, so only the entry-size check keeps it out.
    Elf64_Rela jmprel;
    memset(&jmprel, 0, sizeof(jmprel));
    jmprel.r_offset = GOT_PLT_SLOT;
    jmprel.r_info = ELF64_R_INFO(1, 0);
    memcpy(image + jmprel_off, &jmprel, sizeof(jmprel));

    {
        CodeCache cc("undersized");
        ElfParser::parseProgramHeaders(&cc, image, image + IMAGE_SIZE, /*relocate_dyn=*/false);
        EXPECT_EQ(cc.peekImport(im_pthread_create), nullptr);
    }

    // No entry fits, so nothing is recorded. A walk that wraps back before the
    // table meets the index planted in sym[1].st_size and yields fingerprint 0.
    Elf64_Dyn huge_relent = {DT_RELAENT, {SIZE_MAX - 7}};
    memcpy(image + dyn_off + RELAENT_INDEX * sizeof(Elf64_Dyn), &huge_relent, sizeof(huge_relent));
    {
        CodeCache cc("huge");
        ElfParser::parseProgramHeaders(&cc, image, image + IMAGE_SIZE, /*relocate_dyn=*/false);
        EXPECT_EQ(cc.peekImport(im_pthread_create), nullptr);
        EXPECT_NE(cc.imageFingerprint(), 0u);
    }

    // DT_PLTRELSZ ends 8 bytes into a second entry whose r_info lies past the
    // table; the in-table entry names no symbol, so any recorded import means
    // the walk read past DT_PLTRELSZ.
    Elf64_Dyn relaent = {DT_RELAENT, {sizeof(Elf64_Rela)}};
    Elf64_Dyn truncated = {DT_PLTRELSZ, {sizeof(Elf64_Rela) + sizeof(uint64_t)}};
    memcpy(image + dyn_off + RELAENT_INDEX * sizeof(Elf64_Dyn), &relaent, sizeof(relaent));
    memcpy(image + dyn_off + PLTRELSZ_INDEX * sizeof(Elf64_Dyn), &truncated, sizeof(truncated));
    jmprel.r_info = 0;
    memcpy(image + jmprel_off, &jmprel, sizeof(jmprel));
    Elf64_Rel stray;
    stray.r_offset = GOT_PLT_SLOT;
    stray.r_info = ELF64_R_INFO(1, 0);
    memcpy(image + jmprel_off + sizeof(Elf64_Rela), &stray, sizeof(stray));
    {
        CodeCache cc("truncated");
        ElfParser::parseProgramHeaders(&cc, image, image + IMAGE_SIZE, /*relocate_dyn=*/false);
        EXPECT_EQ(cc.peekImport(im_pthread_create), nullptr);
    }
}

// gABI "Symbol Values": TLS offsets, absolute/common values, section and file
// entries and undefined symbols are not in-image definitions and must not become
// code-cache entries. The last regular index and SHN_XINDEX are kept.
TEST_F(ElfTest, symbolTableSkipsNonAddressSymbols) {
    const uint16_t NSEC = 4;
    const uint64_t shoff = sizeof(Elf64_Ehdr);
    const uint64_t shstr_off = shoff + NSEC * sizeof(Elf64_Shdr);
    const char shstrtab[] = "\0.symtab\0.strtab\0.shstrtab";
    const uint64_t sym_off = shstr_off + sizeof(shstrtab);
    const char strtab[] = "\0good_func\0tls_var\0abs_sym\0undef_stub\0common_sym\0sect_sym\0file_sym\0"
                          "last_regular\0xindex_sym\0loreserve_sym\0";
    enum { GOOD = 1, TLS = 11, ABS = 19, UNDEF = 27, COMMON = 38, SECT = 49, FILE_SYM = 58,
           LAST_REGULAR = 67, XINDEX = 80, LORESERVE = 91 };

    Elf64_Sym sym[10];
    memset(sym, 0, sizeof(sym));
    auto set = [&](int i, uint32_t name, unsigned char type, uint16_t shndx, uint64_t value) {
        sym[i].st_name = name;
        sym[i].st_info = ELF64_ST_INFO(STB_GLOBAL, type);
        sym[i].st_shndx = shndx;
        sym[i].st_value = value;
        sym[i].st_size = 4;
    };
    set(0, GOOD, STT_FUNC, 1, 0x20000);
    set(1, TLS, STT_TLS, 1, 0x8);
    set(2, ABS, STT_NOTYPE, SHN_ABS, 0x30000);
    set(3, UNDEF, STT_FUNC, SHN_UNDEF, 0x40000);
    set(4, COMMON, STT_OBJECT, SHN_COMMON, 0x10);
    set(5, SECT, STT_SECTION, 1, 0x50000);
    set(6, FILE_SYM, STT_FILE, 1, 0x60000);
    set(7, LAST_REGULAR, STT_FUNC, SHN_LORESERVE - 1, 0x70000);
    set(8, XINDEX, STT_FUNC, SHN_XINDEX, 0x80000);
    set(9, LORESERVE, STT_FUNC, SHN_LORESERVE, 0x90000);
    const uint64_t str_off = sym_off + sizeof(sym);

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
    sh[1].sh_size = sizeof(sym);
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
    app(sym, sizeof(sym));
    app(strtab, sizeof(strtab));

    CodeCache cc("regress");
    ASSERT_NO_FATAL_FAILURE(parseElfBytes(b, &cc, /*use_debug=*/true));
    EXPECT_EQ(cc.findSymbol("good_func"), reinterpret_cast<const void*>(0x20000));
    EXPECT_EQ(cc.findSymbol("last_regular"), reinterpret_cast<const void*>(0x70000));
    EXPECT_EQ(cc.findSymbol("xindex_sym"), reinterpret_cast<const void*>(0x80000));
    for (const char* name : {"tls_var", "abs_sym", "undef_stub", "common_sym", "sect_sym", "file_sym",
                             "loreserve_sym"}) {
        EXPECT_EQ(cc.findSymbol(name), nullptr) << name;
    }
}

namespace {

// An in-memory image whose PT_DYNAMIC holds exactly `dyn` (caller adds DT_NULL) and
// whose .rela.plt imports pthread_create into GOT slot PLT_SLOT; null on failure.
constexpr uint64_t PLT_SLOT = 0x800;
constexpr size_t DYN_IMAGE_SIZE = 4096;
constexpr int DYN_NPH = 2;
constexpr uint64_t DYN_OFF = sizeof(Elf64_Ehdr) + DYN_NPH * sizeof(Elf64_Phdr);
constexpr uint64_t DYN_MAX = 16;
constexpr uint64_t DYN_STR_OFF = DYN_OFF + DYN_MAX * sizeof(Elf64_Dyn);
constexpr uint64_t DYN_SYM_OFF = (DYN_STR_OFF + 32 + 7) & ~uint64_t(7);
constexpr uint64_t DYN_JMPREL_OFF = DYN_SYM_OFF + 2 * sizeof(Elf64_Sym);

std::unique_ptr<void, decltype(&free)> buildPltImage(const std::vector<Elf64_Dyn>& dyn) {
    std::unique_ptr<void, decltype(&free)> mem(aligned_alloc(DYN_IMAGE_SIZE, DYN_IMAGE_SIZE), &free);
    if (!mem || dyn.size() > DYN_MAX) return std::unique_ptr<void, decltype(&free)>(nullptr, &free);
    char* image = static_cast<char*>(mem.get());
    memset(image, 0, DYN_IMAGE_SIZE);

    Elf64_Ehdr e = validEhdr();
    e.e_phoff = sizeof(Elf64_Ehdr);
    e.e_phentsize = sizeof(Elf64_Phdr);
    e.e_phnum = DYN_NPH;
    memcpy(image, &e, sizeof(e));

    Elf64_Phdr ph[DYN_NPH];
    memset(ph, 0, sizeof(ph));
    ph[0].p_type = PT_LOAD;
    ph[0].p_filesz = DYN_IMAGE_SIZE;
    ph[0].p_memsz = DYN_IMAGE_SIZE;
    ph[1].p_type = PT_DYNAMIC;
    ph[1].p_vaddr = DYN_OFF;
    ph[1].p_offset = DYN_OFF;
    ph[1].p_filesz = dyn.size() * sizeof(Elf64_Dyn);
    ph[1].p_memsz = dyn.size() * sizeof(Elf64_Dyn);
    memcpy(image + sizeof(Elf64_Ehdr), ph, sizeof(ph));

    memcpy(image + DYN_OFF, dyn.data(), dyn.size() * sizeof(Elf64_Dyn));
    const char strtab[] = "\0pthread_create";
    memcpy(image + DYN_STR_OFF, strtab, sizeof(strtab));

    Elf64_Sym sym[2];
    memset(sym, 0, sizeof(sym));
    sym[1].st_name = 1;  // "pthread_create"
    memcpy(image + DYN_SYM_OFF, sym, sizeof(sym));

    Elf64_Rela rela;
    memset(&rela, 0, sizeof(rela));
    rela.r_offset = PLT_SLOT;
    rela.r_info = ELF64_R_INFO(1, 0);  // .rela.plt entries are not type-checked
    memcpy(image + DYN_JMPREL_OFF, &rela, sizeof(rela));
    return mem;
}

// The dynamic tags every PLT image needs, without any relocation entry-size tag.
std::vector<Elf64_Dyn> pltDyn() {
    return {
        {DT_SYMTAB, {DYN_SYM_OFF}},
        {DT_STRTAB, {DYN_STR_OFF}},
        {DT_SYMENT, {sizeof(Elf64_Sym)}},
        {DT_STRSZ, {sizeof("\0pthread_create")}},
        {DT_JMPREL, {DYN_JMPREL_OFF}},
        {DT_PLTRELSZ, {sizeof(Elf64_Rela)}},
        {DT_PLTREL, {DT_RELA}},
    };
}

// Fingerprints the image, moves the GOT slot of its one relocation entry, and
// fingerprints it again. Returns {before, after}.
std::pair<u64, u64> fingerprintAroundSlotMove(char* image) {
    const Elf64_Phdr* phdrs = reinterpret_cast<const Elf64_Phdr*>(image + sizeof(Elf64_Ehdr));
    const u64 before = Symbols::imageFingerprint(phdrs, DYN_NPH, reinterpret_cast<uintptr_t>(image));
    Elf64_Rela rela;
    memcpy(&rela, image + DYN_JMPREL_OFF, sizeof(rela));
    rela.r_offset = PLT_SLOT + 2 * sizeof(void*);
    memcpy(image + DYN_JMPREL_OFF, &rela, sizeof(rela));
    return {before, Symbols::imageFingerprint(phdrs, DYN_NPH, reinterpret_cast<uintptr_t>(image))};
}

void** parsedPthreadCreateImport(char* image) {
    CodeCache cc("inmem");
    ElfParser::parseProgramHeaders(&cc, image, image + DYN_IMAGE_SIZE, /*relocate_dyn=*/false);
    return cc.peekImport(im_pthread_create);
}

#if defined(__x86_64__)
constexpr uint32_t GLOB_DAT_TYPE = R_X86_64_GLOB_DAT;
#elif defined(__aarch64__)
constexpr uint32_t GLOB_DAT_TYPE = R_AARCH64_GLOB_DAT;
#else
constexpr uint32_t GLOB_DAT_TYPE = 0;  // tests using it skip
#endif

// An image whose only relocation table is the given .rela.dyn / .rel.dyn: one
// GLOB_DAT entry importing pthread_create (the buildPltImage() entry, whose leading
// r_offset and r_info read the same as an Elf64_Rel).
std::unique_ptr<void, decltype(&free)> buildGotImage(int64_t tag, int64_t size_tag, uint64_t size,
                                                     int64_t ent_tag, uint64_t ent,
                                                     int64_t count_tag, uint64_t count) {
    auto mem = buildPltImage({
        {DT_SYMTAB, {DYN_SYM_OFF}},
        {DT_STRTAB, {DYN_STR_OFF}},
        {DT_SYMENT, {sizeof(Elf64_Sym)}},
        {DT_STRSZ, {sizeof("\0pthread_create")}},
        {tag, {DYN_JMPREL_OFF}},
        {size_tag, {size}},
        {ent_tag, {ent}},
        {count_tag, {count}},
        {DT_NULL, {0}},
    });
    if (mem) {
        char* image = static_cast<char*>(mem.get());
        Elf64_Rela rela;
        memcpy(&rela, image + DYN_JMPREL_OFF, sizeof(rela));
        rela.r_info = ELF64_R_INFO(1, GLOB_DAT_TYPE);
        memcpy(image + DYN_JMPREL_OFF, &rela, sizeof(rela));
    }
    return mem;
}

}  // namespace

// gABI: a library with only PLT relocations has no DT_RELENT/DT_RELAENT; the
// DT_JMPREL entry size comes from DT_PLTREL. Its imports must still be recorded
// and be part of the image fingerprint.
TEST_F(ElfTest, pltOnlyImportsWithoutRelent) {
    auto mem = buildPltImage([] { auto d = pltDyn(); d.push_back({DT_NULL, {0}}); return d; }());
    ASSERT_THAT(mem.get(), ::testing::NotNull());
    char* image = static_cast<char*>(mem.get());

    EXPECT_EQ(parsedPthreadCreateImport(image), reinterpret_cast<void**>(image + PLT_SLOT));
    auto fp = fingerprintAroundSlotMove(image);
    EXPECT_NE(fp.first, 0u);
    EXPECT_NE(fp.second, fp.first);  // the PLT table is hashed
}

// DT_PLTREL fixes the DT_JMPREL stride: a conflicting DT_RELAENT too small for an
// entry (which would skip the table) must not override it, in the parse or the fingerprint.
TEST_F(ElfTest, pltRelOverridesRelaent) {
    auto dyn = pltDyn();
    dyn.push_back({DT_RELAENT, {8}});
    dyn.push_back({DT_NULL, {0}});
    auto mem = buildPltImage(dyn);
    ASSERT_THAT(mem.get(), ::testing::NotNull());
    char* image = static_cast<char*>(mem.get());

    EXPECT_EQ(parsedPthreadCreateImport(image), reinterpret_cast<void**>(image + PLT_SLOT));
    auto fp = fingerprintAroundSlotMove(image);
    EXPECT_NE(fp.first, 0u);
    EXPECT_NE(fp.second, fp.first);
}

// A relative-relocation count whose byte count wraps size_t (2^61 * 24 and
// 2^60 * 16 are 0 mod 2^64) must skip the whole .rela.dyn / .rel.dyn, not a
// wrapped-to-zero prefix, in the parse and the fingerprint.
TEST_F(ElfTest, relativeCountOverflowSkipsWholeTable) {
    if (GLOB_DAT_TYPE == 0) GTEST_SKIP() << "no GLOB_DAT relocation type for this architecture";
    struct Table {
        const char* name;
        int64_t tag, size_tag, ent_tag, count_tag;
        uint64_t ent, wrapping_count;
    };
    const Table tables[] = {
        {"rela", DT_RELA, DT_RELASZ, DT_RELAENT, DT_RELACOUNT, sizeof(Elf64_Rela), uint64_t(1) << 61},
        {"rel", DT_REL, DT_RELSZ, DT_RELENT, DT_RELCOUNT, sizeof(Elf64_Rel), uint64_t(1) << 60},
    };
    for (const Table& t : tables) {
        SCOPED_TRACE(t.name);
        // No relative prefix: the entry is an import.
        auto control = buildGotImage(t.tag, t.size_tag, t.ent, t.ent_tag, t.ent, t.count_tag, 0);
        ASSERT_THAT(control.get(), ::testing::NotNull());
        char* image = static_cast<char*>(control.get());
        EXPECT_EQ(parsedPthreadCreateImport(image), reinterpret_cast<void**>(image + PLT_SLOT));
        auto fp = fingerprintAroundSlotMove(image);
        EXPECT_NE(fp.first, 0u);
        EXPECT_NE(fp.second, fp.first);

        auto wrapped = buildGotImage(t.tag, t.size_tag, t.ent, t.ent_tag, t.ent, t.count_tag, t.wrapping_count);
        ASSERT_THAT(wrapped.get(), ::testing::NotNull());
        image = static_cast<char*>(wrapped.get());
        EXPECT_EQ(parsedPthreadCreateImport(image), nullptr);
        fp = fingerprintAroundSlotMove(image);
        EXPECT_NE(fp.first, 0u);
        EXPECT_EQ(fp.second, fp.first);  // the skipped entry is not hashed
    }
}

// A DT_RELAENT smaller than an Elf64_Rela on a DT_RELA table is invalid: the table
// is skipped in the parse and the fingerprint instead of walked at the wrong stride.
// sizeof(Elf64_Rela) itself is accepted (relativeCountOverflowSkipsWholeTable).
TEST_F(ElfTest, relaEntrySizeBelowElf64RelaSkipsTable) {
    if (GLOB_DAT_TYPE == 0) GTEST_SKIP() << "no GLOB_DAT relocation type for this architecture";
    for (uint64_t relaent : {sizeof(Elf64_Rel), sizeof(Elf64_Rela) - 1}) {
        SCOPED_TRACE(relaent);
        auto mem = buildGotImage(DT_RELA, DT_RELASZ, sizeof(Elf64_Rela), DT_RELAENT, relaent,
                                 DT_RELACOUNT, 0);
        ASSERT_THAT(mem.get(), ::testing::NotNull());
        char* image = static_cast<char*>(mem.get());
        EXPECT_EQ(parsedPthreadCreateImport(image), nullptr);
        auto fp = fingerprintAroundSlotMove(image);
        EXPECT_NE(fp.first, 0u);
        EXPECT_EQ(fp.second, fp.first);
    }
}

// Without DT_PLTREL, an invalid DT_RELAENT skips the PLT table rather than falling
// back to DT_RELENT, which would walk 24-byte RELA entries at a 16-byte stride.
TEST_F(ElfTest, pltFallbackRejectsInvalidRelaent) {
    auto dyn = pltDyn();
    dyn.pop_back();  // drop DT_PLTREL
    dyn.push_back({DT_RELAENT, {sizeof(Elf64_Rel)}});
    dyn.push_back({DT_RELENT, {sizeof(Elf64_Rel)}});
    dyn.push_back({DT_NULL, {0}});
    auto mem = buildPltImage(dyn);
    ASSERT_THAT(mem.get(), ::testing::NotNull());
    char* image = static_cast<char*>(mem.get());
    EXPECT_EQ(parsedPthreadCreateImport(image), nullptr);
    auto fp = fingerprintAroundSlotMove(image);
    EXPECT_NE(fp.first, 0u);
    EXPECT_EQ(fp.second, fp.first);
}

// Replaces the value of `tag` in `dyn`, or drops it when `value` is 0.
void setTag(std::vector<Elf64_Dyn>& dyn, int64_t tag, uint64_t value) {
    dyn.erase(std::remove_if(dyn.begin(), dyn.end(), [&](const Elf64_Dyn& d) { return d.d_tag == tag; }),
              dyn.end());
    if (value != 0) dyn.push_back({tag, {value}});
}

// Two DT_JMPREL entries `stride` bytes apart, the first without an import: the
// pthread_create import is only found when the parser walks the table at that stride.
std::unique_ptr<void, decltype(&free)> buildStridedPltImage(std::vector<Elf64_Dyn> dyn, uint64_t stride) {
    setTag(dyn, DT_PLTRELSZ, 2 * stride);
    dyn.push_back({DT_NULL, {0}});
    auto mem = buildPltImage(dyn);
    if (mem) {
        char* image = static_cast<char*>(mem.get());
        Elf64_Rela second;
        memset(&second, 0, sizeof(second));
        second.r_offset = PLT_SLOT;
        second.r_info = ELF64_R_INFO(1, 0);
        memset(image + DYN_JMPREL_OFF, 0, stride);
        memcpy(image + DYN_JMPREL_OFF + stride, &second, sizeof(second));
    }
    return mem;
}

// DT_PLTREL fixes the DT_JMPREL stride: DT_REL is 16-byte Elf64_Rel, DT_RELA 24-byte.
TEST_F(ElfTest, pltRelSelectsEntryStride) {
    struct Case { uint64_t pltrel, stride; bool found; };
    const Case cases[] = {
        {DT_REL, sizeof(Elf64_Rel), true},
        {DT_RELA, sizeof(Elf64_Rel), false},  // a Rela walk steps over the 16-byte second entry
    };
    for (const Case& c : cases) {
        SCOPED_TRACE(c.pltrel);
        auto dyn = pltDyn();
        setTag(dyn, DT_PLTREL, c.pltrel);
        auto mem = buildStridedPltImage(dyn, c.stride);
        ASSERT_THAT(mem.get(), ::testing::NotNull());
        char* image = static_cast<char*>(mem.get());
        EXPECT_EQ(parsedPthreadCreateImport(image),
                  c.found ? reinterpret_cast<void**>(image + PLT_SLOT) : nullptr);
    }
}

// Without DT_PLTREL the stride is a valid DT_RELAENT, else DT_RELENT; the 32-byte
// stride differs from every struct size, and 24 (RELENT) never reaches the second entry.
TEST_F(ElfTest, pltFallbackStride) {
    constexpr uint64_t STRIDE = 32;
    struct Case { uint64_t relaent, relent; bool found; };
    const Case cases[] = {
        {0, STRIDE, true},                       // DT_RELENT alone
        {STRIDE, sizeof(Elf64_Rela), true},      // a valid DT_RELAENT wins over DT_RELENT
        {0, sizeof(Elf64_Rela), false},          // wrong DT_RELENT stride misses the entry
    };
    for (const Case& c : cases) {
        SCOPED_TRACE(c.relaent * 1000 + c.relent);
        auto dyn = pltDyn();
        setTag(dyn, DT_PLTREL, 0);
        setTag(dyn, DT_RELAENT, c.relaent);
        setTag(dyn, DT_RELENT, c.relent);
        auto mem = buildStridedPltImage(dyn, STRIDE);
        ASSERT_THAT(mem.get(), ::testing::NotNull());
        char* image = static_cast<char*>(mem.get());
        EXPECT_EQ(parsedPthreadCreateImport(image),
                  c.found ? reinterpret_cast<void**>(image + PLT_SLOT) : nullptr);
    }
}

// .dynsym loads without any relocation table or entry-size tag, as in the vDSO.
TEST_F(ElfTest, dynamicSymbolsWithoutRelocationTags) {
    constexpr uint64_t HASH_OFF = 0xc00;
    constexpr uint64_t SYM_VALUE = 0x100;
    const uint32_t hash[] = {1, 2, 0, 0, 0};  // nbucket, nchain (= symbol count), bucket, chain
    static_assert(HASH_OFF >= DYN_JMPREL_OFF + sizeof(Elf64_Rela), "hash table overlaps the image data");
    static_assert(HASH_OFF + sizeof(hash) <= DYN_IMAGE_SIZE, "hash table outside the image");
    auto mem = buildPltImage({
        {DT_SYMTAB, {DYN_SYM_OFF}},
        {DT_STRTAB, {DYN_STR_OFF}},
        {DT_SYMENT, {sizeof(Elf64_Sym)}},
        {DT_STRSZ, {sizeof("\0pthread_create")}},
        {DT_HASH, {HASH_OFF}},
        {DT_NULL, {0}},
    });
    ASSERT_THAT(mem.get(), ::testing::NotNull());
    char* image = static_cast<char*>(mem.get());
    memcpy(image + HASH_OFF, hash, sizeof(hash));
    Elf64_Sym sym;
    memcpy(&sym, image + DYN_SYM_OFF + sizeof(Elf64_Sym), sizeof(sym));
    sym.st_info = ELF64_ST_INFO(STB_GLOBAL, STT_FUNC);
    sym.st_shndx = 1;
    sym.st_value = SYM_VALUE;
    sym.st_size = 4;
    memcpy(image + DYN_SYM_OFF + sizeof(Elf64_Sym), &sym, sizeof(sym));

    CodeCache cc("inmem");
    ElfParser::parseProgramHeaders(&cc, image, image + DYN_IMAGE_SIZE, /*relocate_dyn=*/false);
    EXPECT_EQ(cc.findSymbol("pthread_create"), static_cast<const void*>(image + SYM_VALUE));
}

// gABI: the dynamic array ends at the first DT_NULL. Slots after it (patchelf and
// prelink leave stale ones) must not override real tags.
TEST_F(ElfTest, dynamicSectionStopsAtDtNull) {
    auto dyn = pltDyn();
    dyn.push_back({DT_NULL, {0}});
    dyn.push_back({DT_PLTRELSZ, {0}});  // stale slot: would disable the PLT table
    auto mem = buildPltImage(dyn);
    ASSERT_THAT(mem.get(), ::testing::NotNull());
    char* image = static_cast<char*>(mem.get());

    CodeCache cc("inmem");
    ElfParser::parseProgramHeaders(&cc, image, image + DYN_IMAGE_SIZE, /*relocate_dyn=*/false);
    EXPECT_EQ(cc.peekImport(im_pthread_create), reinterpret_cast<void**>(image + PLT_SLOT));
}

#endif //__linux__
