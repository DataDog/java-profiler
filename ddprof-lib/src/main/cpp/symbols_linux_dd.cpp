/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __linux__

#include "symbols_linux_dd.h"
#include <elf.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// GNU build-id extraction implementation
//
// The build-id is a unique identifier embedded in ELF binaries and shared libraries.
// It is stored in a PT_NOTE program header segment as an ELF note with type NT_GNU_BUILD_ID.
//
// References:
// - ELF Specification: https://refspecs.linuxfoundation.org/elf/elf.pdf
// - ELF Note Section: https://refspecs.linuxfoundation.org/LSB_5.0.0/LSB-Core-generic/LSB-Core-generic/noteobject.html
// - GNU build-id: https://fedoraproject.org/wiki/Releases/FeatureBuildId
// - GNU binutils ld --build-id: https://sourceware.org/binutils/docs/ld/Options.html
// - readelf(1) --notes: https://man7.org/linux/man-pages/man1/readelf.1.html
//
// Build-ID format:
// - Located in PT_NOTE program header segments (p_type == PT_NOTE)
// - Stored as ELF note with:
//   - n_namesz = 4 (length of "GNU\0")
//   - n_descsz = build-id length (typically 20 bytes for SHA1)
//   - n_type = NT_GNU_BUILD_ID (3)
//   - name = "GNU\0"
//   - desc = build-id bytes
// - All fields are 4-byte aligned as per ELF note format

// GNU build-id note constants
#define NT_GNU_BUILD_ID 3
#define GNU_BUILD_ID_NAME "GNU"

namespace ddprof {

char* SymbolsLinux::extractBuildId(const char* file_path, size_t* build_id_len) {
    if (!file_path || !build_id_len) {
        return nullptr;
    }

    int fd = open(file_path, O_RDONLY);
    if (fd < 0) {
        return nullptr;
    }

    struct stat st;
    if (fstat(fd, &st) < 0) {
        close(fd);
        return nullptr;
    }

    void* elf_base = mmap(nullptr, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);

    if (elf_base == MAP_FAILED) {
        return nullptr;
    }

    char* result = extractBuildIdFromMemory(elf_base, st.st_size, build_id_len);

    munmap(elf_base, st.st_size);
    return result;
}

char* SymbolsLinux::extractBuildIdFromMemory(const void* elf_base, size_t elf_size, size_t* build_id_len) {
    if (!elf_base || !build_id_len || elf_size < sizeof(Elf64_Ehdr)) {
        return nullptr;
    }

    const Elf64_Ehdr* ehdr = static_cast<const Elf64_Ehdr*>(elf_base);

    // Verify ELF magic
    if (memcmp(ehdr->e_ident, ELFMAG, SELFMAG) != 0) {
        return nullptr;
    }

    // Only handle 64-bit ELF for now
    if (ehdr->e_ident[EI_CLASS] != ELFCLASS64) {
        return nullptr;
    }

    // Check if we have program headers
    if (ehdr->e_phoff == 0 || ehdr->e_phnum == 0) {
        return nullptr;
    }

    // Verify program header table is within file bounds
    if (ehdr->e_phoff + ehdr->e_phnum * sizeof(Elf64_Phdr) > elf_size) {
        return nullptr;
    }

    // Verify program header offset is properly aligned
    if (ehdr->e_phoff % alignof(Elf64_Phdr) != 0) {
        return nullptr;
    }

    const char* base = static_cast<const char*>(elf_base);
    const Elf64_Phdr* phdr = reinterpret_cast<const Elf64_Phdr*>(base + ehdr->e_phoff);

    // Search for PT_NOTE segments
    for (int i = 0; i < ehdr->e_phnum; i++) {
        if (phdr[i].p_type == PT_NOTE && phdr[i].p_filesz > 0) {
            // Ensure note segment is within file bounds
            if (phdr[i].p_offset + phdr[i].p_filesz > elf_size) {
                continue;
            }

            const void* note_data = base + phdr[i].p_offset;
            const uint8_t* build_id_bytes = findBuildIdInNotes(note_data, phdr[i].p_filesz, build_id_len);

            if (build_id_bytes) {
                return buildIdToHex(build_id_bytes, *build_id_len);
            }
        }
    }

    return nullptr;
}

const uint8_t* SymbolsLinux::findBuildIdInNotes(const void* note_data, size_t note_size, size_t* build_id_len) {
    const char* data = static_cast<const char*>(note_data);
    size_t offset = 0;

    // Parse ELF note entries within the PT_NOTE segment
    // Each note has the structure:
    //   typedef struct {
    //     Elf64_Word n_namesz;  // Length of name field (including null terminator)
    //     Elf64_Word n_descsz;  // Length of descriptor (build-id bytes)
    //     Elf64_Word n_type;    // Note type (NT_GNU_BUILD_ID == 3)
    //     // Followed by name (4-byte aligned)
    //     // Followed by descriptor (4-byte aligned)
    //   } Elf64_Nhdr;
    // Reference: https://refspecs.linuxfoundation.org/LSB_5.0.0/LSB-Core-generic/LSB-Core-generic/noteobject.html
    while (offset < note_size) {
        // Ensure there is enough space for the note header itself
        if (note_size - offset < sizeof(Elf64_Nhdr)) {
            break;
        }

        const Elf64_Nhdr* nhdr = reinterpret_cast<const Elf64_Nhdr*>(data + offset);

        // Calculate aligned sizes (4-byte alignment as per ELF spec)
        size_t name_size_aligned = (nhdr->n_namesz + 3) & ~static_cast<size_t>(3);
        size_t desc_size_aligned = (nhdr->n_descsz + 3) & ~static_cast<size_t>(3);

        // Check bounds using subtraction to avoid overflow
        size_t remaining = note_size - offset - sizeof(Elf64_Nhdr);
        if (name_size_aligned > remaining) {
            break;
        }
        remaining -= name_size_aligned;
        if (desc_size_aligned > remaining) {
            break;
        }

        // Check if this is a GNU build-id note
        if (nhdr->n_type == NT_GNU_BUILD_ID && nhdr->n_namesz > 0 && nhdr->n_descsz > 0) {
            const char* name = data + offset + sizeof(Elf64_Nhdr);

            // Verify GNU build-id name (including null terminator)
            if (nhdr->n_namesz == 4 && strncmp(name, GNU_BUILD_ID_NAME, 3) == 0 && name[3] == '\0') {
                const uint8_t* desc = reinterpret_cast<const uint8_t*>(data + offset + sizeof(Elf64_Nhdr) + name_size_aligned);
                *build_id_len = nhdr->n_descsz;
                return desc;
            }
        }

        offset += sizeof(Elf64_Nhdr) + name_size_aligned + desc_size_aligned;
    }

    return nullptr;
}

char* SymbolsLinux::buildIdToHex(const uint8_t* build_id_bytes, size_t byte_len) {
    if (!build_id_bytes || byte_len == 0) {
        return nullptr;
    }

    // Allocate string for hex representation (2 chars per byte + null terminator)
    char* hex_str = static_cast<char*>(malloc(byte_len * 2 + 1));
    if (!hex_str) {
        return nullptr;
    }

    for (size_t i = 0; i < byte_len; i++) {
        snprintf(hex_str + i * 2, 3, "%02x", build_id_bytes[i]);
    }

    hex_str[byte_len * 2] = '\0';
    return hex_str;
}

} // namespace ddprof

#endif // __linux__
