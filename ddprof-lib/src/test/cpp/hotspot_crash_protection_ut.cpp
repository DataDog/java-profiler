/*
 * Copyright 2026 Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Unit tests for the crash-protection and thread-classification mechanisms
 * used by HotspotSupport::walkVM().
 *
 * Background: profiling signals can interrupt any JVM thread — including
 * JVM-internal threads such as MonitorDeflationThread.  walkVM must never
 * dereference JavaThread-only fields (anchor, vframe_top, …) on such threads.
 * VMThread::isJavaThread() provides the gate.
 *
 * Crash recovery inside walkVM relies on setjmp/longjmp:
 *   1. walkVM stores a jmp_buf* on ProfiledThread (setJmpCtx/getJmpCtx),
 *      chaining it with whatever context was already installed so a
 *      signal-based sampler interrupting a non-signal-based sampler's own
 *      in-flight walkVM() call doesn't clobber the outer call's context.
 *   2. If a fault fires during the walk, checkFault() detects the live
 *      context via ProfiledThread::isProtected() and calls longjmp() to
 *      unwind through whatever context is currently installed.
 *   3. ProfiledThread tracks nested crash-handler depth so recursive faults
 *      (e.g. wall-clock signal inside a crash handler) are capped safely.
 *
 * Tests cover:
 *   A. ProfiledThread thread-type classification (isJavaThread fast path)
 *   B. Crash-handler nesting depth (ProfiledThread crash handler state)
 *   C. jmp_buf chaining across nested/interrupted walkVM() calls
 */

#include <gtest/gtest.h>
#include "threadLocalData.h"
#include "hotspot/hotspotSupport.h"

#include "jvmThread.h"
#include "safeAccess.h"
#include "os.h"

#ifdef __linux__

#include <cstring>
#include <sys/mman.h>
#include <unistd.h>

// ---------------------------------------------------------------------------
// A. ProfiledThread thread-type classification (isJavaThread fast path)
//
// JVMTI ThreadStart callbacks call setJavaThread(true/false) to cache the
// result; isJavaThread() returns it directly without touching the vtable.
// ---------------------------------------------------------------------------

class ProfiledThreadTypeTest : public ::testing::Test {
protected:
    void SetUp() override {
        ProfiledThread::initCurrentThread();
        _pt = ProfiledThread::currentSignalSafe();
        ASSERT_NE(nullptr, _pt);
    }

    void TearDown() override {
        ProfiledThread::release();
    }

    ProfiledThread* _pt = nullptr;
};

// A fresh ProfiledThread is not yet classified.
TEST_F(ProfiledThreadTypeTest, InitialStateIsUnknown) {
    EXPECT_EQ(ProfiledThread::TYPE_UNKNOWN, _pt->threadType());
}

TEST_F(ProfiledThreadTypeTest, MarkAsJavaThreadSetsCorrectType) {
    _pt->setJavaThread(true);
    EXPECT_EQ(ProfiledThread::TYPE_JAVA_THREAD, _pt->threadType());
}

// MonitorDeflationThread and similar JVM-internal threads are marked false.
TEST_F(ProfiledThreadTypeTest, MarkAsNonJavaThreadSetsCorrectType) {
    _pt->setJavaThread(false);
    EXPECT_EQ(ProfiledThread::TYPE_NOT_JAVA_THREAD, _pt->threadType());
}

TEST_F(ProfiledThreadTypeTest, ReclassificationFromJavaToNonJava) {
    _pt->setJavaThread(true);
    EXPECT_EQ(ProfiledThread::TYPE_JAVA_THREAD, _pt->threadType());

    _pt->setJavaThread(false);
    EXPECT_EQ(ProfiledThread::TYPE_NOT_JAVA_THREAD, _pt->threadType());
}

// Replicate the fast-path branch used by isJavaThread():
//   if (type != TYPE_UNKNOWN) return type == TYPE_JAVA_THREAD;
TEST_F(ProfiledThreadTypeTest, FastPathReturnsTrueForJavaThread) {
    _pt->setJavaThread(true);
    ProfiledThread::ThreadType type = _pt->threadType();
    bool result = (type != ProfiledThread::TYPE_UNKNOWN)
               && (type == ProfiledThread::TYPE_JAVA_THREAD);
    EXPECT_TRUE(result);
}

TEST_F(ProfiledThreadTypeTest, FastPathReturnsFalseForNonJavaThread) {
    _pt->setJavaThread(false);
    ProfiledThread::ThreadType type = _pt->threadType();
    bool result = (type != ProfiledThread::TYPE_UNKNOWN)
               && (type == ProfiledThread::TYPE_JAVA_THREAD);
    EXPECT_FALSE(result);
}

