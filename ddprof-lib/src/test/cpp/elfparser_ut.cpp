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
#include <cstdint>
#include <algorithm>
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
    static void parseProgramHeaders(CodeCache* cc, const char* base, const char* end, bool relocate_dyn);
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

// Regression test for the production crash:
//   ElfParser::parseDynamicSection()+0x158
//   ElfParser::parseProgramHeaders(CodeCache*, char const*, char const*, bool)+0xf8
//   Symbols::parseLibraries(CodeCacheArray*, bool)+0x4c0
//   Libraries::updateSymbols(bool)+0xc
//   Profiler::start(Arguments&, bool)+0x84c
//
// Before the fix, parseDynamicSection() was the one path in this file NOT
// bounds-checked: dyn_ptr() computes a live-memory pointer from an untrusted
// DT_HASH d_ptr value, and the DT_HASH case dereferenced it immediately with
// no inLiveImage()-style validation. A single malformed DT_HASH entry was
// enough to crash the whole process (this test reliably reproduced it:
// SIGSEGV, exit code 139). parseDynamicSection(), dyn_ptr()'s callers, and
// getSymbolCount() (the DT_GNU_HASH path) now validate every dyn_ptr()-derived
// range against inLiveImage() -- not inImage(), which bounds a different,
// file-offset extent (see symbols_linux.cpp) -- before it is dereferenced,
// so this must return cleanly instead of crashing.
//
// This exercises parseProgramHeaders() rather than parseFile(): only that
// path passes a non-NULL live-memory `base`, which is what makes dyn_ptr()'s
// relocation arithmetic (and therefore this bug) reachable at all. It
// mirrors exactly how Symbols::parseLibraries() scans a live-mapped shared
// library.
TEST_F(ElfTest, dynamicSectionHashPointerOutOfBounds) {
    Elf64_Ehdr e = validEhdr();  // e_type == ET_DYN
    e.e_phoff = sizeof(Elf64_Ehdr);
    e.e_phentsize = sizeof(Elf64_Phdr);
    e.e_phnum = 2;

    const uint64_t dyn_off = sizeof(Elf64_Ehdr) + 2 * sizeof(Elf64_Phdr);
    const uint64_t image_size = dyn_off + 2 * sizeof(Elf64_Dyn);

    Elf64_Phdr ph[2];
    memset(ph, 0, sizeof(ph));
    // p_vaddr == 0 makes calcVirtualLoadAddress() set _vaddr_diff == _base,
    // so at(dynamic) == _base + p_vaddr resolves into our own buffer below.
    ph[0].p_type = PT_LOAD;
    ph[0].p_vaddr = 0;
    ph[0].p_offset = 0;
    ph[0].p_filesz = ph[0].p_memsz = image_size;
    // p_vaddr points at the Dyn array appended right after the two phdrs.
    ph[1].p_type = PT_DYNAMIC;
    ph[1].p_vaddr = dyn_off;
    ph[1].p_offset = dyn_off;
    ph[1].p_filesz = ph[1].p_memsz = 2 * sizeof(Elf64_Dyn);

    Elf64_Dyn dyn[2];
    memset(dyn, 0, sizeof(dyn));
    dyn[0].d_tag = DT_HASH;
    // With relocate_dyn=true, dyn_ptr() returns _vaddr_diff + d_ptr, i.e.
    // _base + d_ptr. 16 TB (the same "reliably unmapped" magnitude used by
    // the OOB tests above) lands the pointer far outside any real mapping
    // regardless of where our tiny buffer happens to sit under ASLR.
    dyn[0].d_un.d_ptr = 0x100000000000ULL;
    dyn[1].d_tag = DT_NULL;

    std::vector<char> b;
    auto app = [&](const void* p, size_t n) {
        const char* c = static_cast<const char*>(p);
        b.insert(b.end(), c, c + n);
    };
    app(&e, sizeof(e));
    app(ph, sizeof(ph));
    app(dyn, sizeof(dyn));
    ASSERT_EQ(b.size(), image_size);

    CodeCache cc("regress-dynsec");
    const char* base = b.data();
    // Mirrors Symbols::parseLibraries()'s call for a live-mapped shared
    // library: base/end delimit the mapping, relocate_dyn matches a
    // GNU-linker-style DSO. This is the exact call that segfaults today
    // inside the DT_HASH case of parseDynamicSection().
    ElfParser::parseProgramHeaders(&cc, base, base + b.size(), /*relocate_dyn=*/true);
    // Beyond "must not crash": there is no DT_SYMTAB/DT_STRTAB here, so
    // parseDynamicSection() must bail out at its "symtab == NULL" check
    // without loading anything -- the malformed DT_HASH entry must not leave
    // behind a symbol table populated from garbage.
    EXPECT_EQ(cc.count(), 0);
}

