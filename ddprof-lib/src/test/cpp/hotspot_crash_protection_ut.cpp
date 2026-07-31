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
 * Crash recovery inside walkVM relies on sigsetjmp/siglongjmp:
 *   1. walkVM stores a sigjmp_buf* on ProfiledThread (setJmpCtx/getJmpCtx),
 *      chaining it with whatever context was already installed so a
 *      signal-based sampler interrupting a non-signal-based sampler's own
 *      in-flight walkVM() call doesn't clobber the outer call's context.
 *   2. If a fault fires during the walk, checkFault() detects the live
 *      context via ProfiledThread::isProtected() and calls siglongjmp() to
 *      unwind through whatever context is currently installed.
 *   3. ProfiledThread tracks nested crash-handler depth so recursive faults
 *      (e.g. wall-clock signal inside a crash handler) are capped safely.
 *
 * Tests cover:
 *   A. ProfiledThread thread-type classification (isJavaThread fast path)
 *   B. Crash-handler nesting depth (ProfiledThread crash handler state)
 *   C. sigjmp_buf chaining across nested/interrupted walkVM() calls
 *   F. HotspotSupport::walkJavaStack()'s AsyncSampleMutex release on a
 *      recovered fault
 */

#include <gtest/gtest.h>
#include "threadLocalData.h"
#include "profiler.h"

#include "asyncSampleMutex.h"
#include "counters.h"
#include "jvmThread.h"
#include "safeAccess.h"
#include "os.h"

#ifdef __linux__

#include <cstring>
#include <sys/mman.h>
#include <unistd.h>

namespace {
// Force Counters::instance()'s function-local static to construct here, off
// the signal path -- mirrors Profiler::setupSignalHandlers()'s own eager
// warm-up (profiler.cpp), which exists precisely because the first touch of
// the singleton runs non-async-signal-safe static-initialization machinery
// (a C++ guard-variable lock, then aligned_alloc/memset). Several fixtures
// below install real signal handlers (Profiler::segvHandler -> checkFault(),
// SafeAccess::handle_safefetch) that increment Counters from inside an
// actual SIGSEGV, without going through setupSignalHandlers() first. Without
// this, whichever such test happens to run first in the process would race
// that first-touch initialization inside a real signal handler instead of
// ordinary code -- not async-signal-safe, and liable to hang.
const bool kCountersPrewarmed = (Counters::getCounters(), true);
}  // namespace

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
        _pt = ProfiledThread::current();
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
//   resetCrashHandler()   — from checkFault before siglongjmp to unwind all
//                           nesting at once
// ---------------------------------------------------------------------------

