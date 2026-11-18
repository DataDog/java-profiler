/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstdint>
#include <utility>
#include <vector>
#include "hotspot/vmStructs.h"

namespace {

typedef std::vector<std::pair<jmethodID, void *>> Bindings;

jmethodID fakeMethod(int i) {
    return reinterpret_cast<jmethodID>(static_cast<uintptr_t>(0x1000 + i));
}

void *fakeAddress(int i) {
    return reinterpret_cast<void *>(static_cast<uintptr_t>(0x100000 + i));
}

Bindings drain(DelayedNativeBindings &delayed) {
    Bindings out;
    delayed.drain([&](jmethodID m, void *a) { out.emplace_back(m, a); });
    return out;
}

} // namespace

TEST(DelayedNativeBindingsTest, ReplaysBindingsInOrder) {
    DelayedNativeBindings delayed;
    for (int i = 0; i < 3; i++) {
        EXPECT_TRUE(delayed.add(fakeMethod(i), fakeAddress(i)));
    }
    Bindings out = drain(delayed);
    ASSERT_EQ(3u, out.size());
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(fakeMethod(i), out[i].first);
        EXPECT_EQ(fakeAddress(i), out[i].second);
    }
}

TEST(DelayedNativeBindingsTest, DropsPairsPastCapacity) {
    DelayedNativeBindings delayed;
    const int capacity = DelayedNativeBindings::CAPACITY;
    for (int i = 0; i < capacity; i++) {
        ASSERT_TRUE(delayed.add(fakeMethod(i), fakeAddress(i))) << "pair " << i;
    }
    EXPECT_FALSE(delayed.add(fakeMethod(capacity), fakeAddress(capacity)));
    EXPECT_FALSE(delayed.add(fakeMethod(capacity + 1), fakeAddress(capacity + 1)));

    // The full list replays intact; the rejected pairs are not in it.
    Bindings out = drain(delayed);
    ASSERT_EQ(static_cast<size_t>(capacity), out.size());
    for (int i = 0; i < capacity; i++) {
        EXPECT_EQ(fakeMethod(i), out[i].first) << "pair " << i;
        EXPECT_EQ(fakeAddress(i), out[i].second) << "pair " << i;
    }
}

TEST(DelayedNativeBindingsTest, DrainWithBindingsClosesList) {
    DelayedNativeBindings delayed;
    EXPECT_TRUE(delayed.add(fakeMethod(0), fakeAddress(0)));
    EXPECT_EQ(1u, drain(delayed).size());

    EXPECT_FALSE(delayed.add(fakeMethod(1), fakeAddress(1)));
    EXPECT_TRUE(drain(delayed).empty());
}

TEST(DelayedNativeBindingsTest, EmptyDrainKeepsListOpen) {
    DelayedNativeBindings delayed;
    EXPECT_TRUE(drain(delayed).empty());

    EXPECT_TRUE(delayed.add(fakeMethod(0), fakeAddress(0)));
    Bindings out = drain(delayed);
    ASSERT_EQ(1u, out.size());
    EXPECT_EQ(fakeMethod(0), out[0].first);
}
