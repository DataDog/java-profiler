/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "taskBlockQueue.h"

#include <stdint.h>

TaskBlockQueue::TaskBlockQueue() : _enqueue_pos(0), _dequeue_pos(0) {
  for (size_t i = 0; i < kCapacity; i++) {
    _buffer[i].sequence.store(i, std::memory_order_relaxed);
  }
}

bool TaskBlockQueue::tryPush(const QueuedTaskBlockEvent& event) {
  Cell* cell;
  size_t pos = _enqueue_pos.load(std::memory_order_relaxed);
  for (;;) {
    cell = &_buffer[pos & (kCapacity - 1)];
    size_t seq = cell->sequence.load(std::memory_order_acquire);
    intptr_t diff = (intptr_t)seq - (intptr_t)pos;
    if (diff == 0) {
      if (_enqueue_pos.compare_exchange_weak(pos, pos + 1,
                                             std::memory_order_relaxed)) {
        break;
      }
    } else if (diff < 0) {
      return false;
    } else {
      pos = _enqueue_pos.load(std::memory_order_relaxed);
    }
  }

  cell->data = event;
  cell->sequence.store(pos + 1, std::memory_order_release);
  return true;
}

bool TaskBlockQueue::tryPop(QueuedTaskBlockEvent& event) {
  Cell* cell;
  size_t pos = _dequeue_pos.load(std::memory_order_relaxed);
  for (;;) {
    cell = &_buffer[pos & (kCapacity - 1)];
    size_t seq = cell->sequence.load(std::memory_order_acquire);
    intptr_t diff = (intptr_t)seq - (intptr_t)(pos + 1);
    if (diff == 0) {
      if (_dequeue_pos.compare_exchange_weak(pos, pos + 1,
                                             std::memory_order_relaxed)) {
        break;
      }
    } else if (diff < 0) {
      return false;
    } else {
      pos = _dequeue_pos.load(std::memory_order_relaxed);
    }
  }

  event = cell->data;
  cell->sequence.store(pos + kCapacity, std::memory_order_release);
  return true;
}

void TaskBlockQueue::discardAll() {
  QueuedTaskBlockEvent event;
  while (tryPop(event)) {
  }
}
