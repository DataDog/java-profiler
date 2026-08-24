/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "flightRecorder.h"
#include "counters.h"
#include "faultInjection.h"
#include "guards.h"
#include "os.h"
#include "profiler.h"
#include "safeAccess.h"
#include "threadLocalData.inline.h"
#include "gtest_crash_handler.h"

// Only meaningful in a fault-injection build (-PenableFaultInjection): that is
// the only configuration where INJECT_CRASH_LIKELY() in
// Lookup::resolveMethod() (see flightRecorder.cpp) expands to anything other
// than a no-op.
#ifdef __FAULT_INJECTION__

static constexpr char RESOLVE_METHOD_FI_TEST_NAME[] = "ResolveMethodFaultInjectionTest";

// Mirrors the real production signal chain (see Profiler::segvHandler):
// safefetch recovery first, then Profiler::checkFault() -- which, since
// resolveMethod() installs its own sigsetjmp jmp ctx on the current
// ProfiledThread, siglongjmp's straight back into resolveMethod()'s recovery
// branch -- falling back to the previous handler / gtest's crash handler for
// a fault this test did not expect.
static void (*orig_segv)(int, siginfo_t*, void*);
static void (*orig_bus)(int, siginfo_t*, void*);

static void resolveMethodFiHandler(int signo, siginfo_t* siginfo, void* context) {
  // Every installed signal handler in production opens a SIGNAL_HANDLER_GUARD_NO_SAMPLE()
  // scope (see Profiler::segvHandler/busHandler). resolveMethod()'s recovery
  // branch calls SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP() to compensate for that
  // scope's destructor being skipped by the siglongjmp out of this handler --
  // without opening the scope here first, that compensation underflows
  // ProfiledThread::_signal_depth and trips its debug assert.
  SIGNAL_HANDLER_GUARD_NO_SAMPLE();
  if (SafeAccess::handle_safefetch(signo, context)) {
    return;
  }
  Profiler::checkFault(ProfiledThread::current(), siginfo, context);  // siglongjmp if protected
  if (signo == SIGBUS && orig_bus != nullptr) {
    orig_bus(signo, siginfo, context);
  } else if (signo == SIGSEGV && orig_segv != nullptr) {
    orig_segv(signo, siginfo, context);
  } else {
    gtestCrashHandler(signo, siginfo, context, RESOLVE_METHOD_FI_TEST_NAME);
  }
}

class ResolveMethodFaultInjectionTest : public ::testing::Test {
protected:
  void SetUp() override {
    ProfiledThread::initCurrentThread();
    faultinj::init();
    orig_segv = OS::replaceSigsegvHandler(resolveMethodFiHandler);
    orig_bus = OS::replaceSigbusHandler(resolveMethodFiHandler);
  }

  void TearDown() override {
    OS::replaceSigsegvHandler(orig_segv);
    OS::replaceSigbusHandler(orig_bus);
    ProfiledThread::release();
  }
};

