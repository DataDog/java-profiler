/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "../../main/cpp/hotspot/klassTraceId.h"

#include <cstdint>
#include <vector>

// KlassTraceId::findOffset() against fake Klass layouts. Each fake klass is a
// row of 64-bit words; the decoy fields mimic what a real Klass holds around
// _trace_id, so the tests pin down which of them the calibration must reject.
namespace {

const int N = KlassTraceId::PROBE_COUNT;
const size_t WORDS = 24;  // 192 bytes, about sizeof(Klass)

struct FakeKlasses {
    std::vector<std::vector<uint64_t>> words;
    std::vector<const void*> ptrs;

    FakeKlasses() : words(N, std::vector<uint64_t>(WORDS, 0)) {
        for (int i = 0; i < N; i++) {
            words[i][0] = 0x7f0000a00000ULL;  // C++ vtable: the same for every klass
            // Pointers to metadata allocated back to back (Symbol*, mirror
            // handle, next sibling...): a few hundred bytes apart.
            words[i][2] = 0x7f1234560000ULL + i * 0x1c0;
            words[i][3] = 0x7f00fffffff0ULL + i * 0x10;  // crosses a 64K boundary
            // Small integers that are equal across array klasses.
            words[i][4] = 0x0000001000000010ULL;
            // Compact-header prototype mark word: narrow klass id << 42.
            words[i][6] = ((uint64_t)(0x40000 + i * 0x38)) << 42 | 1;
        }
        for (int i = 0; i < N; i++) {
            ptrs.push_back(words[i].data());
        }
    }

    // JFR's encoding: (id << 16) | tag bits.
    void setTraceIds(size_t word, uint64_t first, uint64_t step = 1, uint16_t tags = 0) {
        for (int i = 0; i < N; i++) {
            words[i][word] = ((first + i * step) << 16) | tags;
        }
    }

    int find() const { return KlassTraceId::findOffset(ptrs.data(), N, WORDS * 8); }
};

} // namespace

TEST(KlassTraceIdTest, FindsTraceIdAmongDecoys) {
    FakeKlasses k;
    k.setTraceIds(9, 31337);
    EXPECT_EQ(9 * 8, k.find());
}

TEST(KlassTraceIdTest, IgnoresJfrTagBits) {
    FakeKlasses k;
    k.setTraceIds(9, 31337, 1, 0x0303);
    k.words[2][9] |= 0x00f0;  // JFR re-tagged one class while running
    EXPECT_EQ(9 * 8, k.find());
}

// Other threads may create classes between two probes, taking IDs from the
// same counter: some steps are larger than one.
TEST(KlassTraceIdTest, ToleratesIdsTakenByOtherThreads) {
    FakeKlasses k;
    const uint64_t ids[N] = {5000, 5001, 5009, 5010, 5040, 5041};
    for (int i = 0; i < N; i++) {
        k.words[i][9] = ids[i] << 16;
    }
    EXPECT_EQ(9 * 8, k.find());
}

// The probes are passed in creation order, so their IDs must increase.
TEST(KlassTraceIdTest, RejectsIdsOutOfCreationOrder) {
    FakeKlasses k;
    const uint64_t ids[N] = {5000, 5001, 5003, 5002, 5004, 5005};
    for (int i = 0; i < N; i++) {
        k.words[i][9] = ids[i] << 16;
    }
    EXPECT_EQ(-1, k.find());
}

// Values that increase within the window but hardly ever by exactly one are
// not a counter's.
TEST(KlassTraceIdTest, RejectsIdsThatRarelyStepByOne) {
    FakeKlasses k;
    k.setTraceIds(9, 5000, 10);
    EXPECT_EQ(-1, k.find());
    const uint64_t ids[N] = {5000, 5001, 5009, 5017, 5025, 5026};  // two of five steps are +1
    for (int i = 0; i < N; i++) {
        k.words[i][9] = ids[i] << 16;
    }
    EXPECT_EQ(-1, k.find());
}

// What aarch64 17u held in fresh probes, from a CI log: at offset 24 pointers
// whose upper bits were distinct and within the window, next to the real
// trace IDs at offset 168. Both used to qualify, so calibration refused.
TEST(KlassTraceIdTest, RejectsPointersThatLookLikeCloseIds) {
    FakeKlasses k;
    const uint64_t at24[N] = {0x0000f5e11aef6610ULL, 0x0000f5e11afb1720ULL, 0x0000f5e11ad7ba20ULL,
                              0x0000f5e11b11a5a0ULL, 0x0000f5e11b13b540ULL, 0x0000f5e11ae369f0ULL};
    for (int i = 0; i < N; i++) {
        k.words[i][3] = at24[i];
    }
    k.setTraceIds(21, 0x4173);
    EXPECT_EQ(168, k.find());
}

TEST(KlassTraceIdTest, RejectsIdsTooFarApart) {
    FakeKlasses k;
    k.setTraceIds(9, 5000, 1000);
    EXPECT_EQ(-1, k.find());
}

TEST(KlassTraceIdTest, RejectsDuplicateIds) {
    FakeKlasses k;
    k.setTraceIds(9, 5000);
    k.words[3][9] = k.words[1][9];
    EXPECT_EQ(-1, k.find());
}

TEST(KlassTraceIdTest, RejectsZeroIds) {
    // Builds without JFR leave nothing there; a zeroed word must not qualify.
    FakeKlasses k;
    EXPECT_EQ(-1, k.find());
}

TEST(KlassTraceIdTest, RefusesAmbiguousLayout) {
    FakeKlasses k;
    k.setTraceIds(9, 5000);
    k.setTraceIds(12, 9000);
    EXPECT_EQ(-1, k.find());
}

TEST(KlassTraceIdTest, NeverPicksOffsetZero) {
    FakeKlasses k;
    k.setTraceIds(0, 5000);
    EXPECT_EQ(-1, k.find());
    k.setTraceIds(9, 6000);
    EXPECT_EQ(9 * 8, k.find());
}

TEST(KlassTraceIdTest, StaysWithinKlassSize) {
    FakeKlasses k;
    k.setTraceIds(WORDS - 1, 5000);
    EXPECT_EQ((int)((WORDS - 1) * 8), k.find());
    EXPECT_EQ(-1, KlassTraceId::findOffset(k.ptrs.data(), N, (WORDS - 1) * 8));
}

TEST(KlassTraceIdTest, NeedsAtLeastTwoProbes) {
    FakeKlasses k;
    k.setTraceIds(9, 5000);
    EXPECT_EQ(-1, KlassTraceId::findOffset(k.ptrs.data(), 1, WORDS * 8));
}
