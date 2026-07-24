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

#include "faultInjection.h"
#include "safeAccess.h"
#include "os.h"
#include "threadLocalData.h"
#include "hotspot/hotspotSupport.h"
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
  HotspotSupport::checkFault(ProfiledThread::current());  // siglongjmp if protected
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
// caught by the sigsetjmp/siglongjmp crash protection, returning control to setjmp.
TEST_F(FaultInjectionTest, WalkVmSetjmpRecoversFromInjectedFault) {
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
    (void)v;
    reads++;
  }
  t->setJmpCtx(nullptr);

  // We should have observed a recovered fault, or the loop completed cleanly. The
  // essential assertion is that the process did not die and, when a fault was
  // injected, setjmp regained control.
  EXPECT_GT(faults, 0u) << "expected at least one injected fault to longjmp-recover";
  EXPECT_TRUE(recovered);
  SUCCEED();
}

#endif  // __FAULT_INJECTION__
