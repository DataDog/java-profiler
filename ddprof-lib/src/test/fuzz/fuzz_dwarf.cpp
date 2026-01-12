/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * libFuzzer fuzz target for the DWARF exception frame parser.
 *
 * The DwarfParser parses .eh_frame_hdr sections from ELF files to build
 * unwind tables for stack walking. This is a critical attack surface because:
 * - It processes untrusted binary data from loaded libraries
 * - Parsing happens in signal handler context (crashes = JVM crashes)
 * - Minimal bounds checking in LEB128 decoding and pointer arithmetic
 *
 * Expected bug classes:
 * - Buffer over-reads from malformed LEB128 sequences
 * - Integer overflows in offset calculations
 * - Infinite loops from cyclic or malformed structures
 * - Null pointer dereferences from missing validation
 */

#include <stddef.h>
#include <stdint.h>
#include <cstring>

// Include the DWARF parser - dwarf.h comes from cpp-external (async-profiler upstream)
#include "dwarf.h"
#include "dwarf_dd.h"

// Provide a minimal stub for Log since dwarf.cpp uses it
#include "log.h"

// Silence logging during fuzzing to avoid noise
#ifdef FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION
namespace {
    struct LogSilencer {
        LogSilencer() {
            // Fuzzing mode - suppress warnings
        }
    };
    static LogSilencer log_silencer;
}
#endif

/**
 * LLVMFuzzerTestOneInput - The libFuzzer entry point.
 *
 * This function is called by libFuzzer with mutated input data.
 * The fuzzer will try to maximize code coverage by generating
 * inputs that explore new paths through the DWARF parser.
 *
 * @param data Pointer to fuzzer-generated input bytes
 * @param size Size of the input data in bytes
 * @return 0 (required by libFuzzer interface)
 */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    // Minimum size for a valid .eh_frame_hdr header:
    // - 1 byte version
    // - 1 byte eh_frame_ptr encoding
    // - 1 byte fde_count encoding
    // - 1 byte table encoding
    // - 4 bytes eh_frame_ptr
    // - 4 bytes fde_count
    // Minimum: 12 bytes, but we need at least 16 for the table pointer
    if (size < 16) {
        return 0;
    }

    // Cap size to avoid excessive memory allocation during parsing.
    // Real .eh_frame_hdr sections are typically < 1MB
    if (size > 1024 * 1024) {
        size = 1024 * 1024;
    }

    // Create a copy of the input data that's null-terminated for safety
    // (some string operations might expect null termination)
    char *eh_frame_hdr = new char[size + 1];
    memcpy(eh_frame_hdr, data, size);
    eh_frame_hdr[size] = '\0';

    // The DwarfParser constructor takes:
    // - name: library name (for logging)
    // - image_base: base address of the loaded image
    // - eh_frame_hdr: pointer to the .eh_frame_hdr section
    //
    // We use the input data as the image base to create valid relative
    // pointers within the fuzzed data.
    const char *name = "fuzz_target";
    const char *image_base = eh_frame_hdr;  // Relative addresses are within fuzzed data

    // The DwarfParser constructor calls parse() internally, which is where
    // most of the interesting parsing happens. We wrap this in a try-catch
    // because the parser may throw on invalid data.
    try {
        DwarfParser parser(name, image_base, eh_frame_hdr);
        // If we get here, the parser successfully built an unwind table.
        // The parser allocates a FrameDesc table internally; destructor
        // will clean it up.
    } catch (...) {
        // Expected for malformed input - the parser may throw on invalid data
    }

    delete[] eh_frame_hdr;
    return 0;
}
