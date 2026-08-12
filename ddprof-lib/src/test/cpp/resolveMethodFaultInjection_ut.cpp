/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "../../main/cpp/flightRecorder.h"
#include "../../main/cpp/counters.h"
#include "../../main/cpp/faultInjection.h"
#include "../../main/cpp/guards.h"
#include "../../main/cpp/os.h"
#include "../../main/cpp/profiler.h"
#include "../../main/cpp/safeAccess.h"
#include "../../main/cpp/threadLocalData.h"
#include "../../main/cpp/gtest_crash_handler.h"

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
  // Every installed signal handler in production opens a SIGNAL_HANDLER_GUARD()
  // scope (see Profiler::segvHandler/busHandler). resolveMethod()'s recovery
  // branch calls SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP() to compensate for that
  // scope's destructor being skipped by the siglongjmp out of this handler --
  // without opening the scope here first, that compensation underflows
  // ProfiledThread::_signal_depth and trips its debug assert.
  SIGNAL_HANDLER_GUARD();
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

// resolveMethod() wraps its body in a sigsetjmp/siglongjmp jmp ctx specifically
// so that INJECT_CRASH_LIKELY() (a real SIGSEGV, not a poisoned pointer left
// for the caller to dereference) is recoverable: when it fires, control must
// land back at the sigsetjmp, producing the same "unknown" MethodInfo that a
// genuine resolution failure would, and the process must not crash.
//
// The frame here has a NULL method_id and bci == 0 (not a raw-pointer bci),
// so both the non-injected (~99%) and injected-and-recovered (~1%) paths
// converge on the exact same MethodMap key/fill (see flightRecorder.cpp:
// `if (method_id == nullptr) fillNativeMethodInfo(mi, UNKNOWN, nullptr);`),
// which keeps the assertions below valid regardless of which path any given
// call took.
//
// Note: on the non-recovering (success) path resolveMethod() deliberately
// leaves the ProfiledThread's jmp ctx pointing at its own (now-popped) stack
// frame rather than restoring the caller's prior context -- each call
// re-installs a fresh one via sigsetjmp before doing anything risky, so this
// is safe, but it does mean ProfiledThread::isProtected() cannot be used
// here to distinguish a recovered call from a normal one.
TEST_F(ResolveMethodFaultInjectionTest, RecoversFromInjectedCrashInsteadOfCrashing) {
  ProfiledThread* t = ProfiledThread::current();
  ASSERT_NE(t, nullptr);
  t->setFiRng(0xD15EA5EDD15EA5EDULL);

  StringDictionary classes;
  MethodMap methods;
  Lookup lookup(nullptr, &methods, &classes);

  ASGCT_CallFrame frame{};
  frame.bci = 0;
  frame.method_id = nullptr;

  long long faultsBefore = Counters::getCounter(FAULTS_INJECTED);
  bool sawRecoveredInjection = false;

  // LIKELY tier fires ~1% of the time; 5000 tries makes seeing at least one
  // recovery astronomically likely without hardcoding an exact iteration.
  for (int i = 0; i < 5000; i++) {
    long long recoveredBefore = Counters::getCounter(STACKWALK_LONGJMP_RECOVERED);

    MethodInfo* info = lookup.resolveMethod(frame);

    ASSERT_NE(info, nullptr);
    EXPECT_EQ(info->_type, FRAME_NATIVE);

    if (Counters::getCounter(STACKWALK_LONGJMP_RECOVERED) > recoveredBefore) {
      sawRecoveredInjection = true;
      break;
    }
  }

  EXPECT_TRUE(sawRecoveredInjection)
      << "expected INJECT_CRASH_LIKELY() in Lookup::resolveMethod() to fire "
         "and be recovered via siglongjmp within 5000 calls";
  EXPECT_GT(Counters::getCounter(FAULTS_INJECTED), faultsBefore);

  // Every call -- injected-and-recovered or not -- resolves the same NULL
  // method_id frame to the single shared "unknown" MethodInfo row.
  EXPECT_EQ(methods.size(), 1U);

  // Defensive cleanup: leaving the stale post-call jmp ctx (see note above)
  // live into TearDown()/ProfiledThread::release() serves no purpose here.
  t->setJmpCtx(nullptr);
}

#endif  // __FAULT_INJECTION__