// =====================================================================
// Coverage for resolveSymbol()/resolveImportAddr(): the relocation-loop
// guards added by the ELF parser hardening above. The DT_HASH regression
// test just above never reaches either helper -- it has no DT_SYMTAB, so
// parseDynamicSection() returns before the relocation loops. These tests
// populate a real .dynsym/.dynstr/.rela.plt so a single malformed field
// (syment, the symbol index, or r_offset) is the only thing standing
// between "resolves cleanly" and "reads out of bounds", isolating each
// guard in turn.
// =====================================================================

namespace {

// Fixed byte layout shared by every variant below: only syment, sym_index,
// and r_offset change between tests. All are compile-time constants, since
// none of the sizes involved depend on the malformed values under test.
constexpr uint64_t kRelocDynOff = sizeof(Elf64_Ehdr) + 2 * sizeof(Elf64_Phdr);
constexpr int kRelocDynCount = 8;
constexpr uint64_t kRelocSymtabOff = kRelocDynOff + kRelocDynCount * sizeof(Elf64_Dyn);
constexpr uint64_t kRelocStrtabOff = kRelocSymtabOff + 2 * sizeof(Elf64_Sym);
constexpr char kRelocStrtab[] = "\0malloc";  // index 1 = "malloc" (recognized by CodeCache::addImport)
constexpr uint64_t kRelocJmprelOff = kRelocStrtabOff + sizeof(kRelocStrtab);
constexpr uint64_t kRelocGotOff = kRelocJmprelOff + sizeof(Elf64_Rel);
constexpr uint64_t kRelocImageSize = kRelocGotOff + sizeof(void*);

// Builds a minimal ELF64 DSO with one PT_LOAD (covering the whole image) and
// a PT_DYNAMIC pointing at a single DT_JMPREL/.rela.plt entry that resolves
// symbol index `sym_index` through a DT_SYMENT of `syment`, patching the GOT
// slot at `r_offset`. Passing the "correct" values (sizeof(Elf64_Sym), 1,
// kRelocGotOff) resolves cleanly end to end; each test below instead
// corrupts exactly one of the three to isolate one guard.
std::vector<char> buildRelocationTestElf(uint64_t syment, uint32_t sym_index, uint64_t r_offset) {
    Elf64_Ehdr e = validEhdr();
    e.e_phoff = sizeof(Elf64_Ehdr);
    e.e_phentsize = sizeof(Elf64_Phdr);
    e.e_phnum = 2;

    Elf64_Phdr ph[2];
    memset(ph, 0, sizeof(ph));
    ph[0].p_type = PT_LOAD;  // p_vaddr == p_offset == 0: covers the whole image
    ph[0].p_filesz = ph[0].p_memsz = kRelocImageSize;
    ph[1].p_type = PT_DYNAMIC;
    ph[1].p_vaddr = ph[1].p_offset = kRelocDynOff;
    ph[1].p_filesz = ph[1].p_memsz = kRelocDynCount * sizeof(Elf64_Dyn);

    Elf64_Dyn dyn[kRelocDynCount];
    memset(dyn, 0, sizeof(dyn));
    dyn[0].d_tag = DT_SYMTAB;   dyn[0].d_un.d_ptr = kRelocSymtabOff;
    dyn[1].d_tag = DT_STRTAB;   dyn[1].d_un.d_ptr = kRelocStrtabOff;
    dyn[2].d_tag = DT_STRSZ;    dyn[2].d_un.d_val = sizeof(kRelocStrtab);
    dyn[3].d_tag = DT_SYMENT;   dyn[3].d_un.d_val = syment;
    dyn[4].d_tag = DT_JMPREL;   dyn[4].d_un.d_ptr = kRelocJmprelOff;
    dyn[5].d_tag = DT_PLTRELSZ; dyn[5].d_un.d_val = sizeof(Elf64_Rel);
    dyn[6].d_tag = DT_RELENT;   dyn[6].d_un.d_val = sizeof(Elf64_Rel);
    dyn[7].d_tag = DT_NULL;

    Elf64_Sym sym[2];
    memset(sym, 0, sizeof(sym));  // sym[0] is the mandatory null symbol
    sym[1].st_name = 1;   // "malloc" at strtab offset 1
    sym[1].st_value = 0x1000;

    Elf64_Rel rel;
    memset(&rel, 0, sizeof(rel));
    rel.r_info = (uint64_t)sym_index << 32;  // r_type is unchecked by the .rela.plt loop
    rel.r_offset = r_offset;

    std::vector<char> b(kRelocImageSize, 0);
    memcpy(b.data(), &e, sizeof(e));
    memcpy(b.data() + sizeof(e), ph, sizeof(ph));
    memcpy(b.data() + kRelocDynOff, dyn, sizeof(dyn));
    memcpy(b.data() + kRelocSymtabOff, sym, sizeof(sym));
    memcpy(b.data() + kRelocStrtabOff, kRelocStrtab, sizeof(kRelocStrtab));
    memcpy(b.data() + kRelocJmprelOff, &rel, sizeof(rel));
    return b;
}

}  // namespace

