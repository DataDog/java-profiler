/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <csetjmp>
#include <cstdint>
#include <signal.h>
#include <sys/mman.h>
#include <unistd.h>

#include "counters.h"
#include "faultInjection.h"
#include "safeAccess.h"
#include "os.h"
#include "threadLocalData.h"
#include "profiler.h"
#include "../../main/cpp/gtest_crash_handler.h"

static constexpr char FAULT_INJECTION_TEST_NAME[] = "FaultInjectionTest";

// ---------------------------------------------------------------------------
// (a) Disabled build: every macro must be a strict identity. Compiled only when
// the flag is absent (the default gtest / CI build). This is the guard that
// protects production from any behavioural change.
// ---------------------------------------------------------------------------
#ifndef __FAULT_INJECTION__

TEST(FaultInjectionTest, DisabledAddressMacrosAreIdentity) {
  void* p = reinterpret_cast<void*>(0xCAFEBABE);
  const char* cp = reinterpret_cast<const char*>(0x1234);
  uintptr_t up = 0xDEAD;
  EXPECT_EQ(INJECT_FAULT_ADDRESS_RARE(p), p);
  EXPECT_EQ(INJECT_FAULT_ADDRESS_UNLIKELY(cp), cp);
  EXPECT_EQ(INJECT_FAULT_ADDRESS_LIKELY(up), up);
  // Type is preserved: assigning back to the original type must compile.
  void* p2 = INJECT_FAULT_ADDRESS_LIKELY(p);
  EXPECT_EQ(p2, p);
}

TEST(FaultInjectionTest, DisabledValueMacrosAreIdentity) {
  int32_t i = 42;
  int64_t l = 0x1122334455667788LL;
  EXPECT_EQ(INJECT_FAULT_INT_RARE(i), i);
  EXPECT_EQ(INJECT_FAULT_INT_UNLIKELY(i), i);
  EXPECT_EQ(INJECT_FAULT_INT_LIKELY(i), i);
  EXPECT_EQ(INJECT_FAULT_LONG_RARE(l), l);
  EXPECT_EQ(INJECT_FAULT_LONG_UNLIKELY(l), l);
  EXPECT_EQ(INJECT_FAULT_LONG_LIKELY(l), l);

  // BOOL must be identity both ways -- an accidental non-identity expansion
  // (e.g. always forcing false) would otherwise only show up as a silent
  // behavioural change in a production build, never a compile error.
  bool t = true;
  bool f = false;
  EXPECT_EQ(INJECT_FAULT_BOOL_RARE(t), t);
  EXPECT_EQ(INJECT_FAULT_BOOL_UNLIKELY(t), t);
  EXPECT_EQ(INJECT_FAULT_BOOL_LIKELY(t), t);
  EXPECT_EQ(INJECT_FAULT_BOOL_RARE(f), f);
  EXPECT_EQ(INJECT_FAULT_BOOL_UNLIKELY(f), f);
  EXPECT_EQ(INJECT_FAULT_BOOL_LIKELY(f), f);
}

#else  // __FAULT_INJECTION__ enabled (built under -PenableFaultInjection)

// Chain: safefetch recovery first, then walkVM sigsetjmp/siglongjmp recovery, then
// the crash handler as a last resort so a genuine bug still produces a report.
static void (*orig_segvHandler)(int, siginfo_t*, void*);
static void (*orig_busHandler)(int, siginfo_t*, void*);

static void fi_signal_wrapper(int signo, siginfo_t* siginfo, void* context) {
  if (SafeAccess::handle_safefetch(signo, context)) {
    return;  // safefetch load recovered; PC already rewritten to _cont.
  }
  Profiler::checkFault(ProfiledThread::current(), siginfo, context);  // siglongjmp if protected
  // Not protected and not a safefetch fault — real crash.
  if (signo == SIGBUS && orig_busHandler != nullptr) {
    orig_busHandler(signo, siginfo, context);
  } else if (signo == SIGSEGV && orig_segvHandler != nullptr) {
    orig_segvHandler(signo, siginfo, context);
  } else {
    gtestCrashHandler(signo, siginfo, context, FAULT_INJECTION_TEST_NAME);
  }
}

class FaultInjectionTest : public ::testing::Test {
protected:
  void SetUp() override {
    ProfiledThread::initCurrentThread();
    faultinj::init();
    orig_segvHandler = OS::replaceSigsegvHandler(fi_signal_wrapper);
    orig_busHandler = OS::replaceSigbusHandler(fi_signal_wrapper);
  }
  void TearDown() override {
    OS::replaceSigsegvHandler(orig_segvHandler);
    OS::replaceSigbusHandler(orig_busHandler);
    ProfiledThread::release();
  }
};

