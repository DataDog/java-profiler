/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// These tests gate the "attribution pc" fix in StackWalker::walkFP /
// StackWalker::walkDwarf: a pc loaded from a return-address slot, a link
// register, or __builtin_return_address() must be adjusted (pc - 1) before it
// is stored into callchain[] or fed to findLibraryByAddress/findFrameDesc/the
// DW_REG_PLT stub-offset test, while the "walking" pc used for DW_PC_OFFSET
// arithmetic, the no-progress guard and the JIT handoff stays raw.
//
// Build-flag dependency (see build-logic/conventions/src/main/kotlin/com/
// datadoghq/native/config/ConfigurationPresets.kt:74-78): the gtest configs
// compile with -fno-omit-frame-pointer, -momit-leaf-frame-pointer and
// -ffunction-sections. The first is why the C++ collector helpers below keep
// a frame pointer (required for x86_64's callerFP() = __builtin_frame_
// address(1) to be well-defined and for the frame-pointer walk to traverse
// them at all); the third is why every top-level asm() block here opens with
// an explicit ".text" -- compiler-emitted functions land in ".text.<name>",
// so without the directive two .globl labels in one block are not provably
// in the same section, and section-adjacency is the entire point of these
// fixtures. If either flag is later removed, these fixtures may start
// skipping (via their own adjacency/precondition checks) rather than failing
// silently.
//
// Guarded to __linux__ only, following stackWalker_ut.cpp:158 -- it is not
// established that Libraries::updateSymbols() parses the main executable's
// symbol table on macOS, and the asm fixtures below are GNU-as/ELF-CFI
// specific.

#include <gtest/gtest.h>
#include "stackWalker.h"
#include "gtest_crash_handler.h"

// ===========================================================================
// Portable characterization tests (coverage rows 2c/3/4/7). Unlike the
// fixtures below, these need no GNU-as/ELF-CFI asm and no reliance on
// Libraries::updateSymbols() parsing the test binary's own symbol table, so
// they are not gated to __linux__ and provide this file's only coverage of
// attributionPC()/CALLER_PC_IS_RETURN_ADDRESS/findFrameDesc/binarySearch on
// other platforms (e.g. this repo's macOS dev builds).
// ===========================================================================

#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "arch.h"
#include "codeCache.h"
#include "dwarf.h"
#include "stackWalker.inline.h"

// 2c. Documentation test, not a gate: on every arch where the constant is
// true, arch.h defines callerPC() as literally __builtin_return_address(0),
// so the EXPECT_EQ below compares an expression with itself; on aarch64
// (the only false arch) callerPC() is "adr %0, ." -- an address inside
// prof_ra_capture_pc_pair, which can never equal the caller's return
// address -- so the EXPECT_NE is equally self-fulfilling. It is kept because
// it fails loudly if arch.h's two definitions are ever edited apart. The
// behavioral gates for the seed flag are
// Test2c_CallerPcClassificationMatchesSymbol (below, Linux-only) and
// Test2b_SeedFlagConsumedByWalkFP/WalkDwarf.
extern "C" __attribute__((noinline)) void prof_ra_capture_pc_pair(const void** via_macro, const void** via_builtin) {
    *via_macro = callerPC();
    *via_builtin = __builtin_return_address(0);
}

TEST(ReturnAddressAttributionCharacterizationTest, CallerPcMacroMatchesItsArchDefinition) {
    const void* via_macro = nullptr;
    const void* via_builtin = nullptr;
    prof_ra_capture_pc_pair(&via_macro, &via_builtin);

    if (CALLER_PC_IS_RETURN_ADDRESS) {
        EXPECT_EQ(via_builtin, via_macro)
            << "CALLER_PC_IS_RETURN_ADDRESS=true claims callerPC() behaves like "
            << "__builtin_return_address(0), but they diverge on this build";
    } else {
        EXPECT_NE(via_builtin, via_macro)
            << "CALLER_PC_IS_RETURN_ADDRESS=false claims callerPC() is a leaf-seed "
            << "address distinct from __builtin_return_address(0), but they matched "
            << "on this build";
    }
}

TEST(ReturnAddressAttributionCharacterizationTest, AttributionPcArithmetic) {
    int dummy;
    const void* p = (const void*)&dummy;
    EXPECT_EQ(p, attributionPC(p, false));
    EXPECT_EQ((const void*)((const char*)p - 1), attributionPC(p, true));
}

// Supporting characterization (not gating): pins findFrameDesc's and
// binarySearch's row-selection semantics directly, independent of the live
// walker. These do NOT change with the fix -- they document why Test 3's
// live-walk assertion (Linux-only, below) is the right one.
TEST(ReturnAddressAttributionCharacterizationTest, FindFrameDescSelectsRowByRawAddress) {
    CodeCache cc("ra_char_test");
    const char* text_base = (const char*)0x100000;
    cc.setTextBase(text_base);

    const uint32_t CALL_SITE_OFF = 0x40;
    const uint32_t RETURN_OFF = 0x48;

    FrameDesc rows[2];
    rows[0] = { CALL_SITE_OFF, /*cfa*/ 0x10, /*fp_off*/ 0, /*pc_off*/ 0 };
    rows[1] = { RETURN_OFF, /*cfa*/ 0x20, /*fp_off*/ 0, /*pc_off*/ 0 };
    FrameDesc* table = (FrameDesc*)malloc(2 * sizeof(FrameDesc));
    memcpy(table, rows, sizeof(rows));
    cc.setDwarfTable(table, 2);

    FrameDesc at_return = cc.findFrameDesc((const void*)(text_base + RETURN_OFF));
    FrameDesc at_call_site = cc.findFrameDesc((const void*)(text_base + RETURN_OFF - 1));

    EXPECT_EQ(rows[1].cfa, at_return.cfa)
        << "a raw return address that exactly matches a row's loc selects that row";
    EXPECT_EQ(rows[0].cfa, at_call_site.cfa)
        << "pc - 1 selects the row covering the call site instead";
}

TEST(ReturnAddressAttributionCharacterizationTest, BinarySearchPicksNextSymbolAtZeroGapBoundary) {
    CodeCache cc("ra_char_test2");
    const void* f1 = (const void*)0x200000;
    const int len1 = 0x10;
    const int len2 = 0x10;
    cc.add(f1, len1, "first");
    cc.add((const void*)((const char*)f1 + len1), len2, "second");
    cc.sort();

    const char* name = nullptr;
    cc.binarySearch((const void*)((const char*)f1 + len1), &name);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("second", name)
        << "a return address landing exactly on the next symbol's first byte resolves to "
        << "that (wrong, for attribution purposes) symbol -- codeCache.cpp:288-299's fallback "
        << "does not rescue this zero-gap case, per the spec";

    cc.binarySearch((const void*)((const char*)f1 + len1 - 1), &name);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("first", name);
}

// Arithmetic-level fallback coverage for row 4 (kept regardless of whether
// the live fixture below manages to gate it in this build/toolchain): pins
// that the two branches genuinely differ only at raw & 15 == 11.
TEST(ReturnAddressAttributionCharacterizationTest, DwRegPltThresholdArithmetic) {
    uintptr_t raw = 0x1000 + 11;
    EXPECT_GE(raw & 15u, 11u);
    EXPECT_LT((raw - 1) & 15u, 11u);
}

// Mark-based walk termination still works after the attribution change
// (constraint: NativeFunc::read_mark keyed off binarySearch's result must
// keep seeing the correct mark at a return-address boundary).
TEST(ReturnAddressAttributionCharacterizationTest, MarkVisibleAtAdjustedBoundaryAddress) {
    CodeCache cc("ra_mark_test");
    const void* f1 = (const void*)0x300000;
    const int len1 = 0x10;
    const int len2 = 0x10;
    cc.add(f1, len1, "marked_first", /*update_bounds=*/false);
    cc.add((const void*)((const char*)f1 + len1), len2, "unmarked_second", /*update_bounds=*/false);
    cc.sort();

    CodeBlob* first = cc.findBlobByAddress(f1);
    ASSERT_NE(nullptr, first);
    NativeFunc::set_mark(first->_name, MARK_JAVA_PROFILER);

    const char* name_at_boundary = nullptr;
    cc.binarySearch((const void*)((const char*)f1 + len1), &name_at_boundary);
    ASSERT_NE(nullptr, name_at_boundary);
    EXPECT_STREQ("unmarked_second", name_at_boundary);
    EXPECT_FALSE(NativeFunc::is_marked(name_at_boundary))
        << "raw return address (unadjusted) sees no mark at the boundary";

    const char* name_adjusted = nullptr;
    cc.binarySearch((const void*)((const char*)f1 + len1 - 1), &name_adjusted);
    ASSERT_NE(nullptr, name_adjusted);
    EXPECT_STREQ("marked_first", name_adjusted);
    EXPECT_TRUE(NativeFunc::is_marked(name_adjusted))
        << "the attribution address (pc - 1) restores mark visibility at the boundary -- "
        << "MARK_JAVA_PROFILER / MARK_THREAD_ENTRY / MARK_INTERPRETER termination can only "
        << "improve, never regress, from this change";
    EXPECT_EQ(MARK_JAVA_PROFILER, NativeFunc::read_mark(name_adjusted));
}

