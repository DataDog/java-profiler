/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "arguments.h"
#include "vmEntry.h"

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

    args = Arguments();
    error = args.parse("wallprecheck=false");
    EXPECT_FALSE(error);
    EXPECT_FALSE(args._wall_precheck);

    args = Arguments();
    error = args.parse("wallprecheck=1");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._wall_precheck);

    args = Arguments();
    error = args.parse("wallprecheck=0");
    EXPECT_FALSE(error);
    EXPECT_FALSE(args._wall_precheck);
}

TEST(WallPrecheckArgsTest, MonitorCallbacksDisabledWhenWallPrecheckDisabled) {
    EXPECT_FALSE(VM::shouldEnableJvmtiMonitorCallbacks(8, false, false));
    EXPECT_FALSE(VM::shouldEnableJvmtiMonitorCallbacks(11, false, false));
    EXPECT_FALSE(VM::shouldEnableJvmtiMonitorCallbacks(21, false, false));
    EXPECT_FALSE(VM::shouldEnableJvmtiMonitorCallbacks(21, true, false));
}

TEST(WallPrecheckArgsTest, MonitorCallbacksFollowDelegateOnlyWhenWallPrecheckEnabled) {
    EXPECT_TRUE(VM::shouldEnableJvmtiMonitorCallbacks(8, false, true));
    EXPECT_TRUE(VM::shouldEnableJvmtiMonitorCallbacks(8, true, true));
    EXPECT_TRUE(VM::shouldEnableJvmtiMonitorCallbacks(21, false, true));
    EXPECT_FALSE(VM::shouldEnableJvmtiMonitorCallbacks(21, true, true));
}

TEST(WallPrecheckArgsTest, MonitorCapabilityPreservesReleaseBehaviorWhenWallPrecheckDisabled) {
    EXPECT_TRUE(VM::shouldRequestJvmtiMonitorCapability(false, false, false));
    EXPECT_TRUE(VM::shouldRequestJvmtiMonitorCapability(false, true, false));
    EXPECT_TRUE(VM::shouldRequestJvmtiMonitorCapability(false, false, true));
}

TEST(WallPrecheckArgsTest, MonitorCapabilityFollowsNewCallbacksWhenWallPrecheckEnabled) {
    EXPECT_FALSE(VM::shouldRequestJvmtiMonitorCapability(true, false, false));
    EXPECT_TRUE(VM::shouldRequestJvmtiMonitorCapability(true, true, false));
    EXPECT_TRUE(VM::shouldRequestJvmtiMonitorCapability(true, false, true));
}