TEST_F(ElfTest, relocationResolvesValidSymbol) {
    std::vector<char> b = buildRelocationTestElf(sizeof(Elf64_Sym), /*sym_index=*/1, kRelocGotOff);
    CodeCache cc("regress-reloc-valid");
    const char* base = b.data();
    ElfParser::parseProgramHeaders(&cc, base, base + b.size(), /*relocate_dyn=*/true);
    // A guard mutated to reject everything would fail this: the "malloc"
    // relocation must resolve and patch the GOT slot at kRelocGotOff.
    EXPECT_EQ(cc.findImport(im_malloc), (void**)(base + kRelocGotOff));
}

// Regression test for liveSegmentEnd()'s boundary-ambiguity bug: two
// byte-adjacent PT_LOAD segments (a real, spec-legal layout -- linkers
// routinely emit segments with no vaddr gap between them, not just
// corrupted ones) split exactly at kRelocStrtabOff, with DT_STRTAB
// resolving to precisely that shared boundary address. Everything else is
// identical to buildRelocationTestElf()'s single-PT_LOAD layout (same
// symtab/strtab/jmprel/got constants and contents), so this isolates the
// segment-boundary handling specifically. An inclusive-upper-bound,
// first-match liveSegmentEnd() matches the *ending* segment and reports
// zero room, making parseDynamicSection() wrongly bail out (dropping the
// whole dynamic symbol/import set for a perfectly valid library) even
// though strtab is actually the valid start of the second segment, which
// has plenty of room.
TEST_F(ElfTest, strtabAtAdjacentSegmentBoundaryStillResolves) {
    // This layout needs 3 program headers (2x PT_LOAD + PT_DYNAMIC), unlike
    // buildRelocationTestElf()'s single PT_LOAD, so it cannot reuse the
    // kReloc* offset constants (they assume exactly 2 phdrs precede the
    // dyn array) -- everything is laid out fresh, with the DT_STRTAB/split
    // point deliberately coinciding.
    const uint64_t dyn_off = sizeof(Elf64_Ehdr) + 3 * sizeof(Elf64_Phdr);
    const int dyn_count = 8;
    const uint64_t symtab_off = dyn_off + dyn_count * sizeof(Elf64_Dyn);
    const uint64_t strtab_off = symtab_off + 2 * sizeof(Elf64_Sym);  // == the segment split point
    const char strtab[] = "\0malloc";
    const uint64_t jmprel_off = strtab_off + sizeof(strtab);
    const uint64_t got_off = jmprel_off + sizeof(Elf64_Rel);
    const uint64_t image_size = got_off + sizeof(void*);

    Elf64_Ehdr e = validEhdr();
    e.e_phoff = sizeof(Elf64_Ehdr);
    e.e_phentsize = sizeof(Elf64_Phdr);
    e.e_phnum = 3;

    Elf64_Phdr ph[3];
    memset(ph, 0, sizeof(ph));
    ph[0].p_type = PT_LOAD;
    ph[0].p_vaddr = ph[0].p_offset = 0;
    ph[0].p_filesz = ph[0].p_memsz = strtab_off;  // ends exactly where segment 2 begins
    ph[1].p_type = PT_LOAD;
    ph[1].p_vaddr = ph[1].p_offset = strtab_off;  // zero-gap adjacency with ph[0]
    ph[1].p_filesz = ph[1].p_memsz = image_size - strtab_off;
    ph[2].p_type = PT_DYNAMIC;
    ph[2].p_vaddr = ph[2].p_offset = dyn_off;
    ph[2].p_filesz = ph[2].p_memsz = dyn_count * sizeof(Elf64_Dyn);

    Elf64_Dyn dyn[dyn_count];
    memset(dyn, 0, sizeof(dyn));
    dyn[0].d_tag = DT_SYMTAB;   dyn[0].d_un.d_ptr = symtab_off;
    dyn[1].d_tag = DT_STRTAB;   dyn[1].d_un.d_ptr = strtab_off;  // exactly at the segment boundary
    dyn[2].d_tag = DT_STRSZ;    dyn[2].d_un.d_val = sizeof(strtab);
    dyn[3].d_tag = DT_SYMENT;   dyn[3].d_un.d_val = sizeof(Elf64_Sym);
    dyn[4].d_tag = DT_JMPREL;   dyn[4].d_un.d_ptr = jmprel_off;
    dyn[5].d_tag = DT_PLTRELSZ; dyn[5].d_un.d_val = sizeof(Elf64_Rel);
    dyn[6].d_tag = DT_RELENT;   dyn[6].d_un.d_val = sizeof(Elf64_Rel);
    dyn[7].d_tag = DT_NULL;

    Elf64_Sym sym[2];
    memset(sym, 0, sizeof(sym));
    sym[1].st_name = 1;
    sym[1].st_value = 0x1000;

    Elf64_Rel rel;
    memset(&rel, 0, sizeof(rel));
    rel.r_info = (uint64_t)1 << 32;  // symbol index 1 ("malloc")
    rel.r_offset = got_off;

    std::vector<char> b(image_size, 0);
    memcpy(b.data(), &e, sizeof(e));
    memcpy(b.data() + sizeof(e), ph, sizeof(ph));
    memcpy(b.data() + dyn_off, dyn, sizeof(dyn));
    memcpy(b.data() + symtab_off, sym, sizeof(sym));
    memcpy(b.data() + strtab_off, strtab, sizeof(strtab));
    memcpy(b.data() + jmprel_off, &rel, sizeof(rel));

    CodeCache cc("regress-strtab-adjacent-boundary");
    const char* base = b.data();
    ElfParser::parseProgramHeaders(&cc, base, base + b.size(), /*relocate_dyn=*/true);
    EXPECT_EQ(cc.findImport(im_malloc), (void**)(base + got_off));
}