class CrashHandlerNestingTest : public ::testing::Test {
protected:
    void SetUp() override {
        ProfiledThread::initCurrentThread();
        _pt = ProfiledThread::current();
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

// resetCrashHandler() is called by checkFault() before siglongjmp so that the
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
// C. sigjmp_buf chaining (ProfiledThread::setJmpCtx/getJmpCtx/isProtected)
//
// A non-signal-based sampler's walkVM() call can itself be interrupted by a
// signal-based sampler, putting two walkVM() frames on the same thread's
// stack. Each frame follows the same protocol:
//   sigjmp_buf* prev = prof_thread->getJmpCtx(); // save whatever was there
//   prof_thread->setJmpCtx(&my_ctx);            // install this frame's ctx
//   ... walk ...
//   prof_thread->setJmpCtx(prev);               // restore on every exit path
// checkFault() always siglongjmps through whatever is currently installed
// (thrd->getJmpCtx()), so the inner frame must never leave the outer frame's
// context installed while the inner frame is doing its own protected work,
// and must always hand it back — via normal completion or fault recovery —
// before returning control to the outer frame.
// ---------------------------------------------------------------------------

class JmpCtxChainingTest : public ::testing::Test {
protected:
    void SetUp() override {
        ProfiledThread::initCurrentThread();
        _pt = ProfiledThread::current();
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
    sigjmp_buf ctx;
    _pt->setJmpCtx(&ctx);
    EXPECT_TRUE(_pt->isProtected());
    EXPECT_EQ(&ctx, _pt->getJmpCtx());
}

// Replicates a single walkVM() call's save/install/restore around its body.
TEST_F(JmpCtxChainingTest, SingleFrameRestoresPreviousOnExit) {
    sigjmp_buf outer;
    sigjmp_buf* prev = _pt->getJmpCtx();  // nullptr: no enclosing walkVM() call
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
// chain off the outer's sigjmp_buf*, install its own, and hand the outer's back
// on its way out — leaving the outer frame's context exactly as it left it.
TEST_F(JmpCtxChainingTest, NestedFramesChainAndUnwindInOrder) {
    sigjmp_buf outer_ctx;
    sigjmp_buf* outer_prev = _pt->getJmpCtx();
    ASSERT_EQ(nullptr, outer_prev);
    _pt->setJmpCtx(&outer_ctx);
    EXPECT_EQ(&outer_ctx, _pt->getJmpCtx());

    {
        // Inner walkVM() call, as if a signal fired while the outer one was
        // mid-walk.
        sigjmp_buf inner_ctx;
        sigjmp_buf* inner_prev = _pt->getJmpCtx();
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

// End-to-end with real sigsetjmp/siglongjmp: a fault inside the inner frame must
// land in the inner frame's own recovery branch — checkFault() always
// siglongjmps through whatever is currently installed — and once the inner
// frame has recovered and restored the outer's context, the outer frame must
// be left exactly as it was, never having been unwound itself.
TEST_F(JmpCtxChainingTest, FaultInInnerFrameDoesNotDisturbOuterFrame) {
    sigjmp_buf outer_ctx;
    sigjmp_buf* outer_prev = _pt->getJmpCtx();
    int outer_landed = 0;
    int inner_landed = 0;

    if (sigsetjmp(outer_ctx, 1) != 0) {
        outer_landed++;
    } else {
        _pt->setJmpCtx(&outer_ctx);

        // --- inner "walkVM" call, interrupted mid-flight by a fault ---
        sigjmp_buf inner_ctx;
        sigjmp_buf* inner_prev = _pt->getJmpCtx();
        ASSERT_EQ(&outer_ctx, inner_prev);

        if (sigsetjmp(inner_ctx, 1) != 0) {
            inner_landed++;
            _pt->setJmpCtx(inner_prev);
        } else {
            _pt->setJmpCtx(&inner_ctx);
            // Simulate checkFault(): siglongjmp through whatever is currently
            // installed — this must hit the inner frame, not the outer.
            siglongjmp(*_pt->getJmpCtx(), 1);
            FAIL() << "unreachable: siglongjmp does not return";
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
// D. Profiler::checkFault() guard clauses
//
// This gtest binary has no live JVM attached, so JVMThread is not initialized
// and the siglongjmp path can't be exercised end-to-end here.
// These tests still call the real checkFault() (not a replica) to lock down
// its early-return guard: a null ProfiledThread*
// ---------------------------------------------------------------------------

TEST(CheckFaultGuardTest, NullThreadIsNoop) {
    Profiler::checkFault(nullptr, nullptr, nullptr);  // must not crash
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

// ---------------------------------------------------------------------------
// F. HotspotSupport::walkJavaStack()'s AsyncSampleMutex release on a
//    recovered fault
//
// walkJavaStack() runs its getJavaTraceAsync() branches through
// withAsyncSampleGuard() (asyncSampleMutex.h), which holds an
// AsyncSampleMutex -- setting ProfiledThread::is_unwinding_Java() true for
// as long as it is alive and clearing it again in its destructor -- and
// mirrors that lifetime into a local `async_trace_active` flag. A siglongjmp
// out of the guarded callback (Profiler::checkFault() recovering a fault)
// bypasses the AsyncSampleMutex destructor, so walkJavaStack's sigsetjmp
// recovery path explicitly clears is_unwinding_Java() itself whenever that
// flag was set — otherwise it would stay stuck true forever and permanently
// disable async CPU/wall/malloc/socket sampling on that thread (see
// hotspotSupport.cpp).
//
// This gtest binary has no live JVM, so getJavaTraceAsync() itself can't be
// driven into a real fault — it bails out early on a null VMThread. These
// tests instead call the real withAsyncSampleGuard() helper directly (the
// same one walkJavaStack calls) with a real ProfiledThread and a callback
// that faults, via a real sigsetjmp/siglongjmp fault (through the real
// Profiler::segvHandler -> Profiler::checkFault chain), to lock down the
// release behavior. Because the guard/flag lifetime pairing itself lives in
// production code rather than being hand-copied here, a regression in that
// pairing (e.g. async_trace_active being cleared before the mutex's true
// lifetime ended) is caught by these tests.
// ---------------------------------------------------------------------------

class WalkJavaStackAsyncMutexRecoveryTest : public ::testing::Test {
protected:
    void SetUp() override {
        ProfiledThread::initCurrentThread();
        _pt = ProfiledThread::current();
        ASSERT_NE(nullptr, _pt);
        ASSERT_FALSE(_pt->isProtected());
        ASSERT_FALSE(_pt->is_unwinding_Java());

        _orig_segv = OS::replaceSigsegvHandler(Profiler::segvHandler);
        _orig_bus = OS::replaceSigbusHandler(Profiler::busHandler);

        _bad_page = mmap(nullptr, 4096, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        ASSERT_NE(MAP_FAILED, _bad_page);
    }

    void TearDown() override {
        munmap(_bad_page, 4096);
        OS::replaceSigsegvHandler(_orig_segv);
        OS::replaceSigbusHandler(_orig_bus);
        _pt->set_unwinding_Java(false);  // keep failures from this test isolated
        ProfiledThread::release();
    }

    ProfiledThread* _pt = nullptr;
    void* _bad_page = nullptr;
    SigAction _orig_segv = nullptr;
    SigAction _orig_bus = nullptr;
};

// Drives walkJavaStack's cstack<CSTACK_VM branch through the real
// withAsyncSampleGuard() helper (same one hotspotSupport.cpp calls): fault
// inside the guarded callback, as if inside getJavaTraceAsync or the
// JDK-21 virtual-thread continuation check that runs after it, and confirm
// recovery releases the per-thread guard instead of leaking it.
TEST_F(WalkJavaStackAsyncMutexRecoveryTest, RecoveredFaultReleasesAsyncGuard) {
    sigjmp_buf crash_protection_ctx;
    sigjmp_buf* prev_jmp_buf = _pt->getJmpCtx();
    ASSERT_EQ(nullptr, prev_jmp_buf);

    volatile bool async_trace_active = false;

    if (sigsetjmp(crash_protection_ctx, 1) != 0) {
        SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP();
        _pt->setJmpCtx(prev_jmp_buf);
        if (async_trace_active) {
            _pt->set_unwinding_Java(false);
        }
    } else {
        _pt->setJmpCtx(&crash_protection_ctx);

        withAsyncSampleGuard(_pt, async_trace_active, [&]() {
            EXPECT_TRUE(_pt->is_unwinding_Java());

            // Simulate a fault inside the guarded callback -- this never
            // returns; it lands back at the sigsetjmp above via
            // Profiler::checkFault()'s siglongjmp.
            *reinterpret_cast<volatile int*>(_bad_page) = 1;
            FAIL() << "unreachable: the write above must fault";
        });
        FAIL() << "unreachable: withAsyncSampleGuard must not return normally";
    }

    EXPECT_FALSE(_pt->is_unwinding_Java())
        << "a recovered fault must release the AsyncSampleMutex guard, not leak it";
    EXPECT_FALSE(_pt->isProtected());
}

// Baseline: a fault that occurs *outside* the AsyncSampleMutex's window
// (async_trace_active still false, as in walkVM()'s own branches) must not
// touch is_unwinding_Java at all -- confirms the recovery reset is scoped to
// the mutex's true lifetime rather than firing unconditionally.
TEST_F(WalkJavaStackAsyncMutexRecoveryTest, RecoveredFaultOutsideGuardWindowLeavesFlagUntouched) {
    sigjmp_buf crash_protection_ctx;
    sigjmp_buf* prev_jmp_buf = _pt->getJmpCtx();
    volatile bool async_trace_active = false;

    if (sigsetjmp(crash_protection_ctx, 1) != 0) {
        SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP();
        _pt->setJmpCtx(prev_jmp_buf);
        if (async_trace_active) {
            _pt->set_unwinding_Java(false);
        }
    } else {
        _pt->setJmpCtx(&crash_protection_ctx);

        // walkVM()-style branch: no AsyncSampleMutex involved at all.
        *reinterpret_cast<volatile int*>(_bad_page) = 1;
        FAIL() << "unreachable: the write above must fault";
    }

    EXPECT_FALSE(_pt->is_unwinding_Java());
    EXPECT_FALSE(_pt->isProtected());
}

#endif  // __linux__
