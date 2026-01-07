/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __linux__

#include "elfBuildId.h"
#include <elf.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// GNU build-id note constants
#define NT_GNU_BUILD_ID 3
#define GNU_BUILD_ID_NAME "GNU"

char* ElfBuildIdExtractor::extractBuildId(const char* file_path, size_t* build_id_len) {
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

char* ElfBuildIdExtractor::extractBuildIdFromMemory(const void* elf_base, size_t elf_size, size_t* build_id_len) {
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

const uint8_t* ElfBuildIdExtractor::findBuildIdInNotes(const void* note_data, size_t note_size, size_t* build_id_len) {
    const char* data = static_cast<const char*>(note_data);
    size_t offset = 0;

    while (offset + sizeof(Elf64_Nhdr) < note_size) {
        const Elf64_Nhdr* nhdr = reinterpret_cast<const Elf64_Nhdr*>(data + offset);

        // Calculate aligned sizes
        size_t name_size_aligned = (nhdr->n_namesz + 3) & ~3;
        size_t desc_size_aligned = (nhdr->n_descsz + 3) & ~3;

        // Check bounds
        if (offset + sizeof(Elf64_Nhdr) + name_size_aligned + desc_size_aligned > note_size) {
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

char* ElfBuildIdExtractor::buildIdToHex(const uint8_t* build_id_bytes, size_t byte_len) {
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

#endif // __linux__