TEST_F(ElfTest, resolveSymbolRejectsSymentIndexOverflow) {
    // syment == 2^63+12, sym_index == 2: chosen so index*syment overflows
    // size_t and wraps to exactly sizeof(Elf64_Sym) (24) -- landing squarely
    // on the "malloc" symbol at symtab+24, well within the live image. If
    // resolveSymbol()'s first guard ("index > SIZE_MAX / syment", the only
    // thing that catches this input -- the wrapped offset is small, so
    // neither the pointer-overflow check nor inLiveImage() would reject it)
    // were weakened or deleted, this would silently resolve to the wrong
    // symbol and patch the GOT instead of being rejected.
    const uint64_t syment = (1ULL << 63) + 12;
    std::vector<char> b = buildRelocationTestElf(syment, /*sym_index=*/2, kRelocGotOff);
    CodeCache cc("regress-reloc-symentoverflow");
    const char* base = b.data();
    ElfParser::parseProgramHeaders(&cc, base, base + b.size(), /*relocate_dyn=*/true);
    EXPECT_EQ(cc.findImport(im_malloc), nullptr);
}

TEST_F(ElfTest, resolveSymbolRejectsPointerOverflow) {
    // syment == SIZE_MAX, sym_index == 1: index*syment == SIZE_MAX (no
    // multiplication overflow, so the first guard passes), but
    // symtab + SIZE_MAX cannot be formed without wrapping the pointer --
    // resolveSymbol()'s second (offset > UINTPTR_MAX - symtab) guard must
    // catch this instead.
    std::vector<char> b = buildRelocationTestElf(/*syment=*/UINT64_MAX, /*sym_index=*/1, kRelocGotOff);
    CodeCache cc("regress-reloc-ptroverflow");
    const char* base = b.data();
    ElfParser::parseProgramHeaders(&cc, base, base + b.size(), /*relocate_dyn=*/true);
    EXPECT_EQ(cc.findImport(im_malloc), nullptr);
}

TEST_F(ElfTest, resolveSymbolRejectsOutOfImageIndex) {
    // A well-formed syment but a symbol index far past the tiny two-entry
    // symtab: no integer overflow anywhere, but symtab + index*syment lands
    // ~24 MB past the image. resolveSymbol()'s inLiveImage() check must
    // reject it instead of dereferencing an ElfSymbol out there.
    std::vector<char> b = buildRelocationTestElf(sizeof(Elf64_Sym), /*sym_index=*/1000000, kRelocGotOff);
    CodeCache cc("regress-reloc-symoob");
    const char* base = b.data();
    ElfParser::parseProgramHeaders(&cc, base, base + b.size(), /*relocate_dyn=*/true);
    EXPECT_EQ(cc.findImport(im_malloc), nullptr);
}

