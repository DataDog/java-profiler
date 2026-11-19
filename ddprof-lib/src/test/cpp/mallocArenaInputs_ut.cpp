/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <string.h>

#include "mallocArenaInputs.h"

TEST(MallocArenaInputsParse, MissingKey) {
    long v = 7;
    EXPECT_FALSE(parseTunableLong("glibc.malloc.hugetlb=2", "glibc.malloc.arena_max", &v));
    EXPECT_EQ(7, v);
    EXPECT_FALSE(parseTunableLong(NULL, "glibc.malloc.arena_max", &v));
    EXPECT_FALSE(parseTunableLong("", "glibc.malloc.arena_max", &v));
}

TEST(MallocArenaInputsParse, KeyAsSuffixOrPrefixOfAnotherKey) {
    long v = 7;
    EXPECT_FALSE(parseTunableLong("x.glibc.malloc.arena_max=4", "glibc.malloc.arena_max", &v));
    EXPECT_FALSE(parseTunableLong("glibc.malloc.arena_max_x=4", "glibc.malloc.arena_max", &v));
    EXPECT_EQ(7, v);
}

TEST(MallocArenaInputsParse, LastDuplicateKeyWins) {
    long v = 0;
    EXPECT_TRUE(parseTunableLong("glibc.malloc.arena_max=1:glibc.malloc.arena_max=256",
                                 "glibc.malloc.arena_max", &v));
    EXPECT_EQ(256, v);
}

TEST(MallocArenaInputsParse, InvalidDuplicateKeepsEarlierValidValue) {
    long v = 0;
    const char* key = "glibc.malloc.arena_max";
    EXPECT_TRUE(parseTunableLong("glibc.malloc.arena_max=256:glibc.malloc.arena_max=invalid", key, &v));
    EXPECT_EQ(256, v);
    EXPECT_TRUE(parseTunableLong("glibc.malloc.arena_max=invalid:glibc.malloc.arena_max=64", key, &v));
    EXPECT_EQ(64, v);
    v = 7;
    EXPECT_FALSE(parseTunableLong("glibc.malloc.arena_max=x:glibc.malloc.arena_max=4x", key, &v));
    EXPECT_EQ(7, v);
}

TEST(MallocArenaInputsParse, ListPositions) {
    long v = 0;
    EXPECT_TRUE(parseTunableLong("glibc.malloc.arena_max=4", "glibc.malloc.arena_max", &v));
    EXPECT_EQ(4, v);
    EXPECT_TRUE(parseTunableLong("glibc.malloc.hugetlb=2:glibc.malloc.arena_max=16",
                                 "glibc.malloc.arena_max", &v));
    EXPECT_EQ(16, v);
    EXPECT_TRUE(parseTunableLong("glibc.malloc.arena_max=3:glibc.malloc.hugetlb=2",
                                 "glibc.malloc.arena_max", &v));
    EXPECT_EQ(3, v);
}

TEST(MallocArenaInputsParse, NonNumericValues) {
    long v = 7;
    EXPECT_FALSE(parseTunableLong("glibc.malloc.arena_max=max", "glibc.malloc.arena_max", &v));
    EXPECT_FALSE(parseTunableLong("glibc.malloc.arena_max=", "glibc.malloc.arena_max", &v));
    EXPECT_FALSE(parseTunableLong("glibc.malloc.arena_max=4x", "glibc.malloc.arena_max", &v));
    EXPECT_FALSE(parseTunableLong("glibc.malloc.arena_max", "glibc.malloc.arena_max", &v));
    EXPECT_FALSE(parseTunableLong("glibc.malloc.arena_max=99999999999999999999999999",
                                  "glibc.malloc.arena_max", &v));
    EXPECT_EQ(7, v);
}

