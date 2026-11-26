/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "codeCache.h"
#include "dwarf.h"
#include "../../main/cpp/gtest_crash_handler.h"

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <vector>

// Test name for crash handler
static constexpr char DWARF_TEST_NAME[] = "DwarfTest";

class DwarfGlobalSetup {
  public:
    DwarfGlobalSetup() {
        installGtestCrashHandler<DWARF_TEST_NAME>();
    }
    ~DwarfGlobalSetup() {
        restoreDefaultSignalHandlers();
    }
};
static DwarfGlobalSetup dwarf_global_setup;

#if DWARF_SUPPORTED

// Helpers to write little-endian integers into a byte buffer.
static void put32(std::vector<uint8_t>& buf, uint32_t v) {
    buf.push_back(static_cast<uint8_t>(v));
    buf.push_back(static_cast<uint8_t>(v >> 8));
    buf.push_back(static_cast<uint8_t>(v >> 16));
    buf.push_back(static_cast<uint8_t>(v >> 24));
}

static void put8(std::vector<uint8_t>& buf, uint8_t v) {
    buf.push_back(v);
}

// Append a minimal CIE with "z" augmentation to buf.
// Layout: [4-len=11][4-cie_id=0][1-ver=1][2-aug="z\0"][1-code_align=4][1-data_align=-8][1-ra=30][1-aug_data_len=0]
// Total: 15 bytes.
static void appendCie(std::vector<uint8_t>& buf) {
    // body size = cie_id(4) + version(1) + "z\0"(2) + code_align(1) + data_align(1) + ra_col(1) + aug_data_len(1) = 11
    put32(buf, 11);   // length
    put32(buf, 0);    // cie_id = 0
    put8(buf, 1);     // version
    put8(buf, 'z');   // augmentation "z"
    put8(buf, 0);     // null terminator
    put8(buf, 4);     // code_align = 4 (LEB128)
    put8(buf, 0x78);  // data_align = -8 (SLEB128: 0x78)
    put8(buf, 30);    // return address column = 30 (lr)
    put8(buf, 0);     // augmentation data length = 0 (LEB128)
}

// Append an FDE referencing the CIE at cie_start_offset from the buf start.
// cie_offset in the FDE = offset from FDE's cie_id field to the CIE start.
// range_start is encoded as a 4-byte PC-relative signed integer (pcrel).
// With pcrel=0 and image_base=&buf[0]: range_start = offset_of_pcrel_field_within_buf.
// Layout: [4-len=13][4-cie_offset][4-pcrel=0][4-range_len][1-aug_data_len=0]
// Total: 17 bytes.
static void appendFde(std::vector<uint8_t>& buf, uint32_t cie_start_offset, uint32_t range_len) {
    // The FDE's cie_id field will be at buf.size() + 4 (after length field).
    uint32_t cie_id_field_offset = static_cast<uint32_t>(buf.size()) + 4;
    uint32_t cie_offset = cie_id_field_offset - cie_start_offset;

    // body = cie_offset(4) + range_start(4) + range_len(4) + aug_data_len(1) = 13
    put32(buf, 13);          // length
    put32(buf, cie_offset);  // cie_offset from this field back to CIE start
    put32(buf, 0);           // range_start pcrel = 0 (absolute value = field_address - image_base)
    put32(buf, range_len);   // range_len
    put8(buf, 0);            // aug data length = 0 (LEB128, for "z" augmentation)
    // no DWARF call frame instructions
}

static void appendTerminator(std::vector<uint8_t>& buf) {
    put32(buf, 0);
}

// Parse a raw __eh_frame section using the linear DwarfParser constructor.
// image_base is set to buf.data() so that pcrel=0 yields range_start = field_offset_in_buf.
static DwarfParser* parseBuf(const std::vector<uint8_t>& buf) {
    const char* base = reinterpret_cast<const char*>(buf.data());
    return new DwarfParser("test", base, base, buf.size());
}

TEST(DwarfEhFrame, EmptySection) {
    std::vector<uint8_t> buf;
    DwarfParser* dwarf = parseBuf(buf);
    EXPECT_EQ(dwarf->count(), 0);
    free(dwarf->table());
    delete dwarf;
}

TEST(DwarfEhFrame, TerminatorOnly) {
    std::vector<uint8_t> buf;
    appendTerminator(buf);
    DwarfParser* dwarf = parseBuf(buf);
    EXPECT_EQ(dwarf->count(), 0);
    free(dwarf->table());
    delete dwarf;
}

TEST(DwarfEhFrame, CieOnly) {
    std::vector<uint8_t> buf;
    appendCie(buf);
    appendTerminator(buf);
    DwarfParser* dwarf = parseBuf(buf);
    // CIE alone generates no frame records.
    EXPECT_EQ(dwarf->count(), 0);
    free(dwarf->table());
    delete dwarf;
}

TEST(DwarfEhFrame, CieAndFde) {
    // CIE starts at offset 0.
    std::vector<uint8_t> buf;
    appendCie(buf);                    // 15 bytes
    appendFde(buf, 0, 256);            // 17 bytes (cie_offset = 19)
    appendTerminator(buf);             // 4 bytes
    ASSERT_EQ(buf.size(), static_cast<size_t>(36));

    DwarfParser* dwarf = parseBuf(buf);
    // The FDE with no instructions generates two records:
    // one from parseInstructions (initial state at range_start) and one sentinel (at range_start + range_len).
    EXPECT_EQ(dwarf->count(), 2);

    // Table must be in ascending loc order (sorted).
    const FrameDesc* table = dwarf->table();
    ASSERT_NE(table, nullptr);
    EXPECT_LT(table[0].loc, table[1].loc);

    // Sentinel record covers the end of the FDE's range.
    // range_start = offset of pcrel field in buf = 15+4+4 = 23; range_end = 23+256 = 279.
    EXPECT_EQ(table[1].loc, static_cast<uint32_t>(279));

    free(dwarf->table());
    delete dwarf;
}

// --- Bounds-guard tests ---

TEST(DwarfEhFrame, TruncatedRecord) {
    // Build a valid CIE then truncate the buffer so record_end > section_end.
    // The length-overflow guard should fire and produce no records.
    std::vector<uint8_t> buf;
    appendCie(buf);   // 15 bytes: length=11, so record_end = 15
    buf.resize(10);   // section_end = 10 < record_end → overflow guard triggers
    DwarfParser* dwarf = parseBuf(buf);
    EXPECT_EQ(dwarf->count(), 0);
    free(dwarf->table());
    delete dwarf;
}

