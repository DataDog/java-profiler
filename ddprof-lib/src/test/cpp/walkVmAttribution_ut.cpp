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
#include <cstring>
#include <ucontext.h>
#include "arch.h"
#include "codeCache.h"
#include "dwarf.h"
#include "event.h"
#include "gtest_crash_handler.h"
#include "hotspot/hotspotSupport.h"
#include "libraries.h"
#include "os.h"
#include "profiler.h"
#include "stackFrame.h"
#include "stackWalker.inline.h"
#include "threadLocalData.inline.h"
#include "vmEntry.h"

// Friend of VM: walkVM asserts VM::isHotspot(), which only a JVM attach sets.
class VMTestAccessor {
  public:
    static bool getHotspot() { return VM::_hotspot; }
    static void setHotspot(bool v) { VM::_hotspot = v; }
};

// Friend of HotspotSupport: walkVM is private.
class HotspotSupportTestAccessor {
  public:
    static int walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth,
                      StackWalkFeatures features, EventType event_type,
                      int lock_index, bool* truncated) {
        return HotspotSupport::walkVM(ucontext, frames, max_depth, features,
                                      event_type, lock_index, truncated);
    }
};

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

// CodeCacheArray is append-only and the set is process-wide, so the caches are
// built and published exactly once however many fixtures ask for them.
void ensureSyntheticLibsRegistered() {
    static const bool registered = [] {
        static CodeCache symbol_lib("walkvm_attr_symbols", /*lib_index=*/-1,
                                    kSymbolLibBase, kSymbolLibBase + kLibSpan,
                                    /*image_base=*/kSymbolLibBase);
        symbol_lib.add(kSymbolLibBase + kFirstOff, kFuncLen, "walkvm_attr_first");
        symbol_lib.add(kSymbolLibBase + kBoundary, kFuncLen, "walkvm_attr_second");
        symbol_lib.sort();

        static CodeCache bare_lib("walkvm_attr_nosymbols", /*lib_index=*/-1,
                                  kBareLibBase, kBareLibBase + kLibSpan,
                                  /*image_base=*/kBareLibBase);

        bool ok = Libraries::instance()->addLibraryForTest(&symbol_lib);
        ok = Libraries::instance()->addLibraryForTest(&bare_lib) && ok;
        return ok;
    }();
    ASSERT_TRUE(registered);
}

class WalkVmAttributionTest : public ::testing::Test {
  protected:
    static void SetUpTestSuite() { ensureSyntheticLibsRegistered(); }

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

// ===========================================================================
// walkVM end to end, over its native path.
//
// VMStructs is never initialised here, and its code-heap bounds keep their
// inverted defaults (NO_MIN_ADDRESS above NO_MAX_ADDRESS), so
// CodeHeap::contains() is false for every address and walkVM takes the
// non-Java branch on every frame. That is the native resolution and DWARF
// unwind this change touches, and it needs no JVM: walkVM reads its VMThread
// through JVMThread::isInitialized(), which is false here, so the walk uses
// the same NULL handling it would on a thread the JVM has not attached.
// ===========================================================================

constexpr char WALKVM_TEST_NAME[] = "WalkVmNativePathTest";

// Plants one synthetic linked frame so the walk steps off the ucontext leaf
// onto a caller whose pc comes out of a return-address slot -- the only way
// the per-frame flag is observable from outside. Slot offsets are read back
// from the fallback frame descriptor rather than restated, so this follows
// whatever layout the walker itself uses on this architecture.
void plantCallerFrame(uintptr_t frame_fp, const void* return_address) {
    // Must be the descriptor the walker will actually get, which for a cache
    // carrying no DWARF table is CodeCache::_default_frame -- always
    // FrameDesc::default_frame, not fallback_default_frame(), which differs
    // from it on Apple aarch64 and would put these two stores in the wrong
    // slots.
    const FrameDesc& f = FrameDesc::default_frame;
    uintptr_t next_sp = frame_fp + (f.cfa >> 8);
    *(uintptr_t*)(next_sp + f.fp_off) = 0;  // unwalkable, so the walk stops here
    *(const void**)(next_sp + f.pc_off) = return_address;
}

class WalkVmNativePathTest : public ::testing::Test {
  protected:
    static constexpr int kMaxDepth = 8;

