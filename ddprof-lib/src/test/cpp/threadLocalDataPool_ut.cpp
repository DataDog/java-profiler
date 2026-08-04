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
// threadLocalData.h must precede threadLocalDataPool.h: ProfiledThread needs to
// be a complete type before contains()'s pointer arithmetic is parsed (the
// pool header only forward-declares it).
#include "threadLocalData.h"
#include "threadLocalDataPool.h"
#include "counters.h"

// Covers ThreadLocalDataPool::contains(), whose result feeds directly into
// unclaim()'s double-release guard. Uses createForTest()/destroyForTest() to
// build a pool isolated from the process-wide singleton (_pool), so these
// boundary checks don't interact with other tests' initialize()/acquire()/
// release() calls.
class ThreadLocalDataPoolTest : public ::testing::Test {};

TEST_F(ThreadLocalDataPoolTest, firstElementIsContained) {
    ThreadLocalDataPool* pool = ThreadLocalDataPool::createForTest(4);
    ProfiledThread* base = pool->threadsForTest();

    EXPECT_TRUE(pool->containsForTest(base));

    ThreadLocalDataPool::destroyForTest(pool);
}

TEST_F(ThreadLocalDataPoolTest, lastElementIsContained) {
    ThreadLocalDataPool* pool = ThreadLocalDataPool::createForTest(4);
    ProfiledThread* base = pool->threadsForTest();
    uint64_t capacity = pool->capacityForTest();

    EXPECT_TRUE(pool->containsForTest(base + (capacity - 1)));

    ThreadLocalDataPool::destroyForTest(pool);
}

TEST_F(ThreadLocalDataPoolTest, onePastEndIsNotContained) {
    ThreadLocalDataPool* pool = ThreadLocalDataPool::createForTest(4);
    ProfiledThread* base = pool->threadsForTest();
    uint64_t capacity = pool->capacityForTest();

    EXPECT_FALSE(pool->containsForTest(base + capacity));

    ThreadLocalDataPool::destroyForTest(pool);
}

TEST_F(ThreadLocalDataPoolTest, oneBeforeStartIsNotContained) {
    ThreadLocalDataPool* pool = ThreadLocalDataPool::createForTest(4);
    ProfiledThread* base = pool->threadsForTest();

    EXPECT_FALSE(pool->containsForTest(base - 1));

    ThreadLocalDataPool::destroyForTest(pool);
}

TEST_F(ThreadLocalDataPoolTest, nullptrIsNotContained) {
    ThreadLocalDataPool* pool = ThreadLocalDataPool::createForTest(4);

    EXPECT_FALSE(pool->containsForTest(nullptr));

    ThreadLocalDataPool::destroyForTest(pool);
}

// Covers claim()'s (used >= _capacity) fast-path rejection once the pool is
// full. claim()'s return value is nullptr whether that guard reads `>=` or
// (bugged) `>`, because a bugged `>` still falls through to the slot-scanning
// loop, which finds every real slot already claimed and also returns nullptr.
// The observable difference is that the buggy fallthrough additionally
// increments SAMPLES_DROPPED_TLS_POOL_EXHAUSTED, which the fast path must not
// do -- that's what this test pins down.
TEST_F(ThreadLocalDataPoolTest, claimAtCapacityRejectsWithoutExhaustionScan) {
    ThreadLocalDataPool* pool = ThreadLocalDataPool::createForTest(2);

    ASSERT_NE(pool->claimForTest(0), nullptr);
    ASSERT_NE(pool->claimForTest(1), nullptr);

    long long before = Counters::getCounter(SAMPLES_DROPPED_TLS_POOL_EXHAUSTED);
    EXPECT_EQ(pool->claimForTest(2), nullptr);
    long long after = Counters::getCounter(SAMPLES_DROPPED_TLS_POOL_EXHAUSTED);

    EXPECT_EQ(after, before);

    ThreadLocalDataPool::destroyForTest(pool);
}