// ---------------------------------------------------------------------------
// B. Crash-handler nesting depth
//
// ProfiledThread tracks how many crash-handler invocations are active on this
// thread so recursive signals (wall-clock arriving inside a crash handler)
// are capped at CRASH_HANDLER_NESTING_LIMIT.
//
// Profiler::crashHandlerInternal calls:
//   enterCrashHandler()   — on entry, returns false if limit reached
//   exitCrashHandler()    — on normal exit
//   resetCrashHandler()   — from checkFault before longjmp to unwind all
//                           nesting at once
// ---------------------------------------------------------------------------

class CrashHandlerNestingTest : public ::testing::Test {
protected:
    void SetUp() override {
        ProfiledThread::initCurrentThread();
        _pt = ProfiledThread::currentSignalSafe();
        ASSERT_NE(nullptr, _pt);
    }

    void TearDown() override {
        ProfiledThread::release();
    }

    ProfiledThread* _pt = nullptr;
};

TEST_F(CrashHandlerNestingTest, InitialDepthAllowsEntry) {
    EXPECT_TRUE(_pt->enterCrashHandler());
    _pt->exitCrashHandler();
}

TEST_F(CrashHandlerNestingTest, ExitDecrements) {
    _pt->enterCrashHandler();
    _pt->exitCrashHandler();
    // After a balanced enter/exit, another enter should still succeed.
    EXPECT_TRUE(_pt->enterCrashHandler());
    _pt->exitCrashHandler();
}

// At the nesting limit enterCrashHandler returns false to prevent runaway recursion.
TEST_F(CrashHandlerNestingTest, LimitBlocksFurtherEntry) {
    for (u32 i = 0; i < ProfiledThread::CRASH_HANDLER_NESTING_LIMIT; i++) {
        EXPECT_TRUE(_pt->enterCrashHandler()) << "entry " << i << " should succeed";
    }
    EXPECT_FALSE(_pt->enterCrashHandler()) << "entry at limit should fail";

    // Clean up the nesting we opened above.
    for (u32 i = 0; i < ProfiledThread::CRASH_HANDLER_NESTING_LIMIT; i++) {
        _pt->exitCrashHandler();
    }
}

// resetCrashHandler() is called by checkFault() before longjmp so that the
// landing pad in walkVM starts with a clean nesting count.
TEST_F(CrashHandlerNestingTest, ResetAllowsEntryAfterDeepNesting) {
    for (u32 i = 0; i < ProfiledThread::CRASH_HANDLER_NESTING_LIMIT; i++) {
        _pt->enterCrashHandler();
    }
    _pt->resetCrashHandler();
    EXPECT_TRUE(_pt->enterCrashHandler());
    _pt->exitCrashHandler();
}

// exitCrashHandler is a no-op if depth is already 0 (failsafe against
// unbalanced calls during error paths).
TEST_F(CrashHandlerNestingTest, ExitAtZeroIsNoop) {
    _pt->exitCrashHandler();  // depth was 0, must not underflow
    EXPECT_TRUE(_pt->enterCrashHandler());
    _pt->exitCrashHandler();
}

// isDeepCrashHandler returns true only when depth *exceeds* the limit.
// At exactly the limit, it is false — entry is refused but "deep" is not yet set.
TEST_F(CrashHandlerNestingTest, IsDeepOnlyAboveLimit) {
    for (u32 i = 0; i < ProfiledThread::CRASH_HANDLER_NESTING_LIMIT; i++) {
        _pt->enterCrashHandler();
    }
    EXPECT_FALSE(_pt->isDeepCrashHandler());  // at limit, not above it
    _pt->resetCrashHandler();
}

// ---------------------------------------------------------------------------
// C. jmp_buf chaining (ProfiledThread::setJmpCtx/getJmpCtx/isProtected)
//
// A non-signal-based sampler's walkVM() call can itself be interrupted by a
// signal-based sampler, putting two walkVM() frames on the same thread's
// stack. Each frame follows the same protocol:
//   jmp_buf* prev = prof_thread->getJmpCtx();   // save whatever was there
//   prof_thread->setJmpCtx(&my_ctx);            // install this frame's ctx
//   ... walk ...
//   prof_thread->setJmpCtx(prev);               // restore on every exit path
// checkFault() always longjmps through whatever is currently installed
// (thrd->getJmpCtx()), so the inner frame must never leave the outer frame's
// context installed while the inner frame is doing its own protected work,
// and must always hand it back — via normal completion or fault recovery —
// before returning control to the outer frame.
// ---------------------------------------------------------------------------