// (b) The empirical firing rate is within a wide band of the nominal tier rate.
// Wide bounds ([0.3x, 3x]) + a fixed seed keep it deterministic and non-flaky.
static void expectRateInBand(u64 threshold, size_t n, double nominal) {
  ProfiledThread::current()->setFiRng(0x0123456789ABCDEFULL);
  size_t fires = 0;
  for (size_t i = 0; i < n; i++) {
    if (faultinj::shouldFire(threshold, "rateProbe")) {
      fires++;
    }
  }
  double expected = nominal * (double)n;
  EXPECT_GT((double)fires, 0.3 * expected)
      << "fired " << fires << " of " << n << ", expected ~" << expected;
  EXPECT_LT((double)fires, 3.0 * expected)
      << "fired " << fires << " of " << n << ", expected ~" << expected;
}

TEST_F(FaultInjectionTest, LikelyTierRate) {
  expectRateInBand(faultinj::PROB_LIKELY, 200000, 1e-2);    // ~2000 fires
}
TEST_F(FaultInjectionTest, UnlikelyTierRate) {
  expectRateInBand(faultinj::PROB_UNLIKELY, 2000000, 1e-3); // ~2000 fires
}
TEST_F(FaultInjectionTest, RareTierRate) {
  expectRateInBand(faultinj::PROB_RARE, 20000000, 1e-4);    // ~2000 fires
}

// poisonAddress() must always yield a fault-inducing, word-aligned address.
TEST_F(FaultInjectionTest, PoisonAddressIsAlignedAndUnmapped) {
  ProfiledThread::current()->setFiRng(0xF00DF00DF00DF00DULL);
  for (int i = 0; i < 1000; i++) {
    uintptr_t bad = faultinj::poisonAddress();
    EXPECT_EQ(bad & (sizeof(void*) - 1), 0u) << "poison address not word-aligned";
    // Reading it via SafeAccess must fault-and-recover, never return readable data.
    void* got = SafeAccess::load(reinterpret_cast<void**>(bad), (void*)-1);
    EXPECT_EQ(got, (void*)-1) << "poison address was unexpectedly readable";
  }
}

// (c1) SafeAccess path: injecting a poison pointer into SafeAccess::load must be
// absorbed by the safefetch handler — it returns the default and never crashes.
TEST_F(FaultInjectionTest, SafeAccessRecoversFromInjectedFault) {
  void* real = reinterpret_cast<void*>(0xABCDEF00);
  void** valid = &real;
  ProfiledThread::current()->setFiRng(0xBEEFCAFEBEEFCAFEULL);
  size_t fired = 0;
  for (int i = 0; i < 200000; i++) {
    // LIKELY tier: some iterations poison the address, others read `valid`.
    void* got = SafeAccess::load(INJECT_FAULT_ADDRESS_LIKELY(valid), nullptr);
    ASSERT_TRUE(got == real || got == nullptr) << "unexpected value " << got;
    if (got == nullptr) {
      fired++;  // a poison address was injected and safefetch recovered.
    }
  }
  EXPECT_GT(fired, 0u) << "expected at least one injected fault to be recovered";
}

// (c2) walkVM path: a raw dereference of an injected poison pointer must be
// caught by the sigsetjmp/siglongjmp crash protection, returning control to sigsetjmp.
TEST_F(FaultInjectionTest, WalkVmSigsetjmpRecoversFromInjectedFault) {
  ProfiledThread* t = ProfiledThread::current();
  ASSERT_NE(t, nullptr);

  uintptr_t real_slot = 0;             // a valid, readable pointer slot
  uintptr_t base = (uintptr_t)&real_slot;
  volatile bool recovered = false;
  volatile size_t reads = 0;
  volatile size_t faults = 0;

  sigjmp_buf ctx;
  if (sigsetjmp(ctx, 1) != 0) {
    recovered = true;                  // returned here via checkFault -> siglongjmp
    faults++;
  }
  t->setJmpCtx(&ctx);
  t->setFiRng(0xD00DFEEDD00DFEEDULL);

  // Force at least one fire deterministically, then let the tier drive the rest.
  for (int i = 0; i < 5000 && faults == 0; i++) {
    // Raw deref of the (possibly poisoned) base — mirrors walkVM's raw reads.
    uintptr_t v = *(uintptr_t*)INJECT_FAULT_ADDRESS_LIKELY(base);
    // Optimization barrier: tell the compiler `v` is read/write and clobber memory to prevent
    // reordering/optimizing away the load.
    asm volatile("" : "+r"(v) : : "memory");
    reads++;
  }
  t->setJmpCtx(nullptr);

  // We should have observed a recovered fault, or the loop completed cleanly. The
  // essential assertion is that the process did not die and, when a fault was
  // injected, sigsetjmp regained control.
  EXPECT_GT(faults, 0u) << "expected at least one injected fault to siglongjmp-recover";
  EXPECT_TRUE(recovered);
  SUCCEED();
}

