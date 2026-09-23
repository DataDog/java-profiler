/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _PAINBUDGET_H
#define _PAINBUDGET_H

#include "arch.h"

/*
 * Leaky bucket over cost (ms of expensive work), not over an event rate:
 * spend() records the cost; canStartNow() drains the balance by elapsed
 * wall-clock time at _refill_rate and reports whether the debt has cleared.
 * _refill_rate = average fraction of wall-clock time allowed (0.01 = ~1%).
 */class PainBudget {
private:
  double _balance_ms;    // accumulated debt in ms; 0 means "clear to spend"
  double _refill_rate;   // fraction of wall-clock time allowed, e.g. 0.01
  u64 _last_update_ns;   // OS::nanotime() as of the last drain(); 0 = never drained yet

  void drain(u64 now_ns) {
    if (_last_update_ns == 0) {
      // First call ever - nothing to drain yet, just establish the baseline.
      _last_update_ns = now_ns;
      return;
    }
    u64 elapsed_ns = now_ns - _last_update_ns;
    double elapsed_ms = (double)elapsed_ns / 1000000.0;
    // _refill_rate == 0.0 (the default) means the balance never drains:
    // once spend() pushes it above 0, canStartNow() stays false forever.
    _balance_ms -= elapsed_ms * _refill_rate;
    if (_balance_ms < 0) {
      _balance_ms = 0;
    }
    _last_update_ns = now_ns;
  }

public:
  explicit PainBudget(double refill_rate = 0.0)
      : _balance_ms(0), _refill_rate(refill_rate), _last_update_ns(0) {}

  // Adds an operation's cost in ms on top of the current debt.
  void spend(u64 pain_ms) { _balance_ms += (double)pain_ms; }

  // True once the debt has drained back to zero at _refill_rate. Drains
  // the balance as a side effect, so repeated calls track elapsed time.
  bool canStartNow(u64 now_ns) {
    drain(now_ns);
    return _balance_ms <= 0;
  }

  // Test/introspection only - current debt after draining as of now_ns.
  double balanceMs(u64 now_ns) {
    drain(now_ns);
    return _balance_ms;
  }

  // Changes the refill rate without resetting accumulated debt (unlike
  // a fresh PainBudget(rate), which zeroes _balance_ms); drains at the
  // old rate up to now_ns first.
  void setRefillRate(double refill_rate, u64 now_ns) {
    drain(now_ns);
    _refill_rate = refill_rate;
  }
};

#endif // _PAINBUDGET_H