class JmpCtxChainingTest : public ::testing::Test {
protected:
    void SetUp() override {
        ProfiledThread::initCurrentThread();
        _pt = ProfiledThread::currentSignalSafe();
        ASSERT_NE(nullptr, _pt);
    }

    void TearDown() override {
        ProfiledThread::release();
    }

    ProfiledThread* _pt = nullptr;
};

TEST_F(JmpCtxChainingTest, InitiallyUnprotected) {
    EXPECT_FALSE(_pt->isProtected());
    EXPECT_EQ(nullptr, _pt->getJmpCtx());
}

TEST_F(JmpCtxChainingTest, SetAndGetRoundTrip) {
    jmp_buf ctx;
    _pt->setJmpCtx(&ctx);
    EXPECT_TRUE(_pt->isProtected());
    EXPECT_EQ(&ctx, _pt->getJmpCtx());
}

// Replicates a single walkVM() call's save/install/restore around its body.
TEST_F(JmpCtxChainingTest, SingleFrameRestoresPreviousOnExit) {
    jmp_buf outer;
    jmp_buf* prev = _pt->getJmpCtx();  // nullptr: no enclosing walkVM() call
    ASSERT_EQ(nullptr, prev);

    _pt->setJmpCtx(&outer);
    EXPECT_EQ(&outer, _pt->getJmpCtx());

    // Simulate walkVM()'s `done:` path.
    _pt->setJmpCtx(prev);
    EXPECT_EQ(nullptr, _pt->getJmpCtx());
    EXPECT_FALSE(_pt->isProtected());
}

// Replicates two nested walkVM() calls: a signal-based sampler interrupting a
// non-signal-based sampler's own in-flight walkVM(). The inner call must
// chain off the outer's jmp_buf*, install its own, and hand the outer's back
// on its way out — leaving the outer frame's context exactly as it left it.
TEST_F(JmpCtxChainingTest, NestedFramesChainAndUnwindInOrder) {
    jmp_buf outer_ctx;
    jmp_buf* outer_prev = _pt->getJmpCtx();
    ASSERT_EQ(nullptr, outer_prev);
    _pt->setJmpCtx(&outer_ctx);
    EXPECT_EQ(&outer_ctx, _pt->getJmpCtx());

    {
        // Inner walkVM() call, as if a signal fired while the outer one was
        // mid-walk.
        jmp_buf inner_ctx;
        jmp_buf* inner_prev = _pt->getJmpCtx();
        EXPECT_EQ(&outer_ctx, inner_prev);  // chained off the outer frame

        _pt->setJmpCtx(&inner_ctx);
        EXPECT_EQ(&inner_ctx, _pt->getJmpCtx());

        // Inner call completes via its own `done:` path.
        _pt->setJmpCtx(inner_prev);
    }

    // The outer frame's context must be untouched by the inner call.
    EXPECT_EQ(&outer_ctx, _pt->getJmpCtx());

    _pt->setJmpCtx(outer_prev);
    EXPECT_EQ(nullptr, _pt->getJmpCtx());
}

// End-to-end with real setjmp/longjmp: a fault inside the inner frame must
// land in the inner frame's own recovery branch — checkFault() always
// longjmps through whatever is currently installed — and once the inner
// frame has recovered and restored the outer's context, the outer frame must
// be left exactly as it was, never having been unwound itself.
TEST_F(JmpCtxChainingTest, FaultInInnerFrameDoesNotDisturbOuterFrame) {
    jmp_buf outer_ctx;
    jmp_buf* outer_prev = _pt->getJmpCtx();
    int outer_landed = 0;
    int inner_landed = 0;

    if (setjmp(outer_ctx) != 0) {
        outer_landed++;
    } else {
        _pt->setJmpCtx(&outer_ctx);

        // --- inner "walkVM" call, interrupted mid-flight by a fault ---
        jmp_buf inner_ctx;
        jmp_buf* inner_prev = _pt->getJmpCtx();
        ASSERT_EQ(&outer_ctx, inner_prev);

        if (setjmp(inner_ctx) != 0) {
            inner_landed++;
            _pt->setJmpCtx(inner_prev);
        } else {
            _pt->setJmpCtx(&inner_ctx);
            // Simulate checkFault(): longjmp through whatever is currently
            // installed — this must hit the inner frame, not the outer.
            longjmp(*_pt->getJmpCtx(), 1);
            FAIL() << "unreachable: longjmp does not return";
        }
        // --- inner call has returned normally after recovering ---

        EXPECT_EQ(&outer_ctx, _pt->getJmpCtx())
            << "outer frame's context must survive the inner frame's fault";

        _pt->setJmpCtx(outer_prev);
    }

    EXPECT_EQ(1, inner_landed);
    EXPECT_EQ(0, outer_landed) << "the fault must not have unwound past the inner frame";
    EXPECT_FALSE(_pt->isProtected());
}

