/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _NATIVE_BLOCK_H
#define _NATIVE_BLOCK_H

#include "arch.h"

#if defined(__linux__)

#include "context.h"
#include "threadFilter.h"
#include "threadState.h"

enum class NativeBlockKind : u32 {
  STREAM_SOCKET = 1,
  CONNECT = 2,
  ACCEPT = 3,
  UDP_RECEIVE = 4,
  POLL = 5,
  SELECT = 6,
  EPOLL_WAIT = 7,
};

class NativeBlockScope {
public:
  NativeBlockScope(NativeBlockKind kind, int blocker_id,
                   OSThreadState state = OSThreadState::IO_WAIT);
  ~NativeBlockScope();

  NativeBlockScope(const NativeBlockScope&) = delete;
  NativeBlockScope& operator=(const NativeBlockScope&) = delete;

  bool active() const { return _active; }

  static u64 blocker(NativeBlockKind kind, int blocker_id) {
    return (static_cast<u64>(kind) << 32) | static_cast<uint32_t>(blocker_id);
  }

private:
  bool _active = false;
  int _tid = -1;
  ThreadFilter::SlotID _slot_id = -1;
  u32 _generation = 0;
  u64 _start_ticks = 0;
  u64 _blocker = 0;
  OSThreadState _state = OSThreadState::UNKNOWN;
  Context _context = {};

  void finish(u64 end_ticks);
};

#endif // __linux__

#endif // _NATIVE_BLOCK_H