    void SetUp() override {
        installGtestCrashHandler<WALKVM_TEST_NAME>();
        ensureSyntheticLibsRegistered();
        ProfiledThread::initCurrentThread();
        ASSERT_NE(nullptr, ProfiledThread::current());

        _orig_hotspot = VMTestAccessor::getHotspot();
        VMTestAccessor::setHotspot(true);

        // walkVM dereferences the synthetic frame chain directly; keep a real
        // fault recoverable rather than taking the whole binary down.
        _orig_segv = OS::replaceSigsegvHandler(Profiler::segvHandler);
        _orig_bus = OS::replaceSigbusHandler(Profiler::busHandler);
    }

    void TearDown() override {
        OS::replaceSigsegvHandler(_orig_segv);
        OS::replaceSigbusHandler(_orig_bus);
        VMTestAccessor::setHotspot(_orig_hotspot);
        ProfiledThread::release();
        restoreDefaultSignalHandlers();
    }

    // Drives walkVM from a leaf pc with `caller_ra` planted in the caller's
    // return-address slot. EXECUTION_SAMPLE keeps `details` on so native
    // frames carry their resolved names.
    int walk(const void* leaf_pc, const void* caller_ra,
             ASGCT_CallFrame* frames, int max_depth) {
        static uintptr_t scratch[64];
        memset(scratch, 0, sizeof(scratch));
        uintptr_t frame_fp = (uintptr_t)&scratch[16];
        plantCallerFrame(frame_fp, caller_ra);

        // A zeroed ucontext_t is only usable as-is on Linux, where uc_mcontext
        // is embedded by value. On Darwin it is a pointer, so StackFrame's very
        // first register access dereferences NULL -- and with the profiler's
        // SIGSEGV handler installed that faults in a loop rather than crashing.
        // Give it real storage to point at.
        ucontext_t uc{};
#ifdef __APPLE__
        _STRUCT_MCONTEXT64 mc{};
        uc.uc_mcontext = &mc;
#endif
        StackFrame frame(&uc);
        frame.pc() = (uintptr_t)leaf_pc;
        frame.sp() = frame_fp;
        frame.fp() = frame_fp;
        StackWalkFeatures features{};
        return HotspotSupportTestAccessor::walkVM(&uc, frames, max_depth, features,
                                                  EXECUTION_SAMPLE, /*lock_index=*/0,
                                                  /*truncated=*/nullptr);
    }

    static const char* nameOf(const ASGCT_CallFrame& f) {
        return f.bci == BCI_NATIVE_FRAME ? (const char*)f.method_id : nullptr;
    }

    bool _orig_hotspot = false;
    SigAction _orig_segv = nullptr;
    SigAction _orig_bus = nullptr;
};

// The point of threading the flag: the leaf pc comes from the ucontext and is
// exact, the frame above it comes out of a return-address slot. Both land on
// the same zero-gap boundary address, and they must resolve to different
// functions precisely because of that difference.
TEST_F(WalkVmNativePathTest, CallerFrameFromReturnSlotAttributesToTheCaller) {
    const char* boundary = kSymbolLibBase + kBoundary;
    ASGCT_CallFrame frames[kMaxDepth + 1];
    memset(frames, 0, sizeof(frames));

    int depth = walk(/*leaf_pc=*/boundary, /*caller_ra=*/boundary, frames, kMaxDepth);

    ASSERT_GE(depth, 2) << "expected the leaf plus the planted caller frame";

    EXPECT_STREQ("walkvm_attr_second", nameOf(frames[0]))
        << "the leaf pc came from the ucontext, so it is exact and names the "
        << "function starting at that byte";
    EXPECT_STREQ("walkvm_attr_first", nameOf(frames[1]))
        << "the caller pc came out of a return-address slot, so the same "
        << "address must attribute to the function that made the call";
}

}  // namespace

