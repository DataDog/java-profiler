/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "dwarf.h"
#include "../../main/cpp/gtest_crash_handler.h"

#include <cstdint>
#include <cstring>
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
    appendCie(buf);  // 15 bytes; _has_z_augmentation = true

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

#endif  // DWARF_SUPPORTED