// resolveMethod() arms a sigsetjmp/siglongjmp window around fillMethod()
// specifically so that INJECT_CRASH_LIKELY() (a real SIGSEGV, not a poisoned
// pointer left for the caller to dereference) is recoverable: when it fires,
// control must land back at the sigsetjmp, producing the same "unknown"
// MethodInfo that a genuine resolution failure would, and the process must not
// crash.
//
// The frame is a BCI_ERROR frame carrying a plain error string. That shape is
// chosen so the call actually enters the protected window: a null method_id
// short-circuits to the shared unknown row before any protection is armed, and
// BCI_ERROR resolution needs no live JVM (it goes to fillNativeMethodInfo, not
// fillJavaMethodInfo). Both the non-injected (~99%) and injected (~1%) paths
// therefore produce a FRAME_NATIVE MethodInfo, which keeps the per-iteration
// assertions valid regardless of which path any given call took.
TEST_F(ResolveMethodFaultInjectionTest, RecoversFromInjectedCrashInsteadOfCrashing) {
  ProfiledThread* t = ProfiledThread::current();
  ASSERT_NE(t, nullptr);
  t->setFiRng(0xD15EA5EDD15EA5EDULL);

  StringDictionary classes;
  MethodMap methods;
  Lookup lookup(nullptr, &methods, &classes);

  ASGCT_CallFrame frame{};
  frame.bci = BCI_ERROR;
  frame.native_function_name = "injected_fault_test_frame";

  long long faultsBefore = Counters::getCounter(FAULTS_INJECTED);
  bool sawRecoveredInjection = false;

  // LIKELY tier fires ~1% of the time; 5000 tries makes seeing at least one
  // recovery astronomically likely without hardcoding an exact iteration.
  for (int i = 0; i < 5000; i++) {
    // Start each iteration from an empty map so the call is forced down
    // resolveMethod()'s protected slow path. Its fast path deliberately
    // short-circuits an already-marked row without arming any protection, and
    // INJECT_CRASH_LIKELY() lives inside the protected window -- so without the
    // reset only the very first iteration would ever reach the injection site.
    methods.clear();

    long long recoveredBefore =
        Counters::getCounter(METHOD_RESOLVE_LONGJMP_RECOVERED);

    MethodInfo* info = lookup.resolveMethod(frame);

    ASSERT_NE(info, nullptr);
    EXPECT_EQ(info->_type, FRAME_NATIVE);
    // Every exit path restores the jmp ctx the thread had on entry (nullptr
    // here), recovery included -- a landing pad left published would point into
    // resolveMethod()'s already-popped stack frame. Asserting it per iteration
    // covers both the success and the recovery path.
    EXPECT_FALSE(t->isProtected());

    if (Counters::getCounter(METHOD_RESOLVE_LONGJMP_RECOVERED) > recoveredBefore) {
      // The recovery path must hand back the shared unknown row, and must not
      // have touched the MethodMap: it runs with protection already disarmed, so
      // an allocating map insert there is exactly what it must avoid. The
      // injection fires ahead of the map lookup in fillMethod(), so on a
      // recovering iteration the map is still empty.
      EXPECT_EQ(info, &lookup._unknown_method);
      EXPECT_TRUE(methods.empty());
      EXPECT_NE(info->_key, 0U);  // must still be referenceable from a trace
      sawRecoveredInjection = true;
      break;
    }

    // Non-injected iteration: resolved normally into its own map row, not the
    // shared unknown one.
    EXPECT_NE(info, &lookup._unknown_method);
    EXPECT_EQ(methods.size(), 1U);
  }

  EXPECT_TRUE(sawRecoveredInjection)
      << "expected INJECT_CRASH_LIKELY() in Lookup::fillMethod() to fire "
         "and be recovered via siglongjmp within 5000 calls";
  EXPECT_GT(Counters::getCounter(FAULTS_INJECTED), faultsBefore);
}

#else  // __FAULT_INJECTION__ not defined (the default release/debug build).

// INJECT_CRASH_LIKELY() in resolveMethod() compiles to nothing here (see
// faultInjection.h), so there is nothing to inject -- this is a plain smoke
// test of the same call, kept for two reasons: (1) it documents that the
// call site is inert in this configuration, and (2) a translation unit that
// registers zero gtest tests fails to *link* as its own binary: with no
// TEST/TEST_F in this object file, nothing here pulls a member out of
// -lgtest before -lgtest_main's gtest_main.cc.o (which needs
// testing::InitGoogleTest() etc. from that same archive) is processed, and
// -lgtest is never revisited afterwards.
TEST(ResolveMethodFaultInjectionTest, DisabledBuildResolvesNormally) {
  StringDictionary classes;
  MethodMap methods;
  Lookup lookup(nullptr, &methods, &classes);

  // A null method_id short-circuits to the shared unknown row before any
  // protection is armed. That row lives outside the MethodMap
  // (Lookup::_unknown_method), so nothing is inserted for it.
  ASGCT_CallFrame unresolvable{};
  unresolvable.bci = 0;
  unresolvable.method_id = nullptr;

  MethodInfo* unknown = lookup.resolveMethod(unresolvable);
  ASSERT_NE(unknown, nullptr);
  EXPECT_EQ(unknown, &lookup._unknown_method);
  EXPECT_EQ(unknown->_type, FRAME_NATIVE);
  EXPECT_TRUE(unknown->_mark);
  EXPECT_NE(unknown->_key, 0U);  // must still be referenceable from a trace
  EXPECT_TRUE(methods.empty());

  // A BCI_ERROR frame does go through the protected slow path, so this covers
  // the sigsetjmp window itself being inert here rather than just the
  // short-circuit above.
  ASGCT_CallFrame error_frame{};
  error_frame.bci = BCI_ERROR;
  error_frame.native_function_name = "disabled_build_test_frame";

  MethodInfo* resolved = lookup.resolveMethod(error_frame);
  ASSERT_NE(resolved, nullptr);
  EXPECT_NE(resolved, &lookup._unknown_method);
  EXPECT_EQ(resolved->_type, FRAME_NATIVE);
  EXPECT_EQ(methods.size(), 1U);

  // The jmp ctx is restored on the normal path, not just on recovery.
  ProfiledThread* t = ProfiledThread::current();
  ASSERT_NE(t, nullptr);  // the protected path creates one if the thread had none
  EXPECT_FALSE(t->isProtected());
}

#endif  // __FAULT_INJECTION__