// ===========================================================================
// The CFA-register hole in walkVM's DWARF step.
//
// walkDwarf ends its cfa_reg chain with `else break`. walkVM instead
// pre-screens `cfa_reg == DW_REG_INVALID || cfa_reg > DW_REG_PLT` and then
// runs the same three arms with no else, so a register that is none of
// SP/FP/PLT and is <= DW_REG_PLT matches nothing and falls straight through
// without breaking: sp keeps the value it had on entry to the step, and the
// walk goes on to read the "caller's" fp and pc out of the *current* frame's
// slots.
//
// Reachable from real DWARF: DwarfParser takes the register straight off the
// wire (`cfa_reg = getLeb()` under DW_CFA_def_cfa / _def_cfa_register /
// _def_cfa_sf) and addRecord() only rejects it above 0xFF, so nothing
// narrows it to the three the walkers implement. A function whose CFA is
// based on any other register -- x86_64 DWARF numbers RBX 3, R12 12, and so
// on -- lands in the hole.
//
// These two tests are the same planted frame walked by each walker. walkDwarf
// stops at the leaf; walkVM currently does not, which is the divergence that
// has to be reconciled before the shared advanceDwarfFrame() can be a pure
// move.
// ===========================================================================

namespace {

const char* const kCfaHoleLibBase = (const char*)0x5a5c00000000ULL;

// A CFA register the walkers do not implement and that the pre-screen lets
// past: not DW_REG_SP/FP/PLT, not DW_REG_INVALID, and <= DW_REG_PLT.
// x86_64 DWARF numbers this one RBX.
const u32 kUnhandledCfaReg = 3;

const int kHoleLeafOff    = 0x100;
const int kHolePhantomOff = 0x200;
const int kHoleFuncLen    = 0x10;

// One past the phantom's last byte, so its attribution address (pc - 1) lands
// inside the phantom rather than in the gap ahead of it -- the same zero-gap
// shape the attribution tests above use.
const int kHolePlantedPcOff = kHolePhantomOff + kHoleFuncLen;

// Slot offsets for the planted frame. Both must be even: DW_PC_OFFSET is 1,
// so an odd fp_off would send the step down the DW_OP_breg arithmetic branch
// instead of the memory-slot one under test.
const int kHoleFpOff = 0x10;
const int kHolePcOff = 0x18;

// Non-zero so the aarch64 `cfa_off == 0` defaultSenderSP() branch stays out of
// this; the value is otherwise unused, because no cfa_reg arm claims it.
const int kHoleCfaOff = 0x10;

// The frame-pointer case. The fp handed to the walk is deliberately misaligned
// by one byte; this offset is chosen so that fp + cfa_off lands back on a
// word boundary. Without a check on fp itself the derived sp looks perfectly
// well-formed, so the `!aligned(sp)` test further down does not catch it and
// the walk proceeds off a frame pointer it should have rejected.
const int kFpGuardLeafOff = 0x300;
const int kFpGuardCfaOff = (int)sizeof(uintptr_t) - 1;

void ensureCfaHoleLibRegistered() {
    static const bool registered = [] {
        static CodeCache hole_lib("walkvm_cfa_hole", /*lib_index=*/-1,
                                  kCfaHoleLibBase, kCfaHoleLibBase + kLibSpan,
                                  /*image_base=*/kCfaHoleLibBase);
        hole_lib.setTextBase(kCfaHoleLibBase);
        hole_lib.add(kCfaHoleLibBase + kHoleLeafOff, kHoleFuncLen, "walkvm_cfa_hole_leaf");
        hole_lib.add(kCfaHoleLibBase + kHolePhantomOff, kHoleFuncLen, "walkvm_cfa_hole_phantom");
        hole_lib.add(kCfaHoleLibBase + kFpGuardLeafOff, kHoleFuncLen, "walkvm_fp_guard_leaf");
        hole_lib.sort();

        // Row 0 covers the leaf and carries the unhandled CFA register.
        // Row 1 covers everything above it with DW_REG_INVALID, so whichever
        // walker does step past row 0 stops on the next iteration instead of
        // running on through unplanted memory.
        FrameDesc rows[4];
        rows[0] = {(u32)kHoleLeafOff,
                   (u32)(kHoleCfaOff << 8) | kUnhandledCfaReg,
                   kHoleFpOff, kHolePcOff, 0};
        rows[1] = {(u32)(kHoleLeafOff + 0x80),
                   (u32)DW_REG_INVALID, kHoleFpOff, kHolePcOff, 0};
        // Frame-pointer rule, with an offset that re-aligns a deliberately
        // misaligned fp -- see kFpGuardCfaOff.
        rows[2] = {(u32)kFpGuardLeafOff,
                   (u32)(kFpGuardCfaOff << 8) | (u32)DW_REG_FP,
                   kHoleFpOff, kHolePcOff, 0};
        rows[3] = {(u32)(kFpGuardLeafOff + 0x80),
                   (u32)DW_REG_INVALID, kHoleFpOff, kHolePcOff, 0};
        FrameDesc* table = (FrameDesc*)malloc(sizeof(rows));
        memcpy(table, rows, sizeof(rows));
        // Before publication: setDwarfTable() asserts the cache is unpublished.
        hole_lib.setDwarfTable(table, 4);

        return Libraries::instance()->addLibraryForTest(&hole_lib);
    }();
    ASSERT_TRUE(registered);
}

// Lays out the frame both walkers are pointed at. The pc slot is filled at
// sp + kHolePcOff, i.e. in the frame the walker is standing in -- if a walker
// reads it, it did so without ever advancing sp off this frame.
uintptr_t plantHoleFrame(uintptr_t* scratch, size_t words, const void* planted_pc) {
    memset(scratch, 0, words * sizeof(uintptr_t));
    uintptr_t sp = (uintptr_t)&scratch[8];
    *(uintptr_t*)(sp + kHoleFpOff) = 0;  // unwalkable, so nothing chains past it
    *(const void**)(sp + kHolePcOff) = planted_pc;
    return sp;
}

}  // namespace

