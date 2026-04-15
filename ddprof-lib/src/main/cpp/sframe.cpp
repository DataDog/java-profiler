/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "sframe.h"
#include <climits>
#include <cstdlib>
#include <cstring>

SFrameParser::SFrameParser(const char* name, const char* section_base,
                           size_t section_size, u32 section_offset)
    : _name(name),
      _section_base(section_base),
      _section_size(section_size),
      _section_offset(section_offset),
      _capacity(128),
      _count(0),
      _table(static_cast<FrameDesc*>(malloc(128 * sizeof(FrameDesc)))),
      _linked_frame_size(-1) {}

SFrameParser::~SFrameParser() {
    free(_table);  // safe: free(nullptr) is a no-op; table() nulls _table on success
}

FrameDesc* SFrameParser::table() {
    FrameDesc* t = _table;
    _table = nullptr;
    return t;
}

const FrameDesc& SFrameParser::detectedDefaultFrame() const {
    if (_linked_frame_size == LINKED_FRAME_CLANG_SIZE &&
        LINKED_FRAME_CLANG_SIZE != LINKED_FRAME_SIZE) {
        return FrameDesc::default_clang_frame;
    }
    return FrameDesc::default_frame;
}

FrameDesc* SFrameParser::addRecord(u32 loc, u32 cfa, int fp_off, int pc_off) {
    if (!_table) return nullptr;  // constructor malloc failed
    if (_count >= _capacity) {
        if (_capacity > (INT_MAX / 2)) return nullptr;  // overflow guard
        FrameDesc* resized = static_cast<FrameDesc*>(
            realloc(_table, _capacity * 2 * sizeof(FrameDesc)));
        if (!resized) return nullptr;
        _capacity *= 2;
        _table = resized;
    }
    FrameDesc* fd = &_table[_count++];
    fd->loc    = loc;
    fd->cfa    = cfa;
    fd->fp_off = fp_off;
    fd->pc_off = pc_off;
    return fd;
}

bool SFrameParser::parseFDE(const SFrameHeader* hdr, const SFrameFDE* fde,
                             const char* fre_section, const char* fre_end) {
    // Determine FRE start address size
    int addr_size;
    switch (SFRAME_FUNC_FRE_TYPE(fde->info)) {
        case SFRAME_FRE_TYPE_ADDR1: addr_size = 1; break;
        case SFRAME_FRE_TYPE_ADDR2: addr_size = 2; break;
        case SFRAME_FRE_TYPE_ADDR4: addr_size = 4; break;
        default: return false;
    }

    const char* fre_ptr = fre_section + fde->fre_off;

    for (uint32_t j = 0; j < fde->fre_num; j++) {
        // (a) Entry-level bounds check
        if (fre_ptr >= fre_end) return false;

        // (b) Read FRE start address offset (unsigned)
        if (fre_ptr + addr_size > fre_end) return false;
        uint32_t fre_start = 0;
        if (addr_size == 1) {
            fre_start = *reinterpret_cast<const uint8_t*>(fre_ptr);
        } else if (addr_size == 2) {
            uint16_t v; memcpy(&v, fre_ptr, 2); fre_start = v;
        } else {
            memcpy(&fre_start, fre_ptr, 4);
        }
        fre_ptr += addr_size;

        // (c) Read FRE info byte
        if (fre_ptr + 1 > fre_end) return false;
        uint8_t fre_info = *reinterpret_cast<const uint8_t*>(fre_ptr);
        fre_ptr += 1;

        // (d) Determine offset encoding size
        int off_size;
        switch (SFRAME_FRE_OFFSET_SIZE(fre_info)) {
            case SFRAME_FRE_OFFSET_1B: off_size = 1; break;
            case SFRAME_FRE_OFFSET_2B: off_size = 2; break;
            case SFRAME_FRE_OFFSET_4B: off_size = 4; break;
            default: return false;
        }

        // Decide what to read from the stream (governed by FRE info byte alone)
        bool fp_tracked = SFRAME_FRE_FP_TRACKED(fre_info);
        bool ra_in_fre  = SFRAME_FRE_RA_TRACKED(fre_info);

        // (e) Bounds check all remaining reads for this FRE
        int n_offsets = 1 + (fp_tracked ? 1 : 0) + (ra_in_fre ? 1 : 0);
        if (fre_ptr + n_offsets * off_size > fre_end) return false;

        // (f) Read CFA offset (signed)
        int32_t cfa_offset = 0;
        if (off_size == 1) {
            cfa_offset = *reinterpret_cast<const int8_t*>(fre_ptr);
        } else if (off_size == 2) {
            int16_t v; memcpy(&v, fre_ptr, 2); cfa_offset = v;
        } else {
            memcpy(&cfa_offset, fre_ptr, 4);
        }
        fre_ptr += off_size;

        // (g) Read FP offset if tracked
        int32_t fp_offset = 0;
        if (fp_tracked) {
            if (off_size == 1) {
                fp_offset = *reinterpret_cast<const int8_t*>(fre_ptr);
            } else if (off_size == 2) {
                int16_t v; memcpy(&v, fre_ptr, 2); fp_offset = v;
            } else {
                memcpy(&fp_offset, fre_ptr, 4);
            }
            fre_ptr += off_size;
        }

        // (h) Read RA offset if present in FRE (always consume to keep fre_ptr aligned)
        int32_t ra_offset = 0;
        if (ra_in_fre) {
            if (off_size == 1) {
                ra_offset = *reinterpret_cast<const int8_t*>(fre_ptr);
            } else if (off_size == 2) {
                int16_t v; memcpy(&v, fre_ptr, 2); ra_offset = v;
            } else {
                memcpy(&ra_offset, fre_ptr, 4);
            }
            fre_ptr += off_size;
        }

        // (i) Translate to FrameDesc fields
        u32 loc = _section_offset +
                  static_cast<u32>(static_cast<int32_t>(fde->start_addr) +
                                   static_cast<int32_t>(fre_start));

        u32 cfa_reg = SFRAME_FRE_BASE_REG(fre_info) ? static_cast<u32>(DW_REG_FP)
                                                     : static_cast<u32>(DW_REG_SP);
        u32 cfa = (static_cast<u32>(cfa_offset) << 8) | cfa_reg;

        // aarch64 GCC vs Clang detection: first FP-based entry with cfa_offset > 0
        if (_linked_frame_size < 0 && cfa_reg == static_cast<u32>(DW_REG_FP) && cfa_offset > 0) {
            _linked_frame_size = cfa_offset;
        }

        int fp_off = fp_tracked ? static_cast<int>(fp_offset) : DW_SAME_FP;

        // Header fixed RA offset takes priority over per-FRE value
        int pc_off;
        if (hdr->cfa_fixed_ra_offset != 0) {
            pc_off = static_cast<int>(hdr->cfa_fixed_ra_offset);
        } else if (ra_in_fre) {
            pc_off = static_cast<int>(ra_offset);
        } else {
            pc_off = DW_LINK_REGISTER;
        }

        // (j) Append record
        if (!addRecord(loc, cfa, fp_off, pc_off)) return false;
    }

    return true;
}

