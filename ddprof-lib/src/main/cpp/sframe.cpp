/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "sframe.h"
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
    if (_count >= _capacity) {
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

bool SFrameParser::parseFDE(const SFrameHeader* /*hdr*/, const SFrameFDE* /*fde*/,
                             const char* /*fre_section*/, const char* /*fre_end*/) {
    return true;  // stub — implemented in Task 4
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
