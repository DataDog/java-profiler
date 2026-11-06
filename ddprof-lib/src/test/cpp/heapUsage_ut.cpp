/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstdarg>
#include "hotspot/vmStructs.h"

class HeapUsageTestAccessor {
public:
    // Runs initJMXUsage() afresh and returns whether it marked JMX supported,
    // restoring the once-only state afterwards.
    static bool initJMXUsage(JNIEnv *env) {
        bool saved_attempted = HeapUsage::is_jmx_attempted;
        bool saved_supported = HeapUsage::is_jmx_supported;
        HeapUsage::is_jmx_attempted = false;
        HeapUsage::is_jmx_supported = false;
        HeapUsage::initJMXUsage(env);
        bool supported = HeapUsage::is_jmx_supported;
        HeapUsage::is_jmx_attempted = saved_attempted;
        HeapUsage::is_jmx_supported = saved_supported;
        return supported;
    }
};

namespace {

// initJMXUsage()'s six JNI calls, in order. Each returns a non-null handle,
// unless it is the scripted step, which throws or returns null.
enum Outcome { SUCCEED, THROW, RETURN_NULL };
int g_step;
int g_scripted_step;
Outcome g_outcome;
bool g_pending;

template <typename T>
T next() {
    g_step++;
    if (g_step == g_scripted_step && g_outcome != SUCCEED) {
        g_pending = g_outcome == THROW;
        return nullptr;
    }
    return reinterpret_cast<T>(static_cast<uintptr_t>(0x1000 + g_step));
}

jclass JNICALL findClass(JNIEnv *, const char *) { return next<jclass>(); }
jmethodID JNICALL getStaticMethodID(JNIEnv *, jclass, const char *, const char *) {
    return next<jmethodID>();
}
jmethodID JNICALL getMethodID(JNIEnv *, jclass, const char *, const char *) {
    return next<jmethodID>();
}
jobject JNICALL callStaticObjectMethodV(JNIEnv *, jclass, jmethodID, va_list) {
    return next<jobject>();
}
jobject JNICALL callObjectMethodV(JNIEnv *, jobject, jmethodID, va_list) {
    return next<jobject>();
}
jboolean JNICALL exceptionCheck(JNIEnv *) { return g_pending ? JNI_TRUE : JNI_FALSE; }
void JNICALL exceptionClear(JNIEnv *) { g_pending = false; }

class HeapUsageJmxTest : public ::testing::Test {
protected:
    JNINativeInterface_ table{};
    JNIEnv env{};

    void SetUp() override {
        table.FindClass = findClass;
        table.GetStaticMethodID = getStaticMethodID;
        table.GetMethodID = getMethodID;
        table.CallStaticObjectMethodV = callStaticObjectMethodV;
        table.CallObjectMethodV = callObjectMethodV;
        table.ExceptionCheck = exceptionCheck;
        table.ExceptionClear = exceptionClear;
        env.functions = &table;
    }

    bool run(int scripted_step, Outcome outcome) {
        g_step = 0;
        g_scripted_step = scripted_step;
        g_outcome = outcome;
        g_pending = false;
        return HeapUsageTestAccessor::initJMXUsage(&env);
    }
};

constexpr int JNI_STEPS = 6;

// The calls succeed and the MemoryMXBean returns the heap usage: JMX is
// supported. With the guards inverted, the first success returned early.
TEST_F(HeapUsageJmxTest, SupportedWhenEveryCallSucceeds) {
    EXPECT_TRUE(run(0, SUCCEED));
    EXPECT_EQ(JNI_STEPS, g_step);
}

// A call that throws ends the initialization unsupported, with the exception
// cleared and no further JNI call made with it pending.
TEST_F(HeapUsageJmxTest, UnsupportedAndClearedWhenAnyCallThrows) {
    for (int step = 1; step <= JNI_STEPS; step++) {
        SCOPED_TRACE(step);
        EXPECT_FALSE(run(step, THROW));
        EXPECT_EQ(step, g_step);
        EXPECT_FALSE(g_pending);
    }
}

// A null handle without an exception also ends it unsupported. The last call's
// result (the MemoryUsage) is not used, so only the first five are checked.
TEST_F(HeapUsageJmxTest, UnsupportedWhenAHandleIsNull) {
    for (int step = 1; step < JNI_STEPS; step++) {
        SCOPED_TRACE(step);
        EXPECT_FALSE(run(step, RETURN_NULL));
        EXPECT_EQ(step, g_step);
    }
}

} // namespace