// ===========================================================================
// Everything below is Linux/ELF-CFI specific: GNU-as asm() fixtures and
// reliance on Libraries::updateSymbols() parsing the test binary's own
// symbol table, neither established to work on macOS.
// ===========================================================================

#ifdef __linux__

#include <csetjmp>
#include <cstring>
#include <ucontext.h>
#include <algorithm>

#include "arch.h"
#include "codeCache.h"
#include "counters.h"
#include "dwarf.h"
#include "libraries.h"
#include "os.h"
#include "profiler.h"
#include "stackFrame.h"
#include "stackWalker.inline.h"
#include "threadLocalData.inline.h"

[[maybe_unused]] static long long* _return_addr_attr_ut_counters_init = Counters::getCounters();

// Each gating test below (Test1/3/4/5/6) has toolchain-dependent preconditions
// (adjacency, symbol visibility, CFI-row round-tripping) that GTEST_SKIP when
// unmet; gtest counts SKIPPED as a green run, so if every precondition failed
// on some CI toolchain this suite would still pass with zero effective
// regression coverage and nobody would notice. This counter is incremented
// once by each gating test that reaches its final assertions without hitting
// any of its own precondition skips; AtLeastOneGatingAssertionRan (declared
// after all of them, so it runs last under gtest's default registration
// order) fails the build if it is still zero.
static int g_gating_assertions_reached = 0;

// ---------------------------------------------------------------------------
// Frame index map (tester plan "Frame index map" section).
//
// callerPC()/callerFP()/callerSP() expand INSIDE the walker's own body
// (stackWalker.cpp:33 in walkFP, :118 in walkDwarf), not in the caller. On
// x86_64 callerPC() = __builtin_return_address(0) is the walker's own return
// address -- i.e. the byte after "call walkFP" inside the *collector* -- so
// the collector is chain[0] (a return address, adjusted) and the asm caller
// under test is chain[1]. On aarch64 callerPC() = "adr %0, ." is an address
// INSIDE the walker itself, one level deeper, so the collector is chain[1]
// and the asm caller under test is chain[2].
// ---------------------------------------------------------------------------
#if defined(__x86_64__)
static constexpr int kSeedIndex     = 0;   // the collector frame
static constexpr int kBoundaryIndex = 1;   // the asm caller under test
#elif defined(__aarch64__)
static constexpr int kSeedIndex     = 1;   // the collector frame
static constexpr int kBoundaryIndex = 2;   // the asm caller under test
#else
static constexpr int kSeedIndex     = -1;
static constexpr int kBoundaryIndex = -1;
#endif

static constexpr char RA_ATTR_TEST_NAME[] = "ReturnAddressAttributionTest";

// Looks a pc up through the same production path convertNativeTrace uses
// (profiler.cpp:451-455): findLibraryByAddress() then binarySearch() on the
// CodeCache it returns. Returns nullptr if either step fails.
static const char* symbolFor(const void* pc) {
    CodeCache* lib = Libraries::instance()->findLibraryByAddress(pc);
    if (lib == nullptr) {
        return nullptr;
    }
    const char* name = nullptr;
    lib->binarySearch(pc, &name);
    return name;
}

static bool symbolContains(const void* pc, const char* substr) {
    const char* name = symbolFor(pc);
    return name != nullptr && strstr(name, substr) != nullptr;
}

class ReturnAddressAttributionTest : public ::testing::Test {
protected:
    // Same margin rationale as StackWalkerCrashRecoveryTest
    // (stackWalker_ut.cpp): generous enough to cover walkFP/walkDwarf's
    // compiled bodies in any build config.
    static constexpr uintptr_t kRangeMargin = 256 * 1024;

    void SetUp() override {
        installGtestCrashHandler<RA_ATTR_TEST_NAME>();

        ProfiledThread::initCurrentThread();
        _pt = ProfiledThread::current();
        ASSERT_NE(nullptr, _pt);

        // Several tests below drive the walkers with fabricated ucontexts
        // and synthetic CFI, so a wrong CFA rule can send the walker chasing
        // a bogus pointer. Install the same recovery net
        // StackWalkerCrashRecoveryTest uses so a real fault is siglongjmp'd
        // back to instead of crashing the whole gtest binary.
        _orig_segv = OS::replaceSigsegvHandler(Profiler::segvHandler);
        _orig_bus = OS::replaceSigbusHandler(Profiler::busHandler);

        uintptr_t fp_pc = reinterpret_cast<uintptr_t>(&StackWalker::walkFP);
        uintptr_t dwarf_pc = reinterpret_cast<uintptr_t>(&StackWalker::walkDwarf);
        uintptr_t range_lo = std::min(fp_pc, dwarf_pc) - kRangeMargin;
        uintptr_t range_hi = std::max(fp_pc, dwarf_pc) + kRangeMargin;
        Profiler::setAddressRangeForTest(range_lo, range_hi);

        Libraries::instance()->updateSymbols(false);
    }

    void TearDown() override {
        Profiler::resetAddressRangeForTest();
        OS::replaceSigsegvHandler(_orig_segv);
        OS::replaceSigbusHandler(_orig_bus);
        ProfiledThread::release();
        restoreDefaultSignalHandlers();
    }

    // Builds a zero-initialized ucontext pointing at `pc`, with sp/fp inside
    // a caller-owned, zeroed, aligned scratch buffer. Zeroed scratch means
    // any register/stack-slot the walker reads out of it comes back as 0 --
    // which fails isValidFP/isValidSP or the dead-zone check and terminates
    // the walk safely, rather than chasing an arbitrary address.
    static ucontext_t makeFabricatedContext(const void* pc, uintptr_t* scratch, size_t scratch_words) {
        ucontext_t uc{};
        memset(scratch, 0, scratch_words * sizeof(uintptr_t));
        uintptr_t mid = reinterpret_cast<uintptr_t>(scratch + scratch_words / 2);
        StackFrame frame(&uc);
        frame.pc() = reinterpret_cast<uintptr_t>(pc);
        frame.sp() = mid;
        frame.fp() = mid;
        return uc;
    }

    ProfiledThread* _pt = nullptr;
    SigAction _orig_segv = nullptr;
    SigAction _orig_bus = nullptr;
};

// ===========================================================================
// Test 1 -- Boundary regression: a call that is the last instruction of its
// caller (stackWalker.cpp:81 / :169, coverage rows 1 and 2).
// ===========================================================================

#if defined(__x86_64__)

asm(
    ".text\n"
    ".globl prof_ra_caller\n"
    ".type prof_ra_caller,@function\n"
"prof_ra_caller:\n"
    "push %rbp\n"
    "mov  %rsp, %rbp\n"
    "call prof_ra_collect\n"
    ".size prof_ra_caller, .-prof_ra_caller\n"
    ".globl prof_ra_next\n"
    ".type prof_ra_next,@function\n"
"prof_ra_next:\n"
    "ret\n"
    ".size prof_ra_next, .-prof_ra_next\n"
);

#elif defined(__aarch64__)

asm(
    ".text\n"
    ".globl prof_ra_caller\n"
    ".type prof_ra_caller,%function\n"
"prof_ra_caller:\n"
    "stp x29, x30, [sp, #-16]!\n"
    "mov x29, sp\n"
    "bl prof_ra_collect\n"
    ".size prof_ra_caller, .-prof_ra_caller\n"
    ".globl prof_ra_next\n"
    ".type prof_ra_next,%function\n"
"prof_ra_next:\n"
    "ret\n"
    ".size prof_ra_next, .-prof_ra_next\n"
);

#endif

#if defined(__x86_64__) || defined(__aarch64__)

extern "C" void prof_ra_caller(void);
extern "C" void prof_ra_next(void);
extern "C" void prof_ra_collect(void);

namespace {
sigjmp_buf g_ra1_jmpbuf;
const void* g_ra1_captured_retaddr = nullptr;

const void* g_ra1_fp_chain[16];
int g_ra1_fp_depth = -1;
bool g_ra1_fp_truncated = false;

const void* g_ra1_dw_chain[16];
int g_ra1_dw_depth = -1;
bool g_ra1_dw_truncated = false;

// Ucontext-path variants of the same boundary scenario -- see the comment on
// their construction in prof_ra_collect() below. These close the coverage
// gap on stackWalker.cpp:42/132 (the `ucontext != NULL` branch that sets
// pc_is_ra = false for the leaf frame), which Test2a only exercised against
// a single fabricated, zeroed-out frame.
const void* g_ra1_fp_uc_chain[16];
int g_ra1_fp_uc_depth = -1;
bool g_ra1_fp_uc_truncated = false;

const void* g_ra1_dw_uc_chain[16];
int g_ra1_dw_uc_depth = -1;
bool g_ra1_dw_uc_truncated = false;
}  // namespace

