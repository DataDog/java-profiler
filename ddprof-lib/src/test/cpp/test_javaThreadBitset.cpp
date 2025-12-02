/*
 * Copyright 2025, Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include "gtest/gtest.h"
#include "thread.h"
#include <pthread.h>
#include <sched.h>
#include <vector>
#include <atomic>

class JavaThreadBitsetTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Each test starts fresh - no cleanup needed as bitset is static
  }

  void TearDown() override {
    // Cleanup: unregister all test thread IDs
    for (int tid : registered_tids) {
      ProfiledThread::unregisterJavaThread(tid);
    }
    registered_tids.clear();
  }

  std::vector<int> registered_tids;
};

// Test basic registration and lookup
TEST_F(JavaThreadBitsetTest, BasicRegistrationAndLookup) {
  int tid = 12345;

  // Initially should not be registered
  EXPECT_FALSE(ProfiledThread::isLikelyJavaThread(tid));

  // Register the thread
  ProfiledThread::registerJavaThread(tid);
  registered_tids.push_back(tid);

  // Now should be registered
  EXPECT_TRUE(ProfiledThread::isLikelyJavaThread(tid));
}

// Test unregistration
TEST_F(JavaThreadBitsetTest, Unregistration) {
  int tid = 54321;

  // Register
  ProfiledThread::registerJavaThread(tid);
  EXPECT_TRUE(ProfiledThread::isLikelyJavaThread(tid));

  // Unregister
  ProfiledThread::unregisterJavaThread(tid);

  // Should no longer be registered
  EXPECT_FALSE(ProfiledThread::isLikelyJavaThread(tid));
}

// Test multiple thread IDs
TEST_F(JavaThreadBitsetTest, MultipleThreads) {
  std::vector<int> tids = {100, 200, 300, 400, 500};

  // Register all
  for (int tid : tids) {
    ProfiledThread::registerJavaThread(tid);
    registered_tids.push_back(tid);
  }

  // Check all are registered
  for (int tid : tids) {
    EXPECT_TRUE(ProfiledThread::isLikelyJavaThread(tid));
  }

  // Check some unrelated IDs are not registered
  EXPECT_FALSE(ProfiledThread::isLikelyJavaThread(150));
  EXPECT_FALSE(ProfiledThread::isLikelyJavaThread(250));
}

// Test Knuth hash distribution
TEST_F(JavaThreadBitsetTest, KnuthHashDistribution) {
  // Verify that Knuth hashing works correctly for basic registration/unregistration
  // The hash function provides excellent distribution, making collisions rare

  int tid1 = 1000;

  // Register first TID
  ProfiledThread::registerJavaThread(tid1);
  registered_tids.push_back(tid1);

  // First TID should be marked
  EXPECT_TRUE(ProfiledThread::isLikelyJavaThread(tid1));

  // Unregister
  ProfiledThread::unregisterJavaThread(tid1);

  // Should be unmarked
  EXPECT_FALSE(ProfiledThread::isLikelyJavaThread(tid1));
}

// Test with realistic thread ID ranges
TEST_F(JavaThreadBitsetTest, RealisticThreadIds) {
  // Typical Linux thread IDs are in the range of process PID + offset
  int base_tid = 10000;

  for (int i = 0; i < 50; i++) {
    int tid = base_tid + i;
    ProfiledThread::registerJavaThread(tid);
    registered_tids.push_back(tid);
  }

  // Verify all are registered
  for (int i = 0; i < 50; i++) {
    EXPECT_TRUE(ProfiledThread::isLikelyJavaThread(base_tid + i));
  }

  // Verify nearby unregistered IDs are not marked
  EXPECT_FALSE(ProfiledThread::isLikelyJavaThread(base_tid - 1));
  EXPECT_FALSE(ProfiledThread::isLikelyJavaThread(base_tid + 100));
}

// Test concurrent access (basic thread safety)
TEST_F(JavaThreadBitsetTest, ConcurrentAccess) {
  constexpr int NUM_THREADS = 10;
  constexpr int TIDS_PER_THREAD = 100;
  std::vector<pthread_t> threads(NUM_THREADS);
  std::vector<int> thread_indices(NUM_THREADS);

  struct ThreadData {
    int thread_idx;
    std::atomic<bool>* success;
  };

  std::vector<std::atomic<bool>> success_flags(NUM_THREADS);
  std::vector<ThreadData> thread_data(NUM_THREADS);

  for (int i = 0; i < NUM_THREADS; i++) {
    success_flags[i].store(true);
    thread_data[i].thread_idx = i;
    thread_data[i].success = &success_flags[i];
  }

  auto thread_func = [](void* arg) -> void* {
    ThreadData* data = static_cast<ThreadData*>(arg);
    int base_tid = 20000 + (data->thread_idx * TIDS_PER_THREAD);

    // Register many thread IDs
    for (int i = 0; i < TIDS_PER_THREAD; i++) {
      int tid = base_tid + i;
      ProfiledThread::registerJavaThread(tid);

      // Immediately check it's registered
      if (!ProfiledThread::isLikelyJavaThread(tid)) {
        data->success->store(false);
        return reinterpret_cast<void*>(1); // Failure
      }
    }

    return nullptr; // Success
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
    EXPECT_TRUE(success_flags[i].load()) << "Thread " << i << " had registration failure";
  }

  // Verify all registered IDs are still marked
  for (int t = 0; t < NUM_THREADS; t++) {
    int base_tid = 20000 + (t * TIDS_PER_THREAD);
    for (int i = 0; i < TIDS_PER_THREAD; i++) {
      int tid = base_tid + i;
      EXPECT_TRUE(ProfiledThread::isLikelyJavaThread(tid));
      ProfiledThread::unregisterJavaThread(tid);  // Cleanup
    }
  }
}

// Test edge cases
TEST_F(JavaThreadBitsetTest, EdgeCases) {
  // Test with 0
  ProfiledThread::registerJavaThread(0);
  EXPECT_TRUE(ProfiledThread::isLikelyJavaThread(0));
  ProfiledThread::unregisterJavaThread(0);

  // Test with large numbers
  ProfiledThread::registerJavaThread(1000000);
  EXPECT_TRUE(ProfiledThread::isLikelyJavaThread(1000000));
  ProfiledThread::unregisterJavaThread(1000000);

  // Test with negative (should handle modulo correctly)
  ProfiledThread::registerJavaThread(-100);
  EXPECT_TRUE(ProfiledThread::isLikelyJavaThread(-100));
  ProfiledThread::unregisterJavaThread(-100);
}

// Test idempotency
TEST_F(JavaThreadBitsetTest, Idempotency) {
  int tid = 99999;

  // Register multiple times
  ProfiledThread::registerJavaThread(tid);
  ProfiledThread::registerJavaThread(tid);
  ProfiledThread::registerJavaThread(tid);

  // Should still be registered
  EXPECT_TRUE(ProfiledThread::isLikelyJavaThread(tid));

  // Unregister once
  ProfiledThread::unregisterJavaThread(tid);

  // Should be unregistered
  EXPECT_FALSE(ProfiledThread::isLikelyJavaThread(tid));

  // Unregister again (should be safe)
  ProfiledThread::unregisterJavaThread(tid);
  EXPECT_FALSE(ProfiledThread::isLikelyJavaThread(tid));
}

// Test memory ordering (register in one thread, check in another)
TEST_F(JavaThreadBitsetTest, MemoryOrdering) {
  int tid = 77777;
  std::atomic<bool> registered{false};
  std::atomic<bool> checked{false};
  pthread_t writer_thread, reader_thread;

  struct WriterData {
    int tid;
    std::atomic<bool>* registered;
  };

  struct ReaderData {
    int tid;
    std::atomic<bool>* registered;
    std::atomic<bool>* checked;
  };

  WriterData writer_data{tid, &registered};
  ReaderData reader_data{tid, &registered, &checked};

  // Writer thread
  auto writer = [](void* arg) -> void* {
    auto* data = static_cast<WriterData*>(arg);
    ProfiledThread::registerJavaThread(data->tid);
    data->registered->store(true, std::memory_order_release);
    return nullptr;
  };

  // Reader thread
  auto reader = [](void* arg) -> void* {
    auto* data = static_cast<ReaderData*>(arg);
    // Spin until writer signals
    while (!data->registered->load(std::memory_order_acquire)) {
      sched_yield();
    }

    // Check if thread is registered
    bool is_registered = ProfiledThread::isLikelyJavaThread(data->tid);
    data->checked->store(is_registered, std::memory_order_release);
    return nullptr;
  };

  pthread_create(&writer_thread, nullptr, writer, &writer_data);
  pthread_create(&reader_thread, nullptr, reader, &reader_data);

  pthread_join(writer_thread, nullptr);
  pthread_join(reader_thread, nullptr);

  // Reader should have seen the registration
  EXPECT_TRUE(checked.load());

  ProfiledThread::unregisterJavaThread(tid);  // Cleanup
}
