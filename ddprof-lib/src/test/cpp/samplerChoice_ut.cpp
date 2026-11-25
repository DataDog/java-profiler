/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "samplerChoice.h"

// ddprof-test matches these tokens in the J9[choice] TEST_LOG lines.
TEST(SamplerChoice, namesMatchLogTokens) {
  EXPECT_STREQ("none", samplerChoiceName(SamplerChoice::NONE));
  EXPECT_STREQ("asgct", samplerChoiceName(SamplerChoice::ASGCT));
  EXPECT_STREQ("jvmti_requested",
               samplerChoiceName(SamplerChoice::JVMTI_REQUESTED));
  EXPECT_STREQ("jvmti_gated", samplerChoiceName(SamplerChoice::JVMTI_GATED));
}
