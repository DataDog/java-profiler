/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "sframe.h"
#include "../../main/cpp/gtest_crash_handler.h"

#include <cstdint>
#include <cstring>
#include <vector>

static constexpr char SFRAME_TEST_NAME[] = "SFrameTest";

class SFrameGlobalSetup {
  public:
    SFrameGlobalSetup()  { installGtestCrashHandler<SFRAME_TEST_NAME>(); }
    ~SFrameGlobalSetup() { restoreDefaultSignalHandlers(); }
};
static SFrameGlobalSetup sframe_global_setup;

#ifdef __linux__

// --- Architecture constants ---
#ifdef __x86_64__
static const uint8_t HOST_ABI  = SFRAME_ABI_AMD64_ENDIAN_LITTLE;
static const uint8_t WRONG_ABI = SFRAME_ABI_AARCH64_ENDIAN_LITTLE;
#elif defined(__aarch64__)
static const uint8_t HOST_ABI  = SFRAME_ABI_AARCH64_ENDIAN_LITTLE;
static const uint8_t WRONG_ABI = SFRAME_ABI_AMD64_ENDIAN_LITTLE;
#else
static const uint8_t HOST_ABI  = 0xFF;
static const uint8_t WRONG_ABI = 0xFE;
#endif

// --- Binary builder helpers ---
static void put8(std::vector<uint8_t>& buf, uint8_t v) { buf.push_back(v); }

static void put16(std::vector<uint8_t>& buf, uint16_t v) {
    buf.push_back(static_cast<uint8_t>(v));
    buf.push_back(static_cast<uint8_t>(v >> 8));
}

static void put32(std::vector<uint8_t>& buf, uint32_t v) {
    buf.push_back(static_cast<uint8_t>(v));
    buf.push_back(static_cast<uint8_t>(v >> 8));
    buf.push_back(static_cast<uint8_t>(v >> 16));
    buf.push_back(static_cast<uint8_t>(v >> 24));
}

// Appends a valid SFrameHeader (28 bytes, auxhdr_len=0).
static void buildHeader(std::vector<uint8_t>& buf,
                        uint8_t  abi_arch,
                        int8_t   cfa_fixed_ra_offset,
                        uint32_t num_fdes,
                        uint32_t num_fres,
                        uint32_t fre_len,
                        uint32_t fdeoff,
                        uint32_t freoff) {
    put16(buf, SFRAME_MAGIC);
    put8(buf, SFRAME_VERSION_2);
    put8(buf, SFRAME_F_FDE_SORTED);
    put8(buf, abi_arch);
    put8(buf, 0);                            // cfa_fixed_fp_offset
    put8(buf, static_cast<uint8_t>(cfa_fixed_ra_offset));
    put8(buf, 0);                            // auxhdr_len
    put32(buf, num_fdes);
    put32(buf, num_fres);
    put32(buf, fre_len);
    put32(buf, fdeoff);
    put32(buf, freoff);
}

// Appends an SFrameFDE (20 bytes).
// fre_type: SFRAME_FRE_TYPE_ADDR1/2/4; pcmask: set bit 0 of info for PCMASK type.
static void buildFDE(std::vector<uint8_t>& buf,
                     int32_t  start_addr,
                     uint32_t func_size,
                     uint32_t fre_off,
                     uint32_t fre_num,
                     uint8_t  fre_type,
                     bool     pcmask = false) {
    put32(buf, static_cast<uint32_t>(start_addr));
    put32(buf, func_size);
    put32(buf, fre_off);
    put32(buf, fre_num);
    uint8_t info = (pcmask ? 0x1 : 0x0) | (fre_type << 1);
    put8(buf, info);
    put8(buf, 0);    // rep_size
    put16(buf, 0);   // padding
}