// Baseline: walkDwarf's `else break` is what the shared helper should keep.
TEST_F(WalkVmNativePathTest, WalkDwarfStopsOnAnUnhandledCfaRegister) {
    ensureCfaHoleLibRegistered();

    static uintptr_t scratch[64];
    const void* planted_pc = kCfaHoleLibBase + kHolePlantedPcOff;
    uintptr_t sp = plantHoleFrame(scratch, 64, planted_pc);

    ucontext_t uc{};
#ifdef __APPLE__
    _STRUCT_MCONTEXT64 mc{};
    uc.uc_mcontext = &mc;
#endif
    StackFrame frame(&uc);
    frame.pc() = (uintptr_t)(kCfaHoleLibBase + kHoleLeafOff);
    frame.sp() = sp;
    frame.fp() = sp;

    const void* callchain[kMaxDepth + 1];
    memset(callchain, 0, sizeof(callchain));
    StackContext java_ctx{};
    bool truncated = false;
    int depth = StackWalker::walkDwarf(&uc, callchain, kMaxDepth, &java_ctx, &truncated);

    EXPECT_EQ(1, depth)
        << "walkDwarf records the leaf and then breaks: the row's CFA register is "
        << "none of SP/FP/PLT, so there is no rule to derive the caller's sp from";
}

