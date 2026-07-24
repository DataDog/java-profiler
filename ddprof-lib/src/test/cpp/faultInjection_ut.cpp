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

// Chain: safefetch recovery first, then walkVM setjmp/longjmp recovery, then
// the crash handler as a last resort so a genuine bug still produces a report.
static void (*orig_segvHandler)(int, siginfo_t*, void*);
static void (*orig_busHandler)(int, siginfo_t*, void*);

static void fi_signal_wrapper(int signo, siginfo_t* siginfo, void* context) {
  if (SafeAccess::handle_safefetch(signo, context)) {
    return;  // safefetch load recovered; PC already rewritten to _cont.
  }
  Profiler::checkFault(ProfiledThread::current());  // longjmp if protected
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
// caught by the setjmp/longjmp crash protection, returning control to setjmp.
TEST_F(FaultInjectionTest, WalkVmSetjmpRecoversFromInjectedFault) {
  ProfiledThread* t = ProfiledThread::current();
  ASSERT_NE(t, nullptr);

  uintptr_t real_slot = 0;             // a valid, readable pointer slot
  uintptr_t base = (uintptr_t)&real_slot;
  volatile bool recovered = false;
  volatile size_t reads = 0;
  volatile size_t faults = 0;

  jmp_buf ctx;
  if (setjmp(ctx) != 0) {
    recovered = true;                  // returned here via checkFault -> longjmp
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
  // injected, setjmp regained control.
  EXPECT_GT(faults, 0u) << "expected at least one injected fault to longjmp-recover";
  EXPECT_TRUE(recovered);
  SUCCEED();
}

// (c3) recordSample's outer setjmp region (PROF-15447): Profiler::recordSample()
// wraps the native/Java unwind in its own jmp_buf, chaining off whatever
// context a caller may already have installed, so a fault in the
// *unprotected* metadata reads surrounding walkVM/walkFP/walkDwarf (isJitCode,
// findFrameDesc, findLibraryByAddress, AGCT in getJavaTraceAsync, frame.link,
// ...) recovers to a partial trace instead of crashing — and, critically,
// restores the caller's jmp_buf chain on both the clean and the recovery path.
//
// recordSample() itself needs a live JVM (ASGCT, VMStructs, an allocated
// _calltrace_buffer) unavailable in this gtest binary, so — following the
// same "replicate the protocol" approach used elsewhere in this suite for
// JVM-dependent code — this test reproduces its exact save/install/setjmp/
// longjmp/restore sequence verbatim, including the `volatile int num_frames`
// accumulator that must survive the longjmp landing, and drives it with the
// same probabilistic fault injection as WalkVmSetjmpRecoversFromInjectedFault.
// Unlike that test, this one also (a) starts from an already-installed
// "grandparent" jmp_buf to verify nesting/chain-restore, matching how
// recordSample can itself run nested under another sampler's protection, and
// (b) asserts STACKWALK_LONGJMP_RECOVERED actually increments, confirming the
// real Profiler::checkFault() (wired in via fi_signal_wrapper) did the
// recovery rather than some other signal-handling path.
TEST_F(FaultInjectionTest, RecordSampleOuterSetjmpRecoversAndRestoresChain) {
  ProfiledThread* t = ProfiledThread::current();
  ASSERT_NE(t, nullptr);

  // Simulate a pre-existing outer protection context, as recordSample must
  // support when nested inside another sampler's own protected region.
  jmp_buf grandparent_ctx;
  t->setJmpCtx(&grandparent_ctx);

  uintptr_t real_slot = 0;              // a valid, readable "metadata" slot
  uintptr_t base = (uintptr_t)&real_slot;
  long long recovered_before = Counters::getCounter(STACKWALK_LONGJMP_RECOVERED);

  // Read again after the setjmp landing below, so it must be volatile — mirrors
  // recordSample's own num_frames.
  volatile int num_frames = 0;
  // Frames "collected" before the fault, e.g. by a getNativeTrace() call that
  // partially succeeded before walkJavaStack() faulted. Seeding a non-zero
  // value here — mutated between setjmp() and the longjmp below — is what
  // actually exercises the volatile qualifier: a non-volatile local would be
  // indeterminate after the jump, so the post-recovery checks below would not
  // reliably see it. Without this seed, num_frames would still read 0 whether
  // or not it were volatile, and the test would prove nothing about volatile.
  constexpr int kSeededFrames = 3;

  jmp_buf unwind_ctx;
  jmp_buf* prev_jmp_buf = t->getJmpCtx();
  ASSERT_EQ(&grandparent_ctx, prev_jmp_buf);

  t->setFiRng(0xC0FFEEC0FFEEC0FFULL);

  int jmp_rc = setjmp(unwind_ctx);
  if (jmp_rc != 0) {
    // Landed here via the real Profiler::checkFault() -> longjmp, triggered by
    // an actual injected fault below. Mirrors recordSample's
    // `if (num_frames < _max_stack_depth) { num_frames += makeFrame(...); }`:
    // the recovery marker is appended to whatever partial progress survived
    // the jump, never resets it.
    t->setJmpCtx(prev_jmp_buf);
    num_frames += 1;  // stand-in for makeFrame(..., "break_unwind_fault")
  } else {
    t->setJmpCtx(&unwind_ctx);
    num_frames = kSeededFrames;  // mutated before the fault; must survive the longjmp

    // Force at least one fire deterministically, then let the tier drive the rest.
    for (int i = 0; i < 5000 && num_frames == kSeededFrames; i++) {
      // Raw deref of the (possibly poisoned) base — mirrors the unprotected
      // metadata reads recordSample's outer setjmp now guards.
      uintptr_t v = *(uintptr_t*)INJECT_FAULT_ADDRESS_LIKELY(base);
      asm volatile("" : "+r"(v) : : "memory");
    }
    t->setJmpCtx(prev_jmp_buf);
  }

  EXPECT_EQ(&grandparent_ctx, t->getJmpCtx())
      << "must restore the caller's jmp_buf chain on both the clean and the "
         "recovery path, never leave it cleared or pointing at unwind_ctx";
  EXPECT_EQ(kSeededFrames + 1, num_frames)
      << "the seeded pre-fault value must survive the longjmp landing and the "
         "recovery marker must append to it, not overwrite it";
  EXPECT_GT(Counters::getCounter(STACKWALK_LONGJMP_RECOVERED), recovered_before)
      << "checkFault() must have run and incremented the shared recovery counter";

  t->setJmpCtx(nullptr);  // leave the thread unprotected for subsequent tests
}

#endif  // __FAULT_INJECTION__
