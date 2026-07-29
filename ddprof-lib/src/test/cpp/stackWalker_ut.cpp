/*
 * Copyright 2026, Datadog, Inc
 */

#include <gtest/gtest.h>
#include "../../main/cpp/stackWalker.h"
#include "../../main/cpp/gtest_crash_handler.h"

#ifdef __linux__
#include <sys/mman.h>
#include "../../main/cpp/os.h"
#include "../../main/cpp/profiler.h"
#include "../../main/cpp/threadLocalData.h"
#endif

static constexpr char STACKWALKER_TEST_NAME[] = "StackWalkerTest";

class StackWalkerTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<STACKWALKER_TEST_NAME>();
    }

    void TearDown() override {
        restoreDefaultSignalHandlers();
    }

    // Helper to create a frame with a non-NULL method_id
    static ASGCT_CallFrame knownFrame(int id) {
        ASGCT_CallFrame f = {};
        f.bci = 0;
        f.method_id = (jmethodID)(uintptr_t)(id + 1);  // non-NULL
        return f;
    }

    // Helper to create a frame with NULL method_id (unknown)
    static ASGCT_CallFrame unknownFrame() {
        ASGCT_CallFrame f = {};
        f.bci = 0;
        f.method_id = NULL;
        return f;
    }
};

TEST_F(StackWalkerTest, dropUnknownLeaf_empty_trace) {
    ASGCT_CallFrame frames[1];
    int depth = StackWalkValidation::dropUnknownLeaf(frames, 0);
    EXPECT_EQ(0, depth);
}

TEST_F(StackWalkerTest, dropUnknownLeaf_single_unknown_frame) {
    ASGCT_CallFrame frames[1] = { unknownFrame() };
    int depth = StackWalkValidation::dropUnknownLeaf(frames, 1);
    EXPECT_EQ(0, depth);
}

TEST_F(StackWalkerTest, dropUnknownLeaf_single_known_frame) {
    ASGCT_CallFrame frames[1] = { knownFrame(1) };
    int depth = StackWalkValidation::dropUnknownLeaf(frames, 1);
    EXPECT_EQ(1, depth);
    EXPECT_NE(nullptr, frames[0].method_id);
}

TEST_F(StackWalkerTest, dropUnknownLeaf_unknown_leaf_with_known_callers) {
    // frames[0] is the leaf (top of stack), frames[1..2] are callers
    ASGCT_CallFrame frames[3] = { unknownFrame(), knownFrame(1), knownFrame(2) };
    int depth = StackWalkValidation::dropUnknownLeaf(frames, 3);
    EXPECT_EQ(2, depth);
    // The former frames[1] and frames[2] should now be at [0] and [1]
    EXPECT_EQ((jmethodID)(uintptr_t)2, frames[0].method_id);
    EXPECT_EQ((jmethodID)(uintptr_t)3, frames[1].method_id);
}

TEST_F(StackWalkerTest, dropUnknownLeaf_known_leaf_not_dropped) {
    ASGCT_CallFrame frames[3] = { knownFrame(1), knownFrame(2), knownFrame(3) };
    int depth = StackWalkValidation::dropUnknownLeaf(frames, 3);
    EXPECT_EQ(3, depth);
    EXPECT_EQ((jmethodID)(uintptr_t)2, frames[0].method_id);
    EXPECT_EQ((jmethodID)(uintptr_t)3, frames[1].method_id);
    EXPECT_EQ((jmethodID)(uintptr_t)4, frames[2].method_id);
}

TEST_F(StackWalkerTest, dropUnknownLeaf_unknown_non_leaf_not_dropped) {
    // Only the leaf (index 0) should be checked — unknown at other positions stays
    ASGCT_CallFrame frames[3] = { knownFrame(1), unknownFrame(), knownFrame(2) };
    int depth = StackWalkValidation::dropUnknownLeaf(frames, 3);
    EXPECT_EQ(3, depth);
    EXPECT_NE(nullptr, frames[0].method_id);
    EXPECT_EQ(nullptr, frames[1].method_id);
    EXPECT_NE(nullptr, frames[2].method_id);
}

// ---- isValidFP ----

TEST_F(StackWalkerTest, isValidFP_null_is_invalid) {
    EXPECT_FALSE(StackWalkValidation::isValidFP(0));
}

TEST_F(StackWalkerTest, isValidFP_low_address_is_invalid) {
    EXPECT_FALSE(StackWalkValidation::isValidFP(0x100));       // below DEAD_ZONE (0x1000)
    EXPECT_FALSE(StackWalkValidation::isValidFP(0xfff));
}

TEST_F(StackWalkerTest, isValidFP_high_address_is_invalid) {
    // Within DEAD_ZONE of UINTPTR_MAX (i.e. >= -DEAD_ZONE)
    EXPECT_FALSE(StackWalkValidation::isValidFP(~(uintptr_t)0));         // UINTPTR_MAX
    EXPECT_FALSE(StackWalkValidation::isValidFP(~(uintptr_t)0 - 0x100)); // still in dead zone
}

TEST_F(StackWalkerTest, isValidFP_misaligned_is_invalid) {
    // Aligned address in valid range but with low bits set
    EXPECT_FALSE(StackWalkValidation::isValidFP(0x10001));  // odd
    EXPECT_FALSE(StackWalkValidation::isValidFP(0x10002));  // 2-byte aligned but not pointer-aligned
}