TEST_F(ElfTest, resolveImportAddrRejectsPointerOverflow) {
    // Symbol resolution succeeds ("malloc" at index 1), but r_offset is
    // UINT64_MAX: resolveImportAddr()'s "r_offset > UINTPTR_MAX - base"
    // guard must reject the GOT address before base + r_offset is formed.
    std::vector<char> b = buildRelocationTestElf(sizeof(Elf64_Sym), /*sym_index=*/1, /*r_offset=*/UINT64_MAX);
    CodeCache cc("regress-reloc-importptroverflow");
    const char* base = b.data();
    ElfParser::parseProgramHeaders(&cc, base, base + b.size(), /*relocate_dyn=*/true);
    EXPECT_EQ(cc.findImport(im_malloc), nullptr);
}

TEST_F(ElfTest, resolveImportAddrRejectsOutOfImageOffset) {
    // Symbol resolution succeeds, but r_offset (~50 MB) does not overflow
    // the pointer addition -- it just lands well past the image.
    // resolveImportAddr()'s inLiveImage() check must reject it.
    std::vector<char> b = buildRelocationTestElf(sizeof(Elf64_Sym), /*sym_index=*/1, /*r_offset=*/50000000ULL);
    CodeCache cc("regress-reloc-importoob");
    const char* base = b.data();
    ElfParser::parseProgramHeaders(&cc, base, base + b.size(), /*relocate_dyn=*/true);
    EXPECT_EQ(cc.findImport(im_malloc), nullptr);
}

// =====================================================================
// Coverage for getSymbolCount() (the DT_GNU_HASH path). Layout mirrors
// buildRelocationTestElf() (same symtab/strtab/.rela.plt) but adds a real
// DT_GNU_HASH table after the GOT slot, with a one-bucket/one-chain-entry
// hash covering exactly our two dynsyms (the mandatory null symbol at index
// 0, "malloc" at index 1). `bucket_value` is the one knob under test: the
// GNU hash spec requires it to be the *global* dynsym index of the first
// symbol hashed into that bucket, which for a well-formed table is 1.
// =====================================================================