// The divergence. Same row, same planted frame, and walkVM keeps going --
// reading a pc out of the slot at the *leaf's* own sp, because no arm fired
// and nothing moved sp off this frame.
TEST_F(WalkVmNativePathTest, WalkVmAlsoStopsOnAnUnhandledCfaRegister) {
    ensureCfaHoleLibRegistered();

    static uintptr_t scratch[64];
    const void* planted_pc = kCfaHoleLibBase + kHolePlantedPcOff;
    uintptr_t sp = plantHoleFrame(scratch, 64, planted_pc);

    ucontext_t uc{};
#ifdef __APPLE__
    _STRUCT_MCONTEXT64 mc{};
    uc.uc_mcontext = &mc;
#endif
    StackFrame frame(&uc);
    frame.pc() = (uintptr_t)(kCfaHoleLibBase + kHoleLeafOff);
    frame.sp() = sp;
    frame.fp() = sp;

    ASGCT_CallFrame frames[kMaxDepth + 1];
    memset(frames, 0, sizeof(frames));
    StackWalkFeatures features{};
    int depth = HotspotSupportTestAccessor::walkVM(&uc, frames, kMaxDepth, features,
                                                   EXECUTION_SAMPLE, /*lock_index=*/0,
                                                   /*truncated=*/nullptr);

    ASSERT_GE(depth, 1);
    EXPECT_STREQ("walkvm_cfa_hole_leaf", nameOf(frames[0]))
        << "the leaf pc came from the ucontext and names the function it sits in";

    EXPECT_EQ(1, depth)
        << "walkVM must break on an unhandled CFA register exactly as walkDwarf does. "
        << "It currently does not: the pre-screen passes cfa_reg=" << kUnhandledCfaReg
        << " through, no SP/FP/PLT arm claims it, and with no else the step carries on "
        << "with sp unchanged -- so frame " << (depth > 1 ? 1 : 0) << " below was read "
        << "out of the leaf's own slots rather than the caller's: "
        << (depth > 1 && nameOf(frames[1]) ? nameOf(frames[1]) : "<none>");
}

// The other half of the reconcile, in the other direction: walkVM sanity-checks
// the frame pointer before deriving a CFA from it and walkDwarf did not. A
// misaligned fp whose offset re-aligns the result slips past every check that
// looks at sp, so only a check on fp itself stops the walk here.
TEST_F(WalkVmNativePathTest, WalkDwarfRejectsAMisalignedFramePointer) {
    ensureCfaHoleLibRegistered();

    static uintptr_t scratch[64];
    const void* planted_pc = kCfaHoleLibBase + kHolePlantedPcOff;
    uintptr_t sp = plantHoleFrame(scratch, 64, planted_pc);
    // Where the walk would land if it derived sp from the misaligned fp, so
    // that letting it through produces a visible second frame rather than a
    // silent stop somewhere further on.
    uintptr_t derived_sp = sp + 1 + kFpGuardCfaOff;
    *(uintptr_t*)(derived_sp + kHoleFpOff) = 0;
    *(const void**)(derived_sp + kHolePcOff) = planted_pc;

    ucontext_t uc{};
#ifdef __APPLE__
    _STRUCT_MCONTEXT64 mc{};
    uc.uc_mcontext = &mc;
#endif
    StackFrame frame(&uc);
    frame.pc() = (uintptr_t)(kCfaHoleLibBase + kFpGuardLeafOff);
    frame.sp() = sp;
    frame.fp() = sp + 1;  // misaligned by one byte

    const void* callchain[kMaxDepth + 1];
    memset(callchain, 0, sizeof(callchain));
    StackContext java_ctx{};
    bool truncated = false;
    int depth = StackWalker::walkDwarf(&uc, callchain, kMaxDepth, &java_ctx, &truncated);

    EXPECT_EQ(1, depth)
        << "walkDwarf must reject a misaligned frame pointer before deriving a CFA "
        << "from it. fp + " << kFpGuardCfaOff << " is word-aligned, so the sp checks "
        << "below see nothing wrong and the walk records a frame read through a "
        << "frame pointer that cannot be one";
}
