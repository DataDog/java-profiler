/*
 * Copyright 2025, Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include "gtest/gtest.h"
#include "lockFree.h"
#include <pthread.h>
#include <sched.h>
#include <vector>
#include <atomic>

class LockFreeBitsetTest : public ::testing::Test {
protected:
  static constexpr size_t TEST_BITSET_SIZE = 1024;
  LockFreeBitset<TEST_BITSET_SIZE> bitset;

  void SetUp() override {
    bitset.init();
  }
};

// Test initialization
TEST_F(LockFreeBitsetTest, InitClearsAllBits) {
  // Set some bits first
  bitset.set(100);
  bitset.set(200);
  bitset.set(300);

  // Re-initialize
  bitset.init();

  // All should be cleared
  EXPECT_FALSE(bitset.test(100));
  EXPECT_FALSE(bitset.test(200));
  EXPECT_FALSE(bitset.test(300));
}

// Test basic set and test operations
TEST_F(LockFreeBitsetTest, BasicSetAndTest) {
  size_t key = 42;

  // Initially not set
  EXPECT_FALSE(bitset.test(key));

  // Set the bit
  bitset.set(key);

  // Now should be set
  EXPECT_TRUE(bitset.test(key));
}

// Test clear operation
TEST_F(LockFreeBitsetTest, ClearOperation) {
  size_t key = 123;

  // Set the bit
  bitset.set(key);
  EXPECT_TRUE(bitset.test(key));

  // Clear the bit
  bitset.clear(key);

  // Should no longer be set
  EXPECT_FALSE(bitset.test(key));
}

// Test raw bit operations
TEST_F(LockFreeBitsetTest, RawBitOperations) {
  // Use raw index directly (no hashing)
  size_t raw_index = 42;

  // Initially not set
  EXPECT_FALSE(bitset.testRaw(raw_index));

  // Set the bit
  bitset.setRaw(raw_index);
  EXPECT_TRUE(bitset.testRaw(raw_index));

  // Clear the bit
  bitset.clearRaw(raw_index);
  EXPECT_FALSE(bitset.testRaw(raw_index));
}

// Test multiple keys
TEST_F(LockFreeBitsetTest, MultipleKeys) {
  std::vector<size_t> keys = {10, 20, 30, 40, 50};

  // Set all keys
  for (size_t key : keys) {
    bitset.set(key);
  }

  // Check all are set
  for (size_t key : keys) {
    EXPECT_TRUE(bitset.test(key));
  }

  // Check unrelated keys are not set
  EXPECT_FALSE(bitset.test(15));
  EXPECT_FALSE(bitset.test(25));
}

// Test clearAll operation
TEST_F(LockFreeBitsetTest, ClearAll) {
  // Set multiple bits
  bitset.set(100);
  bitset.set(200);
  bitset.set(300);

  // Clear all
  bitset.clearAll();

  // All should be cleared
  EXPECT_FALSE(bitset.test(100));
  EXPECT_FALSE(bitset.test(200));
  EXPECT_FALSE(bitset.test(300));
}

// Test idempotency of set/clear
TEST_F(LockFreeBitsetTest, Idempotency) {
  size_t key = 555;

  // Set multiple times
  bitset.set(key);
  bitset.set(key);
  bitset.set(key);
  EXPECT_TRUE(bitset.test(key));

  // Clear once should clear it
  bitset.clear(key);
  EXPECT_FALSE(bitset.test(key));

  // Clear again should be safe
  bitset.clear(key);
  EXPECT_FALSE(bitset.test(key));
}

// Test edge cases
TEST_F(LockFreeBitsetTest, EdgeCases) {
  // Test with 0
  bitset.set(0);
  EXPECT_TRUE(bitset.test(0));
  bitset.clear(0);
  EXPECT_FALSE(bitset.test(0));

  // Test with large numbers (hash will wrap)
  bitset.set(1000000);
  EXPECT_TRUE(bitset.test(1000000));
  bitset.clear(1000000);
  EXPECT_FALSE(bitset.test(1000000));
}

// Test raw bit at word boundaries
TEST_F(LockFreeBitsetTest, WordBoundaries) {
  // Test bits at word boundaries (64-bit words)
  for (size_t i = 0; i < 4; i++) {
    size_t idx = i * 64;  // Start of each word

    bitset.setRaw(idx);
    EXPECT_TRUE(bitset.testRaw(idx));

    bitset.setRaw(idx + 63);  // End of word
    EXPECT_TRUE(bitset.testRaw(idx + 63));

    bitset.clearRaw(idx);
    bitset.clearRaw(idx + 63);
    EXPECT_FALSE(bitset.testRaw(idx));
    EXPECT_FALSE(bitset.testRaw(idx + 63));
  }
}

// Test concurrent access
TEST_F(LockFreeBitsetTest, ConcurrentAccess) {
  constexpr int NUM_THREADS = 8;
  constexpr int OPS_PER_THREAD = 100;
  std::vector<pthread_t> threads(NUM_THREADS);
  std::vector<std::atomic<bool>> success(NUM_THREADS);

  struct ThreadData {
    LockFreeBitset<TEST_BITSET_SIZE>* bitset;
    int thread_idx;
    std::atomic<bool>* success;
  };

  std::vector<ThreadData> thread_data(NUM_THREADS);
  for (int i = 0; i < NUM_THREADS; i++) {
    success[i].store(true);
    thread_data[i].bitset = &bitset;
    thread_data[i].thread_idx = i;
    thread_data[i].success = &success[i];
  }

  auto thread_func = [](void* arg) -> void* {
    ThreadData* data = static_cast<ThreadData*>(arg);
    size_t base_key = 10000 + (data->thread_idx * OPS_PER_THREAD);

    // Set keys
    for (int i = 0; i < OPS_PER_THREAD; i++) {
      size_t key = base_key + i;
      data->bitset->set(key);

      // Immediately verify
      if (!data->bitset->test(key)) {
        data->success->store(false);
        return reinterpret_cast<void*>(1);
      }
    }

    return nullptr;
  };

  // Start all threads
  for (int i = 0; i < NUM_THREADS; i++) {
    ASSERT_EQ(0, pthread_create(&threads[i], nullptr, thread_func, &thread_data[i]));
  }

  // Wait for all threads
  for (int i = 0; i < NUM_THREADS; i++) {
    void* result;
    pthread_join(threads[i], &result);
    EXPECT_EQ(nullptr, result) << "Thread " << i << " failed";
    EXPECT_TRUE(success[i].load()) << "Thread " << i << " had operation failure";
  }

  // Verify all keys are still set
  for (int t = 0; t < NUM_THREADS; t++) {
    size_t base_key = 10000 + (t * OPS_PER_THREAD);
    for (int i = 0; i < OPS_PER_THREAD; i++) {
      EXPECT_TRUE(bitset.test(base_key + i));
    }
  }
}

// Test memory ordering (set in one thread, test in another)
TEST_F(LockFreeBitsetTest, MemoryOrdering) {
  size_t key = 77777;
  std::atomic<bool> ready{false};
  std::atomic<bool> result{false};

  struct WriterData {
    LockFreeBitset<TEST_BITSET_SIZE>* bitset;
    size_t key;
    std::atomic<bool>* ready;
  };

  struct ReaderData {
    LockFreeBitset<TEST_BITSET_SIZE>* bitset;
    size_t key;
    std::atomic<bool>* ready;
    std::atomic<bool>* result;
  };

  WriterData writer_data{&bitset, key, &ready};
  ReaderData reader_data{&bitset, key, &ready, &result};

  pthread_t writer_thread, reader_thread;

  auto writer = [](void* arg) -> void* {
    auto* data = static_cast<WriterData*>(arg);
    data->bitset->set(data->key);
    data->ready->store(true, std::memory_order_release);
    return nullptr;
  };

  auto reader = [](void* arg) -> void* {
    auto* data = static_cast<ReaderData*>(arg);
    while (!data->ready->load(std::memory_order_acquire)) {
      sched_yield();
    }
    data->result->store(data->bitset->test(data->key), std::memory_order_release);
    return nullptr;
  };

  pthread_create(&writer_thread, nullptr, writer, &writer_data);
  pthread_create(&reader_thread, nullptr, reader, &reader_data);

  pthread_join(writer_thread, nullptr);
  pthread_join(reader_thread, nullptr);

  EXPECT_TRUE(result.load());
}

// Test with different sizes
TEST(LockFreeBitsetSizeTest, DifferentSizes) {
  LockFreeBitset<64> small;
  LockFreeBitset<4096> medium;
  LockFreeBitset<65536> large;

  small.init();
  medium.init();
  large.init();

  // Test basic operations on each
  small.set(10);
  EXPECT_TRUE(small.test(10));

  medium.set(1000);
  EXPECT_TRUE(medium.test(1000));

  large.set(50000);
  EXPECT_TRUE(large.test(50000));
}

// Test compile-time constants
TEST(LockFreeBitsetConstantsTest, Constants) {
  using Bitset128 = LockFreeBitset<128>;
  EXPECT_EQ(128, Bitset128::NUM_BITS);
  EXPECT_EQ(64, Bitset128::BITS_PER_WORD);
  EXPECT_EQ(2, Bitset128::NUM_WORDS);

  using Bitset1024 = LockFreeBitset<1024>;
  EXPECT_EQ(1024, Bitset1024::NUM_BITS);
  EXPECT_EQ(16, Bitset1024::NUM_WORDS);
}

// Test double-hash reduces false positives
// With double-hashing, a key returns true only if BOTH hash functions
// map to set bits. This makes false positives much less likely.
TEST(LockFreeBitsetDoubleHashTest, ReducedFalsePositives) {
  // Use a small bitset to increase collision probability in single hash
  LockFreeBitset<256> bitset;
  bitset.init();

  // Set a known key
  size_t set_key = 12345;
  bitset.set(set_key);
  EXPECT_TRUE(bitset.test(set_key));

  // Test many other keys - with double hashing, false positives should be rare
  // Even with a small 256-bit array, probability of collision in both hashes
  // is roughly (1/256)² ≈ 0.0015%
  int false_positives = 0;
  for (size_t i = 0; i < 10000; i++) {
    if (i == set_key) continue;
    if (bitset.test(i)) {
      false_positives++;
    }
  }

  // With double hashing and 256 bits, we expect very few false positives
  // Single hash would give ~10000/256 ≈ 39 collisions
  // Double hash should give ~10000/(256*256) ≈ 0.15 collisions
  // Allow some tolerance but expect significantly fewer than single hash
  EXPECT_LT(false_positives, 5) << "Too many false positives: " << false_positives;
}

// Test that setting multiple keys maintains integrity
TEST(LockFreeBitsetDoubleHashTest, MultipleKeysIntegrity) {
  LockFreeBitset<512> bitset;
  bitset.init();

  // Set 100 sequential keys (simulating thread IDs)
  std::vector<size_t> keys;
  for (size_t i = 10000; i < 10100; i++) {
    keys.push_back(i);
    bitset.set(i);
  }

  // All set keys should test true
  for (size_t key : keys) {
    EXPECT_TRUE(bitset.test(key)) << "Key " << key << " should be set";
  }

  // Clear half the keys
  for (size_t i = 0; i < 50; i++) {
    bitset.clear(keys[i]);
  }

  // First half should be cleared
  for (size_t i = 0; i < 50; i++) {
    EXPECT_FALSE(bitset.test(keys[i])) << "Key " << keys[i] << " should be cleared";
  }

  // Second half should still be set
  for (size_t i = 50; i < 100; i++) {
    EXPECT_TRUE(bitset.test(keys[i])) << "Key " << keys[i] << " should still be set";
  }
}