namespace {

constexpr uint64_t kGHDynOff = sizeof(Elf64_Ehdr) + 2 * sizeof(Elf64_Phdr);
constexpr int kGHDynCount = 9;  // one more than kRelocDynCount: adds DT_GNU_HASH
constexpr uint64_t kGHSymtabOff = kGHDynOff + kGHDynCount * sizeof(Elf64_Dyn);
constexpr uint64_t kGHStrtabOff = kGHSymtabOff + 2 * sizeof(Elf64_Sym);
constexpr char kGHStrtab[] = "\0malloc";
constexpr uint64_t kGHJmprelOff = kGHStrtabOff + sizeof(kGHStrtab);
constexpr uint64_t kGHGotOff = kGHJmprelOff + sizeof(Elf64_Rel);
constexpr uint64_t kGHGnuHashOff = kGHGotOff + sizeof(void*);
constexpr uint64_t kGHBloomOff = kGHGnuHashOff + 4 * sizeof(uint32_t);  // header: nbuckets,symoffset,bloom_size,bloom_shift
constexpr uint64_t kGHBucketsOff = kGHBloomOff + 2 * sizeof(uint32_t);  // bloom_size(1) * (sizeof(size_t)/4)(2) words
constexpr uint64_t kGHChainOff = kGHBucketsOff + 1 * sizeof(uint32_t);  // one physical bucket slot
constexpr size_t kGHFullGnuHashBytes = (kGHChainOff + 1 * sizeof(uint32_t)) - kGHGnuHashOff;  // header+bloom+bucket+chain

// `nbuckets`/`bucket_value` feed gnu_hash's header and its one physical
// bucket slot -- the malformed cases below set `nbuckets` far larger than
// what's physically present (to overrun the bucket-array bounds check) or
// `bucket_value` to an out-of-image dynsym index (to overrun the chain
// walk). `gnu_hash_bytes` truncates how much of the GNU_HASH region
// actually exists after its header offset, to exercise getSymbolCount()'s
// own leading inLiveImage() check on the header itself; below
// sizeof(gnu_header) it also truncates the header struct that gets written.
// The chain entry, when present, always has its terminator bit set,
// matching a real single-entry chain.
std::vector<char> buildGnuHashTestElf(uint32_t nbuckets, uint32_t bucket_value,
                                      size_t gnu_hash_bytes = kGHFullGnuHashBytes) {
    Elf64_Ehdr e = validEhdr();
    e.e_phoff = sizeof(Elf64_Ehdr);
    e.e_phentsize = sizeof(Elf64_Phdr);
    e.e_phnum = 2;

    const uint64_t image_size = kGHGnuHashOff + gnu_hash_bytes;

    Elf64_Phdr ph[2];
    memset(ph, 0, sizeof(ph));
    ph[0].p_type = PT_LOAD;
    ph[0].p_filesz = ph[0].p_memsz = image_size;
    ph[1].p_type = PT_DYNAMIC;
    ph[1].p_vaddr = ph[1].p_offset = kGHDynOff;
    ph[1].p_filesz = ph[1].p_memsz = kGHDynCount * sizeof(Elf64_Dyn);

    Elf64_Dyn dyn[kGHDynCount];
    memset(dyn, 0, sizeof(dyn));
    dyn[0].d_tag = DT_SYMTAB;   dyn[0].d_un.d_ptr = kGHSymtabOff;
    dyn[1].d_tag = DT_STRTAB;   dyn[1].d_un.d_ptr = kGHStrtabOff;
    dyn[2].d_tag = DT_STRSZ;    dyn[2].d_un.d_val = sizeof(kGHStrtab);
    dyn[3].d_tag = DT_SYMENT;   dyn[3].d_un.d_val = sizeof(Elf64_Sym);
    dyn[4].d_tag = DT_JMPREL;   dyn[4].d_un.d_ptr = kGHJmprelOff;
    dyn[5].d_tag = DT_PLTRELSZ; dyn[5].d_un.d_val = sizeof(Elf64_Rel);
    dyn[6].d_tag = DT_RELENT;   dyn[6].d_un.d_val = sizeof(Elf64_Rel);
    dyn[7].d_tag = DT_GNU_HASH; dyn[7].d_un.d_ptr = kGHGnuHashOff;
    dyn[8].d_tag = DT_NULL;

    Elf64_Sym sym[2];
    memset(sym, 0, sizeof(sym));  // sym[0] is the mandatory null symbol
    sym[1].st_name = 1;
    sym[1].st_value = 0x1000;

    Elf64_Rel rel;
    memset(&rel, 0, sizeof(rel));
    rel.r_info = (uint64_t)1 << 32;  // symbol index 1 ("malloc"); type unchecked by .rela.plt
    rel.r_offset = kGHGotOff;

    uint32_t gnu_header[4] = {nbuckets, /*symoffset=*/1, /*bloom_size=*/1, /*bloom_shift=*/0};
    uint32_t bloom[2] = {0, 0};
    uint32_t chain = 0x1;  // terminator bit set: last (and only) entry in the chain

    std::vector<char> b(image_size, 0);
    memcpy(b.data(), &e, sizeof(e));
    memcpy(b.data() + sizeof(e), ph, sizeof(ph));
    memcpy(b.data() + kGHDynOff, dyn, sizeof(dyn));
    memcpy(b.data() + kGHSymtabOff, sym, sizeof(sym));
    memcpy(b.data() + kGHStrtabOff, kGHStrtab, sizeof(kGHStrtab));
    memcpy(b.data() + kGHJmprelOff, &rel, sizeof(rel));
    // Write only as much of the GNU_HASH region as gnu_hash_bytes allows --
    // that's the whole point of the truncated-header test case.
    memcpy(b.data() + kGHGnuHashOff, gnu_header, std::min(gnu_hash_bytes, sizeof(gnu_header)));
    if (gnu_hash_bytes >= kGHBloomOff + sizeof(bloom) - kGHGnuHashOff) {
        memcpy(b.data() + kGHBloomOff, bloom, sizeof(bloom));
    }
    if (gnu_hash_bytes >= kGHBucketsOff + sizeof(bucket_value) - kGHGnuHashOff) {
        memcpy(b.data() + kGHBucketsOff, &bucket_value, sizeof(bucket_value));
    }
    if (gnu_hash_bytes >= kGHChainOff + sizeof(chain) - kGHGnuHashOff) {
        memcpy(b.data() + kGHChainOff, &chain, sizeof(chain));
    }
    return b;
}

}  // namespace

