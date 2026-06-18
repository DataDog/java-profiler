/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "taskBlockQueue.h"

#include <atomic>
#include <thread>
#include <vector>

namespace {

static QueuedTaskBlockEvent eventWithId(int id) {
  QueuedTaskBlockEvent event{};
  event.tid = id + 1000;
  event.generation = static_cast<u64>(id + 2000);
  event.event._start = static_cast<u64>(id);
  event.event._end = static_cast<u64>(id + 1);
  event.event._blocker = static_cast<u64>(id);
  return event;
}

static void markSeen(const QueuedTaskBlockEvent& event,
                     std::vector<std::atomic<int>>& seen,
                     std::atomic<int>& failures) {
  int id = static_cast<int>(event.event._blocker);
  if (id < 0 || static_cast<size_t>(id) >= seen.size()) {
    failures.fetch_add(1, std::memory_order_relaxed);
    return;
  }
  int expected = 0;
  if (!seen[id].compare_exchange_strong(expected, 1, std::memory_order_relaxed)) {
    failures.fetch_add(1, std::memory_order_relaxed);
  }
  if (event.tid != id + 1000 ||
      event.generation != static_cast<u64>(id + 2000) ||
      event.event._start != static_cast<u64>(id) ||
      event.event._end != static_cast<u64>(id + 1)) {
    failures.fetch_add(1, std::memory_order_relaxed);
  }
}

static void expectAllSeen(const std::vector<std::atomic<int>>& seen) {
  for (size_t i = 0; i < seen.size(); i++) {
    EXPECT_EQ(1, seen[i].load(std::memory_order_relaxed)) << "missing event " << i;
  }
}

static void clearSeen(std::vector<std::atomic<int>>& seen) {
  for (std::atomic<int>& value : seen) {
    value.store(0, std::memory_order_relaxed);
  }
}

} // namespace

TEST(TaskBlockQueueTest, PreservesQueuedEventFields) {
  TaskBlockQueue queue;
  QueuedTaskBlockEvent in{};
  in.tid = 123;
  in.generation = 7;
  in.event._start = 10;
  in.event._end = 20;
  in.event._blocker = 30;
  in.event._unblockingSpanId = 40;
  in.event._ctx.spanId = 50;
  in.event._ctx.rootSpanId = 60;
  in.event._callTraceId = 70;
  in.event._correlationId = 80;

  ASSERT_TRUE(queue.tryPush(in));

  QueuedTaskBlockEvent out{};
  ASSERT_TRUE(queue.tryPop(out));
  EXPECT_EQ(in.tid, out.tid);
  EXPECT_EQ(in.generation, out.generation);
  EXPECT_EQ(in.event._start, out.event._start);
  EXPECT_EQ(in.event._end, out.event._end);
  EXPECT_EQ(in.event._blocker, out.event._blocker);
  EXPECT_EQ(in.event._unblockingSpanId, out.event._unblockingSpanId);
  EXPECT_EQ(in.event._ctx.spanId, out.event._ctx.spanId);
  EXPECT_EQ(in.event._ctx.rootSpanId, out.event._ctx.rootSpanId);
  EXPECT_EQ(in.event._callTraceId, out.event._callTraceId);
  EXPECT_EQ(in.event._correlationId, out.event._correlationId);
  EXPECT_FALSE(queue.tryPop(out));
}

TEST(TaskBlockQueueTest, FullQueueRejectsWithoutBlocking) {
  TaskBlockQueue queue;
  QueuedTaskBlockEvent event{};
  int accepted = 0;
  while (queue.tryPush(event)) {
    accepted++;
  }

  EXPECT_GT(accepted, 0);
  EXPECT_FALSE(queue.tryPush(event));

  QueuedTaskBlockEvent out{};
  for (int i = 0; i < accepted; i++) {
    ASSERT_TRUE(queue.tryPop(out));
  }
  EXPECT_FALSE(queue.tryPop(out));
  EXPECT_TRUE(queue.tryPush(event));
}