// Called from the tail of prof_ra_caller as its FINAL instruction -- no
// epilogue, no ret follows the call. This reproduces the noreturn-callee
// codegen shape (abort/__cxa_throw/_Unwind_Resume/longjmp/...): the return
// address prof_ra_caller pushed is the first byte of the NEXT function,
// prof_ra_next, with no alignment padding in between.
extern "C" void prof_ra_collect(void) {
    g_ra1_captured_retaddr = __builtin_return_address(0);

    StackContext fp_ctx{};
    g_ra1_fp_depth = StackWalker::walkFP(nullptr, g_ra1_fp_chain, 16, &fp_ctx, &g_ra1_fp_truncated);

    StackContext dw_ctx{};
    g_ra1_dw_depth = StackWalker::walkDwarf(nullptr, g_ra1_dw_chain, 16, &dw_ctx, &g_ra1_dw_truncated);

    // Ucontext-path variants: describe exactly the same boundary return
    // address (into prof_ra_caller, landing on prof_ra_next's first byte --
    // g_ra1_captured_retaddr above) and the same live prof_ra_caller frame
    // that the nullptr-path walk above unwinds into one level further in.
    // Feeding that same pc/fp/sp through a ucontext instead drives the walk
    // through the `ucontext != NULL` branch (stackWalker.cpp:39-42/128-132),
    // where pc_is_ra is unconditionally false for the leaf -- against a
    // real, live multi-frame stack, not the single fabricated, zeroed frame
    // Test2a uses.
    //
    // callerPC()/callerFP()/callerSP() are NOT used here: those macros are
    // the walker's own "am I at the entry point" protocol (see the frame
    // index map comment above) and are deliberately asymmetric across
    // arches -- on aarch64 they describe prof_ra_collect's OWN frame
    // (callerPC() = "adr %0, ." is an address inside prof_ra_collect itself,
    // not a return address; callerFP()/callerSP() read the current, not the
    // caller's, registers), unlike x86_64 where they happen to describe the
    // caller's frame. Reusing them for this second, independent purpose
    // silently broke on aarch64. Instead walk the frame-pointer chain
    // explicitly via FRAME_PC_SLOT, which is arch-neutral and matches what
    // the production walker itself does.
    void** own_fp = (void**)__builtin_frame_address(0);
    void* caller_pc = own_fp[FRAME_PC_SLOT];
    void* caller_fp = own_fp[0];
    void* caller_sp = (void*)(own_fp + FRAME_PC_SLOT + 1);

    ucontext_t uc_fp{};
    StackFrame frame_fp(&uc_fp);
    frame_fp.pc() = (uintptr_t)caller_pc;
    frame_fp.fp() = (uintptr_t)caller_fp;
    frame_fp.sp() = (uintptr_t)caller_sp;
    StackContext fp_uc_ctx{};
    g_ra1_fp_uc_depth = StackWalker::walkFP(&uc_fp, g_ra1_fp_uc_chain, 16, &fp_uc_ctx, &g_ra1_fp_uc_truncated);

    ucontext_t uc_dw{};
    StackFrame frame_dw(&uc_dw);
    frame_dw.pc() = (uintptr_t)caller_pc;
    frame_dw.fp() = (uintptr_t)caller_fp;
    frame_dw.sp() = (uintptr_t)caller_sp;
    StackContext dw_uc_ctx{};
    g_ra1_dw_uc_depth = StackWalker::walkDwarf(&uc_dw, g_ra1_dw_uc_chain, 16, &dw_uc_ctx, &g_ra1_dw_uc_truncated);

    siglongjmp(g_ra1_jmpbuf, 1);
}

#endif  // __x86_64__ || __aarch64__

TEST_F(ReturnAddressAttributionTest, Test1_BoundaryRegression_WalkFPAndWalkDwarf) {
#if !defined(__x86_64__) && !defined(__aarch64__)
    GTEST_SKIP() << "boundary fixture only implemented for x86_64/aarch64";
#else
    g_ra1_fp_depth = -1;
    g_ra1_dw_depth = -1;
    g_ra1_captured_retaddr = nullptr;

    if (sigsetjmp(g_ra1_jmpbuf, 1) == 0) {
        prof_ra_caller();
        FAIL() << "prof_ra_caller must not return normally";
    }

    // Precondition 1: adjacency actually happened.
    if (g_ra1_captured_retaddr != (const void*)&prof_ra_next) {
        GTEST_SKIP() << "assembler/linker inserted padding between prof_ra_caller "
                        "and prof_ra_next; this build cannot exhibit the bug";
    }

    // Precondition 2: the symbols are visible to the profiler's tables.
    CodeCache* lib = Libraries::instance()->findLibraryByAddress((const void*)&prof_ra_caller);
    if (lib == nullptr) {
        GTEST_SKIP() << "test binary symbols not visible to Libraries::findLibraryByAddress";
    }
    const char* caller_name = nullptr;
    lib->binarySearch((const void*)&prof_ra_caller, &caller_name);
    if (caller_name == nullptr || strcmp(caller_name, "prof_ra_caller") != 0) {
        GTEST_SKIP() << "binarySearch(&prof_ra_caller) did not resolve to \"prof_ra_caller\" "
                      << "(got " << (caller_name ? caller_name : "<null>") << ")";
    }

    // 3. Demonstrate the mechanism: raw return address resolves to the wrong
    // (next) symbol; pc - 1 resolves to the right (calling) one. This holds
    // both before and after the fix -- it is why the next assertion is
    // correct, not itself the fix.
    {
        const char* raw_name = symbolFor(g_ra1_captured_retaddr);
        const char* adjusted_name = symbolFor((const void*)((const char*)g_ra1_captured_retaddr - 1));
        ASSERT_NE(nullptr, raw_name);
        ASSERT_NE(nullptr, adjusted_name);
        EXPECT_STREQ("prof_ra_next", raw_name);
        EXPECT_STREQ("prof_ra_caller", adjusted_name);
    }

    for (int which = 0; which < 2; which++) {
        const char* label = which == 0 ? "walkFP" : "walkDwarf";
        const void** chain = which == 0 ? g_ra1_fp_chain : g_ra1_dw_chain;
        int depth = which == 0 ? g_ra1_fp_depth : g_ra1_dw_depth;

        // 4. Setup gate.
        ASSERT_GT(depth, kBoundaryIndex) << label << ": walk produced no frames past the boundary "
                                          << "-- check ProfiledThread setup";

        // 5. Index preconditions.
        if (!symbolContains(chain[kSeedIndex], "prof_ra_collect")) {
            GTEST_SKIP() << label << ": chain[" << kSeedIndex << "] is not prof_ra_collect "
                          << "(got " << (symbolFor(chain[kSeedIndex]) ? symbolFor(chain[kSeedIndex]) : "<null>")
                          << ") -- frame index map assumption does not hold, re-derive it";
        }
#if defined(__aarch64__)
        if (!symbolContains(chain[0], which == 0 ? "walkFP" : "walkDwarf")) {
            GTEST_SKIP() << label << ": chain[0] is not the walker itself on aarch64 -- "
                          << "frame index map assumption does not hold";
        }
#endif

        // 6. The acceptance assertion, at the named index.
        EXPECT_TRUE(symbolContains(chain[kBoundaryIndex], "prof_ra_caller"))
            << label << ": chain[" << kBoundaryIndex << "] should symbolize to prof_ra_caller, got "
            << (symbolFor(chain[kBoundaryIndex]) ? symbolFor(chain[kBoundaryIndex]) : "<null>");
        EXPECT_FALSE(symbolContains(chain[kBoundaryIndex], "prof_ra_next"))
            << label << ": chain[" << kBoundaryIndex << "] must not symbolize to prof_ra_next "
            << "-- the raw return address was stored instead of the attribution address";

        // 7. The walk continued past the boundary frame.
        EXPECT_GE(depth, kBoundaryIndex + 2)
            << label << ": walk did not continue past the boundary frame";
    }

    // 8. Ucontext-path counterpart (stackWalker.cpp:42/132): the exact same
    // boundary return address and live prof_ra_caller frame as above, but
    // walked via a ucontext instead of nullptr, so the leaf's pc_is_ra is
    // false rather than CALLER_PC_IS_RETURN_ADDRESS. It must come back raw
    // (mis-symbolizing as prof_ra_next, mirroring the pre-adjustment
    // demonstration in step 3) -- proving the leaf is genuinely left
    // unadjusted against a live stack, not just in the single fabricated
    // frame Test2a covers -- and the walk must still continue past it using
    // the fp/sp taken from that same ucontext.
    for (int which = 0; which < 2; which++) {
        const char* label = which == 0 ? "walkFP(ucontext)" : "walkDwarf(ucontext)";
        const void** chain = which == 0 ? g_ra1_fp_uc_chain : g_ra1_dw_uc_chain;
        int depth = which == 0 ? g_ra1_fp_uc_depth : g_ra1_dw_uc_depth;

        ASSERT_GE(depth, 1) << label << ": ucontext-path walk produced no frames";
        EXPECT_EQ(g_ra1_captured_retaddr, chain[0])
            << label << ": a ucontext-supplied leaf pc must be stored byte-exact "
            << "(pc_is_ra = false), not adjusted by -1";
        EXPECT_TRUE(symbolContains(chain[0], "prof_ra_next"))
            << label << ": chain[0] should still symbolize to prof_ra_next -- if it "
            << "resolved to prof_ra_caller instead, the leaf was wrongly adjusted";
        EXPECT_FALSE(symbolContains(chain[0], "prof_ra_caller"))
            << label << ": chain[0] must not symbolize to prof_ra_caller";
        EXPECT_GE(depth, 2)
            << label << ": walk did not continue past the ucontext leaf frame -- "
            << "fp/sp taken from the ucontext were not usable to keep walking";
    }

    ++g_gating_assertions_reached;
#endif  // __x86_64__ || __aarch64__
}

