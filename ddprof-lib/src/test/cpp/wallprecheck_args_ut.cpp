/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "arguments.h"
#include "engine.h"
#include "j9/j9WallClock.h"
#include "wallClock.h"

TEST(WallPrecheckCapabilityTest, OnlySupportingWallEnginesAdvertiseUnfilteredTracking) {
    Engine engine;
    J9WallClock j9;
    WallClockASGCT asgct;
    WallClockJvmti jvmti;

    EXPECT_FALSE(engine.supportsUnfilteredWallPrecheck());
    EXPECT_FALSE(j9.supportsUnfilteredWallPrecheck());
    EXPECT_TRUE(asgct.supportsUnfilteredWallPrecheck());
    EXPECT_TRUE(jvmti.supportsUnfilteredWallPrecheck());
}

TEST(WallPrecheckArgsTest, DefaultsToDisabled) {
    Arguments args;

    EXPECT_FALSE(args._wall_precheck);
}

TEST(WallPrecheckArgsTest, BareFlagEnablesPrecheck) {
    Arguments args;
    Error error = args.parse("wallprecheck");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._wall_precheck);
}

TEST(WallPrecheckArgsTest, ExplicitBooleanValues) {
    Arguments args;

    Error error = args.parse("wallprecheck=true");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._wall_precheck);

    // parse() frees the previous _buf before allocating a new one, so reusing
    // the same args object is correct and avoids leaking the intermediate buffers.
    error = args.parse("wallprecheck=false");
    EXPECT_FALSE(error);
    EXPECT_FALSE(args._wall_precheck);

    error = args.parse("wallprecheck=1");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._wall_precheck);

    error = args.parse("wallprecheck=0");
    EXPECT_FALSE(error);
    EXPECT_FALSE(args._wall_precheck);
}

TEST(WallPrecheckArgsTest, UnknownValueTreatedAsTrue) {
    // Any value that is not "false" or "0" enables the precheck (strcmp semantics).
    Arguments args;
    Error error = args.parse("wallprecheck=yes");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._wall_precheck);
}

TEST(WallPrecheckArgsTest, EnabledWithinLongerArgString) {
    Arguments args;
    Error error = args.parse("wall=1ms,wallprecheck=true");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._wall_precheck);
}

TEST(WallPrecheckArgsTest, OmittedFilterRemainsNull) {
    Arguments args;

    EXPECT_EQ(nullptr, args._filter);
}

TEST(WallPrecheckArgsTest, ExplicitEmptyFilterIsPreserved) {
    Arguments args;
    Error error = args.parse("filter=");

    EXPECT_FALSE(error);
    ASSERT_NE(nullptr, args._filter);
    EXPECT_STREQ("", args._filter);
}
