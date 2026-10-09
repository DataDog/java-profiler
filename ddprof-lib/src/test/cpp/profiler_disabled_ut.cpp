/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <sstream>
#include "../../main/cpp/arguments.h"
#include "../../main/cpp/profiler.h"
#include "../../main/cpp/gtest_crash_handler.h"

// Disabled mode (agent argument enabled=false): the Profiler singleton enters the
// terminal DISABLED state from NEW and rejects every lifecycle transition.
// DISABLED can't be left, so this lives in its own test binary.

static constexpr char PROFILER_DISABLED_TEST_NAME[] = "ProfilerDisabledTest";
class ProfilerDisabledGlobalSetup {
public:
  ProfilerDisabledGlobalSetup()  { installGtestCrashHandler<PROFILER_DISABLED_TEST_NAME>(); }
  ~ProfilerDisabledGlobalSetup() { restoreDefaultSignalHandlers(); }
};
static ProfilerDisabledGlobalSetup profiler_disabled_global_setup;

static void expectDisabled(const Error& error) {
  ASSERT_TRUE(error);
  EXPECT_STREQ("Profiler is disabled", error.message());
}

TEST(ProfilerDisabledTest, EveryTransitionIsRejected) {
  Profiler* profiler = Profiler::instance();
  ASSERT_FALSE(Profiler::isDisabled());

  // disable() only succeeds from NEW, which is where a fresh process starts.
  ASSERT_TRUE(profiler->disable());
  EXPECT_TRUE(Profiler::isDisabled());
  EXPECT_FALSE(profiler->isRunning());

  // Terminal: a second disable() (or anything else) can't change the state.
  EXPECT_FALSE(profiler->disable());

  Arguments args;
  ASSERT_FALSE(args.parse("start,cpu=10ms,wall=10ms"));
  std::ostringstream out;

  expectDisabled(profiler->init());
  expectDisabled(profiler->start(args, true));
  expectDisabled(profiler->check(args));
  expectDisabled(profiler->stop());
  expectDisabled(profiler->restart(args));
  expectDisabled(profiler->dump("/tmp/ddprof_disabled_ut.jfr", 27));
  expectDisabled(profiler->runInternal(args, out));

  for (Action action : {ACTION_STATUS, ACTION_LIST, ACTION_VERSION, ACTION_STOP}) {
    args._action = action;
    expectDisabled(profiler->runInternal(args, out));
  }
  EXPECT_TRUE(out.str().empty());

  profiler->shutdown(args);
  EXPECT_TRUE(Profiler::isDisabled());
}