TEST(DwarfEhFrame, ShortCieBody) {
    // CIE with length=4: body is exactly cie_id (4 bytes), nothing else.
    // After reading cie_id, _ptr == record_end; the version/augmentation guard triggers.
    std::vector<uint8_t> buf;
    put32(buf, 4);   // length = 4
    put32(buf, 0);   // cie_id = 0 → CIE
    appendTerminator(buf);
    DwarfParser* dwarf = parseBuf(buf);
    EXPECT_EQ(dwarf->count(), 0);
    free(dwarf->table());
    delete dwarf;
}

TEST(DwarfEhFrame, FdeAugDataOverrun) {
    // CIE with 'z' augmentation followed by an FDE whose aug-data-length encodes
    // a value (100) larger than remaining bytes in the record (0).
    // The FDE should be skipped without a crash.
    std::vector<uint8_t> buf;
    appendCie(buf);  // 15 bytes; CIE advertises a "z" augmentation

    // FDE body: cie_offset(4) + range_start(4) + range_len(4) + aug_data_len(1) = 13
    // aug_data_len = 100 but no aug data bytes follow → _ptr += 100 > record_end → break
    uint32_t cie_id_field_offset = static_cast<uint32_t>(buf.size()) + 4;
    put32(buf, 13);                       // length
    put32(buf, cie_id_field_offset - 0);  // cie_offset back to CIE at offset 0
    put32(buf, 0);                        // range_start pcrel
    put32(buf, 128);                      // range_len
    put8(buf, 100);                       // aug_data_len = 100 but 0 bytes of aug data follow
    appendTerminator(buf);
    DwarfParser* dwarf = parseBuf(buf);
    EXPECT_EQ(dwarf->count(), 0);
    free(dwarf->table());
    delete dwarf;
}

// CIE + FDE whose body ends at exactly the last byte of the section (no
// terminator appended). Verifies that _image_end-bounded reads are not
// spuriously rejected when the FDE occupies the full section.
TEST(DwarfEhFrame, FdeAtExactImageBoundary) {
    std::vector<uint8_t> buf;
    appendCie(buf);          // 15 bytes
    appendFde(buf, 0, 256);  // 17 bytes; FDE ends at offset 32 == image_end
    ASSERT_EQ(buf.size(), static_cast<size_t>(32));
    DwarfParser* dwarf = parseBuf(buf);
    EXPECT_EQ(dwarf->count(), 2);  // normal result; boundary must not be spuriously rejected
    free(dwarf->table());
    delete dwarf;
}

// An FDE where fde_len makes fde_end > _image_end.
// parseFde()'s `fde_end > _image_end` guard must reject it without reading past
// the buffer. Uses the .eh_frame_hdr constructor path (parse → parseFde).
//
// Buffer layout (24 bytes):
//   [0-3]   .eh_frame_hdr header (version + 3 encoding bytes)
//   [4-7]   eh_frame_ptr = 0
//   [8-11]  fde_count = 1
//   [12-15] table[0].initial_loc = 0
//   [16-19] table[0].fde_ptr = 20  (offset from hdr start to fde_len field below)
//   [20-23] fde_len = 100          (fde_end = hdr+24+100 = hdr+124 > image_end=hdr+24)
TEST(DwarfEhFrameHdr, FdeExceedsImageEnd) {
    std::vector<uint8_t> hdr(24, 0);
    hdr[0] = 1;     // version
    hdr[1] = 0x03;  // eh_frame_ptr_enc = DW_EH_PE_udata4
    hdr[2] = 0x03;  // fde_count_enc    = DW_EH_PE_udata4
    hdr[3] = 0x33;  // table_enc        = DW_EH_PE_datarel | DW_EH_PE_udata4
    hdr[8]  = 1;    // fde_count = 1
    hdr[16] = 20;   // table[0].fde_ptr: points to the fde_len field below
    hdr[20] = 100;  // fde_len = 100 → fde_end = hdr+124 > image_end = hdr+24

    const char* base = reinterpret_cast<const char*>(hdr.data());
    DwarfParser dwarf("test", base, base, hdr.size(), DwarfParser::EhFrameHdrTag{}, base + hdr.size());
    EXPECT_EQ(dwarf.count(), 0);  // rejected: fde_end > image_end, no crash
    free(dwarf.table());
}

// Regression test for the .eh_frame_hdr hardening (found by fuzz_dwarf).
// A hostile .eh_frame_hdr can claim a large fde_count while providing no
// binary-search table; pre-hardening, parse() walked `table[i*2]` off the end
// of the section. The bounded parser rejects a fde_count that cannot fit in the
// section. The header is a heap buffer sized to exactly 16 bytes (header only,
// no table entries), so ASan's redzone catches any over-read deterministically.
TEST(DwarfEhFrameHdr, FdeCountOverrun) {
    std::vector<uint8_t> hdr(16, 0);  // 16-byte header; the table would start at 16
    hdr[0] = 1;     // version
    hdr[1] = 0x03;  // eh_frame_ptr_enc = DW_EH_PE_udata4
    hdr[2] = 0x03;  // fde_count_enc    = DW_EH_PE_udata4
    hdr[3] = 0x33;  // table_enc        = DW_EH_PE_datarel | DW_EH_PE_udata4
    // fde_count at offset 8 (little-endian): claim 1024 entries that aren't there.
    hdr[8] = 0x00;
    hdr[9] = 0x04;

    const char* base = reinterpret_cast<const char*>(hdr.data());
    DwarfParser dwarf("test", base, base, hdr.size(), DwarfParser::EhFrameHdrTag{}, base + hdr.size());
    EXPECT_EQ(dwarf.count(), 0);  // rejected: no records, no crash
    free(dwarf.table());
}

// Append a CIE with a caller-chosen code_align and no augmentation string
// (so the referencing FDE needs no aug-data-length byte).
// Layout: [4-len=9][4-cie_id=0][1-ver=1][1-aug="\0"][1-code_align][1-data_align=-8][1-ra=30]
static void appendCieWithCodeAlign(std::vector<uint8_t>& buf, uint8_t code_align) {
    put32(buf, 9);           // length
    put32(buf, 0);           // cie_id = 0
    put8(buf, 1);            // version
    put8(buf, 0);            // empty augmentation string
    put8(buf, code_align);   // code_align (LEB128, fits in one byte for the values used here)
    put8(buf, 0x78);         // data_align = -8 (SLEB128)
    put8(buf, 30);           // return address column
}

