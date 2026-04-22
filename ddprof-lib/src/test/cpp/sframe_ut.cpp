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
    std::vector<uint8_t> buf;
    buildHeader(buf, WRONG_ABI, -8, 0, 0, 0, 0, 0);
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

#endif  // __linux__
