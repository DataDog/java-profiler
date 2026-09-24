/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Gates the address split in Profiler::resolveNativeFrameForWalkVM, which
// HotspotSupport::walkVM relies on for every non-Java frame: range lookups
// (findLibraryByAddress/binarySearch) key off the attribution address so a
// call that is the last instruction of its caller still resolves to the
// caller, while the remote-symbolication pc_offset keeps deriving from the
// raw pc because its meaning is a cross-team wire contract.
//
// These use synthetic CodeCaches rather than the test binary's own symbols,
// so unlike returnAddressAttribution_ut.cpp they need no GNU-as/ELF-CFI asm
// and no reliance on updateSymbols() parsing the main executable -- they run
// on every platform this repo builds.

#include <gtest/gtest.h>
#include <cstdint>
#include "codeCache.h"
#include "libraries.h"
#include "profiler.h"
#include "vmEntry.h"

namespace {

// Far above anything the loader maps, so these never overlap a real library
// in the process-wide set they are published into.
const char* const kSymbolLibBase = (const char*)0x5a5a00000000ULL;
const char* const kBareLibBase   = (const char*)0x5a5b00000000ULL;
const size_t kLibSpan = 0x1000;

// Zero-gap pair: `second` starts on the byte immediately after `first` ends,
// which is exactly where a return address lands when the call is the last
// instruction of `first`.
const int kFirstOff  = 0x100;
const int kFuncLen   = 0x10;
const int kBoundary  = kFirstOff + kFuncLen;

// No symbol covers this, so resolution falls through to the library-relative
// packing path that carries pc_offset.
const int kUnnamedOff = 0x800;

class WalkVmAttributionTest : public ::testing::Test {
  protected:
    static void SetUpTestSuite() {
        // CodeCacheArray is append-only and the set is process-wide, so both
        // caches are published once and outlive every test in this binary.
        static CodeCache symbol_lib("walkvm_attr_symbols", /*lib_index=*/-1,
                                    kSymbolLibBase, kSymbolLibBase + kLibSpan,
                                    /*image_base=*/kSymbolLibBase);
        symbol_lib.add(kSymbolLibBase + kFirstOff, kFuncLen, "walkvm_attr_first");
        symbol_lib.add(kSymbolLibBase + kBoundary, kFuncLen, "walkvm_attr_second");
        symbol_lib.sort();

        static CodeCache bare_lib("walkvm_attr_nosymbols", /*lib_index=*/-1,
                                  kBareLibBase, kBareLibBase + kLibSpan,
                                  /*image_base=*/kBareLibBase);

        ASSERT_TRUE(Libraries::instance()->addLibraryForTest(&symbol_lib));
        ASSERT_TRUE(Libraries::instance()->addLibraryForTest(&bare_lib));
    }

    static Profiler::NativeFrameResolution resolve(const char* pc, bool pc_is_ra) {
        return Profiler::instance()->resolveNativeFrameForWalkVM(
            (uintptr_t)pc, pc_is_ra, /*lock_index=*/0);
    }
};

// The defect this fix addresses: at a zero-gap boundary the raw return
// address names the following function, and only the attribution address
// still names the caller that actually made the call.
TEST_F(WalkVmAttributionTest, ReturnAddressAtZeroGapBoundaryResolvesToTheCaller) {
    const char* boundary = kSymbolLibBase + kBoundary;

    Profiler::NativeFrameResolution exact = resolve(boundary, /*pc_is_ra=*/false);
    ASSERT_EQ(BCI_NATIVE_FRAME, exact.bci);
    ASSERT_NE(nullptr, exact.method_name);
    EXPECT_STREQ("walkvm_attr_second", exact.method_name)
        << "an exact pc on the first byte of a function resolves to that function";

    Profiler::NativeFrameResolution as_ra = resolve(boundary, /*pc_is_ra=*/true);
    ASSERT_EQ(BCI_NATIVE_FRAME, as_ra.bci);
    ASSERT_NE(nullptr, as_ra.method_name);
    EXPECT_STREQ("walkvm_attr_first", as_ra.method_name)
        << "the same address flagged as a return address must resolve to the caller, "
        << "not to whatever happens to follow it";
}

// Inside a function the adjustment must be invisible -- it only ever moves the
// lookup by one byte, so it may not reclassify a pc that is nowhere near a
// boundary.
TEST_F(WalkVmAttributionTest, AddressInsideAFunctionResolvesTheSameEitherWay) {
    const char* inside = kSymbolLibBase + kFirstOff + kFuncLen / 2;

    Profiler::NativeFrameResolution exact = resolve(inside, /*pc_is_ra=*/false);
    Profiler::NativeFrameResolution as_ra = resolve(inside, /*pc_is_ra=*/true);

    ASSERT_NE(nullptr, exact.method_name);
    ASSERT_NE(nullptr, as_ra.method_name);
    EXPECT_STREQ("walkvm_attr_first", exact.method_name);
    EXPECT_STREQ("walkvm_attr_first", as_ra.method_name);
}

// The wire contract: the lookup may move, the emitted offset may not. This is
// what keeps walkVM out of the unresolved cross-team question about what
// pc_offset means to the backend symbolizer.
TEST_F(WalkVmAttributionTest, PcOffsetStaysDerivedFromTheRawPc) {
    const char* pc = kBareLibBase + kUnnamedOff;

    Profiler::NativeFrameResolution exact = resolve(pc, /*pc_is_ra=*/false);
    Profiler::NativeFrameResolution as_ra = resolve(pc, /*pc_is_ra=*/true);

    ASSERT_EQ(BCI_NATIVE_FRAME_REMOTE, exact.bci);
    ASSERT_EQ(BCI_NATIVE_FRAME_REMOTE, as_ra.bci);

    uintptr_t exact_off = Profiler::RemoteFramePacker::unpackPcOffset(exact.packed_remote_frame);
    uintptr_t as_ra_off = Profiler::RemoteFramePacker::unpackPcOffset(as_ra.packed_remote_frame);

    EXPECT_EQ((uintptr_t)kUnnamedOff, exact_off);
    EXPECT_EQ((uintptr_t)kUnnamedOff, as_ra_off)
        << "flagging the pc as a return address must not shift the emitted offset -- "
        << "the attribution address is a lookup detail and must not reach the wire";
}

}  // namespace
