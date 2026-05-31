/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "arguments.h"

TEST(WallPrecheckArgsTest, DefaultsToDisabled) {
    Arguments args;

    EXPECT_FALSE(args._wall_precheck);
}

TEST(WallPrecheckArgsTest, BareFlagWithoutValueEnablesPrecheck) {
    // wallprecheck is false by default; passing it without a value enables it,
    // matching the profiler's boolean flag parsing convention.
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
