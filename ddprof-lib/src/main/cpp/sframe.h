/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SFRAME_H
#define _SFRAME_H

#include "dwarf.h"
#include <stddef.h>
#include <stdint.h>

#ifndef PT_GNU_SFRAME
#define PT_GNU_SFRAME 0x6474e554
#endif

// SFrame V2 magic, version, flags
const uint16_t SFRAME_MAGIC        = 0xDEE2;
const uint8_t  SFRAME_VERSION_2    = 2;
const uint8_t  SFRAME_F_FDE_SORTED = 0x01;

// ABI/architecture identifiers
const uint8_t SFRAME_ABI_AARCH64_ENDIAN_LITTLE = 2;
const uint8_t SFRAME_ABI_AMD64_ENDIAN_LITTLE   = 3;

// FDE info byte: bit 0 = FDE type (0=PCINC,1=PCMASK), bits 1-2 = FRE start address size
#define SFRAME_FUNC_FDE_TYPE(info) ((info) & 0x1)
#define SFRAME_FUNC_FRE_TYPE(info) (((info) >> 1) & 0x3)

// FRE info byte: bit 0 = CFA base (0=SP,1=FP), bits 1-2 = offset size, bit 3 = RA tracked, bit 4 = FP tracked
#define SFRAME_FRE_BASE_REG(info)    ((info) & 0x1)
#define SFRAME_FRE_OFFSET_SIZE(info) (((info) >> 1) & 0x3)
#define SFRAME_FRE_RA_TRACKED(info)  (((info) >> 3) & 0x1)
#define SFRAME_FRE_FP_TRACKED(info)  (((info) >> 4) & 0x1)

// FRE offset size codes
const int SFRAME_FRE_OFFSET_1B = 0;
const int SFRAME_FRE_OFFSET_2B = 1;
const int SFRAME_FRE_OFFSET_4B = 2;

// FRE start address size codes (from FDE info bits 1-2)
const int SFRAME_FRE_TYPE_ADDR1 = 0;
const int SFRAME_FRE_TYPE_ADDR2 = 1;
const int SFRAME_FRE_TYPE_ADDR4 = 2;

struct __attribute__((packed)) SFrameHeader {  // 28 bytes
    uint16_t magic;
    uint8_t  version;
    uint8_t  flags;
    uint8_t  abi_arch;
    int8_t   cfa_fixed_fp_offset;
    int8_t   cfa_fixed_ra_offset;  // -8 on x86_64; 0 on aarch64
    uint8_t  auxhdr_len;
    uint32_t num_fdes;
    uint32_t num_fres;
    uint32_t fre_len;
    uint32_t fdeoff;
    uint32_t freoff;
};

struct __attribute__((packed)) SFrameFDE {  // 20 bytes
    int32_t  start_addr;   // signed, relative to .sframe section start (V2)
    uint32_t func_size;
    uint32_t fre_off;      // byte offset into FRE sub-section
    uint32_t fre_num;      // number of FREs
    uint8_t  info;         // FDE type (bit 0) | FRE addr size (bits 1-2)
    uint8_t  rep_size;
    uint16_t padding;
};

class SFrameParser {
  private:
    const char* _name;
    const char* _section_base;
    size_t      _section_size;
    u32         _section_offset;

    int        _capacity;
    int        _count;
    FrameDesc* _table;
    int        _linked_frame_size;  // for aarch64 GCC vs Clang detection; -1 = undetected

    bool       parseFDE(const SFrameHeader* hdr, const SFrameFDE* fde,
                        const char* fre_section, const char* fre_end);
    FrameDesc* addRecord(u32 loc, u32 cfa, int fp_off, int pc_off);

  public:
    SFrameParser(const char* name, const char* section_base,
                 size_t section_size, u32 section_offset);
    ~SFrameParser();

    // Returns false when the section is invalid or unsupported (triggers DWARF fallback).
    bool parse();

    // Transfers table ownership to caller. Nulls _table so the destructor does not double-free.
    // Call only after a successful parse(). Caller must free() the returned pointer.
    FrameDesc* table();
    int count() const { return _count; }

    const FrameDesc& detectedDefaultFrame() const;
};

#endif  // _SFRAME_H