TEST(MallocArenaInputsParse, AcceptsGlibcNumberSyntax) {
    long v = 0;
    const char* key = "glibc.malloc.arena_max";
    EXPECT_TRUE(parseTunableLong("glibc.malloc.arena_max= 4", key, &v));
    EXPECT_EQ(4, v);
    EXPECT_TRUE(parseTunableLong("glibc.malloc.arena_max=+4", key, &v));
    EXPECT_EQ(4, v);
    EXPECT_TRUE(parseTunableLong("glibc.malloc.arena_max=0x10", key, &v));
    EXPECT_EQ(16, v);
    EXPECT_TRUE(parseTunableLong("glibc.malloc.arena_max=0X10", key, &v));
    EXPECT_EQ(16, v);
    EXPECT_TRUE(parseTunableLong("glibc.malloc.arena_max=010", key, &v));
    EXPECT_EQ(8, v);
    EXPECT_TRUE(parseTunableLong("glibc.malloc.arena_max=-4", key, &v));
    EXPECT_EQ(-4, v);
}

TEST(MallocArenaInputsParse, RejectsTrailingCharacters) {
    long v = 7;
    const char* key = "glibc.malloc.arena_max";
    EXPECT_FALSE(parseTunableLong("glibc.malloc.arena_max=4 ", key, &v));
    EXPECT_FALSE(parseTunableLong("glibc.malloc.arena_max=4x", key, &v));
    EXPECT_FALSE(parseTunableLong("glibc.malloc.arena_max=0x", key, &v));
    EXPECT_EQ(7, v);
}

TEST(MallocArenaInputsLimit, HexAndOctalTunable) {
    const char* src = NULL;
    EXPECT_EQ(256, effectiveArenaLimit("glibc.malloc.arena_max=0x100", "16", 4, &src));
    EXPECT_STREQ("tunable", src);
    EXPECT_EQ(8, effectiveArenaLimit(NULL, "010", 4, &src));
    EXPECT_STREQ("env", src);
}

TEST(MallocArenaInputsLimit, Default) {
    const char* src = NULL;
    EXPECT_EQ((long)(sizeof(void*) == 8 ? 8 : 2) * 4, effectiveArenaLimit(NULL, NULL, 4, &src));
    EXPECT_STREQ("default", src);
}

TEST(MallocArenaInputsLimit, EnvAndTunablePrecedence) {
    const char* src = NULL;
    EXPECT_EQ(5, effectiveArenaLimit(NULL, "5", 4, &src));
    EXPECT_STREQ("env", src);
    EXPECT_EQ(3, effectiveArenaLimit("glibc.malloc.arena_max=3", "5", 4, &src));
    EXPECT_STREQ("tunable", src);
    // A tunable that does not parse does not hide a valid env value.
    EXPECT_EQ(5, effectiveArenaLimit("glibc.malloc.arena_max=max", "5", 4, &src));
    EXPECT_STREQ("env", src);
}

TEST(MallocArenaInputsLimit, NonPositiveValuesIgnored) {
    const char* src = NULL;
    long def = (long)(sizeof(void*) == 8 ? 8 : 2) * 2;
    EXPECT_EQ(def, effectiveArenaLimit("glibc.malloc.arena_max=0", "0", 2, &src));
    EXPECT_STREQ("default", src);
    EXPECT_EQ(def, effectiveArenaLimit(NULL, "-3", 2, &src));
    EXPECT_STREQ("default", src);
    EXPECT_EQ(def, effectiveArenaLimit(NULL, "abc", 2, &src));
    EXPECT_STREQ("default", src);
}

TEST(MallocArenaInputsCapture, SaneValues) {
    MallocArenaInputs in = MallocArenaInputs::capture();
    EXPECT_GT(in.onlineCpus, 0);
    EXPECT_GT(in.arenaLimit, 0);
    EXPECT_NE(nullptr, in.arenaLimitSource);
    EXPECT_NE(nullptr, in.memoryLimitSource);
    EXPECT_TRUE(in.cpuQuotaMilli == -1 || in.cpuQuotaMilli > 0);
#ifdef __linux__
    EXPECT_GT(in.memoryLimit, 0);
    EXPECT_STRNE("unknown", in.memoryLimitSource);
#endif
#if defined(__linux__) && defined(__GLIBC__)
    EXPECT_GT(strlen(in.glibcVersion), 0u);
#else
    EXPECT_STREQ("", in.glibcVersion);
#endif
}
