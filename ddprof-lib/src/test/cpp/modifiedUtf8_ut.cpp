/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <array>
#include <cstddef>
#include <string>
#include "modifiedUtf8.h"

namespace {

std::string convert(const char *name, size_t max_units = 64) {
    std::array<char, 3 * 64> out{};
    EXPECT_LE(max_units, 64u);
    return std::string(out.data(), modifiedUtf8ToStandard(name, max_units, out.data()));
}

TEST(ModifiedUtf8ToStandardTest, AsciiAndBmpMultibyteAreCopied) {
    EXPECT_EQ("http-exec-1 [w_2]", convert("http-exec-1 [w_2]"));
    EXPECT_EQ("\xC3\xA9\xE4\xB8\xAD", convert("\xC3\xA9\xE4\xB8\xAD"));  // é中
    EXPECT_EQ("a\xED\x9F\xBF", convert("a\xED\x9F\xBF"));  // U+D7FF is ED-led, not a surrogate
    EXPECT_EQ("", convert(""));
}

TEST(ModifiedUtf8ToStandardTest, NulIsOneZeroByte) {
    EXPECT_EQ(std::string("a\0b", 3), convert("a\xC0\x80" "b"));
}

TEST(ModifiedUtf8ToStandardTest, SurrogatePairBecomesFourBytes) {
    EXPECT_EQ("vt-\xF0\x9F\x98\x80", convert("vt-\xED\xA0\xBD\xED\xB8\x80"));  // U+1F600
    EXPECT_EQ("\xF4\x8F\xBF\xBF", convert("\xED\xAF\xBF\xED\xBF\xBF"));       // U+10FFFF
}

TEST(ModifiedUtf8ToStandardTest, LoneSurrogatesBecomeReplacementChar) {
    EXPECT_EQ("\xEF\xBF\xBD" "a", convert("\xED\xA0\xBD" "a"));    // high without low
    EXPECT_EQ("a\xEF\xBF\xBD", convert("a\xED\xA0\xBD"));          // high at the end
    EXPECT_EQ("\xEF\xBF\xBD" "a", convert("\xED\xB8\x80" "a"));    // low without high
    EXPECT_EQ("\xEF\xBF\xBD\xEF\xBF\xBD", convert("\xED\xA0\xBD\xED\xA0\xBD"));  // two highs
    // A high half followed by a low half cut by the terminator: U+FFFD for each piece.
    EXPECT_EQ("\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD", convert("\xED\xA0\xBD\xED\xB8"));
    // A high half followed by ED and a second byte above BF (not a low half) is not merged.
    EXPECT_EQ(std::string("\xEF\xBF\xBD\xEF\xBF\xBD\0", 7), convert("\xED\xA0\xBD\xED\xC0\x80"));
}

TEST(ModifiedUtf8ToStandardTest, LowestValidLeadsAreCopied) {
    EXPECT_EQ("\xE0\xA0\x80", convert("\xE0\xA0\x80"));  // U+0800
    EXPECT_EQ("\xC2\x80", convert("\xC2\x80"));          // U+0080
}

TEST(ModifiedUtf8ToStandardTest, HighestValidLeadsAreCopied) {
    EXPECT_EQ("\xDF\xBF", convert("\xDF\xBF"));          // U+07FF
    EXPECT_EQ("\xEF\xBF\xBF", convert("\xEF\xBF\xBF"));  // U+FFFF
}

TEST(ModifiedUtf8ToStandardTest, MalformedBytesBecomeReplacementChar) {
    const std::string fffd = "\xEF\xBF\xBD";
    EXPECT_EQ(fffd + fffd, convert("\xC0\x81"));                // C0 not followed by 80
    EXPECT_EQ(fffd + fffd + fffd, convert("\xE0\x9F\xBF"));     // overlong: below U+0800
    EXPECT_EQ(fffd + "a", convert("\x80" "a"));                 // stray continuation
    EXPECT_EQ(fffd + fffd, convert("\xE4\xB8"));                // sequence cut by the terminator
    EXPECT_EQ(fffd + fffd, convert("\xC1\x81"));                // overlong 2-byte
    EXPECT_EQ(fffd + fffd + fffd, convert("\xE0\x81\x81"));     // overlong 3-byte
    EXPECT_EQ(fffd + fffd + fffd + fffd, convert("\xF0\x9F\x98\x80"));  // 4-byte form
}

TEST(ModifiedUtf8ToStandardTest, CapCountsUtf16Units) {
    EXPECT_EQ("abc", convert("abcd", 3));
    EXPECT_EQ("abcd", convert("abcd", 4));
    EXPECT_EQ("", convert("abcd", 0));
    EXPECT_EQ("a\xC3\xA9", convert("a\xC3\xA9\xE4\xB8\xAD", 2));
    EXPECT_EQ(std::string("a\0", 2), convert("a\xC0\x80" "b", 2));
}

TEST(ModifiedUtf8ToStandardTest, CapNeverSplitsSurrogatePair) {
    const char *name = "ab\xED\xA0\xBD\xED\xB8\x80";  // a, b, U+1F600 as two units
    EXPECT_EQ("ab", convert(name, 3));
    EXPECT_EQ("ab\xF0\x9F\x98\x80", convert(name, 4));
}

TEST(ModifiedUtf8ToStandardTest, OutputFitsThreeBytesPerUnit) {
    std::array<char, 3 * 4 + 1> out;
    out.fill('#');
    // Four lone surrogates produce the worst case: 3 output bytes per unit.
    EXPECT_EQ(12u, modifiedUtf8ToStandard("\xED\xA0\xBD\xED\xA0\xBD\xED\xA0\xBD\xED\xA0\xBD" "a",
                                          4, out.data()));
    EXPECT_EQ('#', out[12]);
}

TEST(ModifiedUtf8ToStandardTest, PlatformThreadNameRoundTripsWithEmbeddedNul) {
    EXPECT_EQ(std::string("worker-\xF0\x9F\x98\x80-\xC3\xA9\xE4\xB8\xAD-a\0b", 21),
              convert("worker-\xED\xA0\xBD\xED\xB8\x80-\xC3\xA9\xE4\xB8\xAD-a\xC0\x80" "b"));
}

} // namespace