// ===========================================================================
// Test 2 -- Seed classification (coverage row 5).
// ===========================================================================

// 2a. A ucontext-supplied leaf keeps its exact interrupted address.
TEST_F(ReturnAddressAttributionTest, Test2a_UcontextLeafKeepsExactAddress) {
    static uintptr_t scratch[64];
    // A real, non-trivial function so "+4" lands mid-body rather than on the
    // entry/exit byte; contents/correctness of disassembly at that offset
    // are irrelevant -- only the exact-address assertion below is checked.
    const void* fabricated_pc = (const void*)((const char*)&symbolFor + 4);

    ucontext_t uc = makeFabricatedContext(fabricated_pc, scratch, 64);

    StackContext fp_ctx{};
    bool fp_truncated = false;
    const void* fp_chain[8];
    int fp_depth = StackWalker::walkFP(&uc, fp_chain, 8, &fp_ctx, &fp_truncated);
    ASSERT_GE(fp_depth, 1);
    EXPECT_EQ(fabricated_pc, fp_chain[0])
        << "walkFP must store a ucontext-supplied leaf byte-exact, not adjusted";

    ucontext_t uc2 = makeFabricatedContext(fabricated_pc, scratch, 64);
    StackContext dw_ctx{};
    bool dw_truncated = false;
    const void* dw_chain[8];
    int dw_depth = StackWalker::walkDwarf(&uc2, dw_chain, 8, &dw_ctx, &dw_truncated);
    ASSERT_GE(dw_depth, 1);
    EXPECT_EQ(fabricated_pc, dw_chain[0])
        << "walkDwarf must store a ucontext-supplied leaf byte-exact, not adjusted";
}

// 2b. The CALLER_PC_IS_RETURN_ADDRESS seed is actually consumed by the
// walkers -- asserted on the walk itself, not on the constant's value.
#if defined(__x86_64__)

asm(
    ".text\n"
    ".globl prof_ra_seed_shim\n"
    ".type prof_ra_seed_shim,@function\n"
"prof_ra_seed_shim:\n"
    "push %rbp\n"
    "mov  %rsp, %rbp\n"
    "xor  %edi, %edi\n"
    "lea  prof_ra_seed_chain(%rip), %rsi\n"
    "mov  $16, %edx\n"
    "mov  prof_ra_seed_ctx(%rip), %rcx\n"
    "xor  %r8d, %r8d\n"
    "call *prof_ra_seed_fn(%rip)\n"
    ".globl prof_ra_seed_retaddr\n"
"prof_ra_seed_retaddr:\n"
    "leave\n"
    "ret\n"
    ".size prof_ra_seed_shim, .-prof_ra_seed_shim\n"
);

#elif defined(__aarch64__)

asm(
    ".text\n"
    ".globl prof_ra_seed_shim\n"
    ".type prof_ra_seed_shim,%function\n"
"prof_ra_seed_shim:\n"
    "stp  x29, x30, [sp, #-16]!\n"
    "mov  x29, sp\n"
    "mov  x0, #0\n"
    "adrp x1, prof_ra_seed_chain\n"
    "add  x1, x1, :lo12:prof_ra_seed_chain\n"
    "mov  x2, #16\n"
    "adrp x3, prof_ra_seed_ctx\n"
    "add  x3, x3, :lo12:prof_ra_seed_ctx\n"
    "ldr  x3, [x3]\n"
    "mov  x4, #0\n"
    "adrp x9, prof_ra_seed_fn\n"
    "add  x9, x9, :lo12:prof_ra_seed_fn\n"
    "ldr  x9, [x9]\n"
    "blr  x9\n"
    ".globl prof_ra_seed_retaddr\n"
"prof_ra_seed_retaddr:\n"
    "ldp  x29, x30, [sp], #16\n"
    "ret\n"
    ".size prof_ra_seed_shim, .-prof_ra_seed_shim\n"
);

#endif

#if defined(__x86_64__) || defined(__aarch64__)

extern "C" {
using RaWalkFn = int (*)(void*, const void**, int, StackContext*, bool*);
RaWalkFn prof_ra_seed_fn = nullptr;
const void* prof_ra_seed_chain[16];
StackContext* prof_ra_seed_ctx = nullptr;
int prof_ra_seed_shim(void);
void prof_ra_seed_retaddr(void);
}

#endif

TEST_F(ReturnAddressAttributionTest, Test2b_SeedFlagConsumedByWalkFP) {
#if !defined(__x86_64__) && !defined(__aarch64__)
    GTEST_SKIP() << "seed fixture only implemented for x86_64/aarch64";
#else
    StackContext ctx{};
    prof_ra_seed_ctx = &ctx;
    prof_ra_seed_fn = &StackWalker::walkFP;
    memset(prof_ra_seed_chain, 0, sizeof(prof_ra_seed_chain));

    int depth = prof_ra_seed_shim();
    ASSERT_GT(depth, kSeedIndex);

    const void* expected_adjusted = (const void*)((const char*)&prof_ra_seed_retaddr - 1);

#if defined(__x86_64__)
    EXPECT_EQ(expected_adjusted, prof_ra_seed_chain[0])
        << "x86_64 walkFP seed: chain[0] must be the return address minus one "
        << "(reverting the seed leaves it equal to the raw return address)";
#elif defined(__aarch64__)
    // The walker's own "adr %0, ." seed is a real instruction address:
    // 4-byte aligned, unlike an erroneously-adjusted (adr - 1) value.
    EXPECT_EQ(0u, (uintptr_t)prof_ra_seed_chain[0] & 3u)
        << "aarch64 walkFP seed (chain[0]) must stay 4-byte aligned -- it is a real "
        << "instruction address (adr), not a return address";
    EXPECT_TRUE(symbolContains(prof_ra_seed_chain[0], "walkFP"));
    EXPECT_NE(expected_adjusted, prof_ra_seed_chain[0]);
    ASSERT_GT(depth, kSeedIndex + 1);
    EXPECT_EQ(expected_adjusted, prof_ra_seed_chain[1])
        << "aarch64 walkFP seed: the shim frame (chain[1]) is a genuine return "
        << "address and must be adjusted";
#endif
#endif
}

TEST_F(ReturnAddressAttributionTest, Test2b_SeedFlagConsumedByWalkDwarf) {
#if !defined(__x86_64__) && !defined(__aarch64__)
    GTEST_SKIP() << "seed fixture only implemented for x86_64/aarch64";
#else
    StackContext ctx{};
    prof_ra_seed_ctx = &ctx;
    prof_ra_seed_fn = &StackWalker::walkDwarf;
    memset(prof_ra_seed_chain, 0, sizeof(prof_ra_seed_chain));

    int depth = prof_ra_seed_shim();
    ASSERT_GT(depth, kSeedIndex);

    const void* expected_adjusted = (const void*)((const char*)&prof_ra_seed_retaddr - 1);

#if defined(__x86_64__)
    EXPECT_EQ(expected_adjusted, prof_ra_seed_chain[0])
        << "x86_64 walkDwarf seed: chain[0] must be the return address minus one";
#elif defined(__aarch64__)
    EXPECT_EQ(0u, (uintptr_t)prof_ra_seed_chain[0] & 3u)
        << "aarch64 walkDwarf seed (chain[0]) must stay 4-byte aligned";
    EXPECT_TRUE(symbolContains(prof_ra_seed_chain[0], "walkDwarf"));
    EXPECT_NE(expected_adjusted, prof_ra_seed_chain[0]);
    ASSERT_GT(depth, kSeedIndex + 1);
    EXPECT_EQ(expected_adjusted, prof_ra_seed_chain[1])
        << "aarch64 walkDwarf seed: the shim frame (chain[1]) must be adjusted";
#endif
#endif
}

