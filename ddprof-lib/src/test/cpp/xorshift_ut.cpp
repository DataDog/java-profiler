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

#include "xorshift.h"
#include "reservoirSampler.h"

#include <cmath>
#include <set>
#include <vector>

// ---------------------------------------------------------------------------
// seed()
// ---------------------------------------------------------------------------

// 0 is a fixed point of the recurrence: a stream seeded there yields nothing
// but zeroes, so seed() must never produce it however the inputs cancel.
TEST(Xorshift, SeedIsNeverZero) {
    EXPECT_NE(0u, xorshift::seed(0, 0));
    // identity ^ (sequence * KNUTH) == 0 exactly when the two sides are equal.
    u64 sequence = 7;
    u64 cancelling_identity = sequence * xorshift::KNUTH;
    EXPECT_EQ(0u, cancelling_identity ^ (sequence * xorshift::KNUTH));
    EXPECT_NE(0u, xorshift::seed(cancelling_identity, sequence));
}

// Distinct identities must give distinct streams; this is what makes
// per-instance and per-thread seeding independent rather than merely different
// in principle.
TEST(Xorshift, DistinctIdentitiesGiveDistinctStreams) {
    u64 a = xorshift::seed(0x1000, 1);
    u64 b = xorshift::seed(0x1008, 1);
    ASSERT_NE(a, b);
    for (int i = 0; i < 16; i++) {
        EXPECT_NE(xorshift::next(a), xorshift::next(b));
    }
}

// Sequence numbers in practice are small and start at 0 (an epoch counter, a
// low thread id). Without the Fibonacci multiply those would produce seeds
// differing in only a few low bits.
TEST(Xorshift, SmallSequencesAreSpread) {
    std::set<u64> firsts;
    for (u64 sequence = 0; sequence < 8; sequence++) {
        u64 state = xorshift::seed(0x4000, sequence);
        firsts.insert(xorshift::next(state));
    }
    EXPECT_EQ(8u, firsts.size());
}

// ---------------------------------------------------------------------------
// next()
// ---------------------------------------------------------------------------

TEST(Xorshift, NextAdvancesAndNeverReturnsZero) {
    u64 state = xorshift::seed(0xabcdef, 3);
    u64 previous = state;
    for (int i = 0; i < 4096; i++) {
        u64 value = xorshift::next(state);
        EXPECT_NE(0u, value) << "0 would freeze the stream at iteration " << i;
        EXPECT_NE(previous, value);
        previous = value;
    }
}

// xorshift64 has full period over its 2^64-1 non-zero states, so a few
// thousand draws must not repeat.
TEST(Xorshift, ShortRunHasNoRepeats) {
    u64 state = xorshift::seed(0x5150, 11);
    std::set<u64> seen;
    for (int i = 0; i < 4096; i++) {
        EXPECT_TRUE(seen.insert(xorshift::next(state)).second) << "repeat at " << i;
    }
}

// ---------------------------------------------------------------------------
// toUnitDouble()
// ---------------------------------------------------------------------------

// Callers feed the result to log(), so 0 (log -> -inf) and 1 (log(1 - u) -> -inf
// one step later) both have to be excluded, including at the extremes of the
// input range.
TEST(Xorshift, UnitDoubleIsStrictlyInsideZeroAndOne) {
    EXPECT_GT(xorshift::toUnitDouble(0), 0.0);
    EXPECT_LT(xorshift::toUnitDouble(0), 1.0);
    EXPECT_GT(xorshift::toUnitDouble(UINT64_MAX), 0.0);
    EXPECT_LT(xorshift::toUnitDouble(UINT64_MAX), 1.0);

    u64 state = xorshift::seed(0x1234, 5);
    for (int i = 0; i < 10000; i++) {
        double u = xorshift::toUnitDouble(xorshift::next(state));
        ASSERT_GT(u, 0.0);
        ASSERT_LT(u, 1.0);
        ASSERT_TRUE(std::isfinite(std::log(u)));
    }
}

TEST(Xorshift, UnitDoubleIsRoughlyUniform) {
    u64 state = xorshift::seed(0x99, 2);
    const int buckets = 10;
    const int draws = 100000;
    int counts[buckets] = {0};
    double sum = 0.0;
    for (int i = 0; i < draws; i++) {
        double u = xorshift::toUnitDouble(xorshift::next(state));
        counts[(int)(u * buckets)]++;
        sum += u;
    }
    EXPECT_NEAR(sum / draws, 0.5, 0.01);
    // Each decile should hold a tenth of the draws; 20% slack is far wider than
    // sampling noise at this count but tight enough to catch a skewed mapping.
    for (int i = 0; i < buckets; i++) {
        EXPECT_NEAR(counts[i], draws / buckets, draws / buckets * 0.2) << "decile " << i;
    }
}