// Appends an FRE with 1-byte start address (ADDR1) and 1-byte signed offsets (OFFSET_1B).
// fre_info bits: bit0=CFA_base(0=SP,1=FP), bits1-2=0(1B), bit3=RA_tracked, bit4=FP_tracked.
// fp_off and ra_off are written only when the corresponding bit is set in fre_info.
static void buildFRE_1B(std::vector<uint8_t>& buf,
                        uint8_t start_offset,
                        uint8_t fre_info,
                        int8_t  cfa_off,
                        int8_t  fp_off = 0,
                        int8_t  ra_off = 0) {
    put8(buf, start_offset);
    put8(buf, fre_info);
    put8(buf, static_cast<uint8_t>(cfa_off));
    if (SFRAME_FRE_FP_TRACKED(fre_info)) put8(buf, static_cast<uint8_t>(fp_off));
    if (SFRAME_FRE_RA_TRACKED(fre_info)) put8(buf, static_cast<uint8_t>(ra_off));
}

// Appends an FRE with 2-byte start address (ADDR2) and 2-byte signed offsets (OFFSET_2B).
static void buildFRE_2B(std::vector<uint8_t>& buf,
                        uint16_t start_offset,
                        uint8_t  fre_info,
                        int16_t  cfa_off,
                        int16_t  fp_off = 0,
                        int16_t  ra_off = 0) {
    put16(buf, start_offset);
    put8(buf, fre_info);
    put16(buf, static_cast<uint16_t>(cfa_off));
    if (SFRAME_FRE_FP_TRACKED(fre_info)) put16(buf, static_cast<uint16_t>(fp_off));
    if (SFRAME_FRE_RA_TRACKED(fre_info)) put16(buf, static_cast<uint16_t>(ra_off));
}

// Appends an FRE with 4-byte start address (ADDR4) and 4-byte signed offsets (OFFSET_4B).
static void buildFRE_4B(std::vector<uint8_t>& buf,
                        uint32_t start_offset,
                        uint8_t  fre_info,
                        int32_t  cfa_off,
                        int32_t  fp_off = 0,
                        int32_t  ra_off = 0) {
    put32(buf, start_offset);
    put8(buf, fre_info);
    put32(buf, static_cast<uint32_t>(cfa_off));
    if (SFRAME_FRE_FP_TRACKED(fre_info)) put32(buf, static_cast<uint32_t>(fp_off));
    if (SFRAME_FRE_RA_TRACKED(fre_info)) put32(buf, static_cast<uint32_t>(ra_off));
}

// ============================================================
// Header validation tests
// ============================================================

TEST(SFrameParser, InvalidMagic) {
    std::vector<uint8_t> buf(28, 0);  // all zeros; magic = 0x0000, not 0xDEE2
    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
    EXPECT_FALSE(parser.parse());
}

TEST(SFrameParser, UnsupportedVersion) {
    std::vector<uint8_t> buf;
    buildHeader(buf, HOST_ABI, -8, 0, 0, 0, 0, 0);
    buf[2] = 3;  // overwrite version byte with V3
    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
    EXPECT_FALSE(parser.parse());
}

TEST(SFrameParser, WrongArch) {
    // Build a structurally valid section with WRONG_ABI to confirm arch check fires.
    std::vector<uint8_t> fre_buf;
    buildFRE_1B(fre_buf, 0, 0x00, 8);  // start=0, SP-based, cfa_off=8

    std::vector<uint8_t> buf;
    buildHeader(buf, WRONG_ABI, -8, 1, 1,
                static_cast<uint32_t>(fre_buf.size()),  // fre_len
                0,                                       // fdeoff (FDE array right after header)
                20);                                     // freoff (FRE section after FDE)
    buildFDE(buf, 0x1000, 64, 0, 1, SFRAME_FRE_TYPE_ADDR1);
    buf.insert(buf.end(), fre_buf.begin(), fre_buf.end());

    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
    EXPECT_FALSE(parser.parse());
}

TEST(SFrameParser, TruncatedSection) {
    std::vector<uint8_t> buf;
    buildHeader(buf, HOST_ABI, -8, 0, 0, 0, 0, 0);
    buf.resize(10);  // shorter than sizeof(SFrameHeader) = 28
    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
    EXPECT_FALSE(parser.parse());
}