// Append an FDE (no augmentation, so no aug-data-length byte) referencing the CIE at
// cie_start_offset. Instructions: advance_loc1(delta1), then def_cfa_offset(16) to force
// a genuine state change (addRecord coalesces consecutive records with identical
// cfa/fp/pc, so a second advance alone would not produce an observable record), then
// advance_loc1(delta2).
static void appendFdeWithAdvances(std::vector<uint8_t>& buf, uint32_t cie_start_offset,
                                   uint32_t range_len, uint8_t delta1, uint8_t delta2) {
    uint32_t cie_id_field_offset = static_cast<uint32_t>(buf.size()) + 4;
    uint32_t cie_offset = cie_id_field_offset - cie_start_offset;

    // body = cie_offset(4) + range_start(4) + range_len(4) + advance_loc1(2) +
    //        def_cfa_offset(2) + advance_loc1(2) = 18
    put32(buf, 18);
    put32(buf, cie_offset);
    put32(buf, 0);    // range_start pcrel = 0
    put32(buf, range_len);
    put8(buf, 0x02);  // DW_CFA_advance_loc1
    put8(buf, delta1);
    put8(buf, 0x0e);  // DW_CFA_def_cfa_offset
    put8(buf, 16);    // new cfa_off (LEB128, fits in one byte)
    put8(buf, 0x02);  // DW_CFA_advance_loc1
    put8(buf, delta2);
}

static bool hasLoc(const FrameDesc* table, int count, uint32_t loc) {
    for (int i = 0; i < count; i++) {
        if (table[i].loc == loc) return true;
    }
    return false;
}

// Regression test for per-FDE CIE resolution (parseFde() resolves and parses each
// FDE's own CIE rather than caching the first one seen): a code_align factor from
// one CIE must not leak into a neighboring FDE that resolves a different CIE.
TEST(DwarfEhFrameHdr, PerFdeCieAlignmentDoesNotLeak) {
    std::vector<uint8_t> body;
    uint32_t cie1_offset = static_cast<uint32_t>(body.size());
    appendCieWithCodeAlign(body, 1);  // CIE1: code_align = 1
    uint32_t fde1_offset = static_cast<uint32_t>(body.size());
    appendFdeWithAdvances(body, cie1_offset, 100, 10, 5);

    uint32_t cie2_offset = static_cast<uint32_t>(body.size());
    appendCieWithCodeAlign(body, 4);  // CIE2: code_align = 4
    uint32_t fde2_offset = static_cast<uint32_t>(body.size());
    appendFdeWithAdvances(body, cie2_offset, 100, 10, 5);

    // .eh_frame_hdr: 12-byte fixed header + 2 table entries (8 bytes each) = 28 bytes,
    // followed directly by the CIE/FDE body built above.
    const uint32_t HDR_SIZE = 28;
    std::vector<uint8_t> buf(HDR_SIZE, 0);
    buf[0] = 1;     // version
    buf[1] = 0x03;  // eh_frame_ptr_enc = DW_EH_PE_udata4
    buf[2] = 0x03;  // fde_count_enc    = DW_EH_PE_udata4
    buf[3] = 0x33;  // table_enc        = DW_EH_PE_datarel | DW_EH_PE_udata4
    buf[8] = 2;     // fde_count = 2

    auto putFdePtr = [&](size_t idx, uint32_t fde_len_field_offset) {
        size_t off = 12 + idx * 8 + 4;  // skip this entry's initial_loc field
        buf[off]     = static_cast<uint8_t>(fde_len_field_offset);
        buf[off + 1] = static_cast<uint8_t>(fde_len_field_offset >> 8);
        buf[off + 2] = static_cast<uint8_t>(fde_len_field_offset >> 16);
        buf[off + 3] = static_cast<uint8_t>(fde_len_field_offset >> 24);
    };
    putFdePtr(0, HDR_SIZE + fde1_offset);
    putFdePtr(1, HDR_SIZE + fde2_offset);

    buf.insert(buf.end(), body.begin(), body.end());

    // range_start of each FDE = the absolute offset of its pcrel field (pcrel value is 0
    // and image_base == buf.data()), i.e. HDR_SIZE + fde_offset + 8 (past length+cie_offset).
    uint32_t range_start1 = HDR_SIZE + fde1_offset + 8;
    uint32_t range_start2 = HDR_SIZE + fde2_offset + 8;

    const char* base = reinterpret_cast<const char*>(buf.data());
    DwarfParser dwarf("test", base, base, buf.size(), DwarfParser::EhFrameHdrTag{}, base + buf.size());

    const FrameDesc* table = dwarf.table();
    ASSERT_NE(table, nullptr);
    ASSERT_EQ(dwarf.count(), 6);  // 2 FDEs x (initial state + post-advance state + sentinel)

    EXPECT_TRUE(hasLoc(table, dwarf.count(), range_start1));
    // CIE1's code_align = 1: first advance_loc1(10) moves loc by 10*1 = 10.
    EXPECT_TRUE(hasLoc(table, dwarf.count(), range_start1 + 10));

    EXPECT_TRUE(hasLoc(table, dwarf.count(), range_start2));
    // CIE2's code_align = 4: first advance_loc1(10) moves loc by 10*4 = 40. If CIE2's
    // resolution leaked CIE1's code_align instead, this would land at range_start2 + 10.
    EXPECT_TRUE(hasLoc(table, dwarf.count(), range_start2 + 40));
    EXPECT_FALSE(hasLoc(table, dwarf.count(), range_start2 + 10));

    free(dwarf.table());
}

// ---------------------------------------------------------------------------
// CIE validation / augmentation-gate coverage for the per-FDE CIE path
// (parseFde -> resolveCie -> parseCie). Every test below drives the
// .eh_frame_hdr constructor, which is the only path that reaches parseFde().
// ---------------------------------------------------------------------------

// A CIE with full control over the fields parseCie() validates.
struct CieSpec {
    uint32_t cie_id = 0;
    uint8_t version = 1;
    bool z_augmentation = false;
    // Extra augmentation characters emitted after the leading 'z' (if any),
    // e.g. "S" for a signal frame or "RS" for a signal frame with a pointer
    // encoding. Not interpreted by the builder.
    const char* extra_augmentation = "";
    uint8_t code_align = 1;
    // Cut the declared length short so the record ends right after the
    // augmentation string, leaving no room for code_alignment_factor.
    bool truncate_before_code_align = false;
    // Cut it short one field later: code_alignment_factor is present,
    // data_alignment_factor is not.
    bool truncate_before_data_align = false;
};

