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
 *  C2. JmpCtxScope, the RAII form of that protocol (used by
 *      HotspotSupport::resolve())
 *   F. HotspotSupport::walkJavaStack()'s AsyncSampleMutex release on a
 *      recovered fault
 *   G. HotspotSupport::walkJavaStack()'s ucontext restore on a recovered
 *      fault
 */

#include <gtest/gtest.h>
#include "threadLocalData.inline.h"
#include "profiler.h"

#include "asyncSampleMutex.h"
#include "guards.h"
#include "jvmThread.h"
#include "safeAccess.h"
#include "os.h"
#include "stackFrame.h"
#include "hotspot/hotspotSupport.h"
// HotspotStackFrame::RegisterSnapshot::restore() (constructed inside
// withUcontextFaultRecovery(), instantiated here) conditionally calls
// VMJavaFrameAnchor::setLastJavaPC(), which is inline in vmStructs.h but
// bottoms out in VMStructs::at()/crashProtectionActive(), defined in
// vmStructs.inline.h. Without this include, assertion-enabled builds (the
// gtest targets) leave those symbols unresolved at link time -- see the same
// note in hotspotStackFrame_aarch64.cpp.
#include "hotspot/vmStructs.inline.h"

#ifdef __linux__

#include <cstring>
#include <sys/mman.h>
#include <unistd.h>

// Test-only friend accessor for VMStructs' protected static offsets (see the
// `friend class VMStructsTestAccessor;` declaration in vmStructs.h) -- lets
// FaultInsideProfilerRangeRecoversAndRestoresJavaThreadAnchor below fake a
// VMJavaFrameAnchor layout without a live JVM. Mirrors the same-named
// accessor already used for this purpose in hotspotMethodId_ut.cpp -- each
// is a separate translation-unit-local definition; friendship is granted by
// name+scope, not by a single shared type.
class VMStructsTestAccessor {
public:
    static offset getAnchorPcOffset() { return VMStructs::_anchor_pc_offset; }
    static void setAnchorPcOffset(offset value) { VMStructs::_anchor_pc_offset = value; }
};

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
// C2. JmpCtxScope — the RAII form of the protocol section C tests by hand.
//
// HotspotSupport::resolve() uses it; walkVM/walkJavaStack/walkFP/walkDwarf still
// hand-roll the same save/install/restore. These tests assert the guard
// reproduces that protocol store-for-store, which is what makes migrating those
// four call sites a mechanical change rather than a risky one.
//
// The class's members are both const by design (guards.h): they are initialised
// before the owning frame calls sigsetjmp() and are never written afterwards, so
// reading them from a landing pad is well defined -- unlike a plain non-volatile
// local assigned in between, whose value after siglongjmp is indeterminate.
// ---------------------------------------------------------------------------

// Construction only snapshots the current landing pad; it must not arm anything.
TEST_F(JmpCtxChainingTest, JmpCtxScopeCtorDoesNotInstall) {
    sigjmp_buf ctx;
    {
        JmpCtxScope scope(_pt);
        EXPECT_FALSE(_pt->isProtected());
        EXPECT_EQ(nullptr, _pt->getJmpCtx());
        scope.install(&ctx);
        EXPECT_EQ(&ctx, _pt->getJmpCtx());
    }
    EXPECT_FALSE(_pt->isProtected());
}

// The whole point of the guard: scope exit reinstates the previous context even
// though no explicit restore() call was written.
TEST_F(JmpCtxChainingTest, JmpCtxScopeExitRestoresWithoutExplicitCall) {
    sigjmp_buf outer;
    _pt->setJmpCtx(&outer);

    {
        sigjmp_buf inner;
        JmpCtxScope scope(_pt);
        scope.install(&inner);
        EXPECT_EQ(&inner, _pt->getJmpCtx());
    }

    EXPECT_EQ(&outer, _pt->getJmpCtx());
    _pt->setJmpCtx(nullptr);
}

