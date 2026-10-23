/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Included first: the TU fails to compile if the header is not self-contained.
#include "hotspot/contBoundary.h"

#include <gtest/gtest.h>

// Compile-time checks: the predicates and per-site constants are constexpr.
static_assert(!contBoundaryProvesComplete(ContBoundary::Frozen), "Frozen must not prove completeness");
static_assert(!contBoundaryEntryFpIsCurrentFp(ContBoundary::Frozen), "Frozen uses *fp layout");
static_assert(contBoundaryProvesComplete(ContBoundary::Thawed), "Thawed proves completeness");
static_assert(contBoundaryEntryFpIsCurrentFp(ContBoundary::Thawed), "Thawed uses fp layout");
static_assert(!contBoundaryProvesComplete(ContBoundary::Unverified), "Unverified must not prove completeness");
static_assert(contBoundaryEntryFpIsCurrentFp(ContBoundary::Unverified), "Unverified keeps the thawed fp layout guess");
static_assert(!contBoundaryProvesComplete(CONT_BOUNDARY_AT_SPECULATIVE_UNKNOWN_NM),
              "speculative crossing must mark the sample truncated");
static_assert(contBoundaryEntryFpIsCurrentFp(CONT_BOUNDARY_AT_SPECULATIVE_UNKNOWN_NM),
              "speculative crossing keeps the thawed fp layout guess");
static_assert(!contBoundaryProvesComplete(CONT_BOUNDARY_AT_RETURN_BARRIER),
              "return barrier crossing must mark the sample truncated");
static_assert(!contBoundaryEntryFpIsCurrentFp(CONT_BOUNDARY_AT_RETURN_BARRIER),
              "return barrier crossing uses *fp layout");

// R4: return barrier (frozen frames remain) marks truncated and uses *fp.
TEST(ContBoundary, FrozenMarksTruncatedAndUsesSavedFp) {
    EXPECT_FALSE(contBoundaryProvesComplete(ContBoundary::Frozen));
    EXPECT_FALSE(contBoundaryEntryFpIsCurrentFp(ContBoundary::Frozen));
}

// R5/R6: verified fully-thawed boundary is complete and uses fp.
TEST(ContBoundary, ThawedIsCompleteAndUsesCurrentFp) {
    EXPECT_TRUE(contBoundaryProvesComplete(ContBoundary::Thawed));
    EXPECT_TRUE(contBoundaryEntryFpIsCurrentFp(ContBoundary::Thawed));
}

// R7/R10: speculative (unverified) crossing marks truncated but keeps the
// thawed layout guess. Pre-fix semantics treated it as "thawed => complete".
TEST(ContBoundary, UnverifiedMarksTruncatedButKeepsThawedLayout) {
    EXPECT_FALSE(contBoundaryProvesComplete(ContBoundary::Unverified));
    EXPECT_TRUE(contBoundaryEntryFpIsCurrentFp(ContBoundary::Unverified));
}

// R4-R7: per-call-site constants classify each walkVM boundary.
TEST(ContBoundary, CallSiteConstantsClassifyEachBoundary) {
    EXPECT_EQ(CONT_BOUNDARY_AT_RETURN_BARRIER, ContBoundary::Frozen);
    EXPECT_EQ(CONT_BOUNDARY_AT_ENTRY_RETURN_PC, ContBoundary::Thawed);
    EXPECT_EQ(CONT_BOUNDARY_AT_ENTER_SPECIAL_NM, ContBoundary::Thawed);
    EXPECT_EQ(CONT_BOUNDARY_AT_SPECULATIVE_UNKNOWN_NM, ContBoundary::Unverified);

    EXPECT_FALSE(contBoundaryProvesComplete(CONT_BOUNDARY_AT_SPECULATIVE_UNKNOWN_NM));
    EXPECT_TRUE(contBoundaryEntryFpIsCurrentFp(CONT_BOUNDARY_AT_SPECULATIVE_UNKNOWN_NM));
    EXPECT_FALSE(contBoundaryProvesComplete(CONT_BOUNDARY_AT_RETURN_BARRIER));
    EXPECT_FALSE(contBoundaryEntryFpIsCurrentFp(CONT_BOUNDARY_AT_RETURN_BARRIER));
    EXPECT_TRUE(contBoundaryProvesComplete(CONT_BOUNDARY_AT_ENTRY_RETURN_PC));
    EXPECT_TRUE(contBoundaryEntryFpIsCurrentFp(CONT_BOUNDARY_AT_ENTRY_RETURN_PC));
    EXPECT_TRUE(contBoundaryProvesComplete(CONT_BOUNDARY_AT_ENTER_SPECIAL_NM));
    EXPECT_TRUE(contBoundaryEntryFpIsCurrentFp(CONT_BOUNDARY_AT_ENTER_SPECIAL_NM));
}

// R9: completeness is an allow-list — only Thawed proves it; any other value,
// including an out-of-range one, defaults to "not proven" (truncated).
TEST(ContBoundary, OnlyThawedProvesCompleteness) {
    const ContBoundary all[] = {ContBoundary::Thawed, ContBoundary::Frozen, ContBoundary::Unverified};
    for (ContBoundary k : all) {
        EXPECT_EQ(contBoundaryProvesComplete(k), k == ContBoundary::Thawed);
    }
    ContBoundary unknown = static_cast<ContBoundary>(0xFE);
    EXPECT_FALSE(contBoundaryProvesComplete(unknown));
}