// Returns the offset of the appended CIE within buf.
static uint32_t appendCie(std::vector<uint8_t>& buf, const CieSpec& spec) {
    uint32_t cie_offset = static_cast<uint32_t>(buf.size());

    std::vector<uint8_t> body;
    put32(body, spec.cie_id);
    put8(body, spec.version);
    if (spec.z_augmentation) {
        put8(body, 'z');
    }
    for (const char* c = spec.extra_augmentation; *c != 0; c++) {
        put8(body, static_cast<uint8_t>(*c));
    }
    put8(body, 0);  // augmentation string terminator
    uint32_t len_through_aug_string = static_cast<uint32_t>(body.size());
    if (spec.version >= 4) {
        // DWARF4 inserts these two between the augmentation string and
        // code_alignment_factor.
        put8(body, sizeof(void*));  // address_size
        put8(body, 0);              // segment_selector_size
    }
    put8(body, spec.code_align);  // code_align (LEB128, one byte for the values used here)
    uint32_t len_through_code_align = static_cast<uint32_t>(body.size());
    put8(body, 0x78);             // data_align = -8 (SLEB128)
    put8(body, 30);               // return address column
    if (spec.z_augmentation) {
        put8(body, 0);  // augmentation data length
    }

    uint32_t declared_len = static_cast<uint32_t>(body.size());
    if (spec.truncate_before_code_align) {
        declared_len = len_through_aug_string;
    } else if (spec.truncate_before_data_align) {
        declared_len = len_through_code_align;
    }
    put32(buf, declared_len);
    buf.insert(buf.end(), body.begin(), body.end());
    return cie_offset;
}

// An FDE carrying an explicit augmentation-data blob, as every "z" CIE's FDEs
// do. Instructions: advance_loc1(delta), then def_cfa_offset(16) so the
// advanced loc produces an observable record (addRecord coalesces records
// with identical cfa/fp/pc).
static void appendFdeWithAugData(std::vector<uint8_t>& buf, uint32_t cie_start_offset,
                                  uint32_t range_len, uint8_t delta,
                                  const std::vector<uint8_t>& aug_data) {
    uint32_t cie_id_field_offset = static_cast<uint32_t>(buf.size()) + 4;
    uint32_t cie_offset = cie_id_field_offset - cie_start_offset;

    std::vector<uint8_t> body;
    put32(body, cie_offset);
    put32(body, 0);          // range_start pcrel = 0
    put32(body, range_len);
    put8(body, static_cast<uint8_t>(aug_data.size()));  // aug data length (LEB128)
    body.insert(body.end(), aug_data.begin(), aug_data.end());
    put8(body, 0x02);        // DW_CFA_advance_loc1
    put8(body, delta);
    put8(body, 0x0e);        // DW_CFA_def_cfa_offset
    put8(body, 16);

    put32(buf, static_cast<uint32_t>(body.size()));
    buf.insert(buf.end(), body.begin(), body.end());
}

static uint32_t hdrSizeFor(size_t fde_count) {
    return 12 + static_cast<uint32_t>(fde_count) * 8;  // fixed header + 8-byte table entries
}

// Wraps `body` in a .eh_frame_hdr whose binary-search table points at each
// offset in `fde_offsets` (offsets relative to the start of body).
static std::vector<uint8_t> buildEhFrameHdrImage(const std::vector<uint8_t>& body,
                                                  const std::vector<uint32_t>& fde_offsets) {
    const uint32_t HDR_SIZE = hdrSizeFor(fde_offsets.size());
    std::vector<uint8_t> buf(HDR_SIZE, 0);
    buf[0] = 1;     // version
    buf[1] = 0x03;  // eh_frame_ptr_enc = DW_EH_PE_udata4
    buf[2] = 0x03;  // fde_count_enc    = DW_EH_PE_udata4
    buf[3] = 0x33;  // table_enc        = DW_EH_PE_datarel | DW_EH_PE_udata4
    buf[8] = static_cast<uint8_t>(fde_offsets.size());

    for (size_t i = 0; i < fde_offsets.size(); i++) {
        uint32_t fde_len_field_offset = HDR_SIZE + fde_offsets[i];
        size_t off = 12 + i * 8 + 4;  // skip this entry's initial_loc field
        buf[off]     = static_cast<uint8_t>(fde_len_field_offset);
        buf[off + 1] = static_cast<uint8_t>(fde_len_field_offset >> 8);
        buf[off + 2] = static_cast<uint8_t>(fde_len_field_offset >> 16);
        buf[off + 3] = static_cast<uint8_t>(fde_len_field_offset >> 24);
    }
    buf.insert(buf.end(), body.begin(), body.end());
    return buf;
}

// Builds a single-FDE image from `spec` and reports how many records the
// parser produced plus whether the FDE's first advance landed where
// `spec.code_align` says it should.
struct SingleFdeResult {
    int count;
    bool has_range_start;
    bool has_advanced_loc;
};

static SingleFdeResult parseSingleFde(const CieSpec& spec, uint8_t delta,
                                       uint32_t expected_advance) {
    std::vector<uint8_t> body;
    uint32_t cie_offset = appendCie(body, spec);
    uint32_t fde_offset = static_cast<uint32_t>(body.size());
    if (spec.z_augmentation) {
        appendFdeWithAugData(body, cie_offset, 100, delta, {});
    } else {
        appendFdeWithAdvances(body, cie_offset, 100, delta, 1);
    }

    std::vector<uint8_t> buf = buildEhFrameHdrImage(body, {fde_offset});
    uint32_t range_start = hdrSizeFor(1) + fde_offset + 8;

    const char* base = reinterpret_cast<const char*>(buf.data());
    DwarfParser dwarf("test", base, base, buf.size(), DwarfParser::EhFrameHdrTag{},
                      base + buf.size());
    const FrameDesc* table = dwarf.table();
    SingleFdeResult r{dwarf.count(), false, false};
    if (table != nullptr) {
        r.has_range_start = hasLoc(table, dwarf.count(), range_start);
        r.has_advanced_loc = hasLoc(table, dwarf.count(), range_start + expected_advance);
    }
    free(dwarf.table());
    return r;
}

// A well-formed version-1 CIE is the control for every rejection test below:
// it must produce records, otherwise those tests would pass for the wrong
// reason.
TEST(DwarfEhFrameHdr, ValidCieProducesRecords) {
    CieSpec spec;
    spec.code_align = 4;
    SingleFdeResult r = parseSingleFde(spec, 10, 40);
    EXPECT_EQ(3, r.count);  // initial state + post-advance state + sentinel
    EXPECT_TRUE(r.has_range_start);
    EXPECT_TRUE(r.has_advanced_loc);
}

// An FDE whose cie_offset resolves to a record with a non-zero CIE id is not
// pointing at a CIE at all; the alignment factors read out of it would be
// arbitrary, so the FDE must contribute no rows.
TEST(DwarfEhFrameHdr, NonZeroCieIdRejectsFde) {
    CieSpec spec;
    spec.cie_id = 1;  // an FDE's cie_offset, not a CIE marker
    spec.code_align = 4;
    SingleFdeResult r = parseSingleFde(spec, 10, 40);
    EXPECT_EQ(0, r.count);
}