// ---------------------------------------------------------------------------
// threshold()
// ---------------------------------------------------------------------------

// The saturating branches matter: p * 2^64 is not representable as u64, and
// casting a double at or above it would be undefined.
TEST(Xorshift, ThresholdSaturatesAtTheEnds) {
    EXPECT_EQ(0u, xorshift::threshold(0.0));
    EXPECT_EQ(0u, xorshift::threshold(-0.5));
    EXPECT_EQ(UINT64_MAX, xorshift::threshold(1.0));
    EXPECT_EQ(UINT64_MAX, xorshift::threshold(2.0));
    // Just below 1.0, where the naive cast is most likely to overflow.
    EXPECT_GT(xorshift::threshold(0.9999999999999999), (u64)0);
}

TEST(Xorshift, ThresholdIsMonotonic) {
    u64 previous = 0;
    for (int i = 1; i <= 100; i++) {
        u64 current = xorshift::threshold(i / 100.0);
        EXPECT_GE(current, previous) << "at p = " << (i / 100.0);
        previous = current;
    }
}

// The property the subsampling decision in LivenessTracker relies on: the
// fraction of draws below threshold(p) is p.
TEST(Xorshift, ThresholdFiresAtTheRequestedRate) {
    const double rates[] = {0.01, 0.1, 0.5, 0.9};
    for (double rate : rates) {
        u64 threshold = xorshift::threshold(rate);
        u64 state = xorshift::seed(0x7777, (u64)(rate * 1000));
        const int draws = 200000;
        int fired = 0;
        for (int i = 0; i < draws; i++) {
            if (xorshift::next(state) < threshold) {
                fired++;
            }
        }
        EXPECT_NEAR((double)fired / draws, rate, 0.01) << "rate " << rate;
    }
}

// ---------------------------------------------------------------------------
// boundedIndex()
// ---------------------------------------------------------------------------

TEST(Xorshift, BoundedIndexStaysInRange) {
    u64 state = xorshift::seed(0x2222, 1);
    for (u32 n = 1; n <= 64; n++) {
        for (int i = 0; i < 200; i++) {
            u32 index = xorshift::boundedIndex(xorshift::next(state), n);
            ASSERT_LT(index, n) << "n = " << n;
        }
    }
}

// An empty range has no valid index; returning 0 rather than dividing by zero
// or reading past the end is the defined behaviour callers get.
TEST(Xorshift, BoundedIndexHandlesZero) {
    EXPECT_EQ(0u, xorshift::boundedIndex(0xdeadbeefcafebabeULL, 0));
}

TEST(Xorshift, BoundedIndexCoversAndBalancesTheRange) {
    const u32 n = 8;
    const int draws = 80000;
    u64 state = xorshift::seed(0x3333, 4);
    std::vector<int> counts(n, 0);
    for (int i = 0; i < draws; i++) {
        counts[xorshift::boundedIndex(xorshift::next(state), n)]++;
    }
    for (u32 i = 0; i < n; i++) {
        EXPECT_NEAR(counts[i], draws / (int)n, draws / (int)n * 0.1) << "index " << i;
    }
}

// A modulo-based mapping would over-select low indices for an n that does not
// divide 2^64. Checked against a size that is not a power of two, where that
// bias would show.
TEST(Xorshift, BoundedIndexDoesNotFavourLowIndicesForNonPowerOfTwo) {
    const u32 n = 100;
    const int draws = 200000;
    u64 state = xorshift::seed(0x4444, 9);
    std::vector<int> counts(n, 0);
    for (int i = 0; i < draws; i++) {
        counts[xorshift::boundedIndex(xorshift::next(state), n)]++;
    }
    int low = 0, high = 0;
    for (u32 i = 0; i < n / 2; i++) low += counts[i];
    for (u32 i = n / 2; i < n; i++) high += counts[i];
    EXPECT_NEAR((double)low / high, 1.0, 0.05);
}

// ---------------------------------------------------------------------------
// nextNormal()
// ---------------------------------------------------------------------------