TEST(SFrameParser, AuxhdrLenBoundsCheck) {
    // auxhdr_len = 200 pushes data_start past section end
    std::vector<uint8_t> buf;
    buildHeader(buf, HOST_ABI, -8, 0, 0, 0, 0, 0);
    buf[7] = 200;  // auxhdr_len byte
    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
    EXPECT_FALSE(parser.parse());
}

TEST(SFrameParser, EmptyFDEArray) {
    // num_fdes=0 → no records → parse() returns false
    std::vector<uint8_t> buf;
    buildHeader(buf, HOST_ABI, -8, /*num_fdes=*/0, 0, 0, 0, 0);
    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
    EXPECT_FALSE(parser.parse());
}

TEST(SFrameParser, PCMASK_Skipped) {
    // A single FDE with PCMASK type (bit 0 set in info) is skipped; no records → false
    //
    // Layout: header(28) | FDE(20) | FRE(3)
    // fdeoff=0 (FDE array starts at data_start), freoff=20 (FRE section after FDE)
    std::vector<uint8_t> fre_buf;
    buildFRE_1B(fre_buf, 0, 0x00, 8);  // valid FRE, but FDE is PCMASK so it's skipped

    std::vector<uint8_t> buf;
    buildHeader(buf, HOST_ABI, -8, 1, 1, (uint32_t)fre_buf.size(), /*fdeoff=*/0, /*freoff=*/20);
    buildFDE(buf, 0x100, 64, 0, 1, SFRAME_FRE_TYPE_ADDR1, /*pcmask=*/true);
    buf.insert(buf.end(), fre_buf.begin(), fre_buf.end());

    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
    EXPECT_FALSE(parser.parse());
}

TEST(SFrameParser, EmptyFDE_Skipped) {
    // A single FDE with fre_num=0 is skipped; no records → false
    std::vector<uint8_t> buf;
    buildHeader(buf, HOST_ABI, -8, 1, 0, 0, /*fdeoff=*/0, /*freoff=*/20);
    buildFDE(buf, 0x100, 64, 0, /*fre_num=*/0, SFRAME_FRE_TYPE_ADDR1);

    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
    EXPECT_FALSE(parser.parse());
}

TEST(SFrameParser, SingleFDE_SingleFRE_SPBased) {
    // SP-based CFA with fixed RA offset -8 (x86_64 style).
    // fre_info = 0x00: SP base (bit0=0), 1B offsets (bits1-2=0), no RA (bit3=0), no FP (bit4=0)
    // CFA offset = 8  → cfa = (8 << 8) | DW_REG_SP
    // fp_off = DW_SAME_FP (FP not tracked)
    // pc_off = -8      (from cfa_fixed_ra_offset)
    //
    // Layout: header(28) | FDE(20) | FRE(3 bytes: 1 addr + 1 info + 1 cfa_off)
    std::vector<uint8_t> fre_buf;
    buildFRE_1B(fre_buf, /*start_offset=*/0, /*fre_info=*/0x00, /*cfa_off=*/8);

    std::vector<uint8_t> buf;
    buildHeader(buf, HOST_ABI, /*cfa_fixed_ra_offset=*/-8, 1, 1,
                (uint32_t)fre_buf.size(), /*fdeoff=*/0, /*freoff=*/20);
    buildFDE(buf, /*start_addr=*/0x1000, 64, 0, 1, SFRAME_FRE_TYPE_ADDR1);
    buf.insert(buf.end(), fre_buf.begin(), fre_buf.end());

    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
    ASSERT_TRUE(parser.parse());
    EXPECT_EQ(parser.count(), 1);

    FrameDesc* table = parser.table();
    ASSERT_NE(table, nullptr);
    // loc = section_offset(0) + start_addr(0x1000) + fre_start(0) = 0x1000
    EXPECT_EQ(table[0].loc, static_cast<u32>(0x1000));
    // cfa = (8 << 8) | DW_REG_SP
    EXPECT_EQ(table[0].cfa, static_cast<u32>((8u << 8) | (unsigned)DW_REG_SP));
    EXPECT_EQ(table[0].fp_off, DW_SAME_FP);
    EXPECT_EQ(table[0].pc_off, -8);
    free(table);
}