// restore() and the destructor must be interchangeable and safe to run in
// sequence: _prev is const, so both make the identical store.
TEST_F(JmpCtxChainingTest, JmpCtxScopeRestoreThenDtorIsIdempotent) {
    sigjmp_buf outer;
    _pt->setJmpCtx(&outer);

    {
        sigjmp_buf inner;
        JmpCtxScope scope(_pt);
        scope.install(&inner);
        scope.restore();
        EXPECT_EQ(&outer, _pt->getJmpCtx());
        scope.restore();  // explicitly redundant
        EXPECT_EQ(&outer, _pt->getJmpCtx());
    }  // destructor makes the same store a third time

    EXPECT_EQ(&outer, _pt->getJmpCtx());
    _pt->setJmpCtx(nullptr);
}

// Nested scopes must unwind strictly LIFO, each handing back exactly the context
// that was live when it was constructed.
TEST_F(JmpCtxChainingTest, JmpCtxScopeNestedScopesUnwindLIFO) {
    sigjmp_buf outer_ctx;
    sigjmp_buf inner_ctx;

    {
        JmpCtxScope outer(_pt);
        outer.install(&outer_ctx);
        EXPECT_EQ(&outer_ctx, _pt->getJmpCtx());

        {
            JmpCtxScope inner(_pt);
            inner.install(&inner_ctx);
            EXPECT_EQ(&inner_ctx, _pt->getJmpCtx());
        }

        EXPECT_EQ(&outer_ctx, _pt->getJmpCtx())
            << "inner scope must hand the outer's context back";
    }

    EXPECT_FALSE(_pt->isProtected());
}

// Real sigsetjmp/siglongjmp: the RAII port of
// FaultInInnerFrameDoesNotDisturbOuterFrame above.
TEST_F(JmpCtxChainingTest, JmpCtxScopeFaultInInnerScopeDoesNotDisturbOuter) {
    sigjmp_buf outer_ctx;
    int outer_landed = 0;
    int inner_landed = 0;

    JmpCtxScope outer_scope(_pt);
    if (sigsetjmp(outer_ctx, 1) != 0) {
        outer_landed++;
        outer_scope.restore();
    } else {
        outer_scope.install(&outer_ctx);

        // --- inner protected call, interrupted mid-flight by a fault ---
        {
            sigjmp_buf inner_ctx;
            JmpCtxScope inner_scope(_pt);
            if (sigsetjmp(inner_ctx, 1) != 0) {
                inner_landed++;
                inner_scope.restore();
            } else {
                inner_scope.install(&inner_ctx);
                // Simulate checkFault(): siglongjmp through whatever is
                // installed. This must land in the inner frame, not the outer.
                siglongjmp(*_pt->getJmpCtx(), 1);
                FAIL() << "unreachable: siglongjmp does not return";
            }
        }

        EXPECT_EQ(&outer_ctx, _pt->getJmpCtx())
            << "outer frame's context must survive the inner frame's fault";
        outer_scope.restore();
    }

    EXPECT_EQ(1, inner_landed);
    EXPECT_EQ(0, outer_landed) << "the fault must not have unwound past the inner frame";
    EXPECT_FALSE(_pt->isProtected());
}