// Version 3 shares version 1's field layout.
TEST(DwarfEhFrameHdr, CieVersion3Accepted) {
    CieSpec spec;
    spec.version = 3;
    spec.code_align = 4;
    SingleFdeResult r = parseSingleFde(spec, 10, 40);
    EXPECT_EQ(3, r.count);
    EXPECT_TRUE(r.has_advanced_loc)
        << "a version-3 CIE must be read with the same layout as version 1";
}

// Version 4 inserts address_size and segment_selector_size before
// code_alignment_factor. Reading straight through them would take
// address_size (8) as the code alignment factor, scaling this FDE's
// advance_loc1(10) to 80 instead of 40.
TEST(DwarfEhFrameHdr, CieVersion4SkipsAddressSizeFields) {
    CieSpec spec;
    spec.version = 4;
    spec.code_align = 4;
    SingleFdeResult r = parseSingleFde(spec, 10, 40);
    EXPECT_EQ(3, r.count);
    EXPECT_TRUE(r.has_advanced_loc)
        << "version-4 address_size/segment_selector_size must be skipped before "
        << "code_alignment_factor is read";
}

// Anything outside the handled set is a layout this parser cannot read.
TEST(DwarfEhFrameHdr, UnsupportedCieVersionRejectsFde) {
    CieSpec spec;
    spec.version = 5;
    spec.code_align = 4;
    SingleFdeResult r = parseSingleFde(spec, 10, 40);
    EXPECT_EQ(0, r.count);
}

// The declared CIE length can stop before code_alignment_factor. Reading it
// anyway yields code_align = 0, which collapses every advance_loc delta onto
// range_start and zeroes every register offset -- and, since the CIE is
// resolved per FDE, would do so for every FDE referencing it.
TEST(DwarfEhFrameHdr, TruncatedCieRejectsFde) {
    CieSpec spec;
    spec.truncate_before_code_align = true;
    spec.code_align = 4;
    SingleFdeResult r = parseSingleFde(spec, 10, 40);
    EXPECT_EQ(0, r.count);
}

// Same for a length that stops one field later: code_alignment_factor reads
// fine, data_alignment_factor comes back as 0 and would zero every register
// offset, making walkDwarf read the caller pc from sp+0.
TEST(DwarfEhFrameHdr, CieTruncatedBeforeDataAlignRejectsFde) {
    CieSpec spec;
    spec.truncate_before_data_align = true;
    spec.code_align = 4;
    SingleFdeResult r = parseSingleFde(spec, 10, 40);
    EXPECT_EQ(0, r.count);
}

// A zero code alignment factor is malformed for the same reason.
TEST(DwarfEhFrameHdr, ZeroCodeAlignRejectsFde) {
    CieSpec spec;
    spec.code_align = 0;
    SingleFdeResult r = parseSingleFde(spec, 10, 0);
    EXPECT_EQ(0, r.count);
}

// The branch that runs for every GCC/clang-emitted "zR" CIE: parseFde() must
// skip the FDE's augmentation-data-length field and the blob itself before
// decoding CFI. Left unskipped, the 0x41 bytes below decode as
// DW_CFA_advance_loc(1) and shift every subsequent row.
TEST(DwarfEhFrameHdr, ZAugmentedFdeSkipsAugmentationData) {
    CieSpec spec;
    spec.z_augmentation = true;
    spec.code_align = 4;

    std::vector<uint8_t> body;
    uint32_t cie_offset = appendCie(body, spec);
    uint32_t fde_offset = static_cast<uint32_t>(body.size());
    appendFdeWithAugData(body, cie_offset, 100, 10, {0x41, 0x41, 0x41, 0x41});

    std::vector<uint8_t> buf = buildEhFrameHdrImage(body, {fde_offset});
    uint32_t range_start = hdrSizeFor(1) + fde_offset + 8;

    const char* base = reinterpret_cast<const char*>(buf.data());
    DwarfParser dwarf("test", base, base, buf.size(), DwarfParser::EhFrameHdrTag{},
                      base + buf.size());
    const FrameDesc* table = dwarf.table();
    ASSERT_NE(table, nullptr);

    EXPECT_TRUE(hasLoc(table, dwarf.count(), range_start));
    EXPECT_TRUE(hasLoc(table, dwarf.count(), range_start + 40))
        << "advance_loc1(10) with code_align 4 must land at range_start + 40; a "
        << "different loc means the augmentation data was decoded as CFI";
    free(dwarf.table());
}

// A z-augmented FDE whose CIE is rejected must be skipped outright. Falling
// back to defaults would also clear has_z_augmentation, feeding the
// augmentation-length ULEB and the blob to the CFI decoder.
TEST(DwarfEhFrameHdr, ZAugmentedFdeWithRejectedCieProducesNoRows) {
    CieSpec spec;
    spec.z_augmentation = true;
    spec.version = 5;  // rejected
    spec.code_align = 4;

    std::vector<uint8_t> body;
    uint32_t cie_offset = appendCie(body, spec);
    uint32_t fde_offset = static_cast<uint32_t>(body.size());
    appendFdeWithAugData(body, cie_offset, 100, 10, {0x41, 0x41, 0x41, 0x41});

    std::vector<uint8_t> buf = buildEhFrameHdrImage(body, {fde_offset});
    const char* base = reinterpret_cast<const char*>(buf.data());
    DwarfParser dwarf("test", base, base, buf.size(), DwarfParser::EhFrameHdrTag{},
                      base + buf.size());
    EXPECT_EQ(0, dwarf.count());
    free(dwarf.table());
}

// Real toolchains emit long runs of FDEs sharing one CIE, which parseFde()
// resolves through a memoized last-CIE slot. Every FDE in such a run must see
// that CIE's alignment factors, not a stale or default set.
TEST(DwarfEhFrameHdr, FdesSharingOneCieAllUseItsAlignment) {
    CieSpec spec;
    spec.code_align = 4;

    std::vector<uint8_t> body;
    uint32_t cie_offset = appendCie(body, spec);
    uint32_t fde1_offset = static_cast<uint32_t>(body.size());
    appendFdeWithAdvances(body, cie_offset, 100, 10, 1);
    uint32_t fde2_offset = static_cast<uint32_t>(body.size());
    appendFdeWithAdvances(body, cie_offset, 100, 10, 1);

    std::vector<uint8_t> buf = buildEhFrameHdrImage(body, {fde1_offset, fde2_offset});
    uint32_t range_start1 = hdrSizeFor(2) + fde1_offset + 8;
    uint32_t range_start2 = hdrSizeFor(2) + fde2_offset + 8;

    const char* base = reinterpret_cast<const char*>(buf.data());
    DwarfParser dwarf("test", base, base, buf.size(), DwarfParser::EhFrameHdrTag{},
                      base + buf.size());
    const FrameDesc* table = dwarf.table();
    ASSERT_NE(table, nullptr);

    EXPECT_TRUE(hasLoc(table, dwarf.count(), range_start1 + 40));
    EXPECT_TRUE(hasLoc(table, dwarf.count(), range_start2 + 40))
        << "the second FDE sharing this CIE must still see code_align 4";
    EXPECT_FALSE(hasLoc(table, dwarf.count(), range_start2 + 10));
    free(dwarf.table());
}

