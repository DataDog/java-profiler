/*
 * Copyright 2026 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>
#include "../../main/cpp/threadInfo.h"

// Covers ThreadInfo::updateThreadName, whose resolver now runs OUTSIDE the
// _ti_lock (PROF-15139). The contract the refactor must preserve:
//   - the resolver is NOT invoked when the tid is already named,
//   - an empty resolver result is not inserted,
//   - a non-empty result is inserted and retrievable.
class ThreadInfoTest : public ::testing::Test {};

TEST_F(ThreadInfoTest, resolverSkippedWhenNameKnown) {
    ThreadInfo ti;
    ti.set(42, "known", 7);

    bool resolver_called = false;
    ti.updateThreadName(42, [&](int) {
        resolver_called = true;
        return std::string("replacement");
    });

    EXPECT_FALSE(resolver_called);
    auto info = ti.get(42);
    ASSERT_NE(info.first, nullptr);
    EXPECT_EQ(*info.first, "known");
}

TEST_F(ThreadInfoTest, emptyResolverResultNotInserted) {
    ThreadInfo ti;
    ti.updateThreadName(99, [](int) { return std::string(); });

    auto info = ti.get(99);
    EXPECT_EQ(info.first, nullptr);
}

TEST_F(ThreadInfoTest, resolvedNameInsertedAndRetrievable) {
    ThreadInfo ti;
    int seen_tid = -1;
    ti.updateThreadName(100, [&](int tid) {
        seen_tid = tid;
        return std::string("C2 CompilerThread0");
    });

    EXPECT_EQ(seen_tid, 100);
    auto info = ti.get(100);
    ASSERT_NE(info.first, nullptr);
    EXPECT_EQ(*info.first, "C2 CompilerThread0");
}

// Exercises the contract introduced by resolving OUTSIDE the lock: if another
// writer inserts the tid during the unlocked resolve window, the subsequent
// emplace must be a no-op so the authoritative name (e.g. the JVMTI name set
// via set()) wins. We deterministically simulate that race by performing the
// competing set() from inside the resolver itself.
TEST_F(ThreadInfoTest, racingSetDuringResolveWins) {
    ThreadInfo ti;
    ti.updateThreadName(100, [&](int tid) {
        // Stands in for a concurrent set() landing in the unlocked window.
        ti.set(tid, "jvmti-name", 9);
        return std::string("proc-name");
    });

    auto info = ti.get(100);
    ASSERT_NE(info.first, nullptr);
    EXPECT_EQ(*info.first, "jvmti-name");
    EXPECT_EQ(info.second, 9u);
}
