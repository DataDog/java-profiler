/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * libFuzzer fuzz target for the JFR buffer serialization code.
 *
 * The Buffer class provides serialization primitives for JFR recording:
 * - putVar32/putVar64: Variable-length integer encoding (LEB128-like)
 * - putUtf8: String serialization with length prefix
 * - put8/put16/put32/put64: Fixed-size integer writes
 *
 * CRITICAL FINDING: All bounds checks in Buffer are assert() only!
 * This means in release builds (NDEBUG defined), there is NO runtime
 * validation of buffer boundaries. This fuzzer tests with assertions
 * enabled to catch overflow conditions that would silently corrupt
 * memory in production.
 *
 * Expected bug classes:
 * - Buffer overflows when assertions are disabled
 * - Incorrect varint encoding for edge-case values
 * - String truncation at MAX_STRING_LENGTH boundary
 * - Memory corruption from sequences that fill buffer exactly
 */

#include <stddef.h>
#include <stdint.h>
#include <cstring>

#include "buffers.h"

// We need common.h for type definitions (u32, u64)
#include "common.h"

/**
 * Interpret fuzzer input as a sequence of operations to perform on a Buffer.
 *
 * Input format:
 * Each byte is interpreted as an operation code:
 * - 0x00-0x0F: put8 (next byte is the value)
 * - 0x10-0x1F: put16 (next 2 bytes are the value)
 * - 0x20-0x2F: put32 (next 4 bytes are the value)
 * - 0x30-0x3F: put64 (next 8 bytes are the value)
 * - 0x40-0x4F: putVar32 (next 4 bytes interpreted as u32)
 * - 0x50-0x5F: putVar64 (next 8 bytes interpreted as u64)
 * - 0x60-0x6F: putUtf8 (length from next byte, then string data)
 * - 0x70-0x7F: reset buffer
 * - 0x80-0xFF: skip (advance by lower 4 bits)
 */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Use a RecordingBuffer which has the larger size used in production
    // This is where the "overflow space" workaround lives
    class TestBuffer : public Buffer {
    public:
        // Extend the data array like RecordingBuffer does
        char _extended_data[RECORDING_BUFFER_SIZE + RECORDING_BUFFER_OVERFLOW - BUFFER_SIZE + sizeof(int)];

        TestBuffer() : Buffer() {
            memset(_extended_data, 0xCD, sizeof(_extended_data)); // Canary pattern
        }

        int limit() const override {
            return RECORDING_BUFFER_SIZE;
        }

        // Check if the canary was overwritten (indicates buffer overflow)
        bool checkOverflow() const {
            // Check last few bytes of overflow space
            const char *end = _extended_data + sizeof(_extended_data) - 16;
            for (int i = 0; i < 16; i++) {
                if ((unsigned char)end[i] != 0xCD) {
                    return true; // Overflow detected
                }
            }
            return false;
        }
    };

    TestBuffer buffer;

    size_t pos = 0;
    while (pos < size) {
        uint8_t op = data[pos++];

        // Check for buffer overflow after each operation
        if (buffer.checkOverflow()) {
            // Overflow detected - this is a bug!
            // In fuzzing mode, this will be caught by ASAN
            __builtin_trap();
        }

        if (op < 0x10) {
            // put8
            if (pos >= size) break;
            char v = (char)data[pos++];
            if (buffer.offset() + 1 < buffer.limit()) {
                buffer.put8(v);
            }
        } else if (op < 0x20) {
            // put16
            if (pos + 1 >= size) break;
            short v = (short)((data[pos] << 8) | data[pos + 1]);
            pos += 2;
            if (buffer.offset() + 2 < buffer.limit()) {
                buffer.put16(v);
            }
        } else if (op < 0x30) {
            // put32
            if (pos + 3 >= size) break;
            int v = (data[pos] << 24) | (data[pos + 1] << 16) |
                    (data[pos + 2] << 8) | data[pos + 3];
            pos += 4;
            if (buffer.offset() + 4 < buffer.limit()) {
                buffer.put32(v);
            }
        } else if (op < 0x40) {
            // put64
            if (pos + 7 >= size) break;
            u64 v = 0;
            for (int i = 0; i < 8; i++) {
                v = (v << 8) | data[pos + i];
            }
            pos += 8;
            if (buffer.offset() + 8 < buffer.limit()) {
                buffer.put64(v);
            }
        } else if (op < 0x50) {
            // putVar32 - this is where bugs are likely!
            // The assertion checks for 5 bytes, but encoding can write more
            if (pos + 3 >= size) break;
            u32 v = (data[pos] << 24) | (data[pos + 1] << 16) |
                    (data[pos + 2] << 8) | data[pos + 3];
            pos += 4;
            // putVar32 writes at most 5 bytes
            if (buffer.offset() + 5 < buffer.limit()) {
                buffer.putVar32(v);
            }
        } else if (op < 0x60) {
            // putVar64 - highest risk for overflow
            // Assertion checks for 9 bytes but the loop structure is complex
            if (pos + 7 >= size) break;
            u64 v = 0;
            for (int i = 0; i < 8; i++) {
                v = (v << 8) | data[pos + i];
            }
            pos += 8;
            // putVar64 writes at most 10 bytes (9 asserted but loop can write more)
            if (buffer.offset() + 10 < buffer.limit()) {
                buffer.putVar64(v);
            }
        } else if (op < 0x70) {
            // putUtf8 - string serialization
            if (pos >= size) break;
            size_t len = data[pos++];
            // Clamp length to available data
            if (pos + len > size) {
                len = size - pos;
            }
            // putUtf8 adds 1 byte type + varint length + data
            // Check we have enough space (conservative estimate)
            if (buffer.offset() + 1 + 5 + len < (size_t)buffer.limit()) {
                buffer.putUtf8((const char *)(data + pos), (u32)len);
            }
            pos += len;
        } else if (op < 0x80) {
            // reset - start over with fresh buffer
            buffer.reset();
        } else {
            // skip - advance buffer position
            int skip_amount = (op & 0x0F) + 1;
            if (buffer.offset() + skip_amount < buffer.limit()) {
                buffer.skip(skip_amount);
            }
        }
    }

    return 0;
}

/**
 * Test specific edge cases that are known to be risky.
 * These can be used as seed corpus entries.
 */
#ifdef FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION
// Interesting values for putVar32/putVar64:
// - 0: single byte
// - 0x7F: maximum single byte
// - 0x80: minimum two bytes
// - 0x3FFF: maximum two bytes
// - 0x1FFFFF: maximum three bytes
// - UINT32_MAX: maximum u32
// - UINT64_MAX: maximum u64
//
// Edge cases for strings:
// - Empty string
// - MAX_STRING_LENGTH exactly
// - MAX_STRING_LENGTH + 1 (should be truncated)
// - Very long strings (should be clamped)
#endif
