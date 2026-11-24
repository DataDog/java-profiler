/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "jvmtiHelper.h"

namespace {

static int deallocations = 0;
static unsigned char *last_deallocated = nullptr;
static char VALUE[] = "17.0.20+8-openj9-0.60.0";

static jvmtiError JNICALL countDeallocate(jvmtiEnv *, unsigned char *mem) {
    deallocations++;
    last_deallocated = mem;
    return JVMTI_ERROR_NONE;
}

TEST(JvmtiHelperTest, StringIsDeallocatedAtScopeExit) {
    jvmtiInterface_1_ table{};
    table.Deallocate = &countDeallocate;
    jvmtiEnv env{};
    env.functions = &table;
    deallocations = 0;
    {
        JvmtiString value(&env);
        *value.out() = VALUE;
        EXPECT_STREQ(VALUE, value.get());
        EXPECT_EQ(0, deallocations);
    }
    EXPECT_EQ(1, deallocations);
    EXPECT_EQ(reinterpret_cast<unsigned char *>(VALUE), last_deallocated);
}

TEST(JvmtiHelperTest, UnsetStringIsNotDeallocated) {
    jvmtiInterface_1_ table{};
    table.Deallocate = &countDeallocate;
    jvmtiEnv env{};
    env.functions = &table;
    deallocations = 0;
    {
        JvmtiString value(&env);
        EXPECT_EQ(nullptr, value.get());
    }
    EXPECT_EQ(0, deallocations);
}

} // namespace