TEST_F(ElfTest, gnuHashComputesSymbolCount) {
    // nbuckets == 1, bucket_value == 1: the real global dynsym index of
    // "malloc", the only hashed symbol. getSymbolCount() must walk
    // buckets+chain and return 2 (index 0's null symbol is implicit; index 1
    // is where the chain's terminator bit lands), which unblocks
    // loadSymbolTable()'s sequential walk over the *whole* symtab -- not
    // just what the (independent) .rela.plt import loop resolves. A stub
    // that skips real parsing, or a getSymbolCount() that miscounts, shows
    // up here as a missing debug symbol even though the relocation-based
    // import still succeeds.
    std::vector<char> b = buildGnuHashTestElf(/*nbuckets=*/1, /*bucket_value=*/1);
    CodeCache cc("regress-gnuhash-valid");
    const char* base = b.data();
    ElfParser::parseProgramHeaders(&cc, base, base + b.size(), /*relocate_dyn=*/true);
    EXPECT_EQ(cc.count(), 1);
    EXPECT_EQ(cc.findImport(im_malloc), (void**)(base + kGHGotOff));
}

TEST_F(ElfTest, gnuHashRejectsOutOfImageChainIndex) {
    // bucket_value is a huge, clearly-bogus dynsym index. getSymbolCount()'s
    // chain walk must reject &chain[bucket_value] via inLiveImage() (it is
    // ~16 GB past this tiny image) and return 0 instead of reading out of
    // bounds. The independent .rela.plt import must still resolve normally
    // -- a malformed DT_GNU_HASH must not take down the rest of dynamic
    // section parsing -- so this isolates getSymbolCount()'s own guard
    // rather than merely checking "did not crash".
    std::vector<char> b = buildGnuHashTestElf(/*nbuckets=*/1, /*bucket_value=*/0xFFFFFFF0u);
    CodeCache cc("regress-gnuhash-oob-chain");
    const char* base = b.data();
    ElfParser::parseProgramHeaders(&cc, base, base + b.size(), /*relocate_dyn=*/true);
    EXPECT_EQ(cc.count(), 0);
    EXPECT_EQ(cc.findImport(im_malloc), (void**)(base + kGHGotOff));
}

TEST_F(ElfTest, gnuHashRejectsOutOfImageBucketArray) {
    // nbuckets claims a million buckets, but the image physically has room
    // for exactly one bucket slot. bucket_bytes (~4 MB) does not overflow
    // the multiplication -- this isolates the separate
    // "!inLiveImage(buckets, bucket_bytes)" bucket-array bounds check from
    // the chain-walk check above, which only runs once that check has
    // already passed. The independent .rela.plt import must still resolve.
    std::vector<char> b = buildGnuHashTestElf(/*nbuckets=*/1000000, /*bucket_value=*/1);
    CodeCache cc("regress-gnuhash-oob-buckets");
    const char* base = b.data();
    ElfParser::parseProgramHeaders(&cc, base, base + b.size(), /*relocate_dyn=*/true);
    EXPECT_EQ(cc.count(), 0);
    EXPECT_EQ(cc.findImport(im_malloc), (void**)(base + kGHGotOff));
}

TEST_F(ElfTest, gnuHashRejectsTruncatedHeader) {
    // Only 8 of the mandatory 16 header bytes (nbuckets, symoffset,
    // bloom_size, bloom_shift) are actually present in the image --
    // dyn_ptr() only validates that gnu_hash's *start* is in bounds, so this
    // isolates getSymbolCount()'s own leading inLiveImage(gnu_hash, 16)
    // check from every guard downstream of it. The independent .rela.plt
    // import must still resolve.
    std::vector<char> b = buildGnuHashTestElf(/*nbuckets=*/1, /*bucket_value=*/1, /*gnu_hash_bytes=*/8);
    CodeCache cc("regress-gnuhash-truncated-header");
    const char* base = b.data();
    ElfParser::parseProgramHeaders(&cc, base, base + b.size(), /*relocate_dyn=*/true);
    EXPECT_EQ(cc.count(), 0);
    EXPECT_EQ(cc.findImport(im_malloc), (void**)(base + kGHGotOff));
}

// =====================================================================
// Coverage for the second relocation loop in parseDynamicSection() (.rela.dyn
// via DT_RELA/DT_RELASZ, used for e.g. R_*_GLOB_DAT relocations in libraries
// built without PLT). Every prior relocation test above drives the
// .rela.plt/DT_JMPREL loop; this is a structurally separate loop with its
// own bounds check ("relcount <= SIZE_MAX / relent") and its own call into
// resolveSymbol(), so it needs its own coverage.
// =====================================================================

