/*
 * Copyright The async-profiler authors
 * Copyright 2025, 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _DWARF_H
#define _DWARF_H

#include <stddef.h>
#include <string.h>
#include "arch.h"


const int DW_REG_PLT = 128;      // denotes special rule for PLT entries
const int DW_REG_INVALID = 255;  // denotes unsupported configuration

const int DW_PC_OFFSET = 1;
const int DW_SAME_FP = 0x80000000;
const int DW_LINK_REGISTER = 0x80000000;
const int DW_STACK_SLOT = sizeof(void*);


#if defined(__x86_64__)

#define DWARF_SUPPORTED true

const int DW_REG_FP = 6;
const int DW_REG_SP = 7;
const int DW_REG_PC = 16;
const int EMPTY_FRAME_SIZE = DW_STACK_SLOT;
const int LINKED_FRAME_SIZE = 2 * DW_STACK_SLOT;
const int LINKED_FRAME_CLANG_SIZE = LINKED_FRAME_SIZE;
const int INITIAL_PC_OFFSET = -EMPTY_FRAME_SIZE;

#elif defined(__i386__)

#define DWARF_SUPPORTED true

const int DW_REG_FP = 5;
const int DW_REG_SP = 4;
const int DW_REG_PC = 8;
const int EMPTY_FRAME_SIZE = DW_STACK_SLOT;
const int LINKED_FRAME_SIZE = 2 * DW_STACK_SLOT;
const int LINKED_FRAME_CLANG_SIZE = LINKED_FRAME_SIZE;
const int INITIAL_PC_OFFSET = -EMPTY_FRAME_SIZE;

#elif defined(__aarch64__)

#define DWARF_SUPPORTED true

const int DW_REG_FP = 29;
const int DW_REG_SP = 31;
const int DW_REG_PC = 30;
const int EMPTY_FRAME_SIZE = 0;
const int LINKED_FRAME_SIZE = 0;
const int LINKED_FRAME_CLANG_SIZE = 2 * DW_STACK_SLOT;  // clang uses different frame layout than GCC
const int INITIAL_PC_OFFSET = DW_LINK_REGISTER;

#else

#define DWARF_SUPPORTED false

const int DW_REG_FP = 0;
const int DW_REG_SP = 1;
const int DW_REG_PC = 2;
const int EMPTY_FRAME_SIZE = 0;
const int LINKED_FRAME_SIZE = 0;
const int LINKED_FRAME_CLANG_SIZE = LINKED_FRAME_SIZE;
const int INITIAL_PC_OFFSET = DW_LINK_REGISTER;

#endif


struct FrameDesc {
    u32 loc;
    u32 cfa;
    int fp_off;
    int pc_off;

    static FrameDesc empty_frame;
    static FrameDesc default_frame;
    static FrameDesc default_clang_frame;
    static FrameDesc no_dwarf_frame;

    // Best-guess fallback frame layout when a PC doesn't map to any known library.
    // Per-library detection overrides this: on macOS via __eh_frame section presence,
    // on Linux via DwarfParser::detectedDefaultFrame().
    static const FrameDesc& fallback_default_frame() {
#if defined(__APPLE__) && defined(__aarch64__)
        return default_clang_frame;
#else
        return default_frame;
#endif
    }

    static int comparator(const void* p1, const void* p2) {
        FrameDesc* fd1 = (FrameDesc*)p1;
        FrameDesc* fd2 = (FrameDesc*)p2;
        return (int)(fd1->loc - fd2->loc);
    }
};


class DwarfParser {
  private:
    const char* _name;
    const char* _image_base;
    const char* _ptr;
    // Read window [_section_start, _section_end). Both paths set this window:
    // - parseEhFrame(): set to the .eh_frame section bounds.
    // - parse(): set to the full ELF image bounds [image_base, image_end) so
    //   that FDE reads into the adjacent .eh_frame are bounded to mapped memory.
    const char* _section_start;
    const char* _section_end;

    int _capacity;
    int _count;
    FrameDesc* _table;
    FrameDesc* _prev;

    u32 _code_align;
    int _data_align;
    int _linked_frame_size;  // detected from FP-based DWARF entries; -1 = undetected
    bool _has_z_augmentation;

    // True if `size` bytes can be read at _ptr without leaving the section.
    // Guards against both over-reads (past _section_end) and under-reads
    // (_ptr moved before _section_start by an untrusted offset).
    bool canRead(size_t size) const {
        return _ptr >= _section_start && _ptr <= _section_end &&
               size <= (size_t)(_section_end - _ptr);
    }

    u8 get8() {
        if (!canRead(1)) {
            _ptr = _section_end;
            return 0;
        }
        return *_ptr++;
    }

    u16 get16() {
        if (!canRead(2)) {
            _ptr = _section_end;
            return 0;
        }
        const char* ptr = _ptr;
        _ptr += 2;
        u16 result;
        memcpy(&result, ptr, sizeof(u16));
        return result;
    }

    u32 get32() {
        if (!canRead(4)) {
            _ptr = _section_end;
            return 0;
        }
        const char* ptr = _ptr;
        _ptr += 4;
        u32 result;
        memcpy(&result, ptr, sizeof(u32));
        return result;
    }

    u32 getLeb() {
        u32 result = 0;
        for (u32 shift = 0; canRead(1) && shift < 32; shift += 7) {
            u8 b = *_ptr++;
            result |= (u32)(b & 0x7f) << shift;
            if ((b & 0x80) == 0) {
                break;
            }
        }
        return result;
    }

    u32 getLeb(const char* end) {
        if (end > _section_end) end = _section_end;
        u32 result = 0;
        for (u32 shift = 0; _ptr < end && shift < 32; shift += 7) {
            u8 b = *_ptr++;
            result |= (u32)(b & 0x7f) << shift;
            if ((b & 0x80) == 0) {
                return result;
            }
        }
        return result;
    }

    int getSLeb() {
        int result = 0;
        for (u32 shift = 0; canRead(1) && shift < 32; shift += 7) {
            u8 b = *_ptr++;
            // Compute in unsigned to avoid signed left-shift overflow (UB) for
            // large shift values; the result is reinterpreted as signed below.
            result |= (int)((u32)(b & 0x7f) << shift);
            if ((b & 0x80) == 0) {
                if ((b & 0x40) != 0 && (shift += 7) < 32) {
                    result |= (int)(~0U << shift);
                }
                break;
            }
        }
        return result;
    }

    int getSLeb(const char* end) {
        if (end > _section_end) end = _section_end;
        int result = 0;
        for (u32 shift = 0; _ptr < end && shift < 32; shift += 7) {
            u8 b = *_ptr++;
            // Compute in unsigned to avoid signed left-shift overflow (UB) for
            // large shift values; the result is reinterpreted as signed below.
            result |= (int)((u32)(b & 0x7f) << shift);
            if ((b & 0x80) == 0) {
                if ((b & 0x40) != 0 && (shift += 7) < 32) {
                    result |= (int)(~0U << shift);
                }
                return result;
            }
        }
        return result;
    }

    void skipLeb() {
        while (canRead(1) && (*_ptr++ & 0x80)) {}
    }

    const char* getPtr() {
        const char* ptr = _ptr;
        if (!canRead(4)) {
            _ptr = _section_end;
            return ptr;
        }
        int offset;
        memcpy(&offset, _ptr, sizeof(int));
        _ptr += 4;
        return ptr + offset;
    }

    void init(const char* name, const char* image_base);
    void parse(const char* eh_frame_hdr, size_t size, const char* image_end);
    void parseEhFrame(const char* eh_frame, size_t size);
    void parseCie();
    void parseFde();
    void parseInstructions(u32 loc, const char* end);
    int parseExpression();

    void addRecord(u32 loc, u32 cfa_reg, int cfa_off, int fp_off, int pc_off);
    FrameDesc* addRecordRaw(u32 loc, int cfa, int fp_off, int pc_off);

  public:
    // Tag to disambiguate the .eh_frame_hdr (binary-search index) constructor
    // from the raw .eh_frame constructor below: with a size added, the two
    // would otherwise share a signature.
    struct EhFrameHdrTag {};
    DwarfParser(const char* name, const char* image_base, const char* eh_frame_hdr, size_t eh_frame_hdr_size, EhFrameHdrTag, const char* image_end);
    DwarfParser(const char* name, const char* image_base, const char* eh_frame, size_t eh_frame_size);

    // Ownership of the returned pointer transfers to the caller.
    // The caller is responsible for freeing it with free() (not delete[]).
    // DwarfParser has no destructor; _table is left dangling after this call is used.
    FrameDesc* table() const {
        return _table;
    }

    int count() const {
        return _count;
    }

    const FrameDesc& detectedDefaultFrame() const {
        if (_linked_frame_size == LINKED_FRAME_CLANG_SIZE && LINKED_FRAME_CLANG_SIZE != LINKED_FRAME_SIZE) {
            return FrameDesc::default_clang_frame;
        }
        return FrameDesc::default_frame;
    }
};

#endif // _DWARF_H