// 2c. Supporting characterization (CallerPcIsReturnAddressConstant,
// AttributionPcArithmetic) moved above the __linux__ gate -- portable,
// not Linux/ELF-specific. See ReturnAddressAttributionCharacterizationTest.

// Gates what the portable CallerPcMacroMatchesItsArchDefinition cannot: that
// CALLER_PC_IS_RETURN_ADDRESS classifies callerPC()'s value correctly, using
// a property independent of arch.h's macro text. A genuine return address
// belongs to the *caller* of prof_ra_capture_pc_pair, so it resolves to a
// different symbol; aarch64's "adr %0, ." leaf seed resolves to
// prof_ra_capture_pc_pair itself.
TEST_F(ReturnAddressAttributionTest, Test2c_CallerPcClassificationMatchesSymbol) {
    const void* via_macro = nullptr;
    const void* via_builtin = nullptr;
    prof_ra_capture_pc_pair(&via_macro, &via_builtin);

    const char* macro_sym = symbolFor(via_macro);
    if (macro_sym == nullptr) {
        GTEST_SKIP() << "callerPC() value not visible to findLibraryByAddress/binarySearch "
                      << "in this build";
    }
    const char* capture_sym = symbolFor((const void*)&prof_ra_capture_pc_pair);
    if (capture_sym == nullptr || strstr(capture_sym, "prof_ra_capture_pc_pair") == nullptr) {
        GTEST_SKIP() << "prof_ra_capture_pc_pair does not resolve to its own symbol in this "
                      << "build, so the comparison below cannot distinguish the two cases";
    }

    bool inside_capture = strstr(macro_sym, "prof_ra_capture_pc_pair") != nullptr;
    if (CALLER_PC_IS_RETURN_ADDRESS) {
        EXPECT_FALSE(inside_capture)
            << "CALLER_PC_IS_RETURN_ADDRESS=true claims callerPC() is the caller's return "
            << "address, but it resolved inside prof_ra_capture_pc_pair itself (" << macro_sym << ")";
    } else {
        EXPECT_TRUE(inside_capture)
            << "CALLER_PC_IS_RETURN_ADDRESS=false claims callerPC() is a leaf seed inside the "
            << "capturing function, but it resolved to " << macro_sym;
    }

    ++g_gating_assertions_reached;
}

// ===========================================================================
// Test 3 -- Unwind-row selection at a return address, through the walker
// (coverage row 3, highest-severity primary item).
// ===========================================================================

#if defined(__x86_64__)

asm(
    ".text\n"
    ".globl prof_ra_cfi_caller\n"
    ".type prof_ra_cfi_caller,@function\n"
"prof_ra_cfi_caller:\n"
    ".cfi_startproc\n"
    "push %rbp\n"
    ".cfi_def_cfa_offset 16\n"
    ".cfi_offset %rbp, -16\n"
    "mov  %rsp, %rbp\n"
    ".cfi_def_cfa_register %rbp\n"
    "call prof_ra_cfi_collect\n"
    ".cfi_endproc\n"
    ".size prof_ra_cfi_caller, .-prof_ra_cfi_caller\n"
    ".globl prof_ra_cfi_next\n"
    ".type prof_ra_cfi_next,@function\n"
"prof_ra_cfi_next:\n"
    ".cfi_startproc\n"
    ".cfi_def_cfa_offset 8\n"
    "nop\n"
    ".cfi_endproc\n"
    ".size prof_ra_cfi_next, .-prof_ra_cfi_next\n"
);

#elif defined(__aarch64__)

asm(
    ".text\n"
    ".globl prof_ra_cfi_caller\n"
    ".type prof_ra_cfi_caller,%function\n"
"prof_ra_cfi_caller:\n"
    ".cfi_startproc\n"
    "stp  x29, x30, [sp, #-16]!\n"
    ".cfi_def_cfa_offset 16\n"
    ".cfi_offset x30, -8\n"
    ".cfi_offset x29, -16\n"
    "mov  x29, sp\n"
    "bl   prof_ra_cfi_collect\n"
    ".cfi_endproc\n"
    ".size prof_ra_cfi_caller, .-prof_ra_cfi_caller\n"
    ".globl prof_ra_cfi_next\n"
    ".type prof_ra_cfi_next,%function\n"
"prof_ra_cfi_next:\n"
    ".cfi_startproc\n"
    ".cfi_def_cfa_offset 0\n"
    "nop\n"
    ".cfi_endproc\n"
    ".size prof_ra_cfi_next, .-prof_ra_cfi_next\n"
);

#endif

#if defined(__x86_64__) || defined(__aarch64__)

extern "C" void prof_ra_cfi_caller(void);
extern "C" void prof_ra_cfi_next(void);
extern "C" void prof_ra_cfi_collect(void);

namespace {
sigjmp_buf g_ra3_jmpbuf;
const void* g_ra3_dw_chain[16];
int g_ra3_dw_depth = -1;
}  // namespace

extern "C" void prof_ra_cfi_collect(void) {
    StackContext dw_ctx{};
    bool truncated = false;
    g_ra3_dw_depth = StackWalker::walkDwarf(nullptr, g_ra3_dw_chain, 16, &dw_ctx, &truncated);
    siglongjmp(g_ra3_jmpbuf, 1);
}

// Named trampoline so Test 3's "caller of the boundary frame" is a specific,
// symbolizable function rather than the test body itself.
extern "C" __attribute__((noinline)) void prof_ra_cfi_trampoline(void) {
    // volatile to defeat tail-call/inlining folding this frame away.
    volatile int guard = 1;
    (void)guard;
    prof_ra_cfi_caller();
}

#endif  // __x86_64__ || __aarch64__

TEST_F(ReturnAddressAttributionTest, Test3_UnwindRowSelectedAtReturnAddress) {
#if !defined(__x86_64__) && !defined(__aarch64__)
    GTEST_SKIP() << "CFI fixture only implemented for x86_64/aarch64";
#else
    g_ra3_dw_depth = -1;

    if (sigsetjmp(g_ra3_jmpbuf, 1) == 0) {
        prof_ra_cfi_trampoline();
        FAIL() << "prof_ra_cfi_caller must not return normally";
    }

    CodeCache* lib = Libraries::instance()->findLibraryByAddress((const void*)&prof_ra_cfi_caller);
    if (lib == nullptr) {
        GTEST_SKIP() << "prof_ra_cfi_caller not visible to findLibraryByAddress";
    }

    // Locate the return address into prof_ra_cfi_caller the same way the
    // walk did, to build the two lookup addresses for the precondition.
    const void* raw_return_address = nullptr;
    {
        const char* n1 = nullptr;
        // The call is the caller's final instruction, so the return address
        // is prof_ra_cfi_next's first byte -- same adjacency contract as
        // Test 1, verified indirectly by the symbol check below.
        raw_return_address = (const void*)&prof_ra_cfi_next;
        lib->binarySearch(raw_return_address, &n1);
        if (n1 == nullptr || strcmp(n1, "prof_ra_cfi_next") != 0) {
            GTEST_SKIP() << "adjacency between prof_ra_cfi_caller and prof_ra_cfi_next "
                          << "did not hold in this build";
        }
    }

    FrameDesc row_at_return = lib->findFrameDesc(raw_return_address);
    FrameDesc row_at_call_site =
        lib->findFrameDesc((const void*)((const char*)raw_return_address - 1));

    if (row_at_return.cfa == row_at_call_site.cfa) {
        GTEST_SKIP() << "findFrameDesc(returnAddress) and findFrameDesc(returnAddress - 1) "
                      << "returned the same cfa (" << row_at_return.cfa << ") in this build's "
                      << ".eh_frame -- the fixture cannot discriminate the two rows";
    }

    ASSERT_GT(g_ra3_dw_depth, kBoundaryIndex)
        << "walk produced no frames past the boundary -- check ProfiledThread setup";

    if (!symbolContains(g_ra3_dw_chain[kSeedIndex], "prof_ra_cfi_collect")) {
        GTEST_SKIP() << "chain[" << kSeedIndex << "] is not prof_ra_cfi_collect -- "
                      << "frame index map assumption does not hold";
    }

    // Gating assertion: the walk used the call-site row (cfa correct), so it
    // recovers the trampoline as the boundary frame's caller. Pre-fix the
    // raw return address selects prof_ra_cfi_next's row, producing an 8-byte
    // wrong sp and either the wrong symbol at kBoundaryIndex+1 or a
    // truncated walk (both are asserted for, per the tester plan).
    EXPECT_TRUE(symbolContains(g_ra3_dw_chain[kBoundaryIndex], "prof_ra_cfi_caller"))
        << "boundary frame should symbolize to prof_ra_cfi_caller";
    ASSERT_GE(g_ra3_dw_depth, kBoundaryIndex + 2)
        << "walk truncated at the boundary frame -- one of the two pre-fix failure modes "
        << "(wrong cfa read a bogus next-pc that failed validation)";
    EXPECT_TRUE(symbolContains(g_ra3_dw_chain[kBoundaryIndex + 1], "prof_ra_cfi_trampoline"))
        << "chain[" << (kBoundaryIndex + 1) << "] should symbolize to prof_ra_cfi_trampoline "
        << "(the actual caller of prof_ra_cfi_caller); got "
        << (symbolFor(g_ra3_dw_chain[kBoundaryIndex + 1])
                ? symbolFor(g_ra3_dw_chain[kBoundaryIndex + 1])
                : "<null>")
        << " -- this is the other pre-fix failure mode (wrong row -> wrong symbol)";

    ++g_gating_assertions_reached;
#endif  // __x86_64__ || __aarch64__
}

