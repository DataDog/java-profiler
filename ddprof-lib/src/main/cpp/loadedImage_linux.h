/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Linux-only: ELF image views built from program-header tables. Include only
// from _linux translation units; there is no non-Linux counterpart.
#ifdef __linux__

#ifndef _LOADED_IMAGE_LINUX_H
#define _LOADED_IMAGE_LINUX_H

#include <stdint.h>

#include <elf.h>

#include "os.h"

typedef Elf64_Phdr ElfProgramHeader;

// A loaded ELF image, described by its program headers. Only the file-backed
// parts of its PT_LOAD segments are known to be mapped.
class LoadedImage {
  private:
    const ElfProgramHeader* _ph;
    int _phnum;
    uintptr_t _load_bias;

  public:
    LoadedImage(const ElfProgramHeader* ph, int phnum, uintptr_t load_bias)
        : _ph(ph), _phnum(phnum), _load_bias(load_bias) {}

    bool address(uintptr_t vaddr, uintptr_t& out) const {
        return !__builtin_add_overflow(_load_bias, vaddr, &out);
    }

    // True if [addr, addr + size) lies inside a file-backed PT_LOAD.
    bool readable(uintptr_t addr, size_t size) const {
        for (int i = 0; i < _phnum; i++) {
            if (_ph[i].p_type != PT_LOAD) continue;
            uintptr_t start;
            if (!address(_ph[i].p_vaddr, start)) continue;
            if (addr >= start && addr - start <= _ph[i].p_filesz
                && size <= _ph[i].p_filesz - (addr - start)) {
                return true;
            }
        }
        return false;
    }

    const ElfProgramHeader* find(uint32_t type) const {
        for (int i = 0; i < _phnum; i++) {
            if (_ph[i].p_type == type) return &_ph[i];
        }
        return NULL;
    }

    // A pointer from the dynamic section. glibc relocates them in place, musl
    // and the vDSO do not; an unrelocated one is a vaddr below the image. The
    // same test as ElfParser::dyn_ptr().
    bool dynamicPointer(uintptr_t d_ptr, uintptr_t& out) const {
        uintptr_t min_vaddr = UINTPTR_MAX;
        for (int i = 0; i < _phnum; i++) {
            if (_ph[i].p_type == PT_LOAD && _ph[i].p_vaddr < min_vaddr) min_vaddr = _ph[i].p_vaddr;
        }
        if (min_vaddr == UINTPTR_MAX) return false;

        uintptr_t relocation_threshold;
        if (!address(min_vaddr & ~OS::page_mask, relocation_threshold)) return false;
        if (d_ptr < relocation_threshold) return address(d_ptr, out);

        out = d_ptr;
        return true;
    }
};

#endif // _LOADED_IMAGE_LINUX_H

#endif // __linux__
