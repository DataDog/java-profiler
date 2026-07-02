/*
 * Copyright 2026 Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * ContextExtractionToSupportPlan, Phase E.5 — base-object defensive-path test.
 *
 * Validates the factory-hook (support/threadContext.h g_thread_context_factory)
 * + asProfiledThread() downcast machinery described in
 * doc/specs/ContextExtractionToSupportDesign.md §5.2/§5.7: a thread that
 * allocated its ThreadContext TLS slot *before* the profiler's factory was
 * registered keeps its plain base ThreadContext for its whole lifetime — it
 * is never retroactively upgraded to a ProfiledThread. The base-object read
 * path (ContextApi::get()) and the CriticalSection guard's bitmap fallback
 * must both keep working correctly (and never crash) for such a thread, even
 * after the factory has since been switched to produce ProfiledThread for
 * new threads.
 *
 * This is not a shipping mode (the real profiler registers its factory
 * explicitly in VM::initProfilerBridge, per ContextExtractionToSupportPlan
 * Task D.1, before any thread can observe the TLS slot); it exercises the
 * defensive machinery that makes that ordering guarantee safe to rely on.
 */

#include <gtest/gtest.h>

#include "guards.h"
#include "support/context_api.h"
#include "thread.h"

#include <atomic>
#include <pthread.h>

namespace {

// Mirrors the factory lambda VM::initProfilerBridge installs (vmEntry.cpp) —
// a factory that produces ProfiledThread instances. Redeclared locally so
// this test controls exactly when it gets installed, independent of the
// default factory (support/threadContext.cpp) that's in effect at process
// load time (this gtest binary links every main source, but the profiler
// factory is only installed by VM::initProfilerBridge, which these tests
// never call).
ThreadContext *profiledFactory(int tid) { return ProfiledThread::forTid(tid); }

// RAII: saves/restores g_thread_context_factory so each test starts from a
// known state and leaves the global untouched for tests that run after it.
struct FactoryGuard {
  ThreadContextFactory saved;
  FactoryGuard()
      : saved(g_thread_context_factory.load(std::memory_order_acquire)) {}
  ~FactoryGuard() {
    g_thread_context_factory.store(saved, std::memory_order_release);
  }
};

} // namespace

// ── Base object written before factory registration, sampled after ──────────

static std::atomic<bool> g_worker_ready{false};
static std::atomic<bool> g_factory_registered{false};
static std::atomic<bool> g_sampled_ok{false};
static std::atomic<u64> g_sampled_span_id{0};
static std::atomic<u64> g_sampled_root_span_id{0};
static std::atomic<bool> g_cs_fallback_entered{false};

static void *pre_registration_worker(void *) {
  ThreadContext::initCurrentThread();
  ThreadContext *ctx = ThreadContext::current();
  EXPECT_EQ(nullptr, ctx->asProfiledThread())
      << "a thread created before factory registration must get a plain "
         "ThreadContext, not a ProfiledThread";

  ContextApi::initializeContextTLS(ctx);
  ctx->setContextForTest(0xdeadbeefULL, 424242ULL);

  g_worker_ready.store(true, std::memory_order_release);
  while (!g_factory_registered.load(std::memory_order_acquire)) {
    // Busy-wait for the main thread to switch the factory. This thread's own
    // TLS slot is already populated and must not be affected by that switch.
  }

  // Sample this pre-existing base-object thread AFTER the factory has since
  // been switched to produce ProfiledThread for new threads. ContextApi::get()
  // only requires the base ThreadContext (ThreadContext::currentSignalSafe()),
  // so it must keep working correctly here.
  u64 span_id = 0, root_span_id = 0;
  g_sampled_ok.store(ContextApi::get(span_id, root_span_id),
                     std::memory_order_relaxed);
  g_sampled_span_id.store(span_id, std::memory_order_relaxed);
  g_sampled_root_span_id.store(root_span_id, std::memory_order_relaxed);

  {
    // Defensive machinery (guards.h): CriticalSection falls back to the
    // hash-based bitmap when asProfiledThread() returns null. Must not crash
    // and must still successfully enter.
    CriticalSection cs;
    g_cs_fallback_entered.store(cs.entered(), std::memory_order_relaxed);
  }

  ThreadContext::release();
  return nullptr;
}

TEST(ThreadContextDefensivePathTest, BaseObjectSurvivesLateFactoryRegistration) {
  FactoryGuard factoryGuard;
  // Simulate "before profiler init": reset to the support-only default so the
  // worker thread below allocates a plain ThreadContext.
  resetThreadContextFactory();

  g_worker_ready.store(false, std::memory_order_relaxed);
  g_factory_registered.store(false, std::memory_order_relaxed);
  g_sampled_ok.store(false, std::memory_order_relaxed);
  g_cs_fallback_entered.store(false, std::memory_order_relaxed);

  pthread_t worker;
  ASSERT_EQ(0, pthread_create(&worker, nullptr, pre_registration_worker, nullptr));

  while (!g_worker_ready.load(std::memory_order_acquire)) {
    // Wait for the worker to write context via the base ThreadContext.
  }

  // "Register the factory" — mirrors what VM::initProfilerBridge does at
  // profiler-init time (vmEntry.cpp), done explicitly here so the test
  // controls the ordering relative to the already-live worker thread.
  g_thread_context_factory.store(profiledFactory, std::memory_order_release);
  g_factory_registered.store(true, std::memory_order_release);

  pthread_join(worker, nullptr);

  ASSERT_TRUE(g_sampled_ok.load(std::memory_order_relaxed))
      << "ContextApi::get() must succeed on a base ThreadContext with no ProfiledThread";
  EXPECT_EQ(0xdeadbeefULL, g_sampled_span_id.load(std::memory_order_relaxed));
  EXPECT_EQ(424242ULL, g_sampled_root_span_id.load(std::memory_order_relaxed));
  EXPECT_TRUE(g_cs_fallback_entered.load(std::memory_order_relaxed))
      << "CriticalSection must fall back to the bitmap path for a base-object "
         "thread and still successfully enter";
}

// ── Thread created after factory registration gets a real ProfiledThread ────

static std::atomic<bool> g_is_profiled{false};
static std::atomic<bool> g_cs_primary_entered{false};

static void *post_registration_worker(void *) {
  ThreadContext::initCurrentThread();
  ThreadContext *ctx = ThreadContext::current();
  g_is_profiled.store(ctx->asProfiledThread() != nullptr, std::memory_order_relaxed);

  CriticalSection cs;
  g_cs_primary_entered.store(cs.entered(), std::memory_order_relaxed);

  ThreadContext::release();
  return nullptr;
}

TEST(ThreadContextDefensivePathTest, ThreadCreatedAfterFactoryRegistrationGetsProfiledThread) {
  FactoryGuard factoryGuard;
  g_thread_context_factory.store(profiledFactory, std::memory_order_release);

  g_is_profiled.store(false, std::memory_order_relaxed);
  g_cs_primary_entered.store(false, std::memory_order_relaxed);

  pthread_t worker;
  ASSERT_EQ(0, pthread_create(&worker, nullptr, post_registration_worker, nullptr));
  pthread_join(worker, nullptr);

  EXPECT_TRUE(g_is_profiled.load(std::memory_order_relaxed))
      << "a thread created after factory registration must get a ProfiledThread";
  EXPECT_TRUE(g_cs_primary_entered.load(std::memory_order_relaxed))
      << "CriticalSection primary (ProfiledThread) path must still succeed for a "
         "normally-registered thread";
}
