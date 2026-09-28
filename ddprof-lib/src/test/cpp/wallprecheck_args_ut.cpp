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

TEST(WallPrecheckArgsTest, YesNoSpellingStillWorks) {
    // "yes" is a documented boolean spelling (parseBoolOption), not merely
    // "anything that isn't false/0" - see InvalidValueIsAnError below for the
    // typo case this distinction matters for.
    Arguments args;
    Error error = args.parse("wallprecheck=yes");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._wall_precheck);
}

// wallprecheck used to accept any value other than the literal "false"/"0" via a
// raw strcmp, so a typo like "flase" silently enabled it instead of erroring - it
// now goes through the shared parseBoolOption convention like every other boolean
// option in this file.
TEST(WallPrecheckArgsTest, InvalidValueIsAnError) {
    Arguments args;
    Error error = args.parse("wallprecheck=flase");
    EXPECT_TRUE(error);
}

TEST(WallPrecheckArgsTest, EnabledWithinLongerArgString) {
    Arguments args;
    Error error = args.parse("wall=1ms,wallprecheck=true");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._wall_precheck);
}

