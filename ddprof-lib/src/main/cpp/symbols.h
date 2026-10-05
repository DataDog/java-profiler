/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SYMBOLS_H
#define _SYMBOLS_H

#include "codeCache.h"
#include "mutex.h"

#include <stdint.h>


class Symbols {
  private:
    static Mutex _parse_lock;
    static bool _have_kernel_symbols;
    static bool _libs_limit_reported;

  public:
    static void initLibraryRanges();
    static void parseKernelSymbols(CodeCache* cc);
    static void parseLibraries(CodeCacheArray* array, bool kernel_symbols);

    static bool haveKernelSymbols() {
        return _have_kernel_symbols;
    }
    // Clear internal caches - mainly for test purposes
    static void clearParsingCaches();
    // Fast range check: does this PC lie in libc or libpthread?
    static bool isLibcOrPthreadAddress(uintptr_t pc);
#ifdef __linux__
    // Fingerprint of a loaded ELF image: its program header table plus its
    // PT_NOTE segments, which carry the GNU build-id. The same build loaded at
    // the same address has the same fingerprint. phdrs points to phnum program
    // headers, p_vaddr 0 maps to load_bias, and only [lo, hi) may be read.
    // Returns 0 if part of the image to hash lies outside [lo, hi).
    static u64 imageFingerprint(const void* phdrs, int phnum, uintptr_t load_bias,
                                uintptr_t lo, uintptr_t hi);
#endif
};

class UnloadProtection {
  private:
    void* _lib_handle;
    bool _valid;

  public:
    UnloadProtection(const CodeCache *cc);
    ~UnloadProtection();

    UnloadProtection& operator=(const UnloadProtection& other) = delete;

    bool isValid() const { return _valid; }
};

#endif // _SYMBOLS_H