TEST_F(StackWalkerTest, isValidFP_valid_aligned_address) {
    // Aligned addresses well within valid range should pass
    EXPECT_TRUE(StackWalkValidation::isValidFP(0x10000));
    EXPECT_TRUE(StackWalkValidation::isValidFP(0x7fff0000));
}

// ---- isValidSP ----

TEST_F(StackWalkerTest, isValidSP_must_be_strictly_above_lo) {
    uintptr_t lo = 0x1000;
    uintptr_t hi = 0x5000;
    EXPECT_FALSE(StackWalkValidation::isValidSP(lo, lo, hi));      // sp == lo: not strictly above
    EXPECT_FALSE(StackWalkValidation::isValidSP(lo - 8, lo, hi));  // sp < lo
}

TEST_F(StackWalkerTest, isValidSP_must_be_strictly_below_hi) {
    uintptr_t lo = 0x1000;
    uintptr_t hi = 0x5000;
    EXPECT_FALSE(StackWalkValidation::isValidSP(hi, lo, hi));      // sp == hi: not strictly below
    EXPECT_FALSE(StackWalkValidation::isValidSP(hi + 8, lo, hi));  // sp > hi
}

TEST_F(StackWalkerTest, isValidSP_misaligned_is_invalid) {
    uintptr_t lo = 0x1000;
    uintptr_t hi = 0x5000;
    EXPECT_FALSE(StackWalkValidation::isValidSP(0x2001, lo, hi));  // in range but misaligned
}

TEST_F(StackWalkerTest, isValidSP_valid_aligned_in_range) {
    uintptr_t lo = 0x1000;
    uintptr_t hi = 0x5000;
    EXPECT_TRUE(StackWalkValidation::isValidSP(0x2000, lo, hi));
    EXPECT_TRUE(StackWalkValidation::isValidSP(lo + 8, lo, hi));
    EXPECT_TRUE(StackWalkValidation::isValidSP(hi - 8, lo, hi));
}

#ifdef __linux__

// ---------------------------------------------------------------------------
// Crash recovery: StackWalker::walkFP() / walkDwarf() install a
// sigsetjmp/siglongjmp jmp ctx (mirroring HotspotSupport::walkVM's, see
// stackWalker.cpp) so a SIGSEGV anywhere in the walk is recovered by
// Profiler::checkFault() instead of crashing the process.
//
// `callchain[depth++] = pc;` is the one write in each walker that is NOT
// routed through SafeAccess::load — passing a PROT_NONE `callchain` buffer
// faults on that very first store, before any frame-pointer chasing, so it
// can only be recovered by this jmp-ctx protection (not by safefetch).
//
// These tests install the real Profiler::segvHandler/busHandler (the actual
// production chain: safefetch check, then Profiler::checkFault()) and call
// the real StackWalker functions directly — no live JVM is needed since
// JVMSupport::isJitCode()/JVMThread::current() both degrade to safe
// not-a-JVM-thread defaults without one.
// ---------------------------------------------------------------------------

class StackWalkerCrashRecoveryTest : public ::testing::Test {
protected:
    void SetUp() override {
        ProfiledThread::initCurrentThread();
        _pt = ProfiledThread::current();
        ASSERT_NE(nullptr, _pt);
        ASSERT_FALSE(_pt->isProtected());

        _orig_segv = OS::replaceSigsegvHandler(Profiler::segvHandler);
        _orig_bus = OS::replaceSigbusHandler(Profiler::busHandler);

        _bad_page = mmap(nullptr, 4096, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        ASSERT_NE(MAP_FAILED, _bad_page);
    }

    void TearDown() override {
        munmap(_bad_page, 4096);
        OS::replaceSigsegvHandler(_orig_segv);
        OS::replaceSigbusHandler(_orig_bus);
        ProfiledThread::release();
    }

    ProfiledThread* _pt = nullptr;
    void* _bad_page = nullptr;
    SigAction _orig_segv = nullptr;
    SigAction _orig_bus = nullptr;
};

TEST_F(StackWalkerCrashRecoveryTest, WalkFPRecoversFromFaultInsteadOfCrashing) {
    StackContext java_ctx{};
    bool truncated = false;
    const void** callchain = reinterpret_cast<const void**>(_bad_page);

    // ucontext = nullptr makes walkFP() start from this call's own real
    // pc/fp/sp (callerPC/FP/SP) -- the walk is genuinely live, it just can't
    // write its first frame into the unmapped callchain buffer.
    int depth = StackWalker::walkFP(nullptr, callchain, 64, &java_ctx, &truncated);

    // The exact depth at the moment of the fault is compiler-dependent (the
    // `depth++` store may or may not have landed before the faulting write),
    // so only bound it loosely; what matters is that we got control back at
    // all, with truncation correctly flagged and protection cleanly torn down.
    EXPECT_GE(depth, 0);
    EXPECT_LE(depth, 1);
    EXPECT_TRUE(truncated);
    EXPECT_FALSE(_pt->isProtected()) << "jmp ctx must be restored after recovery";
}

TEST_F(StackWalkerCrashRecoveryTest, WalkDwarfRecoversFromFaultInsteadOfCrashing) {
    StackContext java_ctx{};
    bool truncated = false;
    const void** callchain = reinterpret_cast<const void**>(_bad_page);

    int depth = StackWalker::walkDwarf(nullptr, callchain, 64, &java_ctx, &truncated);

    EXPECT_GE(depth, 0);
    EXPECT_LE(depth, 1);
    EXPECT_TRUE(truncated);
    EXPECT_FALSE(_pt->isProtected()) << "jmp ctx must be restored after recovery";
}

#endif  // __linux__