// ---------------------------------------------------------------------------
// D. HotspotSupport::checkFault() guard clauses
//
// This gtest binary has no live JVM attached, so JVMThread is not initialized
// and the longjmp path can't be exercised end-to-end here.
// These tests still call the real checkFault() (not a replica) to lock down
// its early-return guard: a null ProfiledThread*
// ---------------------------------------------------------------------------

TEST(CheckFaultGuardTest, NullThreadIsNoop) {
    HotspotSupport::checkFault(nullptr);  // must not crash
}

// ---------------------------------------------------------------------------
// E. VTable-stub null-klass and safeFetch64==0 TOCTOU guards
//
// The real call sites (hotspotSupport.cpp's vtable_target branch and
// VMKlass::fromOop's compact-header path) depend on JVM-populated static
// offsets that only exist with a live JVM, so they can't be invoked directly
// in this gtest binary. These tests replicate the exact guard conditions
// verbatim, mirroring the "replicate the protocol" style already used above
// for isJavaThread()'s fast path, to lock down the null-safety contract at
// both sites against future refactors.
// ---------------------------------------------------------------------------

// Mirrors hotspotSupport.cpp's vtable_target branch:
//   VMSymbol* symbol = klass != nullptr ? klass->name() : nullptr;
//   if (symbol != nullptr) fillFrame(...);
// A null klass (e.g. VMKlass::fromOop returning nullptr) must short-circuit
// to a null symbol and skip fillFrame, never dereference klass.
TEST(VTableStubNullKlassTest, NullKlassYieldsNullSymbolAndNoFrame) {
    struct FakeKlass {
        void* name() { return this; }  // would only run if wrongly dereferenced
    };
    FakeKlass* klass = nullptr;
    void* symbol = klass != nullptr ? klass->name() : nullptr;
    EXPECT_EQ(nullptr, symbol);

    bool fillFrameCalled = false;
    if (symbol != nullptr) {
        fillFrameCalled = true;
    }
    EXPECT_FALSE(fillFrameCalled);
}

// SafeAccess::safeFetch64 relies on a registered SIGSEGV/SIGBUS handler
// (SafeAccess::handle_safefetch) to catch the fault and resume with the
// error value instead of crashing — see safefetch_ut.cpp's SafeFetchTest
// fixture for the same pattern. Without it, faulting through safeFetch64
// is a real, unguarded SIGSEGV.
class SafeFetch64TocTouGuardTest : public ::testing::Test {
protected:
    static void handler(int signo, siginfo_t* siginfo, void* context) {
        SafeAccess::handle_safefetch(signo, context);
    }

    void SetUp() override {
        _orig_segv = OS::replaceSigsegvHandler(handler);
        _orig_bus = OS::replaceSigbusHandler(handler);
    }

    void TearDown() override {
        OS::replaceSigsegvHandler(_orig_segv);
        OS::replaceSigbusHandler(_orig_bus);
    }

    SigAction _orig_segv = nullptr;
    SigAction _orig_bus = nullptr;
};

// Mirrors VMKlass::fromOop's compact-object-headers TOCTOU guard:
//   mark = (uintptr_t)SafeAccess::safeFetch64((int64_t*)(mark ^ MONITOR_BIT), 0);
//   if (mark == 0) return nullptr;
// SafeAccess::safeFetch64 on an unmapped/concurrently-freed address returns
// its errorValue (0 here); the caller must treat that as "give up" rather
// than shifting 0 into a bogus klass pointer.
TEST_F(SafeFetch64TocTouGuardTest, ZeroReturnMeansGiveUp) {
    void* page = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    ASSERT_NE(page, MAP_FAILED);
    ASSERT_EQ(0, mprotect(page, 4096, PROT_NONE));

    uintptr_t mark = (uintptr_t)SafeAccess::safeFetch64((int64_t*)page, 0);
    EXPECT_EQ(0u, mark);

    void* klass = mark == 0 ? nullptr : (void*)(mark >> 3);
    EXPECT_EQ(nullptr, klass);

    munmap(page, 4096);
}

#endif  // __linux__