// Returns the flags of the row covering `loc`, or 0xffffffff if no row does.
static uint32_t flagsAtLoc(const FrameDesc* table, int count, uint32_t loc) {
    for (int i = 0; i < count; i++) {
        if (table[i].loc == loc) return table[i].flags;
    }
    return 0xffffffffu;
}

// Builds a single-FDE image from `spec` and returns the flags on the row at
// the FDE's range_start.
static uint32_t parseSingleFdeFlags(const CieSpec& spec) {
    std::vector<uint8_t> body;
    uint32_t cie_offset = appendCie(body, spec);
    uint32_t fde_offset = static_cast<uint32_t>(body.size());
    if (spec.z_augmentation) {
        appendFdeWithAugData(body, cie_offset, 100, 10, {});
    } else {
        appendFdeWithAdvances(body, cie_offset, 100, 10, 1);
    }

    std::vector<uint8_t> buf = buildEhFrameHdrImage(body, {fde_offset});
    uint32_t range_start = hdrSizeFor(1) + fde_offset + 8;

    const char* base = reinterpret_cast<const char*>(buf.data());
    DwarfParser dwarf("test", base, base, buf.size(), DwarfParser::EhFrameHdrTag{},
                      base + buf.size());
    const FrameDesc* table = dwarf.table();
    uint32_t flags = table != nullptr ? flagsAtLoc(table, dwarf.count(), range_start)
                                      : 0xffffffffu;
    free(dwarf.table());
    return flags;
}

// A signal-frame CIE ('S' in the augmentation string) declares that its FDEs'
// return-address column holds the exact interrupted PC, not an address after a
// call. Every row it produces must carry FLAG_SIGNAL_FRAME so walkDwarf can
// suppress the return-address attribution adjustment for it.
TEST(DwarfEhFrameHdr, SignalFrameCieSetsRowFlag) {
    CieSpec spec;
    spec.extra_augmentation = "S";
    spec.code_align = 4;
    EXPECT_EQ(FrameDesc::FLAG_SIGNAL_FRAME, parseSingleFdeFlags(spec));
}

// 'S' is not required to be the first character: with a 'z' augmentation it
// necessarily follows it, so the whole string has to be scanned.
TEST(DwarfEhFrameHdr, SignalFrameFlagFoundAfterZAugmentation) {
    CieSpec spec;
    spec.z_augmentation = true;
    spec.extra_augmentation = "S";
    spec.code_align = 4;
    EXPECT_EQ(FrameDesc::FLAG_SIGNAL_FRAME, parseSingleFdeFlags(spec));
}

// An ordinary CIE must not set it, or every frame would skip the adjustment.
TEST(DwarfEhFrameHdr, OrdinaryCieLeavesSignalFrameFlagClear) {
    CieSpec spec;
    spec.code_align = 4;
    EXPECT_EQ(0u, parseSingleFdeFlags(spec));

    CieSpec z_spec;
    z_spec.z_augmentation = true;
    z_spec.code_align = 4;
    EXPECT_EQ(0u, parseSingleFdeFlags(z_spec));
}

// A character that merely contains an 'S' elsewhere in the alphabet must not
// trip the scan, and an augmentation this parser does not interpret ('R') must
// not either.
TEST(DwarfEhFrameHdr, UninterpretedAugmentationLeavesFlagClear) {
    CieSpec spec;
    spec.z_augmentation = true;
    spec.extra_augmentation = "R";
    spec.code_align = 4;
    EXPECT_EQ(0u, parseSingleFdeFlags(spec));
}

// ---------------------------------------------------------------------------
// The linear __eh_frame path (parseEhFrame) applies the same "no readable CIE,
// no rows" rule as the .eh_frame_hdr path above.
// ---------------------------------------------------------------------------

// An FDE that appears before any CIE has no alignment factors to be decoded
// against.
TEST(DwarfEhFrame, FdeBeforeAnyCieProducesNoRows) {
    std::vector<uint8_t> buf;
    appendFdeWithAdvances(buf, /*cie_start_offset=*/0, 100, 10, 5);
    appendTerminator(buf);
    DwarfParser* dwarf = parseBuf(buf);
    EXPECT_EQ(dwarf->count(), 0);
    free(dwarf->table());
    delete dwarf;
}

// Nor does one following a CIE that was rejected.
TEST(DwarfEhFrame, FdeAfterRejectedCieProducesNoRows) {
    std::vector<uint8_t> buf;
    uint32_t cie_offset = static_cast<uint32_t>(buf.size());
    appendCieWithCodeAlign(buf, 0);  // zero code alignment factor: malformed
    appendFdeWithAdvances(buf, cie_offset, 100, 10, 5);
    appendTerminator(buf);
    DwarfParser* dwarf = parseBuf(buf);
    EXPECT_EQ(dwarf->count(), 0);
    free(dwarf->table());
    delete dwarf;
}

// Control: the same shape with a well-formed CIE does produce rows, so the two
// tests above cannot pass for the wrong reason.
TEST(DwarfEhFrame, FdeAfterValidCieProducesRows) {
    std::vector<uint8_t> buf;
    uint32_t cie_offset = static_cast<uint32_t>(buf.size());
    appendCieWithCodeAlign(buf, 4);
    appendFdeWithAdvances(buf, cie_offset, 100, 10, 5);
    appendTerminator(buf);
    DwarfParser* dwarf = parseBuf(buf);
    EXPECT_GT(dwarf->count(), 0);
    free(dwarf->table());
    delete dwarf;
}

// ---------------------------------------------------------------------------
// Return-address column (pc_off) rules. INITIAL_PC_OFFSET is the CIE's
// assumed rule: DW_LINK_REGISTER on aarch64 (x30 not yet saved), [CFA-8] on
// x86_64. Each test is written against the constants, so it runs on both.
// ---------------------------------------------------------------------------

