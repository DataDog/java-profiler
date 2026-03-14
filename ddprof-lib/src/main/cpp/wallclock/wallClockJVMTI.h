/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _WALLCLOCKJVMTI_H
#define _WALLCLOCKJVMTI_H

#include "wallclock/wallClock.h"

class WallClockJVMTI : public BaseWallClock {
protected:
    void timerLoop() override;

  public:
    struct ThreadEntry {
        jthread java;
        long tid;
    };
    WallClockJVMTI() : BaseWallClock() {}
    const char* name() const override {
        return "WallClock (JVMTI)";
    }

    Mode mode() const override { return Mode::JVMTI; }
};

#endif // _WALLCLOCKJVMTI_H
