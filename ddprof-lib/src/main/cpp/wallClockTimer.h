/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _WALLCLOCKTIMER_H
#define _WALLCLOCKTIMER_H

#include "arch.h"

// A monotonic opportunity schedule, not elapsed-time sample weighting. Carry
// wakeup lateness and timer work into the next wait instead of adding them to
// every interval. If a whole deadline is missed, restart from now: never replay
// missed opportunities in a catch-up burst.
class WallClockTimer {
    u64 _deadline;

public:
    explicit WallClockTimer(u64 now) : _deadline(now) {}

    u64 nextSleep(u64 now, u64 interval) {
        _deadline += interval;
        if (_deadline <= now) {
            _deadline = now + interval;
        }
        return _deadline - now;
    }
};

#endif // _WALLCLOCKTIMER_H