namespace {

constexpr uint8_t DW_CFA_advance_loc_4 = 0x40 | 4;
// DW_CFA_offset <reg>, 2 with data_align -8: a slot that differs from
// INITIAL_PC_OFFSET on every architecture.
constexpr uint8_t kSavedSlotFactor = 2;
constexpr int kSavedSlot = -8 * kSavedSlotFactor;
constexpr uint32_t kFdeRangeLen = 100;

// Parses one FDE whose call frame instructions are `insns`, against a CIE with
// code_align 1 and data_align -8, and keeps the rows for lookup.
class PcColumnFde {
  public:
    explicit PcColumnFde(const std::vector<uint8_t>& insns) {
        std::vector<uint8_t> body;
        uint32_t cie_offset = static_cast<uint32_t>(body.size());
        appendCieWithCodeAlign(body, 1);
        uint32_t fde_offset = static_cast<uint32_t>(body.size());
        uint32_t cie_id_field_offset = fde_offset + 4;
        put32(body, static_cast<uint32_t>(12 + insns.size()));  // cie_offset + range_start + range_len
        put32(body, cie_id_field_offset - cie_offset);
        put32(body, 0);  // range_start pcrel = 0
        put32(body, kFdeRangeLen);
        body.insert(body.end(), insns.begin(), insns.end());

        _image = buildEhFrameHdrImage(body, {fde_offset});
        _range_start = hdrSizeFor(1) + fde_offset + 8;
        const char* base = reinterpret_cast<const char*>(_image.data());
        DwarfParser dwarf("test", base, base, _image.size(), DwarfParser::EhFrameHdrTag{},
                          base + _image.size());
        _table = dwarf.table();
        _count = dwarf.count();
    }
    ~PcColumnFde() { free(_table); }
    PcColumnFde(const PcColumnFde&) = delete;
    PcColumnFde& operator=(const PcColumnFde&) = delete;

    // The row in effect `offset` bytes into the FDE (addRecord() merges identical
    // neighbours, so rows are never indexed). Keep offsets below kFdeRangeLen,
    // where the parser appends its own range-end row.
    const FrameDesc* rowAt(uint32_t offset) const {
        const FrameDesc* best = nullptr;
        for (int i = 0; i < _count; i++) {
            if (_table[i].loc <= _range_start + offset &&
                (best == nullptr || _table[i].loc >= best->loc)) {
                best = &_table[i];
            }
        }
        return best;
    }

  private:
    std::vector<uint8_t> _image;
    uint32_t _range_start = 0;
    FrameDesc* _table = nullptr;
    int _count = 0;
};

std::vector<uint8_t> savePcInSlot() {
    return {static_cast<uint8_t>(0x80 | DW_REG_PC), kSavedSlotFactor};  // DW_CFA_offset
}

}  // namespace

// A function that never saves the return-address register (an arm64 leaf)
// must keep the CIE rule in every row, not a stack slot at CFA+0.
TEST(DwarfPcColumn, RowsWithoutRaSaveCarryInitialPcOffset) {
    PcColumnFde fde({0x0e, 16,  // DW_CFA_def_cfa_offset 16
                     DW_CFA_advance_loc_4,
                     0x0e, 32,  // DW_CFA_def_cfa_offset 32
                     DW_CFA_advance_loc_4});
    for (uint32_t offset : {0u, 4u, 8u}) {
        const FrameDesc* row = fde.rowAt(offset);
        ASSERT_NE(nullptr, row) << "offset " << offset;
        EXPECT_EQ(INITIAL_PC_OFFSET, row->pc_off) << "offset " << offset;
    }
}

// DW_CFA_restore, DW_CFA_restore_extended and DW_CFA_same_value of the
// return-address column all put it back where the CIE had it (for x30: still
// in LR), so the epilogue rows after them must not keep the saved slot.
TEST(DwarfPcColumn, RestoreOfPcResetsToInitialPcOffset) {
    std::vector<uint8_t> insns = savePcInSlot();
    insns.push_back(DW_CFA_advance_loc_4);
    insns.push_back(static_cast<uint8_t>(0xc0 | DW_REG_PC));  // DW_CFA_restore
    insns.push_back(DW_CFA_advance_loc_4);
    PcColumnFde fde(insns);
    ASSERT_NE(nullptr, fde.rowAt(0));
    EXPECT_EQ(kSavedSlot, fde.rowAt(0)->pc_off);
    ASSERT_NE(nullptr, fde.rowAt(4));
    EXPECT_EQ(INITIAL_PC_OFFSET, fde.rowAt(4)->pc_off);
}

TEST(DwarfPcColumn, RestoreExtendedOfPcResetsToInitialPcOffset) {
    std::vector<uint8_t> insns = savePcInSlot();
    insns.insert(insns.end(), {DW_CFA_advance_loc_4,
                               0x06, static_cast<uint8_t>(DW_REG_PC),  // DW_CFA_restore_extended
                               DW_CFA_advance_loc_4});
    PcColumnFde fde(insns);
    ASSERT_NE(nullptr, fde.rowAt(4));
    EXPECT_EQ(kSavedSlot, fde.rowAt(0)->pc_off);
    EXPECT_EQ(INITIAL_PC_OFFSET, fde.rowAt(4)->pc_off);
}

TEST(DwarfPcColumn, SameValueOfPcResetsToInitialPcOffset) {
    std::vector<uint8_t> insns = savePcInSlot();
    insns.insert(insns.end(), {DW_CFA_advance_loc_4,
                               0x08, static_cast<uint8_t>(DW_REG_PC),  // DW_CFA_same_value
                               DW_CFA_advance_loc_4});
    PcColumnFde fde(insns);
    ASSERT_NE(nullptr, fde.rowAt(4));
    EXPECT_EQ(kSavedSlot, fde.rowAt(0)->pc_off);
    EXPECT_EQ(INITIAL_PC_OFFSET, fde.rowAt(4)->pc_off);
}

// DW_CFA_undefined marks an outermost frame, not a return address in LR, so
// it must not be folded into the reset above. Restoring an unrelated register
// must not touch the column either: the case split reads its operand once.
TEST(DwarfPcColumn, UndefinedOfPcAndRestoreOfOtherRegisterKeepTheSlot) {
    const uint8_t other_reg = 19;
    static_assert(other_reg != DW_REG_PC && other_reg != DW_REG_FP, "must be a third register");
    std::vector<uint8_t> insns = savePcInSlot();
    insns.insert(insns.end(), {DW_CFA_advance_loc_4,
                               0x07, static_cast<uint8_t>(DW_REG_PC),  // DW_CFA_undefined
                               0x0e, 16,                               // force a new row
                               DW_CFA_advance_loc_4,
                               0x06, other_reg,                        // DW_CFA_restore_extended
                               0x08, other_reg,                        // DW_CFA_same_value
                               static_cast<uint8_t>(0xc0 | other_reg), // DW_CFA_restore
                               0x0e, 32,
                               DW_CFA_advance_loc_4});
    PcColumnFde fde(insns);
    for (uint32_t offset : {0u, 4u, 8u}) {
        ASSERT_NE(nullptr, fde.rowAt(offset)) << "offset " << offset;
        EXPECT_EQ(kSavedSlot, fde.rowAt(offset)->pc_off) << "offset " << offset;
    }
}