// Friend of Profiler (see profiler.h) — lets this test force the internal
// state to a known value so checkState() can be exercised deterministically
// (matches the pattern in jvmSupport_ut.cpp).
class ProfilerTestAccessor {
public:
  static void setState(Profiler* p, State s) {
    p->_state.store(s, std::memory_order_release);
  }
  static State getState(Profiler* p) {
    return p->_state.load(std::memory_order_acquire);
  }
};

// Friend of VM (see vmEntry.h) — lets this test install a mock jvmtiEnv, the
// same seam jvmSupport_ut.cpp uses. checkState() (below) checks
// prewarmUnwinder() before JVMSupport::initialize(), so the injected-failure
// path never touches this at all; it exists only so the ~99% non-injected
// iterations, which do fall through into JVMSupport::initialize(), fail
// gracefully instead of crashing on a null VM::_jvmti in this no-live-JVM
// binary. Unlike a JVMThread-level fake (which would permanently flip
// JVMThread::isInitialized() for the rest of the process, since ThreadLocal
// pthread keys are never invalidated), this is a plain pointer swap that
// ScopedJvmtiMock restores on scope exit -- no state leaks into later tests.
class VMTestAccessor {
public:
  static jvmtiEnv* getJvmti() { return VM::_jvmti; }
  static void setJvmti(jvmtiEnv* env) { VM::_jvmti = env; }
};

static jvmtiError JNICALL mock_GetCurrentThread_fails(jvmtiEnv*, jthread*) {
  return JVMTI_ERROR_INTERNAL;
}

class ScopedJvmtiMock {
public:
  ScopedJvmtiMock() : _orig(VMTestAccessor::getJvmti()) {
    _tbl.GetCurrentThread = &mock_GetCurrentThread_fails;
    _env.functions = &_tbl;
    VMTestAccessor::setJvmti(&_env);
  }
  ~ScopedJvmtiMock() { VMTestAccessor::setJvmti(_orig); }

private:
  jvmtiInterface_1_ _tbl{};
  _jvmtiEnv _env{};
  jvmtiEnv* _orig;
};

// (d) Value-injection path: PROF-15395 fixed Profiler::checkState() (shared by
// start()/check(), and therefore also reached by the -agentpath auto-start
// path) to fail cleanly instead of crashing later when libgcc_s.so.1 can't be
// loaded. libgcc_s.so.1 is always present in this test environment, so
// INJECT_FAULT_BOOL_LIKELY on prewarmUnwinder()'s return value is what makes
// that failure path reachable here: the real dlopen() still runs and
// succeeds, but the caller is deterministically told it failed.
TEST_F(FaultInjectionTest, CheckStateSurfacesInjectedPrewarmUnwinderFailure) {
#ifdef __linux__
  Profiler* p = Profiler::instance();
  // checkState() checks prewarmUnwinder() before JVMSupport::initialize(), so
  // reaching the injected-failure path below needs nothing but the NEW state.
  ScopedJvmtiMock jvmti_mock;
  ProfilerTestAccessor::setState(p, NEW);
  ProfiledThread::current()->setFiRng(0x5EED5EED5EED5EEDULL);

  bool sawInjectedFailure = false;
  bool sawNonInjectedPrewarm = false;
  // shouldFire() mixes the fixed RNG seed above with an ASLR-dependent
  // per-call-site address, so which outcome the *first* call produces is not
  // deterministic run to run -- the injected failure can land before a
  // non-injected call is observed. Keep iterating (and un-latching the ERROR
  // state that every outcome here leaves behind) until both have been seen.
  for (int i = 0; i < 5000 && !(sawInjectedFailure && sawNonInjectedPrewarm); i++) {
    Error error = p->checkState();
    ASSERT_TRUE((bool)error) << "checkState() must fail here: either the "
                                 "injected prewarmUnwinder() failure or the "
                                 "mocked JVMSupport::initialize() failure";
    if (std::strcmp(error.message(), "Missing libgcc_s.so.1") == 0) {
      sawInjectedFailure = true;
    } else {
      // prewarmUnwinder() succeeded (non-injected, ~99% of calls) and fell
      // through to the mocked JVMSupport::initialize() failure instead.
      EXPECT_STREQ("Profiler encountered fatal error", error.message());
      sawNonInjectedPrewarm = true;
    }
    ProfilerTestAccessor::setState(p, NEW);
  }

  EXPECT_TRUE(sawInjectedFailure)
      << "expected at least one injected prewarmUnwinder() failure within 5000 tries";
  EXPECT_TRUE(sawNonInjectedPrewarm)
      << "expected at least one non-injected prewarmUnwinder() success within 5000 tries";
#endif // __linux__
}

#endif  // __FAULT_INJECTION__
