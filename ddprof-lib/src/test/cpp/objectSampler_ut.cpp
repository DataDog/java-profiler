/*
 * Copyright 2026, Datadog, Inc
 */

#include <gtest/gtest.h>
#include <cstddef>
#include <cstring>
#include "../../main/cpp/objectSampler.h"

// Regression tests for the SIGSEGV reported in PROF-14551. The function
// hardens the prelude of ObjectSampler::recordAllocation so that a null,
// empty, or "L"-only class signature does not dereference a bad pointer
// and does not underflow the strlen(name) - 2 length passed to
// Profiler::lookupClass.
TEST(ObjectSamplerTest, NormalizeRejectsNull) {
    const char *out_name = (const char *)0xdeadbeef;
    size_t out_len = 99;
    EXPECT_FALSE(ObjectSampler::normalizeClassSignature(NULL, &out_name, &out_len));
    // Outputs must be untouched when the call returns false.
    EXPECT_EQ(out_name, (const char *)0xdeadbeef);
    EXPECT_EQ(out_len, 99u);
}

TEST(ObjectSamplerTest, NormalizeRejectsEmpty) {
    const char *out_name = nullptr;
    size_t out_len = 0;
    EXPECT_FALSE(ObjectSampler::normalizeClassSignature("", &out_name, &out_len));
}

TEST(ObjectSamplerTest, NormalizeRejectsLoneL) {
    // Without the underflow guard, len - 2 would wrap to SIZE_MAX and
    // poison the lookupClass call.
    const char *out_name = nullptr;
    size_t out_len = 0;
    EXPECT_FALSE(ObjectSampler::normalizeClassSignature("L", &out_name, &out_len));
}

TEST(ObjectSamplerTest, NormalizeStripsLname) {
    const char *signature = "Ljava/lang/String;";
    const char *out_name = nullptr;
    size_t out_len = 0;
    EXPECT_TRUE(ObjectSampler::normalizeClassSignature(signature, &out_name, &out_len));
    EXPECT_EQ(out_name, signature + 1);
    EXPECT_EQ(out_len, strlen("java/lang/String"));
}

TEST(ObjectSamplerTest, NormalizeRejectsLnameWithEmptyBody) {
    // "L;" has no body between 'L' and ';' so it must be rejected.
    const char *out_name = (const char *)0xdeadbeef;
    size_t out_len = 99;
    EXPECT_FALSE(ObjectSampler::normalizeClassSignature("L;", &out_name, &out_len));
    EXPECT_EQ(out_name, (const char *)0xdeadbeef);
    EXPECT_EQ(out_len, 99u);
}

TEST(ObjectSamplerTest, NormalizeRejectsLnameMissingTrailingSemicolon) {
    // "Ljava/lang/String" lacks the trailing ';' and must be rejected.
    const char *out_name = (const char *)0xdeadbeef;
    size_t out_len = 99;
    EXPECT_FALSE(ObjectSampler::normalizeClassSignature("Ljava/lang/String", &out_name, &out_len));
    EXPECT_EQ(out_name, (const char *)0xdeadbeef);
    EXPECT_EQ(out_len, 99u);
}

TEST(ObjectSamplerTest, NormalizeRejectsNullOutName) {
    size_t out_len = 0;
    EXPECT_FALSE(ObjectSampler::normalizeClassSignature("Ljava/lang/String;", NULL, &out_len));
}

TEST(ObjectSamplerTest, NormalizeRejectsNullOutLen) {
    const char *out_name = nullptr;
    EXPECT_FALSE(ObjectSampler::normalizeClassSignature("Ljava/lang/String;", &out_name, NULL));
}

TEST(ObjectSamplerTest, NormalizePassesThroughPrimitiveArray) {
    const char *signature = "[B";
    const char *out_name = nullptr;
    size_t out_len = 0;
    EXPECT_TRUE(ObjectSampler::normalizeClassSignature(signature, &out_name, &out_len));
    EXPECT_EQ(out_name, signature);
    EXPECT_EQ(out_len, strlen("[B"));
}

TEST(ObjectSamplerTest, NormalizePassesThroughObjectArray) {
    const char *signature = "[Ljava/lang/String;";
    const char *out_name = nullptr;
    size_t out_len = 0;
    EXPECT_TRUE(ObjectSampler::normalizeClassSignature(signature, &out_name, &out_len));
    // Array signatures are passed through verbatim - the leading 'L'
    // strip rule applies only when the very first character is 'L'.
    EXPECT_EQ(out_name, signature);
    EXPECT_EQ(out_len, strlen("[Ljava/lang/String;"));
}