// DW_CFA_restore_state with nothing remembered yields the parser's initial
// remembered state, which must also carry the CIE rule.
TEST(DwarfPcColumn, RestoreStateWithoutRememberUsesInitialPcOffset) {
    std::vector<uint8_t> insns = savePcInSlot();
    insns.insert(insns.end(), {DW_CFA_advance_loc_4,
                               0x0b,  // DW_CFA_restore_state
                               DW_CFA_advance_loc_4});
    PcColumnFde fde(insns);
    ASSERT_NE(nullptr, fde.rowAt(4));
    EXPECT_EQ(kSavedSlot, fde.rowAt(0)->pc_off);
    EXPECT_EQ(INITIAL_PC_OFFSET, fde.rowAt(4)->pc_off);
}

TEST(DwarfPcColumn, RememberRestoreStateRoundTripsPcOffset) {
    std::vector<uint8_t> insns = savePcInSlot();
    insns.insert(insns.end(), {0x0a,  // DW_CFA_remember_state
                               DW_CFA_advance_loc_4,
                               static_cast<uint8_t>(0xc0 | DW_REG_PC),  // DW_CFA_restore
                               DW_CFA_advance_loc_4,
                               0x0b,  // DW_CFA_restore_state
                               DW_CFA_advance_loc_4});
    PcColumnFde fde(insns);
    ASSERT_NE(nullptr, fde.rowAt(8));
    EXPECT_EQ(kSavedSlot, fde.rowAt(0)->pc_off);
    EXPECT_EQ(INITIAL_PC_OFFSET, fde.rowAt(4)->pc_off);
    EXPECT_EQ(kSavedSlot, fde.rowAt(8)->pc_off);
}

// The frame-pointer column keeps its existing rule for all three ops.
TEST(DwarfPcColumn, RestoreExtendedSameValueAndUndefinedOfFpResetFp) {
    const uint8_t save_fp[] = {static_cast<uint8_t>(0x80 | DW_REG_FP), kSavedSlotFactor};
    std::vector<uint8_t> insns;
    for (uint8_t op : {static_cast<uint8_t>(0x06), static_cast<uint8_t>(0x08),
                       static_cast<uint8_t>(0x07)}) {
        insns.insert(insns.end(), std::begin(save_fp), std::end(save_fp));
        insns.push_back(DW_CFA_advance_loc_4);
        insns.push_back(op);
        insns.push_back(static_cast<uint8_t>(DW_REG_FP));
        insns.push_back(DW_CFA_advance_loc_4);
    }
    PcColumnFde fde(insns);
    for (uint32_t offset : {0u, 8u, 16u}) {
        ASSERT_NE(nullptr, fde.rowAt(offset + 4)) << "offset " << offset;
        EXPECT_EQ(kSavedSlot, fde.rowAt(offset)->fp_off) << "offset " << offset;
        EXPECT_EQ(DW_SAME_FP, fde.rowAt(offset + 4)->fp_off) << "offset " << offset;
    }
}

// DW_CFA_register moves the return address to a register the walker does not
// track, so those rows must stop the walk; restoring x30 makes them usable again.
TEST(DwarfPcColumn, RegisterOfPcStopsTheWalkUntilRestored) {
    PcColumnFde fde({0x09, static_cast<uint8_t>(DW_REG_PC), 9,  // DW_CFA_register PC, x9
                     DW_CFA_advance_loc_4,
                     static_cast<uint8_t>(0xc0 | DW_REG_PC),  // DW_CFA_restore
                     DW_CFA_advance_loc_4});
    ASSERT_NE(nullptr, fde.rowAt(0));
    EXPECT_EQ(static_cast<u32>(DW_REG_INVALID), fde.rowAt(0)->cfa & 0xff);
    ASSERT_NE(nullptr, fde.rowAt(4));
    EXPECT_EQ(static_cast<u32>(DW_REG_SP), fde.rowAt(4)->cfa & 0xff);
    EXPECT_EQ(INITIAL_PC_OFFSET, fde.rowAt(4)->pc_off);
}

// Moving another register leaves the column alone, and both operands are
// consumed: the following DW_CFA_def_cfa_offset still applies.
TEST(DwarfPcColumn, RegisterOfOtherRegisterKeepsThePcRule) {
    std::vector<uint8_t> insns = savePcInSlot();
    insns.insert(insns.end(), {DW_CFA_advance_loc_4,
                               0x09, 19, 9,  // DW_CFA_register x19, x9
                               0x0e, 32,     // DW_CFA_def_cfa_offset 32
                               DW_CFA_advance_loc_4});
    PcColumnFde fde(insns);
    ASSERT_NE(nullptr, fde.rowAt(4));
    EXPECT_EQ(kSavedSlot, fde.rowAt(4)->pc_off);
    EXPECT_EQ(static_cast<u32>(DW_REG_SP), fde.rowAt(4)->cfa & 0xff);
    EXPECT_EQ(32, static_cast<int>(fde.rowAt(4)->cfa) >> 8);
}

// A pc in the PLT range below the first row is served FrameDesc::empty_frame.
// PLT entries do not save x30, so that row must carry the CIE rule too.
TEST(DwarfPcColumn, PltRangeBelowFirstRowUsesInitialPcOffset) {
    static char text[0x200];
    CodeCache cc("dwarf_pc_column_plt", /*lib_index=*/-1, text, text + sizeof(text), text);
    cc.setTextBase(text);
    cc.setPlt(/*plt_offset=*/0, /*plt_size=*/0x40);
    FrameDesc* table = static_cast<FrameDesc*>(malloc(sizeof(FrameDesc)));
    ASSERT_NE(nullptr, table);
    *table = FrameDesc::default_frame;
    table->loc = 0x100;
    cc.setDwarfTable(table, 1);

    FrameDesc row = cc.findFrameDesc(text + 0x10);
    // empty_frame, not the default frame: CFA is SP-based.
    EXPECT_EQ(static_cast<u32>(DW_REG_SP), row.cfa & 0xff);
    EXPECT_EQ(INITIAL_PC_OFFSET, row.pc_off);
}

#endif  // DWARF_SUPPORTED
