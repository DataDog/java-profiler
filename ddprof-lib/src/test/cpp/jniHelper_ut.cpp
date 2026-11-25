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

static int deleted_refs = 0;
static jobject last_deleted_ref = nullptr;
static int released_chars = 0;
static const char *last_released_chars = nullptr;
static const char UTF_CHARS[] = "17.0.20+8";

static void JNICALL countDeleteLocalRef(JNIEnv *, jobject ref) {
    deleted_refs++;
    last_deleted_ref = ref;
}

static const char *JNICALL returnUtfChars(JNIEnv *, jstring, jboolean *) {
    return UTF_CHARS;
}

static const char *JNICALL returnNullUtfChars(JNIEnv *, jstring, jboolean *) {
    return nullptr;
}

static void JNICALL countReleaseUtfChars(JNIEnv *, jstring, const char *chars) {
    released_chars++;
    last_released_chars = chars;
}

static JNIEnv fakeEnv(JNINativeInterface_ &table) {
    table.DeleteLocalRef = &countDeleteLocalRef;
    table.ReleaseStringUTFChars = &countReleaseUtfChars;
    JNIEnv env{};
    env.functions = &table;
    return env;
}

TEST(JniHelperTest, LocalRefIsDeletedAtScopeExit) {
    JNINativeInterface_ table{};
    JNIEnv env = fakeEnv(table);
    jobject ref = reinterpret_cast<jobject>(0x10);
    deleted_refs = 0;
    {
        JniLocalRef owner(&env, ref);
        EXPECT_EQ(ref, owner.get());
        EXPECT_EQ(0, deleted_refs);
    }
    EXPECT_EQ(1, deleted_refs);
    EXPECT_EQ(ref, last_deleted_ref);
}

TEST(JniHelperTest, NullLocalRefIsNotDeleted) {
    JNINativeInterface_ table{};
    JNIEnv env = fakeEnv(table);
    deleted_refs = 0;
    { JniLocalRef owner(&env, nullptr); }
    EXPECT_EQ(0, deleted_refs);
}

TEST(JniHelperTest, UtfCharsAreReleasedAtScopeExit) {
    JNINativeInterface_ table{};
    JNIEnv env = fakeEnv(table);
    table.GetStringUTFChars = &returnUtfChars;
    released_chars = 0;
    {
        JniUtfChars chars(&env, reinterpret_cast<jstring>(0x20));
        EXPECT_STREQ(UTF_CHARS, chars.get());
        EXPECT_EQ(0, released_chars);
    }
    EXPECT_EQ(1, released_chars);
    EXPECT_EQ(UTF_CHARS, last_released_chars);
}

static int utf_char_calls = 0;

static const char *JNICALL countUtfChars(JNIEnv *, jstring, jboolean *) {
    utf_char_calls++;
    return UTF_CHARS;
}

TEST(JniHelperTest, NullStringIsNotCopiedOrReleased) {
    JNINativeInterface_ table{};
    JNIEnv env = fakeEnv(table);
    table.GetStringUTFChars = &countUtfChars;
    utf_char_calls = 0;
    released_chars = 0;
    {
        JniUtfChars chars(&env, nullptr);
        EXPECT_EQ(nullptr, chars.get());
    }
    EXPECT_EQ(0, utf_char_calls);
    EXPECT_EQ(0, released_chars);
}

TEST(JniHelperTest, FailedUtfCharsAreNotReleased) {
    JNINativeInterface_ table{};
    JNIEnv env = fakeEnv(table);
    table.GetStringUTFChars = &returnNullUtfChars;
    released_chars = 0;
    {
        JniUtfChars chars(&env, reinterpret_cast<jstring>(0x20));
        EXPECT_EQ(nullptr, chars.get());
    }
    EXPECT_EQ(0, released_chars);
}

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
}

TEST(ModifiedUtf8ToStandardTest, MalformedBytesBecomeReplacementChar) {
    const std::string fffd = "\xEF\xBF\xBD";
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