// Supporting characterization (FindFrameDescSelectsRowByRawAddress,
// BinarySearchPicksNextSymbolAtZeroGapBoundary) moved above the __linux__
// gate -- portable, not Linux/ELF-specific. See
// ReturnAddressAttributionCharacterizationTest. They document why Test 3's
// live-walk assertion below is the right one.

// ===========================================================================
// Test 4 -- The DW_REG_PLT arm uses the same address as the FDE lookup
// (coverage row 4).
// ===========================================================================

#if defined(__x86_64__)

// .cfi_escape 0x0f, 0x0b, <11 filler bytes> synthesizes a DW_REG_PLT row
// (dwarf.cpp: DW_CFA_def_cfa_expression, ULEB length 11). The trailing nops
// pad the return address so that raw & 15 == 11, the only value at which
// the ">= 11 ? *2 : *1" arm differs from the adjusted (raw - 1) address.
asm(
    ".text\n"
    ".globl prof_ra_plt_caller\n"
    ".type prof_ra_plt_caller,@function\n"
"prof_ra_plt_caller:\n"
    ".cfi_startproc\n"
    "push %rbp\n"
    ".cfi_def_cfa_offset 16\n"
    ".cfi_offset %rbp, -16\n"
    "mov  %rsp, %rbp\n"
    ".cfi_escape 0x0f, 0x0b, 0,0,0,0,0,0,0,0,0,0,0\n"
    "nop\nnop\nnop\nnop\nnop\nnop\n"
    "call prof_ra_plt_collect\n"
    ".cfi_endproc\n"
    ".size prof_ra_plt_caller, .-prof_ra_plt_caller\n"
    ".globl prof_ra_plt_next\n"
    ".type prof_ra_plt_next,@function\n"
"prof_ra_plt_next:\n"
    "ret\n"
    ".size prof_ra_plt_next, .-prof_ra_plt_next\n"
);

#elif defined(__aarch64__)

asm(
    ".text\n"
    ".globl prof_ra_plt_caller\n"
    ".type prof_ra_plt_caller,%function\n"
"prof_ra_plt_caller:\n"
    ".cfi_startproc\n"
    "stp  x29, x30, [sp, #-16]!\n"
    ".cfi_def_cfa_offset 16\n"
    ".cfi_offset x30, -8\n"
    ".cfi_offset x29, -16\n"
    "mov  x29, sp\n"
    ".cfi_escape 0x0f, 0x0b, 0,0,0,0,0,0,0,0,0,0,0\n"
    "nop\nnop\nnop\n"
    "bl   prof_ra_plt_collect\n"
    ".cfi_endproc\n"
    ".size prof_ra_plt_caller, .-prof_ra_plt_caller\n"
    ".globl prof_ra_plt_next\n"
    ".type prof_ra_plt_next,%function\n"
"prof_ra_plt_next:\n"
    "ret\n"
    ".size prof_ra_plt_next, .-prof_ra_plt_next\n"
);

#endif

#if defined(__x86_64__) || defined(__aarch64__)

extern "C" void prof_ra_plt_caller(void);
extern "C" void prof_ra_plt_next(void);
extern "C" void prof_ra_plt_collect(void);

namespace {
sigjmp_buf g_ra4_jmpbuf;
const void* g_ra4_captured_retaddr = nullptr;
const void* g_ra4_dw_chain[16];
int g_ra4_dw_depth = -1;
}  // namespace

extern "C" void prof_ra_plt_collect(void) {
    g_ra4_captured_retaddr = __builtin_return_address(0);
    StackContext dw_ctx{};
    bool truncated = false;
    g_ra4_dw_depth = StackWalker::walkDwarf(nullptr, g_ra4_dw_chain, 16, &dw_ctx, &truncated);
    siglongjmp(g_ra4_jmpbuf, 1);
}

extern "C" __attribute__((noinline)) void prof_ra_plt_trampoline(void) {
    volatile int guard = 1;
    (void)guard;
    prof_ra_plt_caller();
}

#endif  // __x86_64__ || __aarch64__

TEST_F(ReturnAddressAttributionTest, Test4_DwRegPltArmUsesAttributionAddress) {
#if !defined(__x86_64__) && !defined(__aarch64__)
    GTEST_SKIP() << "DW_REG_PLT fixture only implemented for x86_64/aarch64";
#else
    g_ra4_dw_depth = -1;
    g_ra4_captured_retaddr = nullptr;

    if (sigsetjmp(g_ra4_jmpbuf, 1) == 0) {
        prof_ra_plt_trampoline();
        FAIL() << "prof_ra_plt_caller must not return normally";
    }

    // Precondition: the return address actually landed at raw & 15 == 11 --
    // the only offset at which the ">= 11" branch and the adjusted-address
    // branch disagree. If the assembler/linker moved it, the two branches
    // are not distinguishable at this address and the fixture cannot gate
    // the item; degrade per the tester plan rather than pass silently.
    if (((uintptr_t)g_ra4_captured_retaddr & 15u) != 11u) {
        GTEST_SKIP() << "return address alignment (raw & 15 == "
                      << ((uintptr_t)g_ra4_captured_retaddr & 15u) << ") is not 11 in this build; "
                      << "stackWalker.cpp's DW_REG_PLT arm ships with arithmetic-level coverage "
                      << "only for this build (see Test4_DwRegPltThresholdArithmetic) and was "
                      << "verified by inspection -- record this gap in the PR description";
    }

    CodeCache* lib = Libraries::instance()->findLibraryByAddress((const void*)&prof_ra_plt_caller);
    if (lib == nullptr) {
        GTEST_SKIP() << "prof_ra_plt_caller not visible to findLibraryByAddress";
    }
    FrameDesc row = lib->findFrameDesc((const void*)&prof_ra_plt_caller);
    // cfa_reg and cfa_off are packed into FrameDesc::cfa as (cfa_off << 8 |
    // cfa_reg) (dwarf.cpp:574-575) -- the low byte is the register.
    if ((row.cfa & 0xffu) != (u32)DW_REG_PLT) {
        GTEST_SKIP() << "the .cfi_escape DW_CFA_def_cfa_expression row did not round-trip as "
                      << "DW_REG_PLT through ElfParser in this build (observed cfa reg="
                      << (row.cfa & 0xffu) << "); degrading per the tester plan";
    }

    ASSERT_GT(g_ra4_dw_depth, kBoundaryIndex)
        << "walk produced no frames past the boundary -- check ProfiledThread setup";

    // Gating: pre-fix the raw pc (raw & 15 == 11) takes the "*2" branch and
    // mis-reads the next pc; post-fix the adjusted pc ((raw-1) & 15 == 10)
    // takes the plain branch and the walk resolves the real caller.
    EXPECT_TRUE(symbolContains(g_ra4_dw_chain[kBoundaryIndex], "prof_ra_plt_caller"));
    ASSERT_GE(g_ra4_dw_depth, kBoundaryIndex + 2);
    EXPECT_TRUE(symbolContains(g_ra4_dw_chain[kBoundaryIndex + 1], "prof_ra_plt_trampoline"))
        << "got " << (symbolFor(g_ra4_dw_chain[kBoundaryIndex + 1])
                          ? symbolFor(g_ra4_dw_chain[kBoundaryIndex + 1])
                          : "<null>");

    ++g_gating_assertions_reached;
#endif  // __x86_64__ || __aarch64__
}

