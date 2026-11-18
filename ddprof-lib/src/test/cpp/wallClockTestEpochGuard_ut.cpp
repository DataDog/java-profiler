/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <chrono>
#include <future>
#include <stdexcept>
#include <thread>
#include "wallClock.h"
#include "wallClockCounters.h"

using namespace std::chrono_literals;

class WallClockTestEpochGuardTest : public ::testing::Test {
protected:
    void SetUp() override { WallClockCounters::reset(); }
    void TearDown() override { WallClockCounters::reset(); }
};

TEST_F(WallClockTestEpochGuardTest, TimeoutDoesNotAcquireEpochMutex) {
    std::future<void> writer;
    {
        WallClockTestEpochGuard guard(0);
        EXPECT_FALSE(guard.ownsLock());
        writer = std::async(std::launch::async, [] {
            auto epoch_lock = BaseWallClock::samplingEpochLock();
        });
        EXPECT_EQ(std::future_status::ready, writer.wait_for(1s));
        EXPECT_EQ(0, WallClockCounters::samplingEpochStart());
    }
    writer.get();
}

TEST_F(WallClockTestEpochGuardTest, ReadyEpochNeedsNoWaitBudget) {
    WallClockCounters::beginSamplingEpoch(17);
    WallClockTestEpochGuard guard(0);
    EXPECT_TRUE(guard.ownsLock());
}

TEST_F(WallClockTestEpochGuardTest, WaitsForInitialEpochPublication) {
    std::thread publisher([] {
        std::this_thread::sleep_for(20ms);
        WallClockCounters::beginSamplingEpoch(23);
    });
    WallClockTestEpochGuard guard(NANOTIME_FREQ);
    EXPECT_TRUE(guard.ownsLock());
    EXPECT_EQ(23, WallClockCounters::samplingEpochStart());
    publisher.join();
}

TEST_F(WallClockTestEpochGuardTest, WaitsForEpochWriterAfterNonzeroPublication) {
    std::promise<void> writer_entered;
    std::promise<void> release_writer;
    auto release = release_writer.get_future();
    std::thread writer([&] {
        auto epoch_lock = BaseWallClock::samplingEpochLock();
        WallClockCounters::beginSamplingEpoch(31);
        writer_entered.set_value();
        release.wait();
    });
    writer_entered.get_future().wait();
    std::promise<void> driver_started;
    auto driver = std::async(std::launch::async, [&] {
        driver_started.set_value();
        WallClockTestEpochGuard guard(0);
        return guard.ownsLock();
    });
    driver_started.get_future().wait();
    EXPECT_EQ(std::future_status::timeout, driver.wait_for(20ms));
    release_writer.set_value();
    writer.join();
    EXPECT_TRUE(driver.get());
}

TEST_F(WallClockTestEpochGuardTest, ExcludesEpochWriterUntilDestruction) {
    WallClockCounters::beginSamplingEpoch(37);
    std::promise<void> writer_started;
    std::future<void> writer;
    {
        WallClockTestEpochGuard guard(0);
        ASSERT_TRUE(guard.ownsLock());
        writer = std::async(std::launch::async, [&] {
            writer_started.set_value();
            auto epoch_lock = BaseWallClock::samplingEpochLock();
            WallClockCounters::beginSamplingEpoch(41);
        });
        writer_started.get_future().wait();
        EXPECT_EQ(std::future_status::timeout, writer.wait_for(20ms));
        EXPECT_EQ(37, WallClockCounters::samplingEpochStart());
    }
    writer.get();
    EXPECT_EQ(41, WallClockCounters::samplingEpochStart());
}

TEST_F(WallClockTestEpochGuardTest, DumpCanAcquireEpochMutexAndDriverReacquiresIt) {
    WallClockCounters::beginSamplingEpoch(43);
    std::promise<void> writer_started;
    std::future<void> writer;
    std::future<void> dump;
    {
        WallClockTestEpochGuard guard(0);
        ASSERT_TRUE(guard.ownsLock());
        guard.withoutEpochLock([&] {
            dump = std::async(std::launch::async, [] {
                auto dump_epoch_lock = BaseWallClock::samplingEpochLock();
            });
            EXPECT_EQ(std::future_status::ready, dump.wait_for(1s));
        });
        EXPECT_TRUE(guard.ownsLock());
        writer = std::async(std::launch::async, [&] {
            writer_started.set_value();
            auto epoch_lock = BaseWallClock::samplingEpochLock();
        });
        writer_started.get_future().wait();
        EXPECT_EQ(std::future_status::timeout, writer.wait_for(20ms));
    }
    dump.get();
    writer.get();
}

TEST_F(WallClockTestEpochGuardTest, ThrowingDumpRestoresEpochOwnership) {
    WallClockCounters::beginSamplingEpoch(47);
    WallClockTestEpochGuard guard(0);
    ASSERT_TRUE(guard.ownsLock());
    EXPECT_THROW(guard.withoutEpochLock([] { throw std::runtime_error("dump"); }),
                 std::runtime_error);
    EXPECT_TRUE(guard.ownsLock());
}
