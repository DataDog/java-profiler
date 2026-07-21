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
    EXPECT_EQ(0, NativeMem::live(NM_THREAD_FILTER));
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

// The peak is a high-water mark: it retains the largest value even after live
// memory has been freed back down.
TEST_F(NativeMemTest, MaxIsHighWaterMark) {
    NativeMem::record(NM_CALLTRACE, 5000);
    NativeMem::record(NM_CALLTRACE, -4900);  // live drops to 100
    EXPECT_EQ(100, NativeMem::live(NM_CALLTRACE));
    EXPECT_EQ(5000, NativeMem::max(NM_CALLTRACE));
}

// The per-category peak is precise: it is captured at allocation time, so a
// spike that rises and falls entirely between two sample() ticks is still seen
// by max(), while the observed total (sampled) misses it. maxTotal() (upper
// bound = sum of per-category peaks) brackets the true peak from above.
TEST_F(NativeMemTest, PerCategoryMaxIsPreciseBetweenSamples) {
    NativeMem::record(NM_CALLTRACE, 9000);
    NativeMem::record(NM_CALLTRACE, -8000);  // peak of 9000 undone before any sample
    NativeMem::sample();                     // only ever observes live == 1000
    EXPECT_EQ(1000, NativeMem::live(NM_CALLTRACE));
    EXPECT_EQ(9000, NativeMem::max(NM_CALLTRACE));    // precise: caught the spike
    EXPECT_EQ(1000, NativeMem::maxTotalObserved());   // sampled: missed the spike
    EXPECT_EQ(9000, NativeMem::maxTotal());           // upper bound
}

// setLive() overwrites the live value (gauge semantics) but still advances the
// peak, which is retained when the gauge shrinks.
TEST_F(NativeMemTest, SetLiveOverwritesAndAdvancesMax) {
    NativeMem::setLive(NM_NATIVE_SYMBOLS, 4096);
    EXPECT_EQ(4096, NativeMem::live(NM_NATIVE_SYMBOLS));
    EXPECT_EQ(4096, NativeMem::max(NM_NATIVE_SYMBOLS));
    NativeMem::setLive(NM_NATIVE_SYMBOLS, 1024);  // gauge shrinks
    EXPECT_EQ(1024, NativeMem::live(NM_NATIVE_SYMBOLS));
    EXPECT_EQ(4096, NativeMem::max(NM_NATIVE_SYMBOLS));  // peak retained
}

// Every category exposes a distinct, non-empty name.
TEST_F(NativeMemTest, CategoryNamesPresent) {
    for (int c = 0; c < NM_NUM_CATEGORIES; c++) {
        const char *name = NativeMem::categoryName((NativeMemCategory)c);
        ASSERT_NE(nullptr, name);
        EXPECT_GT((int)strlen(name), 0);
    }
}
