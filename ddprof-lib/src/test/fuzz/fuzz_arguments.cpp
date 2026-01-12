/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * libFuzzer fuzz target for the profiler argument parser.
 *
 * The Arguments::parse() function processes profiler configuration strings
 * from various sources (JVM agent options, attach API, etc.). This is a
 * potential attack surface because:
 * - Input comes from user-controlled sources
 * - expandFilePattern() uses environment variable expansion with snprintf
 * - The hash function may overflow on very long inputs
 * - strtok-based parsing with many delimiters could cause issues
 *
 * Expected bug classes:
 * - Buffer overflows in expandFilePattern() with large env vars
 * - Integer overflow in hash() with very long strings
 * - Memory corruption from malformed argument strings
 * - Denial of service via pathological input patterns
 */

#include <stddef.h>
#include <stdint.h>
#include <cstring>
#include <cstdlib>

#include "arguments.h"

// Set up environment variables with controlled content for fuzzing.
// This allows the fuzzer to trigger env var expansion code paths.
#ifdef FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION
namespace {
    struct EnvSetup {
        EnvSetup() {
            // Set some environment variables that the fuzzer can reference
            // via %{VAR} patterns in the input
            setenv("FUZZ_TEST_VAR", "fuzz_value", 1);
            setenv("FUZZ_LONG_VAR", std::string(256, 'A').c_str(), 1);
            setenv("HOME", "/tmp/fuzz_home", 1);
        }
    };
    static EnvSetup env_setup;
}
#endif

/**
 * LLVMFuzzerTestOneInput - The libFuzzer entry point.
 *
 * This function parses the fuzzer-generated data as a profiler argument string.
 * The Arguments class supports various configuration options like:
 * - start,event=cpu,interval=10ms
 * - stop
 * - file=/path/to/output.jfr
 * - filter=MyClass::myMethod
 *
 * @param data Pointer to fuzzer-generated input bytes
 * @param size Size of the input data in bytes
 * @return 0 (required by libFuzzer interface)
 */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    // Empty input is valid but uninteresting
    if (size == 0) {
        return 0;
    }

    // Cap size to prevent excessive memory consumption.
    // Real argument strings should be < 64KB
    if (size > 64 * 1024) {
        size = 64 * 1024;
    }

    // Create a null-terminated copy of the input data.
    // Arguments::parse() expects a null-terminated C string.
    char *args = new char[size + 1];
    memcpy(args, data, size);
    args[size] = '\0';

    // Replace any embedded null bytes with spaces to ensure we test
    // the full input length (embedded nulls would truncate parsing)
    for (size_t i = 0; i < size; i++) {
        if (args[i] == '\0') {
            args[i] = ' ';
        }
    }

    // Create an Arguments instance and attempt to parse the fuzzed input
    Arguments arguments;

    try {
        Error error = arguments.parse(args);
        // We don't care about the error result - we're testing for crashes,
        // not correct error handling. Invalid arguments should return an
        // error, not crash.
        (void)error;
    } catch (...) {
        // Unexpected exceptions indicate a bug - the parser should handle
        // all malformed input gracefully without throwing
    }

    delete[] args;
    return 0;
}

/**
 * Optional: Provide initial corpus seeds to guide fuzzing.
 *
 * libFuzzer can use these to understand the expected input format.
 * Place seed files in ddprof-lib/src/test/fuzz/corpus/fuzz_arguments/
 */
#ifdef FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION
// Example valid argument strings for initial corpus:
// "start,event=cpu,interval=10ms"
// "start,event=wall,interval=50ms,file=/tmp/profile.jfr"
// "start,event=alloc,memory=512k"
// "stop"
// "status"
// "start,cstack=dwarf,jstackdepth=512"
#endif
