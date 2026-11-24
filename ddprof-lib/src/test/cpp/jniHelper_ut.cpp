/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <array>
#include <cstddef>
#include <cstring>
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

} // namespace