// Arithmetic-level fallback coverage for row 4 (DwRegPltThresholdArithmetic,
// kept regardless of whether the live fixture above manages to gate it in
// this build/toolchain) moved above the __linux__ gate -- portable. See
// ReturnAddressAttributionCharacterizationTest.

// ===========================================================================
// Test 5 -- DW_PC_OFFSET sets pc_is_ra = true (coverage row 6).
// ===========================================================================

#if defined(__x86_64__)
static constexpr int kPcOffsetK = 8;
asm(
    ".text\n"
    ".globl prof_ra_pcoff_fn\n"
    ".type prof_ra_pcoff_fn,@function\n"
"prof_ra_pcoff_fn:\n"
    ".cfi_startproc\n"
    ".cfi_def_cfa %rsp, 16\n"
    // DW_CFA_val_expression (0x16), register = DW_REG_PC (16 on x86_64,
    // ULEB128, fits one byte), expression length 2, DW_OP_breg16
    // (0x70 + 16 = 0x80, one-byte form covers registers 0-31), SLEB128
    // offset K (fits one byte for K = 8).
    ".cfi_escape 0x16, 16, 0x02, 0x80, 8\n"
    "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n"
    ".cfi_endproc\n"
    ".size prof_ra_pcoff_fn, .-prof_ra_pcoff_fn\n"
    ".globl prof_ra_pcoff_next\n"
    ".type prof_ra_pcoff_next,@function\n"
"prof_ra_pcoff_next:\n"
    "ret\n"
    ".size prof_ra_pcoff_next, .-prof_ra_pcoff_next\n"
);
#elif defined(__aarch64__)
static constexpr int kPcOffsetK = 8;
asm(
    ".text\n"
    ".globl prof_ra_pcoff_fn\n"
    ".type prof_ra_pcoff_fn,%function\n"
"prof_ra_pcoff_fn:\n"
    ".cfi_startproc\n"
    ".cfi_def_cfa sp, 16\n"
    // register = DW_REG_PC (30 on aarch64), expression length 2,
    // DW_OP_breg30 (0x70 + 30 = 0x8e), SLEB128 offset K = 8.
    ".cfi_escape 0x16, 30, 0x02, 0x8e, 8\n"
    "nop\nnop\n"
    ".cfi_endproc\n"
    ".size prof_ra_pcoff_fn, .-prof_ra_pcoff_fn\n"
    ".globl prof_ra_pcoff_next\n"
    ".type prof_ra_pcoff_next,%function\n"
"prof_ra_pcoff_next:\n"
    "ret\n"
    ".size prof_ra_pcoff_next, .-prof_ra_pcoff_next\n"
);
#endif

#if defined(__x86_64__)
asm(
    ".text\n"
    ".globl prof_ra_pcoff_seed\n"
    ".type prof_ra_pcoff_seed,@function\n"
"prof_ra_pcoff_seed:\n"
    ".cfi_startproc\n"
    ".cfi_def_cfa %rsp, 16\n"
    "nop\nnop\nnop\nnop\n"
    ".cfi_endproc\n"
    ".size prof_ra_pcoff_seed, .-prof_ra_pcoff_seed\n"
);
#elif defined(__aarch64__)
asm(
    ".text\n"
    ".globl prof_ra_pcoff_seed\n"
    ".type prof_ra_pcoff_seed,%function\n"
"prof_ra_pcoff_seed:\n"
    ".cfi_startproc\n"
    ".cfi_def_cfa sp, 16\n"
    "nop\nnop\n"
    ".cfi_endproc\n"
    ".size prof_ra_pcoff_seed, .-prof_ra_pcoff_seed\n"
);
#endif

#if defined(__x86_64__) || defined(__aarch64__)
extern "C" void prof_ra_pcoff_fn(void);
extern "C" void prof_ra_pcoff_next(void);
extern "C" void prof_ra_pcoff_seed(void);
#endif

TEST_F(ReturnAddressAttributionTest, Test5_DwPcOffsetSetsFlag) {
#if !defined(__x86_64__) && !defined(__aarch64__)
    GTEST_SKIP() << "DW_PC_OFFSET fixture only implemented for x86_64/aarch64";
#else
    // Precondition: adjacency, and that the .cfi_escape round-tripped into a
    // DW_PC_OFFSET row through ElfParser.
    if ((const void*)&prof_ra_pcoff_next != (const void*)((const char*)&prof_ra_pcoff_fn + kPcOffsetK)) {
        GTEST_SKIP() << "assembler/linker inserted padding after prof_ra_pcoff_fn; "
                      << "this build cannot exhibit the DW_PC_OFFSET path";
    }

    CodeCache* lib = Libraries::instance()->findLibraryByAddress((const void*)&prof_ra_pcoff_fn);
    if (lib == nullptr) {
        GTEST_SKIP() << "prof_ra_pcoff_fn not visible to findLibraryByAddress; degrading -- "
                      << "stackWalker.cpp:198-199 ships with no gating coverage in this build, "
                      << "verified by inspection against dwarf.cpp only. Record this in the PR.";
    }
    FrameDesc row = lib->findFrameDesc((const void*)&prof_ra_pcoff_fn);
    if (!(row.fp_off & DW_PC_OFFSET) || (row.fp_off >> 1) != kPcOffsetK) {
        GTEST_SKIP() << "the .cfi_escape DW_CFA_val_expression row did not round-trip as "
                      << "DW_PC_OFFSET with offset " << kPcOffsetK << " (observed fp_off="
                      << row.fp_off << ") -- degrading per the tester plan, record the gap in the PR";
    }

    static uintptr_t scratch[64];
    ucontext_t uc = makeFabricatedContext((const void*)&prof_ra_pcoff_fn, scratch, 64);
    StackContext ctx{};
    bool truncated = false;
    const void* chain[8];
    int depth = StackWalker::walkDwarf(&uc, chain, 8, &ctx, &truncated);

    ASSERT_GE(depth, 2);
    // The ucontext leaf is byte-exact and NOT adjusted.
    ASSERT_EQ((const void*)&prof_ra_pcoff_fn, chain[0]);

    // Gating assertion. Pre-fix (or with the flag merely carried through)
    // chain[1] is prof_ra_pcoff_next exactly.
    const void* expected = (const void*)((const char*)&prof_ra_pcoff_next - 1);
    EXPECT_EQ(expected, chain[1])
        << "DW_PC_OFFSET-derived pc must be treated as a return address and adjusted; "
        << "got chain[1] == prof_ra_pcoff_next exactly, meaning pc_is_ra stayed false";
    EXPECT_TRUE(symbolContains(chain[1], "prof_ra_pcoff_fn"));
    EXPECT_FALSE(symbolContains(chain[1], "prof_ra_pcoff_next"));

    ++g_gating_assertions_reached;
#endif  // __x86_64__ || __aarch64__
}

