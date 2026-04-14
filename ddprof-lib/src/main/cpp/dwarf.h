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

    int _capacity;
    int _count;
    FrameDesc* _table;
    FrameDesc* _prev;

    u32 _code_align;
    int _data_align;
    int _linked_frame_size;  // detected from FP-based DWARF entries; -1 = undetected
    bool _has_z_augmentation;

    const char* add(size_t size) {
        const char* ptr = _ptr;
        _ptr = ptr + size;
        return ptr;
    }

    u8 get8() {
        return *_ptr++;
    }

    u16 get16() {
        const char* ptr = add(2);
        u16 result;
        memcpy(&result, ptr, sizeof(u16));
        return result;
    }

    u32 get32() {
        const char* ptr = add(4);
        u32 result;
        memcpy(&result, ptr, sizeof(u32));
        return result;
    }

    u32 getLeb() {
        u32 result = 0;
        for (u32 shift = 0; ; shift += 7) {
            u8 b = *_ptr++;
            result |= (b & 0x7f) << shift;
            if ((b & 0x80) == 0) {
                return result;
            }
        }
    }

    u32 getLeb(const char* end) {
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
        for (u32 shift = 0; ; shift += 7) {
            u8 b = *_ptr++;
            result |= (b & 0x7f) << shift;
            if ((b & 0x80) == 0) {
                if ((b & 0x40) != 0 && (shift += 7) < 32) {
                    result |= ~0U << shift;
                }
                return result;
            }
        }
    }

    int getSLeb(const char* end) {
        int result = 0;
        for (u32 shift = 0; _ptr < end; shift += 7) {
            u8 b = *_ptr++;
            result |= (b & 0x7f) << shift;
            if ((b & 0x80) == 0) {
                if ((b & 0x40) != 0 && (shift += 7) < 32) {
                    result |= ~0U << shift;
                }
                return result;
            }
        }
        return result;
    }

    void skipLeb() {
        while (*_ptr++ & 0x80) {}
    }

    const char* getPtr() {
        const char* ptr = _ptr;
        const char* offset_ptr = add(4);
        int offset;
        memcpy(&offset, offset_ptr, sizeof(int));
        return ptr + offset;
    }

    void init(const char* name, const char* image_base);
    void parse(const char* eh_frame_hdr);
    void parseEhFrame(const char* eh_frame, size_t size);
    void parseCie();
    void parseFde();
    void parseInstructions(u32 loc, const char* end);
    int parseExpression();

    void addRecord(u32 loc, u32 cfa_reg, int cfa_off, int fp_off, int pc_off);
    FrameDesc* addRecordRaw(u32 loc, int cfa, int fp_off, int pc_off);

  public:
    DwarfParser(const char* name, const char* image_base, const char* eh_frame_hdr);
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