TEST(SFrameParser, SingleFDE_SingleFRE_FPBased) {
    // FP-based CFA with FP tracked, fixed RA offset -8.
    // fre_info = 0x11: FP base (bit0=1), 1B offsets (bits1-2=0), no RA (bit3=0), FP tracked (bit4=1)
    //                = 0b00010001 = 0x11
    // CFA offset = 16 → cfa = (16 << 8) | DW_REG_FP
    // fp_off = -16
    // pc_off = -8
    std::vector<uint8_t> fre_buf;
    buildFRE_1B(fre_buf, 4, /*fre_info=*/0x11, /*cfa_off=*/16, /*fp_off=*/-16);

    std::vector<uint8_t> buf;
    buildHeader(buf, HOST_ABI, -8, 1, 1, (uint32_t)fre_buf.size(), 0, 20);
    buildFDE(buf, 0x2000, 128, 0, 1, SFRAME_FRE_TYPE_ADDR1);
    buf.insert(buf.end(), fre_buf.begin(), fre_buf.end());

    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
    ASSERT_TRUE(parser.parse());
    EXPECT_EQ(parser.count(), 1);

    FrameDesc* table = parser.table();
    ASSERT_NE(table, nullptr);
    // loc = 0 + 0x2000 + 4 = 0x2004
    EXPECT_EQ(table[0].loc, static_cast<u32>(0x2004));
    EXPECT_EQ(table[0].cfa, static_cast<u32>((16u << 8) | (unsigned)DW_REG_FP));
    EXPECT_EQ(table[0].fp_off, -16);
    EXPECT_EQ(table[0].pc_off, -8);
    free(table);
}

TEST(SFrameParser, FixedRAOffset) {
    // Verify cfa_fixed_ra_offset drives pc_off even when FRE RA bit is set.
    // fre_info = 0x08: SP base (bit0=0), 1B offsets (bits1-2=0), RA tracked (bit3=1), no FP (bit4=0)
    // The FRE encodes ra_off=-16, but the header's cfa_fixed_ra_offset=-8 must win.
    std::vector<uint8_t> fre_buf;
    buildFRE_1B(fre_buf, 0, /*fre_info=*/0x08, /*cfa_off=*/8, /*fp_off=*/0, /*ra_off=*/-16);

    std::vector<uint8_t> buf;
    buildHeader(buf, HOST_ABI, /*cfa_fixed_ra_offset=*/-8, 1, 1,
                (uint32_t)fre_buf.size(), 0, 20);
    buildFDE(buf, 0x500, 32, 0, 1, SFRAME_FRE_TYPE_ADDR1);
    buf.insert(buf.end(), fre_buf.begin(), fre_buf.end());

    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
    ASSERT_TRUE(parser.parse());
    FrameDesc* table = parser.table();
    ASSERT_NE(table, nullptr);
    // pc_off must come from the header (-8), not from the FRE RA offset (-16)
    EXPECT_EQ(table[0].pc_off, -8);
    free(table);
}

TEST(SFrameParser, PerFRE_RA) {
    // aarch64 style: cfa_fixed_ra_offset=0, RA tracked per-FRE.
    // fre_info = 0x08: SP base (bit0=0), 1B offsets (bits1-2=0), RA tracked (bit3=1), no FP (bit4=0)
    //                = 0b00001000 = 0x08
    // RA offset = -8
    std::vector<uint8_t> fre_buf;
    buildFRE_1B(fre_buf, 0, /*fre_info=*/0x08, /*cfa_off=*/16, /*fp_off=*/0, /*ra_off=*/-8);

    std::vector<uint8_t> buf;
    buildHeader(buf, HOST_ABI, /*cfa_fixed_ra_offset=*/0, 1, 1,
                (uint32_t)fre_buf.size(), 0, 20);
    buildFDE(buf, 0x3000, 64, 0, 1, SFRAME_FRE_TYPE_ADDR1);
    buf.insert(buf.end(), fre_buf.begin(), fre_buf.end());

    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
    ASSERT_TRUE(parser.parse());
    FrameDesc* table = parser.table();
    ASSERT_NE(table, nullptr);
    EXPECT_EQ(table[0].pc_off, -8);
    free(table);
}