// The failure mode the guard exists to prevent: a landing pad that forgets to
// disarm. checkFault() would happily jump into a landing pad whose frame has
// already been popped, so the destructor must cover the omission.
TEST_F(JmpCtxChainingTest, JmpCtxScopeDestructorAloneRestoresAfterLongjmp) {
    sigjmp_buf outer;
    _pt->setJmpCtx(&outer);
    int landed = 0;

    {
        sigjmp_buf ctx;
        JmpCtxScope scope(_pt);
        if (sigsetjmp(ctx, 1) != 0) {
            landed++;
            // Deliberately no scope.restore() here.
        } else {
            scope.install(&ctx);
            siglongjmp(*_pt->getJmpCtx(), 1);
            FAIL() << "unreachable: siglongjmp does not return";
        }
    }

    EXPECT_EQ(1, landed);
    EXPECT_EQ(&outer, _pt->getJmpCtx())
        << "destructor must disarm even when the landing pad did not";
    _pt->setJmpCtx(nullptr);
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
// G. HotspotSupport::withUcontextFaultRecovery()'s ucontext restore on a
//    recovered fault -- the crash-protection wrapper walkJavaStack() uses
//    around getJavaTraceAsync()
//
// getJavaTraceAsync() mutates the real signal ucontext's pc/sp/fp in place --
// StackFrame::pc()/sp()/fp() are references straight into uc_mcontext -- while
// probing AsyncGetCallTrace (e.g. the PROBE_SP retry loop's `frame.sp() +=
// sizeof(void*)`, or unwindStub()/unwindCompiled() writing pc()/sp()/fp() by
// reference), and restores them itself on every normal-exit path. But a
// SIGSEGV that strikes mid-mutation is caught by checkFault(), which
// siglongjmp's straight past those restores to withUcontextFaultRecovery()'s
// sigsetjmp. Since this ucontext is the exact one the kernel uses to resume
// the sampled thread when the signal handler returns, withUcontextFaultRecovery()
// snapshots it before running the protected work and restores it again in the
// recovery branch -- otherwise a fault mid-walk would leave the sampled
// thread's real register state corrupted for sigreturn.
//
// These tests call HotspotSupport::withUcontextFaultRecovery() directly --
// the exact function walkJavaStack() delegates to -- rather than replicating
// its sigsetjmp/restore protocol by hand: walkJavaStack() itself can't be
// invoked here (this gtest binary has no live JVM, and its dispatch asserts
// VM::isHotspot() / dereferences VMThread state), but the fault-recovery
// wrapper it calls has no such dependency, so calling it directly means a
// regression to the real recovery branch (e.g. dropping its ctx_snapshot.
// restore() call) fails these tests too, instead of only a hand-rolled copy
// of the same logic.
//
// Recovery is driven through the REAL Profiler::checkFault() -- not a
// simulated siglongjmp -- so its `pc < min || pc >= max` address-range gate
// (profiler_min_address/_max_address, see stackWalker_ut.cpp's
// StackWalkerCrashRecoveryTest for the same pattern) is exercised for real.
// That gate matters here specifically: a fault raised while HotSpot's own
// AsyncGetCallTrace (libjvm.so) dereferences a poisoned sp/pc/fp has its
// faulting instruction *inside libjvm.so*, not inside this library, so
// checkFault() correctly refuses to recover it -- which means
// withUcontextFaultRecovery()'s restore is never reached, and the mutated
// ucontext stays corrupted. SetUp() installs a real range via the
// UNIT_TEST-only Profiler::setAddressRangeForTest() so both sides of that
// gate -- recovered (pc inside range) and rejected (pc outside range) -- are
// exercised, rather than only the "always recovers" path.
//
// Only FaultInsideProfilerRangeRecoversAndRestoresUcontext below actually
// pins withUcontextFaultRecovery()'s own recovery branch (its sigsetjmp,
// JmpCtxScope, RegisterSnapshot and set_unwinding_Java restore all run on
// that path). FaultOutsideProfilerRangeIsNotRecoveredAndLeavesUcontextCorrupted
// is a negative control for checkFault()'s range gate, not regression
// coverage for the wrapper: on that path checkFault() never siglongjmps, so
// `work()` just runs to completion and withUcontextFaultRecovery() falls
// straight through to `return work(ctx_snapshot);` -- every assertion in
// that test would still pass if the wrapper's own sigsetjmp/JmpCtxScope/
// RegisterSnapshot/set_unwinding_Java logic were deleted entirely.
// ---------------------------------------------------------------------------

class WalkJavaStackUcontextRestoreTest : public ::testing::Test {
protected:
    // Comfortably covers walkJavaStack's own compiled body in any build
    // config, while remaining far smaller than the 256MB offset used below
    // to land clearly outside the range.
    static constexpr uintptr_t kRangeMargin = 256 * 1024;

    void SetUp() override {
        ProfiledThread::initCurrentThread();
        _pt = ProfiledThread::current();
        ASSERT_NE(nullptr, _pt);

        uintptr_t self_pc = reinterpret_cast<uintptr_t>(&HotspotSupport::walkJavaStack);
        _range_lo = self_pc - kRangeMargin;
        _range_hi = self_pc + kRangeMargin;
        Profiler::setAddressRangeForTest(_range_lo, _range_hi);

        // Zero-initialized rather than populated via getcontext() -- musl
        // doesn't provide getcontext(), and this test only round-trips
        // arbitrary values through StackFrame::pc()/sp()/fp() (references
        // into uc_mcontext), so a real, live context is unnecessary here.
        _ctx = ucontext_t{};

        // Seed with distinct non-zero values so the restore assertions below
        // are actually exercised. A zeroed ucontext makes fp's mutation
        // (`frame.fp() = saved_sp`, mirroring getJavaTraceAsync) a no-op --
        // saved_sp is 0, same as fp's own untouched value -- so a broken
        // restore()/no-restore-at-all would pass EXPECT_EQ(saved_fp,
        // frame.fp()) by coincidence rather than by actually restoring.
        StackFrame seed(&_ctx);
        seed.pc() = 0xAAAA1000;
        seed.sp() = 0xBBBB2000;
        seed.fp() = 0xCCCC3000;
    }

    void TearDown() override {
        Profiler::resetAddressRangeForTest();
        ProfiledThread::release();
    }

    ProfiledThread* _pt = nullptr;
    ucontext_t _ctx;
    uintptr_t _range_lo = 0;
    uintptr_t _range_hi = 0;
};

// Drives HotspotSupport::withUcontextFaultRecovery() -- the real production
// function, not a replica -- with `work` mutating the ucontext mid-"walk" the
// way getJavaTraceAsync does, then taking a fault whose own faulting
// instruction lands inside this library (e.g. a direct dereference of the
// poisoned sp, as walkVM's existing INJECT_FAULT_ADDRESS_UNLIKELY sites do)
// -- so checkFault() must recover. The recovery branch's ctx_snapshot.
// restore() must undo the mutation -- if that call were ever dropped (the bug
// this fixes), the EXPECT_EQ calls below would see the corrupted values
// instead, because they're reading back through the very ucontext
// withUcontextFaultRecovery() owns.
TEST_F(WalkJavaStackUcontextRestoreTest, FaultInsideProfilerRangeRecoversAndRestoresUcontext) {
    StackFrame frame(&_ctx);
    uintptr_t saved_pc = frame.pc();
    uintptr_t saved_sp = frame.sp();
    uintptr_t saved_fp = frame.fp();
    bool truncated = false;
    volatile int partial = 0;

    int result = HotspotSupport::withUcontextFaultRecovery(&_ctx, _pt, &truncated, partial, [&](HotspotStackFrame::RegisterSnapshot&) {
        // Simulate getJavaTraceAsync() mutating the real ucontext mid-walk
        // (PROBE_SP loop / unwindStub / unwindCompiled all write pc()/sp()/
        // fp() directly).
        frame.sp() += sizeof(void*);
        frame.fp() = saved_sp;
        frame.pc() = saved_pc + 0x1234;

        // The SIGSEGV's own delivery ucontext -- a distinct object from
        // _ctx above -- whose faulting pc sits inside the installed range.
        ucontext_t fault_uc{};
        StackFrame(&fault_uc).pc() = _range_lo + kRangeMargin;

        siginfo_t si{};
        si.si_addr = reinterpret_cast<void*>(1);
        // A real SIGSEGV delivery enters this via segvHandler's
        // SignalHandlerScope before reaching checkFault(); calling checkFault()
        // directly (no real fault, deterministic pc) means mimicking that
        // entry ourselves, so SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP()'s
        // compensating exitSignalScope() -- run inside the recovery branch
        // below -- has a matching enter to unwind instead of underflowing.
        _pt->enterSignalScope();
        Profiler::checkFault(_pt, &si, &fault_uc);
        ADD_FAILURE() << "unreachable: checkFault() must siglongjmp for an in-range pc";
    });

    EXPECT_EQ(0, result);
    EXPECT_TRUE(truncated);
    EXPECT_EQ(saved_pc, frame.pc());
    EXPECT_EQ(saved_sp, frame.sp());
    EXPECT_EQ(saved_fp, frame.fp());
    EXPECT_FALSE(_pt->isProtected());
}

// withUcontextFaultRecovery()'s recovery branch returns `partial_result`
// (hotspotSupport.h), not a hardcoded 0 -- the whole point being that a fault
// *after* `work` has already committed some progress (e.g. getJavaTraceAsync
// filling in frames before a later PROBE_SP-loop fault) must surface as a
// truncated-but-valid count, not get discarded. Every test above leaves
// `partial` at its initial 0 for the whole call, so a regression that
// hardcoded `return 0;` in the recovery branch instead of
// `return partial_result;` would still pass all of them. Set it to a
// distinguishing non-zero value before faulting to actually pin the
// read-back this parameter exists for.
TEST_F(WalkJavaStackUcontextRestoreTest, FaultInsideProfilerRangeRecoversAndPreservesPartialResult) {
    bool truncated = false;
    volatile int partial = 0;

    int result = HotspotSupport::withUcontextFaultRecovery(&_ctx, _pt, &truncated, partial, [&](HotspotStackFrame::RegisterSnapshot&) {
        // Stand in for getJavaTraceAsync() having already committed 3 frames
        // to the output buffer before a later fault (e.g. inside the
        // PROBE_SP retry loop) -- the recovery branch must read this back.
        partial = 3;

        // The SIGSEGV's own delivery ucontext -- a distinct object from
        // _ctx above -- whose faulting pc sits inside the installed range.
        ucontext_t fault_uc{};
        StackFrame(&fault_uc).pc() = _range_lo + kRangeMargin;

        siginfo_t si{};
        si.si_addr = reinterpret_cast<void*>(1);
        // See the matching comment in FaultInsideProfilerRangeRecoversAndRestoresUcontext.
        _pt->enterSignalScope();
        Profiler::checkFault(_pt, &si, &fault_uc);
        ADD_FAILURE() << "unreachable: checkFault() must siglongjmp for an in-range pc";
    });

    EXPECT_EQ(3, result)
        << "a recovered fault must return the partial progress work() already "
           "committed, not discard it back to 0";
    EXPECT_TRUE(truncated);
    EXPECT_FALSE(_pt->isProtected());
}

// The anchor-restore counterpart of the pc/sp/fp test above: getJavaTraceAsync()'s
// ticks_unknown_not_Java branch also mutates the real JavaThread's
// VMJavaFrameAnchor (anchor->setLastJavaPC()) via ctx_snapshot.saveJavaAnchor(),
// and HotspotStackFrame::RegisterSnapshot::restore() must undo that mutation too
// on a recovered fault -- the test above never calls saveJavaAnchor(), so it
// exercises only the base StackFrame::RegisterSnapshot half of restore(), not
// the derived anchor-restore branch.
//
// This gtest binary has no live JVM, so VMStructs::_anchor_pc_offset (and every
// other vmStructs offset) is never resolved -- it stays at its unresolved
// default of -1. A fake VMJavaFrameAnchor is built by pointing that offset at 0
// and reinterpreting a local pointer-sized variable's address as the
// "anchor": VMJavaFrameAnchor has no data members of its own (only static
// vmStructs offsets), so its accessors are pure pointer arithmetic over
// whatever memory they're pointed at -- the same "view over raw memory, never
// actually constructed" contract every VMStructs-derived type in this codebase
// relies on (see cast_to<T>()).
TEST_F(WalkJavaStackUcontextRestoreTest, FaultInsideProfilerRangeRecoversAndRestoresJavaThreadAnchor) {
    struct RestoreAnchorPcOffset {
        offset saved = VMStructsTestAccessor::getAnchorPcOffset();
        ~RestoreAnchorPcOffset() { VMStructsTestAccessor::setAnchorPcOffset(saved); }
    } restore_anchor_pc_offset;
    VMStructsTestAccessor::setAnchorPcOffset(0);

    const void* original_pc = reinterpret_cast<const void*>(0x1111);
    const void* fake_anchor_storage = original_pc;
    VMJavaFrameAnchor* anchor = reinterpret_cast<VMJavaFrameAnchor*>(&fake_anchor_storage);

    bool truncated = false;
    volatile int partial = 0;

    int result = HotspotSupport::withUcontextFaultRecovery(&_ctx, _pt, &truncated, partial, [&](HotspotStackFrame::RegisterSnapshot& ctx_snapshot) {
        // Mirrors getJavaTraceAsync()'s ticks_unknown_not_Java branch: capture
        // the anchor's pre-mutation pc via saveJavaAnchor() before patching
        // it to a new value (hotspotSupport.cpp:1176/1183).
        ctx_snapshot.saveJavaAnchor(anchor, original_pc);
        anchor->setLastJavaPC(reinterpret_cast<const void*>(0xDEAD1234));
        EXPECT_EQ(reinterpret_cast<const void*>(0xDEAD1234), anchor->lastJavaPC())
            << "setLastJavaPC() itself must have taken effect before the fault, "
               "otherwise the restore assertion below would hold trivially";

        // The SIGSEGV's own delivery ucontext -- a distinct object from _ctx
        // above -- whose faulting pc sits inside the installed range.
        ucontext_t fault_uc{};
        StackFrame(&fault_uc).pc() = _range_lo + kRangeMargin;

        siginfo_t si{};
        si.si_addr = reinterpret_cast<void*>(1);
        // See the matching comment in FaultInsideProfilerRangeRecoversAndRestoresUcontext.
        _pt->enterSignalScope();
        Profiler::checkFault(_pt, &si, &fault_uc);
        ADD_FAILURE() << "unreachable: checkFault() must siglongjmp for an in-range pc";
    });

    EXPECT_EQ(0, result);
    EXPECT_TRUE(truncated);
    EXPECT_EQ(original_pc, anchor->lastJavaPC())
        << "a recovered fault must restore the JavaThread anchor's lastJavaPC "
           "to what it was before saveJavaAnchor() captured it, not leave it "
           "at the value setLastJavaPC() patched in mid-walk";
    EXPECT_FALSE(_pt->isProtected());
}

// A negative control for checkFault()'s address-range gate, not for
// withUcontextFaultRecovery() itself: a fault whose instruction pointer falls
// OUTSIDE the profiler's own range -- standing in for a fault raised deep
// inside libjvm.so while AsyncGetCallTrace dereferences a poisoned sp/pc/fp
// (see getJavaTraceAsync's anchor-derived fault-injection site) -- must not be
// recovered by checkFault(). On this path checkFault() never siglongjmps, so
// `work()` simply runs to completion, and withUcontextFaultRecovery() returns
// whatever `partial` (below) was last set to through its normal-completion
// path (hotspotSupport.h's `return partial_result;` after `work(ctx_snapshot)`),
// not its sigsetjmp recovery branch -- proving the range gate actually
// distinguishes the two cases rather than always recovering (which is what
// makes FaultInsideProfilerRangeRecoversAndRestoresUcontext's "recovered"
// result meaningful).
//
// Either way, though, `ctx_snapshot` is a local of withUcontextFaultRecovery
// itself, and RegisterSnapshot's destructor unconditionally calls restore()
// on scope exit -- so by the time withUcontextFaultRecovery returns here, the
// mutation `work()` made has already been undone regardless of which of its
// two return statements ran. That's a stronger guarantee than "the recovery
// branch remembers to call restore()": it also covers this unrecovered path,
// and any future exit from `work()` that forgets to restore explicitly. See
// the suite-level comment above for the test that exercises the recovery
// branch itself.
TEST_F(WalkJavaStackUcontextRestoreTest, FaultOutsideProfilerRangeIsNotRecoveredButUcontextIsStillRestored) {
    StackFrame frame(&_ctx);
    uintptr_t saved_pc = frame.pc();
    uintptr_t saved_sp = frame.sp();
    uintptr_t saved_fp = frame.fp();
    bool truncated = false;
    uintptr_t mutated_pc = 0, mutated_sp = 0, mutated_fp = 0;
    volatile int partial = 0;

    int result = HotspotSupport::withUcontextFaultRecovery(&_ctx, _pt, &truncated, partial, [&](HotspotStackFrame::RegisterSnapshot&) {
        // Same mutation getJavaTraceAsync() performs right before handing
        // sp/pc/fp to jvmAsyncGetCallTrace().
        frame.sp() += sizeof(void*);
        frame.fp() = saved_sp;
        frame.pc() = saved_pc + 0x1234;

        mutated_pc = frame.pc();
        mutated_sp = frame.sp();
        mutated_fp = frame.fp();

        // The SIGSEGV's own delivery ucontext, standing in for a fault
        // inside libjvm.so -- its pc sits 256MB past the installed range,
        // far beyond kRangeMargin regardless of build config.
        ucontext_t fault_uc{};
        StackFrame(&fault_uc).pc() = _range_hi + (256u * 1024 * 1024);

        siginfo_t si{};
        si.si_addr = reinterpret_cast<void*>(1);
        Profiler::checkFault(_pt, &si, &fault_uc);
        // Falls through: checkFault must not recover a pc outside the range.
        partial = 42;  // sentinel proving work() ran to completion, unrecovered
    });

    EXPECT_EQ(42, result) << "checkFault must not have recovered an out-of-range fault";
    EXPECT_FALSE(truncated);
    // Sanity: the mutation above actually took effect before ctx_snapshot's
    // destructor could undo it.
    EXPECT_NE(saved_pc, mutated_pc);
    EXPECT_NE(saved_sp, mutated_sp);
    EXPECT_NE(saved_fp, mutated_fp);
    EXPECT_EQ(saved_pc, frame.pc())
        << "ctx_snapshot's destructor restores the ucontext when "
           "withUcontextFaultRecovery returns, even on this unrecovered path";
    EXPECT_EQ(saved_sp, frame.sp());
    EXPECT_EQ(saved_fp, frame.fp());
    EXPECT_FALSE(_pt->isProtected());
}

// withUcontextFaultRecovery() must not dereference a null ucontext in its
// recovery branch, since ucontext can legitimately be null (e.g. malloc/
// socket hooks sampled outside any signal context).
TEST_F(WalkJavaStackUcontextRestoreTest, NullUcontextSkipsRestoreWithoutCrashing) {
    bool truncated = false;
    volatile int partial = 0;

    int result = HotspotSupport::withUcontextFaultRecovery(nullptr, _pt, &truncated, partial, [&](HotspotStackFrame::RegisterSnapshot&) {
        // A fault whose pc is inside the installed range, same as the
        // "recovers" test above, but with a null ucontext -- the recovery
        // branch's ctx_snapshot.restore() must be a safe no-op here rather
        // than dereferencing a null StackFrame.
        ucontext_t fault_uc{};
        StackFrame(&fault_uc).pc() = _range_lo + kRangeMargin;

        siginfo_t si{};
        si.si_addr = reinterpret_cast<void*>(1);
        // See the matching comment in FaultInsideProfilerRangeRecoversAndRestoresUcontext.
        _pt->enterSignalScope();
        Profiler::checkFault(_pt, &si, &fault_uc);
        ADD_FAILURE() << "unreachable: checkFault() must siglongjmp for an in-range pc";
    });

    EXPECT_EQ(0, result);
    EXPECT_TRUE(truncated);
    EXPECT_FALSE(_pt->isProtected());
}

#endif  // __linux__
