/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <array>
#include <cstddef>
#include <cstring>
#include <string>
#include "jniHelper.h"

#ifdef JNI_VERSION_21
static_assert(offsetof(JNINativeInterface_, IsVirtualThread) == 234 * sizeof(void *),
              "IsVirtualThread must match the JNI ABI slot");
#endif

namespace {

static jboolean JNICALL isVirtual(JNIEnv *, jobject thread) {
    return thread == reinterpret_cast<jobject>(1) ? JNI_TRUE : JNI_FALSE;
}

TEST(JniHelperTest, VirtualThreadDetectionUsesRuntimeTable) {
    std::array<void *, 235> table{};
    auto function = &isVirtual;
    std::memcpy(&table[234], &function, sizeof(function));
    JNIEnv env{};
    env.functions = reinterpret_cast<const JNINativeInterface_ *>(table.data());
    EXPECT_TRUE(jniIsVirtualThread(&env, reinterpret_cast<jobject>(1), 21));
    EXPECT_TRUE(jniIsVirtualThread(&env, reinterpret_cast<jobject>(1), 27));
    EXPECT_FALSE(jniIsVirtualThread(&env, reinterpret_cast<jobject>(2), 21));
}

TEST(JniHelperTest, OlderRuntimesDoNotReadNewTableSlots) {
    JNINativeInterface_ table{};
    JNIEnv env{};
    env.functions = &table;
    EXPECT_FALSE(jniIsVirtualThread(&env, reinterpret_cast<jobject>(1), 17));
    EXPECT_FALSE(jniIsVirtualThread(&env, reinterpret_cast<jobject>(1), 20));
    EXPECT_FALSE(jniIsVirtualThread(nullptr, reinterpret_cast<jobject>(1), 21));
}

std::string encode(const std::u16string &text) {
    std::array<char, 3 * 16> out{};
    EXPECT_LE(text.size(), 16u);
    size_t length = utf16ToUtf8(reinterpret_cast<const jchar *>(text.data()),
                                static_cast<jsize>(text.size()), out.data());
    return std::string(out.data(), length);
}

TEST(Utf16ToUtf8Test, AsciiAndBmpMultibyte) {
    EXPECT_EQ("vt-1", encode(u"vt-1"));
    EXPECT_EQ("\xC3\xA9\xE4\xB8\xAD", encode(u"\u00e9\u4e2d"));
}

TEST(Utf16ToUtf8Test, SupplementaryIsFourBytesNotSurrogateSix) {
    EXPECT_EQ("vt-\xF0\x9F\x98\x80", encode(u"vt-\U0001F600"));
}

TEST(Utf16ToUtf8Test, UnpairedSurrogatesBecomeReplacementChar) {
    EXPECT_EQ("a\xEF\xBF\xBD", encode(std::u16string{u'a', 0xD83D}));
    EXPECT_EQ("\xEF\xBF\xBD" "a", encode(std::u16string{0xDE00, u'a'}));
    EXPECT_EQ("\xEF\xBF\xBD\xEF\xBF\xBD", encode(std::u16string{0xD83D, 0xD83D}));
}

TEST(Utf16ToUtf8Test, NulIsOneZeroByteNotModifiedUtf8) {
    EXPECT_EQ(std::string("a\0b", 3), encode(std::u16string{u'a', 0, u'b'}));
}

TEST(Utf16ToUtf8Test, EmptyInputEncodesToNothing) {
    EXPECT_EQ("", encode(u""));
}

TEST(Utf16TruncatedLengthTest, DropsHighSurrogateWhoseLowHalfIsCutOff) {
    const std::u16string text = u"ab\U0001F600";  // a b D83D DE00
    const jchar *units = reinterpret_cast<const jchar *>(text.data());
    EXPECT_EQ(2, utf16TruncatedLength(units, 3, 4));
    EXPECT_EQ(4, utf16TruncatedLength(units, 4, 4));
    EXPECT_EQ(2, utf16TruncatedLength(units, 2, 4));
}

TEST(Utf16TruncatedLengthTest, KeepsLoneHighSurrogateAtTheEndOfTheString) {
    const std::u16string text{u'a', 0xD83D};
    EXPECT_EQ(2, utf16TruncatedLength(reinterpret_cast<const jchar *>(text.data()), 2, 2));
    EXPECT_EQ(0, utf16TruncatedLength(reinterpret_cast<const jchar *>(text.data()), 0, 2));
}

} // namespace