// Test 5b -- the DW_PC_OFFSET row's offset is applied to the *raw* walking
// pc, not to the attribution address.
//
// Test5 above drives the DW_PC_OFFSET row from a ucontext leaf, where
// attribution_pc == pc, so it cannot tell the two bases apart: reverting the
// base leaves it green. This fixture reaches the same row one level up, from
// a frame whose pc was itself loaded from a return-address slot, so the two
// candidate bases differ by exactly one byte in chain[2].
//
// The base must be the raw pc: DW_CFA_val_expression on the return-address
// column encodes DW_OP_breg<PC> + K, and DW_OP_breg names the value of the
// PC *register* -- the exact interrupted address -- not the address the row
// was looked up with (see the comment on DwarfParser::parseExpression).
TEST_F(ReturnAddressAttributionTest, Test5b_DwPcOffsetAppliesOffsetToRawPc) {
#if !defined(__x86_64__) && !defined(__aarch64__)
    GTEST_SKIP() << "DW_PC_OFFSET fixture only implemented for x86_64/aarch64";
#else
    CodeCache* lib = Libraries::instance()->findLibraryByAddress((const void*)&prof_ra_pcoff_fn);
    if (lib == nullptr) {
        GTEST_SKIP() << "prof_ra_pcoff_fn not visible to findLibraryByAddress in this build";
    }

    // The offset into prof_ra_pcoff_fn that the synthetic return address
    // points at. Any value in (0, kPcOffsetK) keeps it inside the function,
    // so both the raw address and the attribution address (one byte lower)
    // still select the DW_PC_OFFSET row that starts at the function's first
    // byte. 4 keeps it instruction-aligned on aarch64 as well.
    const int kInnerOff = 4;
    const void* synthetic_ra = (const void*)((const char*)&prof_ra_pcoff_fn + kInnerOff);

    FrameDesc pcoff_row = lib->findFrameDesc(
        (const void*)((const char*)synthetic_ra - 1));
    if (!(pcoff_row.fp_off & DW_PC_OFFSET) || (pcoff_row.fp_off >> 1) != kPcOffsetK) {
        GTEST_SKIP() << "the .cfi_escape DW_CFA_val_expression row did not round-trip as "
                      << "DW_PC_OFFSET with offset " << kPcOffsetK << " at the attribution "
                      << "address (observed fp_off=" << pcoff_row.fp_off << ")";
    }
    FrameDesc seed_row = lib->findFrameDesc((const void*)&prof_ra_pcoff_seed);
    if ((seed_row.cfa & 0xffu) != (u32)DW_REG_SP || (seed_row.cfa >> 8) != 16 ||
        (seed_row.fp_off & DW_PC_OFFSET)) {
        GTEST_SKIP() << "prof_ra_pcoff_seed's row did not round-trip as a plain "
                      << "DW_REG_SP/offset-16 frame (observed cfa=" << seed_row.cfa
                      << ", fp_off=" << seed_row.fp_off << ")";
    }

    // Every word of the upper half of the scratch stack holds the synthetic
    // return address, so whichever slot the seed frame's row reads it from
    // (the exact slot differs between x86_64 and aarch64) yields the same
    // value, without this test having to reimplement the CFA arithmetic.
    static uintptr_t scratch[64];
    ucontext_t uc = makeFabricatedContext((const void*)&prof_ra_pcoff_seed, scratch, 64);
    for (size_t i = 32; i < 64; i++) {
        scratch[i] = (uintptr_t)synthetic_ra;
    }

    StackContext ctx{};
    bool truncated = false;
    const void* chain[8];
    int depth = StackWalker::walkDwarf(&uc, chain, 8, &ctx, &truncated);

    ASSERT_GE(depth, 3);
    ASSERT_EQ((const void*)&prof_ra_pcoff_seed, chain[0]);
    ASSERT_EQ((const void*)((const char*)synthetic_ra - 1), chain[1])
        << "frame 1's pc came from a return-address slot, so it must be adjusted";

    // chain[2] = attributionPC(base + K) = base + K - 1.
    const void* expected_raw_base =
        (const void*)((const char*)synthetic_ra + kPcOffsetK - 1);
    const void* if_attribution_base =
        (const void*)((const char*)synthetic_ra - 1 + kPcOffsetK - 1);
    EXPECT_EQ(expected_raw_base, chain[2])
        << "DW_PC_OFFSET's offset must be applied to the raw pc; chain[2] == "
        << if_attribution_base << " would mean it was applied to the attribution address";

    ++g_gating_assertions_reached;
#endif  // __x86_64__ || __aarch64__
}

// ===========================================================================
// Test 6 -- Link-register recovery sets the flag (coverage row 7).
//
// Reachability, so nobody reads a green run here as coverage:
//  - x86_64/i386: structurally unreachable. EMPTY_FRAME_SIZE > 0 makes the
//    guard "EMPTY_FRAME_SIZE > 0 || pc_off != DW_LINK_REGISTER" always true,
//    so the arm never executes.
//  - aarch64: reachable only with a frame table that actually carries
//    pc_off == DW_LINK_REGISTER. DwarfParser never emits it -- it starts
//    pc_off at -EMPTY_FRAME_SIZE and no DW_CFA_ handler assigns that value --
//    so no .eh_frame fixture, including the one below, can reach the arm.
//    The only producer in the tree is SFrameParser (sframe.cpp, gated by
//    SFrameParser.PerFRE_RA_Untracked in sframe_ut.cpp), which needs a
//    .sframe section in the scanned ELF image; the gtest binary is not built
//    with one, and CodeCache::setDwarfTable() cannot be used to inject one
//    because it asserts the cache is unpublished.
//
// The fixture is kept so that it starts gating on its own if a .sframe-
// enabled build ever appears, and so the precondition check documents which
// row shape the arm needs. It deliberately does not increment
// g_gating_assertions_reached on the skip path.
// ===========================================================================

#if defined(__aarch64__)

asm(
    ".text\n"
    ".globl prof_ra_lr_fn\n"
    ".type prof_ra_lr_fn,%function\n"
"prof_ra_lr_fn:\n"
    ".cfi_startproc\n"
    ".cfi_def_cfa sp, 0\n"
    "nop\n"
    ".cfi_endproc\n"
    ".size prof_ra_lr_fn, .-prof_ra_lr_fn\n"
    ".globl prof_ra_lr_next\n"
    ".type prof_ra_lr_next,%function\n"
"prof_ra_lr_next:\n"
    "ret\n"
    ".size prof_ra_lr_next, .-prof_ra_lr_next\n"
);

extern "C" void prof_ra_lr_fn(void);
extern "C" void prof_ra_lr_next(void);

#endif  // __aarch64__

TEST_F(ReturnAddressAttributionTest, Test6_LinkRegisterRecoverySetsFlag) {
#if !defined(__aarch64__)
    GTEST_SKIP() << "link-register recovery is unreachable where EMPTY_FRAME_SIZE > 0 (x86_64/i386)";
#else
    CodeCache* lib = Libraries::instance()->findLibraryByAddress((const void*)&prof_ra_lr_fn);
    if (lib == nullptr) {
        GTEST_SKIP() << "prof_ra_lr_fn not visible to findLibraryByAddress in this build";
    }
    FrameDesc row = lib->findFrameDesc((const void*)&prof_ra_lr_fn);
    if (row.pc_off != DW_LINK_REGISTER || (row.fp_off & DW_PC_OFFSET)) {
        GTEST_SKIP() << "expected: .eh_frame cannot express pc_off == DW_LINK_REGISTER, so this "
                      << "fixture's row parsed as (pc_off=" << row.pc_off << ", fp_off="
                      << row.fp_off << ") and the link-register arm is not reached. The arm is "
                      << "covered by inspection only; its producer is gated by "
                      << "SFrameParser.PerFRE_RA_Untracked. See this test's banner comment.";
    }
    if ((const void*)&prof_ra_lr_next != (const void*)((const char*)&prof_ra_lr_fn + 4)) {
        // Not a hard requirement for this fixture (unlike Tests 1/3/4/5, the
        // link register is set directly below, not derived from an actual
        // call-site return address), but a large gap would mean the two
        // symbols aren't where expected -- keep this as a sanity note only.
    }

    static uintptr_t scratch[64];
    ucontext_t uc = makeFabricatedContext((const void*)&prof_ra_lr_fn, scratch, 64);
    // The link register holds a synthetic return address sitting exactly on
    // prof_ra_lr_next's first byte -- what makes raw vs. adjusted symbolize
    // differently.
    uc.uc_mcontext.regs[30] = (unsigned long)&prof_ra_lr_next;

    StackContext ctx{};
    bool truncated = false;
    const void* chain[8];
    int depth = StackWalker::walkDwarf(&uc, chain, 8, &ctx, &truncated);

    ASSERT_GE(depth, 2);
    ASSERT_EQ((const void*)&prof_ra_lr_fn, chain[0]);

    const void* expected = (const void*)((const char*)&prof_ra_lr_next - 1);
    EXPECT_EQ(expected, chain[1])
        << "link-register-recovered pc must be adjusted; pre-fix chain[1] is "
        << "prof_ra_lr_next exactly";
    EXPECT_TRUE(symbolContains(chain[1], "prof_ra_lr_fn"));

    ++g_gating_assertions_reached;
#endif  // __aarch64__
}

// Test 7 -- Mark-based walk termination (MarkVisibleAtAdjustedBoundaryAddress)
// moved above the __linux__ gate -- portable. See
// ReturnAddressAttributionCharacterizationTest.

// Non-skippable canary (b-3): every gating test above can independently
// GTEST_SKIP if its toolchain-dependent precondition fails, and GTEST_SKIP
// counts as a passing run, so a CI toolchain on which all of them skip would
// otherwise report this whole file as green with zero effective regression
// coverage for the attribution fix. This test cannot skip -- it fails if
// none of the gating tests reached its assertions, surfacing that
// degradation instead of letting it pass silently. Declared last so it runs
// after all of them under gtest's default (registration-order) test order.
// Test6 is excluded by construction -- see its banner comment.
TEST(ReturnAddressAttributionGatingCoverageTest, AtLeastOneGatingAssertionRan) {
    EXPECT_GT(g_gating_assertions_reached, 0)
        << "every gating test in this file (Test1/2c/3/4/5/5b) skipped its precondition "
        << "check on this toolchain -- the attribution fix has zero effective "
        << "regression coverage in this build; see each test's GTEST_SKIP reason "
        << "in the test log above for which precondition failed";
}

#endif  // __linux__