TEST(SFrameParser, PerFRE_RA_Untracked) {
    // aarch64 leaf function: cfa_fixed_ra_offset=0, RA not tracked → DW_LINK_REGISTER.
    // fre_info = 0x00: SP base, 1B offsets, no RA, no FP
    std::vector<uint8_t> fre_buf;
    buildFRE_1B(fre_buf, 0, 0x00, 8);

    std::vector<uint8_t> buf;
    buildHeader(buf, HOST_ABI, /*cfa_fixed_ra_offset=*/0, 1, 1,
                (uint32_t)fre_buf.size(), 0, 20);
    buildFDE(buf, 0x4000, 32, 0, 1, SFRAME_FRE_TYPE_ADDR1);
    buf.insert(buf.end(), fre_buf.begin(), fre_buf.end());

    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
    ASSERT_TRUE(parser.parse());
    FrameDesc* table = parser.table();
    ASSERT_NE(table, nullptr);
    EXPECT_EQ(table[0].pc_off, DW_LINK_REGISTER);
    free(table);
}

TEST(SFrameParser, OffsetSize_2B) {
    // FRE with 2-byte start address (ADDR2) and 2-byte offset encoding (OFFSET_2B).
    // fre_info = 0x02: SP base (bit0=0), 2B offsets (bits1-2=01), no RA, no FP
    //                = 0b00000010 = 0x02
    // CFA offset = 512 (requires 2 bytes)
    std::vector<uint8_t> fre_buf;
    buildFRE_2B(fre_buf, /*start_offset=*/8, /*fre_info=*/0x02, /*cfa_off=*/512);

    // fre_buf size: 2 (addr) + 1 (info) + 2 (cfa) = 5 bytes
    std::vector<uint8_t> buf;
    buildHeader(buf, HOST_ABI, -8, 1, 1, (uint32_t)fre_buf.size(), 0, 20);
    buildFDE(buf, 0x5000, 256, 0, 1, SFRAME_FRE_TYPE_ADDR2);
    buf.insert(buf.end(), fre_buf.begin(), fre_buf.end());

    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
    ASSERT_TRUE(parser.parse());
    FrameDesc* table = parser.table();
    ASSERT_NE(table, nullptr);
    // loc = 0 + 0x5000 + 8 = 0x5008
    EXPECT_EQ(table[0].loc, static_cast<u32>(0x5008));
    // cfa = (512 << 8) | DW_REG_SP
    EXPECT_EQ(table[0].cfa, static_cast<u32>((512u << 8) | (unsigned)DW_REG_SP));
    free(table);
}

TEST(SFrameParser, OffsetSize_4B) {
    // FRE with 4-byte start address (ADDR4) and 4-byte offset encoding (OFFSET_4B).
    // fre_info = 0x04: SP base (bit0=0), 4B offsets (bits1-2=10), no RA, no FP
    //                = 0b00000100 = 0x04
    // CFA offset = 65536 (requires 4 bytes)
    std::vector<uint8_t> fre_buf;
    buildFRE_4B(fre_buf, /*start_offset=*/0, /*fre_info=*/0x04, /*cfa_off=*/65536);

    // fre_buf size: 4 (addr) + 1 (info) + 4 (cfa) = 9 bytes
    std::vector<uint8_t> buf;
    buildHeader(buf, HOST_ABI, -8, 1, 1, (uint32_t)fre_buf.size(), 0, 20);
    buildFDE(buf, 0x6000, 512, 0, 1, SFRAME_FRE_TYPE_ADDR4);
    buf.insert(buf.end(), fre_buf.begin(), fre_buf.end());

    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
    ASSERT_TRUE(parser.parse());
    FrameDesc* table = parser.table();
    ASSERT_NE(table, nullptr);
    EXPECT_EQ(table[0].loc, static_cast<u32>(0x6000));
    EXPECT_EQ(table[0].cfa, static_cast<u32>((65536u << 8) | (unsigned)DW_REG_SP));
    free(table);
}

