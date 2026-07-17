/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _PAINBUDGET_H
#define _PAINBUDGET_H

#include "arch.h"

/*
 * A leaky bucket over *cost* (milliseconds of expensive work already spent),
 * not over an event *rate* - unlike PidController/RateLimiter (which target
 * a steady events-per-second throughput), this answers "have we spent too
 * much recently to justify doing more expensive work right now?"
 *
 * Typical use: a subsystem that occasionally does one genuinely expensive,
 * bounded operation (here: a full-heap BFS pass) wants to avoid doing that
 * operation back-to-back if it keeps being expensive, while still allowing
 * it immediately again if the last one was cheap. spend() records how much
 * an operation cost; canStartNow() drains the balance by however much
 * wall-clock time has passed (at _refill_rate) and reports whether the
 * debt has cleared.
 *
 * _refill_rate is the one tunable: the fraction of wall-clock time this
 * budget is willing to let its owner spend on the expensive operation, on
 * average (e.g. 0.01 = "at most ~1% of wall-clock time, averaged over
 * time"). Unlike PidController's gain triples (P/I/D), this single ratio
 * has a direct, human-interpretable meaning and needs no derivation beyond
 * picking that target fraction.
 */
class PainBudget {
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
    _balance_ms -= elapsed_ms * _refill_rate;
    if (_balance_ms < 0) {
      _balance_ms = 0;
    }
    _last_update_ns = now_ns;
  }

public:
  explicit PainBudget(double refill_rate = 0.0)
      : _balance_ms(0), _refill_rate(refill_rate), _last_update_ns(0) {}

  // Records that an operation just cost `pain_ms` milliseconds of
  // wall-clock time. Does not drain first - the cost is added on top of
  // whatever debt (already correctly drained as of the last canStartNow()
  // call) currently exists.
  void spend(u64 pain_ms) { _balance_ms += (double)pain_ms; }

  // True once the debt has drained back to zero at _refill_rate - i.e. it
  // is now affordable, on average, to spend more pain. Drains the balance
  // as a side effect, so repeated calls correctly reflect elapsed time
  // even if spend() is never called again.
  bool canStartNow(u64 now_ns) {
    drain(now_ns);
    return _balance_ms <= 0;
  }

  // Test/introspection only - current debt after draining as of now_ns.
  double balanceMs(u64 now_ns) {
    drain(now_ns);
    return _balance_ms;
  }
};

#endif // _PAINBUDGET_H
