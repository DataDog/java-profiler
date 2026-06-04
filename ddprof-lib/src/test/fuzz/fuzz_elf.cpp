/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * libFuzzer fuzz target for the Linux ELF parsing code in symbols_linux.cpp.
 *
 * The profiler parses ELF images for every shared library loaded into the JVM
 * (see Symbols::parseLibraries). A corrupt or malicious .so therefore feeds
 * fully attacker-controlled bytes into two distinct parsers, both exercised
 * here from a single ELF-blob corpus:
 *
 *   1. SymbolsLinux::extractBuildIdFromMemory(base, size, &len)
 *      An in-memory parser that walks the program-header table and PT_NOTE
 *      segments to recover the GNU build-id. It guards its reads with manual
 *      bounds checks such as `e_phoff + e_phnum * sizeof(Phdr) > elf_size`
 *      and `p_offset + p_filesz > elf_size` — both u64 additions that can
 *      wrap and defeat the check. Driven against a tight heap buffer so ASan
 *      catches any over-read precisely.
 *
 *   2. ElfParser::parseFile (via Symbols::parseElfFileForFuzzing)
 *      The core symbol/section/relocation loader: validHeader(), findSection()
 *      (indexes the section header table by attacker-controlled e_shoff /
 *      e_shentsize / e_shstrndx), loadSymbolTable() (iterates sh_size bytes in
 *      sh_entsize strides, indexes the string table by st_name) and, with
 *      use_debug, addRelocationSymbols(). parseFile() mmaps a real file, so the
 *      harness materialises the input as a temp file to mirror production
 *      exactly.
 *
 * Expected bug classes:
 * - Integer overflow in the build-id bounds checks -> heap over-read
 * - Out-of-bounds section/symbol/string-table reads from bad offsets
 * - Infinite loop / DoS from a zero sh_entsize stride
 * - Memory corruption in the malloc'd hex build-id string
 *
 * use_debug is enabled to reach the .plt/.rela.plt relocation path. The
 * external debuginfo lookups (build-id / debuglink) it can also trigger are
 * neutralised by clearing the relevant environment variables, so the fuzzer
 * never fans out to unrelated files on disk.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "codeCache.h"
#include "symbols_linux.h"  // SymbolsLinux::extractBuildIdFromMemory

// ElfParser is a translation-unit-local class in symbols_linux.cpp; forward-
// declare its public static parseFile() so the harness can drive it directly,
// mirroring how elfparser_ut.cpp reaches it (no production-side hook needed).
class ElfParser {
  public:
    static bool parseFile(CodeCache* cc, const char* base, const char* file_name, bool use_debug);
};

#ifdef FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION
namespace {

// One-time process setup: neutralise the external debuginfo lookups that
// ElfParser::loadSymbols() performs when use_debug is set and the image has no
// .symtab. With these unset, getDebuginfodCache() yields nothing and the
// /usr/lib/debug build-id path simply fails to open — the fuzzer stays focused
// on in-image parsing instead of walking the host filesystem.
struct ElfFuzzSetup {
    int fd = -1;
    char path[64];

    ElfFuzzSetup() {
        unsetenv("DEBUGINFOD_CACHE_PATH");
        unsetenv("XDG_CACHE_HOME");
        unsetenv("HOME");

        // A single reusable temp file backs the parseFile() path; truncated and
        // rewritten each iteration to avoid per-iteration mkstemp churn.
        strcpy(path, "/tmp/fuzz_elf_XXXXXX");
        fd = mkstemp(path);
    }

    ~ElfFuzzSetup() {
        if (fd != -1) {
            close(fd);
            unlink(path);
        }
    }
};

ElfFuzzSetup g_setup;

}  // namespace
#endif

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Real shared libraries are well under this; cap to bound memory/time.
    if (size > 4 * 1024 * 1024) {
        size = 4 * 1024 * 1024;
    }

    // --- Parser 1: in-memory build-id extraction (ASan-tight heap buffer) ---
    // Copy into an exact-sized allocation so any over-read past `size` is an
    // immediate ASan heap-buffer-overflow rather than a silent read into slack.
    uint8_t *buf = (uint8_t *)malloc(size);
    if (buf != nullptr) {
        memcpy(buf, data, size);
        size_t build_id_len = 0;
        char *hex = SymbolsLinux::extractBuildIdFromMemory(buf, size, &build_id_len);
        free(hex);  // buildIdToHex() returns a malloc'd string (or NULL)
        free(buf);
    }

#ifdef FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION
    // --- Parser 2: full symbol/section/relocation loader (production mmap path) ---
    if (g_setup.fd != -1) {
        if (ftruncate(g_setup.fd, 0) == 0 &&
            pwrite(g_setup.fd, data, size, 0) == (ssize_t)size) {
            CodeCache cc("fuzz_elf");
            // base==NULL keeps symbol addresses as raw st_value (never
            // dereferenced) and makes calcVirtualLoadAddress() a no-op, so the
            // only reads are file-offset-relative into the mmap'd image — the
            // untrusted parsing surface we want to exercise.
            ElfParser::parseFile(&cc, /*base=*/NULL, g_setup.path, /*use_debug=*/true);
        }
    }
#endif

    return 0;
}
