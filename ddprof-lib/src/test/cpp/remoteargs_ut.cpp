/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "arguments.h"
#include "../../main/cpp/gtest_crash_handler.h"

static constexpr char REMOTE_ARGS_TEST_NAME[] = "RemoteArgsTest";

class RemoteArgsGlobalSetup {
public:
    RemoteArgsGlobalSetup() {
        installGtestCrashHandler<REMOTE_ARGS_TEST_NAME>();
    }
    ~RemoteArgsGlobalSetup() {
        restoreDefaultSignalHandlers();
    }
};

static RemoteArgsGlobalSetup global_setup;

class RemoteArgsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Test setup
    }

    void TearDown() override {
        // Test cleanup
    }
};

TEST_F(RemoteArgsTest, DefaultRemoteSymbolicationDisabled) {
    Arguments args;

    // Remote symbolication should be disabled by default
    EXPECT_FALSE(args._remote_symbolication);
}

TEST_F(RemoteArgsTest, EnableRemoteSymbolication) {
    Arguments args;

    // Test enabling remote symbolication
    Error error = args.parse("remotesym=true");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._remote_symbolication);
}

TEST_F(RemoteArgsTest, EnableRemoteSymbolicationShort) {
    Arguments args;

    // Test short form
    Error error = args.parse("remotesym=y");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._remote_symbolication);
}

TEST_F(RemoteArgsTest, DisableRemoteSymbolication) {
    Arguments args;

    // Test explicitly disabling
    Error error = args.parse("remotesym=false");
    EXPECT_FALSE(error);
    EXPECT_FALSE(args._remote_symbolication);
}

TEST_F(RemoteArgsTest, MultipleArgsWithRemoteSymbolication) {
    Arguments args;

    // Test with multiple arguments
    Error error = args.parse("event=cpu,interval=1000000,remotesym=true");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._remote_symbolication);
    EXPECT_STREQ(args._event, "cpu");
    EXPECT_EQ(args._interval, 1000000);
}

TEST_F(RemoteArgsTest, RemoteSymbolicationWithOtherFlags) {
    Arguments args;

    // Test interaction with lightweight flag
    Error error = args.parse("lightweight=true,remotesym=true");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._lightweight);
    EXPECT_TRUE(args._remote_symbolication);
}