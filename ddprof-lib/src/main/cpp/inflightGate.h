/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _INFLIGHT_GATE_H
#define _INFLIGHT_GATE_H

#include "arch.h"

#include <stdint.h>
#include <time.h>

// A gate in front of a per-recording resource that is reachable from code the
// profiler does not control the timing of: hooks, JVMTI callbacks, JNI entry
// points, or the tail of a signal handler. The owner opens the gate once the
// resource is published, and before freeing it closes the gate and drains the
// callers that are already inside.
//
//   InflightGate::Scope scope(gate);
//   if (!scope.entered()) return;   // closed: the resource may be gone
//   ... use the resource ...
//
//   owner:  gate.close(); if (gate.drain(timeout)) free(resource); else leak it
//
// SignalInflight (signalInflight.h) is the process-wide counterpart for the
// signal handlers that write JFR; this is the general-purpose, per-resource one.
//
// Async-signal-safe and allocation-free. The counters are striped by stack
// address so concurrent callers don't bounce one cache line. The constructor is
// constexpr, so a static gate is constant-initialized and costs no resident
// memory until it is used.
//
// Ordering (Dekker): enter() increments its stripe and then re-checks _open;
// close() clears _open and drain() then reads the stripes, all seq_cst. A
// caller that saw the gate open is therefore visible to drain(), and a caller
// that increments after close() backs out without touching the resource.
class InflightGate {
public:
  static constexpr int STRIPES = 16;

  constexpr InflightGate() : _open(false), _stripes{} {}

  InflightGate(const InflightGate&) = delete;
  InflightGate& operator=(const InflightGate&) = delete;

  void open() { __atomic_store_n(&_open, true, __ATOMIC_SEQ_CST); }
  void close() { __atomic_store_n(&_open, false, __ATOMIC_SEQ_CST); }
  bool isOpen() const { return __atomic_load_n(&_open, __ATOMIC_ACQUIRE); }

  // Returns the stripe to pass to exit(), or -1 when the gate is closed.
  int enter() {
    int stripe = stripeIndex();
    __atomic_fetch_add(&_stripes[stripe].count, 1, __ATOMIC_SEQ_CST);
    if (!__atomic_load_n(&_open, __ATOMIC_SEQ_CST)) {
      __atomic_fetch_sub(&_stripes[stripe].count, 1, __ATOMIC_RELEASE);
      return -1;
    }
    return stripe;
  }

  void exit(int stripe) {
    __atomic_fetch_sub(&_stripes[stripe].count, 1, __ATOMIC_RELEASE);
  }

  bool hasInflight() const {
    for (int i = 0; i < STRIPES; i++) {
      if (__atomic_load_n(&_stripes[i].count, __ATOMIC_SEQ_CST) != 0) {
        return true;
      }
    }
    return false;
  }

  // Waits until no caller is inside, or until timeout_ns elapses. Call after
  // close(). Returns false on timeout: the caller must then leak the resource
  // instead of freeing it.
  bool drain(long timeout_ns) const {
    if (!hasInflight()) {
      return true;
    }
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    struct timespec pause = {0, 100000};  // 100 us
    for (;;) {
      if (!hasInflight()) {
        return true;
      }
      struct timespec now;
      clock_gettime(CLOCK_MONOTONIC, &now);
      long elapsed = (now.tv_sec - start.tv_sec) * 1000000000L + (now.tv_nsec - start.tv_nsec);
      if (elapsed >= timeout_ns) {
        return false;
      }
      nanosleep(&pause, nullptr);
    }
  }

  // RAII enter/exit.
  class Scope {
  public:
    explicit Scope(InflightGate& gate) : _gate(gate), _stripe(gate.enter()) {}
    ~Scope() {
      if (_stripe >= 0) {
        _gate.exit(_stripe);
      }
    }
    bool entered() const { return _stripe >= 0; }

    Scope(const Scope&) = delete;
    Scope& operator=(const Scope&) = delete;

  private:
    InflightGate& _gate;
    int _stripe;
  };

private:
  struct alignas(DEFAULT_CACHE_LINE_SIZE) Stripe {
    int count;
  };

  static int stripeIndex() {
    // Threads run on distinct stacks, so the stack address spreads callers
    // across stripes without a syscall or TLS access.
    int marker;
    return (int)(((uintptr_t)&marker >> 14) % STRIPES);
  }

  bool _open;
  Stripe _stripes[STRIPES];
};

#endif // _INFLIGHT_GATE_H
