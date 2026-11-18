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

} // namespace
