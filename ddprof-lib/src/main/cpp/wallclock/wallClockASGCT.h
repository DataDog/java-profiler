/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _WALLCLOCKASGCT_H
#define _WALLCLOCKASGCT_H

#include "wallclock/wallClock.h"

class WallClockASGCT : public BaseWallClock {
  private:
    bool _collapsing;

    static bool inSyscall(void* ucontext);

    static void sharedSignalHandler(int signo, siginfo_t* siginfo, void* ucontext);
    void signalHandler(int signo, siginfo_t* siginfo, void* ucontext, u64 last_sample);

    void initialize(Arguments& args) override;
    void timerLoop() override;

  public:
    WallClockASGCT() : BaseWallClock(), _collapsing(false) {}
    const char* name() const override {
        return "WallClock (ASGCT)";
    }
    Mode mode() const override { return Mode::ASGCT; }
};

#endif // _WALLCLOCKASGCT_H
