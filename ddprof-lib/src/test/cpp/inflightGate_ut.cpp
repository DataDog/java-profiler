/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <atomic>
#include <thread>
#include <vector>
#include "../../main/cpp/inflightGate.h"
#include "../../main/cpp/gtest_crash_handler.h"

static constexpr char INFLIGHT_GATE_TEST_NAME[] = "InflightGateTest";
class InflightGateGlobalSetup {
public:
  InflightGateGlobalSetup()  { installGtestCrashHandler<INFLIGHT_GATE_TEST_NAME>(); }
  ~InflightGateGlobalSetup() { restoreDefaultSignalHandlers(); }
};
static InflightGateGlobalSetup inflight_gate_global_setup;

static const long DRAIN_TIMEOUT_NS = 200000000L;  // 200 ms

TEST(InflightGateTest, ClosedByDefaultRejectsCallers) {
  InflightGate gate;
  EXPECT_FALSE(gate.isOpen());
  InflightGate::Scope scope(gate);
  EXPECT_FALSE(scope.entered());
  EXPECT_FALSE(gate.hasInflight());
}

TEST(InflightGateTest, EnterExitWhileOpen) {
  InflightGate gate;
  gate.open();
  {
    InflightGate::Scope scope(gate);
    EXPECT_TRUE(scope.entered());
    EXPECT_TRUE(gate.hasInflight());
  }
  EXPECT_FALSE(gate.hasInflight());
  gate.close();
  EXPECT_TRUE(gate.drain(DRAIN_TIMEOUT_NS));
  InflightGate::Scope late(gate);
  EXPECT_FALSE(late.entered());
}

TEST(InflightGateTest, DrainTimesOutWhileACallerIsInside) {
  InflightGate gate;
  gate.open();
  int stripe = gate.enter();
  ASSERT_GE(stripe, 0);
  gate.close();
  EXPECT_FALSE(gate.drain(20000000L));  // 20 ms
  gate.exit(stripe);
  EXPECT_TRUE(gate.drain(DRAIN_TIMEOUT_NS));
}

TEST(InflightGateTest, DrainWaitsForCallerToLeave) {
  InflightGate gate;
  gate.open();
  std::atomic<bool> inside{false};
  std::thread t([&] {
    InflightGate::Scope scope(gate);
    ASSERT_TRUE(scope.entered());
    inside.store(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
  });
  while (!inside.load()) {
    std::this_thread::yield();
  }
  gate.close();
  EXPECT_TRUE(gate.drain(DRAIN_TIMEOUT_NS));
  t.join();
}

// After close() + a successful drain(), no caller may still be inside: a
// resource freed at that point is never touched again.
TEST(InflightGateTest, NoCallerInsideAfterCloseAndDrain) {
  for (int round = 0; round < 50; round++) {
    InflightGate gate;
    gate.open();
    std::atomic<bool> freed{false};
    std::atomic<bool> stop{false};
    std::atomic<int> violations{0};
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; i++) {
      threads.emplace_back([&] {
        while (!stop.load(std::memory_order_relaxed)) {
          InflightGate::Scope scope(gate);
          if (scope.entered() && freed.load()) {
            violations.fetch_add(1);
          }
        }
      });
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    gate.close();
    ASSERT_TRUE(gate.drain(DRAIN_TIMEOUT_NS));
    freed.store(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    stop.store(true);
    for (auto& t : threads) {
      t.join();
    }
    EXPECT_EQ(0, violations.load());
  }
}