TEST(SFrameParser, MultipleFDEs) {
    // 3 FDEs with 2 FREs each → 6 total records, verify sorted by loc.
    //
    // FRE layout (2 FREs per FDE × 3 FDEs, each FRE = 3 bytes: 1addr+1info+1cfa):
    //   FDE0 FREs at fre_section+0:  offset 0 cfa=8, offset 8 cfa=16
    //   FDE1 FREs at fre_section+6:  offset 0 cfa=8, offset 4 cfa=16
    //   FDE2 FREs at fre_section+12: offset 0 cfa=8, offset 2 cfa=16
    std::vector<uint8_t> fre_buf;
    buildFRE_1B(fre_buf, 0, 0x00, 8);
    buildFRE_1B(fre_buf, 8, 0x00, 16);
    buildFRE_1B(fre_buf, 0, 0x00, 8);
    buildFRE_1B(fre_buf, 4, 0x00, 16);
    buildFRE_1B(fre_buf, 0, 0x00, 8);
    buildFRE_1B(fre_buf, 2, 0x00, 16);
    // fre_buf.size() = 18

    std::vector<uint8_t> buf;
    // freoff = 3 * sizeof(SFrameFDE) = 60
    buildHeader(buf, HOST_ABI, -8, 3, 6, (uint32_t)fre_buf.size(), /*fdeoff=*/0, /*freoff=*/60);
    buildFDE(buf, 0xA000, 32, 0,  2, SFRAME_FRE_TYPE_ADDR1);  // FDE0: FREs at offset 0
    buildFDE(buf, 0xB000, 32, 6,  2, SFRAME_FRE_TYPE_ADDR1);  // FDE1: FREs at offset 6
    buildFDE(buf, 0xC000, 32, 12, 2, SFRAME_FRE_TYPE_ADDR1);  // FDE2: FREs at offset 12
    buf.insert(buf.end(), fre_buf.begin(), fre_buf.end());

    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
    ASSERT_TRUE(parser.parse());
    EXPECT_EQ(parser.count(), 6);

    FrameDesc* table = parser.table();
    ASSERT_NE(table, nullptr);
    // Verify sorted ascending
    for (int i = 0; i + 1 < 6; i++) {
        EXPECT_LT(table[i].loc, table[i + 1].loc)
            << "table not sorted at index " << i;
    }
    // Spot-check locs: FDE0@0xA000, FDE0@0xA008, FDE1@0xB000, ...
    EXPECT_EQ(table[0].loc, static_cast<u32>(0xA000));
    EXPECT_EQ(table[1].loc, static_cast<u32>(0xA008));
    EXPECT_EQ(table[2].loc, static_cast<u32>(0xB000));
    free(table);
}

TEST(SFrameParser, AddressTranslation) {
    // section_offset=0x1000, FDE start_addr=0x200, FRE start=0x10
    // Expected loc = 0x1000 + 0x200 + 0x10 = 0x1210
    std::vector<uint8_t> fre_buf;
    buildFRE_1B(fre_buf, /*start_offset=*/0x10, 0x00, 8);

    std::vector<uint8_t> buf;
    buildHeader(buf, HOST_ABI, -8, 1, 1, (uint32_t)fre_buf.size(), 0, 20);
    buildFDE(buf, /*start_addr=*/0x200, 64, 0, 1, SFRAME_FRE_TYPE_ADDR1);
    buf.insert(buf.end(), fre_buf.begin(), fre_buf.end());

    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(),
                        /*section_offset=*/0x1000);
    ASSERT_TRUE(parser.parse());
    FrameDesc* table = parser.table();
    ASSERT_NE(table, nullptr);
    EXPECT_EQ(table[0].loc, static_cast<u32>(0x1210));
    free(table);
}