TEST(TaskBlockQueueTest, DiscardAllEmptiesQueue) {
  TaskBlockQueue queue;
  QueuedTaskBlockEvent event{};
  ASSERT_TRUE(queue.tryPush(event));
  ASSERT_TRUE(queue.tryPush(event));

  queue.discardAll();

  QueuedTaskBlockEvent out{};
  EXPECT_FALSE(queue.tryPop(out));
}

TEST(TaskBlockQueueTest, ConcurrentMultiProducerSingleConsumerPreservesAllEvents) {
  TaskBlockQueue queue;
  static constexpr int kProducers = 4;
  static constexpr int kEventsPerProducer = 2048;
  static constexpr int kTotalEvents = kProducers * kEventsPerProducer;
  std::vector<std::atomic<int>> seen(kTotalEvents);
  clearSeen(seen);
  std::atomic<int> consumed{0};
  std::atomic<int> failures{0};

  std::thread consumer([&]() {
    QueuedTaskBlockEvent event{};
    while (consumed.load(std::memory_order_acquire) < kTotalEvents) {
      if (queue.tryPop(event)) {
        markSeen(event, seen, failures);
        consumed.fetch_add(1, std::memory_order_release);
      } else {
        std::this_thread::yield();
      }
    }
  });

  std::vector<std::thread> producers;
  for (int producer = 0; producer < kProducers; producer++) {
    producers.emplace_back([&, producer]() {
      int base = producer * kEventsPerProducer;
      for (int offset = 0; offset < kEventsPerProducer; offset++) {
        QueuedTaskBlockEvent event = eventWithId(base + offset);
        while (!queue.tryPush(event)) {
          std::this_thread::yield();
        }
      }
    });
  }

  for (std::thread& producer : producers) {
    producer.join();
  }
  consumer.join();

  EXPECT_EQ(0, failures.load(std::memory_order_relaxed));
  EXPECT_EQ(kTotalEvents, consumed.load(std::memory_order_relaxed));
  expectAllSeen(seen);
}

TEST(TaskBlockQueueTest, ConcurrentMultiProducerMultiConsumerPreservesAllEvents) {
  TaskBlockQueue queue;
  static constexpr int kProducers = 4;
  static constexpr int kConsumers = 2;
  static constexpr int kEventsPerProducer = 2048;
  static constexpr int kTotalEvents = kProducers * kEventsPerProducer;
  std::vector<std::atomic<int>> seen(kTotalEvents);
  clearSeen(seen);
  std::atomic<int> consumed{0};
  std::atomic<int> failures{0};

  std::vector<std::thread> consumers;
  for (int consumer_index = 0; consumer_index < kConsumers; consumer_index++) {
    consumers.emplace_back([&]() {
      QueuedTaskBlockEvent event{};
      while (consumed.load(std::memory_order_acquire) < kTotalEvents) {
        if (queue.tryPop(event)) {
          markSeen(event, seen, failures);
          consumed.fetch_add(1, std::memory_order_release);
        } else {
          std::this_thread::yield();
        }
      }
    });
  }

  std::vector<std::thread> producers;
  for (int producer = 0; producer < kProducers; producer++) {
    producers.emplace_back([&, producer]() {
      int base = producer * kEventsPerProducer;
      for (int offset = 0; offset < kEventsPerProducer; offset++) {
        QueuedTaskBlockEvent event = eventWithId(base + offset);
        while (!queue.tryPush(event)) {
          std::this_thread::yield();
        }
      }
    });
  }

  for (std::thread& producer : producers) {
    producer.join();
  }
  for (std::thread& consumer : consumers) {
    consumer.join();
  }

  EXPECT_EQ(0, failures.load(std::memory_order_relaxed));
  EXPECT_EQ(kTotalEvents, consumed.load(std::memory_order_relaxed));
  expectAllSeen(seen);
}
