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
};

class UnloadProtection {
  private:
    void* _lib_handle;
    bool _valid;

  public:
    UnloadProtection(const CodeCache *cc);
    ~UnloadProtection();

    UnloadProtection(const UnloadProtection& other) = delete;
    UnloadProtection& operator=(const UnloadProtection& other) = delete;
    UnloadProtection(UnloadProtection&& other) noexcept;
    UnloadProtection& operator=(UnloadProtection&& other) noexcept;

    bool isValid() const { return _valid; }
    void* release();
};

#endif // _SYMBOLS_H