bool SFrameParser::parse() {
    // 1. Size check
    if (_section_size < sizeof(SFrameHeader)) return false;

    const SFrameHeader* hdr = reinterpret_cast<const SFrameHeader*>(_section_base);

    // 2-4. Header field validation
    if (hdr->magic   != SFRAME_MAGIC)     return false;
    if (hdr->version != SFRAME_VERSION_2) return false;

#if defined(__x86_64__)
    if (hdr->abi_arch != SFRAME_ABI_AMD64_ENDIAN_LITTLE)   return false;
#elif defined(__aarch64__)
    if (hdr->abi_arch != SFRAME_ABI_AARCH64_ENDIAN_LITTLE) return false;
#else
    return false;
#endif

    // 5. Bounds check auxhdr_len before computing data_start
    if (sizeof(SFrameHeader) + hdr->auxhdr_len > _section_size) return false;

    const char* data_start  = _section_base + sizeof(SFrameHeader) + hdr->auxhdr_len;
    const char* section_end = _section_base + _section_size;

    // Bounds-check fdeoff, freoff, and fre_len before pointer arithmetic
    size_t data_len = static_cast<size_t>(section_end - data_start);
    if (hdr->fdeoff > data_len) return false;
    if (hdr->freoff > data_len) return false;
    if (hdr->fre_len > data_len - hdr->freoff) return false;

    const SFrameFDE* fde_array   = reinterpret_cast<const SFrameFDE*>(data_start + hdr->fdeoff);
    const char*      fre_section = data_start + hdr->freoff;
    const char*      fre_end     = fre_section + hdr->fre_len;

    // 6-7. Bounds checks for FDE array and FRE section
    if (reinterpret_cast<const char*>(fde_array) +
            (size_t)hdr->num_fdes * sizeof(SFrameFDE) > section_end) return false;
    if (fre_end > section_end) return false;

    // 8. Iterate FDEs
    for (uint32_t i = 0; i < hdr->num_fdes; i++) {
        const SFrameFDE* fde = &fde_array[i];
        if (SFRAME_FUNC_FDE_TYPE(fde->info) != 0) continue;  // skip PCMASK
        if (fde->fre_num == 0)                    continue;  // empty FDE
        parseFDE(hdr, fde, fre_section, fre_end);            // ignore return; skip corrupt FDE
    }

    // 9. Sort
    qsort(_table, _count, sizeof(FrameDesc), FrameDesc::comparator);

    return _count > 0;
}