TEST(SFrameParser, BoundsCheck_FREOverrun) {
    // FDE0's fre_off points at fre_end → parseFDE entry-level bounds check fires
    // immediately (no records added). FDE1 has a valid FRE → 1 record.
    //
    // Layout: header(28) | FDE0(20) | FDE1(20) | FRE(3 bytes)
    // fre_section = data_start + 40, fre_end = fre_section + 3
    // FDE0: fre_off=3, fre_num=1 → fre_ptr = fre_section+3 = fre_end → fail
    // FDE1: fre_off=0, fre_num=1 → fre_ptr = fre_section+0 → reads 3 bytes → OK
    std::vector<uint8_t> fre_buf;
    buildFRE_1B(fre_buf, 0, 0x00, 8);   // FDE1's FRE (3 bytes at offset 0)
    // fre_buf.size() = 3; FDE0's fre_off=3 points exactly at fre_end

    std::vector<uint8_t> buf;
    // freoff = 2 * sizeof(SFrameFDE) = 40
    buildHeader(buf, HOST_ABI, -8, 2, 1, (uint32_t)fre_buf.size(), /*fdeoff=*/0, /*freoff=*/40);
    buildFDE(buf, 0xD000, 64, /*fre_off=*/3, /*fre_num=*/1, SFRAME_FRE_TYPE_ADDR1);  // overruns
    buildFDE(buf, 0xE000, 64, /*fre_off=*/0, /*fre_num=*/1, SFRAME_FRE_TYPE_ADDR1);  // OK
    buf.insert(buf.end(), fre_buf.begin(), fre_buf.end());

    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
    // parse() returns true because FDE1 produced a record
    ASSERT_TRUE(parser.parse());
    EXPECT_EQ(parser.count(), 1);  // only FDE1's FRE made it through
    FrameDesc* table = parser.table();
    ASSERT_NE(table, nullptr);
    EXPECT_EQ(table[0].loc, static_cast<u32>(0xE000));
    free(table);
}

TEST(SFrameParser, ParseFailure_FreesTable) {
    // parse() fails (wrong magic) → destructor must free _table without crashing.
    // With ASAN this also detects leaks.
    std::vector<uint8_t> buf(28, 0);  // all zeros → wrong magic
    {
        SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
        EXPECT_FALSE(parser.parse());
        // destructor runs here; _table was malloc'd in constructor and must be freed
    }
    // Reaching here without crash/ASAN report is the pass condition
}

TEST(SFrameParser, DefaultFrameDetection) {
    // Build a section with one FP-based FRE so _linked_frame_size gets set.
    // fre_info = 0x11: FP base (bit0=1), 1B offsets (bits1-2=0), no RA, FP tracked (bit4=1)
    //                = 0b00010001 = 0x11
    // cfa_offset = LINKED_FRAME_CLANG_SIZE (16 on both x86_64 and aarch64 clang)
    //
    // On x86_64: LINKED_FRAME_CLANG_SIZE == LINKED_FRAME_SIZE == 16
    //   → detectedDefaultFrame() returns default_frame regardless
    // On aarch64: LINKED_FRAME_CLANG_SIZE == 16, LINKED_FRAME_SIZE == 0
    //   → detectedDefaultFrame() returns default_clang_frame
    //
    // In both cases: the function must not crash and must return a valid reference.
    std::vector<uint8_t> fre_buf;
    buildFRE_1B(fre_buf, 4, 0x11, (int8_t)LINKED_FRAME_CLANG_SIZE, (int8_t)-LINKED_FRAME_CLANG_SIZE);

    std::vector<uint8_t> buf;
    buildHeader(buf, HOST_ABI, -8, 1, 1, (uint32_t)fre_buf.size(), 0, 20);
    buildFDE(buf, 0xF000, 64, 0, 1, SFRAME_FRE_TYPE_ADDR1);
    buf.insert(buf.end(), fre_buf.begin(), fre_buf.end());

    SFrameParser parser("test", reinterpret_cast<const char*>(buf.data()), buf.size(), 0);
    ASSERT_TRUE(parser.parse());
    // Just verify it returns one of the two valid static references without crashing
    const FrameDesc& def = parser.detectedDefaultFrame();
    EXPECT_TRUE(&def == &FrameDesc::default_frame || &def == &FrameDesc::default_clang_frame);
    free(parser.table());
}

#endif  // __linux__
