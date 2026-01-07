/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SYMBOLS_LINUX_DD_H
#define _SYMBOLS_LINUX_DD_H

#ifdef __linux__

#include <cstddef>

namespace ddprof {

/**
 * Datadog-specific extensions to Linux symbol handling.
 * Provides build-id extraction for remote symbolication support.
 */
class SymbolsLinux {
public:
    /**
     * Extract GNU build-id from ELF file on disk.
     * Build-id is stored in .note.gnu.build-id section and provides
     * unique identification for libraries/executables for remote symbolication.
     *
     * @param file_path Path to ELF file
     * @param build_id_len Output parameter for build-id length in bytes
     * @return Hex-encoded build-id string (caller must free), or NULL on error
     */
    static char* extractBuildId(const char* file_path, size_t* build_id_len);

    /**
     * Extract GNU build-id from ELF file already mapped in memory.
     *
     * @param elf_base Base address of mapped ELF file
     * @param elf_size Size of mapped ELF file
     * @param build_id_len Output parameter for build-id length in bytes
     * @return Hex-encoded build-id string (caller must free), or NULL on error
     */
    static char* extractBuildIdFromMemory(const void* elf_base, size_t elf_size, size_t* build_id_len);

private:
    /**
     * Convert binary build-id to hex string.
     *
     * @param build_id_bytes Raw build-id bytes
     * @param byte_len Length of raw build-id in bytes
     * @return Hex-encoded string (caller must free)
     */
    static char* buildIdToHex(const uint8_t* build_id_bytes, size_t byte_len);

    /**
     * Parse ELF note section to find GNU build-id.
     *
     * @param note_data Start of note section data
     * @param note_size Size of note section
     * @param build_id_len Output parameter for build-id length
     * @return Raw build-id bytes, or NULL if not found
     */
    static const uint8_t* findBuildIdInNotes(const void* note_data, size_t note_size, size_t* build_id_len);
};

} // namespace ddprof

#endif // __linux__

#endif // _SYMBOLS_LINUX_DD_H