namespace {

// Same fixed layout as buildRelocationTestElf(), except the single
// relocation is delivered via DT_RELA/DT_RELASZ (with DT_RELACOUNT == 0, so
// the loop's "start at relcount*relent" begins at offset 0) instead of
// DT_JMPREL/DT_PLTRELSZ, and carries an R_*_GLOB_DAT type so the .rela.dyn
// loop's type filter accepts it.
std::vector<char> buildRelaDynTestElf(uint32_t sym_index) {
    Elf64_Ehdr e = validEhdr();
    e.e_phoff = sizeof(Elf64_Ehdr);
    e.e_phentsize = sizeof(Elf64_Phdr);
    e.e_phnum = 2;

    Elf64_Phdr ph[2];
    memset(ph, 0, sizeof(ph));
    ph[0].p_type = PT_LOAD;
    ph[0].p_filesz = ph[0].p_memsz = kRelocImageSize;
    ph[1].p_type = PT_DYNAMIC;
    ph[1].p_vaddr = ph[1].p_offset = kRelocDynOff;
    ph[1].p_filesz = ph[1].p_memsz = kRelocDynCount * sizeof(Elf64_Dyn);

    Elf64_Dyn dyn[kRelocDynCount];
    memset(dyn, 0, sizeof(dyn));
    dyn[0].d_tag = DT_SYMTAB;   dyn[0].d_un.d_ptr = kRelocSymtabOff;
    dyn[1].d_tag = DT_STRTAB;   dyn[1].d_un.d_ptr = kRelocStrtabOff;
    dyn[2].d_tag = DT_STRSZ;    dyn[2].d_un.d_val = sizeof(kRelocStrtab);
    dyn[3].d_tag = DT_SYMENT;   dyn[3].d_un.d_val = sizeof(Elf64_Sym);
    dyn[4].d_tag = DT_RELA;     dyn[4].d_un.d_ptr = kRelocJmprelOff;  // reuse the same slot as jmprel
    dyn[5].d_tag = DT_RELASZ;   dyn[5].d_un.d_val = sizeof(Elf64_Rel);
    dyn[6].d_tag = DT_RELAENT;  dyn[6].d_un.d_val = sizeof(Elf64_Rel);
    dyn[7].d_tag = DT_RELACOUNT; dyn[7].d_un.d_val = 0;
    // kRelocDynCount == 8: no room for (and no need for) a trailing DT_NULL --
    // the dynamic-section loop bounds on p_memsz, not on a terminator tag.

    Elf64_Sym sym[2];
    memset(sym, 0, sizeof(sym));
    sym[1].st_name = 1;
    sym[1].st_value = 0x1000;

    Elf64_Rel rel;
    memset(&rel, 0, sizeof(rel));
#if defined(__x86_64__)
    const uint32_t glob_dat = R_X86_64_GLOB_DAT;
#elif defined(__aarch64__)
    const uint32_t glob_dat = R_AARCH64_GLOB_DAT;
#elif defined(__i386__)
    const uint32_t glob_dat = R_386_GLOB_DAT;
#elif defined(__arm__)
    const uint32_t glob_dat = R_ARM_GLOB_DAT;
#else
    const uint32_t glob_dat = 0;  // no GLOB_DAT relocation on this arch; loop below will just skip the entry
#endif
    rel.r_info = ((uint64_t)sym_index << 32) | glob_dat;
    rel.r_offset = kRelocGotOff;

    std::vector<char> b(kRelocImageSize, 0);
    memcpy(b.data(), &e, sizeof(e));
    memcpy(b.data() + sizeof(e), ph, sizeof(ph));
    memcpy(b.data() + kRelocDynOff, dyn, sizeof(dyn));
    memcpy(b.data() + kRelocSymtabOff, sym, sizeof(sym));
    memcpy(b.data() + kRelocStrtabOff, kRelocStrtab, sizeof(kRelocStrtab));
    memcpy(b.data() + kRelocJmprelOff, &rel, sizeof(rel));
    return b;
}

}  // namespace

TEST_F(ElfTest, relaDynLoopResolvesValidSymbol) {
    std::vector<char> b = buildRelaDynTestElf(/*sym_index=*/1);
    CodeCache cc("regress-reladyn-valid");
    const char* base = b.data();
    ElfParser::parseProgramHeaders(&cc, base, base + b.size(), /*relocate_dyn=*/true);
    EXPECT_EQ(cc.findImport(im_malloc), (void**)(base + kRelocGotOff));
}

TEST_F(ElfTest, relaDynLoopRejectsOutOfImageIndex) {
    // Mirrors resolveSymbolRejectsOutOfImageIndex, but through the .rela.dyn
    // loop's own resolveSymbol() call site rather than .rela.plt's.
    std::vector<char> b = buildRelaDynTestElf(/*sym_index=*/1000000);
    CodeCache cc("regress-reladyn-oob");
    const char* base = b.data();
    ElfParser::parseProgramHeaders(&cc, base, base + b.size(), /*relocate_dyn=*/true);
    EXPECT_EQ(cc.findImport(im_malloc), nullptr);
}

#endif //__linux__
