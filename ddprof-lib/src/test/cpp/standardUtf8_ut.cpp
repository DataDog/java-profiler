/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <array>
#include <cstddef>
#include <memory>
#include <string>
#include "buffers.h"
#include "standardUtf8.h"

namespace {

const std::string FFFD = "\xEF\xBF\xBD";

std::string convert(const std::string &in, size_t cap = 64) {
    std::array<char, 64> out{};
    EXPECT_LE(cap, out.size());
    size_t length = toStandardUtf8(in.data(), in.size(), out.data(), cap);
    EXPECT_EQ(length, toStandardUtf8(in.data(), in.size(), nullptr, cap));  // measuring agrees
    EXPECT_LE(length, in.size());
    return std::string(out.data(), length);
}

TEST(ToStandardUtf8Test, StandardUtf8IsCopied) {
    EXPECT_EQ("", convert(""));
    EXPECT_EQ("http-exec-1 [w_2]", convert("http-exec-1 [w_2]"));
    EXPECT_EQ("\xC2\x80\xDF\xBF", convert("\xC2\x80\xDF\xBF"));                  // U+0080, U+07FF
    EXPECT_EQ("\xE0\xA0\x80\xEF\xBF\xBF", convert("\xE0\xA0\x80\xEF\xBF\xBF"));  // U+0800, U+FFFF
    EXPECT_EQ("a\xED\x9F\xBF", convert("a\xED\x9F\xBF"));  // U+D7FF: ED-led, not a surrogate
    EXPECT_EQ("\xF0\x9F\x98\x80", convert("\xF0\x9F\x98\x80"));  // U+1F600 in its 4-byte form
    EXPECT_EQ("\xF0\x90\x80\x80\xF4\x8F\xBF\xBF", convert("\xF0\x90\x80\x80\xF4\x8F\xBF\xBF"));
    EXPECT_EQ(std::string("a\0b", 3), convert(std::string("a\0b", 3)));
}

TEST(ToStandardUtf8Test, ModifiedUtf8IsConverted) {
    EXPECT_EQ(std::string("a\0b", 3), convert("a\xC0\x80" "b"));
    EXPECT_EQ("vt-\xF0\x9F\x98\x80", convert("vt-\xED\xA0\xBD\xED\xB8\x80"));  // U+1F600
    EXPECT_EQ("\xF4\x8F\xBF\xBF", convert("\xED\xAF\xBF\xED\xBF\xBF"));        // U+10FFFF
    EXPECT_EQ(std::string("worker-\xF0\x9F\x98\x80-\xC3\xA9\xE4\xB8\xAD-a\0b", 21),
              convert("worker-\xED\xA0\xBD\xED\xB8\x80-\xC3\xA9\xE4\xB8\xAD-a\xC0\x80" "b"));
}

TEST(ToStandardUtf8Test, ConversionIsIdempotent) {
    const std::string once = convert("a\xC0\x80" "\xED\xA0\xBD\xED\xB8\x80\xED\xB8\x80\x80");
    EXPECT_EQ(once, convert(once));
}

TEST(ToStandardUtf8Test, LoneSurrogatesBecomeReplacementChar) {
    EXPECT_EQ(FFFD + "a", convert("\xED\xA0\xBD" "a"));               // high without low
    EXPECT_EQ(FFFD + "a", convert("\xED\xB8\x80" "a"));               // low without high
    EXPECT_EQ(FFFD + FFFD + "a", convert("\xED\xA0\xBD\xED\xA0\xBD" "a"));  // two highs
    EXPECT_EQ(FFFD + FFFD, convert("\xED\xB8\x80\xED\xB8\x80"));            // two lows
    // ED and a byte above BF after a high half: not a low half, so no pair.
    EXPECT_EQ(FFFD + "?" + std::string("\0", 1), convert("\xED\xA0\xBD\xED\xC0\x80"));
    // ED B0 then a non-continuation byte: a malformed low half.
    EXPECT_EQ(FFFD + "??a", convert("\xED\xA0\xBD\xED\xB0" "a"));
}

TEST(ToStandardUtf8Test, MalformedBytesBecomeQuestionMark) {
    EXPECT_EQ("?a", convert("\x80" "a"));               // stray continuation
    EXPECT_EQ("??", convert("\xC0\x81"));               // C0 not followed by 80
    EXPECT_EQ("??", convert("\xC1\x81"));               // overlong 2-byte
    EXPECT_EQ("???", convert("\xE0\x9F\xBF"));          // overlong 3-byte: below U+0800
    EXPECT_EQ("????", convert("\xF0\x8F\xBF\xBF"));     // overlong 4-byte: below U+10000
    EXPECT_EQ("????", convert("\xF4\x90\x80\x80"));     // above U+10FFFF
    EXPECT_EQ("?a", convert("\xF5" "a"));               // invalid lead
    EXPECT_EQ("??a", convert("\xE4\xB8" "a"));          // 3-byte lead, one continuation, then 'a'
}

TEST(ToStandardUtf8Test, SequenceCutByEndOfInputIsDropped) {
    EXPECT_EQ("native-\xC3\xA9", convert("native-\xC3\xA9\xE4\xB8"));  // 中 cut after 2 bytes
    EXPECT_EQ("a", convert("a\xE4"));
    EXPECT_EQ("a", convert("a\xC0"));
    EXPECT_EQ("a", convert("a\xF0\x9F\x98"));
    EXPECT_EQ("a", convert("a\xED\xA0\xBD"));          // high half at the end
    EXPECT_EQ("a", convert("a\xED\xA0\xBD\xED"));      // pair cut after 4 bytes
    EXPECT_EQ("a", convert("a\xED\xA0\xBD\xED\xB8"));  // pair cut after 5 bytes
    // Not cut pairs: ED then a byte that cannot start a low half, and a low half at the end.
    EXPECT_EQ("a" + FFFD + "?A", convert("a\xED\xA0\xBD\xED" "A"));
    EXPECT_EQ("a" + FFFD + "?", convert("a\xED\xA0\xBD\xED\xC0"));  // C0 is above a low half
    EXPECT_EQ("a" + FFFD, convert("a\xED\xB8\x80"));
}

TEST(ToStandardUtf8Test, CapNeverSplitsACharacter) {
    EXPECT_EQ("abc", convert("abcd", 3));
    EXPECT_EQ("", convert("abcd", 0));
    EXPECT_EQ("a", convert("a\xC3\xA9", 2));
    EXPECT_EQ("a", convert("a\xED\xA0\xBD\xED\xB8\x80", 4));         // pair needs 4 bytes
    EXPECT_EQ("a\xF0\x9F\x98\x80", convert("a\xED\xA0\xBD\xED\xB8\x80", 5));
    EXPECT_EQ("a", convert("a" + FFFD, 3));
}

std::string readJfrString(const RecordingBuffer &buf) {
    const unsigned char *p = reinterpret_cast<const unsigned char *>(buf.data());
    EXPECT_EQ(3, p[0]);  // JFR string encoding 3: UTF-8 byte array
    u32 length = 0;
    int shift = 0;
    int i = 1;
    do {
        length |= static_cast<u32>(p[i] & 0x7F) << shift;
        shift += 7;
    } while (p[i++] & 0x80);
    EXPECT_EQ(static_cast<int>(i + length), buf.offset());
    return std::string(buf.data() + i, length);
}

TEST(PutUtf8Test, AsciiIsWrittenUnchanged) {
    auto buf = std::make_unique<RecordingBuffer>();
    buf->putUtf8("worker-1");
    EXPECT_EQ("worker-1", readJfrString(*buf));
}

TEST(PutUtf8Test, ModifiedUtf8IsWrittenAsStandard) {
    auto buf = std::make_unique<RecordingBuffer>();
    buf->putUtf8("a\xC0\x80" "b\xED\xA0\xBD\xED\xB8\x80");
    EXPECT_EQ(std::string("a\0b\xF0\x9F\x98\x80", 7), readJfrString(*buf));
}

TEST(PutUtf8Test, CapAtMaxStringLengthKeepsWholeCharacters) {
    std::string ascii(MAX_STRING_LENGTH + 10, 'a');
    auto buf = std::make_unique<RecordingBuffer>();
    buf->putUtf8(ascii.c_str());
    EXPECT_EQ(std::string(MAX_STRING_LENGTH, 'a'), readJfrString(*buf));

    // 8190 bytes of 'a' then a 2-byte é: the é crosses the 8191-byte cap and is dropped whole.
    std::string name = std::string(MAX_STRING_LENGTH - 1, 'a') + "\xC3\xA9";
    buf = std::make_unique<RecordingBuffer>();
    buf->putUtf8(name.c_str());
    EXPECT_EQ(std::string(MAX_STRING_LENGTH - 1, 'a'), readJfrString(*buf));
}

TEST(PutUtf8Test, NullIsWrittenAsNullString) {
    auto buf = std::make_unique<RecordingBuffer>();
    buf->putUtf8(nullptr);
    EXPECT_EQ(1, buf->offset());
    EXPECT_EQ(0, buf->data()[0]);
}

} // namespace
