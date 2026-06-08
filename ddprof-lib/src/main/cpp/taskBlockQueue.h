/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _TASK_BLOCK_QUEUE_H
#define _TASK_BLOCK_QUEUE_H

#include "arch.h"
#include "event.h"
#include <atomic>
#include <stddef.h>

struct QueuedTaskBlockEvent {
  int tid;
  u64 generation;
  TaskBlockEvent event;
};

class TaskBlockQueue {
private:
  static const size_t kCapacity = 4096;
  static_assert((kCapacity & (kCapacity - 1)) == 0,
                "TaskBlockQueue capacity must be a power of two");

  struct Cell {
    std::atomic<size_t> sequence;
    QueuedTaskBlockEvent data;
  };

  Cell _buffer[kCapacity];
  std::atomic<size_t> _enqueue_pos;
  std::atomic<size_t> _dequeue_pos;

public:
  // Bounded MPMC sequence-cell queue. Producers publish data before the cell
  // sequence release-store; consumers acquire-load the sequence before reading
  // data. Position CASes only reserve slots, so relaxed ordering is sufficient.
  TaskBlockQueue();

  TaskBlockQueue(const TaskBlockQueue&) = delete;
  void operator=(const TaskBlockQueue&) = delete;

  bool tryPush(const QueuedTaskBlockEvent& event);
  bool tryPop(QueuedTaskBlockEvent& event);
  void discardAll();
};

#endif // _TASK_BLOCK_QUEUE_H