TEST(Xorshift, NextNormalMatchesRequestedMeanAndStddev) {
    u64 state = xorshift::seed(0x5555, 6);
    const int draws = 100000;
    const double mean = 200.0;
    const double stddev = 20.0;
    double sum = 0.0;
    double sum_squares = 0.0;
    for (int i = 0; i < draws; i++) {
        double value = xorshift::nextNormal(state, mean, stddev);
        ASSERT_TRUE(std::isfinite(value)) << "draw " << i;
        sum += value;
        sum_squares += (value - mean) * (value - mean);
    }
    EXPECT_NEAR(sum / draws, mean, stddev * 0.05);
    EXPECT_NEAR(std::sqrt(sum_squares / draws), stddev, stddev * 0.05);
}

// A zero standard deviation is the degenerate case the wall-clock loop hits if
// the interval is small enough to round the 10% dither to nothing.
TEST(Xorshift, NextNormalWithZeroStddevReturnsTheMean) {
    u64 state = xorshift::seed(0x6666, 7);
    for (int i = 0; i < 100; i++) {
        EXPECT_DOUBLE_EQ(50.0, xorshift::nextNormal(state, 50.0, 0.0));
    }
}

// ---------------------------------------------------------------------------
// ReservoirSampler, which is now driven by the above
// ---------------------------------------------------------------------------

TEST(ReservoirSamplerTest, KeepsEverythingWhenInputFitsTheReservoir) {
    ReservoirSampler<int> sampler(8, 1);
    std::vector<int> input = {1, 2, 3, 4};
    std::vector<int>& out = sampler.sample(input);
    EXPECT_EQ(input, out);
}

TEST(ReservoirSamplerTest, FillsTheReservoirWhenInputIsLarger) {
    ReservoirSampler<int> sampler(8, 2);
    std::vector<int> input;
    for (int i = 0; i < 1000; i++) {
        input.push_back(i);
    }
    std::vector<int>& out = sampler.sample(input);
    EXPECT_EQ(8u, out.size());
    for (int value : out) {
        EXPECT_GE(value, 0);
        EXPECT_LT(value, 1000);
    }
}

// Every slot has to be reachable: an index mapping that never returned the top
// slot would quietly reduce the reservoir's effective size.
TEST(ReservoirSamplerTest, EveryReservoirSlotGetsWritten) {
    const int size = 4;
    std::vector<int> input;
    for (int i = 0; i < 5000; i++) {
        input.push_back(i);
    }
    std::set<int> distinct;
    for (int run = 0; run < 50; run++) {
        ReservoirSampler<int> sampler(size, (u64)run);
        std::vector<int>& out = sampler.sample(input);
        ASSERT_EQ((size_t)size, out.size());
        for (int value : out) {
            distinct.insert(value);
        }
    }
    // Replacement draws come from across the input, not just its head.
    EXPECT_GT(distinct.size(), 50u);
}

// Successive samplers at one call site share an address, so the stream
// argument is the only thing separating them. Without it every recording
// replays the first one's choices.
TEST(ReservoirSamplerTest, DistinctStreamsGiveDistinctSamples) {
    std::vector<int> input;
    for (int i = 0; i < 5000; i++) {
        input.push_back(i);
    }
    std::set<std::vector<int>> results;
    for (int run = 0; run < 20; run++) {
        ReservoirSampler<int> sampler(4, (u64)run);
        results.insert(sampler.sample(input));
    }
    EXPECT_GT(results.size(), 15u);
}

// Reproducibility is the other half of that contract: the same stream argument
// at the same call site gives the same answer, which is what makes a failing
// sample reproducible from a log.
TEST(ReservoirSamplerTest, SameStreamGivesSameSamples) {
    std::vector<int> input;
    for (int i = 0; i < 5000; i++) {
        input.push_back(i);
    }
    std::vector<int> first;
    for (int run = 0; run < 5; run++) {
        ReservoirSampler<int> sampler(4, 99);
        std::vector<int> out = sampler.sample(input);
        if (run == 0) {
            first = out;
        } else {
            EXPECT_EQ(first, out) << "run " << run;
        }
    }
}

TEST(ReservoirSamplerTest, HandlesEmptyInput) {
    ReservoirSampler<int> sampler(8, 3);
    std::vector<int> input;
    std::vector<int>& out = sampler.sample(input);
    EXPECT_TRUE(out.empty());
}

TEST(ReservoirSamplerTest, ReuseAcrossCallsDoesNotAccumulate) {
    ReservoirSampler<int> sampler(4, 4);
    std::vector<int> input;
    for (int i = 0; i < 100; i++) {
        input.push_back(i);
    }
    for (int call = 0; call < 10; call++) {
        std::vector<int>& out = sampler.sample(input);
        ASSERT_EQ(4u, out.size()) << "call " << call;
    }
}
