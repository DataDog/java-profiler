/*
 * Copyright 2026 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>
#include <cstring>
#include "nativeMem.h"

class NativeMemTest : public ::testing::Test {
protected:
    void SetUp() override { NativeMem::reset(); }
    void TearDown() override { NativeMem::reset(); }
};

// record() adds to and subtracts from the per-category live gauge, and the
// total is the sum across categories.
TEST_F(NativeMemTest, RecordTracksLivePerCategoryAndTotal) {
    NativeMem::record(NM_CALLTRACE, 1000);
    NativeMem::record(NM_DICTIONARY, 250);
    EXPECT_EQ(1000, NativeMem::live(NM_CALLTRACE));
    EXPECT_EQ(250, NativeMem::live(NM_DICTIONARY));
    EXPECT_EQ(0, NativeMem::live(NM_CONTEXT));
    EXPECT_EQ(1250, NativeMem::liveTotal());

    NativeMem::record(NM_CALLTRACE, -400);
    EXPECT_EQ(600, NativeMem::live(NM_CALLTRACE));
    EXPECT_EQ(850, NativeMem::liveTotal());
}

// sample() folds the current live gauge into the moving average; a single
// sample yields avg == live and max == live.
TEST_F(NativeMemTest, SingleSampleAverageEqualsLive) {
    NativeMem::record(NM_CALLTRACE, 800);
    NativeMem::sample();
    EXPECT_EQ(800, NativeMem::avg(NM_CALLTRACE));
    EXPECT_EQ(800, NativeMem::max(NM_CALLTRACE));
    EXPECT_EQ(800, NativeMem::avgTotal());
    EXPECT_EQ(800, NativeMem::maxTotal());
}

// The moving average is the mean over the sampled ticks.
TEST_F(NativeMemTest, MovingAverageOverSamples) {
    NativeMem::record(NM_CALLTRACE, 100);
    NativeMem::sample();               // window: [100]
    NativeMem::record(NM_CALLTRACE, 200);  // live now 300
    NativeMem::sample();               // window: [100, 300] -> avg 200
    EXPECT_EQ(200, NativeMem::avg(NM_CALLTRACE));
}

// The peak is a high-water mark: it retains the largest sampled value even
// after live memory has been freed back down.
TEST_F(NativeMemTest, MaxIsHighWaterMark) {
    NativeMem::record(NM_CALLTRACE, 5000);
    NativeMem::sample();
    NativeMem::record(NM_CALLTRACE, -4900);  // live drops to 100
    NativeMem::sample();
    EXPECT_EQ(100, NativeMem::live(NM_CALLTRACE));
    EXPECT_EQ(5000, NativeMem::max(NM_CALLTRACE));
}

// Transient negative live (an over-counted free at a not-yet-paired site) is
// clamped to zero when sampled so it does not skew the average or total.
TEST_F(NativeMemTest, NegativeLiveClampedInSample) {
    NativeMem::record(NM_MISC, -1234);
    NativeMem::sample();
    EXPECT_EQ(0, NativeMem::avg(NM_MISC));
    EXPECT_EQ(0, NativeMem::maxTotal());
}

// Every category exposes a distinct, non-empty name.
TEST_F(NativeMemTest, CategoryNamesPresent) {
    for (int c = 0; c < NM_NUM_CATEGORIES; c++) {
        const char *name = NativeMem::categoryName((NativeMemCategory)c);
        ASSERT_NE(nullptr, name);
        EXPECT_GT((int)strlen(name), 0);
    }
}
